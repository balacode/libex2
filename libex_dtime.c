/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_dtime.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_dtime_.h"
#if defined INCLUDED_LIBEX_DTIME_H

#include <float.h>   /* for _isnan()  */
#include <stdio.h>   /* for sprintf() */
#include <string.h>  /* for memset()  */

#include "libex_config_.h"

#include "libex_call_.h"
#include "libex_language_.h"
#include "libex_logging_.h"
#include "libex_macro_.h"
#include "libex_.h"
#include "libex_system_.h"
#include "libex_type_.h"

#if PLATFORM_LINUX
#include <time.h>
#endif

#if PLATFORM_WIN32
#include "libex_win32_.h"
#endif

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#if defined _MSC_VER
#pragma warning (disable:4710)  /* W:L4 function not inlined */
#endif

#define MAX_WORD_COUNT  12

#define NULL_DATE  { 0, 0, 0, 0, 0, 0 }

#define NA  -255
#define DS  -'/'
#define TS  -':'
#define AM  -'A'
#define PM  -'P'

/* -------------------------------------------------------------------------- */
NAMESPACE(c_)

/* -------------------------------------------------------------------------- */
/* Functions: Private                                                         */

#if defined __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#endif


/* Return an English month name given a month number from 1 to 12.            */
static chars_t  _month_name( int  month_number_ ) {                        /*F*/
    static chars_t  month_names[12] = {
        _T("January"),   _T("February"), _T("March"),    _T("April"),
        _T("May"),       _T("June"),     _T("July"),     _T("August"),
        _T("September"), _T("October"),  _T("November"), _T("December")
    };
    chars_t  ret = _T("");
    if (month_number_ >= 1 && month_number_ <= 12) {
        ret = month_names[month_number_ - 1];
    }
    return ret;
} /* _month_name() */


/* Return a short English month name (3 letter) given a number from 1 to 12.  */
static chars_t  _mth_name( int  month_number_ ) {                          /*F*/
    static chars_t  mth_names[12] = {
        _T("Jan"), _T("Feb"), _T("Mar"), _T("Apr"),
        _T("May"), _T("Jun"), _T("Jul"), _T("Aug"),
        _T("Sep"), _T("Oct"), _T("Nov"), _T("Dec")
    };
    chars_t  ret = _T("");
    if (month_number_ >= 1 && month_number_ <= 12) {
        ret = mth_names[month_number_ - 1];
    }
    return ret;
} /* _mth_name() */


/* Assigns the given year_, month_ and day_ to the given date/time object     */
/* provided the given arguments are a valid date, and returns true if set.    */
/* Used only by dtime_chars().                                             */
static bool  _set_date(                                                    /*F*/
    const int       year_,                                                 /*-*/
    const int       month_,                                                /*-*/
    const int       day_,                                                  /*-*/
    dtime_t* const  object_out_ ) {                                        /*-*/
    if (year_  >= 0 && year_  <= 9999 &&
        month_ >= 1 && month_ <= 12 &&
        day_   >= 1 && day_   <= days_in_month(year_, month_)) {

        object_out_->year  = CAST(uint16_t, year_);
        object_out_->month = CAST(uint8_t,  month_);
        object_out_->day   = CAST(uint8_t,  day_);

        if (object_out_->year < 100) {
            object_out_->year += object_out_->year < 50 ? 2000 : 1900;
        }

        return true;
    }
    return false;
} /* _set_date */


/* Process standard-format date/time strings (including ISO-8601).            */
/* Returns true if the string matched one of the standard formats.            */
/* Used only by dtime_chars().                                                */
static bool  _set_standard_dtime(                                          /*F*/
    const int16_t  (*const  parsed_)[MAX_WORD_COUNT],                      /*-*/
    const size_t            count_,                                        /*-*/
    dtime_t* const          object_out_ ) {                                /*-*/

#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4820)  /* W:L4 'N' bytes padding added after 'NAME'  */
#endif

    static struct _t {
        size_t  count;
        char  type[10];
    } const  fmt[8] = {
        {  3, {'h', ':', 'm'}                                    },
        {  5, {'h', ':', 'm', ':', 's'}                          },
        {  5, {'Y', '/', 'M', '/', 'D'}                          },
        {  8, {'Y', '/', 'M', '/', 'D', 'h', ':', 'm'}           },
        { 10, {'Y', '/', 'M', '/', 'D', 'h', ':', 'm', ':', 's'} },
    };
    /*     01234567890123456789 */
    /*  3  hh:mm^               */
    /*  5  hh:mm:ss^            */
    /*  5  YYY-MM-DD^           */
    /*  5  YYYY-MM-DD^          */
    /*  8  YYY-MM-DD hh:mm^     */
    /*  8  YYYY-MM-DD hh:mm^    */
    /* 10  YYY-MM-DD hh:mm:ss^  */
    /* 10  YYYY-MM-DD hh:mm:ss^ */

#if defined _MSC_VER
#pragma warning (pop)
#endif

    dtime_t  out = NULL_DATE;
    int  f;
    for (f = 0; f < 8; f++) {
        if (count_ == fmt[f].count) {

            bool  match = true;
            size_t  i;
            for (i = 0; i < fmt[f].count; i++) {
                const char     type = fmt[f].type[i];
                const int16_t  it   = (*parsed_)[i];

                if ((type == '/' && it != DS) || (type == ':' && it != TS)) {
                    match = false;
                    break;
                }
            }

            if (match) {
                for (i = 0; i < fmt[f].count; i++) {
                    const uint16_t  it = (*parsed_)[i];
                    switch (fmt[f].type[i]) {
                            CASE('M', out.month  = CAST(uint8_t, it));
                            CASE('D', out.day    = CAST(uint8_t, it));
                            CASE('h', out.hour   = CAST(uint8_t, it));
                            CASE('m', out.minute = CAST(uint8_t, it));
                            CASE('s', out.second = CAST(uint8_t, it));

                        case 'Y':
                            out.year = CAST(uint16_t, it);
                            if (out.year < 100) {
                                out.year += out.year < 50 ? 2000 : 1900;
                            }
                            break;

                        default:
                            ;
                    }
                }
                break;
            }
        }
    }
    {
        const bool  ret = is_valid_dtime(&out) && !is_null_dtime(&out);
        if (!ret) {
            dtime_t  out_err = NULL_DATE;
            out = out_err;
        }
        *object_out_ = out;
        return ret;
    }
} /* _set_standard_dtime */


