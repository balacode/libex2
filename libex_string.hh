// -------------------------------------------------------------------------- //
// (c) Ali Silvester Balarabe                 [libex_string.hh] [cat:strings] //
// -------------------------------------------------------------------------- //

#if !defined __cplusplus
#error "Non-C++ code shouldn't include libex_string.hh"
#endif

#if !defined INCLUDED_LIBEX_STRING_HH
#define      INCLUDED_LIBEX_STRING_HH

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#include "libex_config.h"

#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4005)  // W:L1 'NAME': macro redefinition
#pragma warning (disable:4668)  // W:L4 'SYMBOL' is not defined as a p. macro
#pragma warning (disable:4820)  // W:L4 'N' bytes padding added after NAME
#endif

#if LX_PLATFORM_WIN32 && !defined _WINDOWS_
#include <wtypes.h>  // BSTR_win, etc.
#include "libex_win32.h"
#endif                                // LX_PLATFORM_WIN32 && !defined _WINDOWS_

#include <iomanip>
#include <limits>
#include <locale>
#include <sstream>
#include <string>

#if defined _MSC_VER
#pragma warning (pop)
#endif

#include "libex.h"
#include "libex_const.h"
#include "libex_macro.h"
#include "libex_string_class.h"
#include "libex_stringc.h"
#include "libex_variant_functions.h"

// -------------------------------------------------------------------------- //

#if defined UNICODE || defined _UNICODE
#define tofstream       wofstream
#define tostringstream  wostringstream
#define tstring         wstring
#else
#define tofstream       ofstream
#define tostringstream  ostringstream
#define tstring         string
#endif

