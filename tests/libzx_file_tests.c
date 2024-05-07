/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                  [libex_file_tests.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#if !defined INCLUDED_LIBEX_FILE_TESTS_C
#define      INCLUDED_LIBEX_FILE_TESTS_C

#include <stdio.h>   /* for printf()                   */
#include <string.h>  /* for memcmp() memset() strcat() */

#include "libex_all_.h"
#include "libex_c_tests_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif


#define _TEST_PATH                                    \
    _T("X:\\user\\projects\\code\\clg\\cprojects\\")  \
    _T("\\libex\\tests\\test_files\\")            /*#*/
/*  always end with '\\'           ^ */


#define _assert( CONDITION_ )                    \
    _assert_fn(CONDITION_, _T(#CONDITION_))  /*#*/

/* Use _assert macro. Don't call _assert_fn() directly. */
static void  _assert_fn(                                                   /*F*/
    const bool  condition_,                                                /*-*/
    chars_t     message_ ) {                                               /*-*/
    GO                                                            (UID(FE8776));
    if (!condition_) {
        PRINTF_T(_T("\r\n") _T("Test Failed: %s"), message_);
        /* ------------------------------------------------------------------ */
        DEBUG_BREAK;
        /* ------------------------------------------------------------------ */
    }
    RETURN(NIL);
} /* _assert_fn */


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


/* -------------------------------------------------------------------------- */
/* Constructors / Destructor:                                                 */


#if 000
PUBLIC new_file_t  File_init( chars_t  filename_ ) {                       /*C*/
    ;
} /* test_File_new */
#endif                                                                 /* 000 */

#if 000
PUBLIC new_file_t  File_initInMode(                                        /*C*/
    chars_t     filename_,                                                 /*-*/
    const bool  modify_,                                                   /*-*/
    const bool  shared_ ) {                                                /*-*/
    ;
} /* test_File_newInMode */
#endif                                                                 /* 000 */


/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */


#if 000
PUBLIC void  File_free( file_t*  object_ ) {                               /*D*/
    ;
} /* test_File_free */
#endif                                                                 /* 000 */


/* -------------------------------------------------------------------------- */
/* Properties: Read-Only                                                      */


#if 000
#if PLATFORM_WIN32
PUBLIC HANDLE_win  File_getHandle( file_t  object_ ) {                     /*P*/
    ;
} /* test_File_getHandle */
#endif                                                      /* PLATFORM_WIN32 */
#endif                                                                 /* 000 */


#if 000
PUBLIC bool  File_isOpen( const file_t  object_ ) {                        /*P*/
    ;
} /* test_File_isOpen */
#endif                                                                 /* 000 */

#if 000
PUBLIC chars_t  File_getName( const file_t  object_ ) {                    /*P*/
    ;
} /* test_File_getName */
#endif                                                                 /* 000 */

#if 000
PUBLIC size_t  File_getFileSize( const file_t  object_ ) {                 /*P*/
    ;
} /* test_File_getFileSize */
#endif                                                                 /* 000 */


#if 000
PUBLIC void  File_setFileSize(                                             /*P*/
    file_t        object_,                                                 /*-*/
    const size_t  value_ ) {                                               /*-*/
    ;
} /* test_File_setFileSize */
#endif                                                                 /* 000 */


/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */


#if 000
/* TODO: File_open(): Use macro instead. */
PUBLIC void  File_open(                                                    /*M*/
    file_t   object_,                                                      /*-*/
    chars_t  filename_ ) {                                                 /*-*/
    ;
} /* test_File_open */
#endif                                                                 /* 000 */


#if 000
PUBLIC void  File_openInMode(                                              /*M*/
    file_t      object_,                                                   /*-*/
    chars_t     filename_,                                                 /*-*/
    const bool  modify_,                                                   /*-*/
    const bool  shared_ ) {                                                /*-*/
    ;
} /* test_File_openInMode */
#endif                                                                 /* 000 */


#if 000
/* move file pointer to the specified byte position                           */
PUBLIC void  File_goTo(                                                    /*M*/
    file_t        object_,                                                 /*-*/
    const size_t  new_position_ ) {                                        /*-*/
    ;
} /* test_File_goTo */
#endif                                                                 /* 000 */


#if 000
PUBLIC void  File_goBegin( file_t  object_ ) {                             /*M*/
    ;
} /* test_File_goBegin */
#endif                                                                 /* 000 */


#if 000
PUBLIC void  File_goEnd( file_t  object_ ) {                               /*M*/
    ;
} /* test_File_goEnd */
#endif                                                                 /* 000 */


#if 000
PUBLIC void  File_write(                                                   /*M*/
    file_t        object_,                                                 /*-*/
    const void*   bytes_,                                                  /*-*/
    const size_t  length_in_bytes_ ) {                                     /*-*/
    ;
} /* test_File_write */
#endif                                                                 /* 000 */


#if 000
PUBLIC void  File_writeTextData(                                           /*M*/
    file_t   object_,                                                      /*-*/
    chars_t  text_ ) {                                                     /*-*/
    ;
} /* test_File_writeTextData */
#endif                                                                 /* 000 */


#if 000
PUBLIC void  File_writeInt(                                                /*M*/
    file_t     object_,                                                    /*-*/
    const int  value_ ) {                                                  /*-*/
    ;
} /* test_File_writeInt */
#endif                                                                 /* 000 */


#if 000
PUBLIC void  File_writeSize(                                               /*M*/
    file_t        object_,                                                 /*-*/
    const size_t  value_ ) {                                               /*-*/
    ;
} /* test_File_writeSize */
#endif                                                                 /* 000 */


#if 000
PUBLIC size_t  File_read(                                                  /*M*/
    file_t        object_,                                                 /*-*/
    void*         bytes_,                                                  /*-*/
    const size_t  length_in_bytes_ ) {                                     /*-*/
    ;
} /* test_File_read */
#endif                                                                 /* 000 */


#if 000
PUBLIC new_str_t  File_readTextData( file_t  object_ ) {                   /*M*/
    ;
} /* test_File_readTextData */
#endif                                                                 /* 000 */


#if 000
PUBLIC int  File_readInt( file_t  object_ ) {                              /*M*/
    ;
} /* test_File_readInt */
#endif                                                                 /* 000 */


#if 000
PUBLIC size_t  File_readSize( file_t  object_ ) {                          /*M*/
    ;
} /* test_File_readSize */
#endif                                                                 /* 000 */


#if 000
/* close the opened file                                                      */
PUBLIC void  File_close( file_t  object_ ) {                               /*M*/
    ;
} /* test_File_close */
#endif                                                                 /* 000 */


/* -------------------------------------------------------------------------- */
/* Functions: File Information                                                */


#if 000
PUBLIC new_str_t  file_path( chars_t  filename_ ) {                        /*F*/
    ;
} /* test_file_path */
#endif                                                                 /* 000 */


#if 000
/* if a path wasn't given, adds the current directory to a file name          */
PUBLIC new_str_t  file_name_full(                                          /*F*/
    chars_t  filename_,                                                    /*-*/
    chars_t  default_path_ ) {                                             /*-*/
} /* test_file_name_full */
#endif                                                                 /* 000 */


#if 000
PUBLIC new_str_t  file_locate(                                             /*F*/
    chars_t  filename_,                                                    /*-*/
    chars_t  alternate_paths_ ) {                                          /*-*/
    ;
} /* test_file_locate */
#endif                                                                 /* 000 */


#if 000
PUBLIC new_str_t  file_name( chars_t  filename_ ) {                        /*F*/
    ;
} /* test_file_name */
#endif                                                                 /* 000 */


#if 000
PUBLIC size_t  file_size( chars_t  filename_ ) {                           /*F*/
    ;
} /* test_file_size */
#endif                                                                 /* 000 */


#if 000
PUBLIC new_str_t  file_size_description(                                   /*F*/
    const file_size_t  size_,                                              /*-*/
    const bool         format_remainder_ ) {                               /*-*/
    ;
} /* test_file_size_description */
#endif                                                                 /* 000 */


#if 000
PUBLIC bool  file_type_is_text( chars_t  filename_ ) {                     /*F*/
    ;
} /* test_file_type_is_text */
#endif                                                                 /* 000 */


/* -------------------------------------------------------------------------- */
/* Functions: File Manipulation                                            */


#if 000
PUBLIC bool  file_move(                                                    /*F*/
    chars_t     source_filename_,                                          /*-*/
    chars_t     target_filename_,                                          /*-*/
    const bool  overwrite_ ) {                                             /*-*/
    ;
} /* test_file_move */
#endif                                                                 /* 000 */


#if 000
PUBLIC bool  file_copy(                                                    /*F*/
    chars_t     source_filename_,                                          /*-*/
    chars_t     target_filename_,                                          /*-*/
    const bool  overwrite_ ) {                                             /*-*/
    ;
} /* test_file_copy */
#endif                                                                 /* 000 */


#if 000
PUBLIC bool  file_encrypt(                                                 /*F*/
    chars_t                     source_filename_,                          /*-*/
    chars_t                     target_filename_,                          /*-*/
    const bool                  overwrite_,                                /*-*/
    const File_EncryptModeEnum  encrypt_mode_,                             /*-*/
    chars_t                     cipher_ ) {                                /*-*/
    ;
} /* test_file_encrypt */
#endif                                                                 /* 000 */


#if 000
PUBLIC bool  file_write_bytes(                                             /*F*/
    chars_t       filename_,                                               /*-*/
    const size_t  start_byte_,                                             /*-*/
    const size_t  length_in_bytes_,                                        /*-*/
    const void*   data_ ) {                                                /*-*/
    ;
} /* test_file_write_bytes */
#endif                                                                 /* 000 */


#if 000
PUBLIC bool  file_append_bytes(                                            /*F*/
    chars_t       filename_,                                               /*-*/
    const void*   bytes_,                                                  /*-*/
    const size_t  length_in_bytes_ ) {                                     /*-*/
    ;
} /* test_file_append_bytes */
#endif                                                                 /* 000 */


#if 000
PUBLIC new_bytes_t  file_load_bytes( chars_t  filename_ )                  /*F*/
#endif                                                                 /* 000 */

static void  test_file_load_bytes( void ) {                                /*F*/

#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4204)  /* W:L4 nonstandard extension used :          */
#endif

    struct _test_t {
        chars_t      filename;                                     /* _test_t */
        size_t       check_file_size;                              /* _test_t */
        const char*  check_bytes;                                  /* _test_t */
    }
    test[] = {
        { _T("1byte_A_file"),         1, "A"             },
        { _T("1Byte_A_File.binary"),  1, "A"             },
        { _T("1byte_A_file.txt"),     1, "A"             },
        { _T("empty_file"),           0, ""              },
        { _T("empty_file.txt"),       0, ""              },
        { _T("EmptyFile.binary"),     0, ""              },
        { _T("ascii95.txt"),         95, ASCII_CHARS_A   },
        { _T("base64.txt"),          64, BASE64_DIGITS_A },
        { NULL,                       0, "A"             }
    };

#if defined _MSC_VER
#pragma warning (pop)
#endif

    int  i = 0;
    while (test[i].filename != NULL) {
        const size_t    check_file_size = test[i].check_file_size;
        const uint8_t*  check_bytes     = CAST(uint8_t*, test[i].check_bytes);
        new_bytes_t     bytes           = { 0, NULL };

#if !defined MAX_PATH
#define MAX_PATH  256
#endif

        char_t  filename[MAX_PATH];
        CLEAR(filename);
        STRCAT_S_T(filename, MAX_PATH, _TEST_PATH);
        STRCAT_S_T(filename, MAX_PATH, test[i].filename);

        bytes = file_load_bytes(filename);

        _assert(bytes.size == check_file_size);
        _assert(MEMCMP(bytes.data, check_bytes, check_file_size) == 0);

        if (check_file_size > 0) {
            _assert(check_file_size > 0 && bytes.data != NULL);
        }

        if (check_file_size == 0) {
            _assert(check_file_size == 0 && bytes.data == NULL);
        }

        if (bytes.data != 0) {
            Bytes_free(&bytes);
        }

        i++;
    }
} /* test_file_load_bytes */


#if 000
PUBLIC new_str_t  file_read_text(                                          /*F*/
    chars_t  filename_,                                                    /*-*/
    chars_t  alternate_paths_ ) {                                          /*-*/
    ;    /* test_file_read_text */
}
#endif                                                                 /* 000 */


#if 000
new_chars_t  file_read_text(                                               /*F*/
    chars_t  filename_,                                                    /*-*/
    chars_t  alternate_paths_ ) {                                          /*-*/
    ;    /* test_file_read_text */
}
#endif                                                                 /* 000 */


#if 000
byte_array_t  file_t::loadBytes(                                           /*M*/
    chars_t  filename_,                                                    /*-*/
    chars_t  alternate_paths_ ) {                                          /*-*/
    ;
}
#endif                                                                 /* 000 */


#if 000
byte_array_t  file_load_bytes2(                                            /*F*/
    chars_t  filename_,                                                    /*-*/
    chars_t  alternate_paths_ ) {                                          /*-*/
    ;    /* test_file_load_bytes2 */
}
#endif                                                                 /* 000 */


#if 000
byte_array_t  file_load_bytes( chars_t
                               filename_ ) {                      /*F*/
    ;    /* file_load_bytes */
}
#endif                                                                 /* 000 */


#if 000
/* return true if the specified file name exists.                             */
PUBLIC bool  file_exists( chars_t
                          filename_ ) {                           /*F*/
    ;    /* test_file_exists */
}
#endif                                                                 /* 000 */


#if 000
PUBLIC bool  file_delete_4(                                                /*F*/
    chars_t     filename_,                                                 /*-*/
    const bool  ask_user_,                                                 /*-*/
    const bool  send_to_bin_,                                              /*-*/
    const bool  secure_delete_ ) {                                         /*-*/
    ;
} /* test_file_delete4 */
#endif                                                                 /* 000 */


/* -------------------------------------------------------------------------- */
/* Methods: Path Information                                                  */


#if 000
/* returns true if the specified path is a file or folder                     */
PUBLIC bool  path_exists(                                                  /*F*/
    chars_t     path_,                                                     /*-*/
    const bool  folder_,                                                   /*-*/
    const bool  file_ ) {                                                  /*-*/
    ;
} /* test_path_exists */
#endif                                                                 /* 000 */


#if 000
/* returns only the names of existing folders in the given path               */
PUBLIC new_str_t  path_existing( chars_t  path_ ) {                        /*F*/
    ;
} /* test_path_existing */
#endif                                                                 /* 000 */


#if 000
PUBLIC new_str_t  path_extract(                                            /*F*/
    chars_t     path_or_file_,                                             /*-*/
    const bool  root_only_ ) {                                             /*-*/
    ;
} /* test_path_extract */
#endif                                                                 /* 000 */


#if 000
PUBLIC new_str_t  get_path( chars_t  path_or_file_ ) {                     /*F*/
    ;
} /* test_get_path */
#endif                                                                 /* 000 */


#if 000
PUBLIC new_str_t  path_root( chars_t  path_or_file_ ) {                    /*F*/
    ;
} /* test_path_root */
#endif                                                                 /* 000 */


#if 000
PUBLIC new_str_t  folder_name( chars_t  path_ ) {                          /*F*/
    ;
} /* test_folder_name */
#endif                                                                 /* 000 */


#if 000
/* returns the free space on the specified path                               */
PUBLIC size_t  get_free_space( chars_t  path_ ) {                          /*F*/
    ;
} /* test_get_free_space */
#endif                                                                 /* 000 */


#if 000
/* returns the free space on the specified path (large)                       */
PUBLIC file_size_t  get_free_space_large( chars_t  path_ ) {               /*F*/
    ;
} /* test_get_free_space_large */
#endif                                                                 /* 000 */


#if 000
PUBLIC new_str_t  paths_format( chars_t  paths_ ) {                        /*F*/
    ;
} /* test_paths_format */
#endif                                                                 /* 000 */


#if 000
PUBLIC bool  process_files_in_folder(                                      /*F*/
    chars_t     path_,                                                     /*-*/
    const bool  scan_subfolders_,                                          /*-*/
    bool      (*callback_fn_)( chars_t       file_,                        /*-*/
                               const size_t  file_size_ ) ) {              /*-*/
    ;;
} /* test_process_files_in_folder */
#endif                                                                 /* 000 */


#if 000
PUBLIC bool  file_append_text(                                             /*F*/
    chars_t  filename_,                                                    /*-*/
    chars_t  text_ ) {                                                     /*-*/
    ;;
} /* test_file_append_text */
#endif                                                                 /* 000 */


/* -------------------------------------------------------------------------- */


PUBLIC void  test_file_class( void );                                      /*F*/
PUBLIC void  test_file_class( void ) {                                     /*F*/
    test_file_load_bytes();
} /* test_file_class */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
