/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                              [libex_html_generator.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_HTML_GENERATOR_H
#define      INCLUDED_LIBEX_HTML_GENERATOR_H

#include "libex.h"

#if defined _MSC_VER
#pragma once
#endif

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

LX_PUBLIC lx_new_chars_t  lx_html_generate(                                /*F*/
    lx_chars_t  xml_layout_,                                               /*-*/
    lx_chars_t  xml_settings_,                                             /*-*/
    lx_chars_t  csv_data_ );                                               /*-*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
