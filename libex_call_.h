/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_call_.h] */
/* -------------------------------------------------------------------------- */
/* Call Tracing and Definitions and Declarations:                             */

#if !defined INCLUDED_LIBEX_CALL__H
#define      INCLUDED_LIBEX_CALL__H
#include "libex_call.h"

#define CALL_TRACE                      LX_CALL_TRACE
#define GO                              LX_GO
#define RETURN                          LX_RETURN

/* -------------------------------------------------------------------------- */
/* Call-Tracing Function Declarations:                                        */

#if defined LX_CALL_TRACE && LX_CALL_TRACE == 2
#define fn_call_entry                   lx_fn_call_entry
#define fn_call_exit                    lx_fn_call_exit
#define fn_call_report                  lx_fn_call_report
#endif

#endif                                                                   /*eof*/
