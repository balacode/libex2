/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                     [libex_canvas_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_CANVAS__H
#define      INCLUDED_LIBEX_CANVAS__H
#include "libex_canvas.h"

#include "libex_color_.h"

/* -------------------------------------------------------------------------- */
/* External Types                                                             */

#define shading_enum                    lx_shading_enum
#define SHADE_SOLID                     LX_SHADE_SOLID
#define SHADE_VERTICAL_SMOOTH           LX_SHADE_VERTICAL_SMOOTH
#define SHADE_VERTICAL_GLOSSY           LX_SHADE_VERTICAL_GLOSSY
#define SHADE_HORIZONTAL_SMOOTH         LX_SHADE_HORIZONTAL_SMOOTH
#define SHADE_HORIZONTAL_GLOSSY         LX_SHADE_HORIZONTAL_GLOSSY

#define CanvasFont                      lx_CanvasFont
#define Canvas_fontSet                  lx_Canvas_fontSet
#define Canvas_fontSet7                 lx_Canvas_fontSet7

#if LX_PLATFORM_WIN32
#define Canvas_fontHfont                lx_Canvas_fontHfont
#endif

/* -------------------------------------------------------------------------- */

#define poly_point_t                    lx_poly_point_t

#define poly_t                          lx_poly_t
#define Poly_count                      lx_Poly_count

#define rect_t                          lx_rect_t
#define Rect_clear                      lx_Rect_clear
#define Rect_setSize                    lx_Rect_setSize
#define Rect_x2                         lx_Rect_x2
#define Rect_y2                         lx_Rect_y2

/* -------------------------------------------------------------------------- */

#define canvas_t                        lx_canvas_t

/* -------------------------------------------------------------------------- */
/* Constructors / Destructor:                                                 */

#define Canvas_init                     lx_Canvas_init
#define Canvas_initCopy                 lx_Canvas_initCopy
#define Canvas_initCopyAndPosition      lx_Canvas_initCopyAndPosition

#if LX_PLATFORM_WIN32
#define Canvas_fromDC                   lx_Canvas_fromDC
#endif

#define Canvas_free                     lx_Canvas_free

/* -------------------------------------------------------------------------- */
/* Operators:                                                                 */

#define Canvas_opAssign                 lx_Canvas_opAssign


/* Methods: Public */

#define Canvas_set                      lx_Canvas_set
#define Canvas_screen                   lx_Canvas_screen
#define Canvas_attachTo                 lx_Canvas_attachTo

#if LX_PLATFORM_WIN32
#define Canvas_attachToDC               lx_Canvas_attachToDC
#endif

#define Canvas_detach                   lx_Canvas_detach
#define Canvas_resize                   lx_Canvas_resize

/* -------------------------------------------------------------------------- */
/* Implementation: lx::lx_CanvasI                                             */

/* Properties: Public */

#define Canvas_x                        lx_Canvas_x
#define Canvas_y                        lx_Canvas_y
#define Canvas_width                    lx_Canvas_width
#define Canvas_height                   lx_Canvas_height
#define Canvas_x2                       lx_Canvas_x2
#define Canvas_y2                       lx_Canvas_y2

/* Methods: Public */
#define Canvas_area                     lx_Canvas_area
#define Canvas_lineWidth                lx_Canvas_lineWidth
#define Canvas_color                    lx_Canvas_color
#define Canvas_font                     lx_Canvas_font
#define Canvas_font7                    lx_Canvas_font7
#define Canvas_clear                    lx_Canvas_clear
#define Canvas_beginBuffering           lx_Canvas_beginBuffering
#define Canvas_endBuffering             lx_Canvas_endBuffering
#define Canvas_clipRect                 lx_Canvas_clipRect
#define Canvas_clip                     lx_Canvas_clip
#define Canvas_unclip                   lx_Canvas_unclip
#define Canvas_point                    lx_Canvas_point
#define Canvas_line                     lx_Canvas_line
#define Canvas_rect                     lx_Canvas_rect
#define Canvas_rect5                    lx_Canvas_rect5
#define Canvas_rectTo                   lx_Canvas_rectTo
#define Canvas_rectFill                 lx_Canvas_rectFill
#define Canvas_rectFill7                lx_Canvas_rectFill7
#define Canvas_rectFillTo               lx_Canvas_rectFillTo
#define Canvas_roundedRectFill          lx_Canvas_roundedRectFill
#define Canvas_roundedRectFill6         lx_Canvas_roundedRectFill6
#define Canvas_roundedRectFillTo        lx_Canvas_roundedRectFillTo
#define Canvas_ellipse                  lx_Canvas_ellipse
#define Canvas_ellipse5                 lx_Canvas_ellipse5
#define Canvas_ellipseTo                lx_Canvas_ellipseTo
#define Canvas_ellipseFill              lx_Canvas_ellipseFill
#define Canvas_ellipseFill5             lx_Canvas_ellipseFill5
#define Canvas_ellipseFillTo            lx_Canvas_ellipseFillTo
#define Canvas_poly                     lx_Canvas_poly
#define Canvas_polyFill                 lx_Canvas_polyFill
#define Canvas_text                     lx_Canvas_text
#define Canvas_text4                    lx_Canvas_text4
#define Canvas_textLineHeight           lx_Canvas_textLineHeight
#define Canvas_textHeight               lx_Canvas_textHeight
#define Canvas_textWidth                lx_Canvas_textWidth

/* Public: */

#define draw_up_down_arrow              lx_draw_up_down_arrow

/* Functions: Public, Static */

#if LX_PLATFORM_WIN32
#define clip_rect                       lx_clip_rect
#define free_clipping_rect              lx_free_clipping_rect
#endif

#define test_canvas                     lx_test_canvas

#endif                                                                   /*eof*/
