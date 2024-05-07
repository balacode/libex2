/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                               [libex_c_precompiled.h] */
/* -------------------------------------------------------------------------- */

/* Contains standard system include files, or project specific include        */
/* files that are used frequently, but are changed infrequently.              */

#if !defined INCLUDED_LIBEX_C_PRECOMPILED_H
#define      INCLUDED_LIBEX_C_PRECOMPILED_H

#include "libex_c_obfuscate.h"
#include "libex_config.h"

#if LX_PLATFORM_LINUX
#include <arpa/inet.h>
/* ^ for AF_INET connect() htons() inet_pton()      */
/*   LX_SOCK_STREAM sockaddr_in  socket()           */
#include <netdb.h>      /* gethostbyname(), hostent */
#include <sys/errno.h>  /* various error constants  */
#include <sys/ioctl.h>  /* ioctl()                  */
#include <unistd.h>     /* read()                   */
#endif                                                   /* LX_PLATFORM_LINUX */

#if LX_PLATFORM_WIN32

#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4201)  /* W:L4 nonstandard xt: nameless struct/union */
#pragma warning (disable:4255)  /* W:L4 no function prototype given           */
#pragma warning (disable:4548)  /* W:L1 expression has no effect              */
#pragma warning (disable:4574)  /* W:L4 'X' is defined to be '0': did you     */
/* W:C4574                              mean to use '#if X'?                  */
#pragma warning (disable:4668)  /* W:L4 'SYMBOL' is not defined as a p. macro */
#pragma warning (disable:4820)  /* W:L4 'N' bytes padding added after 'NAME'  */
#endif

/* exclude rarely-used stuff from Windows headers */
#define WIN32_LEAN_AND_MEAN

#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4005)  // W:L1 C4005: 'NAME': macro redefinition
#endif

#include <winsock2.h>  /* put before windows.h to avoid errors */

#if defined _MSC_VER
#pragma warning (pop)
#endif

#include <ws2tcpip.h>  /* for inet_pton()                      */
#include <winerror.h>  /* for WSA*                             */
#include <wtypes.h>    /* for BSTR, etc.                       */
#include <shlwapi.h>
#include <ShellAPI.h>
#include <oaidl.h>
#include <ocidl.h>
#include <olectl.h>

#if LX_PLATFORM_WIN32
#include "libex_win32.h"
#endif

#if defined _MSC_VER
#pragma warning (pop)
#endif

#endif                                                   /* LX_PLATFORM_WIN32 */

#include "libex.h"
#include "libex_libc.h"

#endif                                                                   /*eof*/
