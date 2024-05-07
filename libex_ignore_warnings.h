/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                             [libex_ignore_warnings.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_IGNORE_WARNINGS_H
#define      INCLUDED_LIBEX_IGNORE_WARNINGS_H

/* -------------------------------------------------------------------------- */
/* Warnings generated compiling LIBJPEG:                                      */

#if defined _MSC_VER
#pragma warning (disable:4013)  /* W:L3 FN undefined; assuming extern rt. int */
#pragma warning (disable:4100)  /* W:L4 unreferenced formal parameter         */
#pragma warning (disable:4127)  /* W:L4 conditional expression is constant    */
#pragma warning (disable:4244)  /* W:L2 conversion, possible loss of data     */
#pragma warning (disable:4255)  /* W:L4 no function prototype given           */
#pragma warning (disable:4774)  /* W:L4 format string is not string a literal */
#pragma warning (disable:4702)  /* W:L4 unreachable code                      */
#pragma warning (disable:4710)  /* W:L4 function not inlined                  */
#pragma warning (disable:4820)  /* W:L4 'N' bytes padding added after 'NAME'  */
#pragma warning (disable:4996)  /* W:L3 'function': may be unsafe/deprecated  */
#endif

/* -------------------------------------------------------------------------- */
/* Warnings generated compiling LIBPNG:                                       */

#if defined _MSC_VER
#pragma warning (disable:4090)  /* W:L1 'OPERATION' : different 'MODIFIER'    */
/* W:C4090                              qualifiers                            */
#pragma warning (disable:4206)  /* W:L4 nonstandard: translation unit empty   */
#pragma warning (disable:4574)  /* W:L4 'X' is defined to be '0': did you     */
/* W:C4574                              mean to use '#if X'?                  */
#pragma warning (disable:4996)  /* W:L3 'function': may be unsafe/deprecated  */
#endif

/* -------------------------------------------------------------------------- */
/* Warnings generated compiling LIBSQLITE3: v3.8.3                            */

#if defined _MSC_VER
#pragma warning (disable:4100)  /* W:L4 unreferenced formal parameter         */
#pragma warning (disable:4127)  /* W:L4 conditional expression is constant    */
#pragma warning (disable:4131)  /* W:L4 'FUNCTION': uses old-style declarator */
#pragma warning (disable:4206)  /* W:L4 nonstandard: translation unit empty   */
#pragma warning (disable:4232)  /* W:L4 nonstandard extension used :          */
/* W:C4232                              addr. of dllimport NAME is not static */
#pragma warning (disable:4242)  /* W:L4 conversion, possible loss of data     */
#pragma warning (disable:4244)  /* W:L2 conversion, possible loss of data     */
#pragma warning (disable:4456)  /* W:L4 declaration hides previous local decl */
#pragma warning (disable:4668)  /* W:L4 'SYMBOL' is not defined as a p. macro */
#pragma warning (disable:4701)  /* W:L4 Potentially uninitialized local var.  */
#pragma warning (disable:4703)  /* W:L4 Potentially uninitialized local ptr.  */
#pragma warning (disable:4706)  /* W:L4 assignment within conditional expr.   */
#endif

/* -------------------------------------------------------------------------- */
/* Warnings generated compiling ZLIB:                                         */

#if defined __GNUC__
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
#pragma GCC diagnostic ignored "-Wswitch-default"
#pragma GCC diagnostic ignored "-Wswitch-enum"
#endif

#if defined _MSC_VER
#pragma warning (disable:4127)  /* W:L4 conditional expression is constant    */
#pragma warning (disable:4131)  /* W:L4 'FUNCTION': uses old-style declarator */
#pragma warning (disable:4244)  /* W:L2 conversion, possible loss of data     */
#pragma warning (disable:4820)  /* W:L4 'N' bytes padding added after 'NAME'  */
#pragma warning (disable:4996)  /* W:L3 'function': may be unsafe/deprecated  */
#endif

#endif                                                                   /*eof*/
