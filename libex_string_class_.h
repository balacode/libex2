/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                 [libex_string_class_.h] [cat:strings] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_STRING_CLASS__H
#define      INCLUDED_LIBEX_STRING_CLASS__H
#include "libex_string_class.h"

#define STR_INITIAL_CAPACITY            LX_STR_INITIAL_CAPACITY
#define enable_string_warnings          lx_enable_string_warnings

#define str_t                           lx_str_t
#define new_str_t                       lx_new_str_t

/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */

#define S_append                        lx_S_append
#define S_bchars                        lx_S_bchars
#define S_blank                         lx_S_blank
#define S_bracket                       lx_S_bracket
#define S_bsubstr                       lx_S_bsubstr
#define S_chars                         lx_S_chars
#define S_copy                          lx_S_copy
#define S_decodeBase64                  lx_S_decodeBase64
#define S_encodeBase64                  lx_S_encodeBase64
#define S_first                         lx_S_first
#define S_firstChars                    lx_S_firstChars
#define S_formatNumeric                 lx_S_formatNumeric
#define S_getTag                        lx_S_getTag
#define S_getToken                      lx_S_getToken
#define S_getTokenXt                    lx_S_getTokenXt
#define S_insert                        lx_S_insert
#define S_last                          lx_S_last
#define S_lowerCase                     lx_S_lowerCase
#define S_newT                          lx_S_newT
#define S_quote                         lx_S_quote
#define S_remove                        lx_S_remove
#define S_removeBegin                   lx_S_removeBegin
#define S_removeChar                    lx_S_removeChar
#define S_removeEnd                     lx_S_removeEnd
#define S_removeStr                     lx_S_removeStr
#define S_repeat                        lx_S_repeat
#define S_replace                       lx_S_replace
#define S_replaceByRef                  lx_S_replaceByRef
#define S_reserve                       lx_S_reserve
#define S_reverse                       lx_S_reverse
#define S_setToken                      lx_S_setToken
#define S_sortList                      lx_S_sortList
#define S_space                         lx_S_space
#define S_substr                        lx_S_substr
#define S_titleCase                     lx_S_titleCase
#define S_trim                          lx_S_trim
#define S_trimBegin                     lx_S_trimBegin
#define S_trimBeginChar                 lx_S_trimBeginChar
#define S_trimChar                      lx_S_trimChar
#define S_trimEnd                       lx_S_trimEnd
#define S_trimEndChar                   lx_S_trimEndChar
#define S_trimStr                       lx_S_trimStr
#define S_double                         lx_S_double
#define S_trim1                          lx_S_trim1
#define S_trim2                          lx_S_trim2
#define S_uint                           lx_S_uint
#define S_unquote                        lx_S_unquote
#define S_upperCase                      lx_S_upperCase
#define S_wchars                         lx_S_wchars
#define S_wchars_n                       lx_S_wchars_n

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

#define freeS                           lx_freeS

/* -------------------------------------------------------------------------- */
/* Methods: Void                                                              */

