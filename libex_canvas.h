/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                      [libex_canvas.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_CANVAS_H
#define      INCLUDED_LIBEX_CANVAS_H

#if LX_PLATFORM_WIN32
#include "libex_win32.h"
#endif

#include "libex_canvas.h"
#include "libex_color.h"

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

/* -------------------------------------------------------------------------- */
/* External Types                                                             */

typedef enum  _lx_shading_enum {
    LX_SHADE_SOLID             = 0,              /* lx_shading_enum * 0 0 0 0 */
    LX_SHADE_VERTICAL_SMOOTH   = 1,              /* lx_shading_enum * 0 0 0 1 */
    LX_SHADE_VERTICAL_GLOSSY   = 2,              /* lx_shading_enum * 0 0 1 0 */
    LX_SHADE_HORIZONTAL_SMOOTH = 4,              /* lx_shading_enum * 0 1 0 0 */
    LX_SHADE_HORIZONTAL_GLOSSY = 8               /* lx_shading_enum * 1 0 0 0 */
}
lx_shading_enum;                                                        /*enum*/

typedef struct  lx_CanvasFont {
    lx_char_t  name[32];                                     /* lx_CanvasFont */
    int        size;                                         /* lx_CanvasFont */
    lx_bool    bold;                                         /* lx_CanvasFont */
    lx_bool    italic;                                       /* lx_CanvasFont */
    lx_bool    underline;                                    /* lx_CanvasFont */
    lx_bool    strikeout;                                    /* lx_CanvasFont */
    int        angle;                                        /* lx_CanvasFont */
}
lx_CanvasFont;

void  lx_Canvas_fontSet(                                                   /*M*/
    lx_CanvasFont*        object_,                                         /*-*/
    const lx_CanvasFont*  font_ );                                         /*-*/

void  lx_Canvas_fontSet7(                                                  /*M*/
    lx_CanvasFont*  object_,                                               /*-*/
    lx_chars_t      font_name_,                                            /*-*/
    const int       font_size_,                                            /*-*/
    const lx_bool   bold_,                                                 /*-*/
    const lx_bool   italic_,                                               /*-*/
    const lx_bool   underline_,                                            /*-*/
    const lx_bool   strikeout_,                                            /*-*/
    const int       angle_ );                                              /*-*/

#if LX_PLATFORM_WIN32
HFONT_win  lx_Canvas_fontHfont( lx_CanvasFont*  object_ );                 /*M*/
#endif

/* -------------------------------------------------------------------------- */

typedef struct  lx_poly_point_t {
    lx_pixel_t  x;                                         /* lx_poly_point_t */
    lx_pixel_t  y;                                         /* lx_poly_point_t */
}
lx_poly_point_t;

typedef struct  lx_poly_t {
    lx_char_t         id[32];                                    /* lx_poly_t */
    lx_color_t        color;                                     /* lx_poly_t */
    lx_poly_point_t*  points;                                    /* lx_poly_t */
}
lx_poly_t;

int  lx_Poly_count( const lx_poly_t*  object_ );                           /*P*/

typedef struct  lx_rect_t { /* TODO: what is the difference with Rect? */
    lx_pixel_t  x;                                               /* lx_rect_t */
    lx_pixel_t  y;                                               /* lx_rect_t */
    lx_pixel_t  width;                                           /* lx_rect_t */
    lx_pixel_t  height;                                          /* lx_rect_t */
}
lx_rect_t;

LX_PUBLIC void  lx_Rect_clear( lx_rect_t*  object_ );                      /*M*/

LX_PUBLIC void  lx_Rect_setSize(                                           /*M*/
    lx_rect_t*        object_,                                             /*-*/
    const lx_pixel_t  width_,                                              /*-*/
    const lx_pixel_t  height_ );                                           /*-*/

LX_PUBLIC lx_pixel_t  lx_Rect_x2( const lx_rect_t*  object_ );             /*M*/

LX_PUBLIC lx_pixel_t  lx_Rect_y2( const lx_rect_t*  object_ );             /*M*/

/* -------------------------------------------------------------------------- */

typedef struct  lx_canvas_t {

    lx_rect_t         area;                                    /* lx_canvas_t */

    lx_pixel_t        line_width;                              /* lx_canvas_t */
    /* width of lines in pix. */

    lx_color_t        color;                                   /* lx_canvas_t */
    /* Current drawing color */

    lx_CanvasFont     font;                                    /* lx_canvas_t */

    lx_bool           attached_canvas;                         /* lx_canvas_t */
    lx_bool           is_clipped;                              /* lx_canvas_t */
    lx_bool           is_offscreen;                            /* lx_canvas_t */
    lx_bool           memory_prepared;                         /* lx_canvas_t */

#if LX_PLATFORM_WIN32

    int               old_map_mode;                            /* lx_canvas_t */
    int               old_bk_mode;                             /* lx_canvas_t */
    HPEN_win          old_pen;                                 /* lx_canvas_t */

    HDC_win           main_dc;                                 /* lx_canvas_t */
    /* Direct device context */

    HDC_win           mem_dc;                                  /* lx_canvas_t */
    /* Memory device context */

    HDC_win           hdc;                                     /* lx_canvas_t */
    /* Active device context */

    HRGN_win          old_clip_region;                         /* lx_canvas_t */
    HBITMAP_win       mem_bitmap;                              /* lx_canvas_t */
    HBITMAP_win       old_mem_bitmap;                          /* lx_canvas_t */

#endif                                                   /* LX_PLATFORM_WIN32 */
}
lx_canvas_t;

/* -------------------------------------------------------------------------- */
/* Constructors / Destructor:                                                 */

/* Default Constructor */
LX_PUBLIC lx_canvas_t  lx_Canvas_init( void );                             /*C*/

/* Copy Constructor */
LX_PUBLIC lx_canvas_t  lx_Canvas_initCopy(                                 /*C*/
    const lx_canvas_t*  canvas_ );                                         /*-*/

/* Copy Constructor */
LX_PUBLIC lx_canvas_t  lx_Canvas_initCopyAndPosition(                      /*C*/
    const lx_canvas_t*  canvas_,                                           /*-*/
    const lx_rect_t     rectangle_ );                                      /*-*/

#if LX_PLATFORM_WIN32
/* Constructor */
LX_PUBLIC lx_canvas_t  lx_Canvas_fromDC( const HDC_win  hdc_ );            /*C*/
#endif                                                   /* LX_PLATFORM_WIN32 */

/* Destructor */
LX_PUBLIC void  lx_Canvas_free( lx_canvas_t*  object_ );                   /*D*/

/* -------------------------------------------------------------------------- */
/* Operators:                                                                 */

LX_PUBLIC lx_canvas_t*  lx_Canvas_opAssign(                                /*O*/
    lx_canvas_t*        object_,                                           /*-*/
    const lx_canvas_t*  copy_from_ );                                      /*-*/

/* Methods: Public                                                            */

LX_PUBLIC void  lx_Canvas_set(                                             /*M*/
    lx_canvas_t*        object_,                                           /*-*/
    const lx_canvas_t*  canvas_ );                                         /*-*/

LX_PUBLIC lx_canvas_t*  lx_Canvas_screen( void );                          /*M*/

LX_PUBLIC void  lx_Canvas_attachTo(                                        /*M*/
    lx_canvas_t*        object_,                                           /*-*/
    const lx_canvas_t*  canvas_,                                           /*-*/
    const lx_bool       resize_ );                                         /*-*/

#if LX_PLATFORM_WIN32
LX_PUBLIC void  lx_Canvas_attachToDC(                                      /*M*/
    lx_canvas_t*   object_,                                                /*-*/
    const HDC_win  hdc_,                                                   /*-*/
    const lx_bool  resize_ );                                              /*-*/
#endif

LX_PUBLIC void  lx_Canvas_detach( lx_canvas_t*  object_ );                 /*M*/

LX_PUBLIC void  lx_Canvas_resize( lx_canvas_t*  object_ );                 /*M*/

/* -------------------------------------------------------------------------- */
/* Implementation: lx::lx_CanvasI                                             */

/* Properties: Public */

/* return x-origin of canvas. */
LX_PUBLIC lx_pixel_t  lx_Canvas_x( const lx_canvas_t*  object_ );          /*P*/

/* return y-origin of canvas. */
LX_PUBLIC lx_pixel_t  lx_Canvas_y( const lx_canvas_t*  object_ );          /*P*/

/* return width of canvas. */
LX_PUBLIC lx_pixel_t  lx_Canvas_width( const lx_canvas_t*  object_ );      /*P*/

/* return height of canvas. */
LX_PUBLIC lx_pixel_t  lx_Canvas_height( const lx_canvas_t*  object_ );     /*P*/

/* return ending x-coordinate of canvas. */
LX_PUBLIC lx_pixel_t  lx_Canvas_x2( const lx_canvas_t*  object_ );         /*P*/

/* return ending y-coordinate of canvas. */
LX_PUBLIC lx_pixel_t  lx_Canvas_y2( const lx_canvas_t*  object_ );         /*P*/

/* Methods: Public */

/* set the rectangular area occupied by the canvas.                           */
LX_PUBLIC void  lx_Canvas_area(                                            /*M*/
    lx_canvas_t*     object_,                                              /*-*/
    const lx_rect_t  rect_ );                                              /*-*/

/* set the width of drawn lines.                                              */
LX_PUBLIC void  lx_Canvas_lineWidth(                                       /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_pixel_t  line_width_ );                                       /*-*/

/* set the current drawing color.                                             */
LX_PUBLIC void  lx_Canvas_color(                                           /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_color_t  color_ );                                            /*-*/

/* set the current font. Used by text() method.                               */
LX_PUBLIC void  lx_Canvas_font(                                            /*M*/
    lx_canvas_t*          object_,                                         /*-*/
    const lx_CanvasFont*  font_ );                                         /*-*/

/* set the current font by specifying its name and attributes.                */
/* Used by text() method.                                                     */
LX_PUBLIC void  lx_Canvas_font7(                                           /*M*/
    lx_canvas_t*   object_,                                                /*-*/
    lx_chars_t     font_name_,                                             /*-*/
    const int      font_size_,                                             /*-*/
    const lx_bool  bold_,                                                  /*-*/
    const lx_bool  italic_,                                                /*-*/
    const lx_bool  underline_,                                             /*-*/
    const lx_bool  strikeout_,                                             /*-*/
    const int      angle_ );                                               /*-*/

/* Erase the entire canvas area, filling it using the specified               */
/* color_ or the current color if color_ is not specified.                    */
LX_PUBLIC void  lx_Canvas_clear(                                           /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_color_t  color_ );                                            /*-*/

/* begin buffering output to an internal bitmap, to avoid flicker.            */
LX_PUBLIC void  lx_Canvas_beginBuffering( lx_canvas_t*  object_ );         /*M*/

/* End buffering and copy buffer bitmap to canvas.                            */
LX_PUBLIC void  lx_Canvas_endBuffering( lx_canvas_t*  object_ );           /*M*/

LX_PUBLIC void  lx_Canvas_clipRect(                                        /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_pixel_t  x_,                                                  /*-*/
    const lx_pixel_t  y_,                                                  /*-*/
    const lx_pixel_t  width_,                                              /*-*/
    const lx_pixel_t  height_ );                                           /*-*/

LX_PUBLIC void  lx_Canvas_clip( lx_canvas_t*  object_ );                   /*M*/

LX_PUBLIC void  lx_Canvas_unclip( lx_canvas_t*  object_ );                 /*M*/

/* Plot a single point specified by x_ and y_ coordinates, using the          */
/* specified color or the current color if color_ is not specified.           */
LX_PUBLIC void  lx_Canvas_point(                                           /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_pixel_t  x_,                                                  /*-*/
    const lx_pixel_t  y_,                                                  /*-*/
    const lx_color_t  color_ );                                            /*-*/

/* draw a line from point given by x1_ and y1_, to point given                */
/* by x2_ and y2_, using the specified color or the current                   */
/* color if color_ is not specified.                                          */
LX_PUBLIC void  lx_Canvas_line(                                            /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_pixel_t  x1_,                                                 /*-*/
    const lx_pixel_t  y1_,                                                 /*-*/
    const lx_pixel_t  x2_,                                                 /*-*/
    const lx_pixel_t  y2_,                                                 /*-*/
    const lx_color_t  color_ );                                            /*-*/

/* draw a rectangle specified by rectangle_, using the specified color        */
/* or the current color if color_ is not specified.                           */
LX_PUBLIC void  lx_Canvas_rect(                                            /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_rect_t*  rectangle_,                                          /*-*/
    const lx_color_t  color_ );                                            /*-*/

/* draw a rectangle starting at point given by x_ and y_, and having          */
/* the given width_ and height_, using the specified color or the             */
/* current color if color_ is not specified.                                  */
LX_PUBLIC void  lx_Canvas_rect5(                                           /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_pixel_t  x_,                                                  /*-*/
    const lx_pixel_t  y_,                                                  /*-*/
    const lx_pixel_t  width_,                                              /*-*/
    const lx_pixel_t  height_,                                             /*-*/
    const lx_color_t  color_ );                                            /*-*/

/* draw a rectangular outline, using starting (x1_, y1_) and                  */
/* ending (x2_, y2_) coordinates, using the specified color                   */
/* or the current color if color_ is not specified.                           */
LX_PUBLIC void  lx_Canvas_rectTo(                                          /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_pixel_t  x1_,                                                 /*-*/
    const lx_pixel_t  y1_,                                                 /*-*/
    const lx_pixel_t  x2_,                                                 /*-*/
    const lx_pixel_t  y2_,                                                 /*-*/
    const lx_color_t  color_ );                                            /*-*/

/* fill a rectangular area using the specified rectangle_.                    */
/* shade_ can be one of:                                                      */
/* LX_SHADE_SOLID, LX_SHADE_VERTICAL_SMOOTH, LX_SHADE_VERTICAL_GLOSSY         */
/* LX_SHADE_HORIZONTAL_SMOOTH, LX_SHADE_HORIZONTAL_GLOSSY                     */
LX_PUBLIC void  lx_Canvas_rectFill(                                        /*M*/
    lx_canvas_t*           object_,                                        /*-*/
    const lx_rect_t        rectangle_,                                     /*-*/
    const lx_color_t       color1_,                                        /*-*/
    const lx_shading_enum  shade_,                                         /*-*/
    const lx_color_t       color2_or_shine_ );                             /*-*/

/* fill a rectangular area, by using coordinates (x_, y_)                     */
/* and dimensions (width_, height_).                                          */
/* shade_ can be one of:                                                      */
/* LX_SHADE_SOLID, LX_SHADE_VERTICAL_SMOOTH, LX_SHADE_VERTICAL_GLOSSY         */
/* LX_SHADE_HORIZONTAL_SMOOTH, LX_SHADE_HORIZONTAL_GLOSSY                     */
LX_PUBLIC void  lx_Canvas_rectFill7(                                       /*M*/
    lx_canvas_t*           object_,                                        /*-*/
    const lx_pixel_t       x_,                                             /*-*/
    const lx_pixel_t       y_,                                             /*-*/
    const lx_pixel_t       width_,                                         /*-*/
    const lx_pixel_t       height_,                                        /*-*/
    const lx_color_t       color2_,                                        /*-*/
    const lx_shading_enum  shade_,                                         /*-*/
    const lx_color_t       color2_or_shine_ );                             /*-*/

/* fill a rectangular area, by using starting (x1_, y1_)                      */
/* and ending (x2_, y2_) coordinates.                                         */
/* shade_ can be one of:                                                      */
/* LX_SHADE_SOLID, LX_SHADE_VERTICAL_SMOOTH, LX_SHADE_VERTICAL_GLOSSY         */
/* LX_SHADE_HORIZONTAL_SMOOTH, LX_SHADE_HORIZONTAL_GLOSSY                     */
LX_PUBLIC void  lx_Canvas_rectFillTo(                                      /*M*/
    lx_canvas_t*           object_,                                        /*-*/
    const lx_pixel_t       x1_,                                            /*-*/
    const lx_pixel_t       y1_,                                            /*-*/
    const lx_pixel_t       x2_,                                            /*-*/
    const lx_pixel_t       y2_,                                            /*-*/
    const lx_color_t       color1_,                                        /*-*/
    const lx_shading_enum  shade_,                                         /*-*/
    const lx_color_t       color2_or_shine_ );                             /*-*/

/* fill a rounded rectangular area, by using the specified rectangle_.        */
/* round_corner_size_ specifies the size of rounded corners.                  */
LX_PUBLIC void  lx_Canvas_roundedRectFill(                                 /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    lx_rect_t         rectangle_,                                          /*-*/
    const lx_pixel_t  round_corner_size_,                                  /*-*/
    const lx_color_t  color_ );                                            /*-*/

/* fill a rounded rectangular area, by using coordinates (x_, y_)             */
/* and dimensions (width_, height_). round_corner_size_                       */
/* specifies the size of rounded corners.                                     */
LX_PUBLIC void  lx_Canvas_roundedRectFill6(                                /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_pixel_t  x_,                                                  /*-*/
    const lx_pixel_t  y_,                                                  /*-*/
    const lx_pixel_t  width_,                                              /*-*/
    const lx_pixel_t  height_,                                             /*-*/
    const lx_pixel_t  round_corner_size_,                                  /*-*/
    const lx_color_t  color_ );                                            /*-*/

/* fill a rounded rectangular area, by using starting (x1_, y1_)              */
/* and ending (x2_, y2_) coordinates. round_corner_size_                      */
/* specifies the size of rounded corners.                                     */
LX_PUBLIC void  lx_Canvas_roundedRectFillTo(                               /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_pixel_t  x1_,                                                 /*-*/
    const lx_pixel_t  y1_,                                                 /*-*/
    const lx_pixel_t  x2_,                                                 /*-*/
    const lx_pixel_t  y2_,                                                 /*-*/
    const lx_pixel_t  round_corner_size_,                                  /*-*/
    const lx_color_t  color_ );                                            /*-*/

/* Draw an ellipse enclosed by rectangle_, using the specified                */
/* color or the current color if color_ is not specified.                     */
LX_PUBLIC void  lx_Canvas_ellipse(                                         /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_rect_t*  rectangle_,                                          /*-*/
    const lx_color_t  color_ );                                            /*-*/

/* Draw an ellipse enclosed in a rectangle defined by x_, y_, width_          */
/* and height_, using the specified color or the current                      */
/* color if color_ is not specified.                                          */
LX_PUBLIC void  lx_Canvas_ellipse5(                                        /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_pixel_t  x_,                                                  /*-*/
    const lx_pixel_t  y_,                                                  /*-*/
    const lx_pixel_t  width_,                                              /*-*/
    const lx_pixel_t  height_,                                             /*-*/
    const lx_color_t  color_ );                                            /*-*/

/* Draw an ellipse enclosed in a rectangle stretching from (x1_, y1_)         */
/* to (x2_, y2_), using the specified color or the                            */
/* current color if color_ is not specified.                                  */
LX_PUBLIC void  lx_Canvas_ellipseTo(                                       /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_pixel_t  x1_,                                                 /*-*/
    const lx_pixel_t  y1_,                                                 /*-*/
    const lx_pixel_t  x2_,                                                 /*-*/
    const lx_pixel_t  y2_,                                                 /*-*/
    const lx_color_t  color_ );                                            /*-*/

/* Fill an ellipse enclosed by rectangle_, using the specified color          */
/* or the current color if color_ is not specified.                           */
LX_PUBLIC void  lx_Canvas_ellipseFill(                                     /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_rect_t*  rectangle_,                                          /*-*/
    const lx_color_t  color_ );                                            /*-*/

/* Fill an ellipse enclosed in a rectangle defined by x_, y_, width_          */
/* and height_, using the specified color or the current                      */
/* color if color_ is not specified.                                          */
LX_PUBLIC void  lx_Canvas_ellipseFill5(                                    /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_pixel_t  x_,                                                  /*-*/
    const lx_pixel_t  y_,                                                  /*-*/
    const lx_pixel_t  width_,                                              /*-*/
    const lx_pixel_t  height_,                                             /*-*/
    const lx_color_t  color_ );                                            /*-*/

/* Fill an ellipse enclosed in a rectangle stretching from (x1_, y1_)         */
/* to (x2_, y2_), using the specified color or the current                    */
/* color if color_ is not specified.                                          */
LX_PUBLIC void  lx_Canvas_ellipseFillTo(                                   /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_pixel_t  x1_,                                                 /*-*/
    const lx_pixel_t  y1_,                                                 /*-*/
    const lx_pixel_t  x2_,                                                 /*-*/
    const lx_pixel_t  y2_,                                                 /*-*/
    const lx_color_t  color_ );                                            /*-*/

/* Draw the specified polygon, displaced by offset_x_ and offset_y_, using */
/* the specified color or the current color if color_ is not specified.    */
LX_PUBLIC void  lx_Canvas_poly(                                            /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_poly_t*  polygon_,                                            /*-*/
    const lx_color_t  color_,                                              /*-*/
    const lx_pixel_t  offset_x_,                                           /*-*/
    const lx_pixel_t  offset_y_ );                                         /*-*/

LX_PUBLIC void  lx_Canvas_polyFill(                                        /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_poly_t*  polygon_,                                            /*-*/
    const lx_color_t  color_,                                              /*-*/
    const lx_pixel_t  offset_x_,                                           /*-*/
    const lx_pixel_t  offset_y_ );                                         /*-*/

LX_PUBLIC void  lx_Canvas_text(                                            /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    lx_chars_t        text_,                                               /*-*/
    const lx_color_t  color_ );                                            /*-*/

/* draw the specified text at position (x_, y_),                              */
/* using the specified color or the current color if color_                   */
/* is not specified.                                                          */
LX_PUBLIC void  lx_Canvas_text4(                                           /*M*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_pixel_t  x_,                                                  /*-*/
    const lx_pixel_t  y_,                                                  /*-*/
    lx_chars_t        text_,                                               /*-*/
    const lx_color_t  color_ );                                            /*-*/

/* return the height of a single line of text,                                */
/* using the currently-selected font.                                         */
LX_PUBLIC lx_pixel_t  lx_Canvas_textLineHeight( lx_canvas_t*  object_ );   /*M*/

/* return the height of the specified text_,                                  */
/* which can include multiple lines,                                          */
/* using the currently-selected font.                                         */
LX_PUBLIC lx_pixel_t  lx_Canvas_textHeight(                                /*M*/
    lx_canvas_t*  object_,                                                 /*-*/
    lx_chars_t    text_ );                                                 /*-*/

/* return the width of the specified text_,                                   */
/* using the currently-selected font.                                         */
LX_PUBLIC lx_pixel_t  lx_Canvas_textWidth(                                 /*M*/
    lx_canvas_t*  object_,                                                 /*-*/
    lx_chars_t    text_ );                                                 /*-*/

/* Public: */

LX_PUBLIC void  lx_draw_up_down_arrow(                                     /*F*/
    lx_canvas_t*      object_,                                             /*-*/
    const lx_pixel_t  x_,                                                  /*-*/
    const lx_pixel_t  y_,                                                  /*-*/
    const lx_pixel_t  width_,                                              /*-*/
    const lx_pixel_t  height_,                                             /*-*/
    const lx_color_t  back_color_,                                         /*-*/
    const lx_color_t  arrow_color_,                                        /*-*/
    const lx_color_t  border_color_,                                       /*-*/
    const lx_bool     down_arrow_ );                                       /*-*/

/* Functions: Public, Static */

#if LX_PLATFORM_WIN32
LX_PUBLIC HRGN_win  lx_clip_rect(                                          /*F*/
    const HDC_win     hdc_,                                                /*-*/
    const lx_pixel_t  x1_,                                                 /*-*/
    const lx_pixel_t  y1_,                                                 /*-*/
    const lx_pixel_t  x2_,                                                 /*-*/
    const lx_pixel_t  y2_,                                                 /*-*/
    const lx_bool     in_existing_clip_ );                                 /*-*/
#endif                                                   /* LX_PLATFORM_WIN32 */

#if LX_PLATFORM_WIN32
LX_PUBLIC void  lx_free_clipping_rect(                                     /*F*/
    const HDC_win   hdc_,                                                  /*-*/
    const HRGN_win  old_region_ );                                         /*-*/
#endif                                                   /* LX_PLATFORM_WIN32 */

/* Method used for testing new functionality.                                 */
LX_PUBLIC void  lx_test_canvas( const lx_canvas_t*  object_ );             /*F*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
