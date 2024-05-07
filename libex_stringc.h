/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                       [libex_stringc.h] [cat:strings] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_STRINGC_H
#define      INCLUDED_LIBEX_STRINGC_H

#if (defined __GNUC__ || defined __clang__) && !defined __MINGW32__
#pragma GCC diagnostic ignored "-Wunused-macros"
#endif

#include "libex.h"

#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4005)  /* W:L1 'NAME': macro redefinition */
#endif

#if LX_PLATFORM_WIN32
#include <windows.h>
#include <oleauto.h>  /* for BSTR_win */
#endif                                                   /* LX_PLATFORM_WIN32 */

#if defined _MSC_VER
#pragma warning (pop)
#endif

#if LX_PLATFORM_WIN32
#include "libex_win32.h"
#endif                                                   /* LX_PLATFORM_WIN32 */

#define LX_STR_INITIAL_CAPACITY  64

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

extern lx_bool  lx_enable_chars_warnings;

typedef enum  _lx_chars_format_enum {
    LX_DEFAULT = 0,                                   /* lx_chars_format_enum */
    LX_ANSI    = 1,                                   /* lx_chars_format_enum */
    LX_WIDE    = 2                                    /* lx_chars_format_enum */
}
lx_chars_format_enum;                                                   /*enum*/

/* Specifies token operation for lx_token_infoT() to carry out. */
typedef enum  lx_token_info_enum {
    LX_TOKEN_EXISTS = 1,                                /* lx_token_info_enum */
    LX_TOKEN_INDEX  = 2,                                /* lx_token_info_enum */
    LX_TOKEN_COUNT  = 3                                 /* lx_token_info_enum */
}
lx_token_info_enum;                                                     /*enum*/

/* String transformation flags. */
typedef enum  _lx_make_change_enum {
    LX_MAKE_SAME       = 0,                            /* lx_make_change_enum */
    LX_MAKE_FILLED     = 2,                            /* lx_make_change_enum */
    LX_MAKE_UPPER_CASE = 4,                            /* lx_make_change_enum */
    LX_MAKE_LOWER_CASE = 8,                            /* lx_make_change_enum */
    LX_MAKE_TITLE_CASE = 16,                           /* lx_make_change_enum */
    LX_MAKE_REVERSE    = 32                            /* lx_make_change_enum */
}
lx_make_change_enum;                                                    /*enum*/

/* String trimming options. */
typedef enum  _lx_trim_enum {
    LX_TRIM_NONE  = 0,                                        /* lx_trim_enum */
    LX_TRIM_BEGIN = 1,                                        /* lx_trim_enum */
    LX_TRIM_END   = 2,                                        /* lx_trim_enum */
    LX_TRIM_ALL   = 3                                         /* lx_trim_enum */
}
lx_trim_enum;                                                           /*enum*/

/* String comparison options. */
static const lx_bool  LX_MATCH_CASE  = LX_C_FALSE;
static const lx_bool  LX_IGNORE_CASE = LX_C_TRUE;

/* -------------------------------------------------------------------------- */
/* Functions: Standard                                                        */

/* lx_strstriT(): Pointer to first occurrence of a substring, ignoring case   */
LX_PUBLIC lx_char_t*  lx_strstriT(                                         /*F*/
    lx_chars_t  main_,                                                     /*-*/
    lx_chars_t  find_ );                                                   /*-*/

/* -------------------------------------------------------------------------- */
/* Functions: Character String Allocating                                     */

#define lx_appendT( REALLOC_VAR_,    S1_ )                                /*F*/\
    lx_appendnT(    REALLOC_VAR_, 1, S1_)                                  /*#*/

#define lx_append2T( REALLOC_VAR_,    S1_, S2_ )                          /*F*/\
    lx_appendnT(     REALLOC_VAR_, 2, S1_, S2_)                            /*#*/

#define lx_append3T( REALLOC_VAR_,    S1_, S2_, S3_ )                     /*F*/\
    lx_appendnT(     REALLOC_VAR_, 3, S1_, S2_, S3_)                       /*#*/

#define lx_append4T( REALLOC_VAR_,    S1_, S2_, S3_, S4_ )                /*F*/\
    lx_appendnT(     REALLOC_VAR_, 4, S1_, S2_, S3_, S4_)                  /*#*/

#define lx_append5T( REALLOC_VAR_,    S1_, S2_, S3_, S4_, S5_ )           /*F*/\
    lx_appendnT(     REALLOC_VAR_, 5, S1_, S2_, S3_, S4_, S5_)             /*#*/

