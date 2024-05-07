/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                [libex_string_class.h] */
/* -------------------------------------------------------------------------- */

#if (defined __GNUC__ || defined __clang__) && !defined __MINGW32__
#pragma GCC diagnostic ignored "-Wunused-macros"
#endif

#if !defined INCLUDED_LIBEX_STRING_CLASS_H
#define      INCLUDED_LIBEX_STRING_CLASS_H

#include "libex.h"
#include "libex_stringc.h"

#if LX_PLATFORM_WIN32
#include "libex_win32.h"
#endif

#define LX_STR_INITIAL_CAPACITY  64

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

extern lx_bool  lx_enable_string_warnings;

typedef struct  lx_str_t {
    lx_chars_t  cs;                                               /* lx_str_t */
} lx_str_t, lx_new_str_t;

/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */

LX_PUBLIC lx_new_str_t  lx_S_chars( lx_chars_t const  text_ );             /*C*/

LX_PUBLIC lx_new_str_t  lx_S_append(                                       /*C*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  string_ );                                           /*-*/

LX_PUBLIC lx_new_str_t  lx_S_blank( void );                                /*C*/

LX_PUBLIC lx_new_str_t  lx_S_copy( const lx_str_t  source_ );              /*C*/

LX_PUBLIC lx_new_str_t  lx_S_firstChars(                                   /*C*/
    lx_chars_t const  chars_,                                              /*-*/
    const size_t      len_ );                                              /*-*/

LX_PUBLIC lx_new_str_t  lx_S_formatNumeric(                                /*C*/
    lx_chars_t const  string_,                                             /*-*/
    const int         decimal_places_,                                     /*-*/
    const int         group_digits_1_,                                     /*-*/
    const int         group_digits_2_,                                     /*-*/
    const int         group_digits_3_,                                     /*-*/
    const lx_char_t   decimal_point_char_,                                 /*-*/
    const lx_char_t   group_delimiter_char_ );                             /*-*/

/* TODO: Use macro instead of lx_S_bchars(). */
LX_PUBLIC lx_new_str_t  lx_S_bchars( const char* const  source_ );         /*C*/

LX_PUBLIC lx_new_str_t  lx_S_bsubstr(                                      /*C*/
    const char* const  source_,                                            /*-*/
    const size_t       offset_,                                            /*-*/
    const size_t       count_ );                                           /*-*/

LX_PUBLIC lx_new_str_t  lx_S_bchars( const char* const  chars_ );          /*C*/

LX_PUBLIC lx_new_str_t  lx_S_wchars( const wchar_t* const  chars_ );       /*C*/

LX_PUBLIC lx_new_str_t  lx_S_newT( lx_new_chars_t const  text_ );          /*C*/

/* TODO: lx_S_wchars(). Use macro instead. */
LX_PUBLIC lx_new_str_t  lx_S_wchars( const wchar_t* const  source_ );      /*C*/

LX_PUBLIC lx_new_str_t  lx_S_wchars_n(                                     /*C*/
    const wchar_t* const  source_,                                         /*-*/
    const size_t          source_len_,                                     /*-*/
    const size_t          offset_,                                         /*-*/
    const size_t          substr_len_ );                                   /*-*/

LX_PUBLIC lx_new_str_t  lx_S_repeat(                                       /*C*/
    lx_chars_t const  string_,                                             /*-*/
    const int         count_,                                              /*-*/
    const int         max_len_ );                                          /*-*/
/*                    string_ : String to be repeated.              */
/*                    count_  : Max. no. string can repeat.         */
/*                    max_len_: Max. length of the returned string. */

LX_PUBLIC lx_new_str_t  lx_S_reserve( const size_t  char_capacity_ );      /*C*/

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

LX_PUBLIC void  lx_freeS( lx_str_t* const  object_ );                      /*D*/

/* -------------------------------------------------------------------------- */
/* Methods: Void                                                              */

LX_PUBLIC void  lx_closeBufferS( lx_str_t* const  object_ );               /*M*/

LX_PUBLIC void  lx_copyFromBufferS(                                        /*M*/
    lx_str_t* const   object_,                                             /*-*/
    lx_chars_t const  buffer_,                                             /*-*/
    const size_t      buffer_len_ );                                       /*-*/

LX_PUBLIC void  lx_copyToBufferS(                                          /*M*/
    const lx_str_t  object_,                                               /*-*/
    lx_char_t*      buffer_,                                               /*-*/
    const size_t    buffer_len_ );                                         /*-*/

LX_PUBLIC void  lx_freeConversionBufferS( lx_str_t* const  object_ );      /*M*/

LX_PUBLIC void  lx_addS(                                                   /*O*/
    lx_str_t* const  object_,                                              /*-*/
    const lx_str_t   source_ );                                            /*-*/

LX_PUBLIC void  lx_addTS(                                                  /*M*/
    lx_str_t* const   object_,                                             /*-*/
    lx_chars_t const  string_ );                                           /*-*/

LX_PUBLIC void  lx_addAS(                                                  /*O*/
    lx_str_t* const    object_,                                            /*-*/
    const char* const  string_ );                                          /*-*/

LX_PUBLIC void  lx_addIntS(                                                /*O*/
    lx_str_t* const  object_,                                              /*-*/
    const int        number_ );                                            /*-*/

LX_PUBLIC void  lx_addWS(                                                  /*O*/
    lx_str_t* const       object_,                                         /*-*/
    const wchar_t* const  string_ );                                       /*-*/

LX_PUBLIC void  lx_setInS(                                                 /*M*/
    lx_str_t* const   object_,                                             /*-*/
    lx_chars_t const  string_ );                                           /*-*/

LX_PUBLIC void  lx_add3S(                                                  /*M*/
    lx_str_t* const   object_,                                             /*-*/
    lx_chars_t const  string_,                                             /*-*/
    const size_t      length_ );                                           /*-*/

LX_PUBLIC void  lx_addCharS(                                               /*M*/
    lx_str_t* const  object_,                                              /*-*/
    const lx_char_t  char_ );                                              /*-*/

LX_PUBLIC void  lx_addIntS(                                                /*M*/
    lx_str_t* const  object_,                                              /*-*/
    const int        number_ );                                            /*-*/

LX_PUBLIC void  lx_reserveInS(                                             /*M*/
    lx_str_t* const  object_,                                              /*-*/
    const size_t     char_capacity_ );                                     /*-*/

LX_PUBLIC void  lx_setCopyS(                                               /*M*/
    lx_str_t* const  object_,                                              /*-*/
    const lx_str_t   string_ );                                            /*-*/

LX_PUBLIC void  lx_setCopyAnsiS(                                           /*M*/
    lx_str_t* const    object_,                                            /*-*/
    const char* const  string_ );                                          /*-*/

LX_PUBLIC void  lx_setCopyCharS(                                           /*M*/
    lx_str_t* const  object_,                                              /*-*/
    const lx_char_t  char_ );                                              /*-*/

LX_PUBLIC void  lx_setCopyWideS(                                           /*M*/
    lx_str_t* const       object_,                                         /*-*/
    const wchar_t* const  string_ );                                       /*-*/

LX_PUBLIC void  lx_decodeBase64InS( lx_str_t* const  object_ );            /*M*/

LX_PUBLIC void  lx_delimitNumberInS(                                       /*M*/
    lx_str_t* const  object_,                                              /*-*/
    const size_t     decimal_places_,                                      /*-*/
    const size_t     digits_1_,                                            /*-*/
    const size_t     digits_2_,                                            /*-*/
    const size_t     digits_3_,                                            /*-*/
    const lx_char_t  decimal_point_char_,                                  /*-*/
    const lx_char_t  group_char_ );                                        /*-*/

LX_PUBLIC void  lx_clearInS( lx_str_t* const  object_ );                   /*M*/

LX_PUBLIC void  lx_encodeBase64InS( lx_str_t* const  object_ );            /*M*/

#if defined LX_UNUSED_CODE

LX_PUBLIC void  lx_fillInS(                                                /*M*/
    lx_str_t* const  object_,                                              /*-*/
    const lx_char_t  char_,                                                /*-*/
    const size_t     length_,                                              /*-*/
    const lx_bool    align_to_end_,                                        /*-*/
    const lx_bool    spillover_,                                           /*-*/
    const lx_bool    clear_contents_ );                                    /*-*/

#define lx_setFill3S( OBJECT_, CHAR_, LENGTH_ )                           /*M*/\
    lx_fillInS(      OBJECT_, CHAR_, LENGTH_,                                 \
                     LX_C_FALSE, LX_C_FALSE, LX_C_FALSE)                  /*#*/

#define lx_setFill4S( OBJECT_, CHAR_, LENGTH_, ALIGN_TO_END_ )            /*M*/\
    lx_fillInS(      OBJECT_, CHAR_, LENGTH_, ALIGN_TO_END_,                   \
                     LX_C_FALSE, LX_C_FALSE)                               /*#*/

#define lx_setFill5S( OBJECT_, CHAR_, LENGTH_, ALIGN_TO_END_,             /*M*/\
                      SPILLOVER_ )                                             \
