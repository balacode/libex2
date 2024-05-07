/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                    [libex_archive_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_ARCHIVE__H
#define      INCLUDED_LIBEX_ARCHIVE__H
#include "libex_archive.h"

#if defined LX_USE_ZLIB_COMPRESSION
#define USE_ZLIB_COMPRESSION
#else
#undef USE_ZLIB_COMPRESSION
#endif

#define archive_t                       lx_archive_t
#define new_archive_t                   lx_new_archive_t
#define null_archive                    lx_null_archive

#define archive_item_t                  lx_archive_item_t
#define null_archive_item               lx_null_archive_item

/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */

#define Archive_init                    lx_Archive_init
#define Archive_initBytes               lx_Archive_initBytes
#define Archive_initCopy                lx_Archive_initCopy

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

#define Archive_free                    lx_Archive_free

/* -------------------------------------------------------------------------- */
/* Methods: Const                                                             */

#define Archive_equal                   lx_Archive_equal
#define Archive_getItem                 lx_Archive_getItem
#define Archive_getStorageBytes         lx_Archive_getStorageBytes
#define Archive_getStorageSize          lx_Archive_getStorageSize
#define Archive_getText                 lx_Archive_getText
#define Archive_itemExists              lx_Archive_itemExists
#define Archive_report                  lx_Archive_report

/* -------------------------------------------------------------------------- */
/* Methods: Manipulative                                                      */

#define Archive_addFolder               lx_Archive_addFolder
#define Archive_addItem                 lx_Archive_addItem
#define Archive_clear                   lx_Archive_clear
#define Archive_deleteItem              lx_Archive_deleteItem
#define Archive_loadFromBytes           lx_Archive_loadFromBytes
#define Archive_loadFromBytesCharKey    lx_Archive_loadFromBytesCharKey
#define Archive_loadFromFile            lx_Archive_loadFromFile
#define Archive_loadFromFileCharKey     lx_Archive_loadFromFileCharKey
#define Archive_packMemory              lx_Archive_packMemory
#define Archive_removeItems             lx_Archive_removeItems
#define Archive_saveToFile              lx_Archive_saveToFile
#define Archive_setCopy                 lx_Archive_setCopy

#endif                                                                   /*eof*/