#define lx_append6T( REALLOC_VAR_,    S1_, S2_, S3_, S4_, S5_, S6_ )      /*F*/\
    lx_appendnT(     REALLOC_VAR_, 6, S1_, S2_, S3_, S4_, S5_, S6_)        /*#*/

#define lx_append7T( REALLOC_VAR_,    S1_, S2_, S3_, S4_, S5_, S6_,       /*F*/\
                     S7_ )                                                     \
lx_appendnT(         REALLOC_VAR_, 7, S1_, S2_, S3_, S4_, S5_, S6_,            \
                     S7_)                                                  /*#*/

#define lx_append8T( REALLOC_VAR_,    S1_, S2_, S3_, S4_, S5_, S6_,       /*F*/\
                     S7_, S8_ )                                                \
lx_appendnT(         REALLOC_VAR_, 8, S1_, S2_, S3_, S4_, S5_, S6_,            \
                     S7_, S8_)                                             /*#*/

#define lx_append9T( REALLOC_VAR_,    S1_, S2_, S3_, S4_, S5_, S6_,       /*F*/\
                     S7_, S8_, S9_ )                                           \
lx_appendnT(         REALLOC_VAR_, 9, S1_, S2_, S3_, S4_, S5_, S6_,            \
                     S7_, S8_, S9_)                                        /*#*/

LX_PUBLIC lx_bool  lx_appendnT(                                            /*F*/
    lx_new_chars_t*  realloc_var_,                                         /*-*/
    const int        count_,                                               /*-*/
    lx_chars_t       str_1_,                                               /*-*/
    ... );                                                                 /*-*/

LX_PUBLIC lx_new_chars_t  lx_T_format_numeric(                             /*F*/
    lx_chars_t  number_,                                                   /*-*/
    int         decimal_places_ );                                         /*-*/

/*
    lx_T_format_numeric() special format suggestions:

    format_: dpl=2 gr1=3 gr2=3 gr3=3 dpt=. gdc=,
    dp=   decimal places (0-9)
    g1=   group 1 digits (0-9)
    g2=   group 2 digits (0-9)
    g3=   group 3 digits (0-9)
    dpc=  decimal point character
    gdc=  group delimiter character
*/

#define lx_T_chars( SOURCE_STR_ )                                         /*F*/\
    lx_T_chars_n(  SOURCE_STR_, SIZE_MAX)                                  /*#*/

LX_PUBLIC lx_new_chars_t  lx_T_chars_n(                                    /*F*/
    lx_chars_t    source_,                                                 /*-*/
    const size_t  count_ );                                                /*-*/

LX_PUBLIC lx_new_chars_t  lx_T_bchars_n(                                   /*F*/
    const char* const  source_,                                            /*-*/
    const size_t       count_ );                                           /*-*/

#define lx_T_bchars( SOURCE_STR_ )                                        /*F*/\
    lx_T_bchars_n(   SOURCE_STR_, SIZE_MAX)                                /*#*/

#define /*lx_new_chars_t*/ lx_Tutf8( SOURCE_STR_ )                        /*F*/\
    lx_T_bchars_n(                    SOURCE_STR_, SIZE_MAX)               /*#*/

LX_PUBLIC lx_new_chars_t  lx_T_wchars_n(                                   /*F*/
    const wchar_t*  source_,                                               /*-*/
    const size_t    count_ );                                              /*-*/

#define lx_Twchars( SOURCE_STR_ )                                         /*F*/\
    lx_T_wchars_n(   SOURCE_STR_, SIZE_MAX)                                /*#*/

LX_PUBLIC lx_new_chars_t  lx_T_decode_base64( lx_chars_t  string_ );       /*F*/

LX_PUBLIC lx_new_chars_t  lx_T_encode_base64( lx_chars_t  string_ );       /*F*/

LX_PUBLIC lx_new_chars_t  lx_T_first(                                      /*F*/
    lx_chars_t    string_,                                                 /*-*/
    const size_t  length_ );                                               /*-*/

LX_PUBLIC lx_new_chars_t  lx_T_offset(                                     /*F*/
    lx_chars_t    string_,                                                 /*-*/
    const size_t  offset_ );                                               /*-*/

LX_PUBLIC lx_new_chars_t  lx_T_substr(                                     /*F*/
    lx_chars_t    string_,                                                 /*-*/
    const size_t  offset_,                                                 /*-*/
    const size_t  count_ );                                                /*-*/

