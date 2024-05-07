/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                   [libex_functions.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_FUNCTIONS_H
#define      INCLUDED_LIBEX_FUNCTIONS_H

#include "libex_string_class.h"

/*  HOW TO ADD LIBRARY FILES TO A PROJECT:                                    */
/*  => On 'Project' menu, select 'Settings'                                   */
/*  => set 'Settings For' to 'All Configurations'                             */
/*  => Switch to 'C/C++' tab on the dialog                                    */
/*  => set 'Category' to 'Preprocessor'                                       */
/*  => In 'Additional include directories:' enter '..\libex'                  */
/*  => add all requred library source files to the project                    */

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

/* -------------------------------------------------------------------------- */
/* Functions: Conversion                                                      */

/* Convert unsigned integer to text.                                          */
LX_PUBLIC lx_new_str_t  lx_tu(                                             /*F*/
    const unsigned long  value_,                                           /*-*/
    lx_chars_t           format_,                                          /*-*/
    lx_chars_t           delimiter_ );                                     /*-*/

/* Convert a size in bytes to a human-friendly                                */
/* string like: 10.7 MiB, 2 GB, etc.                                          */
LX_PUBLIC lx_new_str_t  lx_byte_size_description(                          /*F*/
    const size_t   size_in_bytes_,                                         /*-*/
    const lx_bool  use_1024_multiple_ );                                   /*-*/

/* -------------------------------------------------------------------------- */

LX_PUBLIC lx_bool  lx_equals_float(                                        /*F*/
    const float  value_1_,                                                 /*-*/
    const float  value_2_ );                                               /*-*/

LX_PUBLIC lx_bool  lx_equals_double(                                       /*F*/
    const double  value_1_,                                                /*-*/
    const double  value_2_ );                                              /*-*/

LX_PUBLIC lx_new_str_t  lx_sql_statement(                                  /*F*/
    lx_chars_t    sql_statements_,                                         /*-*/
    const size_t  index_1_ );                                              /*-*/

/* WARNING: These functions are not to be used. */

/* WARNING: Not to be used: for backward-compatibility only.                  */
LX_PUBLIC lx_new_str_t  lx_old_decrypt(                                    /*F*/
    lx_chars_t  text_,                                                     /*-*/
    lx_chars_t  key_ );                                                    /*-*/

/* WARNING: Not to be used: for backward-compatibility only.                  */
LX_PUBLIC lx_new_str_t  lx_old_encrypt(                                    /*F*/
    lx_chars_t     text_,                                                  /*-*/
    lx_chars_t     key_,                                                   /*-*/
    const lx_bool  decryption_ );                                          /*-*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