lx_fillInS(          OBJECT_, CHAR_, LENGTH_, ALIGN_TO_END_,                   \
                     SPILLOVER_, LX_C_FALSE)                               /*#*/

#endif                                                        //# LX_UNUSED_CODE

LX_PUBLIC void  lx_firstInS(                                               /*M*/
    lx_str_t* const  object_,                                              /*-*/
    const size_t     length_ );                                            /*-*/

LX_PUBLIC void  lx_formatInS(                                              /*M*/
    lx_str_t* const   object_,                                             /*-*/
    lx_chars_t const  format_,                                             /*-*/
    lx_chars_t const  str_0_,                                              /*-*/
    lx_chars_t const  str_1_,                                              /*-*/
    lx_chars_t const  str_2_,                                              /*-*/
    lx_chars_t const  str_3_,                                              /*-*/
    lx_chars_t const  str_4_,                                              /*-*/
    lx_chars_t const  str_5_,                                              /*-*/
    lx_chars_t const  str_6_,                                              /*-*/
    lx_chars_t const  str_7_,                                              /*-*/
    lx_chars_t const  str_8_,                                              /*-*/
    lx_chars_t const  str_9_ );                                            /*-*/

#define lx_format10InS( OBJECT_, FORMAT_,                                 /*M*/\
                        S0_, S1_, S2_, S3_,                                    \
                        S4_, S5_, S6_, S7_ )                                   \
