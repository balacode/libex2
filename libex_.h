/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                            [libex_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX__H
#define      INCLUDED_LIBEX__H
#include "libex.h"

/* -------------------------------------------------------------------------- */
/* Namespaces and Scope:                                                      */

#define PUBLIC                          LX_PUBLIC
#define NAMESPACE                       LX_NAMESPACE
#define END_NAMESPACE                   LX_END_NAMESPACE
#define CL                              LX_CL
#define c_                              lx_c

/* -------------------------------------------------------------------------- */
/* Common Definitions:                                                        */

#undef UNUSED

#define FN_NAME                         LX_FN_NAME
#define FN_NAME_A                       LX_FN_NAME_A
#define NIL                             LX_NIL
#define UID                             LX_UID
#define UNUSED                          LX_UNUSED

/* ANSI to Unicode string transform */
#define STR                             LX_STR

/* C cast */
#define CAST                            LX_CAST

/* C++ casts */
#define CCAST                           LX_CCAST
#define DCAST                           LX_DCAST
#define RCAST                           LX_RCAST
#define SCAST                           LX_SCAST

/* GCC does not recognise abstract keyword */
#define ABSTRACT                        LX_ABSTRACT

/* -------------------------------------------------------------------------- */
/* Threads:                                                                   */

#define THREAD_HANDLE                   LX_THREAD_HANDLE
#define THREAD_RETURN_TYPE              LX_THREAD_RETURN_TYPE

/* -------------------------------------------------------------------------- */
/* Type Definitions:                                                          */

/* boolean type */
#define bool_t                          lx_bool_t
#define C_FALSE                         LX_C_FALSE
#define C_TRUE                          LX_C_TRUE

/* character types */
#define char_t                          lx_char_t
#define chars_t                         lx_chars_t
#define new_bchars_t                    lx_new_bchars_t
#define new_chars_t                     lx_new_chars_t
#define new_wchars_t                    lx_new_wchars

#define bytes_t                         lx_bytes_t
#define handle_t                        lx_handle_t
#define new_bytes_t                     lx_new_bytes_t
#define pixel_t                         lx_pixel_t

#define text_data_format_enum           lx_text_data_format_enum
#define FORMAT_DEFAULT                  LX_FORMAT_DEFAULT
#define FORMAT_MICROSOFT_SQL            LX_FORMAT_MICROSOFT_SQL

#endif                                                                   /*eof*/
