/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                       [libex_stringc.c] [cat:strings] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_stringc_.h"
#if defined INCLUDED_LIBEX_STRINGC_H

#include "libex_config_.h"

#undef __STRICT_ANSI__

#include <ctype.h>   /* for tolower()                              */
#include <limits.h>  /* for UINT_MAX                               */
#include <math.h>    /* for floor()                                */
#include <stdarg.h>  /* for va_arg va_end va_list va_start         */
#include <stdio.h>   /* for printf(), sprintf()                    */
#include <stdlib.h>  /* for atof() mbstowcs() strtoul() wcstombs() */
#include <string.h>  /* for memset()                               */
#include <wchar.h>   /* for vswprintf() wcslen() wcsrtombs()       */

#if PLATFORM_WIN32
#include <tchar.h>  /* on Windows for strstr(), wcsstr() */
#endif

#include "libex_call_.h"
#include "libex_const_.h"
#include "libex_debug.h"
#include "libex_error_.h"
#include "libex_libc_.h"
#include "libex_macro_.h"
#include "libex_.h"
#include "libex_type.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#if defined __GNUC__ && !defined __MINGW32__
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#endif
#if defined __clang__
#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#endif
#if defined _MSC_VER
#pragma warning (disable:4189)  /* W:L4 local var is init but not referenced  */
#pragma warning (disable:4555)  /* W:L1 expression has no effect              */
#pragma warning (disable:4710)  /* W:L4 function not inlined                  */
#pragma warning (disable:4711)  /* W:L1 functn. selected for inline expansion */
#pragma warning (disable:4820)  /* W:L4 'N' bytes padding added after 'NAME'  */
#pragma warning (disable:4996)  /* W:L3 'function': may be unsafe/deprecated  */
#endif

#define _TYPE_STRING_MAIN  0xAA
#define _TYPE_STRING_EXTN  0xBB

/* -------------------------------------------------------------------------- */
NAMESPACE(c_)

bool  enable_chars_warnings = true;

/* -------------------------------------------------------------------------- */
/* Structures and Constants:                                                  */

typedef struct  _str_t {
    size_t  cap;                                                    /* _str_t */
    /* ^ stores the capacity of this string object                            */
    size_t  len;                                                    /* _str_t */
    /* ^ stores length of string, to avoid calculating every time             */
    void*  ext;                                                     /* _str_t */
    /* ^ pointer to re-allocated string extension                             */
    void*  cnv;                                                     /* _str_t */
    /* ^ pointer to a temporary buffer of wide or ANSI characters             */

#if defined DEBUG
    char*  debug_name;                                              /* _str_t */
    /* ^ specifies the file and line where a string was declared              */
    size_t  debug_id;                                               /* _str_t */
    /* ^ specifies the serial number of this string object                    */
#endif                                                               /* DEBUG */

    uint8_t  type;                                                  /* _str_t */
    /* ^ type of struct: must always be assigned _TYPE_STRING_MAIN            */
    /*   and must always be the last data item in the struct                  */
}
_str_t;


typedef struct  _ext_t {
    _str_t*  owner;                                                 /* _ext_t */
    uint8_t  type;                                                  /* _ext_t */
}
_ext_t;


/* -------------------------------------------------------------------------- */
/* Internal Functions: 1                                                      */


#define _warn( DETAIL_, SRC_UID_ )                   \
    if (enable_chars_warnings)                       \
    {       _warn_fn(DETAIL_, SRC_UID_, FN_NAME);    \
    }                                            /*#*/

static void  _warn_fn(                                                     /*F*/
    chars_t         detail_,                                               /*-*/
    const uint32_t  src_uid_,                                              /*-*/
    chars_t         func_name_ ) {                                         /*-*/
    GO                                                            (UID(F1899A));
    UNUSED(detail_);
    UNUSED(src_uid_);

    PRINTF_T(_T("\r\n") _T("%s() 0x%0xU warning: %s"), func_name_,
             CAST(uint32_t, src_uid_), detail_);

    /* WARN(detail_, src_uid_); */

    RETURN(NIL);
} /* _warn_fn */


/* -------------------------------------------------------------------------- */
/* Functions: Standard                                                        */


/* strstriT(): Pointer to first occurrence of a substring, ignoring case  */
PUBLIC char_t*  strstriT(                                                  /*F*/
    chars_t  main_,                                                        /*-*/
    chars_t  find_ ) {                                                     /*-*/
    GO                                                            (UID(FD5C1C));
    chars_t  str       = main_;
    chars_t  find      = find_;
    size_t   find_len  = 0;
    size_t   match_len = 0;

    if (main_ == NULL || find_ == NULL) {
        RETURN(NULL);
    }

    while ('\0' != *find++) { /* get length of find_ */
        find_len++;
    }

    if (find_len == 0) {
        RETURN(NULL);
    }

    find = find_;

    while ('\0' != *str) {
        if (TOLOWER_T(*str) == TOLOWER_T(*find)) {
            if (++match_len == find_len) {
                RETURN(CAST(char_t*, str - find_len + 1));
            }
            find++;
        } else if (0 < match_len) {
            match_len = 0;
            find = find_;
        }
        str++;
    }
    RETURN(NULL);
} /* strstriT */


/* -------------------------------------------------------------------------- */
/* Functions: Character String Allocating                                     */


PUBLIC bool  appendnT(                                                     /*F*/
    new_chars_t*  realloc_var_,                                            /*-*/
    const int     count_,                                                  /*-*/
    chars_t       string_,                                                 /*-*/
    ... ) {                                                                /*-*/
    GO                                                            (UID(FC424C));
    int     i           = 0;
    size_t  realloc_len = 0;
    size_t  total_len   = 0;

    /* items[] stores variable-arguments passed to the function */
    struct str_t {
        chars_t  str;
        size_t   len;
    } items[10];

    if (!ASSERT(count_ <= 10, UID(EB7F92))) {
        RETURN(false);
    }

    if (realloc_var_ == NULL) {
        _warn(_T("realloc_var_ == NULL"), UID(ED538D));
        RETURN(false);
    }

    realloc_len = total_len = STRLEN_T(*realloc_var_);

    {
        /* read items into array and calculate total length of result */
        va_list  list;
        va_start(list, string_);

        for (i = 0; i < count_; i++) {
            items[i].str = string_;
            items[i].len = STRLEN_T(string_);
            total_len += items[i].len;
            string_ = va_arg(list, chars_t);
        }
        va_end(list);
    }

    {
        /* reallocate string (+ 1 for \0) and append fragments to allocation */
        new_chars_t  move_mem = CAST(new_chars_t, REALLOC(*realloc_var_,
                                     (total_len + 1) * sizeof(char_t)));
        char_t*  wr = move_mem + realloc_len;
        if (!ASSERT(move_mem != NULL, UID(EE29A3))) {
            RETURN(false);
        }

        for (i = 0; i < count_; i++) {
            if (items[i].len > 0 && items[i].str != NULL) {
                STRNCPY_S_T(wr, items[i].len + 1,
                            items[i].str, items[i].len);
                wr += items[i].len;
            }
        }
        *wr = '\0';
        *realloc_var_ = move_mem;
    }
    RETURN(true);
} /* appendnT */


PUBLIC new_chars_t  T_format_numeric(                                      /*F*/
    chars_t  number_,                                                      /*-*/
    int      decimal_places_ ) {                                           /*-*/
    GO                                                            (UID(F9F6B6));
    /* Return a comma-formatted numeric string given a numeric string. */

    new_chars_t  wr          = NULL;
    new_chars_t  ret         = NULL;
    size_t       int_len     = 0;
    size_t       result_len  = 1;  /* 1 for terminating zero */
    bool         is_negative = false;

    if (!IS_BLANK(number_)) {
        if (*number_ == '-') {                         /* is number negative? */
            is_negative = true;
            number_++;
        }

        {
            /* calculate length of integer part */
            chars_t  rd = number_;
            while ('.' != *rd && '\0' != *rd) {
                rd++;
                int_len++;
            }
        }
    }

    /* calculate result length: */

    if (is_negative) {                         /* add space for negative sign */
        result_len += 1;
    }

    if (0 < int_len) {        /* add space for integer part, including commas */
        result_len += (int_len + (int_len - 1) / 3);

    } else {
        result_len += 1;    /* add space for leading zero */
    }

    if (0 < decimal_places_) {
        result_len += (1 + decimal_places_);    /* space for decimals */
    }

    ret  = mallocT(result_len * sizeof(char_t));           /* allocate string */
    *ret = '\0';

    wr = ret;

    if (is_negative) {               /* write minus sign for negative numbers */
        *wr++ = '-';
    }

    if (0 < int_len) {                                  /* write integer part */
        int  group = (int_len < 4) ? 3 : (int_len % 3) == 0 ? 3 : (int_len % 3);
        while (0 < int_len--) {
            if (group-- == 0) {
                *wr++ = ',';
                group = 2;
            }
            *wr++ = *number_++;
        }
    } else {
        *wr++ = '0';
    }

    if (0 < decimal_places_) {                          /* write decimal part */
        *wr++ = '.';
        if (number_ != NULL && *number_ == '.') {
            number_++;
        }

        while (0 < decimal_places_--) {
            if (number_ != NULL && '\0' != *number_) {
                *wr++ = *number_++;
            } else {
                *wr++ = '0';
            }
        }
    }
    *wr++ = '\0';
    RETURN(ret);
} /* T_format_numeric */


PUBLIC new_chars_t  T_chars_n(                                             /*F*/
    chars_t       source_,                                                 /*-*/
    const size_t  count_ ) {                                               /*-*/
    GO                                                            (UID(F63E12));
    new_chars_t   ret = NULL;
    const size_t  len = len_maxT(source_, count_);

    if (len > 0) {
        const size_t  bytes = (len + 1) * sizeof(char_t);
        ret = CAST(new_chars_t, MALLOC(bytes));
        STRNCPY_S_T(ret, len + 1, source_, len);
        *(ret + len) = '\0';
    }
    RETURN(ret);
} /* T_chars_n */


PUBLIC new_chars_t  T_bchars_n(                                            /*F*/
    const char* const  source_,                                            /*-*/
    const size_t       count_ ) {                                          /*-*/
    GO                                                            (UID(F9E80B));
    new_chars_t  ret = NULL;
    size_t       len = (source_ == NULL) ? 0 : STRLEN(source_);

    if (len > count_) {
        len = count_;
    }

    if (len > 0) {
        const size_t  bytes = (len + 1) * sizeof(char_t);
        ret = CAST(new_chars_t, MALLOC(bytes));

#if defined UNICODE || defined _UNICODE
        MBSTOWCS(ret, source_, len);
#else
        STRNCPY_S_T(ret, len + 1, source_, len);
#endif
        *(ret + len) = '\0';
    }
    RETURN(ret);
} /* T_bchars_n */


PUBLIC new_chars_t  T_wchars_n(                                            /*F*/
    const wchar_t*  source_,                                               /*-*/
    const size_t    count_ ) {                                             /*-*/
    GO                                                            (UID(FF701E));
    new_chars_t  ret = NULL;

    if (source_ == NULL) {
        ret = CAST(new_chars_t, MALLOC(sizeof(char_t)));
        *ret = '\0';
        RETURN(ret);
    }

#if defined UNICODE || defined _UNICODE
    ret = T_chars_n(source_, count_);
#else                                                  /* UNICODE || _UNICODE */
    {
        size_t  len = WCSLEN(source_);
        if (len > count_) {
            len = count_;
        }

        ret = CAST(new_chars_t, MALLOC((len + 1) * sizeof(char_t)));
        WCSTOMBS(ret, source_, len);
        *(ret + len) = '\0';
    }
#endif                                               /* !UNICODE && !_UNICODE */

    RETURN(ret);
} /* T_wchars_n */


PUBLIC new_chars_t  T_decode_base64( chars_t  string_ ) {                  /*F*/
    GO                                                            (UID(FEE29B));
    const size_t    len        = STRLEN_T(string_);
    const uint8_t*  rd         = NULL;
    uint8_t*        new_bchars = NULL;
    char_t*         wr         = NULL;
    new_chars_t     ret        = NULL;
    size_t          j          = 0;
    size_t          i          = 0;
    uint8_t         b1         = 0;
    uint8_t         b2         = 0;
    uint8_t         b3         = 0;
    uint8_t         arr[4]     = { 0, 0, 0, 0 };

    if (len == 0) {
        ret = mallocT(0);
        RETURN(ret);
    }

    new_bchars = CAST(uint8_t*, to_utf8T(string_));
    ret        = CAST(new_chars_t,
                      MALLOC((CAST(size_t, CAST(double, len) / 4 * 3) + 1)
                             * sizeof(char_t)));

    rd  = new_bchars;
    wr  = ret;
    i   = 0;

    while (*rd && *rd != '=' && i < len) {
        for (j = 0; j < 4; j++) {
            /* ignore whitespaces */
            while (*rd == ' '  || *rd == '\a' || *rd == '\b' || *rd == '\f' ||
                   *rd == '\n' || *rd == '\r' || *rd == '\t' || *rd == '\v') {
                rd++;
                i++;
            }

            arr[j] = 0;

            if (*rd && *rd != '=') {
                arr[j] = CAST(uint8_t,
                              STRCHR(BASE64_DIGITS_A, *rd) - BASE64_DIGITS_A);

            } else if (*rd == '=' || *rd == '\0') {
                break;
            } else {
                if (new_bchars != NULL) {
                    FREE(&new_bchars);
                }
                RETURN(NULL);
            }
            rd++;
            i++;
        }

        b1 = CAST(uint8_t, (arr[0] << 2) + ((arr[1] & 0x30) >> 4));
        /*                                              30 = 0011 0000 */
        b2 = CAST(uint8_t, ((arr[1] & 0x0F) << 4) + ((arr[2] & 0x3C) >> 2));
        /*                            ^ 0F = 0000 1111         3C = 0011 1100 */
        b3 = CAST(uint8_t, ((arr[2] & 0x03) << 6) + arr[3]);
        /*                            ^ 03 = 0000 0011 */

        *wr++ = CAST(char_t, b1);

        if (b2) {
            *wr++ = CAST(char_t, b2);
            if (b3) {
                *wr++ = CAST(char_t, b3);
            }
        }
    }

    if (new_bchars != NULL) {
        FREE(&new_bchars);
    }
    RETURN(ret);
} /* T_decode_base64 */


