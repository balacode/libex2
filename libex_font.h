/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                        [libex_font.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_FONT_H
#define      INCLUDED_LIBEX_FONT_H

#include "libex.h"

#if LX_PLATFORM_WIN32
#include "libex_win32.h"
#endif

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

typedef struct  lx_font_t {
    uint8_t*  ob;                                                /* lx_font_t */
}
lx_font_t, lx_new_font_t;

/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */

/* Default Constructor. */
LX_PUBLIC lx_new_font_t  lx_Font_init(                                     /*C*/
    lx_chars_t     font_name_,                                             /*-*/
    const int      font_size_,                                             /*-*/
    const lx_bool  bold_,                                                  /*-*/
    const lx_bool  italic_,                                                /*-*/
    const lx_bool  underline_,                                             /*-*/
    const lx_bool  strikeout_,                                             /*-*/
    const int      font_angle_ );                                          /*-*/

/* Copy Constructor. */
LX_PUBLIC lx_new_font_t  lx_Font_initCopy( const lx_font_t  copy_from_ );  /*C*/

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

LX_PUBLIC void  lx_Font_free( lx_font_t*  object_ );                       /*D*/

/* -------------------------------------------------------------------------- */
/* Properties: Read-Write                                                     */

LX_PUBLIC lx_chars_t  lx_Font_getName( const lx_font_t  object_ );         /*P*/

LX_PUBLIC void  lx_Font_setName(                                           /*P*/
    lx_font_t*  object_,                                                   /*-*/
    lx_chars_t  value_ );                                                  /*-*/

LX_PUBLIC int  lx_Font_getSize( const lx_font_t  object_ );                /*P*/

LX_PUBLIC void  lx_Font_setSize(                                           /*P*/
    lx_font_t*  object_,                                                   /*-*/
    const int   value_ );                                                  /*-*/

LX_PUBLIC lx_bool  lx_Font_getBold( const lx_font_t  object_ );            /*P*/

LX_PUBLIC void  lx_Font_setBold(                                           /*P*/
    lx_font_t*     object_,                                                /*-*/
    const lx_bool  value_ );                                               /*-*/

LX_PUBLIC lx_bool  lx_Font_getItalic( const lx_font_t  object_ );          /*P*/

LX_PUBLIC void  lx_Font_setItalic(                                         /*P*/
    lx_font_t*     object_,                                                /*-*/
    const lx_bool  value_ );                                               /*-*/

LX_PUBLIC lx_bool  lx_Font_getUnderline( const lx_font_t  object_ );       /*P*/

LX_PUBLIC void  lx_Font_setUnderline(                                      /*P*/
    lx_font_t*     object_,                                                /*-*/
    const lx_bool  value_ );                                               /*-*/

LX_PUBLIC lx_bool  lx_Font_getStrikeout( const lx_font_t  object_ );       /*P*/

LX_PUBLIC void  lx_Font_setStrikeout(                                      /*P*/
    lx_font_t*     object_,                                                /*-*/
    const lx_bool  value_ );                                               /*-*/

LX_PUBLIC int  lx_Font_getAngle( const lx_font_t  object_ );               /*P*/

LX_PUBLIC void  lx_Font_setAngle(                                          /*P*/
    lx_font_t*  object_,                                                   /*-*/
    const int   value_ );                                                  /*-*/

/* -------------------------------------------------------------------------- */
/* Properties: Read-Only                                                      */

LX_PUBLIC lx_bool  lx_Font_isEqual(                                        /*P*/
    const lx_font_t*  object_,                                             /*-*/
    const lx_font_t*  compare_ );                                          /*-*/

/* -------------------------------------------------------------------------- */
/* Properties: Windows-Specific                                               */

#if LX_PLATFORM_WIN32

LX_PUBLIC HDC_win  lx_Font_getDc( const lx_font_t  object_ );              /*P*/

LX_PUBLIC void  lx_Font_setDc(                                             /*P*/
    lx_font_t*     object_,                                                /*-*/
    const HDC_win  value_ );                                               /*-*/

LX_PUBLIC HFONT_win  lx_Font_getHandle(                                    /*P*/
    lx_font_t*      object_,                                               /*-*/
    const HWND_win  window_ );  /* screen device context == NULL */        /*-*/

#endif                                                   /* LX_PLATFORM_WIN32 */

/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */

/* Re-creates the internal font object, applying current properties.          */
LX_PUBLIC void  lx_Font_recreate( lx_font_t*  object_ );                   /*M*/

/* Destroys the internal font object.                                         */
LX_PUBLIC void  lx_Font_reset( lx_font_t*  object_ );                      /*M*/

LX_PUBLIC void  lx_Font_setCopy(                                           /*M*/
    lx_font_t*        object_,                                             /*-*/
    const lx_font_t*  copy_from_ );                                        /*-*/

LX_PUBLIC void  lx_Font_set(                                               /*M*/
    lx_font_t*     object_,                                                /*-*/
    lx_chars_t     font_name_,                                             /*-*/
    const int      font_size_,                                             /*-*/
    const lx_bool  bold_,                                                  /*-*/
    const lx_bool  italic_,                                                /*-*/
    const lx_bool  underline_,                                             /*-*/
    const lx_bool  strikeout_,                                             /*-*/
    const int      font_angle_ );                                          /*-*/

/* -------------------------------------------------------------------------- */
/* Functions: Windows-Specific                                                */

#if LX_PLATFORM_WIN32

/* Creates a font for the specified device context.                           */
LX_PUBLIC HFONT_win  lx_font_create(                                       /*F*/
    const HDC_win  hdc_,                                                   /*-*/
    lx_chars_t     font_name_,                                             /*-*/
    const int      font_size_,                                             /*-*/
    const lx_bool  bold_,                                                  /*-*/
    const lx_bool  italic_,                                                /*-*/
    const lx_bool  underline_,                                             /*-*/
    const lx_bool  strikeout_,                                             /*-*/
    const int      font_angle_ );                                          /*-*/

LX_PUBLIC void  lx_font_destroy( HFONT_win*  font_ );                      /*F*/

#endif                                                   /* LX_PLATFORM_WIN32 */

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
