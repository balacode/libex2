/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                      [libex_number.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_NUMBER_H
#define      INCLUDED_LIBEX_NUMBER_H

#include "libex_string_class.h"

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

#define LX_NUMBER_TESTS  1                /* 1: enable, 0: disable unit tests */

#if LX_NUMBER_TESTS > 0
LX_PUBLIC void  lx_test_num_add( void );                                   /*F*/
LX_PUBLIC void  lx_test_num_cmp( void );                                   /*F*/
LX_PUBLIC void  lx_test_num_div( void );                                   /*F*/
LX_PUBLIC void  lx_test_num_eval( void );                                  /*F*/
LX_PUBLIC void  lx_test_num_mul( void );                                   /*F*/
LX_PUBLIC void  lx_test_num_sub( void );                                   /*F*/
LX_PUBLIC void  lx_test_number( void );                                    /*F*/
#endif                                                 /* LX_NUMBER_TESTS > 0 */

/* -------------------------------------------------------------------------- */
/* Functions: Arithmetic Operations                                           */

LX_PUBLIC lx_new_str_t  lx_num_add(                                        /*F*/
    lx_chars_t  augend_,                                                   /*-*/
    lx_chars_t  addend_ );                                                 /*-*/

LX_PUBLIC lx_new_str_t  lx_num_div(                                        /*F*/
    lx_chars_t  dividend_,                                                 /*-*/
    lx_chars_t  divisor_,                                                  /*-*/
    const int   decimal_places_ );                                         /*-*/

LX_PUBLIC lx_new_str_t  lx_num_mul(                                        /*F*/
    lx_chars_t  multiplicand_,                                             /*-*/
    lx_chars_t  multiplier_ );                                             /*-*/

LX_PUBLIC lx_new_str_t  lx_num_sub(                                        /*F*/
    lx_chars_t  minuend_,                                                  /*-*/
    lx_chars_t  subtrahend_ );                                             /*-*/

/* -------------------------------------------------------------------------- */
/* Functions: Logic                                                           */

LX_PUBLIC int  lx_num_cmp(                                                 /*F*/
    lx_chars_t     number_1_,                                              /*-*/
    lx_chars_t     number_2_,                                              /*-*/
    const lx_bool  absolute_value_ );                                      /*-*/

#define lx_num_cmp2( NUMBER_1_, NUMBER_2_ )                 \
    lx_num_cmp(      NUMBER_1_, NUMBER_2_, LX_C_FALSE)  /*#*/

/* -------------------------------------------------------------------------- */
/* Functions: General Calculation Evaluation                                  */

LX_PUBLIC lx_new_str_t  lx_num_eval( lx_chars_t  expression_ );            /*F*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
