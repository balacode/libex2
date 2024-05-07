/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                      [libex_mutex_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_MUTEX__H
#define      INCLUDED_LIBEX_MUTEX__H
#include "libex_mutex.h"

#define Mutex                           lx_Mutex

/* Constructors: */
#define Mutex_init                      lx_Mutex_init
#define Mutex_initCopy                  lx_Mutex_initCopy

/* Destructor: */
#define Mutex_free                      lx_Mutex_free

/* Properties: */
#define Mutex_isCreated                 lx_Mutex_isCreated

/* Methods: */
#define Mutex_setCopy                   lx_Mutex_setCopy

/* Functions: */
#define mutex_exists                    lx_mutex_exists

#endif                                                                   /*eof*/
