/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                   [libex_functions.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_functions_.h"
#if defined INCLUDED_LIBEX_FUNCTIONS_H

#include <stdio.h>   /* for sprintf() */
#include <string.h>  /* for memset()  */

#include "libex_config_.h"

#include "libex_.h"
#include "libex_call_.h"
#include "libex_const_.h"
#include "libex_debug_.h"
#include "libex_error_.h"
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
#pragma warning (disable:4710)  /* W:L4 function not inlined                  */
#endif

#define BUF_SIZE  65

#define _FORMAT_GENERAL( ARG_NAME_, FORMAT_ )         \
    new_str_t  ret = S_reserve(BUF_SIZE);             \
    char_t     buf[BUF_SIZE];                         \
    CLEAR(buf);                                       \
    SNPRINTF_T(buf, BUF_SIZE, FORMAT_, ARG_NAME_);    \
    setInS(&ret, buf);                              /*#*/

#define _FORMAT_COMMA                                               \
    if (!IS_BLANK(delimiter_))                                      \
    {       delimitNumberInS(&ret, 0, 3, 3, 3, '.', ','); }  /*#*/


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


/* -------------------------------------------------------------------------- */
/* Conversion Functions:                                                      */


PUBLIC new_str_t  tu(                                                      /*F*/
    const unsigned long  value_,                                           /*-*/
    chars_t              format_,                                          /*-*/
    chars_t              delimiter_ ) {                                    /*-*/
    GO                                                            (UID(FF1864));
    _FORMAT_GENERAL(value_, _T("%0lu"));
    _FORMAT_COMMA;
    UNUSED(format_);
    RETURN(ret);
} /* tu */


PUBLIC new_str_t  byte_size_description(                                   /*F*/
    const size_t  size_in_bytes_,                                          /*-*/
    const bool    use_1024_multiple_ ) {                                   /*-*/
    GO                                                            (UID(F412A3));
    const double  mul    = use_1024_multiple_ ? 1024 : 1000;
    double        kilo   = mul;
    double        mega   = mul * kilo;
    double        giga   = mul * mega;
    double        tera   = mul * giga;
    double        size   = CAST(double, size_in_bytes_);
    chars_t       suffix = BLANK;
    new_str_t     ret    = { NULL };

    if (size_in_bytes_ < kilo) {
        suffix = (size_in_bytes_ == 1) ? _T(" byte") : _T(" bytes");

    } else if (size_in_bytes_ < mega) {
        size /= kilo;
        suffix = use_1024_multiple_ ? _T("KiB") : _T("KeyB");
    } else if (size_in_bytes_ < giga) {
        size /= mega;
        suffix = use_1024_multiple_ ? _T("MiB") : _T("MB");
    } else if (size_in_bytes_ < giga) {
        size /= giga;
        suffix = use_1024_multiple_ ? _T("GiB") : _T("GB");
    } else {
        size /= tera;
        suffix = use_1024_multiple_ ? _T("TiB") : _T("TB");
    }

    {
        new_chars_t  chars = formatT(_T("%0.1f %s"), size, suffix);
        ret = S_newT(chars);
    }
    RETURN(ret);
} /* byte_size_description */


#undef _FORMAT_GENERAL
#undef _FORMAT_COMMA


/* -------------------------------------------------------------------------- */
/* Other functions:                                                           */


PUBLIC bool  equals_float(                                                 /*F*/
    const float  value_1_,                                                 /*-*/
    const float  value_2_ ) {                                              /*-*/
    GO                                                            (UID(F545A0));
    const bool  ret = MEMCMP(&value_1_, &value_2_, sizeof(float)) == 0;
    RETURN(ret);
} /* equals_float */


PUBLIC bool  equals_double(                                                /*F*/
    const double  value_1_,                                                /*-*/
    const double  value_2_ ) {                                             /*-*/
    GO                                                            (UID(F0620A));
    const bool  ret = MEMCMP(&value_1_, &value_2_, sizeof(double)) == 0;
    RETURN(ret);
} /* equals_double */


PUBLIC new_str_t  old_decrypt(                                             /*F*/
    chars_t  text_,                                                        /*-*/
    chars_t  key_ ) {                                                      /*-*/
    GO                                                            (UID(F52449));
    const new_str_t  ret = old_encrypt(text_, key_, true);
    RETURN(ret);
} /* old_decrypt */


PUBLIC new_str_t  old_encrypt(                                             /*F*/
    chars_t     text_,                                                     /*-*/
    chars_t     key_,                                                      /*-*/
    const bool  decryption_ ) {                                            /*-*/
    GO                                                            (UID(F2A523));
    new_str_t  ret = { NULL };

    if (IS_BLANK(text_)) {
        WARN(_T("text_ is blank"), UID(E750E9));
        RETURN(ret);
    }

    if (IS_BLANK(key_)) {
        WARN(_T("key_ is blank"), UID(E5BD93));
        RETURN(ret);
    }

    {
        const int  text_len = CAST(int, STRLEN_T(text_));
        const int  key_len  = CAST(int, STRLEN_T(key_));
        int        key_loc  = 0;
        int        text_loc = 0;

        for (text_loc = 0; text_loc < text_len; text_loc++) {
            int        ch       = text_[text_loc];
            const int  key_char = key_[key_loc];

            if (ch > 31) {  /* leave control characters unchanged */
                int  range = 0;
                int  min   = 0;
                int  max   = 0;

                if (ch >= 32 && ch <= 126) {
                    min = 32;
                    max = 126;

                } else if (ch >= 127 && ch <= 255) {
                    min = 127;
                    max = 255;
                }

                range = max - min + 1;
                ch -= min;
                ch++;

                {
                    const int  shift = key_char % range;

                    if (decryption_) {
                        ch -= shift;
                        if (ch < 1) {
                            ch += range;
                        }
                    } else {
                        ch += shift;
                        if (ch > range) {
                            ch -= range;
                        }
                    }
                }
                ch += min;
                ch--;
            }

            addCharS(&ret, CAST(char, ch));

            if (++key_loc >= key_len) {
                key_loc = 0;
            }
        } /* for */
    }
    RETURN(ret);
} /* old_encrypt */


PUBLIC new_str_t  sql_statement(                                           /*F*/
    chars_t       sql_statements_,                                         /*-*/
    const size_t  index_1_ ) {                                             /*-*/
    GO                                                            (UID(FA3CE8));
    new_str_t     ret              = { NULL };
    new_str_t     list             = S_chars(sql_statements_);
    size_t        item             = 1;
    const size_t  len              = lengthS(list);
    size_t        loc              = 0;
    bool          in_brackets      = false;
    bool          in_double_quotes = false;
    bool          in_single_quotes = false;
    char_t        ch               = 0;

    VERIFY(index_1_ > 0, UID(E80FA4));

    for (loc = 0; loc < len; loc++) {
        ch = list.cs[CAST(int, loc)];

        if (in_single_quotes || in_double_quotes || in_brackets) {
            if (ch == '\'') {
                in_single_quotes = false;
            }
            if (ch == '"') {
                in_double_quotes = false;
            }
            if (ch == ']') {
                in_brackets = false;
            }
        } else {
            if (ch == '[') {
                in_brackets = true;
            }
            if (ch == '\'') {
                in_single_quotes = true;
            }
            if (ch == '"') {
                in_double_quotes = true;
            }
        }

        if (item == index_1_) {
            addCharS(&ret, ch);
        }

        if (ch == ';' &&
            (!in_single_quotes) && (!in_double_quotes) && (!in_brackets)) {
            item++;
        }

        if (item > index_1_) {
            break;
        }
    }
    trimIn1S(&ret);
    RETURN(ret);
} /* sql_statement */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