lx_formatInS(           OBJECT_, FORMAT_,                                      \
                        S0_, S1_, S2_, S3_,                                    \
                        S4_, S5_, S6_, S7_,                                    \
                        0, 0)                                              /*#*/

#define lx_format11InS( OBJECT_, FORMAT_,                                 /*M*/\
                        S0_, S1_, S2_, S3_,                                    \
                        S4_, S5_, S6_, S7_, S8_ )                              \
lx_formatInS(           OBJECT_, FORMAT_,                                      \
                        S0_, S1_, S2_, S3_,                                    \
                        S4_, S5_, S6_, S7_, S8_,                               \
                        0)                                                 /*#*/

#define lx_format3InS( OBJECT_, FORMAT_, STR0_ )                          /*M*/\
    lx_formatInS(      OBJECT_, FORMAT_, STR0_,                                \
                       0, 0, 0, 0, 0, 0, 0, 0, 0)                          /*#*/

#define lx_format4InS( OBJECT_, FORMAT_, STR0_, S1_ )                     /*M*/\
    lx_formatInS(      OBJECT_, FORMAT_, STR0_, S1_,                           \
                       0, 0, 0, 0, 0, 0, 0, 0)                             /*#*/

#define lx_format5InS( OBJECT_, FORMAT_, STR0_, S1_, S2_ )                /*M*/\
    lx_formatInS(      OBJECT_, FORMAT_, STR0_, S1_, S2_,                      \
                       0, 0, 0, 0, 0, 0, 0)                                /*#*/

#define lx_format6InS( OBJECT_, FORMAT_, STR0_, S1_, S2_, S3_ )           /*M*/\
    lx_formatInS(      OBJECT_, FORMAT_, STR0_, S1_, S2_, S3_,                 \
                       0, 0, 0, 0, 0, 0)                                   /*#*/

#define lx_format7InS( OBJECT_, FORMAT_, STR0_,                           /*M*/\
                       S1_, S2_, S3_, S4_ )                                    \
lx_formatInS(          OBJECT_, FORMAT_, STR0_,                                \
                       S1_, S2_, S3_, S4_,                                     \
                       0, 0, 0, 0, 0)                                      /*#*/

#define lx_format8InS( OBJECT_, FORMAT_, STR0_,                           /*M*/\
                       S1_, S2_, S3_, S4_, S5_ )                               \
lx_formatInS(          OBJECT_, FORMAT_, STR0_,                                \
                       S1_, S2_, S3_, S4_, S5_,                                \
                       0, 0, 0, 0)                                         /*#*/

#define lx_format9InS( OBJECT_, FORMAT_, STR0_,                           /*M*/\
                       S1_, S2_, S3_, S4_, S5_, S6_ )                          \
lx_formatInS(          OBJECT_, FORMAT_, STR0_,                                \
                       S1_, S2_, S3_, S4_, S5_, S6_,                           \
                       0, 0, 0)                                            /*#*/

