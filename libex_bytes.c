/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_bytes.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_bytes_.h"
#if defined INCLUDED_LIBEX_BYTES_H

#include <stdio.h>   /* for printf()                     */
#include <stdlib.h>  /* for rand(), srand()              */
#include <string.h>  /* for memset()                     */
#include <wchar.h>   /* for swprintf() wcscat() wcslen() */

#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4820)  /* W:L4 'N' bytes padding added after 'NAME'  */
#endif
#include <time.h>    /* for time*()  */
#if defined _MSC_VER
#pragma warning (pop)
#endif

#if defined USE_ZLIB_COMPRESSION
#include "../../clibs/lib_zlib/zlib.h"
#endif

#include "libex_call_.h"
#include "libex_debug.h"
#include "libex_error_.h"
#include "libex_libc_.h"
#include "libex_macro_.h"
#include "libex_.h"
#include "libex_type_.h"


#if defined __cplusplus_cli
#pragma unmanaged
#endif

#if defined _MSC_VER
#pragma warning (disable:4710)  /* W:L4 function not inlined                  */
#endif


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


/* -------------------------------------------------------------------------- */
/* Functions: Private                                                         */


#if defined __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#endif


static new_bytes_t  _bytes_describe(                                       /*F*/
    const uint32_t  char_size_,                                            /*-*/
    const bytes_t   bytes_ ) {                                             /*-*/
    GO                                                            (UID(F05061));
#define MAX_VAL_LEN  20

    new_bytes_t  ret  = { 0, NULL };
    int          pass = 0;
    uint32_t     len  = 0;

    /* 1 for char, 2 for wchar_t on Windows, or 4 for wchar_t on Linux */
    ASSERT(char_size_ == 1 || char_size_ == 2 || char_size_ == 4, UID(EAFBF4));

    for (pass = 0; pass < 2; pass++) {
        const uint8_t*  rd  = bytes_.data;
        uint8_t*        wr  = NULL;
        uint8_t*        val = CAST(uint8_t*, MALLOC(MAX_VAL_LEN * 4));
        uint32_t        i   = 0;

        if (pass == 0) {
            len += (MAX_VAL_LEN * 4);
        } else {
            ret.size = len * char_size_;
            ret.data = wr = CAST(uint8_t*, MALLOC(ret.size));

            MEMSET(wr,  0x00, ret.size);
            MEMSET(val, 0x00, MAX_VAL_LEN * 4);

            if (char_size_ == 1) {
                char*  str = CAST(char*, val);
                SNPRINTF(str, MAX_VAL_LEN,
                         "%u bytes: ", CAST(unsigned int, len));
                MEMSET(wr, 0x00, MAX_VAL_LEN);
                STRCAT_S(CAST(char*, wr), MAX_VAL_LEN, str);
                wr += STRLEN(str);
            } else {
                wchar_t*  str = CAST(wchar_t*, val);
                SWPRINTF_S(str, MAX_VAL_LEN, L"%d bytes: ", len);
                WCSCAT_S(CAST(wchar_t*, wr), MAX_VAL_LEN, str);
                wr += (WCSLEN(str) * char_size_);
            }
        }

        for (i = 0; i < bytes_.size; i++) {
            uint32_t  byte = *rd++;

            if (pass == 0) {
                len += (byte < 32 || byte > 127) ? 9 : 1;
            } else {
                if (byte < 32 || byte > 127) {
                    /* write byte value: [256/FFh] */
                    MEMSET(val, 0x00, MAX_VAL_LEN * 4);

                    if (char_size_ == 1) {
                        char*  str = CAST(char*, val);
                        SNPRINTF(str, MAX_VAL_LEN, "[%d/%02Xh]", byte, byte);
                        MEMSET(wr, 0x00, MAX_VAL_LEN);
                        STRCAT_S(CAST(char*, wr), MAX_VAL_LEN, str);
                        wr += STRLEN(str);
                    } else {
                        wchar_t*  str = CAST(wchar_t*, val);
                        SWPRINTF_S(str, MAX_VAL_LEN,
                                   L"[%d/%02Xh]", byte, byte);
                        WCSCAT_S(CAST(wchar_t*, wr), MAX_VAL_LEN, str);
                        wr += WCSLEN(str) * char_size_;
                    }
                } else {
                    CHAR_PUT(wr, byte);
                    wr += char_size_;
                }
            }
        }

        if (pass == 1) {
            CHAR_PUT(wr, '\0');
        }

        FREE(val);
    }
    RETURN(ret);
} /* _bytes_describe */