LX_PUBLIC lx_new_chars_t  lx_T_double(                                     /*F*/
    long double  value_,                                                   /*-*/
    const int    decimal_places_ );                                        /*-*/

LX_PUBLIC lx_new_chars_t  lx_T_hex(                                        /*F*/
    const uint32_t  value_,                                                /*-*/
    const size_t    min_len_ );                                            /*-*/

LX_PUBLIC lx_new_chars_t  lx_T_int( const int  value_ );                   /*F*/

LX_PUBLIC lx_new_chars_t  lx_T_join(                                       /*F*/
    lx_chars_t  terminator_,                                               /*-*/
    lx_chars_t  string1_,                                                  /*-*/
    ... );                                                                 /*-*/

LX_PUBLIC lx_new_chars_t  lx_T_last(                                       /*F*/
    lx_chars_t    string_,                                                 /*-*/
    const size_t  length_ );                                               /*-*/

LX_PUBLIC lx_new_chars_t  lx_T_lower( lx_chars_t  string_ );               /*F*/
/*TODO:*/

LX_PUBLIC lx_new_chars_t  lx_T_malloc_id(                                  /*F*/
    const size_t  char_len_,                                               /*-*/
    lx_chars_t    filename_,                                               /*-*/
    const int     source_line_ );                                          /*-*/

#define lx_mallocT( SIZE_T__CHAR_LEN_ )                                   /*F*/\
    lx_T_malloc_id( SIZE_T__CHAR_LEN_, LX_STR(__FILE__), __LINE__)         /*#*/

#define lx_reallocT( NEW_CHARS__STR_, SIZE_T__CHAR_LEN_ )                 /*F*/\
    lx_T_realloc_id( NEW_CHARS__STR_, SIZE_T__CHAR_LEN_,                       \
                     LX_STR(__FILE__), __LINE__)                           /*#*/

LX_PUBLIC lx_new_bchars_t  lx_formatA(                                     /*F*/
    const char*  format_,                                                  /*-*/
    ... );                                                                 /*-*/

LX_PUBLIC lx_new_wchars  lx_formatW(                                       /*F*/
    const wchar_t*  format_,                                               /*-*/
    ... );                                                                 /*-*/

#if defined UNICODE || defined _UNICODE
#define lx_formatT  lx_formatW
#else                                                  /* UNICODE || _UNICODE */
#define lx_formatT  lx_formatA
#endif                                               /* !UNICODE && !_UNICODE */

LX_PUBLIC lx_new_chars_t  lx_T_realloc_id(                                 /*F*/
    lx_new_chars_t  string_,                                               /*-*/
    const size_t    char_len_,                                             /*-*/
    lx_chars_t      filename_,                                             /*-*/
    const int       source_line_ );                                        /*-*/

LX_PUBLIC lx_new_chars_t  lx_T_repeat(                                     /*F*/
    lx_chars_t  string_,    /* String to be repeated.                  */  /*-*/
    const int   count_,     /* Max. # of times string can be repeated. */  /*-*/
    const int   max_len_ ); /* Max. length of the returned string.     */  /*-*/

#define lx_repeat2T( STRING_, INT_COUNT_ )                                /*F*/\
    lx_T_repeat(     STRING_, INT_COUNT_, LX_CAST(int, INT_MAX))           /*#*/

LX_PUBLIC lx_new_chars_t  lx_T_replace(                                    /*F*/
    lx_chars_t     string_,        /* string being searched        */      /*-*/
    lx_chars_t     find_,          /* string to find               */      /*-*/
    lx_chars_t     replace_,       /* replacement string           */      /*-*/
    const lx_bool  ignore_case_ ); /* LX_MATCH_CASE/LX_IGNORE_CASE */      /*-*/

LX_PUBLIC void  lx_set_inT(                                                /*F*/
    lx_new_chars_t*  realloc_var_,                                         /*-*/
    lx_chars_t       new_string_ );                                        /*-*/

LX_PUBLIC void  lx_set_default_inT(                                        /*F*/
    lx_new_chars_t*  realloc_var_,                                         /*-*/
    lx_chars_t       new_string_,                                          /*-*/
    lx_chars_t       default_ );                                           /*-*/

LX_PUBLIC lx_new_chars_t  lx_T_get_tag(                                    /*F*/
    lx_chars_t  string_,                                                   /*-*/
    lx_chars_t  tag_,                                                      /*-*/
    lx_chars_t  delimiter_ );                                              /*-*/

