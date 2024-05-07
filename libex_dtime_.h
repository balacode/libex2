/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                      [libex_dtime_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_DTIME__H
#define      INCLUDED_LIBEX_DTIME__H

#include "libex_dtime.h"

#define dtime_t                         lx_dtime_t
#define dtime_str_t                     lx_dtime_str_t

/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */

#define date_chars                      lx_date_chars
#define date_dtime                      lx_date_dtime
#define date_init                       lx_date_init
#define date_value                      lx_date_value
#define day_offset_dtime                lx_day_offset_dtime
#define dtime_chars                     lx_dtime_chars
#define dtime_init                      lx_dtime_init
#define dtime_now                       lx_dtime_now
#define dtime_null                      lx_dtime_null
#define dtime_value                     lx_dtime_value
#define get_time_dtime                  lx_get_time_dtime

/* -------------------------------------------------------------------------- */
#if LX_PLATFORM_WIN32                       /* Constructors: Windows-Specific */

#define dtime_FILETIME                  lx_dtime_FILETIME
#define dtime_SYSTEMTIME                lx_dtime_SYSTEMTIME

#if defined __tagVARIANT
#define dtime_VARIANT                   lx_dtime_VARIANT
#endif

#endif                                                   /* LX_PLATFORM_WIN32 */

/* -------------------------------------------------------------------------- */
/* Methods/Properties:                                                        */

#define format_dtime                    lx_format_dtime
#define has_date_dtime                  lx_has_date_dtime
#define has_time_dtime                  lx_has_time_dtime
#define is_equal_dtime                  lx_is_equal_dtime
#define is_null_dtime                   lx_is_null_dtime
#define is_valid_dtime                  lx_is_valid_dtime
#define iso8601_dtime                   lx_iso8601_dtime
#define value_date                      lx_value_date
#define value_dtime                     lx_value_dtime
#define weekday_dtime                   lx_weekday_dtime

/* -------------------------------------------------------------------------- */
/* Functions:                                                                 */

#define days_in_month                   lx_days_in_month
#define timespan                        lx_timespan
#define weekday                         lx_weekday

/* -------------------------------------------------------------------------- */

#if LX_PLATFORM_WIN32
#define FILETIME_dtime                  lx_FILETIME_dtime
#define FILETIME_set                    lx_FILETIME_set
#define SYSTEMTIME_dtime                lx_SYSTEMTIME_dtime
#define SYSTEMTIME_set                  lx_SYSTEMTIME_set
#endif

#endif                                                                   /*eof*/
