/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                     [libex_console.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_CONSOLE_H
#define      INCLUDED_LIBEX_CONSOLE_H

#include "libex.h"

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

/* -------------------------------------------------------------------------- */
/* Properties:                                                                */

LX_PUBLIC void  lx_Console_setLeftMargin( const int  margin_ );            /*P*/

LX_PUBLIC int  lx_Console_getLeftMargin( void );                           /*P*/

/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */

LX_PUBLIC int  lx_Console_getKey( void );                                  /*M*/

LX_PUBLIC void  lx_Console_out( lx_chars_t  text_ );                       /*M*/

LX_PUBLIC void  lx_Console_outA( const char*  text_ );                     /*M*/

LX_PUBLIC void  lx_Console_outW( const wchar_t*  text_ );                  /*M*/

LX_PUBLIC void  lx_Console_outInt( const int  value_ );                    /*M*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
