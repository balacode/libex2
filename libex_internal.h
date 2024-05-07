/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                    [libex_internal.h] */
/* -------------------------------------------------------------------------- */
/* Don't include this in projects directly.  Instead, include libex.h         */

#if !defined INCLUDED_LIBEX_INTERNAL_H
#define      INCLUDED_LIBEX_INTERNAL_H

#include "libex.h"

#include "libex_call.h"
#include "libex_const.h"
#include "libex_debug.h"
#include "libex_error.h"
#include "libex_macro.h"
#include "libex_stdint.h"
#include "libex_type.h"

#if LX_PLATFORM_WIN32
#include "libex_win32.h"
#endif

#endif                                                                   /*eof*/