#define add3S                           lx_add3S
#define addAS                           lx_addAS
#define addCharS                        lx_addCharS
#define addIntS                         lx_addIntS
#define addTS                           lx_addTS
#define addWS                           lx_addWS
#define closeBufferS                    lx_closeBufferS
#define copyFromBufferS                 lx_copyFromBufferS
#define copyToBufferS                   lx_copyToBufferS
#define freeConversionBufferS           lx_freeConversionBufferS
#define reserveInS                      lx_reserveInS
#define setCopyAnsiS                    lx_setCopyAnsiS
#define setCopyCharS                    lx_setCopyCharS
#define setCopyS                        lx_setCopyS
#define setCopyWideS                    lx_setCopyWideS
#define decodeBase64InS                 lx_decodeBase64InS
#define delimitNumberInS                lx_delimitNumberInS
#define clearInS                        lx_clearInS
#define encodeBase64InS                 lx_encodeBase64InS
#define firstInS                        lx_firstInS
#define format10InS                     lx_format10InS
#define format11InS                     lx_format11InS
#define format3InS                      lx_format3InS
#define format4InS                      lx_format4InS
#define format5InS                      lx_format5InS
#define format6InS                      lx_format6InS
#define format7InS                      lx_format7InS
#define format8InS                      lx_format8InS
#define format9InS                      lx_format9InS
#define formatNumericInS                lx_formatNumericInS
#define formatInS                       lx_formatInS
#define insert3InS                      lx_insert3InS
#define insertInS                       lx_insertInS
#define lastInS                         lx_lastInS
#define tolowerInS                      lx_tolowerInS
#define removeEndInS                    lx_removeEndInS
#define removeInS                       lx_removeInS
#define replace3InS                     lx_replace3InS
#define replace4InS                     lx_replace4InS
#define setReplaceS                     lx_setReplaceS
#define reverseInS                      lx_reverseInS
#define setInS                          lx_setInS
#define sortListInS                     lx_sortListInS
#define spaceInS                        lx_spaceInS
#define totitleInS                      lx_totitleInS
#define toupperInS                      lx_toupperInS
#define trimEndInS                      lx_trimEndInS
#define trimIn1S                        lx_trimIn1S
#define trimIn2S                        lx_trimIn2S
#define trimInS                         lx_trimInS

/* -------------------------------------------------------------------------- */
/* Methods: Informative                                                       */

#define bcharsS                         lx_bcharsS
#define begins2S                        lx_beginsS
#define beginsS                         lx_beginsXtS
#define byteSizeS                       lx_byteSizeS
#define capacityS                       lx_capacityS
#define charsS                          lx_charsS
#define contains2S                      lx_contains2S
#define containsS                       lx_containsS
#define countS                          lx_countS
#define doubleS                         lx_doubleS
#define emptyS                          lx_emptyS
#define ends2S                          lx_ends2S
#define endsS                           lx_endsS
#define equal2S                         lx_equal2S
#define equalS                          lx_equalS
#define find2S                          lx_find2S
#define find3S                          lx_find3S
#define find4S                          lx_find4S
#define findChar2S                      lx_findChar2S
#define findChar3S                      lx_findChar3S
#define findChar4S                      lx_findChar4S
#define findCharS                       lx_findCharS
#define findChars2S                     lx_findChars2S
#define findCharsS                      lx_findCharsS
#define findEndChar4S                   lx_findEndChar4S
#define findEndCharS                    lx_findEndCharS
#define findEndS                        lx_findEndS
#define findFirstNotOfS                 lx_findFirstNotOfS
#define findS                           lx_findS
#define getBufferS                      lx_getBufferS
#define getEmptyBufferS                 lx_getEmptyBufferS
#define intS                            lx_intS
#define isNumberS                       lx_isNumberS
#define isSpaceS                        lx_isSpaceS
#define lengthS                         lx_lengthS
#define like3S                          lx_like3S
#define likeS                           lx_likeS
#define lineCountS                      lx_lineCountS
#define patternMatchS                   lx_patternMatchS
#define skipCharsS                      lx_skipCharsS
#define tokenCountS                     lx_tokenCountS
#define tokenCountXtS                   lx_tokenCountXtS
#define tokenExistsS                    lx_ExistsTokenS
#define tokenIndexS                     lx_tokenIndexS
#define uintS                           lx_uintS
#define wcharsS                         lx_wcharsS

/* -------------------------------------------------------------------------- */
/* Functions: String Allocating                                               */

#define S_hex                           lx_S_hex

/* -------------------------------------------------------------------------- */
/* Functions: Windows-specific OLE Strings                                    */

#if LX_PLATFORM_WIN32
#define S_of_bstr                       lx_S_of_bstr
#endif

#endif                                                                   /*eof*/