#if defined __GNUC__
#pragma GCC diagnostic pop
#endif


/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */


PUBLIC new_bytes_t  Bytes_init(                                            /*C*/
    const uint8_t* const  bytes_,                                          /*-*/
    const uint32_t        size_ ) {                                        /*-*/
    GO                                                            (UID(FC433D));
    new_bytes_t  ret = { 0, NULL };

    ASSERT(size_ > 0, UID(E5C203));

    if (bytes_ == NULL || size_ < 1) {
        RETURN(ret);
    }

    ret.size = size_;
    ret.data = CAST(uint8_t*, MALLOC(size_));
    ASSERT(ret.data != NULL, UID(ED6C16));

    if (ret.data == NULL) {
        ERR(_T("MALLOC() failure."), UID(EB2539));
        ret.size = 0;

    } else if (bytes_ != NULL) {
        MEMCPY(ret.data, bytes_, size_);
    } else {
        MEMSET(ret.data, 0x00, size_);
    }
    RETURN(ret);
} /* Bytes_init */


PUBLIC new_bytes_t  Bytes_fromNewChars( new_chars_t  assign_chars_ ) {     /*C*/
    GO                                                            (UID(F482C6));
    new_bytes_t  ret = { 0, NULL };

    if (!IS_BLANK(assign_chars_)) {
        ret.size = STRLEN_T(assign_chars_) * sizeof(char_t);
        ret.data = CAST(uint8_t*, assign_chars_);
    }
    RETURN(ret);
} /* Bytes_fromNewChars */


/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */


PUBLIC bool  Bytes_free( bytes_t*  bytes_ ) {                              /*D*/
    GO                                                            (UID(D2BB7B));
    bool  ret = false;

    if (bytes_->data != NULL) {
        ASSERT(bytes_->size > 0, UID(EF70EE));
        ret = true;
        FREE(bytes_->data);
    } else {
        ASSERT(bytes_->size == 0, UID(E1DB03));
        ret = false;
    }

    bytes_->size = 0;
    bytes_->data = NULL;

    RETURN(ret);
} /* Bytes_free */


/* -------------------------------------------------------------------------- */
/* Methods                                                                    */


PUBLIC new_bchars_t  Bytes_describe( const bytes_t  bytes_ ) {             /*P*/
    GO                                                            (UID(FCD1FB));
    new_bytes_t   bytes = _bytes_describe(sizeof(char), bytes_);
    new_bchars_t  ret   = CAST(new_bchars_t, bytes.data);
    RETURN(ret);
} /* Bytes_describe */


PUBLIC new_wchars_t  Bytes_describeW( const bytes_t  bytes_ ) {            /*P*/
    GO                                                            (UID(F17C81));
    new_bytes_t   bytes = _bytes_describe(sizeof(wchar_t), bytes_);
    new_wchars_t  ret   = CAST(new_wchars_t, bytes.data);
    RETURN(ret);
} /* Bytes_describeW */


PUBLIC bool  Bytes_equals(                                                 /*P*/
    const bytes_t  bytes_1_,                                               /*-*/
    const bytes_t  bytes_2_ ) {                                            /*-*/
    GO                                                            (UID(F37E41));
    bool  ret = false;

    if (bytes_1_.size != bytes_2_.size ||
        (bytes_1_.data == NULL && bytes_2_.data != NULL) ||
        (bytes_1_.data != NULL && bytes_2_.data == NULL)) {
        ret = false;
    } else {
        uint32_t  size = bytes_1_.size;
#if 111
        ret = C_BOOL(MEMCMP(bytes_1_.data, bytes_2_.data, size) == 0);
#else                                                                  /* 111 */
        const uint8_t*  bytes_1 = CAST(const uint8_t*, bytes_1_.data);
        const uint8_t*  bytes_2 = CAST(const uint8_t*, bytes_2_.data);
        ret = true;
        while (size--) {
            if (*bytes_1++ != *bytes_2++) {
                ret = false;
                break;
            }
        }
#endif                                                                /* !111 */
    }
    RETURN(ret);
} /* Bytes_equals */


