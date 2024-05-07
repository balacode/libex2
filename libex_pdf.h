/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                         [libex_pdf.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_PDF_H
#define      INCLUDED_LIBEX_PDF_H

#include "libex.h"

#if defined _MSC_VER
#pragma once
#endif

#define LX_PDF_EXTRA_FEATURES    1

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

typedef struct  lx_pdf_t {
    uint8_t*  ob;                                                 /* lx_pdf_t */
}
lx_pdf_t, lx_new_pdf_t;

/* -------------------------------------------------------------------------- */
/* Constructor:                                                               */

LX_PUBLIC lx_new_pdf_t  lx_PdfInit( lx_chars_t  page_size_ );              /*C*/

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

LX_PUBLIC void  lx_freePdf( lx_pdf_t*  object_ );                          /*D*/

/* -------------------------------------------------------------------------- */
/* Core Properties:                                                           */

LX_PUBLIC lx_bool  lx_getCompressionPdf( const lx_pdf_t  object_ );        /*P*/

LX_PUBLIC void  lx_setCompressionPdf(                                      /*P*/
    lx_pdf_t       object_,                                                /*-*/
    const lx_bool  value_ );                                               /*-*/

LX_PUBLIC lx_chars_t  lx_getDocAuthorPdf( const lx_pdf_t  object_ );       /*P*/

LX_PUBLIC void  lx_setDocAuthorPdf(                                        /*P*/
    lx_pdf_t    object_,                                                   /*-*/
    lx_chars_t  value_ );                                                  /*-*/

LX_PUBLIC lx_chars_t  lx_getDocCreatorPdf( const lx_pdf_t  object_ );      /*P*/

LX_PUBLIC void  lx_setDocCreatorPdf(                                       /*P*/
    lx_pdf_t    object_,                                                   /*-*/
    lx_chars_t  value_ );                                                  /*-*/

LX_PUBLIC lx_chars_t  lx_getDocKeywordsPdf( const lx_pdf_t  object_ );     /*P*/

LX_PUBLIC void  lx_setDocKeywordsPdf(                                      /*P*/
    lx_pdf_t    object_,                                                   /*-*/
    lx_chars_t  value_ );                                                  /*-*/

LX_PUBLIC lx_chars_t  lx_getDocSubjectPdf( const lx_pdf_t  object_ );      /*P*/

LX_PUBLIC void  lx_setDocSubjectPdf(                                       /*P*/
    lx_pdf_t    object_,                                                   /*-*/
    lx_chars_t  value_ );                                                  /*-*/

LX_PUBLIC lx_chars_t  lx_getDocTitlePdf( const lx_pdf_t  object_ );        /*P*/

LX_PUBLIC void  lx_setDocTitlePdf(                                         /*P*/
    lx_pdf_t    object_,                                                   /*-*/
    lx_chars_t  value_ );                                                  /*-*/

LX_PUBLIC lx_chars_t  lx_getFontNamePdf( const lx_pdf_t  object_ );        /*P*/

LX_PUBLIC void  lx_setFontNamePdf(                                         /*P*/
    lx_pdf_t    object_,                                                   /*-*/
    lx_chars_t  value_ );                                                  /*-*/

LX_PUBLIC lx_pixel_t  lx_getFontSizePtPdf( const lx_pdf_t  object_ );      /*P*/

LX_PUBLIC void  lx_setFontSizePtPdf(                                       /*P*/
    lx_pdf_t          object_,                                             /*-*/
    const lx_pixel_t  font_size_in_points_ );                              /*-*/

LX_PUBLIC uint16_t  lx_getHorizontalScalingPdf(                            /*P*/
    const lx_pdf_t  object_ );                                             /*-*/

LX_PUBLIC void  lx_setHorizontalScalingPdf(                                /*P*/
    lx_pdf_t        object_,                                               /*-*/
    const uint16_t  value_ );                                              /*-*/

LX_PUBLIC lx_pixel_t  lx_getLineWidthPtPdf( const lx_pdf_t  object_ );     /*P*/

LX_PUBLIC void  lx_setLineWidthPdfPt(                                      /*P*/
    lx_pdf_t          object_,                                             /*-*/
    const lx_pixel_t  value_ );                                            /*-*/

LX_PUBLIC lx_pixel_t  lx_getXPdf( const lx_pdf_t  object_ );               /*P*/

LX_PUBLIC void  lx_setXPdf(                                                /*P*/
    lx_pdf_t          object_,                                             /*-*/
    const lx_pixel_t  x_ );                                                /*-*/

LX_PUBLIC lx_pixel_t  lx_getYPdf( const lx_pdf_t  object_ );               /*P*/

LX_PUBLIC void  lx_setYPdf(                                                /*P*/
    lx_pdf_t          object_,                                             /*-*/
    const lx_pixel_t  y_ );                                                /*-*/

LX_PUBLIC void  lx_setXyPdf(                                               /*P*/
    lx_pdf_t          object_,                                             /*-*/
    const lx_pixel_t  x_,                                                  /*-*/
    const lx_pixel_t  y_ );                                                /*-*/

/* -------------------------------------------------------------------------- */
/* Properties: Read-Only                                                      */

LX_PUBLIC int  lx_getCurrentPagePdf( const lx_pdf_t  object_ );            /*P*/

LX_PUBLIC lx_pixel_t  lx_getPageHeightPtPdf( const lx_pdf_t  object_ );    /*P*/

LX_PUBLIC lx_pixel_t  lx_getPageWidthPtPdf( const lx_pdf_t  object_ );     /*P*/

/* -------------------------------------------------------------------------- */
/* Additional Properties:                                                     */

#if LX_PDF_EXTRA_FEATURES > 0

LX_PUBLIC lx_chars_t  lx_getUnitsPdf( const lx_pdf_t  object_ );           /*P*/

LX_PUBLIC void  lx_setUnitsPdf(                                            /*P*/
    lx_pdf_t    object_,                                                   /*-*/
    lx_chars_t  value_ );                                                  /*-*/

#endif                                           /* LX_PDF_EXTRA_FEATURES > 0 */

/* -------------------------------------------------------------------------- */
/* Core Methods:                                                              */

LX_PUBLIC void  lx_addPagePdf( lx_pdf_t  object_ );                        /*M*/

LX_PUBLIC void  lx_drawBoxPdf(                                             /*M*/
    lx_pdf_t          object_,                                             /*-*/
    const lx_pixel_t  x_,                                                  /*-*/
    const lx_pixel_t  y_,                                                  /*-*/
    const lx_pixel_t  width_,                                              /*-*/
    const lx_pixel_t  height_ );                                           /*-*/

LX_PUBLIC void  lx_drawLinePdf(                                            /*M*/
    lx_pdf_t          object_,                                             /*-*/
    const lx_pixel_t  x1_,                                                 /*-*/
    const lx_pixel_t  y1_,                                                 /*-*/
    const lx_pixel_t  x2_,                                                 /*-*/
    const lx_pixel_t  y2_ );                                               /*-*/

LX_PUBLIC void  lx_drawTextPdf(                                            /*M*/
    lx_pdf_t    object_,                                                   /*-*/
    lx_chars_t  string_ );                                                 /*-*/

LX_PUBLIC void  lx_fillBoxPdf(                                             /*M*/
    lx_pdf_t          object_,                                             /*-*/
    const lx_pixel_t  x_,                                                  /*-*/
    const lx_pixel_t  y_,                                                  /*-*/
    const lx_pixel_t  width_,                                              /*-*/
    const lx_pixel_t  height_ );                                           /*-*/

/* return the width of the given text_ using the current font                 */
LX_PUBLIC lx_pixel_t  lx_getTextWidthPdf(                                  /*M*/
    const lx_pdf_t  object_,                                               /*-*/
    lx_chars_t      text_ );                                               /*-*/

LX_PUBLIC void  lx_setColorRgbPdf(                                         /*M*/
    lx_pdf_t   object_,                                                    /*-*/
    const int  red_,                                                       /*-*/
    const int  green_,                                                     /*-*/
    const int  blue_ );                                                    /*-*/

/* -------------------------------------------------------------------------- */
/* Core Methods for Document Output:                                          */

LX_PUBLIC lx_new_bytes_t  lx_BytesFromPdf( const lx_pdf_t  object_ );      /*M*/

LX_PUBLIC void  lx_saveToFilePdf(                                          /*M*/
    const lx_pdf_t  object_,                                               /*-*/
    lx_chars_t      filename_ );                                           /*-*/

/* -------------------------------------------------------------------------- */
/* Additional Methods:                                                        */

#if LX_PDF_EXTRA_FEATURES > 0

LX_PUBLIC void  lx_drawTextInBoxPdf(                                       /*M*/
    lx_pdf_t          object_,                                             /*-*/
    lx_chars_t        text_,                                               /*-*/
    lx_chars_t        text_align_,                                         /*-*/
    const lx_pixel_t  x_,                                                  /*-*/
    const lx_pixel_t  y_,                                                  /*-*/
    const lx_pixel_t  width_,                                              /*-*/
    const lx_pixel_t  height_ );                                           /*-*/

LX_PUBLIC void  lx_drawUnitGridPdf( lx_pdf_t  object_ );                   /*M*/

LX_PUBLIC void  lx_goToNextLinePdf( lx_pdf_t  object_ );                   /*M*/

LX_PUBLIC void  lx_setColorPdf(                                            /*M*/
    lx_pdf_t    object_,                                                   /*-*/
    lx_chars_t  color_name_or_value_ );                                    /*-*/

LX_PUBLIC void  lx_setColumnWidthsPdf(                                     /*M*/
    lx_pdf_t        object_,                                               /*-*/
    const uint32_t  number_of_columns_,                                    /*-*/
    ... );                                                                 /*-*/

LX_PUBLIC void  lx_setLineWidthPdf(                                        /*M*/
    lx_pdf_t          object_,                                             /*-*/
    const lx_pixel_t  line_width_in_points_ );                             /*-*/

#endif                                           /* LX_PDF_EXTRA_FEATURES > 0 */

/* -------------------------------------------------------------------------- */
/* Additional Functions:                                                      */

LX_PUBLIC lx_pixel_t  lx_convert_to_pdf_points(                            /*F*/
    lx_chars_t  number_and_unit_ );                                        /*-*/

LX_PUBLIC void  lx_test_convert_to_pdf_points( void );                     /*F*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
