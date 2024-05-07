/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_file_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_FILE__H
#define      INCLUDED_LIBEX_FILE__H
#include "libex_file.h"

#define FILE_SIZE_MAX                   LX_FILE_SIZE_MAX

#define file_t                          lx_file_t
#define new_file_t                      lx_new_file_t
#define file_size_t                     lx_file_size_t

#define File_TextModeEnum               lx_File_TextModeEnum
#define FILE_TEXT_AUTO                  LX_FILE_TEXT_AUTO
#define FILE_TEXT_ANSI                  LX_FILE_TEXT_ANSI
#define FILE_TEXT_WIDE                  LX_FILE_TEXT_WIDE

#define File_EncryptModeEnum            lx_File_EncryptModeEnum
#define FILE_NO_ENCRYPT                 LX_FILE_NO_ENCRYPT
#define FILE_ENCRYPT                    LX_FILE_ENCRYPT
#define FILE_DECRYPT                    LX_FILE_DECRYPT

/* -------------------------------------------------------------------------- */
/* Constructors / Destructor:                                                 */

#define File_init                       lx_File_init
#define File_initInMode                 lx_File_initInMode
#define File_initRead                   lx_File_initRead

#define File_free                       lx_File_free

/* -------------------------------------------------------------------------- */
/* Properties: Read-Only                                                      */

#if LX_PLATFORM_WIN32
#define File_getHandle                  lx_File_getHandle
#endif

#define File_getFileSize                lx_File_getFileSize
#define File_getName                    lx_File_getName
#define File_isOpen                     lx_File_isOpen
#define File_setFileSize                lx_File_setFileSize

/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */

#define File_close                      lx_File_close
#define File_goBegin                    lx_File_goBegin
#define File_goEnd                      lx_File_goEnd
#define File_goTo                       lx_File_goTo
#define File_open                       lx_File_open
#define File_openInMode                 lx_File_openInMode
#define File_read                       lx_File_read
#define File_readInt                    lx_File_readInt
#define File_readSize                   lx_File_readSize
#define File_readTextData               lx_File_readTextData
#define File_write                      lx_File_write
#define File_writeInt                   lx_File_writeInt
#define File_writeSize                  lx_File_writeSize
#define File_writeTextData              lx_File_writeTextData

/* -------------------------------------------------------------------------- */
/* Functions:                                                                 */

#define file_delete                     lx_file_delete
#define file_delete_4                   lx_file_delete_4
#define file_exists                     lx_file_exists

/* -------------------------------------------------------------------------- */
/* file information functions                                                 */

#define file_locate                     lx_file_locate
#define file_name                       lx_file_name
#define file_name_full                  lx_file_name_full
#define file_path                       lx_file_path
#define file_size                       lx_file_size
#define file_size_description           lx_file_size_description
#define file_type_is_text               lx_file_type_is_text

/* -------------------------------------------------------------------------- */
/* file manipulation functions                                                */

#define file_append_bytes               lx_file_append_bytes
#define file_append_text                lx_file_append_text
#define file_append_text_n              lx_file_append_text_n
#define file_copy                       lx_file_copy
#define file_encrypt                    lx_file_encrypt
#define file_load_bytes                 lx_file_load_bytes
#define file_move                       lx_file_move
#define file_write_bytes                lx_file_write_bytes

/* -------------------------------------------------------------------------- */

#define file_read_text                  lx_file_read_text
#define file_read_text1                 lx_file_read_text1

/* -------------------------------------------------------------------------- */
/* path information functions                                                 */

#define folder_name                     lx_folder_name
#define get_free_space                  lx_get_free_space
#define get_free_space_large            lx_get_free_space_large
#define get_path                        lx_get_path
#define path_existing                   lx_path_existing
#define path_exists                     lx_path_exists
#define path_extract                    lx_path_extract
#define path_root                       lx_path_root
#define paths_format                    lx_paths_format
#define process_files_in_folder         lx_process_files_in_folder

#endif                                                                   /*eof*/