// -------------------------------------------------------------------------- //
namespace  lx {

using std::string;
using std::wstring;

// Constants
static const tstring&  Blank               = _T("");
static const tstring&  DefaultDelimiter    = _T(",");
static const tstring&  DefaultQuote        = _T("\"");
static const tstring&  DefaultQuoteReplace = _T("\"\"");
static const tstring&  Whitespaces         = _T(" \a\b\f\n\r\t\v");

// Text comparison options
static const bool  IgnoreCase = true;
static const bool  MatchCase  = false;

// Limits
static const size_t  MaxLength = std::numeric_limits<size_t>::max();
static const size_t  NoMatch   = tstring::npos;

// -------------------------------------------------------------------------- //
// Common Arguments:

// ignoreCase_: If false (default), applies a case-sensitive comparison.
//              If true, applies a case-insensitive comparison.

// -------------------------------------------------------------------------- //
// Conversion Functions Used by Other Conversion functions

inline string  str_wstr( const wstring&  string_ ) {                         //F
    char*   ptr = lx_c::lx_utf8_of_wide(string_.c_str());
    string  ret (ptr);
    lx_c::lx_freeA(&ptr);
    return ret;
} // str_wstr

inline tstring  tstr_new_chars_t( lx_new_chars_t  string_ ) {                //F
    tstring  ret (string_);
    lx_c::lx_freeT(&string_);
    return ret;
}

// Return the position of find_ within string_, or NoMatch if it is not found.
//
// offset_:  Specifies the starting position in string_. 0 by default.
// fromEnd_: set to true to begin the search from the end of this text.
inline size_t  find(                                                         //F
    const tstring&  string_,                                                 //-
    const tstring&  find_,                                                   //-
    const size_t    offset_     = 0,                                         //-
    const bool      ignoreCase_ = false,                                     //-
    const bool      fromEnd_    = false) {                                   //-
    const size_t ret = lx_c::lx_findT(string_.c_str(), find_.c_str(),
                                      offset_, LX_C_BOOL(ignoreCase_), fromEnd_,
                                      string_.size(), find_.size());
    return ret == LX_NONE ? tstring::npos : ret;
} // find

// -------------------------------------------------------------------------- //

// This function will be redundant when all functions use libex_stringc.h ``
inline tstring  tstr_new_str_t( lx_c::lx_new_str_t  string_ ) {              //F
    tstring  ret (string_.cs);
    lx_c::lx_freeS(&string_);
    return ret;
}

inline string  str_tstr( const tstring&  string_ ) {                         //F
#if defined UNICODE || defined _UNICODE
    return str_wstr(string_);
#else
    return string_;
#endif
} // str_tstr

inline wstring  wstr_str( const string&  string_ ) {                         //F
    return wstring (string_.begin(), string_.end());
}

inline wstring  wstr_tstr( const tstring&  string_ ) {                       //F
#if defined UNICODE || defined _UNICODE
    return string_;
#else
    return wstr_str(string_);
#endif
} // wstr_tstr

// -------------------------------------------------------------------------- //
// String Conversion Functions

// Convert a double  number to text string.
// You can specify formats in format_: e.g. "0.1" for a number with 1dp.
inline tstring  tstr_double(                                                 //F
    const double    value_,                                                  //-
    const tstring&  format_ = Blank) {                                       //-
    return tstr_new_str_t(lx_c::lx_S_double(value_, format_.c_str()));
}

// Convert unsigned long to string / wstring.
inline tstring  tstr_uint(                                                   //F
    const unsigned long  value_,                                             //-
    const tstring&       format_ = Blank) {                                  //-
    return tstr_new_str_t(lx_c::lx_S_uint(value_, format_.c_str()));
}

inline unsigned int  uint_tstr( const tstring&  string_ ) {                  //F
#if defined UNICODE || defined _UNICODE
    return unsigned int (std::strtoul(str_tstr(string_).c_str(), nullptr, 0));
#else
    return unsigned int (std::strtoul(string_.c_str(), nullptr, 0));
#endif
} // uint_tstr

inline tstring  tstr_c_str( const char*  text_ ) {                           //F
#if defined UNICODE || defined _UNICODE
    return wstr_str(text_);
#else
    return text_;
#endif
} // tstr_c_str

inline tstring  tstr_c_str( const wchar_t*  text_ ) {                        //F
#if defined UNICODE || defined _UNICODE
    return text_;
#else
    return str_wstr(text_);
#endif
} // tstr_c_str

inline string  utf8_str( const string&  string_ ) {                          //F
    return string_;
}

inline string  utf8_str( const wstring&  string_ ) {                         //F
    lx_new_bchars_t  chars = lx_c::lx_utf8_of_wide(string_.c_str());
    string           ret   = chars;
    lx_c::lx_freeA(&chars);
    return ret;
} // utf8_str

inline tstring  tstr_VARIANT( const VARIANT&  variant_ ) {                   //F
    return tstr_new_chars_t(lx_c::lx_T_of_var(variant_));
}

inline tstring  tstr_BSTR( const BSTR&  bstr_ ) {                            //F
    return tstr_new_chars_t(lx_c::lx_T_bstr( bstr_ ));
}

inline wstring  wstr_int( int  value_ ) {
    std::wostringstream  ret;
    ret << value_;
    return ret.str();
}

inline tstring  tstr_int( int  value_ ) {
    std::tostringstream  ret;
    ret << value_;
    return ret.str();
}

// -------------------------------------------------------------------------- //

// Return a string that repeats the given string_ count_ number of times,
// up to the maximum length (maxLen_).
//
// maxLen_: maximum length of the resulting text,
//          in characters. Unlimited by default.
//
// note: either count_ or maxLen_ must be specified. < check ``

inline static tstring  repeat(                                               //F
    const tstring&  string_,                                                 //-
    const int       count_,                                                  //-
    const int       maxLen_ = MaxLength ) {                                  //-
    return tstr_new_chars_t(lx_c::lx_T_repeat(string_.c_str(), count_, maxLen_));
} // repeat

inline static tstring  formatNumeric(                                        //F
    const tstring&   string_,                                                //-
    const int        decimalPlaces_      = 2,                                //-
    const int        groupDigits1_       = 3,                                //-
    const int        groupDigits2_       = 3,                                //-
    const int        groupDigits3_       = 3,                                //-
    const lx_char_t  decimalPointChar_   = _T('.'),                          //-
    const lx_char_t  groupDelimiterChar_ = _T(',') ) {                       //-
    return (tstr_new_str_t(lx_c::lx_S_formatNumeric(
                               string_.c_str(), decimalPlaces_,
                               groupDigits1_, groupDigits2_,
                               groupDigits3_, decimalPointChar_,
                               groupDelimiterChar_)));
} // formatNumeric

// Replace contents of this string with a format string
// containing up to 10 different substrings, numbered from
// %0 to %9, which are replaced in format_.
inline tstring  format(                                                      //F
    const tstring&  format_,                                                 //-
    const tstring&  value0_ = Blank,                                         //-
    const tstring&  value1_ = Blank,                                         //-
    const tstring&  value2_ = Blank,                                         //-
    const tstring&  value3_ = Blank,                                         //-
    const tstring&  value4_ = Blank,                                         //-
    const tstring&  value5_ = Blank,                                         //-
    const tstring&  value6_ = Blank,                                         //-
    const tstring&  value7_ = Blank,                                         //-
    const tstring&  value8_ = Blank,                                         //-
    const tstring&  value9_ = Blank ) {                                      //-
    std::tostringstream  ret;
    size_t  prev_pos = 0;
    size_t  pos = tstring::npos;
    while ((pos = format_.find('%', prev_pos)) != tstring::npos) {
        const size_t  arg = pos < format_.size() - 1 ? format_[pos + 1] - '0'
                            : tstring::npos;

        const tstring&  repl = arg == 0 ? value0_ :
                               arg == 1 ? value1_ :
                               arg == 2 ? value2_ :
                               arg == 3 ? value3_ :
                               arg == 4 ? value4_ :
                               arg == 5 ? value5_ :
                               arg == 6 ? value6_ :
                               arg == 7 ? value7_ :
                               arg == 8 ? value8_ :
                               arg == 9 ? value9_ : Blank;

        ret << format_.substr(prev_pos, pos - prev_pos) << repl;
        prev_pos = pos + 2;
    }
    ret << format_.substr(prev_pos);
    return ret.str();
} // format

// Replace all occurrences of find_ within string_ with replace_.
inline tstring  replace(                                                     //F
    const tstring&  string_,                                                 //-
    const tstring&  find_,                                                   //-
    const tstring&  replace_,                                                //-
    const bool      ignoreCase_ = false ) {                                  //-
    std::tostringstream  ret;
    size_t               prev_pos = 0,  pos = tstring::npos;
    do {
        pos = find(string_, find_, prev_pos, ignoreCase_);
        if (pos != tstring::npos) {
            ret << string_.substr(prev_pos, pos - prev_pos) << replace_;
            prev_pos = pos + find_.size();
        }
    } while (pos != tstring::npos);

    if (prev_pos < string_.size()) {
        ret << string_.substr(prev_pos);
    }

    return ret.str();

    // using C function:
    // return tstr_new_chars_t(lx_c::lx_T_replace(string_.c_str(), find_.c_str(),
    //                                           replace_.c_str(),
    //                                           LX_C_BOOL(ignoreCase_)));

} // replace

inline void test_replace() {
    if (replace(_T("AAA"), _T("B"), _T("C")) != _T("AAA")) {
        __debugbreak();
    }

    if (replace(_T("1A2"), _T("A"), _T("B")) != _T("1B2")) {
        __debugbreak();
    }

    if (replace(_T("AAA"), _T("A"), _T("B")) != _T("BBB")) {
        __debugbreak();
    }

    if (replace(_T("x/user/projects/code"), _T("/"), _T("\\")) !=
        _T("x\\user\\projects\\code")) {
        __debugbreak();
    }
} // test_replace

inline tstring*  replaceIn(                                                  //F
    tstring*        string_,                                                 //-
    const tstring&  find_,                                                   //-
    const tstring&  replace_,                                                //-
    const bool      ignoreCase_ = false ) {                                  //-
    *string_ = replace(*string_, find_, replace_, ignoreCase_);
    return string_;
} // replaceIn

// String trimming options.
typedef enum  _TrimEnum {
    TrimNone,                                                     // TrimEnum //
    TrimBegin,                                                    // TrimEnum //
    TrimEnd,                                                      // TrimEnum //
    TrimAll                                                       // TrimEnum //
} TrimEnum;                                                               //enum

// Return a copy of string_ with all the given characters (trimChars_)
// removed from the beginning and/or end.
//
// trimChars_: characters to trim. defaults to whitespaces
//              (space, tab \t, carriage return \r, newline \n, etc.).
inline tstring  trim(                                                        //F
    const tstring&  string_,                                                 //-
    const tstring&  trimChars_ = Whitespaces,                                //-
    const TrimEnum  trimScope_ = TrimAll) {                                  //-
    lx_c::lx_new_str_t  str = lx_c::lx_S_chars(string_.c_str());
    lx_c::lx_trimInS(&str,
                     trimChars_.c_str(),
                     lx_c::lx_trim_enum(trimScope_));
    return tstr_new_str_t(str);
} // trim

inline tstring*  trimIn(                                                     //F
    tstring*        string_,                                                 //-
    const tstring&  trimChars_ = Whitespaces,                                //-
    const TrimEnum  trimScope_ = TrimAll ) {                                 //-
    *string_ = trim(*string_, trimChars_, trimScope_);
    return string_;
} // trimIn

// -------------------------------------------------------------------------- //
// Informative Functions
// -------------------------------------------------------------------------- //

// Return true if string_ is numeric. It may only contain
// decimal numbers, non-consecutive group separators and up to one
// decimal point to be classed numeric. Whitespaces from the
// beginning and end (but not within) the string are also tolerated.

inline bool  isNumber(
    const tstring&   string_,                                                //-
    const lx_char_t  decimalPointChar_ = _T('.'),                            //-
    const lx_char_t  groupSeparator_   = _T(','),                            //-
    const tstring&   whitespaces_      = Whitespaces) {                      //-
    return LX_CPP_BOOL(lx_c::lx_is_numberT(string_.c_str(),
                                           decimalPointChar_,
                                           groupSeparator_,
                                           whitespaces_.c_str()));
} // isNumber

// -------------------------------------------------------------------------- //

// Return true if this string only contains whitespaces.
// i.e. space, tab (\t), carriage return (\r) and newline (\n).
inline bool  isWhitespace( const tstring&  string_ ) {
    return LX_CPP_BOOL(lx_c::lx_is_whitespaceT(string_.c_str()));
}

// -------------------------------------------------------------------------- //

// Return the numeric (integer) value of this string.
inline int  int_tstr( const tstring&  string_ ) {                            //F
#if defined UNICODE || defined _UNICODE
    return int(std::strtol(str_tstr(string_).c_str(), nullptr, 0));
#else
    return int(std::strtol(string_.c_str(), nullptr, 0));
#endif
} //  int_tstr

// Return the numeric (integer) value of this string.
inline uint32_t  uint_str( const string&  string_ ) {                        //F
    return unsigned int (std::strtoul(string_.c_str(), nullptr, 0));
}

// Return the numeric (double) value of this string.
inline double  double_tstr( const tstring& string_ ) {                       //F
    return std::strtod(str_tstr(string_).c_str(), nullptr);
}

// -------------------------------------------------------------------------- //

// Return true if string1_ is equal to string2_, ignoring the case.
template<class stringT>
bool  like(                                                                  //F
    const stringT&      string1_,                                            //-
    const stringT&      string2_,                                            //-
    const bool          ignoreCase_ = true,                                  //-
    const std::locale&  locale_ = std::locale::empty() ) {                   //-
    if (!ignoreCase_ || string1_.size() != string2_.size()) {
        return string1_ == string2_;
    } else {
        stringT::const_iterator  a = string1_.begin();
        stringT::const_iterator  b = string2_.begin();
        while (a != string1_.end()) {
            if (std::tolower<stringT::value_type>(*a++, locale_) !=
                std::tolower<stringT::value_type>(*b++, locale_)) {
                return false;
            }
        }
        return true;
    }
} // like

// Return true if string1_ matches string2_, ignoring case by default.
inline bool  like(                                                           //F
    const tstring&  string1_,                                                //-
    const tstring&  string2_,                                                //-
    const bool      ignoreCase_ = true) {                                    //-
    return like<tstring>(string1_, string2_, ignoreCase_);
}

// Return true if string_ begins with the given match_ string.
inline bool  begins(                                                         //F
    const tstring&  string_,                                                 //-
    const tstring&  match_,                                                  //-
    bool            ignoreCase_ = false ) {                                  //-
    const size_t  match_len = match_.size();
    return string_.empty() && match_len == 0 ? true :
           match_len == 0 || match_len > string_.size() ? false :
           like(string_.substr(0, match_len), match_, ignoreCase_);

    // begins() using C function:
    // return LX_CPP_BOOL(lx_c::lx_begins3T(string_.c_str(), match_.c_str(),
    //                                      LX_C_BOOL(ignoreCase_)));

} // begins

// Return true if string_ ends with the given match_ string.
inline bool  ends(                                                           //F
    const tstring&  string_,                                                 //-
    const tstring&  match_,                                                  //-
    bool            ignoreCase_ = false ) {                                  //-
    const size_t  match_len = match_.size();
    return string_.empty() && match_len == 0 ? true :
           match_len == 0 || match_len > string_.size() ? false :
           like(string_.substr(string_.size() - match_len, match_len), match_,
                ignoreCase_);

    // ends() using C function:
    // return LX_CPP_BOOL(lx_c::lx_endsT(string_.c_str(), match_.c_str(),
    //                                   LX_C_BOOL(ignoreCase_),
    //                                   string_.size(), match_.size()));

} // ends

// Return true if string_ contains find_.
inline bool  contains(                                                       //F
    const tstring&  string_,                                                 //-
    const tstring&  find_,                                                   //-
    bool            ignoreCase_ = false ) {                                  //-
    return LX_CPP_BOOL(lx_c::lx_containsT(string_.c_str(), find_.c_str(),
                                          LX_C_BOOL(ignoreCase_),
                                          string_.size(), find_.size()));
} // contains

// Return true if this text matches the pattern_. In pattern_, "?" is
// a placeholder for one character, while "*" is a placeholder for
// multiple characters. E.g. patternMatch("abc", "*b?") returns true.
inline bool  patternMatch(                                                   //F
    const tstring&  string_,                                                 //-
    const tstring&  pattern_,                                                //-
    const bool      ignoreCase_ = false) {                                   //-
    return LX_CPP_BOOL(lx_c::lx_patternMatchT(string_.c_str(), pattern_.c_str(),
                       LX_C_BOOL(ignoreCase_)));
} // patternMatch

// Return the position of findChar_ within this text, or NoMatch if not found.
//
//
// offset_:  Specifies the starting position, 0 by default.
// fromEnd_: set to true to begin the search from the end of this text.
inline size_t  findChar(                                                     //F
    const tstring&   string_,                                                //-
    const lx_char_t  findChar_,                                              //-
    const size_t     offset_     = 0,                                        //-
    const bool       ignoreCase_ = false,                                    //-
    const bool       fromEnd_    = false) {                                  //-
    return lx_c::lx_find_charT(string_.c_str(), findChar_, offset_,
                               LX_C_BOOL(ignoreCase_),
                               LX_C_BOOL(fromEnd_));
} // findChar

// Return the position of findChar_, searching from the
// end of this text, or NoMatch if it is not found.
inline size_t  findEndChar(                                                  //F
    const tstring&   string_,                                                //-
    const lx_char_t  findChar_,                                              //-
    const bool       ignoreCase_ = false,                                    //-
    const size_t     offset_     = 0) {                                      //-
    return lx_c::lx_find_charT(string_.c_str(), findChar_, offset_,
                               LX_C_BOOL(ignoreCase_), LX_C_BOOL(true));
} // findEndChar

// Return the position of the first character in this string_ that
// matches any character in findChars_. or NONE if it contains
// none. similar to strcspn() / wcscspn() C functions.
inline size_t  findChars(                                                    //F
    const tstring&  string_,                                                 //-
    const tstring&  findChars_,                                              //-
    const bool      ignoreCase_ = false) {                                   //-
    return lx_c::lx_find_charsT( string_.c_str(), findChars_.c_str(),
                                 LX_C_BOOL(ignoreCase_), string_.size() );
} // findChars

// -------------------------------------------------------------------------- //
// Manipulative Functions
// -------------------------------------------------------------------------- //

// Return a copy of charsLen_ characters from string's beginning
// Similar to Visual Basic's Left() / Left$() functions.
inline tstring  first(                                                       //F
    const tstring&  string_,                                                 //-
    const size_t    count_ ) {                                               //-
    return  tstr_new_chars_t(lx_c::lx_T_first(string_.c_str(), count_));
}

// Return a copy of charsLen_ characters from the string's end.
// Similar to Visual Basic's Right() / Right$() functions.
inline tstring  last(                                                        //F
    const tstring&  string_,                                                 //-
    const size_t    count_ ) {                                               //-
    return  tstr_new_chars_t(lx_c::lx_T_last(string_.c_str(), count_));
}

// Return a copy of string_, converted to upper case.
inline tstring  upperCase( const tstring&  string_ ) {                       //F
    lx_c::lx_new_str_t  ob = lx_c::lx_S_chars(string_.c_str());
    lx_c::lx_toupperInS(&ob);
    return tstr_new_str_t(ob);
} // upperCase

// Return a copy of string_, converted to lower case.
inline tstring  lowerCase( const tstring&  string_ ) {                       //F
    lx_c::lx_new_str_t  ob = lx_c::lx_S_chars(string_.c_str());
    lx_c::lx_tolowerInS(&ob);
    return tstr_new_str_t(ob);
} // lowerCase

// Return a copy of string_, converted to title case.
// The first letter of each word is capitalized.
// Existing upper case letters remain the same.
inline tstring  titleCase( const tstring&  string_ ) {                       //F
    lx_c::lx_new_str_t  ob = lx_c::lx_S_chars(string_.c_str());
    lx_c::lx_totitleInS(&ob);
    return tstr_new_str_t(ob);
} // titleCase

// Return a reversed copy of string_. E.g. 'ABCD' becomes 'DCBA'
inline tstring  reverse( const tstring&  string_ ) {                         //F
    lx_c::lx_new_str_t  ob = lx_c::lx_S_chars(string_.c_str());
    lx_c::lx_reverseInS(&ob);
    return tstr_new_str_t(ob);
} // reverse

// Return a text object with the specified character
// trimmed from the beginning and end.
inline tstring  trim(                                                        //F
    const tstring&   string_,                                                //-
    const lx_char_t  char_,                                                  //-
    const TrimEnum   trimScope_ = TrimAll) {                                 //-
    return trim(string_, tstring(1, char_), trimScope_);
}

// Return a copy with any of the specified
// characters trimmed from the beginning.
inline tstring  trimBegin(                                                   //F
    const tstring&  string_,                                                 //-
    const tstring&  trimChars_ = _T("") ) {                                  //-
    return trim(string_, trimChars_, TrimBegin);
}

// Return a copy with the specified character trimmed from the beginning
inline tstring  trimBegin(                                                   //F
    const tstring&   string_,                                                //-
    const lx_char_t  trimChar_ ) {                                           //-
    return trim(string_, tstring(1, trimChar_), TrimBegin);
}

// Return a copy with any of the specified characters trimmed from end.
inline tstring  trimEnd(                                                     //F
    const tstring&  string_,                                                 //-
    const tstring&  trimChars_ = _T("") ) {                                  //-
    return trim(string_, trimChars_, TrimEnd );
}

// Return a copy with the specified character trimmed from the end.
inline tstring  trimEnd(                                                     //F
    const tstring&   string_,                                                //-
    const lx_char_t  trimChar_ ) {                                           //-
    return trim(string_, tstring(1, trimChar_), TrimEnd);
}

// Add blank spaces, padding any existing contents.
inline tstring  space(                                                       //F
    const tstring&  string_,                                                 //-
    const size_t    charsLen_,                                               //-
    const bool      alignToEnd_ = false,                                     //-
    const bool      spillOut_   = false) {                                   //-
    if (string_.size() == charsLen_) {
        return string_;
    } else if (string_.size() > charsLen_) {
        if (spillOut_) {
            return string_;
        } else if (alignToEnd_) {
            return string_.substr(string_.size() - charsLen_, charsLen_);
        } else {
            return string_.substr(0, charsLen_);
        }
    } else if (alignToEnd_) {
        return tstring(charsLen_ - string_.size(), ' ') + string_;
    } else {
        return string_ + tstring(charsLen_ - string_.size(), ' ');
    }
} // space

// Return a copy with the given substring (string_)
// inserted at position_ within this text object.
// substrLen_: optionally specifies the length of string_.
inline tstring  insert(                                                      //F
    const tstring&  string_,                                                 //-
    const tstring&  insert_,                                                 //-
    const size_t    position_ = 0,                                           //-
    const size_t    length_   = MaxLength) {                                 //-
    return tstring(string_)
           .insert(position_, insert_.substr(0, length_));
} // insert

// Return a copy of text quoted with the given quote_ string.
// If the quote already appears within the contents,
// it is replaced with replace_.
inline tstring  quote(                                                       //F
    const tstring&  string_,                                                 //-
    const tstring&  quote_        = DefaultQuote,                            //-
    const tstring&  replaceQuote_ = DefaultQuoteReplace ) {                  //-
    return quote_ + replace(string_, quote_, replaceQuote_) + quote_;
}

// Return an unquoted copy of text, previously quoted with
// the given quote_ string. The quote replacement
// (replace_) is replaced with the original quote.
inline tstring  unquote(                                                     //F
    const tstring&  string_,                                                 //-
    const tstring&  quote_        = DefaultQuote,                            //-
    const tstring&  replaceQuote_ = DefaultQuoteReplace ) {                  //-
    return replace(trim(string_, quote_), replaceQuote_, quote_);
}

inline tstring  noBrackets( const tstring&  string_ ) {                      //F
    if (string_.empty()) {
        return Blank;
    }

    tstring::const_iterator  b = string_.begin();
    tstring::const_iterator  e = string_.end();

    if ((*b == '(' && *e == ')') ||
        (*b == '[' && *e == ']') ||
        (*b == '{' && *e == '}')) {
        b++;
        e--;
    }

    return tstring(b, e);
} // noBrackets

inline tstring  squareBrackets( const tstring&  string_ ) {                  //F
    return _T("[") + noBrackets(string_) + _T("]");
}

// -------------------------------------------------------------------------- //
//                          Token Handling Functions                          //
// -------------------------------------------------------------------------- //

// Return true if this string contains the given token.
// (Tokens are delimited by delimiter_.)
// E.g. tokenExists("dog", "cat;dog;horse", ";") returns true
inline bool  tokenExists(                                                    //F
    const tstring&  list_,                                                   //-
    const tstring&  token_,                                                  //-
    const tstring&  delimiter_  = DefaultDelimiter,                          //-
    const bool      ignoreCase_ = false) {                                   //-
    return list_.empty() ? false : LX_CPP_BOOL(lx_c::lx_token_info_xtT(
                lx_c::LX_TOKEN_EXISTS,
                list_.c_str(), delimiter_.c_str(), token_.c_str(),
                ignoreCase_, list_.size(), token_.size()));
} // tokenExists

// -------------------------------------------------------------------------- //

// Return the number of tokens in the given list_,
// with tokens delimited by the delimiter_.
//
// token_: when given, counts only tokens matching the token.
//
// Example: tokenCount("A;BB;CCC", ";") returns 3,
//          tokenCount(";ABC", ";")     returns 2.
inline size_t  tokenCount(                                                   //F
    const tstring&  list_,                                                   //-
    const tstring&  delimiter_  = _T(","),                                   //-
    const tstring&  token_      = _T(""),                                    //-
    const bool      ignoreCase_ = false) {                                   //-
    return list_.empty() ? 0 : lx_c::lx_token_info_xtT(
               lx_c::LX_TOKEN_COUNT,
               list_.c_str(), delimiter_.c_str(), token_.c_str(),
               ignoreCase_, list_.size(), token_.size());
} // tokenCount

// -------------------------------------------------------------------------- //

// Return a token at the position given by index_ (0 based) in the list_,
// with tokens delimited by delimiter_.
//
// ignoreEndDelimiter_: false by default. if true,
// Returns all characters from the token to the list's end.

inline tstring  getToken(                                                    //F
    const tstring&  list_,                                                   //-
    const size_t    index_,                                                  //-
    const tstring&  delimiter_          = _T(","),                           //-
    const bool      ignoreEndDelimiter_ = false ) {                          //-
    return tstr_new_chars_t(lx_c::lx_T_get_token_xt(
                                list_.c_str(), index_, delimiter_.c_str(),
                                LX_C_BOOL(ignoreEndDelimiter_)));
} // getToken

// -------------------------------------------------------------------------- //

inline tstring  getTag(                                                      //F
    const tstring&  string_,                                                 //-
    const tstring&  tag_,                                                    //-
    const tstring&  endTag_     = Blank,                                     //-
    const tstring&  delimiter_  = Blank,                                     //-
    const bool      ignoreCase_ = false,                                     //-
    const size_t    instanceNo_ = 0 ) {                                      //-
    lx_c::lx_new_str_t  ob = lx_c::lx_S_chars(string_.c_str());
    return tstr_new_str_t(lx_c::lx_S_getTag(ob,
                                            tag_.c_str(),
                                            endTag_.c_str(),
                                            delimiter_.c_str(),
                                            LX_C_BOOL(ignoreCase_),
                                            instanceNo_));
    lx_c::lx_freeS(&ob);
} // getTag

// Convert a value into a hexadecimal string.
inline tstring  hex(                                                         //F
    const uint32_t  value_,                                                  //-
    const size_t    minWidth_ ) {                                            //-
    // TODO: use stream instead of calling C fn.
    return tstr_new_chars_t(lx_c::lx_T_hex(value_, minWidth_));
}

}                                                                        //ns lx
#endif                                                                     //eof
// TODO: re-arrange function order