LX_PUBLIC lx_new_chars_t  lx_T_remove_tag(                                 /*F*/
    lx_chars_t  string_,                                                   /*-*/
    lx_chars_t  tag_,                                                      /*-*/
    lx_chars_t  delimiter_ );                                              /*-*/

/* TODO: where is lx_set_tagT() function?`` */

LX_PUBLIC lx_new_chars_t  lx_T_title( lx_chars_t string_ );                /*F*/
/*TODO*/

LX_PUBLIC lx_new_bytes_t  lx_to_bytesT(                                    /*F*/
    lx_chars_t            string_,                                         /*-*/
    lx_chars_format_enum  string_format_ );                                /*-*/

#define lx_T_get_token( CHARS_LIST_, INDEX_, CHARS_DELIMITER_ )           /*F*/\
    lx_T_get_token_xt(  CHARS_LIST_, INDEX_, CHARS_DELIMITER_,                 \
                        LX_C_FALSE)                                        /*#*/

LX_PUBLIC lx_new_chars_t  lx_T_get_token_xt(                               /*F*/
    lx_chars_t     list_,                                                  /*-*/
    const size_t   index_,                                                 /*-*/
    lx_chars_t     delimiter_,                                             /*-*/
    const lx_bool  ignore_end_delimiter_ );                                /*-*/

LX_PUBLIC lx_new_chars_t  lx_T_tokenize(                                   /*F*/
    lx_chars_t  string_,                                                   /*-*/
    lx_chars_t  delimiter_ );                                              /*-*/

LX_PUBLIC lx_new_chars_t  lx_T_set_token(                                  /*F*/
    lx_chars_t    list_,                                                   /*-*/
    const size_t  index_,                                                  /*-*/
    lx_chars_t    token_,                                                  /*-*/
    lx_chars_t    delimiter_ );                                            /*-*/

LX_PUBLIC lx_new_bchars_t  lx_to_utf8T( lx_chars_t  string_ );             /*F*/

LX_PUBLIC lx_new_chars_t  lx_T_uint( const uint32_t  value_ );             /*F*/

LX_PUBLIC lx_new_chars_t  lx_T_uint64( const uint64_t  value_ );           /*F*/

LX_PUBLIC lx_new_chars_t  lx_T_upper( lx_chars_t  string_ ); /*TODO*/      /*F*/

LX_PUBLIC lx_new_bchars_t  lx_utf8_of_wide( const wchar_t*  string_ );     /*F*/

LX_PUBLIC lx_new_wchars  lx_wide_of_utf8( const char*  string_ );          /*F*/

/* -------------------------------------------------------------------------- */
/* Character String Destructor:                                               */

#if defined UNICODE || defined _UNICODE
#define lx_freeT  lx_freeW                                                 /*F*/
#else                                                  /* UNICODE || _UNICODE */
#define lx_freeT  lx_freeA                                                 /*F*/
#endif                                               /* !UNICODE && !_UNICODE */

LX_PUBLIC void  lx_freeA( lx_new_bchars_t*  string_ );                     /*F*/

LX_PUBLIC void  lx_freeW( lx_new_wchars*  string_ );                       /*F*/

/* -------------------------------------------------------------------------- */
/* Functions: In-Place Character String Manipulation                          */

LX_PUBLIC void  lx_change_in_T(                                            /*F*/
    lx_char_t*  chars_,                                                    /*-*/
    const int   changes_ );                                                /*-*/

LX_PUBLIC void  lx_lower_in_T( lx_char_t*  string_ref_ );                  /*F*/

LX_PUBLIC void  lx_remove_extra_spaces_in_T( lx_char_t*  string_ref_ );    /*F*/

LX_PUBLIC void  lx_replace_in_T(                                           /*F*/
    lx_new_chars_t*  realloc_var_,                                         /*-*/
    lx_chars_t       find_,                                                /*-*/
    lx_chars_t       replace_ );                                           /*-*/

LX_PUBLIC void  lx_set_replace_char(                                       /*F*/
    char*  string_,                                                        /*-*/
    char   find_char_,                                                     /*-*/
    char   replace_char_ );                                                /*-*/

LX_PUBLIC void  lx_replace_char_in_T(                                      /*F*/
    lx_char_t*  string_,                                                   /*-*/
    lx_char_t   find_char_,                                                /*-*/
    lx_char_t   replace_char_ );                                           /*-*/

