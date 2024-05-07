/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                              [libex_html_functions.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_html_functions_.h"
#if defined INCLUDED_LIBEX_HTML_FUNCTIONS_H

#include "libex_.h"
#include "libex_call_.h"
#include "libex_const_.h"
#include "libex_stringc_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif

/* TODO: implement App_label() properly */
PUBLIC new_chars_t  App_label( chars_t  text_ );                           /*F*/

PUBLIC new_chars_t  App_label( chars_t  text_ ) {                          /*F*/
    GO                                                            (UID(FC6118));
    new_chars_t  ret = T_chars(text_);
    RETURN(ret);
} /* App_label */


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


static new_chars_t  _get_val(                                              /*F*/
    chars_t  row_or_value_,                                                /*-*/
    chars_t  field_name_ ) {                                               /*-*/
    GO                                                            (UID(FB5006));
    new_chars_t  ret = NULL;

    if (IS_BLANK(row_or_value_)) {
        ret = NULL;

    } else if (contains2T(row_or_value_, _T("\r\n"))) {
        UNUSED(field_name_);
        /* RETURN(trim(row_or_value_[$field_name_])); */
        trim_in_T(ret);
    } else {
        ret = T_chars(row_or_value_);
        trim_in_T(ret);
    }
    RETURN(ret);
} /* _get_val */


static new_chars_t  _style( chars_t  style_ ) {                            /*F*/
    GO                                                            (UID(FF8217));
    new_chars_t  ret = NULL;

    if (!IS_BLANK(style_)) {
        new_chars_t  style    = T_chars(style_);
        chars_t      position = NULL;

        while (contains2T(style, _T("  "))) {
            /* TODO: replace_in_T(&style, _T("  "), _T(" ")); */
            new_chars_t  repl = T_replace(style, _T("  "), _T(" "),
                                          IGNORE_CASE);
            freeT(&style);
            style = repl;
        }

        if (!contains3T(style, _T("top:"),   IGNORE_CASE) &&
            !contains3T(style, _T("left:"),  IGNORE_CASE) &&
            !contains3T(style, _T("right:"), IGNORE_CASE)) {
            position = BLANK;

        } else if (contains3T(style, _T("position:"), IGNORE_CASE)) {
            position = _T("position:absolute;");
        }

        ret = formatT(_T(" style=\"%s%s\""), position, style);
        freeT(&style);
    }
    RETURN(ret);
} /* _style */


/* -------------------------------------------------------------------------- */
/* Functions: Public                                                          */


PUBLIC chars_t  html_meta_content_type( void ) {                           /*F*/
    GO                                                            (UID(F97F9A));
    chars_t  ret = _T("<meta http-equiv=\"Content-Type\"")
                   _T(" Content=\"text/html; charset=UTF-8\">");
    RETURN(ret);
} /* html_meta_content_type */


/* -------------------------------------------------------------------------- */
/* Functions: Public, Allocating                                              */


PUBLIC new_chars_t  html_button_back(                                      /*F*/
    chars_t  href_,                                                        /*-*/
    chars_t  style_ ) {                                                    /*-*/
    GO                                                            (UID(FEA919));
    new_chars_t  ret      = NULL;
    new_chars_t  style    = NULL;
    new_chars_t  substyle = T_chars(style_);

    trim_in_T(substyle);

    style = formatT(_T("display:block; position:absolute;")
                    _T(" z-order:100; width:50px; height:50px;")
                    _T(" %s"), substyle);

    /* Various button icons are located in C:\user\Graphic\Icons\set - Blue */
    ret = formatT(_T("<div class=\"clsButtonBack\"")
                  _T(" style=\"%s\"><a href=\"%s\">")  /*1*/
                  _T("<img src=\"assets/images/buttonBack.png\"")
                  _T(" width=\"100%\" height=\"100%\" border=\"0\" />")
                  _T("</a></div>"),
                  style, href_);  /*1*/

    freeT(&style);
    freeT(&substyle);

    RETURN(ret);
} /* html_button_back */


PUBLIC new_chars_t  html_button_cancel_form_js( void ) {                   /*F*/
    GO                                                            (UID(FEBFD4));
    new_chars_t  label = App_label(_T("Cancel{}"));
    new_chars_t  ret   = formatT(
                             _T("%s%s%s"),
                             _T("<input id=\"idButtonCancelForm\"")
                             _T(" type=\"button\" value=\""),
                             label,
                             _T("\" onclick=\"buttonCancelForm_()\" />"));
    freeT(&label);
    RETURN(ret);
} /* html_button_cancel_form_js */


PUBLIC new_chars_t  html_button_home( void ) {                             /*F*/
    GO                                                            (UID(FB9201));
    chars_t  style = _T("display:block; position:absolute;")
                     _T(" z-order:100;")
                     _T(" top:5px; right:10px; width:50px; height:50px;");

    /* Various button icons are located in C:\user\Graphic\Icons\set - Blue */
    new_chars_t  ret = formatT(
                           _T("<div class=\"clsButtonHome\" style=\"%s\">")
                           _T("<a href=\"index.php\">")
                           _T("<img src=\"assets/images/buttonHome.png\"")
                           _T(" width=\"100%\" height=\"100%\"")
                           _T(" border=\"0\" />")
                           _T("</a></div>"), style);
    RETURN(ret);
} /* html_button_home */


PUBLIC new_chars_t  html_button_print(                                     /*F*/
    chars_t  href_,                                                        /*-*/
    chars_t  style_ ) {                                                    /*-*/
    GO                                                            (UID(F28710));
    new_chars_t  style    = NULL;
    new_chars_t  substyle = T_chars(style_);
    new_chars_t  ret      = NULL;

    trim_in_T(substyle);

    style = formatT(
                _T("display:block; position:absolute;")
                _T(" z-order:100; width:50px; height:50px;")
                _T(" %s"), substyle);

    /* Various button icons are located in C:\user\Graphic\Icons\set - Blue */
    ret = formatT(
              _T("<div class=\"clsButtonPrint\"")
              _T(" style=\"%s\"><a href=\"%s\">")  /*1*/
              _T("<img src=\"assets/images/buttonPrint.png\"")
              _T(" width=\"100%\" height=\"100%\" border=\"0\" />")
              _T("</a></div>"),
              style, href_);  /*1*/

    freeT(&style);
    freeT(&substyle);
    RETURN(ret);
} /* html_button_print */


PUBLIC new_chars_t  html_button_save_form_js( void ) {                     /*F*/
    GO                                                            (UID(F28203));
    new_chars_t  label = App_label(_T("Save{}"));
    new_chars_t  ret   = formatT(
                             _T("%s%s%s"),
                             _T("<input id=\"idButtonSaveForm\"")
                             _T(" type=\"button\" value=\""),
                             label,
                             _T("\" onclick=\"buttonSaveForm_()\" />"));
    freeT(&label);
    RETURN(ret);
} /* html_button_save_form_js */


PUBLIC new_chars_t  html_field_checkbox(                                   /*F*/
    chars_t  row_or_value_,                                                /*-*/
    chars_t  field_name_,                                                  /*-*/
    chars_t  label_,                                                       /*-*/
    chars_t  style_opt_ ) {                                                /*-*/
    GO                                                            (UID(FE1795));
    new_chars_t  row_or_val = _get_val(row_or_value_, field_name_);
    new_chars_t  label      = App_label(label_);
    new_chars_t  style      = _style(style_opt_);

    new_chars_t  ret =
        formatT(
            _T("<div class=\"clsAllCheckDiv\"%s>")                  /*1*/
            _T("<input class=\"clsAllCheckInput\" id=\"id@%s\"")    /*2*/
            _T(" name=\"id@%s\" type=\"checkbox\" %s />")           /*3*/
            _T("<label class=\"clsAllCheckLabel\" for=\"id@%s\">")  /*4*/
            _T("&nbsp&nbsp&nbsp&nbsp; %s")                          /*5*/
            _T("</label>")
            _T("</div>"),
            style,                    /*1*/
            field_name_,              /*2*/
            field_name_, row_or_val,  /*3*/
            field_name_,              /*4*/
            label);                   /*5*/

    freeT(&row_or_val);
    freeT(&label);
    freeT(&style);
    RETURN(ret);
} /* html_field_checkbox */


PUBLIC new_chars_t  html_field_date(                                       /*F*/
    chars_t  row_or_value_,                                                /*-*/
    chars_t  field_name_,                                                  /*-*/
    chars_t  label_,                                                       /*-*/
    chars_t  style_opt_ ) {                                                /*-*/
    GO                                                            (UID(F73273));
    new_chars_t  row_or_val = _get_val(row_or_value_, field_name_);
    new_chars_t  label      = App_label(label_);
    new_chars_t  style      = _style(style_opt_);
    new_chars_t  date       = NULL;

    /* intval($vRowOrValue_) == 0 */
    /*      ? today_dmy_() : read_date_($vRowOrValue_); */

    new_chars_t  ret = formatT(
                           _T("<div id=\"idDiv%s\"%s dir=\"ltr\">")  /*1*/
                           _T("<label class=\"clsAllFieldLabel\"")
                           _T(" for=\"id@%s\">%s</label>")           /*2*/
                           _T("<input id=\"id@%s\" name=\"id@%s\"")  /*3*/
                           _T(" type=\"text\" maxlength=\"20\"")
                           _T(" value=\"%s\"")                       /*4*/
                           _T(" onchange=\"fieldChanged_(")
                           _T("'id@%s', 'date')\" />")               /*5*/
                           _T("</div>"),
                           field_name_, style,        /*1*/
                           field_name_, label,        /*2*/
                           field_name_, field_name_,  /*3*/
                           date,                      /*4*/
                           field_name_);              /*5*/

    freeT(&row_or_val);
    freeT(&label);
    freeT(&style);
    freeT(&date);
    RETURN(ret);
} /* html_field_date */


PUBLIC new_chars_t  html_field_date_time(                                  /*F*/
    chars_t  row_or_value_,                                                /*-*/
    chars_t  field_name_,                                                  /*-*/
    chars_t  label_,                                                       /*-*/
    chars_t  style_opt_ ) {                                                /*-*/
    GO                                                            (UID(FF6072));
    new_chars_t  row_or_val = _get_val(row_or_value_, field_name_);
    new_chars_t  label      = App_label(label_);
    new_chars_t  style      = _style(style_opt_);
    new_chars_t  date_time  = NULL;
    /*intval($vRowOrVal_) == 0 ? today_dmy_() : read_date_time_($vRowOrVal_);*/

    new_chars_t  ret =
        formatT(_T("<div id=\"idDiv%s\"%s dir=\"ltr\">")                   /*1*/
                _T("<label class=\"clsAllFieldLabel\"")
                _T(" for=\"id@%s\">%s</label>")                            /*2*/
                _T("<input id=\"id@%s\" name=\"id@%s\"")                   /*3*/
                _T(" type=\"text\" maxlength=\"20\" value=\"%s\"")         /*4*/
                _T(" onchange=\"fieldChanged_('id@%s', 'datetime')\" />")  /*5*/
                _T("</div>"),
                field_name_, style,        /*1*/
                field_name_, label,        /*2*/
                field_name_, field_name_,  /*3*/
                date_time,                 /*4*/
                field_name_);              /*5*/

    freeT(&row_or_val);
    freeT(&label);
    freeT(&style);
    freeT(&date_time);
    RETURN(ret);
} /* html_field_date_time */


PUBLIC new_chars_t  html_field_int(                                        /*F*/
    chars_t  row_or_value_,                                                /*-*/
    chars_t  field_name_,                                                  /*-*/
    chars_t  label_,                                                       /*-*/
    chars_t  style_opt_ ) {                                                /*-*/
    GO                                                            (UID(F402E9));
    new_chars_t  row_or_val = _get_val(row_or_value_, field_name_);
    new_chars_t  label      = App_label(label_);
    new_chars_t  style      = _style(style_opt_);
    new_chars_t  int_tstr   = NULL;  /* read_int_($vRowOrValue_); */

    new_chars_t  ret =
        formatT(
            _T("<div id=\"idDiv%s\"%s>")                          /*1*/
            _T("<label class=\"clsAllFieldLabel\"")
            _T(" for=\"id@%s\">%s</label>")                       /*2*/
            _T("<input id=\"id@%s\" name=\"id@%s\"")              /*3*/
            _T(" type=\"text\" maxlength=\"15\" value=\"%s\"")    /*4*/
            _T(" onchange=\"fieldChanged_('id@%s', 'int')\" />")  /*5*/
            _T("</div>"),
            field_name_, style,        /*1*/
            field_name_, label,        /*2*/
            field_name_, field_name_,  /*3*/
            int_tstr,                  /*4*/
            field_name_);              /*5*/

    freeT(&row_or_val);
    freeT(&label);
    freeT(&style);
    freeT(&int_tstr);
    RETURN(ret);
} /* html_field_int */


PUBLIC new_chars_t  html_field_money(                                      /*F*/
    chars_t  row_or_value_,                                                /*-*/
    chars_t  field_name_,                                                  /*-*/
    chars_t  label_,                                                       /*-*/
    chars_t  style_opt_ ) {                                                /*-*/
    GO                                                            (UID(F5F5A7));
    new_chars_t  row_or_val = _get_val(row_or_value_, field_name_);
    new_chars_t  label      = App_label(label_);
    new_chars_t  style      = _style(style_opt_);
    new_chars_t  money      = NULL;
    /* read_money_(floatval($vRowOrValue_)); */

    new_chars_t  ret =
        formatT(
            _T("<div id=\"idDiv%s\"%s>")                            /*1*/
            _T("<label class=\"clsAllFieldLabel\"")
            _T(" for=\"id@%s\">%s</label>")                         /*2*/
            _T("<input id=\"id@%s\" name=\"id@%s\"")                /*3*/
            _T(" type=\"text\" maxlength=\"15\" value=\"%s\"")      /*4*/
            _T(" onchange=\"fieldChanged_('id@%s', 'money')\" />")  /*5*/
            _T("</div>"),
            field_name_, style,        /*1*/
            field_name_, label,        /*2*/
            field_name_, field_name_,  /*3*/
            money,                     /*4*/
            field_name_);              /*5*/

    freeT(&row_or_val);
    freeT(&label);
    freeT(&style);
    freeT(&money);
    RETURN(ret);
} /* html_field_money */


PUBLIC new_chars_t  html_field_real(                                       /*F*/
    chars_t  row_or_value_,                                                /*-*/
    chars_t  field_name_,                                                  /*-*/
    chars_t  label_,                                                       /*-*/
    chars_t  style_opt_ ) {                                                /*-*/
    GO                                                            (UID(F15476));
    new_chars_t  row_or_val = _get_val(row_or_value_, field_name_);
    new_chars_t  label      = App_label(label_);
    new_chars_t  style      = _style(style_opt_);
    new_chars_t  real       = NULL;  /* read_real_($vRowOrValue_); */

    new_chars_t  ret =
        formatT(
            _T("<div id=\"idDiv%s\"%s>")                           /*1*/
            _T("<label class=\"clsAllFieldLabel\"")
            _T(" for=\"id@%s\">%s</label>")                        /*2*/
            _T("<input id=\"id@%s\" name=\"id@%s\"")               /*3*/
            _T(" type=\"text\" maxlength=\"15\" value=\"%s\" />")  /*4*/
            _T("</div>"),
            field_name_, style,        /*1*/
            field_name_, label,        /*2*/
            field_name_, field_name_,  /*3*/
            real);                     /*4*/

    freeT(&row_or_val);
    freeT(&label);
    freeT(&style);
    freeT(&real);
    RETURN(ret);
} /* html_field_real */


PUBLIC new_chars_t  html_field_select(                                     /*F*/
    chars_t  row_or_value_,                                                /*-*/
    chars_t  field_name_,                                                  /*-*/
    chars_t  label_,                                                       /*-*/
    chars_t  values_,                                                      /*-*/
    chars_t  style_opt_,                                                   /*-*/
    chars_t  alt_name_opt_,                                                /*-*/
    chars_t  tag_name_opt_ ) {                                             /*-*/
    GO                                                            (UID(F9E702));
    chars_t  tag_name = IS_BLANK(tag_name_opt_) ? _T("div") : tag_name_opt_;

    new_chars_t  row_or_val = _get_val(row_or_value_, field_name_);
    new_chars_t  label      = App_label(label_);
    new_chars_t  style      = _style(style_opt_);
    new_chars_t  name       = IS_BLANK(alt_name_opt_)
                              ? formatT(_T("id@%s"), field_name_)
                              : T_chars(alt_name_opt_);

    new_chars_t  ret = formatT(
                           _T("<%s id=\"idDiv%s\"%s>")               /*1*/
                           _T("<label class=\"clsAllFieldLabel\"")
                           _T(" for=\"id@%s\">%s</label>")           /*2*/
                           _T("<select id=\"id@%s\" name=\"%s\">"),  /*3*/
                           tag_name, field_name_, style,  /*1*/
                           field_name_, label,            /*2*/
                           field_name_, name);            /*3*/

    {
        uint32_t        i     = 0;
        const uint32_t  count = token_countT(values_, _T(","));

        for (i = 0; i <= count; i++) {
            new_chars_t  opt  = NULL;
            new_chars_t  html = NULL;
            new_chars_t  val  = T_get_token(values_, i, _T(","));

            trim_in_T(val);
            appendT(&val, _T("{}"));
            opt  = App_label(val);
            html = html_option(row_or_val, opt);

            appendT(&ret, html);

            freeT(&val);
            freeT(&opt);
            freeT(&html);
        }
    }

    append3T(&ret, _T("</select></"), tag_name, _T(">"));

    freeT(&row_or_val);
    freeT(&label);
    freeT(&style);
    freeT(&name);
    RETURN(ret);
} /* html_field_select */


PUBLIC new_chars_t  html_field_select_uae(                                 /*F*/
    chars_t  row_or_value_,                                                /*-*/
    chars_t  field_name_,                                                  /*-*/
    chars_t  style_opt_ ) {                                                /*-*/
    GO                                                            (UID(F36C90));
    new_chars_t  ret = html_field_select(
                           row_or_value_,          /* row_or_value_ */
                           field_name_,            /* field_name_   */
                           _T("Location"),         /* label_        */

                           style_opt_,             /* style_opt_    */
                           NULL,                   /* alt_name_opt_ */
                           NULL);                  /* tag_name_opt_ */

    RETURN(ret);
} /* html_field_select_uae */


PUBLIC new_chars_t  html_field_text(                                       /*F*/
    chars_t    row_or_value_,                                              /*-*/
    chars_t    field_name_,                                                /*-*/
    chars_t    label_,                                                     /*-*/
    const int  max_len_,                                                   /*-*/
    chars_t    style_opt_,                                                 /*-*/
    chars_t    on_change_code_opt_ ) {                                     /*-*/
    GO                                                            (UID(FBAF46));
    new_chars_t  ret            = NULL;
    new_chars_t  row_or_val     = _get_val(row_or_value_, field_name_);
    new_chars_t  label          = App_label(label_);
    new_chars_t  style          = _style(style_opt_);
    new_chars_t  text           = NULL;  /* read_text_($vRowOrValue_); */
    new_chars_t  on_change_code = NULL;

    if (IS_BLANK(on_change_code_opt_)) {
        on_change_code = formatT(
                             _T(" onchange=\"fieldChanged_(")
                             _T("'id@%s', 'text')\""), field_name_);
    } else {
        on_change_code = formatT(_T(" onchange=\"%s\""), on_change_code);
    }

    ret = formatT(
              _T("<div id=\"idDiv%s\"%s>")              /*1*/
              _T("<label class=\"clsAllFieldLabel\"")
              _T(" for=\"id@%s\">%s</label>")           /*2*/
              _T("<input id=\"id@%s\" name=\"id@%s\"")  /*3*/
              _T(" type=\"text\" maxlength=\"%d\"")     /*4*/
              _T(" value=\"%s\"%s />")                  /*5*/
              _T("</div>"),
              field_name_, style,        /*1*/
              field_name_, label,        /*2*/
              field_name_, field_name_,  /*3*/
              max_len_,                  /*4*/
              text, on_change_code);     /*5*/

    freeT(&row_or_val);
    freeT(&label);
    freeT(&style);
    freeT(&text);
    freeT(&on_change_code);

    RETURN(ret);
} /* html_field_text */


PUBLIC new_chars_t  html_field_text_list(                                  /*F*/
    chars_t    row_or_value_,                                              /*-*/
    chars_t    field_name_,                                                /*-*/
    chars_t    label_,                                                     /*-*/
    const int  max_len_,                                                   /*-*/
    chars_t    style_opt_,                                                 /*-*/
    chars_t    on_change_code_opt_ ) {                                     /*-*/
    GO                                                            (UID(FFB600));
    new_chars_t  ret            = NULL;
    new_chars_t  row_or_val     = _get_val(row_or_value_, field_name_);
    new_chars_t  label          = App_label(label_);
    new_chars_t  style          = _style(style_opt_);
    new_chars_t  text           = NULL;  /* read_text_($vRowOrValue_); */
    new_chars_t  on_change_code = NULL;

    if (IS_BLANK(on_change_code_opt_)) {
        on_change_code = formatT(
                             _T(" onchange=\"fieldChanged_(")
                             _T("'id@%s', 'text')\""), field_name_);
    } else {
        on_change_code = formatT(
                             _T(" onchange=\"%s\""), on_change_code);
    }

    ret = formatT(
              _T("<div id=\"idDiv%s\"%s>")                        /*1*/
              _T("<label class=\"clsAllFieldLabel\"")
              _T(" for=\"id@%s\">%s</label>")                     /*2*/
              _T("<span style=\"background-color:yellow;\">")
              _T("<input id=\"id@%s\" name=\"id@%s\"")            /*3*/
              _T(" type=\"text\" maxlength=\"%d\"")               /*4*/
              _T(" value=\"%s\"%s")                               /*5*/
              _T(" style=\"position:relative; width:8em; \" />")
              _T("<img id=\"idImgDownArrow\"")
              _T(" src=\"assets/images/downArrow.png\"")
              _T(" style=\"position:relative\" />")
              _T("</span>")
              _T("</div>"),
              field_name_, style,        /*1*/
              field_name_, label,        /*2*/
              field_name_, field_name_,  /*3*/
              max_len_,                  /*4*/
              text, on_change_code       /*5*/
          );

    freeT(&row_or_val);
    freeT(&label);
    freeT(&style);
    freeT(&text);
    freeT(&on_change_code);

    RETURN(ret);
} /* html_field_text_list */


PUBLIC new_chars_t  html_header( chars_t  content_ ) {                     /*F*/
    GO                                                            (UID(F36690));
    chars_t      meta = html_meta_content_type();
    new_chars_t  ret  =
        formatT(
            _T("<!DOCTYPE html PUBLIC ")
            _T("\"-//w3c//dtd xhtml 1.0 transitional//en\" ")
            _T("\"http://www.w3.org/tr/xhtml1/dtd/xhtml1-transitional.dtd\">")
            _T("<html xmlns=\"http://www.w3.org/1999/xhtml\" dir=\"rtl\">")
            _T("<head>%s%s</head>"), meta, content_);
    RETURN(ret);
} /* html_header */


PUBLIC new_chars_t  html_link(                                             /*F*/
    chars_t  href_,                                                        /*-*/
    chars_t  content_,                                                     /*-*/
    chars_t  class_opt_,                                                   /*-*/
    chars_t  on_click_opt_ ) {                                             /*-*/
    GO                                                            (UID(F68953));
    new_chars_t  ret      = NULL;
    new_chars_t  href     = T_chars(href_);
    new_chars_t  content  = App_label(content_);
    new_chars_t  cls      = T_chars(class_opt_);
    new_chars_t  on_click = T_chars(on_click_opt_);

    trim_in_T(href);
    trim_in_T(on_click);

    if (!IS_BLANK(href)) {
        new_chars_t  str = formatT(_T(" href=\"%s\""), href);
        freeT(&href);
        href = str;
    }

    if (!IS_BLANK(cls)) {
        new_chars_t  str = formatT(_T(" class=\"%s\""), cls);
        freeT(&cls);
        cls = str;
    }

    if (!IS_BLANK(on_click)) {
        new_chars_t  str = NULL;

        if (beginsT(on_click, _T("onclick"))) {
            str = T_join(TT, _T(" "), on_click_opt_, TT);
        } else {
            str = formatT(_T(" onclick=\"%s\""), on_click);
        }

        freeT(&on_click);
        on_click = str;
    }

    ret = formatT(_T("<a%s%s%s>%s</a>"), href, cls, on_click, content);

    freeT(&href);
    freeT(&content);
    freeT(&cls);
    freeT(&on_click);

    RETURN(ret);
} /* html_link */


PUBLIC new_chars_t  html_option(                                           /*F*/
    chars_t  value_,                                                       /*-*/
    chars_t  option_ ) {                                                   /*-*/
    GO                                                            (UID(F793F0));
    chars_t  selected = equals_icT(option_, value_)
                        ? _T(" selected=\"selected\"") : BLANK;

#if 000
    html_entity_decode(strval(option_), ENT_QUOTES, "UTF-8")
    ==
    html_entity_decode(strval(value_), ENT_QUOTES, "UTF-8"))
#endif

    new_chars_t  label = App_label(option_);
    new_chars_t  ret   = formatT(_T("<option value=\"%s\"%s>%s</option>"),
                                 label, selected, label);
    freeT(&label);
    RETURN(ret);
} /* html_option */


