/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                        [libex_csv_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_CSV__H
#define      INCLUDED_LIBEX_CSV__H
#include "libex_csv.h"

/* -------------------------------------------------------------------------- */

#define csv_t                           lx_csv_t
#define new_csv_t                       lx_new_csv_t

#define CSV_COMMA                       LX_CSV_COMMA
#define CSV_CR                          LX_CSV_CR
#define CSV_ESCAPE                      LX_CSV_ESCAPE
#define CSV_LF                          LX_CSV_LF
#define CSV_QUOTE                       LX_CSV_QUOTE

#define CSV_COMMA_SUBST                 LX_CSV_COMMA_SUBST
#define CSV_CR_SUBST                    LX_CSV_CR_SUBST
#define CSV_LF_SUBST                    LX_CSV_LF_SUBST
#define CSV_NEXT_ROW                    LX_CSV_NEXT_ROW
#define CSV_QUOTE_SUBST                 LX_CSV_QUOTE_SUBST

/* -------------------------------------------------------------------------- */

#define csv_data_type_enum              lx_csv_data_type_enum

#define CSV_BOOL                        LX_CSV_BOOL
#define CSV_DATE_TIME                   LX_CSV_DATE_TIME
#define CSV_INVALID                     LX_CSV_INVALID
#define CSV_NULL                        LX_CSV_NULL
#define CSV_NUMBER                      LX_CSV_NUMBER
#define CSV_TEXT                        LX_CSV_TEXT

/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */

#define CsvReader                       lx_CsvReader
#define CsvWriter                       lx_CsvWriter

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

#define freeCsv                         lx_freeCsv

/* -------------------------------------------------------------------------- */
/* Properties:                                                                */

#define charsCsv                        lx_charsCsv
#define isEofCsv                        lx_isEofCsv
#define isNewRowCsv                     lx_isNewRowCsv

/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */

#define readNextCsv                     lx_readNextCsv
#define writeNewRowCsv                  lx_writeNewRowCsv
#define writeTextCsv                    lx_writeTextCsv

/* -------------------------------------------------------------------------- */
/* Functions: Lookup                                                          */

#define csv_item                        lx_csv_item
#define csv_key_value                   lx_csv_key_value

/* -------------------------------------------------------------------------- */
/* Functions: Windows-specific                                                */

#if LX_PLATFORM_WIN32 && defined __tagVARIANT
#define csv_from_array                  lx_csv_from_array
#endif

#endif                                                                   /*eof*/