PUBLIC new_chars_t  T_encode_base64( chars_t  string_ ) {                  /*F*/
    GO                                                            (UID(F004AD));
    const size_t  len = STRLEN_T(string_);
    new_chars_t   ret = NULL;

    if (string_ == NULL || len == 0) {
        ret  = CAST(new_chars_t, MALLOC(sizeof(char_t)));
        *ret = '\0';
    } else {
        size_t        padding    = (len % 3) == 0 ? 0 : 3 - (len % 3);
        new_bchars_t  new_bchars = to_utf8T(string_);
        new_bchars_t  rd         = new_bchars;
        new_chars_t   wr         = NULL;
        size_t        i          = 0;
        size_t        j          = 0;
        uint8_t       b1         = 0;
        uint8_t       b2         = 0;
        uint8_t       b3         = 0;
        uint8_t       arr[4]     = { 0, 0, 0, 0 };

        {
            const size_t  bytes = (CAST(size_t, CAST(double, len + padding)
                                        / 3 * 4) + 1) * sizeof(char_t);
            ret = CAST(new_chars_t, MALLOC(bytes));
            wr  = ret;
        }

        for (i = 0; i < len; i += 3) {
            b1 = CAST(uint8_t, *rd);
            b2 = CAST(uint8_t, (i + 1) >= len ? 0 : * (rd + 1));
            b3 = CAST(uint8_t, (i + 2) >= len ? 0 : * (rd + 2));

            arr[0] = CAST(uint8_t, (b1 & 0xFC) >> 2);       /* FC = 1111 1100 */

            arr[1] = CAST(uint8_t, ((b2 & 0xF0) >> 4) + ((b1 & 0x03) << 4));
            /*                            ^ F0 = 1111 0000  03 = 0000 0011    */

            arr[2] = CAST(uint8_t, ((b3 & 0xC0) >> 6) + ((b2 & 0x0F) << 2));
            /*                            ^ C0 = 1100 0000  0F = 0000 1111    */

            arr[3] = CAST(uint8_t, b3 & 0x3F);              /* 3F = 0011 1111 */

            for (j = 0; j < 4 && j < (len - i + 1); j++) {
                *wr++ = CAST(char_t, BASE64_DIGITS_A[arr[j]]);
            }
            rd += 3;
        }

        while (padding--) {
            *wr++ = '=';
        }
        *wr = '\0';
        FREE(new_bchars);
    }
    RETURN(ret);
} /* T_encode_base64 */


PUBLIC new_chars_t  T_first(                                               /*F*/
    chars_t       string_,                                                 /*-*/
    const size_t  count_ ) {                                               /*-*/
    GO                                                            (UID(F850CE));
    new_chars_t  ret = T_substr(string_, 0, count_);
    RETURN(ret);
} /* T_first */


PUBLIC new_chars_t  T_offset(                                              /*F*/
    chars_t       string_,                                                 /*-*/
    const size_t  offset_ ) {                                              /*-*/
    GO                                                            (UID(F7DFAF));
    new_chars_t  ret = T_substr(string_, offset_, SIZE_MAX);
    RETURN(ret);
} /* T_offset */


PUBLIC new_chars_t  T_substr(                                              /*F*/
    chars_t       string_,                                                 /*-*/
    const size_t  offset_,                                                 /*-*/
    const size_t  count_ ) {                                               /*-*/
    GO                                                            (UID(FE6D55));
    chars_t      rd  = string_;
    new_chars_t  ret = NULL;
    size_t       len = 0;

    {
        size_t  i = count_;
        while (rd && *rd++ && i-- > 0) {
            len++;
        }
    }
    len = (offset_ >= len) ? 0 : len - offset_;

    {
        new_chars_t  wr = ret = CAST(new_chars_t, MALLOC((len + 1) *
                                     sizeof(char_t)));
        rd = string_;
        while (rd && *rd && len-- > 0) {
            *wr++ = *rd++;
        }
        *wr = '\0';
    }
    RETURN(ret);
} /* T_substr */


PUBLIC new_chars_t  T_double(                                              /*F*/
    long double  value_,                                                   /*-*/
    const int    decimal_places_ ) {                                       /*-*/
    GO                                                            (UID(F59887));
    const bool   is_negative = C_BOOL(value_ < 0);
    long double  absolute    = is_negative ? -value_ : value_;

    /* get the integer part as an unsigned integer */
    const uint64_t  intgr = CAST(uint64_t, absolute);

    /* get the fractional part and number of leading zeros */
    uint64_t  fract = 0;
    int       zeros = 0;
    int       decimal_places = decimal_places_;

    if (decimal_places > 0) {
        long double  limit = 1;
        long double  fr    = absolute - intgr;
        {
            int  i = decimal_places + 1;
            while (i--) {
                limit /= 10;
            }
        }

        while (fr - CAST(long double, fract) > limit) {
            fr *= 10;
            fract = CAST(uint64_t, fr);
            if (fract == 0) {
                zeros++;
            }
        }
    }

    {
        /* allocate a new string */
        new_chars_t  ret  = CAST(new_chars_t, MALLOC(64 * sizeof(char_t)));
        char_t*      wr   = ret;
        int          part = 0;
        uint64_t     number_part[2];
        number_part[0] = intgr;
        number_part[1] = fract;
        *ret = '\0';

        for (part = 0; part < (decimal_places > 0 ? 2 : 1); part++) {
            /* use 64-bit unsigned integers so UINT_MAX can be handled */
            uint64_t  val = number_part[part], digit = 0, len = 0;

            /* calc. length of number (len) and value of divisor (div) */
            uint64_t  div = 1;

            do {
                div *= 10;  /* base 10 */
                len++;
            } while (div <= val);

            div /= 10;

            if (part == 0 && is_negative) {
                *wr++ = '-';

            } else if (part == 1) {
                int  i = zeros;
                *wr++ = '.';
                while (i--) {
                    *wr++ = '0';
                    decimal_places--;
                }
            }

            /* iterate and write each digit starting */
            /* from the most significant             */
            while ((part == 0 || decimal_places > 0) && len--) {
                digit = div == 0 ? 0 : val / div;
                *wr++ = CAST(char_t, '0' + CAST(char, digit));
                val -= (digit * div);
                div /= 10;  /* base 10 */

                if (part == 1) {
                    decimal_places--;
                }
            }

            /* fill any remaining decimal places with 0 */
            if (part == 1) {
                while (decimal_places--) {
                    *wr++ = '0';
                }
            }
        }

        *wr = '\0';
        {
            const size_t  len = STRLEN_T(ret);
            ret = CAST(new_chars_t, REALLOC(ret, (len + 1) * sizeof(char_t)));
        }
        RETURN(ret);
    }
} /* T_double */


/* Convert a value into a hexadecimal string.                                 */
PUBLIC new_chars_t  T_hex(                                                 /*F*/
    const uint32_t  value_,                                                /*-*/
    const size_t    min_len_ ) {                                           /*-*/
    GO                                                            (UID(FF5B7F));
    static const size_t  MAX_LEN    = 8;
    static const int     BASE_16    = 16;
    static const char*   HEX_DIGITS = "0123456789abcdef";

    size_t    count  = 0;
    size_t    digits = 0;
    uint64_t  val    = value_;  /* use 64-bit unsigned integers */
    uint64_t  digit  = 0;       /* so UINT_MAX can be handled   */
    uint64_t  div    = 0;
    chars_t   rd     = NULL;

    /* allocate a new string */
    new_chars_t  ret =
        CAST(new_chars_t, MALLOC((MAX_LEN + 1) * sizeof(char_t)));

    char_t*  wr = ret;
    *(ret + MAX_LEN) = '\0';

    /* calculate value of divisor (div) */
    div = 1;

    do {
        div *= BASE_16;
        digits++;
    } while (div <= val);

    div /= BASE_16;

    /* iterate and write each digit starting from the most significant */
    while (count < MAX_LEN && digits--) {
        digit = div == 0 ? 0 : val / div;
        *wr++ = CAST(char_t, HEX_DIGITS[CAST(int, digit & 0xFFFF)]);
        count++;
        val -= (digit * div);
        div /= BASE_16;
    }

    *wr = '\0';

    /* add leading zeros */
    if (count < min_len_) {
        rd = ret + count    - 1;
        wr = ret + min_len_ - 1;

        while (wr >= ret && count-- > 0) { /* shift result right */
            *wr-- = *rd--;
        }

        while (wr >= ret) { /* add leading zeros */
            *wr-- = '0';
        }
    }
    RETURN(ret);
} /* T_hex */


PUBLIC new_chars_t  T_int( const int  value_ ) {                           /*F*/
    GO                                                            (UID(FE13B7));
    new_chars_t  ret = mallocT(64);
    SNPRINTF_T(ret, 64, _T("%d"), value_);
    RETURN(ret);
} /* T_int */


PUBLIC new_chars_t  T_join(                                                /*F*/
    chars_t  terminator_,                                                  /*-*/
    chars_t  string1_,                                                     /*-*/
    ... ) {                                                                /*-*/
    GO                                                            (UID(FE295B));
    size_t  bytes = 0;

    /* add length of string1_ */
    if (string1_ != NULL) {
        chars_t  rd = string1_;
        while ('\0' != *rd) {
            rd++;
            bytes++;
        }
    }

    {
        /* add length of other strings: */
        bool     exit = false;
        va_list  list;
        va_start(list, string1_);
        do {
            chars_t  arg = va_arg(list, chars_t);

            if ((arg == NULL && terminator_ == NULL) ||
                equals2T(arg, terminator_)) {
                exit = true;

            } else if (!IS_BLANK(arg)) {
                chars_t  rd = arg;
                while ('\0' != *rd) {
                    rd++;
                    bytes++;
                }
            }
        } while (!exit);
        va_end(list);
    }

    {
        /* build joined string: */
        new_chars_t  ret =
            CAST(new_chars_t, MALLOC((bytes + 1) * sizeof(char_t)));
        /*     allocate space ^               ^ for \0 */
        char_t*  wr = ret;

        if (!ASSERT(ret != NULL, UID(E2A1FD))) {
            RETURN(NULL);
        }

        /* append string1_ */
        if (string1_ != NULL) {
            chars_t  rd = string1_;
            while ('\0' != *rd) {
                *wr++ = *rd++;
            }
        }

        {
            /* append other strings */
            bool     exit = false;
            va_list  list;
            va_start(list, string1_);
            do {
                chars_t  arg = va_arg(list, chars_t);

                if ((arg == NULL && terminator_ == NULL) ||
                    equals2T(arg, terminator_)) {
                    exit = true;

                } else if (!IS_BLANK(arg)) {
                    chars_t  rd = arg;
                    while ('\0' != *rd) {
                        *wr++ = *rd++;
                    }
                }
            } while (!exit);
            va_end(list);
        }
        *wr = '\0';
        RETURN(ret);
    }
} /* T_join */


PUBLIC new_chars_t  T_last(                                                /*F*/
    chars_t       string_,                                                 /*-*/
    const size_t  length_ ) {                                              /*-*/
    GO                                                            (UID(FD9FFB));
    new_chars_t   ret = NULL;
    const size_t  len = STRLEN_T(string_);

    if (length_ >= len) {
        ret = T_chars(string_);
    } else {
        ret = T_substr(string_, len - length_, length_);
    }
    RETURN(ret);
} /* T_last */


PUBLIC new_chars_t  T_lower( chars_t  string_ ) {                          /*F*/
    GO                                                            (UID(FF19CC));
    new_chars_t  ret = T_chars(string_);
    lower_in_T(CAST(char_t*, ret));
    RETURN(ret);
} /* T_lower */


PUBLIC new_chars_t  T_malloc_id(                                           /*F*/
    const size_t  char_len_,                                               /*-*/
    chars_t       filename_,                                               /*-*/
    const int     source_line_ ) {                                         /*-*/
    GO                                                            (UID(F71804));
    const size_t  bytes = (char_len_ + 1) * sizeof(char_t);  /* +1 for \0 */
    new_chars_t   ret   =
        CAST(new_chars_t, malloc_id(bytes, filename_, source_line_));
    MEMSET(ret, 0x00, bytes);
    RETURN(ret);
} /* T_malloc_id */


