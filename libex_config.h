/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                      [libex_config.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_CONFIG_H
#define      INCLUDED_LIBEX_CONFIG_H

#define LX_LIBRARY

/* This file contains various library configuration settings */

#if defined (_WINDOWS) || defined (WIN32) || defined(_MSC_VER)
#define LX_PLATFORM_LINUX  0
#define LX_PLATFORM_WIN32  1
#else
#define LX_PLATFORM_LINUX  1
#define LX_PLATFORM_WIN32  0
#endif

/* -------------------------------------------------------------------------- */

#define LX_CALL_TRACE  0
/* 0 - no call tracing                                                        */
/* 1 - only use printf() to output function entry and exit                    */
/* 2 - use lx_fn_call_entry() and lx_fn_call_exit() for detailed call tracing */
/*     (lx_fn_call_report() gives a detailed function call/timing analysis)   */

#define LX_MEM_USE_OS_FUNCTIONS  1

#if (defined DEBUG || defined _DEBUG)
#define LX_MEM_DEBUG  0  /* < 0 for none, 1 for normal, or 2 for verbose info */
#else
#undef LX_MEM_DEBUG
#endif

#if !defined __cplusplus_cli && defined _MSC_VER && _MSC_VER <= 1500  /*VS2008*/
#define nullptr  NULL
#endif

#endif                                                                   /*eof*/
