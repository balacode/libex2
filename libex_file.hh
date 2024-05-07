// -------------------------------------------------------------------------- //
// (c) Ali Silvester Balarabe                                 [libex_file.hh] //
// -------------------------------------------------------------------------- //

#if !defined __cplusplus
#error "Non-C++ code shouldn't include libex_file.hpp"
#endif

#if !defined INCLUDED_LIBEX_FILE_HH
#define      INCLUDED_LIBEX_FILE_HH

#include "libex_string.hh"
#include <fstream>
#include <string>

// -------------------------------------------------------------------------- //
namespace  lx {
namespace  file {

// -------------------------------------------------------------------------- //
// Functions

inline void appendText(                                                      //F
    const std::tstring&  filename_,                                          //-
    const std::tstring&  text_ ) {                                           //-
    std::tofstream  out(filename_.c_str());
    out << text_ << std::endl;
}

}                                                                      //ns file
}                                                                        //ns lx
#endif                                                                     //eof
