/*
 *Copyright (C) 2010-2011 Project StarGate
 */

#include <ace/Dev_Poll_Reactor.h>
#include <ace/TP_Reactor.h>
#include <ace/ACE.h>
#include <ace/Sig_Handler.h>
#include <openssl/opensslv.h>
#include <openssl/crypto.h>

#include "Common.h"
#include "Database/DatabaseEnv.h"

#include "Configuration/Config.h"
#include "Log.h"
#include "SystemConfig.h"
#include "Util.h"
#include "SignalHandler.h"
#include "RealmList.h"
#include "RealmAcceptor.h"

#ifndef _TRINITY_REALM_CONFIG
# define _TRINITY_REALM_CONFIG  "authserver.conf"
#endif //_TRINITY_REALM_CONFIG

#ifdef _WIN32
#include "ServiceWin32.h"
char serviceName[] = "authserver";
char serviceLongName[] = "StarGateEMU Auth service";
char serviceDescription[] = "StarGateEMU World of Warcraft emulator world auth service";
/*
 * -1 - not in service mode
 *  0 - stopped
 *  1 - running
 *  2 - paused
 */
int m_ServiceStatus = -1;
#endif

bool StartDB();

bool stopEvent = false;                                     ///< Setting it to true stops the server

LoginDatabaseWorkerPool LoginDatabase;                      ///< Accessor to the realm server database

/// Handle realmd's termination signals
class RealmdSignalHandler : public Trinity::SignalHandler
{
    public:
        virtual void HandleSignal(int SigNum)
        {
            switch (SigNum)
            {
                case SIGINT:
                case SIGTERM:
                    stopEvent = true;
                    break;
#ifdef _WIN32
                case SIGBREAK:
                    if (m_ServiceStatus != 1)
                        stopEvent = true;
                    break;
#endif /* _WIN32 */
            }
        }
};

/// Print out the usage string for this program on the console.
void usage(const char *prog)
{
    sLog->outString("Verwendung: \n %s [<options>]\n"
        "    -c config_file           use config_file as configuration file\n\r"
#ifdef _WIN32
        "    Running as service functions:\n\r"
        "    --service                run as service\n\r"
        "    -s install               install service\n\r"
        "    -s uninstall             uninstall service\n\r"
#endif
        , prog);
}