#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable:4774)  /* W:L4 format string is not a string literal */
#endif


#if defined _MSC_VER
static new_bytes_t  _chars_printf(                                         /*F*/
    const size_t    char_size_,                                            /*-*/
    const uint8_t*  format_,                                               /*-*/
    va_list         args_ ) {                                              /*-*/
    GO                                                            (UID(FB1762));
#define MAX_FORMAT_WIDTH  20 * 4            /* maximum: 4 bytes per wide char */

    new_bytes_t  ret        = { 0, NULL };
    int          pass       = 0;
    size_t       result_len = 0;
    size_t       fmt_len    = 0;
    uint8_t      fmt_buf[MAX_FORMAT_WIDTH];

    /* 1 for char, 2 for wchar_t on Windows, or 4 for wchar_t on Linux */
    ASSERT(char_size_ == 1 || char_size_ == 2 || char_size_ == 4, UID(E97699));

    if (format_ == NULL) {
        RETURN(ret);
    }

    CLEAR(fmt_buf);

    /* the first pass [0] calculates the required string length      */
    /* the second pass [1] allocates and writes to the result string */
    for (pass = 0; pass < 2; pass++) {
        const uint8_t*  rd   = format_;
        uint8_t*        wr   = NULL;
        va_list         args = args_;

        /* va_start() is in the calling function */

        if (pass == 1) {
            ret.size = (result_len + 1) * char_size_;
            ret.data = wr = CAST(uint8_t*, MALLOC(ret.size));
        }

        while (CHAR_GET(rd) != '\0') {
            uint32_t  ch = CHAR_GET(rd);

            if (ch == '%' && CHAR_GET_AT(rd, 1) == '%') {
                if (pass == 0) {
                    result_len++;
                } else {
                    CHAR_PUT(wr, '%');
                    wr += char_size_;
                }
                rd += (2 * char_size_);

            } else if (ch == '%' && CHAR_GET_AT(rd, 1) == 's') {
                const uint8_t*  read_str = va_arg(args, const uint8_t*);

                while (read_str && CHAR_GET(read_str) != '\0') {
                    if (pass == 0) {
                        result_len++;
                    } else {
                        CHAR_PUT(wr, CHAR_GET(read_str));
                        wr += char_size_;
                    }
                    read_str += char_size_;
                }
                rd += 2 * char_size_;

            } else if ((fmt_len == 0 && ch == '%') ||
                       (fmt_len > 0 && (ch == '.' || (ch >= '0' && ch <= '9')))) {

                uint8_t*  fmt = &fmt_buf[fmt_len * char_size_];
                CHAR_PUT(fmt, ch);
                fmt_len++;
                rd += char_size_;

            } else if (
                fmt_len > 0 &&
                (ch == 'a' ||  /* double precision, signed hex.     */
                 ch == 'A' ||  /* dbl. precsion, signed hexadecimal */
                 ch == 'c' ||  /* int or wint_t, single character   */
                 ch == 'C' ||  /* int or wint_t, single character   */
                 ch == 'd' ||  /* signed int, prints decimal int.   */
                 ch == 'e' ||  /* dbl. print [-]d.dddd e[sign]dd[d] */
                 ch == 'E' ||  /* dbl. same as 'e' but 'E' not 'e'  */
                 ch == 'f' ||  /* dbl. print in format [-]dddd.dddd */
                 ch == 'g' ||  /* dbl. print in f or e format       */
                 ch == 'G' ||  /* dbl. same as 'g' but 'E' not 'e'  */
                 ch == 'i' ||  /* signed int, prints decimal int    */
                 ch == 'n' ||  /* pointer to integer                */
                 ch == 'o' ||  /* unsigned int, prints octal int.   */
                 ch == 'p' ||  /* ptr. to void, prints a hex. addr. */
                 ch == 'u' ||  /* unsigned int, prints decimal int. */
                 ch == 'x' ||  /* u.int, prints hex. using "abcdef" */
                 ch == 'X')) { /* u.int, print hex using "ABCDEF"   */

#define _MAX_NUMERIC_ARG_LEN  64

                uint8_t  val_buf[_MAX_NUMERIC_ARG_LEN * 4];
                CHAR_PUT(&fmt_buf[fmt_len * char_size_], ch);
                fmt_len++;

                if (pass == 0) {
                    result_len += _MAX_NUMERIC_ARG_LEN;
                } else {
                    CLEAR(val_buf);
                    CHAR_PUT(&fmt_buf[fmt_len * char_size_], '\0');
                }

                if (ch == 'c' || ch == 'C' || ch == 'd' || ch == 'i') {

                    const int  arg = va_arg(args, int);

                    if (pass == 1) {
                        if (char_size_ == 1) {
                            SNPRINTF(
                                CAST(char*, val_buf),
                                _MAX_NUMERIC_ARG_LEN,
                                CAST(const char*, fmt_buf),
                                arg);
                        } else {
                            SWPRINTF_S(
                                CAST(wchar_t*, val_buf),
                                _MAX_NUMERIC_ARG_LEN,
                                CAST(const wchar_t*, fmt_buf),
                                arg);
                        }
                    }

                } else if (ch == 'o' || ch == 'u' || ch == 'x' || ch == 'X') {
                    const uint32_t  arg = va_arg(args, uint32_t);
                    if (pass == 1) {
                        if (char_size_ == 1) {
                            SNPRINTF(
                                CAST(char*, val_buf),
                                _MAX_NUMERIC_ARG_LEN,
                                CAST(const char*, fmt_buf),
                                arg);
                        } else {
                            SWPRINTF_S(
                                CAST(wchar_t*, val_buf),
                                _MAX_NUMERIC_ARG_LEN,
                                CAST(const wchar_t*, fmt_buf),
                                arg);
                        }
                    }

                } else if (ch == 'a' || ch == 'A' ||
                           ch == 'e' || ch == 'E' ||
                           ch == 'f' ||
                           ch == 'g' || ch == 'G') {

                    const double  arg = va_arg(args, double);

                    if (char_size_ == 1) {
                        SNPRINTF(
                            CAST(char*, val_buf),
                            _MAX_NUMERIC_ARG_LEN,
                            CAST(const char*, fmt_buf),
                            arg);
                    } else {
                        SWPRINTF_S(
                            CAST(wchar_t*, val_buf),
                            _MAX_NUMERIC_ARG_LEN,
                            CAST(const wchar_t*, fmt_buf),
                            arg);
                    }

                } else if (ch == 'n' || ch == 'p') {

                    const void*  arg = va_arg(args, void*);

                    if (pass == 1) {
                        if (char_size_ == 1) {
                            SNPRINTF(
                                CAST(char*, val_buf),
                                _MAX_NUMERIC_ARG_LEN,
                                CAST(const char*, fmt_buf),
                                arg);
                        } else {
                            SWPRINTF_S(
                                CAST(wchar_t*, val_buf),
                                _MAX_NUMERIC_ARG_LEN,
                                CAST(const wchar_t*, fmt_buf),
                                arg);
                        }
                    }
                }

#undef _MAX_NUMERIC_ARG_LEN

                /* write formatted value to the output string */
                if (pass == 1) {
                    const uint8_t*  read_val = val_buf;

                    while (CHAR_GET(read_val) != '\0') {
                        CHAR_PUT(wr, CHAR_GET(read_val));
                        wr       += char_size_;
                        read_val += char_size_;
                    }
                }

                fmt_len = 0;
                CLEAR(fmt_buf);
                rd += char_size_;
            } else if (fmt_len > 0) {
                WARN(_T("Unknown format specified."), UID(ED9AD1));
            } else {
                if (pass == 0) {
                    result_len++;
                } else {
                    CHAR_PUT(wr, ch);
                    wr += char_size_;
                }
                rd += char_size_;
            }
        }
        /* va_end() is in the calling function */
    }
    RETURN(ret);
} /* _chars_printf */
#endif                                                            /* _MSC_VER */


#if defined _MSC_VER
#pragma warning (pop)
#endif


PUBLIC new_bchars_t  formatA(                                              /*F*/
    const char*  format_,                                                  /*-*/
    ... ) {                                                                /*-*/
    GO                                                            (UID(F71862));
    va_list       args;
    new_bytes_t   bytes = { 0, NULL };
    new_bchars_t  ret   = NULL;

#if PLATFORM_LINUX
    int  cap = 0;
    int  len = 0;

    va_start(args, format_);
    cap = vsnprintf(NULL, 0, format_, args) + 1;
    va_end(args);

    ret = MALLOC(cap);

    va_start(args, format_);
    len = vsnprintf(ret, cap, format_, args);
    va_end(args);

    bytes.size = len;
    bytes.data = CAST(uint8_t*, ret);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    va_start(args, format_);
    bytes = _chars_printf(sizeof(char),
                          CAST(const uint8_t*, format_), args);
    va_end(args);
#endif                                                      /* PLATFORM_WIN32 */

    ret = CAST(new_bchars_t, bytes.data);

    RETURN(ret);
} /* formatA */


PUBLIC new_wchars_t  formatW(                                              /*F*/
    const wchar_t*  format_,                                               /*-*/
    ... ) {                                                                /*-*/
    GO                                                            (UID(F8B48E));
    va_list       args;
    new_bytes_t   bytes = { 0, NULL };
    new_wchars_t  ret   = NULL;

#if PLATFORM_LINUX
    int  cap = 0;
    int  len = 0;

    va_start(args, format_);
    cap = vswprintf(NULL, 0, format_, args) + 1;
    va_end(args);

    ret = MALLOC(cap * sizeof(wchar_t));

    va_start(args, format_);
    len = vswprintf(ret, cap, format_, args);
    va_end(args);

    bytes.size = len;
    bytes.data = CAST(uint8_t*, ret);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    va_start(args, format_);
    bytes = _chars_printf(
                sizeof(wchar_t), CAST(const uint8_t*, format_), args);
    va_end(args);
#endif                                                      /* PLATFORM_WIN32 */

    ret = CAST(new_wchars_t, bytes.data);
    RETURN(ret);
} /* formatW */


PUBLIC new_chars_t  T_realloc_id(                                          /*F*/
    new_chars_t   string_,                                                 /*-*/
    const size_t  char_len_,                                               /*-*/
    chars_t       filename_,                                               /*-*/
    const int     source_line_ ) {                                         /*-*/
    GO                                                            (UID(FF2506));
    const size_t  bytes = (char_len_ + 1) * sizeof(char_t);  /* +1 for \0 */
    new_chars_t   ret = CAST(new_chars_t, realloc_id(string_, bytes, filename_,
                             source_line_));
    * (ret + char_len_) = '\0';
    RETURN(ret);
} /* T_realloc_id */


PUBLIC new_chars_t  T_repeat(                                              /*F*/
    chars_t    string_,     /* String to be repeated.                  */  /*-*/
    const int  count_,      /* Max. # of times string can be repeated. */  /*-*/
    const int  max_len_ ) { /* Max. length of the returned string.     */
    /*-*/
    GO                                                            (UID(F293E3));
    size_t       len   = 0;
    new_chars_t  blank = CAST(new_chars_t, BLANK);

    if (string_ == NULL || count_ == 0 || max_len_ == 0) {
        RETURN(blank);

    } else if (count_ < 0) {
        _warn(_T("count_ < 0"), UID(ED0474));
        RETURN(blank);

    } else if (max_len_ < 0) {
        _warn(_T("max_len_ < 0"), UID(E6CEA0));
        RETURN(blank);
    }

    if (count_ >
        0) {                   /* calculate maximum length of string */
        len = STRLEN_T(string_);
        len *= CAST(size_t, count_);
    }

    if (len > CAST(size_t, max_len_)) {
        len = CAST(size_t, max_len_);
    }

    if (len < 1) {
        RETURN(blank);
    }

    {
        const size_t  bytes   = (len + 1) * sizeof(char_t);
        new_chars_t   ret     = CAST(new_chars_t, MALLOC(bytes));
        chars_t       rd      = string_;
        char_t*       wr      = ret;
        int           max_len = max_len_;
        int           count   = count_;

        if (ret == NULL) {
            ret = CAST(char_t*, BLANK);
            _warn(_T("allocation error"), UID(EFA90E));
            RETURN(ret);
        }

        if (string_ == NULL) {
            max_len = 0;
        }

        while (count && max_len--) {
            *wr++ = *rd++;
            if (*rd == '\0') {
                rd = string_;
                count--;
            }
        }
        *wr = '\0';
        RETURN(ret);
    }
} /* T_repeat */


typedef struct  _repl_lengths_t {
    size_t  str_len;                                       /* _repl_lengths_t */
    size_t  find_len;                                      /* _repl_lengths_t */
    size_t  repl_len;                                      /* _repl_lengths_t */
    size_t  result_len;                                    /* _repl_lengths_t */
}
_repl_lengths_t;


