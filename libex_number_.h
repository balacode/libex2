/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                     [libex_number_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_NUMBER__H
#define      INCLUDED_LIBEX_NUMBER__H
#include "libex_number.h"

/* -------------------------------------------------------------------------- */

#define NUMBER_TESTS                    LX_NUMBER_TESTS

#if LX_NUMBER_TESTS > 0
#define test_num_add                    lx_test_num_add
#define test_num_cmp                    lx_test_num_cmp
#define test_num_div                    lx_test_num_div
#define test_num_eval                   lx_test_num_eval
#define test_num_mul                    lx_test_num_mul
#define test_num_sub                    lx_test_num_sub
#define test_number                     lx_test_number
#endif

/* -------------------------------------------------------------------------- */
/* Functions: Arithmetic Operations                                           */

#define num_add                         lx_num_add
#define num_div                         lx_num_div
#define num_mul                         lx_num_mul
#define num_sub                         lx_num_sub

/* -------------------------------------------------------------------------- */
/* Functions: Logic                                                           */

#define num_cmp                         lx_num_cmp
#define num_cmp2                        lx_num_cmp2

/* -------------------------------------------------------------------------- */
/* Functions: General Calculation Evaluation                                  */

#define num_eval                        lx_num_eval

#endif                                                                   /*eof*/