LX_PUBLIC void  lx_title_in_T( lx_char_t*  string_ref_ );                  /*F*/

LX_PUBLIC void  lx_trim_in_T( lx_char_t*  string_ref_ );                   /*F*/

LX_PUBLIC void  lx_trim4_in_T(                                             /*F*/
    lx_char_t*     string_ref_,                                            /*-*/
    lx_chars_t     trim_chars_,                                            /*-*/
    const lx_bool  trim_begin_,                                            /*-*/
    const lx_bool  trim_end_ );                                            /*-*/

LX_PUBLIC void  lx_upper_in_T( lx_char_t*  string_ref_ );                  /*F*/

/* -------------------------------------------------------------------------- */
/* Functions: Informative                                                     */

/* Convert a hexadecimal string to actual value.                              */
LX_PUBLIC uint32_t  lx_hex_value( lx_chars_t  hex_ );                      /*F*/

LX_PUBLIC lx_bool  lx_begins3T(                                            /*F*/
    lx_chars_t     main_str_,                                              /*-*/
    lx_chars_t     find_str_,                                              /*-*/
    const lx_bool  ignore_case_ );                                         /*-*/

/* returns lx_bool */
#define lx_beginsT( MAIN_STR_, FIND_STR_ )                                /*F*/\
    lx_begins3T(    MAIN_STR_, FIND_STR_, LX_CL LX_MATCH_CASE)             /*#*/

LX_PUBLIC lx_bool  lx_containsT(                                           /*F*/
    lx_chars_t     string_,                                                /*-*/
    lx_chars_t     substring_,                                             /*-*/
    const lx_bool  ignore_case_,                                           /*-*/
    const size_t   string_len_,                                            /*-*/
    const size_t   substring_len_ );                                       /*-*/

#define lx_contains2T( STRING_, SUBSTRING_ )                              /*F*/\
    lx_containsT(      STRING_, SUBSTRING_, LX_CL LX_MATCH_CASE,               \
                       SIZE_MAX, SIZE_MAX)                                 /*#*/

#define lx_contains3T( STRING_, SUBSTRING_, IGNORE_CASE_ )                /*F*/\
    lx_containsT(      STRING_, SUBSTRING_, IGNORE_CASE_,                      \
                       SIZE_MAX, SIZE_MAX)                                 /*#*/

#define lx_contains4T( STRING_, SUBSTRING_, IGNORE_CASE_, STRING_LEN_ )   /*F*/\
    lx_containsT(      STRING_, SUBSTRING_, IGNORE_CASE_, STRING_LEN_,         \
                       SIZE_MAX)                                           /*#*/

LX_PUBLIC size_t  lx_countT(                                               /*F*/
    lx_chars_t     main_str_,                                              /*-*/
    lx_chars_t     find_str_,                                              /*-*/
    const size_t   offset_,                                                /*-*/
    const lx_bool  ignore_case_,                                           /*-*/
    const lx_bool  reverse_,                                               /*-*/
    const size_t   main_len_,                                              /*-*/
    const size_t   find_len_,                                              /*-*/
    const size_t   max_count_,                                             /*-*/
    size_t*        location_out_ );                                        /*-*/

#define lx_count6T( MAIN_STR_, FIND_STR_, BEGIN_AT_, IGNORE_CASE_,        /*F*/\
                    REVERSE_, MAIN_LEN_ )                                      \
lx_countT(          MAIN_STR_, FIND_STR_, BEGIN_AT_, IGNORE_CASE_,             \
                    REVERSE_, MAIN_LEN_, SIZE_MAX, SIZE_MAX, NULL)         /*#*/

LX_PUBLIC lx_bool  lx_endsT(                                               /*F*/
    lx_chars_t     main_str_,                                              /*-*/
    lx_chars_t     find_str_,                                              /*-*/
    const lx_bool  ignore_case_,                                           /*-*/
    const size_t   main_len_,                                              /*-*/
    const size_t   find_len_ );                                            /*-*/

#define lx_ends2T( MAIN_STR_, FIND_STR_ )                                 /*F*/\
    lx_endsT(      MAIN_STR_, FIND_STR_,                                       \
                   LX_CL LX_MATCH_CASE, SIZE_MAX, SIZE_MAX )               /*#*/

#define lx_ends3T( MAIN_STR_, FIND_STR_, IGNORE_CASE_ )                   /*F*/\
    lx_endsT(      MAIN_STR_, FIND_STR_, IGNORE_CASE_,                         \
                   SIZE_MAX, SIZE_MAX )                                    /*#*/