PUBLIC new_chars_t  html_script(                                           /*F*/
    chars_t  script_1_,                                                    /*-*/
    chars_t  script_2_opt_,                                                /*-*/
    chars_t  script_3_opt_,                                                /*-*/
    chars_t  script_4_opt_,                                                /*-*/
    chars_t  script_5_opt_ ) {                                             /*-*/
    GO                                                            (UID(F0AAFB));
    new_chars_t  ret = NULL;
    size_t       i   = 0;

    chars_t  script[5] = { NULL, NULL, NULL, NULL, NULL };
    script[0] = script_1_;
    script[1] = script_2_opt_;
    script[2] = script_3_opt_;
    script[3] = script_4_opt_;
    script[4] = script_5_opt_;

    for (i = 0; i < 5; i++) {
        if (!IS_BLANK(script[i])) {
            new_chars_t  str = formatT(_T("<script type=\"text/javascript\"")
                                       _T(" src=\"%s\"></script>"), script[i]);
            appendT(&ret, str);
            freeT(&str);
        }
    }
    RETURN(ret);
} /* html_script */


PUBLIC new_chars_t  html_style(                                            /*F*/
    chars_t  style_1_,                                                     /*-*/
    chars_t  style_2_opt_,                                                 /*-*/
    chars_t  style_3_opt_,                                                 /*-*/
    chars_t  style_4_opt_,                                                 /*-*/
    chars_t  style_5_opt_ ) {                                              /*-*/
    GO                                                            (UID(FBCD31));
    new_chars_t  ret      = NULL;
    size_t       i        = 0;
    chars_t      style[5] = { NULL, NULL, NULL, NULL, NULL };

    style[0] = style_1_;
    style[1] = style_2_opt_;
    style[2] = style_3_opt_;
    style[3] = style_4_opt_;
    style[4] = style_5_opt_;

    for (i = 0; i < 5; i++) {
        chars_t  st = style[i];
        /* remove_extra_spaces_(style[i]); */

        if (!IS_BLANK(st)) {
            new_chars_t  html = NULL;
            if (contains3T(st, _T(".css"), IGNORE_CASE)) {
                html = formatT(_T("<link rel=\"stylesheet\"")
                               _T(" type=\"text/css\" href=\"%s\">"), st);
            } else {
                html = formatT(_T("<style type=\"text/css\">")
                               _T(" %s </style>"), st);
            }
            appendT(&ret, html);
            freeT(&html);
        }
    }
    RETURN(ret);
} /* html_style */


