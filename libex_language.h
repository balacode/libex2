/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                    [libex_language.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_LANGUAGE_H
#define      INCLUDED_LIBEX_LANGUAGE_H

#include "libex_stringc.h"

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

/* Provides functions that return language-specific strings and formats.      */

typedef enum  _lx_language_enum {
    LX_LANGUAGE_UNDEFINED = 0,                            /* lx_language_enum */
    LX_LANGUAGE_EN        = 1                             /* lx_language_enum */
}
lx_language_enum;                                                       /*enum*/

/* returns a language ID given a language code.                               */
/* E.g. 'EN', 'EN-US', 'EN-UK'                                                */
LX_PUBLIC lx_language_enum  lx_language_id( lx_chars_t  language_code_ );  /*F*/

/* -------------------------------------------------------------------------- */
/* Functions: Date and time-Related                                           */

/* return the name of a weekday, given a number,                              */
/* starting with 1 for 'Monday'. If the given number                          */
/* is out of range, returns a blank string.                                   */
LX_PUBLIC lx_chars_t  lx_lang_day_name(                                    /*F*/
    lx_language_enum  language_id_,                                        /*-*/
    const int         day_number_ );                                       /*-*/

/* return the short  weekday name, given a number, starting with 1 for 'Mon'  */
/* If the given number is out of range, returns a blank string.               */
LX_PUBLIC lx_chars_t  lx_lang_day_name_short(                              /*F*/
    lx_language_enum  language_id_,                                        /*-*/
    const int         day_number_ );                                       /*-*/

/* return the name of a month, given a number,                                */
/* starting with 1 for 'January'.                                             */
/* If the given number is out of range, returns a blank string.               */
LX_PUBLIC lx_chars_t  lx_lang_month_name(                                  /*F*/
    lx_language_enum  language_id_,                                        /*-*/
    const int         month_number_ );                                     /*-*/

/* return the short  month name, given a number, starting with 1 for 'Jan'.   */
/* If the given number is out of range, returns a blank string.               */
LX_PUBLIC lx_chars_t  lx_lang_month_name_short(                            /*F*/
    lx_language_enum  language_id_,                                        /*-*/
    const int         month_number_ );                                     /*-*/

/* return the text string for AM time: 'am' for 'EN' language.                */
LX_PUBLIC lx_chars_t  lx_lang_time_am( lx_language_enum  language_id_ );   /*F*/

/* return the short  text for AM time: 'a' for 'EN' language.                 */
LX_PUBLIC lx_chars_t  lx_lang_time_am_short(                               /*F*/
    lx_language_enum  language_id_ );                                      /*-*/

/* return the text string for PM time: 'pm' for 'EN' language.                */
LX_PUBLIC lx_chars_t  lx_lang_time_pm( lx_language_enum  language_id_ );   /*F*/

/* return the short  text for PM time: 'p' for 'EN' language.                 */
LX_PUBLIC lx_chars_t  lx_lang_time_pm_short(                               /*F*/
    lx_language_enum  language_id_ );                                      /*-*/

/* -------------------------------------------------------------------------- */
/* Functions: Number-Related                                                  */

/* return the decimal point character.                                        */
LX_PUBLIC lx_chars_t  lx_lang_decimal_point(                               /*F*/
    lx_language_enum  language_id_ );                                      /*-*/

/* return the digit group separator.                                          */
LX_PUBLIC lx_chars_t  lx_lang_digit_group_separator(                       /*F*/
    lx_language_enum  language_id_ );                                      /*-*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