#define lx_ends4T( MAIN_STR_, FIND_STR_, IGNORE_CASE_, MAIN_LEN_ )        /*F*/\
    lx_endsT(      MAIN_STR_, FIND_STR_, IGNORE_CASE_, MAIN_LEN_,              \
                   SIZE_MAX )                                              /*#*/

LX_PUBLIC lx_bool  lx_equalsT(                                             /*F*/
    lx_chars_t     str_1_,                                                 /*-*/
    lx_chars_t     str_2_,                                                 /*-*/
    const lx_bool  ignore_case_,                                           /*-*/
    const size_t   check_len_ );                                           /*-*/

#define lx_equals2T( STR_1_, STR_2_ )                                     /*F*/\
    lx_equalsT(      STR_1_, STR_2_, LX_CL LX_MATCH_CASE, SIZE_MAX)        /*#*/

#define lx_equals_icT( STR_1_, STR_2_ )                                   /*F*/\
    lx_equalsT(        STR_1_, STR_2_, LX_IGNORE_CASE, SIZE_MAX)           /*#*/

LX_PUBLIC size_t  lx_findT(                                                /*F*/
    lx_chars_t     main_str_,                                              /*-*/
    lx_chars_t     find_str_,                                              /*-*/
    const size_t   offset_,                                                /*-*/
    const lx_bool  ignore_case_,                                           /*-*/
    const lx_bool  from_end_,                                              /*-*/
    const size_t   main_len_,                                              /*-*/
    const size_t   find_len_ );                                            /*-*/

#define lx_find2T( MAIN_STR_, FIND_STR_ )                                 /*F*/\
    lx_findT(      MAIN_STR_, FIND_STR_, 0, LX_CL LX_MATCH_CASE,               \
                   LX_C_FALSE, SIZE_MAX, SIZE_MAX)                         /*#*/

#define lx_find3T( MAIN_STR_, FIND_STR_, BEGIN_AT_ )                      /*F*/\
    lx_findT(      MAIN_STR_, FIND_STR_, BEGIN_AT_, LX_CL LX_MATCH_CASE,       \
                   LX_C_FALSE, SIZE_MAX, SIZE_MAX)                         /*#*/

#define lx_find4T( MAIN_STR_, FIND_STR_, BEGIN_AT_, IGNORE_CASE_ )        /*F*/\
    lx_findT(      MAIN_STR_, FIND_STR_, BEGIN_AT_, IGNORE_CASE_,              \
                   LX_C_FALSE, SIZE_MAX, SIZE_MAX)                         /*#*/

#define lx_find5T( MAIN_STR_, FIND_STR_, BEGIN_AT_,                       /*F*/\
                   IGNORE_CASE_, FROM_END_ )                                   \
lx_findT(          MAIN_STR_, FIND_STR_, BEGIN_AT_,                            \
                   IGNORE_CASE_, FROM_END_, SIZE_MAX, SIZE_MAX)            /*#*/

#define lx_find6T( MAIN_STR_, FIND_STR_, BEGIN_AT_, IGNORE_CASE_,         /*F*/\
                   FROM_END_, MAIN_LEN_ )                                      \
lx_findT(          MAIN_STR_, FIND_STR_, BEGIN_AT_, IGNORE_CASE_,              \
                   FROM_END_, MAIN_LEN_, SIZE_MAX)                         /*#*/

LX_PUBLIC size_t  lx_find_charT(                                           /*F*/
    lx_chars_t       main_str_,                                            /*-*/
    const lx_char_t  find_char_,                                           /*-*/
    const size_t     offset_,                                              /*-*/
    const lx_bool    ignore_case_,                                         /*-*/
    const lx_bool    from_end_ );                                          /*-*/

LX_PUBLIC size_t  lx_find_charsT(                                          /*F*/
    lx_chars_t     main_str_,                                              /*-*/
    lx_chars_t     chars_,                                                 /*-*/
    const lx_bool  ignore_case_,                                           /*-*/
    const size_t   main_len_ );                                            /*-*/

#define lx_find_chars2T( MAIN_STR_, CHARS_ )                              /*F*/\
    lx_find_charsT(      MAIN_STR_, CHARS_,                                    \
                         LX_CL LX_MATCH_CASE, SIZE_MAX)                    /*#*/

