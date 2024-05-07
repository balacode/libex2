/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                [libex_string_class.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_string_class_.h"
#if defined INCLUDED_LIBEX_STRING_CLASS__H

#undef __STRICT_ANSI__
#include <ctype.h>   /* for tolower()           */
#include <limits.h>  /* for SIZE_MAX            */
#include <stdio.h>   /* for printf()  sprintf() */
#include <stdlib.h>  /* for qsort()             */
#include <string.h>  /* for memset()            */

#include "libex_config_.h"

#include "libex_.h"
#include "libex_call_.h"
#include "libex_const_.h"
#include "libex_debug_.h"
#include "libex_error_.h"
#include "libex_macro_.h"
#include "libex_stringc_.h"
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
#define _NUM_BUF_SIZE      64


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)

bool  enable_string_warnings = true;

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


#define _WARN( DETAIL_, SRC_UID_ )                                        /*F*/\
    if (enable_string_warnings)                                                \
    {       _warn(DETAIL_, SRC_UID_, FN_NAME); }                           /*#*/

static void  _warn(                                                        /*F*/
    chars_t const   detail_,                                               /*-*/
    const uint32_t  src_uid_,                                              /*-*/
    chars_t const   func_name_ ) {                                         /*-*/
    GO                                                            (UID(FC3EE7));
    PRINTF_T(_T("\r\n") _T("%s() 0x%0xU warning: %s"), func_name_,
             CAST(uint32_t, src_uid_), detail_);

    /* WARN(detail_, src_uid_); */

    RETURN(NIL);
} /* _warn */


/* -------------------------------------------------------------------------- */
/* Internal Functions: 2                                                      */


/* given a string object ptr, return a modifiable pointer to its characters */
#define _STR( optr_ )                                                     /*F*/\
    CAST(char_t*,                                                              \
         optr_ == NULL ? NULL                                                  \
         : optr_->ext != NULL ? CAST(uint8_t*, optr_->ext) + sizeof(_ext_t)    \
         : CAST(uint8_t*, optr_) + sizeof(_str_t))                         /*#*/


/* given a string object ptr, return a const-pointer to its characters */
#define _CSTR( object_ptr_ )                                              /*F*/\
    CAST(chars_t, _STR(object_ptr_))                                       /*#*/


/* given an object handle, return a pointer to object's internal structure */
static _str_t*  _object(                                                   /*F*/
    str_t           object_,                                               /*-*/
    const uint32_t  uid_ ) {                                               /*-*/
    GO                                                            (UID(FFC059));
    if (object_.cs == NULL) {
        RETURN(NULL);
    }

    /* check that object has been previously initialized */
    if (CAST(unsigned long, object_.cs) == 0xCCCCCCCCU ||
        CAST(unsigned long, object_.cs) == 0xFEEEFEEEU) {
        _WARN(_T("Uninitialized object!"), uid_);
        RETURN(NULL);
    }

    {
        const _ext_t* const  ext =
            CAST(_ext_t*, CAST(uint8_t*, object_.cs) - sizeof(_ext_t));

        _str_t*  ret = NULL;

        if (ext->type == _TYPE_STRING_EXTN) {
            ret = ext->owner;
        } else {
            ret = CAST(_str_t*, CAST(uint8_t*, object_.cs) - sizeof(_str_t));
            if (ret->type == _TYPE_STRING_MAIN) {
                RETURN(ret);
            } else {
                WARN(_T("UNKNOWN STRUCTURE"), UID(E5CACD));
                ret = NULL;
            }
        }
        RETURN(ret);
    }
} /* _object */


/*
    TODO: Create _object_init(), which is the same as _object(), but never returns NULL.
       It will automatically call clearInS() if _object() returns NULL.
*/
static _str_t*  _object_init(                                              /*F*/
    str_t           object_,                                               /*-*/
    const uint32_t  uid_ ) {                                               /*-*/
    GO                                                            (UID(F47AEB));
    _str_t*  ret = _object(object_, uid_);
    if (ret == NULL) {
        clearInS(&object_);
        ret = _object(object_, UID(E1F368));
    }
    RETURN(ret);
} /* _object_init */


/* -------------------------------------------------------------------------- */
/* Internal Functions: 3                                                      */


/* called by qsort(), that's why parameters are 'void' */
static int  _qsort_compare(                                                /*F*/
    const void* const  str1_,                                              /*-*/
    const void* const  str2_ ) {                                           /*-*/
    GO                                                            (UID(F5D2A7));
    /* returns:                      */
    /* < 0 str1_ less than str2_     */
    /*   0 str1_ equivalent to str2_ */
    /* > 0 str1_ greater than str2_  */

    chars_t       str1 = *CAST(chars_t*, str1_);
    chars_t       str2 = *CAST(chars_t*, str2_);
    const size_t  len1 = STRLEN_T(str1);
    const size_t  len2 = STRLEN_T(str2);
    const size_t  len  = LESSER(len1, len2);
    size_t        i    = 0;

    for (i = 0; i < len; i++) {
        if (*str1 > *str2) {
            RETURN(1);
        } else if (*str1 < *str2) {
            RETURN(-1);
        }
        str1++;
        str2++;
    }

    if (len1 > len2) {
        RETURN(1);    /* str1_ >  str2_ */
    } else if (len1 < len2) {
        RETURN(-1);   /* str1_ <  str2_ */
    }
    RETURN(0);            /* str1_ == str2_ */
} /* _qsort_compare */


static int  _qsort_compare_desc(                                           /*F*/
    const void* const  str1_,                                              /*-*/
    const void* const  str2_ ) {                                           /*-*/
    GO                                                            (UID(FE57E6));
    const int  ret = -_qsort_compare(str1_, str2_);
    RETURN(ret);
} /* _qsort_compare_desc */


static void  _copy_to_object(                                              /*F*/
    chars_t       source_,                                                 /*-*/
    const size_t  source_len_,                                             /*-*/
    str_t* const  target_ ) {                                              /*-*/
    GO                                                            (UID(F49CA3));
    _str_t* const  me = _object_init(*target_, UID(E25092));

    /* re-allocate the object's memory if more space is needed */
    if (me == NULL || source_len_ > me->cap) {
        reserveInS(target_, source_len_);
    }

    if (source_ && *source_ && source_len_ > 0) {
        char_t*  wr     = _STR(me);
        size_t   len    = 0;
        size_t   remain = source_len_;

        while (*source_ && remain--) {
            *wr++ = *source_++;
            len++;
        }
        *wr = '\0';
        me->len = len;
    }
    RETURN(NIL);
} /* _copy_to_object */


static void  _create(                                                      /*F*/
    const size_t    chars_capacity_,                                       /*-*/
    _str_t** const  head_ptr_out_,                                         /*-*/
    char_t** const  str_ptr_out_ ) {                                       /*-*/
    GO                                                            (UID(FD8CF0));
    const size_t  bytes_size =
        sizeof(_str_t) + (chars_capacity_ > STR_INITIAL_CAPACITY ?
                          1 : STR_INITIAL_CAPACITY + 1) * sizeof(char_t);
    /*                                           ^ + 1 for '\0' */

    _str_t* const  head = CAST(_str_t*, MALLOC(bytes_size));
    char_t*        str  = CAST(char_t*, CAST(uint8_t*, head) + sizeof(_str_t));

    if (head == NULL) {
        _WARN(_T("Allocation failed."), UID(EA48E7));
    } else {
        MEMSET(head, 0x00, bytes_size);

        if (chars_capacity_ > STR_INITIAL_CAPACITY) {
            const size_t  ext_size =
                sizeof(_ext_t) + (chars_capacity_ + 1) * sizeof(char_t);
            head->cap  = chars_capacity_;
            head->ext  = MALLOC(ext_size);

            if (head->ext == NULL) {
                _WARN(_T("Allocation failed."), UID(E2FB2A));
            }

            MEMSET(head->ext, 0x00, ext_size);
            str = CAST(char_t*, CAST(uint8_t*, head->ext) + sizeof(_ext_t));
            {
                _ext_t*  ext = CAST(_ext_t*, head->ext);
                ext->owner = head;
                ext->type  = _TYPE_STRING_EXTN;
            }
        } else {
            head->cap = STR_INITIAL_CAPACITY;
            head->ext = NULL;
        }

        head->type = _TYPE_STRING_MAIN;
        /* this is a newly-allocated string, so length is always 0 */
        head->len = 0;
    }

    if (head_ptr_out_) {
        *head_ptr_out_ = head;
    }
    if (str_ptr_out_) {
        *str_ptr_out_ = head == NULL ? NULL : str;
    }
    RETURN(NIL);
} /* _create */


static void  _free_pcnv( _str_t* const  object_ ) {                        /*F*/
    GO                                                            (UID(F93527));
    if (object_ != NULL && object_->cnv &&
        (object_->cnv != CAST(uint8_t*, BLANK))) {
        FREE(object_->cnv);
        object_->cnv = NULL;
    }
    RETURN(NIL);
} /* _free_pcnv */


static str_t  _object_wrap( _str_t* const  header_ ) {                     /*F*/
    GO                                                            (UID(FDF0E3));
    str_t    ret = { NULL };
    chars_t  str = NULL;

    if (header_->ext != NULL) {
        str = CAST(char_t*, CAST(uint8_t*, header_->ext) + sizeof(_ext_t));
    } else {
        str = CAST(char_t*, CAST(uint8_t*, header_) + sizeof(_str_t));
    }

    ret.cs = str;
    RETURN(ret);
} /* _object_wrap */


static void  _set(                                                         /*F*/
    str_t* const   object_,                                                /*-*/
    chars_t const  source_,                                                /*-*/
    const size_t   source_len_,                                            /*-*/
    const size_t   offset_,                                                /*-*/
    const size_t   substr_len_ ) {                                         /*-*/
    GO                                                            (UID(FB559D));
    if (source_len_ < 1 || IS_BLANK(source_)) {
        clearInS(object_);
    } else {
        const size_t  len =
            substr_lenT(source_, source_len_, offset_, substr_len_);

        if (len < 1) {
            clearInS(object_);
            RETURN(NIL);
        }

        _copy_to_object(source_, len, object_);
    }
    RETURN(NIL);
} /* _set */


/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */


PUBLIC new_str_t  S_chars( chars_t const  text_ ) {                        /*C*/
    GO                                                            (UID(F8C316));
    new_str_t  ret = S_firstChars(text_, SIZE_MAX);
    RETURN(ret);
} /* S_chars */


PUBLIC new_str_t  S_append(                                                /*C*/
    const str_t    object_,                                                /*-*/
    chars_t const  string_ ) {                                             /*-*/
    GO                                                            (UID(FCB9F1));
    const _str_t* const  me  = _object(object_, UID(EB4F39));
    new_str_t            ret = me == NULL ? S_blank() : S_copy(object_);
    addTS(&ret, string_);
    RETURN(ret);
} /* S_append */


PUBLIC new_str_t  S_blank( void ) {                                        /*C*/
    GO                                                            (UID(F96A44));
    new_str_t  ret  = { NULL };
    _str_t*    head = NULL;

    _create(0, &head, NULL);
    ret = _object_wrap(head);
    RETURN(ret);
} /* S_blank */


PUBLIC new_str_t  S_copy( const str_t  source_ ) {                         /*C*/
    GO                                                            (UID(FEFBA0));
    const _str_t* const  me = _object(source_, UID(E82B77));
    if (me == NULL) {
        RETURN(S_blank());
    } else {
        const size_t  len = me->len;
#if defined DEBUG
        {
            const size_t  check_len = STRLEN_T(_CSTR(source_));
            if (len < check_len) {
                _WARN(_T("ErrorIllogic"), UID(E9B36C));
            }
            /* may occur if you call getEmptyBufferS() */
            /* with no subsequent closeBufferS()       */
        }
#endif                                                               /* DEBUG */
        _str_t*  head = NULL;
        char_t*  str  = NULL;
        _create(len, &head, &str);
        head->len = 0;

        if (source_.cs != NULL && len > 0) {
            MEMCPY(str, _CSTR(me), (len + 1) * sizeof(char_t));
            head->len = len;
        }
        RETURN(_object_wrap(head));
    }
} /* S_copy */


PUBLIC new_str_t  S_double(                                                /*C*/
    const double   value_,                                                 /*-*/
    chars_t const  format_ ) {                                             /*-*/
    GO                                                            (UID(F11ED8));
    chars_t const  format = IS_BLANK(format_) ? _T("%f") : format_;
    char_t         buf[_NUM_BUF_SIZE];
    CLEAR(buf);

#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4774)  /* W:L4 format string is not a string literal */
#endif

    SNPRINTF_T(buf, _NUM_BUF_SIZE, format, value_);

#if defined _MSC_VER
#pragma warning (pop)
#endif

    RETURN(S_chars(buf));
} /* uintS */


PUBLIC new_str_t  S_firstChars(                                            /*C*/
    chars_t const  chars_,                                                 /*-*/
    const size_t   len_ ) {                                                /*-*/
    GO                                                            (UID(F6D067));
    new_str_t     ret  = { NULL };
    const size_t  len  = len_maxT(chars_, len_);
    _str_t*       head = NULL;
    char_t*       str  = NULL;

    _create(len, &head, &str);
    ret = _object_wrap(head);
    _copy_to_object(chars_, len, &ret);
    RETURN(ret);
} /* S_firstChars */


