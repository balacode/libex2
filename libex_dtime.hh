// -------------------------------------------------------------------------- //
// (c) Ali Silvester Balarabe                                [libex_dtime.hh] //
// -------------------------------------------------------------------------- //

#if !defined __cplusplus
#error "Non-C++ code shouldn't include libex_dtime.hh"
#endif

#if !defined INCLUDED_LIBEX_DTIME_HH
#define      INCLUDED_LIBEX_DTIME_HH

#include "libex.h"
#include "libex_dtime.h"
#include "libex_macro.h"
#include "libex_string.hh"

#if LX_PLATFORM_WIN32
#include "libex_win32.h"
#endif

#define _LX_THIS  LX_SCAST(lx_c::lx_dtime_t&, *this)

// -------------------------------------------------------------------------- //
namespace  lx {

class DateTime : public lx_c::lx_dtime_t {

public:  // Methods: Static

    // Return the current local date and time,
    inline static DateTime  now( ) {                                         //M
        return lx_c::lx_dtime_now();
    }

    inline static DateTime  null( ) {                                        //M
        return lx_c::lx_dtime_null();
    }

    // Return the day of week num. from the specified date/time object, ranging
    // from 1 for Monday to 7 for Sunday, or 0 if the given date is not valid.
    inline static int  dayOfWeek(                                            //M
        const int  year_,
        const int  month_,
        const int  day_) {
        return lx_c::lx_weekday(year_, month_, day_);
    }

    // Return the number of days in the specified year and month.
    // (If year is less than 1 greater than 9999, returns 0.)
    inline static int  daysInMonth(                                          //M
        const int  year_,
        const int  month_) {
        return lx_c::lx_days_in_month(year_, month_);
    }

public:  // Constructors / Destructor:

    inline  DateTime( const lx_c::lx_dtime_t&  value_ ) {                    //C
        _LX_THIS = value_;
    }

    // Construct the object from explicit date/time values.
    inline  DateTime(                                                        //C
        const int  year_   = 0,
        const int  month_  = 0,
        const int  day_    = 0,
        const int  hour_   = 0,
        const int  minute_ = 0,
        const int  second_ = 0) {
        _LX_THIS = lx_c::lx_dtime_init(year_, month_, day_,
                                       hour_, minute_, second_);
    }

    // Construct the object from the value of another DateTime object.
    inline  DateTime( const DateTime&  value_ ) {                            //C
        _LX_THIS = value_;
    }

    // Construct the object from a floating-point number.
    inline  DateTime( const double  value_ ) {                               //C
        _LX_THIS = lx_c::lx_dtime_value(value_);
    }

    // Construct the object from a text string.
    inline  DateTime( const std::tstring&  text_ ) {                         //C
        _LX_THIS = lx_c::lx_dtime_chars(text_.c_str());
    }

#if LX_PLATFORM_WIN32
    inline  DateTime( FILETIME_win&  value_ ) {                              //C
        _LX_THIS = lx_c::lx_dtime_FILETIME(&value_);
    }

    inline  DateTime( SYSTEMTIME_win&  value_ ) {                            //C
        _LX_THIS = lx_c::lx_dtime_SYSTEMTIME(&value_);
    }
#endif

    // Destructor
    inline virtual  ~DateTime( )  { }                                        //D

public:  // Operators:

    // Return the date/time as a floating point number (The integer part
    // represents the date, while the fractional part represents the time).
    inline  operator double( ) const {                                       //O
        return lx_c::lx_value_dtime(this);
    }

    inline  operator lx_c::lx_dtime_t( ) const {                             //O
        return lx_c::lx_dtime_t(*this);
    }

    // Change this DateTime to the value of another DateTime.
    inline DateTime&  operator = ( const DateTime&  value_ ) {               //O
        _LX_THIS = value_;
        return *this;
    }

    // Return true if the date/time equals the specified value.
    inline bool  operator == ( const DateTime&  value_ ) const {             //O
        return LX_CPP_BOOL(lx_is_equal_dtime(this, &value_));
    }

    // Return true if the date/time does not equal the specified value.
    inline bool  operator != ( const DateTime&  value_ ) const {             //O
        return !LX_CPP_BOOL(lx_is_equal_dtime(this, &value_));
    }

public:  // Properties: Informative

    // Return true if the date has not been assinged any value.
    inline bool  isNull( ) const {                                           //P
        return LX_CPP_BOOL(lx_is_null_dtime(this));
    }

    // Return true if the date/time is valid
    inline bool  isValid( ) const {                                          //P
        return LX_CPP_BOOL(lx_is_valid_dtime(this));
    }

    // Return true if a date has been assigned.
    inline bool  hasDate( ) const {                                          //P
        return LX_CPP_BOOL(lx_has_date_dtime(this));
    }

    // Return true if a time has been assigned.
    inline bool  hasTime( ) const {                                          //P
        return LX_CPP_BOOL(lx_has_time_dtime(this));
    }

    // Return the day of week.
    inline int  dayOfWeek( ) const {                                         //P
        return lx_weekday_dtime(this);
    }

    // Return only the date from this object.
    inline DateTime  date( ) const {                                         //P
        return lx_c::lx_date_dtime(this);
    }

    // Return only the time from this object.
    inline DateTime  time( ) const {                                         //P
        return lx_c::lx_get_time_dtime(this);
    }

    // Return a DateTime object offset by the specified number of days.
    inline DateTime  dayOffset( const int  days_ ) const {                   //P
        return lx_c::lx_day_offset_dtime(this, days_);
    }

    // Return an ISO-8601 formatted string (yyyy-mm-dd or yyyy-mm-ddT0h:0m:0s).
    inline std::tstring  iso8601( ) const {                                  //P
        return lx_iso8601_dtime(this).cs;
    }

    // Return a formatted string (e.g. specify "%HH:%NN:%SS")
    inline std::tstring  format( const std::tstring&  format_ ) const {      //M
        return lx_c::lx_format_dtime(this, format_.c_str()).cs;
    }

    // TODO: DateTime minuteOffset(const int  offset_);

};                                                             //class  DateTime

#undef _LX_THIS

}                                                                        //ns lx
#endif                                                                     //eof
