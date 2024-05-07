/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                         [libex_key.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_KEY_H
#define      INCLUDED_LIBEX_KEY_H

#include "libex.h"

#if LX_PLATFORM_WIN32
#include "libex_win32.h"
#endif

#if LX_PLATFORM_LINUX
#define _KEY( WIN_KEY_CODE_, LINUX_KEY_CODE_ )  (LINUX_KEY_CODE_)
#endif

#if LX_PLATFORM_WIN32
#define _KEY( WIN_KEY_CODE_, LINUX_KEY_CODE_ )  (WIN_KEY_CODE_)
#endif

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

typedef enum  _lx_key_code_enum {
    LX_KEY_NONE        = 0,                               /* lx_key_code_enum */

    /* number keys */
    LX_KEY_0           = '0',                             /* lx_key_code_enum */
    LX_KEY_1           = '1',                             /* lx_key_code_enum */
    LX_KEY_2           = '2',                             /* lx_key_code_enum */
    LX_KEY_3           = '3',                             /* lx_key_code_enum */
    LX_KEY_4           = '4',                             /* lx_key_code_enum */
    LX_KEY_5           = '5',                             /* lx_key_code_enum */
    LX_KEY_6           = '6',                             /* lx_key_code_enum */
    LX_KEY_7           = '7',                             /* lx_key_code_enum */
    LX_KEY_8           = '8',                             /* lx_key_code_enum */
    LX_KEY_9           = '9',                             /* lx_key_code_enum */

    /* alphabetic keys */
    LX_KEY_A           = 'A',                             /* lx_key_code_enum */
    LX_KEY_B           = 'B',                             /* lx_key_code_enum */
    LX_KEY_C           = 'C',                             /* lx_key_code_enum */
    LX_KEY_D           = 'D',                             /* lx_key_code_enum */
    LX_KEY_E           = 'E',                             /* lx_key_code_enum */
    LX_KEY_F           = 'F',                             /* lx_key_code_enum */
    LX_KEY_G           = 'G',                             /* lx_key_code_enum */
    LX_KEY_H           = 'H',                             /* lx_key_code_enum */
    LX_KEY_I           = 'I',                             /* lx_key_code_enum */
    LX_KEY_J           = 'J',                             /* lx_key_code_enum */
    LX_KEY_K           = 'K',                             /* lx_key_code_enum */
    LX_KEY_L           = 'L',                             /* lx_key_code_enum */
    LX_KEY_M           = 'M',                             /* lx_key_code_enum */
    LX_KEY_N           = 'N',                             /* lx_key_code_enum */
    LX_KEY_O           = 'O',                             /* lx_key_code_enum */
    LX_KEY_P           = 'P',                             /* lx_key_code_enum */
    LX_KEY_Q           = 'Q',                             /* lx_key_code_enum */
    LX_KEY_R           = 'R',                             /* lx_key_code_enum */
    LX_KEY_S           = 'S',                             /* lx_key_code_enum */
    LX_KEY_T           = 'T',                             /* lx_key_code_enum */
    LX_KEY_U           = 'U',                             /* lx_key_code_enum */
    LX_KEY_V           = 'V',                             /* lx_key_code_enum */
    LX_KEY_W           = 'W',                             /* lx_key_code_enum */
    LX_KEY_X           = 'X',                             /* lx_key_code_enum */
    LX_KEY_Y           = 'Y',                             /* lx_key_code_enum */
    LX_KEY_Z           = 'Z',                             /* lx_key_code_enum */

    /* function keys */
    LX_KEY_F1          = _KEY(VK_F1_win,       000),      /* lx_key_code_enum */
    LX_KEY_F2          = _KEY(VK_F2_win,       000),      /* lx_key_code_enum */
    LX_KEY_F3          = _KEY(VK_F3_win,       000),      /* lx_key_code_enum */
    LX_KEY_F4          = _KEY(VK_F4_win,       000),      /* lx_key_code_enum */
    LX_KEY_F5          = _KEY(VK_F5_win,       000),      /* lx_key_code_enum */
    LX_KEY_F6          = _KEY(VK_F6_win,       000),      /* lx_key_code_enum */
    LX_KEY_F7          = _KEY(VK_F7_win,       000),      /* lx_key_code_enum */
    LX_KEY_F8          = _KEY(VK_F8_win,       000),      /* lx_key_code_enum */
    LX_KEY_F9          = _KEY(VK_F9_win,       000),      /* lx_key_code_enum */
    LX_KEY_F10         = _KEY(VK_F10_win,      000),      /* lx_key_code_enum */
    LX_KEY_F11         = _KEY(VK_F11_win,      000),      /* lx_key_code_enum */
    LX_KEY_F12         = _KEY(VK_F12_win,      000),      /* lx_key_code_enum */

    /* navigation keys */

    LX_KEY_LEFT        = _KEY(VK_LEFT_win,     000),      /* lx_key_code_enum */
    LX_KEY_RIGHT       = _KEY(VK_RIGHT_win,    000),      /* lx_key_code_enum */
    LX_KEY_UP          = _KEY(VK_UP_win,       000),      /* lx_key_code_enum */
    LX_KEY_DOWN        = _KEY(VK_DOWN_win,     000),      /* lx_key_code_enum */

    LX_KEY_HOME        = _KEY(VK_HOME_win,     000),      /* lx_key_code_enum */
    LX_KEY_PAGE_UP     = _KEY(VK_PRIOR_win,    000),      /* lx_key_code_enum */
    LX_KEY_PAGE_DOWN   = _KEY(VK_NEXT_win,     000),      /* lx_key_code_enum */
    LX_KEY_END         = _KEY(VK_END_win,      000),      /* lx_key_code_enum */

    LX_KEY_ESC         = _KEY(VK_ESCAPE_win,   000),      /* lx_key_code_enum */
    LX_KEY_SCROLL_LOCK = _KEY(VK_SCROLL_win,   000),      /* lx_key_code_enum */
    LX_KEY_NUMBER_LOCK = _KEY(VK_NUMLOCK_win,  000),      /* lx_key_code_enum */
    LX_KEY_BACKSPACE   = _KEY(VK_BACK_win,     000),      /* lx_key_code_enum */
    LX_KEY_TAB         = _KEY(VK_TAB_win,      000),      /* lx_key_code_enum */

    LX_KEY_PLUS        = _KEY(VK_ADD_win,      000),      /* lx_key_code_enum */
    LX_KEY_MINUS       = _KEY(VK_SUBTRACT_win, 000),      /* lx_key_code_enum */
    LX_KEY_MULTIPLY    = _KEY(VK_MULTIPLY_win, 000),      /* lx_key_code_enum */
    LX_KEY_DIVIDE      = _KEY(VK_DIVIDE_win,   000),      /* lx_key_code_enum */

    LX_KEY_CONTROL     = _KEY(VK_CONTROL_win,  000),      /* lx_key_code_enum */
    LX_KEY_ALT         = _KEY(VK_MENU_win,     000),      /* lx_key_code_enum */
    LX_KEY_SHIFT       = _KEY(VK_SHIFT_win,    000),      /* lx_key_code_enum */

    LX_KEY_DELETE      = _KEY(VK_DELETE_win,   000),      /* lx_key_code_enum */
    LX_KEY_INSERT      = _KEY(VK_INSERT_win,   000),      /* lx_key_code_enum */

    LX_KEY_ENTER       = _KEY(VK_RETURN_win,   000),      /* lx_key_code_enum */
    LX_KEY_SPACE       = _KEY(VK_SPACE_win,    000)       /* lx_key_code_enum */

}
lx_key_code_enum;                                                       /*enum*/

/* -------------------------------------------------------------------------- */
/* Functions: Modifier Keys                                                   */

/* returns true if the 'alt' key is being held.                               */
LX_PUBLIC lx_bool  lx_key_alt( void );                                     /*F*/

/* returns true if the 'control' key is being held.                           */
LX_PUBLIC lx_bool  lx_key_control( void );                                 /*F*/

/* returns true if the 'shift' key is being held.                             */
LX_PUBLIC lx_bool  lx_key_shift( void );                                   /*F*/

/* -------------------------------------------------------------------------- */
/* Functions:                                                                 */

LX_PUBLIC lx_bool  lx_key_down( const lx_key_code_enum  key_ );            /*F*/

LX_PUBLIC lx_key_code_enum  lx_key_from_code( const uint32_t  char_ );     /*F*/

LX_PUBLIC uint32_t  lx_key_to_code( const lx_key_code_enum  key_ );        /*F*/

#undef _KEY

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
