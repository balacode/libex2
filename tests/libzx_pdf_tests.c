/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                   [libex_pdf_tests.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"

#if !defined INCLUDED_LIBEX_PDF_TESTS_C
#define      INCLUDED_LIBEX_PDF_TESTS_C

#include <stdio.h>  /* for printf() */

#if PLATFORM_LINUX
#include <termios.h>
#include <unistd.h>
#endif
#if PLATFORM_WIN32
#include <windows.h>
#endif

#include "libex_all_.h"
#include "libex_c_tests_.h"

#if defined _MSC_VER
#pragma warning (disable:4505)  /* W:L4 unreferenced local function removed   */
#endif


/* this test demonstrates the 14 built-in typefaces                           */
static void  _pdf_test_3( void ) {                                         /*F*/
    //struct _test_t {
    //    chars_t  font_name;                                        /* _test_t */
    //    chars_t  color_name;                                       /* _test_t */
    //}
    //test[] = {
    //    { _T("Courier"),               _T("FireBrick") },
    //    { _T("Courier-Bold"),          _T("FireBrick") },
    //    { _T("Courier-BoldOblique"),   _T("FireBrick") },
    //    { _T("Courier-Oblique"),       _T("FireBrick") },

    //    { _T("Helvetica"),             _T("DarkGreen") },
    //    { _T("Helvetica-Bold"),        _T("DarkGreen") },
    //    { _T("Helvetica-BoldOblique"), _T("DarkGreen") },
    //    { _T("Helvetica-Oblique"),     _T("DarkGreen") },

    //    { _T("Times-Bold"),            _T("DarkBlue") },
    //    { _T("Times-BoldItalic"),      _T("DarkBlue") },
    //    { _T("Times-Italic"),          _T("DarkBlue") },
    //    { _T("Times-Roman"),           _T("DarkBlue") },

    //    { _T("Symbol"),                _T("DarkMagenta") },
    //    { _T("ZapfDingbats"),          _T("DarkMagenta") },

    //    { NULL, NULL }
    //};

    {
        pdf_t    pdf  = PdfInit(_T("A4"));  /* 595 x 841 points */
        //chars_t  text = _T("The quick brown fox jumps over the lazy dog.");
        //int      i    = 0;
        //pixel_t  x    = 2.2;
        //pixel_t  y    = 1.7;

        setCompressionPdf( pdf, false);
        addPagePdf(        pdf);
        setUnitsPdf(       pdf, _T("cm"));
        drawUnitGridPdf(   pdf);

        //setHorizontalScalingPdf(pdf, 80);

        /* print heading */
        //setXyPdf(         pdf, x, y);
        //setColorPdf(      pdf, _T("Black"));
        //setFontNamePdf(   pdf, _T("Helvetica"));
        //setFontSizePtPdf( pdf, 20);
        //drawTextPdf(      pdf, _T("The 14 PDF standard Fonts"));
        //y += 1;

        //while (test[i].font_name) {
        //    setColorPdf(pdf, test[i].color_name);

        //    /* write name of font */
        //    setXyPdf(         pdf, x, y);
        //    setColorPdf(      pdf, _T("Black"));
        //    setFontNamePdf(   pdf, _T("Helvetica"));
        //    setFontSizePtPdf( pdf, 10);
        //    drawTextPdf(      pdf, test[i].font_name);
        //    y += 0.7;

        //    /* write sample text using the font */
        //    setXyPdf(         pdf, x, y);
        //    setColorPdf(      pdf, test[i].color_name);
        //    setFontNamePdf(   pdf, test[i].font_name);
        //    setFontSizePtPdf( pdf, 20);
        //    drawTextPdf(      pdf, text);
        //    y += 1.1;

        //    i++;
        //}

        saveToFilePdf(pdf, _T("__pdf_test_3.pdf"));
        freePdf(&pdf);
    }
} /* _pdf_test_3 */


static void  _pdf_test_1( void ) {                                         /*F*/
    pdf_t  pdf = PdfInit(_T("A4"));  /* 595 x 841 points */

    setCompressionPdf( pdf, false);

    setDocAuthorPdf(   pdf, _T("_DocAuthor_"));
    setDocCreatorPdf(  pdf, _T("_DocCreator_"));
    setDocKeywordsPdf( pdf, _T("_DocKeywords_"));
    setDocSubjectPdf(  pdf, _T("_DocSubject_"));
    setDocTitlePdf(    pdf, _T("_DocTitle_"));

    /* page 1 */
    addPagePdf(        pdf);
    setUnitsPdf(       pdf, _T("cm"));
    drawUnitGridPdf(   pdf);
    setUnitsPdf(       pdf, _T("mm"));

    setFontSizePtPdf(  pdf, 20);
    setLineWidthPdf(   pdf, 2);

    setColorPdf(       pdf, _T("Red"));
    fillBoxPdf(        pdf, 20, 20, 50, 15);
    setColorPdf(       pdf, _T("White"));
    drawTextInBoxPdf(  pdf, _T("<RED>"), _T("lt"), 20, 20, 50, 15);

    setColorPdf(       pdf, _T("Green"));
    fillBoxPdf(        pdf, 70, 20, 50, 15);
    setColorPdf(       pdf, _T("White"));
    drawTextInBoxPdf(  pdf, _T("<GREEN>"), _T("c"), 70, 20, 50, 15);

    setColorPdf(       pdf, _T("Blue"));
    fillBoxPdf(        pdf, 120, 20, 50, 15);
    setColorPdf(       pdf, _T("White"));
    drawTextInBoxPdf(  pdf, _T("<BLUE>"), _T("rb"), 120, 20, 50, 15);

    /* page 2 */
    addPagePdf(        pdf);
    setUnitsPdf(       pdf, _T("cm"));
    drawUnitGridPdf(   pdf);
    setUnitsPdf(       pdf, _T("mm"));

    setFontSizePtPdf(  pdf, 40);
    setXyPdf(          pdf, 100, 100);
    setColorPdf(       pdf, _T("#AA0000"));
    drawTextPdf(       pdf, _T("(RED)"));
    setColorPdf(       pdf, _T("#00FF00"));
    drawTextPdf(       pdf, _T("(Green"));
    setColorPdf(       pdf, _T("#000081"));
    drawTextPdf(       pdf, _T("blue"));
    setDocAuthorPdf(   pdf, _T("By Me"));

    /* page 3 */
    addPagePdf(        pdf);
    setUnitsPdf(       pdf, _T("cm"));
    drawUnitGridPdf(   pdf);
    setUnitsPdf(       pdf, _T("mm"));

    setXyPdf(          pdf, 250, 250);
    setColorRgbPdf(    pdf, 128, 50, 50);
    drawTextPdf(       pdf, _T("(Hello World)"));

    addPagePdf(        pdf);
    setColorRgbPdf(    pdf, 0, 0, 128);
    setXyPdf(          pdf, 500, 500);
    drawTextPdf(       pdf, _T("(((\\)))"));

    setColorRgbPdf(    pdf, 0, 127, 0);
    setLineWidthPdf(   pdf, 3);
    drawLinePdf(       pdf, 100, 100, 700, 700);
    drawBoxPdf(        pdf, 100, 100, 700, 700);

    setColorRgbPdf(    pdf, 0, 0, 127);
    setLineWidthPdf(   pdf, 6);
    fillBoxPdf(        pdf, 200, 200, 250, 250);

    saveToFilePdf(     pdf, _T("__pdf_test_1.pdf"));
    freePdf(          &pdf);
} /* _pdf_test_1 */


static void  _pdf_test_2( void ) {                                         /*F*/
    pdf_t  pdf = PdfInit(_T("A4"));  /* 595 x 841 points */
    setCompressionPdf( pdf, false);

    addPagePdf(        pdf);
    setUnitsPdf(       pdf, _T("in"));
    drawUnitGridPdf(   pdf);
    setLineWidthPdf(   pdf, 0.1);
    setFontSizePtPdf(  pdf, 15);

    setColorPdf(       pdf, _T("Blue"));
    setColorPdf(       pdf, _T("Red"));
    fillBoxPdf(        pdf, 3, 1, 5, 2);

    setColorPdf(       pdf, _T("Green"));
    drawTextInBoxPdf(  pdf, _T("ABC"), NULL, 3, 1, 5, 2);

    drawBoxPdf(        pdf, 3, 1, 5, 2);

    saveToFilePdf(     pdf, _T("__pdf_test_2.pdf"));
    freePdf(&          pdf);
} /* _pdf_test_2 */


#if PLATFORM_WIN32  /* uses ADO */
static void  _pdf_report_test( void ) {                                    /*F*/
    uint32_t  time1      = uptime_ms();
    uint32_t  time2      = 0;
    uint32_t  time_spent = 0;

    Ado  db = Ado_openJetDb(_T("s:\\data\\proddata.mdb"),
                            NULL, NULL, NULL, NULL);

    new_chars_t  csv_str = Ado_readCsv(
                               db,
                               _T("SELECT TOP 10000")
                               _T(" EntryTime, CustomerID, ProductID, Product")
                               _T(" FROM tblFgProduct"),
                               /* _T(" WHERE CustomerID = 'C022'"), */
                               true);

    csv_t  csv = CsvReader(csv_str);
    pdf_t  pdf = PdfInit(_T("A4"));

    setCompressionPdf(pdf, false);

    addPagePdf(      pdf);
    drawUnitGridPdf( pdf);

    setColorPdf(             pdf, _T("Black"));
    setFontNamePdf(          pdf, _T("Helvetica"));
    setHorizontalScalingPdf( pdf, 60);
    setFontSizePtPdf(        pdf, 11);

    setColumnWidthsPdf(pdf,
                       4,
                       CAST(pixel_t, 120),
                       CAST(pixel_t, 40),
                       CAST(pixel_t, 70),
                       CAST(pixel_t, 200));

    drawTextPdf(pdf, _T("VAL1"));
    drawTextPdf(pdf, _T("VAL2"));
    drawTextPdf(pdf, _T("VAL3"));
    drawTextPdf(pdf, _T("VAL4"));

#if 111
    do {
        chars_t  val = readNextCsv(csv);

        if (isNewRowCsv(csv)) {
            goToNextLinePdf(pdf);
            /* PRINTF_T(_T("row %u \n"), row++); */
        } else {
            drawTextPdf(pdf, val);
        }
    } while (!isEofCsv(csv));
#endif                                                                 /* 111 */

    saveToFilePdf(pdf, _T("__pdf_report_test.pdf"));

    /* free all objects */
    freeCsv(&csv);
    freePdf(&pdf);
    Ado_free(&db);
    freeT(&csv_str);

    {
        /* report how much time was spent: */
        new_chars_t  msg = NULL;

        time2      = uptime_ms();
        time_spent = time2 - time1;
        msg        = formatT(_T("time spent: %ums"), time_spent);

        PRINTF_T(_T("%s"), msg);
        freeT(&msg);
    }
    mem_report();
} /* _pdf_report_test */
#endif                                                      /* PLATFORM_WIN32 */


PUBLIC void  test_pdf_class( void );                                       /*F*/
PUBLIC void  test_pdf_class( void ) {                                      /*F*/
    //_pdf_test_1();
    //_pdf_test_2();
    _pdf_test_3();

#if PLATFORM_WIN32
    /* _pdf_report_test(); */
#endif

} /* test_pdf_class */


#endif                                                                   /*eof*/