/* implement the same function in libex_stringc.c ``` */
PUBLIC new_str_t  S_formatNumeric(                                         /*C*/
    chars_t const  string_,                                                /*-*/
    const int      decimal_places_,                                        /*-*/
    const int      group_digits_1_,                                        /*-*/
    const int      group_digits_2_,                                        /*-*/
    const int      group_digits_3_,                                        /*-*/
    const char_t   decimal_point_char_,                                    /*-*/
    const char_t   group_delimiter_char_ ) {                               /*-*/
    GO                                                            (UID(FEE691));
    new_str_t     ret           = { NULL };
    bool          minus         = false;
    bool          decimal_point = false;
    int           left          = 0;
    int           right         = 0;
    const size_t  str_len       = STRLEN_T(string_);
    char_t*       wr            = NULL;
    chars_t       rd            = NULL;
    _str_t*       str           = NULL;
    int           group[3]      = { 0, 0, 0 };

    group[0] = group_digits_1_;
    group[1] = group_digits_2_;
    group[2] = group_digits_3_;

    if (string_ == NULL) {
        ret = S_chars(_T("0"));
        RETURN(ret);
    }

    /* determine length of string after formatting: */

    /* count number of digits to the left and right of the decimal point */
    for (rd = string_ + str_len - 1; rd >= string_; rd--) {
        if (*rd >= '0' && *rd <= '9') {
            if (decimal_point) {
                left++;
            } else {
                right++;
            }

        } else if (*rd == decimal_point_char_) {
            decimal_point = true;

        } else if (*rd == '-' && !minus) {
            minus = true;
        }
    }

    if (!decimal_point) {
        left  = right;
        right = 0;
    }

    if (left == 0 && right == 0 && decimal_places_ == 0) {
        ret = S_chars(_T("0"));
        RETURN(ret);
    }

    {
        /* increase left count to accommodate group separators */
        int  i = left;
        int  g = 0;

        while (i > group[g]) {
            if (group[g] > 0) {
                left++;
            }

            i -= group[g];

            if (g < 2 || group[g] == 0) {
                g++;
            }
        }
    }

    if (minus) {
        left++;
    }

    {
        /* allocate a temporary buffer */
        const size_t  result_len =
            CAST(size_t, (left ? left : 1)
                 + (decimal_places_ ? 1 : 0) + decimal_places_);

        _create(result_len, &str, &wr);
        str->len = result_len;

        if (wr == NULL) {
            _WARN(BLANK, UID(E8D127));
            ret = S_blank();
            RETURN(ret);
        }

        /* commence filling the buffer, starting from the end: */
        wr += result_len;
        *wr-- = '\0';
    }

    /* suffix any missing decimals with trailing zeros */
    if (decimal_places_ > 0) {
        int  i = right;
        while (i++ < decimal_places_) {
            *wr-- = '0';
        }

        if (right == 0) {
            *wr-- = decimal_point_char_;
        }
    }

    {
        /* copy only numeric characters from the source to the buffer: */
        int  group_digits = 0;
        int  g            = 0;

        rd = string_ + str_len - 1;

        while (rd >= string_) {
            if (*rd >= '0' && *rd <= '9') {
                /* (surplus decimal digits are skipped) */
                if (right > 0) {
                    if (right <= decimal_places_) {
                        *wr-- = *rd;
                    }

                    if (--right == 0) {
                        *wr-- = decimal_point_char_;
                    }
                } else if (left > 0) {
                    *wr-- = *rd;
                    left--;

                    if (left > 1) {
                        if (++group_digits == group[g]) {
                            *wr-- = group_delimiter_char_;
                            left--;
                            group_digits = 0;

                            if (g < 2) {
                                g++;
                            }
                        }
                    }
                }

            } else if (*rd == decimal_point_char_ &&
                       decimal_places_ > 0 && !decimal_point) {
                decimal_point = true;
                group_digits = 0;
            }
            rd--;
        }
    }
    wr++;

    while (*wr == '0' || *wr == group_delimiter_char_) {
        wr++;
    }

    if (*wr == decimal_point_char_) {
        *(--wr) = '0';
    }

    if (minus) {
        *(--wr) = '-';
    }

    ret = _object_wrap(str);
    RETURN(ret);
} /* S_formatNumeric */


PUBLIC new_str_t  S_bchars( const char* const  source_ ) {                 /*C*/
    GO                                                            (UID(F8FD90));
    new_str_t  ret = S_bsubstr(source_, 0, SIZE_MAX);
    RETURN(ret);
} /* S_bchars */


PUBLIC new_str_t  S_bsubstr(                                               /*C*/
    const char* const  source_,                                            /*-*/
    const size_t       offset_,                                            /*-*/
    const size_t       count_ ) {                                          /*-*/
    GO                                                            (UID(F56A5D));
    new_str_t  ret     = { NULL };
    size_t     src_len = STRLEN(source_);

    if (!source_ || source_[0] == '\0') {
        ret = S_blank();
        RETURN(ret);
    }

#if defined UNICODE || defined _UNICODE
    {
        wchar_t* const  new_wchar = wide_of_utf8(source_);

        if (src_len == SIZE_MAX && offset_ == 0 && count_ == SIZE_MAX) {
            ret = S_newT(new_wchar);
        } else {
            _set(&ret, new_wchar, src_len, offset_, count_);
            FREE(new_wchar);
        }
    }
#else                                                  /* UNICODE || _UNICODE */
    _set(&ret, source_, src_len, offset_, count_);
#endif                                               /* !UNICODE && !_UNICODE */

    RETURN(ret);
} /* S_bsubstr */


PUBLIC new_str_t  S_wchars( const wchar_t* const  chars_ ) {               /*C*/
    GO                                                            (UID(F86B68));
    RETURN(S_newT(Twchars(chars_)));
} /* S_wchars */


PUBLIC new_str_t  S_newT( new_chars_t const  chars_ ) {                    /*C*/
    GO                                                            (UID(F4B486));
    new_str_t     ret  = { NULL };
    _str_t*       head = NULL;
    const size_t  len  = chars_ == NULL ? 0 : STRLEN_T(chars_);

    if (len < 1) {
        ret = S_blank();
    } else {
        /* create space for header */
        const size_t  bytes_size = sizeof(_str_t) + (len + 1) * sizeof(char_t);

        head = CAST(_str_t*, REALLOC(chars_, bytes_size));
        if (head == NULL) {
            _WARN(_T("Reallocation failed."), UID(EC2DF6));
            ret = S_blank();
        } else {
            char_t* const  str =
                CAST(char_t*, CAST(uint8_t*, head) + sizeof(_str_t));

            MEMMOVE(str, head, bytes_size - sizeof(_str_t));
            MEMSET(head, 0x00, sizeof(_str_t));
            head->cap  = len;
            head->len  = len;
            head->ext  = NULL;
            head->cnv  = NULL;
            head->type = _TYPE_STRING_MAIN;
            ret        = _object_wrap(head);
        }
    }
    RETURN(ret);
} /* S_newT */


PUBLIC new_str_t  S_wchars_n(                                              /*C*/
    const wchar_t* const  source_,                                         /*-*/
    const size_t          source_len_,                                     /*-*/
    const size_t          offset_,                                         /*-*/
    const size_t          substr_len_ ) {                                  /*-*/
    GO                                                            (UID(F3AD0D));
    new_str_t  ret     = { NULL };
    size_t     src_len = LESSER(source_len_, WCSLEN(source_));

    if (!source_ || source_[0] == L'\0') {
        ret = S_blank();
        RETURN(ret);
    }

#if defined UNICODE || defined _UNICODE
    _set(&ret, source_, src_len, offset_, substr_len_);
#else                                                  /* UNICODE || _UNICODE */
    {
        new_bchars_t const  new_utf8 = utf8_of_wide(source_);
        if (src_len == SIZE_MAX && offset_ == 0 && substr_len_ == SIZE_MAX) {
            ret = S_newT(new_utf8);
        } else {
            _set(&ret, new_utf8, src_len, offset_, substr_len_);
            FREE(new_utf8);
        }
    }
#endif                                               /* !UNICODE && !_UNICODE */

    RETURN(ret);
} /* S_wchars_n */


PUBLIC new_str_t  S_repeat(                                                /*C*/
    chars_t const  string_,                                                /*-*/
    const int      count_,                                                 /*-*/
    const int      max_len_ ) {                                            /*-*/
    GO                                                            (UID(FB82C9));
    /* string_  : String to be repeated.              */
    /* count_   : Max. no. string can repeat.         */
    /* max_len_ : Max. length of the returned string. */

    new_str_t  ret = { NULL };

    if (string_ == NULL || count_ < 1 || max_len_ < 1) {
        ret = S_blank();
    } else {
        ret = S_newT(T_repeat(string_, count_, max_len_));
    }
    RETURN(ret);
} /* S_repeat */


PUBLIC new_str_t  S_reserve( const size_t  char_capacity_ ) {              /*C*/
    GO                                                            (UID(FCF05E));
    new_str_t  ret  = { NULL };
    _str_t*    head = NULL;
    char_t*    str  = NULL;

    _create(char_capacity_, &head, &str);
    ret = _object_wrap(head);
    RETURN(ret);
} /* S_reserve */


PUBLIC new_str_t  S_uint(                                                  /*C*/
    const unsigned long  value_,                                           /*-*/
    chars_t const        format_ ) {                                       /*-*/
    GO                                                            (UID(F48B89));
    chars_t const  format = IS_BLANK(format_) ? _T("%u") : format_;
    char_t         buf[_NUM_BUF_SIZE];
    CLEAR(buf);

#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4774)  /* W:L4 format string is not a string literal */
#endif

    SNPRINTF_T(buf, _NUM_BUF_SIZE, format, value_);

#if defined _MSC_VER
#pragma warning (pop)
#endif

    RETURN(S_chars(buf));
} /* uintS */


/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */


PUBLIC void  freeS( str_t* const  object_ ) {                              /*D*/
    GO                                                            (UID(DEFB5E));
    if (object_ != NULL) {
        _str_t* const  me = _object(*object_, UID(EB4DE4));
        if (me != NULL) {
            _free_pcnv(me);
            if (me->ext != NULL) {
                FREE(me->ext);
                me->ext = NULL;
            }
            FREE(me);
            object_->cs = NULL;
        }
    }
    RETURN(NIL);
} /* freeS */


/* -------------------------------------------------------------------------- */
/* Methods: Void                                                              */


PUBLIC void  closeBufferS( str_t* const  object_ ) {                       /*M*/
    GO                                                            (UID(F85BC0));
    _str_t* const  me = _object_init(*object_, UID(E9AA16));
    me->len = STRLEN_T(_CSTR(me));
    RETURN(NIL);
} /* closeBufferS */


PUBLIC void  copyFromBufferS(                                              /*M*/
    str_t* const   object_,                                                /*-*/
    chars_t const  buffer_,                                                /*-*/
    const size_t   buffer_len_ ) {                                         /*-*/
    GO                                                            (UID(F76718));
    _str_t* const  me = _object_init(*object_, UID(E11324));
    if (buffer_len_ == 0) {
        clearInS(object_);
    } else {
        const uint8_t* const  src  = CAST(const uint8_t*, buffer_);
        uint8_t* const        dest =
            CAST(uint8_t*, getEmptyBufferS(object_, buffer_len_));
        MEMCPY(dest, src, buffer_len_ * sizeof(char_t));
        closeBufferS(object_);
    }
    RETURN(NIL);
} /* copyFromBufferS */


PUBLIC void  copyToBufferS(                                                /*M*/
    const str_t   object_,                                                 /*-*/
    char_t*       buffer_,                                                 /*-*/
    const size_t  buffer_len_ ) {                                          /*-*/
    GO                                                            (UID(F2A9BF));
    const _str_t* const  me = _object(object_, UID(E0A786));
    if (me == NULL) {
        RETURN(NIL);
    }

    if (IS_BLANK(buffer_)) {
        _WARN(_T("buffer_ == NULL"),  UID(E8E980));
        RETURN(NIL);
    }
    if (buffer_len_ == 0) {
        _WARN(_T("buffer_len_ == 0"), UID(E9EE81));
        RETURN(NIL);
    }

    {
        const char_t* const  buf_end = buffer_ + buffer_len_;

        {
            /* copy characters from object to buffer */
            chars_t  rd = NULL;
            for (rd = _CSTR(me); rd < _CSTR(me) + me->len && buffer_ < buf_end;
                 rd++) {
                *buffer_ = *rd;
                buffer_++;
            }
        }

        if (buffer_ < buf_end) { /* add terminating null character */
            *buffer_ = '\0';
            buffer_++;
        }

        /* fill any remaining free characters in the buffer with null chars */
        if (me->len < buffer_len_) {
            while (buffer_ < buf_end) {
                *buffer_ = '\0';
                buffer_++;
            }
        }
    }
    RETURN(NIL);
} /* copyToBufferS */


PUBLIC void  freeConversionBufferS( str_t* const  object_ ) {              /*M*/
    GO                                                            (UID(F10159));
    if (object_ != NULL) {
        _str_t* const  me = _object(*object_, UID(E57B93));
        if (me != NULL) {
            _free_pcnv(me);
        }
    }
    RETURN(NIL);
} /* freeConversionBufferS */