PUBLIC new_bytes_t  Bytes_join(                                            /*M*/
    const bytes_t  bytes_1_,                                               /*-*/
    const bytes_t  bytes_2_ ) {                                            /*-*/
    GO                                                            (UID(FEAF09));
    bytes_t  ret = { 0, NULL };

    ret.size = bytes_1_.size + bytes_2_.size;
    ret.data = CAST(uint8_t*, MALLOC(ret.size));

    ASSERT(ret.data != NULL, UID(E72A00));

    MEMCPY(ret.data, bytes_1_.data, bytes_1_.size);
    MEMCPY(ret.data + bytes_1_.size, bytes_2_.data, bytes_2_.size);

    RETURN(ret);
} /* Bytes_join */


PUBLIC bool  Bytes_resize(                                                 /*M*/
    bytes_t*        bytes_,                                                /*-*/
    const uint32_t  new_size_ ) {                                          /*-*/
    GO                                                            (UID(FDB51B));
    bool  ret = false;
    if (new_size_ > 0) {
        uint8_t*  move_mem = CAST(uint8_t*, REALLOC(bytes_->data, new_size_));
        if (move_mem != NULL) {
            bytes_->size = new_size_;
            bytes_->data = move_mem;
            ret          = true;
        }
    } else {
        Bytes_free(bytes_);
        if (bytes_->size == 0 && bytes_->data == NULL) {
            ret = true;
        }
    }
    RETURN(ret);
} /* Bytes_resize */


/* -------------------------------------------------------------------------- */
/* Functions: Byte Pointers                                                   */


/* {7FD63E38-AE17-4928-82A8-60555BF345E4} */
#if defined USE_ZLIB_COMPRESSION
static const uint8_t  COMPRESSED_SIGNATURE[] = {
    0x7F, 0xD6, 0x3E, 0x38, 0xAE, 0x17, 0x49, 0x28,
    0x82, 0xA8, 0x60, 0x55, 0x5B, 0xF3, 0x45, 0xE4
};
#endif


/*  byte_random_positions() Creates a byte array of positions              */
/*  in random order for use by bytes_transpose()                           */
/*                                                                            */
/*  positions_out_: Pointer to the byte buffer to be filled with positions.   */
/*                  The routine manipulates this buffer directly.             */
/*                  The buffer will be filled with all values                 */
/*                  from 0 to length_ - 1 in random order.                    */
/*                                                                            */
/*  length_:        A positive integer in the range 1 to 256, specifying      */
/*                  the number of positions to generate.                      */
/*                                                                            */
/*  return value:   returns true on success, or false on any error.           */
/*                  Note that the routine modifies positions_out_ directly.   */
/*                                                                            */
/*  version:        Created on 11-Mar-2004 12:24pm                            */

PUBLIC bool  byte_random_positions(                                        /*F*/
    uint8_t*   positions_out_,                                             /*-*/
    const int  length_ ) {                                                 /*-*/
    GO                                                            (UID(F4449B));
    uint8_t*  byte      = positions_out_;
    bool      ascending = false;
    int       loc       = 0;
    int       i         = 0;

    VERIFY(positions_out_ != NULL,         UID(E73773));
    VERIFY(length_ >= 1 && length_ <= 256, UID(EE0ECC));

    /* declare and initialize variables */

    SRAND(CAST(uint32_t, TIME(0)));

    /* set all elements to zero */
    for (i = 0; i < length_; i++) {
        byte[i] = 0;
    }

    for (i = 1; i < length_; i++) {
        /* get next random position within accepted range */
        loc = RAND() % length_;
        VERIFY(loc >= 0 && loc < length_, UID(EA9A35));

        /* note that if this position is already occupied  */
        /* by a non-zero value, search for a free position */
        /* in either ascending or descending direction     */

        ascending = C_BOOL(!ascending);  /* toggle ascending search flag */

        if (ascending) {  /* look for next available place in ascending order */
            while (byte[loc] != 0) {
                if (++loc == length_) {
                    loc = 0;
                }
            }
        } else { /* look for next available place in descending order */
            while (byte[loc] != 0) {
                if (--loc < 0) {
                    loc = length_ - 1;
                }
            }
        }
        byte[loc] = CAST(uint8_t, i);
    }
    RETURN(true);
} /* byte_random_positions */


