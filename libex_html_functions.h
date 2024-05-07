/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                              [libex_html_functions.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_HTML_FUNCTIONS_H
#define      INCLUDED_LIBEX_HTML_FUNCTIONS_H

#include "libex.h"

#if defined _MSC_VER
#pragma once
#endif

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

/* -------------------------------------------------------------------------- */
/* Functions: Public                                                          */

LX_PUBLIC lx_chars_t  lx_html_meta_content_type( void );                   /*F*/

/* -------------------------------------------------------------------------- */
/* Functions: Public, Allocating                                              */

LX_PUBLIC lx_new_chars_t  lx_html_button_back(                             /*F*/
    lx_chars_t  href_,                                                     /*-*/
    lx_chars_t  style_ );                                                  /*-*/

LX_PUBLIC lx_new_chars_t  lx_html_button_cancel_form_js( void );           /*F*/

LX_PUBLIC lx_new_chars_t  lx_html_button_home( void );                     /*F*/

LX_PUBLIC lx_new_chars_t  lx_html_button_print(                            /*F*/
    lx_chars_t  href_,                                                     /*-*/
    lx_chars_t  style_ );                                                  /*-*/

LX_PUBLIC lx_new_chars_t  lx_html_button_save_form_js( void );             /*F*/

LX_PUBLIC lx_new_chars_t  lx_html_field_checkbox(                          /*F*/
    lx_chars_t  row_or_value_,                                             /*-*/
    lx_chars_t  field_name_,                                               /*-*/
    lx_chars_t  label_,                                                    /*-*/
    lx_chars_t  style_opt_ );                                              /*-*/

LX_PUBLIC lx_new_chars_t  lx_html_field_date(                              /*F*/
    lx_chars_t  row_or_value_,                                             /*-*/
    lx_chars_t  field_name_,                                               /*-*/
    lx_chars_t  label_,                                                    /*-*/
    lx_chars_t  style_opt_ );                                              /*-*/

LX_PUBLIC lx_new_chars_t  lx_html_field_date_time(                         /*F*/
    lx_chars_t  row_or_value_,                                             /*-*/
    lx_chars_t  field_name_,                                               /*-*/
    lx_chars_t  label_,                                                    /*-*/
    lx_chars_t  style_opt_ );                                              /*-*/

LX_PUBLIC lx_new_chars_t  lx_html_field_int(                               /*F*/
    lx_chars_t  row_or_value_,                                             /*-*/
    lx_chars_t  field_name_,                                               /*-*/
    lx_chars_t  label_,                                                    /*-*/
    lx_chars_t  style_opt_ );                                              /*-*/

LX_PUBLIC lx_new_chars_t  lx_html_field_money(                             /*F*/
    lx_chars_t  row_or_value_,                                             /*-*/
    lx_chars_t  field_name_,                                               /*-*/
    lx_chars_t  label_,                                                    /*-*/
    lx_chars_t  style_opt_ );                                              /*-*/

LX_PUBLIC lx_new_chars_t  lx_html_field_real(                              /*F*/
    lx_chars_t  row_or_value_,                                             /*-*/
    lx_chars_t  field_name_,                                               /*-*/
    lx_chars_t  label_,                                                    /*-*/
    lx_chars_t  style_opt_ );                                              /*-*/

LX_PUBLIC lx_new_chars_t  lx_html_field_select(                            /*F*/
    lx_chars_t  row_or_value_,                                             /*-*/
    lx_chars_t  field_name_,                                               /*-*/
    lx_chars_t  label_,                                                    /*-*/
    lx_chars_t  values_,                                                   /*-*/
    lx_chars_t  style_opt_,                                                /*-*/
    lx_chars_t  alt_name_opt_,                                             /*-*/
    lx_chars_t  tag_name_opt_ );                                           /*-*/

LX_PUBLIC lx_new_chars_t  lx_html_field_select_uae(                        /*F*/
    lx_chars_t  row_or_value_,                                             /*-*/
    lx_chars_t  field_name_,                                               /*-*/
    lx_chars_t  style_opt_ );                                              /*-*/

LX_PUBLIC lx_new_chars_t  lx_html_field_text(                              /*F*/
    lx_chars_t  row_or_value_,                                             /*-*/
    lx_chars_t  field_name_,                                               /*-*/
    lx_chars_t  label_,                                                    /*-*/
    const int   max_len_,                                                  /*-*/
    lx_chars_t  style_opt_,                                                /*-*/
    lx_chars_t  on_change_code_opt_ );                                     /*-*/

LX_PUBLIC lx_new_chars_t  lx_html_field_text_list(                         /*F*/
    lx_chars_t  row_or_value_,                                             /*-*/
    lx_chars_t  field_name_,                                               /*-*/
    lx_chars_t  label_,                                                    /*-*/
    const int   max_len_,                                                  /*-*/
    lx_chars_t  style_opt_,                                                /*-*/
    lx_chars_t  on_change_code_opt_ );                                     /*-*/

LX_PUBLIC lx_new_chars_t  lx_html_header( lx_chars_t  content_ );          /*F*/

LX_PUBLIC lx_new_chars_t  lx_html_link(                                    /*F*/
    lx_chars_t  href_,                                                     /*-*/
    lx_chars_t  content_,                                                  /*-*/
    lx_chars_t  class_opt_,                                                /*-*/
    lx_chars_t  on_click_opt_ );                                           /*-*/

LX_PUBLIC lx_new_chars_t  lx_html_option(                                  /*F*/
    lx_chars_t  value_,                                                    /*-*/
    lx_chars_t  option_ );                                                 /*-*/

LX_PUBLIC lx_new_chars_t  lx_html_script(                                  /*F*/
    lx_chars_t  script_1_,                                                 /*-*/
    lx_chars_t  script_2_opt_,                                             /*-*/
    lx_chars_t  script_3_opt_,                                             /*-*/
    lx_chars_t  script_4_opt_,                                             /*-*/
    lx_chars_t  script_5_opt_ );                                           /*-*/

LX_PUBLIC lx_new_chars_t  lx_html_style(                                   /*F*/
    lx_chars_t  style_1_,                                                  /*-*/
    lx_chars_t  style_2_opt_,                                              /*-*/
    lx_chars_t  style_3_opt_,                                              /*-*/
    lx_chars_t  style_4_opt_,                                              /*-*/
    lx_chars_t  style_5_opt_ );                                            /*-*/

LX_PUBLIC lx_new_chars_t  lx_html_table_head( lx_chars_t  columns_ );      /*F*/

LX_PUBLIC lx_new_chars_t  lx_html_table_row(                               /*F*/
    lx_chars_t  column_1_,                                                 /*-*/
    lx_chars_t  column_2_opt_,                                             /*-*/
    lx_chars_t  column_3_opt_,                                             /*-*/
    lx_chars_t  column_4_opt_,                                             /*-*/
    lx_chars_t  column_5_opt_,                                             /*-*/
    lx_chars_t  column_6_opt_,                                             /*-*/
    lx_chars_t  column_7_opt_,                                             /*-*/
    lx_chars_t  column_8_opt_,                                             /*-*/
    lx_chars_t  column_9_opt_,                                             /*-*/
    lx_chars_t  column_10_opt_,                                            /*-*/
    lx_chars_t  column_11_opt_,                                            /*-*/
    lx_chars_t  column_12_opt_,                                            /*-*/
    lx_chars_t  column_13_opt_,                                            /*-*/
    lx_chars_t  column_14_opt_,                                            /*-*/
    lx_chars_t  column_15_opt_ );                                          /*-*/

LX_PUBLIC lx_new_chars_t  lx_html_title( lx_chars_t  title_ );             /*F*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
