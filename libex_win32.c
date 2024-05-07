/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_win32.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_config_.h"
#include "libex_win32_.h"
#if defined INCLUDED_LIBEX_WIN32_H && PLATFORM_WIN32

#include <stdio.h>  /* for sprintf*() */

#include "libex_call_.h"
#include "libex_debug_.h"
#include "libex_error_.h"
#include "libex_macro_.h"
#include "libex_.h"
#include "libex_type_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#if defined _MSC_VER
#pragma warning (disable:4710)  /* W:L4 function not inlined                  */
#endif

/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


/* -------------------------------------------------------------------------- */
/* Functions: Windows-Specific                                                */


PUBLIC chars_t  map_mode_name_win( const UINT_win  map_mode_ ) {           /*F*/
    GO                                                            (UID(F045C3));
    chars_t  ret = NULL;

    switch (map_mode_) {
            CASE_TO_TEXT(MM_ANISOTROPIC_win, ret);
            CASE_TO_TEXT(MM_HIENGLISH_win,   ret);
            CASE_TO_TEXT(MM_HIMETRIC_win,    ret);
            CASE_TO_TEXT(MM_ISOTROPIC_win,   ret);
            CASE_TO_TEXT(MM_LOENGLISH_win,   ret);
            CASE_TO_TEXT(MM_LOMETRIC_win,    ret);
            CASE_TO_TEXT(MM_TEXT_win,        ret);
            CASE_TO_TEXT(MM_TWIPS_win,       ret);
        default: {
            const size_t  size = 20 * sizeof(char_t);
            new_chars_t   msg  = MALLOC(size);

            MEMSET(msg, 0x00, size);
            SNPRINTF_T(msg, size, _T("UNKNOWN MAP MODE: 0x%x"), map_mode_);
            WARN(msg, UID(E8CF6B));
            FREE(&msg);
            ret = _T("UNKNOWN_MESSAGE");
        }
    } /* switch */

    RETURN(ret);
} /* map_mode_name_win */


PUBLIC int  message_loop_win( void ) {                                     /*F*/
    GO                                                            (UID(FB6CD4));
    bool      ret    = false;
    BOOL_win  result = FALSE_win;
    MSG_win   msg;

    CLEAR(msg);

    /* just wait for a WM_QUIT message to end the program */
    while ((result = GetMessage_win(&msg, NULL, 0, 0)) != 0) {
        if (result == -1) { /* normally, result never returns -1 */
            ret = 0;
            break;
        } else {
            TranslateMessage_win(&msg);
            DispatchMessage_win(&msg);
        }

        if (msg.message == WM_QUIT) {
            ret = 1;
            break;
        }
    }
    RETURN(ret);
} /* message_loop_win */


