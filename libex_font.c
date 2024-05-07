/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                        [libex_font.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_font_.h"
#if defined INCLUDED_LIBEX_FONT_H

#include <string.h>  /* for memset() */

#include "libex_.h"
#include "libex_call_.h"
#include "libex_config_.h"
#include "libex_debug_.h"
#include "libex_error_.h"
#include "libex_macro_.h"
#include "libex_stringc_.h"
#include "libex_type_.h"

#if PLATFORM_WIN32
#include "libex_win32_.h"
#endif

#if defined __cplusplus_cli
#pragma unmanaged
#endif


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


typedef struct  _font_t {
    new_chars_t  font_name;                                        /* _font_t */
    int          font_size;                                        /* _font_t */
    bool         font_bold;                                        /* _font_t */
    bool         font_italic;                                      /* _font_t */
    bool         font_underline;                                   /* _font_t */
    bool         font_strikeout;                                   /* _font_t */
    int          font_angle;                                       /* _font_t */

#if PLATFORM_WIN32
    HDC_win      font_dc;                                          /* _font_t */
    HFONT_win    handle;                                           /* _font_t */
#endif
}
_font_t;


#define _BASE_OBJ_WRAP_INC
#define _OBJ_HANDLE_TYPE   font_t
#define _OBJ_INNER_TYPE    _font_t
#define _OBJ_ALLOC_FN_UID  UID(FB7F1E)
#define _OBJ_FREE_FN_UID   UID(FCDF74)
#define _OBJ_CONST_FN_UID  UID(F8663B)
#define _OBJ_FN_UID        UID(F54652)
#define _OBJ_WRAP_FN_UID   UID(F97BC0)
#include "libex_object_wrapper.inc.c"


/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */


PUBLIC new_font_t  Font_init(                                              /*C*/
    chars_t     font_name_,                                                /*-*/
    const int   font_size_,                                                /*-*/
    const bool  bold_,                                                     /*-*/
    const bool  italic_,                                                   /*-*/
    const bool  underline_,                                                /*-*/
    const bool  strikeout_,                                                /*-*/
    const int   font_angle_ ) {                                            /*-*/
    GO                                                            (UID(F6A359));
    _font_t*    ob  = _object_alloc();
    new_font_t  ret = _object_wrap(ob);

    ob->font_name      = T_chars(font_name_);
    ob->font_size      = font_size_;
    ob->font_bold      = bold_;
    ob->font_italic    = italic_;
    ob->font_underline = underline_;
    ob->font_strikeout = strikeout_;
    ob->font_angle     = font_angle_;

#if PLATFORM_WIN32
    ob->handle  = NULL;
    ob->font_dc = NULL;
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* Font_init */


PUBLIC new_font_t  Font_initCopy( const font_t  copy_from_ ) {             /*C*/
    GO                                                            (UID(FC0C8F));
    const _font_t*  copy = _object_const(&copy_from_, UID(EA590C));
    _font_t*        ob   = _object_alloc();
    new_font_t      ret  = _object_wrap(ob);

    ob->font_name      = T_chars(copy->font_name);
    ob->font_size      = copy->font_size;
    ob->font_bold      = copy->font_bold;
    ob->font_italic    = copy->font_italic;
    ob->font_underline = copy->font_underline;
    ob->font_strikeout = copy->font_strikeout;
    ob->font_angle     = copy->font_angle;

#if PLATFORM_WIN32
    ob->handle  = NULL;
    ob->font_dc = copy->font_dc;
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* Font_initCopy */


PUBLIC void  Font_set(                                                     /*M*/
    font_t*     object_,                                                   /*-*/
    chars_t     font_name_,                                                /*-*/
    const int   font_size_,                                                /*-*/
    const bool  bold_,                                                     /*-*/
    const bool  italic_,                                                   /*-*/
    const bool  underline_,                                                /*-*/
    const bool  strikeout_,                                                /*-*/
    const int   font_angle_ ) {                                            /*-*/
    GO                                                            (UID(FA92E4));
    _font_t* const  me = _object(object_, UID(EE661C));

    me->font_name      = T_chars(font_name_);
    me->font_size      = font_size_;
    me->font_bold      = bold_;
    me->font_italic    = italic_;
    me->font_underline = underline_;
    me->font_strikeout = strikeout_;
    me->font_angle     = font_angle_;

#if PLATFORM_WIN32

    if (me->handle != NULL) {
        font_destroy(&me->handle);
        me->handle = NULL;
    }

    me->font_dc = NULL;
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Font_set */


/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */


PUBLIC void  Font_free( font_t*  object_ ) {                               /*D*/
    GO                                                            (UID(F3556B));
    _font_t* const  me = _object(object_, UID(E35E8B));

#if PLATFORM_WIN32
    if (me->handle != NULL) {
        font_destroy(&me->handle);
    }
#endif                                                      /* PLATFORM_WIN32 */

    freeT(&me->font_name);
    _object_free(object_);
    RETURN(NIL);
} /* Font_free */


/* -------------------------------------------------------------------------- */
/* Properties: Read/Write                                                     */


PUBLIC chars_t  Font_getName( const font_t  object_ ) {                    /*P*/
    GO                                                            (UID(FEDE14));
    const _font_t* const  me  = _object_const(&object_, UID(EF51A3));
    chars_t               ret = me->font_name;
    RETURN(ret);
} /* Font_getName */


PUBLIC void  Font_setName(                                                 /*P*/
    font_t*  object_,                                                      /*-*/
    chars_t  value_ ) {                                                    /*-*/
    GO                                                            (UID(FA538B));
    _font_t* const  me = _object(object_, UID(ED0EFF));
    set_inT(&me->font_name, value_);
    Font_recreate(object_);
    RETURN(NIL);
} /* Font_setName */


PUBLIC int  Font_getSize( const font_t  object_ ) {                        /*P*/
    GO                                                            (UID(F5AF47));
    const _font_t* const  me = _object_const(&object_, UID(E7306A));
    const int  ret = me->font_bold;
    RETURN(ret);
} /* Font_getSize */


PUBLIC void  Font_setSize(                                                 /*P*/
    font_t*    object_,                                                    /*-*/
    const int  value_ ) {                                                  /*-*/
    GO                                                            (UID(F7D92C));
    _font_t* const  me = _object(object_, UID(E51348));
    me->font_size = value_;
    Font_recreate(object_);
    RETURN(NIL);
} /* Font_setSize */


PUBLIC bool  Font_getBold( const font_t  object_ ) {                       /*P*/
    GO                                                            (UID(F60344));
    const _font_t* const  me = _object_const(&object_, UID(E7EE55));
    const bool  ret = me->font_bold;
    RETURN(ret);
} /* Font_getBold */


PUBLIC void  Font_setBold(                                                 /*P*/
    font_t*     object_,                                                   /*-*/
    const bool  value_ ) {                                                 /*-*/
    GO                                                            (UID(F9C00E));
    _font_t* const  me = _object(object_, UID(E4D64A));
    me->font_bold = value_;
    Font_recreate(object_);
    RETURN(NIL);
} /* Font_setBold */


PUBLIC bool  Font_getItalic( const font_t  object_ ) {                     /*P*/
    GO                                                            (UID(FFAD10));
    const _font_t* const  me = _object_const(&object_, UID(E79A08));
    const bool  ret = me->font_italic;
    RETURN(ret);
} /* Font_getItalic */


PUBLIC void  Font_setItalic(                                               /*P*/
    font_t*     object_,                                                   /*-*/
    const bool  value_ ) {                                                 /*-*/
    GO                                                            (UID(F582EB));
    _font_t* const  me = _object(object_, UID(E6CC16));
    me->font_italic = value_;
    Font_recreate(object_);
    RETURN(NIL);
} /* Font_setItalic */

PUBLIC bool  Font_getUnderline( const font_t  object_ ) {                  /*P*/
    GO                                                            (UID(FB48F2));
    const _font_t* const  me = _object_const(&object_, UID(EF7D0F));
    const bool  ret = me->font_underline;
    RETURN(ret);
} /* Font_getUnderline */


PUBLIC void  Font_setUnderline(                                            /*P*/
    font_t*     object_,                                                   /*-*/
    const bool  value_ ) {                                                 /*-*/
    GO                                                            (UID(F5CCC0));
    _font_t* const  me = _object(object_, UID(EF5B26));
    me->font_underline = value_;
    Font_recreate(object_);
    RETURN(NIL);
} /* Font_setUnderline */


PUBLIC bool  Font_getStrikeout( const font_t  object_ ) {                  /*P*/
    GO                                                            (UID(FD5128));
    const _font_t* const  me = _object_const(&object_, UID(E638CB));
    const bool  ret = me->font_strikeout;
    RETURN(ret);
} /* Font_getStrikeout */


PUBLIC void  Font_setStrikeout(                                            /*P*/
    font_t*     object_,                                                   /*-*/
    const bool  value_ ) {                                                 /*-*/
    GO                                                            (UID(F4183A));
    _font_t* const  me = _object(object_, UID(E33BD7));
    me->font_strikeout = value_;
    Font_recreate(object_);
    RETURN(NIL);
} /* Font_setStrikeout */


PUBLIC int  Font_getAngle( const font_t  object_ ) {                       /*P*/
    GO                                                            (UID(F0BDFA));
    const _font_t* const  me = _object_const(&object_, UID(E989D5));
    const int  ret = me->font_angle;
    RETURN(ret);
} /* Font_getAngle */


PUBLIC void  Font_setAngle(                                                /*P*/
    font_t*    object_,                                                    /*-*/
    const int  value_ ) {                                                  /*-*/
    GO                                                            (UID(F577D2));
    _font_t* const  me = _object(object_, UID(E43801));
    me->font_angle = value_;
    Font_recreate(object_);
    RETURN(NIL);
} /* Font_setAngle */


/* -------------------------------------------------------------------------- */
/* Properties: Read-Only                                                      */


PUBLIC bool  Font_isEqual(                                                 /*P*/
    const font_t*  object_,                                                /*-*/
    const font_t*  compare_ ) {                                            /*-*/
    GO                                                            (UID(F29099));
    const _font_t* const  font1 = _object_const(object_, UID(EE719C));
    const _font_t* const  font2 = _object_const(compare_, UID(E61EA0));

    const bool  ret = (font1->font_size      == font2->font_size      &&
                       font1->font_bold      == font2->font_bold      &&
                       font1->font_italic    == font2->font_italic    &&
                       font1->font_underline == font2->font_underline &&
                       font1->font_strikeout == font2->font_strikeout &&
                       font1->font_angle     == font2->font_angle     &&
                       equals2T(font1->font_name, font2->font_name));

    /* 'font_dc' and 'handle' can differ and are not compared. */

    RETURN(ret);
} /* Font_isEqual */


/* -------------------------------------------------------------------------- */
/* Properties: Windows-Specific                                               */


#if PLATFORM_WIN32
PUBLIC HDC_win  Font_getDc( const font_t  object_ ) {                      /*P*/
    GO                                                            (UID(F5B53F));
    const _font_t* const  me = _object_const(&object_, UID(E0B293));
    const HDC_win  ret = me->font_dc;
    RETURN(ret);
} /* Font_getDc */
#endif                                                      /* PLATFORM_WIN32 */


#if PLATFORM_WIN32
PUBLIC void  Font_setDc(                                                   /*P*/
    font_t*        object_,                                                /*-*/
    const HDC_win  value_ ) {                                              /*-*/
    GO                                                            (UID(F81A23));
    _font_t* const  me = _object(object_, UID(ED48A0));

    me->font_dc = value_;
    Font_recreate(object_);

    RETURN(NIL);
} /* Font_setDc */
#endif                                                      /* PLATFORM_WIN32 */


#if PLATFORM_WIN32
PUBLIC HFONT_win  Font_getHandle(                                          /*P*/
    font_t*         object_,                                               /*-*/
    const HWND_win  window_ ) { /* screen device context == NULL */
    /*-*/
    GO                                                            (UID(FC5E53));
    _font_t* const  me = _object(object_, UID(E82C28));

    if (me->handle == NULL) {
        const HDC_win  hdc  = GetDC_win(window_);
        me->handle = font_create(hdc,
                                 me->font_name,
                                 me->font_size,
                                 me->font_bold,
                                 me->font_italic,
                                 me->font_underline,
                                 me->font_strikeout,
                                 me->font_angle);
        OS_VERIFY(ReleaseDC_win(window_, hdc), UID(EB7CEC));
    }
    {
        const HFONT_win  ret = me->handle;
        RETURN(ret);
    }
} /* Font_getHandle */
#endif                                                      /* PLATFORM_WIN32 */


/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */


PUBLIC void  Font_recreate( font_t*  object_ ) {                           /*M*/
    GO                                                            (UID(F22017));
    _font_t* const  me = _object(object_, UID(EAEE33));

#if PLATFORM_WIN32
    font_destroy(&me->handle);
    me->handle = font_create(me->font_dc,
                             me->font_name,
                             me->font_size,
                             me->font_bold,
                             me->font_italic,
                             me->font_underline,
                             me->font_strikeout,
                             me->font_angle);
#endif                                                      /* PLATFORM_WIN32 */
    RETURN(NIL);
} /* Font_recreate */


PUBLIC void  Font_reset( font_t*  object_ ) {                              /*M*/
    GO                                                            (UID(F9A3EE));
    _font_t* const  me = _object(object_, UID(E5A2F9));

#if PLATFORM_WIN32
    font_destroy(&me->handle);
#endif

    RETURN(NIL);
} /* Font_reset */


PUBLIC void  Font_setCopy(                                                 /*M*/
    font_t*        object_,                                                /*-*/
    const font_t*  copy_from_ ) {                                          /*-*/
    GO                                                            (UID(FFB5AC));
    _font_t* const  me = _object(object_, UID(E8EEC7));

    const _font_t* const  copy = _object_const(copy_from_, UID(E45197));

#if PLATFORM_WIN32

    if (me->handle != NULL) {
        font_destroy(&me->handle);
    }

#endif                                                      /* PLATFORM_WIN32 */

    set_inT(&me->font_name, copy->font_name);

    me->font_size      = copy->font_size;
    me->font_bold      = copy->font_bold;
    me->font_italic    = copy->font_italic;
    me->font_underline = copy->font_underline;
    me->font_strikeout = copy->font_strikeout;
    me->font_angle     = copy->font_angle;

#if PLATFORM_WIN32
    me->handle  = NULL;
    me->font_dc = NULL;
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Font_setCopy */


/* -------------------------------------------------------------------------- */
/* Functions: Windows-Specific                                                */


#if PLATFORM_WIN32
PUBLIC HFONT_win  font_create(                                             /*F*/
    const HDC_win  hdc_,                                                   /*-*/
    chars_t        font_name_,                                             /*-*/
    const int      font_size_,                                             /*-*/
    const bool     bold_,                                                  /*-*/
    const bool     italic_,                                                /*-*/
    const bool     underline_,                                             /*-*/
    const bool     strikeout_,                                             /*-*/
    const int      font_angle_ ) {                                         /*-*/
    GO                                                            (UID(F5D405));
    LOGFONT_win  font;
    CLEAR(font);
    font.lfHeight = -MulDiv_win(font_size_,
                                GetDeviceCaps_win(hdc_, LOGPIXELSY_win), 72);
    font.lfWidth          = 0;
    font.lfEscapement     = font_angle_ * 10;
    font.lfOrientation    = font.lfEscapement;
    font.lfWeight         = bold_      ? FW_BOLD_win : FW_NORMAL_win;
    font.lfItalic         = italic_    ? TRUE_win    : FALSE_win;
    font.lfUnderline      = underline_ ? TRUE_win    : FALSE_win;
    font.lfStrikeOut      = strikeout_ ? TRUE_win    : FALSE_win;
    font.lfCharSet        = DEFAULT_CHARSET_win;
    font.lfOutPrecision   = OUT_TT_ONLY_PRECIS_win;
    font.lfClipPrecision  = CLIP_DEFAULT_PRECIS_win;
    font.lfQuality        = PROOF_QUALITY_win;
    font.lfPitchAndFamily = DEFAULT_PITCH_win + FF_DONTCARE_win;

    STRCPY_S_T(font.lfFaceName, LF_FACESIZE_win, font_name_);
    {
        const HFONT_win  ret = CreateFontIndirect_win(&font);
        OS_VERIFY(ret != NULL, UID(E508C1));
        RETURN(ret);
    }
} /* font_create */
#endif                                                      /* PLATFORM_WIN32 */


#if PLATFORM_WIN32
PUBLIC void  font_destroy( HFONT_win*  font_ ) {                           /*F*/
    GO                                                            (UID(FDC92C));
    if (font_ != NULL && *font_ != NULL) {
        OS_VERIFY(DeleteObject_win(font_), UID(E1574B));
        *font_ = NULL;
    }
    RETURN(NIL);
} /* font_destroy */
#endif                                                      /* PLATFORM_WIN32 */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