PUBLIC void  addS(                                                         /*M*/
    str_t* const  object_,                                                 /*-*/
    const str_t   source_ ) {                                              /*-*/
    GO                                                            (UID(F7D058));
    _str_t* const  source = _object(source_, UID(EF066D));
    if (source != NULL) {
        add3S(object_, _CSTR(source), source->len);
    }
    RETURN(NIL);
} /* addS */


PUBLIC void  addTS(                                                        /*M*/
    str_t* const   object_,                                                /*-*/
    chars_t const  source_ ) {                                             /*-*/
    GO                                                            (UID(F421B2));
    add3S(object_, source_, SIZE_MAX);
    RETURN(NIL);
} /* addS */


PUBLIC void  addAS(                                                        /*M*/
    str_t* const       object_,                                            /*-*/
    const char* const  string_ ) {                                         /*-*/
    GO                                                            (UID(FF8717));
    if (string_ != NULL) {
#if defined UNICODE || defined _UNICODE
        wchar_t*  wide = wide_of_utf8(string_);
        addTS(object_, CAST(chars_t, wide));
        freeT(&wide);
#else
        addTS(object_, string_);
#endif
    }
    RETURN(NIL);
} /* addAS */


PUBLIC void  addWS(                                                        /*M*/
    str_t* const          object_,                                         /*-*/
    const wchar_t* const  string_ ) {                                      /*-*/
    GO                                                            (UID(F6763C));
    const _str_t* const  me = _object_init(*object_, UID(E6AC22));

    if (string_ != NULL) {
#if defined UNICODE || defined _UNICODE
        addTS(object_, string_);
#else                                                  /* UNICODE || _UNICODE */
        new_bchars_t  buf = utf8_of_wide(string_);
        addTS(object_, CAST(chars_t, buf));
        freeT(&buf);
#endif                                               /* !UNICODE && !_UNICODE */
    }
    RETURN(NIL);
} /* addWS */


PUBLIC void  setInS(                                                       /*M*/
    str_t* const   object_,                                                /*-*/
    chars_t const  string_ ) {                                             /*-*/
    GO                                                            (UID(F57149));
    const size_t  len = lenT(string_);
    clearInS(object_);
    _copy_to_object(string_, len, object_);
    RETURN(NIL);
} /* setInS */


PUBLIC void  add3S(                                                        /*M*/
    str_t* const   object_,                                                /*-*/
    chars_t const  string_,                                                /*-*/
    const size_t   length_ ) {                                             /*-*/
    GO                                                            (UID(FC69FA));
    _str_t* const  me = _object_init(*object_, UID(E26F2D));

    if (length_ >= 1 && !IS_BLANK(string_)) {
        const size_t  len = len_maxT(string_, length_);

        if (me->cap < (me->len + len + 1)) {  /* + 1 for \0 */
            const size_t  new_size =
                CAST(size_t, 32 + CAST(double, me->cap + len) * 1.5);
            reserveInS(object_, new_size);
        }

        {
            chars_t  rd = string_;
            char_t*  wr = _STR(me) + me->len;

            while (*rd && wr < (_CSTR(me) + me->len + len)) {
                *wr++ = *rd++;
            }
            *wr = '\0';
        }
        me->len += len;
    }
    RETURN(NIL);
} /* add3S */


PUBLIC void  addCharS(                                                     /*M*/
    str_t* const  object_,                                                 /*-*/
    const char_t  char_ ) {                                                /*-*/
    GO                                                            (UID(F30C8D));
    _str_t* const  me = _object_init(*object_, UID(ED7976));

    if (char_ == '\0') {
        RETURN(NIL);
    }

    if (me->cap < (me->len + 2)) {
        const size_t  new_size =
            CAST(size_t, 32 + CAST(double, me->cap + 1) * 1.5);
        reserveInS(object_, new_size);
    }

    *(_STR(me) + me->len) = char_;
    me->len++;
    *(_STR(me) + me->len) = '\0';
    RETURN(NIL);
} /* addCharS */


PUBLIC void  addIntS(                                                      /*M*/
    str_t* const  object_,                                                 /*-*/
    const int     number_ ) {                                              /*-*/
    GO                                                            (UID(F6D28D));
    _str_t* const  me = _object_init(*object_, UID(EE7339));
    char_t         chars[32];

    MEMSET(chars, 0x00, sizeof(char_t) * 32);
    SNPRINTF_T(chars, 32, _T("%i"), number_);
    addTS(object_, chars);
    RETURN(NIL);
} /* addIntS */


PUBLIC void  reserveInS(                                                   /*M*/
    str_t* const  object_,                                                 /*-*/
    const size_t  char_capacity_ ) {                                       /*-*/
    GO                                                            (UID(F9CB8D));
    _str_t* const  me         = _object(*object_, UID(EDC29E));
    _ext_t*        new_ext    = NULL;
    const size_t   bytes_size = sizeof(_ext_t)
                                + (char_capacity_ + 1) * sizeof(char_t);

    if (me == NULL || char_capacity_ <= me->cap) {
        RETURN(NIL);
    }

    if (!me->ext) {  /* if there is no string extension, allocate it */
        new_ext = CAST(_ext_t*, MALLOC(bytes_size));

        if (new_ext == NULL) {
            _WARN(BLANK, UID(E12263));
            RETURN(NIL);
        }
    } else { /* reallocate existing string extension */
        new_ext = CAST(_ext_t*, REALLOC(me->ext, bytes_size));
        if (new_ext == NULL) {
            _WARN(BLANK, UID(E0E010));
            RETURN(NIL);
        }
    }

    {
        char_t* const  buf =
            CAST(char_t*, CAST(uint8_t*, new_ext) + sizeof(_ext_t));

        /* copy main string to string extension */
        if (!me->ext && me->len > 0) {
            const size_t  bytes_to_copy = (me->len + 1) * sizeof(char_t);
            chars_t const  str =
                CAST(char_t*, CAST(uint8_t*, me) + sizeof(_str_t));
            MEMCPY(buf, str, bytes_to_copy);
        }

        *(buf + me->len)        = '\0';  /* add terminating zero */
        *(buf + char_capacity_) = '\0';
    }

    new_ext->owner = me;
    new_ext->type  = _TYPE_STRING_EXTN;

    me->ext = new_ext;
    me->cap = char_capacity_;

    /* use pointer to text in string extension */
    object_->cs = CAST(chars_t, CAST(uint8_t*, new_ext) + sizeof(_ext_t));

    RETURN(NIL);
} /* reserveInS */


PUBLIC void  setCopyS(                                                     /*M*/
    str_t* const  object_,                                                 /*-*/
    const str_t   string_ ) {                                              /*-*/
    GO                                                            (UID(F5FF60));
    _str_t* const  src = _object(string_, UID(E8AC63));
    if (src != NULL) {
        _set(object_, _CSTR(src), src->len, 0, SIZE_MAX);
    }
    RETURN(NIL);
} /* setCopyS */


PUBLIC void  setCopyAnsiS(                                                 /*M*/
    str_t* const       object_,                                            /*-*/
    const char* const  string_ ) {                                         /*-*/
    GO                                                            (UID(FEF78C));
    const _str_t* const  me = _object_init(*object_, UID(E77790));

#if defined UNICODE || defined _UNICODE
    {
        wchar_t* const  wide = wide_of_utf8(string_);
        freeS(object_);
        *object_ = S_newT(wide);
    }
#else                                                  /* UNICODE || _UNICODE */
    _set(object_, string_, SIZE_MAX, 0, SIZE_MAX);
#endif                                               /* !UNICODE && !_UNICODE */

    RETURN(NIL);
} /* setCopyAnsiS */


PUBLIC void  setCopyCharS(                                                 /*M*/
    str_t* const  object_,                                                 /*-*/
    const char_t  char_ ) {                                                /*-*/
    GO                                                            (UID(F49F2B));
    _str_t* const  me = _object_init(*object_, UID(EE9B23));
    CHAR_TO_STR(ch, char_);
    _set(object_, ch, SIZE_MAX, 0, SIZE_MAX);
    RETURN(NIL);
} /* setCopyCharS */


PUBLIC void  setCopyWideS(                                                 /*M*/
    str_t* const          object_,                                         /*-*/
    const wchar_t* const  string_ ) {                                      /*-*/
    GO                                                            (UID(FB0D03));
    _str_t* const  me = _object_init(*object_, UID(E0976A));
#if defined UNICODE || defined _UNICODE
    _set(object_, string_, SIZE_MAX, 0, SIZE_MAX);
#else                                                  /* UNICODE || _UNICODE */
    new_bchars_t const  str = utf8_of_wide(string_);
    freeS(object_);
    *object_ = S_newT(str);
#endif                                               /* !UNICODE && !_UNICODE */
    RETURN(NIL);
} /* setCopyWideS */


PUBLIC void  decodeBase64InS( str_t* const  object_ ) {                    /*M*/
    GO                                                            (UID(F58F16));
    _str_t* const  me = _object(*object_, UID(E9FA50));
    if (me == NULL) {
        clearInS(object_);
    } else {
        new_str_t  set = S_decodeBase64(*object_);
        clearInS(object_);
        *object_ = set;
    }
    RETURN(NIL);
} /* decodeBase64InS */


PUBLIC void  delimitNumberInS(                                             /*M*/
    str_t* const  object_,                                                 /*-*/
    const size_t  decimal_places_,                                         /*-*/
    const size_t  digits_1_,                                               /*-*/
    const size_t  digits_2_,                                               /*-*/
    const size_t  digits_3_,                                               /*-*/
    const char_t  decimal_point_char_,                                     /*-*/
    const char_t  group_char_ ) {                                          /*-*/
    GO                                                            (UID(F8FDBD));
    _str_t* const  me = _object(*object_, UID(E09F55));

    bool     has_dp     = false;
    char_t*  str        = NULL;
    size_t   i          = 0;
    size_t   g          = 0;
    size_t   free_count = 0;
    size_t   len        = 0;
    size_t   move       = 0;
    size_t   num_dp     = 0;
    size_t   group[3];

    if (me == NULL) {
        clearInS(object_);
        RETURN(NIL);
    }

    str = _STR(me);

    if (IS_BLANK(_CSTR(me))) {
        RETURN(NIL);
    }

    /* determine length of numeric string,  */
    /* and count digits after decimal point */
    len    = 0;
    num_dp = 0;

    while (len < me->len && *str != '\0') {
        if (*str == decimal_point_char_) {
            if (decimal_places_ > 0) {
                has_dp = true;
                num_dp = 0;
            } else {
                *str = '\0';
                break;
            }
        } else if (has_dp) {
            /* remove any characters after specified number of decimal places */
            if (++num_dp > decimal_places_) {
                *str = '\0';
                break;
            }
        }

        str++;
        len++;
    }

    free_count = me->cap - len;

    if (!free_count) {
        reserveInS(object_, len + 24);
        free_count = me->cap - len;
        str = _STR(me) + len;
    }

    /* insert zeros if there are less digits after */
    /* the decimal point (or no decimal point)     */
    if (decimal_places_ > 0) {
        /* add decimal point */
        if (!has_dp && free_count) {
            *str++ = decimal_point_char_;
            len++;
            free_count--;
        }

        /* suffix zeros */
        while (num_dp++ < decimal_places_ && free_count) {
            *str++ = '0';
            len++;
            free_count--;
        }

        /* add terminating null */
        *str = '\0';
    }

    /* move pointer before the decimal point */
    move = 1;  /* for \0 */

    if (decimal_places_ > 0) {
        str -= (1 + decimal_places_);
        move += (1 + decimal_places_);
    }

    g = 0;
    group[0] = digits_1_;
    group[1] = digits_2_;
    group[2] = digits_3_;

    while (str > _CSTR(me) && free_count) {
        str -= group[g];
        move += group[g];

        if (str <= _CSTR(me)) {
            break;
        }

        if (*(str - 1) == '-') {
            break;
        }

        /* shift characters to the right */
        free_count--;
        i = move;

        while (i--) {
            *(str + i + 1) = *(str + i);
        }

        *str = group_char_;
        move++;  /* for the inserted group char */
        len++;

        if (g < 2) {
            g++;
        }
    }

    /* insert leading zero */
    if (decimal_places_ && len &&
        *_CSTR(me) == decimal_point_char_ && free_count) {

        len++;
        free_count--;

        for (str = _STR(me) + len + 1; str > _STR(me); str--) {
            *str = *(str - 1);
        }

        *_STR(me) = '0';
    }
    me->len = len;
    RETURN(NIL);
} /* delimitNumberInS */


PUBLIC void  clearInS( str_t* const  object_ ) {                           /*M*/
    GO                                                            (UID(F16054));
    _str_t*  me = _object(*object_, UID(EABD60));
    if (me == NULL) {
        *object_ = S_blank();
        me = _object(*object_, UID(E66689));
    }

    /* add terminating zeros */
    if (_CSTR(me) && me->cap > 0) {
        *(_STR(me) + me->cap) = '\0';
        *_STR(me) = '\0';
    }

    if (me->cnv) {
        _free_pcnv(me);
    }

    me->len = 0;
    RETURN(NIL);
} /* clearInS */


PUBLIC void  encodeBase64InS( str_t* const  object_ ) {                    /*M*/
    GO                                                            (UID(F0851B));
    _str_t* const  me = _object(*object_, UID(E3C0D0));
    if (me == NULL) {
        clearInS(object_);
    } else {
        new_str_t  set = S_encodeBase64(*object_);
        clearInS(object_);
        *object_ = set;
    }
    RETURN(NIL);
} /* encodeBase64InS */


