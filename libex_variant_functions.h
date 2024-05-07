/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                           [libex_variant_functions.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_VARIANT_FUNCTIONS_H && LX_PLATFORM_WIN32
#define      INCLUDED_LIBEX_VARIANT_FUNCTIONS_H

#if !defined __wtypes_h__
#include <wtypes.h>  /* Windows API */   /* for BSTR_win, etc. */
#endif
#if !defined VARIANT_win
#include <oaidl.h>  /* Windows API */
#endif

#include "libex.h"
#include "libex_string_class.h"

#if LX_PLATFORM_WIN32
#include "libex_win32.h"
#endif

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

/* -------------------------------------------------------------------------- */
/* Functions: Conversion from Variant                                         */

LX_PUBLIC lx_new_chars_t  lx_T_of_var( const VARIANT_win  value_ );        /*F*/

LX_PUBLIC lx_new_str_t  lx_S_of_var( const VARIANT_win  value_ );          /*F*/

LX_PUBLIC lx_bool  lx_bool_of_var( const VARIANT_win  value_ );            /*F*/

LX_PUBLIC uint8_t  lx_byte_of_var( const VARIANT_win  value_ );            /*F*/

LX_PUBLIC int16_t  lx_short_of_var( const VARIANT_win  value_ );           /*F*/

LX_PUBLIC long  lx_long_of_var( const VARIANT_win  value_ );               /*F*/

LX_PUBLIC float  lx_float_of_var( const VARIANT_win  value_ );             /*F*/

LX_PUBLIC double  lx_double_of_var( const VARIANT_win  value_ );           /*F*/

LX_PUBLIC CURRENCY_win  lx_currency_of_var( const VARIANT_win  value_ );   /*F*/

LX_PUBLIC DATE_win  lx_date_of_var( const VARIANT_win  value_ );           /*F*/

/* -------------------------------------------------------------------------- */
/* Functions: Conversion to Variant                                           */

LX_PUBLIC VARIANT_win  lx_var_of_bool( const lx_bool  value_ );            /*F*/

LX_PUBLIC VARIANT_win  lx_var_of_byte( const uint8_t  value_ );            /*F*/

LX_PUBLIC VARIANT_win  lx_var_of_short( const short  value_ );             /*F*/

LX_PUBLIC VARIANT_win  lx_var_of_long( const long  value_ );               /*F*/

LX_PUBLIC VARIANT_win  lx_var_of_float( const float  value_ );             /*F*/

LX_PUBLIC VARIANT_win  lx_var_of_double( const double  value_ );           /*F*/

LX_PUBLIC VARIANT_win  lx_var_of_currency( const CURRENCY_win  value_ );   /*F*/

LX_PUBLIC VARIANT_win  lx_var_of_date( const DATE_win  value_ );           /*F*/

LX_PUBLIC VARIANT_win  lx_var_of_chars( lx_chars_t  value_ );              /*F*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
