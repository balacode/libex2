/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                      [libex_stringc_.h] [cat:strings] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_STRINGC__H
#define      INCLUDED_LIBEX_STRINGC__H
#include "libex_stringc.h"

#define enable_chars_warnings           lx_enable_chars_warnings

#define chars_format_enum               lx_chars_format_enum
#define ANSI                            LX_ANSI
#define DEFAULT                         LX_DEFAULT
#define WIDE                            LX_WIDE

#define token_info_enum                 lx_token_info_enum
#define TOKEN_COUNT                     LX_TOKEN_COUNT
#define TOKEN_EXISTS                    LX_TOKEN_EXISTS
#define TOKEN_INDEX                     LX_TOKEN_INDEX

#define trim_enum                       lx_trim_enum
#define TRIM_ALL                        LX_TRIM_ALL
#define TRIM_BEGIN                      LX_TRIM_BEGIN
#define TRIM_END                        LX_TRIM_END
#define TRIM_NONE                       LX_TRIM_NONE

#define make_change_enum                lx_make_change_enum
#define MAKE_FILLED                     LX_MAKE_FILLED
#define MAKE_LOWER_CASE                 LX_MAKE_LOWER_CASE
#define MAKE_REVERSE                    LX_MAKE_REVERSE
#define MAKE_SAME                       LX_MAKE_SAME
#define MAKE_TITLE_CASE                 LX_MAKE_TITLE_CASE
#define MAKE_UPPER_CASE                 LX_MAKE_UPPER_CASE

#define IGNORE_CASE                     LX_IGNORE_CASE
#define MATCH_CASE                      LX_MATCH_CASE

/* -------------------------------------------------------------------------- */
/* Functions: Standard                                                        */

#define strstriT                        lx_strstriT

/* -------------------------------------------------------------------------- */
/* Functions: Character String Allocating                                     */

#define append2T                        lx_append2T //RR
#define append3T                        lx_append3T
#define append4T                        lx_append4T
#define append5T                        lx_append5T
#define append6T                        lx_append6T
#define append7T                        lx_append7T
#define append8T                        lx_append8T
#define append9T                        lx_append9T
#define appendnT                        lx_appendnT
#define appendT                         lx_appendT
#define formatA                         lx_formatA
#define formatT                         lx_formatT
#define formatW                         lx_formatW
#define mallocT                         lx_mallocT
#define reallocT                        lx_reallocT
#define repeat2T                        lx_repeat2T
#define set_default_inT                 lx_set_default_inT
#define set_inT                         lx_set_inT
#define T_bchars_n                      lx_T_bchars_n
#define T_chars_n                       lx_T_chars_n
#define T_decode_base64                 lx_T_decode_base64
#define T_double                        lx_T_double
#define T_encode_base64                 lx_T_encode_base64
#define T_first                         lx_T_first
#define T_format_numeric                lx_T_format_numeric
#define T_get_tag                       lx_T_get_tag
#define T_get_token                     lx_T_get_token
#define T_get_token_xt                  lx_T_get_token_xt
#define T_hex                           lx_T_hex
#define T_int                           lx_T_int
#define T_join                          lx_T_join
#define T_last                          lx_T_last
#define T_lower                         lx_T_lower
#define T_malloc_id                     lx_T_malloc_id
#define T_offset                        lx_T_offset
#define T_realloc_id                    lx_T_realloc_id
#define T_remove_tag                    lx_T_remove_tag
#define T_repeat                        lx_T_repeat
#define T_replace                       lx_T_replace
#define T_set_token                     lx_T_set_token
#define T_substr                        lx_T_substr
#define T_title                         lx_T_title
#define T_tokenize                      lx_T_tokenize
#define T_uint                          lx_T_uint
#define T_uint64                        lx_T_uint64
#define T_upper                         lx_T_upper
#define T_wchars_n                      lx_T_wchars_n
#define T_bchars                        lx_T_bchars
#define T_chars                         lx_T_chars
#define to_bytesT                       lx_to_bytesT
#define to_utf8T                        lx_to_utf8T
#define Tutf8                           lx_Tutf8
#define Twchars                         lx_Twchars
#define utf8_of_wide                  lx_utf8_of_wide
#define wide_of_utf8                  lx_wide_of_utf8