/* the main use of this function is to caluclate the length of string_        */
/* after replacing all find_ with replace_, returned in result_len            */
static _repl_lengths_t  _calc_repl_lengths(                                /*F*/
    chars_t     string_,                                                   /*-*/
    chars_t     find_,                                                     /*-*/
    chars_t     replace_,                                                  /*-*/
    const bool  ignore_case_ ) {                                           /*-*/
    GO                                                            (UID(FC992C));
    _repl_lengths_t  ret;
    ret.str_len    = STRLEN_T(string_);
    ret.find_len   = STRLEN_T(find_);
    ret.repl_len   = STRLEN_T(replace_);
    ret.result_len = 0;

    if (ret.str_len < 1 && ret.find_len < 1) {
        ret.result_len = ret.repl_len;

    } else if (ret.find_len < 1 ||
               ret.find_len > ret.str_len ||
               ret.find_len == ret.repl_len) {
        ret.result_len = ret.str_len;

    } else {
        chars_t  str     = string_;
        chars_t  find    = find_;
        size_t   i       = 0;
        size_t   matches = 0;  /* matching characters found */

        ret.result_len = ret.str_len;

        for (i = 0; i < ret.str_len; i++) {
            if (ignore_case_ ? TOLOWER_T(*str) == TOLOWER_T(*find)
                : *str == *find) {

                find++;
                matches++;

                if (matches == ret.find_len) {
                    ret.result_len -= ret.find_len;
                    ret.result_len += ret.repl_len;
                    find = find_;
                    matches = 0;
                }
            } else if (matches > 0) {
                str -= matches;
                i -= matches;
                find = find_;
                matches = 0;
            }
            str++;
        }
    }
    RETURN(ret);
} /* _calc_repl_lengths */


PUBLIC new_chars_t  T_replace(                                             /*F*/
    chars_t     string_,        /* string being searched      */           /*-*/
    chars_t     find_,          /* string to find             */           /*-*/
    chars_t     replace_,       /* replacement string         */           /*-*/
    const bool  ignore_case_ ) { /* MATCH_CASE_C/IGNORE_CASE_C */
    /*-*/
    GO                                                            (UID(F0DAB2));
    _repl_lengths_t  calc = _calc_repl_lengths(string_, find_, replace_,
                            ignore_case_);

    new_chars_t  ret = CAST(new_chars_t,
                            MALLOC((calc.result_len + 1) * sizeof(char_t)));

    ASSERT(ret != NULL, UID(E9488A));

    if (calc.str_len == 0 && calc.find_len == 0 && calc.repl_len > 0) {
        MEMCPY(ret, replace_, calc.repl_len * sizeof(char_t));

    } else if (calc.result_len > 0) {
        size_t   matches = 0;
        char_t*  wr      = ret     + calc.result_len - 1;
        chars_t  src     = string_ + calc.str_len - 1;
        chars_t  find    = find_ + (calc.find_len == 0 ? 0 : calc.find_len - 1);

        *(wr + 1) = '\0';

        while (wr >= ret) {
            if (ignore_case_ ? TOLOWER_T(*src) == TOLOWER_T(*find)
                : *src == *find) {

                if (++matches == calc.find_len) {
                    chars_t  repl = replace_ + calc.repl_len - 1;
                    size_t   i    = 0;

                    for (i = 0; i < calc.repl_len; i++) {
                        *wr = *repl;
                        wr--;
                        repl--;
                    }

                    src--;
                    find = find_ + calc.find_len - 1;
                    matches = 0;
                } else {
                    find--;
                    src--;
                }
            } else {
                if (matches > 0) {
                    src += matches;
                    find = find_ + calc.find_len - 1;
                    matches = 0;
                }
                *wr-- = *src--;
            }
        }
    }
    RETURN(ret);
} /* T_replace */


PUBLIC void  set_inT(                                                      /*F*/
    new_chars_t*  realloc_var_,                                            /*-*/
    chars_t       new_string_ ) {                                          /*-*/
    GO                                                            (UID(F002DF));
    new_chars_t  str = NULL;

    if (realloc_var_ == NULL) {
        _warn(_T("realloc_var_ == NULL"), UID(EB58C7));
        RETURN(NIL);
    }

    if (*realloc_var_ != NULL) {
        FREE(*realloc_var_);
        *realloc_var_ = NULL;
    }

    if (new_string_ == NULL) {
        RETURN(NIL);
    }

    {
        const size_t  old_len = lenT(*realloc_var_);
        const size_t  new_len = lenT(new_string_);

        if ((old_len < new_len) || (new_string_ != NULL && new_len == 0)) {
            const size_t  bytes = (new_len + 1 /* for \0 */) * sizeof(char_t);
            str = CAST(new_chars_t, REALLOC(*realloc_var_, bytes));
        } else {
            str = *realloc_var_;
        }

        *str = '\0';

        if (new_len > 0) {
            STRCAT_S_T(str, new_len + 1, new_string_);
        }

        if (str == NULL) {
            RETURN(NIL);
        }
    }

    *realloc_var_ = str;

    RETURN(NIL);
} /* set_inT */


PUBLIC void  set_default_inT(                                              /*F*/
    new_chars_t*  realloc_var_,                                            /*-*/
    chars_t       new_string_,                                             /*-*/
    chars_t       default_ ) {                                             /*-*/
    GO                                                            (UID(FC1758));
    if (IS_BLANK(new_string_)) {
        set_inT(realloc_var_, default_);
    } else {
        set_inT(realloc_var_, new_string_);
    }
    RETURN(NIL);
} /* set_default_inT */


PUBLIC new_chars_t  T_get_tag(                                             /*F*/
    chars_t  string_,                                                      /*-*/
    chars_t  tag_,                                                         /*-*/
    chars_t  delimiter_ ) {                                                /*-*/
    GO                                                            (UID(F2613C));
    chars_t      tag = strstriT(string_, tag_);
    new_chars_t  ret = NULL;

    if (tag != NULL) {
        new_chars_t  end = NULL;

        string_ = tag + STRLEN_T(tag_);
        end     = strstriT(string_, delimiter_);

        if (end == NULL) {
            ret = T_chars(string_);
        } else {
            const uint32_t  end_pos = end - string_;
            ret = T_chars_n(string_, end_pos);
        }
    }
    RETURN(ret);
} /* T_get_tag */


PUBLIC new_chars_t  T_remove_tag(                                          /*F*/
    chars_t  string_,                                                      /*-*/
    chars_t  tag_,                                                         /*-*/
    chars_t  delimiter_ ) {                                                /*-*/
    GO                                                            (UID(F6E973));
    new_chars_t  ret = NULL;
    chars_t      tag = strstriT(string_, tag_);

    if (tag == NULL) {
        ret = T_chars(string_);
    } else {
        const uint32_t  pos     = tag - string_;
        const uint32_t  tag_len = STRLEN_T(tag_);
        chars_t         end_ptr = strstriT(string_ + pos + tag_len,
                                           delimiter_);
        if (end_ptr == NULL) {
            ret = T_chars_n(string_, pos);
        } else {
            const uint32_t  delim_len = STRLEN_T(delimiter_);
            new_chars_t     begin     = T_chars_n(string_, pos);
            new_chars_t     end       = T_chars(end_ptr + delim_len);

            ret = T_join(TT, begin, end, TT);

            freeT(&begin);
            freeT(&end);
        }
    }
    RETURN(ret);
} /* T_remove_tag */


PUBLIC new_chars_t  T_title( chars_t  string_ ) {                          /*F*/
    GO                                                            (UID(F42716));
    new_chars_t  ret = T_chars(string_);
    title_in_T(CAST(char_t*, ret));
    RETURN(ret);
} /* T_title */


PUBLIC new_bytes_t  to_bytesT(                                             /*F*/
    chars_t            string_,                                            /*-*/
    chars_format_enum  string_format_ ) {                                  /*-*/
    GO                                                            (UID(FA1AC5));
    new_bytes_t  ret = { 0, NULL };
    ret.size = STRLEN_T(string_);

    if (string_ == NULL || ret.size < 1) {
        ret.size = 0;
        ret.data = NULL;
        RETURN(ret);
    }

    ret.size++;  /* for \0 */

#if defined UNICODE || defined _UNICODE

    if (string_format_ == ANSI) {
        ret.data = CAST(uint8_t*, utf8_of_wide(string_));
    } else {
        ret.size *= sizeof(wchar_t);
        ret.data = CAST(uint8_t*, T_chars(string_));
    }

#else                                                  /* UNICODE || _UNICODE */

    if (string_format_ == WIDE) {
        ret.size *= sizeof(wchar_t);
        ret.data = CAST(uint8_t*, wide_of_utf8(string_));
    } else {
        ret.data = CAST(uint8_t*, T_chars(string_));
    }

#endif                                               /* !UNICODE && !_UNICODE */

    if (ret.data == NULL) {
        ERR(_T("MALLOC() failure."), UID(EF0ED6));
        ret.size = 0;
    }
    RETURN(ret);
} /* to_bytesT */


PUBLIC new_chars_t  T_get_token_xt(                                        /*F*/
    chars_t       list_,                                                   /*-*/
    const size_t  index_,                                                  /*-*/
    chars_t       delimiter_,                                              /*-*/
    const bool    ignore_end_delimiter_ ) {                                /*-*/
    GO                                                            (UID(F1F1D2));
    new_chars_t   ret      = NULL;
    const size_t  list_len = STRLEN_T(list_);
    size_t        curr     = 0;
    size_t        next     = 0;

    /* location_out_ can be used as output parameter. but left unused. */

    /* if (location_out_) {         */
    /*     *location_out_ = NONE; } */

    if (IS_BLANK(delimiter_)) {
        if (index_ == 0) {
            /* if (location_out_) {      */
            /*     *location_out_ = 0; } */
            ret = T_chars_n(list_, list_len);
            RETURN(ret);
        } else {
            RETURN(NULL);
        }
    }

    {
        const size_t  delim_len = STRLEN_T(delimiter_);
        if (delim_len > list_len) {
            RETURN(NULL);
        }

        next = findT(list_, delimiter_, 0, MATCH_CASE, false, list_len,
                     delim_len);
        {
            size_t  index = index_;
            while (index--) {
                if (next == NONE) {
                    curr = NONE;
                    break;
                }

                curr = next + delim_len;
                next = findT(list_, delimiter_, curr, MATCH_CASE, false,
                             list_len, delim_len);
            }
        }
    }

    if (curr == NONE) {
        RETURN(NULL);
    }

    /* if (location_out_) {        */
    /*    *location_out_ = curr; } */

    if (next == NONE || ignore_end_delimiter_) {
        ret = T_chars(list_ + curr);
    } else {
        ret = T_chars_n(list_ + curr, next - curr);
    }
    RETURN(ret);
} /* T_get_token_xt */


#if defined UNFINISHED_CODE
PUBLIC new_chars_t  T_tokenize(                                            /*F*/
    chars_t  string_,                                                      /*-*/
    chars_t  delimiter_ ) {                                                /*-*/
    GO                                                            (UID(FD02FA));
    size_t  delim_len   = 0;
    size_t  sum_len     = 0;
    size_t  max_len     = 0;
    size_t  str_len     = 0;
    size_t  token_count = 0;
    size_t  token_len   = 0;

    _str_t  ret;
    _STR_INIT(ret);

    str_len = STRLEN_T(string_);
    if (str_len < 1) {
        RETURN(ret);
    }

    delim_len = STRLEN_T(delimiter_);

    {
        /* count tokens and maximum length of a token */
        chars_t  ch = string_;
        while (*ch) {
            if ((*ch >= 'a' && *ch <= 'z') || (*ch >= 'A' && *ch <= 'Z') ||
                (*ch >= '0' && *ch <= '9')) {
                token_len++;
            } else {
                if (token_len > 0) {
                    token_count++;
                    sum_len += token_len;

                    if (token_len > max_len) {
                        max_len = token_len;
                    }

                    token_len = 0;
                }
            }
            ch++;
        }
    }

    {
        /* allocate space: */
        /*
            const size_t  avg_len = (sum_len / token_count) + 1;
            const size_t  len     = (avg_len + delim_len) * token_count + 1;
            char_t*       tokens  = MALLOC(sizeof(char_t) * len);
        */
    }
    RETURN(ret);
} /* T_tokenize */
#endif                                                     /* UNFINISHED_CODE */


PUBLIC new_chars_t  T_set_token(                                           /*F*/
    chars_t       list_,                                                   /*-*/
    const size_t  index_,                                                  /*-*/
    chars_t       token_,                                                  /*-*/
    chars_t       delimiter_ ) {                                           /*-*/
    GO                                                            (UID(F3DC06));
    new_chars_t   ret       = NULL;
    const size_t  list_len  = STRLEN_T(list_);
    const size_t  token_len = STRLEN_T(token_);
    const size_t  delim_len = STRLEN_T(delimiter_);
    size_t        curr      = 0;
    size_t        next      = 0;
    size_t        i         = 0;

    if (list_len < 1) {
        ret = T_chars(token_);
        RETURN(ret);
    }

    if (delim_len < 1) {
        ERR(_T("zero-length delimiter"), UID(EEE57D));
        RETURN(NULL);
    }

    do {
        next = findT(list_, delimiter_, curr, IGNORE_CASE, false, list_len,
                     delim_len);

        if (next == NONE) {
            break;
        }

        if (i < index_) {
            curr = next + delim_len;
            i++;
        }
    } while (i <= index_ && next < curr);

    if (i < index_) {
        new_chars_t  delimiters =
            repeat2T(delimiter_, CAST(int, index_ - i));

        const size_t  len = token_len + STRLEN_T(delimiters);

        ret = mallocT(len);
        STRCAT_S_T(ret, len, delimiters);
        STRCAT_S_T(ret, len, token_);
        freeT(&delimiters);
        RETURN(ret);
    } else {
        const size_t  len =
            curr + token_len + (next == NONE ? 0 : list_len - next);

        ret = mallocT(len);

        if (curr > 0) {
            STRNCAT_S_T(ret, len, list_, curr);
        }

        STRCAT_S_T(ret, len, token_);

        if (next != NONE) {
            STRCAT_S_T(ret, len, list_ + next);
        }
    }
    RETURN(ret);
} /* T_set_token */


