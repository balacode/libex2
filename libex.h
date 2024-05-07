/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                             [libex.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_H
#define      INCLUDED_LIBEX_H

#include "libex_config.h"               /* defines the target operating system*/

#include <stddef.h>
#if defined _MSC_VER
#include <tchar.h>
#endif

#include "libex_stdint.h"

/* -------------------------------------------------------------------------- */
/* Namespaces and Scope:                                                      */

#if defined __cplusplus
#define LX_PUBLIC  extern "C"
#else
#define LX_PUBLIC
#endif

#if defined __cplusplus
#define LX_CL                  lx_c::
#define LX_NAMESPACE( NAME_ )  namespace NAME_ {
#define LX_END_NAMESPACE       }
#else                                                          /* __cplusplus */
#define LX_CL
#define LX_NAMESPACE( NAME_ )
#define LX_END_NAMESPACE
#endif                                                        /* !__cplusplus */

/* -------------------------------------------------------------------------- */
/* Common Definitions:                                                        */

#if !defined _T
#if defined UNICODE || defined _UNICODE
#define _T( TEXT_LITERAL_ )  L ## TEXT_LITERAL_
#else
#define _T( TEXT_LITERAL_ )  TEXT_LITERAL_
#endif
#endif                                                                 /* !_T */

#define LX_UID( CODE_ )  0x##CODE_

#define LX_NIL

#define LX_UNUSED( VARIABLE_ ) {                                 \
        const char*  unused = LX_CAST(const char*, &VARIABLE_);  \
        unused++;                                                \
    }                                                        /*#*/

#if !defined LX_FN_NAME
#if !defined __FUNCTION__
#define __FUNCTION__  "__FUNCTION__"
#endif
#if defined UNICODE || defined _UNICODE
#define LX_FN_NAME  LX_WIDE(__FUNCTION__)
#else
#define LX_FN_NAME  __FUNCTION__
#endif
#endif                                                         /* !LX_FN_NAME */

#if defined __GNUC__
#define LX_FN_NAME_A  __func__
#endif
#if defined _MSC_VER
#define LX_FN_NAME_A  __FUNCTION__
#endif

/* ANSI to Unicode string transform */
#if defined UNICODE || defined _UNICODE
#define LX_WIDE_2_SUB( STRING_ )  L ## STRING_
#define LX_WIDE( STRING_ )        LX_WIDE_2_SUB(STRING_)
#define LX_STR( STRING_ )         LX_WIDE(STRING_)
#else
#define LX_STR( STRING_ )         STRING_
#endif

/* C cast */
#define LX_CAST( TYPE_, VALUE_ )  ((TYPE_)(VALUE_))

/* C++ casts */
#define LX_CCAST( TYPE_, VALUE_ )   const_cast<TYPE_>(VALUE_)
#define LX_DCAST( TYPE_, VALUE_ )   dynamic_cast<TYPE_>(VALUE_)
#define LX_RCAST( TYPE_, VALUE_ )   reinterpret_cast<TYPE_>(VALUE_)
#define LX_SCAST( TYPE_, VALUE_ )   static_cast<TYPE_>(VALUE_)

/* GCC does not recognise abstract keyword */
#if defined __cplusplus && defined _MSC_VER
#define LX_ABSTRACT  abstract
#else
#define LX_ABSTRACT
#endif

/* -------------------------------------------------------------------------- */
/* Threads:                                                                   */

#if LX_PLATFORM_LINUX
#define LX_THREAD_HANDLE       pthread_t
#define LX_THREAD_RETURN_TYPE  void*

#elif LX_PLATFORM_WIN32
#define LX_THREAD_HANDLE       uintptr_t
#define LX_THREAD_RETURN_TYPE  void
#endif

/* -------------------------------------------------------------------------- */
/* Type Definitions:                                                          */

/* boolean type */

LX_NAMESPACE(lx_c)
enum lx_bool_t { lx_false = 0, lx_true = 1 };
#if defined __cplusplus
typedef bool             lx_bool;
#else
typedef enum  lx_bool_t  lx_bool;
#endif
LX_END_NAMESPACE

#if defined __cplusplus
#define LX_C_FALSE  lx_c::lx_bool(0)
#define LX_C_TRUE   lx_c::lx_bool(1)
#else
#define LX_C_FALSE  lx_false
#define LX_C_TRUE   lx_true
#endif

/* character types */
#if defined UNICODE || defined _UNICODE
#define lx_char_t        wchar_t
#define lx_chars_t       const wchar_t*
#define lx_new_chars_t   wchar_t*
#else                                                  /* UNICODE || _UNICODE */
#define lx_char_t        char
#define lx_chars_t       const char*
#define lx_new_chars_t   char*
#endif                                               /* !UNICODE && !_UNICODE */

#define lx_new_bchars_t  char*
#define lx_new_wchars    wchar_t*

LX_NAMESPACE(lx_c)

typedef void*   lx_handle_t;

typedef double  lx_pixel_t;  /* coordinate type */

/* byte buffer type */
typedef struct  lx_bytes_t {
    size_t    size;                                             /* lx_bytes_t */
    uint8_t*  data;                                             /* lx_bytes_t */
}
lx_bytes_t, lx_new_bytes_t;

typedef enum  _lx_text_data_format_enum {
    LX_FORMAT_DEFAULT,                            /* lx_text_data_format_enum */
    LX_FORMAT_MICROSOFT_SQL                       /* lx_text_data_format_enum */
}
lx_text_data_format_enum;                                               /*enum*/

LX_END_NAMESPACE

#include "libex_libc.h"

#endif                                                                   /*eof*/
