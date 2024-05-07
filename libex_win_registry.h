/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                [libex_win_registry.h] */
/* -------------------------------------------------------------------------- */

#include "libex_config.h"

#if !defined INCLUDED_LIBEX_WIN_REGISTRY_H && LX_PLATFORM_WIN32
#define      INCLUDED_LIBEX_WIN_REGISTRY_H
#include "libex.h"

#if LX_PLATFORM_WIN32
#include "libex_win32.h"
#endif

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

LX_PUBLIC HKEY_win  lx_registry_extract_key( lx_chars_t  key_ );           /*F*/

LX_PUBLIC lx_new_chars_t  lx_registry_extract_subkey(                      /*F*/
    lx_chars_t  key_ );                                                    /*-*/

LX_PUBLIC lx_bool  lx_registry_value_exists(                               /*F*/
    lx_chars_t  key_,                                                      /*-*/
    lx_chars_t  value_name_ );                                             /*-*/

LX_PUBLIC lx_new_chars_t  lx_registry_get_text(                            /*F*/
    lx_chars_t  key_,                                                      /*-*/
    lx_chars_t  value_name_ );                                             /*-*/

LX_PUBLIC lx_bool  lx_registry_set_text(                                   /*F*/
    lx_chars_t  key_,                                                      /*-*/
    lx_chars_t  value_name_,                                               /*-*/
    lx_chars_t  value_ );                                                  /*-*/

LX_PUBLIC DWORD_win  lx_registry_get_dword(                                /*F*/
    lx_chars_t       key_,                                                 /*-*/
    lx_chars_t       value_name_,                                          /*-*/
    const DWORD_win  default_ );                                           /*-*/

LX_PUBLIC lx_bool  lx_registry_set_dword(                                  /*F*/
    lx_chars_t       key_,                                                 /*-*/
    lx_chars_t       value_name_,                                          /*-*/
    const DWORD_win  value_ );                                             /*-*/

/*TODO: join code common to ..text ..dword and ..int into the same subroutine */

LX_PUBLIC lx_bool  lx_registry_delete_value(                               /*F*/
    lx_chars_t  key_,                                                      /*-*/
    lx_chars_t  value_name_ );                                             /*-*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
