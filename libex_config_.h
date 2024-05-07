/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                     [libex_config_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_CONFIG__H
#define      INCLUDED_LIBEX_CONFIG__H
#include "libex_config.h"

#define PLATFORM_LINUX                  LX_PLATFORM_LINUX
#define PLATFORM_WIN32                  LX_PLATFORM_WIN32

#define CALL_TRACE                      LX_CALL_TRACE

#define MEM_USE_OS_FUNCTIONS            LX_MEM_USE_OS_FUNCTIONS

#if (defined DEBUG || defined _DEBUG)
#define MEM_DEBUG                       LX_MEM_DEBUG
#else
#undef MEM_DEBUG
#endif

#endif                                                                   /*eof*/
