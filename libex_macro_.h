/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                      [libex_macro_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_MACRO__H
#define      INCLUDED_LIBEX_MACRO__H
#include "libex_macro.h"

#define NULL_STATEMENT                  LX_NULL_STATEMENT

/* -------------------------------------------------------------------------- */
/* Boolean Macros */

#define C_BOOL                          LX_C_BOOL
#define CPP_BOOL                        LX_CPP_BOOL
#define XOR                             LX_XOR

/* -------------------------------------------------------------------------- */
/* Numeric Macros                                                             */

#define KB                              LX_KB
#define MB                              LX_MB
#define GB                              LX_GB
#define TB                              LX_TB

#define ABS                             LX_ABS
#define EQUALS                          LX_EQUALS
#define GREATER                         LX_GREATER
#define LESSER                          LX_LESSER
#define POSITIVE                        LX_POSITIVE
#define UNEQUAL                         LX_UNEQUAL

#define ROLL_BITS_LEFT                  LX_ROLL_BITS_LEFT
#define ROLL_BITS_RIGHT                 LX_ROLL_BITS_RIGHT
#define IS_SET_BIT                      LX_IS_SET_BIT

/* -------------------------------------------------------------------------- */
/* String/Character Macros                                                    */

#define HEX_DIGIT                       LX_HEX_DIGIT
#define HEX_DIGIT_VAL                   LX_HEX_DIGIT_VAL
#define IS_ALPHA                        LX_IS_ALPHA
#define IS_BLANK                        LX_IS_BLANK
#define IS_DIGIT                        LX_IS_DIGIT
#define IS_HEX_DIGIT                    LX_IS_HEX_DIGIT
#define IS_LOWER_CASE                   LX_IS_LOWER_CASE
#define IS_SPACE                        LX_IS_SPACE
#define IS_SYMBOL                       LX_IS_SYMBOL
#define IS_UPPER_CASE                   LX_IS_UPPER_CASE
#define STR_EQUAL                       LX_STR_EQUAL

/* Variable-Size Character Macros: */
#define CHAR_GET                        LX_CHAR_GET
#define CHAR_GET_AT                     LX_CHAR_GET_AT
#define CHAR_PUT                        LX_CHAR_PUT

/* -------------------------------------------------------------------------- */
/* Miscellaneous Macros: */

#define CASE                            LX_CASE
#define CASE_TO_TEXT                    LX_CASE_TO_TEXT
#define CHAR_TO_STR                     LX_CHAR_TO_STR
#define CLEAR_CHARS                     LX_CLEAR_CHARS
#define CLEAR_N                         LX_CLEAR_N
#define CLEAR_VARIANT                   LX_CLEAR_VARIANT
#define CLEAR                           LX_CLEAR
#define IMPLEMENT                       LX_IMPLEMENT
#define TEST_CODE                       LX_TEST_CODE
#define TRANSLITERATE                   LX_TRANSLITERATE

#endif                                                                   /*eof*/