#if defined USE_ZLIB_COMPRESSION
PUBLIC uint32_t  bytes_compress(                                           /*F*/
    void*           bytes_,                                                /*-*/
    const uint32_t  size_in_bytes_ ) {                                     /*-*/
    GO                                                            (UID(F3EE53));
    uint32_t  ret = 0;

    /* exit immediately if the data is too short  to be compressed */
    if (size_in_bytes_ <= COMPRESSED_HEADER_SIZE) {
        ret = size_in_bytes_;

        /* if the data is already compressed, log a warning and exit */
    } else if (0 == MEMCMP(bytes_, COMPRESSED_SIGNATURE,
                           sizeof(COMPRESSED_SIGNATURE))) {

        WARN(_T("compress() : compressed already"), UID(ED45EE));
        ret = size_in_bytes_;
    } else {
        /* allocate temporary buffer with space for data size */
        uLongf  comp_size = compressBound(size_in_bytes_);
        uint8_t*  comp = CAST(uint8_t*,
                              MALLOC(COMPRESSED_HEADER_SIZE + comp_size));
        uint8_t*  comp_buf = comp;

        /* write the compression signature, to mark compressed data */
        MEMCPY(comp_buf, COMPRESSED_SIGNATURE, sizeof(COMPRESSED_SIGNATURE));
        comp_buf += sizeof(COMPRESSED_SIGNATURE);

        {
            /* write the uncompressed data size, needed when uncompressing: */
            const uint32_t  size = size_in_bytes_;
            MEMCPY(comp_buf, &size, sizeof(uint32_t));
            comp_buf += sizeof(uint32_t);
        }

        {
            /* store and skip location where compressed size will be stored */
            uint32_t*  write_comp_size = CAST(uint32_t*, comp_buf);
            comp_buf += sizeof(uint32_t);
            {
                /* compress data to the temporary buffer */
                const int  result = compress2(
                                        comp_buf, &comp_size,
                                        CAST(const Bytef*, bytes_),
                                        size_in_bytes_, Z_BEST_COMPRESSION);

                if (result != Z_OK) {
                    chars_t  err = NULL;

#if LX_PLATFORM_LINUX
                    IMPLEMENT_LINUX();  /* TODO: 'err' is set but unused */
                    UNUSED(err);
#endif                                                   /* LX_PLATFORM_LINUX */

                    switch (result) {
                            CASE(Z_BUF_ERROR,    err = _T("Z_BUF_ERROR"));
                            CASE(Z_MEM_ERROR,    err = _T("Z_MEM_ERROR"));
                            CASE(Z_STREAM_ERROR, err = _T("Z_STREAM_ERROR"));
                        default:
                            err = _T("<other error>");
                    }

                    WARN(err, UID(E8236E));
                    FREE(comp);
                    RETURN(size_in_bytes_);
                }

                /* store the final compressed size in the buffer */
                *write_comp_size = comp_size;
                {
                    /* copy the compressed data back to the supplied buffer, */
                    /* provided the compressed data size (including the      */
                    /* header) is less than the original size_in_bytes_      */
                    ret = COMPRESSED_HEADER_SIZE + comp_size;
                    if (ret <= size_in_bytes_) {
                        MEMCPY(bytes_, comp, ret);
                    } else {
                        ret = size_in_bytes_;
                    }
                    FREE(comp);
                }
            }
        }
    }
    RETURN(ret);  /* return compressed size */
} /* bytes_compress */
#endif                                                /* USE_ZLIB_COMPRESSION */


