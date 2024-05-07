// -------------------------------------------------------------------------- //
// (c) Ali Silvester Balarabe             [libex_string_cli.cc] [cat:strings] //
// -------------------------------------------------------------------------- //

#include "libex_string_cli.hh"
#if defined INCLUDED_LIBEX_STRING_CLI_HH

#include "libex_.h"

#if defined __cplusplus_cli
#pragma managed
namespace lx {

// -------------------------------------------------------------------------- //
// Managed String Functions:

cli::interior_ptr<const System::Char>  cli_chars_ptr(                        //F
    System::String^  string_ ) {                                             //-
    cli::interior_ptr<System::Byte>  ptr =
        CCAST(cli::interior_ptr<System::Byte>,
              RCAST(cli::interior_ptr<const System::Byte>, string_));

    if (ptr != nullptr) {
        ptr += System::Runtime::CompilerServices::
               RuntimeHelpers::OffsetToStringData;
    }
    return reinterpret_cast<cli::interior_ptr<const System::Char>>(ptr);
} // cli_chars_ptr

}                                                                // namespace lx
#endif                                                       //#__cplusplus_cli
#endif                                                                     //eof
// string-related file