PUBLIC void  fillInS(                                                      /*M*/
    str_t* const  object_,                                                 /*-*/
    const char_t  char_,                                                   /*-*/
    const size_t  length_,                                                 /*-*/
    const bool    align_to_end_,                                           /*-*/
    const bool    spillover_,                                              /*-*/
    const bool    clear_contents_ ) {                                      /*-*/
    GO                                                            (UID(F5B744));
    _str_t* const  me = _object_init(*object_, UID(E52DCE));

    if (spillover_ && !clear_contents_ && me->len > length_) {
        RETURN(NIL);
    }

    {
        /* ensure the string is long enough */
        const size_t  cap = GREATER(me->len, length_);
        if (cap > me->cap) {
            reserveInS(object_, cap);
        }
    }

    {
        char_t*        string  = _STR(me);
        const char_t*  end     = _CSTR(me) + me->len;
        const size_t   old_len = me->len;

        me->len = length_;

        if (old_len < me->len) {
            if (align_to_end_) {
                char_t*       trim = NULL;
                const size_t  step = length_ - old_len;

                end = _CSTR(me) + step;

                for (trim = _STR(me) + length_ - 1; trim >= end; trim--) {
                    *trim = *(trim - step);
                }

                end = _CSTR(me) + me->len - old_len;
            } else {
                string = _STR(me) + old_len;
            }
        }

        while (string != NULL && string < end) { /* fill */
            *string++ = char_;
        }
    }

    if (me->cap > 0 && _CSTR(me)) {
        *(_STR(me) + me->len) = '\0';    /* set terminating null */
    }

    RETURN(NIL);
} /* fillInS */


PUBLIC void  firstInS(                                                     /*M*/
    str_t* const  object_,                                                 /*-*/
    const size_t  length_ ) {                                              /*-*/
    GO                                                            (UID(FD18B1));
    _str_t* const  me = _object(*object_, UID(EC2316));
    if (me == NULL) {
        clearInS(object_);
    } else {
        if (length_ >= me->len) {
            RETURN(NIL);
        }
        *(_STR(me) + length_) = '\0';
        me->len = length_;
    }
    RETURN(NIL);
} /* firstInS */


