/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_color.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_COLOR_H
#define      INCLUDED_LIBEX_COLOR_H

#include "libex.h"

#if LX_PLATFORM_WIN32
#include "libex_win32.h"
#endif

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

#if LX_PLATFORM_LINUX
typedef unsigned int  lx_color_t;
#endif

#if LX_PLATFORM_WIN32
#include "wtypes.h"   /* Windows API */
typedef COLORREF_win  lx_color_t;
#endif

static const lx_color_t  LX_COLOR_NULL = LX_CAST(lx_color_t, -1);

/* To convert a color to a HTML value, reverse the hexadecimal string.        */
/* E.g. the value of LX_COLOR_BLUE (0xFF0000) is #0000FF in HTML.             */
typedef enum  _lx_color_name_enum {
    /* HTML color                        = 0xBBGGRR */
    LX_COLOR_ALICE_BLUE                  = 0xFFF8F0,    /* lx_color_name_enum */
    LX_COLOR_ANTIQUE_WHITE               = 0xD7EBFA,    /* lx_color_name_enum */
    LX_COLOR_AQUA                        = 0xFFFF00,    /* lx_color_name_enum */
    LX_COLOR_AQUAMARINE                  = 0xD4FF7F,    /* lx_color_name_enum */
    LX_COLOR_AZURE                       = 0xFFFFF0,    /* lx_color_name_enum */
    LX_COLOR_BEIGE                       = 0xDCF5F5,    /* lx_color_name_enum */
    LX_COLOR_BISQUE                      = 0xC4E4FF,    /* lx_color_name_enum */
    LX_COLOR_BLACK                       = 0x000000,    /* lx_color_name_enum */
    LX_COLOR_BLANCHED_ALMOND             = 0xCDEBFF,    /* lx_color_name_enum */
    LX_COLOR_BLUE                        = 0xFF0000,    /* lx_color_name_enum */
    LX_COLOR_BLUE_VIOLET                 = 0xE22B8A,    /* lx_color_name_enum */
    LX_COLOR_BROWN                       = 0x2A2AA5,    /* lx_color_name_enum */
    LX_COLOR_BURLY_WOOD                  = 0x87B8DE,    /* lx_color_name_enum */
    LX_COLOR_CADET_BLUE                  = 0xA09E5F,    /* lx_color_name_enum */
    LX_COLOR_CHARTREUSE                  = 0x00FF7F,    /* lx_color_name_enum */
    LX_COLOR_CHOCOLATE                   = 0x1E69D2,    /* lx_color_name_enum */
    LX_COLOR_CORAL                       = 0x507FFF,    /* lx_color_name_enum */
    LX_COLOR_CORNFLOWER_BLUE             = 0xED9564,    /* lx_color_name_enum */
    LX_COLOR_CORNSILK                    = 0xDCF8FF,    /* lx_color_name_enum */
    LX_COLOR_CRIMSON                     = 0x3C14DC,    /* lx_color_name_enum */
    LX_COLOR_CYAN                        = 0xFFFF00,    /* lx_color_name_enum */
    LX_COLOR_DARK_BLUE                   = 0x8B0000,    /* lx_color_name_enum */
    LX_COLOR_DARK_CYAN                   = 0x8B8B00,    /* lx_color_name_enum */
    LX_COLOR_DARK_GOLDEN_ROD             = 0x0B86B8,    /* lx_color_name_enum */
    LX_COLOR_DARK_GRAY                   = 0xA9A9A9,    /* lx_color_name_enum */
    LX_COLOR_DARK_GREEN                  = 0x006400,    /* lx_color_name_enum */
    LX_COLOR_DARK_KHAKI                  = 0x6BB7BD,    /* lx_color_name_enum */
    LX_COLOR_DARK_MAGENTA                = 0x8B008B,    /* lx_color_name_enum */
    LX_COLOR_DARK_OLIVE_GREEN            = 0x2F6B55,    /* lx_color_name_enum */
    LX_COLOR_DARK_ORANGE                 = 0x008CFF,    /* lx_color_name_enum */
    LX_COLOR_DARK_ORCHID                 = 0xCC3299,    /* lx_color_name_enum */
    LX_COLOR_DARK_RED                    = 0x00008B,    /* lx_color_name_enum */
    LX_COLOR_DARK_SALMON                 = 0x7A96E9,    /* lx_color_name_enum */
    LX_COLOR_DARK_SEA_GREEN              = 0x8FBC8F,    /* lx_color_name_enum */
    LX_COLOR_DARK_SLATE_BLUE             = 0x8B3D48,    /* lx_color_name_enum */
    LX_COLOR_DARK_SLATE_GRAY             = 0x4F4F2F,    /* lx_color_name_enum */
    LX_COLOR_DARK_TURQUOISE              = 0xD1CE00,    /* lx_color_name_enum */
    LX_COLOR_DARK_VIOLET                 = 0xD30094,    /* lx_color_name_enum */
    LX_COLOR_DEEP_PINK                   = 0x9314FF,    /* lx_color_name_enum */
    LX_COLOR_DEEP_SKY_BLUE               = 0xFFBF00,    /* lx_color_name_enum */
    LX_COLOR_DIM_GRAY                    = 0x696969,    /* lx_color_name_enum */
    LX_COLOR_DODGER_BLUE                 = 0xFF901E,    /* lx_color_name_enum */
    LX_COLOR_FIRE_BRICK                  = 0x2222B2,    /* lx_color_name_enum */
    LX_COLOR_FLORAL_WHITE                = 0xF0FAFF,    /* lx_color_name_enum */
    LX_COLOR_FOREST_GREEN                = 0x228B22,    /* lx_color_name_enum */
    LX_COLOR_FUCHSIA                     = 0xFF00FF,    /* lx_color_name_enum */
    LX_COLOR_GAINSBORO                   = 0xDCDCDC,    /* lx_color_name_enum */
    LX_COLOR_GHOST_WHITE                 = 0xFFF8F8,    /* lx_color_name_enum */
    LX_COLOR_GOLD                        = 0x00D7FF,    /* lx_color_name_enum */
    LX_COLOR_GOLDEN_ROD                  = 0x20A5DA,    /* lx_color_name_enum */
    LX_COLOR_GRAY                        = 0x808080,    /* lx_color_name_enum */
    LX_COLOR_GREEN                       = 0x008000,    /* lx_color_name_enum */
    LX_COLOR_GREEN_YELLOW                = 0x2FFFAD,    /* lx_color_name_enum */
    LX_COLOR_HONEY_DEW                   = 0xF0FFF0,    /* lx_color_name_enum */
    LX_COLOR_HOT_PINK                    = 0xB469FF,    /* lx_color_name_enum */
    LX_COLOR_INDIAN_RED                  = 0x5C5CCD,    /* lx_color_name_enum */
    LX_COLOR_INDIGO                      = 0x82004B,    /* lx_color_name_enum */
    LX_COLOR_IVORY                       = 0xF0FFFF,    /* lx_color_name_enum */
    LX_COLOR_KHAKI                       = 0x8CE6F0,    /* lx_color_name_enum */
    LX_COLOR_LAVENDER                    = 0xFAE6E6,    /* lx_color_name_enum */
    LX_COLOR_LAVENDER_BLUSH              = 0xF5F0FF,    /* lx_color_name_enum */
    LX_COLOR_LAWN_GREEN                  = 0x00FC7C,    /* lx_color_name_enum */
    LX_COLOR_LEMON_CHIFFON               = 0xCDFAFF,    /* lx_color_name_enum */
    LX_COLOR_LIGHT_BLUE                  = 0xE6D8AD,    /* lx_color_name_enum */
    LX_COLOR_LIGHT_CORAL                 = 0x8080F0,    /* lx_color_name_enum */
    LX_COLOR_LIGHT_CYAN                  = 0xFFFFE0,    /* lx_color_name_enum */
    LX_COLOR_LIGHT_GOLDEN_ROD_YELLOW     = 0xD2FAFA,    /* lx_color_name_enum */
    LX_COLOR_LIGHT_GRAY                  = 0xD3D3D3,    /* lx_color_name_enum */
    LX_COLOR_LIGHT_GREEN                 = 0x90EE90,    /* lx_color_name_enum */
    LX_COLOR_LIGHT_PINK                  = 0xC1B6FF,    /* lx_color_name_enum */
    LX_COLOR_LIGHT_SALMON                = 0x7AA0FF,    /* lx_color_name_enum */
    LX_COLOR_LIGHT_SEA_GREEN             = 0xAAB220,    /* lx_color_name_enum */
    LX_COLOR_LIGHT_SKY_BLUE              = 0xFACE87,    /* lx_color_name_enum */
    LX_COLOR_LIGHT_SLATE_GRAY            = 0x998877,    /* lx_color_name_enum */
    LX_COLOR_LIGHT_STEEL_BLUE            = 0xDEC4B0,    /* lx_color_name_enum */
    LX_COLOR_LIGHT_YELLOW                = 0xE0FFFF,    /* lx_color_name_enum */
    LX_COLOR_LIME                        = 0x00FF00,    /* lx_color_name_enum */
    LX_COLOR_LIME_GREEN                  = 0x32CD32,    /* lx_color_name_enum */
    LX_COLOR_LINEN                       = 0xE6F0FA,    /* lx_color_name_enum */
    LX_COLOR_MAGENTA                     = 0xFF00FF,    /* lx_color_name_enum */
    LX_COLOR_MAROON                      = 0x000080,    /* lx_color_name_enum */
    LX_COLOR_MEDIUM_AQUAMARINE           = 0xAACD66,    /* lx_color_name_enum */
    LX_COLOR_MEDIUM_BLUE                 = 0xCD0000,    /* lx_color_name_enum */
    LX_COLOR_MEDIUM_ORCHID               = 0xD355BA,    /* lx_color_name_enum */
    LX_COLOR_MEDIUM_PURPLE               = 0xD87093,    /* lx_color_name_enum */
    LX_COLOR_MEDIUM_SEA_GREEN            = 0x71B33C,    /* lx_color_name_enum */
    LX_COLOR_MEDIUM_SLATE_BLUE           = 0xEE687B,    /* lx_color_name_enum */
    LX_COLOR_MEDIUM_SPRING_GREEN         = 0x9AFA00,    /* lx_color_name_enum */
    LX_COLOR_MEDIUM_TURQUOISE            = 0xCCD148,    /* lx_color_name_enum */
    LX_COLOR_MEDIUM_VIOLET_RED           = 0x8515C7,    /* lx_color_name_enum */
    LX_COLOR_MIDNIGHT_BLUE               = 0x701919,    /* lx_color_name_enum */
    LX_COLOR_MINT_CREAM                  = 0xFAFFF5,    /* lx_color_name_enum */
    LX_COLOR_MISTY_ROSE                  = 0xE1E4FF,    /* lx_color_name_enum */
    LX_COLOR_MOCCASIN                    = 0xB5E4FF,    /* lx_color_name_enum */
    LX_COLOR_NAVAJO_WHITE                = 0xADDEFF,    /* lx_color_name_enum */
    LX_COLOR_NAVY                        = 0x800000,    /* lx_color_name_enum */
    LX_COLOR_NAVY_BLUE                   = 0xDFAF9F,    /* lx_color_name_enum */
    LX_COLOR_OLD_LACE                    = 0xE6F5FD,    /* lx_color_name_enum */
    LX_COLOR_OLIVE                       = 0x008080,    /* lx_color_name_enum */
    LX_COLOR_OLIVE_DRAB                  = 0x238E6B,    /* lx_color_name_enum */
    LX_COLOR_ORANGE                      = 0x00A5FF,    /* lx_color_name_enum */
    LX_COLOR_ORANGE_RED                  = 0x0045FF,    /* lx_color_name_enum */
    LX_COLOR_ORCHID                      = 0xD670DA,    /* lx_color_name_enum */
    LX_COLOR_PALE_GOLDEN_ROD             = 0xAAE8EE,    /* lx_color_name_enum */
    LX_COLOR_PALE_GREEN                  = 0x98FB98,    /* lx_color_name_enum */
    LX_COLOR_PALE_TURQUOISE              = 0xEEEEAF,    /* lx_color_name_enum */
    LX_COLOR_PALE_VIOLET_RED             = 0x9370D8,    /* lx_color_name_enum */
    LX_COLOR_PAPAYA_WHIP                 = 0xD5EFFF,    /* lx_color_name_enum */
    LX_COLOR_PEACH_PUFF                  = 0xB9DAFF,    /* lx_color_name_enum */
    LX_COLOR_PERU                        = 0x3F85CD,    /* lx_color_name_enum */
    LX_COLOR_PINK                        = 0xCBC0FF,    /* lx_color_name_enum */
    LX_COLOR_PLUM                        = 0xDDA0DD,    /* lx_color_name_enum */
    LX_COLOR_POWDER_BLUE                 = 0xE6E0B0,    /* lx_color_name_enum */
    LX_COLOR_PURPLE                      = 0x800080,    /* lx_color_name_enum */
    LX_COLOR_RED                         = 0x0000FF,    /* lx_color_name_enum */
    LX_COLOR_ROSY_BROWN                  = 0x8F8FBC,    /* lx_color_name_enum */
    LX_COLOR_ROYAL_BLUE                  = 0xE16941,    /* lx_color_name_enum */
    LX_COLOR_SADDLE_BROWN                = 0x13458B,    /* lx_color_name_enum */
    LX_COLOR_SALMON                      = 0x7280FA,    /* lx_color_name_enum */
    LX_COLOR_SANDY_BROWN                 = 0x60A4F4,    /* lx_color_name_enum */
    LX_COLOR_SEA_GREEN                   = 0x578B2E,    /* lx_color_name_enum */
    LX_COLOR_SEA_SHELL                   = 0xEEF5FF,    /* lx_color_name_enum */
    LX_COLOR_SIENNA                      = 0x2D52A0,    /* lx_color_name_enum */
    LX_COLOR_SILVER                      = 0xC0C0C0,    /* lx_color_name_enum */
    LX_COLOR_SKY_BLUE                    = 0xEBCE87,    /* lx_color_name_enum */
    LX_COLOR_SLATE_BLUE                  = 0xCD5A6A,    /* lx_color_name_enum */
    LX_COLOR_SLATE_GRAY                  = 0x908070,    /* lx_color_name_enum */
    LX_COLOR_SNOW                        = 0xFAFAFF,    /* lx_color_name_enum */
    LX_COLOR_SPRING_GREEN                = 0x7FFF00,    /* lx_color_name_enum */
    LX_COLOR_STEEL_BLUE                  = 0xB48246,    /* lx_color_name_enum */
    LX_COLOR_TAN                         = 0x8CB4D2,    /* lx_color_name_enum */
    LX_COLOR_TEAL                        = 0x808000,    /* lx_color_name_enum */
    LX_COLOR_THISTLE                     = 0xD8BFD8,    /* lx_color_name_enum */
    LX_COLOR_TOMATO                      = 0x4763FF,    /* lx_color_name_enum */
    LX_COLOR_TURQUOISE                   = 0xD0E040,    /* lx_color_name_enum */
    LX_COLOR_VIOLET                      = 0xEE82EE,    /* lx_color_name_enum */
    LX_COLOR_WHEAT                       = 0xB3DEF5,    /* lx_color_name_enum */
    LX_COLOR_WHITE                       = 0xFFFFFF,    /* lx_color_name_enum */
    LX_COLOR_WHITE_SMOKE                 = 0xF5F5F5,    /* lx_color_name_enum */
    LX_COLOR_YELLOW                      = 0x00FFFF,    /* lx_color_name_enum */
    LX_COLOR_YELLOW_GREEN                = 0x32CD9A,    /* lx_color_name_enum */

    /* custom colors */
    LX_COLOR_BLUE_1                      = 0xE00000,    /* lx_color_name_enum */
    LX_COLOR_BLUE_2                      = 0xC00000,    /* lx_color_name_enum */
    LX_COLOR_BLUE_3                      = 0xA00000,    /* lx_color_name_enum */
    LX_COLOR_BLUE_4                      = 0x800000,    /* lx_color_name_enum */
    LX_COLOR_BLUE_5                      = 0x600000,    /* lx_color_name_enum */
    LX_COLOR_BLUE_6                      = 0x400000,    /* lx_color_name_enum */
    LX_COLOR_BLUE_7                      = 0x200000,    /* lx_color_name_enum */
    LX_COLOR_GRAY_1                      = 0xE0E0E0,    /* lx_color_name_enum */
    LX_COLOR_GRAY_2                      = 0xC0C0C0,    /* lx_color_name_enum */
    LX_COLOR_GRAY_3                      = 0xA0A0A0,    /* lx_color_name_enum */
    LX_COLOR_GRAY_4                      = 0x808080,    /* lx_color_name_enum */
    LX_COLOR_GRAY_5                      = 0x606060,    /* lx_color_name_enum */
    LX_COLOR_GRAY_6                      = 0x404040,    /* lx_color_name_enum */
    LX_COLOR_GRAY_7                      = 0x202020,    /* lx_color_name_enum */
    LX_COLOR_GREEN_1                     = 0x00E000,    /* lx_color_name_enum */
    LX_COLOR_GREEN_2                     = 0x00C000,    /* lx_color_name_enum */
    LX_COLOR_GREEN_3                     = 0x00A000,    /* lx_color_name_enum */
    LX_COLOR_GREEN_4                     = 0x008000,    /* lx_color_name_enum */
    LX_COLOR_GREEN_5                     = 0x006000,    /* lx_color_name_enum */
    LX_COLOR_GREEN_6                     = 0x004000,    /* lx_color_name_enum */
    LX_COLOR_GREEN_7                     = 0x002000,    /* lx_color_name_enum */
    LX_COLOR_LIB_LIGHT_YELLOW            = 0x99FFFF,    /* lx_color_name_enum */

    /* the number after the color specifies the luminosity */
    LX_COLOR_ORANGE_100                  = 0x006AD5,    /* lx_color_name_enum */
    LX_COLOR_ORANGE_110                  = 0x0075EA,    /* lx_color_name_enum */
    LX_COLOR_ORANGE_120                  = 0x0080FF,    /* lx_color_name_enum */
    LX_COLOR_ORANGE_130                  = 0x158AFF,    /* lx_color_name_enum */
    LX_COLOR_ORANGE_140                  = 0x2B94FF,    /* lx_color_name_enum */
    LX_COLOR_ORANGE_150                  = 0x409FFF,    /* lx_color_name_enum */
    LX_COLOR_ORANGE_160                  = 0x55AAFF,    /* lx_color_name_enum */
    LX_COLOR_ORANGE_170                  = 0x6AB5FF,    /* lx_color_name_enum */
    LX_COLOR_ORANGE_180                  = 0x80BFFF,    /* lx_color_name_enum */
    LX_COLOR_ORANGE_190                  = 0x95CAFF,    /* lx_color_name_enum */
    LX_COLOR_ORANGE_200                  = 0xAAD5FF,    /* lx_color_name_enum */
    LX_COLOR_ORANGE_210                  = 0xBFDFFF,    /* lx_color_name_enum */
    LX_COLOR_ORANGE_220                  = 0xD5EAFF,    /* lx_color_name_enum */
    LX_COLOR_ORANGE_70                   = 0x004A95,    /* lx_color_name_enum */
    LX_COLOR_ORANGE_80                   = 0x0055AA,    /* lx_color_name_enum */
    LX_COLOR_ORANGE_90                   = 0x0056BF,    /* lx_color_name_enum */
    LX_COLOR_RED_1                       = 0x0000E0,    /* lx_color_name_enum */
    LX_COLOR_RED_2                       = 0x0000C0,    /* lx_color_name_enum */
    LX_COLOR_RED_3                       = 0x0000A0,    /* lx_color_name_enum */
    LX_COLOR_RED_4                       = 0x000080,    /* lx_color_name_enum */
    LX_COLOR_RED_5                       = 0x000060,    /* lx_color_name_enum */
    LX_COLOR_RED_6                       = 0x000040,    /* lx_color_name_enum */
    LX_COLOR_RED_7                       = 0x000020,    /* lx_color_name_enum */

#if 000
    /* Windows system colors */
    LX_COLOR_SYS_3D_DK_SHADOW            = 0x80000015,  /* lx_color_name_enum */
    LX_COLOR_SYS_3D_FACE                 = 0x8000000F,  /* lx_color_name_enum */
    LX_COLOR_SYS_3D_HLIGHT               = 0x80000014,  /* lx_color_name_enum */
    LX_COLOR_SYS_3D_LIGHT                = 0x80000016,  /* lx_color_name_enum */
    LX_COLOR_SYS_3D_SHADOW               = 0x80000010,  /* lx_color_name_enum */
    LX_COLOR_SYS_ACTIVE_BORDER           = 0x8000000A,  /* lx_color_name_enum */
    LX_COLOR_SYS_ACTIVE_TITLE_BAR        = 0x80000002,  /* lx_color_name_enum */
    LX_COLOR_SYS_ACTIVE_TITLE_BAR_TEXT   = 0x80000009,  /* lx_color_name_enum */
    LX_COLOR_SYS_APP_WORKSPACE           = 0x8000000C,  /* lx_color_name_enum */
    LX_COLOR_SYS_BTN_FACE                = 0x8000000F,  /* lx_color_name_enum */
    LX_COLOR_SYS_BTN_SHADOW              = 0x80000010,  /* lx_color_name_enum */
    LX_COLOR_SYS_BTN_TEXT                = 0x80000012,  /* lx_color_name_enum */
    LX_COLOR_SYS_DESKTOP                 = 0x80000001,  /* lx_color_name_enum */
    LX_COLOR_SYS_GRAY_TEXT               = 0x80000011,  /* lx_color_name_enum */
    LX_COLOR_SYS_HLIGHT                  = 0x8000000D,  /* lx_color_name_enum */
    LX_COLOR_SYS_HLIGHT_TEXT             = 0x8000000E,  /* lx_color_name_enum */
    LX_COLOR_SYS_INACTIVE_BORDER         = 0x8000000B,  /* lx_color_name_enum */
    LX_COLOR_SYS_INACTIVE_CAPTION_TEXT   = 0x80000013,  /* lx_color_name_enum */
    LX_COLOR_SYS_INACTIVE_TITLE_BAR      = 0x80000003,  /* lx_color_name_enum */
    LX_COLOR_SYS_INACTIVE_TITLE_BAR_TEXT = 0x80000013,  /* lx_color_name_enum */
    LX_COLOR_SYS_INFO_BACK               = 0x80000018,  /* lx_color_name_enum */
    LX_COLOR_SYS_INFO_TEXT               = 0x80000017,  /* lx_color_name_enum */
    LX_COLOR_SYS_MENU_BAR                = 0x80000004,  /* lx_color_name_enum */
    LX_COLOR_SYS_MENU_TEXT               = 0x80000007,  /* lx_color_name_enum */
    LX_COLOR_SYS_SCROLLBARS              = 0x80000000,  /* lx_color_name_enum */
    LX_COLOR_SYS_TITLE_BAR_TEXT          = 0x80000009,  /* lx_color_name_enum */
    LX_COLOR_SYS_WND_BACK                = 0x80000005,  /* lx_color_name_enum */
    LX_COLOR_SYS_WND_FRAME               = 0x80000006,  /* lx_color_name_enum */
    LX_COLOR_SYS_WND_TEXT                = 0x80000008,  /* lx_color_name_enum */
#endif                                                                 /* 000 */
}
lx_color_name_enum;                                                     /*enum*/