/// Launch the realm server
extern int main(int argc, char **argv)
{
    sLog->SetLogDB(false);

    ///- Command line parsing to get the configuration file name
    char const* cfg_file = _TRINITY_REALM_CONFIG;
    int c = 1;
    while(c < argc)
    {
        if (strcmp(argv[c], "-c") == 0)
        {
            if (++c >= argc)
            {
                sLog->outError("Runtime-Error: -c option requires an input argument");
                usage(argv[0]);
                return 1;
            }
            else
                cfg_file = argv[c];
        }

#ifdef _WIN32
        ////////////
        //Services//
        ////////////
        if (strcmp(argv[c], "-s") == 0)
        {
            if (++c >= argc)
            {
                sLog->outError("Runtime-Error: -s option requires an input argument");
                usage(argv[0]);
                return 1;
            }
            if (strcmp(argv[c], "install") == 0)
            {
                if (WinServiceInstall())
                    sLog->outString("Installiere Service");
                return 1;
            }
            else if (strcmp(argv[c], "uninstall") == 0)
            {
                if (WinServiceUninstall())
                    sLog->outString("Deinstalliere Service");
                return 1;
            }
            else
            {
                sLog->outError("Runtime-Error: unsupported option %s", argv[c]);
                usage(argv[0]);
                return 1;
            }
        }

        if (strcmp(argv[c], "--service") == 0)
            WinServiceRun();

#endif
        ++c;
    }

    if (!sConfig->SetSource(cfg_file))
    {
        sLog->outError("Invalid or missing configuration file : %s", cfg_file);
        sLog->outError("Verify that the file exists and has \'[authserver]\' written in the top of the file!");
        return 1;
    }
    sLog->Initialize();
    sLog->outString(" ");
    sLog->outString("  #####                       #####                      ");
    sLog->outString(" #     # #####   ##   #####  #     #   ##   ##### ###### ");
    sLog->outString(" #         #    #  #  #    # #        #  #    #   #      ");
    sLog->outString("  #####    #   #    # #    # #  #### #    #   #   #####  ");
    sLog->outString("       #   #   ###### #####  #     # ######   #   #      ");
    sLog->outString(" #     #   #   #    # #   #  #     # #    #   #   #      ");
    sLog->outString("  #####    #   #    # #    #  #####  #    #   #   ######" );
    sLog->outString(" ");
    sLog->outString("               Project StarGateEmu 2011 (c)               ");
    sLog->outString(" ");
    sLog->outString("    %s ", _FULLVERSION);
    sLog->outString(" ");
    sLog->outString(" ");


    sLog->outDetail("%s (Library: %s)", OPENSSL_VERSION_TEXT, SSLeay_version(SSLEAY_VERSION));

#if defined (ACE_HAS_EVENT_POLL) || defined (ACE_HAS_DEV_POLL)
    ACE_Reactor::instance(new ACE_Reactor(new ACE_Dev_Poll_Reactor(ACE::max_handles(), 1), 1), true);
#else
    ACE_Reactor::instance(new ACE_Reactor(new ACE_TP_Reactor(), true), true);
#endif

    sLog->outBasic("Max. zulässige offene Dateien %d", ACE::max_handles());

    /// realmd PID file creation
    std::string pidfile = sConfig->GetStringDefault("PidFile", "");
    if (!pidfile.empty())
    {
        uint32 pid = CreatePIDFile(pidfile);
        if (!pid)
        {
            sLog->outError("Cannot create PID file %s.\n", pidfile.c_str());
            return 1;
        }

        sLog->outString("Daemon PID: %u\n", pid);
    }

    ///- Initialize the database connection
    if (!StartDB())
        return 1;

    ///- Initialize the log database
    sLog->SetLogDBLater(sConfig->GetBoolDefault("EnableLogDB", false)); // set var to enable DB logging once startup finished.
    sLog->SetLogDB(false);
    sLog->SetRealmID(0);                                               // ensure we've set realm to 0 (realmd realmid)

    ///- Get the list of realms for the server
    sRealmList->Initialize(sConfig->GetIntDefault("RealmsStateUpdateDelay", 20));
    if (sRealmList->size() == 0)
    {
        sLog->outError("Keine gültige Bereiche angegeben.");
        return 1;
    }

    ///- Launch the listening network socket
    RealmAcceptor acceptor;

    uint16 rmport = sConfig->GetIntDefault("RealmServerPort", 3724);
    std::string bind_ip = sConfig->GetStringDefault("BindIP", "0.0.0.0");

    ACE_INET_Addr bind_addr(rmport, bind_ip.c_str());

    if (acceptor.open(bind_addr, ACE_Reactor::instance(), ACE_NONBLOCK) == -1)
    {
        sLog->outError("StarGateAuth nicht zu binden %s:%d", bind_ip.c_str(), rmport);
        return 1;
    }

    // Initialise the signal handlers
    RealmdSignalHandler SignalINT, SignalTERM;
#ifdef _WIN32
    RealmdSignalHandler SignalBREAK;
#endif /* _WIN32 */

    // Register realmd's signal handlers
    ACE_Sig_Handler Handler;
    Handler.register_handler(SIGINT, &SignalINT);
    Handler.register_handler(SIGTERM, &SignalTERM);
#ifdef _WIN32
    Handler.register_handler(SIGBREAK, &SignalBREAK);
#endif /* _WIN32 */

    ///- Handle affinity for multiple processors and process priority on Windows
#ifdef _WIN32
    {
        HANDLE hProcess = GetCurrentProcess();

        uint32 Aff = sConfig->GetIntDefault("UseProcessors", 0);
        if (Aff > 0)
        {
            ULONG_PTR appAff;
            ULONG_PTR sysAff;

            if (GetProcessAffinityMask(hProcess, &appAff, &sysAff))
            {
                ULONG_PTR curAff = Aff & appAff;            // remove non accessible processors

                if (!curAff)
                    sLog->outError("Prozessoren in UseProcessors Bitmaske markiert (hex) %x nicht zugänglich realmd. Accessible Prozessor Bitmaske (hex): %x", Aff, appAff);
                else if (SetProcessAffinityMask(hProcess, curAff))
                    sLog->outString("Mit Prozessoren (bitmask, hex): %x", curAff);
                else
                    sLog->outError("Kann verwendeter Prozessor nicht festgelegen!.(hex): %x", curAff);
            }
        }

        bool Prio = sConfig->GetBoolDefault("ProcessPriority", false);

        if (Prio)
        {
            if (SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS))
                sLog->outString("[StarGate-Auth] Prozess-Priorität festgelegt auf HOCH");
            else
                sLog->outError("Realmd Prozess-Priorität Fehler!.");
        }
    }