#define lx_find_chars3T( MAIN_STR_, CHARS_, IGNORE_CASE_ )                /*F*/\
    lx_find_charsT(      MAIN_STR_, CHARS_, IGNORE_CASE_, SIZE_MAX)        /*#*/

#define lx_find_last_T( STRING_, CHARS__FIND_ )                           /*F*/\
    lx_find_last3T(     STRING_, CHARS__FIND_, LX_C_FALSE)                 /*#*/

LX_PUBLIC size_t  lx_find_last3T(                                          /*F*/
    lx_chars_t     string_,                                                /*-*/
    lx_chars_t     find_,                                                  /*-*/
    const lx_bool  ignore_case_ );                                         /*-*/

#undef  LX_IS_BLANK
#define LX_IS_BLANK( STRING_ )                                            /*F*/\
    (STRING_ == NULL || STRING_[0] == 0)                                   /*#*/

LX_PUBLIC lx_bool  lx_is_numberT(                                          /*F*/
    lx_chars_t       string_,                                              /*-*/
    const lx_char_t  decimal_point_char_,                                  /*-*/
    const lx_char_t  group_separator_char_,                                /*-*/
    lx_chars_t       whitespaces_ );                                       /*-*/

#define lx_is_number1T( STRING_ )                                         /*F*/\
    lx_is_numberT(      STRING_, '.', ',', LX_WHITESPACES)                 /*#*/

#define lx_is_number2T( STRING_, DECIMAL_POINT_CHAR_ )                    /*F*/\
    lx_is_numberT(      STRING_, DECIMAL_POINT_CHAR_,                          \
                        ',', LX_WHITESPACES)                               /*#*/

#define lx_is_number3T( STRING_, DECIMAL_POINT_CHAR_,                     /*F*/\
                        GROUP_SEPARATOR_CHAR_ )                                \
lx_is_numberT(          STRING_, DECIMAL_POINT_CHAR_,                          \
                        GROUP_SEPARATOR_CHAR_, LX_WHITESPACES)             /*#*/

LX_PUBLIC lx_bool  lx_is_whitespaceT( lx_chars_t  string_ );               /*F*/

LX_PUBLIC lx_bool  lx_is_wide( const void*  string_ );                     /*F*/

LX_PUBLIC lx_bool  lx_is_wide_n(                                           /*F*/
    const void*   string_,                                                 /*-*/
    const size_t  max_len_in_bytes_ );                                     /*-*/

LX_PUBLIC size_t  lx_lenT( lx_chars_t  string_ );                          /*F*/

LX_PUBLIC size_t  lx_len_maxT(                                             /*F*/
    lx_chars_t    string_,                                                 /*-*/
    const size_t  max_len_ );                                              /*-*/

LX_PUBLIC int  lx_line_countT( lx_chars_t  string_ );                      /*F*/

#define lx_likeT( STR_1_, STR_2_ )                                        /*F*/\
    lx_equalsT(   STR_1_, STR_2_, LX_CL LX_IGNORE_CASE, SIZE_MAX)          /*#*/

LX_PUBLIC lx_bool  lx_patternMatchT(                                       /*F*/
    lx_chars_t     string_,                                                /*-*/
    lx_chars_t     pattern_,                                               /*-*/
    const lx_bool  ignore_case_ );                                         /*-*/

#define lx_patternMatch2T( STRING_, PATTERN_ )                            /*F*/\
    lx_patternMatchT(      STRING_, PATTERN_, LX_CL LX_IGNORE_CASE)        /*#*/

LX_PUBLIC size_t  lx_skip_charsT(                                          /*F*/
    lx_chars_t     main_str_,                                              /*-*/
    lx_chars_t     chars_to_skip_,                                         /*-*/
    const lx_bool  ignore_case_,                                           /*-*/
    const size_t   main_len_ );                                            /*-*/

#define lx_skip_chars2T( MAIN_STR_, CHARS_TO_SKIP_ )                      /*F*/\
    lx_skip_charsT(      MAIN_STR_, CHARS_TO_SKIP_,                            \
                         LX_CL LX_MATCH_CASE, SIZE_MAX);                   /*#*/

#define lx_skip_chars3T( MAIN_STR_, CHARS_TO_SKIP_, IGNORE_CASE_ )        /*F*/\
    lx_skip_charsT(      MAIN_STR_, CHARS_TO_SKIP_, IGNORE_CASE_,              \
                         SIZE_MAX);                                        /*#*/