PUBLIC new_bchars_t  to_utf8T( chars_t  string_ ) {                        /*F*/
    GO                                                            (UID(FCD5AC));
    new_bchars_t  ret = NULL;

    if (string_ == NULL) {
        ret = CAST(new_bchars_t, MALLOC(sizeof(char_t)));
        *ret = '\0';
    } else {

#if defined UNICODE || defined _UNICODE
        ret = utf8_of_wide(string_);
#else
        ret = T_chars(string_);
#endif
    }
    RETURN(ret);
} /* to_utf8T */


PUBLIC new_chars_t  T_uint( const uint32_t  value_ ) {                     /*F*/
    GO                                                            (UID(FB50E9));
    new_chars_t  ret = mallocT(16 * sizeof(char_t));
    SNPRINTF_T(ret, 16, _T("%u"), value_);
    RETURN(ret);
} /* T_uint */


PUBLIC new_chars_t  T_uint64( const uint64_t  value_ ) {                   /*F*/
    GO                                                            (UID(F16EFC));
    new_chars_t  ret = mallocT(21 * sizeof(char_t));

#if PLATFORM_LINUX
    SNPRINTF_T(ret, 21, _T("%llu"), CAST(unsigned long long, value_));

#elif PLATFORM_WIN32
    SNPRINTF_T(ret, 21, _T("%I64u"), value_);

#else
#error UID(E7732B) PLATFORM IS NOT PROPERLY DEFINED
#endif

    RETURN(ret);
} /* T_uint64 */


PUBLIC new_chars_t  T_upper( chars_t  string_ ) {                          /*F*/
    GO                                                            (UID(FC9E1F));
    new_chars_t  ret = T_chars(string_);
    upper_in_T(CAST(char_t*, ret));
    RETURN(ret);
} /* T_upper */


