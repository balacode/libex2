/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                   [libex_clipboard.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_clipboard_.h"
#if defined INCLUDED_LIBEX_CLIPBOARD_H

#include "libex_config_.h"

#include "libex_.h"
#include "libex_call_.h"
#include "libex_debug_.h"
#include "libex_error_.h"
#include "libex_string_class_.h"
#include "libex_type_.h"

#if PLATFORM_WIN32
#include "libex_win32_.h"
#endif

#if defined __cplusplus_cli
#pragma unmanaged
#endif


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


PUBLIC new_str_t  Clipboard_getText( void ) {                              /*M*/
    GO                                                            (UID(FBF6C4));
    new_str_t  ret = { NULL };

#if PLATFORM_WIN32
    if (0 != OpenClipboard_win(NULL)) {
        const UINT_win  fmt =
            sizeof(char_t) == 2 ? CF_UNICODETEXT_win : CF_TEXT_win;

        if (0 != IsClipboardFormatAvailable_win(fmt)) {
            HGLOBAL_win  hclip = GetClipboardData_win(fmt);

            if (hclip != NULL) {
                LPTSTR_win  data = CAST(LPTSTR_win, GlobalLock_win(hclip));
                if (data != NULL) {
                    ret = S_chars(data);
                    GlobalUnlock_win(data);
                }
            }
        }
        OS_VERIFY(CloseClipboard_win(), UID(ED0A60));
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* Clipboard_getText */


PUBLIC bool  Clipboard_setText( chars_t  text_ ) {                         /*M*/
    GO                                                            (UID(F98AF5));
    bool  ret = false;

#if PLATFORM_LINUX
    UNUSED(text_);
    IMPLEMENT_LINUX();  /* TODO: How to set clipboard text in GNOME? */
#endif                                                      /* PLATFORM_LINUX */


#if PLATFORM_WIN32
    bool          is_locked     = false;
    bool          is_clip_open  = false;
    HWND_win      active_window = NULL;     /* initialize before 'goto _exit' */
    HGLOBAL_win   handle        = NULL;
    const size_t  len           = STRLEN_T(text_) + 1;

    if (len < 2) {
        RETURN(false);
    }

    {
        /* allocate memory */
        const size_t  bytes_size = len * sizeof(char_t);
        handle = GlobalAlloc_win(GMEM_MOVEABLE_win, bytes_size);

        if (handle == NULL) {
            RETURN(false);
        }

        if (GlobalSize_win(handle) != bytes_size) {
            DEBUG_WARN(system_error_name(0), UID(E297BD));
            goto _exit;
        }
    }

    {
        /* copy string to memory: */
        /* lock memory            */
        char_t*  buf = CAST(char_t*, GlobalLock_win(handle));
        is_locked = (buf != NULL);

        if (!is_locked) {
            DEBUG_WARN(system_error_name(0), UID(EF74FE));
            goto _exit;
        }

        /* copy to memory */
        STRCPY_S_T(buf, len, text_);
    }

    /* copy data from memory to clipboard */
    active_window = GetActiveWindow_win();
    is_clip_open  = (OpenClipboard_win(active_window) != 0);

    if (!is_clip_open) {
        DEBUG_WARN(system_error_name(0), UID(EDCED7));
        goto _exit;
    } else {
        if (!EmptyClipboard_win()) {
            DEBUG_WARN(system_error_name(0), UID(EAFF0C));
            goto _exit;
        } else {
            const UINT_win  fmt =
                sizeof(char_t) == 2 ? CF_UNICODETEXT_win : CF_TEXT_win;

            ret = (SetClipboardData_win(fmt, handle) != NULL);

            if (!ret) {
                DEBUG_WARN(system_error_name(0), UID(EEFBD2));
                goto _exit;
            }

            if (!CloseClipboard_win()) {
                DEBUG_WARN(system_error_name(0), UID(EFB7AA));
                goto _exit;
            }
        }
    }

_exit:
    /* unlock memory */
    if (is_locked && handle != NULL) {
        const BOOL_win  result = GlobalUnlock_win(handle);
        OS_VERIFY(result == 0 && GetLastError_win() == NO_ERROR_win,
                  UID(E5A090));
    }

    /* close clipboard */
    if (is_clip_open) {
        CloseClipboard_win();
    }

    /* release memory (only if SetClipboardData_win() failed) */
    if (!ret && handle != NULL) {
        OS_VERIFY(GlobalFree_win(handle) == NULL, UID(E3546A));
    }

#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* Clipboard_setText */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