PUBLIC void  formatInS(                                                    /*M*/
    str_t* const   object_,                                                /*-*/
    chars_t const  format_,                                                /*-*/
    chars_t const  str0_,                                                  /*-*/
    chars_t const  str1_,                                                  /*-*/
    chars_t const  str2_,                                                  /*-*/
    chars_t const  str3_,                                                  /*-*/
    chars_t const  str4_,                                                  /*-*/
    chars_t const  str5_,                                                  /*-*/
    chars_t const  str6_,                                                  /*-*/
    chars_t const  str7_,                                                  /*-*/
    chars_t const  str8_,                                                  /*-*/
    chars_t const  str9_ ) {                                               /*-*/
    GO                                                            (UID(F12859));
    _str_t* const  me = _object_init(*object_, UID(EC6D41));

    size_t        i           = 0;
    const size_t  fmt_len     = STRLEN_T(format_);
    size_t        new_len     = 0;
    char_t*       wr          = NULL;
    chars_t       pb          = NULL;
    chars_t       str         = NULL;
    size_t        arg_len[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    if (format_ == NULL || fmt_len < 1) {
        clearInS(object_);
        RETURN(NIL);
    }

    /* calculate lengths of all arguments */
    for (i = 0; i < 10; i++) {
        str = i == 0 ? str0_
              : i == 1 ? str1_
              : i == 2 ? str2_
              : i == 3 ? str3_
              : i == 4 ? str4_
              : i == 5 ? str5_
              : i == 6 ? str6_
              : i == 7 ? str7_
              : i == 8 ? str8_
              : str9_;

        if (str == NULL) {
            arg_len[i] = 0;
        } else {
            arg_len[i] = STRLEN_T(str);
        }
    }

    /* calculate capacity required after making replacements */
    new_len = fmt_len;

    for (str = format_; str < (format_ + fmt_len - 1); str++) {
        if (*str != '%') {
            continue;
        }

        pb = str + 1;
        i = *pb == '0' ? 0u :
            *pb == '1' ? 1u :
            *pb == '2' ? 2u :
            *pb == '3' ? 3u :
            *pb == '4' ? 4u :
            *pb == '5' ? 5u :
            *pb == '6' ? 6u :
            *pb == '7' ? 7u :
            *pb == '8' ? 8u :
            *pb == '9' ? 9u : 10u;

        if (i < 10) {
            str++;
            new_len += arg_len[i] - 2;
        }
    }

    /* allocate required space */
    reserveInS(object_, new_len);
    me->len = new_len;

    /* fill this string with format specifier and sub-strings */
    wr = _STR(me);

    for (str = format_; str < (format_ + fmt_len); str++) {
        if (*str == '%' && str < (format_ + fmt_len - 1)) {
            /* what sub-string to use? */
            pb = str + 1;
            i = *pb == '0' ? 0u :
                *pb == '1' ? 1u :
                *pb == '2' ? 2u :
                *pb == '3' ? 3u :
                *pb == '4' ? 4u :
                *pb == '5' ? 5u :
                *pb == '6' ? 6u :
                *pb == '7' ? 7u :
                *pb == '8' ? 8u :
                *pb == '9' ? 9u : 10u;

            /* if it's an actual sub-string, append it to this string */
            if (i < 10) {
                chars_t  src = i == 0 ? str0_ :
                               i == 1 ? str1_ :
                               i == 2 ? str2_ :
                               i == 3 ? str3_ :
                               i == 4 ? str4_ :
                               i == 5 ? str5_ :
                               i == 6 ? str6_ :
                               i == 7 ? str7_ :
                               i == 8 ? str8_ : str9_;
                str++;

                if (src) {
                    while (*src) {
                        *wr++ = *src++;
                    }
                }
            } else {
                *wr++ = *str;
            }
        } else {
            *wr++ = *str;
        }
    }
    RETURN(NIL);
} /* formatInS */


PUBLIC void  formatNumericInS(                                             /*M*/
    str_t* const  object_,                                                 /*-*/
    const int     decimal_places_,                                         /*-*/
    const int     group_digits_1_,                                         /*-*/
    const int     group_digits_2_,                                         /*-*/
    const int     group_digits_3_,                                         /*-*/
    const char_t  decimal_point_char_,                                     /*-*/
    const char_t  group_delimiter_char_ ) {                                /*-*/
    GO                                                            (UID(F94A2E));
    new_str_t  ob = S_formatNumeric(
                        object_->cs, decimal_places_,
                        group_digits_1_, group_digits_2_, group_digits_3_,
                        decimal_point_char_, group_delimiter_char_);
    freeS(object_);
    *object_ = ob;
} /* formatNumericInS */


PUBLIC void  insertInS(                                                    /*M*/
    str_t* const   object_,                                                /*-*/
    chars_t const  string_,                                                /*-*/
    const size_t   insert_at_position_,                                    /*-*/
    const size_t   length_ ) {                                             /*-*/
    GO                                                            (UID(F86C34));
    str_t  ob = S_insert(*object_, string_, insert_at_position_, length_);
    freeS(object_);
    *object_ = ob;
    RETURN(NIL);
} /* insertInS */


PUBLIC void  lastInS(                                                      /*M*/
    str_t* const  object_,                                                 /*-*/
    const size_t  length_ ) {                                              /*-*/
    GO                                                            (UID(F852D2));
    _str_t* const  me = _object(*object_, UID(EA4A29));
    if (me == NULL) {
        clearInS(object_);
        RETURN(NIL);
    }

    if (length_ >= me->len) {
        RETURN(NIL);
    }

    if (length_ > 0) {
        chars_t  rd = (_CSTR(me) + me->len - length_);
        char_t*  wr = _STR(me);
        size_t   i  = 0;

        for (i = 0; i < length_; i++) {
            *wr++ = *rd++;
        }
    }

    *(_STR(me) + length_) = '\0';
    me->len = length_;
    RETURN(NIL);
} /* lastInS */


PUBLIC void  tolowerInS( str_t* const  object_ ) {                         /*M*/
    GO                                                            (UID(F67586));
    const _str_t* const  me = _object(*object_, UID(E5DB73));
    if (me == NULL) {
        clearInS(object_);
    } else if (me->len > 0) {
        change_in_T(CAST(char_t*, object_->cs), MAKE_LOWER_CASE);
    }
    RETURN(NIL);
} /* tolowerInS */


PUBLIC void  removeInS(                                                    /*M*/
    str_t* const  object_,                                                 /*-*/
    const size_t  position_,                                               /*-*/
    const size_t  char_count_ ) {                                          /*-*/
    GO                                                            (UID(F5C20E));
    const _str_t* const  me = _object(*object_, UID(E2BCBF));
    if (me == NULL) {
        clearInS(object_);
        RETURN(NIL);
    } else {
        new_str_t  ob = S_remove(*object_, position_, char_count_);
        setCopyS(object_, ob);
        freeS(&ob);
    }
    RETURN(NIL);
} /* removeEndInS */


PUBLIC void  removeEndInS(                                                 /*M*/
    str_t* const  object_,                                                 /*-*/
    const size_t  char_count_ ) {                                          /*-*/
    GO                                                            (UID(FFFF9A));
    _str_t* const  me = _object(*object_, UID(E45F48));
    if (me == NULL) {
        clearInS(object_);
    } else if (char_count_ >= me->len) {
        me->len = 0;
    } else {
        me->len -= char_count_;
    }
    *(_STR(me) + me->len) = '\0';
    RETURN(NIL);
} /* removeEndInS */


PUBLIC void  setReplaceS(                                                  /*M*/
    str_t* const   object_,                                                /*-*/
    chars_t const  find_str_,                                              /*-*/
    chars_t const  replace_str_,                                           /*-*/
    const bool     ignore_case_,                                           /*-*/
    const size_t   find_len_,                                              /*-*/
    const size_t   replace_len_ ) {                                        /*-*/
    GO                                                            (UID(F3A0FA));
    /* object_      : pointer to string object             */
    /* find_str_    : string being searched for            */
    /* replace_str_ : replacement string                   */
    /* ignore_case_ : MATCH_CASE / IGNORE_CASE             */
    /* find_len_    : length of find_str_ in characters    */
    /* replace_len_ : length of replace_str_ in characters */

    _str_t* const  me = _object(*object_, UID(E9E910));

    size_t   new_len = 0;
    size_t   found   = 0;
    chars_t  src     = NULL;
    chars_t  find    = NULL;
    chars_t  rd      = NULL;
    char_t*  wr      = NULL;

    const size_t  find_len =  (find_len_ != SIZE_MAX) ? find_len_
                              : STRLEN_T(find_str_);

    const size_t  repl_len =  (replace_len_ != SIZE_MAX) ? replace_len_
                              : STRLEN_T(replace_str_);

    if (me == NULL) {
        clearInS(object_);
        RETURN(NIL);
    }

    /* replace a blank string with replace_str_ */
    if (me->len == 0 && find_len == 0 && repl_len > 0) {
        rd = replace_str_;

        /* re-allocate the string if the replacement */
        /* is longer than the capacity               */
        if (repl_len > me->cap) {
            reserveInS(object_, repl_len);
        }

        wr = _STR(me);
        {
            size_t  i = 0;
            for (i = 0; i < repl_len; i++) {
                *wr++ = *rd++;
            }
        }
        *wr = '\0';
        RETURN(NIL);
    }

    /* return immediately if this instance is blank or */
    /* find_str_ is blank or wider than this instance  */
    if (me->len < 1 || find_len < 1 || find_len > me->len) {
        RETURN(NIL);
    }

    src  = _CSTR(me);
    find = find_str_;

    /* calculate new string length after all replacements (new_len) */
    new_len = me->len;
    {
        found = 0;  /* number of matching characters found */
        if (repl_len != find_len) {
            size_t  i = 0;
            for (i = 0; i < me->len; i++) {
                if (ignore_case_
                    ? TOLOWER_T(*src) == TOLOWER_T(*find)
                    : *src == *find) {

                    find++;
                    found++;

                    if (found == find_len) {
                        new_len += (repl_len - find_len);
                        find = find_str_;
                        found = 0;
                    }
                } else if (found) {
                    src -= found;
                    find = find_str_;
                    i -= found;
                    found = 0;
                }
                src++;
            }
        }
    }

    /* re-allocate the string if the replacement is longer than capacity */
    if (new_len > me->cap) {
        reserveInS(object_, new_len);
    }

    found = 0;

    if (repl_len <= find_len) {  /* create and fill replacement string */
        wr   = _STR(me);
        src  = _STR(me);
        find = find_str_;

        while (wr != (_CSTR(me) + new_len)) {
            if (ignore_case_
                ? TOLOWER_T(*src) == TOLOWER_T(*find) : *src == *find) {

                find++;

                if (++found == find_len) {
                    chars_t  repl     = replace_str_;
                    size_t   repl_pos = repl_len;

                    while (repl_pos--) {
                        if (*repl == '\0') {
                            new_len -= (repl_pos + 1);
                            break;
                        }
                        *wr++ = *repl++;
                    }

                    find  = find_str_;
                    found = 0;
                }
            } else {
                src -= found;
                find  = find_str_;
                found = 0;
                *wr++ = *src;
            }
            src++;
        };
        *wr = '\0';
    } else { /* create and fill replacement string */
        wr   = _STR(me)  + new_len  - 1;
        src  = _STR(me)  + me->len  - 1;
        find = find_str_ + find_len - 1;
        *(wr + 1) = '\0';

        while (wr > _CSTR(me)) {
            if (ignore_case_
                ? TOLOWER_T(*src) == TOLOWER_T(*find)
                : *src == *find) {
                if (++found == find_len) {
                    chars_t  repl     = replace_str_ + repl_len - 1;
                    size_t   repl_pos = repl_len;

                    while (repl_pos--) {
                        if (*repl == '\0') {
                            new_len -= (repl_pos + 1);
                            break;
                        }

                        *wr = *repl;
                        wr--;
                        repl--;
                    }

                    src--;
                    find  = find_str_ + find_len - 1;
                    found = 0;
                } else {
                    find--;
                    src--;
                }
            } else {
                if (found > 0) {
                    src += found;
                    find  = find_str_ + find_len - 1;
                    found = 0;
                }

                *wr = *src;
                wr--;
                src--;
            }
        }
    }
    me->len = new_len;
    RETURN(NIL);
} /* setReplaceS */


PUBLIC void  reverseInS( str_t* const  object_ ) {                         /*M*/
    GO                                                            (UID(FA50F9));
    _str_t* const  me = _object(*object_, UID(EA147D));
    if (me == NULL) {
        clearInS(object_);
    } else if (me->len > 0) {
        change_in_T(CAST(char_t*, object_->cs), MAKE_REVERSE);
    }
    RETURN(NIL);
} /* reverseInS */


PUBLIC void  sortListInS(                                                  /*M*/
    str_t* const   object_,                                                /*-*/
    chars_t const  delimiter_,                                             /*-*/
    const bool     descending_,                                            /*-*/
    const bool     unique_ ) {                                             /*-*/
    GO                                                            (UID(FDF4DA));
    _str_t* const  me = _object(*object_, UID(EF5027));

    /* removed from arguments, because they are seldom used: */

    /* Specifies the first token from which to begin sorting. */
    const size_t  SORT_FROM = 0;

    /* Specifies the number of tokens to be sorted. */
    const size_t  SORT_COUNT = SIZE_MAX;

    if (me == NULL) {
        clearInS(object_);
        RETURN(NIL);
    }

    if (me->len == 0 || IS_BLANK(_CSTR(me)) || IS_BLANK(delimiter_)) {
        RETURN(NIL);
    }

    {
        char_t*  buf = NULL;

        /* count number of tokens */
        const size_t  token_count =
            token_info_xtT(
                CAST(token_info_enum, TOKEN_COUNT),
                _CSTR(me), delimiter_, NULL, IGNORE_CASE, me->len, SIZE_MAX);

        /* initialize array of tokens                       */
        /* don't use mallocT(). it's an array of pointers. */
        char_t**  token_ptrs =
            CAST(char_t**, MALLOC(sizeof(char_t*) * token_count));

        if (token_ptrs == NULL) {
            _WARN(BLANK, UID(ED21DF));
            RETURN(NIL);
        }

        {
            size_t  i = 0;
            for (i = 0; i < token_count; i++) {
                token_ptrs[i] = NULL;
            }
        }

        /* copy string to a temporary buffer */
        buf = mallocT(me->len);
        if (buf == NULL) {
            _WARN(BLANK, UID(E56629));
            RETURN(NIL);
        }
        {
            size_t  i = 0;
            for (i = 0; i < me->len; i++) {
                buf[i] = _CSTR(me)[i];
            }
        }
        buf[me->len] = '\0';

        {
            /* tokenize the buffer: */
            char_t*  string   = buf;
            char_t*  token    = buf;
            chars_t  delim    = delimiter_;
            size_t   token_no = 0;
            size_t   same     = 0;
            size_t   i        = 0;

            const size_t  delim_len = STRLEN_T(delimiter_);

            for (i = 0; i < me->len; i++) {
                if (*string == *delim) {
                    delim++;

                    if (++same == delim_len) {
                        /* store pointer to token in the array */
                        token_ptrs[token_no] = token;
                        token = string + 1;
                        token_no++;

                        /* add \0 at the end of token */
                        *(string - delim_len + 1) = '\0';

                        delim = delimiter_;
                        same = 0;
                    }
                } else if (same) {
                    if (same < delim_len) {
                        i -= same;
                        string -= same;
                    }
                    delim = delimiter_;
                    same = 0;
                }
                string++;
            }
            token_ptrs[token_no] = token;
        }

        {
            /* sort the array */
            const size_t  sort_count =
                LESSER(SORT_COUNT, token_count - SORT_FROM);

            if (descending_) {
                QSORT(&token_ptrs[SORT_FROM], sort_count,
                      sizeof(char_t*), _qsort_compare_desc);
            } else {
                QSORT(&token_ptrs[SORT_FROM], sort_count,
                      sizeof(char_t*), _qsort_compare);
            }
        }

        /* if unique_ is true, remove duplicated strings */
        if (unique_) {
            size_t  i = 0;
            size_t  b = 0;
            for (i = 0; i < (token_count - 1); i++) {
                b = i + 1;
                while (b < token_count && token_ptrs[i] != NULL) {
                    if (_qsort_compare(&token_ptrs[i], &token_ptrs[b]) == 0) {
                        token_ptrs[b++] = NULL;
                    } else {
                        break;
                    }
                }
            }
        }

        /* clear contents of this string */
        clearInS(object_);

        /* write sorted tokens and delimiters back to this string */
        {
            size_t  i = 0;
            for (i = 0; i < token_count; i++) {
                if (token_ptrs[i] != NULL) {
                    if (i > 0) {
                        addTS(object_, delimiter_);
                    }
                    addTS(object_, token_ptrs[i]);
                }
            }
        }

        /* cleanup */
        FREE(token_ptrs);
        FREE(buf);
    }
    RETURN(NIL);
} /* sortListInS */


PUBLIC void  spaceInS(                                                     /*M*/
    str_t* const  object_,                                                 /*-*/
    const size_t  length_,                                                 /*-*/
    const bool    align_to_end_,                                           /*-*/
    const bool    spillover_ ) {                                           /*-*/
    GO                                                            (UID(FB4EA5));
    const _str_t* const  me = _object_init(*object_, UID(E86557));
    fillInS(object_, ' ', length_, align_to_end_, spillover_, false);
    RETURN(NIL);
} /* spaceInS */


PUBLIC void  totitleInS( str_t* const  object_ ) {                         /*M*/
    GO                                                            (UID(FAA587));
    const _str_t* const  me = _object(*object_, UID(EE0541));
    if (me == NULL) {
        clearInS(object_);
    } else if (me->len > 0) {
        change_in_T(CAST(char_t*, object_->cs), CAST(int, MAKE_TITLE_CASE));
    }
    RETURN(NIL);
} /* totitleInS */


PUBLIC void  trimInS(                                                      /*M*/
    str_t* const     object_,                                              /*-*/
    chars_t const    trim_chars_,                                          /*-*/
    const trim_enum  trim_scope_ ) {                                       /*-*/
    GO                                                            (UID(FB30C6));
    _str_t* const  me = _object(*object_, UID(E01D59));

    chars_t  trim      = NULL;
    chars_t  str       = NULL;
    bool     trim_char = false;
    size_t   begin_len = 0;
    size_t   end_len   = 0;

    if (me == NULL) {
        clearInS(object_);
        RETURN(NIL);
    }

    if (IS_BLANK(_CSTR(me))) {
        RETURN(NIL);
    }

    /* count number of characters to trim from beginning */
    if (trim_scope_ == TRIM_BEGIN || trim_scope_ == TRIM_ALL) {
        str       = _CSTR(me);
        trim      = trim_chars_;
        trim_char = false;

        while (*str) {
            trim_char = false;
            trim      = trim_chars_;

            while (*trim) {
                if (*str == *trim) {
                    trim_char = true;
                    begin_len++;
                    break;
                }
                trim++;
            }

            if (!trim_char) {
                break;
            }
            str++;
        }
    }

    /* count number of characters to trim from end */
    end_len = 0;

    if (trim_scope_ == TRIM_END || trim_scope_ == TRIM_ALL) {
        str       = _CSTR(me) + me->len - 1;
        trim      = trim_chars_;
        trim_char = false;

        while (str >= _CSTR(me)) {
            trim_char = false;
            trim      = trim_chars_;

            while (*trim) {
                if (*str == *trim) {
                    trim_char = true;
                    end_len++;
                    break;
                }
                trim++;
            }

            if (!trim_char) {
                break;
            }

            str--;
        }
    }

    if (begin_len + end_len >= me->len) { /* nothing left to return */
        me->len = 0;

    } else if (begin_len + end_len > 0) {
        if (begin_len > 0) {
            char_t*  wr = NULL;
            for (wr = _STR(me); wr < (_CSTR(me) + me->len); wr++) {
                *wr = *(wr + begin_len);
            }
        }
        me->len -= (begin_len + end_len);
    }
    *(_STR(me) + me->len) = '\0';
    RETURN(NIL);
} /* trimInS */


PUBLIC void  toupperInS( str_t* const  object_ ) {                         /*M*/
    GO                                                            (UID(F36E25));
    const _str_t* const  me = _object(*object_, UID(E9F08A));
    if (me == NULL) {
        clearInS(object_);
    } else if (me->len > 0) {
        change_in_T(CAST(char_t*, object_->cs), MAKE_UPPER_CASE);
    }
    RETURN(NIL);
} /* toupperInS */


/* -------------------------------------------------------------------------- */
/* Methods: Informative                                                       */


PUBLIC bool  beginsS(                                                      /*M*/
    const str_t    object_,                                                /*-*/
    chars_t const  string_,                                                /*-*/
    const bool     ignore_case_ ) {                                        /*-*/
    GO                                                            (UID(F80687));
    const _str_t* const  me  = _object(object_, UID(EDC60C));
    const bool           ret =
        me == NULL ? false : begins3T(_CSTR(me), string_, ignore_case_);
    RETURN(ret);
} /* beginsS */


PUBLIC size_t  byteSizeS( const str_t  object_ ) {                         /*M*/
    GO                                                            (UID(FE7401));
    const _str_t* const  me  = _object(object_, UID(E1DD82));
    const size_t         ret = me == NULL ? 0 : (me->len + 1) * sizeof(char_t);
    RETURN(ret);
} /* byteSizeS */


PUBLIC size_t  capacityS( const str_t  object_ ) {                         /*M*/
    GO                                                            (UID(FD017F));
    const _str_t* const  me  = _object(object_, UID(E803B9));
    const size_t         ret = me == NULL ? 0 : me->cap;
    RETURN(ret);
} /* capacityS */


PUBLIC const char*  bcharsS( const str_t  object_ ) {                      /*M*/
    GO                                                            (UID(FFF1AF));
    const _str_t* const  me  = _object(object_, UID(E8A93B));
    if (me == NULL) {
        RETURN("");
    } else {
#if defined UNICODE || defined _UNICODE
        if (me->cnv) {
            FREE(me->cnv);
        }

        CAST(_str_t*, me)->cnv = CAST(uint8_t*, utf8_of_wide(_CSTR(me)));
        RETURN(CAST(const char*, me->cnv));
#else                                                  /* UNICODE || _UNICODE */
        RETURN(_CSTR(me));
#endif                                               /* !UNICODE && !_UNICODE */
    }
} /* bcharsS */


PUBLIC chars_t  charsS( const str_t  object_ ) {                           /*M*/
    GO                                                            (UID(FD443E));
    const _str_t* const  me  = _object(object_, UID(EE57A8));
    chars_t              ret = BLANK;
    if (me != NULL) {
        ret = _CSTR(me);
        if (ret == NULL) {
            ret = BLANK;
        }
    }
    RETURN(ret);
} /* charsS */


PUBLIC bool  containsS(                                                    /*M*/
    const str_t    object_,                                                /*-*/
    chars_t const  substring_,                                             /*-*/
    const bool     ignore_case_ ) {                                        /*-*/
    GO                                                            (UID(FB147A));
    const _str_t* const  me  = _object(object_, UID(E59870));
    bool                 ret = false;
    if (me != NULL) {
        ret = NONE == findT(_CSTR(me), substring_, 0,
                            ignore_case_, false, me->len, SIZE_MAX)
              ? false : true;
    }
    RETURN(ret);
} /* containsS */


PUBLIC size_t  countS(                                                     /*M*/
    const str_t    object_,                                                /*-*/
    chars_t const  string_,                                                /*-*/
    const bool     ignore_case_,                                           /*-*/
    const size_t   offset_ ) {                                             /*-*/
    GO                                                            (UID(FABE0F));
    const _str_t* const  me  = _object(object_, UID(E4B907));
    const size_t         ret = (me == NULL) ? 0
                               : countT(_CSTR(me),     /* main_str_     */
                                        string_,       /* find_str_     */
                                        offset_,     /* offset_     */
                                        ignore_case_,  /* ignore_case_  */
                                        false,         /* reverse_      */
                                        me->len,       /* main_len_     */
                                        SIZE_MAX,      /* find_len_     */
                                        SIZE_MAX,      /* max_count_    */
                                        NULL);         /* location_out_ */
    RETURN(ret);
} /* countS */


PUBLIC bool  endsS(                                                        /*M*/
    const str_t    object_,                                                /*-*/
    chars_t const  string_,                                                /*-*/
    const bool     ignore_case_ ) {                                        /*-*/
    GO                                                            (UID(F1DF62));
    const _str_t* const  me  = _object(object_, UID(E0CC92));
    bool                 ret = false;
    if (me != NULL) {
        chars_t const  str = _CSTR(me);
        ret = ends4T(str, string_, ignore_case_, me->len);
    }
    RETURN(ret);
} /* endsS */


PUBLIC bool  equalS(                                                       /*M*/
    const str_t    object_,                                                /*-*/
    chars_t const  string_,                                                /*-*/
    const bool     ignore_case_ ) {                                        /*-*/
    GO                                                            (UID(F9EAF7));
    const _str_t* const  me = _object(object_, UID(E6F5E4));
    const bool  ret = (me == NULL) ? false
                      : equalsT(_CSTR(me), string_, ignore_case_, SIZE_MAX);
    RETURN(ret);
} /* equalS */


PUBLIC size_t  findS(                                                      /*M*/
    const str_t    object_,                                                /*-*/
    chars_t const  find_str_,                                              /*-*/
    const size_t   offset_,                                                /*-*/
    const bool     ignore_case_,                                           /*-*/
    const bool     from_end_ ) {                                           /*-*/
    GO                                                            (UID(F371B1));
    const _str_t* const  me = _object(object_, UID(E4F499));
    const size_t  ret =
        (me == NULL) ? 0
        : find6T(_CSTR(me), find_str_, offset_, ignore_case_, from_end_,
                 me->len);
    RETURN(ret);
} /* findS */


PUBLIC size_t  findCharS(                                                  /*M*/
    const str_t   object_,                                                 /*-*/
    const char_t  find_char_,                                              /*-*/
    const size_t  offset_,                                                 /*-*/
    const bool    ignore_case_,                                            /*-*/
    const bool    from_end_ ) {                                            /*-*/
    GO                                                            (UID(F619CF));
    const _str_t* const  me = _object(object_, UID(E3843F));
    const size_t  ret =
        (me == NULL) ? 0
        : find_charT(_CSTR(me), find_char_, offset_, ignore_case_, from_end_);
    RETURN(ret);
} /* findCharS */


PUBLIC size_t  findCharsS(                                                 /*M*/
    const str_t    object_,                                                /*-*/
    chars_t const  chars_to_find_,                                         /*-*/
    const bool     ignore_case_ ) {                                        /*-*/
    GO                                                            (UID(F0087E));
    const _str_t* const  me  = _object(object_, UID(E077F1));
    if (me != NULL) {
        size_t  pos =
            find_charsT(_CSTR(me), chars_to_find_, ignore_case_, me->len);
        if (pos < SIZE_MAX) {
            RETURN(pos);
        }
    }
    RETURN(NONE);
} /* findCharsS */


PUBLIC size_t  findEndS(                                                   /*M*/
    const str_t    object_,                                                /*-*/
    chars_t const  find_str_,                                              /*-*/
    const size_t   offset_,                                                /*-*/
    const bool     ignore_case_ ) {                                        /*-*/
    GO                                                            (UID(F3EA92));
    const _str_t* const  me  = _object(object_, UID(EACC6B));
    size_t               ret = 0;
    if (me == NULL) {
        ret = 0;
    } else if (me->len < 1 || offset_ > me->len - 1 || IS_BLANK(_CSTR(me))) {
        ret = NONE;
    } else {
        ret = find6T(_CSTR(me), find_str_, offset_, ignore_case_, true,
                     me->len);
    }
    RETURN(ret);
} /* findEndS */


PUBLIC size_t  findEndChar4S(                                              /*M*/
    const str_t   object_,                                                 /*-*/
    const char_t  find_char_,                                              /*-*/
    const bool    ignore_case_,                                            /*-*/
    const size_t  offset_ ) {                                              /*-*/
    GO                                                            (UID(F997A2));
    const _str_t* const  me  = _object(object_, UID(EDF95E));
    if (me != NULL) {
        CHAR_TO_STR(ch, find_char_);
        {
            const size_t  pos = findEndS(object_, ch, offset_, ignore_case_);
            RETURN(pos);
        }
    }
    RETURN(0);
} /* findEndChar4S */


PUBLIC size_t  findFirstNotOfS(                                            /*M*/
    const str_t    object_,                                                /*-*/
    chars_t const  chars_ ) {                                              /*-*/
    GO                                                            (UID(F65FF0));
    const _str_t* const  me = _object(object_, UID(EE2A3A));
    const size_t  ret = (me == NULL) ? 0 : skip_chars2T(_CSTR(me), chars_);
    RETURN(ret);
} /* findFirstNotOfS */


PUBLIC char_t*  getBufferS( str_t* const  object_ ) {                      /*M*/
    GO                                                            (UID(FC1E72));
    _str_t* const  me  = _object(*object_, UID(EE7BE4));
    char_t* const  ret = me != NULL ? _STR(me) : NULL;
    RETURN(ret);
} /* getBufferS */


PUBLIC char_t*  getEmptyBufferS(                                           /*M*/
    str_t* const  object_,                                                 /*-*/
    const size_t  length_ ) {                                              /*-*/
    GO                                                            (UID(FDD2F9));
    const _str_t* const  me = _object_init(*object_, UID(E781BE));

    if (length_ == 0) {
        _WARN(_T("length_ == 0"), UID(E2DB9B));
    }

    {
        const size_t  len = (length_ == 0) ? 1 : length_;
        reserveInS(object_, len);
        {
            char_t* const  ret = _STR(me);
            MEMSET(ret, 0x00, me->cap * sizeof(char_t));
            RETURN(ret);
        }
    }
} /* getEmptyBufferS */


PUBLIC bool  emptyS( const str_t  object_ ) {                              /*P*/
    GO                                                            (UID(F61039));
    const _str_t* const  me = _object(object_, UID(E28A82));
    const bool  ret = me == NULL || me->len < 1 || _CSTR(me) == NULL
                      || *_CSTR(me) == '\0';
    RETURN(ret);
} /* emptyS */


PUBLIC bool  isNumberS(                                                    /*P*/
    const str_t    object_,                                                /*-*/
    const char_t   decimal_point_char_,                                    /*-*/
    const char_t   group_separator_char_,                                  /*-*/
    chars_t const  whitespaces_ ) {                                        /*-*/
    GO                                                            (UID(F0C8E0));
    const _str_t* const  me  = _object(object_, UID(E4DEE2));
    bool                 ret = false;
    if (me != NULL) {
        ret = is_numberT(_CSTR(me), decimal_point_char_, group_separator_char_,
                         whitespaces_);
    }
    RETURN(ret);
} /* isNumberS */


PUBLIC bool  isSpaceS( const str_t  object_ ) {                            /*P*/
    GO                                                            (UID(F90563));
    const _str_t* const  me  = _object(object_, UID(EF241D));
    const bool           ret = me == NULL ? false : is_whitespaceT(_CSTR(me));
    RETURN(ret);
} /* isSpaceS */


PUBLIC size_t  lengthS( const str_t  object_ ) {                           /*M*/
    GO                                                            (UID(F2FBBD));
    const _str_t* const  me  = _object(object_, UID(E31F46));
    const size_t         ret =
        (me == NULL || _CSTR(me) == NULL || *_CSTR(me) == '\0') ? 0
        : me->len;
    RETURN(ret);
} /* lengthS */


PUBLIC bool  like3S(                                                       /*M*/
    const str_t    object_,                                                /*-*/
    chars_t const  string_,                                                /*-*/
    const bool     ignore_case_ ) {                                        /*-*/
    GO                                                            (UID(F11F7A));
    const _str_t* const  me  = _object(object_, UID(E8EE02));
    const bool           ret =
        (me == NULL && lenT(string_) == 0) ? true
        : equalsT(_CSTR(me), string_, ignore_case_, SIZE_MAX);
    RETURN(ret);
} /* like3S */


PUBLIC int  lineCountS( const str_t  object_ ) {                           /*M*/
    GO                                                            (UID(F6A47C));
    const _str_t* const  me  = _object(object_, UID(ED1CE2));
    const int            ret = me == NULL ? 0 : line_countT(_CSTR(me));
    RETURN(ret);
} /* lineCountS */


PUBLIC bool  patternMatchS(                                                /*M*/
    const str_t    object_,                                                /*-*/
    chars_t const  pattern_,                                               /*-*/
    const bool     ignore_case_ ) {                                        /*-*/
    GO                                                            (UID(FFC6D6));
    const _str_t* const  me  = _object(object_, UID(E2DCDA));
    const bool  ret =
        me == NULL ? false : patternMatchT(_CSTR(me), pattern_, ignore_case_);
    RETURN(ret);
} /* patternMatchS */


PUBLIC size_t  skipCharsS(                                                 /*M*/
    const str_t    object_,                                                /*-*/
    chars_t const  chars_to_skip_,                                         /*-*/
    const bool     ignore_case_ ) {                                        /*-*/
    GO                                                            (UID(F52173));
    const _str_t* const  me  = _object(object_, UID(E0903C));
    const size_t         ret =
        (me == NULL) ? 0
        : skip_charsT(_CSTR(me), chars_to_skip_, ignore_case_, me->len);
    RETURN(ret);
} /* skipCharsS */


PUBLIC double  doubleS( const str_t  object_ ) {                           /*M*/
    GO                                                            (UID(FC3931));
    const _str_t* const  me  = _object(object_, UID(E680BE));
    double               ret = me == NULL ? 0 : doubleT(_CSTR(me));
    RETURN(ret);
} /* doubleS */


PUBLIC int  intS( const str_t  object_ ) {                                 /*M*/
    GO                                                            (UID(F45791));
    const _str_t* const  me  = _object(object_, UID(E5E77B));
    const int            ret = me == NULL ? 0 : int_T(_CSTR(me));
    RETURN(ret);
} /* intS */


PUBLIC size_t  tokenCountXtS(                                              /*M*/
    const str_t    object_,                                                /*-*/
    chars_t const  delimiter_,                                             /*-*/
    chars_t const  token_,                                                 /*-*/
    const bool     ignore_case_ ) {                                        /*-*/
    GO                                                            (UID(F25BD0));
    const _str_t* const  me = _object(object_, UID(E50EB3));
    const size_t  ret =
        (me == NULL) ? 0
        : (me->len == 0 || IS_BLANK(_CSTR(me))) ? 0
        : token_info_xtT(TOKEN_COUNT, _CSTR(me), delimiter_, token_,
                         ignore_case_, me->len, SIZE_MAX);
    RETURN(ret);
} /* tokenCountXtS */


PUBLIC bool  tokenExistsS(                                                 /*M*/
    const str_t    object_,                                                /*-*/
    chars_t const  token_,                                                 /*-*/
    chars_t const  delimiter_,                                             /*-*/
    const bool     ignore_case_ ) {                                        /*-*/
    GO                                                            (UID(F53E2C));
    const _str_t* const  me  = _object(object_, UID(E765F2));
    bool                 ret = false;
    if (me != NULL) {
        ret = C_BOOL(token_info_xtT(
                         TOKEN_EXISTS, _CSTR(me), delimiter_, token_,
                         ignore_case_, me->len, SIZE_MAX) != 0);
    }
    RETURN(ret);
} /* tokenExistsS */


PUBLIC size_t  tokenIndexS(                                                /*M*/
    const str_t    object_,                                                /*-*/
    chars_t const  token_,                                                 /*-*/
    chars_t const  delimiter_,                                             /*-*/
    const bool     ignore_case_ ) {                                        /*-*/
    GO                                                            (UID(F3CCE0));
    const _str_t* const  me  = _object(object_, UID(EB3E17));
    const size_t         ret =
        (me == NULL) ? 0
        : token_info_xtT(TOKEN_INDEX, _CSTR(me), delimiter_, token_,
                         ignore_case_, me->len, SIZE_MAX);
    RETURN(ret);
} /* tokenIndexS */


PUBLIC uint32_t  uintS( const str_t  object_ ) {                           /*M*/
    GO                                                            (UID(F3C155));
    const _str_t* const  me  = _object(object_, UID(EFE078));
    uint32_t             ret = me == NULL ? 0 : uint_of_T(_CSTR(me));
    RETURN(ret);
} /* uintS */


PUBLIC const wchar_t*  wcharsS( const str_t  object_ ) {                   /*M*/
    GO                                                            (UID(F4F1EA));
    _str_t* const  me = _object(object_, UID(E546EB));
    if (me == NULL || _CSTR(me) == NULL) {
        RETURN(L"");
    } else {
#if defined UNICODE || defined _UNICODE
        RETURN(_CSTR(me));
#else
        if (me->cnv) {
            FREE(me->cnv);
        }

        me->cnv = CAST(uint8_t*, wide_of_utf8(_CSTR(me)));
        RETURN(CAST(const wchar_t* const, me->cnv));
#endif                                               /* !UNICODE && !_UNICODE */
    }
} /* wcharsS */


/* -------------------------------------------------------------------------- */
/* Methods: Allocating                                                        */


PUBLIC new_str_t  S_bracket(                                               /*C*/
    const str_t    object_,                                                /*-*/
    chars_t const  brackets_ ) {                                           /*-*/
    GO                                                            (UID(F5515F));
    const _str_t* const  me   = _object(object_, UID(E05D5A));
    new_str_t            ret  = { NULL };
    char_t*              wr   = NULL;
    _str_t*              head = NULL;

    if (me == NULL) {
        ret = S_blank();
        RETURN(ret);
    }

    if (brackets_ == NULL ||
        brackets_[0] == '\0' || brackets_[1] == '\0') {

        _WARN(_T("Missing bracket(s)."), UID(E1C2CF));
        ret = S_copy(object_);
        RETURN(ret);
    }

    if (me->len == 0) {
        char_t  empty[3] = { 0, 0, 0 };
        empty[0] = brackets_[0];
        empty[1] = brackets_[1];
        ret = S_chars(empty);
        RETURN(ret);
    }

    {
        const size_t  cap = me->len + 3;  /* 2 brackets and \0 */
        _create(cap, &head, &wr);
    }

    {
        size_t  len = 0;

        /* append opening bracket */
        chars_t  rd = _CSTR(me);
        if (*rd != brackets_[0]) {
            *wr++ = brackets_[0];
            len++;
        }

        {
            /* copy string */
            size_t  i = 0;
            for (i = 0; i < me->len; i++) {
                *wr++ = *rd++;
                len++;
            }
        }

        /* append closing bracket */
        if (*(wr - 1) != brackets_[1]) {
            *wr++ = brackets_[1];
            len++;
        }

        *wr       = '\0';  /* terminating null */
        head->len = len;
        ret       = _object_wrap(head);
    }
    RETURN(ret);
} /* S_bracket */


PUBLIC new_str_t  S_decodeBase64( const str_t  object_ ) {                 /*C*/
    GO                                                            (UID(F51AC3));
    const _str_t* const  me  = _object(object_, UID(E02A87));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        chars_t const  str = _CSTR(me);
        ret = S_newT(T_decode_base64(str));
    }
    RETURN(ret);
} /* S_decodeBase64 */


