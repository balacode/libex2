/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                     [libex_console.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_console_.h"
#if defined INCLUDED_LIBEX_CONSOLE_H

#include "libex_config_.h"

#include <stdio.h>   /* for printf*() */
#include <string.h>  /* for memset()  */

#include "libex_.h"
#include "libex_call_.h"
#include "libex_libc_.h"
#include "libex_macro_.h"
#include "libex_string_class_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#if defined _MSC_VER
#pragma warning (disable:4710)  /* W:L4 function not inlined                  */
#endif


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


static int  _console_left_margin = 0;


/* -------------------------------------------------------------------------- */
/* Properties:                                                                */


PUBLIC void  Console_setLeftMargin( const int  margin_ ) {                 /*P*/
    GO                                                            (UID(F2C982));
    _console_left_margin = margin_;
    RETURN(NIL);
} /* Console_setLeftMargin */


PUBLIC int  Console_getLeftMargin( void ) {                                /*P*/
    GO                                                            (UID(FA1042));
    RETURN(_console_left_margin);
} /* Console_getLeftMargin */


/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */


PUBLIC int  Console_getKey( void ) {                                       /*M*/
    GO                                                            (UID(F182F7));
#if PLATFORM_LINUX
    const int  ret = 0;
    IMPLEMENT_LINUX();  /* TODO: implement Console_getKey() on Linux */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    const int  ret = _getch();
#endif

    RETURN(ret);
} /* Console_getKey */


PUBLIC void  Console_out( chars_t  text_ ) {                               /*M*/
    GO                                                            (UID(F8B289));
    static const int  MAX_MARGIN = 1024;

    if (_console_left_margin > MAX_MARGIN) {
        _console_left_margin = MAX_MARGIN;
    }

    if (_console_left_margin > 0) {
        str_t  text = S_chars(text_);
        str_t  gap  = S_repeat(_T(" "), _console_left_margin, MAX_MARGIN);

        insertInS(&gap, _T("\n"), 0, SIZE_MAX);
        replace3InS(&text, _T("\n"), gap.cs);
        PRINTF_T(_T("%s"), text.cs);
        freeS(&gap);
        freeS(&text);
    } else {
        PRINTF_T(_T("%s"), text_);
    }
    RETURN(NIL);
} /* Console_out */


PUBLIC void  Console_outA( const char*  text_ ) {                          /*M*/
    GO                                                            (UID(F8BC9C));
#if defined UNICODE || defined _UNICODE
    str_t  text = S_bchars(text_);
    Console_out(wcharsS(text));
    freeS(&text);
#else                                                  /* UNICODE || _UNICODE */
    Console_out(text_);
#endif                                               /* !UNICODE && !_UNICODE */

    RETURN(NIL);
} /* Console_outA */


PUBLIC void  Console_outW( const wchar_t*  text_ ) {                       /*M*/
    GO                                                            (UID(F4C9DF));
#if defined UNICODE || defined _UNICODE
    Console_out(text_);
#else                                                  /* UNICODE || _UNICODE */
    str_t  text = S_wchars(text_);
    Console_out(text.cs);
    freeS(&text);
#endif                                               /* !UNICODE && !_UNICODE */

    RETURN(NIL);
} /* Console_outW */


PUBLIC void  Console_outInt( const int  value_ ) {                         /*M*/
    GO                                                            (UID(FA6085));
    char_t  buf[32];
    CLEAR(buf);
    itot_fn(value_, buf, 32, 10);  /* convert integer to string */
    Console_out(buf);
    RETURN(NIL);
} /* Console_outInt */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
