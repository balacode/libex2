/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_dtime.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_DTIME_H
#define      INCLUDED_LIBEX_DTIME_H

#if LX_PLATFORM_WIN32
#include <windows.h>
#include "libex_win32.h"
#endif

#include "libex.h"

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4820)  /* W:L4 'N' bytes padding added after 'NAME'  */
#endif

typedef struct  lx_dtime_t {
    uint16_t  year;                                             /* lx_dtime_t */
    uint8_t   month;                                            /* lx_dtime_t */
    uint8_t   day;                                              /* lx_dtime_t */
    uint8_t   hour;                                             /* lx_dtime_t */
    uint8_t   minute;                                           /* lx_dtime_t */
    uint8_t   second;                                           /* lx_dtime_t */
}
lx_dtime_t;

typedef struct  lx_dtime_str_t {
    lx_char_t  cs[65];                                      /* lx_dtime_str_t */
}
lx_dtime_str_t;

#if defined _MSC_VER
#pragma warning (pop)
#endif

/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */

/* Construct a date/time object from given year, month and day numbers.       */
LX_PUBLIC lx_dtime_t  lx_date_init(                                        /*C*/
    const int  year_,                                                      /*-*/
    const int  month_,                                                     /*-*/
    const int  day_ );                                                     /*-*/

/* Construct the object from a text string (date-only, time set 00:00:00)     */
LX_PUBLIC lx_dtime_t  lx_date_chars( lx_chars_t  text_ );                  /*C*/

/* Return only the date from the given object.                                */
LX_PUBLIC lx_dtime_t  lx_date_dtime( const lx_dtime_t* const  object_ );   /*C*/

/* Construct a lx_dtime_t object from a floating-point number.                */
LX_PUBLIC lx_dtime_t  lx_date_value( const double  value_ );               /*C*/

/* Return a lx_dtime_t object offset by the specified number of days.         */
LX_PUBLIC lx_dtime_t  lx_day_offset_dtime(                                 /*C*/
    const lx_dtime_t* const  object_,                                      /*-*/
    const int                days_ );                                      /*-*/

/* Construct a date/time object from numeric year, month, date, hour, etc.    */
LX_PUBLIC lx_dtime_t  lx_dtime_init(                                       /*C*/
    const int  year_,                                                      /*-*/
    const int  month_,                                                     /*-*/
    const int  day_,                                                       /*-*/
    const int  hour_,                                                      /*-*/
    const int  minute_,                                                    /*-*/
    const int  second_ );                                                  /*-*/

/* Construct the object from a text string.                                   */
LX_PUBLIC lx_dtime_t  lx_dtime_chars( lx_chars_t  text_ );                 /*C*/

/* Return the current local date and time.                                    */
LX_PUBLIC lx_dtime_t  lx_dtime_now( void );                                /*C*/

/* Construct a null date/time object, with all fields zet to zero.            */
LX_PUBLIC lx_dtime_t  lx_dtime_null( void );                               /*C*/

/* Construct a lx_dtime_t object from a floating-point number.                */
LX_PUBLIC lx_dtime_t  lx_dtime_value( const double  value_ );              /*C*/

/* Return only the time from the given object.                                */
LX_PUBLIC lx_dtime_t  lx_get_time_dtime(                                   /*C*/
    const lx_dtime_t* const  object_ );                                    /*-*/

/* -------------------------------------------------------------------------- */
#if LX_PLATFORM_WIN32                 /* Constructors: Windows-Specific */

/* Construct a date/time object from a FILETIME.                              */
LX_PUBLIC lx_dtime_t  lx_dtime_FILETIME(                                   /*C*/
    const FILETIME_win* const  object_ );                                  /*-*/

/* Construct a date/time object from a SYSTEMTIME.                            */
LX_PUBLIC lx_dtime_t  lx_dtime_SYSTEMTIME(                                 /*C*/
    const SYSTEMTIME_win* const  object_ );                                /*-*/

#if defined __tagVARIANT
/* Construct a date/time object from a VARIANT.                               */
LX_PUBLIC lx_dtime_t  lx_dtime_VARIANT(                                    /*F*/
    const VARIANT_win* const  object_ );                                   /*C*/
#endif

#endif                                                   /* LX_PLATFORM_WIN32 */

/* -------------------------------------------------------------------------- */
/* Methods/Properties:                                                        */

/* Return a formatted string. (e.g. specify "%HH:%NN:%SS")                    */
LX_PUBLIC lx_dtime_str_t  lx_format_dtime(                                 /*M*/
    const lx_dtime_t* const  object_,                                      /*-*/
    lx_chars_t               format_ );                                    /*-*/

