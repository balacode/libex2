/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                         [libex_csv.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_CSV_H
#define      INCLUDED_LIBEX_CSV_H

#include "libex.h"
#if LX_PLATFORM_WIN32
#include "libex_win32.h"
#endif

#if defined _MSC_VER
#pragma once
#endif

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

typedef struct  lx_csv_t {
    uint8_t*  ob;                                                 /* lx_csv_t */
}
lx_csv_t, lx_new_csv_t;

#if defined __GNUC__ || defined __clang__
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

static const lx_char_t  LX_CSV_ESCAPE = '\x01B';
static const lx_char_t  LX_CSV_COMMA  = ',';
static const lx_char_t  LX_CSV_CR     = '\r';
static const lx_char_t  LX_CSV_LF     = '\n';
static const lx_char_t  LX_CSV_QUOTE  = '\'';

static lx_chars_t  LX_CSV_NEXT_ROW    = _T("\n");
static lx_chars_t  LX_CSV_COMMA_SUBST = _T("\x01B&#44;");
static lx_chars_t  LX_CSV_CR_SUBST    = _T("\x01B&#13;");
static lx_chars_t  LX_CSV_LF_SUBST    = _T("\x01B&#10;");
static lx_chars_t  LX_CSV_QUOTE_SUBST = _T("\x01B&#39;");  /* 34=" 39=' */

/* -------------------------------------------------------------------------- */

typedef enum  _lx_csv_data_type_enum {
    LX_CSV_INVALID,                                  /* lx_csv_data_type_enum */
    LX_CSV_NULL,                                     /* lx_csv_data_type_enum */
    LX_CSV_BOOL,                                     /* lx_csv_data_type_enum */
    LX_CSV_NUMBER,                                   /* lx_csv_data_type_enum */
    LX_CSV_DATE_TIME,                                /* lx_csv_data_type_enum */
    LX_CSV_TEXT                                      /* lx_csv_data_type_enum */
}
lx_csv_data_type_enum;                                                  /*enum*/

/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */

LX_PUBLIC lx_new_csv_t  lx_CsvReader( lx_chars_t  csv_string_ );           /*C*/

LX_PUBLIC lx_new_csv_t  lx_CsvWriter(                                      /*C*/
    const uint32_t  column_count_,                                         /*-*/
    const uint32_t  initial_capacity_opt_ );                               /*-*/

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

LX_PUBLIC void  lx_freeCsv( lx_csv_t*  object_ );                          /*D*/

/* -------------------------------------------------------------------------- */
/* Properties:                                                                */

LX_PUBLIC lx_chars_t  lx_charsCsv( lx_csv_t  object_ );                    /*P*/

LX_PUBLIC lx_bool  lx_isEofCsv( lx_csv_t  object_ );                       /*P*/

LX_PUBLIC lx_bool  lx_isNewRowCsv( lx_csv_t  object_ );                    /*P*/

/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */

LX_PUBLIC lx_chars_t  lx_readNextCsv( lx_csv_t  object_ );                 /*M*/

LX_PUBLIC void  lx_writeNewRowCsv( lx_csv_t  object_ );                    /*M*/

LX_PUBLIC void  lx_writeTextCsv(                                           /*M*/
    lx_csv_t    object_,                                                   /*-*/
    lx_chars_t  string_ );                                                 /*-*/

/* -------------------------------------------------------------------------- */
/* Functions: Lookup                                                          */

LX_PUBLIC lx_new_chars_t  lx_csv_item(                                     /*F*/
    lx_chars_t      csv_,                                                  /*-*/
    const uint32_t  row_no_,                                               /*-*/
    const uint32_t  column_no_ );                                          /*-*/

LX_PUBLIC lx_new_chars_t  lx_csv_key_value(                                /*F*/
    lx_chars_t  csv_,                                                      /*-*/
    lx_chars_t  key_id_ );                                                 /*-*/

/* -------------------------------------------------------------------------- */
/* Functions: Windows-specific                                                */

#if LX_PLATFORM_WIN32 && defined __tagVARIANT

LX_PUBLIC lx_new_chars_t  lx_csv_from_array(                               /*F*/
    VARIANT_win*  variant_,                                                /*-*/
    lx_chars_t    prepend_text_ );                                         /*-*/

#endif                                                   /* LX_PLATFORM_WIN32 */

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
