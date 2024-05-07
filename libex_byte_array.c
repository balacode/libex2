/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                  [libex_byte_array.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_byte_array_.h"
#if defined INCLUDED_LIBEX_BYTE_ARRAY_H

#include <stdio.h>   /* for sprintf() */
#include <string.h>  /* for memset()  */

#include "libex_.h"
#include "libex_call_.h"
#include "libex_debug_.h"
#include "libex_error_.h"
#include "libex_macro_.h"
#include "libex_stringc_.h"
#include "libex_type_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#if defined _MSC_VER
#pragma warning (disable:4710)  /* W:L4 function not inlined                  */
#endif

/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


typedef struct  _byte_array_t {
    uint8_t*  mem;                                           /* _byte_array_t */
    /* Pointer to allocated memory block */

    size_t  size;                                            /* _byte_array_t */
    /* Size of allocated memory block, in bytes */

    size_t  pos;                                             /* _byte_array_t */
    /* The current read/write postion */

    bool  is_compressed;                                     /* _byte_array_t */
    /* If true, this is a compressed block */

    char_t*  temp_chars;                                     /* _byte_array_t */
    /* used by readAsciiString() and ReadHexString() */
}
_byte_array_t;


/* -------------------------------------------------------------------------- */
/* Functions: Private                                                         */


#define _BASE_OBJ_WRAP_INC
#define _OBJ_HANDLE_TYPE   byte_array_t
#define _OBJ_INNER_TYPE    _byte_array_t
#define _OBJ_ALLOC_FN_UID  UID(FF1546)
#define _OBJ_FREE_FN_UID   UID(F86574)
#define _OBJ_CONST_FN_UID  UID(F432A6)
#define _OBJ_FN_UID        UID(F2072E)
#define _OBJ_WRAP_FN_UID   UID(FC8BB7)
#include "libex_object_wrapper.inc.c"


/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */


PUBLIC new_byte_array_t  ByteArray_init( void ) {                          /*C*/
    GO                                                            (UID(C994E3));
    _byte_array_t*  ob = _object_alloc();
    /* _object_alloc() zeros everything, so all data members */
    /* will be NULL, 0 or false, as appropriate              */

    new_byte_array_t  ret = _object_wrap(ob);

    RETURN(ret);
} /* ByteArray_init */


PUBLIC void  ByteArray_setCopy(                                            /*C*/
    byte_array_t        object_,                                           /*-*/
    const byte_array_t  copy_from_ ) {                                     /*-*/
    GO                                                            (UID(FF3C6E));
    _byte_array_t* const  me = _object(&object_, UID(E75B52));
    const _byte_array_t* const  copy_from = _object(&copy_from_, UID(E02BF1));

    if (copy_from == me) {
        RETURN(NIL);
    }

    ByteArray_clear(object_);

    if (copy_from->size > 0) {
        me->mem = CAST(uint8_t*, MALLOC(copy_from->size));
    }

    me->size          = copy_from->size;
    me->pos           = copy_from->pos;
    me->is_compressed = copy_from->is_compressed;

    if (copy_from->size > 0) {
        MEMCPY(me->mem, copy_from->mem, me->size);
    }
    RETURN(NIL);
} /* ByteArray_setCopy */


PUBLIC new_byte_array_t  ByteArray_newCopy(                                /*C*/
    const byte_array_t  copy_from_ ) {                                     /*-*/
    GO                                                            (UID(F6F6BB));
    new_byte_array_t  ret = ByteArray_init();
    ByteArray_setCopy(ret, copy_from_);
    RETURN(ret);
} /* ByteArray_newCopy */


/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */


PUBLIC void  ByteArray_free( byte_array_t*  object_ ) {                    /*D*/
    GO                                                            (UID(F4100F));
    _byte_array_t* const  me = _object(object_, UID(E5C0BF));

    if (me->mem != NULL) {
        FREE(me->mem);
    }

    if (me->temp_chars != NULL) {
        FREE(me->temp_chars);
    }

    _object_free(object_);
    RETURN(NIL);
} /* ByteArray_free */


/* -------------------------------------------------------------------------- */
/* Properties:                                                                */


PUBLIC bool  ByteArray_bof( const byte_array_t  object_ ) {                /*P*/
    GO                                                            (UID(FB3065));
    _byte_array_t* const  me = _object(&object_, UID(E79125));
    const bool  ret = (me->pos == 0);
    RETURN(ret);
} /* ByteArray_bof */


PUBLIC bool  ByteArray_eof( const byte_array_t  object_ ) {                /*P*/
    GO                                                            (UID(FFFE85));
    _byte_array_t* const  me = _object(&object_, UID(E1C373));
    const bool  ret = (me->pos == (me->size - 1));
    RETURN(ret);
} /* ByteArray_eof */


PUBLIC size_t  ByteArray_getPosition( const byte_array_t  object_ ) {      /*P*/
    GO                                                            (UID(F500AE));
    const _byte_array_t* const  me = _object_const(&object_, UID(E4BF66));
    const size_t  ret = me->pos;
    RETURN(ret);
} /* ByteArray_getPosition */


PUBLIC bool  ByteArray_setPosition(                                        /*P*/
    byte_array_t  object_,                                                 /*-*/
    const size_t  new_value_ ) {                                           /*-*/
    GO                                                            (UID(FAB286));
    _byte_array_t* const  me = _object(&object_, UID(EB382F));

    if (new_value_ > (me->size - 1)) {
        RETURN(false);
    }

    me->pos = new_value_;

    RETURN(true);
} /* ByteArray_setPosition */


PUBLIC size_t  ByteArray_getSize( const byte_array_t  object_ ) {          /*P*/
    GO                                                            (UID(F620C3));
    const _byte_array_t* const  me = _object_const(&object_, UID(E1F273));
    RETURN(me->size);
} /* ByteArray_getSize */


PUBLIC bool  ByteArray_setSize(                                            /*P*/
    byte_array_t  object_,                                                 /*-*/
    const size_t  new_value_ ) {                                           /*-*/
    GO                                                            (UID(F4646C));
    _byte_array_t* const  me = _object(&object_, UID(EA3288));

    size_t    new_size = 0;
    uint8_t*  bytes    = NULL;

    if (new_value_ == me->size) {
        RETURN(true);
    }

    if (new_value_ < me->size) {
        me->size = new_value_;
        RETURN(true);
    }

    /* allocate memory */
    new_size = new_value_;
    bytes    = CAST(uint8_t*, MALLOC(new_size));

    if (bytes == NULL) {
        new_size = 0;
    }

    if (new_size == 0) {
        RETURN(false);
    }

    /* set all allocated bytes to 0 */
    MEMSET(bytes, 0x00, new_size);

    /* copy old buffer to bytes buffer, and release the old buffer */
    if (me->mem != NULL) {
        if (me->size > 0) {
            MEMCPY(bytes, me->mem, me->size);
        }
        FREE(me->mem);
    }

    me->mem  = bytes;
    me->size = new_size;

    RETURN(true);
} /* ByteArray_setSize */


/* returns true if the size and contents of the given block are identical     */
/* to this memory block. (The current read/write position is ignored)         */
PUBLIC bool  ByteArray_equal(                                              /*P*/
    const byte_array_t  object_,                                           /*-*/
    const byte_array_t  compare_ ) {                                       /*-*/
    GO                                                            (UID(F4F050));
    const _byte_array_t* const  me = _object_const(&object_, UID(E45186));
    const _byte_array_t* const  cmp = _object_const(&compare_, UID(EC8499));
    bool  ret = false;

    if (me->size == cmp->size && me->is_compressed == cmp->is_compressed) {
        ret = MEMCMP(cmp->mem, me->mem, me->size) == 0;
    }
    RETURN(ret);
} /* ByteArray_equal */


PUBLIC bool  ByteArray_matches(                                            /*M*/
    const byte_array_t  object_,                                           /*-*/
    const char*         ascii_chars_,                                      /*-*/
    const size_t        length_ ) {                                        /*-*/
    GO                                                            (UID(FD88C6));
    const _byte_array_t* const  me = _object_const(&object_, UID(EDA43C));

    const uint8_t*  data  = NULL;
    const uint8_t*  ascii = CAST(const uint8_t*, ascii_chars_);
    size_t          size  = length_;
    size_t          i     = 0;

    if (size == 0) {
        size = STRLEN(ascii_chars_);
    }

    if (size == 0 || me->pos + size > me->size) {
        RETURN(false);
    }

    data = me->mem + me->pos;

    for (i = 0; i < size; i++) {
        if (*ascii++ != *data++) {
            RETURN(false);
        }
    }
    RETURN(true);
} /* ByteArray_matches */


PUBLIC bool  ByteArray_isCompressed( const byte_array_t object_ ) {        /*P*/
    GO                                                            (UID(F0D9B5));
    _byte_array_t* const  me = _object(&object_, UID(E802E9));
    RETURN(me->is_compressed);
} /* ByteArray_isCompressed */


/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */


PUBLIC uint8_t*  ByteArray_getBuffer( byte_array_t  object_ ) {            /*M*/
    GO                                                            (UID(F5E439));
    _byte_array_t* const  me = _object(&object_, UID(EC10D1));
    RETURN(me->mem);
} /* ByteArray_getBuffer */


PUBLIC void  ByteArray_clear( byte_array_t  object_ ) {                    /*M*/
    GO                                                            (UID(F087F4));
    _byte_array_t* const  me = _object(&object_, UID(EA080A));

    if (me != NULL && me->mem) {
        FREE(me->mem);
        me->mem           = NULL;
        me->size          = 0;
        me->pos           = 0;
        me->is_compressed = false;

        freeT(&me->temp_chars);
    }
    RETURN(NIL);
} /* ByteArray_clear */


PUBLIC void  ByteArray_set(                                                /*M*/
    byte_array_t   object_,                                                /*-*/
    const size_t   size_in_bytes_,                                         /*-*/
    const uint8_t  fill_ ) {                                               /*-*/
    GO                                                            (UID(F59140));
    _byte_array_t* const  me = _object(&object_, UID(EB88D4));
    ByteArray_clear(object_);
    me->size = size_in_bytes_;
    me->mem  = CAST(uint8_t*, MALLOC(me->size));
    MEMSET(me->mem, fill_, me->size);  /* fill memory */
    RETURN(NIL);
} /* ByteArray_set */


PUBLIC void  ByteArray_copyBytes(                                          /*M*/
    byte_array_t  object_,                                                 /*-*/
    const void*   bytes_,                                                  /*-*/
    const size_t  size_in_bytes_,                                          /*-*/
    const bool    compressed_ ) {                                          /*-*/
    GO                                                            (UID(FB17AC));
    _byte_array_t* const  me = _object(&object_, UID(ED46D4));

    ByteArray_clear(object_);

    me->size          = size_in_bytes_;
    me->mem           = CAST(uint8_t*, MALLOC(size_in_bytes_));
    me->pos           = 0;
    me->is_compressed = compressed_;

    MEMCPY(me->mem, bytes_, size_in_bytes_);

    RETURN(NIL);
} /* ByteArray_copyBytes */


/* Sets all bytes in the memory block to the specified value.                 */
PUBLIC void  ByteArray_fill(                                               /*M*/
    byte_array_t   object_,                                                /*-*/
    const uint8_t  value_ ) {                                              /*-*/
    GO                                                            (UID(FDFA42));
    _byte_array_t* const  me = _object(&object_, UID(E8FD5D));
    MEMSET(me->mem, value_, me->size);
    RETURN(NIL);
} /* ByteArray_fill */


PUBLIC uint8_t*  ByteArray_detachBuffer( byte_array_t  object_ ) {         /*M*/
    GO                                                            (UID(FB41D4));
    _byte_array_t* const  me = _object(&object_, UID(EE59B2));

    uint8_t* const  ret = me->mem;

    me->mem           = NULL;
    me->size          = 0;
    me->pos           = 0;
    me->is_compressed = false;

    RETURN(ret);
} /* ByteArray_detachBuffer */


PUBLIC bool  ByteArray_goBegin( byte_array_t  object_ ) {                  /*M*/
    GO                                                            (UID(FCAC83));
    _byte_array_t* const  me = _object(&object_, UID(E49036));
    me->pos = 0;
    RETURN(true);
} /* ByteArray_goBegin */


PUBLIC bool  ByteArray_goEnd( byte_array_t  object_ ) {                    /*M*/
    GO                                                            (UID(F5D647));
    _byte_array_t* const  me = _object(&object_, UID(EFBC3A));

    if (me->size == 0) {
        me->pos = 0;
    } else {
        me->pos = me->size - 1;
    }
    RETURN(true);
} /* ByteArray_goEnd */


PUBLIC bool  ByteArray_goBack(                                             /*M*/
    byte_array_t  object_,                                                 /*-*/
    const size_t  count_ ) {                                               /*-*/
    GO                                                            (UID(F015BC));
    _byte_array_t* const  me = _object(&object_, UID(E62ADC));

    if (me->pos <= count_) {
        DEBUG_WARN(_T("Invalid position."), UID(E09C7B));
        RETURN(false);
    }

    me->pos -= count_;

    RETURN(true);
} /* ByteArray_goBack */


PUBLIC bool  ByteArray_goForward(                                          /*M*/
    byte_array_t  object_,                                                 /*-*/
    const size_t  count_ ) {                                               /*-*/
    GO                                                            (UID(F40646));
    _byte_array_t* const  me = _object(&object_, UID(E3FE17));

    if (me->pos + count_ >= me->size) {
        DEBUG_WARN(_T("Invalid position."), UID(ED14F5));
        RETURN(false);
    }

    me->pos += count_;

    RETURN(true);
} /* ByteArray_goForward */


PUBLIC bool  ByteArray_writeInt(                                           /*M*/
    byte_array_t  object_,                                                 /*-*/
    const int     value_ ) {                                               /*-*/
    GO                                                            (UID(F7E8E6));
    _byte_array_t* const  me = _object(&object_, UID(E82483));

    if ((me->pos + sizeof(int)) > me->size) {
        RETURN(false);
    }

    MEMCPY(me->mem + me->pos, &value_, sizeof(int));
    me->pos += sizeof(int);

    RETURN(true);
} /* ByteArray_writeInt */


/*
    byte_1_out_ = NULL,
    byte_2_out_ = NULL,
    byte_3_out_ = NULL,
    byte_4_out_ = NULL
*/
PUBLIC uint32_t  ByteArray_readUnsigned(                                   /*M*/
    byte_array_t  object_,                                                 /*-*/
    const size_t  bytes_,                                                  /*-*/
    uint8_t*      byte_1_out_,                                             /*-*/
    uint8_t*      byte_2_out_,                                             /*-*/
    uint8_t*      byte_3_out_,                                             /*-*/
    uint8_t*      byte_4_out_ ) {                                          /*-*/
    GO                                                            (UID(F937A0));
    _byte_array_t* const  me = _object(&object_, UID(EB02FF));

    if (bytes_ < 1 || bytes_ > 4) {
        DEBUG_WARN(_T("Invalid bytes_ size."),     UID(EF4306));
        RETURN(0);
    }

    if (me->pos + bytes_ > me->size) {
        DEBUG_WARN(_T("Read past end of buffer."), UID(E1101F));
        RETURN(0);
    }

    if (byte_2_out_ != NULL && bytes_ < 2) {
        DEBUG_WARN(_T("Invalid arguments."),       UID(E22137));
        RETURN(0);
    }

    if (byte_3_out_ != NULL && bytes_ < 3) {
        DEBUG_WARN(_T("Invalid arguments."),       UID(E01430));
        RETURN(0);
    }

    if (byte_4_out_ != NULL && bytes_ < 4) {
        DEBUG_WARN(_T("Invalid arguments."),       UID(E0D005));
        RETURN(0);

    } else {
        uint32_t  ret   = 0;
        uint32_t  power = 1;
        size_t    i     = 0;

        for (i = 1; i <= bytes_; i++) {
            const uint8_t  val = *(me->mem + me->pos + bytes_ - i);

            switch (i) {
                case  1:
                    if (byte_1_out_ != NULL) {
                        *byte_1_out_ = val;
                    }
                    break;

                case  2:
                    if (byte_2_out_ != NULL) {
                        *byte_2_out_ = val;
                    }
                    break;

                case  3:
                    if (byte_3_out_ != NULL) {
                        *byte_3_out_ = val;
                    }
                    break;

                case  4:
                    if (byte_4_out_ != NULL) {
                        *byte_4_out_ = val;
                    }
                    break;

                default:
                    DEBUG_WARN(_T("Invalid arguments."), UID(E01349));
            }
            ret += (val * power);
            power *= 256;
        }
        me->pos += bytes_;
        RETURN(ret);
    }
} /* ByteArray_readUnsigned */


PUBLIC uint32_t  ByteArray_readUnsignedVariable(                           /*M*/
    byte_array_t  object_,                                                 /*-*/
    size_t*       length_in_bytes_out_ ) {                                 /*-*/
    GO                                                            (UID(F35620));
    _byte_array_t* const  me = _object(&object_, UID(E7ED68));

    size_t    i     = 0;
    size_t    len   = 0;
    uint8_t   val   = 0;
    uint32_t  power = 0;
    uint32_t  ret   = 0;

    if (length_in_bytes_out_) {
        *length_in_bytes_out_ = 0;
    }

    /* determine the length of the variable-length number */
    /* 4 is the maximum length of variable-length numbers */
    for (i = 0; i < 4; i++) {
        /* warn if the variable-length number exceeds the end of buffer */
        if (me->pos + i > me->size) {
            DEBUG_WARN(_T("Read past end of buffer."), UID(E7052D));
            RETURN(0);
        }

        val = *(me->mem + me->pos + i);
        len++;

        if (!(val & 0x80)) {
            break;
        }
    }

    /* make sure the length does not exceed 4 bytes */
    if (len == 4 && !(*(me->mem + me->pos + 4) & 0x80)) {
        DEBUG_WARN(_T("Variable-length longer than 4 bytes."), UID(E9EFB5));
        RETURN(0);
    }

    power = 1;

    for (i = 1; i <= len; i++) {
        /* only 7 bits of the byte store the value */
        const size_t  num = *(me->mem + me->pos + len - i) & 0x7F;
        ret += (num * power);
        power *= 128;
    }

    me->pos += len;

    if (length_in_bytes_out_) {
        *length_in_bytes_out_ = len;
    }
    RETURN(ret);
} /* ByteArray_readUnsignedVariable */


PUBLIC chars_t  ByteArray_readAsciiString(                                 /*M*/
    byte_array_t  object_,                                                 /*-*/
    const size_t  count_ ) {                                               /*-*/
    GO                                                            (UID(F9AB18));
    _byte_array_t* const  me = _object(&object_, UID(E3D264));

    char_t*  new_buf = NULL;
    size_t   i       = 0;

    if (count_ == 0) {
        RETURN(NULL);
    }

    /* warn if the length to read exceeds the end of buffer */
    if (me->pos + count_ > me->size) {
        DEBUG_WARN(_T("Read past end of buffer."), UID(EFC83E));
        RETURN(NULL);
    }

    /* release buffer, if previously allocated */
    freeT(&me->temp_chars);

    /* allocate a new buffer (+ 1 is for \0) */
    new_buf = CAST(char_t*, MALLOC((count_ + 1) * sizeof(char_t)));

    /* copy ASCII characters to new buffer */
    for (i = 0; i < count_; i++) {
        *(new_buf + i) = *(me->mem + me->pos + i);
    }
    *(new_buf + count_) = '\0';

    /* store buffer address and advance current position */
    me->temp_chars = new_buf;
    me->pos += count_;

    {
        chars_t  ret = me->temp_chars;
        RETURN(ret);
    }
} /* ByteArray_readAsciiString */


PUBLIC bool  ByteArray_writeUnsignedInt(                                   /*M*/
    byte_array_t    object_,                                               /*-*/
    const uint32_t  value_ ) {                                             /*-*/
    GO                                                            (UID(F948AF));
    _byte_array_t* const  me = _object(&object_, UID(E35F18));

    if ((me->pos + sizeof(uint32_t)) > me->size) {
        RETURN(false);
    }

    MEMCPY(me->mem + me->pos, &value_, sizeof(uint32_t));
    me->pos += sizeof(uint32_t);

    RETURN(true);
} /* ByteArray_writeUnsignedInt */


PUBLIC bool  ByteArray_writeString(                                        /*M*/
    byte_array_t  object_,                                                 /*-*/
    chars_t       text_,                                                   /*-*/
    const size_t  max_len_ ) {                                             /*-*/
    GO                                                            (UID(F8D227));
    _byte_array_t* const  me = _object(&object_, UID(E79A2E));

    const size_t  size = LESSER(STRLEN_T(text_), max_len_) * sizeof(char_t);

    if ((me->pos + size + 1) > me->size) {
        RETURN(false);
    }

    MEMCPY(me->mem + me->pos, text_, size);
    *(me->mem + size + 1) = '\0';
    me->pos += (size + 1);

    RETURN(true);
} /* ByteArray_writeString */


PUBLIC chars_t  ByteArray_getHexString(                                    /*M*/
    byte_array_t  object_,                                                 /*-*/
    const size_t  bytes_,                                                  /*-*/
    const long    offset_ ) {                                              /*-*/
    GO                                                            (UID(FBF122));
    _byte_array_t* const  me = _object(&object_, UID(E92464));

    size_t  pos = me->pos;

    if (bytes_ == 0) {
        RETURN(NULL);
    }

    /* warn if a negative offset is out of range */
    if (offset_ < 0 && CAST(size_t, -offset_) > pos) {
        DEBUG_WARN(_T("Invalid offset."), UID(ECD1E4));
        RETURN(NULL);
    }

    /* adjust reading position by offset */
    if (offset_ < 0) {
        pos -= CAST(size_t, -offset_);
    } else {
        pos += CAST(size_t, offset_);
    }

    /* warn if the length to read exceeds the end of buffer */
    if (pos + bytes_ > me->size) {
        DEBUG_WARN(_T("Read past end of buffer."), UID(EFF4A3));
        RETURN(NULL);
    }

    /* release buffer, if previously allocated */
    freeT(&me->temp_chars);

    {
        /* allocate a new buffer */
        char_t*  new_buf =
            CAST(char_t*, MALLOC((bytes_ * 3 + 1) * sizeof(char_t)));
        /*                                     ^ for \0 */
        char_t*  buf     = new_buf;

        {
            /* copy bytes as hex characters in buffer */
            size_t  i = 0;
            for (i = 0; i < bytes_; i++) {
                const uint8_t  val = *(me->mem + pos + i);
                SNPRINTF_T(buf, 4, _T("%02X "), val);
                buf += 3;
            }
        }
        *(buf - 1) = '\0';
        me->temp_chars = new_buf;
        RETURN(new_buf);
    }
} /* ByteArray_getHexString */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
