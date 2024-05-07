/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_const.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_CONST_H
#define      INCLUDED_LIBEX_CONST_H

#if !defined NULL
#define NULL  0x00
#endif

/* -------------------------------------------------------------------------- */
/* Numeric Constants:                                                         */

#define LX_MILLION  1000000

#define LX_NONE     UINT_MAX

/* -------------------------------------------------------------------------- */
/* String Constants:                                                          */

#define LX_ASCII_CHARS  _T("!\"#$%&'()*+,-. /")  \
    _T("0123456789")                             \
    _T(":;<=>?@")                                \
    _T("ABCDEFGHIJKLMNOPQRSTUVWXYZ")             \
    _T("[\\]^_\x60")                             \
    _T("abcdefghijklmnopqrstuvwxyz")             \
    _T("{|}~")                               /*#*/

#define LX_ASCII_CHARS_A  "!\"#$%&'()*+,-. /"  \
    "0123456789"                               \
    ":;<=>?@"                                  \
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"               \
    "[\\]^_\x60"                               \
    "abcdefghijklmnopqrstuvwxyz"               \
    "{|}~"                                 /*#*/

#define LX_BASE64_DIGITS_A          \
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"    \
    "abcdefghijklmnopqrstuvwxyz"    \
    "0123456789+/"              /*#*/

#define LX_BLANK  _T("")

#define LX_ERR_TEXT  _T("error\b")

#define LX_NL  _T("\r\n")

#define LX_TT  _T("\a\b\f\v")
/* Text terminator. Used in various functions such as lx_T_join() */
/* to indicate the end of a variable-argument list of strings.    */
/* (\a = bell, \b = backspace, \f = formfeed, \v = vertical tab)  */

#define LX_WHITESPACES  _T(" \a\b\f\n\r\t\v")

#endif                                                                   /*eof*/
