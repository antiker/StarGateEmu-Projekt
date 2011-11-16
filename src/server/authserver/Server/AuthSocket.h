/*
 * Copyright (C) 2010-2011 Project StarGate
 *
 */

/// \addtogroup realmd
/// @{
/// \file

#ifndef _AUTHSOCKET_H
#define _AUTHSOCKET_H

#include "Common.h"
#include "BigNumber.h"

#include "RealmSocket.h"

enum RealmFlags
{
    REALM_FLAG_NONE         = 0x00,
    REALM_FLAG_INVALID      = 0x01,
    REALM_FLAG_OFFLINE      = 0x02,
    REALM_FLAG_SPECIFYBUILD = 0x04,                         // client will show realm version in RealmList screen in form "RealmName (major.minor.revision.build)"
    REALM_FLAG_UNK1         = 0x08,
    REALM_FLAG_UNK2         = 0x10,
    REALM_FLAG_RECOMMENDED  = 0x20,                         // client checks pop == 600f
    REALM_FLAG_NEW          = 0x40,                         // client checks pop == 200f
    REALM_FLAG_FULL         = 0x80                          // client checks pop == 400f
};

/// Handle login commands
class AuthSocket: public RealmSocket::Session
{
    public:
        const static int s_BYTE_SIZE = 32;

        AuthSocket(RealmSocket& socket);
        virtual ~AuthSocket(void);

        virtual void OnRead(void);
        virtual void OnAccept(void);
        virtual void OnClose(void);

        bool _HandleLogonChallenge();
        bool _HandleLogonProof();
        bool _HandleReconnectChallenge();
        bool _HandleReconnectProof();
        bool _HandleRealmList();
        //data transfer handle for patch

        bool _HandleXferResume();
        bool _HandleXferCancel();
        bool _HandleXferAccept();

        void _SetVSFields(const std::string& rI);

        FILE *pPatch;
        ACE_Thread_Mutex patcherLock;

    private:
        RealmSocket& socket_;
        RealmSocket& socket(void) { return socket_; }

        BigNumber N, s, g, v;
        BigNumber b, B;
        BigNumber K;
        BigNumber _reconnectProof;

        bool _authed;

        std::string _login;

        // Since GetLocaleByName() is _NOT_ bijective, we have to store the locale as a string. Otherwise we can't differ
        // between enUS and enGB, which is important for the patch system
        std::string _localizationName;
        uint16 _build;
        uint8 _expversion;
        AccountTypes _accountSecurityLevel;
};
#endif
/// @}