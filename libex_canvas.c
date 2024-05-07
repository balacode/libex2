/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                      [libex_canvas.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_canvas_.h"
#if defined INCLUDED_LIBEX_CANVAS_H

#include "libex_config_.h"

#include <string.h>  /* for memset() */

#if PLATFORM_WIN32
#include "libex_win32_.h"
#include <wingdi.h>
#include <winuser.h>
#if defined _MSC_VER
#pragma comment (lib, "user32.lib")
/*      DrawText()               */
/*      GetClientRect()          */
/*      GetDC()                  */
/*      WindowFromDC()           */
#pragma comment (lib, "gdi32.lib")
/*      AngleArc()               */
/*      BeginPath()              */
/*      BitBlt()                 */
/*      CreateCompatibleBitmap() */
/*      CreateCompatibleDC()     */
/*      CreatePen()              */
/*      CreateRectRgn()          */
/*      CreateSolidBrush()       */
/*      DeleteObject()           */
/*      Ellipse()                */
/*      EndPath()                */
/*      ExtSelectClipRgn()       */
/*      ExtTextOut()             */
/*      GetClipRgn()             */
/*      GetMapMode()             */
/*      GetStockObject()         */
/*      GetTextExtentPoint32()   */
/*      LineTo()                 */
/*      MoveToEx()               */
/*      Polygon()                */
/*      Polyline()               */
/*      Rectangle()              */
/*      RoundRect()              */
/*      SelectClipRgn()          */
/*      SelectObject()           */
/*      SetBkColor()             */
/*      SetBkMode()              */
/*      SetDCBrushColor()        */
/*      SetMapMode()             */
/*      SetTextColor()           */
/*      SetWindowOrgEx()         */
/*      StrokeAndFillPath()      */
#endif
#endif                                                      /* PLATFORM_WIN32 */

#include "libex_.h"
#include "libex_call_.h"
#include "libex_const_.h"
#include "libex_logging_.h"
#include "libex_macro_.h"
#include "libex_string_class_.h"
#include "libex_stringc_.h"
#include "libex_system_.h"
#include "libex_type_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif


/* -------------------------------------------------------------------------- */
/* Macros:                                                                    */

#undef       CHECK_FOR_NULL_OBJECT
#if !defined CHECK_FOR_NULL_OBJECT
#define CHECK_FOR_NULL_OBJECT( OBJECT_, SRC_UID_ )                             \
    {                                                                          \
        if (OBJECT_ == NULL)                                                   \
        {   DEBUG_WARN(_T("object_ == NULL"), SRC_UID_);  RETURN(NULL); }      \
    }                                                                      /*#*/
#endif                                              /* !CHECK_FOR_NULL_OBJECT */

#define _ASSERT_DC                                      \
    if (&object_->hdc == NULL || object_->hdc == NULL)  \
    {       RETURN(NIL) }                           /*#*/

#define _INIT_XY                                  \
    const pixel_t  x = x_ + object_->area.x;      \
    const pixel_t  y = y_ + object_->area.y;  /*#*/

#define _INIT_XY2                                   \
    const pixel_t  x1 = x1_ + object_->area.x;      \
    const pixel_t  y1 = y1_ + object_->area.y;      \
    const pixel_t  x2 = x2_ + object_->area.x;      \
    const pixel_t  y2 = y2_ + object_->area.y;  /*#*/

#define _SET_COLOR( OBJECT_, ARG_ )             \
    if (ARG_ != COLOR_NULL)                     \
    {       Canvas_color(object_, ARG_); }  /*#*/


/* -------------------------------------------------------------------------- */
/* WinGDI.h                                                                   */


#if !defined _DC_BRUSH
#define _DC_BRUSH  18
#endif

#if !defined _DC_PEN
#define _DC_PEN  19
#endif


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


/* -------------------------------------------------------------------------- */
/* Functions: Private                                                         */


#if defined __GNUC__
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wunused-function"
#endif


static void  _gradient_fill(                                               /*F*/
    canvas_t*      object_,                                                /*-*/
    pixel_t        x_,                                                     /*-*/
    pixel_t        y_,                                                     /*-*/
    const pixel_t  width_,                                                 /*-*/
    const pixel_t  height_,                                                /*-*/
    const color_t  color1_,                                                /*-*/
    const color_t  color2_,                                                /*-*/
    const bool     vertical_fill_ ) {                                      /*-*/
    GO                                                            (UID(FB9671));
#if PLATFORM_LINUX
    IMPLEMENT_LINUX();  /* TODO: implement _gradient_fill() on Linux */
    UNUSED(object_);
    UNUSED(x_);
    UNUSED(y_);
    UNUSED(width_);
    UNUSED(height_);
    UNUSED(color1_);
    UNUSED(color2_);
    UNUSED(vertical_fill_);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    double    blue       = 0;
    double    green      = 0;
    double    red        = 0;
    double    grow_blue  = 0;
    double    grow_green = 0;
    double    grow_red   = 0;
    int       i          = 0;
    RECT_win  rect       = { 0, 0, 0, 0 };
    color_t   color1     = { 0 };
    color_t   color2     = { 0 };
    pixel_t   size       = 0;

    _INIT_XY;
    _ASSERT_DC;

    if (object_->hdc == NULL) {
        RETURN(NIL);
    }

    color1 = Color_rgb(color1_);
    color2 = Color_rgb(color2_);

    rect.left   = CAST(LONG_win, x);
    rect.top    = CAST(LONG_win, y);
    rect.right  = CAST(LONG_win, x + width_);
    rect.bottom = CAST(LONG_win, y + height_);

    red   = Color_getRed(color1);
    green = Color_getGreen(color1);
    blue  = Color_getBlue(color1);

    size       = vertical_fill_ ? height_ : width_;
    grow_red   = (Color_getRed(color2)   - red)   / size;
    grow_green = (Color_getGreen(color2) - green) / size;
    grow_blue  = (Color_getBlue(color2)  - blue)  / size;

    for (i = 0; i < size; i++) {
        if (vertical_fill_) {
            rect.top    = CAST(LONG_win, y + i);
            rect.bottom = CAST(LONG_win, y + i + 1);

            if (rect.bottom > y + height_) {
                rect.bottom = CAST(LONG_win, y + height_);
            }
        } else {
            rect.left  = CAST(LONG_win, x + i);
            rect.right = CAST(LONG_win, x + i + 1);

            if (rect.right > x + width_) {
                rect.right = CAST(LONG_win, x + width_);
            }
        }

        OS_VERIFY(CLR_INVALID_win != SetBkColor_win(
                      object_->hdc,
                      Color_fromRgb(CAST(uint8_t, red),
                                    CAST(uint8_t, green),
                                    CAST(uint8_t, blue))), UID(E88D53));

        OS_VERIFY(ExtTextOut_win(
                      object_->hdc,
                      0, 0, ETO_OPAQUE_win, &rect, NULL, 0, NULL), UID(E87483));

        red   += grow_red;
        green += grow_green;
        blue  += grow_blue;
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* _gradient_fill */


#if PLATFORM_WIN32
static HBRUSH_win  _set_brush( const canvas_t*  object_ ) {                /*F*/
    GO                                                            (UID(F9FE59));
    const HBRUSH_win  ret =
        CAST(HBRUSH_win, SelectObject_win(
                 object_->hdc, GetStockObject_win(_DC_BRUSH)));

    OS_VERIFY(HGDI_ERROR_win != ret, UID(E89D6E));
    OS_VERIFY(CLR_INVALID_win != SetDCBrushColor_win(
                  object_->hdc, Color_rgb(object_->color)), UID(E3ECDE));
    RETURN(ret);
} /* _set_brush */
#endif                                                      /* PLATFORM_WIN32 */


/* Private: create a new pen and select it into object_->hdc.                 */
/* Call with make_pen_ = false to destroy the                                 */
/* previously-created pen, without creating any new one.                      */

static void  _make_pen(                                                    /*F*/
    canvas_t*   object_,                                                   /*-*/
    const bool  make_pen_ ) {                                              /*-*/
    GO                                                            (UID(FB481B));
#if PLATFORM_LINUX
    IMPLEMENT_LINUX();  /* TODO: implement _make_pen() on Linux */
    UNUSED(object_);
    UNUSED(make_pen_);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    static HPEN_win  static_old_pen = NULL;

    HPEN_win  new_pen = NULL;
    HPEN_win  old_pen = NULL;

    /* create and select a new pen */
    if (make_pen_) {
        new_pen = CreatePen_win(
                      PS_SOLID_win,                    /* pen style */
                      CAST(int, object_->line_width),  /* pen width */
                      Color_rgb(object_->color));   /* pen color */

        OS_VERIFY(new_pen != NULL, UID(EFBC40));

        if (new_pen) {
            old_pen = CAST(HPEN_win, SelectObject_win(object_->hdc, new_pen));
        }
    }

    /* destroy the old pen */
    if (static_old_pen != NULL &&
        (!make_pen_ || (make_pen_ && new_pen != NULL &&
                        old_pen == static_old_pen))) {

        OS_VERIFY(DeleteObject_win(static_old_pen), UID(ECE113));
        static_old_pen = NULL;
    }

    /* remember the handle of the pen */
    if (new_pen) {
        static_old_pen = new_pen;
    }

#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* _make_pen */


/* -------------------------------------------------------------------------- */
/* Temporary Stubs:                                                           */


#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4100)  /* W:L4 unreferenced formal parameter         */
#endif


PUBLIC void  Rect_setSize(                                                 /*M*/
    rect_t*        object_,                                                /*-*/
    const pixel_t  width_,                                                 /*-*/
    const pixel_t  height_ ) {                                             /*-*/
    GO                                                            (UID(FCB19D));
    UNUSED(object_);
    UNUSED(width_);
    UNUSED(height_);
    /* TODO: implement Rect_setSize() */
    RETURN(NIL);
} /* Rect_setSize */


PUBLIC void  Rect_clear( rect_t*  object_ ) {                              /*M*/
    GO                                                            (UID(FF0F2E));
    UNUSED(object_);
    /* TODO: implement Rect_clear() */
    RETURN(NIL);
} /* Rect_clear */


PUBLIC pixel_t  Rect_x2( const rect_t*  object_ ) {                        /*M*/
    GO                                                            (UID(F25108));
    UNUSED(object_);
    RETURN(0);  /* TODO: implement Rect_x2() */
} /* Rect_x2 */


PUBLIC pixel_t  Rect_y2( const rect_t*  object_ ) {                        /*M*/
    GO                                                            (UID(F26017));
    UNUSED(object_);
    RETURN(0);  /* TODO: implement Rect_y2() */
} /* Rect_y2 */


PUBLIC void  Canvas_fontSet(                                               /*M*/
    CanvasFont*        object_,                                            /*-*/
    const CanvasFont*  font_ ) {                                           /*-*/
    GO                                                            (UID(FB997A));
    UNUSED(object_);
    UNUSED(font_);
    /* TODO: implement Canvas_fontSet() */
    RETURN(NIL);
} /* Canvas_fontSet */


PUBLIC void  Canvas_fontSet7(                                              /*M*/
    CanvasFont*  object_,                                                  /*-*/
    chars_t      font_name_,                                               /*-*/
    const int    font_size_,                                               /*-*/
    const bool   bold_,                                                    /*-*/
    const bool   italic_,                                                  /*-*/
    const bool   underline_,                                               /*-*/
    const bool   strikeout_,                                               /*-*/
    const int    angle_ ) {                                                /*-*/
    GO                                                            (UID(F18BDE));
    UNUSED(object_);
    UNUSED(font_name_);
    UNUSED(font_size_);
    UNUSED(bold_);
    UNUSED(italic_);
    UNUSED(underline_);
    UNUSED(strikeout_);
    UNUSED(angle_);
    /* TODO: implement Canvas_fontSet7() */
    RETURN(NIL);
} /* Canvas_fontSet7 */


PUBLIC int  Poly_count( const poly_t*  object_ ) {                         /*P*/
    GO                                                            (UID(FEF863));
    UNUSED(object_);
    RETURN(0);  /* TODO: implement Poly_count() */
} /* Poly_count */


#if PLATFORM_WIN32
PUBLIC HFONT_win  Canvas_fontHfont( CanvasFont*  object_ ) {               /*P*/
    GO                                                            (UID(FF7EA0));
    RETURN(0);  /* TODO: implement Canvas_fontHfont() */
} /* Canvas_fontHfont */
#endif                                                      /* PLATFORM_WIN32 */


#if defined _MSC_VER
#pragma warning (pop)
#endif


/* -------------------------------------------------------------------------- */
/* Constructors / Destructor:                                                 */


PUBLIC canvas_t  Canvas_init( void ) {                                     /*C*/
    GO                                                            (UID(F75581));
    canvas_t  ret;
    CLEAR(ret);

    ret.area.x          = 0;
    ret.area.y          = 0;
    ret.area.width      = 0;
    ret.area.height     = 0;

    ret.line_width      = 1;
    ret.color           = COLOR_BLACK;

    MEMCPY(ret.font.name, _T("Arial"), 6 * sizeof(char_t));
    ret.font.size       = 9;
    ret.font.bold       = false;
    ret.font.italic     = false;
    ret.font.underline  = false;
    ret.font.strikeout  = false;
    ret.font.angle      = 0;

    ret.attached_canvas = false;
    ret.is_clipped      = false;
    ret.is_offscreen    = false;
    ret.memory_prepared = false;

#if PLATFORM_WIN32
    ret.old_map_mode    = 0;
    ret.old_bk_mode     = 0;
    ret.old_pen         = NULL;
    ret.main_dc         = NULL;
    ret.mem_dc          = NULL;
    ret.hdc             = NULL;
    ret.old_clip_region = NULL;
    ret.mem_bitmap      = NULL;
    ret.old_mem_bitmap  = NULL;
#endif

    RETURN(ret);
} /* Canvas_init */


PUBLIC canvas_t  Canvas_initCopy( const canvas_t*  canvas_ ) {             /*C*/
    GO                                                            (UID(F9FF80));
    canvas_t  ret = Canvas_init();
    Canvas_set(&ret, canvas_);
    RETURN(ret);
} /* Canvas_initCopy */


PUBLIC canvas_t  Canvas_initCopyAndPosition(                               /*C*/
    const canvas_t*  canvas_,                                              /*-*/
    const rect_t     rectangle_ ) {                                        /*-*/
    GO                                                            (UID(F69F31));
    canvas_t  ret = Canvas_init();
    Canvas_set(&ret, canvas_);
    ret.area = rectangle_;
    RETURN(ret);
} /* Canvas_initCopyAndPosition */


/* Constructor                                                                */
#if PLATFORM_WIN32
PUBLIC canvas_t  Canvas_fromDC( const HDC_win  hdc_ ) {                    /*C*/
    GO                                                            (UID(FE6A50));
    canvas_t  ret = Canvas_init();
    Canvas_attachToDC(&ret, hdc_, true);
    RETURN(ret);
} /* Canvas_fromDC */
#endif                                                      /* PLATFORM_WIN32 */


PUBLIC void  Canvas_free( canvas_t*  object_ ) {                           /*D*/
    GO                                                            (UID(F146CF));
    if (object_->is_offscreen) {
        object_->is_offscreen = false;
        Canvas_endBuffering(object_);
    }

    _make_pen(object_, false);

    if (object_->attached_canvas) {
        RETURN(NIL);
    } else {
#if PLATFORM_WIN32
        _ASSERT_DC;
        OS_VERIFY(SetMapMode_win(object_->main_dc, object_->old_map_mode),
                  UID(EFE5E8));
        OS_VERIFY(SetBkMode_win(object_->main_dc, object_->old_bk_mode),
                  UID(E62854));
        OS_VERIFY(SelectObject_win(object_->main_dc, object_->old_pen),
                  UID(EF95FA));
#endif                                                      /* PLATFORM_WIN32 */
    }
    RETURN(NIL);
} /* Canvas_free */


/* -------------------------------------------------------------------------- */
/* Operators:                                                                 */


PUBLIC canvas_t*  Canvas_opAssign(                                         /*O*/
    canvas_t*        object_,                                              /*-*/
    const canvas_t*  copy_from_ ) {                                        /*-*/
    GO                                                            (UID(FEEDE9));
    CHECK_FOR_NULL_OBJECT(object_, UID(E2C083));

    object_->attached_canvas = copy_from_->attached_canvas;
    object_->is_clipped      = copy_from_->is_clipped;
    object_->is_offscreen    = copy_from_->is_offscreen;
    object_->memory_prepared = copy_from_->memory_prepared;

#if PLATFORM_WIN32
    object_->old_map_mode    = copy_from_->old_map_mode;
    object_->old_bk_mode     = copy_from_->old_bk_mode;
    object_->old_pen         = copy_from_->old_pen;
    object_->main_dc         = copy_from_->main_dc;
    object_->mem_dc          = copy_from_->mem_dc;
    object_->hdc             = copy_from_->hdc;
    object_->old_clip_region = copy_from_->old_clip_region;
    object_->mem_bitmap      = copy_from_->mem_bitmap;
    object_->old_mem_bitmap  = copy_from_->old_mem_bitmap;
#endif

    RETURN(object_);
} /* Canvas_opAssign */


/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */


PUBLIC void  Canvas_set(                                                   /*M*/
    canvas_t*        object_,                                              /*-*/
    const canvas_t*  canvas_ ) {                                           /*-*/
    GO                                                            (UID(F38BCE));
    object_->line_width      = canvas_->line_width;
    object_->color           = canvas_->color;
    object_->font            = canvas_->font;

    object_->is_clipped      = canvas_->is_clipped;
    object_->is_offscreen    = canvas_->is_offscreen;
    object_->memory_prepared = canvas_->memory_prepared;

#if PLATFORM_WIN32
    object_->old_clip_region = canvas_->old_clip_region;
    object_->old_map_mode    = canvas_->old_map_mode;
    object_->old_bk_mode     = canvas_->old_bk_mode;
    object_->old_pen         = canvas_->old_pen;
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Canvas_set */


PUBLIC canvas_t*  Canvas_screen( void ) {                                  /*F*/
    GO                                                            (UID(F78455));
    static canvas_t  canvas;

#if PLATFORM_WIN32
    const HDC_win  screen_dc = GetDC_win(NULL);
    Canvas_attachToDC(&canvas, screen_dc, false);
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(&canvas);
} /* Canvas_screen */


PUBLIC void  Canvas_attachTo(                                              /*M*/
    canvas_t*        object_,                                              /*-*/
    const canvas_t*  canvas_,                                              /*-*/
    const bool       resize_ ) {                                           /*-*/
    GO                                                            (UID(F284E2));
    if (resize_) {
        object_->area.x      = canvas_->area.x;
        object_->area.y      = canvas_->area.y;
        object_->area.width  = canvas_->area.width;
        object_->area.height = canvas_->area.height;
    }

#if PLATFORM_WIN32
    Canvas_attachToDC(object_, canvas_->hdc, false);
    object_->attached_canvas = true;
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Canvas_attachTo */


#if PLATFORM_WIN32
PUBLIC void  Canvas_attachToDC(                                            /*M*/
    canvas_t*      object_,                                                /*-*/
    const HDC_win  hdc_,                                                   /*-*/
    const bool     resize_ ) {                                             /*-*/
    GO                                                            (UID(F6BCE0));
    object_->main_dc = object_->hdc = hdc_;

    if (hdc_ == NULL) {
        object_->old_map_mode = 0;
        object_->old_bk_mode  = 0;
        object_->old_pen      = NULL;

        _make_pen(object_, false);
    } else {
        object_->old_map_mode = SetMapMode_win(object_->main_dc, MM_TEXT_win);
        OS_VERIFY(object_->old_map_mode, UID(EB1253));
        object_->old_bk_mode = SetBkMode_win(object_->main_dc, TRANSPARENT_win);
        OS_VERIFY(object_->old_bk_mode, UID(E6E1A1));
        object_->old_pen = CAST(HPEN_win, SelectObject_win(
                                    object_->hdc,
                                    GetStockObject_win(_DC_PEN)));
        OS_VERIFY(object_->old_pen, UID(E29E51));
        _make_pen(object_, true);
    }

    if (resize_) {
        Canvas_resize(object_);
    }
    RETURN(NIL);
} /* Canvas_attachToDC */
#endif                                                      /* PLATFORM_WIN32 */


PUBLIC void  Canvas_detach( canvas_t*  object_ ) {                         /*M*/
    GO                                                            (UID(F72F79));
#if PLATFORM_LINUX
    IMPLEMENT_LINUX();  /* TODO: implement Canvas_detach() on Linux */
    UNUSED(object_);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    _ASSERT_DC;
    _make_pen(object_, false);

    OS_VERIFY(SetMapMode_win(object_->main_dc, object_->old_map_mode),
              UID(E6C7DD));

    OS_VERIFY(SetBkMode_win(object_->main_dc, object_->old_bk_mode),
              UID(EE5BA6));

    OS_VERIFY(SelectObject_win(object_->main_dc, object_->old_pen),
              UID(EBAB87));
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Canvas_detach */


PUBLIC void  Canvas_resize( canvas_t*  object_ ) {                         /*M*/
    GO                                                            (UID(FEC70A));
#if PLATFORM_LINUX
    IMPLEMENT_LINUX();  /* TODO: implement Canvas_resize() on Linux */
    UNUSED(object_);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    HWND_win  hwnd = NULL;

    /* get the dimensions of the window's client area */
    /* (if DC is not a memory DC)                     */
    Rect_clear(&object_->area);

    hwnd = WindowFromDC_win(object_->main_dc);

    if (hwnd != NULL) {
        RECT_win  rect;
        OS_VERIFY(GetClientRect_win(hwnd, &rect), UID(E7561D));
        Rect_setSize(&object_->area, rect.right, rect.bottom);
    }

#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Canvas_resize */


#if defined UNIMPLEMENTED
PUBLIC void  Canvas_clipRect(                                              /*M*/
    canvas_t*      object_,                                                /*-*/
    const pixel_t  x_,                                                     /*-*/
    const pixel_t  y_,                                                     /*-*/
    const pixel_t  width_,                                                 /*-*/
    const pixel_t  height_ ) {                                             /*-*/
    GO                                                            (UID(F544EB));
    UNUSED(x_);
    UNUSED(y_);
    UNUSED(width_);
    UNUSED(height_);
    /* TODO: implement clip_rect() */
    RETURN(NIL);
} /* Canvas_clipRect */
#endif                                                       /* UNIMPLEMENTED */


#if 111
PUBLIC void  Canvas_clip( canvas_t*  object_ ) {                           /*M*/
    GO                                                            (UID(F82F0D));
#if PLATFORM_LINUX
    IMPLEMENT_LINUX();  /* TODO: implement Canvas_clip() on Linux */
    UNUSED(object_);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    _ASSERT_DC;
    object_->old_clip_region = clip_rect(object_->hdc,
                                         object_->area.x,
                                         object_->area.y,
                                         Rect_x2(&object_->area),
                                         Rect_y2(&object_->area),
                                         true);
    object_->is_clipped = true;
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Canvas_clip */
#endif                                                                 /* 111 */


PUBLIC void  Canvas_unclip( canvas_t*  object_ ) {                         /*M*/
    GO                                                            (UID(F52BA7));
#if PLATFORM_LINUX
    IMPLEMENT_LINUX();  /* TODO: implement Canvas_unclip() on Linux */
    UNUSED(object_);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    _ASSERT_DC;

    if (!object_->is_clipped) {
        RETURN(NIL);
    }

    free_clipping_rect(object_->hdc, object_->old_clip_region);
    object_->is_clipped = false;
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Canvas_unclip */


/* -------------------------------------------------------------------------- */
/* Properties: Canvas Interface                                               */


PUBLIC pixel_t  Canvas_x( const canvas_t*  object_ ) {                     /*P*/
    GO                                                            (UID(F7973B));
    const pixel_t  ret = object_->area.x;
    RETURN(ret);
} /* Canvas_x */


PUBLIC pixel_t  Canvas_y( const canvas_t*  object_ ) {                     /*P*/
    GO                                                            (UID(FC659E));
    const pixel_t  ret = object_->area.y;
    RETURN(ret);
} /* Canvas_y */


PUBLIC pixel_t  Canvas_width( const canvas_t*  object_ ) {                 /*P*/
    GO                                                            (UID(F60967));
    const pixel_t  ret = object_->area.width;
    RETURN(ret);
} /* Canvas_width */


PUBLIC pixel_t  Canvas_height( const canvas_t*  object_ ) {                /*P*/
    GO                                                            (UID(F4AF43));
    const pixel_t  ret = object_->area.height;
    RETURN(ret);
} /* Canvas_height */


PUBLIC pixel_t  Canvas_x2( const canvas_t*  object_ ) {                    /*P*/
    GO                                                            (UID(F34C9F));
    const pixel_t  ret = Rect_x2(&object_->area);
    RETURN(ret);
} /* Canvas_x2 */


PUBLIC pixel_t  Canvas_y2( const canvas_t*  object_ ) {                    /*P*/
    GO                                                            (UID(FE7A77));
    const pixel_t  ret = Rect_y2(&object_->area);
    RETURN(ret);
} /* Canvas_y2 */


/* -------------------------------------------------------------------------- */
/* Methods: Canvas Interface                                                  */


PUBLIC void  Canvas_clear(                                                 /*M*/
    canvas_t*      object_,                                                /*-*/
    const color_t  color_ ) {                                              /*-*/
    GO                                                            (UID(F80B08));
    const color_t  null = COLOR_NULL;
    _SET_COLOR(object_, color_);
    Canvas_rectFill(object_, object_->area, null, SHADE_SOLID, null);
    RETURN(NIL);
} /* Canvas_clear */


PUBLIC void  Canvas_beginBuffering( canvas_t*  object_ ) {                 /*M*/
    GO                                                            (UID(F0D9D6));
#if PLATFORM_LINUX
    IMPLEMENT_LINUX();
    UNUSED(object_);
    /* TODO: implement Canvas_beginBuffering() on Linux */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32

    if (!object_->memory_prepared) {
        object_->mem_dc = CreateCompatibleDC_win(object_->main_dc);
        OS_VERIFY(object_->mem_dc, UID(E9BA32));

        object_->mem_bitmap = CreateCompatibleBitmap_win(
                                  object_->main_dc,
                                  CAST(int, object_->area.width),
                                  CAST(int, object_->area.height));

        OS_VERIFY(object_->mem_bitmap, UID(ED41B8));

        object_->old_mem_bitmap =
            CAST(HBITMAP_win, SelectObject_win(object_->mem_dc,
                                               object_->mem_bitmap));

        OS_VERIFY(object_->old_mem_bitmap != HGDI_ERROR_win, UID(E97F6B));

        OS_VERIFY(SetMapMode_win(object_->mem_dc,
                                 GetMapMode_win(object_->main_dc)),
                  UID(E1D804));

        OS_VERIFY(SetWindowOrgEx_win(object_->mem_dc,
                                     CAST(int, object_->area.x),
                                     CAST(int, object_->area.y),
                                     NULL), UID(E9F4A1));

        object_->memory_prepared = true;
    }

    object_->hdc = object_->mem_dc;
    object_->is_offscreen = true;
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Canvas_beginBuffering */


PUBLIC void  Canvas_endBuffering( canvas_t*  object_ ) {                   /*M*/
    GO                                                            (UID(F605D0));
#if PLATFORM_LINUX
    IMPLEMENT_LINUX();
    UNUSED(object_);
    /* TODO: implement Canvas_endBuffering() on Linux */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32

    if (object_->is_offscreen) {
        OS_VERIFY(BitBlt_win(object_->main_dc,
                             CAST(int, object_->area.x),
                             CAST(int, object_->area.y),
                             CAST(int, object_->area.width),
                             CAST(int, object_->area.height),
                             object_->mem_dc,
                             CAST(int, object_->area.x),
                             CAST(int, object_->area.y),
                             SRCCOPY_win), UID(E49256));

        object_->is_offscreen = false;
    }

    OS_VERIFY(HGDI_ERROR_win != SelectObject_win(
                  object_->mem_dc, object_->old_mem_bitmap), UID(E06DCE));

    object_->old_mem_bitmap = NULL;

    if (object_->mem_bitmap) {
        OS_VERIFY(DeleteObject_win(object_->mem_bitmap), UID(E1A17F));
    }

    object_->memory_prepared = false;
    object_->hdc = object_->main_dc;
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Canvas_endBuffering */


/* Current settings                                                           */


PUBLIC void  Canvas_area(                                                  /*M*/
    canvas_t*     object_,                                                 /*-*/
    const rect_t  rect_ ) {                                                /*-*/
    GO                                                            (UID(F261C0));
    object_->area = rect_;
    RETURN(NIL);
} /* Canvas_area */


PUBLIC void  Canvas_lineWidth(                                             /*M*/
    canvas_t*      object_,                                                /*-*/
    const pixel_t  line_width_ ) {                                         /*-*/
    GO                                                            (UID(F77C89));
    object_->line_width = line_width_;

#if PLATFORM_WIN32
    if (object_->hdc != NULL) {
        _make_pen(object_, true);
    }
#endif

    RETURN(NIL);
} /* Canvas_lineWidth */


PUBLIC void  Canvas_color(                                                 /*M*/
    canvas_t*      object_,                                                /*-*/
    const color_t  color_ ) {                                              /*-*/
    GO                                                            (UID(F77CA2));
    object_->color = color_;

#if PLATFORM_WIN32
    if (object_->hdc != NULL) {
        color_t  rgb = Color_rgb(object_->color);
        OS_VERIFY(CLR_INVALID_win != SetTextColor_win(object_->hdc, rgb),
                  UID(EFBFD3));
        _make_pen(object_, true);
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Canvas_color */


PUBLIC void  Canvas_font(                                                  /*M*/
    canvas_t*          object_,                                            /*-*/
    const CanvasFont*  font_ ) {                                           /*-*/
    GO                                                            (UID(F6CCFF));
    Canvas_fontSet(&object_->font, font_);
    RETURN(NIL);
} /* Canvas_font */


PUBLIC void  Canvas_font7(                                                 /*M*/
    canvas_t*   object_,                                                   /*-*/
    chars_t     font_name_,                                                /*-*/
    const int   font_size_,                                                /*-*/
    const bool  bold_,                                                     /*-*/
    const bool  italic_,                                                   /*-*/
    const bool  underline_,                                                /*-*/
    const bool  strikeout_,                                                /*-*/
    const int   angle_ ) {                                                 /*-*/
    GO                                                            (UID(FBAC1D));
    Canvas_fontSet7(&object_->font, font_name_, font_size_,
                    bold_, italic_, underline_, strikeout_, angle_);

    RETURN(NIL);
} /* Canvas_font */


/* point */


PUBLIC void  Canvas_point(                                                 /*M*/
    canvas_t*      object_,                                                /*-*/
    const pixel_t  x_,                                                     /*-*/
    const pixel_t  y_,                                                     /*-*/
    const color_t  color_ ) {                                              /*-*/
    GO                                                            (UID(F01120));
#if PLATFORM_LINUX
    IMPLEMENT_LINUX();  /* TODO: implement Canvas_point() on Linux */
    UNUSED(object_);
    UNUSED(x_);
    UNUSED(y_);
    UNUSED(color_);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    _INIT_XY;
    _ASSERT_DC;
    _SET_COLOR(object_, color_);

    OS_VERIFY(MoveToEx_win(object_->hdc,
                           CAST(int, x), CAST(int, y), NULL), UID(EAE31E));

    OS_VERIFY(LineTo_win(object_->hdc,
                         CAST(int, x + 1), CAST(int, y + 1)), UID(E9F7AC));
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Canvas_point */


/* line */


PUBLIC void  Canvas_line(                                                  /*M*/
    canvas_t*      object_,                                                /*-*/
    const pixel_t  x1_,                                                    /*-*/
    const pixel_t  y1_,                                                    /*-*/
    const pixel_t  x2_,                                                    /*-*/
    const pixel_t  y2_,                                                    /*-*/
    const color_t  color_ ) {                                              /*-*/
    GO                                                            (UID(FB41F1));
#if PLATFORM_LINUX
    IMPLEMENT_LINUX();  /* TODO: implement Canvas_line() on Linux */
    UNUSED(object_);
    UNUSED(x1_);
    UNUSED(y1_);
    UNUSED(x2_);
    UNUSED(y2_);
    UNUSED(color_);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    _INIT_XY2;
    _ASSERT_DC;

    _SET_COLOR(object_, color_);

    OS_VERIFY(MoveToEx_win(object_->hdc,
                           CAST(int, x1), CAST(int, y1), NULL), UID(EEBD49));

    OS_VERIFY(LineTo_win(object_->hdc,
                         CAST(int, x2), CAST(int, y2)), UID(EA6B5F));

    /* to draw last pixel */
    OS_VERIFY(LineTo_win(object_->hdc,
                         CAST(int, x1), CAST(int, y1)), UID(E2E558));
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Canvas_line */


/* rectangle */


PUBLIC void  Canvas_rect(                                                  /*M*/
    canvas_t*      object_,                                                /*-*/
    const rect_t*  rectangle_,                                             /*-*/
    const color_t  color_ ) {                                              /*-*/
    GO                                                            (UID(F73814));
    Canvas_rectTo(object_,
                  rectangle_->x,
                  rectangle_->y,
                  Rect_x2(rectangle_),
                  Rect_y2(rectangle_),
                  color_);

    RETURN(NIL);
} /* Canvas_rect */


PUBLIC void  Canvas_rect5(                                                 /*M*/
    canvas_t*      object_,                                                /*-*/
    const pixel_t  x_,                                                     /*-*/
    const pixel_t  y_,                                                     /*-*/
    const pixel_t  width_,                                                 /*-*/
    const pixel_t  height_,                                                /*-*/
    const color_t  color_ ) {                                              /*-*/
    GO                                                            (UID(FB510D));
    Canvas_rectTo(object_,
                  x_,
                  y_,
                  x_ + width_  - 1,
                  y_ + height_ - 1,
                  color_);

    RETURN(NIL);
} /* Canvas_rect5 */


PUBLIC void  Canvas_rectTo(                                                /*M*/
    canvas_t*      object_,                                                /*-*/
    const pixel_t  x1_,                                                    /*-*/
    const pixel_t  y1_,                                                    /*-*/
    const pixel_t  x2_,                                                    /*-*/
    const pixel_t  y2_,                                                    /*-*/
    const color_t  color_ ) {                                              /*-*/
    GO                                                            (UID(FB7B58));
#if PLATFORM_LINUX
    /* TODO: implement NCanvas_rectToNN() on Linux */
    IMPLEMENT_LINUX();
    UNUSED(object_);
    UNUSED(x1_);
    UNUSED(y1_);
    UNUSED(x2_);
    UNUSED(y2_);
    UNUSED(color_);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    HBRUSH_win  old_brush = NULL;

    _INIT_XY2;
    _ASSERT_DC;
    _SET_COLOR(object_, color_);

    /* select pen and brush */
    old_brush = CAST(HBRUSH_win, SelectObject_win(object_->hdc,
                     GetStockObject_win(NULL_BRUSH_win)));
    OS_VERIFY(old_brush != HGDI_ERROR_win, UID(E4551C));

    /* draw the box (up to the specified end coordinates) */
    OS_VERIFY(Rectangle_win(object_->hdc,
                            CAST(int, x1),     CAST(int, y1),
                            CAST(int, x2 + 1), CAST(int, y2 + 1)), UID(EE4EBD));

    /* restore the old pen and brush */
    OS_VERIFY(HGDI_ERROR_win != SelectObject_win(object_->hdc, old_brush),
              UID(E52ECA));
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Canvas_rectTo */


PUBLIC void  Canvas_rectFill(                                              /*M*/
    canvas_t*           object_,                                           /*-*/
    const rect_t        rectangle_,                                        /*-*/
    const color_t       color1_,                                           /*-*/
    const shading_enum  shade_,                                            /*-*/
    const color_t       color2_or_shine_ ) {                               /*-*/
    GO                                                            (UID(FFD637));
    Canvas_rectFill7(object_, rectangle_.x, rectangle_.y,
                     rectangle_.width, rectangle_.height,
                     color1_, shade_, color2_or_shine_);
    RETURN(NIL);
} /* Canvas_rectFill */


PUBLIC void  Canvas_rectFillTo(                                            /*M*/
    canvas_t*           object_,                                           /*-*/
    const pixel_t       x1_,                                               /*-*/
    const pixel_t       y1_,                                               /*-*/
    const pixel_t       x2_,                                               /*-*/
    const pixel_t       y2_,                                               /*-*/
    const color_t       color1_,                                           /*-*/
    const shading_enum  shade_,                                            /*-*/
    const color_t       color2_or_shine_ ) {                               /*-*/
    GO                                                            (UID(FF2321));
    Canvas_rectFill7(object_, x1_, y1_,
                     x2_ - x1_ + 1, y2_ - y1_ + 1,
                     color1_, shade_, color2_or_shine_);
    RETURN(NIL);
} /* Canvas_rectFillTo */


PUBLIC void  Canvas_rectFill7(                                             /*M*/
    canvas_t*           object_,                                           /*-*/
    const pixel_t       x_,                                                /*-*/
    const pixel_t       y_,                                                /*-*/
    const pixel_t       width_,                                            /*-*/
    const pixel_t       height_,                                           /*-*/
    const color_t       color1_,                                           /*-*/
    const shading_enum  shade_,                                            /*-*/
    const color_t       color2_or_shine_ ) {                               /*-*/
    GO                                                            (UID(F78E81));
#if PLATFORM_LINUX
    /* TODO: implement Canvas_rectFill7() on Linux */
    IMPLEMENT_LINUX();
    UNUSED(object_);
    UNUSED(x_);
    UNUSED(y_);
    UNUSED(width_);
    UNUSED(height_);
    UNUSED(color1_);
    UNUSED(shade_);
    UNUSED(color2_or_shine_);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    RECT_win  rect      = { 0, 0, 0, 0 };
    color_t   light1    = { 0 };
    color_t   light2    = { 0 };
    color_t   mid_color = { 0 };

    _INIT_XY;
    _ASSERT_DC;

    if (width_ < 1 || height_ < 1) {
        RETURN(NIL);
    }

    if (shade_ == SHADE_SOLID) {
        _SET_COLOR(object_, color1_);

        rect.left   = CAST(LONG_win, x);
        rect.top    = CAST(LONG_win, y);
        rect.right  = CAST(LONG_win, x + width_);
        rect.bottom = CAST(LONG_win, y + height_);

        OS_VERIFY(CLR_INVALID_win != SetBkColor_win(object_->hdc,
                  Color_rgb(object_->color)), UID(EFB182));

        OS_VERIFY(ExtTextOut_win(object_->hdc, 0, 0,
                                 ETO_OPAQUE_win, &rect, NULL, 0, NULL),
                  UID(EB3261));

    } else if (shade_ == SHADE_HORIZONTAL_GLOSSY ||
               shade_ == SHADE_VERTICAL_GLOSSY) {

        const int  color_red   = Color_getRed(color1_);
        const int  color_green = Color_getGreen(color1_);
        const int  color_blue  = Color_getBlue(color1_);

        const int  dark_red    = ABS(CAST(int, color_red   - 85));
        const int  dark_green  = ABS(CAST(int, color_green - 85));
        const int  dark_blue   = ABS(CAST(int, color_blue  - 85));

        const int  len =
            shade_ == SHADE_HORIZONTAL_GLOSSY ? CAST(int, width_)  :
            shade_ == SHADE_VERTICAL_GLOSSY   ? CAST(int, height_) : 0;

        const int  half = len / 2;

        int  red   = 0;
        int  green = 0;
        int  blue  = 0;

        const int  color2_or_shine = 0;  /* color2_or_shine_ */

        /* 0 = no white shine - > 100 = max white shine */
        int  shine = color2_or_shine == CAST(int, COLOR_NULL) ?
                     75 : CAST(int, color2_or_shine);
        shine = GREATER(0, LESSER(shine, 95));

        red   = dark_red   + (color_red   - dark_red)   / len;
        green = dark_green + (color_green - dark_green) / len;
        blue  = dark_blue  + (color_blue  - dark_blue)  / len;

        light1 = Color_blend(
                     Color_fromRgb(red, green, blue),
                     Color_fromValue(COLOR_WHITE),
                     LESSER(100 - shine, 100));

        red   = dark_red   + ((half - 1) * (color_red   - dark_red)   / len);
        green = dark_green + ((half - 1) * (color_green - dark_green) / len);
        blue  = dark_blue  + ((half - 1) * (color_blue  - dark_blue)  / len);

        light2 = Color_blend(
                     Color_fromRgb(red, green, blue),
                     Color_fromValue(COLOR_WHITE),
                     LESSER((100 - shine) * half, 100));

        red   = dark_red   + (color_red   - dark_red)   / 2;
        green = dark_green + (color_green - dark_green) / 2;
        blue  = dark_blue  + (color_blue  - dark_blue)  / 2;

        mid_color = Color_fromRgb(red, green, blue);

        if (shade_ == SHADE_HORIZONTAL_GLOSSY) {
            _gradient_fill(object_, x, y, half, height_, light1, light2,
                           false);

            _gradient_fill(object_, x + half, y, half, height_, mid_color,
                           color1_, false);

        } else if (shade_ == SHADE_VERTICAL_GLOSSY) {
            _gradient_fill(object_, x, y, width_, half, light1, light2, true);

            _gradient_fill(object_, x, y + half, width_, half, mid_color,
                           color1_, true);
        }

    } else if (shade_ == SHADE_HORIZONTAL_SMOOTH) {
        _gradient_fill(object_, x, y, width_, height_, color1_,
                       color2_or_shine_, false);

    } else if (shade_ == SHADE_VERTICAL_SMOOTH) {
        _gradient_fill(object_, x, y, width_, height_, color1_,
                       color2_or_shine_, true);
    }

#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Canvas_rectFill7 */


/* rounded rectangle */


PUBLIC void  Canvas_roundedRectFill(                                       /*M*/
    canvas_t*      object_,                                                /*-*/
    rect_t         rectangle_,                                             /*-*/
    const pixel_t  round_corner_size_,                                     /*-*/
    const color_t  color_ ) {                                              /*-*/
    GO                                                            (UID(FE4284));
    Canvas_roundedRectFillTo(object_,
                             rectangle_.x,
                             rectangle_.y,
                             Rect_x2(&rectangle_),
                             Rect_y2(&rectangle_),
                             round_corner_size_,
                             color_);
    RETURN(NIL);
} /* Canvas_roundedRectFill */


PUBLIC void  Canvas_roundedRectFill6(                                      /*M*/
    canvas_t*      object_,                                                /*-*/
    const pixel_t  x_,                                                     /*-*/
    const pixel_t  y_,                                                     /*-*/
    const pixel_t  width_,                                                 /*-*/
    const pixel_t  height_,                                                /*-*/
    const pixel_t  round_corner_size_,                                     /*-*/
    const color_t  color_ ) {                                              /*-*/
    GO                                                            (UID(F22078));
    Canvas_roundedRectFillTo(object_,
                             x_,
                             y_,
                             x_ + width_  - 1,
                             y_ + height_ - 1,
                             round_corner_size_,
                             color_);
    RETURN(NIL);
} /* Canvas_roundedRectFill6 */


PUBLIC void  Canvas_roundedRectFillTo(                                     /*M*/
    canvas_t*      object_,                                                /*-*/
    const pixel_t  x1_,                                                    /*-*/
    const pixel_t  y1_,                                                    /*-*/
    const pixel_t  x2_,                                                    /*-*/
    const pixel_t  y2_,                                                    /*-*/
    const pixel_t  round_corner_size_,                                     /*-*/
    const color_t  color_ ) {                                              /*-*/
    GO                                                            (UID(FBEFF9));
#if PLATFORM_LINUX
    /* TODO: implement Canvas_roundedRectFillTo() on Linux */
    IMPLEMENT_LINUX();
    UNUSED(object_);
    UNUSED(x1_);
    UNUSED(y1_);
    UNUSED(x2_);
    UNUSED(y2_);
    UNUSED(round_corner_size_);
    UNUSED(color_);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    HGDIOBJ_win  old_pen   = NULL;
    HBRUSH_win   old_brush = NULL;

    _SET_COLOR(object_, color_);

    /* create brush and pen */
    old_pen = SelectObject_win(object_->hdc, GetStockObject_win(NULL_PEN_win));

    /* select brush */
    old_brush = _set_brush(object_);
    OS_VERIFY(old_brush != HGDI_ERROR_win, UID(ECB2BB));

    RoundRect_win(object_->hdc,
                  CAST(int, x1_), CAST(int, y1_),
                  CAST(int, x2_), CAST(int, y2_),
                  CAST(int, round_corner_size_),
                  CAST(int, round_corner_size_));

    /* restore the old pen and brush */
    OS_VERIFY(HGDI_ERROR_win != SelectObject_win(object_->hdc, old_brush),
              UID(EA1308));

    OS_VERIFY(HGDI_ERROR_win != SelectObject_win(object_->hdc, old_pen),
              UID(EE8B6B));
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Canvas_roundedRectFillTo */


/* ellipse                                                                    */


PUBLIC void  Canvas_ellipse(                                               /*M*/
    canvas_t*      object_,                                                /*-*/
    const rect_t*  rectangle_,                                             /*-*/
    const color_t  color_ ) {                                              /*-*/
    GO                                                            (UID(F417EA));
    Canvas_ellipseTo(object_, rectangle_->x, rectangle_->y,
                     Rect_x2(rectangle_), Rect_y2(rectangle_), color_);
    RETURN(NIL);
} /* Canvas_ellipse */


PUBLIC void  Canvas_ellipse5(                                              /*M*/
    canvas_t*      object_,                                                /*-*/
    const pixel_t  x_,                                                     /*-*/
    const pixel_t  y_,                                                     /*-*/
    const pixel_t  width_,                                                 /*-*/
    const pixel_t  height_,                                                /*-*/
    const color_t  color_ ) {                                              /*-*/
    GO                                                            (UID(FF705C));
    Canvas_ellipseTo(object_, x_, y_,
                     x_ + width_ - 1, y_ + height_ - 1, color_);

    RETURN(NIL);
} /* Canvas_ellipse5 */


PUBLIC void  Canvas_ellipseTo(                                             /*M*/
    canvas_t*      object_,                                                /*-*/
    const pixel_t  x1_,                                                    /*-*/
    const pixel_t  y1_,                                                    /*-*/
    const pixel_t  x2_,                                                    /*-*/
    const pixel_t  y2_,                                                    /*-*/
    const color_t  color_ ) {                                              /*-*/
    GO                                                            (UID(F8F2AB));
#if PLATFORM_LINUX
    /* TODO: implement Canvas_ellipseTo() on Linux */
    IMPLEMENT_LINUX();
    UNUSED(object_);
    UNUSED(x1_);
    UNUSED(y1_);
    UNUSED(x2_);
    UNUSED(y2_);
    UNUSED(color_);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    HBRUSH_win  old_brush = NULL;

    _INIT_XY2;
    _ASSERT_DC;
    _SET_COLOR(object_, color_);

    /* select a transparent brush */
    old_brush = CAST(HBRUSH_win, SelectObject_win(object_->hdc,
                     GetStockObject_win(NULL_BRUSH_win)));
    OS_VERIFY(old_brush != HGDI_ERROR_win, UID(EF15C5));

    OS_VERIFY(Ellipse_win(
                  object_->hdc,
                  CAST(int, x1), CAST(int, y1),
                  CAST(int, x2), CAST(int, y2)), UID(EBBF89));

    /* restore the old brush */
    OS_VERIFY(HGDI_ERROR_win != SelectObject_win(object_->hdc, old_brush),
              UID(E10FA0));
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Canvas_ellipseTo */


PUBLIC void  Canvas_ellipseFill(                                           /*M*/
    canvas_t*      object_,                                                /*-*/
    const rect_t*  rectangle_,                                             /*-*/
    const color_t  color_ ) {                                              /*-*/
    GO                                                            (UID(F30518));
    Canvas_ellipseFillTo(object_, rectangle_->x, rectangle_->y,
                         Rect_x2(rectangle_), Rect_y2(rectangle_),
                         color_);
    RETURN(NIL);
} /* Canvas_ellipseFill */


PUBLIC void  Canvas_ellipseFill5(                                          /*M*/
    canvas_t*      object_,                                                /*-*/
    const pixel_t  x_,                                                     /*-*/
    const pixel_t  y_,                                                     /*-*/
    const pixel_t  width_,                                                 /*-*/
    const pixel_t  height_,                                                /*-*/
    const color_t  color_ ) {                                              /*-*/
    GO                                                            (UID(F4F9FA));
    Canvas_ellipseFillTo(object_, x_, y_, x_ + width_, y_ + height_, color_);

    RETURN(NIL);
} /* Canvas_ellipseFill5 */


PUBLIC void  Canvas_ellipseFillTo(                                         /*M*/
    canvas_t*      object_,                                                /*-*/
    const pixel_t  x1_,                                                    /*-*/
    const pixel_t  y1_,                                                    /*-*/
    const pixel_t  x2_,                                                    /*-*/
    const pixel_t  y2_,                                                    /*-*/
    const color_t  color_ ) {                                              /*-*/
    GO                                                            (UID(F6B0EF));
#if PLATFORM_LINUX
    /* TODO: implement Canvas_ellipseFillTo() on Linux */
    IMPLEMENT_LINUX();
    UNUSED(object_);
    UNUSED(x1_);
    UNUSED(y1_);
    UNUSED(x2_);
    UNUSED(y2_);
    UNUSED(color_);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    HBRUSH_win  old_brush = NULL;

    _INIT_XY2;
    _ASSERT_DC;
    _SET_COLOR(object_, color_);

    /* select brush */
    old_brush = _set_brush(object_);
    OS_VERIFY(old_brush != HGDI_ERROR_win, UID(E719C5));

    /* draw the filled ellipse */
    OS_VERIFY(Ellipse_win(object_->hdc,
                          CAST(int, x1), CAST(int, y1),
                          CAST(int, x2), CAST(int, y2)), UID(E1EAA4));

    /* restore the old pen and brush */
    OS_VERIFY(HGDI_ERROR_win != SelectObject_win(object_->hdc, old_brush),
              UID(EB9AAC));
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Canvas_ellipseFillTo */


/* polygon                                                                    */


PUBLIC void  Canvas_poly(                                                  /*M*/
    canvas_t*      object_,                                                /*-*/
    const poly_t*  polygon_,                                               /*-*/
    const color_t  color_,                                                 /*-*/
    const pixel_t  offset_x_,                                              /*-*/
    const pixel_t  offset_y_ ) {                                           /*-*/
    GO                                                            (UID(FF72BB));
#if PLATFORM_LINUX
    IMPLEMENT_LINUX();  /* TODO: implement Canvas_poly() on Linux */
    UNUSED(object_);
    UNUSED(polygon_);
    UNUSED(color_);
    UNUSED(offset_x_);
    UNUSED(offset_y_);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    _ASSERT_DC;
    /* TODO: This has to be adjusted over each point. _INIT_XY2; */

    _SET_COLOR(object_, color_);
    {
        /* copy polygon object's data to temporary PONT array, for Polyline() */
        /* + 1 is to copy the first point                                     */
        POINT_win*  points = MALLOC((Poly_count(polygon_) + 1)
                                    * sizeof(POINT_win));
        int  i;
        for (i = 0; i < Poly_count(polygon_); i++) {
            points[i].x = CAST(LONG_win, polygon_->points[i].x + offset_x_);
            points[i].y = CAST(LONG_win, polygon_->points[i].y + offset_y_);
        }

        points[Poly_count(polygon_)].x =
            CAST(LONG_win, polygon_->points[0].x + offset_x_);

        points[Poly_count(polygon_)].y =
            CAST(LONG_win, polygon_->points[0].y + offset_y_);

        /* draw the polygon's outline */
        Polyline_win(object_->hdc, points, Poly_count(polygon_) + 1);

        /* release the temporary array */
        FREE(points);
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Canvas_poly */


PUBLIC void  Canvas_polyFill(                                              /*M*/
    canvas_t*      object_,                                                /*-*/
    const poly_t*  polygon_,                                               /*-*/
    const color_t  color_,                                                 /*-*/
    const pixel_t  offset_x_,                                              /*-*/
    const pixel_t  offset_y_ ) {                                           /*-*/
    GO                                                            (UID(F78164));
#if PLATFORM_LINUX
    /* TODO: implement Canvas_polyFill() on Linux */
    IMPLEMENT_LINUX();
    UNUSED(object_);
    UNUSED(polygon_);
    UNUSED(color_);
    UNUSED(offset_x_);
    UNUSED(offset_y_);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    _ASSERT_DC;
    /* TODO: This has to be adjusted over each point. _INIT_XY2; */
    _SET_COLOR(object_, color_);
    {
        /* create brush and pen */
        const HGDIOBJ_win  old_pen = SelectObject_win(
                                         object_->hdc,
                                         GetStockObject_win(NULL_PEN_win));

        /* select brush */
        const HBRUSH_win  old_brush = _set_brush(object_);
        OS_VERIFY(old_brush != HGDI_ERROR_win, UID(E9ED32));

        {
            /* copy polygon object's data to temporary */
            /* POINT_win  array, for Polygon_win()     */
            POINT_win*   points =
                MALLOC(Poly_count(polygon_) * sizeof(POINT_win));

            int  i = 0;
            for (i = 0; i < Poly_count(polygon_); i++) {
                points[i].x = CAST(LONG_win, polygon_->points[i].x + offset_x_);
                points[i].y = CAST(LONG_win, polygon_->points[i].y + offset_y_);
            }

            /* draw the filled polygon */
            Polygon_win(object_->hdc, points, Poly_count(polygon_));

            FREE(points);
        }

        /* restore the old pen and brush */
        OS_VERIFY(HGDI_ERROR_win
                  != SelectObject_win(object_->hdc, old_brush), UID(EBCC0D));

        OS_VERIFY(HGDI_ERROR_win
                  != SelectObject_win(object_->hdc, old_pen), UID(E7E0E1));
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Canvas_polyFill */


PUBLIC void  draw_up_down_arrow(                                           /*F*/
    canvas_t*      object_,                                                /*-*/
    const pixel_t  x_,                                                     /*-*/
    const pixel_t  y_,                                                     /*-*/
    const pixel_t  width_,                                                 /*-*/
    const pixel_t  height_,                                                /*-*/
    const color_t  back_color_,                                            /*-*/
    const color_t  arrow_color_,                                           /*-*/
    const color_t  border_color_,                                          /*-*/
    const bool     down_arrow_ ) {                                         /*-*/
    GO                                                            (UID(FF6E1A));
    const pixel_t  ARROW_HEIGHT = 3;

    color_t  old_color  = { 0 };
    pixel_t  line_width = 0;
    pixel_t  y          = 0;
    pixel_t  arrow_x    = 0;
    pixel_t  arrow_y    = 0;

#if PLATFORM_WIN32
    _ASSERT_DC;
#endif

    /* _INIT_XY; don't adjust the X and Y coordinate, */
    /* because other called methods do it already     */

    /* save the currently selected color */
    old_color = object_->color;

    /* draw the background and border of the arrow */
    Canvas_rectFill7(object_, x_, y_, width_, height_, back_color_,
                     SHADE_SOLID, COLOR_NULL);

    Canvas_rect5(object_, x_, y_, width_, height_, border_color_);

    arrow_x = x_ + (CAST(double, width_) / 2) - 1;
    arrow_y = y_ + ((CAST(double, height_) - ARROW_HEIGHT) / 2) - 1;

    if (down_arrow_) {
        arrow_y += ARROW_HEIGHT;
    }

    /* draw the arrow */
    Canvas_color(object_, arrow_color_);

    for (y = 1; y <= ARROW_HEIGHT; y++) {
        Canvas_line(object_, arrow_x, arrow_y,
                    arrow_x + line_width, arrow_y, COLOR_NULL);

        arrow_x--;

        if (down_arrow_) {
            arrow_y--;
        } else {
            arrow_y++;
        }

        line_width += 2;
    }

    /* restore the old color setting */
    Canvas_color(object_, old_color);

    RETURN(NIL);
} /* draw_up_down_arrow */


PUBLIC void  Canvas_text(                                                  /*M*/
    canvas_t*      object_,                                                /*-*/
    chars_t        text_,                                                  /*-*/
    const color_t  color_ ) {                                              /*-*/
    GO                                                            (UID(F77B12));
#if PLATFORM_WIN32
    SelectObject_win(
        object_->hdc,
        Canvas_fontHfont(&object_->font));
#endif                                                      /* PLATFORM_WIN32 */

    Canvas_text4(object_,
                 object_->area.x, object_->area.y, text_, color_);
    /*object_->area.x += Canvas_textWidth(text_); */

    RETURN(NIL);
} /* Canvas_text */


PUBLIC void  Canvas_text4(                                                 /*M*/
    canvas_t*      object_,                                                /*-*/
    const pixel_t  x_,                                                     /*-*/
    const pixel_t  y_,                                                     /*-*/
    chars_t        text_,                                                  /*-*/
    const color_t  color_ ) {                                              /*-*/
    GO                                                            (UID(FEF71B));
#if PLATFORM_LINUX
    IMPLEMENT_LINUX();  /* TODO: implement Canvas_text4() on Linux */
    UNUSED(object_);
    UNUSED(x_);
    UNUSED(y_);
    UNUSED(text_);
    UNUSED(color_);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    if (IS_BLANK(text_)) {
        RETURN(NIL);
    }

    {
        _INIT_XY;
        _ASSERT_DC;
        _SET_COLOR(object_, color_);

        SelectObject_win(object_->hdc, Canvas_fontHfont(&object_->font));

        {
            const int  len  = CAST(int, STRLEN_T(text_));
            RECT_win   rect = { 0, 0, 0, 0 };

            rect.left   = CAST(LONG_win, x);
            rect.top    = CAST(LONG_win, y);
            rect.right  = CAST(LONG_win, x + 1);
            rect.bottom = CAST(LONG_win, y + 1);

            OS_VERIFY(DrawText_win(object_->hdc, text_, len, &rect,
                                   DT_NOCLIP_win) != 0, UID(E517CB));
        }
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Canvas_text4 */


PUBLIC pixel_t  Canvas_textLineHeight( canvas_t*  object_ ) {              /*M*/
    GO                                                            (UID(F2F658));
    pixel_t  ret = 0;

#if PLATFORM_WIN32
    if (object_->hdc != NULL)
#endif
    {
        ret = Canvas_textHeight(object_, ASCII_CHARS);
    }
    RETURN(ret);
} /* Canvas_textLineHeight */


/* returns text height in logical coordinates                                 */
PUBLIC pixel_t  Canvas_textHeight(                                         /*M*/
    canvas_t*  object_,                                                    /*-*/
    chars_t    text_ ) {                                                   /*-*/
    GO                                                            (UID(FD4024));
    pixel_t  ret = 0;

#if PLATFORM_LINUX
    IMPLEMENT_LINUX();  /* TODO: implement Canvas_textHeight() on Linux */
    UNUSED(object_);
    UNUSED(text_);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    SIZE_win  text_size = { 0, 0 };

    if (object_->hdc == NULL || IS_BLANK(text_)) {
        RETURN(0);
    }

    SelectObject_win(
        object_->hdc,
        Canvas_fontHfont(&object_->font));

    /* get the height of one line of text */
    OS_VERIFY(GetTextExtentPoint32_win(object_->hdc, text_,
                                       CAST(int, STRLEN_T(text_)), &text_size),
              UID(EEAB3B));
    ret = text_size.cy;

    /* if the text contains carriage returns (\r) or new lines (\n), */
    /* multiply by number of lines                                   */
    if (contains2T(text_, _T("\n")) ||
        contains2T(text_, _T("\r"))) {

        str_t  text = S_chars(text_);
        replace3InS(&text, _T("\r\n"), _T("\n"));
        replace3InS(&text, _T("\n\r"), _T("\n"));
        replace3InS(&text, _T("\r"),   _T("\n"));
        {
            const size_t  lines = tokenCountXtS(text, _T("\n"), NULL,
                                                IGNORE_CASE);
            ret *= lines;
        }
        freeS(&text);
    }

#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* Canvas_textHeight */


/* returns text width in logical coordinates                                  */
PUBLIC pixel_t  Canvas_textWidth(                                          /*M*/
    canvas_t*  object_,                                                    /*-*/
    chars_t    text_ ) {                                                   /*-*/
    GO                                                            (UID(F99438));
    pixel_t  ret = 0;

#if PLATFORM_LINUX
    IMPLEMENT_LINUX();  /* TODO: implement Canvas_textWidth() on Linux */
    UNUSED(object_);
    UNUSED(text_);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    new_chars_t  part      = NULL;
    SIZE_win     text_size = { 0, 0 };
    LONG_win     max       = 0;

    if (object_->hdc == NULL || IS_BLANK(text_)) {
        RETURN(0);
    }

    SelectObject_win(
        object_->hdc,
        Canvas_fontHfont(&object_->font));

    if (contains2T(text_, _T("\n"))) {
        const size_t  count = token_countT(text_, _T("\n"));
        size_t        i     = 0;

        for (i = 0; i < count; i++) {
            part = T_get_token(text_, i, _T("\n"));
            OS_VERIFY(GetTextExtentPoint32_win(
                          object_->hdc, part,
                          CAST(int, lenT(part)),
                          &text_size),                             UID(E949A6));

            if (max < text_size.cx) {
                max = text_size.cx;
            }
        }

        ret = max;
    } else {
        OS_VERIFY(GetTextExtentPoint32_win(object_->hdc,
                                           text_,
                                           CAST(int, STRLEN_T(text_)),
                                           &text_size),            UID(E7E101));
        ret = text_size.cx;
    }

#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* Canvas_textWidth */


/* -------------------------------------------------------------------------- */
/* Methods: Static                                                            */


#if PLATFORM_WIN32
PUBLIC HRGN_win  clip_rect(                                                /*F*/
    const HDC_win  hdc_,                                                   /*-*/
    const pixel_t  x1_,                                                    /*-*/
    const pixel_t  y1_,                                                    /*-*/
    const pixel_t  x2_,                                                    /*-*/
    const pixel_t  y2_,                                                    /*-*/
    const bool     in_existing_clip_ ) {                                   /*-*/
    GO                                                            (UID(F5901E));
    HRGN_win  ret  = NULL;
    HRGN_win  hrgn = 0;
    INT_win   mode = 0;

    if (hdc_ == NULL) {
        RETURN(NULL);
    }

    {
        /* get a handle to the current clipping region: */
        const int  result = GetClipRgn_win(hdc_, ret);
        if (result == 0) { /* no selected clipping region */
            ret = NULL;
        } else if (result == (-1)) {
            OS_ERR(_T("GetClipRgn()"), UID(E71F4F));
            RETURN(NULL);
        }
    }

    /* define the clipping region specified by coordinates */
    hrgn = CreateRectRgn_win(CAST(int, x1_), CAST(int, y1_),
                             CAST(int, x2_), CAST(int, y2_));

    if (hrgn == NULL) {
        OS_ERR(_T("CreateRectRgn()"), UID(E021D0));
        RETURN(NULL);
    }

    /* create a new region from the intersection */
    /* of the existing and specified regions     */
    mode = in_existing_clip_ ? RGN_AND_win : RGN_COPY_win;

    if (ExtSelectClipRgn_win(hdc_, hrgn, mode) == ERROR_win) {
        OS_ERR(_T("ExtSelectClipRgn() == ERROR_win"), UID(E609A3));
        RETURN(NULL);
    }

    /* destroy the new clipping region definition (already applied) */
    OS_VERIFY(DeleteObject_win(hrgn), UID(EFA98C));

    RETURN(ret);  /* return handle to current clipping region */
} /* clip_rect */
#endif                                                      /* PLATFORM_WIN32 */


#if PLATFORM_WIN32
PUBLIC void  free_clipping_rect(                                           /*F*/
    const HDC_win   hdc_,                                                  /*-*/
    const HRGN_win  old_region_ ) {                                        /*-*/
    GO                                                            (UID(F7FDD6));
    if (hdc_ == NULL) {
        RETURN(NIL);
    }
    OS_VERIFY(SelectClipRgn_win(hdc_, old_region_) != ERROR_win, UID(EC786E));
    RETURN(NIL);
} /* free_clipping_rect */
#endif                                                      /* PLATFORM_WIN32 */


#if (000)
PUBLIC void  Canvas_test_pie( void)  /* draws pie chart segments */ {      /*F*/
    GO                                                            (UID(FF324B));
    pixel_t            x           = 200;
    pixel_t            y           = 200;
    DWORD_win          radius      = 100;
    float              start_angle = 90;
    float              sweep_angle = 20;
    color_t            color       = COLOR_ORANGE;
    const HBRUSH_win   brush       = CreateSolidBrush_win(color);
    const HGDIOBJ_win  old_brush   = SelectObject_win(object_->hdc, brush);
    const HGDIOBJ_win  old_pen     = SelectObject_win(
                                         object_->hdc,
                                         GetStockObject_win(NULL_PEN_win));

    BeginPath_win(object_->hdc);
    {
        start_angle -= 90;
        MoveToEx_win(object_->hdc, x, y, LPPOINT_win(NULL));
        AngleArc_win(object_->hdc, x, y, radius, -start_angle, -sweep_angle);
        LineTo_win(object_->hdc, x, y);
    }
    EndPath_win(object_->hdc);
    StrokeAndFillPath_win(object_->hdc);

    SelectObject_win(object_->hdc, old_pen);
    SelectObject_win(object_->hdc, old_brush);
    DeleteObject_win(brush);

    RETURN(NIL);
} /* TestPie */
#endif                                                                 /* 000 */


PUBLIC void  test_canvas( const canvas_t*  object_ ) {                     /*F*/
    GO                                                            (UID(FFF3FE));
    /* pixel_t    x           = 200; */
    /* pixel_t    y           = 200; */
    /* DWORD_win  radius      = 100; */
    /* float      start_angle = 90;  */
    /* float      sweep_angle = 20;  */

    color_t  color = COLOR_ORANGE;

#if PLATFORM_LINUX
    IMPLEMENT_LINUX();  /* TODO: implement test_canvas() on Linux */
    UNUSED(object_);
    UNUSED(color);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    const HBRUSH_win   brush     = CreateSolidBrush_win(color);
    const HGDIOBJ_win  old_brush = SelectObject_win(object_->hdc, brush);
    const HGDIOBJ_win  old_pen   = SelectObject_win(
                                       object_->hdc,
                                       GetStockObject_win(NULL_PEN_win));

    const POINT_win  points[5] = {
        { 83, 134 }, { 214, 86 }, { 430, 49 }, { 491, 154 }, { 295, 350 }
    };

    Polygon_win(object_->hdc, points, 5);

    SelectObject_win(object_->hdc, old_pen);
    SelectObject_win(object_->hdc, old_brush);
    DeleteObject_win(brush);
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* test_canvas */


#undef _ASSERT_DC
#undef _INIT_XY
#undef _INIT_XY2

END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