#if defined USE_ZLIB_COMPRESSION
PUBLIC uint32_t  bytes_compressed_size( void*  bytes_ ) {                  /*F*/
    GO                                                            (UID(F3F037));
    uint32_t  ret = 0;

    if (0 == MEMCMP(bytes_, COMPRESSED_SIGNATURE,
                    sizeof(COMPRESSED_SIGNATURE))) {

        ret = *CAST(uint32_t*, CAST(uint8_t*, bytes_)
                    + sizeof(COMPRESSED_SIGNATURE) + sizeof(uint32_t));
    }
    RETURN(ret);
} /* bytes_compressed_size */
#endif                                                /* USE_ZLIB_COMPRESSION */


/* Transposes bytes in a buffer (256 bytes max),                              */
/* according to a list of positions                                           */
/*                                                                            */
/* bytes_out_:      Pointer to the byte buffer to be transposed.              */
/*                  The routine manipulates this buffer directly.             */
/*                  To pass character strings, etc. cast them to (uint8_t*)   */
/*                                                                            */
/* positions_:      Pointer to a byte buffer with new byte positions,         */
/*                  (0-based) No position can be repeated or omitted          */
/*                  E.g. to transpose a 4-byte buffer, positions_             */
/*                  should be like {2, 0, 1, 3} or {3, 1, 0, 2}               */
/*                                                                            */
/* length_:         A positive integer in the range 1 to 256, specifying      */
/*                  the number of bytes to transpose.                         */
/*                                                                            */
/* return value:    Returns true on success, or false on any error.           */
/*                  Note that the routine modifies bytes_out_ directly.       */
PUBLIC bool  bytes_transpose(                                              /*F*/
    uint8_t*        bytes_out_,                                            /*-*/
    const uint8_t*  positions_,                                            /*-*/
    const int       length_ ) {                                            /*-*/
    GO                                                            (UID(F2DC95));
    int      i = 0;
    uint8_t  b = 0;

    VERIFY(bytes_out_ != NULL,             UID(EEAE37));
    VERIFY(positions_ != NULL,             UID(E42339));
    VERIFY(length_ >= 1 && length_ <= 256, UID(E8D250));

    {
        /* verify that positions_ holds a list of all positions_  */
        /* (otherwise some position has been omitted or repeated) */
        bool  exists = false;

        for (b = 0; b < length_; b++) {
            exists = false;

            for (i = 0; i < length_; i++) {
                if (positions_[i] == b) {
                    exists = true;
                    break;
                }
            }

            if (!exists) {
                ERR(_T("positions_ is invalid"), UID(E21699));
                RETURN(false);
            }
        }
    }

    {
        /* create a temporary result buffer (always uses maximum length) */
        uint8_t  buf[256];

        /* fill result buffer copying values from source to new positions_ */
        uint8_t  byte_pos = 0;
        for (i = 0; i < length_; i++) {
            byte_pos = positions_[i];
            buf[byte_pos] = bytes_out_[i];
        }

        /* copy temporary buffer back to source, thereby transposing it */
        for (i = 0; i < length_; i++) {
            bytes_out_[i] = buf[i];
        }
    }
    RETURN(true);
} /* bytes_transpose */