#endif

    // maximum counter for next ping
    uint32 numLoops = (sConfig->GetIntDefault("MaxPingTime", 30) * (MINUTE * 1000000 / 100000));
    uint32 loopCounter = 0;

    // possibly enable db logging; avoid massive startup spam by doing it here.
    if (sLog->GetLogDBLater())
    {
        sLog->outString("Aktiviere Datenbankprotokollierung...");
        sLog->SetLogDBLater(false);

        // login db needs thread for logging
        sLog->SetLogDB(true);
    }
    else
        sLog->SetLogDB(false);

    ///- Wait for termination signal
    while (!stopEvent)
    {
        // dont move this outside the loop, the reactor will modify it
        ACE_Time_Value interval(0, 100000);

        if (ACE_Reactor::instance()->run_reactor_event_loop(interval) == -1)
            break;

        if ((++loopCounter) == numLoops)
        {
            loopCounter = 0;
            sLog->outDetail("Ping MySQL: Verbindung aufrecht zu erhalten");
            LoginDatabase.KeepAlive();
        }
#ifdef _WIN32
        if (m_ServiceStatus == 0)
            stopEvent = true;
        else
        {
            while (m_ServiceStatus == 2)
                Sleep(1000);
        }
#endif
    }

    ///- Close the Database Pool
    LoginDatabase.Close();

    sLog->outString("Halte Prozess...");
    return 0;
}

/// Initialize connection to the database
bool StartDB()
{
    std::string dbstring = sConfig->GetStringDefault("LoginDatabaseInfo", "");
    if (dbstring.empty())
    {
        sLog->outError("Database nicht angegeben");
        return false;
    }

    uint8 worker_threads = sConfig->GetIntDefault("LoginDatabase.WorkerThreads", 1);
    if (worker_threads < 1 || worker_threads > 32)
    {
        sLog->outError("Improper value specified for LoginDatabase.WorkerThreads, defaulting to 1.");
        worker_threads = 1;
    }

    uint8 synch_threads = sConfig->GetIntDefault("LoginDatabase.SynchThreads", 1);
    if (synch_threads < 1 || synch_threads > 32)
    {
        sLog->outError("Improper value specified for LoginDatabase.SynchThreads, defaulting to 1.");
        synch_threads = 1;
    }

    /// NOTE: While authserver is singlethreaded you should keep synch_threads == 1. Increasing it is just silly since only 1 will be used ever.
    if (!LoginDatabase.Open(dbstring.c_str(), worker_threads, synch_threads))
    {
        sLog->outError("Keine Verbindung zur Datenbank");
        return false;
    }

    return true;
}

/// @}