/* Label1{class:cls1},Label2{class:cls2},Label3{class:cls3}... */
PUBLIC new_chars_t  html_table_head( chars_t  columns_ ) {                 /*F*/
    GO                                                            (UID(FF2B0C));
    new_chars_t     ret   = T_chars(_T("<thead><tr>"));
    uint32_t        i     = 0;
    const uint32_t  count = token_countT(columns_, _T(","));

    for (i = 0; i <= count; i++) {
        new_chars_t  col = T_get_token(columns_, i, _T(","));

        if (!IS_BLANK(col)) {
            new_chars_t  cls = NULL;

            if (contains2T(col, _T("{"))) {
                cls = T_get_tag(col, _T("{class:"), _T("}"));

                if (IS_BLANK(cls)) {
                    new_chars_t  str =
                        T_remove_tag(col, _T("{class:"), _T("}"));
                    freeT(&col);
                    col = str;
                }
            }

            if (IS_BLANK(cls)) {
                freeT(&cls);
                cls = formatT(_T("cls%d"), i + 1);
            }

            {
                new_chars_t  col_th = T_join(TT, col, _T("{TH}"), TT);
                new_chars_t  label  = App_label(col_th);
                new_chars_t  html   = formatT(_T("<th class=\"%s\">%s</th>"),
                                              cls, label);
                appendT(&ret, html);
                freeT(&col_th);
                freeT(&label);
                freeT(&html);
            }
        }
        freeT(&col);
    }
    appendT(&ret, _T("</tr></thead>"));
    RETURN(ret);
} /* html_table_head */


