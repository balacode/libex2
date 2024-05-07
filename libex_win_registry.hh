// -------------------------------------------------------------------------- //
// (c) Ali Silvester Balarabe                         [libex_win_registry.hh] //
// -------------------------------------------------------------------------- //

#include "libex_config.h"

#if !defined INCLUDED_LIBEX_WIN_REGISTRY_HH && LX_PLATFORM_WIN32
#define      INCLUDED_LIBEX_WIN_REGISTRY_HH
#include "libex.h"
#include "libex_win_registry.h"
#if LX_PLATFORM_WIN32
#include "libex_win32.h"
#endif

#include "libex_string.hh"

// -------------------------------------------------------------------------- //
namespace  lxos {

class Registry {
public:

    static inline HKEY_win  extractKey( const std::tstring& key_ ) {         //F
        return lx_c::lx_registry_extract_key(key_.c_str());
    }

    static inline std::tstring  extractSubkey( const std::tstring&  key_ ) { //F
        return lx::tstr_c_str(lx_c::lx_registry_extract_subkey(key_.c_str()));
    }

    static inline bool  valueExists(                                         //F
        const std::tstring&  key_,                                           //-
        const std::tstring&  valueName_ ) {                                  //-
        return LX_CPP_BOOL(lx_c::lx_registry_value_exists(
                               key_.c_str(), valueName_.c_str()));
    }

    static inline std::tstring  getText(                                     //F
        const std::tstring&  key_,                                           //-
        const std::tstring&  valueName_ ) {                                  //-
        return lx::tstr_new_chars_t(
                   lx_c::lx_registry_get_text(key_.c_str(),
                                              valueName_.c_str()));
    }

    static inline bool  setText(                                             //F
        const std::tstring&  key_,                                           //-
        const std::tstring&  valueName_,                                     //-
        const std::tstring&  value_ ) {                                      //-
        return LX_CPP_BOOL(lx_c::lx_registry_set_text(key_.c_str(),
                           valueName_.c_str(),
                           value_.c_str()));
    }

    static inline DWORD_win  getDword(                                       //F
        const std::tstring&  key_,                                           //-
        const std::tstring&  valueName_,                                     //-
        const DWORD_win      default_ ) {                                    //-
        return lx_c::lx_registry_get_dword(
                   key_.c_str(), valueName_.c_str(), default_);
    }

    static inline bool  setDword(                                            //F
        const std::tstring&  key_,                                           //-
        const std::tstring&  valueName_,                                     //-
        const DWORD_win      value_ ) {                                      //-
        return LX_CPP_BOOL(lx_c::lx_registry_set_dword(
                               key_.c_str(), valueName_.c_str(), value_));
    }

    static inline bool  deleteValue(                                         //F
        const std::tstring&  key_,                                           //-
        const std::tstring&  valueName_ ) {                                  //-
        return LX_CPP_BOOL(lx_c::lx_registry_delete_value(
                               key_.c_str(), valueName_.c_str()));
    }

};                                                             //class  Registry

}                                                                      //ns lxos
#endif                                                                     //eof