/* Return an abbreviated English weekday name given a number from 1 to 7.     */
static chars_t  _wday_name( int  weekday_number_ ) {                       /*F*/
    static chars_t  wday_names[12] = {
        _T("Mon"), _T("Tue"), _T("Wed"), _T("Thu"),
        _T("Fri"), _T("Sat"), _T("Sun")
    };
    chars_t  ret = _T("");
    if (weekday_number_ >= 1 && weekday_number_ <= 7) {
        ret = wday_names[weekday_number_ - 1];
    }
    return ret;
} /* _wday_name() */


/* Return an English weekday name given a number from 1 to 7.                 */
static chars_t  _weekday_name( int  weekday_number_ ) {                    /*F*/
    static chars_t  weekday_names[12] = {
        _T("Monday"), _T("Tuesday"), _T("Wednesday"), _T("Thursday"),
        _T("Friday"), _T("Saturday"), _T("Sunday")
    };
    chars_t  ret = _T("");
    if (weekday_number_ >= 1 && weekday_number_ <= 7) {
        ret = weekday_names[weekday_number_ - 1];
    }
    return ret;
} /* _weekday_name() */


/* Given a part of a date, returns an integer. Numeric strings are changed    */
/* to positive integers, while month names, date and time separators and      */
/* 'AM' and 'PM' are changed to negative integer placeholders.                */
/* Used only by dtime_chars().                                                */
static int16_t  _word_value( chars_t  word_ ) {                            /*F*/
#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4820)  /* W:L4 'N' bytes padding added after 'NAME'  */
#endif

    static struct _t {
        chars_t str;
        int16_t val;
    } const tokens[] = {
        { _T("/"),    DS }, { _T("-"),         DS }, { _T(":"), TS },
        { _T("JAN"),  -1 }, { _T("JANUARY"),   -1 },
        { _T("FEB"),  -2 }, { _T("FEBRUARY"),  -2 },
        { _T("MAR"),  -3 }, { _T("MARCH"),     -3 },
        { _T("APR"),  -4 }, { _T("APRIL"),     -4 },
        { _T("MAY"),                           -5 },
        { _T("JUN"),  -6 }, { _T("JUNE"),      -6 },
        { _T("JUL"),  -7 }, { _T("JULY"),      -7 },
        { _T("AUG"),  -8 }, { _T("AUGUST"),    -8 },
        { _T("SEP"),  -9 }, { _T("SEPTEMBER"), -9 },
        { _T("OCT"), -10 }, { _T("OCTOBER"),  -10 },
        { _T("NOV"), -11 }, { _T("NOVEMBER"), -11 },
        { _T("DEC"), -12 }, { _T("DECEMBER"), -12 },
        { _T("A"),    AM }, { _T("AM"),        AM },
        { _T("P"),    PM }, { _T("PM"),        PM },
        { NULL, 0 }
    };

#if defined _MSC_VER
#pragma warning (pop)
#endif

    int16_t  ret = 0;

    /* check if the word is in the array, and return matching value */
    size_t  i = 0;
    do {
        chars_t  a = tokens[i].str;
        chars_t  b = word_;
        while (*a == *b && *a != '\0') {
            a++;
            b++;
        }
        if (*a == '\0' && *b == '\0') {
            ret = tokens[i].val;
            goto _ret;
        }
        i++;
    } while (tokens[i].str != NULL);

    /* if the word is a number, convert and return it */
    while (IS_DIGIT(*word_)) {
        ret *= 10;
        ret += (*word_++) - '0';
    }
_ret:
    return ret;
} /* _word_value */


#if defined __GNUC__
#pragma GCC diagnostic pop
#endif


/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */


/* Construct a date/time object from given year, month and day numbers.       */
PUBLIC dtime_t  date_init(                                                 /*C*/
    const int  year_,                                                      /*-*/
    const int  month_,                                                     /*-*/
    const int  day_ ) {                                                    /*-*/
    GO                                                            (UID(F3FB0C));
    dtime_t  ret = NULL_DATE;
    ret.year     = CAST(uint16_t, year_);
    ret.month    = CAST(uint8_t,  month_);
    ret.day      = CAST(uint8_t,  day_);

    if (ret.year < 100) {
        ret.year += ret.year < 50 ? 2000 : 1900;
    }

    if (!is_valid_dtime(&ret)) {
        goto _err;
    }

_ret:
    RETURN(ret);
_err: {
        dtime_t  ret_err = NULL_DATE;
        ret = ret_err;
    }
    goto _ret;
} /* date_init */


/* Construct the object from a text string (date-only, time set 00:00:00)     */
PUBLIC dtime_t  date_chars( chars_t  text_ ) {                             /*C*/
    GO                                                            (UID(F85E27));
    dtime_t  dt  = dtime_chars(text_);
    dtime_t  ret = NULL_DATE;
    ret.year     = dt.year;  /* use only the date part of the result */
    ret.month    = dt.month;
    ret.day      = dt.day;
    RETURN(ret);
} /* date_chars */


