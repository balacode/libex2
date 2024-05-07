/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                  [libex_pdf_report.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_pdf_report_.h"
#if defined INCLUDED_LIBEX_PDF_REPORT_H

#include <limits.h>
#include <string.h>  /* for memset() */

#include "libex_.h"
#include "libex_call_.h"
#include "libex_const_.h"
#include "libex_csv_.h"
#include "libex_debug_.h"
#include "libex_error_.h"
#include "libex_macro_.h"
#include "libex_pdf_.h"
#include "libex_stringc_.h"
#include "libex_type_.h"
#include "libex_xml_reader_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#define _MAX_CGROUPS  10
#define _MAX_COLUMNS  40


/* -------------------------------------------------------------------------- */


typedef enum  _m_format_enum {
    FORMAT_NONE = 0,                                          /* _format_enum */
    FORMAT_CODE,                                              /* _format_enum */
    FORMAT_NAME,                                              /* _format_enum */
    FORMAT_0_DP,                                              /* _format_enum */
    FORMAT_1_DP,                                              /* _format_enum */
    FORMAT_2_DP                                               /* _format_enum */
}
_format_enum;                                                           /*enum*/


#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4820)  /* W:L4 'N' bytes padding added after 'NAME'  */
#endif


typedef struct  _col_group_t {
    new_chars_t  title;                                       /* _col_group_t */
    pixel_t      x;                                           /* _col_group_t */
    pixel_t      width;                                       /* _col_group_t */
}
_col_group_t;


typedef struct  _col_t {
    new_chars_t   title;                                            /* _col_t */
    _format_enum  format;                                           /* _col_t */
    chars_t       align;                                            /* _col_t */
    pixel_t       x;                                                /* _col_t */
    pixel_t       width;                                            /* _col_t */
    new_chars_t   source;                                           /* _col_t */
    uint32_t      cgroup;                                           /* _col_t */
}
_col_t;


#if defined _MSC_VER
#pragma warning (pop)
#endif


typedef struct  _report_t {
    new_chars_t    report_title;                                 /* _report_t */
    new_chars_t    organization;                                 /* _report_t */
    new_chars_t    sql;                                          /* _report_t */
    new_chars_t    page_size;                                    /* _report_t */
    pixel_t        margin_left;                                  /* _report_t */
    pixel_t        margin_top;                                   /* _report_t */
    pixel_t        margin_right;                                 /* _report_t */
    pixel_t        margin_bottom;                                /* _report_t */
    pixel_t        columns_width;                                /* _report_t */
    uint32_t       cgroup_count;                                 /* _report_t */
    uint32_t       col_count;                                    /* _report_t */
    _col_group_t   cgroups[_MAX_CGROUPS];                        /* _report_t */
    _col_t         columns[_MAX_COLUMNS];                        /* _report_t */
}
_report_t;


/* -------------------------------------------------------------------------- */
/* Functions: Private                                                         */


#define _BASE_OBJ_WRAP_INC
#define _OBJ_HANDLE_TYPE   Report
#define _OBJ_INNER_TYPE    _report_t
#define _OBJ_ALLOC_FN_UID  UID(FDFEF1)
#define _OBJ_FREE_FN_UID   UID(F47245)
#define _OBJ_CONST_FN_UID  UID(F934D1)
#define _OBJ_FN_UID        UID(F3A56F)
#define _OBJ_WRAP_FN_UID   UID(FA64A4)
#include "libex_object_wrapper.inc.c"


/* -------------------------------------------------------------------------- */


static chars_t  _horizontal_alignment( _format_enum  format_ ) {           /*F*/
    GO                                                            (UID(FA8A7C));
    chars_t  ret = _T("c");
    switch (format_) {
            CASE(FORMAT_NONE, ret = _T("c"));  /* center/left/right */
            CASE(FORMAT_CODE, ret = _T("c"));
            CASE(FORMAT_NAME, ret = _T("l"));
            CASE(FORMAT_0_DP, ret = _T("l"));
            CASE(FORMAT_1_DP, ret = _T("r"));
            CASE(FORMAT_2_DP, ret = _T("r"));
        default:
            ret = _T("");
    }
    RETURN(ret);
} /* _horizontal_alignment */


static void  _draw_multiline_text(                                         /*F*/
    pdf_t          pdf_,                                                   /*-*/
    chars_t        text_,                                                  /*-*/
    chars_t        text_align_,                                            /*-*/
    const pixel_t  font_size_,                                             /*-*/
    const pixel_t  x_,                                                     /*-*/
    const pixel_t  y_,                                                     /*-*/
    const pixel_t  width_ ) {                                              /*-*/
    GO                                                            (UID(FC1B03));
    const size_t  lines = token_countT(text_, _T("~"));

    if (lines == 1) {
        drawTextInBoxPdf(pdf_, text_, text_align_, x_, y_, width_, font_size_);
    } else {
        size_t   line   = 0;
        pixel_t  line_y = y_;

        for (line = 0; line < lines; line++) {
            new_chars_t  str = T_get_token(text_, line, _T("~"));
            drawTextInBoxPdf(pdf_, str, text_align_, x_, line_y, width_,
                             font_size_);
            line_y += font_size_;
            freeT(&str);
        }
    }
    RETURN(NIL);
} /* _draw_multiline_text */


/* -------------------------------------------------------------------------- */
/* Private Functions for Drawing:                                             */


static void  _draw_cgroup_headings(                                        /*F*/
    pdf_t       pdf_,                                                      /*-*/
    _report_t*  report_,                                                   /*-*/
    pixel_t*    y_in_out_ ) {                                              /*-*/
    GO                                                            (UID(FCB2A4));
    const pixel_t  FONT_SIZE = 10;

    uint32_t  i                = 0;
    uint32_t  cgroup_lines_max = 0;
    pixel_t   head_height      = 0;
    pixel_t   line_height      = 0;

    setFontNamePdf(pdf_, _T("Helvetica"));
    setFontSizePtPdf(pdf_, FONT_SIZE);
    setHorizontalScalingPdf(pdf_, 80);

    /* determine maximum number of lines in column group headings */
    cgroup_lines_max = 0;

    for (i = 0; i < report_->cgroup_count; i++) {
        const uint32_t  lines =
            token_countT(report_->cgroups[i].title, _T("~"));

        if (cgroup_lines_max < lines) {
            cgroup_lines_max = lines;
        }
    }

    head_height = (FONT_SIZE * cgroup_lines_max) + 4;

    /* calculate height of vertical lines */
    line_height = getPageHeightPtPdf(pdf_) - * y_in_out_
                  - report_->margin_bottom - 8
                  - convert_to_pdf_points(_T("0.5cm"));

    /* fill background */
    setColorPdf(pdf_, _T("LightGray"));
    fillBoxPdf(pdf_, report_->margin_left,
               *y_in_out_, report_->columns_width, head_height);

    /* draw border around column heading */
    setColorPdf(pdf_, _T("Black"));
    drawBoxPdf(pdf_, report_->margin_left,
               *y_in_out_, report_->columns_width, line_height);

    /* draw each column group */
    for (i = 0; i < report_->cgroup_count; i++) {
        const _col_group_t  cgroup = report_->cgroups[i];
        const pixel_t        x      = report_->margin_left + cgroup.x;
        const pixel_t        width  = cgroup.width;

        /* fill background */
        setColorPdf(pdf_, _T("LightGray"));
        fillBoxPdf(pdf_, x, *y_in_out_, width, head_height);

        /* draw border around column heading */
        setColorPdf(pdf_, _T("Black"));
        drawBoxPdf(pdf_, x, *y_in_out_, width, line_height);

        _draw_multiline_text(pdf_, cgroup.title, _T("c"),
                             FONT_SIZE, x, *y_in_out_, width);
    }

    *y_in_out_ += head_height;

    RETURN(NIL);
} /* _draw_cgroup_headings */


static void  _draw_column_headings(                                        /*F*/
    pdf_t       pdf_,                                                      /*-*/
    _report_t*  report_,                                                   /*-*/
    pixel_t*    y_in_out_ ) {                                              /*-*/
    GO                                                            (UID(F35E84));
    const pixel_t  FONT_SIZE = 10;

    uint32_t  i                 = 0;
    pixel_t   height            = 0;
    uint32_t  heading_lines_max = 0;

    setFontNamePdf(pdf_, _T("Helvetica"));
    setFontSizePtPdf(pdf_, FONT_SIZE);
    setHorizontalScalingPdf(pdf_, 80);

    /* determine maximum number of lines in column headings */
    for (i = 0; i < report_->col_count; i++) {
        const _col_t*   col   = &report_->columns[i];
        const uint32_t  lines = token_countT(col->title, _T("~"));

        if (heading_lines_max < lines) {
            heading_lines_max = lines;
        }
    }

    height = (FONT_SIZE * heading_lines_max) + 4;

    for (i = 0; i < report_->col_count; i++) {
        const _col_t   col = report_->columns[i];
        const pixel_t  x   = report_->margin_left + col.x;

        /* fill background */
        setColorPdf(pdf_, _T("LightGray"));
        fillBoxPdf(pdf_, x, *y_in_out_, col.width, height);

        /* draw border around column heading */
        setColorPdf(pdf_, _T("Black"));
        drawBoxPdf(pdf_, x, *y_in_out_, col.width, height);

        _draw_multiline_text(
            pdf_,        /* pdf_t    pdf_        */
            col.title,   /* chars_t  text_       */
            col.align,   /* chars_t  text_align_ */
            FONT_SIZE,   /* pixel_t  font_size_  */
            x,           /* pixel_t  x_          */
            *y_in_out_,  /* pixel_t  y_          */
            col.width);  /* pixel_t  width_      */
    }

    * y_in_out_ += height;

    RETURN(NIL);
} /* _draw_column_headings */


static void  _draw_page_footer(                                            /*F*/
    pdf_t          pdf_,                                                   /*-*/
    const pixel_t  font_size_,                                             /*-*/
    const pixel_t  bottom_margin_,                                         /*-*/
    const pixel_t  left_margin_,                                           /*-*/
    const pixel_t  columns_width_ ) {                                      /*-*/
    GO                                                            (UID(FF831E));
    const pixel_t  page_height = getPageHeightPtPdf(pdf_);
    const pixel_t  y           = page_height - bottom_margin_ - font_size_;
    const pixel_t  width       = columns_width_;

    setColorPdf(      pdf_, _T("LightGray"));
    setLineWidthPdf(  pdf_, 2);
    drawLinePdf(      pdf_, left_margin_, y,
                      left_margin_ + columns_width_, y);

    setColorPdf(      pdf_, _T("DarkGray"));
    setFontNamePdf(   pdf_, _T("Helvetica"));
    setFontSizePtPdf( pdf_, font_size_);

    drawTextInBoxPdf( pdf_, _T("ReportName"),
                      _T("l"), left_margin_, y, width, font_size_);

    drawTextInBoxPdf( pdf_, _T("Page 0 of 0"),
                      _T("c"), left_margin_, y, width, font_size_);

    drawTextInBoxPdf( pdf_, _T("00/00/0000 00:00pm"),
                      _T("r"), left_margin_, y, width, font_size_);

    RETURN(NIL);
} /* _draw_page_footer */


static void  _draw_fixed_page_elements(                                    /*F*/
    pdf_t       pdf_,                                                      /*-*/
    _report_t*  report_ ) {                                                /*-*/
    GO                                                            (UID(F8CACA));
    const pixel_t  TITLE_FONT_SIZE  = 14;
    const pixel_t  FOOTER_FONT_SIZE = 8;

    pixel_t  y = report_->margin_top;

    /* draw cm grid, then switch to points */
#if 000
    setUnitsPdf(pdf_, _T("cm"));
    drawUnitGridPdf(pdf_);
#endif                                                                 /* 000 */
    setUnitsPdf(pdf_, _T("points"));

    setColorPdf(pdf_, _T("Navy"));
    setFontNamePdf(pdf_, _T("Times-Bold"));
    setFontSizePtPdf(pdf_, TITLE_FONT_SIZE);

    /* draw organization name */
    if (!is_whitespaceT(report_->organization)) {
        setXyPdf(pdf_, report_->margin_left, y + TITLE_FONT_SIZE);
        drawTextPdf(pdf_, report_->organization);
        y += TITLE_FONT_SIZE + convert_to_pdf_points(_T("0.1cm"));
    }

    /* draw report name */
    if (!is_whitespaceT(report_->organization)) {
        setXyPdf(pdf_, report_->margin_left, y + TITLE_FONT_SIZE);
        drawTextPdf(pdf_, report_->report_title);
        y += TITLE_FONT_SIZE + convert_to_pdf_points(_T("0.1cm"));
    }

    y += convert_to_pdf_points(_T("0.3cm"));

    _draw_cgroup_headings(pdf_, report_, &y);
    _draw_column_headings(pdf_, report_, &y);

    _draw_page_footer(
        pdf_,
        FOOTER_FONT_SIZE,
        report_->margin_bottom,
        report_->margin_left,
        report_->columns_width);

    RETURN(NIL);
} /* _draw_fixed_page_elements */


static _format_enum  _format( chars_t  format_string_ ) {                  /*F*/
    GO                                                            (UID(F58698));
    new_chars_t   fmt = T_chars(format_string_);
    _format_enum  ret = FORMAT_NONE;

    lower_in_T(fmt);

    if (equals2T(fmt, _T("code"))) {
        ret = FORMAT_CODE;
    }

    if (equals2T(fmt, _T("name"))) {
        ret = FORMAT_NAME;
    }

    if (equals2T(fmt, _T("0dp"))) {
        ret = FORMAT_0_DP;
    }

    if (equals2T(fmt, _T("1dp"))) {
        ret = FORMAT_1_DP;
    }

    if (equals2T(fmt, _T("2dp"))) {
        ret = FORMAT_2_DP;
    }

    freeT(&fmt);

    RETURN(ret);
} /* _format */


static void  _parse_xml(                                                   /*F*/
    _report_t*  object_,                                                   /*-*/
    chars_t     xml_ ) {                                                   /*-*/
    GO                                                            (UID(CB6753));
#define DEFAULT_PAGE_SIZE  _T("A4")
#define DEFAULT_MARGIN     _T("1.5cm")

    new_Xmlr  xml = Xmlr_of_chars(xml_);

#if 000
    chars_t  debug_info = Xmlr_debugInfo(xml);
    DUMP_OPEN;
    DUMP(_T("%s"), debug_info);
    DUMP_CLOSE;
#endif                                                                 /* 000 */

    Xmlr_goRoot(xml);

    set_inT(&object_->organization, Xmlr_attr(xml, _T("org")));
    set_inT(&object_->report_title, Xmlr_attr(xml, _T("title")));

    set_default_inT(&object_->page_size, Xmlr_attr(xml, _T("pageSize")),
                    DEFAULT_PAGE_SIZE);

    set_inT(&object_->sql, Xmlr_childContent(xml, true, _T("sql")));

    {
        /* set margins:          */
        /* read margins from xml */
        new_chars_t  margin_left   = NULL;
        new_chars_t  margin_top    = NULL;
        new_chars_t  margin_right  = NULL;
        new_chars_t  margin_bottom = NULL;

        set_default_inT(&margin_left, Xmlr_attr(xml, _T("leftMargin")),
                        DEFAULT_MARGIN);

        set_default_inT(&margin_top, Xmlr_attr(xml, _T("topMargin")),
                        DEFAULT_MARGIN);

        set_default_inT(&margin_right, Xmlr_attr(xml, _T("rightMargin")),
                        DEFAULT_MARGIN);

        set_default_inT(&margin_bottom, Xmlr_attr(xml, _T("bottomMargin")),
                        DEFAULT_MARGIN);

        object_->margin_left   = convert_to_pdf_points(margin_left);
        object_->margin_top    = convert_to_pdf_points(margin_top);
        object_->margin_right  = convert_to_pdf_points(margin_right);
        object_->margin_bottom = convert_to_pdf_points(margin_bottom);

        freeT(&margin_left);
        freeT(&margin_top);
        freeT(&margin_right);
        freeT(&margin_bottom);
    }

    /* read columns */
    Xmlr_goRoot(xml);

    if (Xmlr_goChild(xml, _T("columns"))) {
        pixel_t  x = 0;

        Xmlr_goChild(xml, NULL);

        object_->col_count     = 0;
        object_->columns_width = 0;

        do {
            if (Xmlr_isTagName(xml, _T("column"))) {
                _col_t  col;
                CLEAR(col);

                col.title  = T_chars(Xmlr_attr(xml, _T("title")));
                col.format = _format(Xmlr_attr(xml, _T("format")));
                col.align  = _horizontal_alignment(col.format);
                col.x      = x;
                col.width  = convert_to_pdf_points(Xmlr_attr(xml,
                                                   _T("width")));
                col.source = T_chars(Xmlr_attr(xml, _T("source")));

                object_->columns[object_->col_count] = col;
                object_->col_count++;
                object_->columns_width += col.width;

                x += col.width;
            }
        } while (object_->col_count < _MAX_COLUMNS &&
                 Xmlr_goAnyNext(xml, _T("column")));
    }

    /* read column groups */
    Xmlr_goRoot(xml);

    if (Xmlr_goChild(xml, _T("columns"))) {
        pixel_t   x      = 0;
        uint32_t  column = 0;

        Xmlr_goChild(xml, NULL);
        object_->cgroup_count = 0;

        do {
            if (Xmlr_isTagName(xml, _T("cgroup"))) {
                _col_group_t  cgroup;
                CLEAR(cgroup);
                cgroup.x     = x;
                cgroup.width = 0;
                cgroup.title = T_chars(Xmlr_attr(xml, _T("title")));

                object_->cgroups[object_->cgroup_count] = cgroup;
                object_->cgroup_count++;
            } else if (Xmlr_isTagName(xml, _T("column"))) {
                _col_t* const  col = &object_->columns[column];

                if (Xmlr_isParentTag(xml, _T("cgroup"))) {
                    _col_group_t*  group =
                        &object_->cgroups[object_->cgroup_count - 1];
                    group->width += col->width;
                }

                x += col->width;
                column++;
            }
        } while (object_->cgroup_count < _MAX_CGROUPS &&
                 Xmlr_goAnyNext(xml, NULL));
    }
    RETURN(NIL);

#undef DEFAULT_PAGE_SIZE
#undef DEFAULT_MARGIN
} /* _parse_xml */


/* -------------------------------------------------------------------------- */
/* Constructor:                                                               */


PUBLIC new_Report  Report_init( void ) {                                   /*C*/
    GO                                                            (UID(C6DD49));
    _report_t* const  ob  = _object_alloc();
    new_Report        ret = _object_wrap(ob);
    CLEAR(*ob);
    RETURN(ret);
} /* Report_init */


/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */


PUBLIC void  Report_free( Report*  object_ ) {                             /*D*/
    GO                                                            (UID(F97D37));
    _object_free(object_);
    RETURN(NIL);
} /* Report_free */


/* -------------------------------------------------------------------------- */


static void  _process_report_data(                                         /*F*/
    pdf_t       pdf_,                                                      /*-*/
    _report_t*  report_,                                                   /*-*/
    chars_t     csv_rows_ ) {                                              /*-*/
    GO                                                            (UID(F317E9));
    new_csv_t  csv     = CsvReader(csv_rows_);
    uint32_t   csv_col = 0;
    uint32_t   row     = 0;
    pixel_t    y       = 120;

    /* match column names in CSV to column indexes in the report's array */
    uint32_t  col_index[_MAX_COLUMNS];
    CLEAR(col_index);
    csv_col = 0;

    do {
        chars_t   col_name = readNextCsv(csv);
        uint32_t  i        = 0;

        if (csv_col < _MAX_COLUMNS) {
            col_index[csv_col] = NONE;

            for (i = 0; i < report_->col_count; i++) {
                if (equals2T(report_->columns[i].source, col_name)) {
                    col_index[csv_col] = i;
                    break;
                }
            }
        }
        csv_col++;
    } while (!isNewRowCsv(csv) && !isEofCsv(csv));

    /* read data */
    setColorPdf(pdf_, _T("black"));
    csv_col = 0;

    do {
        chars_t  val = readNextCsv(csv);

        if (isNewRowCsv(csv)) {
            csv_col = 0;
            row++;
            y += 11;
            if (row > 63) {
                break;    /* TODO: remove later */
            }
        } else if (csv_col < _MAX_COLUMNS) {
            const uint32_t  index = col_index[csv_col];

            if (index != NONE && index < _MAX_COLUMNS) {
                const _col_t*  col    = &report_->columns[index];
                const pixel_t  x      = report_->margin_left + col->x;
                const pixel_t  height = 11;

                drawTextInBoxPdf(pdf_,
                                 val, col->align, x, y, col->width, height);
            }
            csv_col++;
        } else {
            csv_col++;
        }
    } while (!isEofCsv(csv));

    freeCsv(&csv);
    RETURN(NIL);
} /* _process_report_data */


PUBLIC new_bytes_t  Report_get(                                            /*M*/
    Report   object_,                                                      /*-*/
    chars_t  report_xml_,                                                  /*-*/
    chars_t  csv_rows_ ) {                                                 /*-*/
    GO                                                            (UID(F9C901));
    _report_t* const  me = _object(&object_, UID(E64ACB));

    new_pdf_t    pdf = { NULL };
    new_bytes_t  ret = { 0, NULL };

    _parse_xml(me, report_xml_);
    pdf = PdfInit(me->page_size);
    addPagePdf(pdf);
    _draw_fixed_page_elements(pdf, me);

    _process_report_data(pdf, me, csv_rows_);

    ret = BytesFromPdf(pdf);
    freePdf(&pdf);

    RETURN(ret);
} /* Report_get */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
