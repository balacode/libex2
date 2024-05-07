/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_mutex.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_MUTEX_H
#define      INCLUDED_LIBEX_MUTEX_H

#include "libex.h"
#include "libex_stringc.h"

#if LX_PLATFORM_WIN32
#include "libex_win32.h"
#endif

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

#if LX_PLATFORM_LINUX
typedef struct  lx_Mutex {
    void*  ob;                                                    /* lx_Mutex */
}
lx_Mutex;
#endif                                                   /* LX_PLATFORM_LINUX */

#if LX_PLATFORM_WIN32
typedef struct  lx_Mutex {
    HANDLE_win  ob;                                               /* lx_Mutex */
}
lx_Mutex;
#endif                                                   /* LX_PLATFORM_WIN32 */

/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */

/* Default Constructor */
LX_PUBLIC lx_Mutex  lx_Mutex_init( lx_chars_t  mutex_name_ );              /*C*/

/* Copy Constructor */
LX_PUBLIC lx_Mutex  lx_Mutex_initCopy( const lx_Mutex  copy_from_ );       /*C*/

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

LX_PUBLIC void  lx_Mutex_free( lx_Mutex  object_ );                        /*D*/

/* -------------------------------------------------------------------------- */
/* Properties:                                                                */

LX_PUBLIC lx_bool  lx_Mutex_isCreated( lx_Mutex  object_ );                /*P*/

/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */

/* Assignment Operator */
LX_PUBLIC void  lx_Mutex_setCopy(                                          /*M*/
    lx_Mutex        object_,                                               /*-*/
    const lx_Mutex  copy_from_ );                                          /*-*/

/* -------------------------------------------------------------------------- */
/* Functions:                                                                 */

lx_bool  lx_mutex_exists( lx_chars_t  mutex_name_ );                       /*F*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
