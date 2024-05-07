/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_mutex.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_mutex_.h"
#if defined INCLUDED_LIBEX_MUTEX_H

#include "libex_config_.h"

#include "libex_call_.h"
#include "libex_debug_.h"
#include "libex_error_.h"
#include "libex_macro_.h"
#include "libex_.h"
#include "libex_type_.h"

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


PUBLIC Mutex  Mutex_init( chars_t  mutex_name_ ) {                         /*C*/
    GO                                                            (UID(FE89A9));
    Mutex  ret = { NULL };

#if PLATFORM_LINUX
    UNUSED(mutex_name_);
    IMPLEMENT_LINUX();  /* TODO: implement Mutex_init() on Linux */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    ret.ob = CreateMutex_win(NULL, TRUE_win, mutex_name_);

    if (GetLastError_win() == ERROR_ALREADY_EXISTS_win) {
        if (ret.ob && !CloseHandle_win(ret.ob)) {
            OS_WARN(_T("CloseHandle()"), UID(E8B844));
        }
        ret.ob = NULL;
    }

#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* Mutex_init */


PUBLIC Mutex  Mutex_initCopy( const Mutex  copy_from_ ) {                  /*C*/
    GO                                                            (UID(F92F70));
    Mutex  ret = { NULL };
    ret.ob  = copy_from_.ob;
    RETURN(ret);
} /* Mutex_initCopy */


/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */


PUBLIC void  Mutex_free( Mutex  object_ ) {                                /*D*/
    GO                                                            (UID(D8D724));
#if PLATFORM_LINUX
    UNUSED(object_);
    IMPLEMENT_LINUX();  /* TODO: implement Mutex_free() on Linux */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32

    if (object_.ob && !CloseHandle_win(object_.ob)) {
        OS_WARN(_T("CloseHandle()"), UID(E0ED97));
    }

#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* Mutex_free */


/* -------------------------------------------------------------------------- */
/* Properties:                                                                */


bool  Mutex_isCreated( Mutex  object_ ) {                                  /*P*/
    GO                                                            (UID(FD2AA8));
    const bool  ret = C_BOOL(object_.ob != NULL);
    RETURN(ret);
} /* Mutex_isCreated */


/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */


PUBLIC void  Mutex_setCopy(                                                /*M*/
    Mutex        object_,                                                  /*-*/
    const Mutex  copy_from_ ) {                                            /*-*/
    GO                                                            (UID(F58725));
    if (object_.ob != copy_from_.ob) {
        Mutex_free(object_);
        object_.ob = copy_from_.ob;
    }
    RETURN(NIL);
} /* Mutex_setCopy */


/* -------------------------------------------------------------------------- */
/* Functions:                                                                 */

bool  mutex_exists( chars_t  mutex_name_ ) {                               /*F*/
    GO                                                            (UID(F2996F));
    bool  ret = false;

#if PLATFORM_LINUX
    UNUSED(mutex_name_);
    IMPLEMENT_LINUX();  /* TODO: implement mutex_exists() */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    const HANDLE_win  mutex = OpenMutex_win(
                                  READ_CONTROL_win, TRUE_win, mutex_name_);

    ret = (mutex != NULL);

    if (mutex) {
        if (!CloseHandle_win(mutex)) {
            OS_WARN(_T("CloseHandle()"), UID(E6D9FD));
        }
    } else {
        if (GetLastError_win() != ERROR_FILE_NOT_FOUND_win) {
            OS_WARN(_T("OpenMutex()"), UID(EAD072));
        }
    }

#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* mutex_exists */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
