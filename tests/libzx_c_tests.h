/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                     [libex_c_tests.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_C_TESTS_H
#define      INCLUDED_LIBEX_C_TESTS_H

#if LX_PLATFORM_WIN32 && defined _MSC_VER
#pragma comment (lib, "rpcrt4.lib")
#pragma comment (lib, "winmm.lib")
#endif

#if LX_PLATFORM_WIN32
#include <conio.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include "libex.h"
#include "libex_variant_functions.h"

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

LX_PUBLIC void  lx_test_dtime_class( void );                               /*F*/
LX_PUBLIC void  lx_test_file_class( void );                                /*F*/
LX_PUBLIC void  lx_test_string_class( void );                              /*F*/
LX_PUBLIC void  lx_test_pdf_class( void );                                 /*F*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
