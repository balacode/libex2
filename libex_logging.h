/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                     [libex_logging.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_LOGGING_H
#define      INCLUDED_LIBEX_LOGGING_H

#define LX_USE_LOGGING_MACROS

#include "libex.h"

/* -------------------------------------------------------------------------- */
/* Macro Definitions:                                                         */

#undef LX_FN_NAME_A
#if defined __GNUC__
#define LX_FN_NAME_A  __func__
#endif
#if defined _MSC_VER
#define LX_FN_NAME_A  __FUNCTION__
#endif

#undef LX_FN_NAME
#if defined UNICODE || defined _UNICODE
/* ANSI to Unicode transform */
#define LX_TMP_WIDE2( FN_NAME_ )  L ## FN_NAME_
#define LX_TMP_WIDE( FN_NAME_ )   LX_TMP_WIDE2(FN_NAME_)
#define LX_FN_NAME                LX_TMP_WIDE(LX_FN_NAME_A)
#else                                                  /* UNICODE || _UNICODE */
#define LX_FN_NAME  LX_FN_NAME_A
#endif                                               /* !UNICODE && !_UNICODE */

#undef LX_LINE
#if defined LX_USE_LOGGING_MACROS
#if !defined __LINE__
#define __LINE__  0
#endif
#define LX_LINE  err_line = __LINE__
#else
#define LX_LINE  0
#endif                                               /* LX_USE_LOGGING_MACROS */

#undef LX_ERR
#undef LX_INFO
#undef LX_WARN

#if defined LX_USE_LOGGING_MACROS

#define LX_INFO( MESSAGE_, SRC_UID_ )                            \
    LX_CL lx_log_info(MESSAGE_, LX_FN_NAME, SRC_UID_, NULL)  /*#*/

#define LX_WARN( MESSAGE_, SRC_UID_ )                            \
    LX_CL lx_log_warn(MESSAGE_, LX_FN_NAME, SRC_UID_, NULL)  /*#*/

#define LX_ERR( MESSAGE_, SRC_UID_ )                              \
    LX_CL lx_log_error(MESSAGE_, LX_FN_NAME, SRC_UID_, NULL)  /*#*/
#else                                                /* LX_USE_LOGGING_MACROS */
#define LX_INFO( MESSAGE_, SRC_UID_ )             \
    { LX_DEBUG_BREAK; LX_UNUSED(SRC_UID_); }  /*#*/

#define LX_WARN( MESSAGE_, SRC_UID_ )             \
    { LX_DEBUG_BREAK; LX_UNUSED(SRC_UID_); }  /*#*/

#define LX_ERR( MESSAGE_, SRC_UID_ )              \
    { LX_DEBUG_BREAK; LX_UNUSED(SRC_UID_); }  /*#*/
#endif                                              /* !LX_USE_LOGGING_MACROS */

#undef LX_WARN_IF
#if defined LX_USE_LOGGING_MACROS
#define LX_WARN_IF( CONDITION_, SRC_UID_ )                       \
    {                                                            \
        if (CONDITION_)                                          \
            LX_CL lx_log_warn(_T(" warning: ") _T(#CONDITION_),  \
                              LX_FN_NAME, SRC_UID_, NULL);       \
    }                                                        /*#*/

#else
#define LX_WARN_IF( CONDITION_, SRC_UID_ )        \
    { LX_DEBUG_BREAK; LX_UNUSED(SRC_UID_); }  /*#*/
#endif                                               /* LX_USE_LOGGING_MACROS */

#undef LX_VERIFY
#undef LX_OS_VERIFY
#undef LX_NET_VERIFY
#if defined LX_USE_LOGGING_MACROS
#define _V_FAILCODE( CONDITION_, NOTES_, SRC_UID_ )             \
    {                                                           \
        if (!(CONDITION_))                                      \
        {                                                       \
            LX_CL lx_log_warn(_T(#CONDITION_) _T(" failed: "),  \
                              LX_FN_NAME, SRC_UID_, NOTES_);    \
        }                                                       \
    }                                                       /*#*/

#define LX_VERIFY( CONDITION_, SRC_UID_ )        \
    _V_FAILCODE(CONDITION_, NULL, SRC_UID_)  /*#*/

#define LX_OS_VERIFY( CONDITION_, SRC_UID_ )                              \
    _V_FAILCODE(CONDITION_, LX_CL lx_system_error_name(0), SRC_UID_)  /*#*/

#define LX_NET_VERIFY( CONDITION_, SRC_UID_ )                    \
    _V_FAILCODE(CONDITION_, lx_net_error_name(0), SRC_UID_)  /*#*/
#else                                                /* LX_USE_LOGGING_MACROS */
#define LX_VERIFY( CONDITION_, SRC_UID_ )
#define LX_OS_VERIFY( CONDITION_, SRC_UID_ )
#define LX_NET_VERIFY( CONDITION_, SRC_UID_ )
#endif                                              /* !LX_USE_LOGGING_MACROS */

#undef LX_OS_WARN
#undef LX_OS_ERR

#if defined LX_USE_LOGGING_MACROS

#define LX_OS_WARN( FN_NAME_, SRC_UID_ )                   \
    LX_CL lx_log_warn(LX_CL lx_system_error_name(0),       \
                      FN_NAME_, SRC_UID_, LX_FN_NAME)  /*#*/
#define LX_OS_ERR( FN_NAME_, SRC_UID_ )                     \
    LX_CL lx_log_error(LX_CL lx_system_error_name(0),       \
                       FN_NAME_, SRC_UID_, LX_FN_NAME)  /*#*/
#else                                                /* LX_USE_LOGGING_MACROS */
#define LX_OS_WARN( FN_NAME_, SRC_UID_ )          \
    { LX_DEBUG_BREAK; LX_UNUSED(SRC_UID_); }  /*#*/
#define LX_OS_ERR( FN_NAME_, SRC_UID_ )           \
    { LX_DEBUG_BREAK; LX_UNUSED(SRC_UID_); }  /*#*/

#endif                                              /* !LX_USE_LOGGING_MACROS */

#undef LX_DEBUG_INFO
#undef LX_DEBUG_WARN
#if (defined DEBUG || defined _DEBUG)
#define LX_DEBUG_INFO( MESSAGE_, SRC_UID_ )  LX_INFO(MESSAGE_, SRC_UID_)
#define LX_DEBUG_WARN( MESSAGE_, SRC_UID_ )  LX_WARN(MESSAGE_, SRC_UID_)
#else
#define LX_DEBUG_INFO( MESSAGE_, SRC_UID_ )
#define LX_DEBUG_WARN( MESSAGE_, SRC_UID_ )
#endif

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

typedef enum  _lx_err_msg_type_enum {
    LX_MSG_SUCCESS,                                   /* lx_err_msg_type_enum */
    LX_MSG_INFO,                                      /* lx_err_msg_type_enum */
    LX_MSG_WARN,                                      /* lx_err_msg_type_enum */
    LX_MSG_ERROR                                      /* lx_err_msg_type_enum */
}
lx_err_msg_type_enum;                                                   /*enum*/

typedef enum  _lx_err_code_enum {
    LX_ERR_ILLOGIC      = 0x10000003,                     /* lx_err_code_enum */
    LX_ERR_UNKNOWN_TYPE = 0x10000001,                     /* lx_err_code_enum */
    LX_ERR_MISSING_ITEM = 0x10000002                      /* lx_err_code_enum */
}
lx_err_code_enum;                                                       /*enum*/

LX_PUBLIC void  lx_log_error(                                              /*F*/
    lx_chars_t      detail_,                                               /*-*/
    lx_chars_t      source_func_,                                          /*-*/
    const uint32_t  src_uid_,                                              /*-*/
    lx_chars_t      notes_ );                                              /*-*/

LX_PUBLIC size_t  lx_err_count( void );                                    /*F*/

LX_PUBLIC void  lx_log_info(                                               /*F*/
    lx_chars_t      detail_,                                               /*-*/
    lx_chars_t      source_func_,                                          /*-*/
    const uint32_t  src_uid_,                                              /*-*/
    lx_chars_t      notes_ );                                              /*-*/

LX_PUBLIC lx_bool  lx_log_to_event_log(                                    /*F*/
    lx_chars_t                  message_,                                  /*-*/
    const lx_err_msg_type_enum  type_,                                     /*-*/
    lx_chars_t                  app_name_,                                 /*-*/
    lx_chars_t                  msg_dll_ );                                /*-*/

LX_PUBLIC lx_chars_t  lx_log_to_file( lx_chars_t  text_ );                 /*F*/

LX_PUBLIC void  lx_log_warn(                                               /*F*/
    lx_chars_t      detail_,                                               /*-*/
    lx_chars_t      source_func_,                                          /*-*/
    const uint32_t  src_uid_,                                              /*-*/
    lx_chars_t      notes_ );                                              /*-*/

/* "The animistic metaphor of the bug that maliciously sneaked in while       */
/* the programmer was not looking is intellectually dishonest as it           */
/* disguises that the error is the programmer's own creation."                */
/* -- E. W. Dijkstra, EWD1036                                                 */

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