/* Return only the date from the given object.                                */
PUBLIC dtime_t  date_dtime( const dtime_t* const  object_ ) {              /*C*/
    GO                                                            (UID(FDF1D9));
    dtime_t  ret = NULL_DATE;
    ret.year     = object_->year;
    ret.month    = object_->month;
    ret.day      = object_->day;
    RETURN(ret);
} /* date_dtime */


/* Construct a dtime_t object from a floating-point number.                */
PUBLIC dtime_t  date_value( const double  value_ ) {                       /*C*/
    GO                                                            (UID(F247A6));
    dtime_t  ret = dtime_value(value_);
    ret.hour = ret.minute = ret.second = 0;
    RETURN(ret);
} /* date_value */


/* Return a dtime_t object offset by the specified number of days.         */
PUBLIC dtime_t  day_offset_dtime(                                          /*C*/
    const dtime_t* const  object_,                                         /*-*/
    const int             days_ ) {                                        /*-*/
    GO                                                            (UID(FA0309));
    int  offset_days = days_;
    int  year        = object_->year;
    int  month       = object_->month;
    int  day         = object_->day;

    if (offset_days == 0) {
        dtime_t  ret = *object_;
        RETURN(ret);
    }

    /* back-iterate */
    while (offset_days < 0) {
        const int  i = LESSER(-offset_days, day);
        offset_days += i;
        day         -= i;

        if (day < 1) {
            month--;
            if (month < 1) {
                month = 12;
                year--;
            }
            day = days_in_month(year, month);
        }
    }

    /* positive offsets use a simple iteration without extra arithmetic */
    if (offset_days > 0) {
        int  mdays = days_in_month(year, month);

        while (offset_days > 0) {
            offset_days--;
            if (++day > mdays) {
                day = 1;
                if (++month > 12) {
                    month = 1;
                    year++;
                }
                mdays = days_in_month(year, month);
            }
        }
    }
    {
        dtime_t  ret = dtime_init(year, month, day,
                                  object_->hour, object_->minute,
                                  object_->second);
        RETURN(ret);
    }
} /* day_offset_dtime */


/* Construct a date/time object from numeric year, month, date, hour, etc.    */
PUBLIC dtime_t  dtime_init(                                                /*C*/
    const int  year_,                                                      /*-*/
    const int  month_,                                                     /*-*/
    const int  day_,                                                       /*-*/
    const int  hour_,                                                      /*-*/
    const int  minute_,                                                    /*-*/
    const int  second_ ) {                                                 /*-*/
    GO                                                            (UID(FEB0A8));
    dtime_t  ret = NULL_DATE;
    ret.year     = CAST(uint16_t, year_);
    ret.month    = CAST(uint8_t,  month_);
    ret.day      = CAST(uint8_t,  day_);
    ret.hour     = CAST(uint8_t,  hour_);
    ret.minute   = CAST(uint8_t,  minute_);
    ret.second   = CAST(uint8_t,  second_);

    if (ret.year < 100) {
        ret.year += ret.year < 50 ? 2000 : 1900;
    }

    if (!is_valid_dtime(&ret)) {
        goto _err;
    }

_ret:
    RETURN(ret);
_err: {
        dtime_t  ret_err = NULL_DATE;
        ret = ret_err;
    }
    goto _ret;
} /* dtime_init */


