/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                         [libex_key.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_key_.h"
#if defined INCLUDED_LIBEX_KEY_H

#include "libex_config_.h"

#include "libex_call_.h"
#include "libex_.h"
#include "libex_type_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


/* -------------------------------------------------------------------------- */
/* Functions: Modifier Keys                                                   */

/* returns true if the 'alt' key is being held.                               */
PUBLIC bool  key_alt( void ) {                                             /*F*/
    GO                                                            (UID(FC97D7));
    bool  ret = false;

#if PLATFORM_LINUX
    IMPLEMENT_LINUX();  /* TODO: How to find out if ALT key is down? */
#endif

#if PLATFORM_WIN32
    ret = (GetKeyState_win(VK_MENU_win) < 0);
#endif

    RETURN(ret);
} /* key_alt */


/* returns true if the 'control' key is being held.                           */
PUBLIC bool  key_control( void ) {                                         /*F*/
    GO                                                            (UID(FC209D));
    bool  ret = false;

#if PLATFORM_LINUX
    IMPLEMENT_LINUX();  /* TODO: How to detect CONTROL key down on Linux? */
#endif

#if PLATFORM_WIN32
    ret = (GetKeyState_win(VK_CONTROL_win) < 0);
#endif

    RETURN(ret);
} /* key_control */


/* returns true if the 'shift' key is being held.                             */
PUBLIC bool  key_shift( void ) {                                           /*F*/
    GO                                                            (UID(F2AAFC));
    bool  ret = false;

#if PLATFORM_LINUX
    IMPLEMENT_LINUX();  /* TODO: How to detect SHIFT key down on Linux? */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    ret = (GetKeyState_win(VK_SHIFT_win) < 0);
#endif

    RETURN(ret);
} /* key_shift */


/* -------------------------------------------------------------------------- */
/* Functions:                                                                 */


PUBLIC bool  key_down( const key_code_enum  key_ ) {                       /*F*/
    GO                                                            (UID(FD0992));
    bool  ret = false;

#if PLATFORM_LINUX
    UNUSED(key_);
    IMPLEMENT_LINUX();  /* TODO: How to detect a specific key press Linux? */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    ret = GetKeyState_win(key_to_code(key_)) < 0;
#endif

    RETURN(ret);
} /* key_down */


PUBLIC key_code_enum  key_from_code( const uint32_t  char_ ) {             /*F*/
    GO                                                            (UID(F2A48B));
    const key_code_enum  ret = CAST(key_code_enum, char_);
    RETURN(ret);
} /* key_from_code */


PUBLIC uint32_t  key_to_code( const key_code_enum  key_ ) {                /*F*/
    GO                                                            (UID(F0EFB6));
    const uint32_t  ret = CAST(uint32_t, key_);
    RETURN(ret);
} /* key_to_code */


/*
    UNUSED KEYS:

    have you ever seen a keyboard with so many function keys?
    VK_F13_win
    VK_F14_win
    VK_F15_win
    VK_F16_win
    VK_F17_win
    VK_F18_win
    VK_F19_win
    VK_F20_win
    VK_F21_win
    VK_F22_win
    VK_F23_win
    VK_F24_win

    these are special bells and whistles

    VK_BROWSER_BACK_win
    VK_BROWSER_FORWARD_win
    VK_BROWSER_REFRESH_win
    VK_BROWSER_STOP_win
    VK_BROWSER_SEARCH_win
    VK_BROWSER_FAVORITES_win
    VK_BROWSER_HOME_win

    VK_VOLUME_MUTE_win
    VK_VOLUME_DOWN_win
    VK_VOLUME_UP_win

    VK_MEDIA_NEXT_TRACK_win
    VK_MEDIA_PREV_TRACK_win
    VK_MEDIA_STOP_win
    VK_MEDIA_PLAY_PAUSE_win

    VK_LAUNCH_MAIL_win
    VK_LAUNCH_MEDIA_SELECT_win
    VK_LAUNCH_APP1_win
    VK_LAUNCH_APP2_win

    mouse buttons (let mouse class handle that)

    VK_LBUTTON_win
    VK_RBUTTON_win
    VK_MBUTTON_win

    are these game console keys ?

    VK_XBUTTON1_win
    VK_XBUTTON2_win

*/


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