PUBLIC chars_t  message_name_win( const UINT_win  message_code_ ) {        /*F*/
    GO                                                            (UID(F7D434));
    /* all these WM__win... constants are defined in WinUser.h */
    /* additional constants that may not be defined unless     */
    /* the proper Windows version is used, are defined below,  */
    /* as they are defined in WinUser.h                        */
    chars_t  ret = NULL;

    switch (message_code_) {
            CASE_TO_TEXT(WM_ACTIVATE_win,               ret);
            CASE_TO_TEXT(WM_ACTIVATEAPP_win,            ret);
            CASE_TO_TEXT(WM_AFXFIRST_win,               ret);
            CASE_TO_TEXT(WM_AFXLAST_win,                ret);
            CASE_TO_TEXT(WM_APP_win,                    ret);
            CASE_TO_TEXT(WM_ASKCBFORMATNAME_win,        ret);
            CASE_TO_TEXT(WM_CANCELJOURNAL_win,          ret);
            CASE_TO_TEXT(WM_CANCELMODE_win,             ret);
            CASE_TO_TEXT(WM_CAPTURECHANGED_win,         ret);
            CASE_TO_TEXT(WM_CHANGECBCHAIN_win,          ret);
            CASE_TO_TEXT(WM_CHAR_win,                   ret);
            CASE_TO_TEXT(WM_CHARTOITEM_win,             ret);
            CASE_TO_TEXT(WM_CHILDACTIVATE_win,          ret);
            CASE_TO_TEXT(WM_CLEAR_win,                  ret);
            CASE_TO_TEXT(WM_CLOSE_win,                  ret);
            CASE_TO_TEXT(WM_COMMAND_win,                ret);
            CASE_TO_TEXT(WM_COMMNOTIFY_win,             ret);
            CASE_TO_TEXT(WM_COMPACTING_win,             ret);
            CASE_TO_TEXT(WM_COMPAREITEM_win,            ret);
            CASE_TO_TEXT(WM_CONTEXTMENU_win,            ret);
            CASE_TO_TEXT(WM_COPY_win,                   ret);
            CASE_TO_TEXT(WM_COPYDATA_win,               ret);
            CASE_TO_TEXT(WM_CREATE_win,                 ret);
            CASE_TO_TEXT(WM_CTLCOLORBTN_win,            ret);
            CASE_TO_TEXT(WM_CTLCOLORDLG_win,            ret);
            CASE_TO_TEXT(WM_CTLCOLOREDIT_win,           ret);
            CASE_TO_TEXT(WM_CTLCOLORLISTBOX_win,        ret);
            CASE_TO_TEXT(WM_CTLCOLORMSGBOX_win,         ret);
            CASE_TO_TEXT(WM_CTLCOLORSCROLLBAR_win,      ret);
            CASE_TO_TEXT(WM_CTLCOLORSTATIC_win,         ret);
            CASE_TO_TEXT(WM_CUT_win,                    ret);
            CASE_TO_TEXT(WM_DEADCHAR_win,               ret);
            CASE_TO_TEXT(WM_DELETEITEM_win,             ret);
            CASE_TO_TEXT(WM_DESTROY_win,                ret);
            CASE_TO_TEXT(WM_DESTROYCLIPBOARD_win,       ret);
            CASE_TO_TEXT(WM_DEVICECHANGE_win,           ret);
            CASE_TO_TEXT(WM_DEVMODECHANGE_win,          ret);
            CASE_TO_TEXT(WM_DISPLAYCHANGE_win,          ret);
            CASE_TO_TEXT(WM_DRAWCLIPBOARD_win,          ret);
            CASE_TO_TEXT(WM_DRAWITEM_win,               ret);
            CASE_TO_TEXT(WM_DROPFILES_win,              ret);
            CASE_TO_TEXT(WM_ENABLE_win,                 ret);
            CASE_TO_TEXT(WM_ENDSESSION_win,             ret);
            CASE_TO_TEXT(WM_ENTERIDLE_win,              ret);
            CASE_TO_TEXT(WM_ENTERMENULOOP_win,          ret);
            CASE_TO_TEXT(WM_ENTERSIZEMOVE_win,          ret);
            CASE_TO_TEXT(WM_ERASEBKGND_win,             ret);
            CASE_TO_TEXT(WM_EXITMENULOOP_win,           ret);
            CASE_TO_TEXT(WM_EXITSIZEMOVE_win,           ret);
            CASE_TO_TEXT(WM_FONTCHANGE_win,             ret);
            CASE_TO_TEXT(WM_GETDLGCODE_win,             ret);
            CASE_TO_TEXT(WM_GETFONT_win,                ret);
            CASE_TO_TEXT(WM_GETHOTKEY_win,              ret);
            CASE_TO_TEXT(WM_GETICON_win,                ret);
            CASE_TO_TEXT(WM_GETMINMAXINFO_win,          ret);
            CASE_TO_TEXT(WM_GETTEXT_win,                ret);
            CASE_TO_TEXT(WM_GETTEXTLENGTH_win,          ret);
            CASE_TO_TEXT(WM_HANDHELDFIRST_win,          ret);
            CASE_TO_TEXT(WM_HANDHELDLAST_win,           ret);
            CASE_TO_TEXT(WM_HELP_win,                   ret);
            CASE_TO_TEXT(WM_HOTKEY_win,                 ret);
            CASE_TO_TEXT(WM_HSCROLL_win,                ret);
            CASE_TO_TEXT(WM_HSCROLLCLIPBOARD_win,       ret);
            CASE_TO_TEXT(WM_ICONERASEBKGND_win,         ret);
            CASE_TO_TEXT(WM_IME_CHAR_win,               ret);
            CASE_TO_TEXT(WM_IME_COMPOSITION_win,        ret);
            CASE_TO_TEXT(WM_IME_COMPOSITIONFULL_win,    ret);
            CASE_TO_TEXT(WM_IME_CONTROL_win,            ret);
            CASE_TO_TEXT(WM_IME_ENDCOMPOSITION_win,     ret);
            CASE_TO_TEXT(WM_IME_KEYDOWN_win,            ret);
            CASE_TO_TEXT(WM_IME_KEYUP_win,              ret);
            CASE_TO_TEXT(WM_IME_NOTIFY_win,             ret);
            CASE_TO_TEXT(WM_IME_SELECT_win,             ret);
            CASE_TO_TEXT(WM_IME_SETCONTEXT_win,         ret);
            CASE_TO_TEXT(WM_IME_STARTCOMPOSITION_win,   ret);
            CASE_TO_TEXT(WM_INITDIALOG_win,             ret);
            CASE_TO_TEXT(WM_INITMENU_win,               ret);
            CASE_TO_TEXT(WM_INITMENUPOPUP_win,          ret);
            CASE_TO_TEXT(WM_INPUTLANGCHANGE_win,        ret);
            CASE_TO_TEXT(WM_INPUTLANGCHANGEREQUEST_win, ret);
            CASE_TO_TEXT(WM_KEYDOWN_win,                ret);
            CASE_TO_TEXT(WM_KEYUP_win,                  ret);
            CASE_TO_TEXT(WM_KILLFOCUS_win,              ret);
            CASE_TO_TEXT(WM_LBUTTONDBLCLK_win,          ret);
            CASE_TO_TEXT(WM_LBUTTONDOWN_win,            ret);
            CASE_TO_TEXT(WM_LBUTTONUP_win,              ret);
            CASE_TO_TEXT(WM_MBUTTONDBLCLK_win,          ret);
            CASE_TO_TEXT(WM_MBUTTONDOWN_win,            ret);
            CASE_TO_TEXT(WM_MBUTTONUP_win,              ret);
            CASE_TO_TEXT(WM_MDIACTIVATE_win,            ret);
            CASE_TO_TEXT(WM_MDICASCADE_win,             ret);
            CASE_TO_TEXT(WM_MDICREATE_win,              ret);
            CASE_TO_TEXT(WM_MDIDESTROY_win,             ret);
            CASE_TO_TEXT(WM_MDIGETACTIVE_win,           ret);
            CASE_TO_TEXT(WM_MDIICONARRANGE_win,         ret);
            CASE_TO_TEXT(WM_MDIMAXIMIZE_win,            ret);
            CASE_TO_TEXT(WM_MDINEXT_win,                ret);
            CASE_TO_TEXT(WM_MDIREFRESHMENU_win,         ret);
            CASE_TO_TEXT(WM_MDIRESTORE_win,             ret);
            CASE_TO_TEXT(WM_MDISETMENU_win,             ret);
            CASE_TO_TEXT(WM_MDITILE_win,                ret);
            CASE_TO_TEXT(WM_MEASUREITEM_win,            ret);
            CASE_TO_TEXT(WM_MENUCHAR_win,               ret);
            CASE_TO_TEXT(WM_MENUSELECT_win,             ret);
            CASE_TO_TEXT(WM_MOUSEACTIVATE_win,          ret);
            CASE_TO_TEXT(WM_MOUSEHOVER_win,             ret);
            CASE_TO_TEXT(WM_MOUSELEAVE_win,             ret);
            CASE_TO_TEXT(WM_MOUSEMOVE_win,              ret);
            CASE_TO_TEXT(WM_MOUSEWHEEL_win,             ret);
            CASE_TO_TEXT(WM_MOVE_win,                   ret);
            CASE_TO_TEXT(WM_MOVING_win,                 ret);
            CASE_TO_TEXT(WM_NCACTIVATE_win,             ret);
            CASE_TO_TEXT(WM_NCCALCSIZE_win,             ret);
            CASE_TO_TEXT(WM_NCCREATE_win,               ret);
            CASE_TO_TEXT(WM_NCDESTROY_win,              ret);
            CASE_TO_TEXT(WM_NCHITTEST_win,              ret);
            CASE_TO_TEXT(WM_NCLBUTTONDBLCLK_win,        ret);
            CASE_TO_TEXT(WM_NCLBUTTONDOWN_win,          ret);
            CASE_TO_TEXT(WM_NCLBUTTONUP_win,            ret);
            CASE_TO_TEXT(WM_NCMBUTTONDBLCLK_win,        ret);
            CASE_TO_TEXT(WM_NCMBUTTONDOWN_win,          ret);
            CASE_TO_TEXT(WM_NCMBUTTONUP_win,            ret);
            CASE_TO_TEXT(WM_NCMOUSEMOVE_win,            ret);
            CASE_TO_TEXT(WM_NCPAINT_win,                ret);
            CASE_TO_TEXT(WM_NCRBUTTONDBLCLK_win,        ret);
            CASE_TO_TEXT(WM_NCRBUTTONDOWN_win,          ret);
            CASE_TO_TEXT(WM_NCRBUTTONUP_win,            ret);
            CASE_TO_TEXT(WM_NEXTDLGCTL_win,             ret);
            CASE_TO_TEXT(WM_NEXTMENU_win,               ret);
            CASE_TO_TEXT(WM_NOTIFY_win,                 ret);
            CASE_TO_TEXT(WM_NOTIFYFORMAT_win,           ret);
            CASE_TO_TEXT(WM_NULL_win,                   ret);
            CASE_TO_TEXT(WM_PAINT_win,                  ret);
            CASE_TO_TEXT(WM_PAINTCLIPBOARD_win,         ret);
            CASE_TO_TEXT(WM_PAINTICON_win,              ret);
            CASE_TO_TEXT(WM_PALETTECHANGED_win,         ret);
            CASE_TO_TEXT(WM_PALETTEISCHANGING_win,      ret);
            CASE_TO_TEXT(WM_PARENTNOTIFY_win,           ret);
            CASE_TO_TEXT(WM_PASTE_win,                  ret);
            CASE_TO_TEXT(WM_PENWINFIRST_win,            ret);
            CASE_TO_TEXT(WM_PENWINLAST_win,             ret);
            CASE_TO_TEXT(WM_POWER_win,                  ret);
            CASE_TO_TEXT(WM_POWERBROADCAST_win,         ret);
            CASE_TO_TEXT(WM_PRINT_win,                  ret);
            CASE_TO_TEXT(WM_PRINTCLIENT_win,            ret);
            CASE_TO_TEXT(WM_QUERYDRAGICON_win,          ret);
            CASE_TO_TEXT(WM_QUERYENDSESSION_win,        ret);
            CASE_TO_TEXT(WM_QUERYNEWPALETTE_win,        ret);
            CASE_TO_TEXT(WM_QUERYOPEN_win,              ret);
            CASE_TO_TEXT(WM_QUEUESYNC_win,              ret);
            CASE_TO_TEXT(WM_QUIT_win,                   ret);
            CASE_TO_TEXT(WM_RBUTTONDBLCLK_win,          ret);
            CASE_TO_TEXT(WM_RBUTTONDOWN_win,            ret);
            CASE_TO_TEXT(WM_RBUTTONUP_win,              ret);
            CASE_TO_TEXT(WM_RENDERALLFORMATS_win,       ret);
            CASE_TO_TEXT(WM_RENDERFORMAT_win,           ret);
            CASE_TO_TEXT(WM_SETCURSOR_win,              ret);
            CASE_TO_TEXT(WM_SETFOCUS_win,               ret);
            CASE_TO_TEXT(WM_SETFONT_win,                ret);
            CASE_TO_TEXT(WM_SETHOTKEY_win,              ret);
            CASE_TO_TEXT(WM_SETICON_win,                ret);
            CASE_TO_TEXT(WM_SETREDRAW_win,              ret);
            CASE_TO_TEXT(WM_SETTEXT_win,                ret);
            CASE_TO_TEXT(WM_SETTINGCHANGE_win,          ret);
            CASE_TO_TEXT(WM_SHOWWINDOW_win,             ret);
            CASE_TO_TEXT(WM_SIZE_win,                   ret);
            CASE_TO_TEXT(WM_SIZECLIPBOARD_win,          ret);
            CASE_TO_TEXT(WM_SIZING_win,                 ret);
            CASE_TO_TEXT(WM_SPOOLERSTATUS_win,          ret);
            CASE_TO_TEXT(WM_STYLECHANGED_win,           ret);
            CASE_TO_TEXT(WM_STYLECHANGING_win,          ret);
            CASE_TO_TEXT(WM_SYNCPAINT_win,              ret);
            CASE_TO_TEXT(WM_SYSCHAR_win,                ret);
            CASE_TO_TEXT(WM_SYSCOLORCHANGE_win,         ret);
            CASE_TO_TEXT(WM_SYSCOMMAND_win,             ret);
            CASE_TO_TEXT(WM_SYSDEADCHAR_win,            ret);
            CASE_TO_TEXT(WM_SYSKEYDOWN_win,             ret);
            CASE_TO_TEXT(WM_SYSKEYUP_win,               ret);
            CASE_TO_TEXT(WM_TCARD_win,                  ret);
            CASE_TO_TEXT(WM_TIMECHANGE_win,             ret);
            CASE_TO_TEXT(WM_TIMER_win,                  ret);
            CASE_TO_TEXT(WM_UNDO_win,                   ret);
            CASE_TO_TEXT(WM_USER_win,                   ret);
            CASE_TO_TEXT(WM_USERCHANGED_win,            ret);
            CASE_TO_TEXT(WM_VKEYTOITEM_win,             ret);
            CASE_TO_TEXT(WM_VSCROLL_win,                ret);
            CASE_TO_TEXT(WM_VSCROLLCLIPBOARD_win,       ret);
            CASE_TO_TEXT(WM_WINDOWPOSCHANGED_win,       ret);
            CASE_TO_TEXT(WM_WINDOWPOSCHANGING_win,      ret);

#if defined WINVER && WINVER >= 0x0500
            CASE_TO_TEXT(WM_GETOBJECT_win,       ret);
            CASE_TO_TEXT(WM_IME_REQUEST_win,     ret);
            CASE_TO_TEXT(WM_MENUCOMMAND_win,     ret);
            CASE_TO_TEXT(WM_MENUDRAG_win,        ret);
            CASE_TO_TEXT(WM_MENUGETOBJECT_win,   ret);
            CASE_TO_TEXT(WM_MENURBUTTONUP_win,   ret);
            CASE_TO_TEXT(WM_NCMOUSEHOVER_win,    ret);
            CASE_TO_TEXT(WM_NCMOUSELEAVE_win,    ret);
            CASE_TO_TEXT(WM_UNINITMENUPOPUP_win, ret);
#endif                                                    /* WINVER >= 0x0500 */

#if (_WIN32_WINNT >= 0x0500)
            CASE_TO_TEXT(WM_APPCOMMAND_win,      ret);
            CASE_TO_TEXT(WM_CHANGEUISTATE_win,   ret);
            CASE_TO_TEXT(WM_NCXBUTTONDBLCLK_win, ret);
            CASE_TO_TEXT(WM_NCXBUTTONDOWN_win,   ret);
            CASE_TO_TEXT(WM_NCXBUTTONUP_win,     ret);
            CASE_TO_TEXT(WM_QUERYUISTATE_win,    ret);
            CASE_TO_TEXT(WM_UPDATEUISTATE_win,   ret);
            CASE_TO_TEXT(WM_XBUTTONDBLCLK_win,   ret);
            CASE_TO_TEXT(WM_XBUTTONDOWN_win,     ret);
            CASE_TO_TEXT(WM_XBUTTONUP_win,       ret);
#endif                                              /* _WIN32_WINNT >= 0x0500 */

#if (_WIN32_WINNT >= 0x0501)
            CASE_TO_TEXT(WM_INPUT_win,             ret);
            CASE_TO_TEXT(WM_TABLET_FIRST_win,      ret);
            CASE_TO_TEXT(WM_TABLET_LAST_win,       ret);
            CASE_TO_TEXT(WM_THEMECHANGED_win,      ret);
            CASE_TO_TEXT(WM_UNICHAR_win,           ret);
            CASE_TO_TEXT(WM_WTSSESSION_CHANGE_win, ret);
#endif                                              /* _WIN32_WINNT >= 0x0501 */

            /* edit control messages */
            CASE_TO_TEXT(EM_CANUNDO_win,             ret);
            CASE_TO_TEXT(EM_EMPTYUNDOBUFFER_win,     ret);
            CASE_TO_TEXT(EM_FMTLINES_win,            ret);
            CASE_TO_TEXT(EM_GETFIRSTVISIBLELINE_win, ret);
            CASE_TO_TEXT(EM_GETHANDLE_win,           ret);
            CASE_TO_TEXT(EM_GETLINE_win,             ret);
            CASE_TO_TEXT(EM_GETLINECOUNT_win,        ret);
            CASE_TO_TEXT(EM_GETMODIFY_win,           ret);
            CASE_TO_TEXT(EM_GETPASSWORDCHAR_win,     ret);
            CASE_TO_TEXT(EM_GETRECT_win,             ret);
            CASE_TO_TEXT(EM_GETSEL_win,              ret);
            CASE_TO_TEXT(EM_GETTHUMB_win,            ret);
            CASE_TO_TEXT(EM_GETWORDBREAKPROC_win,    ret);
            CASE_TO_TEXT(EM_LINEFROMCHAR_win,        ret);
            CASE_TO_TEXT(EM_LINEINDEX_win,           ret);
            CASE_TO_TEXT(EM_LINELENGTH_win,          ret);
            CASE_TO_TEXT(EM_LINESCROLL_win,          ret);
            CASE_TO_TEXT(EM_REPLACESEL_win,          ret);
            CASE_TO_TEXT(EM_SCROLL_win,              ret);
            CASE_TO_TEXT(EM_SCROLLCARET_win,         ret);
            CASE_TO_TEXT(EM_SETHANDLE_win,           ret);
            CASE_TO_TEXT(EM_SETMODIFY_win,           ret);
            CASE_TO_TEXT(EM_SETPASSWORDCHAR_win,     ret);
            CASE_TO_TEXT(EM_SETREADONLY_win,         ret);
            CASE_TO_TEXT(EM_SETRECT_win,             ret);
            CASE_TO_TEXT(EM_SETRECTNP_win,           ret);
            CASE_TO_TEXT(EM_SETSEL_win,              ret);
            CASE_TO_TEXT(EM_SETTABSTOPS_win,         ret);
            CASE_TO_TEXT(EM_SETWORDBREAKPROC_win,    ret);
            CASE_TO_TEXT(EM_UNDO_win,                ret);

#if defined WINVER && WINVER < 0x0400
            CASE_TO_TEXT(EM_LIMITTEXT_win, ret);
#else                                            /* WINVER && WINVER < 0x0400 */
            CASE_TO_TEXT(EM_SETLIMITTEXT_win, ret);
#endif                                         /* !WINVER && !WINVER < 0x0400 */

#if defined WINVER && WINVER >= 0x0400
            CASE_TO_TEXT(EM_CHARFROMPOS_win,  ret);
            CASE_TO_TEXT(EM_GETLIMITTEXT_win, ret);
            CASE_TO_TEXT(EM_GETMARGINS_win,   ret);
            CASE_TO_TEXT(EM_POSFROMCHAR_win,  ret);
            CASE_TO_TEXT(EM_SETMARGINS_win,   ret);
#endif                                                    /* WINVER >= 0x0400 */

#if defined WINVER && WINVER >= 0x0500
            CASE_TO_TEXT(EM_GETIMESTATUS_win, ret);
            CASE_TO_TEXT(EM_SETIMESTATUS_win, ret);
#endif                                                    /* WINVER >= 0x0500 */
        default: {
            const size_t  size = 20 * sizeof(char_t);
            new_chars_t   msg  = MALLOC(size);

            MEMSET(msg, 0x00, size);
            SNPRINTF_T(msg, size, _T("UNKNOWN MSG ID: 0x%x"), message_code_);
            WARN(msg, UID(E53514));
            FREE(&msg);
            ret = _T("UNKNOWN_MESSAGE");
        }
    } /* switch */

    RETURN(ret);
} /* message_name_win */