/* Construct the object from a text string.                                   */
PUBLIC dtime_t  dtime_chars( chars_t  str_ ) {                             /*C*/
    GO                                                            (UID(FA433B));
#define MAX_WORD_LEN  10

    int16_t  arr[MAX_WORD_COUNT];  /* array of parsed word values  */
    char_t   word[MAX_WORD_LEN];   /* temp buffer for current word */
    size_t   i        = 0;         /* general-purpose iterator     */
    size_t   count    = 0;         /* total number of parsed words */
    size_t   len      = 0;         /* holds length of input string */
    size_t   trim     = 0;         /* number of trimmed spaces     */
    int8_t   month    = 0;
    bool     has_am   = false;
    bool     has_pm   = false;
    bool     set_hour = false;

    /* parse str_ into an integer array, with non-numeric words negative */
    dtime_t  ret = NULL_DATE;
    chars_t  ch  = str_;

    while (IS_SPACE(*ch)) {
        ch++;
        trim++;
    }

    while (*ch != '\0') {
        if (IS_SPACE(*ch)) {
            while (IS_SPACE(*ch)) {
                ch++;
            }
            continue;
        } else if (IS_DIGIT(*ch)) {
            while (IS_DIGIT(*ch)) {
                word[i++] = *ch++;
            }
        } else if (IS_ALPHA(*ch)) {
            while (IS_ALPHA(*ch)) {
                word[i++] = IS_LOWER_CASE(*ch) ? *ch - 'a' + 'A' : *ch;
                ch++;
            }
        } else if (*ch == ':' || *ch == '/' || *ch == '-') {
            word[i++] = *ch++;
        } else {
            ch++;
        }

        if (i >= MAX_WORD_LEN) {
            goto _err;
        }

        if (i > 0) {
            word[i] = '\0';
            arr[count++] = _word_value(word);
            i = 0;
        }
    } /* while */
#undef MAX_WORD_LEN

    len = ch - str_ - trim;
    while (IS_SPACE(*--ch)) {
        len--;
    }
    if (len < 3 || count < 2) {
        goto _err;
    }

    if (len ==  5 || len ==  8 || len ==  9 || len == 10 ||
        len == 15 || len == 16 || len == 18 || len == 19) {

        if (_set_standard_dtime((const int16_t (*const)[12]) &arr, count, &ret)) {
            return ret;
        }
    }

    /* extract month */
    for (i = 0; i < count; i++) {
        if (arr[i] >= -12 && arr[i] <= -1) {
            if (month != 0) {
                goto _err;
            }
            ret.month = month = CAST(uint8_t, -arr[i]);
            arr[i]    = NA;
        }
    }

    /* extract time ('hh:mm' or 'hh:mm:ss') */
    for (i = 0; i < count; i++) {
        if (arr[i] != TS) {
            continue;
        }
        if (i == 0 || i == (count - 1)) {
            goto _err;
        }
        if (!set_hour) {
            set_hour     = true;
            {
                ret.hour   = CAST(uint8_t, arr[i - 1]);
                arr[i - 1] = NA;
            }
            {
                ret.minute = CAST(uint8_t, arr[i + 1]);
                arr[i + 1] = NA;
            }
        } else {
            ret.second = CAST(uint8_t, arr[i + 1]);
            arr[i + 1] = NA;
        }
    }

    /* extract 'AM', 'PM', 'A' or 'P' */
    for (i = 0; i < count; i++) {
        if (arr[i] == AM || arr[i] == PM) {
            if (i == 0 || has_am || has_pm) {
                goto _err;
            }

            has_am = arr[i] == AM;
            has_pm = arr[i] == PM;
            arr[i] = NA;

            if (!set_hour && arr[i - 1] >= 0 && arr[i - 1] <= 23) {
                set_hour = true;
                {
                    ret.hour = CAST(uint8_t, arr[i - 1]);
                    arr[i - 1] = NA;
                }
            }
        }
    }

    {
        /* remove already-parsed items and separators from the array */
        size_t  w = 0,  removed = 0;
        for (i = 0; i < count; i++) {
            if (arr[i] == NA || arr[i] == DS || arr[i] == TS) {
                removed++;
                continue;
            }
            arr[w++] = arr[i];
        }
        count -= removed;
    }

    if (count == 3) {
        if (!_set_date(arr[0], arr[1], arr[2], &ret) &&  /* y-m-d */
            !_set_date(arr[2], arr[0], arr[1], &ret) &&  /* m-d-y */
            !_set_date(arr[2], arr[1], arr[0], &ret)) {  /* d-m-y */
            goto _err;
        }

    } else if (count == 2) {
        if (month == 0) {
            const int  year_now = dtime_now().year;
            if (!_set_date(year_now, arr[0], arr[1], &ret) &&
                !_set_date(year_now, arr[1], arr[0], &ret) &&
                !_set_date(arr[0], arr[1], 1, &ret)        &&
                !_set_date(arr[1], arr[0], 1, &ret)) {
                goto _err;
            }
        } else if (!_set_date(arr[0], month, arr[1], &ret) &&
                   !_set_date(arr[1], month, arr[0], &ret)) {
            goto _err;
        }

    } else if (count == 1) {
        int  val = arr[0];
        if (ret.year == 0 && month != 0 && ret.day == 0) {
            uint16_t  year_now = dtime_now().year;
            uint8_t   days     = days_in_month(year_now, month);

            if (val > 0 && val <= days) {
                ret.year = CAST(uint16_t, year_now);
                ret.day  = CAST(uint8_t, val);
            } else {
                ret.year = CAST(uint16_t, val);
                ret.day = 1;
            }
        }
    }

    if (has_pm && ret.hour < 13) {
        ret.hour += 12;
    }
_ret:
    if (ret.year < 100 && ret.month != 0) {
        ret.year += ret.year < 50 ? 2000 : 1900;
    }
    RETURN(ret);
_err: {
        dtime_t  ret_err = NULL_DATE;
        ret = ret_err;
    }
    goto _ret;
} /* dtime_chars */