/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */

/* To initialize a default color use: var_name = LX_COLOR_NULL;               */

/* Return a color value based on the name of a color.                         */
/* If the color can not be converted, returns LX_COLOR_NULL                   */
LX_PUBLIC lx_color_t  lx_Color_fromName( lx_chars_t  color_name_ );        /*C*/

/* Return a physical color from a logical system color value.                 */
LX_PUBLIC lx_color_t  lx_Color_fromSystem( const lx_color_t  os_color_ );  /*C*/

/* Return a physical color value composed from red, green and blue parts.     */
LX_PUBLIC lx_color_t  lx_Color_fromRgb(                                    /*C*/
    const int  red_part_,                                                  /*-*/
    const int  green_part_,                                                /*-*/
    const int  blue_part_ );                                               /*-*/

/* Return a physical color value based on a color integer.                    */
LX_PUBLIC lx_color_t  lx_Color_fromValue( const lx_color_t  value_ );      /*C*/

/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */

LX_PUBLIC uint8_t  lx_Color_getBlue( const lx_color_t  color_ );           /*M*/

LX_PUBLIC uint8_t  lx_Color_getGreen( const lx_color_t  color_ );          /*M*/

LX_PUBLIC uint8_t  lx_Color_getRed( const lx_color_t  color_ );            /*M*/

LX_PUBLIC lx_color_t  lx_Color_brighten(                                   /*M*/
    const lx_color_t  color_,                                              /*-*/
    const double      ratio_ );                                            /*-*/

LX_PUBLIC lx_color_t  lx_Color_shift(                                      /*M*/
    const lx_color_t  color_,                                              /*-*/
    const int         steps_ );                                            /*-*/

LX_PUBLIC lx_color_t  lx_Color_blend(                                      /*M*/
    const lx_color_t  color1_,                                             /*-*/
    const lx_color_t  color2_,                                             /*-*/
    const size_t      color1_percent_ );                                   /*-*/

/* convert logical (system) color values to physical color values.            */
LX_PUBLIC lx_color_t  lx_Color_rgb( const lx_color_t  logic_color_ );      /*M*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