LX_PUBLIC size_t  lx_substr_lenT(                                          /*F*/
    lx_chars_t    main_str_,                                               /*-*/
    const size_t  main_len_,                                               /*-*/
    const size_t  offset_,                                                 /*-*/
    const size_t  substr_len_ );                                           /*-*/

LX_PUBLIC double  lx_doubleT( lx_chars_t  string_ );                       /*F*/

LX_PUBLIC int  lx_int_T( lx_chars_t  string_ );                            /*F*/

LX_PUBLIC size_t  lx_token_infoT(                                          /*F*/
    const lx_token_info_enum  mode_,                                       /*-*/
    lx_chars_t                list_,                                       /*-*/
    lx_chars_t                delimiter_,                                  /*-*/
    lx_chars_t                token_ );                                    /*-*/

LX_PUBLIC size_t  lx_token_info_xtT(                                       /*F*/
    lx_token_info_enum  mode_,                                             /*-*/
    lx_chars_t          list_,                                             /*-*/
    lx_chars_t          delimiter_,                                        /*-*/
    lx_chars_t          token_,                                            /*-*/
    const lx_bool       ignore_case_,                                      /*-*/
    const size_t        list_len_,                                         /*-*/
    const size_t        token_len_ );                                      /*-*/

LX_PUBLIC int  lx_token_countT(                                            /*F*/
    lx_chars_t  string_,                                                   /*-*/
    lx_chars_t  delimiter_ );                                              /*-*/

LX_PUBLIC uint32_t  lx_uint_of_T( lx_chars_t  string_ );                   /*F*/

LX_PUBLIC lx_bool  lx_is_unicode_mode( void );                             /*F*/

/* -------------------------------------------------------------------------- */
/* Functions: UTF-8                                                           */

/* Return the number of Unicode characters (code points) in a UTF8 string,    */
/* excluding the terminating zero. for validation, use lx_utf8_is_valid().    */
LX_PUBLIC size_t  lx_utf8_len( lx_chars_t  string_ );                      /*F*/

/* -------------------------------------------------------------------------- */
/* Functions: Windows-specific OLE Strings                                    */

#if LX_PLATFORM_WIN32

LX_PUBLIC lx_new_chars_t  lx_T_bstr( const BSTR_win  text_ );              /*F*/

LX_PUBLIC BSTR_win  lx_bstrA( const char*  text_ );                        /*F*/

LX_PUBLIC BSTR_win  lx_bstr_of_T( lx_chars_t  text_ );                     /*F*/

/* Allocate a COM/Automation string from a narrow character string.           */
/* Uses SysAllocString_win().                                                 */
/* The string is wide (Unicode) by default,                                   */
/* but can be made narrow by setting make_wide_ to false.                     */
LX_PUBLIC BSTR_win  lx_bstr_exA(                                           /*F*/
    const char*    text_,                                                  /*-*/
    const lx_bool  make_wide_ );                                           /*-*/

LX_PUBLIC BSTR_win  lx_bstr_exT(                                           /*F*/
    lx_chars_t     text_,                                                  /*-*/
    const lx_bool  make_wide_ );                                           /*-*/

LX_PUBLIC BSTR_win  lx_bstrW( const wchar_t*  text_ );                     /*F*/

/* Allocate a COM/Automation string from a wide (Unicode) character string.   */
/* Uses SysAllocString_win().                                                 */
/* The string is wide (Unicode) by default, but can                           */
/* be made narrow by setting make_wide_ to false.                             */
LX_PUBLIC BSTR_win  lx_bstr_exW(                                           /*F*/
    const wchar_t*  text_,                                                 /*-*/
    const lx_bool   make_wide_ );                                          /*-*/

#endif                                                   /* LX_PLATFORM_WIN32 */

/* It is not the clay the potter throws                                       */
/* which gives the pot its usefulness                                         */
/* but the space within the shape.                                            */

/* -------------------------------------------------------------------------- */
/* Methods: Unimplemented                                                     */

/* TODO: IMPLEMENT lx_T_pad_xt() */
LX_PUBLIC lx_new_chars_t  lx_T_pad_xt(                                     /*F*/
    lx_chars_t     string_,                                                /*-*/
    const size_t   min_width_,                                             /*-*/
    const lx_bool  align_right_ );                                         /*-*/

#define lx_T_pad( STRING_, SIZE_T__MIN_WIDTH_ )                           /*F*/\
    lx_T_pad_xt(      STRING_, SIZE_T__MIN_WIDTH_, LX_C_FALSE)             /*#*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
