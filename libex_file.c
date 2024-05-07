/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                        [libex_file.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_file_.h"
#if defined INCLUDED_LIBEX_FILE_H

#include "libex_config_.h"

#include <limits.h>
#include <stdarg.h>  /* for va_arg va_end va_list va_start           */
#include <stdio.h>   /* for fpos_t fclose() fread() fseek() SEEK_SET */
/*                          file_size _fsopen() SEEK_END fgetpos()   */
#include <string.h>  /* for memset()                                 */

#if PLATFORM_LINUX
#define _XOPEN_SOURCE 500
#include <fcntl.h>
#include <ftw.h>
#endif

#if PLATFORM_WIN32
#include <share.h>  /* for _SH_DENYNO */
#include <tchar.h>  /* on Windows     */
#endif

#include "libex_.h"
#include "libex_call_.h"
#include "libex_const_.h"
#include "libex_debug_.h"
#include "libex_dtime_.h"
#include "libex_error_.h"
#include "libex_logging_.h"  /* important to give descriptive errors */
#include "libex_macro_.h"
#include "libex_string_class_.h"
#include "libex_stringc_.h"
#include "libex_system_.h"
#include "libex_type_.h"
#include "libex_variant_functions_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#if PLATFORM_WIN32 && defined _MSC_VER
#pragma comment (lib, "shell32.lib")
/*      SHFileOperation() */
#endif


#define _CHECK_HAS_NAME( NAME_, EXEC_ON_ERROR_, SRC_UID_ )   \
    if (STRLEN_T(NAME_) == 0)                                \
    {                                                        \
        ERR(_T("file or folder not specified"), SRC_UID_);   \
        EXEC_ON_ERROR_                                       \
    }                                                    /*#*/


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


typedef struct  _file_t {
    new_chars_t  full_name;                                        /* _file_t */
    new_chars_t  path;                                             /* _file_t */
    new_chars_t  name;                                             /* _file_t */
    size_t       size;                                             /* _file_t */
    size_t       pos;                                              /* _file_t */
    dtime_t      created_on;                                       /* _file_t */
    dtime_t      modified_on;                                      /* _file_t */
    bool         is_opened;                                        /* _file_t */
    bool         modify;                                           /* _file_t */

#if PLATFORM_LINUX
    int          file;                                             /* _file_t */
#endif

#if PLATFORM_WIN32
    HANDLE_win   file;                                             /* _file_t */
#endif
}
_file_t;


/* -------------------------------------------------------------------------- */
/* Functions: Private                                                         */


#define _BASE_OBJ_WRAP_INC
#define _OBJ_HANDLE_TYPE   file_t
#define _OBJ_INNER_TYPE    _file_t
#define _OBJ_ALLOC_FN_UID  UID(FBE11A)
#define _OBJ_FREE_FN_UID   UID(F48E41)
#define _OBJ_CONST_FN_UID  UID(F7CE8B)
#define _OBJ_FN_UID        UID(FCB40F)
#define _OBJ_WRAP_FN_UID   UID(F9F2C3)
#include "libex_object_wrapper.inc.c"


/* -------------------------------------------------------------------------- */
/* Constructors / Destructor:                                                 */


PUBLIC new_file_t  File_init( chars_t  filename_ ) {                       /*C*/
    GO                                                            (UID(FB6218));
    const new_file_t  ret = File_initInMode(filename_, true, true);
    RETURN(ret);
} /* File_init */


PUBLIC new_file_t  File_initInMode(                                        /*C*/
    chars_t     filename_,                                                 /*-*/
    const bool  modify_,                                                   /*-*/
    const bool  shared_ ) {                                                /*-*/
    GO                                                            (UID(F8479C));
    _file_t*    ob  = _object_alloc();
    new_file_t  ret = _object_wrap(ob);

    ob->modify = modify_;
    ob->name   = T_chars(filename_);

    File_openInMode(ret, filename_, modify_, shared_);

    RETURN(ret);
} /* File_initInMode */


/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */


PUBLIC void  File_free( file_t*  object_ ) {                               /*D*/
    GO                                                            (UID(F44183));
    _file_t* const  me = _object(object_, UID(E5C333));

    File_close(*object_);

    me->modify    = true;
    me->is_opened = false;
    me->pos       = 0;
    me->size      = 0;

#if PLATFORM_WIN32
    me->file = 0;
#endif

    freeT(&me->full_name);
    freeT(&me->name);
    freeT(&me->path);

    CLEAR(me->created_on);
    CLEAR(me->modified_on);

    _object_free(object_);

    RETURN(NIL);
} /* File_free */


/* -------------------------------------------------------------------------- */
/* Properties: Read-Only                                                      */


#if PLATFORM_WIN32
PUBLIC HANDLE_win  File_getHandle( file_t  object_ ) {                     /*P*/
    GO                                                            (UID(F26CE6));
    const _file_t* const  me  = _object(&object_, UID(E627F6));
    const HANDLE_win      ret = CAST(HANDLE_win, me->file);
    RETURN(ret);
} /* File_getHandle */
#endif                                                      /* PLATFORM_WIN32 */


PUBLIC bool  File_isOpen( const file_t  object_ ) {                        /*P*/
    GO                                                            (UID(F07363));
    const _file_t* const  me  = _object_const(&object_, UID(E56C97));
    const bool            ret = me->is_opened;
    RETURN(ret);
} /* File_isOpen */


PUBLIC chars_t  File_getName( const file_t  object_ ) {                    /*P*/
    GO                                                            (UID(FA5295));
    const _file_t* const  me = _object_const(&object_, UID(E9B9DD));
    chars_t  ret = me->full_name;
    RETURN(ret);
} /* File_getName */


PUBLIC size_t  File_getFileSize( const file_t  object_ ) {                 /*P*/
    GO                                                            (UID(F46E16));
    const _file_t* const  me = _object_const(&object_, UID(E8877B));
    const size_t  ret = me->is_opened ? me->size : 0;
    RETURN(ret);
} /* File_getFileSize */


PUBLIC void  File_setFileSize(                                             /*P*/
    file_t        object_,                                                 /*-*/
    const size_t  value_ ) {                                               /*-*/
    GO                                                            (UID(F791F9));
    _file_t* const  me = _object(&object_, UID(E98220));
    me->size = value_;
    RETURN(NIL);
} /* File_setFileSize */


/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */


/* TODO: File_open(). Use macro instead. */
PUBLIC void  File_open(                                                    /*M*/
    file_t   object_,                                                      /*-*/
    chars_t  filename_ ) {                                                 /*-*/
    GO                                                            (UID(F1810B));
    File_openInMode(object_, filename_, true, true);
    RETURN(NIL);
} /* File_open */


PUBLIC void  File_openInMode(                                              /*M*/
    file_t      object_,                                                   /*-*/
    chars_t     filename_,                                                 /*-*/
    const bool  modify_,                                                   /*-*/
    const bool  shared_ ) {                                                /*-*/
    GO                                                            (UID(F68F1F));
    _file_t* const  me = _object(&object_, UID(ED7258));

    size_t  fsize = 0;

    if (me->is_opened) {
        File_close(object_);
    }

    me->modify = modify_;

#if PLATFORM_LINUX
    {
        int  access = (modify_ ? (O_CREAT | O_RDWR) : O_RDONLY);
        if (!shared_) {
            access |= O_EXCL;
        }

        {
            const int  file = open(filename_, access);

            if (file == -1) {
                me->is_opened = false;
                OS_WARN(_T("open()"), UID(E825DD));
                RETURN(NIL);
            }

            {
                const off_t  pos = lseek(file, 0, SEEK_END);

                if (pos == CAST(off_t, -1)) {
                    OS_WARN(_T("lseek()"), UID(E6BCC2));
                    RETURN(NIL);
                }

                fsize    = CAST(size_t, pos);
                me->pos  = fsize - 1;
                me->file = file;
            }
        }
    }
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    {
        const DWORD_win  desired_access = (modify_ ? GENERIC_WRITE_win : 0) |
                                          GENERIC_READ_win;

        const DWORD_win  share_mode =
            shared_ ? (FILE_SHARE_READ_win | FILE_SHARE_WRITE_win) : 0;

        const HANDLE_win  file =
            CreateFile_win(
                filename_,                  /* fine name            */
                desired_access,             /* desired access       */
                share_mode,                 /* share mode           */
                NULL,                       /* security attributes  */
                OPEN_ALWAYS_win,            /* creation disposition */
                FILE_ATTRIBUTE_NORMAL_win,  /* flags and attributes */
                NULL);                      /* template file        */

        if (file == INVALID_HANDLE_VALUE_win) {
            me->is_opened = false;
            OS_WARN(_T("CreateFile_win()"), UID(EF94F6));
            RETURN(NIL);
        }

        fsize = GetFileSize_win(file, NULL);

        if (fsize == INVALID_FILE_SIZE_win) {
            OS_WARN(_T("GetFileSize_win()"), UID(ECC78A));
            RETURN(NIL);
        }

        me->file = file;
    }
#endif                                                      /* PLATFORM_WIN32 */

    me->size      = fsize;
    me->is_opened = true;
    File_goBegin(object_);
    RETURN(NIL);
} /* File_openInMode */


/* move file pointer to the specified byte position                           */
PUBLIC void  File_goTo(                                                    /*M*/
    file_t        object_,                                                 /*-*/
    const size_t  new_position_ ) {                                        /*-*/
    GO                                                            (UID(FE5D09));
    _file_t* const  me = _object(&object_, UID(EBCB50));

    if (new_position_ > (me->size - 1)) {
        WARN(_T("new_position_ out of range."), UID(E4CCEB));
        RETURN(NIL);
    }

#if PLATFORM_LINUX

    if (me->pos != new_position_) {
        const off_t  pos = lseek(me->file, new_position_, SEEK_SET);

        if (pos == CAST(off_t, -1)) {
            OS_WARN(_T("lseek()"), UID(E57C4B));
            RETURN(NIL);
        }
    }

#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32

    if (me->pos != new_position_) {
        const DWORD_win  result
            = SetFilePointer_win(
                  me->file,         /* file                 */
                  0,                /* lDistanceToMove      */
                  0,                /* lpDistanceToMoveHigh */
                  FILE_BEGIN_win);  /* dwMoveMethod         */

        if (result == INVALID_SET_FILE_POINTER_win) {
            OS_WARN(_T("SetFilePointer_win()")
                    _T(" == INVALID_SET_FILE_POINTER_win"), UID(EA92ED));
            RETURN(NIL);
        }
    }

#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* File_goTo */


PUBLIC void  File_goBegin( file_t  object_ ) {                             /*M*/
    GO                                                            (UID(F1BCCA));
    File_goTo(object_, 0);
    RETURN(NIL);
} /* File_goBegin */


PUBLIC void  File_goEnd( file_t  object_ ) {                               /*M*/
    GO                                                            (UID(F12C23));
    const _file_t* const  me = _object_const(&object_, UID(E0ECB8));
    File_goTo(object_, me->size);
    RETURN(NIL);
} /* File_goEnd */


PUBLIC void  File_write(                                                   /*M*/
    file_t        object_,                                                 /*-*/
    const void*   bytes_,                                                  /*-*/
    const size_t  length_in_bytes_ ) {                                     /*-*/
    GO                                                            (UID(F77F50));
#if PLATFORM_LINUX
    UNUSED(object_);
    UNUSED(bytes_);
    UNUSED(length_in_bytes_);
    IMPLEMENT_LINUX();  /* TODO: implement File_write() on Linux */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    _file_t* const  me = _object(&object_, UID(E3619F));

    const DWORD_win  begun     = GetTickCount_win();
    const DWORD_win  offset_lo = CAST(DWORD_win, me->size);
    const DWORD_win  offset_hi = 0;
    const DWORD_win  bytes_lo  = offset_lo + CAST(DWORD_win, length_in_bytes_);
    const DWORD_win  bytes_hi  = 0;
    BOOL_win         locked    = FALSE_win;

    /* return if the output length is zero-length */
    if (length_in_bytes_ < 1) {
        RETURN(NIL);
    }

    /* lock the part of the file being written to */
    /* (attempt to acquire lock in 2 seconds)     */
    while (!locked && GetTickCount_win() < begun + 2000) {
        locked = LockFile_win(
                     me->file, offset_lo, offset_hi, bytes_lo, bytes_hi);

        if (!locked) {
            Sleep_win(250);
        }
    }

    if (!locked) {
        OS_WARN(_T("LockFile_win()"), UID(E22D30));
        RETURN(NIL);
    }

    /* write to the file */
    if (locked) {
        DWORD_win  bytes_writ = 0;
        const BOOL_win   wfile = WriteFile_win(
                                     me->file,     /* file handle */
                                     bytes_,       /* lpBuffer    */

                                     CAST(DWORD_win, length_in_bytes_),
                                     /* nNumberOfBytesToWrite */

                                     &bytes_writ,  /* lpNumberOfBytesWritten */
                                     NULL);        /* lpOverlapped           */

        VERIFY(wfile, UID(E07439));

        if (wfile) {
            me->pos  += bytes_writ;
            me->size += bytes_writ;
        }

        /* unlock the file */
        VERIFY(UnlockFile_win(
                   me->file, offset_lo, offset_hi, bytes_lo, bytes_hi),
               UID(ED920A));
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* File_write */


PUBLIC void  File_writeTextData(                                           /*M*/
    file_t   object_,                                                      /*-*/
    chars_t  text_ ) {                                                     /*-*/
    GO                                                            (UID(FBC57A));
    const size_t  len        = STRLEN_T(text_);
    const size_t  bytes_size = len * sizeof(char_t);

    File_write(object_, &len, sizeof(len));
    File_write(object_, text_, bytes_size);
    RETURN(NIL);
} /* File_writeTextData */


PUBLIC void  File_writeInt(                                                /*M*/
    file_t     object_,                                                    /*-*/
    const int  value_ ) {                                                  /*-*/
    GO                                                            (UID(F8D7B4));
    File_write(object_, &value_, sizeof(value_));
    RETURN(NIL);
} /* File_writeInt */


PUBLIC void  File_writeSize(                                               /*M*/
    file_t        object_,                                                 /*-*/
    const size_t  value_ ) {                                               /*-*/
    GO                                                            (UID(FB792C));
    File_write(object_, &value_, sizeof(value_));
    RETURN(NIL);
} /* File_writeSize */


PUBLIC size_t  File_read(                                                  /*M*/
    file_t        object_,                                                 /*-*/
    void*         bytes_,                                                  /*-*/
    const size_t  length_in_bytes_ ) {                                     /*-*/
    GO                                                            (UID(FD075A));
    _file_t* const  me = _object(&object_, UID(EB7D61));

#if PLATFORM_LINUX
    const size_t  ret = read(me->file, bytes_, length_in_bytes_);
    if (ret == CAST(size_t, -1)) {
        OS_WARN(_T("read()"), UID(E88C73));
    } else {
        me->pos += ret;
    }
#endif

#if PLATFORM_WIN32
    DWORD_win  ret = 0;
    if (0 != ReadFile_win(
            me->file, bytes_, CAST(DWORD_win, length_in_bytes_), &ret, NULL)) {
        me->pos += ret;
    } else {
        OS_WARN(_T("ReadFile_win()"), UID(E4A738));
    }
#endif

    RETURN(CAST(size_t, ret));  /* return number of bytes read */
} /* File_read */


PUBLIC new_str_t  File_readTextData( file_t  object_ ) {                   /*M*/
    GO                                                            (UID(FBB1EB));
    /* read length of text */
    size_t  len = 0;
    File_read(object_, &len, sizeof(len));

    {
        /* read text from the file: */
        new_str_t    ret;
        new_chars_t  buf = mallocT(len + 1);
        File_read(object_, buf, len * sizeof(char_t));
        *(buf + len) = '\0';
        ret = S_newT(buf);
        RETURN(ret);
    }
} /* File_readTextData */


PUBLIC int  File_readInt( file_t  object_ ) {                              /*M*/
    GO                                                            (UID(F30D63));
    int  ret = 0;
    File_read(object_, &ret, sizeof(ret));
    RETURN(ret);
} /* File_readInt */


PUBLIC size_t  File_readSize( file_t  object_ ) {                          /*M*/
    GO                                                            (UID(F039B0));
    size_t  ret = 0;
    File_read(object_, &ret, sizeof(ret));
    RETURN(ret);
} /* File_readSize */


/* close the opened file                                                      */
PUBLIC void  File_close( file_t  object_ ) {                               /*M*/
    GO                                                            (UID(FC36B5));
    _file_t* const  me = _object(&object_, UID(EDD6AB));

#if PLATFORM_WIN32

    if (me->is_opened) {
        if (me->modify) {
            VERIFY(FlushFileBuffers_win(me->file), UID(E906A2));
        }

        VERIFY(CloseHandle_win(me->file), UID(E20B6B));
        me->file      = 0;
        me->is_opened = false;
    }

#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* File_close */


/* -------------------------------------------------------------------------- */
/* Functions: File Information                                                */


PUBLIC new_str_t  file_path( chars_t  filename_ ) {                        /*F*/
    GO                                                            (UID(F0F9BA));
    const new_str_t  ret = path_extract(filename_, false);
    RETURN(ret);
} /* file_path */


/* if a path was not specified, adds the current directory to a file name     */
PUBLIC new_str_t  file_name_full(                                          /*F*/
    chars_t  filename_,                                                    /*-*/
    chars_t  default_path_ ) {                                             /*-*/
    GO                                                            (UID(FA7F0E));
    new_str_t  ret = { NULL };

#if PLATFORM_LINUX
    UNUSED(filename_);
    UNUSED(default_path_);

    IMPLEMENT_LINUX();  /* TODO: implement file_name_full() on Linux */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    char_t     buf[MAX_PATH_win];
    new_str_t  default_path = { NULL };
    new_str_t  path         = { NULL };

    /* if trimmed filename_ is blank, return a blank */
    if (is_whitespaceT(filename_)) {
        ret = S_blank();
        RETURN(ret);
    }

    path = file_path(filename_);

    if (!emptyS(path)) {

        MEMSET(buf, 0x00, sizeof(buf));

        if (0 != GetFullPathName_win(path.cs, MAX_PATH_win, buf, NULL)) {
            freeS(&path);
            path = S_chars(buf);
        }

        if (!path_exists(path.cs, true, false)) {
            freeS(&path);
        }
    }

    default_path = file_path(default_path_);

    if (!emptyS(default_path)) {
        MEMSET(buf, 0x00, sizeof(buf));

        if (0 != GetFullPathName_win(
                default_path.cs, MAX_PATH_win, buf, NULL)) {

            freeS(&default_path);
            default_path = S_chars(buf);
        }

        if (!path_exists(default_path.cs, true, false)) {
            freeS(&default_path);
        }
    }

    /* if both the file name's path and default path are unspecified */
    /* or don't exist, then use the current directory as the path    */
    if (emptyS(path) && emptyS(default_path)) {

        DWORD_win  result = 0;
        MEMSET(buf, 0x00, sizeof(buf));
        result = GetCurrentDirectory_win(MAX_PATH_win, buf);

        if (!result) {
            OS_ERR(_T("GetCurrentDirectory_win"), UID(E4A74D));
        } else {
            freeS(&path);
            path   = S_chars(buf);
            result = GetFullPathName_win(path.cs, MAX_PATH_win, buf, NULL);

            if (!result) {
                OS_ERR(_T("GetFullPathName_win"), UID(E76BDD));
            } else {
                freeS(&path);
                path = S_chars(buf);
            }
        }
    }

    if (emptyS(path) && !emptyS(default_path)) {
        freeS(&path);
        path = S_copy(default_path);
    }

    {
        new_str_t     filename = file_name(filename_);
        const size_t  path_len = lengthS(path);
        const size_t  len      = path_len + 1 + lengthS(filename);

        ret = S_reserve(len);
        addTS(&ret, path.cs);


        if (path.cs[path_len - 1] != '\\') {
            addTS(&ret, _T("\\"));
        }

        addTS(&ret, filename.cs);
        freeS(&default_path);
        freeS(&filename);
    }

#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* file_name_full */


PUBLIC new_str_t  file_locate(                                             /*F*/
    chars_t  filename_,                                                    /*-*/
    chars_t  alternate_paths_ ) {                                          /*-*/
    GO                                                            (UID(FEFF20));
    new_str_t  ret    = S_chars(filename_);
    bool       exists = file_exists(ret.cs);

    if (!exists) {
        new_str_t  paths = S_chars(alternate_paths_);
        trimIn1S(&paths);

        if (!emptyS(paths)) {
            new_str_t  name = file_name(ret.cs);
            const int  max  = tokenCountS(paths, _T(";"));
            int        i    = 0;

            for (i = 0; i < max; i++) {
                new_str_t  path = S_getToken(paths, i, _T(";"));
                trimIn1S(&path);
                trimInS(&path, _T("\\"), TRIM_END);

                /* TODO: use simpler, one-line syntax here, when available */
                setInS(&ret, path.cs);
                addTS(&ret, _T("\\"));
                addTS(&ret, name.cs);

                freeS(&path);

                if (file_exists(ret.cs)) {
                    exists = true;
                    break;
                }
            }
            freeS(&name);
        }
        freeS(&paths);
    }

    if (!exists) {
        ret = S_blank();
    }
    RETURN(ret);
} /* file_locate */


PUBLIC new_str_t  file_name( chars_t  filename_ ) {                        /*F*/
    GO                                                            (UID(FFBF51));
    new_str_t  ret = S_blank();

    /* find position of the rightmost slash or backslash */
    size_t  loc = find_last_T(filename_, _T("\\"));
    {
        const size_t  loc_slash = find_last_T(filename_, _T("/"));
        if (loc_slash > loc) {
            loc = loc_slash;
        }
    }

    /* if a (back)slash is found, return the text after the (back)slash */
    /* (otherwise return the same file name)                            */
    if (loc == NONE) {
        ret = S_chars(filename_);
    } else {
        ret = S_chars(filename_ + loc + 1);
    }
    RETURN(ret);
} /* file_name */


PUBLIC size_t  file_size( chars_t  filename_ ) {                           /*F*/
    GO                                                            (UID(FF4ED5));
    size_t  ret = 0;

#if PLATFORM_LINUX
    UNUSED(filename_);

    IMPLEMENT_LINUX();  /* TODO: implement file_size() on Linux */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    /* prepare data structure */
    WIN32_FIND_DATA_win  fdata;
    CLEAR(fdata);

    _CHECK_HAS_NAME(filename_, RETURN(0); , UID(E9ED5A));

    {
        /* get file information: */
        const HANDLE_win  handle = FindFirstFile_win(filename_, &fdata);

        if (handle == INVALID_HANDLE_VALUE_win) {
            new_chars_t  msg = formatT(_T("FindFirstFile_win('%s')")
                                       _T(" == INVALID_HANDLE_VALUE_win"),
                                       filename_);
            OS_WARN(msg, UID(E1483D));
            freeT(&msg);
            RETURN(0);
        }

        if (!FindClose_win(handle)) {
            OS_WARN(_T("FindClose_win()"), UID(E84A96));
            RETURN(0);
        }
    }

    if (fdata.nFileSizeHigh > 0) {
        RETURN(SIZE_MAX);
    }

    ret = fdata.nFileSizeLow;
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* file_size */


PUBLIC new_str_t  file_size_description(                                   /*F*/
    file_size_t  size_,                                                    /*-*/
    const bool   format_remainder_ ) {                                     /*-*/
    GO                                                            (UID(FA7113));
    file_size_t  i         = 0;
    file_size_t  factor    = 0;
    file_size_t  remainder = 0;
    chars_t      suffix    = NULL;
    new_str_t    ret       = S_reserve(64);

    if (size_ >= GB(1)) {
        factor = GB(1);
        suffix = _T("gb");

    } else if (size_ >= MB(1)) {
        factor = MB(1);
        suffix = _T("mb");

    } else if (size_ >= KB(1)) {
        factor = KB(1);
        suffix = _T("kb");
    } else {
        factor = 1;
        if (size_ == 1) {
            suffix = _T(" byte");
        } else {
            suffix = _T(" bytes");
        }
    }

    if (factor < KB(1)) {
        i = size_;
        remainder = 0;
    } else {
        i = size_ / factor;
        remainder = size_ % factor;
    }

    {
        new_chars_t  fsize = T_int(CAST(int, i));

        addTS(&ret, fsize);
        addTS(&ret, suffix);

        if (format_remainder_ && remainder > 0) {
            new_str_t  str = file_size_description(remainder, false);
            addTS(&ret, _T(" + "));
            addTS(&ret, str.cs);
            freeS(&str);
        }
        RETURN(ret);
    }
} /* file_size_description */


PUBLIC bool  file_type_is_text( chars_t  filename_ ) {                     /*F*/
    GO                                                            (UID(F55136));
    chars_t  _TEXT_FILE_TYPES[] = {
        /* Miscellaneous Files */
        _T(".bat"),
        _T(".reg"),
        _T(".sql"),
        _T(".txt"),

        /* Web Files */
        _T(".asp"),
        _T(".aspx"),
        _T(".css"),
        _T(".ctp"),
        _T(".hta"),
        _T(".htm"),
        _T(".html"),
        _T(".java"),
        _T(".js"),
        _T(".php"),
        _T(".shtml"),
        _T(".xhtml"),

        _T(".ctp"),

        /* Android Files */
        _T(".classpath"),
        _T(".java"),
        _T(".prefs"),
        _T(".project"),
        _T(".properties"),

        /* Markup Files */
        _T(".svg"),
        _T(".xaml"),
        _T(".xml"),

        /* C++ */
        _T(".c"),
        _T(".cbp"),
        _T(".clw"),
        _T(".cpp"),
        _T(".def"),
        _T(".dsp"),
        _T(".dsw"),
        _T(".fd"),
        _T(".h"),
        _T(".hc"),
        _T(".hpp"),
        _T(".layout"),
        _T(".manifest"),
        _T(".odl"),
        _T(".plg"),
        _T(".rc"),
        _T(".rc2"),
        _T(".sln"),
        _T(".vcproj"),
        _T(".vcxproj"),
        _T(".workspace"),

        /* C# */
        _T(".cs"),
        _T(".csproj"),
        _T(".resx"),
        _T(".sln"),
        _T(".user"),
        _T(".xsd"),
        _T(".xsx"),

        /* Visual Basic */
        _T(".bas"),
        _T(".cls"),
        _T(".ctl"),
        _T(".dep"),
        _T(".frm"),
        _T(".log"),
        _T(".pdm"),
        _T(".vbp"),
        _T(".vbw"),

        NULL
    };

    {
        uint32_t  type = 0;
        while (_TEXT_FILE_TYPES[type++] != NULL) {
            chars_t  str = _TEXT_FILE_TYPES[type];
            if (ends3T(filename_, str, IGNORE_CASE)) {
                RETURN(true);
            }
        }
    }
    RETURN(false);
} /* file_type_is_text */


/* -------------------------------------------------------------------------- */
/* Functions: File Manipulation                                               */


PUBLIC bool  file_move(                                                    /*F*/
    chars_t     source_filename_,                                          /*-*/
    chars_t     target_filename_,                                          /*-*/
    const bool  overwrite_ ) {                                             /*-*/
    GO                                                            (UID(F7B3F2));
    bool  ret = false;

    if (file_exists(target_filename_)) {
        if (overwrite_) {
            file_delete(target_filename_);
        } else {
            RETURN(false);
        }
    }

#if PLATFORM_LINUX
    UNUSED(source_filename_);
    UNUSED(target_filename_);
    UNUSED(overwrite_);

    IMPLEMENT_LINUX();  /* TODO: implement file_move() on Linux */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    if (0 != MoveFile_win(source_filename_, target_filename_)) {
        ret = true;

    } else {
        new_chars_t  msg = formatT(_T("MoveFile_win('%s', '%s')"),
                                   source_filename_, target_filename_);
        OS_WARN(msg, UID(E80308));
        freeT(&msg);
        ret = false;
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* file_move */


PUBLIC bool  file_copy(                                                    /*F*/
    chars_t     source_filename_,                                          /*-*/
    chars_t     target_filename_,                                          /*-*/
    const bool  overwrite_ ) {                                             /*-*/
    GO                                                            (UID(F07B37));
#if PLATFORM_LINUX
    UNUSED(source_filename_);
    UNUSED(target_filename_);
    UNUSED(overwrite_);
    IMPLEMENT_LINUX();  /* TODO: implement file_copy() on Linux */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    if (file_exists(target_filename_)) {
        if (overwrite_) {
            file_delete(target_filename_);
        } else {
            RETURN(false);
        }
    }

    if (0 != CopyFile_win(source_filename_, target_filename_, overwrite_
                          ? FALSE_win : TRUE_win)) {
        RETURN(true);
    } else {
        new_chars_t  msg = formatT(_T("CopyFile_win('%s', '%s')"),
                                   source_filename_, target_filename_);
        OS_WARN(msg, UID(E5ADA7));
        freeT(&msg);
    }
#endif                                                      /* PLATFORM_WIN32 */
    RETURN(false);
} /* file_copy */


PUBLIC bool  file_encrypt(                                                 /*F*/
    chars_t                     source_filename_,                          /*-*/
    chars_t                     target_filename_,                          /*-*/
    const bool                  overwrite_,                                /*-*/
    const File_EncryptModeEnum  encrypt_mode_,                             /*-*/
    chars_t                     cipher_ ) {                                /*-*/
    GO                                                            (UID(FE62E9));
    const size_t  MAX_BUF_SIZE    = MB(1);
    const size_t  FIXED_KEY_COUNT = 16;

    static const uint32_t  FIXED_KEYS[16]  = {
        0xAD07B932, 0xBA903D01, 0x7DFE2EDC, 0xCD990791,
        0x51BA2069, 0xE4B0BE7B, 0x1378A4CE, 0x976C5B19,
        0x03A25ABD, 0x95AC7D31, 0xC5D1A3A1, 0xD2A00E91,
        0xB12A8BA7, 0x357AC109, 0x00970001, 0x318DA342
    };

    size_t     buf_size      = 0;
    size_t     cipher_no     = 0;
    size_t     ciphers_count = 0;
    size_t     count         = 0;
    size_t     fsize         = 0;
    size_t     bytes_read    = 0;
    size_t     bytes_writ    = 0;
    uint32_t   seed          = 0;
    uint32_t*  ciphers       = NULL;
    uint8_t*   buf           = NULL;
    file_t     source_file   = { NULL };
    file_t     target_file   = { NULL };

    /* determine the source file name */
    if (!file_exists(source_filename_)) {
        new_chars_t  err = formatT(_T("File '%s' does not exist"),
                                   source_filename_);
        ERR(err, UID(E19AAD));
        freeT(&err);
        RETURN(false);
    }

    /* build target file name */
    if (!overwrite_ && file_exists(target_filename_)) {
        new_chars_t  err = formatT(_T("File '%s' already exists"),
                                   target_filename_);
        ERR(err, UID(E734DD));
        freeT(&err);
        RETURN(false);
    }

    /* open source file for reading (move to beginning of file) */
    fsize       = file_size(source_filename_);
    source_file = File_init(source_filename_);

    /* open target file for writing */
    target_file = File_initInMode(target_filename_, true, false);

    /* prepare memory buffer */

    /* NOTE: THIS COULD CAUSE PROBLEMS WITH SMALLER FILES */
    buf_size = fsize < MAX_BUF_SIZE ? fsize : MAX_BUF_SIZE;
    buf      = MALLOC(buf_size);
    count    = buf_size / 4;
    CLEAR_N(buf, buf_size);

    /* loop to copy data from source to memory and to target file */
    if (encrypt_mode_ != FILE_NO_ENCRYPT) {
        size_t  bit       = 0;
        size_t  i         = 0;
        size_t  key_index = 0;
        size_t  shift     = 0;

        const size_t  cipher_len = STRLEN_T(cipher_);

        /* copy the cipher to a DWORD_win-aligned (uint32_t) memory block */
        ciphers_count = (cipher_len / sizeof(uint32_t))
                        + ((cipher_len % sizeof(uint32_t)) == 0 ? 0 : 1);
        ciphers = MALLOC(sizeof(uint32_t) * ciphers_count);
        CLEAR_N(ciphers, sizeof(uint32_t) * ciphers_count);
        MEMCPY(ciphers, cipher_, cipher_len);

        /* calculate the 'seed' key:                    */
        /* If there was no 'seed' key, similar ciphers, */
        /* e.g. '123' and '124' would partially decrypt */
        /* the file (~90%)! What this code does is, it  */
        /* checks each bit of the password passed in    */
        /* cipher_ and XORs it with one of the fixed    */
        /* keys, rolls their bits to produce            */
        /* a reasonably unique seed value.              */

        for (i = 0; i < cipher_len; i++) {
            for (bit = 0; bit < 8; bit++) {
                if (IS_SET_BIT(cipher_[i], bit)) {
                    seed ^= ROLL_BITS_RIGHT(FIXED_KEYS[key_index], shift);

                    if (++key_index >= FIXED_KEY_COUNT) {
                        key_index = 0;
                    }

                    if (++shift >= 32) {
                        shift = 0;
                    }
                }
            }
        }
    }

    do {
        bytes_read =
            File_read(source_file, buf, CAST(uint32_t, buf_size));

        if (bytes_read == 0) {
            break;
        }

        /* apply an operation to the file buffer */
        /* (encrypt, decrypt, or leave alone)    */
        if (encrypt_mode_ != FILE_NO_ENCRYPT) {
            uint32_t           key       = seed;
            uint32_t*          dword     = CAST(uint32_t*, buf);
            register uint32_t  new_val   = 0;
            register uint32_t  old_val   = 0;
            size_t             key_index = 0;
            size_t             shift     = 1;
            size_t             i         = 0;

            for (i = 0; i < count; i++) {
                old_val = *(dword + i);

                if (encrypt_mode_ == FILE_ENCRYPT) {
                    new_val = old_val ^ key;
                    key ^= new_val;
                    new_val = ROLL_BITS_RIGHT(new_val, shift);
                } else if (encrypt_mode_ == FILE_DECRYPT) {
                    old_val = ROLL_BITS_LEFT(old_val, shift);
                    new_val = old_val ^ key;
                    key ^= old_val;
                }

                /* mix key with fixed keys */
                key ^= FIXED_KEYS[key_index];

                if (++key_index >= FIXED_KEY_COUNT) {
                    key_index = 0;
                }

                /* mix key with cipher */
                key ^= ciphers[cipher_no];

                if (++cipher_no >= ciphers_count) {
                    cipher_no = 0;
                }

                if (++shift >= 32) {
                    shift = 0;
                }

                *(dword + i) = new_val;
            }
        }

        File_write(target_file, buf, CAST(int, bytes_read));
        bytes_writ += bytes_read;
    } while (bytes_read > 0);

    /* close files and release memory */
    File_free(&target_file);
    File_free(&source_file);

    if (encrypt_mode_ != FILE_NO_ENCRYPT) {
        FREE(ciphers);
    }
    FREE(buf);
    RETURN(true);
} /* file_encrypt */


PUBLIC bool  file_write_bytes(                                             /*F*/
    chars_t       filename_,                                               /*-*/
    const size_t  start_byte_,                                             /*-*/
    const size_t  length_in_bytes_,                                        /*-*/
    const void*   data_ ) {                                                /*-*/
    GO                                                            (UID(FC16A9));
#if PLATFORM_LINUX
    UNUSED(filename_);
    UNUSED(start_byte_);
    UNUSED(length_in_bytes_);
    UNUSED(data_);

    IMPLEMENT_LINUX();  /* TODO: implement file_write_bytes() on Linux  */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    HANDLE_win  file = NULL;

    /* return if the output length is zero-length */
    if (length_in_bytes_ < 1) {
        RETURN(false);
    }

    {
        /* open the file: */
        const DWORD_win  open_mode = file_exists(filename_)
                                     ? OPEN_EXISTING_win : CREATE_NEW_win;
        file = CreateFile_win(
                   filename_,                  /* lpFileName            */
                   GENERIC_WRITE_win,          /* desired_access        */
                   FILE_SHARE_READ_win,        /* share_mode            */
                   NULL,                       /* lpSecurityAttributes  */
                   open_mode,                  /* dwCreationDisposition */
                   FILE_ATTRIBUTE_NORMAL_win,  /* dwFlagsAndAttributes  */
                   NULL);                      /* hTemplateFile         */

        if (file == INVALID_HANDLE_VALUE_win) {
            new_chars_t  msg = formatT(_T("CreateFile_win('%s')"), filename_);
            OS_WARN(msg, UID(E9EFC1));
            freeT(&msg);
            RETURN(false);
        }
    }

    {
        /* get the file size: */
        const DWORD_win  fsize = GetFileSize_win(file, NULL);

        if (fsize == INVALID_FILE_SIZE_win) {
            new_chars_t  msg = formatT(_T("GetFileSize_win('%s')")
                                       _T(" == INVALID_FILE_SIZE_win"),
                                       filename_);
            OS_WARN(msg, UID(EB5DB2));
            freeT(&msg);
            RETURN(false);
        }

        {
            /* lock the file to prevent other processes from writing to it: */
            const DWORD_win  begun  = GetTickCount_win();
            BOOL_win         locked = FALSE_win;

            /* attempt to acquire lock in 2 seconds */
            while (!locked && GetTickCount_win() < begun + 2000) {
                locked = LockFile_win(
                             file,                                   /* hFile */
                             CAST(DWORD_win, start_byte_),   /*dwFileOffsetLow*/
                             0,                           /* dwFileOffsetHigh */
                             fsize,                /* nNumberOfBytesToLockLow */
                             0);                  /* nNumberOfBytesToLockHigh */

                if (!locked) {
                    Sleep_win(250);
                }
            }

            if (!locked) {
                new_chars_t  msg = T_join(TT, _T("LockFile_win() filename_: "),
                                          filename_, TT);
                OS_WARN(msg, UID(E8A316));
                freeT(&msg);
                CloseHandle_win(file);
                RETURN(false);
            }
        }
    }

    /* move file pointer to the write position */
    if (INVALID_SET_FILE_POINTER_win == SetFilePointer_win(
            file,               /* file                 */
            start_byte_,        /* lDistanceToMove      */
            0,                  /* lpDistanceToMoveHigh */
            FILE_BEGIN_win)) {  /* dwMoveMethod         */

        new_chars_t  msg = T_join(TT, _T("SetFilePointer_win() filename_: "),
                                  filename_, TT);
        OS_WARN(msg, UID(E4B461));
        freeT(&msg);
        CloseHandle_win(file);
        RETURN(false);
    }

    {
        /* write to the file: */
        DWORD_win  bytes_writ = 0;
        if (!WriteFile_win(
                file,                               /* pFile                  */
                data_,                              /* lpBuffer               */
                CAST(DWORD_win, length_in_bytes_),  /* nNumberOfBytesToWrite  */
                &bytes_writ,                        /* lpNumberOfBytesWritten */
                NULL)) {                            /* lpOverlapped           */
            new_chars_t  msg = T_join(TT, _T("WriteFile_win() filename_: "),
                                      filename_, TT);
            OS_WARN(msg, UID(EE3AA0));
            freeT(&msg);
        }
    }

    /* close the opened file */
    if (!CloseHandle_win(file)) {
        new_chars_t  msg = T_join(TT, _T("CloseHandle_win() filename_: "),
                                  filename_, TT);
        OS_WARN(msg, UID(E0549B));
        freeT(&msg);
    }

#endif                                                      /* PLATFORM_WIN32 */

    RETURN(true);
} /* file_write_bytes */


PUBLIC bool  file_append_bytes(                                            /*F*/
    chars_t       filename_,                                               /*-*/
    const void*   bytes_,                                                  /*-*/
    const size_t  length_in_bytes_ ) {                                     /*-*/
    GO                                                            (UID(F5D39E));
    const size_t  start_byte =
        file_exists(filename_) ? file_size(filename_) : 0;

    const bool  ret = file_write_bytes(filename_, start_byte,
                                       length_in_bytes_, bytes_);
    RETURN(ret);
} /* file_append_bytes */


PUBLIC new_bytes_t  file_load_bytes( chars_t  filename_ ) {                /*F*/
    GO                                                            (UID(FB6405));
    bytes_t  ret  = { 0, NULL };
    FILE*    file = NULL;
    fpos_t   fsize;

    /* open (shared) file for reading in binary mode */
#if PLATFORM_WIN32
    file = FSOPEN_T(filename_, _T("rb"), _SH_DENYNO);
#endif
#if PLATFORM_LINUX
    file = fopen(filename_, "rb");
#endif

    if (file == NULL) {
        ERR(_T("FSOPEN_T() failed"), UID(ECB32E));
        RETURN(ret);
    }

    /* move to end of file */
    if (FSEEK(file, 0, SEEK_END) != 0) {
        ERR(_T("FSEEK(...SEEK_END) failed"), UID(EC0131));
        RETURN(ret);
    }

    /* determine file size by reading file-position indicator */
    if (FGETPOS(file, &fsize) != 0) {
        ERR(_T("FGETPOS() failed"), UID(EB60E4));
        RETURN(ret);
    }

    /* move to beginning of file */
    if (FSEEK(file, 0, SEEK_SET) != 0) {
        ERR(_T("FSEEK(...SEEK_SET) failed"), UID(EC0C84));
        RETURN(ret);
    }

    /* allocate memory */
#if PLATFORM_LINUX
    ret.size = CAST(size_t, fsize.__pos);
#endif
#if PLATFORM_WIN32
    ret.size = CAST(size_t, fsize);
#endif

    if (ret.size > 0) {
        ret.data = MALLOC(ret.size);
        if (ret.data == NULL) {
            ERR(_T("MALLOC() returned NULL"), UID(E282DD));
            ret.size = 0;
            RETURN(ret);
        }
    }

    /* read file into memory, in 512KB chunks */
    if (ret.size > 0) {
        size_t    chunk_size = KB(512);
        size_t    bytes_read = 0;
        uint8_t*  bytes      = ret.data;

        if (ret.size < chunk_size) {
            chunk_size = ret.size;
        }

        do {
            bytes_read = FREAD(bytes, 1, chunk_size, file);
            if (bytes_read != 0) {
                bytes += bytes_read;
            }
        } while (bytes_read == chunk_size);
    }

    /* close the file */
    if (FCLOSE(file) != 0) {
        file = NULL;
        ERR(_T("FCLOSE() failed"), UID(EC06F1));
    }
    RETURN(ret);
} /* file_load_bytes */


PUBLIC new_str_t  file_read_text(                                          /*F*/
    chars_t  filename_,                                                    /*-*/
    chars_t  alternate_paths_ ) {                                          /*-*/
    GO                                                            (UID(F47D5F));
    new_str_t  filename = file_locate(filename_, alternate_paths_);
    new_str_t  ret      = { NULL };

    if (emptyS(filename)) {
        ret = S_blank();

    } else {  /* read contents of file to a memory buffer */
        file_t        read_file = File_init(filename.cs);
        const size_t  fsize     = File_getFileSize(read_file);
        char*         buf       = MALLOC(fsize + 1);  /* +1 for \0 */
        CLEAR_N(buf, fsize + 1);
        {
            const size_t  bytes_read = File_read(read_file, buf, fsize);
            VERIFY(bytes_read == fsize, UID(EE99CF));

            if (is_wide_n(buf, bytes_read)) {
                ret = S_wchars(CAST(wchar_t*, buf));
            } else {
                ret = S_bchars(CAST(char*, buf));
            }
        }
        FREE(buf);
    }
    freeS(&filename);
    RETURN(ret);
} /* file_read_text */


#if 000
new_chars_t  file_read_text(                                               /*F*/
    chars_t  filename_,                                                    /*-*/
    chars_t  alternate_paths_ ) {                                          /*-*/
    GO                                                            (UID(F4A33C));
    new_chars_t  filename = file_locate(filename_, alternate_paths_);
    if (!IS_BLANK(filename)) {  /* read contents of file to a memory buffer */
        file_t  read_file (filename);
        char*   buf = new char[read_file.size + 1];  /* +1 for end \0 */
        CLEAR_N(buf, read_file.size + 1);
        {
            const size_t  bytes_read = read_file.read(buf, read_file.size);
            WARN_IF(bytes_read != read_file.size, UID(EECE64));
            str_t  ret;
            if (is_wide_n(buf, bytes_read)) {
                ret = CAST(wchar_t*, buf);
            } else {
                ret = CAST(char*, buf);
            }
        }
        delete[] buf;
        RETURN(ret);
    } else {
        RETURN(BLANK);
    }
    RETURN(NIL);
} /* file_read_text */
#endif                                                                 /* 000 */


#if 000
byte_array_t  file_t::loadBytes(                                           /*M*/
    chars_t  filename_,                                                    /*-*/
    chars_t  alternate_paths_ ) {                                          /*-*/
    GO                                                            (UID(FA04E7));
    str_t         filename = file_t::locate(filename_, alternate_paths_);
    byte_array_t  ret;

    if (!IS_BLANK(filename)) {
        file_t  read_file (filename);
        ret.set(read_file.size, 0);
        {
            const size_t  bytes_read =
                read_file.read(ret.getBuffer(), read_file.size);
            WARN_IF(bytes_read != read_file.size, UID(E09563));
        }
    }
    RETURN(ret);
} /* loadBytes */
#endif                                                                 /* 000 */

#if 000
byte_array_t  file_load_bytes2(                                            /*F*/
    chars_t  filename_,                                                    /*-*/
    chars_t  alternate_paths_ ) {                                          /*-*/
    GO                                                            (UID(FA6A39));
    byte_array_t  ret;
    CLEAR(ret);
    ret.mem           = NULL;
    ret.size          = 0;
    ret.pos           = 0;
    ret.is_compressed = false;
    ret.temp_chars    = NULL;

    str_t         filename = file_t::locate(filename_, alternate_paths_);
    byte_array_t  ret;

    if (!IS_BLANK(filename)) {
        file_t  read_file (filename);
        ret.set(read_file.size, 0);
        {
            const size_t  bytes_read =
                read_file.read(ret.getBuffer(), read_file.size);

            WARN_IF(bytes_read != read_file.size, UID(EC4A1D));
        }
    }
    RETURN(ret);
} /* file_load_bytes2 */
#endif                                                                 /* 000 */


#if 000
byte_array_t  file_load_bytes( chars_t  filename_ ) {                      /*F*/
    GO                                                            (UID(FDA322));
    const byte_array_t  ret = file_load_bytes2(filename_, NULL);
    RETURN(ret);
} /* file_load_bytes */
#endif                                                                 /* 000 */


/* return true if the specified file name exists.                             */
PUBLIC bool  file_exists( chars_t  filename_ ) {                           /*F*/
    GO                                                            (UID(F2E57E));
    const bool  ret = path_exists(filename_, false, true);
    RETURN(ret);
} /* file_exists */


PUBLIC bool  file_delete_4(                                                /*F*/
    chars_t     filename_,                                                 /*-*/
    const bool  ask_user_,                                                 /*-*/
    const bool  send_to_bin_,                                              /*-*/
    const bool  secure_delete_ ) {                                         /*-*/
    GO                                                            (UID(F60451));
#if PLATFORM_LINUX
    if (unlink(filename_) == 0) {
        RETURN(true);
    } else {
        RETURN(false);
    }

    UNUSED(ask_user_);
    UNUSED(send_to_bin_);
    UNUSED(secure_delete_);

    IMPLEMENT_LINUX();  /* TODO: implement file_delete_4() on Linux */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    _CHECK_HAS_NAME(filename_, RETURN(false); , UID(E7C758));

    if (!file_exists(filename_)) {
        RETURN(true);
    }

    if (secure_delete_) {
        const size_t  size  = file_size(filename_);
        char*         bytes = { 0 };

        file_write_bytes(filename_, 0, size, bytes);
    }

    if (ask_user_ || send_to_bin_) {
        /* copy filename_ to name because SHFileOperation_win() */
        /* requires the file name to end with \0\0              */
        char_t  name[MAX_PATH_win];
        MEMSET(name, 0x00, sizeof(name));
        STRCPY_S_T(name, sizeof(name), filename_);

        {
            SHFILEOPSTRUCT_win  fileop;
            CLEAR(fileop);
            fileop.wFunc  = FO_DELETE_win;
            fileop.pFrom  = name;
            fileop.fFlags = (send_to_bin_ ? FOF_ALLOWUNDO_win : 0) |
                            (ask_user_ ? 0
                             : FOF_NOCONFIRMATION_win |
                             FOF_NOERRORUI_win |
                             FOF_SILENT_win);

            if (0 != SHFileOperation_win(&fileop)) {
                new_chars_t  msg = T_join(TT, _T("SHFileOperation() failed.")
                                          _T(" filename_: "), filename_, TT);
                WARN(msg, UID(E4D407));
                freeT(&msg);
            }
        }
    } else if (!DeleteFile_win(filename_)) {
        new_chars_t  msg = formatT(_T("DeleteFile_win('%s')"), filename_);
        OS_WARN(msg, UID(E814AC));
        freeT(&msg);
    }

#endif                                                      /* PLATFORM_WIN32 */

    {
        /* return true if the file no longer exists: */
        const bool  ret = !file_exists(filename_);
        RETURN(ret);
    }
} /* file_delete_4 */


/* -------------------------------------------------------------------------- */
/* Methods: Path Information                                                  */


/* returns true if the specified path is a file or folder                     */
PUBLIC bool  path_exists(                                                  /*F*/
    chars_t     path_,                                                     /*-*/
    const bool  folder_,                                                   /*-*/
    const bool  file_ ) {                                                  /*-*/
    GO                                                            (UID(FABB52));
    bool         ret  = false;
    new_chars_t  path = T_chars(path_);

    trim_in_T(path);

#if PLATFORM_LINUX
    /* UNUSED(path_);   */
    /* UNUSED(folder_); */
    /* UNUSED(file_);   */

    IMPLEMENT_LINUX();  /* TODO: implement path_exists() on Linux */

    trim4_in_T(path, "/", false, true);

    if (!IS_BLANK(path)) {

        if (folder_) {
            new_chars_t  find_name = T_join(TT, path, "/*.*", TT);
            ret = (access(path, 0) == 0) ? true : false;
            freeT(&find_name);
        }

        if (!ret && file_) {
            ret = (access(path, 0) == 0) ? true : false;
        }
    }
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    trim4_in_T(path, _T("\\"), false, true);

    if (!IS_BLANK(path)) {
        /* prepare data structure */
        HANDLE_win           handle = NULL;
        WIN32_FIND_DATA_win  fdata;
        CLEAR(fdata);

        if (folder_) {
            new_chars_t  find_name = T_join(TT, path, _T("\\*.*"), TT);
            handle = FindFirstFile_win(find_name, &fdata);
            ret    = (handle != INVALID_HANDLE_VALUE_win);
            freeT(&find_name);
        }

        if (!ret && file_) {
            handle = FindFirstFile_win(path, &fdata);
            ret = (!(fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY_win) &&
                   !IS_BLANK(fdata.cFileName));
        }

        if (handle != INVALID_HANDLE_VALUE_win) {
            VERIFY(FindClose_win(handle), UID(ED1A9F));
        }
    }

#endif                                                      /* PLATFORM_WIN32 */

    freeT(&path);
    RETURN(ret);
} /* path_exists */


/* returns only the names of existing folders in the given path               */
PUBLIC new_str_t  path_existing( chars_t  path_ ) {                        /*F*/
    GO                                                            (UID(FCE1B1));
    new_str_t  ret = { NULL };

#if PLATFORM_LINUX
    UNUSED(path_);
    IMPLEMENT_LINUX();  /* TODO: implement path_existing() on Linux */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    chars_t      DELIMITER = _T("\\");
    size_t       i         = 0;
    size_t       count     = 0;
    new_chars_t  chars     = NULL;
    new_chars_t  source    = T_chars(path_);

    trim_in_T(source);
    trim4_in_T(source, _T("\\"), false, true);

    count = token_countT(source, DELIMITER);

    for (i = 0; i < count; i++) {
        new_chars_t  part = T_get_token(source, i, DELIMITER);

        if (i == 0 && (STRSTR_T(part, _T(":")) ||
                       STRSTR_T(part, _T("\\\\")))) {

            freeT(&chars);
            chars = T_chars(part);
            upper_in_T(chars);
            STRCAT_S_T(chars, MAX_PATH_win, DELIMITER);
        } else {
            WIN32_FIND_DATA_win  fdata;
            HANDLE_win           handle = NULL;

            new_chars_t  find_name = T_chars(chars);
            STRCAT_S_T(chars, MAX_PATH_win, _T("*.*"));

            CLEAR(fdata);
            handle = FindFirstFile_win(find_name, &fdata);

            if (handle != INVALID_HANDLE_VALUE_win) {
                bool  exit = false;
                do {
                    const BOOL_win  is_found = FindNextFile_win(handle, &fdata);
                    if (!is_found) {
                        DWORD_win  last_err = GetLastError_win();

                        if (last_err != ERROR_NO_MORE_FILES_win) {
                            new_chars_t  err_src =
                                formatT(_T("path_existing('%s')"), path_);
                            OS_ERR(err_src, UID(E13C04));
                            freeT(&err_src);
                        }
                        exit = true;
                    }

                    {
                        new_chars_t  name = T_chars(fdata.cFileName);

                        if ((fdata.dwFileAttributes &
                             FILE_ATTRIBUTE_DIRECTORY_win) &&
                            !(equals2T(name, _T(".")) ||
                              equals2T(name, _T(".."))) &&
                            likeT(part, name)) {

                            STRCAT_S_T(chars, MAX_PATH_win, name);
                            STRCAT_S_T(chars, MAX_PATH_win, DELIMITER);
                            break;
                        }
                        freeT(&name);
                    }
                } while (!exit);
                VERIFY(FindClose_win(handle), UID(EE53A8));
            }
            freeT(&find_name);
        }
        freeT(&part);
    }

    trim4_in_T(chars, _T("\\"), false, true);
    ret = S_newT(chars);

    freeT(&source);
    freeT(&chars);
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* path_existing */


PUBLIC new_str_t  path_extract(                                            /*F*/
    chars_t     path_or_file_,                                             /*-*/
    const bool  root_only_ ) {                                             /*-*/
    GO                                                            (UID(F08AAA));
    new_str_t  ret = { NULL };

#if PLATFORM_LINUX
    UNUSED(path_or_file_);
    UNUSED(root_only_);
    IMPLEMENT_LINUX();  /* TODO: implement path_extract() on Linux */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    char_t       ch    = '\0';
    size_t       count = 0;
    new_chars_t  arg   = T_chars(path_or_file_);

    /* get the position of the last slash / backslash */
    /* or ':' character in the string                 */
    size_t  last = SIZE_MAX;
    {
        size_t        i   = 0;
        const size_t  len = STRLEN_T(arg);

        for (i = 0; i < len; i++) {
            ch = arg[CAST(int, i)];
            if (ch == '\\' || ch == ':' || ch == '/') {
                last = i;
                if (root_only_) {
                    if (ch == ':') {
                        break;
                    }
                    count++;
                    /* 4 backslashes in UNC path = "\\server\share\" */
                    if (count >= 4) {
                        break;
                    }
                }
            }
        }
    }

    {
        /* extract the path, or return a blank string */
        /* if no slash / backslash or ':' was found   */

        const size_t  len_max = STRLEN_T(arg);
        new_chars_t   chars   = mallocT(len_max);

        if (last != UINT_MAX) {
            if (root_only_ && count < 4) {
                STRCAT_S_T(chars, len_max, arg);
            } else {
                STRNCAT_S_T(chars, len_max, arg, CAST(int, last) + 1);
            }

            /* if necessary, append trailing backslash */
            ch = chars[STRLEN_T(chars) - 1];

            if (ch != '\\' && ch != '/') {
                STRCAT_S_T(chars, len_max, _T("\\"));
            }
        }
        freeT(&arg);
        trim_in_T(chars);
        ret = S_newT(chars);
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* path_extract */


PUBLIC new_str_t  get_path( chars_t  path_or_file_ ) {                     /*F*/
    GO                                                            (UID(F5D0BD));
    const new_str_t  ret = path_extract(path_or_file_, false);
    RETURN(ret);
} /* get_path */


PUBLIC new_str_t  path_root( chars_t  path_or_file_ ) {                    /*F*/
    GO                                                            (UID(F66421));
    const new_str_t  ret = path_extract(path_or_file_, true);
    RETURN(ret);
} /* path_root */


PUBLIC new_str_t  folder_name( chars_t  path_ ) {                          /*F*/
    GO                                                            (UID(FA2435));
    new_chars_t   chars = T_chars(path_);
    const size_t  loc   = find_last_T(chars, _T("\\"));

    if (loc != NONE) {
        chars[loc] = '\0';
    }
    trim_in_T(chars);
    {
        const new_str_t  ret = S_newT(chars);
        RETURN(ret);
    }
} /* folder_name */


/* returns the free space on the specified path                               */
PUBLIC size_t  get_free_space( chars_t  path_ ) {                          /*F*/
    GO                                                            (UID(F8982C));
#if PLATFORM_LINUX
    UNUSED(path_);
    IMPLEMENT_LINUX();  /* TODO: implement get_free_space() on Linux */
    const size_t  ret = 0;
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    const file_size_t  get_free_space = get_free_space_large(path_);

    /* If the free space is more than 4 gigabytes, return 4      */
    /* gigabytes (because the maximum value of a 32-bit          */
    /* ULONG_win is 4,294,967,295 i.e. 4 gigabytes. In this case */
    /* a simple cast from a 64-bit to a 32-bit value would be    */
    /* wrong! Note that in Win32 DWORD_win, UINT_win, ULONG_win  */
    /* and size_t are all the same 32-bit unsigned integers)     */
    const size_t  ret = (get_free_space >= UINT_MAX)
                        ? UINT_MAX : CAST(size_t, get_free_space);
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* get_free_space */


/* returns the free space on the specified path (large)                       */
PUBLIC file_size_t  get_free_space_large( chars_t  path_ ) {               /*F*/
    GO                                                            (UID(F7C289));
    /* path_ can be the name of an existing drive or folder. */
    /* You can even use a file name, provided it             */
    /* contains the drive name/folder                        */

#if PLATFORM_LINUX
    UNUSED(path_);
    IMPLEMENT_LINUX();  /* TODO: implement get_free_space_large() on Linux */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    /* first determine if GetDiskFreeSpaceEx() is available */
    bool  extended_version = false;
    {
        /* get handle to kernel                                     */
        /* (no need to use LoadLibrary() - kernel is always loaded) */
        const HMODULE_win  kernel = GetModuleHandle_win(_T("kernel32.dll"));
        VERIFY(kernel != NULL, UID(ECC9D0));
        {
            /* use GetProcAddress(), just to see if it returns a valid ptr. */
            /* get real name of the function in the kernel,                 */
            /* depending on presence of Unicode                             */
#if defined UNICODE || defined _UNICODE
            const FARPROC_win  fn =
                GetProcAddress_win(kernel, "GetDiskFreeSpaceExW");
#else
            const FARPROC_win  fn =
                GetProcAddress_win(kernel, "GetDiskFreeSpaceExA");
#endif
            extended_version = (fn != NULL);
        }
    }

    /* use GetDiskFreeSpaceEx_win()            */
    /* to return the free space (if available) */
    if (extended_version) {
        /* build a GetDiskFreeSpaceEx-friendly path */
        /* (removes file name if present)           */
        new_str_t  dir_name = get_path(path_);

        ULARGE_INTEGER_win  free_bytes       = { 0, 0 };
        ULARGE_INTEGER_win  disk_size        = { 0, 0 };
        ULARGE_INTEGER_win  total_free_bytes = { 0, 0 };

        const BOOL_win  result = GetDiskFreeSpaceEx_win(dir_name.cs,
                                 &free_bytes, &disk_size, &total_free_bytes);
        freeS(&dir_name);
        if (result) {
            const file_size_t  ret = free_bytes.QuadPart;
            RETURN(ret);
        }
    }

    {
        /* if GetDiskFreeSpaceEx() is not available, use GetDiskFreeSpace() */
        new_str_t       root_path           = path_root(path_);
        DWORD_win       sectors_per_cluster = 0;
        DWORD_win       bytes_per_sector    = 0;
        DWORD_win       free_clusters       = 0;
        DWORD_win       clusters            = 0;
        const BOOL_win  result = GetDiskFreeSpace_win(
                                     root_path.cs,
                                     &sectors_per_cluster, &bytes_per_sector,
                                     &free_clusters, &clusters);
        if (result) {                      /* calculate and return free space */
            const file_size_t  free_space =
                free_clusters * sectors_per_cluster * bytes_per_sector;
            RETURN(free_space);
        }
        freeS(&root_path);
    }
#endif                                                      /* PLATFORM_WIN32 */

    /* if it gets to this line, it is probably because some non-existent */
    /* drive or folder name was specified                                */
    RETURN(0);
} /* get_free_space_large */


PUBLIC new_str_t  paths_format( chars_t  paths_ ) {                        /*F*/
    GO                                                            (UID(FFDABD));
    new_str_t  ret = { NULL };

#if PLATFORM_LINUX
    UNUSED(paths_);
    IMPLEMENT_LINUX();  /* TODO: implement paths_format() on Linux */
#endif                                                      /* PLATFORM_LINUX */


#if PLATFORM_WIN32
    chars_t    DELIMITER = _T("|");
    new_str_t  paths     = S_chars(paths_);
    char_t*    wr        = CAST(char_t*, paths.cs);
    size_t     i         = 0;

    {
        /* replace 'CR', 'LF', '<', '>', ',' and " in the path with '|' */
        const size_t  paths_len = lengthS(paths);
        for (i = 0; i < paths_len; i++) {
            *wr = paths.cs[i];
            if (*wr == '\r' || *wr == '\n' || *wr == '<' ||
                *wr == '>'  || *wr == '"'  || *wr == ',') {
                *wr = DELIMITER[0];
            }
        }
    }
    trimIn1S(&paths);
    trimInS(&paths, _T("|"), TRIM_ALL);

    {
        const size_t  count = tokenCountS(paths, DELIMITER);
        for (i = 0; i < count; i++) {
            new_str_t  part = S_getToken(paths, i, DELIMITER);
            trimIn1S(&part);

            if (!emptyS(part)) {
                if (!emptyS(ret)) {
                    addTS(&ret, _T(" "));
                    addTS(&ret, DELIMITER);
                    addTS(&ret, _T(" "));
                }
                addTS(&ret, part.cs);
            }
            freeS(&part);
        }
    }
    freeS(&paths);
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* paths_format */

/* -------------------------------------------------------------------------- */

#if PLATFORM_LINUX

bool (*process_files_in_folder_callback_fn)(                               /*F*/
    chars_t  filename_,                                                    /*-*/
    size_t   file_size_ ) = NULL;                                          /*-*/

#if defined __GNUC__
#pragma GCC diagnostic push
#endif

#if defined __clang__
#pragma GCC diagnostic ignored "-Wvisibility"
#endif

static int  _nftw_callback_fn(                                             /*F*/
    const char*         path_,                                             /*-*/
    const struct stat*  sb_,                                               /*-*/
    int                 tflag_,                                            /*-*/
    struct FTW*         ftwbuf_ ) {                                        /*-*/
    /*
        printf("%-3s %2d %7jd   %-40s %d %s\n",
            (tflag_ == FTW_D)   ? "d"   : (tflag_ == FTW_DNR) ? "dnr" :
            (tflag_ == FTW_DP)  ? "dp"  : (tflag_ == FTW_F)   ? "f" :
            (tflag_ == FTW_NS)  ? "ns"  : (tflag_ == FTW_SL)  ? "sl" :
            (tflag_ == FTW_SLN) ? "sln" : "???",
            ftwbuf_->level,
            CAST(size_t, sb_->st_size),
            path_,
            ftwbuf_->base,
            path_ + ftwbuf_->base);
    */

    /* invoke callback function */
    const bool  exit = !(*process_files_in_folder_callback_fn)
                       (path_, CAST(size_t, sb_->st_size));

    UNUSED(tflag_);
    UNUSED(ftwbuf_);

    return exit ? 1 : 0;
} /* _nftw_callback_fn */
#endif                                                      /* PLATFORM_LINUX */

#if defined __GNUC__
#pragma GCC diagnostic pop
#endif


PUBLIC bool  process_files_in_folder(                                      /*F*/
    chars_t     path_,                                                     /*-*/
    const bool  scan_subfolders_,                                          /*-*/
    bool        (*callback_fn_)( chars_t  filename_,                       /*-*/
                                 size_t  file_size_ ) ) {                  /*-*/
    GO                                                            (UID(F690B7));
    bool  ret = false;

    /* create a path name that ends with \ or / */
    new_chars_t  path = T_chars(path_);

#if PLATFORM_LINUX
    UNUSED(path_);
    UNUSED(scan_subfolders_);
    UNUSED(callback_fn_);

    if (!ends2T(path, _T("/"))) {
        appendT(&path, _T("/"));
    }

    {
        int  result = 0;
        process_files_in_folder_callback_fn = callback_fn_;
        result = nftw(path,               /* searched path     */
                      _nftw_callback_fn,  /* callback function */
                      20,                 /* maximum open FDs  */
                      0);                 /* flags             */
        process_files_in_folder_callback_fn = NULL;
        ret = (result == -1) ? false : true;
    }
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    if (!ends2T(path, _T("\\"))) {
        appendT(&path, _T("\\"));
    }

    {
        WIN32_FIND_DATA_win  fdata;
        new_chars_t          find_file  = T_join(TT, path, _T("*.*"), TT);
        /*m*/ HANDLE_win     handle     = FindFirstFile_win(find_file, &fdata);
        BOOL_win             found_file = FALSE_win;
        freeT(&find_file);

        found_file = (handle != INVALID_HANDLE_VALUE_win);
        while (found_file) {

            /* skip special file names . and .. */
            if (equals2T(fdata.cFileName, _T(".")) ||
                equals2T(fdata.cFileName, _T(".."))) {
                goto _next_file;
            }

            /* skip subfolders */
            if (fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY_win) {
                goto _next_file;
            }

            {
                /* call the callback function */
                new_chars_t  filename = T_join(TT, path, fdata.cFileName, TT);
                const bool   exit =
                    !(*callback_fn_)(filename, fdata.nFileSizeLow);
                freeT(&filename);
                if (exit) {
                    break;
                }
            }
_next_file:
            found_file = FindNextFile_win(handle, &fdata);
        }

        if (handle != INVALID_HANDLE_VALUE_win) {
            FindClose_win(handle);
        }

        /* iterate through subfolders */
        if (scan_subfolders_) {
            find_file = T_join(TT, path, _T("*.*"), TT);
            handle    = FindFirstFile_win(find_file, &fdata);
            freeT(&find_file);
            found_file = (handle != INVALID_HANDLE_VALUE_win);

            while (found_file) {
                if (fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY_win) {
                    /* skip special file names '.' and '..' */
                    new_chars_t  filename = T_chars(fdata.cFileName);
                    if (!equals2T(filename, _T(".")) &&
                        !equals2T(filename, _T(".."))) {

                        new_chars_t  sub_path = T_join(TT, path, filename, TT);
                        T_join(TT, path, filename, TT);
                        process_files_in_folder(
                            sub_path, scan_subfolders_, callback_fn_);
                        freeT(&sub_path);
                    }
                }
                found_file = FindNextFile_win(handle, &fdata);
            };
        }

        if (handle != INVALID_HANDLE_VALUE_win) {
            FindClose_win(handle);
        }

        ret = C_BOOL(handle != INVALID_HANDLE_VALUE_win);
    }
#endif                                                      /* PLATFORM_WIN32 */

    freeT(&path);
    RETURN(ret);
} /* process_files_in_folder */


PUBLIC bool  file_append_text(                                             /*F*/
    chars_t  filename_,                                                    /*-*/
    chars_t  text_ ) {                                                     /*-*/
    GO                                                            (UID(FDB4A6));
    bool  ret = false;

#if PLATFORM_LINUX
    const int  file = open(filename_, O_CREAT | O_RDWR | O_APPEND);
    if (file == -1) {
        const char*  err = strerror(errno);
        ret = false;

    } else if (write(file, text_, strlen(text_)) < 0) {
        const char*  err = strerror(errno);
        ret = false;
    } else {
        ret = true;
    }
    close(file);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    File_TextModeEnum  mode     = FILE_TEXT_ANSI;
    size_t             len      = 0;
    void*              bytes    = NULL;
    bool               is_alloc = false;

    if (IS_BLANK(text_)) {
        RETURN(false);
    }

    len = STRLEN_T(text_);

    if (mode == FILE_TEXT_ANSI && is_unicode_mode()) {
        bytes = utf8_of_wide(CAST(const wchar_t*, text_));
        len *= sizeof(char);
        is_alloc = true;

    } else if (mode == FILE_TEXT_WIDE && !is_unicode_mode()) {
        bytes = wide_of_utf8(CAST(const char*, text_));
        len *= sizeof(wchar_t);
        is_alloc = true;

    } else {
        bytes = CAST(void*, text_);
        len *= sizeof(char_t);
        is_alloc = false;
    }

    {
        /* 2015-04-15 TODO: If a path not supplied in the filename,         */
        /* the file should be created in the folder of the running process. */
        /* Right now this is not guaranteed.                                */
        const size_t  start_byte = file_exists(filename_)
                                   ? file_size(filename_) : 0;

        ret = file_write_bytes(filename_, start_byte, len, bytes);

        if (is_alloc) {
            FREE(bytes);
        }
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* file_append_text */


PUBLIC bool  file_append_text_n(                                           /*F*/
    chars_t  filename_,                                                    /*-*/
    chars_t  terminator_,                                                  /*-*/
    ... ) {                                                                /*-*/
    GO                                                            (UID(F4C67A));
    /* Append a number of text strings to the file specified by filename_. */
    /* If the file does not exist already, it will be created.             */
    /* terminator_: the string (or NULL) that terminates the sequence.     */
    /* For example:                                                        */
    /* file_append_text_n(_T("tes.txt"), NULL, "ABC", "123", NULL);     */

    bool  ret  = true;
    bool  exit = false;

    va_list  args_ptr;
    va_start(args_ptr, terminator_);

    do {
        chars_t  text = va_arg(args_ptr, chars_t);

        if ((text == NULL && terminator_ == NULL) ||
            equals2T(text, terminator_)) {
            exit = true;

        } else if (!IS_BLANK(text)) {
            const bool  result = file_append_text(filename_, text);
            if (!result) {
                ret  = false;
                exit = true;
            }
        }
    } while (!exit);

    va_end(args_ptr);

    RETURN(ret);
} /* file_append_text_n */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
