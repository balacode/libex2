// -------------------------------------------------------------------------- //
// (c) Ali Silvester Balarabe             [libex_string_cli.hh] [cat:strings] //
// -------------------------------------------------------------------------- //

#if !defined __cplusplus_cli
#error "Non-C++/CLI code shouldn't include libex_string_cli.hh"
#endif

#if !defined INCLUDED_LIBEX_STRING_CLI_HH
#define      INCLUDED_LIBEX_STRING_CLI_HH

#include "libex_string.hh"

// -------------------------------------------------------------------------- //
#if defined __cplusplus_cli
#pragma managed
namespace  lx {

cli::interior_ptr<const System::Char>  cli_chars_ptr(                        //F
    System::String^  string_ );                                              //-

// Convert std::string to CLI String
inline System::String^  cli_str( const std::string&  string_ ) {             //F
    return gcnew System::String(wstr_str(string_).c_str());
}

// Convert std::wstring to CLI String
inline System::String^  cli_wstr( const std::wstring&  string_ ) {           //F
    return gcnew System::String(string_.c_str());
}

// Convert a CLI String to std::string
inline std::string  str_cli( System::String^  string_ ) {                    //F
    const pin_ptr<const wchar_t>  wide  = cli_chars_ptr(string_);
    return str_wstr(wide);
}

// Convert a CLI String to std::wstring
inline std::wstring  wstr_cli( System::String^  string_ ) {                  //F
    const pin_ptr<const wchar_t>  wide  = cli_chars_ptr(string_);
    return wide;
}

}                                                                        //ns lx
#endif                                                       //#__cplusplus_cli
#endif                                                                     //eof