PUBLIC new_str_t  S_encodeBase64( const str_t  object_ ) {                 /*C*/
    GO                                                            (UID(F59817));
    const _str_t* const  me  = _object(object_, UID(EC717B));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        chars_t const  str = _CSTR(me);
        ret = S_newT(T_encode_base64(str));
    }
    RETURN(ret);
} /* S_encodeBase64 */


PUBLIC new_str_t  S_first(                                                 /*C*/
    const str_t   object_,                                                 /*-*/
    const size_t  length_ ) {                                              /*-*/
    GO                                                            (UID(F3039F));
    const _str_t* const  me  = _object(object_, UID(E442B1));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();

    } else if (me->len < 1 || length_ < 1 || IS_BLANK(_CSTR(me))) {
        ret = S_blank();

    } else {
        const size_t  len  = LESSER(length_, me->len);
        _str_t*       head = NULL;

        _create(len, &head, NULL);
        head->len = len;
        ret = _object_wrap(head);

        if (len > 0) {
            const size_t   bytes_size = len * sizeof(char_t);
            chars_t const  from       = _CSTR(me);
            char_t* const  to         = CAST(char_t*, ret.cs);
            MEMCPY(to, from, bytes_size);
        }
    }
    RETURN(ret);
} /* S_first */


PUBLIC new_str_t  S_substr(                                                /*C*/
    const str_t   object_,                                                 /*-*/
    const size_t  offset_,                                                 /*-*/
    const size_t  count_ ) {                                               /*-*/
    GO                                                            (UID(F972AB));
    const _str_t* const  me  = _object(object_, UID(E668A8));
    new_str_t            ret = { NULL };

    if (me == NULL || offset_ >= me->len || me->len < 1 || count_ < 1) {
        ret = S_blank();

    } else {
        const size_t  len  = len_maxT(_CSTR(me), count_);
        _str_t*       head = NULL;
        char_t*       str  = NULL;
        _create(len, &head, &str);

        MEMCPY(str, _CSTR(me) + offset_, (len + 1) * sizeof(char_t));
        *(str + len) = '\0';
        head->len = len;
        ret = _object_wrap(head);
    }
    RETURN(ret);
} /* S_substr */