/* -------------------------------------------------------------------------- */
/* Character String Destructor:                                               */

#define freeA                           lx_freeA
#define freeT                           lx_freeT
#define freeW                           lx_freeW

/* -------------------------------------------------------------------------- */
/* Functions: In-Place Character String Manipulation                          */

#define change_in_T                     lx_change_in_T
#define remove_extra_spaces_in_T        lx_remove_extra_spaces_in_T
#define set_replace_char                lx_set_replace_char
#define replace_char_in_T               lx_replace_char_in_T
#define lower_in_T                      lx_lower_in_T
#define replace_in_T                    lx_replace_in_T
#define title_in_T                      lx_title_in_T
#define upper_in_T                      lx_upper_in_T
#define trim4_in_T                      lx_trim4_in_T
#define trim_in_T                       lx_trim_in_T

/* -------------------------------------------------------------------------- */
/* Functions: Informative                                                     */

#define begins3T                        lx_begins3T
#define beginsT                         lx_beginsT
#define contains2T                      lx_contains2T
#define contains3T                      lx_contains3T
#define contains4T                      lx_contains4T
#define containsT                       lx_containsT
#define count6T                         lx_count6T
#define countT                          lx_countT
#define doubleT                         lx_doubleT
#define ends2T                          lx_ends2T
#define ends3T                          lx_ends3T
#define ends4T                          lx_ends4T
#define endsT                           lx_endsT
#define equals_icT                      lx_equals_icT
#define equals2T                        lx_equals2T
#define equalsT                         lx_equalsT
#define find_chars2T                    lx_find_chars2T
#define find_chars3T                    lx_find_chars3T
#define find_charsT                     lx_find_charsT
#define find_charT                      lx_find_charT
#define find_last_T                     lx_find_last_T
#define find_last3T                     lx_find_last3T
#define find2T                          lx_find2T
#define find3T                          lx_find3T
#define find4T                          lx_find4T
#define find5T                          lx_find5T
#define find6T                          lx_find6T
#define findT                           lx_findT
#define hex_value                       lx_hex_value
#define int_T                           lx_int_T
#define IS_BLANK                        LX_IS_BLANK
#define is_number1T                     lx_is_number1T
#define is_number2T                     lx_is_number2T
#define is_number3T                     lx_is_number3T
#define is_numberT                      lx_is_numberT
#define is_unicode_mode                 lx_is_unicode_mode
#define is_whitespaceT                  lx_is_whitespaceT
#define is_wide                         lx_is_wide
#define is_wide_n                       lx_is_wide_n
#define len_maxT                        lx_len_maxT
#define lenT                            lx_lenT
#define likeT                           lx_likeT
#define line_countT                     lx_line_countT
#define patternMatch2T                  lx_patternMatch2T
#define patternMatchT                   lx_patternMatchT
#define skip_chars2T                    lx_skip_chars2T
#define skip_chars3T                    lx_skip_chars3T
#define skip_charsT                     lx_skip_charsT
#define substr_lenT                     lx_substr_lenT
#define token_countT                    lx_token_countT
#define token_info_xtT                  lx_token_info_xtT
#define token_infoT                     lx_token_infoT
#define uint_of_T                       lx_uint_of_T

/* -------------------------------------------------------------------------- */
/* Functions: UTF-8                                                           */

#define utf8_len                        lx_utf8_len

/* -------------------------------------------------------------------------- */
/* Functions: Windows-specific OLE Strings                                    */

#if LX_PLATFORM_WIN32
#define bstr_exA                        lx_bstr_exA
#define bstr_exT                        lx_bstr_exT
#define bstr_exW                        lx_bstr_exW
#define bstr_of_T                       lx_bstr_of_T
#define bstrA                           lx_bstrA
#define bstrW                           lx_bstrW
#define T_bstr                          lx_T_bstr
#endif

/* -------------------------------------------------------------------------- */
/* Methods: Unimplemented                                                     */

#define T_pad                           lx_T_pad
#define T_pad_xt                        lx_T_pad_xt

#endif                                                                   /*eof*/
