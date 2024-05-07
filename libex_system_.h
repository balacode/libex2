/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                     [libex_system_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_SYSTEM__H
#define      INCLUDED_LIBEX_SYSTEM__H
#include "libex_system.h"

#define RECT_WIDTH                      LX_RECT_WIDTH
#define RECT_HEIGHT                     LX_RECT_HEIGHT

/* -------------------------------------------------------------------------- */

#define os_class_enum                   lx_os_class_enum
#define OS_UNKNOWN                      LX_OS_UNKNOWN
#define OS_LINUX                        LX_OS_LINUX
#define OS_WINDOWS_9X                   LX_OS_WINDOWS_9X
#define OS_WINDOWS_NT                   LX_OS_WINDOWS_NT

/* -------------------------------------------------------------------------- */

#define create_guid                     lx_create_guid
#define input_box                       lx_input_box

#if LX_PLATFORM_WIN32
#define load_resource_win               lx_load_resource_win
#endif

#define message_box_icon_enum           lx_message_box_icon_enum
#define ICON_ERROR                      LX_ICON_ERROR
#define ICON_ASK                        LX_ICON_ASK
#define ICON_WARN                       LX_ICON_WARN
#define ICON_INFO                       LX_ICON_INFO

#define message_box                     lx_message_box
#define MESSAGE_BOX1                    LX_MESSAGE_BOX1

#define sleep_ms                        lx_sleep_ms
#define system_error_name               lx_system_error_name
#define timestamp                       lx_timestamp
#define uptime_ms                       lx_uptime_ms

/* -------------------------------------------------------------------------- */
/* Functions: Process-Related                                                 */

#define full_process_name               lx_full_process_name
#define kill_process                    lx_kill_process
#define log_filename                    lx_log_filename
#define process_name                    lx_process_name
#define program_path                    lx_program_path

#endif                                                                   /*eof*/