PUBLIC new_str_t  S_insert(                                                /*C*/
    const str_t    object_,                                                /*-*/
    chars_t const  string_,                                                /*-*/
    const size_t   insert_at_position_,                                    /*-*/
    const size_t   length_ ) {                                             /*-*/
    GO                                                            (UID(F1513A));
    new_str_t  ret = { NULL };
    chars_t    str = NULL;
    size_t     len = 0;

    {
        const _str_t* const  me = _object(object_, UID(E631E7));
        if (me != NULL) {
            str = _CSTR(me);
            len = me->len;
        }
    }

    {
        const size_t  str_len = len_maxT(string_, length_);
        const size_t  new_len = str_len + len;
        _str_t*       head    = NULL;
        char_t*       wr      = NULL;

        const size_t  pos =
            (insert_at_position_ > 0 && insert_at_position_ >= len)
            ? (len == 0 ? 0 : len - 1) : insert_at_position_;

        if (insert_at_position_ > 0 && insert_at_position_ >= len) {
            _WARN(_T("insert_at_position_ out of range."), UID(E05240));
        }

        _create(new_len, &head, &wr);

        /* append part before pos */
        if (pos > 0) {
            MEMCPY(wr, str, pos * sizeof(char_t));
            wr += pos;
        }

        /* append inserted string */
        MEMCPY(wr, string_, str_len * sizeof(char_t));
        wr += str_len;

        /* append part after pos */
        if (pos < len) {
            const size_t  chr_count = (len - pos);
            MEMCPY(wr, str + pos, chr_count * sizeof(char_t));
            wr += chr_count;
        }

        *wr = '\0';
        ret = _object_wrap(head);
        head->len = new_len;
    }
    RETURN(ret);
} /* S_insert */


PUBLIC new_str_t  S_last(                                                  /*C*/
    const str_t   object_,                                                 /*-*/
    const size_t  length_ ) {                                              /*-*/
    GO                                                            (UID(F380E7));
    const _str_t* const  me  = _object(object_, UID(E615F6));
    new_str_t            ret = { NULL };

    if (me == NULL || me->len < 1 || length_ < 1 || IS_BLANK(_CSTR(me))) {
        ret = S_blank();
    } else {
        const size_t  len  = LESSER(length_, me->len);
        _str_t*       head = NULL;

        _create(len, &head, NULL);
        ret = _object_wrap(head);

        if (len > 0) {
            MEMCPY(_STR(CAST(_str_t*, ret.cs)),
                   _CSTR(me) + me->len - len,
                   len * sizeof(char_t));
        }
    }
    RETURN(ret);
} /* S_last */


PUBLIC new_str_t  S_lowerCase( const str_t  object_ ) {                    /*C*/
    GO                                                            (UID(FC5068));
    const _str_t* const  me  = _object(object_, UID(EF900A));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        ret = S_copy(object_);
        if (me->len > 0) {
            change_in_T(CAST(char_t*, ret.cs), MAKE_LOWER_CASE);
        }
    }
    RETURN(ret);
} /* S_lowerCase */


PUBLIC new_str_t  S_quote(                                                 /*C*/
    const str_t    object_,                                                /*-*/
    chars_t const  quote_,                                                 /*-*/
    chars_t const  replace_ ) {                                            /*-*/
    GO                                                            (UID(F63013));
    const _str_t* const  me  = _object(object_, UID(E5D05B));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        new_str_t  str = S_copy(object_);
        ret = S_chars(quote_);
        setReplaceS(&str, quote_, replace_, IGNORE_CASE, SIZE_MAX, SIZE_MAX);
        addTS(&ret, _CSTR(CAST(_str_t*, str.cs)));
        addTS(&ret, quote_);
        freeS(&str);
    }
    RETURN(ret);
} /* S_quote */


PUBLIC new_str_t  S_remove(                                                /*C*/
    const str_t   object_,                                                 /*-*/
    const size_t  position_,                                               /*-*/
    const size_t  length_ ) {                                              /*-*/
    GO                                                            (UID(F38FF6));
    const _str_t* const  me  = _object(object_, UID(EE5CA2));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        _str_t*  head = NULL;
        char_t*  wr   = NULL;
        size_t   pos  = position_;
        size_t   len  = length_;

        if (pos >= me->len) {
            _WARN(_T("position_ out of range."), UID(E65F46));
            pos = 0;
            len = 0;
        }

        if ((pos + len) > me->len) {
            _WARN(_T("(position_ + length_) out of range."), UID(E46119));
            len = me->len - pos;
        }

        {
            const size_t  new_len = me->len - len;
            _create(new_len, &head, &wr);

            /* append part before pos */
            if (pos > 0) {
                MEMCPY(wr, _CSTR(me), pos * sizeof(char_t));
                wr += pos;
            }

            /* append part after pos */
            if (pos < (me->len - 1)) {
                const size_t  chr_count = (me->len - pos - len);
                MEMCPY(wr, _CSTR(me) + pos + len, chr_count * sizeof(char_t));
                wr += chr_count;
            }
            *wr = '\0';
            head->len = new_len;
        }
        ret = _object_wrap(head);
    }
    RETURN(ret);
} /* S_remove */


PUBLIC new_str_t  S_removeBegin(                                           /*C*/
    const str_t   object_,                                                 /*-*/
    const size_t  char_count_ ) {                                          /*-*/
    GO                                                            (UID(F08395));
    const _str_t* const  me  = _object(object_, UID(EFAA4C));
    new_str_t            ret = { NULL };

    if (me == NULL || char_count_ > me->len) {
        ret = S_blank();

    } else if (char_count_ < 1) {
        ret = S_firstChars(_CSTR(me), me->len);

    } else {
        ret = S_firstChars(_CSTR(me) + char_count_, me->len - char_count_);
    }
    RETURN(ret);
} /* S_removeBegin */


PUBLIC new_str_t  S_removeChar(                                            /*C*/
    const str_t   object_,                                                 /*-*/
    const char_t  char_,                                                   /*-*/
    const bool    ignore_case_ ) {                                         /*-*/
    GO                                                            (UID(F1653D));
    const _str_t* const  me  = _object(object_, UID(E1402C));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        CHAR_TO_STR(find, char_);
        ret = S_copy(object_);
        setReplaceS(&ret, find, BLANK, ignore_case_, SIZE_MAX, 0);
    }
    RETURN(ret);
} /* S_removeChar */


PUBLIC new_str_t  S_removeEnd(                                             /*C*/
    const str_t   object_,                                                 /*-*/
    const size_t  char_count_ ) {                                          /*-*/
    GO                                                            (UID(F205A0));
    const _str_t* const  me  = _object(object_, UID(ED5C1B));
    new_str_t            ret = { NULL };

    if (me == NULL || char_count_ > me->len) {
        ret = S_blank();

    } else if (char_count_ < 1) {
        ret = S_firstChars(_CSTR(me), me->len);
    } else {
        ret = S_firstChars(_CSTR(me), me->len - char_count_);
    }
    RETURN(ret);
} /* S_removeEnd */


PUBLIC new_str_t  S_removeStr(                                             /*C*/
    const str_t    object_,                                                /*-*/
    chars_t const  string_,                                                /*-*/
    const bool     ignore_case_ ) {                                        /*-*/
    GO                                                            (UID(F91D0B));
    const _str_t* const  me  = _object(object_, UID(E15665));
    new_str_t            ret = { NULL };
    if (me == NULL) {
        ret = S_blank();
    } else {
        ret = S_copy(object_);
        setReplaceS(&ret, string_, BLANK, ignore_case_, SIZE_MAX, 0);
    }
    RETURN(ret);
} /* S_removeStr */


PUBLIC new_str_t  S_replace(                                               /*C*/
    const str_t    object_,                                                /*-*/
    chars_t const  find_str_,                                              /*-*/
    chars_t const  replace_str_,                                           /*-*/
    const bool     ignore_case_ ) {                                        /*-*/
    GO                                                            (UID(F9CC54));
    const _str_t* const  me  = _object(object_, UID(E3A535));
    if (me == NULL) {
        RETURN(S_blank());
    } else {
        const size_t  find_len = STRLEN_T(find_str_);
        const size_t  repl_len = STRLEN_T(replace_str_);
        new_str_t     ret      = S_copy(object_);

        setReplaceS(&ret, find_str_, replace_str_, ignore_case_,
                    find_len, repl_len);
        RETURN(ret);
    }
} /* S_replace */


PUBLIC new_str_t  S_replaceByRef(                                          /*C*/
    const str_t  object_,                                                  /*-*/
    const str_t  find_,                                                    /*-*/
    const str_t  replace_,                                                 /*-*/
    const bool   ignore_case_ ) {                                          /*-*/
    GO                                                            (UID(FD813C));
    const _str_t* const  me  = _object(object_, UID(EB41A4));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        const _str_t* const  find = _object(find_,    UID(E1DF41));
        const _str_t* const  repl = _object(replace_, UID(E28A28));

        ret = S_copy(object_);

        setReplaceS(&ret, _CSTR(find), _CSTR(repl), ignore_case_,
                    find->len, repl->len);
    }
    RETURN(ret);
} /* S_replaceByRef */


PUBLIC new_str_t  S_reverse( const str_t  object_ ) {                      /*C*/
    GO                                                            (UID(FC887D));
    const _str_t* const  me  = _object(object_, UID(EDD0E0));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        ret = S_copy(object_);
        if (me->len > 0) {
            change_in_T(CAST(char_t*, ret.cs), MAKE_REVERSE);
        }
    }
    RETURN(ret);
} /* S_reverse */


