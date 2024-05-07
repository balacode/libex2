/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                 [libex_byte_array_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_BYTE_ARRAY__H
#define      INCLUDED_LIBEX_BYTE_ARRAY__H

#include "libex_byte_array.h"

#define byte_array_t                    lx_byte_array_t
#define new_byte_array_t                lx_new_byte_array_t

/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */

#define ByteArray_init                  lx_ByteArray_init
#define ByteArray_newCopy               lx_ByteArray_newCopy

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

#define ByteArray_free                  lx_ByteArray_free

/* -------------------------------------------------------------------------- */
/* Properties:                                                                */

#define ByteArray_bof                   lx_ByteArray_bof
#define ByteArray_eof                   lx_ByteArray_eof
#define ByteArray_getPosition           lx_ByteArray_getPosition
#define ByteArray_setPosition           lx_ByteArray_setPosition
#define ByteArray_getSize               lx_ByteArray_getSize
#define ByteArray_setSize               lx_ByteArray_setSize
#define ByteArray_equal                 lx_ByteArray_equal
#define ByteArray_matches               lx_ByteArray_matches
#define ByteArray_isCompressed          lx_ByteArray_isCompressed

/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */

#define ByteArray_getBuffer             lx_ByteArray_getBuffer
#define ByteArray_clear                 lx_ByteArray_clear
#define ByteArray_set                   lx_ByteArray_set
#define ByteArray_setCopy               lx_ByteArray_setCopy
#define ByteArray_copyBytes             lx_ByteArray_copyBytes
#define ByteArray_fill                  lx_ByteArray_fill
#define ByteArray_detachBuffer          lx_ByteArray_detachBuffer
#define ByteArray_goBegin               lx_ByteArray_goBegin
#define ByteArray_goEnd                 lx_ByteArray_goEnd
#define ByteArray_goBack                lx_ByteArray_goBack
#define ByteArray_goForward             lx_ByteArray_goForward
#define ByteArray_getHexString          lx_ByteArray_getHexString

/* -------------------------------------------------------------------------- */
/* Read/Write Methods:                                                        */

#define ByteArray_writeInt              lx_ByteArray_writeInt
#define ByteArray_readUnsigned          lx_ByteArray_readUnsigned
#define ByteArray_readUnsignedVariable  lx_ByteArray_readUnsignedVariable
#define ByteArray_readAsciiString       lx_ByteArray_readAsciiString
#define ByteArray_writeUnsignedInt      lx_ByteArray_writeUnsignedInt
#define ByteArray_writeString           lx_ByteArray_writeString

#endif                                                                   /*eof*/
