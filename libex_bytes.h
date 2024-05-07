/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_bytes.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_BYTES_H
#define      INCLUDED_LIBEX_BYTES_H

#include "libex.h"

/* note: to enable ZLib compression, define LX_USE_ZLIB_COMPRESSION */
/*       in the project settings                                    */

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

#if defined LX_USE_ZLIB_COMPRESSION
static const uint32_t  LX_COMPRESSED_HEADER_SIZE = 16 + sizeof(uint32_t) * 2;
#endif

/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */

LX_PUBLIC lx_new_bytes_t  lx_Bytes_init(                                   /*C*/
    const uint8_t* const  bytes_,                                          /*-*/
    const uint32_t        size_ );                                         /*-*/

/* TODO: create Bytes_initChars( lx_chars_t  text_ ); */

LX_PUBLIC lx_new_bytes_t  lx_Bytes_fromNewChars(                           /*C*/
    lx_new_chars_t  assign_chars_ );                                       /*-*/

/* -------------------------------------------------------------------------- */
/* Destructor                                                                 */

LX_PUBLIC lx_bool  lx_Bytes_free( lx_bytes_t*  bytes_ );                   /*D*/

/* -------------------------------------------------------------------------- */

LX_PUBLIC lx_new_bchars_t  lx_Bytes_describe( const lx_bytes_t  bytes_ );  /*P*/

LX_PUBLIC lx_new_wchars  lx_Bytes_describeW( const lx_bytes_t  bytes_ );   /*P*/

#if defined UNICODE || defined _UNICODE
#define lx_Bytes_describeT  lx_Bytes_describeW                             /*P*/
#else
#define lx_Bytes_describeT  lx_Bytes_describe                              /*P*/
#endif

/* -------------------------------------------------------------------------- */

LX_PUBLIC lx_bool  lx_Bytes_equals(                                        /*P*/
    const lx_bytes_t  bytes_1_,                                            /*-*/
    const lx_bytes_t  bytes_2_ );                                          /*-*/

LX_PUBLIC lx_new_bytes_t  lx_Bytes_join(                                   /*M*/
    const lx_bytes_t  bytes_1_,                                            /*-*/
    const lx_bytes_t  bytes_2_ );                                          /*-*/

LX_PUBLIC lx_bool  lx_Bytes_resize(                                        /*M*/
    lx_bytes_t*     bytes_,                                                /*-*/
    const uint32_t  new_size_ );                                           /*-*/

/* -------------------------------------------------------------------------- */
/* Functions: Byte Pointers                                                   */

LX_PUBLIC lx_bool  lx_byte_random_positions(                               /*F*/
    uint8_t*   positions_out_,                                             /*-*/
    const int  length_ );                                                  /*-*/

#if defined LX_USE_ZLIB_COMPRESSION
LX_PUBLIC uint32_t  lx_bytes_compress(                                     /*F*/
    void*           bytes_,                                                /*-*/
    const uint32_t  size_in_bytes_ );                                      /*-*/
#endif                                             /* LX_USE_ZLIB_COMPRESSION */

#if defined LX_USE_ZLIB_COMPRESSION
LX_PUBLIC uint32_t  lx_bytes_compressed_size( void*  bytes_ );             /*F*/
#endif

LX_PUBLIC lx_bool  lx_bytes_transpose(                                     /*F*/
    uint8_t*        bytes_out_,                                            /*-*/
    const uint8_t*  positions_,                                            /*-*/
    const int       length_ );                                             /*-*/

#if defined LX_USE_ZLIB_COMPRESSION
LX_PUBLIC uint32_t  lx_bytes_uncompress(                                   /*F*/
    void*           bytes_,                                                /*-*/
    const uint32_t  size_in_bytes_ );                                      /*-*/
#endif                                             /* LX_USE_ZLIB_COMPRESSION */

#if defined LX_USE_ZLIB_COMPRESSION
LX_PUBLIC uint32_t  lx_bytes_uncompressed_size( void*  bytes_ );           /*F*/
#endif

/* uses the Adler-32 checksum algorithm        */
/* (see http://en.wikipedia.org/wiki/Adler-32) */
LX_PUBLIC uint32_t  lx_checksum(                                           /*F*/
    const uint8_t*  data_,                                                 /*-*/
    const uint32_t  length_in_bytes_ );                                    /*-*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
