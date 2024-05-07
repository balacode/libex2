/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                      [libex_system.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_SYSTEM_H
#define      INCLUDED_LIBEX_SYSTEM_H

#include "libex.h"
#include "libex_string_class.h"

#if LX_PLATFORM_WIN32
#include <windows.h>
#include "libex_win32.h"
#endif

#if defined __cplusplus
#include "libex_string.hh"
#endif

#if (defined __GNUC__ || defined __clang__) && !defined __MINGW32__
#pragma GCC diagnostic ignored "-Wunused-macros"
#endif

#define LX_RECT_WIDTH( RECT_ )   (RECT_.right - RECT_.left)
#define LX_RECT_HEIGHT( RECT_ )  (RECT_.bottom - RECT_.top)

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

typedef enum  _lx_os_class_enum {
    LX_OS_UNKNOWN = 0,                                    /* lx_os_class_enum */
    LX_OS_LINUX,                                          /* lx_os_class_enum */
    LX_OS_WINDOWS_9X,                                     /* lx_os_class_enum */
    LX_OS_WINDOWS_NT                                      /* lx_os_class_enum */
}
lx_os_class_enum;                                                       /*enum*/

/* -------------------------------------------------------------------------- */

LX_PUBLIC lx_new_str_t  lx_create_guid( const lx_bool  add_delimiter_ );   /*F*/

LX_PUBLIC lx_chars_t  lx_input_box(                                        /*F*/
    lx_chars_t  prompt_,                                                   /*-*/
    lx_chars_t  title_,                                                    /*-*/
    lx_chars_t  default_,                                                  /*-*/
    void*       owner_window_ );                                           /*-*/

#if LX_PLATFORM_WIN32
LX_PUBLIC uint8_t*  lx_load_resource_win(                                  /*F*/
    lx_chars_t         type_,                                              /*-*/
    const int          resource_id_,                                       /*-*/
    size_t*            data_size_out_,                                     /*-*/
    const HMODULE_win  module_ );                                          /*-*/
#endif                                                   /* LX_PLATFORM_WIN32 */

typedef enum  _lx_message_box_icon_enum {
    LX_ICON_ERROR = 16,                           /* lx_message_box_icon_enum */
    LX_ICON_ASK   = 32,                           /* lx_message_box_icon_enum */
    LX_ICON_WARN  = 48,                           /* lx_message_box_icon_enum */
    LX_ICON_INFO  = 64                            /* lx_message_box_icon_enum */
}
lx_message_box_icon_enum;                                               /*enum*/

/*
    LX_ICON_ERROR == MB_ICONHAND_win, MB_ICONERROR_win, MB_ICONSTOP_win
    LX_ICON_ASK   == MB_ICONQUESTION_win
    LX_ICON_WARN  == MB_ICONEXCLAMATION_win, MB_ICONWARNING_win
    LX_ICON_INFO  == MB_ICONASTERISK_win, MB_ICONINFORMATION_win
*/

LX_PUBLIC void  lx_message_box(                                            /*F*/
    lx_chars_t                text_,                                       /*-*/
    lx_chars_t                title_,                                      /*-*/
    lx_message_box_icon_enum  icon_ );                                     /*-*/

#define LX_MESSAGE_BOX1( CHARS__TEXT_ )                                   /*M*/\
    lx_message_box(      CHARS__TEXT_,                                         \
                         _T("Message"), LX_CL LX_ICON_INFO)                /*#*/

LX_PUBLIC void  lx_sleep_ms( const unsigned long  milliseconds_ );         /*F*/

LX_PUBLIC lx_chars_t  lx_system_error_name( const int  error_no_ );        /*F*/

LX_PUBLIC lx_chars_t  lx_timestamp( void );                                /*F*/

LX_PUBLIC unsigned long  lx_uptime_ms( void );                             /*F*/

/* -------------------------------------------------------------------------- */
/* Functions: Process-Related                                                 */

LX_PUBLIC lx_chars_t  lx_full_process_name( void );                        /*F*/

LX_PUBLIC lx_bool  lx_kill_process( lx_chars_t  process_name_ );           /*F*/

LX_PUBLIC lx_new_chars_t  lx_log_filename( lx_chars_t  file_extension_ );  /*F*/

LX_PUBLIC lx_chars_t  lx_process_name( void );                             /*F*/

LX_PUBLIC lx_chars_t  lx_program_path( void );                             /*F*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