/* format this string as a numeric string                                     */
LX_PUBLIC void  lx_formatNumericInS(                                       /*M*/
    lx_str_t* const  object_,                                              /*-*/
    const int        decimal_places_,                                      /*-*/
    const int        group_digits_1_,                                      /*-*/
    const int        group_digits_2_,                                      /*-*/
    const int        group_digits_3_,                                      /*-*/
    const lx_char_t  decimal_point_char_,                                  /*-*/
    const lx_char_t  group_delimiter_char_ );                              /*-*/

LX_PUBLIC void  lx_insertInS(                                              /*M*/
    lx_str_t* const   object_,                                             /*-*/
    lx_chars_t const  string_,                                             /*-*/
    const size_t      insert_at_position_,                                 /*-*/
    const size_t      length_ );                                           /*-*/

#define lx_insert3InS( OBJECT_, STRING_, INSERT_AT_POSITION_ )            /*M*/\
    lx_insertInS(      OBJECT_, STRING_, INSERT_AT_POSITION_,                  \
                       SIZE_MAX)                                           /*#*/

LX_PUBLIC void  lx_lastInS(                                                /*M*/
    lx_str_t* const  object_,                                              /*-*/
    const size_t     length_ );                                            /*-*/

LX_PUBLIC void  lx_tolowerInS( lx_str_t* const  object_ );                 /*M*/

LX_PUBLIC void  lx_removeInS(                                              /*M*/
    lx_str_t* const  object_,                                              /*-*/
    const size_t     position_,                                            /*-*/
    const size_t     char_count_ );                                        /*-*/

LX_PUBLIC void  lx_removeEndInS(                                           /*M*/
    lx_str_t* const  object_,                                              /*-*/
    const size_t     char_count_ );                                        /*-*/

LX_PUBLIC void  lx_setReplaceS(                                            /*M*/
    lx_str_t* const   object_,                                             /*-*/
    lx_chars_t const  find_str_,                                           /*-*/
    lx_chars_t const  replace_str_,                                        /*-*/
    const lx_bool     ignore_case_,                                        /*-*/
    const size_t      find_len_,                                           /*-*/
    const size_t      replace_len_ );                                      /*-*/

/* object_      : pointer to string object                                    */
/* find_str_    : string being searched for                                   */
/* replace_str_ : replacement string                                          */
/* ignore_case_ : LX_MATCH_CASE / LX_IGNORE_CASE                              */
/* find_len_    : length of find_str_ in characters                           */
/* replace_len_ : length of replace_str_ in characters                        */

#define lx_replace3InS( OBJECT_, FIND_STR_, REPLACE_STR_ )                /*M*/\
    lx_setReplaceS(      OBJECT_, FIND_STR_, REPLACE_STR_,                     \
                         LX_MATCH_CASE, SIZE_MAX, SIZE_MAX)                /*#*/

#define lx_replace4InS( OBJECT_, FIND_STR_, REPLACE_STR_,                 /*M*/\
                        ignore_case_ )                                        \
lx_setReplaceS(          OBJECT_, FIND_STR_, REPLACE_STR_,                     \
                         ignore_case_, SIZE_MAX, SIZE_MAX)                 /*#*/

LX_PUBLIC void  lx_reverseInS( lx_str_t* const  object_ );                 /*M*/

LX_PUBLIC void  lx_sortListInS(                                            /*M*/
    lx_str_t* const   object_,                                             /*-*/
    lx_chars_t const  delimiter_,                                          /*-*/
    const lx_bool     descending_,                                         /*-*/
    const lx_bool     unique_ );                                           /*-*/

LX_PUBLIC void  lx_spaceInS(                                               /*M*/
    lx_str_t* const  object_,                                              /*-*/
    const size_t     length_,                                              /*-*/
    const lx_bool    align_to_end_,                                        /*-*/
    const lx_bool    spillover_ );                                         /*-*/

LX_PUBLIC void  lx_totitleInS( lx_str_t* const  object_ );                 /*M*/

LX_PUBLIC void  lx_trimInS(                                                /*M*/
    lx_str_t* const     object_,                                           /*-*/
    lx_chars_t const    trim_chars_,                                       /*-*/
    const lx_trim_enum  trim_scope_ );                                     /*-*/

#define lx_trimIn1S( OBJECT_ )                                            /*M*/\
    lx_trimInS(      OBJECT_,                                                  \
                     LX_WHITESPACES, LX_CL LX_TRIM_ALL);                   /*#*/

#define lx_trimIn2S( OBJECT_, TRIM_CHARS_ )                               /*M*/\
    lx_trimInS(      OBJECT_, TRIM_CHARS_, LX_CL LX_TRIM_ALL);            /*#*/

