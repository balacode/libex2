/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                              [libex_html_generator.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_html_generator_.h"
#if defined INCLUDED_LIBEX_HTML_GENERATOR_H

#include <limits.h>

#include "libex_.h"
#include "libex_array_.h"
#include "libex_call_.h"
#include "libex_const_.h"
#include "libex_csv_.h"
#include "libex_debug_.h"
#include "libex_error_.h"
#include "libex_macro_.h"
#include "libex_string_class_.h"
#include "libex_stringc_.h"
#include "libex_type_.h"
#include "libex_xml_reader_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif

/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


typedef struct  _macro_t {
    uint32_t     macro_def;                                       /* _macro_t */
    new_chars_t  csv_find;                                        /* _macro_t */
    new_str_t    text;                                            /* _macro_t */
}
_macro_t;


/* -------------------------------------------------------------------------- */
/* Functions: Private                                                         */


static _macro_t*  _process_tag_macro_def(                                  /*F*/
    Xmlr     xml_,                                                         /*-*/
    array_t  macros_ ) {                                                   /*-*/
    GO                                                            (UID(F2340C));
    /* input: <lx.macro.def id="name" attr1="REPLACE1" attr2="REPLACE2" ...> */
    /* ... </lx.macro.def> */

    _macro_t*  ret = NULL;

    if (Xmlr_isStartTag(xml_, NULL)) {
        _macro_t  macro = { 0, NULL, { NULL } };

        macro.macro_def = Xmlr_position(xml_);
        macro.csv_find  = Xmlr_attrsToCsv(xml_);
        macro.text      = S_chars(BLANK);

        Array_addItem(&macros_, &macro, sizeof(_macro_t), NULL);
        ret = CAST(_macro_t*, Array_getLastItem(&macros_));
    } else {
        WARN(_T("Tag type is not a starting tag."), UID(E4CE9F));
    }

    Xmlr_skipTag(xml_);
    RETURN(ret);
} /* _process_tag_macro_def */


/* only used by _process_tag_macro() */
static void  _process_tag_macro_helper(                                    /*F*/
    str_t*     output_,                                                    /*-*/
    _macro_t*  macro_,                                                     /*-*/
    chars_t    csv_replace_ ) {                                            /*-*/
    GO                                                            (UID(F9FCD7));
    new_chars_t  text = T_chars(macro_->text.cs);
    size_t       i    = 0;

    do {
        new_chars_t  key = csv_item(macro_->csv_find, i, 0);

        if (IS_BLANK(key)) {
            i = NONE;

        } else if (!equals2T(key, _T("id"))) {
            new_chars_t  find    = csv_item(macro_->csv_find, i, 1);
            new_chars_t  replace = csv_key_value(csv_replace_, key);

            replace_in_T(&text, find, replace);

            freeT(&find);
            freeT(&replace);
        }

        freeT(&key);
    } while (i++ != NONE);

    addTS(output_, text);
    freeT(&text);

    RETURN(NIL);
} /* _process_tag_macro_helper */


static void  _process_tag_macro(                                           /*F*/
    Xmlr     xml_,                                                         /*-*/
    str_t*   output_,                                                      /*-*/
    array_t  macros_ ) {                                                   /*-*/
    GO                                                            (UID(F2B452));
    /* input: <lx.macro id="name" attr1="REPLACE1" attr2="REPLACE2" ...> */
    /*        ... </lx.macro>                                            */

    if (Xmlr_isEmptyTag(xml_, NULL)) {
        size_t        i        = 0;
        const size_t  count    = Array_count(macros_);
        chars_t       macro_id = Xmlr_attr(xml_, _T("id"));

        ASSERT(!IS_BLANK(macro_id), UID(E623C9));

        for (i = 0; i < count; i++) {
            _macro_t*    macro = CAST(_macro_t*, Array_getItemAt(&macros_, i));
            new_chars_t  id    = csv_key_value(macro->csv_find, _T("id"));
            const bool   match = equals2T(id, macro_id);

            freeT(&id);

            if (match) {
                new_chars_t  args = Xmlr_attrsToCsv(xml_);
                _process_tag_macro_helper(output_, macro, args);
                freeT(&args);
                break;
            }
        }
    }

    Xmlr_skipElement(xml_);

    RETURN(NIL);
} /* _process_tag_macro */


static void  _process_tag_html(                                            /*F*/
    Xmlr    xml_,                                                          /*-*/
    str_t*  output_ ) {                                                    /*-*/
    GO                                                            (UID(FA4498));
    /* input: <lx.html> </lx.html> */

    if (Xmlr_isStartTag(xml_, _T("lx.html"))) {
        addTS(output_, _T("<html>"));

    } else if (Xmlr_isEndTag(xml_, _T("lx.html"))) {
        addTS(output_, _T("</html>"));
    } else {
        WARN(_T("wrong tag!"), UID(E75497));
    }

    Xmlr_skipTag(xml_);
    RETURN(NIL);
} /* _process_tag_html */


static void  _process_tag_ie6(                                             /*F*/
    Xmlr    xml_,                                                          /*-*/
    str_t*  output_ ) {                                                    /*-*/
    GO                                                            (UID(F958BD));
    /* input: <lx.ie6> ... </lx.ie6> */

    const bool  ie6 = false;

#if defined __GNUC__                   /* get rid of warning caused by ie6 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunreachable-code"
#endif

    if (ie6 && Xmlr_isStartTag(xml_, NULL)) {
        new_chars_t  text = T_chars(Xmlr_content(xml_, false));
        remove_extra_spaces_in_T(text);
        addTS(output_, text);
        freeT(&text);
    }

#if defined __GNUC__
#pragma GCC diagnostic pop
#endif

    Xmlr_skipElement(xml_);
    RETURN(NIL);
} /* _process_tag_ie6 */


static void  _process_tag_label(                                           /*F*/
    Xmlr    xml_,                                                          /*-*/
    str_t*  output_ ) {                                                    /*-*/
    GO                                                            (UID(F67C62));
    /* input: <lx.label text="text" [format="format"] /> */

    if (Xmlr_isEmptyTag(xml_, NULL)) {
        new_chars_t  text  = T_chars(Xmlr_attr(xml_, _T("text")));
        new_chars_t  tran  = NULL;  /* translated text */
        new_chars_t  fmt   = T_chars(Xmlr_attr(xml_, _T("format")));
        new_chars_t  label = NULL;

        while (contains2T(text, _T("{}"))) {
            replace_in_T(&text, _T("{}"), _T(""));
            set_inT(&fmt, _T(""));
        }

        while (contains3T(text, _T("{B}"), IGNORE_CASE)) {
            replace_in_T(&text, _T("{b}"), _T(""));
            replace_in_T(&text, _T("{B}"), _T(""));
            set_inT(&fmt, _T("B"));
        }

        tran = T_chars(text);  /* TODO: add translation code */

        if (!IS_BLANK(fmt)) {
            upper_in_T(fmt);

#if 1

            /* one language */
            if (equals2T(fmt, _T("TITLE"))) {
                label = formatT(_T("&nbsp; %s &nbsp;"), text);

            } else if (equals2T(fmt, _T("TH"))) {
                label = formatT(_T("<b>%s</b>"), text);

            } else if (equals2T(fmt, _T("BR"))) {
                label = formatT(_T("<b>%s</b>"), text);

            } else if (equals2T(fmt, _T("B"))) {
                label = formatT(_T("<b>%s</b>"), text);

            } else if (equals2T(fmt, _T("EN"))) {
                label = formatT(_T("%s"), text);

            } else if (equals2T(fmt, _T("AR"))) {
                label = formatT(_T("%s"), text);
            }
#else                                                       /* (one language) */
            /* two languages */
            if (equals2T(fmt, _T("TITLE"))) {
                label = formatT(_T("%s &nbsp; %s"), tran, text);

            } else if (equals2T(fmt, _T("TH"))) {
                label = formatT(_T("<b>%s</b><br/>%s"), tran, text);

            } else if (equals2T(fmt, _T("BR"))) {
                label = formatT(_T("<b>%s</b><br/>%s"), tran, text);

            } else if (equals2T(fmt, _T("B"))) {
                label = formatT(
                            _T("<b>%s</b> &nbsp; %s"), tran, text);
            } else if (equals2T(fmt, _T("EN"))) {
                label = formatT(_T("%s"), text);

            } else if (equals2T(fmt, _T("AR"))) {
                label = formatT(_T("%s"), tran);
            }
#endif                                                       /* two languages */
        }

        if (label == NULL) {
#if 1
            /* one language */
            label = formatT(_T("%s"), tran, text);
#else                                                       /* (one language) */
            /* two languages */
            label = formatT(_T("%s &nbsp; %s"), tran, text);
#endif                                                       /* two languages */
        }

        addTS(output_, label);

        freeT(&text);
        freeT(&tran);
        freeT(&fmt);
        freeT(&label);
    }

    Xmlr_skipElement(xml_);

    RETURN(NIL);
} /* _process_tag_label */


static void  _process_tag_org_name(                                        /*F*/
    Xmlr     xml_,                                                         /*-*/
    str_t*   output_,                                                      /*-*/
    chars_t  csv_settings_ ) {                                             /*-*/
    GO                                                            (UID(FC6A86));
    /* input: <lx.org_name format="format" /> */

    /* TODO: IMPLEMENT ATTRIBUTE "format" */

    new_chars_t  text = csv_key_value(csv_settings_, _T("lx.org_name"));
    addTS(output_, text);
    freeT(&text);

    Xmlr_skipElement(xml_);

    RETURN(NIL);
} /* _process_tag_org_name */


static void  _process_tag_site(                                            /*F*/
    Xmlr     xml_,                                                         /*-*/
    str_t*   output_,                                                      /*-*/
    chars_t  csv_settings_ ) {                                             /*-*/
    GO                                                            (UID(FA6119));
    /* input: <lx.site /> */

    new_chars_t  text = csv_key_value(csv_settings_, _T("lx.site"));
    addTS(output_, text);
    freeT(&text);

    Xmlr_skipElement(xml_);

    RETURN(NIL);
} /* _process_tag_site */


static void  _process_tag_style(                                           /*F*/
    Xmlr    xml_,                                                          /*-*/
    str_t*  output_ ) {                                                    /*-*/
    GO                                                            (UID(F80CDD));
    /* input: <lx.style href="link" />   or   <lx.style> </lx.style> */

    new_chars_t  style = NULL;

    if (Xmlr_isEmptyTag(xml_, NULL)) {
        chars_t  href = Xmlr_attr(xml_, _T("href"));
        style = formatT(_T("<link rel=\"stylesheet\"")
                        _T(" type=\"text/css\" href=\"%s\" />"),
                        href);
    } else {
        style = formatT(
                    _T("<style type=\"text/css\">%s</style>"),
                    Xmlr_content(xml_, false));
    }

    remove_extra_spaces_in_T(style);

    if (!IS_BLANK(style)) {
        addTS(output_, style);
    }

    freeT(&style);
    Xmlr_skipElement(xml_);
    RETURN(NIL);
} /* _process_tag_style */


/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */


PUBLIC new_chars_t  html_generate(                                         /*F*/
    chars_t  xml_layout_,                                                  /*-*/
    chars_t  xml_settings_,                                                /*-*/
    chars_t  csv_data_ ) {                                                 /*-*/
    GO                                                            (UID(F982E9));
    new_Xmlr     xml        = Xmlr_of_chars(xml_layout_);
    new_str_t    str        = { NULL };
    new_chars_t  ret        = NULL;
    array_t      macros     = Array_init(sizeof(_macro_t), 10, 0);
    new_str_t*   str_output = &str;

    /* load settings as a CSV string */
    new_chars_t  csv_settings = NULL;
    {
        new_Xmlr  settings = Xmlr_of_chars(xml_settings_);
        csv_settings = Xmlr_keyValuesToCsv(
                           settings,
                           _T("lx.settings"),
                           _T("lx.setting"),
                           _T("name"),
                           _T("value"));
        freeXmlr(&settings);
    }

    UNUSED(csv_data_);  /* TODO */

    Xmlr_removeComments(xml);

#if 000
    DUMP_OPEN;
    DUMP(_T("%s"), Xmlr_debugInfo(xml));
    DUMP(_T("\r\n\r\nPARSED:\r\n%s"), ret);
    DUMP_CLOSE;
#endif                                                                 /* 000 */

    if (!IS_BLANK(Xmlr_doctypeTag(xml))) {
        addTS(str_output, Xmlr_doctypeTag(xml));
        addTS(str_output, _T("\r\n"));
    }

    Xmlr_goRoot(xml);

    while (!Xmlr_eof(xml)) {
        _macro_t*  macro = NULL;

        if (Xmlr_isText(xml)) {
            chars_t  text = Xmlr_tagText(xml);
            addTS(str_output, text);
            Xmlr_skipTag(xml);
        } else if (Xmlr_isTagName(xml, _T("lx.macro.def"))) {
            if (Xmlr_isStartTag(xml, NULL)) {
                macro      = _process_tag_macro_def(xml, macros);
                str_output = &macro->text;
            } else if (Xmlr_isEndTag(xml, NULL)) {
                Xmlr_skipTag(xml);
                str_output = &str;
                macro      = NULL;
            } else {
                WARN(_T("lx.macro.def can't be empty."), UID(E735CB));
            }
        } else if (Xmlr_isTagName(xml, _T("lx.macro"))) {
            _process_tag_macro(xml, str_output, macros);

        } else if (Xmlr_isTagName(xml, _T("lx.style"))) {
            _process_tag_style(xml, str_output);

        } else if (Xmlr_isTagName(xml, _T("lx.org_name"))) {
            _process_tag_org_name(xml, str_output, csv_settings);

        } else if (Xmlr_isTagName(xml, _T("lx.site"))) {
            _process_tag_site(xml, str_output, csv_settings);

        } else if (Xmlr_isTagName(xml, _T("lx.label"))) {
            _process_tag_label(xml, str_output);

        } else if (Xmlr_isTagName(xml, _T("lx.ie6"))) {
            _process_tag_ie6(xml, str_output);

        } else if (Xmlr_isTagName(xml, _T("lx.html"))) {
            _process_tag_html(xml, str_output);

        } else if (Xmlr_isComment(xml)) {
            /* skip comments */

        } else if (Xmlr_isTagName(xml, NULL)) {
            chars_t  text = Xmlr_tagText(xml);
            addTS(str_output, text);
            Xmlr_skipTag(xml);
        }
    }

    ret = T_chars(str.cs);
    remove_extra_spaces_in_T(ret);

    freeT(&csv_settings);
    freeS(&str);
    freeXmlr(&xml);

    {
        /* free-up macros array: */
        size_t        i     = 0;
        const size_t  count = Array_count(macros);
        _macro_t*     macro = NULL;

        for (i = 0; i < count; i++) {
            macro = CAST(_macro_t*, Array_getItemAt(&macros, i));

            if (macro->csv_find != NULL) {
                freeT(&macro->csv_find);
            }
            freeS(&macro->text);
        }
        Array_removeItems(&macros);
        Array_free(&macros);
    }
    RETURN(ret);
} /* html_generate */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
