/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                   [libex_clipboard.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_CLIPBOARD_H
#define      INCLUDED_LIBEX_CLIPBOARD_H

#include "libex_string_class.h"

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

/* Retrieves text copied on the system clipboard.                             */
LX_PUBLIC lx_new_str_t  lx_Clipboard_getText( void );                      /*M*/

/* Copies the specified text to the system clipboard.                         */
LX_PUBLIC lx_bool  lx_Clipboard_setText( lx_chars_t  text_ );              /*M*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