PUBLIC new_str_t  S_sortList(                                              /*C*/
    const str_t    object_,                                                /*-*/
    chars_t const  delimiter_,                                             /*-*/
    const bool     descending_,                                            /*-*/
    const bool     unique_ ) {                                             /*-*/
    GO                                                            (UID(F0EB49));
    const _str_t* const  me  = _object(object_, UID(E1EE9C));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        ret = S_copy(object_);
        sortListInS(&ret, delimiter_, descending_, unique_);
    }
    RETURN(ret);
} /* S_sortList */


PUBLIC new_str_t  S_space(                                                 /*C*/
    const str_t   object_,                                                 /*-*/
    const size_t  length_in_chars_,                                        /*-*/
    const bool    align_to_end_,                                           /*-*/
    const bool    spillover_ ) {                                           /*-*/
    GO                                                            (UID(F9D024));
    const _str_t* const  me  = _object(object_, UID(E35297));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        ret = S_copy(object_);
        fillInS(&ret, ' ', length_in_chars_, align_to_end_, spillover_, true);
    }
    RETURN(ret);
} /* S_space */


PUBLIC new_str_t  S_getTag(                                                /*C*/
    const str_t    object_,                                                /*-*/
    chars_t const  tag_,                                                   /*-*/
    chars_t const  end_tag_,                                               /*-*/
    chars_t const  delimiter_,                                             /*-*/
    const bool     ignore_case_,                                           /*-*/
    const size_t   instance_no_ ) {                                        /*-*/
    GO                                                            (UID(F0281C));
    const _str_t* const  me  = _object(object_, UID(EE4EF8));
    new_str_t            ret = { NULL };

    if (me == NULL || IS_BLANK(_CSTR(me))) {
        ret = S_blank();

    } else {
        /* calculate lengths of tags and delimiter */
        const size_t  tag_len     = STRLEN_T(tag_);
        const size_t  end_tag_len = STRLEN_T(end_tag_);
        const size_t  delim_len   = STRLEN_T(delimiter_);

        /* get position of the required instance of the named tag */
        size_t  loc = NONE;
        {
            size_t  next = 0;
            size_t  i    = instance_no_;
            do {
                loc  = find3T(_CSTR(me), tag_, next);
                next = loc + tag_len;
            } while (i--);
        }

        /* return a blank string if named tag is not found */
        if (loc == NONE) {
            ret = S_blank();

        } else {  /* calculate end position */
            size_t  end = NONE;
            loc += tag_len;

            if (end_tag_len > 0) {
                end = find4T(_CSTR(me), end_tag_, loc, ignore_case_);
            } else if (delim_len > 0) {
                end = find4T(_CSTR(me), delimiter_, loc, ignore_case_);
            }

            {
                /* return a part of the main string */
                const size_t   len = (end == NONE ? SIZE_MAX : end - loc);
                chars_t const  str = _CSTR(me) + loc;
                ret = S_firstChars(str, len);
            }
        }
    }
    RETURN(ret);
} /* S_getTag */


PUBLIC new_str_t  S_titleCase( const str_t  object_ ) {                    /*C*/
    GO                                                            (UID(FC6F3A));
    const _str_t* const  me  = _object(object_, UID(ECE5BD));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        ret = S_copy(object_);
        if (me->len > 0) {
            change_in_T(CAST(char_t*, ret.cs), MAKE_TITLE_CASE);
        }
    }
    RETURN(ret);
} /* S_titleCase */


PUBLIC new_str_t  S_getToken(                                              /*C*/
    const str_t    object_,                                                /*-*/
    const size_t   index_,                                                 /*-*/
    chars_t const  delimiter_ ) {                                          /*-*/
    GO                                                            (UID(F3FC29));
    const _str_t* const  me  = _object(object_, UID(EAA7ED));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        ret = S_newT(T_get_token_xt(_CSTR(me), index_, delimiter_, false));
    }
    RETURN(ret);
} /* S_getToken */


PUBLIC new_str_t  S_getTokenXt(                                            /*C*/
    const str_t    object_,                                                /*-*/
    const size_t   index_,                                                 /*-*/
    chars_t const  delimiter_,                                             /*-*/
    const bool     ignore_end_delimiter_ ) {                               /*-*/
    GO                                                            (UID(FFBBA6));
    const _str_t* const  me  = _object(object_, UID(E5E4C2));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        ret = S_newT(T_get_token_xt(_CSTR(me), index_, delimiter_,
                                    ignore_end_delimiter_));
    }
    RETURN(ret);
} /* S_getTokenXt */


PUBLIC new_str_t  S_setToken(                                              /*C*/
    const str_t    object_,                                                /*-*/
    const size_t   index_,                                                 /*-*/
    chars_t const  token_,                                                 /*-*/
    chars_t const  delimiter_ ) {                                          /*-*/
    GO                                                            (UID(FCAE8C));
    const _str_t* const  me  = _object(object_, UID(E05AA3));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        ret = S_newT(T_set_token(_CSTR(me), index_, token_, delimiter_));
    }
    RETURN(ret);
} /* S_setToken */


PUBLIC new_str_t  S_trim(                                                  /*C*/
    const str_t      object_,                                              /*-*/
    chars_t const    trim_chars_,                                          /*-*/
    const trim_enum  trim_scope_ ) {                                       /*-*/
    GO                                                            (UID(F56DAD));
    const _str_t* const  me  = _object(object_, UID(E9640A));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        ret = S_copy(object_);
        trimInS(&ret, trim_chars_, trim_scope_);
    }
    RETURN(ret);
} /* S_trim */


PUBLIC new_str_t  S_trimBegin(                                             /*C*/
    const str_t    object_,                                                /*-*/
    chars_t const  trim_chars_ ) {                                         /*-*/
    GO                                                            (UID(F3F1CA));
    const _str_t* const  me  = _object(object_, UID(EC0C7F));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        ret = S_copy(object_);
        trimInS(&ret, trim_chars_, TRIM_BEGIN);
    }
    RETURN(ret);
} /* S_trimBegin */


PUBLIC new_str_t  S_trimBeginChar(                                         /*C*/
    const str_t   object_,                                                 /*-*/
    const char_t  char_ ) {                                                /*-*/
    GO                                                            (UID(F39D3B));
    const _str_t* const  me  = _object(object_, UID(E455AE));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        CHAR_TO_STR(ch, char_);
        ret = S_copy(object_);
        trimInS(&ret, ch, TRIM_BEGIN);
    }
    RETURN(ret);
} /* S_trimBeginChar */


PUBLIC new_str_t  S_trimChar(                                              /*C*/
    const str_t      object_,                                              /*-*/
    const char_t     char_,                                                /*-*/
    const trim_enum  trim_scope_ ) {                                       /*-*/
    GO                                                            (UID(F9147A));
    const _str_t* const  me  = _object(object_, UID(E61FD4));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        CHAR_TO_STR(ch, char_);
        ret = S_copy(object_);
        trimInS(&ret, ch, trim_scope_);
    }
    RETURN(ret);
} /* S_trimChar */


PUBLIC new_str_t  S_trimEnd(                                               /*C*/
    const str_t    object_,                                                /*-*/
    chars_t const  trim_chars_ ) {                                         /*-*/
    GO                                                            (UID(F52489));
    const _str_t* const  me  = _object(object_, UID(E8F4E2));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        ret = S_copy(object_);
        trimInS(&ret, trim_chars_, TRIM_END);
    }
    RETURN(ret);
} /* S_trimEnd */


PUBLIC new_str_t  S_trimEndChar(                                           /*C*/
    const str_t   object_,                                                 /*-*/
    const char_t  char_ ) {                                                /*-*/
    GO                                                            (UID(FC0E78));
    const _str_t* const  me  = _object(object_, UID(ED5ABE));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        CHAR_TO_STR(ch, char_);
        ret = S_copy(object_);
        trimInS(&ret, ch, TRIM_END);
    }
    RETURN(ret);
} /* S_trimEndChar */


PUBLIC new_str_t  S_trimStr(                                               /*C*/
    const str_t      object_,                                              /*-*/
    chars_t const    string_,                                              /*-*/
    const trim_enum  trim_scope_,                                          /*-*/
    const bool       ignore_case_ ) {                                      /*-*/
    GO                                                            (UID(F13EEF));
    const _str_t* const  me  = _object(object_, UID(E18228));
    new_str_t            ret = { NULL };

    if (me == NULL || IS_BLANK(_CSTR(me))) {
        ret = S_blank();
    } else {
        const size_t  find_len = STRLEN_T(string_);
        size_t        len      = me->len;
        size_t        pos      = 0;

        if (find_len < 1) {
            ret = S_firstChars(_CSTR(me), me->len);
        } else {
            if (trim_scope_ == TRIM_BEGIN || trim_scope_ == TRIM_ALL) {
                while (begins3T(_CSTR(me) + pos, string_, ignore_case_)) {
                    pos += find_len;
                }
            }

            if (trim_scope_ == TRIM_END || trim_scope_ == TRIM_ALL) {
                while (endsT(_CSTR(me), string_, ignore_case_, len, find_len)) {
                    len -= find_len;
                }
            }
            ret = S_firstChars(_CSTR(me) + pos, len);
        }
    }
    RETURN(ret);
} /* S_trimStr */


PUBLIC new_str_t  S_unquote(                                               /*C*/
    const str_t    object_,                                                /*-*/
    chars_t const  quote_,                                                 /*-*/
    chars_t const  replace_ ) {                                            /*-*/
    GO                                                            (UID(FC40C9));
    const _str_t* const  me  = _object(object_, UID(E787F3));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        size_t        begin     = 0;
        size_t        len       = me->len;
        const size_t  quote_len = STRLEN_T(quote_);

        if (begins3T(_CSTR(me), quote_, MATCH_CASE)) {
            begin = quote_len;
            len -= quote_len;
        }

        if (endsT(_CSTR(me), quote_, MATCH_CASE, SIZE_MAX, SIZE_MAX)) {
            len -= quote_len;
        }

        ret = S_substr(object_, begin, len);
        setReplaceS(&ret, replace_, quote_, IGNORE_CASE, SIZE_MAX, SIZE_MAX);
    }
    RETURN(ret);
} /* S_unquote */


PUBLIC new_str_t  S_upperCase( const str_t  object_ ) {                    /*C*/
    GO                                                            (UID(FBEBAB));
    const _str_t* const  me  = _object(object_, UID(EFE569));
    new_str_t            ret = { NULL };

    if (me == NULL) {
        ret = S_blank();
    } else {
        ret = S_copy(object_);
        if (me->len > 0) {
            change_in_T(CAST(char_t*, ret.cs), MAKE_UPPER_CASE);
        }
    }
    RETURN(ret);
} /* S_upperCase */


/* -------------------------------------------------------------------------- */
/* Functions: String Allocating                                               */


/* Convert a value into a hexadecimal string.                                 */
PUBLIC new_str_t  S_hex(                                                   /*F*/
    const uint32_t  value_,                                                /*-*/
    const size_t    minimum_length_ ) {                                    /*-*/
    GO                                                            (UID(FF5C14));
    new_chars_t const  chars = T_hex(value_, minimum_length_);
    new_str_t          ret   = S_newT(chars);
    RETURN(ret);
} /* S_hex */


/* -------------------------------------------------------------------------- */
/* Functions: Windows-specific OLE Strings                                    */


#if PLATFORM_WIN32
PUBLIC new_str_t  S_of_bstr( const BSTR_win  text_ ) {                     /*F*/
    GO                                                            (UID(FF591B));
    new_chars_t const  chars = T_bstr(text_);
    new_str_t          ret   = S_newT(chars);
    RETURN(ret);
} /* S_of_bstr */
#endif                                                      /* PLATFORM_WIN32 */


/* -------------------------------------------------------------------------- */
/*  This file uses the following library functions:

    ----------------------------------------------------------------------------
    ALIAS FN.     C-LIBRARY FN.            HEADER FILE / ALTERNATIVE HEADER
    ----------------------------------------------------------------------------
    FREE()        free()                   stdlib.h / malloc.h
    ISALPHA_T()   isalpha() / iswalpha()   ctype.h  / wchar.h
    MEMCPY()      memcpy()                 string.h / memory.h
    MEMMOVE()     memmove()                string.h
    MEMSET()      memset()                 string.h / memory.h
    PRINTF_T()    printf() / wprintf()     stdio.h  / wchar.h
    QSORT()       qsort()                  stdlib.h / search.h
    REALLOC()     realloc()                stdlib.h / malloc.h
    SNPRINTF_T()  snprintf() / swprintf()  stdio.h  / wchar.h
    STRLEN_T()    strlen() / wcslen()      string.h / wchar.h
    TOLOWER_T()   tolower() / towlower()   ctype.h  / wchar.h
    TOUPPER_T()   toupper() / towupper()   ctype.h  / wchar.h
    MALLOC()      malloc()                 stdlib.h / malloc.h

    Library macros used in this file:
    _T
    NAMESPACE
    CAST
    CHAR_TO_STR
    DEBUG
    END_NAMESPACE
    FN_NAME
    GO
    GREATER
    LESSER
    NIL
    PLATFORM_WIN32
    PUBLIC
    RETURN
    UID
    UNUSED
    WARN
*/

END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