/* Return the current local date and time.                                    */
PUBLIC dtime_t  dtime_now( void ) {                                        /*C*/
    GO                                                            (UID(F997AC));
    dtime_t  ret = NULL_DATE;

#if PLATFORM_LINUX
    time_t  t;
    time(&t);
    struct tm  now = (*localtime(&t));   /* for UTC time: (*gmtime(&time)) */
    ret.year   = now.tm_year + 1900;
    ret.month  = now.tm_mon + 1;
    ret.day    = now.tm_mday;
    ret.hour   = now.tm_hour;
    ret.minute = now.tm_min;
    ret.second = now.tm_sec;
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    SYSTEMTIME_win  now = { 0 };
    GetLocalTime_win(&now);      /* to get UTC time: GetSystemTime_win(&now); */
    ret = dtime_SYSTEMTIME(&now);
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* dtime_now */


/* Construct a null date/time object, with all fields zet to zero.            */
PUBLIC dtime_t  dtime_null( void ) {                                       /*C*/
    GO                                                            (UID(F3D424));
    const dtime_t  ret = NULL_DATE;
    RETURN(ret);
} /* dtime_null */


/* Construct a dtime_t object from a floating-point number.                   */
PUBLIC dtime_t  dtime_value( const double  value_ ) {                      /*C*/
    GO                                                            (UID(F4BAAB));
    dtime_t  ret = NULL_DATE;

#if defined __GNUC__ || defined __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

    if (ISNAN(value_) || value_ <= -657435.0 || value_ >= 2958466.0) {
        goto _err;
    }

#if defined __GNUC__ || defined __clang__
#pragma GCC diagnostic pop
#endif

    {
        /* set date */
        const double    dt  = value_ + 719468 - 25569;
        const int       era = CAST(int, (dt >= 0 ? dt : dt - 146096) / 146097);
        const unsigned  doe = CAST(unsigned, dt - era * 146097);    /*0-146096*/
        const unsigned  yoe =
            (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;     /*0-399*/
        const int       yr  = CAST(int, yoe) + era * 400;
        const unsigned  doy = doe - (365 * yoe + yoe / 4 - yoe / 100); /*0-365*/
        const unsigned  mp  = (5 * doy + 2) / 153;                     /* 0-11*/
        const unsigned  dy  = doy - (153 * mp + 2) / 5 + 1;            /* 1-31*/
        const unsigned  mt  = mp + (mp < 10 ? 3 : -9);                 /* 1-12*/

        ret.year  = CAST(uint16_t, yr + (mt <= 2));
        ret.month = CAST(uint8_t,  mt);
        ret.day   = CAST(uint8_t,  dy);
    }
    {
        /* set time */
        double  time = value_ - CAST(int, value_);
        if (time < 0) {
            time = -time;
        }
        if (time > 0) {
            ret.hour   = CAST(uint8_t, time * 24.0);
            time      -= CAST(double, ret.hour) / 24.0;
            ret.minute = CAST(uint8_t, time * 24.0 * 60.0);
            time      -= CAST(double, ret.minute) / (24.0 * 60.0);
            ret.second = CAST(uint8_t, time * 24.0 * 60.0 * 60.0);
        }
    }
_ret:
    RETURN(ret);
_err: {
        dtime_t  ret_err = NULL_DATE;
        ret = ret_err;
    }
    goto _ret;
} /* dtime_value */


/* Return only the time from the given object.                                */
PUBLIC dtime_t  get_time_dtime( const dtime_t* const  object_ ) {          /*C*/
    GO                                                            (UID(F6CFC2));
    dtime_t  ret = NULL_DATE;
    ret.hour     = object_->hour;
    ret.minute   = object_->minute;
    ret.second   = object_->second;
    RETURN(ret);
} /* get_time_dtime */


/* -------------------------------------------------------------------------- */
#if PLATFORM_WIN32                          /* Constructors: Windows-Specific */


/* Construct a date/time object from a FILETIME.                              */
PUBLIC dtime_t  dtime_FILETIME( const FILETIME_win* const  object_ ) {     /*C*/
    GO                                                            (UID(FA93D5));
    SYSTEMTIME_win  time = { 0 };
    OS_VERIFY(FileTimeToSystemTime_win(object_, &time), UID(EF5A19));
    {
        const dtime_t  ret = dtime_SYSTEMTIME(&time);
        RETURN(ret);
    }
} /* dtime_FILETIME */


/* Construct a date/time object from a SYSTEMTIME.                            */
PUBLIC dtime_t  dtime_SYSTEMTIME( const SYSTEMTIME_win* const  object_ ) { /*C*/
    GO                                                            (UID(F54C7C));
    dtime_t  ret = NULL_DATE;
    ret.year     = CAST(uint16_t, object_->wYear);
    ret.month    = CAST(uint8_t,  object_->wMonth);
    ret.day      = CAST(uint8_t,  object_->wDay);
    ret.hour     = CAST(uint8_t,  object_->wHour);
    ret.minute   = CAST(uint8_t,  object_->wMinute);
    ret.second   = CAST(uint8_t,  object_->wSecond);
    RETURN(ret);
} /* dtime_SYSTEMTIME */


#if defined __tagVARIANT
/* Construct a date/time object from a VARIANT.                               */
PUBLIC dtime_t  dtime_VARIANT( const VARIANT_win* const  object_ ) {       /*C*/
    GO                                                            (UID(F025F2));
    VARIANT_win  date_var = { 0 };
    if (object_->vt == VT_NULL_win || object_->vt == VT_EMPTY_win) {
        dtime_t  ret = dtime_null();
        RETURN(ret);
    }

    if (S_OK_win != VariantChangeType_win(
            &date_var, CAST(VARIANT_win*, &object_), 0, VT_DATE_win)) {

        dtime_t  ret = dtime_null();
        OS_WARN(_T("VariantChangeType_win()"), UID(EA4503));
        RETURN(ret);
    }
    {
        const dtime_t  ret = dtime_value(date_var.date);
        RETURN(ret);
    }
} /* dtime_VARIANT */
#endif                                                        /* __tagVARIANT */


#endif                                                      /* PLATFORM_WIN32 */


/* -------------------------------------------------------------------------- */
/* Methods/Properties:                                                        */


/* Return a formatted string. (e.g. specify "%HH:%NN:%SS")                    */
PUBLIC dtime_str_t  format_dtime(                                          /*M*/
    const dtime_t* const  object_,                                         /*-*/
    chars_t               format_ ) {                                      /*-*/
    GO                                                            (UID(FC4789));
#define LCASE( CHAR_ )                                            \
    (IS_LOWER_CASE((CHAR_)) ? (CHAR_) : (CHAR_) - 'A' + 'a')  /*#*/

#define UCASE( CHAR_ )                                            \
    (IS_UPPER_CASE((CHAR_)) ? (CHAR_) : (CHAR_) - 'a' + 'A')  /*#*/

#define TOCASE( CASE_, CHAR_ )                        \
    ((CASE_) == 'L' ? (LCASE(CHAR_)) :                \
     (CASE_) == 'U' ? (UCASE(CHAR_)) : (CHAR_));  /*#*/

    static const char_t  formats[] =
    { 'y', 'm', 'd', 'h', 'n', 's', 'w', 'a', 'p', '\0' };

    dtime_str_t  ret;
    chars_t      rd = format_;
    char_t*      wr = ret.cs;
    *wr = '\0';

    do {
        if (*rd == '%') {
            char_t   fmt  = '\0';    /* format specifier       */
            chars_t  frd  = rd + 1;  /* format reading pointer */
            size_t   flen = 0;       /* format length          */
            size_t   i    = 0;       /* format index           */

            do {
                fmt = formats[i];
                if (LCASE(*frd) == fmt) {
                    if (LCASE(*frd) == 'a' || LCASE(*frd) == 'p') {
                        flen = LCASE(frd[1]) == 'm' ? 2 : 1;
                    } else {
                        while (LCASE(*frd) == formats[i]) {
                            frd++;
                            flen++;
                        }
                    }
                    break;
                }
            } while (formats[i++] != '\0');
            frd = rd + 1;

            if (flen != 0) {
                int      val    = 0;
                chars_t  str    = NULL;
                bool     is_num = false;

                rd += flen;
                if (flen > 4) {
                    flen = 4;
                }

                switch (fmt) {
                        CASE('y', val = object_->year;   is_num = true);
                        CASE('h', val = object_->hour;   is_num = true);
                        CASE('n', val = object_->minute; is_num = true);
                        CASE('s', val = object_->second; is_num = true);
                        CASE('w', val = 0 /*TODO:WEEK*/; is_num = true);

                    case 'm':
                        val = object_->month;
                        is_num = flen == 1 || flen == 2;
                        if (flen == 3) {
                            str = _mth_name(val);
                        } else if (flen == 4) {
                            str = _month_name(val);
                        }
                        break;

                    case 'd':
                        val = object_->day;
                        is_num = flen == 1 || flen == 2;
                        if (flen >= 3) {
                            val = weekday_dtime(object_);
                            str = flen == 3 ?
                                  _wday_name(val) : _weekday_name(val);
                        }
                        break;

                    case 'a': {
                        is_num = false;
                        str = flen == 1 ? _T("A") : _T("AM");
                    }
                    break;

                    case 'p': {
                        is_num = false;
                        str = flen == 1 ? _T("P") : _T("PM");
                    }
                    break;

                    default:
                        ;
                }

                if (is_num) {
                    char_t  ch = CAST(char_t, val / 1000 + '0');
                    if ((flen == 1 && ch != '0') || flen == 4) {
                        *wr++ = ch;
                    }

                    if (val > 999) {
                        val -= val / 1000 * 1000;
                    }

                    ch = CAST(char_t, val / 100 + '0');
                    if ((flen == 1 && ch != '0') || flen == 4) {
                        *wr++ = ch;
                    }

                    if (val > 99) {
                        val -= val / 100 * 100;
                    }

                    ch = CAST(char_t, val / 10 + '0');
                    if (flen == 2 || flen == 4 || ch != '0') {
                        *wr++ = ch;
                    }

                    if (val > 9) {
                        val -= val / 10 * 10;
                    }

                    *wr++ = CAST(char_t, val + '0');
                } else {
                    const char_t  char_case =
                        IS_LOWER_CASE(*frd)   ? 'L' :
                        IS_UPPER_CASE(frd[1]) ? 'U' : '\0';
                    while (str && *str) {
                        *wr++ = TOCASE(char_case, *str);
                        str++;
                    }
                }
            } /* flen != 0 */
        } else {
            *wr++ = *rd;
        }
    } while (*rd++ != '\0');
    *wr = '\0';
    RETURN(ret);
} /* format_dtime */


/* Return true if a date has been assigned.                                   */
PUBLIC bool  has_date_dtime( const dtime_t* const  object_ ) {             /*P*/
    GO                                                            (UID(F97F67));
    const bool  ret = C_BOOL(object_->year  != 0  &&
                             object_->month != 0  &&
                             object_->day   != 0);
    RETURN(ret);
} /* has_date_dtime */


/* Return true if a time has been assigned.                                   */
PUBLIC bool  has_time_dtime( const dtime_t* const  object_ ) {             /*P*/
    GO                                                            (UID(F21D37));
    const bool  ret = C_BOOL(object_->hour   != 0  ||
                             object_->minute != 0  ||
                             object_->second != 0);
    RETURN(ret);
} /* has_time_dtime */


/* Return true if the date/time equals the specified value.                   */
PUBLIC bool  is_equal_dtime(                                               /*P*/
    const dtime_t* const  object_1_,                                       /*-*/
    const dtime_t* const  object_2_ ) {                                    /*-*/
    GO                                                            (UID(F03D47));
    const bool  ret = C_BOOL(object_1_->year   == object_2_->year    &&
                             object_1_->month  == object_2_->month   &&
                             object_1_->day    == object_2_->day     &&
                             object_1_->hour   == object_2_->hour    &&
                             object_1_->minute == object_2_->minute  &&
                             object_1_->second == object_2_->second);
    RETURN(ret);
} /* is_equal_dtime */


/* Return true if the date has not been assinged any value.                   */
PUBLIC bool  is_null_dtime( const dtime_t* const  object_ ) {              /*P*/
    GO                                                            (UID(FF9B2B));
    const bool  ret = C_BOOL(object_->year   == 0  &&
                             object_->month  == 0  &&
                             object_->day    == 0  &&
                             object_->hour   == 0  &&
                             object_->minute == 0  &&
                             object_->second == 0);
    RETURN(ret);
} /* is_null_dtime */


/* Return true if the values of all fields in the date are valid.             */
PUBLIC bool  is_valid_dtime( const dtime_t* const  object_ ) {             /*P*/
    GO                                                            (UID(F3D792));
    const bool  ret =
        object_->hour <= 23 && object_->minute <= 59 && object_->second <= 59 &&
        (
            (object_->year == 0 && object_->month == 0 && object_->day == 0)
            ||
            (object_->year  >= 100 && object_->year  <= 9999 &&
             object_->month >= 1   && object_->month <= 12   &&
             object_->day   >= 1   &&
             object_->day   <= days_in_month(object_->year, object_->month))
        );
    RETURN(ret);
} /* is_valid_dtime */


/* Return an ISO-8601 formatted string (yyyy-mm-dd or yyyy-mm-ddT0h:0m:0s).   */
PUBLIC dtime_str_t  iso8601_dtime( const dtime_t* const  object_ ) {       /*M*/
    GO                                                            (UID(F85394));
    /* (maximum length = 20 characters: 0000-00-00T00:00:00\0) */
#define BUF_SIZE  20

    /* prepare and clear the buffer */
    char_t  buf[BUF_SIZE] = { '\0' };

    /* date-only format */
    if ((object_->hour + object_->minute + object_->second) == 0) {
        SNPRINTF_T(buf, BUF_SIZE, _T("%04u-%02u-%02u"),
                   object_->year, object_->month, object_->day);
    } else { /* date and time format */
        SNPRINTF_T(buf, BUF_SIZE, _T("%04u-%02u-%02uT%02u:%02u:%02u"),
                   object_->year, object_->month,  object_->day,
                   object_->hour, object_->minute, object_->second);
    }

    {
        dtime_str_t  ret;
        CLEAR(ret);
        RETURN(ret);
    }
#undef BUF_SIZE
} /* iso8601_dtime */


/* Return a floating-point number based on given object. (date-only)          */
PUBLIC double  value_date( const dtime_t* const  object_ ) {               /*P*/
    GO                                                            (UID(F624ED));
    dtime_t  date = NULL_DATE;
    date.year     = object_->year;
    date.month    = object_->month;
    date.day      = object_->day;
    {
        const double  ret = value_dtime(&date);
        RETURN(ret);
    }
} /* value_date */


/* Return a floating-point number based on given object.                      */
PUBLIC double  value_dtime( const dtime_t* const  object_ ) {              /*P*/
    GO                                                            (UID(FCD74C));
    double        ret  = 0;
    double        days = 0;
    int           yr   = object_->year;
    int           mt   = object_->month;
    int           dy   = object_->day;
    const double  time = (1.0 / 24.0 * object_->hour) +
                         (1.0 / 24.0 / 60.0 * object_->minute) +
                         (1.0 / 24.0 / 60.0 / 60.0 * object_->second);

    if (yr == 0 && mt == 0 && dy == 0) {
        yr = 1899;
        mt = 12;
        dy = 30;
    }
    yr -= mt <= 2;

    {
        const int       era = (yr >= 0 ? yr : yr - 399) / 400;
        const unsigned  yoe = CAST(unsigned, yr - era * 400);  /* 0..399 */
        const unsigned  doy =
            (153 * (mt + (mt > 2 ? -3 : 9)) + 2) / 5 + dy - 1;  /* 0..365 */
        const unsigned  doe =
            yoe * 365 + yoe / 4 - yoe / 100 + doy;  /* 0..146096 */
        days = CAST(int, era * 146097 + CAST(int, doe) - 719468);
        days += 25569;
        ret = days >= 0 ? (days + time) : (days - time);
    }
    RETURN(ret);
} /* value_dtime */


/* Return the day of week num. from the specified date/time object, ranging   */
/* from 1 for Monday to 7 for Sunday, or 0 if the given date is not valid.    */
PUBLIC uint8_t  weekday_dtime( const dtime_t* const  object_ ) {           /*P*/
    GO                                                            (UID(F20801));
    const uint8_t ret = weekday(object_->year, object_->month, object_->day);
    RETURN(ret);
} /* weekday_dtime */


/* -------------------------------------------------------------------------- */
/* Functions:                                                                 */


/* Return the number of days in the specified year and month.                 */
/* (If year is less than 1 greater than 9999, returns 0.)                     */
PUBLIC uint8_t  days_in_month(                                             /*F*/
    const int  year_,                                                      /*-*/
    const int  month_ ) {                                                  /*-*/
    GO                                                            (UID(F2B10E));
    uint8_t   ret = 0;
    uint16_t  yr  = CAST(uint16_t, year_ < 100 ? 1900 + year_ :
                         year_           <  50 ? 2000 + year_ : year_);

    if (yr > 9999 || month_ < 1 || month_ > 12) {
        goto _end;
    }

    /* A year is a leap year if it is divisible by 4 but not by 100,   */
    /* unless it is also divisible by 400, which makes it a leap year. */
    if (month_ == 2 && (((yr % 4 == 0) && (yr % 100 != 0)) || (yr % 400 == 0))) {
        ret = 29;
    } else {
        static const uint8_t  mdays[12] =
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        ret = mdays[month_ - 1];
    }
_end:
    RETURN(ret);
} /* days_in_month */


/* Return a human-friendly time interval string, given the number of seconds. */
PUBLIC dtime_str_t  timespan( const int  seconds_ ) {                      /*F*/
    GO                                                            (UID(F7BD41));
    static struct  t {
        int  seconds;
        chars_t  one;
        chars_t  many;
    }
    const  units[5] = {
        {  1,               _T("second"), _T("seconds"), },
        { 60,               _T("minute"), _T("minutes"), },
        { 60 * 60,          _T("hour"),   _T("hours"),   },
        { 60 * 60 * 24,     _T("day"),    _T("days"),    },
        { 60 * 60 * 24 * 7, _T("week"),   _T("weeks"),   },
    };

    dtime_str_t  ret;
    char_t*      wr     = ret.cs;
    int          remain = seconds_;
    int          parts  = 1;
    int          i;

    for (i = 4; i >= 0 && parts < 3; i--) {
        int      qty = remain / units[i].seconds;
        chars_t  rd  = qty == 1 ? units[i].one : units[i].many;

        remain -= qty * units[i].seconds;

        if (qty != 0 || (seconds_ == 0 && i == 0)) {
            bool  lead = false;
            int   n    = 10000;

            while (n) {
                const char_t  ch = CAST(char_t, qty / n + '0');
                if (ch != '0' || lead || (seconds_ == 0 && n == 1)) {
                    *wr++ = ch;
                    lead = true;
                }

                if (qty > (n - 1)) {
                    qty -= qty / n * n;
                }

                n /= 10;
            }

            if (lead) {
                *wr++ = ' ';
            }

            while (*rd) {
                *wr++ = *rd++;
            }

            *wr++ = ' ';
            parts++;
        }
    }
    *--wr = '\0';
    RETURN(ret);
} /* timespan */


/* Return the day of week num. from the given date, ranging from 1 for Monday */
/* to 7 for Sunday (ISO-8601 weekday), or 0 if the given date is not valid.   */
PUBLIC uint8_t  weekday(                                                   /*F*/
    const int  year_,                                                      /*-*/
    const int  month_,                                                     /*-*/
    const int  day_ ) {                                                    /*-*/
    GO                                                            (UID(F3B2E6));
    uint8_t  ret = 0;

    if (year_ < 0 || year_ > 9999) {
        WARN(_T("Bad year number."),  UID(EF904C));
        goto _err;
    }
    if (month_ < 1 || month_ > 12) {
        WARN(_T("Bad month number."), UID(E34F29));
        goto _err;
    }
    if (day_ < 1 || day_ > 31) {
        WARN(_T("Bad day number."),   UID(EBA84C));
        goto _err;
    }

    {
        const int   year = year_ < 100 ? 1900 + year_ :
                           year_ <  50 ? 2000 + year_ : year_;
        dtime_t     dt   = date_init(year, month_, day_);
        const int   sn   = CAST(int, value_dtime(&dt)) + 657434 + 5;
        /* The anchor date is the first Sunday before Friday 0100-01-01 ^ */
        /* 657434 is the number of days between 0100-01-01 and 1899-12-30 */
        ret = CAST(uint8_t, sn % 7);
        if (ret == 0) {
            ret = 7;
        }
    }
_ret:
    RETURN(ret);
_err:
    ret = 0;
    goto _ret;
} /* weekday */


/* -------------------------------------------------------------------------- */
#if PLATFORM_WIN32                             /* Functions: Windows-Specific */


/* Return a FILETIME based on the given date/time object.                     */
PUBLIC FILETIME_win  FILETIME_dtime( const dtime_t* const  object_ ) {     /*M*/
    GO                                                            (UID(F0890C));
    SYSTEMTIME_win  stime = SYSTEMTIME_dtime(object_);
    FILETIME_win    ret   = { 0 };
    OS_VERIFY(SystemTimeToFileTime_win(&stime, &ret), UID(E94FC9));
    RETURN(ret);
} /* FILETIME_dtime */


/* Return a FILETIME based on given numeric year, month, day, hour, etc.      */
PUBLIC FILETIME_win  FILETIME_set(                                         /*F*/
    const int  year_,                                                      /*-*/
    const int  month_,                                                     /*-*/
    const int  day_,                                                       /*-*/
    const int  hour_,                                                      /*-*/
    const int  minute_,                                                    /*-*/
    const int  second_ ) {                                                 /*-*/
    GO                                                            (UID(F260F4));
    FILETIME_win    ret  = { 0 };
    SYSTEMTIME_win  time =
        SYSTEMTIME_set(year_, month_, day_, hour_, minute_, second_);
    OS_VERIFY(SystemTimeToFileTime_win(&time, &ret), UID(E8ED0F));
    RETURN(ret);
} /* FILETIME_set */


/* Return a SYSTEMTIME based on the given date/time object.                   */
PUBLIC SYSTEMTIME_win  SYSTEMTIME_dtime( const dtime_t* const  object_ ) { /*M*/
    GO                                                            (UID(F36752));
    SYSTEMTIME_win  ret = { 0 };
    ret.wYear           = object_->year;
    ret.wMonth          = object_->month;
    ret.wDay            = object_->day;
    ret.wDayOfWeek      = CAST(WORD_win, weekday_dtime(object_));
    ret.wHour           = object_->hour;
    ret.wMinute         = object_->minute;
    ret.wSecond         = object_->second;
    ret.wMilliseconds   = 0;
    RETURN(ret);
} /* SYSTEMTIME_dtime */


/* Return a SYSTEMTIME based on given numeric year, month, day, hour, etc.    */
PUBLIC SYSTEMTIME_win  SYSTEMTIME_set(                                     /*F*/
    const int  year_,                                                      /*-*/
    const int  month_,                                                     /*-*/
    const int  day_,                                                       /*-*/
    const int  hour_,                                                      /*-*/
    const int  minute_,                                                    /*-*/
    const int  second_ ) {                                                 /*-*/
    GO                                                            (UID(F22C4B));
    SYSTEMTIME_win  ret = { 0 };
    ret.wYear           = CAST(uint16_t, year_);
    ret.wMonth          = CAST(uint8_t,  month_);
    ret.wDay            = CAST(uint8_t,  day_);
    ret.wDayOfWeek      = CAST(WORD_win, weekday(year_, month_, day_));
    ret.wHour           = CAST(uint8_t, hour_);
    ret.wMinute         = CAST(uint8_t, minute_);
    ret.wSecond         = CAST(uint8_t, second_);
    RETURN(ret);
} /* SYSTEMTIME_set */

#endif                                                      /* PLATFORM_WIN32 */


/* -------------------------------------------------------------------------- */

/* TODO: create: dtime_t  minute_offset_dtime( const int  offset_ ); */
/* TODO: libdtime.c: should not depend on str_t */
/* TODO: PUBLIC dtime_t  date_zone_now( const int  tzone_ ); */            /*C*/

END_NAMESPACE                                                             /*c_*/
#endif                                                                   /*eof*/
