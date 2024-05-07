// -------------------------------------------------------------------------- //
// (c) Ali Silvester Balarabe                 [libex_string.cc] [cat:strings] //
// -------------------------------------------------------------------------- //

//#include "libex_cc_precompiled.hpp"
#include "libex_string.hh"
#if defined INCLUDED_LIBEX_STRING_HH

#include <locale>
#include <iostream>

#include "libex_.h"
#include "libex_call_.h"

#if defined _MSC_VER
#pragma warning (disable:4710)  // W:L4 function not inlined
#endif

#if defined _MSC_VER  // TEMPORARY!
#pragma warning (push)
#pragma warning (disable:4100)  // W:L4 unreferenced formal parameter
#endif

// -------------------------------------------------------------------------- //
namespace lx {

using std::locale;
using std::string;
using std::tolower;
using std::tostringstream;
using std::wstring;


// -------------------------------------------------------------------------- //
// Unmanaged String Functions:

#if defined __cplusplus_cli
#pragma unmanaged
#endif


// -------------------------------------------------------------------------- //


}                                                                // namespace lx
#endif                                                                     //eof
