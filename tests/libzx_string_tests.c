/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                [libex_string_tests.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_c_tests_.h"
#if defined INCLUDED_LIBEX_C_TESTS__H

#include <limits.h>  /* for INT_MIN, INT_MAX */
#include <stdio.h>   /* for printf()         */
#include <string.h>  /* for memset()         */

#include "libex_config_.h"
#if PLATFORM_WIN32
#include <tchar.h>
#include <windows.h>
#endif

#include "libex_all_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#define _TYPE_STRING_MAIN  0xAA
#define _TYPE_STRING_EXTN  0xBB

#define _INIT_TEST_VARS            \
    str_t    test_str = { NULL };  \
    size_t   cap      = 0;         \
    size_t   len      = 0;         \
    chars_t  str      = NULL;      \
    chars_t  ext      = NULL;      \
    void*    cnv      = NULL;      \
    \
    CLEAR(test_str);  \
    cap = 0;          \
    len = 0;          \
    str = NULL;       \
    ext = NULL;       \
    cnv = NULL;   /*#*/

#define _READ_TEST_VARS       \
    cap = _cap(test_str);     \
    len = _len(test_str);     \
    str = _str(test_str);     \
    ext = _ext(test_str);     \
    cnv = _cnv(test_str)  /*#*/

#if defined __GNUC__
#pragma GCC diagnostic ignored "-Wredundant-decls"
#endif

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#if defined _MSC_VER
#pragma warning (disable:4127)  /* W:L4 conditional expression is constant    */
#pragma warning (disable:4204)  /* W:L4 nonstandard extension used :          */
/* W:C4204                              non-constant aggregate initializer    */
#endif

#define NUM_0_TO_9_X50                                            \
    _T("01234567890123456789012345678901234567890123456789")      \
    _T("01234567890123456789012345678901234567890123456789")      \
    _T("01234567890123456789012345678901234567890123456789")      \
    _T("01234567890123456789012345678901234567890123456789")      \
    _T("01234567890123456789012345678901234567890123456789")      \
    _T("01234567890123456789012345678901234567890123456789")      \
    _T("01234567890123456789012345678901234567890123456789")      \
    _T("01234567890123456789012345678901234567890123456789")      \
    _T("01234567890123456789012345678901234567890123456789")      \
    _T("01234567890123456789012345678901234567890123456789")  /*#*/

#define A_TO_Z_X10                                                  \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")  /*#*/

#define A_TO_Z_X50                                                  \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")      \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")  /*#*/


/* The following section is copied directly from libex_string_class.c */

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


static _str_t*  _object(                                                   /*F*/
    str_t           object_,                                               /*-*/
    const uint32_t  uid_ ) {                                               /*-*/
    GO                                                            (UID(F6DA4E));
    if (object_.cs == NULL) {
        RETURN(NULL);
    }

    if (CAST(unsigned long, object_.cs) == 0xCCCCCCCCU ||
        CAST(unsigned long, object_.cs) == 0xFEEEFEEEU) {
        WARN(_T("Uninitialized object!"), uid_);
        RETURN(NULL);
    }

    {
        _ext_t*  ext =
            CAST(_ext_t*, CAST(uint8_t*, object_.cs) - sizeof(_ext_t));

        if (ext->type == _TYPE_STRING_EXTN) {
            _str_t*  ret = ext->owner;
            RETURN(ret);

        } else {
            _str_t*  ret =
                CAST(_str_t*, CAST(uint8_t*, object_.cs) - sizeof(_str_t));

            if (ret->type == _TYPE_STRING_MAIN) {
                RETURN(ret);
            } else {
                WARN(_T("UNKNOWN STRUCTURE"), UID(E013C0));
                RETURN(NULL);
            }
        }
    }
} /* _object */


static size_t  _cap( const str_t  object_ ) {                              /*F*/
    GO                                                            (UID(FB2432));
    const _str_t*  ob  = _object(object_, UID(E3515C));
    const size_t   ret = ob ? ob->cap : 0;
    RETURN(ret);
} /* _cap */


static size_t  _len( const str_t  object_ ) {                              /*F*/
    GO                                                            (UID(FEA222));
    const _str_t*  ob  = _object(object_, UID(E84CF6));
    const size_t   ret = ob ? ob->len : 0;
    RETURN(ret);
} /* _len */


static void*  _ext( str_t  object_ ) {                                     /*F*/
    GO                                                            (UID(F390CF));
    _str_t*  ob  = _object(object_, UID(EA6BCC));
    void*    ret = ob ? ob->ext : 0;
    RETURN(ret);
} /* _len */


static void*  _cnv( str_t  object_ ) {                                     /*F*/
    GO                                                            (UID(F09E27));
    _str_t*  ob  = _object(object_, UID(E618F7));
    void*    ret = ob ? ob->cnv : 0;
    RETURN(ret);
} /* _len */


static char_t*  _str( str_t  object_ ) {                                   /*F*/
    GO                                                            (UID(F92E82));
    char_t*  ret = CAST(char_t*, object_.cs);
    RETURN(ret);
} /* _str */


/* -------------------------------------------------------------------------- */


static bool  _equal(                                                       /*F*/
    chars_t  string1_,                                                     /*-*/
    chars_t  string2_ ) {                                                  /*-*/
    GO                                                            (UID(FE2155));
    const bool  is_blank1 = (string1_ == NULL || string1_[0] == '\0');
    const bool  is_blank2 = (string2_ == NULL || string2_[0] == '\0');

    if (is_blank1 && is_blank2) {
        RETURN(true);

    } else if ((is_blank1 && !is_blank2) && (!is_blank1 && is_blank2)) {
        RETURN(false);

    } else if (STRCMP_T(string1_, string2_) == 0) {
        RETURN(true);
    }

    RETURN(false);
} /* _equal */


#define _assert( CONDITION_ )                    \
    _assert_fn(CONDITION_, _T(#CONDITION_))  /*#*/

/* Use _assert macro. Don't call _assert_fn() directly. */
static void  _assert_fn(                                                   /*F*/
    const bool  condition_,                                                /*-*/
    chars_t     message_ ) {                                               /*-*/
    GO                                                            (UID(FF0651));
    if (!condition_) {
        PRINTF_T(_T("\r\n") _T("Test Failed: %s"), message_);
        /* ------------------------------------------------------------------ */
        DEBUG_BREAK;
        /* ------------------------------------------------------------------ */
    }
    RETURN(NIL);
} /* _assert_fn */


#define _CHECK_STR_INIT( EXPRESSION_, EXPECTED_ )                 \
    {                                                             \
        new_str_t  str = EXPRESSION_;                             \
        _check_str_init_fn(_T(#EXPRESSION_), str.cs, EXPECTED_);  \
        freeS(&str);                                              \
    }                                                         /*#*/

/* Use _CHECK_STR_INIT() macro. Don't call this function directly.           */
static void  _check_str_init_fn(                                           /*F*/
    chars_t  expression_,                                                  /*-*/
    chars_t  result_,                                                      /*-*/
    chars_t  expected_ ) {                                                 /*-*/
    GO                                                            (UID(FCF962));
    if (STRCMP_T(result_, expected_) != 0) {
        PRINTF_T(_T("\r\n") _T("Failed: %s != '%s' (returned '%s')"),
                 expression_, expected_, result_);
        /* ------------------------------------------------------------------ */
        DEBUG_BREAK;
        /* ------------------------------------------------------------------ */
    }
    RETURN(NIL);
} /* _check_str_init_fn */


static void  _check_str(                                                   /*F*/
    str_t    test_,                                                        /*-*/
    chars_t  expect_string_ ) {                                            /*-*/
    GO                                                            (UID(FA825A));
    const size_t  cap = _cap(test_);
    const size_t  len = _len(test_);
    chars_t       str = _str(test_);
    chars_t       ext = _ext(test_);
    void*         cnv = _cnv(test_);

    size_t   check_len = 0;
    chars_t  rd = str;

    if (rd != NULL) {
        while (*(rd++)) {
            check_len++;
        }
    }

    if (ext == NULL) {
        _assert(cap <= STR_INITIAL_CAPACITY);
    } else {
        _assert(cap > STR_INITIAL_CAPACITY);
    }

    _assert(len == check_len);
    _assert(cap >= len);
    _assert(str == NULL || ((void*)str) != ((void*)cnv));
    _assert(_equal(str, expect_string_));

    RETURN(NIL);
} /* _check_str */


/* -------------------------------------------------------------------------- */


PUBLIC void  freeS( str_t*  object_ );                                     /*D*/

static void  _test_freeS( void ) {                                         /*F*/
    GO                                                            (UID(F21C81));
    _INIT_TEST_VARS;
    freeS(&test_str);  /*null-test*/
    RETURN(NIL);
} /* _test_freeS */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_chars( chars_t  text_ );                               /*C*/

static void  _test_Schars( void ) {                                        /*F*/
    GO                                                            (UID(FE9D04));
    _INIT_TEST_VARS;

#define _TEST( INIT_STR_, CHECK_STR_ )   \
    test_str = S_chars(INIT_STR_);        \
    _check_str(test_str, CHECK_STR_);    \
    freeS(&test_str)                 /*#*/

    _TEST(NULL,         _T(""));  /*null-test*/
    _TEST(_T(""),       _T(""));
    _TEST(_T("\0"),     _T(""));
    _TEST(_T(" "),      _T(" "));
    _TEST(_T("\t"),     _T("\t"));
    _TEST(_T("A"),      _T("A"));
    _TEST(_T("ABC"),    _T("ABC"));
    _TEST(_T("ABCDEF"), _T("ABCDEF"));

#undef _TEST

    RETURN(NIL);
} /* _test_Schars */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_append(                                                /*C*/
    const str_t  object_,                                                  /*-*/
    chars_t      string_ );                                                /*-*/

static void  _test_Sappend( void ) {                                       /*F*/
    GO                                                            (UID(FB515B));
    _INIT_TEST_VARS;

    /* TODO: implement _test_Sappend() */
    test_str = S_append(test_str, NULL);  /*null-test*/
    freeS(&test_str);

    RETURN(NIL);
} /* _test_Sappend */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_blank( void );                                         /*C*/

static void  _test_Sblank( void ) {                                        /*F*/
    GO                                                            (UID(F14E87));
    _INIT_TEST_VARS;
    {
        test_str = S_blank();
        _READ_TEST_VARS;

        /* capacity should == STR_INITIAL_CAPACITY */
        _assert(cap == STR_INITIAL_CAPACITY);

        _assert(len == 0);       /* length should be zero              */
        _assert(str != NULL);    /* shouldn't be NULL, but zero-length */
        _assert(IS_BLANK(str));  /* should be zero-length              */
        _assert(ext == NULL);    /* string extension should be NULL    */
        _assert(cnv == NULL);    /* conversion pointer should be NULL  */

        freeS(&test_str);
    }
    RETURN(NIL);
} /* _test_Sblank */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_copy( const str_t  source_ );                          /*C*/

static void  _test_Scopy( void ) {                                         /*F*/
    GO                                                            (UID(FB9A91));
    _INIT_TEST_VARS;

    test_str = S_copy(test_str);  /*null-test*/
    freeS(&test_str);

    {
        str_t  from = S_wchars(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        str_t  to   = S_copy(from);

        const size_t  from_len = _len(from);
        chars_t       from_cnv = _cnv(from);
        chars_t       from_str = _str(from);

        const size_t  to_cap   = _cap(to);
        const size_t  to_len   = _len(to);
        chars_t       to_cnv   = _cnv(to);
        chars_t       to_str   = _str(to);

        _assert(to_cap >= to_len);
        _assert(to_len == from_len);
        _assert(_equal(to_str, from_str));
        _assert(to_cnv == from_cnv);

        freeS(&from);
        freeS(&to);
    }
    RETURN(NIL);
} /* _test_Scopy */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_firstChars(                                            /*C*/
    chars_t       chars_,                                                  /*-*/
    const size_t  len_ );                                                  /*-*/

static void  _test_SfirstChars( void ) {                                   /*F*/
    GO                                                            (UID(F5D6CE));
    _INIT_TEST_VARS;

#define _TEST( INIT_STR_, INIT_LENGTH_, RESULT_CHECK_ )  \
    test_str = S_firstChars(INIT_STR_, INIT_LENGTH_);     \
    _check_str(test_str, RESULT_CHECK_);                 \
    freeS(&test_str);                                /*#*/

    _TEST(NULL,          0, _T(""));  /*null-test*/
    _TEST(NULL,        100, _T(""));  /*null-test*/
    _TEST(NULL,    1000000, _T(""));  /*null-test*/

    _TEST(_T(""),        0, _T(""));
    _TEST(_T("\0"),      0, _T(""));
    _TEST(_T("A"),       0, _T(""));
    _TEST(_T("ABC"),     0, _T(""));
    _TEST(_T("ABCDEF"),  0, _T(""));

    _TEST(NULL,          1, _T(""));
    _TEST(_T(""),        1, _T(""));
    _TEST(_T("\0"),      1, _T(""));
    _TEST(_T("A"),       1, _T("A"));
    _TEST(_T("ABC"),     1, _T("A"));
    _TEST(_T("ABCDEF"),  1, _T("A"));

    _TEST(NULL,          5, _T(""));
    _TEST(_T(""),        5, _T(""));
    _TEST(_T("\0"),      5, _T(""));
    _TEST(_T("A"),       5, _T("A"));
    _TEST(_T("ABC"),     5, _T("ABC"));
    _TEST(_T("ABCDEF"),  5, _T("ABCDE"));

    _TEST(NULL,         50, _T(""));
    _TEST(_T(""),       50, _T(""));
    _TEST(_T("\0"),     50, _T(""));
    _TEST(_T("A"),      50, _T("A"));
    _TEST(_T("ABC"),    50, _T("ABC"));
    _TEST(_T("ABCDEF"), 50, _T("ABCDEF"));

#undef _TEST

    RETURN(NIL);
} /* _test_SfirstChars */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_formatNumeric(                                         /*C*/
    chars_t       string_,                                                 /*-*/
    const int     decimal_places_,                                         /*-*/
    const int     group_digits_1_,                                         /*-*/
    const int     group_digits_2_,                                         /*-*/
    const int     group_digits_3_,                                         /*-*/
    const char_t  decimal_point_char_,                                     /*-*/
    const char_t  group_delimiter_char_ );                                 /*-*/

static void  _test_SformatNumeric( void ) {                                /*F*/
    GO                                                            (UID(F55B11));
    _INIT_TEST_VARS;

    test_str = S_formatNumeric(NULL, 0, 0, 0, 0, '\0', '\0');
    freeS(&test_str);

    test_str = S_formatNumeric(_T("123"), 0, 0, 0, 0, '.', ',');
    _check_str(test_str, _T("123"));
    freeS(&test_str);

    test_str = S_formatNumeric(_T("123"), 0, 3, 3, 3, '.', ',');
    _check_str(test_str, _T("123"));
    freeS(&test_str);

    test_str = S_formatNumeric(_T("1234"), 0, 3, 3, 3, '.', ',');
    _check_str(test_str, _T("1,234"));
    freeS(&test_str);

    test_str = S_formatNumeric(_T("1234"), 1, 3, 3, 3, '.', ',');
    _check_str(test_str, _T("1,234.0"));
    freeS(&test_str);

    test_str = S_formatNumeric(_T("1234567890"), 1, 1, 2, 3, '.', ',');
    _check_str(test_str, _T("1,234,567,89,0.0"));
    freeS(&test_str);

    test_str = S_formatNumeric(_T("1234567890"), 20, 1, 2, 3, ',', ',');
    _check_str(test_str, _T("1,234,567,89,0,00000000000000000000"));
    freeS(&test_str);

    RETURN(NIL);
} /* _test_SformatNumeric */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_bchars( const char*  source_ );                        /*C*/

static void  _test_Sbchars( void ) {                                       /*F*/
    GO                                                            (UID(FA204D));
    _INIT_TEST_VARS;

#define _TEST( INIT_STR_, CHECK_STR_ )   \
    test_str = S_bchars(INIT_STR_);      \
    _check_str(test_str, CHECK_STR_);    \
    freeS(&test_str)                 /*#*/

    _TEST(NULL,     _T(""));  /*null-test*/
    _TEST("",       _T(""));
    _TEST("\0",     _T(""));
    _TEST(" ",      _T(" "));
    _TEST("\t",     _T("\t"));
    _TEST("A",      _T("A"));
    _TEST("ABC",    _T("ABC"));
    _TEST("ABCDEF", _T("ABCDEF"));

#undef _TEST

    RETURN(NIL);
} /* _test_Sbchars */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_bsubstr(                                               /*C*/
    const char*   source_,                                                 /*-*/
    const size_t  offset_,                                                 /*-*/
    const size_t  count_ );                                                /*-*/

static void  _test_Sbsubstr( void ) {                                      /*F*/
    GO                                                            (UID(F59371));
    _INIT_TEST_VARS;

    test_str = lx_S_bsubstr(NULL, 0, 0);  /*null-test*/
    freeS(&test_str);

    /* zero-length strings */
    test_str = S_bsubstr(NULL, 200, SIZE_MAX);
    _READ_TEST_VARS;
    _assert(cap == STR_INITIAL_CAPACITY);
    _assert(len == 0);
    _assert(IS_BLANK(str));
    _assert(cnv == NULL);
    freeS(&test_str);

    test_str = S_bsubstr("", 200, SIZE_MAX);
    _READ_TEST_VARS;
    _assert(cap == STR_INITIAL_CAPACITY);
    _assert(len == 0);
    _assert(IS_BLANK(str));
    _assert(cnv == NULL);
    freeS(&test_str);

    test_str = S_bsubstr("\0XYZ", 200, SIZE_MAX);
    _READ_TEST_VARS;
    _assert(cap == STR_INITIAL_CAPACITY);
    _assert(len == 0);
    _assert(IS_BLANK(str));
    _assert(cnv == NULL);
    freeS(&test_str);

    /* 1-character string */
    test_str = S_bsubstr("abcdefghijklmnopqrstuvwxyz", 200, 1);
    _READ_TEST_VARS;
    _assert(cap == STR_INITIAL_CAPACITY);
    _assert(len == 0);
    _assert(_equal(str, _T("")));
    _assert(cnv == NULL);
    freeS(&test_str);

    /* multi-character string */
    test_str = S_bsubstr("abcdefghijklmnopqrstuvwxyz", 0, SIZE_MAX);
    _READ_TEST_VARS;
    _assert(cap == STR_INITIAL_CAPACITY);
    _assert(len == 12);
    _assert(_equal(str, _T("abcdefghijkl")));
    _assert(cnv == NULL);
    freeS(&test_str);

    RETURN(NIL);
} /* _test_Sbsubstr */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_newT( new_chars_t  text_ );                            /*C*/

static void  _test_SnewT( void ) {                                         /*F*/
    GO                                                            (UID(F38D3C));
    _INIT_TEST_VARS;
    test_str = S_newT(NULL);  /*null-test*/
    freeS(&test_str);
    RETURN(NIL);
} /* _test_SnewT */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_wchars( const wchar_t*  source_ );                     /*C*/

static void  _test_Swchars( void ) {                                       /*F*/
    GO                                                            (UID(F22AFD));
    _INIT_TEST_VARS;

    test_str = S_wchars(NULL);  /*null-test*/
    _check_str(test_str, _T(""));
    freeS(&test_str);

    test_str = S_wchars(NULL);
    _check_str(test_str, _T(""));
    freeS(&test_str);

    test_str = S_wchars(L"");
    _check_str(test_str, _T(""));
    freeS(&test_str);

    test_str = S_wchars(L"\0");
    _check_str(test_str, _T(""));
    freeS(&test_str);

    test_str = S_wchars(L" ");
    _check_str(test_str, _T(" "));
    freeS(&test_str);

    test_str = S_wchars(L"\t");
    _check_str(test_str, _T("\t"));
    freeS(&test_str);

    test_str = S_wchars(L"A");
    _check_str(test_str, _T("A"));
    freeS(&test_str);

    test_str = S_wchars(L"ABC");
    _check_str(test_str, _T("ABC"));
    freeS(&test_str);

    test_str = S_wchars(L"ABCDEF");
    _check_str(test_str, _T("ABCDEF"));
    freeS(&test_str);

    RETURN(NIL);
} /* _test_Swchars */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_wchars_n(                                              /*C*/
    const wchar_t*  source_,                                               /*-*/
    const size_t    source_len_,                                           /*-*/
    const size_t    offset_,                                               /*-*/
    const size_t    substr_len_ );                                         /*-*/

static void  _test_Swchars_n( void ) {                                     /*F*/
    GO                                                            (UID(FBE819));
    _INIT_TEST_VARS;

    test_str = S_wchars_n(NULL, 0, 0, 0);  /*null-test*/
    freeS(&test_str);

    /* zero-length strings */
    test_str = S_wchars_n(NULL, 100, 200, SIZE_MAX);
    _READ_TEST_VARS;
    _assert(cap == STR_INITIAL_CAPACITY);
    _assert(len == 0);
    _assert(IS_BLANK(_str(test_str)));
    _assert(cnv == NULL);
    freeS(&test_str);

    test_str = S_wchars_n(L"", 100, 200, SIZE_MAX);
    _READ_TEST_VARS;
    _assert(cap == STR_INITIAL_CAPACITY);
    _assert(len == 0);
    _assert(IS_BLANK(_str(test_str)));
    _assert(cnv == NULL);
    freeS(&test_str);

    test_str = S_wchars_n(L"\0XYZ", 100, 200, SIZE_MAX);
    _READ_TEST_VARS;
    _assert(cap == STR_INITIAL_CAPACITY);
    _assert(len == 0);
    _assert(IS_BLANK(_str(test_str)));
    _assert(cnv == NULL);
    freeS(&test_str);

    /* 1-character string */
    test_str = S_wchars_n(L"abcdefghijklmnopqrstuvwxyz", 12, 0, SIZE_MAX);
    _READ_TEST_VARS;
    _assert(cap == STR_INITIAL_CAPACITY);
    _assert(len == 12);
    _assert(_equal(_str(test_str), _T("abcdefghijkl")));
    _assert(cnv == NULL);
    freeS(&test_str);

    RETURN(NIL);
} /* _test_Swchars_n */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_repeat(                                                /*C*/
    chars_t    string_,     /* String to be repeated               */      /*-*/
    const int  count_,      /* Max. no. of times string can repeat */      /*-*/
    const int  max_len_ );  /* Maximum len. of returned string     */      /*-*/

static void  _test_Srepeat( void ) {                                       /*F*/
    GO                                                            (UID(F8355C));
    _INIT_TEST_VARS;

#define _TEST( STRING_, COUNT_, MAX_LEN_, RESULT_CHECK_ )  \
    test_str = S_repeat(STRING_, COUNT_, MAX_LEN_);         \
    _check_str(test_str, RESULT_CHECK_);                   \
    freeS(&test_str);                                  /*#*/

    _TEST(NULL,  0, 0, _T(""));  /*null-test*/
    _TEST(NULL,  0, 1, _T(""));
    _TEST(NULL,  1, 1, _T(""));
    _TEST(NULL,  5, 1, _T(""));
    _TEST(NULL, 10, 1, _T(""));
    /* _TEST(NULL,  -10, 1, _T("")); */

    _TEST(NULL, 0, 1000, _T(""));
    _TEST(NULL, 1, 1000, _T(""));
    _TEST(NULL, 5, 1000, _T(""));
    _TEST(NULL, 10, 1000, _T(""));
    /* _TEST(NULL,  -10, 1000, _T("")); */

    _TEST(_T(""), 0, 1, _T(""));
    _TEST(_T(""), 1, 1, _T(""));
    _TEST(_T(""), 5, 1, _T(""));
    _TEST(_T(""), 10, 1, _T(""));
    /* _TEST(_T(""), -10, 1, _T("")); */

    _TEST(_T(""), 0, 1000, _T(""));
    _TEST(_T(""), 1, 1000, _T(""));
    _TEST(_T(""), 5, 1000, _T(""));
    _TEST(_T(""), 10, 1000, _T(""));
    /* _TEST(_T(""), -10, 1000, _T("")); */

    _TEST(_T("A"), 0, 1000, _T(""));
    _TEST(_T("A"), 1, 1000, _T("A"));
    _TEST(_T("A"), 5, 1000, _T("AAAAA"));
    _TEST(_T("A"), 10, 1000, _T("AAAAAAAAAA"));
    /* _TEST(_T("A"), -10, 1000, _T("")); */

    _TEST(_T("A"), 0, 1, _T(""));
    _TEST(_T("A"), 1, 1, _T("A"));
    _TEST(_T("A"), 5, 1, _T("A"));
    _TEST(_T("A"), 10, 1, _T("A"));
    /* _TEST(_T("A"), -10, 1, _T("")); */

    _TEST(_T("ABC"), 0, 1000, _T(""));
    _TEST(_T("ABC"), 1, 1000, _T("ABC"));
    _TEST(_T("ABC"), 5, 1000, _T("ABCABCABCABCABC"));
    _TEST(_T("ABC"), 10, 1000, _T("ABCABCABCABCABCABCABCABCABCABC"));
    /* _TEST(_T("ABC"), -10, 1000, _T("")); */

    _TEST(_T("ABC"), 0, 1, _T(""));
    _TEST(_T("ABC"), 1, 1, _T("A"));
    _TEST(_T("ABC"), 5, 1, _T("A"));
    _TEST(_T("ABC"), 10, 1, _T("A"));
    /* _TEST(_T("ABC"), -10, 1, _T("")); */

#undef _TEST

    RETURN(NIL);
} /* _test_Srepeat */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_reserve( const size_t  char_capacity_ );               /*C*/

static void  _test_Sreserve( void ) {                                      /*F*/
    GO                                                            (UID(FA1194));
    _INIT_TEST_VARS;

    test_str = S_reserve(0);  /*null-test*/
    freeS(&test_str);

    /* empty string */
    test_str = S_reserve(0);
    cap = _cap(test_str);
    _assert(cap == STR_INITIAL_CAPACITY);
    len = _len(test_str);
    _assert(len == 0);
    str = _str(test_str);
    _assert(IS_BLANK(str));
    cnv = _cnv(test_str);
    _assert(cnv == NULL);
    freeS(&test_str);

    /* 1-char string */
    test_str = S_reserve(1);
    cap = _cap(test_str);
    _assert(cap == STR_INITIAL_CAPACITY);
    len = _len(test_str);
    _assert(len == 0);
    str = _str(test_str);
    _assert(IS_BLANK(str));
    cnv = _cnv(test_str);
    _assert(cnv == NULL);
    freeS(&test_str);

    /* 1mb string */
    test_str = S_reserve(1024 * 1024);
    cap = _cap(test_str);
    _assert(cap == 1024 * 1024);
    len = _len(test_str);
    _assert(len == 0);
    str = _str(test_str);
    _assert(IS_BLANK(str));
    cnv = _cnv(test_str);
    _assert(cnv == NULL);
    freeS(&test_str);

    RETURN(NIL);
} /* _test_Sreserve */


/* -------------------------------------------------------------------------- */


PUBLIC void  clearInS( str_t*  object_ );                                  /*M*/

static void  _test_clearInS( void ) {                                      /*F*/
    GO                                                            (UID(F5B53A));
    _INIT_TEST_VARS;

    clearInS(&test_str);  /*null-test*/
    _READ_TEST_VARS;
    _assert(cap > 0);
    _assert(len == 0);
    _assert(str != NULL);
    _assert(ext == NULL);
    _assert(cnv == NULL);
    freeS(&test_str);

    RETURN(NIL);
} /* _test_clearInS */


/* -------------------------------------------------------------------------- */


PUBLIC void  closeBufferS( str_t*  object_ );                              /*M*/

static void  _test_closeBufferS( void ) {                                  /*F*/
    GO                                                            (UID(F35097));
    _INIT_TEST_VARS;

    closeBufferS(&test_str);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_closeBufferS() */

    RETURN(NIL);
} /* _test_closeBufferS */


/* -------------------------------------------------------------------------- */


PUBLIC void  copyFromBufferS(                                              /*M*/
    str_t*        object_,                                                 /*-*/
    chars_t       buffer_,                                                 /*-*/
    const size_t  buffer_len_ );                                           /*-*/

static void  _test_copyFromBufferS( void ) {                               /*F*/
    GO                                                            (UID(F6F2A5));
    _INIT_TEST_VARS;

    copyFromBufferS(&test_str, NULL, 0);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_copyFromBufferS() */

    RETURN(NIL);
} /* _test_copyFromBufferS */


/* -------------------------------------------------------------------------- */


PUBLIC void  copyToBufferS(                                                /*M*/
    const str_t   object_,                                                 /*-*/
    char_t*       buffer_,                                                 /*-*/
    const size_t  buffer_len_ );                                           /*-*/

static void  _test_copyToBufferS( void ) {                                 /*F*/
    GO                                                            (UID(F0DE75));
    _INIT_TEST_VARS;

    copyToBufferS(test_str, NULL, 1);

    /* TODO: implement _test_copyToBufferS() */

    RETURN(NIL);
} /* _test_copyToBufferS */


/* -------------------------------------------------------------------------- */


PUBLIC void  freeConversionBufferS( str_t*  object_ );                     /*M*/

static void  _test_freeConversionBufferS( void ) {                         /*F*/
    GO                                                            (UID(F6CE27));
    _INIT_TEST_VARS;

    freeConversionBufferS(&test_str);  /*null-test*/
    /* TODO: implement _test_freeConversionBufferS() */

    RETURN(NIL);
} /* _test_freeConversionBufferS */


/* -------------------------------------------------------------------------- */


PUBLIC void  setCopyAnsiS(                                                 /*M*/
    str_t*       object_,                                                  /*-*/
    const char*  string_ );                                                /*-*/

static void  _test_setCopyAnsiS( void ) {                                  /*F*/
    GO                                                            (UID(F2C655));
    _INIT_TEST_VARS;

    setCopyAnsiS(&test_str, NULL);  /*null-test*/
    freeS(&test_str);
    /* TODO: implement _test_setCopyAnsiS() */

    RETURN(NIL);
} /* _test_setCopyAnsiS */


/* -------------------------------------------------------------------------- */


PUBLIC void  setCopyCharS(                                                 /*M*/
    str_t*        object_,                                                 /*-*/
    const char_t  char_ );                                                 /*-*/

static void  _test_setCopyCharS( void ) {                                  /*F*/
    GO                                                            (UID(F9142F));
    _INIT_TEST_VARS;

    setCopyCharS(&test_str, '\0');  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_setCopyCharS() */
    RETURN(NIL);
} /* _test_setCopyCharS */


/* -------------------------------------------------------------------------- */


PUBLIC void  setCopyWideS(                                                 /*M*/
    str_t*          object_,                                               /*-*/
    const wchar_t*  string_ );                                             /*-*/

static void  _test_setCopyWideS( void ) {                                  /*F*/
    GO                                                            (UID(F5E178));
    _INIT_TEST_VARS;

    /* TODO: fix SEGFAULT in _test_setCopyWideS() */
    /* setCopyWideS(&test_str, NULL);*/  /*null-test*/
    /* freeS(&test_str); */

    /* TODO: implement _test_setCopyWideS() */

    RETURN(NIL);
} /* _test_setCopyWideS */


/* -------------------------------------------------------------------------- */


PUBLIC void  addS(                                                         /*M*/
    str_t*       object_,                                                  /*-*/
    const str_t  source_ );                                                /*-*/

static void  _test_addS( void ) {                                          /*F*/
    GO                                                            (UID(FAD40A));
    _INIT_TEST_VARS;

    addS(&test_str, test_str);  /*null-test*/

    /* TODO: implement _test_addS() */
    RETURN(NIL);
} /* _test_addS */


/* -------------------------------------------------------------------------- */


PUBLIC void  addAS(                                                        /*M*/
    str_t*       object_,                                                  /*-*/
    const char*  string_ );                                                /*-*/

static void  _test_addAS( void ) {                                         /*F*/
    GO                                                            (UID(F940BB));
    _INIT_TEST_VARS;

    addAS(&test_str, NULL);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_addAS() */
    RETURN(NIL);
} /* _test_addAS */


/* -------------------------------------------------------------------------- */


PUBLIC void  addTS(                                                        /*M*/
    str_t* const   object_,                                                /*-*/
    chars_t const  string_ );                                              /*-*/

static void  _test_addTS( void ) {                                         /*F*/
    GO                                                            (UID(F940BB));
    _INIT_TEST_VARS;

    addTS(&test_str, NULL);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_addTS() */
    RETURN(NIL);
} /* _test_addTS */


/* -------------------------------------------------------------------------- */


PUBLIC void  addWS(                                                        /*M*/
    str_t*          object_,                                               /*-*/
    const wchar_t*  string_ );                                             /*-*/

static void  _test_addWS( void ) {                                         /*F*/
    GO                                                            (UID(FAE731));
    _INIT_TEST_VARS;

    addWS(&test_str, NULL);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_addWS() */
    RETURN(NIL);
} /* _test_addWS */


/* -------------------------------------------------------------------------- */


PUBLIC void  reserveInS(                                                   /*M*/
    str_t*        object_,                                                 /*-*/
    const size_t  char_capacity_ );                                        /*-*/

static void  _test_reserveInS( void ) {                                    /*F*/
    GO                                                            (UID(FD6805));
    _INIT_TEST_VARS;

    reserveInS(&test_str, 0);  /*null-test*/
    setInS(&test_str, A_TO_Z_X50);
    reserveInS(&test_str, STR_INITIAL_CAPACITY * 100);
    _check_str(test_str, A_TO_Z_X50);
    freeS(&test_str);

    /* TODO: implement _test_reserveInS() */
    RETURN(NIL);
} /* _test_reserveInS */


/* -------------------------------------------------------------------------- */


PUBLIC void  setInS(                                                       /*M*/
    str_t*   object_,                                                      /*-*/
    chars_t  string_ );                                                    /*-*/

static void  _test_setS( void ) {                                          /*F*/
    GO                                                            (UID(F41EE9));
    _INIT_TEST_VARS;

    setInS(&test_str, NULL);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_setS() */
    RETURN(NIL);
} /* _test_setS */


/* -------------------------------------------------------------------------- */


PUBLIC void  add3S(                                                        /*M*/
    str_t*        object_,                                                 /*-*/
    chars_t       string_,                                                 /*-*/
    const size_t  length_ );                                               /*-*/

static void  _test_add3S( void ) {                                         /*F*/
    GO                                                            (UID(F44BC2));
    _INIT_TEST_VARS;
    add3S(&test_str, NULL, 0);  /*null-test*/
    freeS(&test_str);
    /* TODO: implement _test_add3S() */
    RETURN(NIL);
} /* _test_add3S */


/* -------------------------------------------------------------------------- */


PUBLIC void  addCharS(                                                     /*M*/
    str_t*        object_,                                                 /*-*/
    const char_t  char_ );                                                 /*-*/

static void  _test_addCharS( void ) {                                      /*F*/
    GO                                                            (UID(FCDD7E));
    _INIT_TEST_VARS;

    addCharS(&test_str, '\0');  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_addCharS() */
    RETURN(NIL);
} /* _test_addCharS */


/* -------------------------------------------------------------------------- */


PUBLIC void  addIntS(                                                      /*M*/
    str_t*     object_,                                                    /*-*/
    const int  number_ );                                                  /*-*/

static void  _test_addIntS( void ) {                                       /*F*/
    GO                                                            (UID(FF5824));
    _INIT_TEST_VARS;

    addIntS(&test_str, 0);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_addIntS() */
    RETURN(NIL);
} /* _test_addIntS */


/* -------------------------------------------------------------------------- */


PUBLIC void  setCopyS(                                                     /*M*/
    str_t*       object_,                                                  /*-*/
    const str_t  string_ );                                                /*-*/

static void  _test_setCopyS( void ) {                                      /*F*/
    GO                                                            (UID(FFC959));
    _INIT_TEST_VARS;

    setCopyS(&test_str, test_str);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_setCopyS() */
    RETURN(NIL);
} /* _test_setCopyS */


/* -------------------------------------------------------------------------- */


PUBLIC void  decodeBase64InS( str_t*  object_ );                           /*M*/

static void  _test_decodeBase64InS( void ) {                               /*F*/
    GO                                                            (UID(F5EF86));
    _INIT_TEST_VARS;

    decodeBase64InS(&test_str);
    freeS(&test_str);

    /* TODO: implement _test_decodeBase64InS() */
    RETURN(NIL);
} /* _test_decodeBase64InS */


/* -------------------------------------------------------------------------- */


PUBLIC void  delimitNumberInS(                                             /*M*/
    str_t*        object_,                                                 /*-*/
    const size_t  decimal_places_,                                         /*-*/
    const size_t  digits_1_,                                               /*-*/
    const size_t  digits_2_,                                               /*-*/
    const size_t  digits_3_,                                               /*-*/
    const char_t  decimal_point_char_,                                     /*-*/
    const char_t  group_char_ );                                           /*-*/

static void  _test_delimitNumberInS( void ) {                              /*F*/
    GO                                                            (UID(FE69A3));
    _INIT_TEST_VARS;

    delimitNumberInS(&test_str, 0, 0, 0, 0, '\0', '\0');  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_delimitNumberInS() */
    RETURN(NIL);
} /* _test_delimitNumberInS */


/* -------------------------------------------------------------------------- */


PUBLIC void  encodeBase64InS( str_t*  object_ );                           /*M*/

static void  _test_encodeBase64InS( void ) {                               /*F*/
    GO                                                            (UID(F1B6E0));
    _INIT_TEST_VARS;

    encodeBase64InS(&test_str);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_encodeBase64InS() */
    RETURN(NIL);
} /* _test_encodeBase64InS */


/* -------------------------------------------------------------------------- */


#if defined LX_UNUSED_CODE
PUBLIC void  fillInS(                                                      /*M*/
    str_t*        object_,                                                 /*-*/
    const char_t  char_,                                                   /*-*/
    const size_t  length_,                                                 /*-*/
    const bool    align_to_end_,                                           /*-*/
    const bool    spillover_,                                              /*-*/
    const bool    clear_contents_ );                                       /*-*/

static void  _test_setFillS( void ) {                                      /*F*/
    GO                                                            (UID(FC8898));
    _INIT_TEST_VARS;

    fillInS(&test_str, '\0', 0, false, false, false);
    /*null-test*/

    freeS(&test_str);

    /* TODO: implement _test_setFillS() */
    RETURN(NIL);
} /* _test_setFillS */
#endif                                                        //# LX_UNUSED_CODE


/* -------------------------------------------------------------------------- */


PUBLIC void  firstInS(                                                     /*M*/
    str_t*        object_,                                                 /*-*/
    const size_t  length_ );                                               /*-*/

static void  _test_firstInS( void ) {                                      /*F*/
    GO                                                            (UID(FED158));
    _INIT_TEST_VARS;

    CLEAR(test_str);

    firstInS(&test_str, 0);  /*null-test*/

    setInS(&test_str, _T(""));
    firstInS(&test_str, 0);
    _assert(_equal(_str(test_str), _T("")));

    setInS(&test_str, _T("1234567890"));
    firstInS(&test_str, 0);
    _assert(_equal(_str(test_str), _T("")));

    setInS(&test_str, _T("1234567890"));
    firstInS(&test_str, 1);
    _assert(_equal(_str(test_str), _T("1")));

    setInS(&test_str, _T("1234567890"));
    firstInS(&test_str, 5);
    _assert(_equal(_str(test_str), _T("12345")));

    setInS(&test_str, _T("1234567890"));
    firstInS(&test_str, 10);
    _assert(_equal(_str(test_str), _T("1234567890")));

    setInS(&test_str, _T("1234567890"));
    firstInS(&test_str, 20);
    _assert(_equal(_str(test_str), _T("1234567890")));

    setInS(&test_str, NULL);
    firstInS(&test_str, 0);
    _assert(_equal(_str(test_str), _T("")));

    freeS(&test_str);

    RETURN(NIL);
} /* _test_firstInS */


/* -------------------------------------------------------------------------- */


PUBLIC void  formatInS(                                                    /*M*/
    str_t*   object_,                                                      /*-*/
    chars_t  format_,                                                      /*-*/
    chars_t  str_0_,                                                       /*-*/
    chars_t  str_1_,                                                       /*-*/
    chars_t  str_2_,                                                       /*-*/
    chars_t  str_3_,                                                       /*-*/
    chars_t  str_4_,                                                       /*-*/
    chars_t  str_5_,                                                       /*-*/
    chars_t  str_6_,                                                       /*-*/
    chars_t  str_7_,                                                       /*-*/
    chars_t  str_8_,                                                       /*-*/
    chars_t  str_9_ );                                                     /*-*/

static void  _test_formatInS( void ) {                                     /*F*/
    GO                                                            (UID(F58ABF));
    _INIT_TEST_VARS;

    formatInS(&test_str, NULL, NULL, NULL, NULL, NULL,
              NULL, NULL, NULL, NULL, NULL, NULL);  /*null-test*/

    freeS(&test_str);

    /* TODO: implement _test_formatInS() */
    RETURN(NIL);
} /* _test_formatInS */

/* -------------------------------------------------------------------------- */

PUBLIC void  formatNumericInS(                                             /*M*/
    str_t*        object_,                                                 /*-*/
    const int     decimal_places_,                                         /*-*/
    const int     group_digits_1_,                                         /*-*/
    const int     group_digits_2_,                                         /*-*/
    const int     group_digits_3_,                                         /*-*/
    const char_t  decimal_point_char_,                                     /*-*/
    const char_t  group_delimiter_char_ );                                 /*-*/

static void  _test_formatNumericInS( void ) {                              /*F*/
    GO                                                            (UID(F9FD4D));
    _INIT_TEST_VARS;
    {
        struct _test_t {
            chars_t  init;                                         /* _test_t */
            int      decimal_places_;                              /* _test_t */
            int      group_digits_1_;                              /* _test_t */
            int      group_digits_2_;                              /* _test_t */
            int      group_digits_3_;                              /* _test_t */
            char_t   decimal_point_char_;                          /* _test_t */
            char_t   group_delimiter_char_;                        /* _test_t */
            chars_t  check;                                        /* _test_t */
        }
        test[] = {

            /* zero-length string should return 0 with specified d. p. */
            {
                _T(""),                            0, 3, 3, 3, _T('.'), _T(','),
                _T("0")
            },
            {
                _T(""),                            1, 3, 3, 3, _T('.'), _T(','),
                _T("0.0")
            },
            {
                _T(""),                            2, 3, 3, 3, _T('.'), _T(','),
                _T("0.00")
            },
            {
                _T(""),                            3, 3, 3, 3, _T('.'), _T(','),
                _T("0.000")
            },
            {
                _T(""),                            4, 3, 3, 3, _T('.'), _T(','),
                _T("0.0000")
            },

            /* blank (whitespace) string should return 0 with specified d. p. */
            {
                _T(" \r\t\b\n"),                   0, 3, 3, 3, _T('.'), _T(','),
                _T("0")
            },
            {
                _T(" \r\t\b\n"),                   1, 3, 3, 3, _T('.'), _T(','),
                _T("0.0")
            },
            {
                _T(" \r\t\b\n"),                   2, 3, 3, 3, _T('.'), _T(','),
                _T("0.00")
            },
            {
                _T(" \r\t\b\n"),                   3, 3, 3, 3, _T('.'), _T(','),
                _T("0.000")
            },
            {
                _T(" \r\t\b\n"),                   4, 3, 3, 3, _T('.'), _T(','),
                _T("0.0000")
            },

            /* test regular currency format with positive numbers */
            {
                _T("1."),                          2, 3, 3, 3, _T('.'), _T(','),
                _T("1.00")
            },
            {
                _T("1.2"),                         2, 3, 3, 3, _T('.'), _T(','),
                _T("1.20")
            },
            {
                _T("1.23"),                        2, 3, 3, 3, _T('.'), _T(','),
                _T("1.23")
            },
            {
                _T("12.34"),                       2, 3, 3, 3, _T('.'), _T(','),
                _T("12.34")
            },
            {
                _T("123.45"),                      2, 3, 3, 3, _T('.'), _T(','),
                _T("123.45")
            },
            {
                _T("1234.56"),                     2, 3, 3, 3, _T('.'), _T(','),
                _T("1,234.56")
            },
            {
                _T("12345.67"),                    2, 3, 3, 3, _T('.'), _T(','),
                _T("12,345.67")
            },
            {
                _T("123456.78"),                   2, 3, 3, 3, _T('.'), _T(','),
                _T("123,456.78")
            },
            {
                _T("1234567.89"),                  2, 3, 3, 3, _T('.'), _T(','),
                _T("1,234,567.89")
            },
            {
                _T("12345678.90"),                 2, 3, 3, 3, _T('.'), _T(','),
                _T("12,345,678.90")
            },
            {
                _T("123456789.01"),                2, 3, 3, 3, _T('.'), _T(','),
                _T("123,456,789.01")
            },
            {
                _T("1234567890.12"),               2, 3, 3, 3, _T('.'), _T(','),
                _T("1,234,567,890.12")
            },

            /* test regular currency format with negative numbers */
            {
                _T("-1."),                         2, 3, 3, 3, _T('.'), _T(','),
                _T("-1.00")
            },
            {
                _T("-1.2"),                        2, 3, 3, 3, _T('.'), _T(','),
                _T("-1.20")
            },
            {
                _T("-1.23"),                       2, 3, 3, 3, _T('.'), _T(','),
                _T("-1.23")
            },
            {
                _T("-12.34"),                      2, 3, 3, 3, _T('.'), _T(','),
                _T("-12.34")
            },
            {
                _T("-123.45"),                     2, 3, 3, 3, _T('.'), _T(','),
                _T("-123.45")
            },
            {
                _T("-1234.56"),                    2, 3, 3, 3, _T('.'), _T(','),
                _T("-1,234.56")
            },
            {
                _T("-12345.67"),                   2, 3, 3, 3, _T('.'), _T(','),
                _T("-12,345.67")
            },
            {
                _T("-123456.78"),                  2, 3, 3, 3, _T('.'), _T(','),
                _T("-123,456.78")
            },
            {
                _T("-1234567.89"),                 2, 3, 3, 3, _T('.'), _T(','),
                _T("-1,234,567.89")
            },
            {
                _T("-12345678.90"),                2, 3, 3, 3, _T('.'), _T(','),
                _T("-12,345,678.90")
            },
            {
                _T("-123456789.01"),               2, 3, 3, 3, _T('.'), _T(','),
                _T("-123,456,789.01")
            },
            {
                _T("-1234567890.12"),              2, 3, 3, 3, _T('.'), _T(','),
                _T("-1,234,567,890.12")
            },

            {
                /* test groupings */
                _T("123456"),                      2, 0, 0, 0, _T('.'), _T(','),
                _T("123456.00")
            },

#if 000 /* TODO: _Str_setFormatNumeric() fails a test */
            {
                _T("123456"),                      2, 0, 0, 1, _T('.'), _T(','),
                _T("12345,6.00")
            },
#endif

            {
                _T("123456"),                      2, 1, 0, 0, _T('.'), _T(','),
                _T("12345,6.00")
            },
            {
                _T("123456"),                      2, 1, 2, 0, _T('.'), _T(','),
                _T("123,45,6.00")
            },

            /* test_str different symbols for decimal place, etc.    */
            /* test_str invalid parameters with negative values      */
            /* test_str int values much longer than length of string */

            { NULL, 0, 0, 0, 0, '\0', '\0', NULL }  /* exit */
        };

        int  i = 0;
        while (test[i].init != NULL) {
            chars_t       init                  = test[i].init;
            const int     decimal_places_       = test[i].decimal_places_;
            const int     group_digits_1_       = test[i].group_digits_1_;
            const int     group_digits_2_       = test[i].group_digits_2_;
            const int     group_digits_3_       = test[i].group_digits_3_;
            const char_t  decimal_point_char_   = test[i].decimal_point_char_;
            const char_t  group_delimiter_char_ = test[i].group_delimiter_char_;
            chars_t       check                 = test[i].check;

            setInS(&test_str, init);

            formatNumericInS(
                &test_str,  /* object_ */
                decimal_places_,
                group_digits_1_,
                group_digits_2_,
                group_digits_3_,
                decimal_point_char_,
                group_delimiter_char_);

            _assert(_equal(_str(test_str), check));
            freeS(&test_str);
            i++;
        }
    }
    RETURN(NIL);
} /* _test_formatInS */


/* -------------------------------------------------------------------------- */


PUBLIC void  lastInS(                                                      /*M*/
    str_t*        object_,                                                 /*-*/
    const size_t  length_ );                                               /*-*/

static void  _test_setLastS( void ) {                                      /*F*/
    GO                                                            (UID(F88FB9));
    _INIT_TEST_VARS;

    CLEAR(test_str);

    lastInS(&test_str, 0);  /*null-test*/

    setInS(&test_str, _T(""));
    lastInS(&test_str, 0);
    _assert(_equal(_str(test_str), _T("")));

    setInS(&test_str, _T("1234567890"));
    lastInS(&test_str, 0);
    _assert(_equal(_str(test_str), _T("")));

    setInS(&test_str, _T("1234567890"));
    lastInS(&test_str, 1);
    _assert(_equal(_str(test_str), _T("0")));

    setInS(&test_str, _T("1234567890"));
    lastInS(&test_str, 5);
    _assert(_equal(_str(test_str), _T("67890")));

    setInS(&test_str, _T("1234567890"));
    lastInS(&test_str, 10);
    _assert(_equal(_str(test_str), _T("1234567890")));

    setInS(&test_str, _T("1234567890"));
    lastInS(&test_str, 20);
    _assert(_equal(_str(test_str), _T("1234567890")));

    setInS(&test_str, NULL);
    lastInS(&test_str, 0);
    _assert(_equal(_str(test_str), _T("")));

    freeS(&test_str);

    RETURN(NIL);
} /* _test_setLastS */


/* -------------------------------------------------------------------------- */


PUBLIC void  tolowerInS( str_t*  object_ );                                /*M*/

static void  _test_tolowerInS( void ) {                                    /*F*/
    GO                                                            (UID(FF073F));
    _INIT_TEST_VARS;

    tolowerInS(&test_str);  /*null-test*/
    freeS(&test_str);

    CLEAR(test_str);

    setInS(&test_str, _T(""));
    tolowerInS(&test_str);
    _assert(_equal(_str(test_str), _T("")));

    setInS(&test_str, _T(" "));
    tolowerInS(&test_str);
    _assert(_equal(_str(test_str), _T(" ")));

    setInS(&test_str, NULL);
    tolowerInS(&test_str);
    _assert(_equal(_str(test_str), _T("")));

    setInS(&test_str, _T("a"));
    tolowerInS(&test_str);
    _assert(_equal(_str(test_str), _T("a")));

    setInS(&test_str, _T("abc"));
    tolowerInS(&test_str);
    _assert(_equal(_str(test_str), _T("abc")));

    setInS(&test_str, _T("A"));
    tolowerInS(&test_str);
    _assert(_equal(_str(test_str), _T("a")));

    setInS(&test_str, _T("ABC"));
    tolowerInS(&test_str);
    _assert(_equal(_str(test_str), _T("abc")));

    setInS(&test_str, _T("Abc"));
    tolowerInS(&test_str);
    _assert(_equal(_str(test_str), _T("abc")));

    setInS(&test_str, _T("Abc123"));
    tolowerInS(&test_str);
    _assert(_equal(_str(test_str), _T("abc123")));

    freeS(&test_str);

    RETURN(NIL);
} /* _test_tolowerInS */


/* -------------------------------------------------------------------------- */


PUBLIC void  removeInS(                                                    /*M*/
    str_t*        object_,                                                 /*-*/
    const size_t  position_,                                               /*-*/
    const size_t  char_count_ );                                           /*-*/

static void  _test_removeInS( void ) {                                     /*F*/
    GO                                                            (UID(FFF38A));
    _INIT_TEST_VARS;

    removeInS(&test_str, 0, 0);  /*null-test*/
    freeS(&test_str);

    CLEAR(test_str);

    setInS(&test_str, _T("-1-1"));
    removeInS(&test_str, 0, 2);
    _assert(_equal(_str(test_str), _T("-1")));

    setInS(&test_str, _T("-1.00-1"));
    removeInS(&test_str, 0, 5);
    _assert(_equal(_str(test_str), _T("-1")));

    setInS(&test_str, _T("Abc123"));
    removeInS(&test_str, 0, 1);
    _assert(_equal(_str(test_str), _T("bc123")));

    setInS(&test_str, _T("Abc123"));
    removeInS(&test_str, 0, 6);
    _assert(_equal(_str(test_str), _T("")));

    setInS(&test_str, _T("Abc123"));
    removeInS(&test_str, 3, 3);
    _assert(_equal(_str(test_str), _T("Abc")));

    setInS(&test_str, _T("Abc123"));
    removeInS(&test_str, 5, 1);
    _assert(_equal(_str(test_str), _T("Abc12")));

    setInS(&test_str, _T("Abc123"));
    removeInS(&test_str, 7, 100);
    _assert(_equal(_str(test_str), _T("Abc123")));

    setInS(&test_str, _T("Abc123"));
    removeInS(&test_str, 0, 100);
    _assert(_equal(_str(test_str), _T("")));

    freeS(&test_str);

    RETURN(NIL);
} /* _test_removeInS */


/* -------------------------------------------------------------------------- */


PUBLIC void  removeEndInS(                                                 /*M*/
    str_t*        object_,                                                 /*-*/
    const size_t  char_count_ );                                           /*-*/

static void  _test_setRemoveEndS( void ) {                                 /*F*/
    GO                                                            (UID(FC2450));
    _INIT_TEST_VARS;

    removeEndInS(&test_str, 0);  /*null-test*/
    freeS(&test_str);

    CLEAR(test_str);

    setInS(&test_str, _T("Abc123"));
    removeEndInS(&test_str, 0);
    _assert(_equal(_str(test_str), _T("Abc123")));

    setInS(&test_str, _T("Abc123"));
    removeEndInS(&test_str, 1);
    _assert(_equal(_str(test_str), _T("Abc12")));

    setInS(&test_str, _T("Abc123"));
    removeEndInS(&test_str, 2);
    _assert(_equal(_str(test_str), _T("Abc1")));

    setInS(&test_str, _T("Abc123"));
    removeEndInS(&test_str, 3);
    _assert(_equal(_str(test_str), _T("Abc")));

    setInS(&test_str, _T("Abc123"));
    removeEndInS(&test_str, 7);
    _assert(_equal(_str(test_str), _T("")));

    setInS(&test_str, _T("Abc123"));
    removeEndInS(&test_str, 6);
    _assert(_equal(_str(test_str), _T("")));

    freeS(&test_str);

    RETURN(NIL);
} /* _test_setRemoveEndS */

/* -------------------------------------------------------------------------- */

PUBLIC void  setReplaceS(                                                  /*M*/
    str_t*        object_,                                                 /*-*/
    chars_t       find_str_,                                               /*-*/
    chars_t       replace_str_,                                            /*-*/
    const bool    ignore_case_,                                            /*-*/
    const size_t  find_len_,                                               /*-*/
    const size_t  replace_len_ );                                          /*-*/

static void  _test_setReplaceS( void ) {                                   /*F*/
    GO                                                            (UID(F29C59));
    _INIT_TEST_VARS;

    setReplaceS(&test_str, NULL, NULL, IGNORE_CASE, 0, 0);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_setReplaceS() */
    RETURN(NIL);
} /* _test_setReplaceS */


/* -------------------------------------------------------------------------- */


PUBLIC void  reverseInS( str_t*  object_ );                                /*M*/

static void  _test_reverseInS( void ) {                                    /*F*/
    GO                                                            (UID(FE3EDD));
    _INIT_TEST_VARS;

    reverseInS(&test_str);  /*null-test*/

#define _TEST( BEFORE_, AFTER_ )              \
    setInS(&test_str, BEFORE_);                 \
    reverseInS(&test_str);                   \
    _assert(_equal(_str(test_str), AFTER_));  \
    freeS(&test_str)                      /*#*/

    _TEST(NULL,          _T(""));  /*null-test*/
    _TEST(_T(""),        _T(""));
    _TEST(_T(" "),       _T(" "));
    _TEST(_T("12"),      _T("21"));
    _TEST(_T("123"),     _T("321"));
    _TEST(_T("1234567"), _T("7654321"));
    _TEST(_T("a"),       _T("a"));

#undef _TEST

    RETURN(NIL);
} /* _test_reverseInS */


/* -------------------------------------------------------------------------- */


PUBLIC void  sortListInS(                                                  /*M*/
    str_t*      object_,                                                   /*-*/
    chars_t     delimiter_,                                                /*-*/
    const bool  descending_,                                               /*-*/
    const bool  unique_ );                                                 /*-*/

static void  _test_setSortListS( void ) {                                  /*F*/
    GO                                                            (UID(FF3348));
    _INIT_TEST_VARS;

    sortListInS(&test_str, NULL, false, false);  /*null-test*/

#define _TEST( INITIAL_, DELIMITER_, DESCENDING_, UNIQUE_, FINAL_ )  \
    setInS(&test_str, INITIAL_);                                       \
    sortListInS(&test_str, DELIMITER_, DESCENDING_, UNIQUE_);       \
    _assert(_equal(_str(test_str), FINAL_));                     /*#*/

    /*    INITIAL  DELIM.    DESC.  UNIQUE       */
    _TEST(_T(""), _T("  "), false, false, _T(""));
    _TEST(_T(""), _T("  "), true,  false, _T(""));
    _TEST(_T(""), _T(";"),  false, false, _T(""));
    _TEST(_T(""), _T(";"),  false, true,  _T(""));
    _TEST(_T(""), _T(";"),  true,  false, _T(""));
    _TEST(_T(""), _T(";"),  true,  true,  _T(""));

    _TEST(_T("q  w  e  r  t  y"), _T("  "), false, false,
          _T("e  q  r  t  w  y"));

    _TEST(_T("q  w  e  r  t  y"), _T("  "), true, false,
          _T("y  w  t  r  q  e"));

    _TEST(_T("q;w;e;r;t;y"), _T(";"), false, false,
          _T("e;q;r;t;w;y"));

    _TEST(_T("q;w;e;r;t;y"), _T(";"), true, false,
          _T("y;w;t;r;q;e"));

    _TEST(_T("q;w;e;r;t;y;q;w"), _T(";"), false, false,
          _T("e;q;q;r;t;w;w;y"));

    _TEST(_T("q;w;e;r;t;y;q;w"), _T(";"), false, true,
          _T("e;q;r;t;w;y"));

    _TEST(_T("q;w;e;r;t;y;q;w"), _T(";"), true, false,
          _T("y;w;w;t;r;q;q;e"));

    _TEST(_T("q;w;e;r;t;y;q;w"), _T(";"), true, true,
          _T("y;w;t;r;q;e"));

    _TEST(_T("q  ww  eee  r  tt  yyyy"), _T("  "), false, false,
          _T("eee  q  r  tt  ww  yyyy"));

    _TEST(_T("q  ww  eee  r  tt  yyyy"), _T("  "), true, false,
          _T("yyyy  ww  tt  r  q  eee"));

    _TEST(_T("q;ww;eee;r;tt;yyyy"), _T(";"), false, false,
          _T("eee;q;r;tt;ww;yyyy"));

    _TEST(_T("q;ww;eee;r;tt;yyyy"), _T(";"), true, false,
          _T("yyyy;ww;tt;r;q;eee"));

    _TEST(_T("q;ww;eee;r;tt;yyyy;q;ww"), _T(";"), false, false,
          _T("eee;q;q;r;tt;ww;ww;yyyy"));

    _TEST(_T("q;ww;eee;r;tt;yyyy;q;ww"), _T(";"), false, true,
          _T("eee;q;r;tt;ww;yyyy"));

    _TEST(_T("q;ww;eee;r;tt;yyyy;q;ww"), _T(";"), true, false,
          _T("yyyy;ww;ww;tt;r;q;q;eee"));

    _TEST(_T("q;ww;eee;r;tt;yyyy;q;ww"), _T(";"), true, true,
          _T("yyyy;ww;tt;r;q;eee"));

    _TEST(_T("zebra;lioness;lion;monkey;zebra;lion;ape;chimp;zebra"),
          _T(";"), false, false,
          _T("ape;chimp;lion;lion;lioness;monkey;zebra;zebra;zebra"));

    _TEST(_T("zebra;lioness;lion;monkey;zebra;lion;ape;chimp;zebra"),
          _T(";"), false, true,
          _T("ape;chimp;lion;lioness;monkey;zebra"));

    _TEST(_T("zebra;lioness;lion;monkey;zebra;lion;ape;chimp;zebra"),
          _T(";"), true, false,
          _T("zebra;zebra;zebra;monkey;lioness;lion;lion;chimp;ape"));

    _TEST(_T("zebra;lioness;lion;monkey;zebra;lion;ape;chimp;zebra"),
          _T(";"), true, true,
          _T("zebra;monkey;lioness;lion;chimp;ape"));

#undef _TEST

    freeS(&test_str);
    RETURN(NIL);
} /* _test_setSortListS */


/* -------------------------------------------------------------------------- */


PUBLIC void  spaceInS(                                                     /*M*/
    str_t*        object_,                                                 /*-*/
    const size_t  length_,                                                 /*-*/
    const bool    align_to_end_,                                           /*-*/
    const bool    spillover_ );                                            /*-*/

static void  _test_spaceInS( void ) {                                      /*F*/
    GO                                                            (UID(FC95FB));
    _INIT_TEST_VARS;

    spaceInS(&test_str, 0, false, false);  /*null-test*/

#define _TEST( INITIAL_, LENGTH_, ALIGN_TO_END_, SPILLOVER_, FINAL_ )  \
    setInS(&test_str, INITIAL_);                                         \
    spaceInS(&test_str, LENGTH_, ALIGN_TO_END_, SPILLOVER_);          \
    _assert(_equal(_str(test_str), FINAL_));                       /*#*/

    /*                    LEN  ALIGNEND  SPILLOUT  RESULT */
    _TEST(_T(""),          0, false, false, _T(""));
    _TEST(_T(""),          0, false, true,  _T(""));
    _TEST(_T(""),          1, false, false, _T(" "));
    _TEST(_T(""),         10, false, false, _T("          "));
    /* _TEST(_T("12345"),  3, false, false, _T("123")); FAIL */
    _TEST(_T("12345"),     3, false, true,  _T("12345"));
    /* _TEST(_T("12345"),  3, true,  false, _T("123")); FAIL */

    _TEST(_T("12345"),     3, true,  true,  _T("12345"));

    /* _TEST(_T("12345"),  5, false, false, _T("12345")); FAIL */
    /* _TEST(_T("12345"),  5, false, true,  _T("12345")); FAIL */
    /* _TEST(_T("12345"),  5, true,  false, _T("12345")); FAIL */

    /*  FAIL:
        _TEST(_T("12345"),     5, true,  true,  _T("12345"));
        _TEST(_T("12345"),    10, false, false, _T("12345     "));
        _TEST(_T("12345"),    10, false, true,  _T("12345     "));
        _TEST(_T("12345"),    10, true,  false, _T("     12345"));
        _TEST(_T("12345"),    10, true,  true,  _T("     12345"));
        _TEST(NULL,            0, false, false, _T(""));
        _TEST(NULL,            0, false, true,  _T(""));
        _TEST(NULL,            1, false, false, _T(" "));
        _TEST(NULL,           10, false, false, _T("          "));
    */

#undef _TEST

    freeS(&test_str);
    RETURN(NIL);
} /* _test_spaceInS */


/* -------------------------------------------------------------------------- */


PUBLIC void  totitleInS( str_t*  object_ );                                /*M*/

static void  _test_totitleInS( void ) {                                    /*F*/
    GO                                                            (UID(FE4388));
    _INIT_TEST_VARS;

    CLEAR(test_str);

    totitleInS(&test_str);  /*null-test*/

    setInS(&test_str, _T(""));
    totitleInS(&test_str);
    _assert(_equal(_str(test_str), _T("")));

    setInS(&test_str, _T(" "));
    totitleInS(&test_str);
    _assert(_equal(_str(test_str), _T(" ")));

    setInS(&test_str, NULL);
    totitleInS(&test_str);
    _assert(_equal(_str(test_str), _T("")));

    setInS(&test_str, _T("a"));
    totitleInS(&test_str);
    _assert(_equal(_str(test_str), _T("A")));

    setInS(&test_str, _T("abc"));
    totitleInS(&test_str);
    _assert(_equal(_str(test_str), _T("Abc")));

    setInS(&test_str, _T("A"));
    totitleInS(&test_str);
    _assert(_equal(_str(test_str), _T("A")));

    setInS(&test_str, _T("ABC"));
    totitleInS(&test_str);
    _assert(_equal(_str(test_str), _T("ABC")));

    setInS(&test_str, _T("Abc"));
    totitleInS(&test_str);
    _assert(_equal(_str(test_str), _T("Abc")));

    setInS(&test_str, _T("Abc123"));
    totitleInS(&test_str);
    _assert(_equal(_str(test_str), _T("Abc123")));

    setInS(&test_str, _T("abc def"));
    totitleInS(&test_str);
    _assert(_equal(_str(test_str), _T("Abc Def")));

    freeS(&test_str);
    RETURN(NIL);
} /* _test_totitleInS */


/* -------------------------------------------------------------------------- */


PUBLIC void  trimInS(                                                      /*M*/
    str_t*           object_,                                              /*-*/
    chars_t          trim_chars_,                                          /*-*/
    const trim_enum  trim_scope_ );                                        /*-*/

static void  _test_trimInS( void ) {                                       /*F*/
    GO                                                            (UID(F4A45C));
    _INIT_TEST_VARS;
    trimInS(&test_str, NULL, TRIM_ALL);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_trimInS() */
    RETURN(NIL);
} /* _test_trimInS */


/* -------------------------------------------------------------------------- */


PUBLIC void  toupperInS( str_t*  object_ );                                /*M*/

static void  _test_toupperInS( void ) {                                    /*F*/
    GO                                                            (UID(FE765C));
    _INIT_TEST_VARS;
    CLEAR(test_str);

    toupperInS(&test_str);  /*null-test*/

    setInS(&test_str, _T(""));
    toupperInS(&test_str);
    _assert(_equal(_str(test_str), _T("")));

    setInS(&test_str, _T(" "));
    toupperInS(&test_str);
    _assert(_equal(_str(test_str), _T(" ")));

    setInS(&test_str, NULL);
    toupperInS(&test_str);
    _assert(_equal(_str(test_str), _T("")));

    setInS(&test_str, _T("a"));
    toupperInS(&test_str);
    _assert(_equal(_str(test_str), _T("A")));

    setInS(&test_str, _T("abc"));
    toupperInS(&test_str);
    _assert(_equal(_str(test_str), _T("ABC")));

    setInS(&test_str, _T("A"));
    toupperInS(&test_str);
    _assert(_equal(_str(test_str), _T("A")));

    setInS(&test_str, _T("ABC"));
    toupperInS(&test_str);
    _assert(_equal(_str(test_str), _T("ABC")));

    setInS(&test_str, _T("Abc"));
    toupperInS(&test_str);
    _assert(_equal(_str(test_str), _T("ABC")));

    setInS(&test_str, _T("Abc123"));
    toupperInS(&test_str);
    _assert(_equal(_str(test_str), _T("ABC123")));

    freeS(&test_str);
    RETURN(NIL);
} /* _test_toupperInS */


/* -------------------------------------------------------------------------- */


PUBLIC bool  beginsS(                                                      /*M*/
    const str_t  object_,                                                  /*-*/
    chars_t      string_,                                                  /*-*/
    const bool   ignore_case_ );                                           /*-*/

static void  _test_S_begins( void ) {                                      /*F*/
    GO                                                            (UID(FE22B9));
    _INIT_TEST_VARS;

    beginsS(test_str, NULL, IGNORE_CASE);  /*null-test*/

    CLEAR(test_str);

#define _TEST( INITIAL_STRING_, TEST_STRING_, IGNORE_CASE_, RESULT_ )  \
    setInS(&test_str, INITIAL_STRING_);                                  \
    _assert(beginsS(test_str, TEST_STRING_, IGNORE_CASE_)              \
            == (RESULT_))                                          /*#*/

    /* if search string and contents are both blank, return true */
    _TEST(_T(""), _T(""), IGNORE_CASE, true);
    _TEST(_T(""), _T(""), MATCH_CASE,  true);
    _TEST(_T(""), NULL,   IGNORE_CASE, true);
    _TEST(_T(""), NULL,   MATCH_CASE,  true);
    _TEST(NULL,   _T(""), IGNORE_CASE, true);
    _TEST(NULL,   _T(""), MATCH_CASE,  true);
    _TEST(NULL,   NULL,   IGNORE_CASE, true);
    _TEST(NULL,   NULL,   MATCH_CASE,  true);

    /* if search string is not blank, */
    /* while contents are blank, always return false */
    _TEST(_T(""), _T("abc"), MATCH_CASE,  false);
    _TEST(_T(""), _T("abc"), IGNORE_CASE, false);

    /* if search string is blank, */
    /* while contents are not blank, always return false */
    _TEST(_T("abc"), _T(""), IGNORE_CASE, false);
    _TEST(_T("abc"), _T(""), MATCH_CASE,  false);

    /* match starting character, with result depending on case */
    _TEST(_T("abc"), _T("a"),  MATCH_CASE,  true);
    _TEST(_T("abc"), _T("A"),  MATCH_CASE,  false);
    _TEST(_T("abc"), _T("A"),  IGNORE_CASE, true);
    _TEST(_T("abc"), _T("ab"), MATCH_CASE,  true);
    _TEST(_T("abc"), _T("Ab"), MATCH_CASE,  false);
    _TEST(_T("abc"), _T("Ab"), IGNORE_CASE, true);

    /* match similar strings, with result depending on case */
    _TEST(_T("abc"), _T("abc"), MATCH_CASE,  true);
    _TEST(_T("abc"), _T("Abc"), MATCH_CASE,  false);
    _TEST(_T("abc"), _T("Abc"), IGNORE_CASE, true);

    /* if search string is longer than contents, always return false */
    _TEST(_T("abc"), _T("Abcd"), IGNORE_CASE, false);
    _TEST(_T("abc"), _T("Abcd"), MATCH_CASE,  false);
    _TEST(_T("abc"), _T("abcd"), MATCH_CASE,  false);

#undef _TEST

    freeS(&test_str);
    RETURN(NIL);
} /* _test_S_begins */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  byteSizeS( const str_t  object_ );                          /*M*/

static void  _test_S_byteSize( void ) {                                    /*F*/
    GO                                                            (UID(F26A5A));
    _INIT_TEST_VARS;

    _assert(byteSizeS(test_str) == 0);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_S_byteSize() */
    RETURN(NIL);
} /* _test_S_byteSize */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  capacityS( const str_t  object_ );                          /*M*/

static void  _test_S_capacity( void ) {                                    /*F*/
    GO                                                            (UID(F47C3C));
    _INIT_TEST_VARS;

    capacityS(test_str);  /*null-test*/

    /* TODO: implement _test_S_capacity() */
    RETURN(NIL);
} /* _test_S_capacity */


/* -------------------------------------------------------------------------- */


PUBLIC chars_t  charsS( const str_t  object_ );                            /*M*/

static void  _test_charsS( void ) {                                        /*F*/
    GO                                                            (UID(FDBFAA));
    _INIT_TEST_VARS;
    charsS(test_str);  /*null-test*/
    RETURN(NIL);
} /* _test_charsS */


/* -------------------------------------------------------------------------- */


PUBLIC bool  containsS(                                                    /*M*/
    const str_t  object_,                                                  /*-*/
    chars_t      substring_,                                               /*-*/
    const bool   ignore_case_ );                                           /*-*/

static void  _test_S_contains( void ) {                                    /*F*/
    GO                                                            (UID(F9FE9D));
    _INIT_TEST_VARS;

    containsS(test_str, NULL, IGNORE_CASE);  /*null-test*/

    CLEAR(test_str);

#define _TEST( INITIAL_STRING_, TEST_STRING_, IGNORE_CASE_, RESULT_ )  \
    setInS(&test_str, INITIAL_STRING_);                                  \
    _assert(containsS(test_str, TEST_STRING_, IGNORE_CASE_)            \
            == (RESULT_))                                          /*#*/

    /* if search string and contents are both blank, return true */
    _TEST(_T(""), _T(""), IGNORE_CASE, true);
    _TEST(_T(""), _T(""), MATCH_CASE,  true);
    _TEST(_T(""), NULL,   IGNORE_CASE, true);
    _TEST(_T(""), NULL,   MATCH_CASE,  true);
    _TEST(NULL,   _T(""), IGNORE_CASE, true);
    _TEST(NULL,   _T(""), MATCH_CASE,  true);
    _TEST(NULL,   NULL,   IGNORE_CASE, true);
    _TEST(NULL,   NULL,   MATCH_CASE,  true);

    /* if search string is not blank, */
    /* while contents are blank, always return false */
    _TEST(_T(""), _T("abc"), MATCH_CASE,  false);
    _TEST(_T(""), _T("abc"), IGNORE_CASE, false);

    /* if search string is blank, */
    /* while contents are not blank, always return false */
    _TEST(_T("abc"), _T(""), IGNORE_CASE, false);
    _TEST(_T("abc"), _T(""), MATCH_CASE,  false);

    /* match with result depending on case */
    _TEST(_T("abcde"), _T("a"),  MATCH_CASE,  true);
    _TEST(_T("abcde"), _T("A"),  MATCH_CASE,  false);
    _TEST(_T("abcde"), _T("A"),  IGNORE_CASE, true);
    _TEST(_T("abcde"), _T("ab"), MATCH_CASE,  true);
    _TEST(_T("abcde"), _T("Ab"), MATCH_CASE,  false);
    _TEST(_T("abcde"), _T("Ab"), IGNORE_CASE, true);

    _TEST(_T("abcde"), _T("e"),  MATCH_CASE,  true);
    _TEST(_T("abcde"), _T("E"),  MATCH_CASE,  false);
    _TEST(_T("abcde"), _T("E"),  IGNORE_CASE, true);
    _TEST(_T("abcde"), _T("de"), MATCH_CASE,  true);
    _TEST(_T("abcde"), _T("DE"), MATCH_CASE,  false);
    _TEST(_T("abcde"), _T("DE"), IGNORE_CASE, true);

    _TEST(_T("abcde"), _T("b"),  MATCH_CASE,  true);
    _TEST(_T("abcde"), _T("B"),  MATCH_CASE,  false);
    _TEST(_T("abcde"), _T("B"),  IGNORE_CASE, true);
    _TEST(_T("abcde"), _T("bc"), MATCH_CASE,  true);
    _TEST(_T("abcde"), _T("BC"), MATCH_CASE,  false);
    _TEST(_T("abcde"), _T("BC"), IGNORE_CASE, true);

    /* match similar strings, with result depending on case */
    _TEST(_T("abc"), _T("abc"), MATCH_CASE,  true);
    _TEST(_T("abc"), _T("Abc"), MATCH_CASE,  false);
    _TEST(_T("abc"), _T("Abc"), IGNORE_CASE, true);

    /* if search string is longer than contents, always return false */
    _TEST(_T("abc"), _T("Abcd"), IGNORE_CASE, false);
    _TEST(_T("abc"), _T("Abcd"), MATCH_CASE,  false);
    _TEST(_T("abc"), _T("abcd"), MATCH_CASE,  false);

#undef _TEST

    freeS(&test_str);
    RETURN(NIL);
} /* _test_S_contains */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  countS(                                                     /*M*/
    const str_t   object_,                                                 /*-*/
    chars_t       string_,                                                 /*-*/
    const bool    ignore_case_,                                            /*-*/
    const size_t  offset_ );                                               /*-*/

static void  _test_S_count( void ) {                                       /*F*/
    GO                                                            (UID(F26162));
    _INIT_TEST_VARS;

    countS(test_str, NULL, IGNORE_CASE, 0);  /*null-test*/

    /* TODO: implement _test_S_count() */
    RETURN(NIL);
} /* _test_S_count */


/* -------------------------------------------------------------------------- */


PUBLIC bool  endsS(                                                        /*M*/
    const str_t  object_,                                                  /*-*/
    chars_t      string_,                                                  /*-*/
    const bool   ignore_case_ );                                           /*-*/

static void  _test_S_ends( void ) {                                        /*F*/
    GO                                                            (UID(F8334A));
    _INIT_TEST_VARS;

    endsS(test_str, NULL, IGNORE_CASE);  /*null-test*/

    CLEAR(test_str);

#define _TEST( INITIAL_STRING_, TEST_STRING_, IGNORE_CASE_, RESULT_ )  \
    setInS(&test_str, INITIAL_STRING_);                                  \
    _assert(endsS(test_str, TEST_STRING_, IGNORE_CASE_)                \
            == (RESULT_))                                          /*#*/

    /* if search string and contents are both blank, return true */
    _TEST(_T(""), _T(""), IGNORE_CASE, true);
    _TEST(_T(""), _T(""), MATCH_CASE,  true);
    _TEST(_T(""), NULL,   IGNORE_CASE, true);
    _TEST(_T(""), NULL,   MATCH_CASE,  true);
    _TEST(NULL,   _T(""), IGNORE_CASE, true);
    _TEST(NULL,   _T(""), MATCH_CASE,  true);
    _TEST(NULL,   NULL,   IGNORE_CASE, true);
    _TEST(NULL,   NULL,   MATCH_CASE,  true);

    /* if search string is not blank,                */
    /* while contents are blank, always return false */
    _TEST(_T(""), _T("abc"), MATCH_CASE,  false);
    _TEST(_T(""), _T("abc"), IGNORE_CASE, false);

    /* if search string is blank,                        */
    /* while contents are not blank, always return false */
    _TEST(_T("abc"), _T(""), IGNORE_CASE, false);
    _TEST(_T("abc"), _T(""), MATCH_CASE,  false);

    /* match starting character, with result depending on case */
    _TEST(_T("abc"), _T("c"),  MATCH_CASE,  true);
    _TEST(_T("abc"), _T("C"),  MATCH_CASE,  false);
    _TEST(_T("abc"), _T("C"),  IGNORE_CASE, true);
    _TEST(_T("abc"), _T("bc"), MATCH_CASE,  true);
    _TEST(_T("abc"), _T("BC"), MATCH_CASE,  false);
    _TEST(_T("abc"), _T("BC"), IGNORE_CASE, true);

    /* match similar strings, with result depending on case */
    _TEST(_T("abc"), _T("abc"), MATCH_CASE,  true);
    _TEST(_T("abc"), _T("Abc"), MATCH_CASE,  false);
    _TEST(_T("abc"), _T("Abc"), IGNORE_CASE, true);

    /* if search string is longer than contents, always return false */
    _TEST(_T("abc"), _T("Abcd"), IGNORE_CASE, false);
    _TEST(_T("abc"), _T("Abcd"), MATCH_CASE,  false);
    _TEST(_T("abc"), _T("abcd"), MATCH_CASE,  false);

#undef _TEST

    freeS(&test_str);
    RETURN(NIL);
} /* _test_S_ends */


/* -------------------------------------------------------------------------- */


PUBLIC bool  equalS(                                                       /*M*/
    const str_t  object_,                                                  /*-*/
    chars_t      string_,                                                  /*-*/
    const bool   ignore_case_ );                                           /*-*/

static void  _test_S_equal( void ) {                                       /*F*/
    GO                                                            (UID(F8045E));
    _INIT_TEST_VARS;

    equalS(test_str, NULL, IGNORE_CASE);  /*null-test*/
    CLEAR(test_str);

#define _TEST( INITIAL_STRING_, TEST_STRING_, IGNORE_CASE_, RESULT_ )  \
    setInS(&test_str, INITIAL_STRING_);                                  \
    _assert(equalS(test_str, TEST_STRING_, IGNORE_CASE_)               \
            == (RESULT_))                                          /*#*/

    /* if search string and contents are both blank, return true */
    _TEST(_T(""), _T(""), IGNORE_CASE, true);
    _TEST(_T(""), _T(""), MATCH_CASE,  true);
    _TEST(_T(""), NULL,   IGNORE_CASE, true);
    _TEST(_T(""), NULL,   MATCH_CASE,  true);
    _TEST(NULL,   _T(""), IGNORE_CASE, true);
    _TEST(NULL,   _T(""), MATCH_CASE,  true);
    _TEST(NULL,   NULL,   IGNORE_CASE, true);
    _TEST(NULL,   NULL,   MATCH_CASE,  true);

    /* if search string is not blank, */
    /* while contents are blank, always return false */
    _TEST(_T(""), _T("abc"), MATCH_CASE,  false);
    _TEST(_T(""), _T("abc"), IGNORE_CASE, false);

    /* if search string is blank, */
    /* while contents are not blank, always return false */
    _TEST(_T("abc"), _T(""), IGNORE_CASE, false);
    _TEST(_T("abc"), _T(""), MATCH_CASE,  false);

    /* where length of content and search string differs, always return false */
    _TEST(_T("abc"), _T("Abcd"), IGNORE_CASE, false);
    _TEST(_T("abc"), _T("abcd"), MATCH_CASE,  false);
    _TEST(_T("abc"), _T("Abcd"), MATCH_CASE,  false);
    _TEST(_T("abc"), _T("bc"),   IGNORE_CASE, false);
    _TEST(_T("abc"), _T("bc"),   MATCH_CASE,  false);
    _TEST(_T("abc"), _T("bc"),   MATCH_CASE,  false);
    _TEST(_T("abc"), _T("C"),    IGNORE_CASE, false);
    _TEST(_T("abc"), _T("c"),    MATCH_CASE,  false);
    _TEST(_T("abc"), _T("C"),    MATCH_CASE,  false);

    /* match similar strings, with result depending on case */
    _TEST(_T("abc"), _T("abc"), MATCH_CASE,  true);
    _TEST(_T("abc"), _T("Abc"), MATCH_CASE,  false);
    _TEST(_T("abc"), _T("Abc"), IGNORE_CASE, true);

#undef _TEST

    freeS(&test_str);
    RETURN(NIL);
} /* _test_S_equal */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  findS(                                                      /*M*/
    const str_t   object_,                                                 /*-*/
    chars_t       find_str_,                                               /*-*/
    const size_t  offset_,                                                 /*-*/
    const bool    ignore_case_,                                            /*-*/
    const bool    from_end_ );                                             /*-*/

static void  _test_S_find( void ) {                                        /*F*/
    GO                                                            (UID(FDEE3D));
    _INIT_TEST_VARS;

    findS(test_str, NULL, 0, IGNORE_CASE, false);  /*null-test*/

    RETURN(NIL);
} /* _test_S_find */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  findCharS(                                                  /*M*/
    const str_t   object_,                                                 /*-*/
    const char_t  find_char_,                                              /*-*/
    const size_t  offset_,                                                 /*-*/
    const bool    ignore_case_,                                            /*-*/
    const bool    from_end_ );                                             /*-*/

static void  _test_S_findChar( void ) {                                    /*F*/
    GO                                                            (UID(F046B3));
    _INIT_TEST_VARS;

    findCharS(test_str, '\0', 0, IGNORE_CASE, false);  /*null-test*/

    /* TODO: implement _test_S_findChar() */
    RETURN(NIL);
} /* _test_S_findChar */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  findCharsS(                                                 /*M*/
    const str_t  object_,                                                  /*-*/
    chars_t      chars_to_find_,                                           /*-*/
    const bool   ignore_case_ );                                           /*-*/

static void  _test_S_findChars( void ) {                                   /*F*/
    GO                                                            (UID(F730BB));
    _INIT_TEST_VARS;

    findCharsS(test_str, NULL, IGNORE_CASE);  /*null-test*/

    /* TODO: implement _test_S_findChars() */
    RETURN(NIL);
} /* _test_S_findChars */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  findEndS(                                                   /*M*/
    const str_t   object_,                                                 /*-*/
    chars_t       find_str_,                                               /*-*/
    const size_t  offset_,                                                 /*-*/
    const bool    ignore_case_ );                                          /*-*/

static void  _test_S_findEnd( void ) {                                     /*F*/
    GO                                                            (UID(FC1120));
    _INIT_TEST_VARS;

    findEndS(test_str, NULL, 0, IGNORE_CASE);  /*null-test*/

    /* TODO: implement _test_S_findEnd() */
    RETURN(NIL);
} /* _test_S_findEnd */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  findEndChar4S(                                              /*M*/
    const str_t   object_,                                                 /*-*/
    const char_t  find_char_,                                              /*-*/
    const bool    ignore_case_,                                            /*-*/
    const size_t  offset_ );                                               /*-*/

static void  _test_S_findEndChar4( void ) {                                /*F*/
    GO                                                            (UID(F138DE));
    _INIT_TEST_VARS;

    findEndChar4S(test_str, '\0', IGNORE_CASE, 0);  /*null-test*/

    /* TODO: implement _test_S_findEndChar4() */
    RETURN(NIL);
} /* _test_S_findEndChar4 */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  findFirstNotOfS(                                            /*M*/
    const str_t  object_,                                                  /*-*/
    chars_t      chars_ );                                                 /*-*/

static void  _test_S_findFirstNotOf( void ) {                              /*F*/
    GO                                                            (UID(FF14C2));
    _INIT_TEST_VARS;

    findFirstNotOfS(test_str, NULL);  /*null-test*/

    /* TODO: implement _test_S_findFirstNotOf() */
    RETURN(NIL);
} /* _test_S_findFirstNotOf */


/* -------------------------------------------------------------------------- */


PUBLIC char_t*  getBufferS( str_t*  object_ );                             /*M*/

static void  _test_getBufferS( void ) {                                    /*F*/
    GO                                                            (UID(F5FE2A));
    _INIT_TEST_VARS;

    getBufferS(&test_str);  /*null-test*/

    /* TODO: implement _test_getBufferS() */
    RETURN(NIL);
} /* _test_getBufferS */


/* -------------------------------------------------------------------------- */


PUBLIC char_t*  getEmptyBufferS(                                           /*M*/
    str_t*        object_,                                                 /*-*/
    const size_t  length_ );                                               /*-*/

static void  _test_getEmptyBufferS( void ) {                               /*F*/
    GO                                                            (UID(F16D3D));
    _INIT_TEST_VARS;

    getEmptyBufferS(&test_str, 0);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_getEmptyBufferS() */
    RETURN(NIL);
} /* _test_getEmptyBufferS */


/* -------------------------------------------------------------------------- */


PUBLIC bool  emptyS( const str_t  object_ );                               /*P*/

static void  _test_emptyS( void ) {                                        /*F*/
    GO                                                            (UID(F2B6F8));
    _INIT_TEST_VARS;

    emptyS(test_str);  /*null-test*/

    test_str = S_blank();
    _assert(emptyS(test_str) == true);
    freeS(&test_str);

    setInS(&test_str, _T("123"));
    _assert(emptyS(test_str) == false);
    freeS(&test_str);

    setInS(&test_str, _T(""));
    _assert(emptyS(test_str) == true);
    freeS(&test_str);

    setInS(&test_str, _T("\0abc"));
    _assert(emptyS(test_str) == true);
    freeS(&test_str);

    setInS(&test_str, BLANK);
    _assert(emptyS(test_str) == true);
    freeS(&test_str);

    setInS(&test_str, NULL);
    _assert(emptyS(test_str) == true);
    freeS(&test_str);

    setInS(&test_str, _T(" "));
    _assert(emptyS(test_str) == false);
    freeS(&test_str);

    setInS(&test_str, _T("\b"));
    _assert(emptyS(test_str) == false);
    freeS(&test_str);

    setInS(&test_str, _T("\n"));
    _assert(emptyS(test_str) == false);
    freeS(&test_str);

    setInS(&test_str, _T("\r"));
    _assert(emptyS(test_str) == false);
    freeS(&test_str);

    setInS(&test_str, _T("\t"));
    _assert(emptyS(test_str) == false);
    freeS(&test_str);

    setInS(&test_str, _T("1"));
    _assert(emptyS(test_str) == false);
    freeS(&test_str);

    {
        struct _test_t {
            chars_t  init;                                         /* _test_t */
            bool     result;                                       /* _test_t */
        }
        test[] = {
            { _T(""),      true  },
            { _T("\0abc"), true  },
            { NULL,        true  },
            { BLANK,       true  },

            { _T(" "),     false },
            { _T("\b"),    false },
            { _T("\n"),    false },
            { _T("\r"),    false },
            { _T("\t"),    false },
            { _T("1"),     false },
            { _T("123"),   false },
            { _T("a"),     false },
            { _T("abc"),   false },

            { NULL,        false }
        };

        int  i = 0;
        while (test[i].init != NULL) {
            chars_t     init     = test[i].init;
            const bool  is_check = test[i].result;

            setInS(&test_str, init);
            _assert(emptyS(test_str) == is_check);
            freeS(&test_str);
            i++;
        }
    }
    RETURN(NIL);
} /* _test_emptyS */


/* -------------------------------------------------------------------------- */


PUBLIC bool  isNumberS(                                                    /*P*/
    const str_t   object_,                                                 /*-*/
    const char_t  decimal_point_char_,                                     /*-*/
    const char_t  group_separator_char_,                                   /*-*/
    chars_t       whitespaces_ );                                          /*-*/

static void  _test_S_isNumber( void ) {                                    /*F*/
    GO                                                            (UID(FAD609));
    _INIT_TEST_VARS;

    isNumberS(test_str, '\0', '\0', NULL);  /*null-test*/

#define _TEST( VALUE_ )                                               \
    _assert(isNumberS(test_str, '.', ',', _T(" \r\n\t")) == VALUE_);  \
    freeS(&test_str);                                             /*#*/

    CLEAR(test_str);

    /* numeric */
    {
        setInS(&test_str, _T(" .0000000000001 "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" -.0000000000001 "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" .0000000000001"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" -.0000000000001"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" .123"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" +.0000000000001 "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" +.0000000000001"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" +0.123"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" +123,456,789 "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" +123,456,789"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" 0 "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" 0"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" 0.01"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" -0.123"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" 00 "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" 00"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" 0001234"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" 0001234."));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" 123,456,789 "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" -123,456,789 "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" 123,456,789"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" -123,456,789"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" 123,456,789.12345 "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" 123,456,789.12345"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" 123456789"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(".0000000000001 "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("-.0000000000001 "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(".0000000000001"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("-.0000000000001"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(".123"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("-.123"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("+.0000000000001 "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("+.0000000000001"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("+.123"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("+0.123"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("+1"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("+123,456,789 "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("+123,456,789"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("+123456"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("0 "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("0"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("0,123"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("0.01"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("-0.123"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("00 "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("00"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("0001234"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("0001234."));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("0001234.0"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("0001234.00"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("123,456,789 "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("-123,456,789 "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("123,456,789"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("-123,456,789"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("123,456,789.12345 "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("123,456,789.12345"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("123456789"));
        _TEST(true);
    }

    /* non-numeric: blank strings */
    {
        setInS(&test_str, _T(""));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("\0"));
        _TEST(false);
    }
    {
        setInS(&test_str, BLANK);
        _TEST(false);
    }

    /* non-numeric: single numeric formatting characters */
    {
        setInS(&test_str, _T(" "));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("-"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T(","));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("."));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("\n"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("\r"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("\t"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("+"));
        _TEST(false);
    }

    /* non-numeric: multiple decimal points */
    {
        setInS(&test_str, _T(".."));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("..."));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("..0"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("..1"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("..100"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T(".0."));
        _TEST(false);
    }
    {
        setInS(&test_str, _T(".1."));
        _TEST(false);
    }
    {
        setInS(&test_str, _T(".100."));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("0.."));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("1.."));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("100.."));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("100.100.100"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("195.168.0.0"));
        _TEST(false);
    }

    /* non-numeric: multiple signs */
    {
        setInS(&test_str, _T("--"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("+-"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("-+"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("++"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("++0"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("++1"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("0--"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("--0"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("0++"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("1--"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("--1"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("1++"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("-123,456,789.-12345"));
        _TEST(false);
    }

    /* non-numeric: alphabetic charactes */
    {
        setInS(&test_str, _T("123A"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("a"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("A"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("A123"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("abc"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("ABC"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("z"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("Z"));
        _TEST(false);
    }

    /* non-numeric: wrong formatting */
    {
        setInS(&test_str, _T(",123"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("0-1"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("1-"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("1+"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("12 34"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("-123.456,789.12345"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("123456+"));
        _TEST(false);
    }

#undef _TEST

    RETURN(NIL);
} /* _test_S_isNumber */


/* -------------------------------------------------------------------------- */


PUBLIC bool  isSpaceS( const str_t  object_ );                             /*P*/

static void  _test_S_isWhitespace( void ) {                                /*F*/
    GO                                                            (UID(FE6C0C));
    _INIT_TEST_VARS;

    isSpaceS(test_str);  /*null-test*/

#define _TEST( VALUE_ )                     \
    _assert(isSpaceS(test_str) == VALUE_);  \
    freeS(&test_str);                   /*#*/

    CLEAR(test_str);

    {
        setInS(&test_str, _T("  "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" \b "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" \b"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" \n "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" \n"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" \r "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" \r"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" \t "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T(" \t"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("\b "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("\b"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("\n "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("\n"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("\r "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("\r"));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("\t "));
        _TEST(true);
    }
    {
        setInS(&test_str, _T("\t"));
        _TEST(true);
    }

    {
        setInS(&test_str, _T(" a"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T(""));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("\0"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("a "));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("a"));
        _TEST(false);
    }
    {
        setInS(&test_str, _T("abc"));
        _TEST(false);
    }
    {
        setInS(&test_str, BLANK);
        _TEST(false);
    }
    {
        setInS(&test_str, NULL);
        _TEST(false);
    }

#undef _TEST

    RETURN(NIL);
} /* _test_S_isWhitespace */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  lengthS( const str_t  object_ );                            /*M*/

static void  _test_S_length( void ) {                                      /*F*/
    GO                                                            (UID(F5FFCB));
    _INIT_TEST_VARS;

    lengthS(test_str);  /*null-test*/

    /* TODO: implement _test_S_length() */
    RETURN(NIL);
} /* _test_S_length */


/* -------------------------------------------------------------------------- */


PUBLIC bool  like3S(                                                       /*M*/
    const str_t  object_,                                                  /*-*/
    chars_t      string_,                                                  /*-*/
    const bool   ignore_case_ );                                           /*-*/

static void  _test_S_like3( void ) {                                       /*F*/
    GO                                                            (UID(F7CAC9));
    _INIT_TEST_VARS;

    like3S(test_str, NULL, IGNORE_CASE);  /*null-test*/

    _assert(like3S(test_str, _T(""), IGNORE_CASE) == true);
    _assert(like3S(test_str, _T(""), MATCH_CASE)  == true);
    _assert(like3S(test_str, NULL,   IGNORE_CASE) == true);
    _assert(like3S(test_str, NULL,   MATCH_CASE)  == true);

    _assert(like3S(test_str, _T(" "),  MATCH_CASE) == false);
    _assert(like3S(test_str, _T("\r"), MATCH_CASE) == false);
    _assert(like3S(test_str, _T("\n"), MATCH_CASE) == false);
    _assert(like3S(test_str, _T("\t"), MATCH_CASE) == false);
    _assert(like3S(test_str, _T("a"),  MATCH_CASE) == false);
    _assert(like3S(test_str, _T("a"),  MATCH_CASE) == false);

    _assert(like3S(test_str, _T(" "),  MATCH_CASE) == false);
    _assert(like3S(test_str, _T("\r"), MATCH_CASE) == false);
    _assert(like3S(test_str, _T("\n"), MATCH_CASE) == false);
    _assert(like3S(test_str, _T("\t"), MATCH_CASE) == false);
    _assert(like3S(test_str, _T("a"),  MATCH_CASE) == false);
    _assert(like3S(test_str, _T("a"),  MATCH_CASE) == false);

    setInS(&test_str, _T("abc"));

    _assert(like3S(test_str, NULL,   MATCH_CASE)  == false);
    _assert(like3S(test_str, _T(""), MATCH_CASE)  == false);
    _assert(like3S(test_str, NULL,   IGNORE_CASE) == false);
    _assert(like3S(test_str, _T(""), IGNORE_CASE) == false);

    _assert(like3S(test_str, _T("ab"),   MATCH_CASE)  == false);
    _assert(like3S(test_str, _T("abcd"), MATCH_CASE)  == false);
    _assert(like3S(test_str, _T("ab"),   IGNORE_CASE) == false);
    _assert(like3S(test_str, _T("abcd"), IGNORE_CASE) == false);

    _assert(like3S(test_str, _T("ABC"), MATCH_CASE)  == false);
    _assert(like3S(test_str, _T("ABC"), IGNORE_CASE) == true);
    _assert(like3S(test_str, _T("abc"), MATCH_CASE)  == true);
    _assert(like3S(test_str, _T("abc"), IGNORE_CASE) == true);

    freeS(&test_str);
    RETURN(NIL);
} /* _test_S_like3 */


/* -------------------------------------------------------------------------- */


PUBLIC int  lineCountS( const str_t  object_ );                            /*M*/

static void  _test_S_lineCount( void ) {                                   /*F*/
    GO                                                            (UID(FD979A));
    _INIT_TEST_VARS;

    lineCountS(test_str);  /*null-test*/

    RETURN(NIL);
} /* _test_S_lineCount */


/* -------------------------------------------------------------------------- */


PUBLIC bool  patternMatchS(                                                /*M*/
    const str_t  object_,                                                  /*-*/
    chars_t      pattern_,                                                 /*-*/
    const bool   ignore_case_ );                                           /*-*/

static void  _test_patternMatchS( void ) {                                 /*F*/
    GO                                                            (UID(F37318));
    _INIT_TEST_VARS;

    patternMatchS(test_str, NULL, IGNORE_CASE);  /*null-test*/

    /* TODO: implement _test_patternMatchS() */
    RETURN(NIL);
} /* _test_patternMatchS */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  skipCharsS(                                                 /*M*/
    const str_t  object_,                                                  /*-*/
    chars_t      chars_to_skip_,                                           /*-*/
    const bool   ignore_case_ );                                           /*-*/

static void  _test_S_skipChars( void ) {                                   /*F*/
    GO                                                            (UID(F19156));
    _INIT_TEST_VARS;

    skipCharsS(test_str, NULL, IGNORE_CASE);  /*null-test*/

    /* TODO: implement _test_S_skipChars() */
    RETURN(NIL);
} /* _test_S_skipChars */


/* -------------------------------------------------------------------------- */


PUBLIC double  doubleS( const str_t  object_ );                            /*M*/

static void  _test_doubleS( void ) {                                       /*F*/
    GO                                                            (UID(F164D6));
    _INIT_TEST_VARS;
    doubleS(test_str);  /*null-test*/
    RETURN(NIL);
} /* _test_doubleS */


/* -------------------------------------------------------------------------- */


PUBLIC int  intS( const str_t  object_ );                                  /*M*/

static void  _test_S_toInt( void ) {                                       /*F*/
    GO                                                            (UID(F2D73F));
    _INIT_TEST_VARS;
    intS(test_str);  /*null-test*/
    RETURN(NIL);
} /* _test_S_toInt */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  tokenCountXtS(                                              /*M*/
    const str_t  object_,                                                  /*-*/
    chars_t      delimiter_,                                               /*-*/
    chars_t      token_,                                                   /*-*/
    const bool   ignore_case_ );                                           /*-*/

static void  _test_tokenCountXtS( void ) {                                 /*F*/
    GO                                                            (UID(FF81E4));
    _INIT_TEST_VARS;

    tokenCountXtS(test_str, NULL, NULL, IGNORE_CASE);  /*null-test*/

    /* TODO: implement _test_tokenCountXtS() */
    RETURN(NIL);
} /* _test_tokenCountXtS */


/* -------------------------------------------------------------------------- */


PUBLIC bool  tokenExistsS(                                                 /*M*/
    const str_t  object_,                                                  /*-*/
    chars_t      token_,                                                   /*-*/
    chars_t      delimiter_,                                               /*-*/
    const bool   ignore_case_ );                                           /*-*/

static void  _test_existsTokenS( void ) {                                  /*F*/
    GO                                                            (UID(FBD94B));
    _INIT_TEST_VARS;

    tokenExistsS(test_str, NULL, NULL, IGNORE_CASE);  /*null-test*/

    /* TODO: implement _test_existsTokenS() */
    RETURN(NIL);
} /* _test_existsTokenS */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  tokenIndexS(                                                /*M*/
    const str_t  object_,                                                  /*-*/
    chars_t      token_,                                                   /*-*/
    chars_t      delimiter_,                                               /*-*/
    const bool   ignore_case_ );                                           /*-*/

static void  _test_tokenIndexS( void ) {                                   /*F*/
    GO                                                            (UID(F389A2));
    _INIT_TEST_VARS;

    tokenIndexS(test_str, NULL, NULL, IGNORE_CASE);  /*null-test*/

    /* TODO: implement _test_tokenIndexS() */
    RETURN(NIL);
} /* _test_tokenIndexS */


/* -------------------------------------------------------------------------- */


PUBLIC uint32_t  uintS( const str_t  object_ );                            /*M*/

static void  _test_uintS( void ) {                                         /*F*/
    GO                                                            (UID(FD7603));
    _INIT_TEST_VARS;

    uintS(test_str);  /*null-test*/

    RETURN(NIL);
} /* _test_uintS */


/* -------------------------------------------------------------------------- */


PUBLIC const wchar_t*  wcharsS( const str_t  object_ );                    /*M*/

static void  _test_wcharsS( void ) {                                       /*F*/
    GO                                                            (UID(FD11BC));
    _INIT_TEST_VARS;

    wcharsS(test_str);  /*null-test*/

    /* TODO: implement _test_wcharsS() */
    RETURN(NIL);
} /* _test_wcharsS */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_bracket(                                               /*M*/
    const str_t  object_,                                                  /*-*/
    chars_t      brackets_ );                                              /*-*/

static void  _test_Sbracket( void ) {                                      /*F*/
    GO                                                            (UID(F83174));
    _INIT_TEST_VARS;

    test_str = S_bracket(test_str, NULL);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_Sbracket() */
    RETURN(NIL);
} /* _test_Sbracket */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_decodeBase64( const str_t  object_ );                  /*M*/

static void  _test_SdecodeBase64( void ) {                                 /*F*/
    GO                                                            (UID(FE72AA));
    _INIT_TEST_VARS;

    test_str = S_decodeBase64(test_str);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_SdecodeBase64() */
    RETURN(NIL);
} /* _test_SdecodeBase64 */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_encodeBase64( const str_t  object_ );                  /*M*/

static void  _test_SencodeBase64( void ) {                                 /*F*/
    GO                                                            (UID(FD9678));
    _INIT_TEST_VARS;

    test_str = S_encodeBase64(test_str);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_SencodeBase64() */
    RETURN(NIL);
} /* _test_SencodeBase64 */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_first(                                                 /*M*/
    const str_t   object_,                                                 /*-*/
    const size_t  count_ );                                                /*-*/

static void  _test_Sfirst( void ) {                                        /*F*/
    GO                                                            (UID(F85417));
    _INIT_TEST_VARS;

    test_str = S_first(test_str, 0);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_Sfirst() */
    RETURN(NIL);
} /* _test_Sfirst */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_substr(                                                /*M*/
    const str_t   object_,                                                 /*-*/
    const size_t  offset_,                                                 /*-*/
    const size_t  length_ );                                               /*-*/

static void  _test_Ssubstr( void ) {                                       /*F*/
    GO                                                            (UID(F41648));
    _INIT_TEST_VARS;

    test_str = S_substr(test_str, 0, 0);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_Ssubstr() */
    RETURN(NIL);
} /* _test_Ssubstr */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_insert(                                                /*M*/
    const str_t   object_,                                                 /*-*/
    chars_t       string_,                                                 /*-*/
    const size_t  position_,                                               /*-*/
    const size_t  length_ );                                               /*-*/

static void  _test_Sinsert( void ) {                                       /*F*/
    GO                                                            (UID(F3C6A3));
    _INIT_TEST_VARS;

    test_str = S_insert(test_str, NULL, 0, 0);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_Sinsert() */
    RETURN(NIL);
} /* _test_Sinsert */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_last(                                                  /*M*/
    const str_t   object_,                                                 /*-*/
    const size_t  length_ );                                               /*-*/

static void  _test_Slast( void ) {                                         /*F*/
    GO                                                            (UID(FF9EA9));
    _INIT_TEST_VARS;

    test_str = S_last(test_str, 0);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_Slast() */
    RETURN(NIL);
} /* _test_Slast */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_lowerCase( const str_t  object_ );                     /*M*/

static void  _test_SlowerCase( void ) {                                    /*F*/
    GO                                                            (UID(F97FBF));
    _INIT_TEST_VARS;

    test_str = S_lowerCase(test_str);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_SlowerCase() */
    RETURN(NIL);
} /* _test_SlowerCase */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_quote(                                                 /*M*/
    const str_t  object_,                                                  /*-*/
    chars_t      quote_,                                                   /*-*/
    chars_t      replace_ );                                               /*-*/

static void  _test_Squote( void ) {                                        /*F*/
    GO                                                            (UID(FC26EE));
    _INIT_TEST_VARS;

    test_str = S_quote(test_str, NULL, NULL);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_Squote() */
    RETURN(NIL);
} /* _test_Squote */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_remove(                                                /*M*/
    const str_t   object_,                                                 /*-*/
    const size_t  position_,                                               /*-*/
    const size_t  length_ );                                               /*-*/

static void  _test_Sremove( void ) {                                       /*F*/
    GO                                                            (UID(FF5493));
    _INIT_TEST_VARS;

    test_str = S_remove(test_str, 0, 0);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_Sremove() */
    RETURN(NIL);
} /* _test_Sremove */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_removeBegin(                                           /*M*/
    const str_t   object_,                                                 /*-*/
    const size_t  char_count_ );                                           /*-*/

static void  _test_SremoveBegin( void ) {                                  /*F*/
    GO                                                            (UID(F74FE3));
    _INIT_TEST_VARS;

    test_str = S_removeBegin(test_str, 0);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_SremoveBegin() */
    RETURN(NIL);
} /* _test_SremoveBegin */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_removeChar(                                            /*M*/
    const str_t   object_,                                                 /*-*/
    const char_t  char_,                                                   /*-*/
    const bool    ignore_case_ );                                          /*-*/

static void  _test_SremoveChar( void ) {                                   /*F*/
    GO                                                            (UID(F89ADE));
    _INIT_TEST_VARS;

    test_str = S_removeChar(test_str, '\0', IGNORE_CASE);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_SremoveChar() */
    RETURN(NIL);
} /* _test_SremoveChar */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_removeEnd(                                             /*M*/
    const str_t   object_,                                                 /*-*/
    const size_t  char_count_ );                                           /*-*/

static void  _test_SremoveEnd( void ) {                                    /*F*/
    GO                                                            (UID(F336A0));
    _INIT_TEST_VARS;

    test_str = S_removeEnd(test_str, 0);  /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_SremoveEnd() */
    RETURN(NIL);
} /* _test_SremoveEnd */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_removeStr(                                             /*M*/
    const str_t  object_,                                                  /*-*/
    chars_t      string_,                                                  /*-*/
    const bool   ignore_case_ );                                           /*-*/

static void  _test_SremoveStr( void ) {                                    /*F*/
    GO                                                            (UID(FF3F4F));
    _INIT_TEST_VARS;

    test_str = S_removeStr(test_str, NULL, IGNORE_CASE);   /*null-test*/
    freeS(&test_str);

    /* TODO: implement _test_SremoveStr() */
    RETURN(NIL);
} /* _test_SremoveStr */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_replace(                                               /*M*/
    const str_t  object_,                                                  /*-*/
    chars_t      find_str_,                                                /*-*/
    chars_t      replace_str_,                                             /*-*/
    const bool   ignore_case_ );                                           /*-*/

static void  _test_Sreplace( void ) {                                      /*F*/
    GO                                                            (UID(FB16BB));
    _INIT_TEST_VARS;

    test_str = S_replace(test_str, NULL, NULL, IGNORE_CASE);  /*null-test*/
    freeS(&test_str);

    {
        /* when 'a' is null... */
        str_t  a = S_chars(NULL);

        {
            /* repacing a blank string should effect the replacement */
            str_t  b = S_replace(a, _T(""), _T("ABC"), MATCH_CASE);
            _assert(_equal(_str(b), _T("ABC")));
            freeS(&b);
        }
        {
            /* when 'a' is null, repacing a blank should do the replacement */
            str_t  b = S_replace(a, _T(""), _T("ABC"), MATCH_CASE);
            _assert(_equal(_str(b), _T("ABC")));
            freeS(&b);
        }
        {
            /* when 'a' is null, repacing a null should do the replacement */
            str_t  b = S_replace(a, NULL, _T("ABC"), MATCH_CASE);
            _assert(_equal(_str(b), _T("ABC")));
            freeS(&b);
        }
        freeS(&a);
    }
    {
        /* when 'a' is blank, repacing a blank should do the replacement */
        str_t  a = S_chars(_T(""));
        str_t  b = S_replace(a, _T(""), _T("ABC"), MATCH_CASE);
        _assert(_equal(_str(b), _T("ABC")));
        freeS(&a);
        freeS(&b);
    }
    {
        /* if 'a' isn't blank, repacing a blank string should have no effect */
        str_t  a = S_chars(_T("123"));
        str_t  b = S_replace(a, _T(""), _T("ABC"), MATCH_CASE);
        _assert(_equal(_str(b), _T("123")));
        freeS(&a);
        freeS(&b);
    }
    {
        /* if 'a' is not blank, repacing a null string should have no effect */
        str_t  a = S_chars(_T("123"));
        str_t  b = S_replace(a, NULL, _T("ABC"), MATCH_CASE);
        _assert(_equal(_str(b), _T("123")));
        freeS(&a);
        freeS(&b);
    }
    RETURN(NIL);
} /* _test_Sreplace */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_replaceByRef(                                          /*M*/
    const str_t  object_,                                                  /*-*/
    const str_t  find_,                                                    /*-*/
    const str_t  replace_,                                                 /*-*/
    const bool   ignore_case_ );                                           /*-*/

static void  _test_SreplaceByRef( void ) {                                 /*F*/
    GO                                                            (UID(FCBEE9));
    _INIT_TEST_VARS;
    /*null-test*/
    test_str = S_replaceByRef(test_str, test_str, test_str, IGNORE_CASE);
    freeS(&test_str);
    /* TODO: implement _test_SreplaceByRef() */
    RETURN(NIL);
} /* _test_SreplaceByRef */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_reverse( const str_t  object_ );                       /*M*/

static void  _test_Sreverse( void ) {                                      /*F*/
    GO                                                            (UID(F04B88));
    _INIT_TEST_VARS;
    test_str = S_reverse(test_str);  /*null-test*/
    freeS(&test_str);
    /* TODO: implement _test_Sreverse() */
    RETURN(NIL);
} /* _test_Sreverse */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_sortList(                                              /*M*/
    const str_t  object_,                                                  /*-*/
    chars_t      delimiter_,                                               /*-*/
    const bool   descending_,                                              /*-*/
    const bool   unique_ );                                                /*-*/

static void  _test_SsortList( void ) {                                     /*F*/
    GO                                                            (UID(F68AFB));
    _INIT_TEST_VARS;
    test_str = S_sortList(test_str, NULL, false, false);  /*null-test*/
    freeS(&test_str);
    /* TODO: implement _test_SsortList() */
    RETURN(NIL);
} /* _test_SsortList */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_space(                                                 /*M*/
    const str_t   object_,                                                 /*-*/
    const size_t  length_in_chars_,                                        /*-*/
    const bool    align_to_end_,                                           /*-*/
    const bool    spillover_ );                                            /*-*/

static void  _test_Sspace( void ) {                                        /*F*/
    GO                                                            (UID(F87A71));
    _INIT_TEST_VARS;
    test_str = S_space(test_str, 0, false, false);  /*null-test*/
    freeS(&test_str);
    /* TODO: implement _test_Sspace() */
    RETURN(NIL);
} /* _test_Sspace */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_getTag(                                                /*M*/
    const str_t   object_,                                                 /*-*/
    chars_t       tag_,                                                    /*-*/
    chars_t       end_tag_,                                                /*-*/
    chars_t       delimiter_,                                              /*-*/
    const bool    ignore_case_,                                            /*-*/
    const size_t  instance_no_ );                                          /*-*/

static void  _test_SgetTag( void ) {                                       /*F*/
    GO                                                            (UID(F967FA));
    _INIT_TEST_VARS;
    test_str = S_getTag(test_str, NULL, NULL, NULL, IGNORE_CASE, 0);
    /*null-test*/
    freeS(&test_str);
    /* TODO: implement _test_SgetTag() */
    RETURN(NIL);
} /* _test_SgetTag */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_titleCase( const str_t  object_ );                     /*M*/

static void  _test_StitleCase( void ) {                                    /*F*/
    GO                                                            (UID(FC73B0));
    _INIT_TEST_VARS;
    test_str = S_titleCase(test_str);  /*null-test*/
    freeS(&test_str);
    /* TODO: implement _test_StitleCase() */
    RETURN(NIL);
} /* _test_StitleCase */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_getToken(                                              /*M*/
    const str_t   object_,                                                 /*-*/
    const size_t  index_,                                                  /*-*/
    chars_t       delimiter_ );                                            /*-*/

static void  _test_S_getToken( void ) {                                    /*F*/
    GO                                                            (UID(FDE7EF));
    _INIT_TEST_VARS;
    test_str = S_getToken(test_str, 0, NULL);  /*null-test*/
    freeS(&test_str);
    /* TODO: Add S_getToken(("AAA BBB"), 2, " ")  must return blank */
    /* TODO: implement _test_S_getToken() */
    RETURN(NIL);
} /* _test_S_getToken */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_getTokenXt(                                            /*M*/
    const str_t   object_,                                                 /*-*/
    const size_t  index_,                                                  /*-*/
    chars_t       delimiter_,                                              /*-*/
    const bool    ignore_end_delimiter_ );                                 /*-*/

static void  _test_S_getTokenXt( void ) {                                  /*F*/
    GO                                                            (UID(F469A3));
    _INIT_TEST_VARS;
    test_str = S_getTokenXt(test_str, 0, NULL, false);  /*null-test*/
    freeS(&test_str);
    /* TODO: implement _test_S_getTokenXt() */
    RETURN(NIL);
} /* _test_S_getTokenXt */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_setToken(                                              /*M*/
    const str_t   object_,                                                 /*-*/
    const size_t  index_,                                                  /*-*/
    chars_t       token_,                                                  /*-*/
    chars_t       delimiter_ );                                            /*-*/

static void  _test_S_setToken( void ) {                                    /*F*/
    GO                                                            (UID(FB45D9));
    _INIT_TEST_VARS;
    test_str = S_setToken(test_str, 0, NULL, NULL);  /*null-test*/
    freeS(&test_str);
    /* TODO: implement _test_S_setToken() */
    RETURN(NIL);
} /* _test_S_setToken */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_trim(                                                  /*M*/
    const str_t      object_,                                              /*-*/
    chars_t          trim_chars_,                                          /*-*/
    const trim_enum  trim_scope_ );                                        /*-*/

static void  _test_Strim( void ) {                                         /*F*/
    GO                                                            (UID(F272F2));
    _INIT_TEST_VARS;
    test_str = S_trim(test_str, NULL, TRIM_ALL);  /*null-test*/
    freeS(&test_str);
    /* TODO: implement _test_Strim() */
    RETURN(NIL);
} /* _test_Strim */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_trimBegin(                                             /*M*/
    const str_t  object_,                                                  /*-*/
    chars_t      trim_chars_ );                                            /*-*/

static void  _test_StrimBegin( void ) {                                    /*F*/
    GO                                                            (UID(F59317));
    _INIT_TEST_VARS;
    test_str = S_trimBegin(test_str, NULL);  /*null-test*/
    freeS(&test_str);
    /* TODO: implement _test_StrimBegin() */
    RETURN(NIL);
} /* _test_StrimBegin */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_trimBeginChar(                                         /*M*/
    const str_t   object_,                                                 /*-*/
    const char_t  char_ );                                                 /*-*/

static void  _test_StrimBeginChar( void ) {                                /*F*/
    GO                                                            (UID(FA9D1D));
    _INIT_TEST_VARS;
    test_str = S_trimBeginChar(test_str, '\0');  /*null-test*/
    freeS(&test_str);
    /* TODO: implement _test_StrimBeginChar() */
    RETURN(NIL);
} /* _test_StrimBeginChar */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_trimChar(                                              /*M*/
    const str_t      object_,                                              /*-*/
    const char_t     char_,                                                /*-*/
    const trim_enum  trim_scope_ );                                        /*-*/

static void  _test_StrimChar( void ) {                                     /*F*/
    GO                                                            (UID(F0E1DB));
    _INIT_TEST_VARS;
    test_str = S_trimChar(test_str, '\0', TRIM_ALL);  /*null-test*/
    freeS(&test_str);
    /* TODO: implement _test_StrimChar() */
    RETURN(NIL);
} /* _test_StrimChar */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_trimEnd(                                               /*M*/
    const str_t  object_,                                                  /*-*/
    chars_t      trim_chars_ );                                            /*-*/

static void  _test_StrimEnd( void ) {                                      /*F*/
    GO                                                            (UID(F81FFA));
    _INIT_TEST_VARS;
    test_str = S_trimEnd(test_str, NULL);  /*null-test*/
    freeS(&test_str);
    /* TODO: implement _test_StrimEnd() */
    RETURN(NIL);
} /* _test_StrimEnd */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_trimEndChar(                                           /*M*/
    const str_t   object_,                                                 /*-*/
    const char_t  char_ );                                                 /*-*/

static void  _test_StrimEndChar( void ) {                                  /*F*/
    GO                                                            (UID(FF0789));
    _INIT_TEST_VARS;
    test_str = S_trimEndChar(test_str, '\0');  /*null-test*/
    freeS(&test_str);
    /* TODO: implement _test_StrimEndChar() */
    RETURN(NIL);
} /* _test_StrimEndChar */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_trimStr(                                               /*M*/
    const str_t      object_,                                              /*-*/
    chars_t          string_,                                              /*-*/
    const trim_enum  trim_scope_,                                          /*-*/
    const bool       ignore_case_ );                                       /*-*/

static void  _test_StrimStr( void ) {                                      /*F*/
    GO                                                            (UID(FF3259));
    _INIT_TEST_VARS;
    test_str = S_trimStr(test_str, NULL, TRIM_ALL, IGNORE_CASE);
    freeS(&test_str);
    /* TODO: implement _test_StrimStr() */
    RETURN(NIL);
} /* _test_StrimStr */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_unquote(                                               /*M*/
    const str_t  object_,                                                  /*-*/
    chars_t      quote_,                                                   /*-*/
    chars_t      replace_ );                                               /*-*/

static void  _test_Sunquote( void ) {                                      /*F*/
    GO                                                            (UID(FA452F));
    _INIT_TEST_VARS;
    test_str = S_unquote(test_str, NULL, NULL);  /*null-test*/
    freeS(&test_str);
    /* TODO: implement _test_Sunquote() */
    RETURN(NIL);
} /* _test_Sunquote */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_upperCase( const str_t  object_ );                     /*M*/

static void  _test_SupperCase( void ) {                                    /*F*/
    GO                                                            (UID(F3001D));
    _INIT_TEST_VARS;
    test_str = S_upperCase(test_str);  /*null-test*/
    freeS(&test_str);
    /* TODO: implement _test_SupperCase() */
    RETURN(NIL);
} /* _test_SupperCase */


/* -------------------------------------------------------------------------- */
/* Character Function Tests                                                   */
/* -------------------------------------------------------------------------- */


PUBLIC bool  appendnT(                                                     /*F*/
    new_chars_t*  realloc_var_,                                            /*-*/
    const int     count_,                                                  /*-*/
    chars_t       string_,                                                 /*-*/
    ... );                                                                 /*-*/

static void  _test_appendnT( void ) {                                      /*F*/
    GO                                                            (UID(F09AFB));
    appendnT(NULL, 0, NULL, NULL);  /*null-test*/
    RETURN(NIL);
} /* _test_appendnT */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_format_numeric(                                      /*F*/
    chars_t  number_,                                                      /*-*/
    int      decimal_places_ );                                            /*-*/

static void  _test_T_format_numeric( void ) {                              /*F*/
    GO                                                            (UID(F1B751));
#define _TEST( STRING_, DECIMAL_PLACES_, RESULT_ ) {                           \
        new_chars_t  result = T_format_numeric(STRING_, DECIMAL_PLACES_);       \
        if(STRCMP_T(CAST(chars_t, result), RESULT_) != 0) {                    \
            PRINTF_T(_T("FAIL T_format_numeric(\"%s\", %d) != \"%s\"")          \
                     _T(" returned \"%s\"\n"),                                 \
                     STRING_, DECIMAL_PLACES_, RESULT_, result);               \
        }                                                                      \
        freeT(&result);                                                        \
    }                                                                      /*#*/

    _TEST(_T("0"),           0, _T("0"));
    _TEST(_T("0"),           1, _T("0.0"));
    _TEST(_T("0"),           2, _T("0.00"));

    _TEST(_T("1"),           2, _T("1.00"));
    _TEST(_T("12"),          2, _T("12.00"));
    _TEST(_T("123"),         2, _T("123.00"));
    _TEST(_T("1234"),        2, _T("1,234.00"));
    _TEST(_T("12345"),       2, _T("12,345.00"));
    _TEST(_T("123456"),      2, _T("123,456.00"));
    _TEST(_T("1234567"),     2, _T("1,234,567.00"));
    _TEST(_T("12345678"),    2, _T("12,345,678.00"));
    _TEST(_T("123456789"),   2, _T("123,456,789.00"));
    _TEST(_T("1234567890"),  2, _T("1,234,567,890.00"));

    _TEST(_T("1."),          2, _T("1.00"));
    _TEST(_T("12."),         2, _T("12.00"));
    _TEST(_T("123."),        2, _T("123.00"));
    _TEST(_T("1234."),       2, _T("1,234.00"));
    _TEST(_T("12345."),      2, _T("12,345.00"));
    _TEST(_T("123456."),     2, _T("123,456.00"));
    _TEST(_T("1234567."),    2, _T("1,234,567.00"));
    _TEST(_T("12345678."),   2, _T("12,345,678.00"));
    _TEST(_T("123456789."),  2, _T("123,456,789.00"));
    _TEST(_T("1234567890."), 2, _T("1,234,567,890.00"));

    _TEST(_T("1."),          0, _T("1"));
    _TEST(_T("12."),         0, _T("12"));
    _TEST(_T("123."),        0, _T("123"));
    _TEST(_T("1234."),       0, _T("1,234"));

    _TEST(_T("-1"),          2, _T("-1.00"));
    _TEST(_T("-12"),         2, _T("-12.00"));
    _TEST(_T("-123"),        2, _T("-123.00"));
    _TEST(_T("-1234"),       2, _T("-1,234.00"));

    _TEST(_T("-1."),         2, _T("-1.00"));
    _TEST(_T("-12."),        2, _T("-12.00"));
    _TEST(_T("-123."),       2, _T("-123.00"));
    _TEST(_T("-1234."),      2, _T("-1,234.00"));

    _TEST(_T("-1."),         0, _T("-1"));
    _TEST(_T("-12."),        0, _T("-12"));
    _TEST(_T("-123."),       0, _T("-123"));
    _TEST(_T("-1234."),      0, _T("-1,234"));
#undef _TEST

    RETURN(NIL);
} /* _test_T_format_numeric */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_chars_n(                                             /*F*/
    chars_t       source_,                                                 /*-*/
    const size_t  count_ );                                                /*-*/

static void  _test_T_chars_n( void ) {                                     /*F*/
    GO                                                            (UID(FF8A65));
    new_chars_t  result = T_chars_n(NULL, 0);  /*null-test*/
    freeT(&result);
    /* TODO: implement _test_T_chars_n() */
    RETURN(NIL);
} /* _test_T_chars_n */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_bchars_n(                                            /*F*/
    const char*   source_,                                                 /*-*/
    const size_t  count_ );                                                /*-*/

static void  _test_T_bchars_n( void ) {                                    /*F*/
    GO                                                            (UID(F6F06C));
    new_chars_t  result = T_bchars_n(NULL, 0);  /*null-test*/
    freeT(&result);
    RETURN(NIL);
} /* _test_T_bchars_n */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_wchars_n(                                            /*F*/
    const wchar_t*  source_,                                               /*-*/
    const size_t    count_ );                                              /*-*/

static void  _test_T_wchars_n( void ) {                                    /*F*/
    GO                                                            (UID(F36D96));
    new_chars_t  result = T_wchars_n(NULL, 0);  /*null-test*/
    freeT(&result);
    RETURN(NIL);
} /* _test_T_wchars_n */


/* Twchars() is a macro */
static void  _test_Twchars( void ) {                                       /*F*/
    GO                                                            (UID(F3A3B4));
    new_chars_t  result = Twchars(NULL);  /*null-test*/
    freeT(&result);
    RETURN(NIL);
} /* _test_T_wchars_n */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_decode_base64( chars_t  string_ );                   /*F*/

static void  _test_T_decode_base64( void ) {                               /*F*/
    GO                                                            (UID(FABDF3));
    new_chars_t  result = T_decode_base64(NULL);  /*null-test*/
    freeT(&result);
    /* TODO: implement _test_T_decode_base64() */
    RETURN(NIL);
} /* _test_T_decode_base64 */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_encode_base64( chars_t  string_ );                   /*F*/

static void  _test_T_encode_base64( void ) {                               /*F*/
    GO                                                            (UID(FC220A));
    new_chars_t  result = T_encode_base64(NULL);  /*null-test*/
    freeT(&result);
    /* TODO: implement _test_T_encode_base64() */
    RETURN(NIL);
} /* _test_T_encode_base64 */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_first(                                               /*F*/
    chars_t       string_,                                                 /*-*/
    const size_t  length_ );                                               /*-*/

static void  _test_T_first( void ) {                                       /*F*/
    GO                                                            (UID(F43980));
    new_chars_t  result = T_first(NULL, 0);  /*null-test*/
    freeT(&result);
    RETURN(NIL);
} /* _test_T_first */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_offset(                                              /*F*/
    chars_t       string_,                                                 /*-*/
    const size_t  offset_ );                                               /*-*/

static void  _test_T_offset( void ) {                                      /*F*/
    GO                                                            (UID(FF66A7));
    new_chars_t  result = T_offset(NULL, 0);  /*null-test*/
    freeT(&result);
    RETURN(NIL);
} /* _test_T_offset */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_substr(                                              /*F*/
    chars_t       string_,                                                 /*-*/
    const size_t  offset_,                                                 /*-*/
    const size_t  count_ );                                                /*-*/

static void  _test_T_substr( void ) {                                      /*F*/
    GO                                                            (UID(F21C94));
    new_chars_t  result = T_substr(NULL, 0, 0);  /*null-test*/
    freeT(&result);
    RETURN(NIL);
} /* _test_T_substr */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_double(                                              /*F*/
    long double  value_,                                                   /*-*/
    const int    decimal_places_ );                                        /*-*/

static void  _test_T_double( void ) {                                      /*F*/
    GO                                                            (UID(F5A0C6));
    {
        new_chars_t  result = T_double(0, 0);  /*null-test*/
        /* TODO: test_T_double(): result is not compared to anything */
        freeT(&result);
    }

    {
        struct _test_t {
            long double  value_;                                   /* _test_t */
            int          decimal_places_;                          /* _test_t */
            chars_t      result;                                   /* _test_t */
        }
        test[] = {

            /* value_     decimal_places_     result */

            /* 999 trillion: the highest integer */
            /* that retained precision on win32  */
            { 999999999999999.0,  0, _T("999999999999999")    },
            { 999999999999999.1,  1, _T("999999999999999.1")  },
            { -999999999999999.0, 0, _T("-999999999999999")   },
            { -999999999999999.1, 1, _T("-999999999999999.1") },

            /* test_str zero */
            { 0.0, 0, _T("0") },
            { 0.0, 1, _T("0.0") },
            { 0.0, 10, _T("0.0000000000") },
            { 0.0, 20, _T("0.00000000000000000000") },

            /* test_str diminishing value (positive) */
            { 0.1, 1, _T("0.1") },
            { 0.01, 2, _T("0.01") },
            { 0.001, 3, _T("0.001") },
            { 0.0001, 4, _T("0.0001") },
            { 0.00001, 5, _T("0.00001") },
            { 0.000001, 6, _T("0.000001") },
            { 0.0000001, 7, _T("0.0000001") },
            { 0.00000001, 8, _T("0.00000001") },
            { 0.000000001, 9, _T("0.000000001") },
            { 0.0000000001, 10, _T("0.0000000001") },

            /* Win32 FAIL */
            /* { 0.00000000001,    11, _T("0.00000000001")    },*/
            /* { 0.000000000001,   12, _T("0.000000000001")   },*/
            /* { 0.0000000000001,  13, _T("0.0000000000001")  },*/
            /* { 0.00000000000001, 14, _T("0.00000000000001") },*/

            { 0.000000000000001, 15, _T("0.000000000000001") },
            { 0.0000000000000001, 16, _T("0.0000000000000001") },
            { 0.00000000000000001, 17, _T("0.00000000000000001") },
            { 0.000000000000000001, 18, _T("0.000000000000000001") },
            { 0.0000000000000000001, 19, _T("0.0000000000000000001") },
            { 0.00000000000000000001, 20, _T("0.00000000000000000001") },
            { 0.000000000000000000001, 21, _T("0.000000000000000000001") },
            { 0.0000000000000000000001, 22, _T("0.0000000000000000000001") },
            { 0.00000000000000000000001, 23, _T("0.00000000000000000000001") },
            {
                0.000000000000000000000001, 24,
                _T("0.000000000000000000000001")
            },
            {
                0.0000000000000000000000001, 25,
                _T("0.0000000000000000000000001")
            },
            {
                0.00000000000000000000000001, 26,
                _T("0.00000000000000000000000001")
            },
            {
                0.000000000000000000000000001, 27,
                _T("0.000000000000000000000000001")
            },
            {
                0.0000000000000000000000000001, 28,
                _T("0.0000000000000000000000000001")
            },
            {
                0.00000000000000000000000000001, 29,
                _T("0.00000000000000000000000000001")
            },
            {
                0.000000000000000000000000000001, 30,
                _T("0.000000000000000000000000000001")
            },

            /* test_str diminishing value (negative) */
            { -0.1, 1, _T("-0.1") },
            { -0.01, 2, _T("-0.01") },
            { -0.001, 3, _T("-0.001") },
            { -0.0001, 4, _T("-0.0001") },
            { -0.00001, 5, _T("-0.00001") },
            { -0.000001, 6, _T("-0.000001") },
            { -0.0000001, 7, _T("-0.0000001") },
            { -0.00000001, 8, _T("-0.00000001") },
            { -0.000000001, 9, _T("-0.000000001") },
            { -0.0000000001, 10, _T("-0.0000000001") },

            /* {   -0.00000000001, 11  */
            /* _T("-0.00000000001") }, */   /* Win32 FAIL */

            /* {   -0.000000000001, 12, */
            /* _T("-0.000000000001") }, */   /* Win32 FAIL */

            /* {   -0.0000000000001, 13, */
            /* _T("-0.0000000000001") }, */   /* Win32 FAIL */

            /* {   -0.00000000000001, 14, */
            /* _T("-0.00000000000001") }, */   /* Win32 FAIL */

            { -0.000000000000001, 15, _T("-0.000000000000001") },
            { -0.0000000000000001, 16, _T("-0.0000000000000001") },
            { -0.00000000000000001, 17, _T("-0.00000000000000001") },
            { -0.000000000000000001, 18, _T("-0.000000000000000001") },
            { -0.0000000000000000001, 19, _T("-0.0000000000000000001") },
            { -0.00000000000000000001, 20, _T("-0.00000000000000000001") },
            { -0.000000000000000000001, 21, _T("-0.000000000000000000001") },
            { -0.0000000000000000000001, 22, _T("-0.0000000000000000000001") },
            {
                -0.00000000000000000000001, 23,
                _T("-0.00000000000000000000001")
            },
            {
                -0.000000000000000000000001, 24,
                _T("-0.000000000000000000000001")
            },
            {
                -0.0000000000000000000000001, 25,
                _T("-0.0000000000000000000000001")
            },
            {
                -0.00000000000000000000000001, 26,
                _T("-0.00000000000000000000000001")
            },
            {
                -0.000000000000000000000000001, 27,
                _T("-0.000000000000000000000000001")
            },
            {
                -0.0000000000000000000000000001, 28,
                _T("-0.0000000000000000000000000001")
            },
            {
                -0.00000000000000000000000000001, 29,
                _T("-0.00000000000000000000000000001")
            },
            {
                -0.000000000000000000000000000001, 30,
                _T("-0.000000000000000000000000000001")
            },

            /* miscellaneous */

            /* FAIL {     0.00000000000000000001,  0,  */
            /* FAIL   _T("0.000000000000000000001") }, */

            /* FAIL {     123456789012345.99999, 1, */
            /* FAIL   _T("123456789012345.9") },    */

            /* FAIL {     123456789012345.99999, 2, */
            /* FAIL   _T("123456789012345.9") },    */

            { 0.01,                 2, _T("0.01") },
            { 0.01,                20, _T("0.01000000000000000000") },
            { 0.1,                  1, _T("0.1") },
            { 0.11999,              2, _T("0.11") },
            { 0.11999,              3, _T("0.119") },
            { 0.1199999999,         3, _T("0.119") },
            { 1.0,                  0, _T("1") },
            { 1.0,                  1, _T("1.0") },
            { 1.0,                 10, _T("1.0000000000") },
            { 123456789012345.99,   0, _T("123456789012345") },
            { 123456789012345.99,   1, _T("123456789012345.9") },
            { -123456789012345.99,  0, _T("-123456789012345") },
            { -123456789012345.99,  1, _T("-123456789012345.9") },
            { 9.0,                  0, _T("9") },
            { 9.0,                  1, _T("9.0") },
            { 9.0,                 10, _T("9.0000000000") },
            { 99e-2,                2, _T("0.99") },
            { -1.0,                 0, _T("-1") },
            { -1.0,                 1, _T("-1.0") },
            { -1.0,                10, _T("-1.0000000000") },
            { -1.0,                20, _T("-1.00000000000000000000") },
            /*
                0
                0.0
                0.01
                0.02
                0.2
                0000
                0x1p-1074
                -0x1p-1074
                1
                -1
                1.0
                -1.0
                10
                10.0
                100
                100.0
                100.01
                10000
                100000
                -12.0
                12000
                1200000
                123.01
                126.71
                16
                2
                -2
                200
                2000
                3
                322.5
                3225000000000000000
                -323
                4
                -4
                494
                5
                -5
                5.5
                53
                55
                6
            */

            /* NULL result terminates loop */
            { 0, 0, NULL }
        };

        int  i = 0;
        while (test[i].result != NULL) {
            long double  value_          = test[i].value_;
            const int    decimal_places_ = test[i].decimal_places_;
            chars_t      check           = test[i].result;
            new_chars_t  ret_str         = T_double(value_, decimal_places_);

            if (STRCMP_T(check, ret_str) != 0) {
                PRINTF_T(_T("\r\n") _T("Failed: T_double(%Lf, %d)")
                         _T(" != '%s' (returned '%s')"),
                         value_, decimal_places_, check, ret_str);
            }
            i++;

            freeT(&ret_str);
        }
    }
    RETURN(NIL);
} /* _test_T_double */


/* -------------------------------------------------------------------------- */


PUBLIC new_str_t  S_hex(                                                   /*F*/
    const uint32_t  value_,                                                /*-*/
    const size_t    minimum_length_ );                                     /*-*/


static void  _test_Shex( void ) {                                          /*F*/
    GO                                                            (UID(F25EFD));
    _CHECK_STR_INIT(S_hex(0,          8), _T("00000000"));   /*null-test*/
    _CHECK_STR_INIT(S_hex(1,          8), _T("00000001"));
    _CHECK_STR_INIT(S_hex(10,         8), _T("0000000a"));
    _CHECK_STR_INIT(S_hex(16,         8), _T("00000010"));
    _CHECK_STR_INIT(S_hex(1000,       8), _T("000003e8"));
    _CHECK_STR_INIT(S_hex(268435456,  8), _T("10000000"));
    _CHECK_STR_INIT(S_hex(1048576000, 8), _T("3e800000"));
    _CHECK_STR_INIT(S_hex(4294967295, 8), _T("ffffffff"));
    RETURN(NIL);
} /* _test_Shex */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_int( const int  value_ );                            /*F*/

static void  _test_T_int( void ) {                                         /*F*/
    GO                                                            (UID(F442A2));
    new_chars_t  result = T_int(0);  /*null-test*/
    freeT(&result);
    /* TODO: implement _test_T_int() */
    RETURN(NIL);
} /* _test_T_int */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_join(                                                /*F*/
    chars_t  terminator_,                                                  /*-*/
    chars_t  string1_,                                                     /*-*/
    ... );                                                                 /*-*/

static void  _test_T_join( void ) {                                        /*F*/
    GO                                                            (UID(F7B8CE));
    new_chars_t  result = T_join(TT, NULL, NULL, TT);  /*null-test*/
    freeT(&result);
    RETURN(NIL);
} /* _test_T_join */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_last(                                                /*F*/
    chars_t       string_,                                                 /*-*/
    const size_t  length_ );                                               /*-*/

static void  _test_T_last( void ) {                                        /*F*/
    GO                                                            (UID(FAB03C));
    new_chars_t  result = T_last(NULL, 0);  /*null-test*/
    freeT(&result);
    RETURN(NIL);
} /* _test_T_last */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_malloc_id(                                           /*F*/
    const size_t  char_len_,                                               /*-*/
    chars_t       filename_,                                               /*-*/
    const int     source_line_ );                                          /*-*/

static void  _test_T_malloc_id( void ) {                                   /*F*/
    GO                                                            (UID(FEB5ED));
    new_chars_t  result = T_malloc_id(0, NULL, 0);  /*null-test*/
    freeT(&result);
    RETURN(NIL);
} /* _test_T_malloc_id */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_realloc_id(                                          /*F*/
    new_chars_t   string_,                                                 /*-*/
    const size_t  char_len_,                                               /*-*/
    chars_t       filename_,                                               /*-*/
    const int     source_line_ );                                          /*-*/

static void  _test_T_realloc_id( void ) {                                  /*F*/
    GO                                                            (UID(F641CF));
    new_chars_t  result = T_realloc_id(NULL, 0, NULL, 0);  /*null-test*/
    freeT(&result);
    RETURN(NIL);
} /* _test_T_realloc_id */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  formatT(                                               /*F*/
    chars_t  format_,                                                      /*-*/
    ... );                                                                 /*-*/

static void  _test_formatT( void ) {                                       /*F*/
    GO                                                            (UID(FC34FA));
    new_chars_t  result = NULL;

    result = formatT(NULL);  /*null-test*/
    ASSERT(result == NULL, UID(E1E8EC));

    result = formatT(_T("A"));
    ASSERT(STRCMP_T(result, _T("A")) == 0, UID(EEA580));
    freeT(&result);

    result = formatT(_T("Hello World!"));
    ASSERT(STRCMP_T(result, _T("Hello World!")) == 0, UID(EDF3D7));
    freeT(&result);

    result = formatT(_T("%s"), _T("Hello World!"));
    ASSERT(STRCMP_T(result, _T("Hello World!")) == 0, UID(E66151));
    freeT(&result);

    result = formatT(_T("Hello %s!"), _T("World"));
    ASSERT(STRCMP_T(result, _T("Hello World!")) == 0, UID(E60D91));
    freeT(&result);

    result = formatT(_T("Hello %s%s"), _T("World"), _T("!"));
    ASSERT(STRCMP_T(result, _T("Hello World!")) == 0, UID(E0CEB8));
    freeT(&result);

    result = formatT(
                 _T("int ranges from %d to %d"), -2147483647, 2147483647);

    ASSERT(STRCMP_T(
               result,
               _T("int ranges from -2147483647 to 2147483647")) == 0,
           UID(E2CC63));

    freeT(&result);

    result = formatT(_T("0x%08X"), 0);
    ASSERT(STRCMP_T(result, _T("0x00000000")) == 0, UID(E8AB46));
    freeT(&result);

    result = formatT(_T("0x%08X"), 0xFFFFFFFF);
    ASSERT(STRCMP_T(result, _T("0xFFFFFFFF")) == 0, UID(E61686));
    freeT(&result);

    RETURN(NIL);
} /* _test_formatT */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_repeat(                                              /*F*/
    chars_t    string_,     /* String to be repeated.                  */  /*-*/
    const int  count_,      /* Max. # of times string can be repeated. */  /*-*/
    const int  max_len_ );  /* Max. length of the returned string.     */  /*-*/

static void  _test_T_repeat( void ) {                                      /*F*/
    GO                                                            (UID(F9CB2A));
    new_chars_t  result = T_repeat(NULL, 0, 0);  /*null-test*/
    freeT(&result);
    RETURN(NIL);
} /* _test_T_repeat */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_replace(                                             /*F*/
    chars_t     string_,         /* string being searched     */           /*-*/
    chars_t     find_,           /* string to find            */           /*-*/
    chars_t     replace_,        /* replacement string        */           /*-*/
    const bool  ignore_case_ );  /* MATCH_CASE /  IGNORE_CASE */           /*-*/

static void  _test_T_replace( void ) {                                     /*F*/
    GO                                                            (UID(F6888B));
    struct _test_t {
        chars_t  string;                                           /* _test_t */
        chars_t  find;                                             /* _test_t */
        chars_t  replace;                                          /* _test_t */
        bool     ignore_case;                                      /* _test_t */
        chars_t  check_val;                                        /* _test_t */
    }
    test[] = {

        /*       string_  find_ replace_  ignore_case_ */
        /*00*/ { NULL, NULL, NULL, IGNORE_CASE, _T("") },
        /*01*/ { NULL, NULL, NULL, MATCH_CASE,  _T("") },
        /* null-test^ */

        /*02*/ { NULL, NULL,      _T("ABC"), IGNORE_CASE, _T("ABC") },
        /*03*/ { NULL, NULL,      _T("ABC"), MATCH_CASE,  _T("ABC") },
        /*04*/ { NULL, _T("ABC"), NULL,      IGNORE_CASE, _T("") },
        /*05*/ { NULL, _T("ABC"), NULL,      MATCH_CASE,  _T("") },
        /*06*/ { NULL, _T("ABC"), _T("123"), IGNORE_CASE, _T("") },
        /*07*/ { NULL, _T("ABC"), _T("123"), MATCH_CASE,  _T("") },

        {
            /*08*/
            _T("ABC"), _T("A"), _T("123"), IGNORE_CASE, _T("123BC")
        },
        {
            /*09*/
            _T("ABC"), _T("A"), _T("123"), MATCH_CASE, _T("123BC")
        },
        {
            /*10*/
            _T("ABC"), _T("ABC"), _T("123"), IGNORE_CASE, _T("123")
        },
        {
            /*11*/
            _T("ABC"), _T("ABC"), _T("123"), MATCH_CASE, _T("123")
        },
        {
            /*12*/
            _T("ABC"), _T("B"), _T("123"), IGNORE_CASE, _T("A123C")
        },
        {
            /*13*/
            _T("ABC"), _T("B"), _T("123"), MATCH_CASE, _T("A123C")
        },
        {
            /*14*/
            _T("ABC"), _T("C"), _T("123"), IGNORE_CASE, _T("AB123")
        },
        {
            /*15*/
            _T("ABC"), _T("C"), _T("123"), MATCH_CASE, _T("AB123")
        },
        {
            /*16*/
            _T("ABC"), _T("a"), _T("123"), IGNORE_CASE, _T("123BC")
        },
        {
            /*17*/
            _T("ABC"), _T("a"), _T("123"), MATCH_CASE, _T("ABC")
        },
        {
            /*18*/
            _T("ABC"), _T("b"), _T("123"), IGNORE_CASE, _T("A123C")
        },
        {
            /*19*/
            _T("ABC"), _T("b"), _T("123"), MATCH_CASE, _T("ABC")
        },
        {
            /*20*/
            _T("ABC"), _T("c"), _T("123"), IGNORE_CASE, _T("AB123")
        },
        {
            /*21*/
            _T("ABC"), _T("c"), _T("123"), MATCH_CASE, _T("ABC")
        },

        /* test_str replacing strings with blanks: */

        { _T("ABC"),    _T("A"),  NULL,   MATCH_CASE,  _T("BC") },     /*22*/
        { _T("ABC"),    _T("A"),  _T(""), MATCH_CASE,  _T("BC") },     /*23*/
        { _T("ABC"),    _T("B"),  NULL,   MATCH_CASE,  _T("AC") },     /*24*/
        { _T("ABC"),    _T("B"),  _T(""), MATCH_CASE,  _T("AC") },     /*25*/
        { _T("ABC"),    _T("C"),  NULL,   MATCH_CASE,  _T("AB") },     /*26*/
        { _T("ABC"),    _T("C"),  _T(""), MATCH_CASE,  _T("AB") },     /*27*/
        { _T("ABC"),    _T("a"),  NULL,   IGNORE_CASE, _T("BC") },     /*28*/
        { _T("ABC"),    _T("a"),  _T(""), IGNORE_CASE, _T("BC") },     /*29*/
        { _T("ABC"),    _T("b"),  NULL,   IGNORE_CASE, _T("AC") },     /*30*/
        { _T("ABC"),    _T("b"),  _T(""), IGNORE_CASE, _T("AC") },     /*31*/
        { _T("ABC"),    _T("c"),  NULL,   IGNORE_CASE, _T("AB") },     /*32*/
        { _T("ABC"),    _T("c"),  _T(""), IGNORE_CASE, _T("AB") },     /*33*/
        { _T("AaBbCc"), _T("AA"), NULL,   IGNORE_CASE, _T("BbCc") },   /*34*/
        { _T("AaBbCc"), _T("AA"), _T(""), IGNORE_CASE, _T("BbCc") },   /*35*/
        { _T("AaBbCc"), _T("Aa"), NULL,   MATCH_CASE,  _T("BbCc") },   /*36*/
        { _T("AaBbCc"), _T("Aa"), _T(""), MATCH_CASE,  _T("BbCc") },   /*37*/
        { _T("AaBbCc"), _T("BB"), NULL,   IGNORE_CASE, _T("AaCc") },   /*38*/
        { _T("AaBbCc"), _T("BB"), _T(""), IGNORE_CASE, _T("AaCc") },   /*39*/
        { _T("AaBbCc"), _T("Bb"), NULL,   MATCH_CASE,  _T("AaCc") },   /*40*/
        { _T("AaBbCc"), _T("Bb"), _T(""), MATCH_CASE,  _T("AaCc") },   /*41*/
        { _T("AaBbCc"), _T("CC"), NULL,   IGNORE_CASE, _T("AaBb") },   /*42*/
        { _T("AaBbCc"), _T("CC"), _T(""), IGNORE_CASE, _T("AaBb") },   /*43*/
        { _T("AaBbCc"), _T("Cc"), NULL,   MATCH_CASE,  _T("AaBb") },   /*44*/
        { _T("AaBbCc"), _T("Cc"), _T(""), MATCH_CASE,  _T("AaBb") },   /*45*/

        { NULL, NULL, NULL, IGNORE_CASE, NULL }  /* end */
    };

    {
        int  i = 0;
        while (test[i].check_val != NULL) {
            chars_t      string      = test[i].string;
            chars_t      find        = test[i].find;
            chars_t      replace     = test[i].replace;
            const bool   ignore_case = test[i].ignore_case;
            chars_t      check_val   = test[i].check_val;
            new_chars_t  result = T_replace(string, find, replace, ignore_case);

            _assert(STRCMP_T(result, check_val) == 0);
            freeT(&result);
            i++;
        }
    }
    RETURN(NIL);
} /* _test_T_replace */


/* -------------------------------------------------------------------------- */


PUBLIC void  set_inT(                                                      /*F*/
    new_chars_t*  realloc_var_,                                            /*-*/
    chars_t       new_string_ );                                           /*-*/

static void  _test_setT( void ) {                                          /*F*/
    GO                                                            (UID(F2453C));
    set_inT(NULL, NULL);  /*null-test*/
    RETURN(NIL);
} /* _test_setT */


/* -------------------------------------------------------------------------- */


PUBLIC void  set_default_inT(                                              /*F*/
    new_chars_t*  realloc_var_,                                            /*-*/
    chars_t       new_string_,                                             /*-*/
    chars_t       default_ );                                              /*-*/

static void  _test_set_defaultT( void ) {                                  /*F*/
    GO                                                            (UID(FC7CD7));
    set_default_inT(NULL, NULL, NULL);  /*null-test*/
    RETURN(NIL);
} /* _test_set_defaultT */


/* -------------------------------------------------------------------------- */


PUBLIC new_bytes_t  to_bytesT(                                             /*F*/
    chars_t            string_,                                            /*-*/
    chars_format_enum  string_format_ );                                   /*-*/

static void  _test_to_bytesT( void ) {                                     /*F*/
    GO                                                            (UID(F40C00));
    to_bytesT(NULL, DEFAULT);  /*null-test*/
    RETURN(NIL);
} /* _test_to_bytesT */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_get_token_xt(                                        /*F*/
    chars_t       list_,                                                   /*-*/
    const size_t  index_,                                                  /*-*/
    chars_t       delimiter_,                                              /*-*/
    const bool    ignore_end_delimiter_ );                                 /*-*/

static void  _test_T_get_token_xt( void ) {                                /*F*/
    GO                                                            (UID(FE754F));
    new_chars_t  result = T_get_token_xt(NULL, 0, NULL, false);
    freeT(&result);
    RETURN(NIL);
} /* _test_T_get_token_xt */


/* -------------------------------------------------------------------------- */


#if defined UNFINISHED_CODE
PUBLIC new_chars_t  T_tokenize(                                            /*F*/
    chars_t  string_,                                                      /*-*/
    chars_t  delimiter_ );                                                 /*-*/

static void  _test_T_tokenize( void ) {                                    /*F*/
    GO                                                            (UID(F55811));
    new_chars_t  result = T_tokenize(NULL, NULL);  /*null-test*/
    freeT(&result);
    RETURN(NIL);
} /* _test_T_tokenize */
#endif                                                     /* UNFINISHED_CODE */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_set_token(                                           /*F*/
    chars_t       list_,                                                   /*-*/
    const size_t  index_,                                                  /*-*/
    chars_t       token_,                                                  /*-*/
    chars_t       delimiter_ );                                            /*-*/

static void  _test_T_set_token( void ) {                                   /*F*/
    GO                                                            (UID(FC0652));
    new_chars_t  result = T_set_token(NULL, 0, NULL, NULL);  /*null-test*/
    freeT(&result);

    /* TODO: implement _test_T_set_token() */
    RETURN(NIL);
} /* _test_T_set_token */


/* -------------------------------------------------------------------------- */


PUBLIC new_bchars_t  to_utf8T( chars_t  string_ );                         /*F*/

static void  _test_chars_to_utf8( void ) {                                 /*F*/
    GO                                                            (UID(FC1620));
    new_bchars_t  result = to_utf8T(NULL);  /*null-test*/
    freeA(&result);
    RETURN(NIL);
} /* _test_chars_to_utf8 */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_uint( const uint32_t  value_ );                      /*F*/

static void  _test_uT_int( void ) {                                        /*F*/
    GO                                                            (UID(FA3511));
    new_chars_t  result = T_uint(0);  /*null-test*/
    freeT(&result);
    RETURN(NIL);
} /* _test_uT_int */


/* -------------------------------------------------------------------------- */


PUBLIC new_chars_t  T_uint64( const uint64_t  value_ );                    /*F*/

static void  _test_T_uint64( void ) {                                      /*F*/
    GO                                                            (UID(FB99A6));
    struct _test_t {
        uint64_t  val;                                             /* _test_t */
        chars_t   check_val;                                       /* _test_t */
    }
    test[] = {
        { 0, _T("0") },  /*null-test*/
        { 127, _T("127") },
        { 128, _T("128") },
        { 255, _T("255") },
        { 256, _T("256") },
        { 32767, _T("32767") },
        { 32768, _T("32768") },
        { 65535, _T("65535") },
        { 65536, _T("65536") },
        { 2147483647, _T("2147483647") },
        { 2147483648, _T("2147483648") },
        { 4294967295, _T("4294967295") },
        { 4294967296, _T("4294967296") },
        { 9223372036854775807, _T("9223372036854775807") },
        { 9223372036854775808U, _T("9223372036854775808") },
        { 18446744073709551615U, _T("18446744073709551615") },

        { 1, _T("1") },
        { 10, _T("10") },
        { 100, _T("100") },
        { 1000, _T("1000") },
        { 10000, _T("10000") },
        { 100000, _T("100000") },
        { 1000000, _T("1000000") },
        { 10000000, _T("10000000") },
        { 100000000, _T("100000000") },
        { 1000000000, _T("1000000000") },
        { 10000000000, _T("10000000000") },
        { 100000000000, _T("100000000000") },
        { 1000000000000, _T("1000000000000") },
        { 10000000000000, _T("10000000000000") },
        { 100000000000000, _T("100000000000000") },
        { 1000000000000000, _T("1000000000000000") },
        { 10000000000000000, _T("10000000000000000") },
        { 100000000000000000, _T("100000000000000000") },
        { 1000000000000000000, _T("1000000000000000000") },
        { 10000000000000000000U, _T("10000000000000000000") },

        { 9, _T("9") },
        { 99, _T("99") },
        { 999, _T("999") },
        { 9999, _T("9999") },
        { 99999, _T("99999") },
        { 999999, _T("999999") },
        { 9999999, _T("9999999") },
        { 99999999, _T("99999999") },
        { 999999999, _T("999999999") },
        { 9999999999, _T("9999999999") },
        { 99999999999, _T("99999999999") },
        { 999999999999, _T("999999999999") },
        { 9999999999999, _T("9999999999999") },
        { 99999999999999, _T("99999999999999") },
        { 999999999999999, _T("999999999999999") },
        { 9999999999999999, _T("9999999999999999") },
        { 99999999999999999, _T("99999999999999999") },
        { 999999999999999999, _T("999999999999999999") },
        { 9999999999999999999U, _T("9999999999999999999") },

        { 0, NULL }
    };

    {
        int  i = 0;
        while (test[i].check_val != NULL) {
            const uint64_t  val       = test[i].val;
            chars_t         check_val = test[i].check_val;
            new_chars_t     result    = T_uint64(val);

            _assert(STRCMP_T(result, check_val) == 0);
            freeT(&result);
            i++;
        }
    }
    RETURN(NIL);
} /* _test_T_uint64 */


/* -------------------------------------------------------------------------- */


PUBLIC new_bchars_t  utf8_of_wide( const wchar_t*  string_ );              /*F*/

static void  _test_utf8_from_wide( void ) {                                /*F*/
    GO                                                            (UID(FCF052));
    /* TODO: fix SEGFAULT in _test_utf8_from_wide() */
    /* utf8_of_wide(NULL);*/  /*null-test*/

    /* TODO: implement _test_utf8_from_wide() */
    RETURN(NIL);
} /* _test_utf8_from_wide */


/* -------------------------------------------------------------------------- */

PUBLIC size_t  utf8_len( chars_t  string_ );                               /*F*/

static void  _test_utf8_len( void ) {                                      /*F*/
    GO                                                            (UID(FD56B5));
    /* TODO: implement _test_utf8_len() */
    RETURN(NIL);
} /* _test_utf8_len */


/* -------------------------------------------------------------------------- */


PUBLIC new_wchars_t  wide_of_utf8( const char*  string_ );                 /*F*/

static void  _test_wchars_from_utf8( void ) {                              /*F*/
    GO                                                            (UID(F6D799));
    /* TODO: fix SEGFAULT in _test_wchars_from_utf8() */
    /* wide_of_utf8(NULL); */  /*null-test*/

    /* TODO: implement _test_wchars_from_utf8() */
    RETURN(NIL);
} /* _test_wchars_from_utf8 */


/* -------------------------------------------------------------------------- */


PUBLIC void  lower_in_T( char_t*  string_ref_ );                           /*F*/

static void  _test_lower_in_T( void ) {                                    /*F*/
    GO                                                            (UID(FC76BC));
    lower_in_T(NULL);  /*null-test*/
    RETURN(NIL);
} /* _test_lower_in_T */


/* -------------------------------------------------------------------------- */


PUBLIC void  remove_extra_spaces_in_T( char_t*  string_ref_ );             /*F*/

static void  _test_remove_extra_spaces_in_T( void ) {                      /*F*/
    GO                                                            (UID(FABF7B));
    remove_extra_spaces_in_T(NULL);  /*null-test*/
    RETURN(NIL);
} /* _test_remove_extra_spaces_in_T */


/* -------------------------------------------------------------------------- */


PUBLIC void  replace_in_T(                                                 /*F*/
    new_chars_t*  realloc_var_,                                            /*-*/
    chars_t       find_,                                                   /*-*/
    chars_t       replace_ );                                              /*-*/

static void  _test_replace_in_T( void ) {                                  /*F*/
    GO                                                            (UID(F706CF));
    replace_in_T(NULL, NULL, NULL);  /*null-test*/
    RETURN(NIL);
} /* _test_replace_in_T */


/* -------------------------------------------------------------------------- */


PUBLIC void  title_in_T( char_t*  string_ref_ );                           /*F*/

static void  _test_title_in_T( void ) {                                    /*F*/
    GO                                                            (UID(F29C6C));
    title_in_T(NULL);  /*null-test*/
    RETURN(NIL);
} /* title_in_T */


/* -------------------------------------------------------------------------- */


PUBLIC void  trim_in_T( char_t*  string_ref_ );                            /*F*/

static void  _test_trim_in_T( void ) {                                     /*F*/
    GO                                                            (UID(F8B4BC));
    trim_in_T(NULL);  /*null-test*/
    RETURN(NIL);
} /* _test_trim_in_T */


/* -------------------------------------------------------------------------- */


PUBLIC void  trim4_in_T(                                                   /*F*/
    char_t*     string_ref_,                                               /*-*/
    chars_t     trim_chars_,                                               /*-*/
    const bool  trim_begin_,                                               /*-*/
    const bool  trim_end_ );                                               /*-*/

static void  _test_trim4_in_T( void ) {                                    /*F*/
    GO                                                            (UID(F34D79));
    trim4_in_T(NULL, NULL, false, false);  /*null-test*/
    RETURN(NIL);
} /* _test_trim4_in_T */


/* -------------------------------------------------------------------------- */


PUBLIC void  upper_in_T( char_t*  string_ref_ );                           /*F*/

static void  _test_upper_in_T( void ) {                                    /*F*/
    GO                                                            (UID(FA8414));
    upper_in_T(NULL);  /*null-test*/
    RETURN(NIL);
} /* _test_upper_in_T */


/* -------------------------------------------------------------------------- */


PUBLIC bool  begins3T(                                                     /*F*/
    chars_t     main_str_,                                                 /*-*/
    chars_t     find_str_,                                                 /*-*/
    const bool  ignore_case_ );                                            /*-*/

static void  _test_begins3T( void ) {                                      /*F*/
    GO                                                            (UID(F13B2E));
    begins3T(NULL, NULL, IGNORE_CASE);  /*null-test*/

    _assert(begins3T(_T("abc"), _T("a"),     MATCH_CASE) == true);
    _assert(begins3T(_T("abc"), _T("ab"),    MATCH_CASE) == true);
    _assert(begins3T(_T("abc"), _T("abc"),   MATCH_CASE) == true);
    _assert(begins3T(_T("abc"), _T("A"),     MATCH_CASE) == false);
    _assert(begins3T(_T("abc"), _T("aarrB"), MATCH_CASE) == false);
    _assert(begins3T(_T("abc"), _T("ABC"),   MATCH_CASE) == false);
    _assert(begins3T(_T("abc"), _T("abcd"),  MATCH_CASE) == false);
    _assert(begins3T(_T("abc"), _T("b"),     MATCH_CASE) == false);
    _assert(begins3T(_T("abc"), _T("bc"),    MATCH_CASE) == false);
    _assert(begins3T(_T("abc"), _T("bcd"),   MATCH_CASE) == false);
    _assert(begins3T(_T("def"), _T("D"),     MATCH_CASE) == false);
    _assert(begins3T(_T("def"), _T("DE"),    MATCH_CASE) == false);
    _assert(begins3T(_T("def"), _T("DEF"),   MATCH_CASE) == false);
    _assert(begins3T(_T("def"), _T("DEFG"),  MATCH_CASE) == false);

    _assert(begins3T(BLANK, NULL,  IGNORE_CASE) == true);
    _assert(begins3T(BLANK, NULL,  MATCH_CASE)  == true);
    _assert(begins3T(NULL,  BLANK, IGNORE_CASE) == true);
    _assert(begins3T(NULL,  BLANK, MATCH_CASE)  == true);
    _assert(begins3T(NULL,  NULL,  IGNORE_CASE) == true);
    _assert(begins3T(NULL,  NULL,  MATCH_CASE)  == true);

    RETURN(NIL);
} /* _test_begins3T */


/* -------------------------------------------------------------------------- */


PUBLIC bool  containsT(                                                    /*F*/
    chars_t       string_,                                                 /*-*/
    chars_t       substring_,                                              /*-*/
    const bool    ignore_case_,                                            /*-*/
    const size_t  string_len_,                                             /*-*/
    const size_t  substring_len_ );                                        /*-*/

static void  _test_containsT( void ) {                                     /*F*/
    GO                                                            (UID(F47B3B));
    containsT(NULL, NULL, IGNORE_CASE, 0, 0);  /*null-test*/

    /* TODO: implement _test_containsT() */
    RETURN(NIL);
} /* _test_containsT */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  countT(                                                     /*F*/
    chars_t       main_str_,                                               /*-*/
    chars_t       find_str_,                                               /*-*/
    const size_t  offset_,                                                 /*-*/
    const bool    ignore_case_,                                            /*-*/
    const bool    reverse_,                                                /*-*/
    const size_t  main_len_,                                               /*-*/
    const size_t  find_len_,                                               /*-*/
    const size_t  max_count_,                                              /*-*/
    size_t*       location_out_ );                                         /*-*/

static void  _test_countT( void ) {                                        /*F*/
    GO                                                            (UID(F4953C));
    countT(NULL, NULL, 0, IGNORE_CASE, false, 0, 0, 0, 0);

    /* TODO: implement _test_countT() */
    RETURN(NIL);
} /* _test_countT */


/* -------------------------------------------------------------------------- */


PUBLIC bool  endsT(                                                        /*F*/
    chars_t       main_str_,                                               /*-*/
    chars_t       find_str_,                                               /*-*/
    const bool    ignore_case_,                                            /*-*/
    const size_t  main_len_,                                               /*-*/
    const size_t  find_len_ );                                             /*-*/

static void  _test_endsT( void ) {                                         /*F*/
    GO                                                            (UID(F95607));
    endsT(NULL, NULL, IGNORE_CASE, 0, 0);  /*null-test*/
    _assert(ends3T(_T("abc"), _T("ABC"),  IGNORE_CASE) == true);
    _assert(ends3T(_T("abc"), _T("abc"),  MATCH_CASE)  == true);
    _assert(ends3T(_T("abc"), _T("abcd"), MATCH_CASE)  == false);
    _assert(ends3T(_T("abc"), _T("b"),    MATCH_CASE)  == false);
    _assert(ends3T(_T("abc"), _T("bc"),   IGNORE_CASE) == true);
    _assert(ends3T(_T("abc"), _T("bc"),   MATCH_CASE)  == true);
    _assert(ends3T(_T("abc"), _T("bcd"),  MATCH_CASE)  == false);
    _assert(ends3T(_T("abc"), _T("C"),    IGNORE_CASE) == true);
    _assert(ends3T(_T("abc"), _T("c"),    MATCH_CASE)  == true);
    _assert(ends3T(_T("def"), _T("D"),    MATCH_CASE)  == false);
    _assert(ends3T(_T("def"), _T("DE"),   MATCH_CASE)  == false);
    _assert(ends3T(_T("def"), _T("DEF"),  MATCH_CASE)  == false);
    _assert(ends3T(_T("def"), _T("DEFG"), MATCH_CASE)  == false);
    _assert(ends3T(BLANK,     NULL,       IGNORE_CASE) == true);
    _assert(ends3T(BLANK,     NULL,       MATCH_CASE)  == true);
    _assert(ends3T(NULL,      BLANK,      IGNORE_CASE) == true);
    _assert(ends3T(NULL,      BLANK,      MATCH_CASE)  == true);
    _assert(ends3T(NULL,      NULL,       IGNORE_CASE) == true);
    _assert(ends3T(NULL,      NULL,       MATCH_CASE)  == true);
    RETURN(NIL);
} /* _test_endsT */


/* -------------------------------------------------------------------------- */


PUBLIC bool  equalsT(                                                      /*F*/
    chars_t       string1_,                                                /*-*/
    chars_t       string2_,                                                /*-*/
    const bool    ignore_case_,                                            /*-*/
    const size_t  check_len_ );                                            /*-*/

static void  _test_equalsT( void ) {                                       /*F*/
    GO                                                            (UID(F7FEA4));
    equalsT(NULL, NULL, IGNORE_CASE, 0);  /*null-test*/

    /* compare blank strings */

    _assert(equalsT(_T(""), _T(""), IGNORE_CASE, 0) == true);
    _assert(equalsT(_T(""), _T(""), IGNORE_CASE, 0) == true);
    _assert(equalsT(_T(""), NULL,   IGNORE_CASE, 0) == true);
    _assert(equalsT(NULL,   _T(""), IGNORE_CASE, 0) == true);
    _assert(equalsT(NULL,   NULL,   IGNORE_CASE, 0) == true);

    _assert(equalsT(_T(""), _T(""), MATCH_CASE, 10) == true);
    _assert(equalsT(_T(""), _T(""), MATCH_CASE, 10) == true);
    _assert(equalsT(_T(""), NULL,   MATCH_CASE, 10) == true);
    _assert(equalsT(NULL,  _T(""),  MATCH_CASE, 10) == true);
    _assert(equalsT(NULL,   NULL,   MATCH_CASE, 10) == true);

    _assert(equalsT(_T("\0abc"), _T("\0def"), IGNORE_CASE, 10) == true);
    _assert(equalsT(_T("\0abc"), _T("\0def"), MATCH_CASE,  10) == true);
    _assert(equalsT(_T("\0abc"), _T("\0def"), IGNORE_CASE,  0) == true);
    _assert(equalsT(_T("\0abc"), _T("\0def"), MATCH_CASE,   0) == true);

    /* compare non-blank strings and blank strings */
    _assert(equalsT(_T(""),      _T("abc"), IGNORE_CASE, 1) == false);
    _assert(equalsT(_T(""),      _T("abc"), IGNORE_CASE, 7) == false);
    _assert(equalsT(_T(""),      _T("abc"), MATCH_CASE,  1) == false);
    _assert(equalsT(_T(""),      _T("abc"), MATCH_CASE,  7) == false);
    _assert(equalsT(_T("\0abc"), _T("abc"), IGNORE_CASE, 1) == false);
    _assert(equalsT(_T("\0abc"), _T("abc"), MATCH_CASE,  1) == false);
    _assert(equalsT(_T("abC"),   _T("abc"), MATCH_CASE,  2) == true);
    _assert(equalsT(_T("abc"),   _T("Abc"), MATCH_CASE,  3) == false);
    _assert(equalsT(_T("abC"),   _T("abc"), MATCH_CASE,  3) == false);
    _assert(equalsT(_T("abcD"),  _T("abc"), IGNORE_CASE, 3) == true);
    _assert(equalsT(_T("abcD"),  _T("abc"), IGNORE_CASE, 7) == false);
    _assert(equalsT(_T("abcD"),  _T("abc"), MATCH_CASE,  3) == true);
    _assert(equalsT(_T("abcD"),  _T("abc"), MATCH_CASE,  7) == false);

    RETURN(NIL);
} /* _test_equalsT */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  findT(                                                      /*F*/
    chars_t       main_str_,                                               /*-*/
    chars_t       find_str_,                                               /*-*/
    const size_t  offset_,                                                 /*-*/
    const bool    ignore_case_,                                            /*-*/
    const bool    from_end_,                                               /*-*/
    const size_t  main_len_,                                               /*-*/
    const size_t  find_len_ );                                             /*-*/

static void  _test_findT( void ) {                                         /*F*/
    GO                                                            (UID(F6FF61));
    findT(NULL, NULL, 0, IGNORE_CASE, false, 0, 0);
    /*null-test*/

    _assert(NONE == find4T(_T("A COPY CAT"),
                           _T("a copy cat"), 1, MATCH_CASE));

    _assert(NONE == find4T(_T("A COPY CAT"),
                           _T("a copy cat"), 1000, IGNORE_CASE));

    _assert(find2T(_T("A COPY CAT"), _T("A COPY")) == 0);
    _assert(find2T(_T("A COPY CAT"), _T("A")) == 0);
    _assert(find4T(_T("A COPY CAT"), _T("A"), 0, IGNORE_CASE) == 0);
    _assert(find2T(_T("A COPY CAT"), _T("CAT")) == 7);
    _assert(find4T(_T("A COPY CAT"), _T("CAT"), 0, IGNORE_CASE) == 7);
    _assert(find4T(_T("A COPY CAT"), _T("CAT"), 7, IGNORE_CASE) == 7);

    _assert(NONE == find4T(_T("A COPY CAT"), _T("cat"), 7, MATCH_CASE));

    _assert(NONE == find4T(_T("A COPY CAT"), _T("CAT"), 8, IGNORE_CASE));

    _assert(find2T(_T("A COPY CAT"), _T("COPY")) == 2);

    _assert(find4T(_T("A COPY CAT"), _T("COPY"), 0, IGNORE_CASE) == 2);

    _assert(NONE == find4T(_T("A COPY CAT"), _T("copy"), 3, MATCH_CASE));

    _assert(NONE == find2T(_T("A COPY CAT"), _T("crocodile")));
    _assert(NONE == find2T(_T("A COPY CAT"), _T("dog")));
    _assert(find4T(_T("A COPY CAT"), _T("T"), 0, IGNORE_CASE) == 9);

    _assert(NONE == find2T(_T("A COPY CAT"), _T("s")));
    _assert(NONE == find2T(_T("A COPY CAT"), BLANK));
    _assert(NONE == find3T(_T("A COPY CAT"), _T("a copy cat"), 0));

    _assert(find4T(_T("A COPY CAT"),
                   _T("A COPY CAT"), 0, IGNORE_CASE) == 0);

    _assert(NONE == find4T(_T("A COPY CAT"),
                           _T("A copy CAT"), 0, MATCH_CASE));

    _assert(NONE == find4T(_T("A COPY CAT"), BLANK, 1000, IGNORE_CASE));
    RETURN(NIL);
} /* _test_findT */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  find_charT(                                                 /*F*/
    chars_t       main_str_,                                               /*-*/
    const char_t  find_char_,                                              /*-*/
    const size_t  offset_,                                                 /*-*/
    const bool    ignore_case_,                                            /*-*/
    const bool    from_end_ );                                             /*-*/

static void  _test_find_charT( void ) {                                    /*F*/
    GO                                                            (UID(FC5310));
    find_charT(NULL, '\0', 0, IGNORE_CASE, false);  /*null-test*/

    /* TODO: implement _test_find_charT() */
    RETURN(NIL);
} /* _test_find_charT */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  find_charsT(                                                /*F*/
    chars_t       main_str_,                                               /*-*/
    chars_t       chars_,                                                  /*-*/
    const bool    ignore_case_,                                            /*-*/
    const size_t  main_len_ );                                             /*-*/

static void  _test_find_charsT( void ) {                                   /*F*/
    GO                                                            (UID(F57E06));
    find_charsT(NULL, NULL, IGNORE_CASE, 0);  /*null-test*/

    /* TODO: implement _test_find_charsT() */
    RETURN(NIL);
} /* _test_find_charsT */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  find_last3T(                                                /*F*/
    chars_t     string_,                                                   /*-*/
    chars_t     find_,                                                     /*-*/
    const bool  ignore_case_ );                                            /*-*/

static void  _test_find_last3T( void ) {                                   /*F*/
    GO                                                            (UID(F9E205));
    find_last3T(NULL, NULL, false);  /*null-test*/
    RETURN(NIL);
} /* _test_find_last3T */


/* -------------------------------------------------------------------------- */


PUBLIC bool  is_numberT(                                                   /*F*/
    chars_t       string_,                                                 /*-*/
    const char_t  decimal_point_char_,                                     /*-*/
    const char_t  group_separator_char_,                                   /*-*/
    chars_t       whitespaces_ );                                          /*-*/

static void  _test_is_numberT( void ) {                                    /*F*/
    GO                                                            (UID(FBEA37));
    is_numberT(NULL, '\0', '\0', NULL);  /*null-test*/

    /* TODO: implement _test_is_numberT() */
    RETURN(NIL);
} /* _test_is_numberT */


/* -------------------------------------------------------------------------- */


PUBLIC bool  is_whitespaceT( chars_t  string_ );                           /*F*/

static void  _test_is_whitespaceT( void ) {                                /*F*/
    GO                                                            (UID(F47469));
#define _TEST( STRING_, RESULT_ )                     \
    _assert(is_whitespaceT(STRING_) == RESULT_);  /*#*/

    _TEST(NULL,      false);  /*null-test*/
    _TEST(BLANK,  false);

    _TEST(_T(""),    false);
    _TEST(_T("\0"),  false);
    _TEST(_T(" a"),  false);
    _TEST(_T("a "),  false);
    _TEST(_T("a"),   false);
    _TEST(_T("abc"), false);

    _TEST(_T("  "),   true);
    _TEST(_T(" "),    true);
    _TEST(_T(" \b "), true);
    _TEST(_T(" \b"),  true);
    _TEST(_T(" \n "), true);
    _TEST(_T(" \n"),  true);
    _TEST(_T(" \r "), true);
    _TEST(_T(" \r"),  true);
    _TEST(_T(" \t "), true);
    _TEST(_T(" \t"),  true);
    _TEST(_T("\b "),  true);
    _TEST(_T("\b"),   true);
    _TEST(_T("\n "),  true);
    _TEST(_T("\n"),   true);
    _TEST(_T("\r "),  true);
    _TEST(_T("\r"),   true);
    _TEST(_T("\t "),  true);
    _TEST(_T("\t"),   true);

#undef _TEST
    RETURN(NIL);
} /* _test_is_whitespaceT */


/* -------------------------------------------------------------------------- */


PUBLIC bool  is_wide( const void*  string_ );                              /*F*/

static void  _test_is_wide( void ) {                                       /*F*/
    GO                                                            (UID(F36BB2));
    is_wide(NULL);  /*null-test*/

    /* TODO: implement _test_is_wide() */
    RETURN(NIL);
} /* _test_is_wide */


/* -------------------------------------------------------------------------- */


PUBLIC bool  is_wide_n(                                                    /*F*/
    const void*   string_,                                                 /*-*/
    const size_t  max_len_in_bytes_ );                                     /*-*/

static void  _test_is_wide_n( void ) {                                     /*F*/
    GO                                                            (UID(FA57BA));
    is_wide_n(NULL, 0);  /*null-test*/

    /* TODO: implement _test_is_wide_n() */
    RETURN(NIL);
} /* _test_is_wide_n */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  lenT( chars_t  string_ );                                   /*F*/

static void  _test_lenT( void ) {                                          /*F*/
    GO                                                            (UID(FE7A1F));
    lenT(NULL);  /*null-test*/
    _assert(lenT(_T("   "))      == 3);
    _assert(lenT(_T("  "))       == 2);
    _assert(lenT(_T(" "))        == 1);
    _assert(lenT(_T(""))         == 0);
    _assert(lenT(_T("\0 12345")) == 0);
    _assert(lenT(_T("\n"))       == 1);
    _assert(lenT(_T("\r"))       == 1);
    _assert(lenT(_T("\t"))       == 1);
    _assert(lenT(_T("1\0 2345")) == 1);
    _assert(lenT(_T("123\0 45")) == 3);
    _assert(lenT(_T("12345\0 ")) == 5);
    _assert(lenT(_T("a"))        == 1);
    _assert(lenT(_T("ab"))       == 2);
    _assert(lenT(_T("abc"))      == 3);
    _assert(lenT(_T("abcd"))     == 4);
    _assert(lenT(_T("abcde"))    == 5);
    _assert(lenT(BLANK)          == 0);
    _assert(lenT(NULL)           == 0);
    RETURN(NIL);
} /* _test_lenT */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  len_maxT(                                                   /*F*/
    chars_t       string_,                                                 /*-*/
    const size_t  max_len_ );                                              /*-*/

static void  _test_len_maxT( void ) {                                      /*F*/
    GO                                                            (UID(FD17BD));
    len_maxT(NULL, 0);  /*null-test*/

    /* TODO: implement _test_len_maxT() */
    RETURN(NIL);
} /* _test_len_maxT */


/* -------------------------------------------------------------------------- */


PUBLIC int  line_countT( chars_t  string_ );                               /*F*/

static void  _test_line_countT( void ) {                                   /*F*/
    GO                                                            (UID(FB02B9));
    line_countT(NULL);  /*null-test*/
    RETURN(NIL);
} /* _test_line_countT */


/* -------------------------------------------------------------------------- */


PUBLIC bool  patternMatchT(                                                /*F*/
    chars_t     string_,                                                   /*-*/
    chars_t     pattern_,                                                  /*-*/
    const bool  ignore_case_ );                                            /*-*/

static void  _test_matchT( void ) {                                        /*F*/
    GO                                                            (UID(FDBD3A));
    patternMatchT(NULL, NULL, IGNORE_CASE);  /*null-test*/
    /* TODO: implement _test_matchT() */
    RETURN(NIL);
} /* _test_matchT */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  skip_charsT(                                                /*F*/
    chars_t       main_str_,                                               /*-*/
    chars_t       chars_to_skip_,                                          /*-*/
    const bool    ignore_case_,                                            /*-*/
    const size_t  main_len_ );                                             /*-*/

static void  _test_skip_charsT( void ) {                                   /*F*/
    GO                                                            (UID(F52991));
    skip_charsT(NULL, NULL, IGNORE_CASE, 0);  /*null-test*/

    /* TODO: implement _test_skip_charsT() */
    RETURN(NIL);
} /* _test_skip_charsT */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  substr_lenT(                                                /*F*/
    chars_t       main_str_,                                               /*-*/
    const size_t  main_len_,                                               /*-*/
    const size_t  offset_,                                                 /*-*/
    const size_t  substr_len_ );                                           /*-*/

static void  _test_substr_lenT( void ) {                                   /*F*/
    GO                                                            (UID(F8CFAF));
    substr_lenT(NULL, 0, 0, 0);  /*null-test*/

    /* TODO: implement _test_substr_lenT() */
    RETURN(NIL);
} /* _test_substr_lenT */


/* -------------------------------------------------------------------------- */


PUBLIC double  doubleT( chars_t  string_ );                                /*F*/

static void  _test_doubleT( void ) {                                       /*F*/
    GO                                                            (UID(FA675F));
#define _TEST( STRING_, RESULT_ )                  \
    {                                              \
        double  val = doubleT(STRING_);            \
        _assert((val > ((RESULT_) - 0.00001)) &&   \
                (val < ((RESULT_) + 0.00001)));    \
    }                                          /*#*/

    _TEST(NULL, 0);  /*null-test*/

    /* simple values, including spaces */
    _TEST(_T(" -123 "),     -123);
    _TEST(_T(" -123"),      -123);
    _TEST(_T(" -123.456 "), -123.456);
    _TEST(_T(" -123.456"),  -123.456);
    _TEST(_T("-123 "),      -123);
    _TEST(_T("123"),        123);
    _TEST(_T("-123"),       -123);
    _TEST(_T("-123.456 "),  -123.456);
    _TEST(_T("123.456"),    123.456);
    _TEST(_T("-123.456"),   -123.456);

    /* values returning zero */
    _TEST(NULL,            0);
    _TEST(_T("   "),       0);
    _TEST(_T("  "),        0);
    _TEST(_T(" "),         0);
    _TEST(_T(""),          0);
    _TEST(_T("\0"),        0);
    _TEST(_T("\n"),        0);
    _TEST(_T("\r"),        0);
    _TEST(_T("\t"),        0);
    _TEST(_T(" \n"),       0);
    _TEST(_T(" \r"),       0);
    _TEST(_T(" \t"),       0);
    _TEST(_T("\n "),       0);
    _TEST(_T("\r "),       0);
    _TEST(_T("\t "),       0);

    _TEST(_T(" 0 "),       0);
    _TEST(_T(" 0"),        0);
    _TEST(_T("0 "),        0);
    _TEST(_T("0"),         0);

    _TEST(_T(" 00 "),      0);
    _TEST(_T(" 00"),       0);
    _TEST(_T("00 "),       0);
    _TEST(_T("00"),        0);

    _TEST(_T(" 000 "),     0);
    _TEST(_T(" 000"),      0);
    _TEST(_T("000 "),      0);
    _TEST(_T("000"),       0);

    _TEST(_T(" 0.0 "),     0);
    _TEST(_T(" 0.0"),      0);
    _TEST(_T("0.0 "),      0);
    _TEST(_T("0.0"),       0);

    _TEST(_T(" 00.0 "),    0);
    _TEST(_T(" 00.0"),     0);
    _TEST(_T("00.0 "),     0);
    _TEST(_T("00.0"),      0);

    _TEST(_T(" 000.0 "),   0);
    _TEST(_T(" 000.0"),    0);
    _TEST(_T("000.0 "),    0);
    _TEST(_T("000.0"),     0);

    _TEST(_T(" -0 "),      0);
    _TEST(_T(" -0"),       0);
    _TEST(_T("-0 "),       0);
    _TEST(_T("-0"),        0);

    _TEST(_T(" -00 "),     0);
    _TEST(_T(" -00"),      0);
    _TEST(_T("-00 "),      0);
    _TEST(_T("-00"),       0);

    _TEST(_T(" -000 "),    0);
    _TEST(_T(" -000"),     0);
    _TEST(_T("-000 "),     0);
    _TEST(_T("-000"),      0);

    _TEST(_T(" -0.0 "),    0);
    _TEST(_T(" -0.0"),     0);
    _TEST(_T("-0.0 "),     0);
    _TEST(_T("-0.0"),      0);

    _TEST(_T(" -00.0 "),   0);
    _TEST(_T(" -00.0"),    0);
    _TEST(_T("-00.0 "),    0);
    _TEST(_T("-00.0"),     0);

    _TEST(_T(" -000.0 "),  0);
    _TEST(_T(" -000.0"),   0);
    _TEST(_T("-000.0 "),   0);
    _TEST(_T("-000.0"),    0);

    /* miscellaneous tests */
    _TEST(_T("1234"), 1234);
    _TEST(_T("-1234"), -1234);
    _TEST(_T("1234567890"), 1234567890);
    _TEST(_T("-2147483647"), -2147483647);
    _TEST(_T("2147483647"), 2147483647);
    _TEST(_T("1.23456"), 1.23456);
    _TEST(_T("1.5"), 1.5);

#undef _TEST
    RETURN(NIL);
} /* _test_doubleT */


/* -------------------------------------------------------------------------- */


PUBLIC int  int_T( chars_t  string_ );                                     /*F*/

static void  _test_int_T( void ) {                                         /*F*/
    GO                                                            (UID(FBE250));
    _INIT_TEST_VARS;

    int_T(NULL);  /*null-test*/

    CLEAR(test_str);

#define _TEST( INITIAL_STRING_, INT_VAL_ )            \
    setInS(&test_str, INITIAL_STRING_);               \
    _assert(int_T(_str(test_str)) == (INT_VAL_))  /*#*/

    /* simple integer,      including spaces */
    _TEST(_T(" -123 "),    -123);
    _TEST(_T(" -123"),     -123);
    _TEST(_T("-123 "),     -123);
    _TEST(_T("123"),       123);
    _TEST(_T("-123"),      -123);

    /* values returning zero */
    _TEST(NULL,            0);

    _TEST(_T("   "),       0);
    _TEST(_T("  "),        0);
    _TEST(_T(" "),         0);
    _TEST(_T(" \n"),       0);
    _TEST(_T(" \r"),       0);
    _TEST(_T(" \t"),       0);
    _TEST(_T(""),          0);
    _TEST(_T("\0"),        0);
    _TEST(_T("\n "),       0);
    _TEST(_T("\n"),        0);
    _TEST(_T("\r "),       0);
    _TEST(_T("\r"),        0);
    _TEST(_T("\t "),       0);
    _TEST(_T("\t"),        0);

    _TEST(_T(" 0 "),       0);
    _TEST(_T(" 0"),        0);
    _TEST(_T("0 "),        0);
    _TEST(_T("0"),         0);

    _TEST(_T(" 00 "),      0);
    _TEST(_T(" 00"),       0);
    _TEST(_T("00 "),       0);
    _TEST(_T("00"),        0);

    _TEST(_T(" 000 "),     0);
    _TEST(_T(" 000"),      0);
    _TEST(_T("000 "),      0);
    _TEST(_T("000"),       0);

    _TEST(_T(" 0.0 "),     0);
    _TEST(_T(" 0.0"),      0);
    _TEST(_T("0.0 "),      0);
    _TEST(_T("0.0"),       0);

    _TEST(_T(" 00.0 "),    0);
    _TEST(_T(" 00.0"),     0);
    _TEST(_T("00.0 "),     0);
    _TEST(_T("00.0"),      0);

    _TEST(_T(" 000.0 "),   0);
    _TEST(_T(" 000.0"),    0);
    _TEST(_T("000.0 "),    0);
    _TEST(_T("000.0"),     0);

    _TEST(_T(" -0 "),      0);
    _TEST(_T(" -0"),       0);
    _TEST(_T("-0 "),       0);
    _TEST(_T("-0"),        0);

    _TEST(_T(" -00 "),     0);
    _TEST(_T(" -00"),      0);
    _TEST(_T("-00 "),      0);
    _TEST(_T("-00"),       0);

    _TEST(_T(" -000 "),    0);
    _TEST(_T(" -000"),     0);
    _TEST(_T("-000 "),     0);
    _TEST(_T("-000"),      0);

    _TEST(_T(" -0.0 "),    0);
    _TEST(_T(" -0.0"),     0);
    _TEST(_T("-0.0 "),     0);
    _TEST(_T("-0.0"),      0);

    _TEST(_T(" -00.0 "),   0);
    _TEST(_T(" -00.0"),    0);
    _TEST(_T("-00.0 "),    0);
    _TEST(_T("-00.0"),     0);

    _TEST(_T(" -000.0 "),  0);
    _TEST(_T(" -000.0"),   0);
    _TEST(_T("-000.0 "),   0);
    _TEST(_T("-000.0"),    0);

    /* miscellaneous tests */
    _TEST(_T("1,234"),       1234);
    _TEST(_T("-1,234"),      -1234);
    _TEST(_T("1.23456"),     1);
    _TEST(_T("1.5"),         1);
    _TEST(_T("1234567890"),  1234567890);
    _TEST(_T("2147483647"),  2147483647);
    _TEST(_T("-2147483647"), -2147483647);

#undef _TEST

    freeS(&test_str);
    RETURN(NIL);
} /* _test_int_T */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  token_infoT(                                                /*F*/
    token_info_enum  mode_,                                                /*-*/
    chars_t          list_,                                                /*-*/
    chars_t          delimiter_,                                           /*-*/
    chars_t          token_ );                                             /*-*/

static void  _test_token_infoT( void ) {                                   /*F*/
    GO                                                            (UID(FCBDCB));
    token_infoT(TOKEN_EXISTS, NULL, NULL, NULL);  /*null-test*/

    /* TODO: implement _test_token_infoT() */
    RETURN(NIL);
} /* _test_token_infoT */


/* -------------------------------------------------------------------------- */


PUBLIC size_t  token_info_xtT(                                             /*F*/
    const token_info_enum  mode_,                                          /*-*/
    chars_t                list_,                                          /*-*/
    chars_t                delimiter_,                                     /*-*/
    chars_t                token_,                                         /*-*/
    const bool             ignore_case_,                                   /*-*/
    const size_t           list_len_,                                      /*-*/
    const size_t           token_len_ );                                   /*-*/

static void  _test_token_info_xtT( void ) {                                /*F*/
    GO                                                            (UID(F21A5E));
    /*null-test*/
    token_info_xtT(TOKEN_EXISTS, NULL, NULL, NULL, IGNORE_CASE, 0, 0);

    /* TODO: implement _test_token_info_xtT() */
    RETURN(NIL);
} /* _test_token_info_xtT */


/* -------------------------------------------------------------------------- */


PUBLIC int  token_countT(                                                  /*F*/
    chars_t  string_,                                                      /*-*/
    chars_t  delimiter_ );                                                 /*-*/

static void  _test_token_countT( void ) {                                  /*F*/
    GO                                                            (UID(FB4490));
    {
        const int  result = token_countT(NULL, NULL);  /*null-test*/
        _assert(result == 0);
    }

    {
        struct _test_t {
            chars_t  string_;                                      /* _test_t */
            chars_t  delimiter_;                                   /* _test_t */
            int      expected;                                     /* _test_t */
        }
        test[] = {

            /* if string is blank, always returns zero */
            { NULL, _T(""), 0 },
            { NULL, _T("1"), 0 },
            { NULL, _T("12"), 0 },
            { NULL, _T("123"), 0 },

            { _T(""), NULL, 0 },
            { _T(""), _T(""), 0 },
            { _T(""), _T("1"), 0 },
            { _T(""), _T("12"), 0 },
            { _T(""), _T("123"), 0 },

            /* expect 1 */
            { _T("123"), NULL, 1 },
            { _T("123"), _T(""), 1 },
            { _T("123"), _T("~"), 1 },

            /* expect 2 */
            { _T("~"), _T("~"), 2 },
            { _T("123~"), _T("~"), 2 },
            { _T("~456"), _T("~"), 2 },
            { _T("123~456"), _T("~"), 2 },

            /* expect 2 */
            { _T("--"), _T("--"), 2 },
            { _T("123--"), _T("--"), 2 },
            { _T("--456"), _T("--"), 2 },
            { _T("123--456"), _T("--"), 2 },

            { NULL, NULL, 0 }
        };

        int  i = 0;
        while (test[i].string_ != NULL && test[i].delimiter_ != NULL) {
            if (i == -1) {
                DEBUG_BREAK;
            }

            {
                /* do test_str */
                chars_t    string_    = test[i].string_;
                chars_t    delimiter_ = test[i].delimiter_;
                const int  result     = token_countT(string_, delimiter_);

                _assert(result == test[i].expected);
                i++;
            }
        }
    }
    RETURN(NIL);
} /* _test_token_countT */


/* -------------------------------------------------------------------------- */


PUBLIC uint32_t  uint_of_T( chars_t  string_ );                            /*F*/

static void  _test_uint_of_T( void ) {                                     /*F*/
    GO                                                            (UID(F77521));
    _INIT_TEST_VARS;

    uint_of_T(NULL);  /*null-test*/

    CLEAR(test_str);

#define _TEST( STRING_, UNSIGNED_ )                   \
    setInS(&test_str, STRING_);                       \
    _assert(uint_of_T(_str(test_str)) == UNSIGNED_);  \
    freeS(&test_str);                             /*#*/

    _TEST(_T(" "), 0);
    _TEST(_T(" 1234567890"), 1234567890);
    _TEST(_T(" 4294967295"), 4294967295);
    _TEST(_T(""), 0);
    _TEST(_T("0"), 0);
    _TEST(_T("0.0"), 0);
    _TEST(_T("00"), 0);
    _TEST(_T("00.00"), 0);
    _TEST(_T("1"), 1);
    _TEST(_T("1234567890"), 1234567890);
    _TEST(_T("1A"), 1);
    _TEST(_T("4294967295"), 4294967295);
    _TEST(NULL, 0);

    /* overflow */
    _TEST(_T("-1"), 4294967295);
    _TEST(_T("-4294967295"), 1);
    _TEST(_T("4294967296"), 4294967295);

#undef _TEST
    RETURN(NIL);
} /* _test_uint_of_T */


/* -------------------------------------------------------------------------- */


PUBLIC bool  is_unicode_mode( void );                                      /*F*/

static void  _test_is_unicode_mode( void ) {                               /*F*/
    GO                                                            (UID(FC2707));
    is_unicode_mode();  /*null-test*/
    /* TODO: implement _test_is_unicode_mode() */
    RETURN(NIL);
} /* _test_is_unicode_mode */


/* -------------------------------------------------------------------------- */


PUBLIC void  test_large_operations( void );                                /*F*/
PUBLIC void  test_large_operations( void ) {                               /*F*/
    GO                                                            (UID(FC7055));
#if PLATFORM_WIN32
    str_t  test_str = S_blank();
    spaceInS(&test_str, 400 * 1024 * 1024, false, false);

    MessageBox_win(NULL, _T("ALLOCATED!"), _T("ALLOCATED"),
                   MB_ICONINFORMATION_win);

    setReplaceS(&test_str, _T(" "), _T("A"), IGNORE_CASE, 1, 1);

    MessageBox_win(NULL, _T("REPLACED!"), _T("REPLACED"),
                   MB_ICONINFORMATION_win);
#endif                                                      /* PLATFORM_WIN32 */
    RETURN(NIL);
} /* test_large_operations */


/* -------------------------------------------------------------------------- */


PUBLIC void  test_string_class( void );                                    /*F*/
PUBLIC void  test_string_class( void ) {                                   /*F*/
    GO                                                            (UID(F25284));
#define _TEST_CONSTRUCTORS_AND_DESTRUCTOR  1
#define _TEST_METHODS_CHANGING_OBJECT      1
#define _TEST_METHODS_ALLOCATING           1
#define _TEST_METHODS_INFORMATIVE          1
#define _TEST_FUNCTIONS_ALLOCATING         1
#define _TEST_FUNCTIONS_IN_PLACE           1
#define _TEST_FUNCTIONS_INFORMATIVE        1

#define _FN( NAME_ )  { NAME_, STR(#NAME_) }

    int  i = 0;

    struct _test_t {
        void    (*fn)( void );                                     /* _test_t */
        chars_t   fn_name;                                         /* _test_t */
    }
    test[] = {

#if _TEST_CONSTRUCTORS_AND_DESTRUCTOR
        /* constructors */
        _FN(_test_Sappend),
        _FN(_test_Sbchars),
        _FN(_test_Sblank),
        _FN(_test_Sbsubstr),
        _FN(_test_Schars),
        _FN(_test_Scopy),
        _FN(_test_SfirstChars),
        _FN(_test_SformatNumeric),
        _FN(_test_SnewT),
        _FN(_test_Srepeat),
        _FN(_test_Sreserve),
        _FN(_test_Swchars),
        _FN(_test_Swchars_n),

        /* destructor */
        _FN(_test_freeS),
#endif                                   /* _TEST_CONSTRUCTORS_AND_DESTRUCTOR */

#if _TEST_METHODS_CHANGING_OBJECT
        // _FN(_test_setFillS),
        _FN(_test_add3S),
        _FN(_test_addAS),
        _FN(_test_addCharS),
        _FN(_test_addIntS),
        _FN(_test_addS),
        _FN(_test_addTS),
        _FN(_test_addWS),
        _FN(_test_closeBufferS),
        _FN(_test_copyFromBufferS),
        _FN(_test_copyToBufferS),
        _FN(_test_freeConversionBufferS),
        _FN(_test_reserveInS),
        _FN(_test_setCopyAnsiS),
        _FN(_test_setCopyCharS),
        _FN(_test_setCopyS),
        _FN(_test_setCopyWideS),
        _FN(_test_decodeBase64InS),
        _FN(_test_delimitNumberInS),
        _FN(_test_clearInS),
        _FN(_test_encodeBase64InS),
        _FN(_test_firstInS),
        _FN(_test_formatNumericInS),
        _FN(_test_formatInS),
        _FN(_test_setLastS),
        _FN(_test_tolowerInS),
        _FN(_test_setRemoveEndS),
        _FN(_test_removeInS),
        _FN(_test_setReplaceS),
        _FN(_test_reverseInS),
        _FN(_test_setS),
        _FN(_test_setSortListS),
        _FN(_test_spaceInS),
        _FN(_test_totitleInS),
        _FN(_test_trimInS),
        _FN(_test_toupperInS),
#endif                                       /* _TEST_METHODS_CHANGING_OBJECT */

#if _TEST_METHODS_ALLOCATING
        _FN(_test_Sbracket),
        _FN(_test_SdecodeBase64),
        _FN(_test_SencodeBase64),
        _FN(_test_Sfirst),
        _FN(_test_SgetTag),
        _FN(_test_S_getToken),
        _FN(_test_S_getTokenXt),
        _FN(_test_Sinsert),
        _FN(_test_Slast),
        _FN(_test_SlowerCase),
        _FN(_test_Squote),
        _FN(_test_Sremove),
        _FN(_test_SremoveBegin),
        _FN(_test_SremoveChar),
        _FN(_test_SremoveEnd),
        _FN(_test_SremoveStr),
        _FN(_test_Sreplace),
        _FN(_test_SreplaceByRef),
        _FN(_test_Sreverse),
        _FN(_test_SsortList),
        _FN(_test_Sspace),
        _FN(_test_Ssubstr),
        _FN(_test_StitleCase),
        _FN(_test_S_setToken),
        _FN(_test_Strim),
        _FN(_test_StrimBegin),
        _FN(_test_StrimBeginChar),
        _FN(_test_StrimChar),
        _FN(_test_StrimEnd),
        _FN(_test_StrimEndChar),
        _FN(_test_StrimStr),
        _FN(_test_Sunquote),
        _FN(_test_SupperCase),
#endif                                            /* _TEST_METHODS_ALLOCATING */

#if _TEST_METHODS_INFORMATIVE
        /* UNDEFINED _FN(_test_S_asString), */
        _FN(_test_charsS),
        _FN(_test_doubleS),
        _FN(_test_emptyS),
        _FN(_test_getBufferS),
        _FN(_test_getEmptyBufferS),
        _FN(_test_patternMatchS),
        _FN(_test_S_begins),
        _FN(_test_S_byteSize),
        _FN(_test_S_capacity),
        _FN(_test_S_contains),
        _FN(_test_S_count),
        _FN(_test_S_ends),
        _FN(_test_S_equal),
        _FN(_test_S_find),
        _FN(_test_S_findChar),
        _FN(_test_S_findChars),
        _FN(_test_S_findEnd),
        _FN(_test_S_findEndChar4),
        _FN(_test_S_findFirstNotOf),
        _FN(_test_S_isNumber),
        _FN(_test_S_isWhitespace),
        _FN(_test_S_length),
        _FN(_test_S_like3),
        _FN(_test_S_lineCount),
        _FN(_test_S_skipChars),
        _FN(_test_S_toInt),
        _FN(_test_tokenCountXtS),
        _FN(_test_existsTokenS),
        _FN(_test_tokenIndexS),
        _FN(_test_uintS),
        _FN(_test_wcharsS),
#endif                                           /* _TEST_METHODS_INFORMATIVE */

#if _TEST_FUNCTIONS_ALLOCATING
        /* _FN(_test_T_tokenize), */
        _FN(_test_appendnT),
        _FN(_test_chars_to_utf8),
        _FN(_test_doubleT),
        _FN(_test_formatT),
        _FN(_test_set_defaultT),
        _FN(_test_setT),
        _FN(_test_Shex),
        _FN(_test_T_bchars_n),
        _FN(_test_T_chars_n),
        _FN(_test_T_decode_base64),
        _FN(_test_T_encode_base64),
        _FN(_test_T_first),
        _FN(_test_T_format_numeric),
        _FN(_test_T_get_token_xt),
        _FN(_test_T_int),
        _FN(_test_T_join),
        _FN(_test_T_last),
        _FN(_test_T_malloc_id),
        _FN(_test_T_offset),
        _FN(_test_T_realloc_id),
        _FN(_test_T_repeat),
        _FN(_test_T_replace),
        _FN(_test_T_set_token),
        _FN(_test_T_substr),
        _FN(_test_T_uint64),
        _FN(_test_T_wchars_n),
        _FN(_test_to_bytesT),
        _FN(_test_Twchars),
        _FN(_test_uT_int),
        _FN(_test_utf8_from_wide),
        _FN(_test_wchars_from_utf8),
#endif                                          /* _TEST_FUNCTIONS_ALLOCATING */

#if _TEST_FUNCTIONS_IN_PLACE
        _FN(_test_lower_in_T),
        _FN(_test_remove_extra_spaces_in_T),
        _FN(_test_replace_in_T),
        _FN(_test_title_in_T),
        _FN(_test_trim_in_T),
        _FN(_test_trim4_in_T),
        _FN(_test_upper_in_T),
#endif                                            /* _TEST_FUNCTIONS_IN_PLACE */

#if _TEST_FUNCTIONS_INFORMATIVE
        _FN(_test_begins3T),
        _FN(_test_containsT),
        _FN(_test_countT),
        _FN(_test_doubleT),
        _FN(_test_endsT),
        _FN(_test_equalsT),
        _FN(_test_find_charsT),
        _FN(_test_find_charT),
        _FN(_test_find_last3T),
        _FN(_test_findT),
        _FN(_test_int_T),
        _FN(_test_is_numberT),
        _FN(_test_is_unicode_mode),
        _FN(_test_is_whitespaceT),
        _FN(_test_is_wide),
        _FN(_test_is_wide_n),
        _FN(_test_len_maxT),
        _FN(_test_lenT),
        _FN(_test_line_countT),
        _FN(_test_matchT),
        _FN(_test_skip_charsT),
        _FN(_test_substr_lenT),
        _FN(_test_token_countT),
        _FN(_test_token_info_xtT),
        _FN(_test_token_infoT),
        _FN(_test_uint_of_T),
        _FN(_test_utf8_len),
#endif                                         /* _TEST_FUNCTIONS_INFORMATIVE */
        /* exit marker */
        _FN(NULL)
    };
    // Warning C4047   'initializing': 'void (__cdecl *)(void)' ``
    // differs in levels of indirection from 'int'

    enable_string_warnings = false;
    enable_chars_warnings  = false;

    /* mem_report(); */
    do {
        chars_t  fn_name = test[i].fn_name;
        mem_check();
        {
            const int  before = mem_pending();
            int        after  = 0;
            test[i].fn();  /* call function */
            after             = mem_pending();

            if (mem_pending() != before) {
                PRINTF_T(_T("\r\n")
                         _T(" %s has memory leaks! before: %d after: %d"),
                         fn_name, before, after);
                DEBUG_BREAK;
            }
        }
        mem_check();
        PRINTF_T(_T("\r\n tested %s"), fn_name);
    } while (test[++i].fn);
    /* mem_report(); */

    enable_string_warnings = true;
    enable_chars_warnings  = true;
    RETURN(NIL);
} /* test_string_class */


/* -------------------------------------------------------------------------- */
/* TYPE NAME          |BYTES| RANGE                                           */
/* -------------------------------------------------------------------------- */
/* short              |  2  | -32,768 to 32,767                               */
/* int                |  4  | -2,147,483,648 to 2,147,483,647                 */
/* long               |  4  | -2,147,483,648 to 2,147,483,647                 */
/* long long          |  8  | -9,223,372,036,854,775,808                      */
/*                    |     | to 9,223,372,036,854,775,807                    */
/*                    |     |                                                 */
/* unsigned short     |  2  | 0 to 65,535                                     */
/* unsigned long      |  4  | 0 to 4,294,967,295                              */
/* unsigned int       |  4  | 0 to 4,294,967,295                              */
/* unsigned long long |  8  | 0 to 18,446,744,073,709,551,615                 */
/*                    |     |                                                 */
/* float              |  4  | 3.4E +/- 38 (7 digits)                          */
/* double             |  8  | 1.7E +/- 308 (15 digits)                        */
/* long double        |  8  | same as double                                  */
/*                    |     |                                                 */
/* signed char        |  1  | -128 to 127                                     */
/* unsigned char      |  1  | 0 to 255                                        */
/* char               |  1  | -128 to 127 by default                          */
/*                    |     | (0 to 255 when compiled with /J)                */
/*                    |     |                                                 */
/* wchar_t            |  2  | 0 to 65,535                                     */
/*                    |     |                                                 */
/*                    |vary | See Remarks.                                    */
/* bool               |  1  | false or true                                   */
/*                    |     |                                                 */
/* Visual C++ Types:  |     |                                                 */
/* __int8             |  1  | -128 to 127                                     */
/* __int16            |  2  | -32,768 to 32,767                               */
/* __int32            |  4  | -2,147,483,648 to 2,147,483,647                 */
/* __int64            |  8  | -9,223,372,036,854,775,808                      */
/*                    |     | to 9,223,372,036,854,775,807                    */
/*                    |     |                                                 */
/* unsigned __int8    |  1  | 0 to 255                                        */
/* unsigned __int16   |  2  | 0 to 65,535                                     */
/* unsigned __int32   |  4  | 0 to 4,294,967,295                              */
/* unsigned __int64   |  8  | 0 to 18,446,744,073,709,551,615                 */
/* -------------------------------------------------------------------------- */

#endif                                                                   /*eof*/

/* TODO: How to catch 2 consecutive de-allocations */
/* TODO: Needs setInsert() method                  */

