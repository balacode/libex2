/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                        [libex_file.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_FILE_H
#define      INCLUDED_LIBEX_FILE_H

#include "libex_config.h"

#if LX_PLATFORM_WIN32
#include <windows.h>
#endif

#include "libex.h"
#include "libex_string_class.h"
#if LX_PLATFORM_WIN32
#include "libex_win32.h"
#endif

#define LX_FILE_SIZE_MAX  9223372036854775807

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

typedef struct  lx_file_t {
    uint8_t*  ob;                                                /* lx_file_t */
}
lx_file_t, lx_new_file_t;

#if LX_PLATFORM_LINUX
typedef long long      lx_file_size_t;
#endif

#if LX_PLATFORM_WIN32
typedef ULONGLONG_win  lx_file_size_t;
#endif

typedef enum  _lx_File_TextModeEnum {
    LX_FILE_TEXT_AUTO = 0,                            /* lx_File_TextModeEnum */
    LX_FILE_TEXT_ANSI = 1,                            /* lx_File_TextModeEnum */
    LX_FILE_TEXT_WIDE = 2                             /* lx_File_TextModeEnum */
}
lx_File_TextModeEnum;                                                   /*enum*/

typedef enum  _lx_File_EncryptModeEnum {
    LX_FILE_NO_ENCRYPT = 0,                        /* lx_File_EncryptModeEnum */
    LX_FILE_ENCRYPT    = 1,                        /* lx_File_EncryptModeEnum */
    LX_FILE_DECRYPT    = -1                        /* lx_File_EncryptModeEnum */
}
lx_File_EncryptModeEnum;                                                /*enum*/

/* -------------------------------------------------------------------------- */
/* Constructors / Destructor:                                                 */

/* TODO: lx_File_init(). Use macro. */
LX_PUBLIC lx_new_file_t  lx_File_init( lx_chars_t  filename_ );            /*C*/

LX_PUBLIC lx_new_file_t  lx_File_initInMode(                               /*C*/
    lx_chars_t     filename_,                                              /*-*/
    const lx_bool  modify_,                                                /*-*/
    const lx_bool  shared_ );                                              /*-*/

#define lx_File_initRead( CHARS__FILENAME_ )                              /*M*/\
    lx_File_initInMode(   CHARS__FILENAME_, LX_C_FALSE, LX_C_TRUE)         /*#*/

LX_PUBLIC void  lx_File_free( lx_file_t*  object_ );                       /*D*/

/* -------------------------------------------------------------------------- */
/* Properties: Read-Only                                                      */

#if LX_PLATFORM_WIN32
LX_PUBLIC HANDLE_win  lx_File_getHandle( lx_file_t  object_ );             /*P*/
#endif

LX_PUBLIC lx_bool  lx_File_isOpen( const lx_file_t  object_ );             /*P*/

LX_PUBLIC lx_chars_t  lx_File_getName( const lx_file_t  object_ );         /*P*/

LX_PUBLIC size_t  lx_File_getFileSize( const lx_file_t  object_ );         /*P*/

LX_PUBLIC void  lx_File_setFileSize(                                       /*P*/
    lx_file_t     object_,                                                 /*-*/
    const size_t  value_ );                                                /*-*/

/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */

LX_PUBLIC void  lx_File_open(                                              /*M*/
    lx_file_t   object_,                                                   /*-*/
    lx_chars_t  filename_ );                                               /*-*/

LX_PUBLIC void  lx_File_openInMode(                                        /*M*/
    lx_file_t      object_,                                                /*-*/
    lx_chars_t     filename_,                                              /*-*/
    const lx_bool  modify_,                                                /*-*/
    const lx_bool  shared_ );                                              /*-*/

LX_PUBLIC void  lx_File_goTo(                                              /*M*/
    lx_file_t     object_,                                                 /*-*/
    const size_t  new_position_ );                                         /*-*/

/* Move file pointer to the beginning.                                        */
LX_PUBLIC void  lx_File_goBegin( lx_file_t  object_ );                     /*M*/

/* Move file pointer to the end.                                              */
LX_PUBLIC void  lx_File_goEnd( lx_file_t  object_ );                       /*M*/

LX_PUBLIC void  lx_File_write(                                             /*M*/
    lx_file_t     object_,                                                 /*-*/
    const void*   bytes_,                                                  /*-*/
    const size_t  length_in_bytes_ );                                      /*-*/

LX_PUBLIC void  lx_File_writeTextData(                                     /*M*/
    lx_file_t   object_,                                                   /*-*/
    lx_chars_t  text_ );                                                   /*-*/

LX_PUBLIC void  lx_File_writeInt(                                          /*M*/
    lx_file_t  object_,                                                    /*-*/
    const int  value_ );                                                   /*-*/

LX_PUBLIC void  lx_File_writeSize(                                         /*M*/
    lx_file_t     object_,                                                 /*-*/
    const size_t  value_ );                                                /*-*/

LX_PUBLIC size_t  lx_File_read(                                            /*M*/
    lx_file_t     object_,                                                 /*-*/
    void*         bytes_,                                                  /*-*/
    const size_t  length_in_bytes_ );                                      /*-*/

/* Read a previously-stored text value from a file.                           */
LX_PUBLIC lx_new_str_t  lx_File_readTextData( lx_file_t  object_ );        /*M*/

LX_PUBLIC int  lx_File_readInt( lx_file_t  object_ );                      /*M*/

LX_PUBLIC size_t  lx_File_readSize( lx_file_t  object_ );                  /*M*/

/* Close the opened file.                                                     */
LX_PUBLIC void  lx_File_close( lx_file_t  object_ );                       /*M*/


/* -------------------------------------------------------------------------- */
/* Functions:                                                                 */

/* returns true if the specified file name exists.                            */
LX_PUBLIC lx_bool  lx_file_exists( lx_chars_t  filename_ );                /*F*/

/* delete the specified file, with optionally of confirming the deletion      */
/* from the user, sending the file to the recycle bin (instead of just        */
/* deleting it), or erasing its contents before deletion.                     */
LX_PUBLIC lx_bool  lx_file_delete_4(                                       /*F*/
    lx_chars_t     filename_,                                              /*-*/
    const lx_bool  ask_user_,                                              /*-*/
    const lx_bool  send_to_bin_,                                           /*-*/
    const lx_bool  secure_delete_ );                                       /*-*/

#define lx_file_delete( CHARS__FILENAME_ )                                /*F*/\
    lx_file_delete_4( CHARS__FILENAME_,                                        \
                      LX_C_FALSE, LX_C_FALSE, LX_C_FALSE)                  /*#*/

/* -------------------------------------------------------------------------- */
/* file information functions                                                 */

LX_PUBLIC lx_new_str_t  lx_file_path( lx_chars_t  filename_ );             /*F*/

/* If a path was not specified, adds the current directory to a file name.    */
LX_PUBLIC lx_new_str_t  lx_file_name_full(                                 /*F*/
    lx_chars_t  filename_,                                                 /*-*/
    lx_chars_t  default_path_ );                                           /*-*/

LX_PUBLIC lx_new_str_t  lx_file_locate(                                    /*F*/
    lx_chars_t  filename_,                                                 /*-*/
    lx_chars_t  alternate_paths_ );                                        /*-*/

LX_PUBLIC lx_new_str_t  lx_file_name( lx_chars_t  filename_ );             /*F*/

LX_PUBLIC size_t  lx_file_size( lx_chars_t  filename_ );                   /*F*/

LX_PUBLIC lx_new_str_t  lx_file_size_description(                          /*F*/
    lx_file_size_t  size_,                                                 /*-*/
    const lx_bool   format_remainder_ );                                   /*-*/

LX_PUBLIC lx_bool  lx_file_type_is_text( lx_chars_t  filename_ );          /*F*/

/* -------------------------------------------------------------------------- */
/* file manipulation functions                                                */

LX_PUBLIC lx_bool  lx_file_move(                                           /*F*/
    lx_chars_t     source_filename_,                                       /*-*/
    lx_chars_t     target_filename_,                                       /*-*/
    const lx_bool  overwrite_ );                                           /*-*/

LX_PUBLIC lx_bool  lx_file_copy(                                           /*F*/
    lx_chars_t     source_filename_,                                       /*-*/
    lx_chars_t     target_filename_,                                       /*-*/
    const lx_bool  overwrite_ );                                           /*-*/

/* Encrypts or decrypts from one file to another.                             */
LX_PUBLIC lx_bool  lx_file_encrypt(                                        /*F*/
    lx_chars_t                     source_filename_,                       /*-*/
    lx_chars_t                     target_filename_,                       /*-*/
    const lx_bool                  overwrite_,                             /*-*/
    const lx_File_EncryptModeEnum  encrypt_mode_,                          /*-*/
    lx_chars_t                     cipher_ );                              /*-*/

LX_PUBLIC lx_bool  lx_file_write_bytes(                                    /*F*/
    lx_chars_t    filename_,                                               /*-*/
    const size_t  start_byte_,                                             /*-*/
    const size_t  length_in_bytes_,                                        /*-*/
    const void*   data_ );                                                 /*-*/

LX_PUBLIC lx_bool  lx_file_append_bytes(                                   /*F*/
    lx_chars_t    filename_,                                               /*-*/
    const void*   bytes_,                                                  /*-*/
    const size_t  length_in_bytes_ );                                      /*-*/

LX_PUBLIC lx_bool  lx_file_append_text(                                    /*F*/
    lx_chars_t  filename_,                                                 /*-*/
    lx_chars_t  text_ );                                                   /*-*/

LX_PUBLIC lx_bool  lx_file_append_text_n(                                  /*F*/
    lx_chars_t  filename_,                                                 /*-*/
    lx_chars_t  terminator_,                                               /*-*/
    ... );                                                                 /*-*/

LX_PUBLIC lx_new_bytes_t  lx_file_load_bytes( lx_chars_t  filename_ );     /*F*/

/* -------------------------------------------------------------------------- */

LX_PUBLIC lx_new_str_t  lx_file_read_text(                                 /*F*/
    lx_chars_t  filename_,                                                 /*-*/
    lx_chars_t  alternate_paths_ );                                        /*-*/

#define lx_file_read_text1( CHARS__FILENAME_ )                            /*F*/\
    lx_file_read_text(      CHARS__FILENAME_, LX_BLANK)                    /*#*/

/* -------------------------------------------------------------------------- */
/* path information functions                                                 */

/* return true if the specified folder or file exists.                        */
LX_PUBLIC lx_bool  lx_path_exists(                                         /*F*/
    lx_chars_t     path_,                                                  /*-*/
    const lx_bool  folder_,                                                /*-*/
    const lx_bool  file_ );                                                /*-*/

/* return only the names of existing folders in the given path.               */
LX_PUBLIC lx_new_str_t  lx_path_existing( lx_chars_t  path_or_file_ );     /*F*/

LX_PUBLIC lx_new_str_t  lx_path_extract(                                   /*F*/
    lx_chars_t     path_or_file_,                                          /*-*/
    const lx_bool  root_only_ );                                           /*-*/

LX_PUBLIC lx_new_str_t  lx_get_path( lx_chars_t  path_or_file_ );          /*F*/

LX_PUBLIC lx_new_str_t  lx_path_root( lx_chars_t  path_or_file_ );         /*F*/

/* return the name of a folder path without a file name                       */
LX_PUBLIC lx_new_str_t  lx_folder_name( lx_chars_t  path_ );               /*F*/

/* return the free space on the specified path.                               */
LX_PUBLIC size_t  lx_get_free_space( lx_chars_t  path_ );                  /*F*/

/* return the free space on the specified path (large).                       */
LX_PUBLIC lx_file_size_t  lx_get_free_space_large( lx_chars_t  path_ );    /*F*/

LX_PUBLIC lx_new_str_t  lx_paths_format( lx_chars_t  paths_ );             /*F*/

/* -------------------------------------------------------------------------- */
/* Function: lx_process_files_in_folder()                                     */

/*   Use the following declaration format for the callback function:          */
/*   lx_bool  callback_fn( lx_chars_t  filename_,  const size_t  file_size_ ) */
/*                                                                            */
/*   Use it as follows:                                                       */
/*   lx_process_files_in_folder(_T("\\your_path"), true, &callback_fn);       */
/*                                                                            */
/*   The callback function should return true to make                         */
/*   lx_process_files_in_folder() continue reading file names                 */
/*   or false to stop.                                                        */
/*                                                                            */
/*   (Substitute callback_fn with your function name.)                        */

#if 000   /* Callback function template: */
LX_PUBLIC lx_bool  callback_fn(                                            /*F*/
    lx_chars_t    filename_,                                               /*-*/
    const size_t  file_size_ ) {                                           /*-*/
    LX_GO                                                      (LX_UID(FD5322));
    const lx_bool  ret = true;  /* <- set the return value you want here */

    LX_RETURN(ret);
} /* callback_fn */
#endif                                                                 /* 000 */

LX_PUBLIC lx_bool  lx_process_files_in_folder(                             /*F*/
    lx_chars_t     path_,                                                  /*-*/
    const lx_bool  scan_subfolders_,                                       /*-*/
    lx_bool  (*    callback_fn_)(lx_chars_t    file_,                      /*-*/
                                 const size_t  file_size_ ) );             /*-*/

/* -------------------------------------------------------------------------- */

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
