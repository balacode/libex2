/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_libc_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_LIBC__H
#define      INCLUDED_LIBEX_LIBC__H
#include "libex_libc.h"

/* -------------------------------------------------------------------------- */
/* Linux Development Stuff:                                                   */

#if LX_PLATFORM_LINUX
#define IMPLEMENT_LINUX                 LX_IMPLEMENT_LINUX
#define DL                              LX_DL
#endif

#define implement_linux                 lx_implement_linux

/* -------------------------------------------------------------------------- */
/* malloc.h (with extensions)                                                 */

/* Extended Memory Management Functions: */

#if 000
#define stack                           lx_stack
#define stack_src                       lx_stack_src
#define unstack                         lx_unstack
#define unstack_and_retain              lx_unstack_and_retain
#define unstack_and_retain_src          lx_unstack_and_retain_src
#define unstack_src                     lx_unstack_src
#endif                                                                 /* 000 */

#define free_all                        lx_free_all
#define free_id                         lx_free_id
#define malloc_id                       lx_malloc_id
#define mem_report                      lx_mem_report
#define realloc_id                      lx_realloc_id

#define itoa_fn                         lx_itoa_fn
#define itot_fn                         lx_itot_fn
#define itow_fn                         lx_itow_fn

/* Debugging / Informative Functions: */
#define mem_check                       lx_mem_check
#define mem_pending                     lx_mem_pending
#define mem_static                      lx_mem_static

#define test_itoa_fn                    lx_test_itoa_fn

#endif                                                                   /*eof*/
