/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                    [libex_logging_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_LOGGING__H
#define      INCLUDED_LIBEX_LOGGING__H
#include "libex_logging.h"

#define FN_NAME                         LX_FN_NAME
#define FN_NAME_A                       LX_FN_NAME_A
#define LINE                            LX_LINE

#define DEBUG_INFO                      LX_DEBUG_INFO
#define DEBUG_WARN                      LX_DEBUG_WARN
#define ERR                             LX_ERR
#define INFO                            LX_INFO
#define NET_VERIFY                      LX_NET_VERIFY
#define OS_ERR                          LX_OS_ERR
#define OS_VERIFY                       LX_OS_VERIFY
#define OS_WARN                         LX_OS_WARN
#define VERIFY                          LX_VERIFY
#define WARN                            LX_WARN
#define WARN_IF                         LX_WARN_IF

#define err_msg_type_enum               lx_err_msg_type_enum
#define MSG_SUCCESS                     LX_MSG_SUCCESS
#define MSG_INFO                        LX_MSG_INFO
#define MSG_WARN                        LX_MSG_WARN
#define MSG_ERROR                       LX_MSG_ERROR

#define err_code_enum                   lx_err_code_enum
#define ERR_ILLOGIC                     LX_ERR_ILLOGIC
#define ERR_UNKNOWN_TYPE                LX_ERR_UNKNOWN_TYPE
#define ERR_MISSING_ITEM                LX_ERR_MISSING_ITEM

#define err_count                       lx_err_count
#define log_error                       lx_log_error
#define log_info                        lx_log_info
#define log_to_event_log                lx_log_to_event_log
#define log_to_file                     lx_log_to_file
#define log_warn                        lx_log_warn

#endif                                                                   /*eof*/
