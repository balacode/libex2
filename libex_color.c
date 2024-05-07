/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_color.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_color_.h"
#if defined INCLUDED_LIBEX_COLOR_H

#include "libex_config_.h"

#include <ctype.h>   /* for toupper() */
#include <stdlib.h>  /* for strtol()  */
#include <string.h>  /* for memset()  */

#include "libex_call_.h"
#include "libex_macro_.h"
#include "libex_.h"

#if PLATFORM_WIN32
#include "libex_win32_.h"
#endif

#if defined __cplusplus_cli
#pragma unmanaged
#endif


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */


PUBLIC color_t  Color_fromName( chars_t  color_name_ ) {                   /*C*/
    GO                                                            (UID(F76F84));
    color_t  ret;

#define _NAME_BUF_SIZE  32

    size_t  name_len = 0;
    char_t  name[_NAME_BUF_SIZE];

    ret = CAST(color_t, -1);

    /* convert name to upper case and strip non-alphanumeric characters */
    MEMSET(name, 0x00, _NAME_BUF_SIZE * sizeof(char_t));

    if (color_name_ == NULL) {
        RETURN(ret);
    } else {
        chars_t  from = color_name_;
        char_t*  to   = name;

        while (*from && name_len < _NAME_BUF_SIZE) {

            if ((*from >= '0' && *from <= '9') ||
                (*from >= 'A' && *from <= 'Z')) {
                *(to++) = *from;

            } else if (*from >= 'a' && *from <= 'z') {
                *(to++) = CAST(char_t, TOUPPER(*from));
            }

            from++;
            name_len++;
        }
    }

#undef _NAME_BUF_SIZE

    /* if name starts with '#' treat it as an HTML color */
    if (name[0] == '#' && name_len >= 7) {
        /* "red shift": put hex digits in their right positions: */
        /* HTML colors are specified as #RRGGBB,                 */
        /* while hex value needs to be 0xBBGGRR                  */
        /* For example RED equals 0x0000FF,                      */
        /* while its HTML color is #FF0000                       */
        name[11] = name[5];
        name[12] = name[6];
        name[13] = name[3];
        name[14] = name[4];
        name[15] = name[1];
        name[16] = name[2];
        name[17] = '\0';

        /* convert resulting hex string to integer */
        ret = CAST(color_t, STRTOL_T(&name[11], NULL, 16));
        RETURN(ret);
    }

#define _RETURN_IF( COLOR_NAME_, COLOR_VAL_ )   \
    if (STRCMP_T(name, COLOR_NAME_) == 0)       \
    {   RETURN(COLOR_VAL_); }               /*#*/

    /* standard html colors */
    _RETURN_IF(_T("ALICEBLUE"),            COLOR_ALICE_BLUE);
    _RETURN_IF(_T("ANTIQUEWHITE"),         COLOR_ANTIQUE_WHITE);
    _RETURN_IF(_T("AQUA"),                 COLOR_AQUA);
    _RETURN_IF(_T("AQUAMARINE"),           COLOR_AQUAMARINE);
    _RETURN_IF(_T("AZURE"),                COLOR_AZURE);
    _RETURN_IF(_T("BEIGE"),                COLOR_BEIGE);
    _RETURN_IF(_T("BISQUE"),               COLOR_BISQUE);
    _RETURN_IF(_T("BLACK"),                COLOR_BLACK);
    _RETURN_IF(_T("BLANCHEDALMOND"),       COLOR_BLANCHED_ALMOND);
    _RETURN_IF(_T("BLUE"),                 COLOR_BLUE);
    _RETURN_IF(_T("BLUEVIOLET"),           COLOR_BLUE_VIOLET);
    _RETURN_IF(_T("BROWN"),                COLOR_BROWN);
    _RETURN_IF(_T("BURLYWOOD"),            COLOR_BURLY_WOOD);
    _RETURN_IF(_T("CADETBLUE"),            COLOR_CADET_BLUE);
    _RETURN_IF(_T("CHARTREUSE"),           COLOR_CHARTREUSE);
    _RETURN_IF(_T("CHOCOLATE"),            COLOR_CHOCOLATE);
    _RETURN_IF(_T("CORAL"),                COLOR_CORAL);
    _RETURN_IF(_T("CORNFLOWERBLUE"),       COLOR_CORNFLOWER_BLUE);
    _RETURN_IF(_T("CORNSILK"),             COLOR_CORNSILK);
    _RETURN_IF(_T("CRIMSON"),              COLOR_CRIMSON);
    _RETURN_IF(_T("CYAN"),                 COLOR_CYAN);
    _RETURN_IF(_T("DARKBLUE"),             COLOR_DARK_BLUE);
    _RETURN_IF(_T("DARKCYAN"),             COLOR_DARK_CYAN);
    _RETURN_IF(_T("DARKGOLDENROD"),        COLOR_DARK_GOLDEN_ROD);
    _RETURN_IF(_T("DARKGRAY"),             COLOR_DARK_GRAY);
    _RETURN_IF(_T("DARKGREEN"),            COLOR_DARK_GREEN);
    _RETURN_IF(_T("DARKKHAKI"),            COLOR_DARK_KHAKI);
    _RETURN_IF(_T("DARKMAGENTA"),          COLOR_DARK_MAGENTA);
    _RETURN_IF(_T("DARKOLIVEGREEN"),       COLOR_DARK_OLIVE_GREEN);
    _RETURN_IF(_T("DARKORANGE"),           COLOR_DARK_ORANGE);
    _RETURN_IF(_T("DARKORCHID"),           COLOR_DARK_ORCHID);
    _RETURN_IF(_T("DARKRED"),              COLOR_DARK_RED);
    _RETURN_IF(_T("DARKSALMON"),           COLOR_DARK_SALMON);
    _RETURN_IF(_T("DARKSEAGREEN"),         COLOR_DARK_SEA_GREEN);
    _RETURN_IF(_T("DARKSLATEBLUE"),        COLOR_DARK_SLATE_BLUE);
    _RETURN_IF(_T("DARKSLATEGRAY"),        COLOR_DARK_SLATE_GRAY);
    _RETURN_IF(_T("DARKTURQUOISE"),        COLOR_DARK_TURQUOISE);
    _RETURN_IF(_T("DARKVIOLET"),           COLOR_DARK_VIOLET);
    _RETURN_IF(_T("DEEPPINK"),             COLOR_DEEP_PINK);
    _RETURN_IF(_T("DEEPSKYBLUE"),          COLOR_DEEP_SKY_BLUE);
    _RETURN_IF(_T("DIMGRAY"),              COLOR_DIM_GRAY);
    _RETURN_IF(_T("DODGERBLUE"),           COLOR_DODGER_BLUE);
    _RETURN_IF(_T("FIREBRICK"),            COLOR_FIRE_BRICK);
    _RETURN_IF(_T("FLORALWHITE"),          COLOR_FLORAL_WHITE);
    _RETURN_IF(_T("FORESTGREEN"),          COLOR_FOREST_GREEN);
    _RETURN_IF(_T("FUCHSIA"),              COLOR_FUCHSIA);
    _RETURN_IF(_T("GAINSBORO"),            COLOR_GAINSBORO);
    _RETURN_IF(_T("GHOSTWHITE"),           COLOR_GHOST_WHITE);
    _RETURN_IF(_T("GOLD"),                 COLOR_GOLD);
    _RETURN_IF(_T("GOLDENROD"),            COLOR_GOLDEN_ROD);
    _RETURN_IF(_T("GRAY"),                 COLOR_GRAY);
    _RETURN_IF(_T("GREEN"),                COLOR_GREEN);
    _RETURN_IF(_T("GREENYELLOW"),          COLOR_GREEN_YELLOW);
    _RETURN_IF(_T("HONEYDEW"),             COLOR_HONEY_DEW);
    _RETURN_IF(_T("HOTPINK"),              COLOR_HOT_PINK);
    _RETURN_IF(_T("INDIANRED"),            COLOR_INDIAN_RED);
    _RETURN_IF(_T("INDIGO"),               COLOR_INDIGO);
    _RETURN_IF(_T("IVORY"),                COLOR_IVORY);
    _RETURN_IF(_T("KHAKI"),                COLOR_KHAKI);
    _RETURN_IF(_T("LAVENDER"),             COLOR_LAVENDER);
    _RETURN_IF(_T("LAVENDERBLUSH"),        COLOR_LAVENDER_BLUSH);
    _RETURN_IF(_T("LAWNGREEN"),            COLOR_LAWN_GREEN);
    _RETURN_IF(_T("LEMONCHIFFON"),         COLOR_LEMON_CHIFFON);
    _RETURN_IF(_T("LIGHTBLUE"),            COLOR_LIGHT_BLUE);
    _RETURN_IF(_T("LIGHTCORAL"),           COLOR_LIGHT_CORAL);
    _RETURN_IF(_T("LIGHTCYAN"),            COLOR_LIGHT_CYAN);
    _RETURN_IF(_T("LIGHTGOLDENRODYELLOW"), COLOR_LIGHT_GOLDEN_ROD_YELLOW);
    _RETURN_IF(_T("LIGHTGREEN"),           COLOR_LIGHT_GREEN);
    _RETURN_IF(_T("LIGHTGRAY"),            COLOR_LIGHT_GRAY);
    _RETURN_IF(_T("LIGHTPINK"),            COLOR_LIGHT_PINK);
    _RETURN_IF(_T("LIGHTSALMON"),          COLOR_LIGHT_SALMON);
    _RETURN_IF(_T("LIGHTSEAGREEN"),        COLOR_LIGHT_SEA_GREEN);
    _RETURN_IF(_T("LIGHTSKYBLUE"),         COLOR_LIGHT_SKY_BLUE);
    _RETURN_IF(_T("LIGHTSLATEGRAY"),       COLOR_LIGHT_SLATE_GRAY);
    _RETURN_IF(_T("LIGHTSTEELBLUE"),       COLOR_LIGHT_STEEL_BLUE);
    _RETURN_IF(_T("LIGHTYELLOW"),          COLOR_LIGHT_YELLOW);
    _RETURN_IF(_T("LIME"),                 COLOR_LIME);
    _RETURN_IF(_T("LIMEGREEN"),            COLOR_LIME_GREEN);
    _RETURN_IF(_T("LINEN"),                COLOR_LINEN);
    _RETURN_IF(_T("MAGENTA"),              COLOR_MAGENTA);
    _RETURN_IF(_T("MAROON"),               COLOR_MAROON);
    _RETURN_IF(_T("MEDIUMAQUAMARINE"),     COLOR_MEDIUM_AQUAMARINE);
    _RETURN_IF(_T("MEDIUMBLUE"),           COLOR_MEDIUM_BLUE);
    _RETURN_IF(_T("MEDIUMORCHID"),         COLOR_MEDIUM_ORCHID);
    _RETURN_IF(_T("MEDIUMPURPLE"),         COLOR_MEDIUM_PURPLE);
    _RETURN_IF(_T("MEDIUMSEAGREEN"),       COLOR_MEDIUM_SEA_GREEN);
    _RETURN_IF(_T("MEDIUMSLATEBLUE"),      COLOR_MEDIUM_SLATE_BLUE);
    _RETURN_IF(_T("MEDIUMSPRINGGREEN"),    COLOR_MEDIUM_SPRING_GREEN);
    _RETURN_IF(_T("MEDIUMTURQUOISE"),      COLOR_MEDIUM_TURQUOISE);
    _RETURN_IF(_T("MEDIUMVIOLETRED"),      COLOR_MEDIUM_VIOLET_RED);
    _RETURN_IF(_T("MIDNIGHTBLUE"),         COLOR_MIDNIGHT_BLUE);
    _RETURN_IF(_T("MINTCREAM"),            COLOR_MINT_CREAM);
    _RETURN_IF(_T("MISTYROSE"),            COLOR_MISTY_ROSE);
    _RETURN_IF(_T("MOCCASIN"),             COLOR_MOCCASIN);
    _RETURN_IF(_T("NAVAJOWHITE"),          COLOR_NAVAJO_WHITE);
    _RETURN_IF(_T("NAVY"),                 COLOR_NAVY);
    _RETURN_IF(_T("NAVYBLUE"),             COLOR_NAVY_BLUE);
    _RETURN_IF(_T("OLDLACE"),              COLOR_OLD_LACE);
    _RETURN_IF(_T("OLIVE"),                COLOR_OLIVE);
    _RETURN_IF(_T("OLIVEDRAB"),            COLOR_OLIVE_DRAB);
    _RETURN_IF(_T("ORANGE"),               COLOR_ORANGE);
    _RETURN_IF(_T("ORANGERED"),            COLOR_ORANGE_RED);
    _RETURN_IF(_T("ORCHID"),               COLOR_ORCHID);
    _RETURN_IF(_T("PALEGOLDENROD"),        COLOR_PALE_GOLDEN_ROD);
    _RETURN_IF(_T("PALEGREEN"),            COLOR_PALE_GREEN);
    _RETURN_IF(_T("PALETURQUOISE"),        COLOR_PALE_TURQUOISE);
    _RETURN_IF(_T("PALEVIOLETRED"),        COLOR_PALE_VIOLET_RED);
    _RETURN_IF(_T("PAPAYAWHIP"),           COLOR_PAPAYA_WHIP);
    _RETURN_IF(_T("PEACHPUFF"),            COLOR_PEACH_PUFF);
    _RETURN_IF(_T("PERU"),                 COLOR_PERU);
    _RETURN_IF(_T("PINK"),                 COLOR_PINK);
    _RETURN_IF(_T("PLUM"),                 COLOR_PLUM);
    _RETURN_IF(_T("POWDERBLUE"),           COLOR_POWDER_BLUE);
    _RETURN_IF(_T("PURPLE"),               COLOR_PURPLE);
    _RETURN_IF(_T("RED"),                  COLOR_RED);
    _RETURN_IF(_T("ROSYBROWN"),            COLOR_ROSY_BROWN);
    _RETURN_IF(_T("ROYALBLUE"),            COLOR_ROYAL_BLUE);
    _RETURN_IF(_T("SADDLEBROWN"),          COLOR_SADDLE_BROWN);
    _RETURN_IF(_T("SALMON"),               COLOR_SALMON);
    _RETURN_IF(_T("SANDYBROWN"),           COLOR_SANDY_BROWN);
    _RETURN_IF(_T("SEAGREEN"),             COLOR_SEA_GREEN);
    _RETURN_IF(_T("SEASHELL"),             COLOR_SEA_SHELL);
    _RETURN_IF(_T("SIENNA"),               COLOR_SIENNA);
    _RETURN_IF(_T("SILVER"),               COLOR_SILVER);
    _RETURN_IF(_T("SKYBLUE"),              COLOR_SKY_BLUE);
    _RETURN_IF(_T("SLATEBLUE"),            COLOR_SLATE_BLUE);
    _RETURN_IF(_T("SLATEGRAY"),            COLOR_SLATE_GRAY);
    _RETURN_IF(_T("SNOW"),                 COLOR_SNOW);
    _RETURN_IF(_T("SPRINGGREEN"),          COLOR_SPRING_GREEN);
    _RETURN_IF(_T("STEELBLUE"),            COLOR_STEEL_BLUE);
    _RETURN_IF(_T("TAN"),                  COLOR_TAN);
    _RETURN_IF(_T("TEAL"),                 COLOR_TEAL);
    _RETURN_IF(_T("THISTLE"),              COLOR_THISTLE);
    _RETURN_IF(_T("TOMATO"),               COLOR_TOMATO);
    _RETURN_IF(_T("TURQUOISE"),            COLOR_TURQUOISE);
    _RETURN_IF(_T("VIOLET"),               COLOR_VIOLET);
    _RETURN_IF(_T("WHEAT"),                COLOR_WHEAT);
    _RETURN_IF(_T("WHITE"),                COLOR_WHITE);
    _RETURN_IF(_T("WHITESMOKE"),           COLOR_WHITE_SMOKE);
    _RETURN_IF(_T("YELLOW"),               COLOR_YELLOW);
    _RETURN_IF(_T("YELLOWGREEN"),          COLOR_YELLOW_GREEN);

    /* custom colors */
    _RETURN_IF(_T("BLUE1"),          COLOR_BLUE_1);
    _RETURN_IF(_T("BLUE2"),          COLOR_BLUE_2);
    _RETURN_IF(_T("BLUE3"),          COLOR_BLUE_3);
    _RETURN_IF(_T("BLUE4"),          COLOR_BLUE_4);
    _RETURN_IF(_T("BLUE5"),          COLOR_BLUE_5);
    _RETURN_IF(_T("BLUE6"),          COLOR_BLUE_6);
    _RETURN_IF(_T("BLUE7"),          COLOR_BLUE_7);
    _RETURN_IF(_T("GRAY1"),          COLOR_GRAY_1);
    _RETURN_IF(_T("GRAY2"),          COLOR_GRAY_2);
    _RETURN_IF(_T("GRAY3"),          COLOR_GRAY_3);
    _RETURN_IF(_T("GRAY4"),          COLOR_GRAY_4);
    _RETURN_IF(_T("GRAY5"),          COLOR_GRAY_5);
    _RETURN_IF(_T("GRAY6"),          COLOR_GRAY_6);
    _RETURN_IF(_T("GRAY7"),          COLOR_GRAY_7);
    _RETURN_IF(_T("GREEN1"),         COLOR_GREEN_1);
    _RETURN_IF(_T("GREEN2"),         COLOR_GREEN_2);
    _RETURN_IF(_T("GREEN3"),         COLOR_GREEN_3);
    _RETURN_IF(_T("GREEN4"),         COLOR_GREEN_4);
    _RETURN_IF(_T("GREEN5"),         COLOR_GREEN_5);
    _RETURN_IF(_T("GREEN6"),         COLOR_GREEN_6);
    _RETURN_IF(_T("GREEN7"),         COLOR_GREEN_7);
    _RETURN_IF(_T("LIBLIGHTYELLOW"), COLOR_LIB_LIGHT_YELLOW);
    _RETURN_IF(_T("ORANGE100"),      COLOR_ORANGE_100);
    _RETURN_IF(_T("ORANGE110"),      COLOR_ORANGE_110);
    _RETURN_IF(_T("ORANGE120"),      COLOR_ORANGE_120);
    _RETURN_IF(_T("ORANGE130"),      COLOR_ORANGE_130);
    _RETURN_IF(_T("ORANGE140"),      COLOR_ORANGE_140);
    _RETURN_IF(_T("ORANGE150"),      COLOR_ORANGE_150);
    _RETURN_IF(_T("ORANGE160"),      COLOR_ORANGE_160);
    _RETURN_IF(_T("ORANGE170"),      COLOR_ORANGE_170);
    _RETURN_IF(_T("ORANGE180"),      COLOR_ORANGE_180);
    _RETURN_IF(_T("ORANGE190"),      COLOR_ORANGE_190);
    _RETURN_IF(_T("ORANGE200"),      COLOR_ORANGE_200);
    _RETURN_IF(_T("ORANGE210"),      COLOR_ORANGE_210);
    _RETURN_IF(_T("ORANGE220"),      COLOR_ORANGE_220);
    _RETURN_IF(_T("ORANGE70"),       COLOR_ORANGE_70);
    _RETURN_IF(_T("ORANGE80"),       COLOR_ORANGE_80);
    _RETURN_IF(_T("ORANGE90"),       COLOR_ORANGE_90);
    _RETURN_IF(_T("RED1"),           COLOR_RED_1);
    _RETURN_IF(_T("RED2"),           COLOR_RED_2);
    _RETURN_IF(_T("RED3"),           COLOR_RED_3);
    _RETURN_IF(_T("RED4"),           COLOR_RED_4);
    _RETURN_IF(_T("RED5"),           COLOR_RED_5);
    _RETURN_IF(_T("RED6"),           COLOR_RED_6);
    _RETURN_IF(_T("RED7"),           COLOR_RED_7);

#undef _RETURN_IF

    /* TODO add 2nd parameter for locale name */

    ret = COLOR_NULL;

    RETURN(ret);
} /* Color_fromName */


