/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_font_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_FONT__H
#define      INCLUDED_LIBEX_FONT__H
#include "libex_font.h"

#define font_t                          lx_font_t
#define new_font_t                      lx_new_font_t

/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */

#define Font_init                       lx_Font_init
#define Font_initCopy                   lx_Font_initCopy

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

#define Font_free                       lx_Font_free

/* -------------------------------------------------------------------------- */
/* Properties: Read-Write                                                     */

#define Font_getAngle                   lx_Font_getAngle
#define Font_getBold                    lx_Font_getBold
#define Font_getItalic                  lx_Font_getItalic
#define Font_getName                    lx_Font_getName
#define Font_getSize                    lx_Font_getSize
#define Font_getStrikeout               lx_Font_getStrikeout
#define Font_getUnderline               lx_Font_getUnderline

#define Font_setAngle                   lx_Font_setAngle
#define Font_setBold                    lx_Font_setBold
#define Font_setItalic                  lx_Font_setItalic
#define Font_setName                    lx_Font_setName
#define Font_setSize                    lx_Font_setSize
#define Font_setStrikeout               lx_Font_setStrikeout
#define Font_setUnderline               lx_Font_setUnderline

/* -------------------------------------------------------------------------- */
/* Properties: Read-Only                                                      */

#define Font_isEqual                    lx_Font_isEqual

/* -------------------------------------------------------------------------- */
/* Properties: Windows-Specific                                               */

#if LX_PLATFORM_WIN32
#define Font_getDc                      lx_Font_getDc
#define Font_getHandle                  lx_Font_getHandle
#define Font_setDc                      lx_Font_setDc
#endif

/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */

#define Font_recreate                   lx_Font_recreate
#define Font_reset                      lx_Font_reset
#define Font_set                        lx_Font_set
#define Font_setCopy                    lx_Font_setCopy

/* -------------------------------------------------------------------------- */
/* Functions: Windows-Specific                                                */

#if LX_PLATFORM_WIN32
#define font_create                     lx_font_create
#define font_destroy                    lx_font_destroy
#endif

#endif                                                                   /*eof*/