PUBLIC new_bchars_t  utf8_of_wide( const wchar_t*  string_ ) {             /*F*/
    GO                                                            (UID(F85A7F));
    /* note: if you modify this function, also check and update: */
    /* function _utf8_from_wide() in libex_pdf.c                 */
    char*  ret = NULL;

#if PLATFORM_LINUX
    const size_t  len       = WCSLEN(string_);
    const size_t  utf8_size = (len + 1) * sizeof(char);

    mbstate_t  state;

    CLEAR(state);
    ret = MALLOC(utf8_size);
    MEMSET(ret, 0x00, utf8_size);
    WCSRTOMBS(ret, &string_, len, &state);
    RETURN(ret);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    int  dest_len = 0;

    if (string_ == NULL) {
        RETURN(NULL);
    }

    /* determine number of bytes needed for output buffer */
    dest_len =
        WideCharToMultiByte_win(
            CP_UTF8_win,  /* CodePage: 8-bit Unicode transform. fmt. */
            0,            /* dwFlags: must be NULL for CP_UTF8_win   */
            string_,      /* lpWideCharStr                           */
            -1,           /* CCHWideChar - len.-1 = long as required */
            NULL,         /* lpMultiByteStr                          */
            0,            /* cbMultiByte:   0 returns # bytes needed */
            NULL,         /* lpDefaultChar:     NULL for CP_UTF8_win */
            NULL);        /* lpUsedDefaultChar: NULL for CP_UTF8_win */

    if (dest_len < 1) {
        OS_WARN(_T("WideCharToMultiByte()"), UID(E87209));
        RETURN(NULL);
    }

    /* allocate a new character buffer (+ 1 is for \0) */
    ret = CAST(char*, MALLOC(sizeof(char) * CAST(size_t, dest_len + 1)));
    if (ret == NULL) {
        _warn(NULL, UID(E8386D));
        RETURN(NULL);
    }

    CLEAR_N(ret, CAST(size_t, dest_len + 1));

    {
        /* write converted wide characters to character buffer: */
        const int  result = WideCharToMultiByte_win(
                                CP_UTF8_win,  /* CodePage          */
                                0,            /* dwFlags           */
                                string_,      /* lpWideCharStr     */
                                -1,           /* CCHWideChar       */
                                ret,          /* lpMultiByteStr    */
                                dest_len,     /* cbMultiByte       */
                                NULL,         /* lpDefaultChar     */
                                NULL);        /* lpUsedDefaultChar */

        if (!result) {
            OS_WARN(_T("WideCharToMultiByte()"), UID(E70868));
            freeA(&ret);
            RETURN(NULL);
        }
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* utf8_of_wide */


PUBLIC new_wchars_t  wide_of_utf8( const char*  string_ ) {                /*F*/
    GO                                                            (UID(F2BF08));
    wchar_t*  ret = NULL;

#if PLATFORM_LINUX
    const size_t  len  = STRLEN(string_);
    const size_t  wlen = (len + 1) * sizeof(wchar_t);

    ret = MALLOC(wlen);

    MEMSET(ret, 0x00, wlen);
    MBSTOWCS(ret, string_, len);
    *(ret + len) = '\0';
    RETURN(ret);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    int  dest_len = 0;

    if (string_ == NULL) {
        RETURN(NULL);
    }

    /* determine number of bytes needed for output buffer */
    dest_len = MultiByteToWideChar_win(
                   CP_UTF8_win,  /* CodePage: code page                  */
                   0,            /* dwFlags: char-type (0 for CP_UTF8)   */
                   string_,      /* lpMultiByteStr: string to map        */
                   -1,           /* cbMultiByte: of bytes in string      */
                   NULL,         /* lpWideCharStr: wide-character buffer */
                   0);           /* CCHWideChar: size of buffer          */

    if (dest_len < 1) {
        OS_WARN(_T("MultiByteToWideChar_win()"), UID(E68BAB));
        RETURN(NULL);
    }

    /* allocate a new character buffer */
    ret = CAST(wchar_t*, MALLOC(sizeof(wchar_t) * (dest_len + 1)));
    /* +1 for \0 */

    if (ret == NULL) {
        _warn(BLANK, UID(EDEA3F));
        RETURN(NULL);
    }

    CLEAR_N(ret, (dest_len + 1) * sizeof(wchar_t));

    {
        /* write converted wide characters to character buffer: */
        const int  result =
            MultiByteToWideChar_win(
                CP_UTF8_win,  /* CodePage:            code page */
                0,            /* dwFlags: type, 0 = CP_UTF8_win */
                string_,      /* lpMultiByteStr:  string to map */
                -1,           /* cbMultiByte:# of bytes in str. */
                ret,          /* lpWideCharStr: wide-char buff. */
                dest_len);    /* CCHWideChar:    size of buffer */

        if (!result) {
            OS_WARN(_T("Conversion failure."), UID(E89556));
            if (ret != NULL) {
                FREE(&ret);
            }
            RETURN(NULL);
        }
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* wide_of_utf8 */


/* -------------------------------------------------------------------------- */
/* Character String Destructor:                                               */


PUBLIC void  freeA( new_bchars_t*  string_ ) {                             /*F*/
    GO                                                            (UID(D27EE8));
    if (*string_ != NULL) {
        FREE(*string_);
        *string_ = NULL;
    }
    RETURN(NIL);
} /* freeA */


PUBLIC void  freeW( new_wchars_t*  string_ ) {                             /*F*/
    GO                                                            (UID(D8AB71));
    if (*string_ != NULL) {
        FREE(*string_);
        *string_ = NULL;
    }
    RETURN(NIL);
} /* freeW */


/* -------------------------------------------------------------------------- */
/* Functions: In-Place Character String Manipulation                          */


void  change_in_T(                                                         /*F*/
    char_t*    chars_,                                                     /*-*/
    const int  changes_ ) {                                                /*-*/
    GO                                                            (UID(FF8FDF));
    if (!IS_BLANK(chars_)) {
        const size_t  len = lenT(chars_);

        if (len != 0) {
            size_t    i       = 0;
            bool      in_word = false;
            chars_t   rd      = chars_;
            char_t*   wr      = chars_;

            for (i = 0; i < len && *rd != 0; i++) {

                if ((changes_ & MAKE_UPPER_CASE) == MAKE_UPPER_CASE) {
                    *wr = CAST(char_t, TOUPPER_T(*rd));

                } else if ((changes_ & MAKE_LOWER_CASE) == MAKE_LOWER_CASE) {
                    *wr = CAST(char_t, TOLOWER_T(*rd));

                } else if ((changes_ & MAKE_TITLE_CASE) == MAKE_TITLE_CASE) {
                    if (!ISALPHA_T(*rd)) {
                        *wr = *rd;
                        in_word = false;

                    } else if (in_word) {
                        *wr = *rd;
                    } else {
                        *wr = CAST(char_t, TOUPPER_T(*rd));
                        in_word = true;
                    }

                } else {
                    *wr = *rd;
                }
                rd++;
                wr++;
            }
            *wr = '\0';

            if ((changes_ & MAKE_REVERSE) == MAKE_REVERSE) {
                char_t*  reversed = chars_ + len - 1;

                wr = chars_;
                for (i = 0; i < (len / 2) && *reversed != 0; i++) {
                    char_t  ch = *wr;
                    *wr++ = *reversed;
                    *(reversed--) = ch;
                }
            }
            *(chars_ + len) = '\0';
        }
    }
    RETURN(NIL);
} /* change_in_T */


PUBLIC void  lower_in_T( char_t*  string_ref_ ) {                          /*F*/
    GO                                                            (UID(F713DD));
    char_t*  ch = string_ref_;
    while (ch && *ch) {
        *ch = CAST(char_t, TOLOWER_T(*ch));
        ch++;
    }
    RETURN(NIL);
} /* lower_in_T */


PUBLIC void  remove_extra_spaces_in_T( char_t*  string_ref_ ) {            /*F*/
    GO                                                            (UID(F9ACB4));
    const size_t  old_len = STRLEN_T(string_ref_) + 1;
    new_chars_t   new_mem = mallocT(old_len);
    chars_t       rd      = string_ref_;
    char_t*       wr      = new_mem;

    while (rd != NULL && *rd != '\0') {
        bool  ws = false;  /* whitespace */
        bool  cr = false;
        bool  lf = false;

        while (IS_SPACE(*rd)) {
            ws = true;
            if (*rd == '\r') {
                cr = true;
            } else if (*rd == '\n') {
                lf = true;
            } else {
                ws = true;
            }
            rd++;
        }

        if (cr && lf) {
            *wr++ = '\r';
            *wr++ = '\n';
        } else if (cr) {
            *wr++ = '\r';
        } else if (lf) {
            *wr++ = '\n';
        } else if (ws) {
            *wr++ = ' ';
        }

        while (*rd != '\0' && !IS_SPACE(*rd)) {
            *wr++ = *rd++;
        }
    }
    *wr = '\0';

    if (string_ref_ != NULL) {
        STRCPY_S_T(string_ref_, old_len, new_mem);
    }
    freeT(&new_mem);

    RETURN(NIL);
} /* remove_extra_spaces_in_T */


PUBLIC void  replace_in_T(                                                 /*F*/
    new_chars_t*  realloc_var_,                                            /*-*/
    chars_t       find_,                                                   /*-*/
    chars_t       replace_ ) {                                             /*-*/
    GO                                                            (UID(F4DE7C));
    if (realloc_var_ != NULL && contains2T(*realloc_var_, find_)) {
        new_chars_t  move_mem = T_replace(*realloc_var_, find_, replace_,
                                          MATCH_CASE);
        if (*realloc_var_ != NULL) {
            FREE(*realloc_var_);
        }
        *realloc_var_ = move_mem;
    }
    RETURN(NIL);
} /* replace_in_T */


PUBLIC void  set_replace_char(                                             /*F*/
    char*  string_,                                                        /*-*/
    char   find_char_,                                                     /*-*/
    char   replace_char_ ) {                                               /*-*/
    GO                                                            (UID(F91DA5));
    while (*string_ != '\0') {
        if (*string_ == find_char_) {
            *string_ = replace_char_;
        }
        string_++;
    }
    RETURN(NIL);
} /* set_replace_char */


PUBLIC void  replace_char_in_T(                                            /*F*/
    char_t*  string_,                                                      /*-*/
    char_t   find_char_,                                                   /*-*/
    char_t   replace_char_ ) {                                             /*-*/
    GO                                                            (UID(F44D86));
    while (*string_ != '\0') {
        if (*string_ == find_char_) {
            *string_ = replace_char_;
        }
        string_++;
    }
    RETURN(NIL);
} /* replace_char_in_T */


PUBLIC void  title_in_T( char_t*  string_ref_ ) {                          /*F*/
    GO                                                            (UID(F9AB56));
    change_in_T(string_ref_, MAKE_TITLE_CASE);
    RETURN(NIL);
} /* title_in_T */


PUBLIC void  trim_in_T( char_t*  string_ref_ ) {                           /*F*/
    GO                                                            (UID(F69861));
    trim4_in_T(string_ref_, WHITESPACES, true, true);
    RETURN(NIL);
} /* trim_in_T */


PUBLIC void  trim4_in_T(                                                   /*F*/
    char_t*     string_ref_,                                               /*-*/
    chars_t     trim_chars_,                                               /*-*/
    const bool  trim_begin_,                                               /*-*/
    const bool  trim_end_ ) {                                              /*-*/
    GO                                                            (UID(F1C7B0));
    if (string_ref_ != NULL) {
        size_t  len = STRLEN_T(string_ref_);

        if (len > 0 && trim_begin_) {
            const size_t  trim = STRSPN_T(string_ref_, trim_chars_);

            if (trim > 0) {
                char_t*  ch = string_ref_;
                do {
                    *ch = *(ch + trim);
                } while (*((ch++) + trim));

                len -= trim;
            }
        }

        if (len > 0 && trim_end_) {
            char_t*  ch = string_ref_ + len - 1;

            while (ch > string_ref_ && STRCHR_T(trim_chars_, *ch)) {
                *(ch--) = '\0';
            }
        }
    }
    RETURN(NIL);
} /* trim4_in_T */


PUBLIC void  upper_in_T( char_t*  string_ref_ ) {                          /*F*/
    GO                                                            (UID(F0243D));
    char_t*  ch = string_ref_;
    while (ch && *ch) {
        *ch = CAST(char_t, TOUPPER_T(*ch));
        ch++;
    }
    RETURN(NIL);
} /* upper_in_T */


/* -------------------------------------------------------------------------- */
/* Functions: Informative                                                     */


PUBLIC uint32_t  hex_value( chars_t  hex_ ) {                              /*F*/
    GO                                                            (UID(FA4A45));
    /* note: strtoul() standard library function does the same */

    uint32_t      ret = 0;
    const size_t  len = STRLEN_T(hex_);

    if (len > 8) {
        WARN(_T("invalid hex value."), UID(E0E396));
    } else {
        chars_t   ch    = hex_ + len - 1;
        uint32_t  digit = 0;
        uint32_t  power = 1;
        uint32_t  i     = 0;

        for (i = 0; i < len; i++) {
            digit = HEX_DIGIT_VAL(*ch);

            if (digit > 15) {
                RETURN(0);
            }
            ch--;
            ret += digit * power;
            power *= 16;
        }
    }
    RETURN(ret);
} /* hex_value */


PUBLIC bool  begins3T(                                                     /*F*/
    chars_t     main_str_,                                                 /*-*/
    chars_t     find_str_,                                                 /*-*/
    const bool  ignore_case_ ) {                                           /*-*/
    GO                                                            (UID(F300F0));
    size_t  i         = 0;
    size_t  str_len   = 0;
    size_t  find_len  = 0;
    size_t  match_len = 0;

    if (IS_BLANK(main_str_) && IS_BLANK(find_str_)) {
        RETURN(true);
    }

    if (IS_BLANK(main_str_) || IS_BLANK(find_str_)) {
        RETURN(false);
    }

    /* use an approach that doesn't require lenT() */
    find_len = lenT(find_str_);
    if (find_len < 1) {
        RETURN(false);
    }

    str_len = lenT(main_str_);
    if (str_len < 1) {
        RETURN(false);
    }

    if (find_len > str_len) {
        RETURN(false);
    }

    match_len = 0;

    for (i = 0; i < find_len; i++) {
        if (ignore_case_ ? TOLOWER_T(*main_str_) == TOLOWER_T(*find_str_)
            : *main_str_ == *find_str_) {
            match_len++;
        } else {
            RETURN(false);
        }

        main_str_++;
        find_str_++;
    }

    {
        const bool  ret = C_BOOL(match_len == find_len);
        RETURN(ret);
    }
} /* begins3T */


PUBLIC bool  containsT(                                                    /*F*/
    chars_t       string_,                                                 /*-*/
    chars_t       substring_,                                              /*-*/
    const bool    ignore_case_,                                            /*-*/
    const size_t  string_len_,                                             /*-*/
    const size_t  substring_len_ ) {                                       /*-*/
    GO                                                            (UID(F304D4));
    const bool  ret = C_BOOL(findT(string_,         /* main_str_    */
                                   substring_,      /* find_str_    */
                                   0,               /* offset_      */
                                   ignore_case_,    /* ignore_case_ */
                                   false,           /* from_end_    */
                                   string_len_,     /* main_len_    */
                                   substring_len_)  /* find_len_    */
                             != NONE);
    RETURN(ret);
} /* containsT */


PUBLIC size_t  countT(                                                     /*F*/
    chars_t       main_str_,                                               /*-*/
    chars_t       find_str_,                                               /*-*/
    const size_t  offset_,                                                 /*-*/
    const bool    ignore_case_,                                            /*-*/
    const bool    reverse_,                                                /*-*/
    const size_t  main_len_,                                               /*-*/
    const size_t  find_len_,                                               /*-*/
    const size_t  max_count_,                                              /*-*/
    size_t*       location_out_ ) {                                        /*-*/
    GO                                                            (UID(F2D2C4));
    /* return the number of substrings in the specified string.      */
    /* ignore_case_: MATCH_CASE  - applies case-sensitive match      */
    /*               IGNORE_CASE - applies a case-insensitive match  */
    /*                             otherwise it is case-insensitive. */

    chars_t  str       = NULL;
    chars_t  find      = NULL;
    size_t   i         = 0;
    size_t   count     = 0;
    size_t   match_len = 0;

    const size_t  str_len  = len_maxT(main_str_, main_len_);
    const size_t  find_len = len_maxT(find_str_, find_len_);

    str  = reverse_ ? main_str_ + str_len  - 1 : main_str_ + offset_;
    find = reverse_ ? find_str_ + find_len - 1 : find_str_;

    if (IS_BLANK(main_str_) || IS_BLANK(find_str_) ||
        (find_len < 1 || offset_ + find_len > str_len) ||
        (str_len  < 1 || offset_ > str_len - 1)) {

        if (location_out_) {
            *location_out_ = NONE;
        }
        RETURN(0);
    }

    /* search for string */
    for (i = 0; i < (str_len - offset_); i++) {
        if (reverse_ && i > str_len - offset_ - 1) {
            break;
        }

        if (ignore_case_ ? TOLOWER_T(*str) == TOLOWER_T(*find)
            : *str == *find) {
            find += reverse_ ? -1 : 1;

            if (++match_len == find_len) {
                const size_t  pos = reverse_ ? str_len - i - 1
                                    : offset_ + i + 1 - match_len;

                if (location_out_) {
                    *location_out_ = pos;
                }

                if (++count >= max_count_) {
                    break;
                }
            }
        } else if (match_len) {
            if (match_len < find_len) {
                i -= match_len;
                str = (reverse_ ? str + match_len : str - match_len);
            }
            find = find_str_ + (reverse_ ? find_len - 1 : 0);
            match_len = 0;
        }
        str += reverse_ ? -1 : 1;
    }
    RETURN(count);
} /* countT */


PUBLIC bool  endsT(                                                        /*F*/
    chars_t       main_str_,                                               /*-*/
    chars_t       find_str_,                                               /*-*/
    const bool    ignore_case_,                                            /*-*/
    const size_t  main_len_,                                               /*-*/
    const size_t  find_len_ ) {                                            /*-*/
    GO                                                            (UID(FDF4E0));
    size_t  str_len   = 0;
    size_t  find_len  = 0;
    size_t  match_len = 0;

    if (IS_BLANK(main_str_) && IS_BLANK(find_str_)) {
        RETURN(true);
    }

    if (IS_BLANK(main_str_) || IS_BLANK(find_str_)) {
        RETURN(false);
    }

    find_len = len_maxT(find_str_, find_len_);
    if (find_len < 1) {
        RETURN(false);
    }

    str_len = len_maxT(main_str_, main_len_);
    if (str_len < 1) {
        RETURN(false);
    }

    if (find_len > str_len) {
        RETURN(false);
    }

    /* start matching from the end of both strings */
    match_len = 0;
    main_str_ += (str_len  - 1);
    find_str_ += (find_len - 1);

    {
        size_t  i = 0;
        for (i = 0; i < find_len; i++) {
            if (ignore_case_ ? TOLOWER_T(*main_str_) == TOLOWER_T(*find_str_)
                : *main_str_ == *find_str_) {
                match_len++;
            } else {
                RETURN(false);
            }
            main_str_--;
            find_str_--;
        }
    }

    {
        const bool  ret = C_BOOL(match_len == find_len);
        RETURN(ret);
    }
} /* endsT */


PUBLIC bool  equalsT(                                                      /*F*/
    chars_t       string1_,                                                /*-*/
    chars_t       string2_,                                                /*-*/
    const bool    ignore_case_,                                            /*-*/
    const size_t  check_len_ ) {                                           /*-*/
    GO                                                            (UID(F97397));
    if (IS_BLANK(string1_) && IS_BLANK(string2_)) {
        RETURN(true);

    } else if (check_len_ == 0 || IS_BLANK(string1_) || IS_BLANK(string2_)) {
        RETURN(false);
    }

    {
        size_t  ctr1 = STRLEN_T(string1_);
        size_t  ctr2 = STRLEN_T(string2_);

        if (check_len_ == SIZE_MAX && (ctr1 != ctr2)) {
            RETURN(false);
        }

        {
            size_t  check = check_len_;
            while (check && ctr1-- && ctr2-- && *string1_ && *string2_) {
                check--;

                if (ignore_case_
                    ? TOLOWER_T(*string1_) != TOLOWER_T(*string2_)
                    : *string1_ != *string2_) {
                    RETURN(false);
                }

                string1_++;
                string2_++;
            }

            {
                const bool  ret = C_BOOL(check == 0 || *string1_ == *string2_);
                RETURN(ret);
            }
        }
    }
} /* equalsT */


PUBLIC size_t  findT(                                                      /*F*/
    chars_t       main_str_,                                               /*-*/
    chars_t       find_str_,                                               /*-*/
    const size_t  offset_,                                                 /*-*/
    const bool    ignore_case_,                                            /*-*/
    const bool    from_end_,                                               /*-*/
    const size_t  main_len_,                                               /*-*/
    const size_t  find_len_ ) {                                            /*-*/
    GO                                                            (UID(F6353E));
    size_t  ret = NONE;

    if (IS_BLANK(main_str_) && IS_BLANK(find_str_)) {
        RETURN(0);
    }

    countT(main_str_, find_str_, offset_, ignore_case_, from_end_, main_len_,
           find_len_, 1, &ret);
    RETURN(ret);
} /* findT */


PUBLIC size_t  find_charT(                                                 /*F*/
    chars_t       main_str_,                                               /*-*/
    const char_t  find_char_,                                              /*-*/
    const size_t  offset_,                                                 /*-*/
    const bool    ignore_case_,                                            /*-*/
    const bool    from_end_ ) {                                            /*-*/
    GO                                                            (UID(FB6D7F));
    size_t  ret = NONE;

    CHAR_TO_STR(ch_str, find_char_);
    countT(main_str_, ch_str, offset_, ignore_case_, from_end_, SIZE_MAX,
           SIZE_MAX, 1, &ret);
    RETURN(ret);
} /* find_charT */


PUBLIC size_t  find_charsT(                                                /*F*/
    chars_t       main_str_,                                               /*-*/
    chars_t       chars_,                                                  /*-*/
    const bool    ignore_case_,                                            /*-*/
    const size_t  main_len_ ) {                                            /*-*/
    GO                                                            (UID(F199EE));
    if (!IS_BLANK(main_str_) && !IS_BLANK(chars_)) {
        chars_t  str     = main_str_;
        size_t   a       = 0;
        size_t   str_len = 0;

        if (main_len_ < SIZE_MAX) {
            str_len = main_len_;
        } else {
            str_len = STRLEN_T(main_str_);
        }

        for (a = 0; a < str_len && *str != '\0'; a++) {

            const size_t  find_len = len_maxT(chars_, str_len);
            size_t        b        = 0;
            chars_t       find     = chars_;

            for (b = 0; b < find_len && *find != '\0'; b++) {
                if (ignore_case_ ? TOLOWER_T(*str) == TOLOWER_T(*find)
                    : *str == *find) {
                    RETURN(a);
                }
                find++;
            }
            str++;
        }
    }
    RETURN(NONE);
} /* find_charsT */


PUBLIC size_t  find_last3T(                                                /*F*/
    chars_t     string_,                                                   /*-*/
    chars_t     find_,                                                     /*-*/
    const bool  ignore_case_ ) {                                           /*-*/
    GO                                                            (UID(FFA222));
    size_t    ret   = NONE;
    chars_t   found = NULL;

    if (string_ == NULL || string_[0] == '\0' ||
        find_ == NULL   || find_[0]   == '\0') {
        RETURN(ret);
    }

    do {
        if (ignore_case_) {
            found = strstriT(string_, find_);
        } else {
            found = STRSTR_T(string_, find_);
        }

        if (found) {
            if (ret == NONE) {
                ret = 0;
            }
            ret += CAST(size_t, found - string_);
        }
    } while (found);

    RETURN(ret);
} /* find_last3T */


PUBLIC bool  is_numberT(                                                   /*F*/
    chars_t       string_,                                                 /*-*/
    const char_t  decimal_point_char_,                                     /*-*/
    const char_t  group_separator_char_,                                   /*-*/
    chars_t       whitespaces_ ) {                                         /*-*/
    GO                                                            (UID(F3C323));
    bool    has_dec_point = false;
    bool    has_digit     = false;
    bool    has_sign      = false;
    bool    prev_sep      = false;
    size_t  len           = 0;

    if (IS_BLANK(string_)) {
        RETURN(false);
    }

    len = STRLEN_T(string_);
    if (len < 1) {
        RETURN(false);
    }

    /* skip leading whitespaces */
    while (len > 0 && STRCHR_T(whitespaces_, *string_)) {
        string_++;
        len--;
    }

    /* skip trailing whitespaces (by reducing len) */
    while (len > 0 && STRCHR_T(whitespaces_, *(string_ + len - 1))) {
        len--;
    }

    do {
        if (ISDIGIT_T(*string_)) {
            has_digit = true;
            prev_sep = false;
            continue;

            /* note: two consecutive group separators make string non-numeric */
        } else if (*string_ == group_separator_char_) {
            if (prev_sep) {
                RETURN(false);
            } else if (!has_digit) {
                RETURN(false);
            } else {
                prev_sep = true;
                continue;
            }
        } else if (*string_ == '-' || *string_ == '+') {
            if (has_sign) {
                RETURN(false);
            } else if (has_digit) {
                RETURN(false);
            } else {
                has_sign = true;
            }
        } else if (*string_ == decimal_point_char_) {
            if (has_dec_point) {
                RETURN(false);
            } else {
                has_dec_point = true;
            }
        } else {
            RETURN(false);
        }
        prev_sep = false;
    } while (--len && *(++string_));

    RETURN(has_digit);
} /* is_numberT */


PUBLIC bool  is_whitespaceT( chars_t  string_ ) {                          /*F*/
    GO                                                            (UID(F4B6F5));
    if (IS_BLANK(string_)) {
        RETURN(false);
    }

    do {
        if (*string_ != ' '  && *string_ != '\a' && *string_ != '\b' &&
            *string_ != '\f' && *string_ != '\n' && *string_ != '\r' &&
            *string_ != '\t' && *string_ != '\v') {
            RETURN(false);
        }
    } while (*(++string_));

    RETURN(true);
} /* is_whitespaceT */


PUBLIC bool  is_wide( const void*  string_ ) {                             /*F*/
    GO                                                            (UID(F19842));
    const bool  ret = is_wide_n(string_, SIZE_MAX);
    RETURN(ret);
} /* is_wide */


PUBLIC bool  is_wide_n(                                                    /*F*/
    const void*   string_,                                                 /*-*/
    const size_t  max_len_in_bytes_ ) {                                    /*-*/
    GO                                                            (UID(FBD915));
    bool  ret = false;

    /* if string_ is a null pointer, return false right away */
    if (string_ == NULL) {
        RETURN(false);
    }

#if PLATFORM_LINUX
    {
        const uint8_t*  str      = CAST(const uint8_t*, string_);
        const size_t    clen = STRLEN(CAST(char*, string_));
        const size_t    wlen = WCSLEN(CAST(wchar_t*, string_)) * 4;
        /* (4 bytes for each wide char) */
        size_t          i        = 0;

        size_t  len = GREATER(clen, wlen);
        if (len > max_len_in_bytes_) {
            len = max_len_in_bytes_;
        }

        /* if the string contains any 0, it's Unicode */
        for (i = 0; i < len; i++) {
            if (str[i] == 0) {
                RETURN(true);
            }
        }
    }
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    {
        size_t  blen = STRLEN(CAST(char*, string_));

        if (blen > 1) {
            if (blen > max_len_in_bytes_) {
                blen = max_len_in_bytes_;
            }

#pragma comment (lib, "Advapi32.lib")
            ret = C_BOOL(IsTextUnicode_win(
                             string_, CAST(int, blen), NULL) == TRUE_win);
        } else {
            /* (2 bytes for each wide char) */
            size_t  wlen = WCSLEN(CAST(wchar_t*, string_)) * 2;

            if (wlen > max_len_in_bytes_) {
                wlen = max_len_in_bytes_;
            }

            ret = C_BOOL(IsTextUnicode_win(
                             string_, CAST(int, wlen), NULL)
                         == TRUE_win);
        }
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* is_wide_n */


PUBLIC size_t  lenT( chars_t  string_ ) {                                  /*F*/
    GO                                                            (UID(F34913));
    size_t  ret = 0;
    if (string_ != NULL && *string_ != '\0') {
        ret = STRLEN_T(string_);
    }
    RETURN(ret);
} /* lenT */


PUBLIC size_t  len_maxT(                                                   /*F*/
    chars_t       string_,                                                 /*-*/
    const size_t  max_len_ ) {                                             /*-*/
    GO                                                            (UID(F0A388));
    size_t  ret = 0;

    if (string_ != NULL) {
        while (*string_ != '\0' && ret < max_len_) {
            string_++;
            ret++;
        }
    }
    RETURN(ret);
} /* len_maxT */


PUBLIC int  line_countT( chars_t  string_ ) {                              /*F*/
    GO                                                            (UID(F7DECA));
    int      ret = IS_BLANK(string_) ? 0 : 1;
    bool     cr  = false;
    char_t   ch  = '\0';
    chars_t  str = string_;

    while (str && *str) {
        ch = *str++;

        if (ch == '\r') {             /* carriage return (CR, hex:0d, dec:13) */
            ret++;
            cr = true;

        } else if (ch == '\n') {               /* new line (LF, hex:0a, dec:10) */
            if (!cr) {
                ret++;
            }
            cr = false;

        } else {                                      /* all other characters */
            cr = false;
        }
    }
    RETURN(ret);
} /* line_countT */


PUBLIC bool  patternMatchT(                                                /*F*/
    chars_t     string_,                                                   /*-*/
    chars_t     pattern_,                                                  /*-*/
    const bool  ignore_case_ ) {                                           /*-*/
    GO                                                            (UID(F29054));
    chars_t  str = NULL;
    chars_t  pat = NULL;

    if (IS_BLANK(string_) || IS_BLANK(pattern_)) {
        RETURN(false);
    }

    while (*pattern_ != '*' && *string_ != '\0') {
        if (*pattern_ != '?' &&
            (ignore_case_ ? TOLOWER_T(*pattern_) != TOLOWER_T(*string_)
             : *pattern_ != *string_)) {
            RETURN(false);
        }
        pattern_++;
        string_++;
    }

    str = pattern_;
    pat = string_ + 1;

    while (*string_ != '\0') {
        if (*pattern_ == '*') {
            pattern_++;
            if (*pattern_ == '\0') {
                RETURN(true);
            }
            pat = pattern_;
            str = string_ + 1;

        } else if (*pattern_ == '?' ||
                   (ignore_case_ ? TOLOWER_T(*pattern_) == TOLOWER_T(*string_)
                    : *pattern_ == *string_)
                  ) {
            pattern_++;
            string_++;

        } else {
            pattern_ = pat;
            string_ = str;
            str++;
        }
    }

    while (*pattern_ == '*') {
        pattern_++;
    }

    {
        const bool  ret = C_BOOL(!(*pattern_));
        RETURN(ret);
    }
} /* patternMatchT */


PUBLIC size_t  skip_charsT(                                                /*F*/
    chars_t       main_str_,                                               /*-*/
    chars_t       chars_to_skip_,                                          /*-*/
    const bool    ignore_case_,                                            /*-*/
    const size_t  main_len_ ) {                                            /*-*/
    GO                                                            (UID(F9D208));
    chars_t       main_str = main_str_;
    chars_t       find     = NULL;
    bool          found    = false;
    size_t        a        = 0;
    size_t        b        = 0;
    const size_t  str_len  = len_maxT(main_str_, main_len_);
    const size_t  find_len = len_maxT(chars_to_skip_, str_len);

    if (IS_BLANK(main_str_) || IS_BLANK(chars_to_skip_)) {
        RETURN(NONE);
    }

    for (a = 0; a < str_len && *main_str != '\0'; a++) {
        found = false;
        find  = chars_to_skip_;

        for (b = 0; b < find_len && *find != '\0'; b++) {
            if (ignore_case_ ? TOLOWER_T(*main_str) == TOLOWER_T(*find)
                : *main_str == *find) {
                found = true;
                break;
            }
            find++;
        }

        if (!found) {
            RETURN(a);
        }

        main_str++;
    }
    RETURN(NONE);
} /* skip_charsT */


PUBLIC size_t  substr_lenT(                                                /*F*/
    chars_t       main_str_,                                               /*-*/
    const size_t  main_len_,                                               /*-*/
    const size_t  offset_,                                                 /*-*/
    const size_t  substr_len_ ) {                                          /*-*/
    GO                                                            (UID(F18699));
    size_t  ret = 0;

    if (main_len_ >= 1 && substr_len_ >= 1 && offset_ < main_len_) {
        const size_t  str_len = len_maxT(main_str_, main_len_);

        if (substr_len_ == SIZE_MAX || offset_ + substr_len_ > str_len) {
            ret = str_len <= offset_ ? 0 : str_len - offset_;
        } else {
            ret = substr_len_;
        }
    }
    RETURN(ret);
} /* substr_lenT */


PUBLIC double  doubleT( chars_t  string_ ) {                               /*F*/
    GO                                                            (UID(F0C939));
    double  ret = 0;
    if (!IS_BLANK(string_)) {
        ret = ATOF_T(string_);
        /* floor() = the largest integer that isn't greater than argument */
        ret = floor(ret * 10e10f + 1) / 10e10f;
    }
    RETURN(ret);
} /* doubleT */


PUBLIC int  int_T( chars_t  string_ ) {                                    /*F*/
    GO                                                            (UID(F6E18D));
    int  digits[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    int           digit_count = 0;
    int           number      = 0;
    int           ret         = 0;
    size_t        i           = 0;
    const size_t  len         = LESSER(STRLEN_T(string_), 16);
    bool          has_minus   = false;
    char_t        ch          = '\0';

    if (len == 0 && IS_BLANK(string_)) {
        RETURN(0);
    }

    /* parse the string and store each digit as a value from 0 to 9 */
    for (i = 0; i < len; i++) {
        ch = string_[i];
        if (ch >= '0' && ch <= '9') {
            ch -= '0';
            digits[digit_count++] = ch;

        } else if (ch == ','  || ch == ' '  || ch == '\a' ||
                   ch == '\b' || ch == '\f' || ch == '\n' ||
                   ch == '\r' || ch == '\t' || ch == '\v') {
            ;    /* ignore comma and whitespaces */

        } else if (ch == '-' && !has_minus) {
            has_minus = true;

        } else {
            break;
        }
    }

    /* calculate numeric value of each digit and add it to the result */
    if (digit_count > 0) {
        number = 1;
        i = CAST(size_t, digit_count - 1);
        do {
            ret += digits[i] * number;
            number *= 10;
        } while (i--);
    }

    if (has_minus) {
        ret = -ret;
    }
    RETURN(ret);
} /* int_T */


PUBLIC size_t  token_infoT(                                                /*F*/
    token_info_enum  mode_,                                                /*-*/
    chars_t          list_,                                                /*-*/
    chars_t          delimiter_,                                           /*-*/
    chars_t          token_ ) {                                            /*-*/
    GO                                                            (UID(F498F3));
    const size_t  ret = token_info_xtT(mode_, list_, delimiter_, token_,
                                       MATCH_CASE, SIZE_MAX, SIZE_MAX);
    RETURN(ret);
} /* token_infoT */


PUBLIC size_t  token_info_xtT(                                             /*F*/
    const token_info_enum  mode_,                                          /*-*/
    chars_t                list_,                                          /*-*/
    chars_t                delimiter_,                                     /*-*/
    chars_t                token_,                                         /*-*/
    const bool             ignore_case_,                                   /*-*/
    const size_t           list_len_,                                      /*-*/
    const size_t           token_len_ ) {                                  /*-*/
    GO                                                            (UID(FBA56B));
    /* return true if a token_ exists in list_ delimited by delimiter_    */
    /* when mode_ is TOKEN_EXISTS, or its position when mode_ is          */
    /*               TOKEN_INDEX, or count the number of its              */
    /*               occurrences when mode_ is TOKEN_COUNT.               */
    /* ignore_case_: if false (default), applies a case-sensitive  match, */
    /*               otherwise it is case-insensitive.                    */

    const size_t  delim_len = STRLEN_T(delimiter_);
    const size_t  list_len  = len_maxT(list_, list_len_);
    const size_t  token_len = len_maxT(token_, token_len_);
    size_t        i         = 0;
    size_t        count     = 0;
    size_t        index     = 0;
    size_t        ret       = 0;
    size_t        sub_len   = 0;
    chars_t       cursor    = list_;

    for (i = 0; i <= list_len; i++) {
        const bool  by_end = C_BOOL(i == list_len || *cursor == '\0');

        /* check if current list position is on a delimiter */
        bool  by_delimiter = false;
        if (!by_end) {
            chars_t  cur     = cursor;
            chars_t  delim   = delimiter_;
            size_t   matches = 0;

            while (*cur != '\0' && *delim != '\0' &&
                   (ignore_case_ ? TOLOWER_T(*cur) == TOLOWER_T(*delim)
                    : *cur == *delim)) {
                matches++;
                cur++;
                delim++;
            }

            if (matches == delim_len) {
                by_delimiter = true;
            }
        }

        if (by_delimiter || by_end) {

            if (token_len == 0) {
                count++;

            } else if (sub_len == token_len) {
                chars_t  cur     = cursor - sub_len;
                chars_t  delim   = token_;
                size_t   matches = 0;

                while (*cur != '\0' && *delim != '\0' &&
                       (ignore_case_ ? TOUPPER_T(*cur) == TOUPPER_T(*delim)
                        : *cur == *delim)) {
                    matches++;
                    cur++;
                    delim++;
                }

                if (matches == token_len) {
                    switch (mode_) {
                            CASE(TOKEN_EXISTS, RETURN(true));
                            CASE(TOKEN_INDEX,  RETURN(index));
                            CASE(TOKEN_COUNT,  count++);
                        default:
                            _warn(_T("Unknown mode."), UID(E27D44));
                            RETURN(false);
                    }
                }
            }

            if (by_end) {
                break;
            } else {
                sub_len = 0;
                cursor += delim_len;
                index++;
                i += delim_len - 1;
            }
        } else {
            cursor++;
            sub_len++;
        }
    }

    switch (mode_) {
            CASE(TOKEN_EXISTS, ret = false);
            CASE(TOKEN_INDEX,  ret = NONE);
            CASE(TOKEN_COUNT,  ret = count);
        default:
            _warn(_T("Unknown mode."), UID(EB3A31));
            RETURN(false);
    }
    RETURN(ret);
} /* token_info_xtT */


PUBLIC int  token_countT(                                                  /*F*/
    chars_t  string_,                                                      /*-*/
    chars_t  delimiter_ ) {                                                /*-*/
    GO                                                            (UID(F6BBAA));
    const size_t  delimiter_len = STRLEN_T(delimiter_);

    if (IS_BLANK(string_)) {
        RETURN(0);
    }

    if (delimiter_len < 1) {
        RETURN(1);
    }

    {
        int      count = 1;
        chars_t  str   = string_;

        while (str != NULL) {
            str = STRSTR_T(str, delimiter_);
            if (str != NULL) {
                str += delimiter_len;
                count++;
            }
        }
        RETURN(count);
    }
} /* token_countT */


PUBLIC uint32_t  uint_of_T( chars_t  string_ ) {                           /*F*/
    GO                                                            (UID(FB43CB));
    if (IS_BLANK(string_)) {
        RETURN(0);
    }

    if (is_whitespaceT(string_)) {
        RETURN(0);
    }

    {
        const size_t  ret = STRTOUL_T(string_, NULL, 10);
        RETURN(ret);
    }
} /* uint_of_T */


PUBLIC bool  is_unicode_mode( void ) {                                     /*F*/
    GO                                                            (UID(F247E7));
#if defined UNICODE || defined _UNICODE
    const bool  ret = true;
#else
    const bool  ret = false;
#endif
    RETURN(ret);
} /* is_unicode_mode */


/* -------------------------------------------------------------------------- */
/* Functions: UTF-8                                                           */


/* Return the number of Unicode characters (code points) in a UTF8 string,    */
/* excluding the terminating zero. for validation, use utf8_is_valid().    */
PUBLIC size_t  utf8_len( chars_t  string_ ) {                              /*F*/
    GO                                                            (UID(F75B31));
    size_t  ret = 0;

    if (string_ != NULL) {
        chars_t  rd = string_;
        while ('\0' != *rd) {
            if (0x80 != (0xC0 & *rd++)) {
                ret++;
            }
        }
    }
    RETURN(ret);
} /* utf8_len */


/* -------------------------------------------------------------------------- */
/* Functions: Windows-specific OLE Strings                                    */
#if PLATFORM_WIN32


PUBLIC new_chars_t  T_bstr( const BSTR_win  text_ ) {                      /*F*/
    GO                                                            (UID(F5587F));
    char_t*  ret = NULL;

    if (text_ != NULL) {
        const int  byte_len = CAST(int, SysStringByteLen_win(text_));
        /* excludes terminating zero. (link with oleaut32.lib) */

        if (byte_len != 0) {
            const bool  is_wide = is_wide_n(text_, byte_len) ? true : false;

#if defined UNICODE || defined _UNICODE
            if (is_wide) {
                ret = T_chars_n(CAST(chars_t, text_), byte_len / 2);
            } else {
                ret = wide_of_utf8(CAST(char*, text_));
            }
#else                                                  /* UNICODE || _UNICODE */
            if (!is_wide) {
                ret = T_chars_n(CAST(chars_t, text_), byte_len);
            } else {
                ret = utf8_of_wide(text_);
            }
#endif                                               /* !UNICODE && !_UNICODE */
        }
    }
    RETURN(ret);
} /* T_bstr */


/* Allocate a COM/Automation string from a narrow character string.           */
/* Calls SysAllocString() (oleauto.h  Oleaut32.lib). By default, this is      */
/* a wide Unicode string. Use bstr_exA("", false) for a narrow string.        */
PUBLIC BSTR_win  bstrA( const char*   text_ ) {                            /*F*/
    GO                                                            (UID(F52977));
    const BSTR_win  ret = bstr_exA(text_, true);
    RETURN(ret);
} /* bstrA */


PUBLIC BSTR_win  bstr_of_T( chars_t  text_ ) {                             /*F*/
    GO                                                            (UID(FB9528));
#if defined UNICODE || defined _UNICODE
    BSTR_win  ret = bstr_exW(text_, true);
#else
    BSTR_win  ret = bstr_exA(text_, true);
#endif
    RETURN(ret);
} /* bstr_of_T */


/* Allocate a COM/Automation string from a narrow character string.           */
/* Calls API func. SysAllocString() and SysAllocStringByteLen (in oleauto.h). */
PUBLIC BSTR_win  bstr_exA(                                                 /*F*/
    const char*  text_,                                                    /*-*/
    const bool   make_wide_ ) {                                            /*-*/
    GO                                                            (UID(FB780A));
    BSTR_win  ret = NULL;

    if (make_wide_) {
        new_wchars_t  buf = wide_of_utf8(text_);
        ret = SysAllocString_win(buf);
        freeW(&buf);
    } else {
        const UINT_win  len = CAST(UINT_win, STRLEN(text_));
        ret = SysAllocStringByteLen_win(text_, len);
    }
    RETURN(ret);
} /* bstr_exA */


PUBLIC BSTR_win  bstr_exT(                                                 /*F*/
    chars_t     text_,                                                     /*-*/
    const bool  make_wide_ ) {                                             /*-*/
    GO                                                            (UID(F8B80D));
#if defined UNICODE || defined _UNICODE
    const BSTR_win  ret = bstr_exW(text_, make_wide_);
#else
    const BSTR_win  ret = bstr_exA(text_, make_wide_);
#endif
    RETURN(ret);
} /* bstr_exT */


PUBLIC BSTR_win  bstrW( const wchar_t*  text_ ) {                          /*F*/
    GO                                                            (UID(FA6128));
    const BSTR_win  ret = bstr_exW(text_, true);
    RETURN(ret);
} /* bstrW */


PUBLIC BSTR_win  bstr_exW(                                                 /*F*/
    const wchar_t*  text_,                                                 /*-*/
    const bool      make_wide_ ) {                                         /*-*/
    GO                                                            (UID(F3FEB2));
    BSTR_win  ret;
    if (make_wide_) {
        ret = SysAllocString_win(text_);

    } else {
        const UINT_win  len = CAST(UINT_win, WCSLEN(text_));
        char*           buf = utf8_of_wide(text_);

        ret = SysAllocStringByteLen_win(buf, len);
        FREE(buf);
    }
    RETURN(ret);
} /* bstr_exW */

#endif                                                      /* PLATFORM_WIN32 */

/*
    This file uses the following library functions:
    --------------------------------------------------------------------------------
    ALIAS FUNC.     C-LIBRARY FN.        HEADER FILE
    --------------------------------------------------------------------------------
    ATOF_T          atof / _wtof         math.h and stdlib.h / stdlib.h or wchar.h
    FREE            free                 stdlib.h and malloc.h
    ISALPHA_T       isalpha / iswalpha   ctype.h or wchar.h / wchar.h
    ISDIGIT_T       isdigit / iswdigit   ctype.h or wchar.h / wchar.h
    MALLOC          malloc               stdlib.h and malloc.h
    MBSTOWCS        mbstowcs             stdlib.h
    MEMCPY          memcpy               memory.h or string.h
    MEMSET          memset               memory.h or string.h
    PRINTF_T        printf / wprintf     stdio.h / wchar.h
    QSORT           qsort                stdlib.h and search.h
    REALLOC         realloc              stdlib.h and malloc.h
    SNPRINTF_T      snprintf / swprintf  stdio.h / stdio.h or wchar.h
    STRCAT_S_T      strcat / wcscat      string.h / string.h or wchar.h
    STRCHR_T        strchr / wcschr      string.h / string.h or wchar.h
    STRCMP_T        strcmp / wcscmp      string.h / string.h or wchar.h
    STRCPY_S_T      strcpy / wcscpy      string.h / string.h or wchar.h
    STRLEN          strlen               string.h
    STRLEN_T        strlen / wcslen      string.h / string.h or wchar.h
    STRNCAT_S_T     strncat / wcsncat    string.h / string.h or wchar.h
    STRNCPY_S_T     strncpy / wcsncpy    string.h / string.h or wchar.h
    STRSPN_T        strspn / wcsspn      string.h / string.h or wchar.h
    STRSTR          strstr               string.h
    STRSTR_T        strstr / wcsstr      string.h / string.h or wchar.h
    STRTOUL_T       strtoul / wcstoul    stdlib.h / stdlib.h or wchar.h
    TOLOWER_T       tolower / towlower   ctype.h / ctype.h or wchar.h
    TOUPPER         toupper              ctype.h
    TOUPPER_T       toupper / towupper   ctype.h / ctype.h or wchar.h
    va_arg          va_arg               stdio.h and stdarg.h
    va_end          va_end               stdio.h and stdarg.h
    va_start        va_start             stdio.h and stdarg.h
    WCSLEN          wcslen               string.h or wchar.h
    WCSRTOMBS       wcsrtombs            wchar.h
    WCSSTR          wcsstr               string.h or wchar.h
    WCSTOMBS        wcstombs             stdlib.h

    Windows functions called from this file:
    IsTextUnicode_win()
    MultiByteToWideChar_win()
    WideCharToMultiByte_win()

    Library macros used in this file:

    _T
    ANSI
    ASSERT
    ATOF_T
    BASE64_DIGITS_A
    BLANK
    bool
    CAST
    CHAR_GET
    CHAR_GET_AT
    CHAR_PUT
    CHAR_TO_STR
    CHARS_H
    CLEAR
    CLEAR_N
    DEBUG
    enable_chars_warnings
    END_NAMESPACE
    ERROR
    FN_NAME
    FREE
    GREATER
    HEX_DIGIT_VAL
    IGNORE_CASE
    IGNORE_CASE_C
    IS_BLANK
    ISALPHA_T
    ISDIGIT_T
    LESSER
    MAKE_LOWER_CASE
    MAKE_REVERSE
    MAKE_TITLE_CASE
    MAKE_UPPER_CASE
    MALLOC
    MATCH_CASE
    MATCH_CASE_C
    MBSTOWCS
    MEMCPY
    MEMSET
    NAMESPACE
    new_chars_t
    NONE
    OS_WARN
    pad_chars
    PLATFORM_LINUX
    PLATFORM_WIN32
    PRINTF_T
    QSORT
    REALLOC
    SNPRINTF_T
    STRCAT_S_T
    STRCHR_T
    STRCMP_T
    STRCPY_S_T
    STRLEN
    STRLEN_T
    STRNCAT_S_T
    STRNCPY_S_T
    STRSPN_T
    STRSTR
    STRSTR_T
    STRTOUL_T
    STRUCT
    TOKEN_COUNT
    TOKEN_EXISTS
    TOKEN_INDEX
    TOLOWER_T
    TOUPPER
    TOUPPER_T
    UID
    UNFINISHED_CODE
    VERIFY
    WARN
    WCSLEN
    WCSRTOMBS
    WCSSTR
    WCSTOMBS
    WHITESPACES
    WIDE

    --------------------------------------------------------------------------------
*/


/* -------------------------------------------------------------------------- */
/* Methods: Unimplemented                                                     */


#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4100)  /* W:L4 unreferenced formal parameter         */
#endif

new_chars_t  pad_chars(                                                    /*F*/
    chars_t       string_,                                                 /*-*/
    const size_t  min_width_,                                              /*-*/
    const bool    align_right_ ) {                                         /*-*/
    GO                                                            (UID(FDA1E6));
    /* TODO: pad_chars() */
    UNUSED(string_);
    UNUSED(min_width_);
    UNUSED(align_right_);

    RETURN(NULL);
} /* pad_chars */


#if defined _MSC_VER
#pragma warning (pop)
#endif


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