/* convert logical (system) color values to physical color values             */
PUBLIC color_t  Color_fromSystem( const color_t  os_color_ ) {             /*M*/
    GO                                                            (UID(FB5DC9));
    color_t  ret = COLOR_NULL;

#if PLATFORM_LINUX
    UNUSED(os_color_);
    IMPLEMENT_LINUX();  /* TODO: implement Color_fromSystem() on Linux */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    if (os_color_ & 0x80000000) {
        const int  index = os_color_ && 0xFF;
        ret = GetSysColorBrush_win(index) == NULL ? COLOR_NULL
              : GetSysColor_win(index);
    } else if (!(os_color_ & 0xFF000000)) {
        ret = os_color_;
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* Color_fromSystem */


/* Return a physical color value composed from red, green and blue parts.     */
PUBLIC color_t  Color_fromRgb(                                             /*M*/
    const int  red_part_,                                                  /*-*/
    const int  green_part_,                                                /*-*/
    const int  blue_part_ ) {                                              /*-*/
    GO                                                            (UID(F84C73));
    const color_t  ret = CAST(color_t, CAST(uint8_t, red_part_)) |
                         CAST(color_t, CAST(uint8_t, green_part_)) << 8 |
                         CAST(color_t, CAST(uint8_t, blue_part_))  << 16;
    RETURN(ret);
} /* Color_fromRgb */


/* Return a physical color value based on a color integer.                    */
PUBLIC color_t  Color_fromValue( const color_t  value_ ) {                 /*M*/
    GO                                                            (UID(FAFB7C));
    const color_t  ret = CAST(color_t, value_);
    RETURN(ret);
} /* Color_fromValue */


/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */


PUBLIC uint8_t  Color_getRed( const color_t  color_ ) {                    /*M*/
    GO                                                            (UID(F3F8BB));
    const uint8_t  ret = CAST(uint8_t, color_ & 0xFF);
    RETURN(ret);
} /* Color_getRed */


PUBLIC uint8_t  Color_getGreen( const color_t  color_ ) {                  /*M*/
    GO                                                            (UID(FD5DE9));
    const uint8_t  ret = CAST(uint8_t, (color_ & 0xFF00) / 0x100);
    RETURN(ret);
} /* Color_getGreen */


PUBLIC uint8_t  Color_getBlue( const color_t  color_ ) {                   /*M*/
    GO                                                            (UID(FA7201));
    const uint8_t  ret = CAST(uint8_t, (color_ & 0xFF0000) / 0x10000);
    RETURN(ret);
} /* Color_getBlue */


PUBLIC color_t  Color_brighten(                                            /*M*/
    const color_t  color_,                                                 /*-*/
    const double   ratio_ ) {                                              /*-*/
    GO                                                            (UID(F86073));
    color_t  ret = COLOR_NULL;

    /* extract the red, green and blue components */
    double  red   = Color_getRed(color_);
    double  green = Color_getGreen(color_);
    double  blue  = Color_getBlue(color_);

    double  ratio = ABS(ratio_);

    if (ratio < 0.001) {
        ret = COLOR_BLACK;
        RETURN(ret);
    }

    if (ratio > 1) {
        red   += (255 - red)   - ((255 - red)   * (1 / ratio));
        green += (255 - green) - ((255 - green) * (1 / ratio));
        blue  += (255 - blue)  - ((255 - blue)  * (1 / ratio));
    } else {
        red   *= ratio;
        green *= ratio;
        blue  *= ratio;
    }

    /* ensure RGB values stay within bounds */
    if (ratio > 1.0) {
        const size_t  max = 255;
        red   = red   > max ? max : red;
        green = green > max ? max : green;
        blue  = blue  > max ? max : blue;
    }

    /* 0.00000000001 is needed as rounding problems may occur when */
    /* changing back to int (for example double 1.15 x double      */
    /* 100 became 114 when converted to integer!)                  */

    ret = Color_fromRgb(CAST(uint8_t, red   + 0.00000000001),
                        CAST(uint8_t, green + 0.00000000001),
                        CAST(uint8_t, blue  + 0.00000000001));
    RETURN(ret);
} /* Color_brighten */


PUBLIC color_t  Color_shift(                                               /*M*/
    const color_t  color_,                                                 /*-*/
    const int      steps_ ) {                                              /*-*/
    GO                                                            (UID(FD54BC));
    int  red   = Color_getRed(color_);
    int  green = Color_getGreen(color_);
    int  blue  = Color_getBlue(color_);

    red   += steps_;
    green += steps_;
    blue  += steps_;

    if (red < 0) {
        red = -red;
    }

    if (green < 0) {
        green = -green;
    }

    if (blue < 0) {
        blue = -blue;
    }

    {
        const color_t  ret = Color_fromRgb(CAST(uint8_t, red   & 0xFF),
                                           CAST(uint8_t, green & 0xFF),
                                           CAST(uint8_t, blue  & 0xFF));
        RETURN(ret);
    }
} /* Color_shift */


PUBLIC color_t  Color_blend(                                               /*M*/
    const color_t  color1_,                                                /*-*/
    const color_t  color2_,                                                /*-*/
    const size_t   color1_percent_ ) {                                     /*-*/
    GO                                                            (UID(FE52B7));
    const int  red1   = Color_getRed(color1_);
    const int  green1 = Color_getGreen(color1_);
    const int  blue1  = Color_getBlue(color1_);

    const int  red2   = Color_getRed(color2_);
    const int  green2 = Color_getGreen(color2_);
    const int  blue2  = Color_getBlue(color2_);

    const int  red = (red1 * 100 + (CAST(int, color1_percent_)
                                    * (red2 - red1))) / 100;

    const int  green = (green1 * 100 + (CAST(int, color1_percent_)
                                        * (green2 - green1))) / 100;

    const int  blue = (blue1 * 100 + (CAST(int, color1_percent_)
                                      * (blue2 - blue1))) / 100;

    {
        const color_t  ret = Color_fromRgb(red, green, blue);
        RETURN(ret);
    }
} /* Color_blend */


/* convert logical (system) color values to physical color values.            */
PUBLIC color_t  Color_rgb( const color_t  logic_color_ ) {                 /*P*/
    GO                                                            (UID(F9B8EB));
    color_t  ret = COLOR_NULL;

#if PLATFORM_LINUX
    ret = logic_color_;
    IMPLEMENT_LINUX();  /* TODO: implement Color_rgb() on Linux */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32

    if (logic_color_ & 0x80000000) {
        const int  index = logic_color_ && 0xFF;
        ret = GetSysColorBrush_win(index) == NULL ? COLOR_NULL
              : GetSysColor_win(index);
    } else if (!(logic_color_ & 0xFF000000)) {
        ret = logic_color_;
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* Color_rgb */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