PUBLIC void  post_quit_message_to_thread_win(                              /*F*/
    const DWORD_win  thread_id_ ) {                                        /*-*/
    GO                                                            (UID(F4F43A));
    OS_VERIFY(PostThreadMessage_win(
                  thread_id_,    /* DWORD idThread */
                  WM_QUIT_win,   /* UINT Msg       */
                  0,             /* WPARAM wParam  */
                  0),            /* LPARAM lParam  */
              UID(E55E49));
    RETURN(NIL);
} /* quit_message_win */


PUBLIC new_chars_t  resource_html_win(                                     /*F*/
    const UINT_win       resource_id_,                                     /*-*/
    const HINSTANCE_win  instance_ ) {                                     /*-*/
    GO                                                            (UID(F7C7E2));
    new_chars_t   ret      = NULL;
    HGLOBAL_win   hres     = NULL;
    LPVOID_win    resource = NULL;
    uint8_t*      buf      = NULL;
    DWORD_win     byte_len = 0;

    /* TODO: this modified function hasn't been checked */
#if (defined DEBUG || defined _DEBUG) && defined _MSC_VER
    DEBUG_BREAK;
#endif

    {
        /* get instance handle, if not specified */
#if defined _MFC_VER
        const HINSTANCE_win  instance =
            (instance_ == NULL) ? AfxGetInstanceHandle() : instance_;
#else                                                             /* _MFC_VER */
        const HINSTANCE_win  instance =
            (instance_ == NULL) ? GetModuleHandle_win(NULL) : instance_;
#endif                                                           /* !_MFC_VER */

        /* locate the resource and determine its size */
        const HRSRC_win  resource_info =
            FindResource_win(instance, MAKEINTRESOURCE_win(resource_id_),
                             RT_HTML_win);

        if (resource_info == NULL) {
            OS_WARN(_T("FindResource()"), UID(E840F7));
            RETURN(NULL);
        }

        byte_len = SizeofResource_win(instance, resource_info);
        if (byte_len < 1) {
            OS_WARN(_T("SizeofResource()"), UID(E663AF));
            RETURN(NULL);
        }

        /* load the resource */
        hres = LoadResource_win(instance, resource_info);
        if (hres == NULL) {
            OS_WARN(_T("LoadResource()"), UID(EE2FF8));
            RETURN(NULL);
        }

        /* lock the resource */
        resource = LockResource_win(hres);
        if (resource == NULL) {
            OS_WARN(_T("LockResource_win()"), UID(EC975A));
            RETURN(NULL);
        }

        /* allocate buffer (+ 1 for terminating \0) */
        buf = CAST(uint8_t*, MALLOC(byte_len + 1));

        /* convert multibyte characters to wide characters if necessary */
        if (buf != NULL) {
            const char*  src = CAST(char*, buf);

            /* copy resource bytes into buffer */
            MEMSET(buf, 0x00, byte_len + 1);
            MEMCPY(buf, resource, byte_len);

            if (src == NULL) {
                FREE(buf);
                RETURN(NULL);
            }

#if defined UNICODE || defined _UNICODE
            {
                const size_t  len = STRLEN(src);
                ret = MALLOC((len + 1) * sizeof(char_t));

#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4996)  /* W:L3 'function': may be unsafe/deprecated  */
#endif
                MBSTOWCS(ret, src, len);
#if defined _MSC_VER
#pragma warning (pop)
#endif

                *(ret + len) = '\0';
            }
            FREE(buf);
#else                                                  /* UNICODE || _UNICODE */
            ret = CAST(char*, buf);
#endif                                               /* !UNICODE && !_UNICODE */
        }
    }
    RETURN(ret);
} /* resource_html_win */


