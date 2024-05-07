/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                     [libex_archive.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_ARCHIVE_H
#define      INCLUDED_LIBEX_ARCHIVE_H

#if !defined LX_USE_ZLIB_COMPRESSION
#define LX_USE_ZLIB_COMPRESSION  1   /* Enable compression with the ZLib lib. */
#endif

#include "libex_array.h"
#include "libex_string_class.h"

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

typedef struct  lx_archive_t {
    uint8_t*  ob;                                             /* lx_archive_t */
}
lx_archive_t, lx_new_archive_t;

typedef struct  lx_archive_item_t {
    lx_new_chars_t  item_name;                           /* lx_archive_item_t */
    uint32_t        item_size;                           /* lx_archive_item_t */
    uint8_t*        item_data;                           /* lx_archive_item_t */
}
lx_archive_item_t;

static lx_archive_t       lx_null_archive      = { NULL };
static lx_archive_item_t  lx_null_archive_item = { NULL, 0, NULL };

/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */

/* Default Constructor */
LX_PUBLIC lx_new_archive_t  lx_Archive_init( void );                       /*C*/

/* Constructor: Constructs an archive from a pointer to                       */
/* an encrypted archive image, and an ANSI character key.                     */
LX_PUBLIC lx_new_archive_t  lx_Archive_initBytes(                          /*C*/
    uint8_t*     storage_bytes_,                                           /*-*/
    const char*  encryption_key_ );                                        /*-*/

/* Copy Constructor */
LX_PUBLIC lx_new_archive_t  lx_Archive_initCopy(                           /*C*/
    const lx_archive_t  copy_from_ );                                      /*-*/

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

LX_PUBLIC void  lx_Archive_free( lx_archive_t*  object_ );                 /*D*/

/* -------------------------------------------------------------------------- */
/* Methods: Const                                                             */

/* returns true if two archives contain the same items.                       */
LX_PUBLIC lx_bool  lx_Archive_equal(                                       /*M*/
    const lx_archive_t  object_,                                           /*-*/
    const lx_archive_t  compare_ );                                        /*-*/

LX_PUBLIC lx_archive_item_t  lx_Archive_getItem(                           /*M*/
    const lx_archive_t  object_,                                           /*-*/
    lx_chars_t          item_name_ );                                      /*-*/

/* Generates and returns a pointer to an encrypted archive image              */
LX_PUBLIC const uint8_t*  lx_Archive_getStorageBytes(                      /*M*/
    const lx_archive_t  object_,                                           /*-*/
    const uint32_t      key_size_,                                         /*-*/
    const uint8_t*      encryption_key_ );                                 /*-*/

/* returns the size of the image in bytes.                                    */
/* Only call it after getting an image pointer with getStorageBytes()         */
LX_PUBLIC uint32_t  lx_Archive_getStorageSize(                             /*M*/
    const lx_archive_t  object_ );                                         /*-*/

/* returns the named item as a text string.                                   */
LX_PUBLIC lx_new_str_t  lx_Archive_getText(                                /*M*/
    const lx_archive_t  object_,                                           /*-*/
    lx_chars_t          item_name_ );                                      /*-*/

/* returns true if the named item exists in the archive.                      */
LX_PUBLIC lx_bool  lx_Archive_itemExists(                                  /*M*/
    const lx_archive_t  object_,                                           /*-*/
    lx_chars_t          item_name_ );                                      /*-*/

LX_PUBLIC lx_chars_t  lx_Archive_report( const lx_archive_t  object_ );    /*M*/

/* -------------------------------------------------------------------------- */
/* Methods: Manipulative                                                      */

LX_PUBLIC lx_bool  lx_Archive_addFolder(                                   /*M*/
    lx_archive_t*  object_,                                                /*-*/
    lx_chars_t     path_,                                                  /*-*/
    lx_chars_t     pattern_,                                               /*-*/
    lx_chars_t     relative_path_ );                                       /*-*/

LX_PUBLIC const lx_archive_item_t*  lx_Archive_addItem(                    /*M*/
    lx_archive_t*   object_,                                               /*-*/
    lx_chars_t      item_name_,                                            /*-*/
    const uint32_t  item_size_,                                            /*-*/
    const uint8_t*  item_data_ );                                          /*-*/

/* Clears the contents of the archive, releasing all allocated memory.        */
LX_PUBLIC void  lx_Archive_clear( lx_archive_t*  object_ );                /*M*/

LX_PUBLIC lx_bool  lx_Archive_deleteItem(                                  /*M*/
    lx_archive_t*  object_,                                                /*-*/
    lx_chars_t     item_name_ );                                           /*-*/

LX_PUBLIC lx_bool  lx_Archive_loadFromBytes(                               /*M*/
    lx_archive_t*   object_,                                               /*-*/
    const uint8_t*  bytes_,                                                /*-*/
    const uint32_t  key_size_,                                             /*-*/
    const uint8_t*  encryption_key_ );                                     /*-*/

LX_PUBLIC lx_bool  lx_Archive_loadFromBytesCharKey(                        /*M*/
    lx_archive_t*   object_,                                               /*-*/
    const uint8_t*  bytes_,                                                /*-*/
    const char*     encryption_key_ );                                     /*-*/

LX_PUBLIC lx_bool  lx_Archive_loadFromFile(                                /*M*/
    lx_archive_t*   object_,                                               /*-*/
    lx_chars_t      filename_,                                             /*-*/
    const uint32_t  key_size_,                                             /*-*/
    const uint8_t*  encryption_key_ );                                     /*-*/

LX_PUBLIC lx_bool  lx_Archive_loadFromFileCharKey(                         /*M*/
    lx_archive_t*  object_,                                                /*-*/
    lx_chars_t     filename_,                                              /*-*/
    const char*    encryption_key_ );                                      /*-*/

LX_PUBLIC void  lx_Archive_packMemory( lx_archive_t*  object_ );           /*M*/

LX_PUBLIC void  lx_Archive_removeItems( lx_archive_t*  object_ );          /*M*/

LX_PUBLIC lx_bool  lx_Archive_saveToFile(                                  /*M*/
    const lx_archive_t  object_,                                           /*-*/
    lx_chars_t          filename_,                                         /*-*/
    const uint32_t      key_size_,                                         /*-*/
    const uint8_t*      encryption_key_ );                                 /*-*/

LX_PUBLIC void  lx_Archive_setCopy(                                        /*M*/
    lx_archive_t*       object_,                                           /*-*/
    const lx_archive_t  copy_from_ );                                      /*-*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
