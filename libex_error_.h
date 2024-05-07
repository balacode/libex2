/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                      [libex_error_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_ERROR__H
#define      INCLUDED_LIBEX_ERROR__H
#include "libex_error.h"

#undef ASSERT
#undef VERIFY

#define ASSERT                          LX_ASSERT
#define ERR                             LX_ERR
#define ERR_2                           LX_ERR_2
#define LINE                            LX_LINE
#define OS_ERR                          LX_OS_ERR
#define OS_VERIFY                       LX_OS_VERIFY
#define OS_WARN                         LX_OS_WARN
#define VERIFY                          LX_VERIFY
#define WARN                            LX_WARN
#define WARN_2                          LX_WARN_2
#define WARN_3                          LX_WARN_3
#define WARN_4                          LX_WARN_4

#define assert_fn                       lx_assert_fn
#define bool_reflect                    lx_bool_reflect
#define counter                         lx_counter

#endif                                                                   /*eof*/