PUBLIC new_chars_t  resource_text_win(                                     /*F*/
    const UINT_win       resource_id_,                                     /*-*/
    const HINSTANCE_win  instance_ ) {                                     /*-*/
    GO                                                            (UID(FD3DC0));
    new_chars_t  ret        = { NULL };
    DWORD_win    bytes_size = 0;

    /* get instance handle, if not specified */
    const HINSTANCE_win  instance =
        (instance_ == NULL) ? GetModuleHandle_win(NULL) : instance_;

    {
        /* determine size of resource in bytes */
        LPTSTR_win  name = MAKEINTRESOURCE_win((resource_id_ >> 4) + 1);

        HRSRC_win  resource_info =
            FindResource_win(instance, name, RT_STRING_win);

        if (resource_info == NULL) {
            ret = NULL;
            RETURN(ret);
        }

        bytes_size = SizeofResource_win(instance, resource_info);

        if (bytes_size < 1) {
            ret = NULL;
            RETURN(ret);
        }
    }

    {
        /* allocate buffer */
        bytes_size += sizeof(char_t);  /* for terminating \0 */
        ret = MALLOC(bytes_size);

        {
            /* load string into buffer */
            const int  char_len =
                LoadString_win(instance, resource_id_, ret, bytes_size);

            if (char_len < 1) {
                ret = NULL;
                RETURN(ret);
            }
        }
        RETURN(ret);
    }
} /* resource_text_win */


PUBLIC new_chars_t  window_text_win( const HWND_win  window_ ) {           /*F*/
    GO                                                            (UID(FD272A));
    const int  len = GetWindowTextLength_win(window_);

    if (len > 0) {
        const size_t  bytes = (len + 1) * sizeof(char_t);
        new_chars_t   ret   = MALLOC(bytes);

        MEMSET(ret, 0x00, bytes);  /* + 1 for \0 */
        GetWindowText_win(window_, ret, len + 1);
        *(ret + len) = 0;
        RETURN(ret);
    }
    RETURN(NULL);
} /* window_text_win */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
