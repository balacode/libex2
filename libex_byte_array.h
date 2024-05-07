/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                  [libex_byte_array.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_BYTE_ARRAY_H
#define      INCLUDED_LIBEX_BYTE_ARRAY_H

#include "libex.h"

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

typedef struct  lx_byte_array_t {
    uint8_t*  ob;                                          /* lx_byte_array_t */
}
lx_byte_array_t, lx_new_byte_array_t;

/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */

LX_PUBLIC lx_new_byte_array_t  lx_ByteArray_init( void );                  /*C*/

LX_PUBLIC lx_new_byte_array_t  lx_ByteArray_newCopy(                       /*C*/
    const lx_byte_array_t  copy_from_ );                                   /*-*/

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

LX_PUBLIC void  lx_ByteArray_free( lx_byte_array_t*  object_ );            /*D*/

/* -------------------------------------------------------------------------- */
/* Properties:                                                                */

LX_PUBLIC lx_bool  lx_ByteArray_bof( const lx_byte_array_t  object_ );     /*M*/

LX_PUBLIC lx_bool  lx_ByteArray_eof( const lx_byte_array_t  object_ );     /*P*/

LX_PUBLIC size_t  lx_ByteArray_getPosition(                                /*P*/
    const lx_byte_array_t  object_ );                                      /*-*/

LX_PUBLIC lx_bool  lx_ByteArray_setPosition(                               /*P*/
    lx_byte_array_t  object_,                                              /*-*/
    const size_t     new_value_ );                                         /*-*/

LX_PUBLIC size_t  lx_ByteArray_getSize( const lx_byte_array_t  object_ );  /*P*/

LX_PUBLIC lx_bool  lx_ByteArray_setSize(                                   /*P*/
    lx_byte_array_t  object_,                                              /*-*/
    const size_t     new_value_ );                                         /*-*/

LX_PUBLIC lx_bool  lx_ByteArray_equal(                                     /*P*/
    const lx_byte_array_t  object_,                                        /*-*/
    const lx_byte_array_t  compare_ );                                     /*-*/

LX_PUBLIC lx_bool  lx_ByteArray_matches(                                   /*P*/
    const lx_byte_array_t  object_,                                        /*-*/
    const char*            ascii_chars_,                                   /*-*/
    const size_t           length_ );                                      /*-*/

LX_PUBLIC lx_bool  lx_ByteArray_isCompressed(                              /*P*/
    const lx_byte_array_t  object_ );                                      /*-*/

/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */

LX_PUBLIC uint8_t*  lx_ByteArray_getBuffer( lx_byte_array_t  object_ );    /*M*/

LX_PUBLIC void  lx_ByteArray_clear( lx_byte_array_t  object_ );            /*M*/

LX_PUBLIC void  lx_ByteArray_set(                                          /*M*/
    lx_byte_array_t  object_,                                              /*-*/
    const size_t     size_in_bytes_,                                       /*-*/
    const uint8_t    fill_ );                                              /*-*/

LX_PUBLIC void  lx_ByteArray_setCopy(                                      /*C*/
    lx_byte_array_t        object_,                                        /*-*/
    const lx_byte_array_t  copy_from_ );                                   /*-*/

LX_PUBLIC void  lx_ByteArray_copyBytes(                                    /*M*/
    lx_byte_array_t  object_,                                              /*-*/
    const void*      bytes_,                                               /*-*/
    const size_t     size_in_bytes_,                                       /*-*/
    const lx_bool    compressed_ );                                        /*-*/

LX_PUBLIC void  lx_ByteArray_fill(                                         /*M*/
    lx_byte_array_t  object_,                                              /*-*/
    const uint8_t    value_ );                                             /*-*/

LX_PUBLIC uint8_t*  lx_ByteArray_detachBuffer( lx_byte_array_t  object_ ); /*M*/

LX_PUBLIC lx_bool  lx_ByteArray_goBegin( lx_byte_array_t  object_ );       /*M*/

LX_PUBLIC lx_bool  lx_ByteArray_goEnd( lx_byte_array_t  object_ );         /*M*/

LX_PUBLIC lx_bool  lx_ByteArray_goBack(                                    /*M*/
    lx_byte_array_t  object_,                                              /*-*/
    const size_t     count_ );                                             /*-*/

LX_PUBLIC lx_bool  lx_ByteArray_goForward(                                 /*M*/
    lx_byte_array_t  object_,                                              /*-*/
    const size_t     count_ );                                             /*-*/

LX_PUBLIC lx_chars_t  lx_ByteArray_getHexString(                           /*M*/
    lx_byte_array_t  object_,                                              /*-*/
    const size_t     bytes_,                                               /*-*/
    const long       offset_ );                                            /*-*/

/* -------------------------------------------------------------------------- */
/* Read/Write Methods:                                                        */

LX_PUBLIC lx_bool  lx_ByteArray_writeInt(                                  /*M*/
    lx_byte_array_t  object_,                                              /*-*/
    const int        value_ );                                             /*-*/

LX_PUBLIC uint32_t  lx_ByteArray_readUnsigned(                             /*M*/
    lx_byte_array_t  object_,                                              /*-*/
    const size_t     bytes_,                                               /*-*/
    uint8_t*         byte_1_out_,                                          /*-*/
    uint8_t*         byte_2_out_,                                          /*-*/
    uint8_t*         byte_3_out_,                                          /*-*/
    uint8_t*         byte_4_out_ );                                        /*-*/

LX_PUBLIC uint32_t  lx_ByteArray_readUnsignedVariable(                     /*M*/
    lx_byte_array_t  object_,                                              /*-*/
    size_t*          length_in_bytes_out_ );                               /*-*/

LX_PUBLIC lx_chars_t  lx_ByteArray_readAsciiString(                        /*M*/
    lx_byte_array_t  object_,                                              /*-*/
    const size_t     count_ );                                             /*-*/

LX_PUBLIC lx_bool  lx_ByteArray_writeUnsignedInt(                          /*M*/
    lx_byte_array_t  object_,                                              /*-*/
    const uint32_t   value_ );                                             /*-*/

LX_PUBLIC lx_bool  lx_ByteArray_writeString(                               /*M*/
    lx_byte_array_t  object_,                                              /*-*/
    lx_chars_t       text_,                                                /*-*/
    const size_t     max_len_ );                                           /*-*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