#if defined USE_ZLIB_COMPRESSION
PUBLIC uint32_t  bytes_uncompress(                                         /*F*/
    void*           bytes_,                                                /*-*/
    const uint32_t  size_in_bytes_ ) {                                     /*-*/
    GO                                                            (UID(F22B51));
    uint8_t*  comp_buf    = CAST(uint8_t*, bytes_);
    uLongf    uncomp_size = 0;
    uint32_t  comp_size   = 0;
    uint8_t*  uncomp_buf  = NULL;

    /* exit immediately if the buffer is too short to be uncompressed */
    if (size_in_bytes_ <= COMPRESSED_HEADER_SIZE) {
        RETURN(0);
    }

    /* if the buffer is not compressed, log a warning and return 0 */
    if (0 != MEMCMP(comp_buf, COMPRESSED_SIGNATURE,
                    sizeof(COMPRESSED_SIGNATURE))) {
        WARN(_T("uncompress(): no compressed data"), UID(EF1435));
        RETURN(0);
    } else {
        const uint32_t  sign_size = sizeof(COMPRESSED_SIGNATURE);
        comp_buf += sign_size;
    }

    /* read the uncompressed size from the buffer */
    uncomp_size = *CAST(uint32_t*, comp_buf);

    /* if the buffer is too small, log a warning and return 0 */
    if (uncomp_size > size_in_bytes_) {
        WARN(_T("uncompress(): buffer too small"), UID(E4D4D3));
        RETURN(0);
    }

    comp_buf += sizeof(uint32_t);

    /* read the compressed size from the buffer */
    comp_size = *CAST(uint32_t*, comp_buf);

    /* if the buffer is too small, log a warning and return 0 */
    if (comp_size > uncomp_size || comp_size > size_in_bytes_) {
        WARN(_T("uncompress(): invalid compressed size"), UID(E56862));
        RETURN(0);
    }

    comp_buf += sizeof(uint32_t);

    /* allocate temporary buffer for uncompressed data */
    uncomp_buf = CAST(uint8_t*, MALLOC(uncomp_size));

    {
        /* uncompress the buffer: */
        const int  result = uncompress(uncomp_buf, &uncomp_size, comp_buf,
                                       comp_size);
        if (result != Z_OK) {
            uint32_t  uid = 0;

            /* there was not enough memory */
            if (result == Z_MEM_ERROR) {
                uid = UID(EB889A);

                /* there not enough room in the output buffer */
            } else if (result == Z_BUF_ERROR) {
                uid = UID(EE16E0);

                /* the input data is corrupted or incomplete */
            } else if (result == Z_DATA_ERROR) {
                uid = UID(EB0518);
            }

            WARN(_T("uncompress(): failed uncompressing."), uid);
            FREE(uncomp_buf);

#if defined CALL_TRACE && CALL_TRACE == 2
            src_uid = uid;
#endif
            RETURN(0);
        }
    }

    /* if the buffer is too small, log a warning and return 0 */
    if (uncomp_size > size_in_bytes_) {
        WARN(_T("uncompress(): buffer too small"), UID(EC38B1));
        FREE(uncomp_buf);
        RETURN(0);
    }

    /* copy the uncompressed data back to this buffer */
    MEMCPY(bytes_, uncomp_buf, uncomp_size);

    /* free the temporary buffer and return uncompressed data size */
    FREE(uncomp_buf);

    RETURN(uncomp_size);
} /* bytes_uncompress */
#endif                                                /* USE_ZLIB_COMPRESSION */


#if defined USE_ZLIB_COMPRESSION
PUBLIC uint32_t  bytes_uncompressed_size( void*  bytes_ ) {                /*F*/
    GO                                                            (UID(F03CB9));
    uint32_t  ret = 0;

    if (0 == MEMCMP(bytes_, COMPRESSED_SIGNATURE,
                    sizeof(COMPRESSED_SIGNATURE))) {

        ret = *CAST(uint32_t*, CAST(uint8_t*, bytes_)
                    + sizeof(COMPRESSED_SIGNATURE));
    }
    RETURN(ret);
} /* bytes_uncompressed_size */
#endif                                                /* USE_ZLIB_COMPRESSION */


PUBLIC uint32_t  checksum(                                                 /*F*/
    const uint8_t*  data_,                                                 /*-*/
    const uint32_t  length_in_bytes_ ) {                                   /*-*/
    GO                                                            (UID(F3857A));
    /* uses the Adler-32 checksum algorithm         */
    /* (see http:/ /en.wikipedia.org/wiki/Adler-32) */

    const uint32_t  mod    = 65521;
    uint32_t        a      = 1;
    uint32_t        b      = 0;
    size_t          remain = length_in_bytes_;

    while (remain > 0) {
        uint32_t  len = LESSER(remain, 5550);
        remain -= len;
        do {
            a += *data_++;
            b += a;
        } while (--len);
        a %= mod;
        b %= mod;
    }
    {
        const uint32_t  ret = ((b << 16) | a);
        RETURN(ret);
    }
} /* checksum */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