#define lx_trimEndInS( OBJECT_ )                                          /*M*/\
    lx_trimInS(        OBJECT_,                                                \
                       LX_WHITESPACES, LX_CL LX_TRIM_END);                 /*#*/

LX_PUBLIC void  lx_toupperInS( lx_str_t* const  object_ );                 /*M*/

/* -------------------------------------------------------------------------- */
/* Methods: Informative                                                       */

LX_PUBLIC lx_bool  lx_beginsXtS(                                           /*M*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  string_,                                             /*-*/
    const lx_bool     ignore_case_ );                                      /*-*/

#define lx_beginsS( OBJECT_, STRING_ )                                    /*M*/\
    lx_beginsXtS(   OBJECT_, STRING_, LX_CL LX_MATCH_CASE)                 /*#*/

LX_PUBLIC size_t  lx_byteSizeS( const lx_str_t  object_ );                 /*M*/

LX_PUBLIC size_t  lx_capacityS( const lx_str_t  object_ );                 /*M*/

LX_PUBLIC const char*  lx_bcharsS( const lx_str_t  object_ );              /*M*/

LX_PUBLIC lx_chars_t  lx_charsS( const lx_str_t  object_ );                /*M*/

LX_PUBLIC lx_bool  lx_containsS(                                           /*M*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  substring_,                                          /*-*/
    const lx_bool     ignore_case_ );                                      /*-*/

#define lx_contains2S( OBJECT_, SUBSTRING_ )                              /*M*/\
    lx_containsS(      OBJECT_, SUBSTRING_, LX_CL LX_MATCH_CASE)           /*#*/

LX_PUBLIC size_t  lx_countS(                                               /*M*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  string_,                                             /*-*/
    const lx_bool     ignore_case_,                                        /*-*/
    const size_t      offset_ );                                           /*-*/

LX_PUBLIC lx_bool  lx_endsS(                                               /*M*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  string_,                                             /*-*/
    const lx_bool     ignore_case_ );                                      /*-*/

#define lx_ends2S( OBJECT_, STRING_ )                                     /*M*/\
    lx_endsS(      OBJECT_, STRING_, LX_CL LX_MATCH_CASE)                  /*#*/

LX_PUBLIC lx_bool  lx_equalS(                                              /*M*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  string_,                                             /*-*/
    const lx_bool     ignore_case_ );                                      /*-*/

#define lx_equal2S( OBJECT_, STRING_ )                                    /*M*/\
    lx_equalS(      OBJECT_, STRING_, LX_CL LX_MATCH_CASE)                 /*#*/

LX_PUBLIC size_t  lx_findS(                                                /*M*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  find_str_,                                           /*-*/
    const size_t      offset_,                                             /*-*/
    const lx_bool     ignore_case_,                                        /*-*/
    const lx_bool     from_end_ );                                         /*-*/

#define lx_find2S( OBJECT_, FIND_STR_ )                                   /*M*/\
    lx_findS(      OBJECT_, FIND_STR_,                                         \
                   0, LX_CL LX_MATCH_CASE, LX_C_FALSE)                     /*#*/

#define lx_find3S( OBJECT_, FIND_STR_, BEGIN_AT_ )                        /*M*/\
    lx_findS(      OBJECT_, FIND_STR_, BEGIN_AT_,                              \
                   LX_CL LX_MATCH_CASE, LX_C_FALSE)                        /*#*/

#define lx_find4S( OBJECT_, FIND_STR_, BEGIN_AT_, ignore_case_ )          /*M*/\
    lx_findS(      OBJECT_, FIND_STR_, BEGIN_AT_, ignore_case_,                \
                   LX_C_FALSE)                                             /*#*/

LX_PUBLIC size_t  lx_findCharS(                                            /*M*/
    const lx_str_t   object_,                                              /*-*/
    const lx_char_t  find_char_,                                           /*-*/
    const size_t     offset_,                                              /*-*/
    const lx_bool    ignore_case_,                                         /*-*/
    const lx_bool    from_end_ );                                          /*-*/

#define lx_findChar2S( OBJECT_, FIND_CHAR_ )                              /*M*/\
    lx_findCharS(      OBJECT_, FIND_CHAR_,                                    \
                       0, LX_CL LX_MATCH_CASE, LX_C_FALSE);                /*#*/

#define lx_findChar3S( OBJECT_, FIND_CHAR_, BEGIN_AT_ )                   /*M*/\
    lx_findCharS(      OBJECT_, FIND_CHAR_, BEGIN_AT_,                         \
                       LX_CL LX_MATCH_CASE, LX_C_FALSE);                   /*#*/

