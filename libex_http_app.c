/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                    [libex_http_app.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_http_app_.h"
#if defined INCLUDED_LIBEX_HTTP_APP_H

#include <string.h>  /* for memset() */

#include "libex_.h"
#include "libex_archive_.h"
#include "libex_array_.h"
#include "libex_bytes_.h"
#include "libex_call_.h"
#include "libex_debug_.h"
#include "libex_error_.h"
#include "libex_html_generator_.h"
#include "libex_http_server_.h"
#include "libex_macro_.h"
#include "libex_pdf_report_.h"
#include "libex_string_class_.h"
#include "libex_stringc_.h"
#include "libex_type_.h"
#include "libex_xml_reader_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif


/* TODO: remove this later, once utf8 encoding is used everywhere */
#if defined _MSC_VER
#pragma warning (disable:4133)  /* W:L3 incompatible types - from T1 to T2    */
#endif


#define _DOC_NOT_FOUND                                                \
    "<!DOCTYPE html PUBLIC '-//w3c//dtd xhtml 1.0 transitional//en'"  \
    " 'http://www.w3.org/tr/xhtml1/dtd/xhtml1-transitional.dtd'>"     \
    "<html xmlns='http://www.w3.org/1999/xhtml'>"                     \
    "<head><title>E404</title></head>"                                \
    "<body bgcolor='#ffffff'>"                                        \
    "<div style='position: absolute; left: 55px; width: 350px;"       \
    " top: 55px; height: 85px; background-color: #FF3300;"            \
    " font-family: Arial, Helvetica, sans-serif;"                     \
    " font-size: xx-large; font-weight: bolder;"                      \
    " color: #FFFFFF;' align='center'>"                               \
    "404: That page was not found! *</div>"                           \
    "<div style='position: absolute; left: 55px; width: 350px;"       \
    " top: 150px; font-family: Arial, Helvetica, sans-serif;"         \
    " font-weight: bolder; color: #FF3300;' align='center'>"          \
    "* However the server is responding.</div>"                       \
    "</body></html>"                                              /*#*/


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


typedef enum  _m_link_type_enum {
    LINK_UNKNOWN = 0,                                      /* _link_type_enum */
    LINK_STATIC,                                           /* _link_type_enum */
    LINK_PAGE,                                             /* _link_type_enum */
    LINK_REPORT,                                           /* _link_type_enum */
    LINK_SPECIAL                                           /* _link_type_enum */
}
_link_type_enum;                                                        /*enum*/


typedef struct  _link_t {    /* stores XML in <lx.link url="" type"" path="" */
    new_chars_t      url;                                          /* _link_t */
    _link_type_enum  type;                                         /* _link_t */
    new_chars_t      path;                                         /* _link_t */
}
_link_t;


typedef struct  _http_app_t {
    HttpServer  http;                                          /* _http_app_t */
    chars_t     site_path;                                     /* _http_app_t */
    archive_t   archive;                                       /* _http_app_t */
    array_t     links;                                         /* _http_app_t */

    HTTP_APP_DATA_READER_FN(data_reader_fn);                   /* _http_app_t */
}
_http_app_t;


static bool         _is_init = false;
static _http_app_t  _t;


/* -------------------------------------------------------------------------- */
/* Functions: Private                                                         */


static _link_type_enum  _link_type_from_chars( chars_t  text_ ) {          /*F*/
    GO                                                            (UID(F465D4));
    _link_type_enum  ret = LINK_UNKNOWN;

    if (equals_icT(text_, _T("static"))) {
        ret = LINK_STATIC;

    } else if (equals_icT(text_, _T("page"))) {
        ret = LINK_PAGE;

    } else if (equals_icT(text_, _T("report"))) {
        ret = LINK_REPORT;

    } else if (equals_icT(text_, _T("special"))) {
        ret = LINK_SPECIAL;
    } else {
        ret = LINK_UNKNOWN;
    }
    RETURN(ret);
} /* _link_type_from_chars */


/* -------------------------------------------------------------------------- */


static void  _fill_links_array(                                            /*F*/
    chars_t  xml_,                                                         /*-*/
    array_t  links_ ) {                                                    /*-*/
    GO                                                            (UID(FB354B));
    Xmlr  xml  = Xmlr_of_chars(xml_);
    bool  read = false;

    Xmlr_goRoot(xml);

    while (!Xmlr_eof(xml)) {
        if (Xmlr_isStartTag(xml, _T("lx.links"))) {
            read = true;

        } else if (read && Xmlr_isEmptyTag(xml, _T("lx.link"))) {
            _link_t  link = { NULL, LINK_UNKNOWN, NULL };

            link.url = T_chars(Xmlr_attr(xml, _T("url")));
            {
                chars_t const  type = Xmlr_attr(xml, _T("type"));
                link.type = _link_type_from_chars(type);
            }
            link.path = T_chars(Xmlr_attr(xml, _T("path")));

            Array_addItem(&links_, &link, sizeof(link), NULL);
        } else if (read && Xmlr_isEndTag(xml, _T("lx.links"))) {
            break;
        }

        Xmlr_skipTag(xml);
    }
    freeXmlr(&xml);

    RETURN(NIL);
} /* _fill_links_array */


static void  _free_links_array( array_t*  links_ ) {                       /*F*/
    GO                                                            (UID(F87ED7));
    size_t        i     = 0;
    const size_t  count = Array_count(*links_);

    for (i = 0; i < count; i++) {
        _link_t*  link = CAST(_link_t*, Array_getItemAt(links_, i));
        freeT(&link->url);
        freeT(&link->path);
    }

    if (count > 0) {
        Array_removeItems(links_);
    }

    Array_free(links_);

    RETURN(NIL);
} /* _free_links_array */


static new_bytes_t  _get_page_html(                                        /*F*/
    archive_t  archive_,                                                   /*-*/
    str_t      settings_,                                                  /*-*/
    chars_t    page_name_ ) {                                              /*-*/
    GO                                                            (UID(F35B9B));
    new_bytes_t  ret        = { 0, NULL };
    new_str_t    xml_layout = Archive_getText(archive_, page_name_);

    if (!IS_BLANK(xml_layout.cs)) {
        const void*  NO_CSV = NULL;
        new_chars_t  html = html_generate(xml_layout.cs, settings_.cs, NO_CSV);
        ret = Bytes_fromNewChars(html);
    }
    freeS(&xml_layout);

    RETURN(ret);
} /* _get_page_html */


static new_bytes_t  _get_page(                                             /*F*/
    archive_t  archive_,                                                   /*-*/
    chars_t    page_name_ ) {                                              /*-*/
    GO                                                            (UID(F41D57));
    new_bytes_t  ret          = { 0, NULL };
    new_str_t    xml_settings = { NULL };

    if (Archive_itemExists(archive_, _T("app.settings.xml"))) {
        xml_settings = Archive_getText(archive_, _T("app.settings.xml"));
    }

    if (Archive_itemExists(archive_, page_name_)) {
        ret = _get_page_html(archive_, xml_settings, page_name_);
    }
    freeS(&xml_settings);

    RETURN(ret);
} /* _get_page */


static new_bytes_t  _get_report(                                           /*F*/
    archive_t  archive_,                                                   /*-*/
    chars_t    report_name_ ) {                                            /*-*/
    GO                                                            (UID(FB2573));
    new_bytes_t  ret = { 0, NULL };

    if (Archive_itemExists(archive_, report_name_)) {

        archive_item_t  item   = Archive_getItem(archive_, report_name_);
        new_chars_t     xml    = Tutf8(CAST(const char*, item.item_data));
        new_chars_t     sql    = T_get_tag(xml, _T("<sql>"), _T("</sql>"));
        new_chars_t     csv    = NULL;
        new_Report      report = Report_init();

        if (_t.data_reader_fn != NULL) {
            csv = (*_t.data_reader_fn)(sql);
        }

        ret = Report_get(report, xml, csv);

        freeT(&xml);
        freeT(&sql);
        freeT(&csv);
        Report_free(&report);
    }
    RETURN(ret);
} /* _get_report */


/* -------------------------------------------------------------------------- */
/* Initializer:                                                               */


PUBLIC void  HttpApp_init(                                                 /*C*/
    archive_t  archive_,                                                   /*-*/
    chars_t    site_path_ ) {                                              /*-*/
    GO                                                            (UID(F23B6D));
    chars_t  LINKS_DOC = _T("app.links.xml");

    if (_is_init) {
        WARN(_T("HttpApp_init() already called previously."), UID(E863C2));
    } else {
        _is_init = true;

        CLEAR(_t);
        _t.archive        = archive_;
        _t.site_path      = site_path_;
        _t.links          = Array_init(sizeof(_link_t), 100, 0);
        _t.data_reader_fn = NULL;
        _t.http           = HttpServer_init();

        HttpServer_setHttpGetHandler(_t.http, &HttpApp_get);

        if (Archive_itemExists(archive_, LINKS_DOC)) {
            archive_item_t  item = Archive_getItem(archive_, LINKS_DOC);
            new_chars_t     xml  = Tutf8(CAST(const char*, item.item_data));

            _fill_links_array(xml, _t.links);
            freeT(&xml);
        }
    }
    RETURN(NIL);
} /* HttpApp_init */


/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */


PUBLIC void  HttpApp_free( void ) {                                        /*D*/
    GO                                                            (UID(F3B8C8));
    HttpServer_free(&_t.http);
    _free_links_array(&_t.links);
    RETURN(NIL);
} /* HttpApp_free */


/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */


PUBLIC void  HttpApp_setDataReader(                                        /*M*/
    HTTP_APP_DATA_READER_FN(  callback_fn_) ) {                            /*-*/
    GO                                                            (UID(F9B8AF));
    _t.data_reader_fn = callback_fn_;
    RETURN(NIL);
} /* HttpApp_setDataReader */


PUBLIC void  HttpApp_run( const int  listen_on_port_ ) {                   /*M*/
    GO                                                            (UID(F614C0));
    HttpServer_run(_t.http, listen_on_port_);
    RETURN(NIL);
} /* HttpApp_run */


/* -------------------------------------------------------------------------- */
/* Methods: HTTP                                                              */

PUBLIC new_bytes_t  HttpApp_get(  http_request_t*  request_ ) {            /*M*/
    GO                                                            (UID(F5141C));
    new_bytes_t   ret          = { 0, NULL };
    size_t        i            = 0;
    const size_t  links_count  = Array_count(_t.links);
    bool          is_processed = false;
    new_chars_t   link         = Tutf8(CAST(char*, request_->recv_url));

    for (i = 0; i < links_count; i++) {
        const _link_t*  item =
            CAST(const _link_t*, Array_getItemAt(&_t.links, i));

        if (equals_icT(link, item->url)) {
            if (item->type == LINK_STATIC) {
                set_inT(&link, item->path);
                break;

            } else if (item->type == LINK_PAGE) {
                ret = _get_page(_t.archive, item->path);
                is_processed = true;
                break;
            } else if (item->type == LINK_REPORT) {
                ret = _get_report(_t.archive, item->path);
                is_processed = true;
                break;
            } else if (item->type == LINK_SPECIAL &&
                       equals2T(item->path, _T("terminate_server"))) {
                HttpServer_stop(_t.http);
                is_processed = true;
            }

            /* TODO: add processing of file links (LINK_FILE??) */

            /*
                } else if (file_exists(path)) {
                    ret = file_load_bytes(path);
                }
            */
        }
    }

    if (!is_processed) {
        new_chars_t  path = NULL;

        if (ends2T(_t.site_path, _T("/"))) {
            path = formatT(_T("%s%s"), _t.site_path, link);
        } else {
            path = formatT(_T("%s/%s"), _t.site_path, link);
        }

        if (Archive_itemExists(_t.archive, path)) {
            archive_item_t  item = Archive_getItem(_t.archive, path);

            ret          = Bytes_init(item.item_data, item.item_size);
            is_processed = true;
        } else {
            /* TODO: display 404 */
        }

        freeT(&path);
    }

    freeT(&link);

    RETURN(ret);
} /* HttpApp_get */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
