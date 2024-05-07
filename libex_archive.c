/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                     [libex_archive.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_archive_.h"
#if defined INCLUDED_LIBEX_ARCHIVE_H

#include <limits.h>
#include <string.h>  /* for memset() */

#include "libex_config_.h"

#include "libex_.h"
#include "libex_array_.h"
#include "libex_bytes_.h"
#include "libex_call_.h"
#include "libex_const_.h"
#include "libex_debug_.h"
#include "libex_error_.h"
#include "libex_file_.h"
#include "libex_hash_.h"
#include "libex_macro_.h"
#include "libex_string_class_.h"
#include "libex_stringc_.h"
#include "libex_type_.h"

#if PLATFORM_WIN32
#include "libex_win32_.h"
#endif

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#if defined _MSC_VER
#pragma warning (disable:4710)  /* W:L4 function not inlined */
#endif

#define _REPORTING  1

/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


static const uint32_t  MAX_NAME_LEN = 1024U;


typedef struct  _archive_t {
    array_t      items;                                         /* _archive_t */
    uint8_t*     storage;                                       /* _archive_t */
    uint32_t     storage_size;                                  /* _archive_t */
    new_chars_t  report_text;                                   /* _archive_t */
    uint32_t     report_size;                                   /* _archive_t */
}
_archive_t;


/* -------------------------------------------------------------------------- */
/* Functions: Private                                                         */


#if defined __GNUC__ && !defined __MINGW32__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#endif


#define _BASE_OBJ_WRAP_INC
#define _OBJ_HANDLE_TYPE   archive_t
#define _OBJ_INNER_TYPE    _archive_t
#define _OBJ_ALLOC_FN_UID  UID(FE7E99)
#define _OBJ_FREE_FN_UID   UID(F3669E)
#define _OBJ_CONST_FN_UID  UID(FBAFBE)
#define _OBJ_FN_UID        UID(FA6DFE)
#define _OBJ_WRAP_FN_UID   UID(F39B5B)
#include "libex_object_wrapper.inc.c"


static uint8_t*  _malloc( const size_t  size_in_bytes_ ) {                 /*F*/
    GO                                                            (UID(F4C0FA));
    /* sizeof(char_t) is added to accommodate        */
    /* terminating \0 added at the end of text files */

    const size_t  bytes_size = size_in_bytes_ + sizeof(char_t);
    uint8_t*      ret        = CAST(uint8_t*, MALLOC(bytes_size));

    if (ret != NULL) {
        MEMSET(ret, 0x00, bytes_size);
    }
    RETURN(ret);
} /* _malloc */


static bool  _xor_encrypt_or_decrypt(                                      /*F*/
    uint8_t*        data_,                                                 /*-*/
    const uint32_t  data_size_,                                            /*-*/
    const uint8_t*  encryption_key_,                                       /*-*/
    const uint32_t  key_size_ ) {                                          /*-*/
    GO                                                            (UID(F45EE8));
    if (data_ == NULL) {
        WARN(_T("data_ == NULL"), UID(ECF4B5));
        RETURN(false);
    }

    if (data_size_ == 0) {
        WARN(_T("data_size_ == 0"), UID(EF099E));
        RETURN(false);
    }

    if (encryption_key_ == NULL) {
        WARN(_T("encryption_key_ == NULL"), UID(EBDA6F));
        RETURN(false);
    }

    if (key_size_ == 0) {
        WARN(_T("key_size_ == 0"), UID(E6BD7D));
        RETURN(false);
    }

#define _HASH_COUNT  64

    {
        /* create a long encryption key: */
        uint32_t   i = 0;
        hash_t  hashes[_HASH_COUNT];
        hash_t  hash = hash_of_bytes(encryption_key_, key_size_);
        hash = hash_of_hash(&hash);

        for (i = 0; i < _HASH_COUNT; i++) {
            /* mutate the hash */
            hash.hash_bytes[00] ^= 128;
            hash.hash_bytes[12] ^= CAST(uint8_t, i);
            hash.hash_bytes[16] ^= encryption_key_[0];
            hash.hash_bytes[63] ^= 255;

            hash = hash_of_hash(&hash);  /* make hash from permutated hash */
            hashes[i] = hash;  /* store the new hash to the array of hashes */
        }

        {
            const uint32_t  hash_len = sizeof(hashes[0].hash_bytes);
            uint8_t         key_byte = 0;
            uint32_t        key      = 0;
            uint32_t        hash_no  = 0;
            uint8_t*        data     = NULL;

            for (data = data_; data < data_ + data_size_; data++) {
                key_byte = hashes[hash_no].hash_bytes[key];
                key++;

                if (key >= hash_len) {
                    key = 0;
                    hash_no++;
                    if (hash_no >= _HASH_COUNT) {
                        hash_no = 0;
                    }
                }

                *data = CAST(uint8_t, CAST(uint32_t, key_byte)
                             ^ CAST(uint32_t, *data));
            }
        }
    }
#undef _HASH_COUNT

    RETURN(true);
} /* _xor_encrypt_or_decrypt */


static uint32_t  _read_uint( const uint8_t*  bytes_ ) {                    /*F*/
    GO                                                            (UID(FEA1B3));
    uint32_t  ret = 0;
    MEMCPY(&ret, bytes_, sizeof(uint32_t));
    RETURN(ret);
} /* _read_uint */


static void  _report_header(                                               /*F*/
    _archive_t*  me_,                                                      /*-*/
    chars_t      func_name_ ) {                                            /*-*/
    GO                                                            (UID(F7E939));
    new_chars_t  dashes = repeat2T(_T("-"), 70);
    new_chars_t  line   =
        T_join(TT,
               _T("\r\n") _T(" "), dashes,
               _T("\r\n") _T(" "), func_name_,
               _T("\r\n") _T(" | Serial# | Size in Bytes | Name"), TT);
    set_inT(&me_->report_text, line);
    me_->report_size = 0;
    freeT(&dashes);
    freeT(&line);
    RETURN(NIL);
} /* _report_header */


static void  _report_item(                                                 /*F*/
    _archive_t*     me_,                                                   /*-*/
    const uint32_t  item_size_,                                            /*-*/
    chars_t         item_name_ ) {                                         /*-*/
    GO                                                            (UID(FE9DED));
    const int     item_count  = Array_count(me_->items);
    const int     item_size   = CAST(int, item_size_);
    new_chars_t   report_line =
        formatT(_T("%s") _T("\r\n") _T(" | %7d | %13d | %s"),
                me_->report_text, item_count, item_size, item_name_);
    me_->report_size += item_size_;
    set_inT(&me_->report_text, report_line);
    freeT(&report_line);
    RETURN(NIL);
} /* _report_item */


static void  _report_summary( _archive_t*  me_ ) {                         /*F*/
    GO                                                            (UID(F86FEF));
    const uint32_t  item_count  = Array_count(me_->items);
    new_chars_t     report_line =
        formatT(_T("%s") _T("\r\n") _T(" | %7d | %13d | %s"),
                me_->report_text, item_count, me_->report_size,
                _T("TOTAL"));
    set_inT(&me_->report_text, report_line);
    freeT(&report_line);
    RETURN(NIL);
} /* _report_summary() */


static void  _write_uint(                                                  /*F*/
    uint8_t**       bytes_,                                                /*-*/
    const uint32_t  value_ ) {                                             /*-*/
    GO                                                            (UID(F930E7));
    MEMCPY(*bytes_, &value_, sizeof(uint32_t));
    *bytes_ += sizeof(uint32_t);
    RETURN(NIL);
} /* _write_uint */


#if defined __GNUC__
#pragma GCC diagnostic pop
#endif


/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */


PUBLIC new_archive_t  Archive_init( void ) {                               /*C*/
    GO                                                            (UID(F253CC));
    _archive_t*    ob  = _object_alloc();
    new_archive_t  ret = _object_wrap(ob);

    ob->items        = Array_init(sizeof(archive_item_t), 10, 0);
    ob->storage      = NULL;
    ob->storage_size = 0;
    ob->report_text  = NULL;
    ob->report_size  = 0;
    RETURN(ret);
} /* Archive_init */


PUBLIC new_archive_t  Archive_initBytes(                                   /*C*/
    uint8_t*     storage_bytes_,                                           /*-*/
    const char*  encryption_key_ ) {                                       /*-*/
    GO                                                            (UID(FC3309));
    new_archive_t   ret      = Archive_init();
    const uint32_t  key_size = STRLEN(encryption_key_);

    Archive_loadFromBytes(&ret, storage_bytes_,
                          key_size, CAST(uint8_t*, encryption_key_));
    RETURN(ret);
} /* Archive_initBytes */


PUBLIC new_archive_t  Archive_initCopy( const archive_t  copy_from_ ) {    /*C*/
    GO                                                            (UID(F78887));
    new_archive_t  ret = Archive_init();
    Archive_setCopy(&ret, copy_from_);
    RETURN(ret);
} /* Archive_initCopy */


/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */


PUBLIC void  Archive_free( archive_t*  object_ ) {                         /*D*/
    GO                                                            (UID(F1CB65));
    _archive_t* const  me = _object(object_, UID(E8FA94));

    if (me->storage != NULL) {
        FREE(me->storage);
        me->storage = NULL;
    }

    me->storage_size = 0;

    if (me->report_text != NULL) {
        freeT(&me->report_text);
    }

    Archive_removeItems(object_);
    Array_free(&me->items);
    _object_free(object_);

    RETURN(NIL);
} /* Archive_free */


/* -------------------------------------------------------------------------- */
/* Methods: Const                                                             */


PUBLIC bool  Archive_equal(                                                /*M*/
    const archive_t  object_,                                              /*-*/
    const archive_t  compare_ ) {                                          /*-*/
    GO                                                            (UID(FE08DB));
    const _archive_t* const  me = _object_const(&object_, UID(E4D310));

    const _archive_t*  cmp        = _object_const(&compare_, UID(E3F47A));
    const uint32_t     item_count = Array_count(me->items);
    const uint32_t     cmp_count  = Array_count(cmp->items);
    uint32_t           i          = 0;

    if (item_count != cmp_count) {
        RETURN(false);
    }

    /* compare the size and contents of each item in the two archives */
    for (i = 0; i < item_count; i++) {
        const archive_item_t*  item1 =
            CAST(const archive_item_t*, Array_getItemAt(
                     &CAST(_archive_t*, me)->items, i));

        const archive_item_t*  item2 =
            CAST(const archive_item_t*, Array_getItemAt(
                     &CAST(_archive_t*, cmp)->items, i));

        if (item1->item_size != item2->item_size) {
            RETURN(false);

        } else if (MEMCMP(item1->item_data, item2->item_data,
                          item2->item_size) != 0) {
            RETURN(false);
        }
    }
    RETURN(true);
} /* Archive_equal */


PUBLIC archive_item_t  Archive_getItem(                                    /*M*/
    const archive_t  object_,                                              /*-*/
    chars_t          item_name_ ) {                                        /*-*/
    GO                                                            (UID(FA1382));
    const _archive_t* const  me = _object_const(&object_, UID(E655B2));

    uint32_t        i          = 0;
    const uint32_t  item_count = Array_count(me->items);
    new_chars_t     item_name  = T_first(item_name_, MAX_NAME_LEN);

    upper_in_T(item_name);
    replace_char_in_T(item_name, '\\', '/');

    for (i = 0; i < item_count; i++) {
        archive_item_t*  item =
            CAST(archive_item_t*, Array_getItemAt(
                     &CAST(_archive_t*, me)->items, i));

        if (likeT(item->item_name, item_name)) {
            freeT(&item_name);
            RETURN(*item);
        }
    }

    {
        new_chars_t  msg = formatT(_T("item '%s' not found in archive."),
                                   item_name_);
        WARN(msg, UID(E9F793));
        freeT(&msg);
    }

    freeT(&item_name);

    {
        const archive_item_t  ret = null_archive_item;
        RETURN(ret);
    }
} /* Archive_getItem */


PUBLIC const uint8_t*  Archive_getStorageBytes(                            /*M*/
    const archive_t  object_,                                              /*-*/
    const uint32_t   key_size_,                                            /*-*/
    const uint8_t*   encryption_key_ ) {                                   /*-*/
    GO                                                            (UID(FEB05A));
    _archive_t* const  me = _object(&object_, UID(EB679B));

    uint32_t        i          = 0;
    const uint32_t  item_count = Array_count(me->items);
    uint8_t*        wr         = NULL;

    /* calculate the uncompressed size of the image, in bytes */
    me->storage_size = 4 + sizeof(uint32_t) * 2;

    /* reserved for signature, size and count */
    for (i = 0; i < item_count; i++) {
        const archive_item_t*  item =
            CAST(const archive_item_t*, Array_getItemAt(&me->items, i));

        /* calculate item size, in bytes */
        const uint32_t  chars_len = lenT(item->item_name);
        const uint32_t  bytes_size =
            sizeof(uint32_t)              /* length of item's name        */
            + chars_len * sizeof(char_t)  /* item's name, without \0      */
            + sizeof(uint32_t)            /* size of item's data          */
            + item->item_size;            /* item's data length, in bytes */

        me->storage_size += bytes_size;
    }

    /* allocate fresh memory for the image */
    if (me->storage != NULL) {
        Archive_packMemory(CAST(archive_t*, &object_));
    }

    me->storage = _malloc(me->storage_size);
    MEMSET(me->storage, 0x00, me->storage_size);

    /* write data to allocated bytes: */
    wr = me->storage;
    MEMCPY(wr, "ARC1", 4);  /* write signature */
    wr += 4;
    _write_uint(&wr, me->storage_size);  /* write archive size */
    _write_uint(&wr, item_count);        /* write item count   */

    /* write all item names and data */
    for (i = 0; i < item_count; i++) {
        const archive_item_t*  item =
            CAST(const archive_item_t*, Array_getItemAt(&me->items, i));

        {
            /* write item's name: */
            new_bchars_t    utf8       = to_utf8T(item->item_name);
            const uint32_t  bytes_size = STRLEN(utf8) + 1;

            set_replace_char(utf8, '\\', '/');

            MEMCPY(wr, utf8, bytes_size);
            freeA(&utf8);
            wr += bytes_size;
        }

        /* write item's data size in bytes, followed by the data */
        _write_uint(&wr, item->item_size);
        MEMCPY(wr, item->item_data, item->item_size);
        wr += item->item_size;
    }

    me->storage_size = bytes_compress(me->storage, me->storage_size);

    /* encrypt the data in-situ */
    _xor_encrypt_or_decrypt(me->storage, me->storage_size, encryption_key_,
                            key_size_);
    {
        const uint8_t*  ret = me->storage;
        RETURN(ret);
    }
} /* Archive_getStorageBytes */


PUBLIC uint32_t  Archive_getStorageSize( const archive_t  object_ ) {      /*M*/
    GO                                                            (UID(FB4FBA));
    const _archive_t* const  me = _object_const(&object_, UID(E7B37E));
    RETURN(me->storage_size);
} /* Archive_getStorageSize */


PUBLIC new_str_t  Archive_getText(                                         /*M*/
    const archive_t  object_,                                              /*-*/
    chars_t          item_name_ ) {                                        /*-*/
    GO                                                            (UID(F9D333));
    new_str_t       ret  = { NULL };
    archive_item_t  item = Archive_getItem(object_, item_name_);
    uint8_t*        data = item.item_data;
    const uint32_t  size = item.item_size;

    if (!Archive_itemExists(object_, item_name_)) {
        new_chars_t  msg = formatT(_T("item '%s' not found in archive."),
                                   item_name_);
        WARN(msg, UID(EEE2AB));
        freeT(&msg);
    }

    /* check for byte-order-mark (BOM), and use UTF-8 decoding */
    if (size >= 3 &&
        *data == 0xEF &&
        *(data + 1) == 0xBB &&
        *(data + 2) == 0xBF) {  /* UTF-8 */

        new_wchars_t  new_wide = wide_of_utf8(CAST(const char*, data));

        if (*new_wide == 0xFEFF || *new_wide == 0xFFFE) {
            ret = S_wchars(new_wide + 1);
        } else {
            ret = S_wchars(new_wide);
        }

        FREE(new_wide);

        /* if a byte-order-mark (BOM) indicates UTF-16, */
        /* issue a warning and return a blank string */
    } else if (size >= 2 &&
               ((*data == 0xFE && *(data + 1) == 0xFF)
                /* <- UTF16 big-endian */ ||
                (*data == 0xFF && *(data + 1) == 0xFE)))
        /* <- UTF16 little-endian */
    {
        DEBUG_WARN(_T("Archive_getText('") + str_t(item_name_)
                   + _T("'): Contains UTF16 byte-order-mark.")
                   _T(" UTF16 can't be handled."), UID(E5F118));
    } else if (is_wide_n(data, size)) {
        ret = S_wchars(CAST(wchar_t*, data));
    } else {
        ret = S_bchars(CAST(char*, data));
    }

    firstInS(&ret, size);
    RETURN(ret);
} /* Archive_getText */


PUBLIC bool  Archive_itemExists(                                           /*M*/
    const archive_t  object_,                                              /*-*/
    chars_t          item_name_ ) {                                        /*-*/
    GO                                                            (UID(FE36EC));
    const _archive_t* const  me = _object_const(&object_, UID(E1142B));
    bool  ret = false;

    if (me != NULL) {
        new_chars_t     item_name  = T_first(item_name_, MAX_NAME_LEN);
        const uint32_t  item_count = Array_count(me->items);
        uint32_t        i          = 0;

        replace_char_in_T(item_name, '\\', '/');

        for (i = 0; i < item_count; i++) {
            const archive_item_t*  item =
                CAST(const archive_item_t*, Array_getItemAt(
                         &CAST(_archive_t*, me)->items, i));

            if (likeT(item->item_name, item_name)) {
                ret = true;
                break;
            }
        }

        freeT(&item_name);
    }
    RETURN(ret);
} /* Archive_itemExists */


PUBLIC chars_t  Archive_report( const archive_t  object_ ) {               /*M*/
    GO                                                            (UID(FC80D2));
    const _archive_t* const  me = _object_const(&object_, UID(E30598));
    chars_t  ret = BLANK;

    if (me != NULL) {
        ret  = me->report_text;
    }
    RETURN(ret);
} /* Archive_report */


/* -------------------------------------------------------------------------- */
/* Methods: Manipulative                                                      */


PUBLIC bool  Archive_addFolder(                                            /*M*/
    archive_t*  object_,                                                   /*-*/
    chars_t     path_,                                                     /*-*/
    chars_t     pattern_,                                                  /*-*/
    chars_t     relative_path_ ) {                                         /*-*/
    GO                                                            (UID(F355EC));
    _archive_t* const  me = _object(object_, UID(E04CA7));

    new_chars_t  path       = NULL;
    new_chars_t  rel_path   = NULL;
    bool         found_file = false;

#if PLATFORM_WIN32
    HANDLE_win           handle = NULL;
    WIN32_FIND_DATA_win  fdata;
#endif                                                      /* PLATFORM_WIN32 */

#if _REPORTING > 0

    if (IS_BLANK(relative_path_)) {
        new_chars_t  fn_name =
            formatT(_T("\r\n") _T(" Archive_addFolder('%s', '%s')"),
                    path_, pattern_);
        _report_header(me, fn_name);
        freeT(&fn_name);
    }

#endif                                                      /* _REPORTING > 0 */

    /* create a path name that ends with \ or / */
    path = T_chars(path_);

    if (!ends2T(path, _T("\\")) && !ends2T(path, _T("//"))) {
        appendT(&path, _T("\\"));
    }

    /* create a relative path name that ends with \ or / */
    rel_path = T_chars(relative_path_);

    if (!IS_BLANK(rel_path) && !ends2T(rel_path, _T("\\")) &&
        !ends2T(rel_path, _T("//"))) {
        appendT(&rel_path, _T("\\"));
    }

    /* TODO: abstract this block. */
#if PLATFORM_WIN32
    {
        new_chars_t  find_file = T_join(TT, path, pattern_, TT);
        handle = FindFirstFile_win(find_file, &fdata);
        freeT(&find_file);
    }
    found_file = (handle != INVALID_HANDLE_VALUE_win);
#endif                                                      /* PLATFORM_WIN32 */

    while (found_file) {
        new_chars_t  filename  = NULL;
        uint32_t     fsize     = 0;

        /* skip special file names . and .. */
#if PLATFORM_WIN32
        filename = T_chars(fdata.cFileName);
        fsize    = fdata.nFileSizeLow;
#endif

        if (equals2T(filename, _T(".")) || equals2T(filename, _T(".."))) {
            ;    /* skip special folders */


            /* skip subfolders */   /* TODO: abstract this. */
#if PLATFORM_WIN32

            if (fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY_win) {
                ;    /* skip folders */
            }

#endif                                                      /* PLATFORM_WIN32 */
        } else {
            new_chars_t  path_filename     = T_join(TT, path, filename, TT);
            new_chars_t  rel_path_filename = T_join(TT, rel_path, filename, TT);

            archive_item_t*  item =
                CAST(archive_item_t*, Archive_addItem(
                         object_, rel_path_filename, fsize, NULL));

            file_t  file = File_init(path_filename);
            File_read(file, item->item_data, item->item_size);

            File_close(file);
            File_free(&file);
            freeT(&path_filename);
            freeT(&rel_path_filename);

#if _REPORTING > 0
            _report_item(me, item->item_size, item->item_name);
#endif
        }

#if PLATFORM_WIN32  /* TODO: abstract */
        found_file = (FALSE_win != FindNextFile_win(handle, &fdata));
#endif

        freeT(&filename);
    } /* while */

#if PLATFORM_WIN32  /* TODO: abstract */
    if (handle != INVALID_HANDLE_VALUE_win) {
        FindClose_win(handle);
    }
#endif                                                      /* PLATFORM_WIN32 */


    {
        /* iterate through subfolders: */
        new_chars_t  find_file = T_join(TT, path, _T("*.*"), TT);

#if PLATFORM_WIN32  /* TODO: abstract */
        handle = FindFirstFile_win(find_file, &fdata);
#endif
        freeT(&find_file);
    }

#if PLATFORM_WIN32  /* TODO: abstract */
    found_file = (handle != INVALID_HANDLE_VALUE_win);
#endif

    while (found_file) {
        bool  is_folder = false;
#if PLATFORM_WIN32  /* TODO: abstract */
        is_folder = (fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY_win);
#endif

        /* TODO: abstract */
        if (is_folder) {
            new_chars_t  filename = NULL;

            /* skip special file names . and .. */
#if PLATFORM_WIN32  /* TODO: abstract */
            filename = T_chars(fdata.cFileName);
#endif

            if (!equals2T(filename, _T(".")) &&
                !equals2T(filename, _T(".."))) {
                new_chars_t  path2     = T_join(TT, path, filename, TT);
                new_chars_t  rel_path2 = T_join(TT, rel_path, filename, TT);

                Archive_addFolder(object_, path2, pattern_, rel_path2);

                freeT(&path2);
                freeT(&rel_path2);
            }
        }

#if PLATFORM_WIN32  /* TODO: abstract */
        found_file = FindNextFile_win(handle, &fdata);
#endif
    };

#if PLATFORM_WIN32  /* TODO: abstract */
    if (handle != INVALID_HANDLE_VALUE_win) {
        FindClose_win(handle);
    }

#endif                                                      /* PLATFORM_WIN32 */

#if _REPORTING > 0

    if (IS_BLANK(relative_path_)) {
        _report_summary(me);
    }

#endif                                                      /* _REPORTING > 0 */

    {
        /* TODO: abstract */
        bool  ret = false;
#if PLATFORM_WIN32  /* TODO: abstract */
        ret = C_BOOL(handle != INVALID_HANDLE_VALUE_win);
#endif
        RETURN(ret);
    }
} /* Archive_addFolder */


PUBLIC const archive_item_t*  Archive_addItem(                             /*M*/
    archive_t*      object_,                                               /*-*/
    chars_t         item_name_,                                            /*-*/
    const uint32_t  item_size_,                                            /*-*/
    const uint8_t*  item_data_ ) {                                         /*-*/
    GO                                                            (UID(FB2FCB));
    _archive_t* const  me = _object(object_, UID(E65045));

    new_chars_t      item_name  = T_first(item_name_, MAX_NAME_LEN);
    uint32_t         i          = 0;
    const uint32_t   item_count = Array_count(me->items);
    archive_item_t*  ret        = NULL;
    archive_item_t   item;

    replace_char_in_T(item_name, '\\', '/');

    CLEAR(item);
    item.item_name = item_name;
    item.item_size = item_size_;
    item.item_data = NULL;

    /* copy data to item's buffer */
    if (item_size_ > 0) {
        item.item_data = _malloc(item_size_);
        if (item_data_ != NULL) {
            MEMCPY(item.item_data, item_data_, item_size_);
        }
    }

    /* store the item in the array: */

    /* if an item with the same name exists in the archive, replace it */
    for (i = 0; i < item_count; i++) {
        ret = CAST(archive_item_t*, Array_getItemAt(&me->items, i));

        if (likeT(ret->item_name, item_name)) {
            if (ret->item_data != NULL) {
                FREE(ret->item_data);
            }
            *ret = item;
            RETURN(ret);
        }
    }

    /* otherwise, add the item to end of the array */
    Array_addItem(&me->items, &item, sizeof(item), NULL);

    ret = CAST(archive_item_t*, Array_getLastItem(&me->items));

    RETURN(ret);
} /* Archive_addItem */


PUBLIC void  Archive_clear( archive_t*  object_ ) {                        /*M*/
    GO                                                            (UID(FE48F0));
    Archive_removeItems(object_);
    Archive_packMemory(object_);
    RETURN(NIL);
} /* Archive_clear */


PUBLIC bool  Archive_deleteItem(                                           /*M*/
    archive_t*  object_,                                                   /*-*/
    chars_t     item_name_ ) {                                             /*-*/
    GO                                                            (UID(F6DEF6));
    _archive_t* const  me = _object(object_, UID(E8D914));

    uint32_t        i          = 0;
    const uint32_t  item_count = Array_count(me->items);
    new_chars_t     item_name  = T_first(item_name_, MAX_NAME_LEN);

    replace_char_in_T(item_name, '\\', '/');

    for (i = 0; i < item_count; i++) {
        archive_item_t*  item =
            CAST(archive_item_t*, Array_getItemAt(&me->items, i));

        if (likeT(item->item_name, item_name)) {
            FREE(item->item_data);
            Array_removeAt(&me->items, i);
            RETURN(true);
        }
    }
    RETURN(false);
} /* Archive_deleteItem */


PUBLIC bool  Archive_loadFromBytes(                                        /*M*/
    archive_t*      object_,                                               /*-*/
    const uint8_t*  bytes_,                                                /*-*/
    const uint32_t  key_size_,                                             /*-*/
    const uint8_t*  encryption_key_ ) {                                    /*-*/
    GO                                                            (UID(FAF9A3));
    _archive_t* const  me = _object(object_, UID(E52B9E));

    uint32_t        comp_size = 0;
    uint32_t        data_size = 0;
    const uint8_t*  data      = NULL;

    if (bytes_ == NULL) {
        WARN("bytes_ is NULL!", UID(E1AF19));
        RETURN(false);
    }

#if _REPORTING > 0
    _report_header(me, _T("Archive_loadFromBytes()"));
#endif

    {
        /* decrypt the compressed header to determine uncompressed data size: */
        uint8_t*  header = _malloc(COMPRESSED_HEADER_SIZE);
        MEMCPY(header, bytes_, COMPRESSED_HEADER_SIZE);
        _xor_encrypt_or_decrypt(header, COMPRESSED_HEADER_SIZE,
                                encryption_key_, key_size_);
        comp_size = bytes_compressed_size(header);
        data_size = bytes_uncompressed_size(header);
        FREE(header);
    }

    if (data_size == 0) {
        RETURN(false);
    } else {
        const size_t  header_size = 4 + 2 * sizeof(uint32_t);
        uint32_t      item_count  = 0;
        uint32_t      i           = 0;

        /* allocate, uncompress and un-encrypt data */
        uint8_t*  storage = _malloc(data_size);
        MEMCPY(storage, bytes_, COMPRESSED_HEADER_SIZE + comp_size);

        _xor_encrypt_or_decrypt(storage, data_size,
                                encryption_key_, key_size_);

        VERIFY(data_size == bytes_uncompress(storage, data_size), UID(E91CE1));

        {
            /* read the archive's signature, size and number of items: */
            /* get archive signature */
            const uint8_t*  bytes = storage;
            if (MEMCMP(bytes, "ARC1", 4) != 0) {
                if (storage != NULL) {
                    FREE(storage);
                    RETURN(false);
                }
            }
            bytes += 4;

            /* determine size of archive (in bytes) */
            data_size = _read_uint(bytes);
            bytes += sizeof(uint32_t);

            /* determine number of items in the archive */
            item_count = _read_uint(bytes);
            bytes += sizeof(uint32_t);

            /* warn and exit if the number of items */
            /* is greater than the archive size     */
            if (item_count >= data_size) {
                WARN(_T("item_count >= data_size"), UID(E94B36));
                RETURN(false);
            }
        }

        /* remove all existing items from this archive */
        Archive_removeItems(object_);

        /* read all items from the archive */
        data = storage + header_size;

        for (i = 0; i < item_count; i++) {
            archive_item_t  item;
            CLEAR(item);

            /* read the item's name */
            item.item_name = Tutf8(CAST(const char*, data));
            replace_char_in_T(item.item_name, '\\', '/');
            {
                const uint32_t  len = STRLEN(CAST(const char*, data)) + 1;
                data += len;
            }

            /* read byte size of item's data */
            item.item_size = _read_uint(data);
            data += sizeof(uint32_t);
            ASSERT(item.item_size < data_size, UID(E91A29));

            /* read item's data */
            if (item.item_size > 0) {
                item.item_data = _malloc(item.item_size);
                MEMCPY(item.item_data, data, item.item_size);
            } else {
                ASSERT(item.item_data == NULL, UID(E3C2F1));
                item.item_data = NULL;
            }

            data += item.item_size;

            Array_addItem(&me->items, &item, sizeof(item), NULL);

#if _REPORTING > 0
            _report_item(me, item.item_size, item.item_name);
#endif
        }

        Archive_packMemory(object_);
        me->storage      = storage;
        me->storage_size = data_size;

#if _REPORTING > 0
        _report_summary(me);
#endif
    }
    RETURN(true);
} /* Archive_loadFromBytes */


PUBLIC bool  Archive_loadFromBytesCharKey(                                 /*M*/
    archive_t*      object_,                                               /*-*/
    const uint8_t*  bytes_,                                                /*-*/
    const char*     encryption_key_ ) {                                    /*-*/
    GO                                                            (UID(FE86CE));
    bool  ret = false;

    if (bytes_ == NULL) {
        WARN("bytes_ is NULL!", UID(E46A8B));
    } else {
        const uint32_t  key_len = STRLEN(encryption_key_);

        ret = Archive_loadFromBytes(
                  object_, bytes_, key_len, CAST(uint8_t*, encryption_key_));
    }
    RETURN(ret);
} /* Archive_loadFromBytesCharKey */


PUBLIC bool  Archive_loadFromFile(                                         /*M*/
    archive_t*      object_,                                               /*-*/
    chars_t         filename_,                                             /*-*/
    const uint32_t  key_size_,                                             /*-*/
    const uint8_t*  encryption_key_ ) {                                    /*-*/
    GO                                                            (UID(F59261));
    bool    ret  = false;
    file_t  file = File_initRead(filename_);

    if (File_isOpen(file)) {
        const uint32_t  bytes_size = File_getFileSize(file);
        if (bytes_size > 0) {
            uint8_t*  data = _malloc(bytes_size);
            File_read(file, data, bytes_size);
            ret = C_BOOL(Archive_loadFromBytes(
                             object_, data, key_size_, encryption_key_));
            FREE(data);
        }
    }
    File_free(&file);

    RETURN(ret);
} /* Archive_loadFromFile */


PUBLIC bool  Archive_loadFromFileCharKey(                                  /*M*/
    archive_t*   object_,                                                  /*-*/
    chars_t      filename_,                                                /*-*/
    const char*  encryption_key_ ) {                                       /*-*/
    GO                                                            (UID(F39406));
    const uint32_t  key_len = STRLEN(encryption_key_);
    const bool      ret     = Archive_loadFromFile(
                                  object_, filename_, key_len,
                                  CAST(uint8_t*, encryption_key_));
    RETURN(ret);
} /* Archive_loadFromFileCharKey */


PUBLIC void  Archive_packMemory( archive_t*  object_ ) {                   /*M*/
    GO                                                            (UID(FDBAA0));
    _archive_t* const  me = _object(object_, UID(EFAECE));

    if (me->storage != NULL) {
        FREE(me->storage);
        me->storage = NULL;
    }

    me->storage_size = 0;

    if (me->report_text != NULL) {
        freeT(&me->report_text);
    }
    RETURN(NIL);
} /* Archive_packMemory */


PUBLIC void  Archive_removeItems( archive_t*  object_ ) {                  /*M*/
    GO                                                            (UID(FD7C1D));
    _archive_t* const  me = _object(object_, UID(E891DF));

    uint32_t        i          = 0;
    const uint32_t  item_count = Array_count(me->items);

    for (i = 0; i < item_count; i++) {
        archive_item_t*  item =
            CAST(archive_item_t*, Array_getItemAt(&me->items, i));

        if (item->item_name != NULL) {
            freeT(&item->item_name);
        }

        if (item->item_data != NULL) {
            FREE(item->item_data);
        }
    }
    Array_removeItems(&me->items);
    RETURN(NIL);
} /* Archive_removeItems */


PUBLIC bool  Archive_saveToFile(                                           /*M*/
    const archive_t  object_,                                              /*-*/
    chars_t          filename_,                                            /*-*/
    const uint32_t   key_size_,                                            /*-*/
    const uint8_t*   encryption_key_ ) {                                   /*-*/
    GO                                                            (UID(F38190));
    const uint8_t*  data       = Archive_getStorageBytes(
                                     object_, key_size_, encryption_key_);
    const uint32_t  bytes_size = Archive_getStorageSize(object_);
    file_t          file       = File_initInMode(filename_, true, false);

    if (!File_isOpen(file)) {
        RETURN(false);
    }

    File_write(file, data, bytes_size);
    File_close(file);
    File_free(&file);

    RETURN(true);
} /* Archive_saveToFile */


PUBLIC void  Archive_setCopy(                                              /*M*/
    archive_t*       object_,                                              /*-*/
    const archive_t  copy_from_ ) {                                        /*-*/
    GO                                                            (UID(F27BB1));
    const _archive_t*  src        = _object_const(&copy_from_, UID(E8FE6C));
    const uint32_t      item_count = Array_count(src->items);
    uint32_t            i          = 0;

    Archive_clear(object_);

    for (i = 0; i < item_count; i++) {
        const archive_item_t*  item =
            CAST(const archive_item_t*,
                 Array_getItemAt(&CAST(_archive_t*, src)->items, i));

        Archive_addItem(
            object_, item->item_name, item->item_size, item->item_data);
    }
    RETURN(NIL);
} /* Archive_setCopy */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