#define lx_findChar4S                                                     /*M*/\
    (             OBJECT_, FIND_CHAR_, BEGIN_AT_, IGNORE_CASE_ )               \
    lx_findCharS( OBJECT_, FIND_CHAR_, BEGIN_AT_, IGNORE_CASE_,                \
                  LX_C_FALSE);                                             /*#*/

LX_PUBLIC size_t  lx_findCharsS(                                           /*M*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  chars_to_find_,                                      /*-*/
    const lx_bool     ignore_case_ );                                      /*-*/

#define lx_findChars2S( OBJECT_, CHARS_TO_FIND_ )                         /*M*/\
    lx_findCharsS(      OBJECT_, CHARS_TO_FIND_,                               \
                        LX_CL LX_MATCH_CASE)                               /*#*/

LX_PUBLIC size_t  lx_findEndS(                                             /*M*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  find_str_,                                           /*-*/
    const size_t      offset_,                                             /*-*/
    const lx_bool     ignore_case_ );                                      /*-*/

#define lx_findEndCharS( OBJECT_, FIND_CHAR_ )                            /*M*/\
    lx_findEndChar4S(    OBJECT_, FIND_CHAR_,                                  \
                         LX_CL LX_MATCH_CASE, 0)                           /*#*/

LX_PUBLIC size_t  lx_findEndChar4S(                                        /*M*/
    const lx_str_t   object_,                                              /*-*/
    const lx_char_t  find_char_,                                           /*-*/
    const lx_bool    ignore_case_,                                         /*-*/
    const size_t     offset_ );                                            /*-*/