/* Return true if a date has been assigned.                                   */
LX_PUBLIC lx_bool  lx_has_date_dtime( const lx_dtime_t* const  object_ );  /*P*/

/* Return true if a time has been assigned.                                   */
LX_PUBLIC lx_bool  lx_has_time_dtime( const lx_dtime_t* const  object_ );  /*P*/

/* Return true if the date/time equals the specified value.                   */
LX_PUBLIC lx_bool  lx_is_equal_dtime(                                      /*P*/
    const lx_dtime_t* const  object_1_,                                    /*-*/
    const lx_dtime_t* const  object_2_ );                                  /*-*/

/* Return true if the date has not been assinged any value.                   */
LX_PUBLIC lx_bool  lx_is_null_dtime( const lx_dtime_t* const  object_ );   /*P*/

/* Return true if the values of all fields in the date are valid.             */
LX_PUBLIC lx_bool  lx_is_valid_dtime( const lx_dtime_t* const  object_ );  /*P*/

/* Return an ISO-8601 formatted string (yyyy-mm-dd or yyyy-mm-ddT0h:0m:0s).   */
LX_PUBLIC lx_dtime_str_t  lx_iso8601_dtime(                                /*M*/
    const lx_dtime_t* const  object_ );                                    /*-*/

/* Return a floating-point number based on given object. (date-only)          */
LX_PUBLIC double  lx_value_date( const lx_dtime_t* const  object_ );       /*P*/

/* Return a floating-point number based on given object.                      */
LX_PUBLIC double  lx_value_dtime( const lx_dtime_t* const  object_ );      /*P*/

/* Return the day of week num. from the specified date/time object, ranging   */
/* from 1 for Monday to 7 for Sunday, or 0 if the given date is not valid.    */
LX_PUBLIC uint8_t  lx_weekday_dtime( const lx_dtime_t* const  object_ );   /*P*/

/* -------------------------------------------------------------------------- */
/* Functions:                                                                 */

/* Return the number of days in the specified year and month.                 */
/* (If year is less than 1 greater than 9999, returns 0.)                     */
LX_PUBLIC uint8_t  lx_days_in_month(                                       /*F*/
    const int  year_,                                                      /*-*/
    const int  month_ );                                                   /*-*/

/* Return a human-friendly time interval string, given the number of seconds. */
LX_PUBLIC lx_dtime_str_t  lx_timespan( const int  seconds_ );              /*F*/

/* Return the day of week num. from the given date, ranging from 1 for Monday */
/* to 7 for Sunday (ISO-8601 weekday), or 0 if the given date is not valid.   */
LX_PUBLIC uint8_t  lx_weekday(                                             /*F*/
    const int  year_,                                                      /*-*/
    const int  month_,                                                     /*-*/
    const int  day_ );                                                     /*-*/

/* -------------------------------------------------------------------------- */
#if LX_PLATFORM_WIN32      /* Functions: Windows-Specific               */

/* Return a FILETIME based on the given date/time object.                     */
LX_PUBLIC FILETIME_win  lx_FILETIME_dtime(                                 /*M*/
    const lx_dtime_t* const  object_ );                                    /*-*/

/* Return a FILETIME based on given numeric year, month, day, hour, etc.      */
LX_PUBLIC FILETIME_win  lx_FILETIME_set(                                   /*F*/
    const int  year_,                                                      /*-*/
    const int  month_,                                                     /*-*/
    const int  day_,                                                       /*-*/
    const int  hour_,                                                      /*-*/
    const int  minute_,                                                    /*-*/
    const int  second_ );                                                  /*-*/

/* Return a SYSTEMTIME based on the given date/time object.                   */
LX_PUBLIC SYSTEMTIME_win  lx_SYSTEMTIME_dtime(                             /*M*/
    const lx_dtime_t* const  object_ );                                    /*-*/

/* Return a SYSTEMTIME based on given numeric year, month, day, hour, etc.    */
LX_PUBLIC SYSTEMTIME_win  lx_SYSTEMTIME_set(                               /*F*/
    const int  year_,                                                      /*-*/
    const int  month_,                                                     /*-*/
    const int  day_,                                                       /*-*/
    const int  hour_,                                                      /*-*/
    const int  minute_,                                                    /*-*/
    const int  second_ );                                                  /*-*/

#endif                                                   /* LX_PLATFORM_WIN32 */

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
