/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                  [libex_pdf_report.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_PDF_REPORT_H
#define      INCLUDED_LIBEX_PDF_REPORT_H

#include "libex.h"

#if defined _MSC_VER
#pragma once
#endif

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

typedef struct  lx_Report {
    uint8_t*  ob;                                          /* lx_Report */
}
lx_Report, lx_new_Report;

/* -------------------------------------------------------------------------- */
/* Constructor:                                                               */

LX_PUBLIC lx_new_Report  lx_Report_init( void );                           /*C*/

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

LX_PUBLIC void  lx_Report_free( lx_Report*  object_ );                     /*D*/

/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */

LX_PUBLIC lx_new_bytes_t  lx_Report_get(                                   /*M*/
    lx_Report   object_,                                                   /*-*/
    lx_chars_t  report_xml_,                                               /*-*/
    lx_chars_t  csv_rows_ );                                               /*-*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