LX_PUBLIC size_t  lx_findFirstNotOfS(                                      /*M*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  chars_ );                                            /*-*/

LX_PUBLIC lx_char_t*  lx_getBufferS( lx_str_t* const  object_ );           /*M*/


LX_PUBLIC lx_char_t*  lx_getEmptyBufferS(                                  /*M*/
    lx_str_t* const  object_,                                              /*-*/
    const size_t     length_ );                                            /*-*/

LX_PUBLIC lx_bool  lx_emptyS( const lx_str_t  object_ );                   /*P*/

LX_PUBLIC lx_bool  lx_isNumberS(                                           /*P*/
    const lx_str_t    object_,                                             /*-*/
    const lx_char_t   decimal_point_char_,                                 /*-*/
    const lx_char_t   group_separator_char_,                               /*-*/
    lx_chars_t const  whitespaces_ );                                      /*-*/

LX_PUBLIC lx_bool  lx_isSpaceS( const lx_str_t  object_ );                 /*P*/

LX_PUBLIC size_t  lx_lengthS( const lx_str_t  object_ );                   /*P*/

#define lx_likeS( OBJECT_, STRING_ )                                      /*M*/\
    lx_like3S(    OBJECT_, STRING_, LX_CL LX_MATCH_CASE)                   /*#*/

LX_PUBLIC lx_bool  lx_like3S(                                              /*M*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  string_,                                             /*-*/
    const lx_bool     ignore_case_ );                                      /*-*/

LX_PUBLIC int  lx_lineCountS( const lx_str_t  object_ );                   /*P*/

LX_PUBLIC lx_bool  lx_patternMatchS(                                       /*M*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  pattern_,                                            /*-*/
    const lx_bool     ignore_case_ );                                      /*-*/

LX_PUBLIC size_t  lx_skipCharsS(                                           /*M*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  chars_to_skip_,                                      /*-*/
    const lx_bool     ignore_case_ );                                      /*-*/

LX_PUBLIC double  lx_doubleS( const lx_str_t  object_ );                   /*M*/

LX_PUBLIC int  lx_intS( const lx_str_t  object_ );                         /*M*/

LX_PUBLIC size_t  lx_tokenCountXtS(                                        /*M*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  delimiter_,                                          /*-*/
    lx_chars_t const  token_,                                              /*-*/
    const lx_bool     ignore_case_ );                                      /*-*/

#define lx_tokenCountS( OBJECT_, DELIMITER_ )                             /*M*/\
    lx_tokenCountXtS(   OBJECT_, DELIMITER_,                                   \
                        NULL, LX_CL LX_MATCH_CASE)                         /*#*/

LX_PUBLIC lx_bool  lx_ExistsTokenS(                                        /*M*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  token_,                                              /*-*/
    lx_chars_t const  delimiter_,                                          /*-*/
    const lx_bool     ignore_case_ );                                      /*-*/

LX_PUBLIC size_t  lx_tokenIndexS(                                          /*M*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  token_,                                              /*-*/
    lx_chars_t const  delimiter_,                                          /*-*/
    const lx_bool     ignore_case_ );                                      /*-*/

LX_PUBLIC uint32_t  lx_uintS( const lx_str_t  object_ );                   /*M*/

LX_PUBLIC const wchar_t*  lx_wcharsS( const lx_str_t  object_ );           /*M*/

/* -------------------------------------------------------------------------- */
/* Methods: Allocating                                                        */

LX_PUBLIC lx_new_str_t  lx_S_bracket(                                      /*C*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  brackets_ );                                         /*-*/

LX_PUBLIC lx_new_str_t  lx_S_decodeBase64( const lx_str_t  object_ );      /*C*/

LX_PUBLIC lx_new_str_t  lx_S_double(                                       /*C*/
    const double      value_,                                              /*-*/
    lx_chars_t const  format_);                                            /*-*/

LX_PUBLIC lx_new_str_t  lx_S_encodeBase64( const lx_str_t  object_ );      /*C*/

LX_PUBLIC lx_new_str_t  lx_S_first(                                        /*C*/
    const lx_str_t  object_,                                               /*-*/
    const size_t    length_ );                                             /*-*/

LX_PUBLIC lx_new_str_t  lx_S_substr(                                       /*C*/
    const lx_str_t  object_,                                               /*-*/
    const size_t    offset_,                                               /*-*/
    const size_t    length_ );                                             /*-*/

LX_PUBLIC lx_new_str_t  lx_S_insert(                                       /*C*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  string_,                                             /*-*/
    const size_t      insert_at_position_,                                 /*-*/
    const size_t      length_ );                                           /*-*/

LX_PUBLIC lx_new_str_t  lx_S_last(                                         /*C*/
    const lx_str_t  object_,                                               /*-*/
    const size_t    length_ );                                             /*-*/

LX_PUBLIC lx_new_str_t  lx_S_lowerCase( const lx_str_t  object_ );         /*C*/

LX_PUBLIC lx_new_str_t  lx_S_quote(                                        /*C*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  quote_,                                              /*-*/
    lx_chars_t const  replace_ );                                          /*-*/

LX_PUBLIC lx_new_str_t  lx_S_remove(                                       /*C*/
    const lx_str_t  object_,                                               /*-*/
    const size_t    position_,                                             /*-*/
    const size_t    length_ );                                             /*-*/

LX_PUBLIC lx_new_str_t  lx_S_removeBegin(                                  /*C*/
    const lx_str_t  object_,                                               /*-*/
    const size_t    char_count_ );                                         /*-*/

LX_PUBLIC lx_new_str_t  lx_S_removeChar(                                   /*C*/
    const lx_str_t   object_,                                              /*-*/
    const lx_char_t  char_,                                                /*-*/
    const lx_bool    ignore_case_ );                                       /*-*/

LX_PUBLIC lx_new_str_t  lx_S_removeEnd(                                    /*C*/
    const lx_str_t  object_,                                               /*-*/
    const size_t    char_count_ );                                         /*-*/

LX_PUBLIC lx_new_str_t  lx_S_removeStr(                                    /*C*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  string_,                                             /*-*/
    const lx_bool     ignore_case_ );                                      /*-*/

LX_PUBLIC lx_new_str_t  lx_S_replace(                                      /*C*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  find_str_,                                           /*-*/
    lx_chars_t const  replace_str_,                                        /*-*/
    const lx_bool     ignore_case_ );                                      /*-*/

LX_PUBLIC lx_new_str_t  lx_S_replaceByRef(                                 /*C*/
    const lx_str_t  object_,                                               /*-*/
    const lx_str_t  find_,                                                 /*-*/
    const lx_str_t  replace_,                                              /*-*/
    const lx_bool   ignore_case_ );                                        /*-*/

LX_PUBLIC lx_new_str_t  lx_S_reverse( const lx_str_t  object_ );           /*C*/

LX_PUBLIC lx_new_str_t  lx_S_sortList(                                     /*C*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  delimiter_,                                          /*-*/
    const lx_bool     descending_,                                         /*-*/
    const lx_bool     unique_ );                                           /*-*/

LX_PUBLIC lx_new_str_t  lx_S_space(                                        /*C*/
    const lx_str_t  object_,                                               /*-*/
    const size_t    length_in_chars_,                                      /*-*/
    const lx_bool   align_to_end_,                                         /*-*/
    const lx_bool   spillover_ );                                          /*-*/

LX_PUBLIC lx_new_str_t  lx_S_getTag(                                       /*C*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  tag_,                                                /*-*/
    lx_chars_t const  end_tag_,                                            /*-*/
    lx_chars_t const  delimiter_,                                          /*-*/
    const lx_bool     ignore_case_,                                        /*-*/
    const size_t      instance_no_ );                                      /*-*/

LX_PUBLIC lx_new_str_t  lx_S_titleCase( const lx_str_t  object_ );         /*C*/

LX_PUBLIC lx_new_str_t  lx_S_getToken(                                     /*C*/
    const lx_str_t    object_,                                             /*-*/
    const size_t      index_,                                              /*-*/
    lx_chars_t const  delimiter_ );                                        /*-*/

LX_PUBLIC lx_new_str_t  lx_S_getTokenXt(                                   /*C*/
    const lx_str_t    object_,                                             /*-*/
    const size_t      index_,                                              /*-*/
    lx_chars_t const  delimiter_,                                          /*-*/
    const lx_bool     ignore_end_delimiter_ );                             /*-*/

LX_PUBLIC lx_new_str_t  lx_S_setToken(                                     /*C*/
    const lx_str_t    object_,                                             /*-*/
    const size_t      index_,                                              /*-*/
    lx_chars_t const  token_,                                              /*-*/
    lx_chars_t const  delimiter_ );                                        /*-*/

LX_PUBLIC lx_new_str_t  lx_S_trim(                                         /*C*/
    const lx_str_t      object_,                                           /*-*/
    lx_chars_t const    trim_chars_,                                       /*-*/
    const lx_trim_enum  trim_scope_ );                                     /*-*/

#define lx_S_trim1( OBJECT_ )                                             /*C*/\
    lx_S_trim(      OBJECT_, LX_WHITESPACES, LX_CL LX_TRIM_ALL)            /*#*/

#define lx_S_trim2( OBJECT_, TRIM_CHARS_ )                                /*C*/\
    lx_S_trim(     OBJECT_, TRIM_CHARS_, LX_CL LX_TRIM_ALL)                /*#*/

LX_PUBLIC lx_new_str_t  lx_S_trimBegin(                                    /*C*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  trim_chars_ );                                       /*-*/

LX_PUBLIC lx_new_str_t  lx_S_trimBeginChar(                                /*C*/
    const lx_str_t   object_,                                              /*-*/
    const lx_char_t  char_ );                                              /*-*/

LX_PUBLIC lx_new_str_t  lx_S_trimChar(                                     /*C*/
    const lx_str_t      object_,                                           /*-*/
    const lx_char_t     char_,                                             /*-*/
    const lx_trim_enum  trim_scope_ );                                     /*-*/

LX_PUBLIC lx_new_str_t  lx_S_trimEnd(                                      /*C*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  trim_chars_ );                                       /*-*/

LX_PUBLIC lx_new_str_t  lx_S_trimEndChar(                                  /*C*/
    const lx_str_t   object_,                                              /*-*/
    const lx_char_t  char_ );                                              /*-*/

LX_PUBLIC lx_new_str_t  lx_S_trimStr(                                      /*C*/
    const lx_str_t      object_,                                           /*-*/
    lx_chars_t const    string_,                                           /*-*/
    const lx_trim_enum  trim_scope_,                                       /*-*/
    const lx_bool       ignore_case_ );                                    /*-*/

LX_PUBLIC lx_new_str_t  lx_S_uint(                                         /*C*/
    const unsigned long  value_,                                           /*-*/
    lx_chars_t const     format_ );                                        /*-*/

LX_PUBLIC lx_new_str_t  lx_S_unquote(                                      /*C*/
    const lx_str_t    object_,                                             /*-*/
    lx_chars_t const  quote_,                                              /*-*/
    lx_chars_t const  replace_ );                                          /*-*/

LX_PUBLIC lx_new_str_t  lx_S_upperCase( const lx_str_t  object_ );         /*C*/

/* -------------------------------------------------------------------------- */
/* Functions: String Allocating                                               */

/* Convert a value into a hexadecimal string.                                 */
LX_PUBLIC lx_new_str_t  lx_S_hex(                                          /*F*/
    const uint32_t  value_,                                                /*-*/
    const size_t    minimum_length_ );                                     /*-*/

/* -------------------------------------------------------------------------- */
/* Functions: Windows-specific OLE Strings                                    */

#if LX_PLATFORM_WIN32

/* create and return a text object from a COM/Automation string.              */
LX_PUBLIC lx_new_str_t  lx_S_of_bstr( const BSTR_win  text_ );             /*F*/

#endif                                                   /* LX_PLATFORM_WIN32 */

/* It is not the clay the potter throws                                       */
/* which gives the pot its usefulness                                         */
/* but the space within the shape.                                            */

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
