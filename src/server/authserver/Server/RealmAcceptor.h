/*
 * Copyright (C) 2010-2011 Project StarGate
 *
 */

/** \file
  \ingroup realmd
  */

#ifndef __REALMACCEPTOR_H__
#define __REALMACCEPTOR_H__

#include <ace/Acceptor.h>
#include <ace/SOCK_Acceptor.h>

#include "RealmSocket.h"
#include "AuthSocket.h"

class RealmAcceptor : public ACE_Acceptor<RealmSocket, ACE_SOCK_Acceptor>
{
    public:
        RealmAcceptor(void) { }
        virtual ~RealmAcceptor(void) { }

    protected:
        virtual int make_svc_handler(RealmSocket *&sh)
        {
            if (sh == 0)
                ACE_NEW_RETURN(sh, RealmSocket, -1);

            sh->reactor(reactor());
            sh->set_session(new AuthSocket(*sh));
            return 0;
        }
};

#endif /* __REALMACCEPTOR_H__ */