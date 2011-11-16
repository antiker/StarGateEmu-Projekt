/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifdef _WIN32
#ifndef _WIN32_SERVICE_
#define _WIN32_SERVICE_

bool WinServiceInstall();
bool WinServiceUninstall();
bool WinServiceRun();

#endif                                                      // _WIN32_SERVICE_
#endif                                                      // _WIN32