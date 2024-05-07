/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                        [libex_pdf_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_PDF__H
#define      INCLUDED_LIBEX_PDF__H
#include "libex_pdf.h"

#define PDF_EXTRA_FEATURES              LX_PDF_EXTRA_FEATURES

/* -------------------------------------------------------------------------- */

#define pdf_t                           lx_pdf_t
#define new_pdf_t                       lx_new_pdf_t

/* -------------------------------------------------------------------------- */
/* Constructor:                                                               */

#define PdfInit                         lx_PdfInit

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

#define freePdf                         lx_freePdf

/* -------------------------------------------------------------------------- */
/* Core Properties:                                                           */

#define getCompressionPdf               lx_getCompressionPdf
#define getDocAuthorPdf                 lx_getDocAuthorPdf
#define getDocCreatorPdf                lx_getDocCreatorPdf
#define getDocKeywordsPdf               lx_getDocKeywordsPdf
#define getDocSubjectPdf                lx_getDocSubjectPdf
#define getDocTitlePdf                  lx_getDocTitlePdf
#define getFontNamePdf                  lx_getFontNamePdf
#define getFontSizePtPdf                lx_getFontSizePtPdf
#define getHorizontalScalingPdf         lx_getHorizontalScalingPdf
#define getLineWidthPtPdf               lx_getLineWidthPtPdf
#define getXPdf                         lx_getXPdf
#define getYPdf                         lx_getYPdf

#define setCompressionPdf               lx_setCompressionPdf
#define setDocAuthorPdf                 lx_setDocAuthorPdf
#define setDocCreatorPdf                lx_setDocCreatorPdf
#define setDocKeywordsPdf               lx_setDocKeywordsPdf
#define setDocSubjectPdf                lx_setDocSubjectPdf
#define setDocTitlePdf                  lx_setDocTitlePdf
#define setFontNamePdf                  lx_setFontNamePdf
#define setFontSizePtPdf                lx_setFontSizePtPdf
#define setHorizontalScalingPdf         lx_setHorizontalScalingPdf
#define setLineWidthPdfPt               lx_setLineWidthPdfPt
#define setXPdf                         lx_setXPdf
#define setXyPdf                        lx_setXyPdf
#define setYPdf                         lx_setYPdf

/* -------------------------------------------------------------------------- */
/* Properties: Read-Only                                                      */

#define getCurrentPagePdf               lx_getCurrentPagePdf
#define getPageHeightPtPdf              lx_getPageHeightPtPdf
#define getPageWidthPtPdf               lx_getPageWidthPtPdf

/* -------------------------------------------------------------------------- */
/* Additional Properties:                                                     */

#if LX_PDF_EXTRA_FEATURES > 0
#define getUnitsPdf                     lx_getUnitsPdf
#define setUnitsPdf                     lx_setUnitsPdf
#endif

/* -------------------------------------------------------------------------- */
/* Core Methods:                                                              */

#define addPagePdf                      lx_addPagePdf
#define drawBoxPdf                      lx_drawBoxPdf
#define drawLinePdf                     lx_drawLinePdf
#define drawTextPdf                     lx_drawTextPdf
#define fillBoxPdf                      lx_fillBoxPdf
#define getTextWidthPdf                 lx_getTextWidthPdf
#define setColorRgbPdf                  lx_setColorRgbPdf

/* -------------------------------------------------------------------------- */
/* Core Methods for Document Output:                                          */

#define BytesFromPdf                    lx_BytesFromPdf
#define saveToFilePdf                   lx_saveToFilePdf

/* -------------------------------------------------------------------------- */
/* Additional Methods:                                                        */

#if LX_PDF_EXTRA_FEATURES > 0
#define drawTextInBoxPdf                lx_drawTextInBoxPdf
#define drawUnitGridPdf                 lx_drawUnitGridPdf
#define goToNextLinePdf                 lx_goToNextLinePdf
#define setColorPdf                     lx_setColorPdf
#define setColumnWidthsPdf              lx_setColumnWidthsPdf
#define setLineWidthPdf                 lx_setLineWidthPdf
#endif

/* -------------------------------------------------------------------------- */
/* Additional Functions:                                                      */

#define convert_to_pdf_points           lx_convert_to_pdf_points
#define test_convert_to_pdf_points      lx_test_convert_to_pdf_points

#endif                                                                   /*eof*/
