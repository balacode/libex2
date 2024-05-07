/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                      [libex_bytes_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_BYTES__H
#define      INCLUDED_LIBEX_BYTES__H
#include "libex_bytes.h"

#if defined LX_USE_ZLIB_COMPRESSION
#define USE_ZLIB_COMPRESSION
#else
#undef USE_ZLIB_COMPRESSION
#endif

#if defined LX_USE_ZLIB_COMPRESSION
#define COMPRESSED_HEADER_SIZE          LX_COMPRESSED_HEADER_SIZE
#endif

/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */

#define Bytes_init                      lx_Bytes_init
#define Bytes_initChars                 lx_Bytes_initChars              /*TODO*/
#define Bytes_fromNewChars              lx_Bytes_fromNewChars

/* -------------------------------------------------------------------------- */
/* Destructor                                                                 */

#define Bytes_free                      lx_Bytes_free

/* -------------------------------------------------------------------------- */

#define Bytes_describe                  lx_Bytes_describe
#define Bytes_describeW                 lx_Bytes_describeW
#define Bytes_describeT                lx_Bytes_describeT

/* -------------------------------------------------------------------------- */

#define Bytes_equals                    lx_Bytes_equals
#define Bytes_join                      lx_Bytes_join
#define Bytes_resize                    lx_Bytes_resize

/* -------------------------------------------------------------------------- */
/* Functions: Byte Pointers                                                   */

#define byte_random_positions           lx_byte_random_positions

#if defined LX_USE_ZLIB_COMPRESSION
#define bytes_compress                  lx_bytes_compress
#define bytes_compressed_size           lx_bytes_compressed_size
#define bytes_uncompress                lx_bytes_uncompress
#define bytes_uncompressed_size         lx_bytes_uncompressed_size
#endif

#define bytes_transpose                 lx_bytes_transpose
#define checksum                        lx_checksum

#endif                                                                   /*eof*/
