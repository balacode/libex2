/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                     [libex_logging.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_logging_.h"
#if defined INCLUDED_LIBEX_LOGGING_H

#include "libex_config_.h"

#include <stdio.h>   /* for printf() fopen() fclose() sprintf_s() fprintf_s() */
#include <string.h>  /* for memset() strlen()                                 */

#if PLATFORM_WIN32 && defined _MSC_VER
#include "libex_win32_.h"
#include <shlwapi.h>
#include <tchar.h>  /* on Windows */
#include <windows.h>
#pragma comment (lib, "advapi32.lib")                         /* windows.h */
/*      CopySid()                   */
/*      DeregisterEventSource()     */
/*      GetLengthSid()              */
/*      GetTokenInformation()       */
/*      OpenProcessToken()          */
/*      OpenThreadToken()           */
/*      RegCloseKey()               */
/*      RegCreateKeyEx()            */
/*      RegisterEventSource()       */
/*      RegSetValueEx()             */
/*      ReportEvent()               */
#pragma comment (lib, "shlwapi.lib")                          /* shlwapi.h */
/*      PathAppend()                */
/*      PathFileExists()            */
/*      PathFindOnPath()            */
/*      PathRemoveFileSpec()        */
/*      PathStripPath()             */
#pragma comment (lib, "user32.lib")                           /* windows.h */
/*      MessageBox()                */
#pragma comment (lib, "kernel32.lib")                         /* windows.h */
/*      CloseHandle()               */
/*      DebugBreak()                */
/*      GetCurrentProcess()         */
/*      GetCurrentThread()          */
/*      GetModuleFileName()         */
/*      GetProcessHeap()            */
/*      GetTickCount()              */
/*      HeapAlloc()                 */
/*      HeapFree()                  */
/*      IsDebuggerPresent()         */
/*      OutputDebugString()         */
#endif

#include "libex_.h"
#include "libex_call_.h"
#include "libex_const_.h"
#include "libex_macro_.h"
#include "libex_stringc_.h"
#include "libex_type_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#if defined __clang__
#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#endif
#if defined __GNUC__ && !defined __MINGW32__
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#endif
#if defined _MSC_VER
#pragma warning (disable:4710)  /* W:L4 function not inlined                  */
#endif

#define _ASSERT( CONDITION_ )                                          \
    if (!(CONDITION_))                                                 \
    {   _debug_dump(_T(#CONDITION_) _T(" failed in ") FN_NAME); }  /*#*/


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


/* -------------------------------------------------------------------------- */
/* Internal Functions:                                                        */


static void  _debug_dump( chars_t  text_ ) {                               /*F*/
    GO                                                            (UID(FD92B8));
#if PLATFORM_LINUX
    PRINTF_T(text_, NULL);
#endif

#if PLATFORM_WIN32
#if defined _MSC_VER
    /* dump text to output window */
    OutputDebugString_win(text_);
#else                                                             /* _MSC_VER */
    PRINTF_T(text_);
#endif                                                           /* !_MSC_VER */
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* _debug_dump */


#if PLATFORM_WIN32
/* note: the contents of buffer_out_ are always changed */
static bool  _set_event_msg_dll(                                           /*F*/
    char_t*       buffer_out_,                                             /*-*/
    const size_t  size_in_bytes_ ) {                                       /*-*/
    GO                                                            (UID(F1370B));
    bool  ret = false;

#if PLATFORM_LINUX
    UNUSED(buffer_out_);
    UNUSED(size_in_bytes_);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    chars_t  DLL_NAME = _T("\\eventmsg.dll");

    /* erase the buffer */
    MEMSET(buffer_out_, 0x00, size_in_bytes_);

    /* search for the dll in the same folder as the running process */
    GetModuleFileName_win(
        NULL,                              /* NULL = current process   */
        buffer_out_,                       /* receiving buffer         */
        CAST(DWORD_win, size_in_bytes_));  /* size of buffer in TCHARs */

    PathRemoveFileSpec_win(buffer_out_);                         /*shlwapi.lib*/
    PathAppend_win(buffer_out_, DLL_NAME);                       /*shlwapi.lib*/

    if (PathFileExists_win(buffer_out_) == TRUE_win) {           /*shlwapi.lib*/
        RETURN(true);
    }

    PathStripPath_win(buffer_out_);                              /*shlwapi.lib*/

    ret = PathFindOnPath_win(buffer_out_, NULL) ? true : false;
    /*shlwapi.lib*/
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* _set_event_msg_dll */
#endif                                                      /* PLATFORM_WIN32 */


static void  _log(                                                         /*F*/
    const err_msg_type_enum  type_,                                        /*-*/
    chars_t                  detail_,                                      /*-*/
    chars_t                  source_func_,                                 /*-*/
    const uint32_t           src_uid_,                                     /*-*/
    chars_t                  notes_ ) {                                    /*-*/
    GO                                                            (UID(F0C502));

#if PLATFORM_LINUX
    chars_t  type = _T("(UNKNOWN)");

    switch (type_) {
            CASE(MSG_SUCCESS, type = _T("SUCCESS:"));
            CASE(MSG_INFO,    type = _T("INFORMATION:"));
            CASE(MSG_WARN,    type = _T("WARNING:"));
            CASE(MSG_ERROR,   type = _T("ERROR:"));
        default:
            type = _T("MESSAGE:");
    }

    {
        const size_t  size = 128
                             + STRLEN_T(detail_)
                             + STRLEN_T(source_func_)
                             + STRLEN_T(notes_);

        new_chars_t  msg = mallocT(size);

        SNPRINTF_T(msg, size,
                   _T("%s \r\n Detail: %s ") _T("\r\n")
                   _T(" Source: %s() ")      _T("\r\n")
                   _T(" id: UID(%X) ")       _T("\r\n")
                   _T(" Notes: %s"),
                   type, detail_, source_func_, CAST(uint32_t, src_uid_),
                   notes_);

        _debug_dump(msg);

        freeT(&msg);
    }

#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    static chars_t  FORMAT =
        _T("%s\r\n%s%s\r\n%s\r\n\r\n") _T("UID(%08XU) #%u");

    static size_t  serial_no = 0;

    chars_t  detail      = STRLEN_T(detail_)      > 0 ? detail_      : BLANK;
    chars_t  source_name = STRLEN_T(source_func_) > 0 ? source_func_ : BLANK;
    chars_t  note_label  = STRLEN_T(notes_)       > 0 ? _T("\r\nnote: ")
                           : BLANK;

    chars_t  notes = STRLEN_T(notes_) == 0 ? BLANK : notes_;

    /* estimate length of temporary buffer */
    const size_t  len = 256 + STRLEN_T(detail) + STRLEN_T(source_name)
                        + STRLEN_T(notes);

    /* create a temporary buffer */
    char_t*  buf = CAST(char_t*, MALLOC((len + 1) * sizeof(char_t)));
    MEMSET(buf, 0x00, len);

    serial_no++;

    /* TODO: use function */
#if defined _MSC_VER && _MSC_VER >= 1400  /* VS2005 */

#pragma warning (push)
#pragma warning (disable:4774)  /* W:L4 format string is not a string literal */
    _STPRINTF_S(buf, len, FORMAT, detail, note_label, notes, source_name,
                src_uid_, serial_no);
#pragma warning (pop)

#elif defined UNICODE || defined _UNICODE
    SWPRINTF(buf, FORMAT, detail, note_label, notes, source_name, src_uid_,
             serial_no);

#else
    SPRINTF(buf, FORMAT, detail, note_label, notes, source_name, src_uid_,
            serial_no);
#endif

    /* output the message to the console */
    PRINTF_T(_T("\r\n"));
    switch (type_) {
            CASE(MSG_SUCCESS, PRINTF_T(_T("Success")));
            CASE(MSG_INFO,    PRINTF_T(_T("Info")));
            CASE(MSG_WARN,    PRINTF_T(_T("Warning")));
            CASE(MSG_ERROR,   PRINTF_T(_T("Error")));
    }
    PRINTF_T(_T(": "));

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable:4774)  /* W:L4 format string is not a string literal */
#endif

    PRINTF_T(buf);

#if defined _MSC_VER
#pragma warning (pop)
#endif

    PRINTF_T(_T("\r\n"));

    log_to_event_log(buf, type_, NULL, NULL);

#if (defined DEBUG || defined _DEBUG)
    log_to_file(buf);
#endif

    if (IsDebuggerPresent_win()) {
        _debug_dump(_T("------->"));
        _debug_dump(buf);

        /* break execution on this statement                     */
        /* (use call stack to see what code invoked log_error()) */
        if (type_ == MSG_WARN || type_ == MSG_ERROR) {
            UINT_win  type = (type_ == MSG_WARN ? MB_ICONWARNING_win
                              : MB_ICONERROR_win);
            MessageBox_win(NULL, buf, _T("Warning/Error."), type);
#if defined _MSC_VER

            if (IsDebuggerPresent_win()) {
                __debugbreak();
            }

#endif                                                            /* _MSC_VER */
        }
    }
    FREE(buf);
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* _log */


/* -------------------------------------------------------------------------- */
/* Functions:                                                                 */


PUBLIC void  log_error(                                                    /*F*/
    chars_t         detail_,                                               /*-*/
    chars_t         source_func_,                                          /*-*/
    const uint32_t  src_uid_,                                              /*-*/
    chars_t         notes_ ) {                                             /*-*/
    GO                                                            (UID(FB4BEB));
    _log(MSG_ERROR, detail_, source_func_, src_uid_, notes_);
    RETURN(NIL);
} /* log_error */


PUBLIC size_t  err_count( void ) {                                         /*F*/
    GO                                                            (UID(F192E4));
    static const size_t  ret = 0;  /* TODO: this does nothing */
    RETURN(ret);
} /* err_count */


PUBLIC void  log_info(                                                     /*F*/
    chars_t         detail_,                                               /*-*/
    chars_t         source_func_,                                          /*-*/
    const uint32_t  src_uid_,                                              /*-*/
    chars_t         notes_ ) {                                             /*-*/
    GO                                                            (UID(FC6EB2));
    _log(MSG_INFO, detail_, source_func_, src_uid_, notes_);
    RETURN(NIL);
} /* info */


PUBLIC bool  log_to_event_log(                                             /*F*/
    chars_t                  message_,                                     /*-*/
    const err_msg_type_enum  type_,                                        /*-*/
    chars_t                  app_name_,                                    /*-*/
    chars_t                  msg_dll_ ) {                                  /*-*/
    GO                                                            (UID(FAE8B5));
#if PLATFORM_LINUX
    UNUSED(message_);
    UNUSED(type_);
    UNUSED(app_name_);
    UNUSED(msg_dll_);
    RETURN(false);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    /* static variables */
    static HANDLE_win  log        = NULL;
    static bool        registered = false;
    static char_t      app_name[_MAX_PATH_win];
    static char_t      dll_name[_MAX_PATH_win];

    char_t     key_name[_MAX_PATH_win * 2];
    HKEY       key     = NULL;
    DWORD_win  types   = 0;
    chars_t*   strings = NULL;
    BOOL_win   result  = FALSE_win;
    WORD_win   wtype   = 0;
    PSID_win   sid     = 0;

    if (registered && message_ == NULL) {
        if (log) {
            DeregisterEventSource_win(log);
        }
        log = NULL;
        RETURN(true);
    }

    if (!registered || app_name_ != NULL || msg_dll_ != NULL) {
        if (log) {
            DeregisterEventSource_win(log);
            log = NULL;
        }

        MEMSET(app_name, 0x00, _MAX_PATH_win);

        if (app_name_) {
            _ASSERT(PathAppend_win(app_name, app_name_));  /*shlwapi.lib*/
        } else {
            _ASSERT(GetModuleFileName_win(NULL, app_name, _MAX_PATH_win));
            PathStripPath_win(app_name);  /*shlwapi.lib*/
        }

        MEMSET(dll_name, 0x00, _MAX_PATH_win);

        if (msg_dll_) {
            _ASSERT(PathAppend_win(dll_name, msg_dll_));  /*shlwapi.lib*/
        } else {
            _set_event_msg_dll(dll_name, _MAX_PATH_win);
        }

        MEMSET(key_name, 0x00, _MAX_PATH_win * 2 * sizeof(char_t));
        _ASSERT(PathAppend_win(key_name,   /*shlwapi.lib*/
                               _T("SYSTEM\\CurrentControlSet")
                               _T("\\Services\\Eventlog\\Application\\")));
        _ASSERT(PathAppend_win(key_name, app_name));  /*shlwapi.lib*/

        /* create the event log registry key and values, */
        /* for the current application                   */
        if (ERROR_SUCCESS_win != RegCreateKeyEx_win(
                HKEY_LOCAL_MACHINE_win, key_name, 0, NULL,
                REG_OPTION_NON_VOLATILE_win, KEY_ALL_ACCESS_win,
                NULL, &key, NULL)) {

            _debug_dump(
                _T("RegCreateKeyEx() failed in log_to_event_log()"));
            registered = false;
            RETURN(false);
        }

        if (ERROR_SUCCESS_win != RegSetValueEx_win(
                key, _T("EventMessageFile"), 0, REG_SZ_win,
                CAST(const BYTE_win*, dll_name),
                CAST(DWORD_win, (STRLEN_T(dll_name) + 1) * sizeof(char_t))))
            /* C4267 conversion from 'size_t' to 'DWORD' possible loss... */
        {
            _debug_dump(_T("RegSetValueEx() failed in log_to_event_log()"));
            registered = false;
            RETURN(false);
        }

        /* DWORD_win */ types = EVENTLOG_SUCCESS_win          |
                                EVENTLOG_INFORMATION_TYPE_win |
                                EVENTLOG_WARNING_TYPE_win     |
                                EVENTLOG_ERROR_TYPE_win;

        if (ERROR_SUCCESS_win != RegSetValueEx_win(
                key, _T("TypesSupported"), 0, REG_DWORD_win,
                CAST(const BYTE_win*, &types),
                sizeof(DWORD_win))) {

            _debug_dump(_T("RegSetValueEx() failed in log_to_event_log()"));
            registered = false;
            RETURN(false);
        }

        if (RegCloseKey_win(key) != ERROR_SUCCESS_win) {
            _debug_dump(_T("RegCloseKey failed in log_to_event_log()"));
            registered = false;
            RETURN(false);
        }

        log = RegisterEventSource_win(NULL, app_name);
    }

    /* get current user's security identifier (SID) */
    sid = NULL;
    {
        HANDLE_win        token = NULL;
        const HANDLE_win  heap  = GetProcessHeap_win();
        _ASSERT(heap != NULL);

        /* get access token for the calling thread or process */
        /* HANDLE_win */ token = NULL;

        if (OpenThreadToken_win(GetCurrentThread_win(),
                                TOKEN_QUERY_win, true, &token) ||
            OpenProcessToken_win(GetCurrentProcess_win(),
                                 TOKEN_QUERY_win, &token)) {

            /* get length of user information */
            DWORD_win  token_size = 0;
            GetTokenInformation_win(
                token, TokenUser_win, NULL, 0, &token_size);

            if (token_size > 0) {
                /* allocate user information buffer */
                PTOKEN_USER_win user = NULL;
                user = CAST(PTOKEN_USER_win,
                            HeapAlloc_win(heap, 0, token_size));
                _ASSERT(user != NULL);

                if (user) {
                    /* read user information from token to buffer */
                    BOOL_win  get_token_info =
                        GetTokenInformation_win(
                            token, TokenUser_win, user,
                            token_size, &token_size);
                    _ASSERT(get_token_info);

                    if (get_token_info) {
                        DWORD_win  sid_byte_len =
                            GetLengthSid_win(user->User.Sid);

                        /* allocate 'SID buffer'              */
                        /* (released before function returns) */
                        sid = CAST(PSID_win, HeapAlloc_win(
                                       heap, 0, sid_byte_len));
                        _ASSERT(sid != NULL);

                        if (sid) {  /* copy security identifier to buffer */
                            result =
                                CopySid_win(sid_byte_len, sid, user->User.Sid);
                            _ASSERT(result);
                        }
                    }

                    _ASSERT(HeapFree_win(heap, 0, user));
                }
            }

            _ASSERT(CloseHandle_win(token));
        }
    }

    /* translate message type enum value to event log type */
    wtype = 0;
    switch (type_) {
            CASE(MSG_SUCCESS, wtype = EVENTLOG_SUCCESS_win);
            CASE(MSG_INFO,    wtype = EVENTLOG_INFORMATION_TYPE_win);
            CASE(MSG_WARN,    wtype = EVENTLOG_WARNING_TYPE_win);
            CASE(MSG_ERROR,   wtype = EVENTLOG_ERROR_TYPE_win);
        default:
            wtype = EVENTLOG_ERROR_TYPE_win;
    }

    strings = &message_;
    result  = ReportEvent_win(
                  log,          /* handle to event log         */
                  wtype,        /* event type                  */
                  0,            /* event category              */
                  0x20000001L,  /* event ID (GENERIC_MESSAGE)  */
                  sid,          /* optnl. user sec. identifier */
                  1,            /* number of strings to merge  */
                  0,            /* size of binary data (bytes) */
                  strings,      /* array of strings to merge   */
                  NULL);        /* binary data buffer          */

    /* release 'SID buffer' */
    if (sid) {
        const HANDLE_win  heap = GetProcessHeap_win();
        _ASSERT(heap != NULL);
        _ASSERT(HeapFree_win(heap, 0, sid));
    }

    _ASSERT(result);
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(true);
} /* log_to_event_log */


PUBLIC chars_t  log_to_file( chars_t  text_ ) {                            /*F*/
    GO                                                            (UID(FADFF4));

#if PLATFORM_LINUX
    PRINTF_T(text_, NULL);
    RETURN(BLANK);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    FILE*  file = NULL;

    /* create log file name */
    static char_t  ret[_MAX_PATH_win + 1];
    MEMSET(ret, 0x00, _MAX_PATH_win + 1);
    GetModuleFileName_win(NULL, ret, _MAX_PATH_win + 1);
    {
        const int  name_len = STRLEN_T(ret);
        ret[name_len - 3] = 'l';
        ret[name_len - 2] = 'o';
        ret[name_len - 1] = 'g';
    }

#if defined _MSC_VER
#pragma warning (disable:4996)  /* W:L3 'function': may be unsafe/deprecated  */
#endif

    {
        /* output text to log file: */
        const DWORD_win  time = GetTickCount_win();

        while (file == NULL && (GetTickCount_win() - time) < 2000) {
#if defined UNICODE || defined _UNICODE
            file = WFOPEN(ret, L"a+");
#else                                                  /* UNICODE || _UNICODE */
            file = FOPEN(ret, "a+");
#endif                                               /* !UNICODE && !_UNICODE */
        }
    }

    if (file != NULL) {
        FPRINTF_T(file,
                  _T("-------------------------------------------")
                  _T("\r\n") _T("%s") _T("\r\n\r\n"),
                  text_);
        FCLOSE(file);
    } else if (IsDebuggerPresent_win()) {
        DebugBreak_win();
    }
    RETURN(ret);  /* return filename */
#endif                                                      /* PLATFORM_WIN32 */
} /* log_to_file */


PUBLIC void  log_warn(                                                     /*F*/
    chars_t         detail_,                                               /*-*/
    chars_t         source_func_,                                          /*-*/
    const uint32_t  src_uid_,                                              /*-*/
    chars_t         notes_ ) {                                             /*-*/
    GO                                                            (UID(F72F6B));
    _log(MSG_WARN, detail_, source_func_, src_uid_, notes_);
    RETURN(NIL);
} /* log_warn */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
