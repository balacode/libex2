/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                    [libex_language.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_language_.h"
#if defined INCLUDED_LIBEX_LANGUAGE_H

#include "libex_.h"
#include "libex_call_.h"
#include "libex_const_.h"
#include "libex_stringc_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif

/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


PUBLIC language_enum  language_id( chars_t  language_code_ ) {             /*F*/
    GO                                                            (UID(F9BEFE));
    language_enum  ret = LANGUAGE_UNDEFINED;

    if (begins3T(language_code_, _T("EN"), IGNORE_CASE)) {
        ret = LANGUAGE_EN;
    }
    RETURN(ret);
} /* language_id */


/* -------------------------------------------------------------------------- */
/* Functions: Date and time-Related                                           */


PUBLIC chars_t  lang_day_name(                                             /*F*/
    language_enum  language_id_,                                           /*-*/
    const int      day_number_ ) {                                         /*-*/
    GO                                                            (UID(F828B5));
    chars_t  ret = BLANK;

    if (language_id_ == LANGUAGE_EN &&
        day_number_ >= 1 && day_number_ <= 7) {
        static chars_t  list[7] = {
            _T("Monday"),
            _T("Tuesday"),
            _T("Wednesday"),
            _T("Thursday"),
            _T("Friday"),
            _T("Saturday"),
            _T("Sunday")
        };

        if (day_number_ >= 1 && day_number_ <= 7) {
            ret = list[day_number_ - 1];
        }
    }
    RETURN(ret);
} /* lang_day_name */


PUBLIC chars_t  lang_day_name_short(                                       /*F*/
    language_enum  language_id_,                                           /*-*/
    const int      day_number_ ) {                                         /*-*/
    GO                                                            (UID(FB5859));
    if (day_number_ < 1 || day_number_ > 7) {
        RETURN(BLANK);
    }

    if (language_id_ == LANGUAGE_EN) {
        static chars_t  list[7] = {
            _T("Mon"), _T("Tue"), _T("Wed"), _T("Thu"),
            _T("Fri"), _T("Sat"), _T("Sun")
        };

        if (day_number_ >= 1 && day_number_ <= 7) {
            chars_t  ret = list[day_number_ - 1];
            RETURN(ret);
        }
    }
    RETURN(BLANK);
} /* lang_day_name_short */


PUBLIC chars_t  lang_month_name(                                           /*F*/
    language_enum  language_id_,                                           /*-*/
    const int      month_number_ ) {                                       /*-*/
    GO                                                            (UID(F37AF7));
    if (month_number_ < 1 || month_number_ > 12) {
        RETURN(BLANK);
    }

    if (language_id_ == LANGUAGE_EN) {
        static chars_t  list[12] = {
            _T("January"),
            _T("February"),
            _T("March"),
            _T("April"),
            _T("May"),
            _T("June"),
            _T("July"),
            _T("August"),
            _T("September"),
            _T("October"),
            _T("November"),
            _T("December")
        };

        if (month_number_ >= 1 && month_number_ <= 12) {
            chars_t  ret = list[month_number_ - 1];
            RETURN(ret);
        }
    }
    RETURN(BLANK);
} /* lang_month_name */


PUBLIC chars_t  lang_month_name_short(                                     /*F*/
    language_enum  language_id_,                                           /*-*/
    const int      month_number_ ) {                                       /*-*/
    GO                                                            (UID(F1D1AF));
    if (month_number_ < 1 || month_number_ > 12) {
        RETURN(BLANK);
    }

    if (language_id_ == LANGUAGE_EN) {
        static chars_t  list[12] = {
            _T("Jan"), _T("Feb"), _T("Mar"),
            _T("Apr"), _T("May"), _T("Jun"),
            _T("Jul"), _T("Aug"), _T("Sep"),
            _T("Oct"), _T("Nov"), _T("Dec")
        };

        if (month_number_ >= 1 && month_number_ <= 12) {
            chars_t  ret = list[month_number_ - 1];
            RETURN(ret);
        }
    }
    RETURN(BLANK);
} /* lang_month_name_short */


PUBLIC chars_t  lang_time_am( language_enum  language_id_ ) {              /*F*/
    GO                                                            (UID(F47051));
    if (language_id_ == LANGUAGE_EN) {
        RETURN(_T("am"));
    }
    RETURN(BLANK);
} /* lang_time_am */


PUBLIC chars_t  lang_time_am_short( language_enum  language_id_ ) {        /*F*/
    GO                                                            (UID(F9E2F8));
    if (language_id_ == LANGUAGE_EN) {
        RETURN(_T("a"));
    }
    RETURN(BLANK);
} /* lang_time_am_short */


PUBLIC chars_t  lang_time_pm( language_enum  language_id_ ) {              /*F*/
    GO                                                            (UID(FD04CD));
    if (language_id_ == LANGUAGE_EN) {
        RETURN(_T("pm"));
    }
    RETURN(BLANK);
} /* lang_time_pm */


PUBLIC chars_t  lang_time_pm_short( language_enum  language_id_ ) {        /*F*/
    GO                                                            (UID(F6F2B7));
    if (language_id_ == LANGUAGE_EN) {
        RETURN(_T("p"));
    }
    RETURN(BLANK);
} /* lang_time_pm_short */


/* -------------------------------------------------------------------------- */
/* Functions: Number-Related                                                  */


PUBLIC chars_t  lang_decimal_point( language_enum  language_id_ ) {        /*F*/
    GO                                                            (UID(FBCDF9));
    if (language_id_ == LANGUAGE_EN) {
        RETURN(_T("."));
    }
    RETURN(BLANK);
} /* lang_decimal_point */


PUBLIC chars_t  lang_digit_group_separator( language_enum
        language_id_ ) { /*F*/
    GO                                                            (UID(F3B228));
    if (language_id_ == LANGUAGE_EN) {
        RETURN(_T(","));
    }
    RETURN(BLANK);
} /* lang_digit_group_separator */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
