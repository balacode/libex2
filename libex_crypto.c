/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                      [libex_crypto.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_crypto_.h"
#if defined INCLUDED_LIBEX_CRYPTO_H

#include "libex_call_.h"
#include "libex_debug_.h"
#include "libex_error_.h"
#include "libex_.h"
#include "libex_type_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#if defined __GNUC__ && !defined __MINGW32__
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#endif
#if defined __clang__
#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#endif


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


static new_bytes_t  _simple_encrypt_or_decrypt(                            /*F*/
    const bytes_t  data_,                                                  /*-*/
    const bytes_t  key_,                                                   /*-*/
    const bool     encrypt_ ) {                                            /*-*/
    GO                                                            (UID(FE900A));
    new_bytes_t  ret      = { 0, NULL };
    size_t       data_pos = 0;
    size_t       key_pos  = 0;
    size_t       ret_pos  = 0;

    if (data_.size < 1) {
        WARN(_T("data_ is empty."), UID(E7D2B4));
        RETURN(ret);
    }

    if (key_.size < 1) {
        WARN(_T("key_ is empty."), UID(EB45C4));
        RETURN(ret);
    }

    ret.size = data_.size;
    ret.data = MALLOC(ret.size);

    for (data_pos = 0; data_pos < data_.size; data_pos++) {
        int        data_byte = data_.data[data_pos];
        const int  key_byte  = key_.data[key_pos];

        if (data_byte > 31) {  /* leave control characters unchanged */
            uint8_t  range = 0;
            uint8_t  shift = 0;
            uint8_t  min   = 0;
            uint8_t  max   = 0;

            if (data_byte >= 32 && data_byte <= 126) {
                min = 32;
                max = 126;
            }

            if (data_byte >= 127 && data_byte <= 255) {
                min = 127;
                max = 255;
            }

            range = max - min + 1;
            data_byte -= min;
            data_byte++;
            shift = key_byte % range;

            if (encrypt_) {
                data_byte += shift;

                if (data_byte > range) {
                    data_byte -= range;
                }
            } else {
                data_byte -= shift;

                if (data_byte < 1) {
                    data_byte += range;
                }
            }

            data_byte += min;
            data_byte--;
        }

        ret.data[ret_pos++] = CAST(uint8_t, data_byte);

        if (++key_pos >= key_.size) {
            key_pos = 0;
        }
    }
    RETURN(ret);
} /* _simple_encrypt_or_decrypt */


PUBLIC new_bytes_t  simple_encrypt(                                        /*F*/
    const bytes_t  data_,                                                  /*-*/
    const bytes_t  key_ ) {                                                /*-*/
    GO                                                            (UID(FBCDBD));
    const new_bytes_t  ret = _simple_encrypt_or_decrypt(data_, key_, true);
    RETURN(ret);
} /* simple_encrypt */


PUBLIC new_bytes_t  simple_decrypt(                                        /*F*/
    const bytes_t  data_,                                                  /*-*/
    const bytes_t  key_ ) {                                                /*-*/
    GO                                                            (UID(F75D5B));
    const new_bytes_t  ret = _simple_encrypt_or_decrypt(data_, key_, false);
    RETURN(ret);
} /* simple_decrypt */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
