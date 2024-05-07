/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                          [libex_variant_functions_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_VARIANT_FUNCTIONS__H && LX_PLATFORM_WIN32
#define      INCLUDED_LIBEX_VARIANT_FUNCTIONS__H

#include "libex_variant_functions.h"

/* -------------------------------------------------------------------------- */
/* Functions: Conversion from Variant                                         */

#define bool_of_var                     lx_bool_of_var
#define byte_of_var                     lx_byte_of_var
#define currency_of_var                 lx_currency_of_var
#define date_of_var                     lx_date_of_var
#define double_of_var                   lx_double_of_var
#define float_of_var                    lx_float_of_var
#define long_of_var                     lx_long_of_var
#define S_of_var                        lx_S_of_var
#define short_of_var                    lx_short_of_var
#define T_of_var                        lx_T_of_var

/* -------------------------------------------------------------------------- */
/* Functions: Conversion to Variant                                           */

#define var_of_bool                     lx_var_of_bool
#define var_of_byte                     lx_var_of_byte
#define var_of_chars                    lx_var_of_chars
#define var_of_currency                 lx_var_of_currency
#define var_of_date                     lx_var_of_date
#define var_of_double                   lx_var_of_double
#define var_of_float                    lx_var_of_float
#define var_of_long                     lx_var_of_long
#define var_of_short                    lx_var_of_short

#endif                                                                   /*eof*/
/* TODO: arrange .h and .c file in same order `` */
