/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_debug.h] */
/* -------------------------------------------------------------------------- */
/* Don't include this in projects directly.  Instead, include libex.h         */

#if !defined INCLUDED_LIBEX_DEBUG_H
#define      INCLUDED_LIBEX_DEBUG_H

#include "libex.h"

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

/* -------------------------------------------------------------------------- */
/* Debugging:                                                                 */

#undef LX_DEBUG_BREAK
#if defined _MSC_VER && (defined DEBUG || defined _DEBUG)
#define LX_DEBUG_BREAK  __debugbreak();
#else
#define LX_DEBUG_BREAK  ;
#endif

#if !defined LX_DEBUG_WARN
#if (defined DEBUG || defined _DEBUG) || defined LX_DEBUG
#define LX_DEBUG_WARN( MESSAGE_, SRC_UID_ )  LX_DEBUG_BREAK
#else
#define LX_DEBUG_WARN( MESSAGE_, SRC_UID_ )
#endif
#endif                                                      /* !LX_DEBUG_WARN */

#if LX_PLATFORM_LINUX
#define LX_DEBUG_LOG_FILE  "./libex_debug.log"
#endif

#if LX_PLATFORM_WIN32
#define LX_DEBUG_LOG_FILE  "X:\\libex_debug.log"
#endif

#if LX_PLATFORM_LINUX
#define LX_DUMP_OPEN                                                      /*F*/\
    {                                                                          \
        FILE*  debug_log_file = FOPEN(LX_DEBUG_LOG_FILE, "a+");            /*#*/
#endif                                                   /* LX_PLATFORM_WIN32 */

#if LX_PLATFORM_WIN32
#define LX_DUMP_OPEN                                                      /*F*/\
    {                                                                          \
        FILE*  debug_log_file                                                  \
            = lx_fsopen(LX_DEBUG_LOG_FILE, "a+", _SH_DENYNO);              /*#*/
#endif                                                   /* LX_PLATFORM_WIN32 */

#define LX_DUMP( FORMAT_, ... )                                           /*F*/\
    PRINTF_T(FORMAT_, ## __VA_ARGS__);                                         \
    FPRINTF_T(debug_log_file, FORMAT_, ## __VA_ARGS__);                    /*#*/

#define LX_DUMP_CLOSE                                                     /*F*/\
    fclose(debug_log_file);                                                    \
    }                                                                      /*#*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