PUBLIC new_chars_t  html_table_row(                                        /*F*/
    chars_t  column_1_,                                                    /*-*/
    chars_t  column_2_opt_,                                                /*-*/
    chars_t  column_3_opt_,                                                /*-*/
    chars_t  column_4_opt_,                                                /*-*/
    chars_t  column_5_opt_,                                                /*-*/
    chars_t  column_6_opt_,                                                /*-*/
    chars_t  column_7_opt_,                                                /*-*/
    chars_t  column_8_opt_,                                                /*-*/
    chars_t  column_9_opt_,                                                /*-*/
    chars_t  column_10_opt_,                                               /*-*/
    chars_t  column_11_opt_,                                               /*-*/
    chars_t  column_12_opt_,                                               /*-*/
    chars_t  column_13_opt_,                                               /*-*/
    chars_t  column_14_opt_,                                               /*-*/
    chars_t  column_15_opt_ ) {                                            /*-*/
    GO                                                            (UID(F1A22B));
    new_chars_t  ret      = T_chars(_T("<tr class=\"clsRow\">"));
    uint32_t     i        = 0;
    chars_t      cols[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    cols[0]  = column_1_;
    cols[1]  = column_2_opt_;
    cols[2]  = column_3_opt_;
    cols[3]  = column_4_opt_;
    cols[4]  = column_5_opt_;
    cols[5]  = column_6_opt_;
    cols[6]  = column_7_opt_;
    cols[7]  = column_8_opt_;
    cols[8]  = column_9_opt_;
    cols[9]  = column_10_opt_;
    cols[10] = column_11_opt_;
    cols[11] = column_12_opt_;
    cols[12] = column_13_opt_;
    cols[13] = column_14_opt_;
    cols[14] = column_15_opt_;

    for (i = 0; i <= 15; i++) {
        new_chars_t  col     = T_chars(cols[i]);
        new_chars_t  cls     = NULL;
        new_chars_t  style   = NULL;
        new_chars_t  colspan = NULL;

        if (IS_BLANK(col)) {
            freeT(&col);
            continue;
        }

        if (contains2T(col, _T("{"))) {
            cls = T_get_tag(col, _T("{class:"), _T("}"));

            if (!IS_BLANK(cls)) {
                new_chars_t  str = formatT(_T(" class=\"%s\""), cls);
                freeT(&cls);
                cls = str;

                str = T_remove_tag(col, _T("{class:"), _T("}"));
                freeT(&col);
                col = str;
            }

            style = T_get_tag(col, _T("{style:"), _T("}"));

            if (!IS_BLANK(style)) {
                new_chars_t  str = formatT(_T(" style=\"%s\""), style);
                freeT(&style);
                style = str;

                str = T_remove_tag(col, _T("{style:"), _T("}"));
                freeT(&col);
                col = str;
            }

            colspan = T_get_tag(col, _T("{colspan:"), _T("}"));

            if (!IS_BLANK(colspan)) {
                new_chars_t  str = formatT(_T(" colspan=\"%s\""), colspan);
                freeT(&colspan);
                colspan = str;

                str = T_remove_tag(col, _T("{colspan:"), _T("}"));
                freeT(&col);
                col = str;
            }

            freeT(&col);
            freeT(&cls);
            freeT(&style);
            freeT(&colspan);
        }

        {
            new_chars_t  html = formatT(_T("<td %s%s%s>%s</td>"),
                                        cls, style, colspan, col);
            appendT(&ret, html);
            freeT(&html);
        }
    }
    appendT(&ret, _T("</tr>"));
    RETURN(ret);
} /* html_table_row */


PUBLIC new_chars_t  html_title( chars_t  title_ ) {                        /*F*/
    GO                                                            (UID(F5C860));
    new_chars_t  label = App_label(title_);
    new_chars_t  ret   = formatT(_T("<title>%s</title>"), label);
    freeT(&label);
    RETURN(ret);
} /* html_title */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
