/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                          [libex_object_wrapper.inc.c] */
/* -------------------------------------------------------------------------- */

#if defined _BASE_OBJ_WRAP_INC

/* This is a 'template' implementation that provides functions for            */
/* allocating, deallocating, and referencing objects.                         */
/*                                                                            */
/* This file should never be added to a project and compiled directly,        */
/* but only included from class implementation files.                         */
/*                                                                            */
/* Object instances in this library are referenced by object handles outside  */
/* of the class implementation. Within a class implementation, the handle is  */
/* converted to a pointer to a structure which holds the object's data.       */
/*                                                                            */
/* _object_alloc(): Creating an object.                                       */
/* The constructor function of a class should call _object_alloc() to         */
/* create an empty (all bytes set to zero) object data structure on the heap. */
/* The constructor then initializes the data members as required,             */
/* after which it returns a handle, as follows below.                         */
/*                                                                            */
/* _object_wrap(): Returning a new object instance.                           */
/* After the constructor creates an object its handle needs to be returned.   */
/* To do this use _object_wrap() which converts a pointer to an object data   */
/* structure to an object handle, which is then returned.                     */
/*                                                                            */
/* _object(): Handling an object handle.                                      */
/* Methods of the class receive a handle (e.g. Widget). To get a pointer      */
/* to the object's structure, use _object(). This returns a modifiable        */
/* pointer to the object's data structure (e.g. _widget_t*).                  */
/*                                                                            */
/* _object_const(): Read-only access.                                         */
/* There is also a non-modifiable (const) pointer which is obtained           */
/* by calling _object_const(). This is useful for object properties           */
/* and methods that don't change the object's state (ie. leave the data       */
/* structure unchanged.)                                                      */
/*                                                                            */
/* _object_free(): Destroying an object instance.                             */
/* When an object instance needs to be destroyed, its destructor function     */
/* should call _object_free() after all other cleanup to release this struct. */
/*                                                                            */
/* To include this file, copy the block below into your class, change         */
/* Widget and _widget_t to the types for your class, and change               */
/* the UID() values to any unique IDs. (The IDs are used by the               */
/* call tracer and for error handling. If you don't use unique UID's          */
/* there will be no problem, but some confusion when profiling code           */
/* or an error occurs.)                                                       */
/*                                                                            */
/* This should obviously be placed before you try using any of these          */
/* functions, preferably near the beginning of your source file.              */

#if 000 /* sample usage code */
#define _BASE_OBJ_WRAP_INC
#define _OBJ_HANDLE_TYPE   Widget
#define _OBJ_INNER_TYPE    _widget_t
#define _OBJ_ALLOC_FN_UID  UID(F0BB11)
#define _OBJ_FREE_FN_UID   UID(F8A4D4)
#define _OBJ_CONST_FN_UID  UID(F79BDB)
#define _OBJ_FN_UID        UID(F74788)
#define _OBJ_WRAP_FN_UID   UID(F7F6BB)
#include "libex_object_wrapper.inc.c"
#endif                                                                 /* 000 */

#if defined __cplusplus_cli
#pragma unmanaged
#endif


/* -------------------------------------------------------------------------- */


static _OBJ_INNER_TYPE*  _object_alloc( void ) {                           /*F*/
    GO                                                      (_OBJ_ALLOC_FN_UID);
    const size_t      bsize = sizeof(_OBJ_INNER_TYPE);
    _OBJ_INNER_TYPE*  ret   = CAST(_OBJ_INNER_TYPE*, MALLOC(bsize));
    MEMSET(ret, 0x00, bsize);
    RETURN(ret);
} /* _object_alloc */


static void  _object_free( _OBJ_HANDLE_TYPE*  object_ ) {                  /*F*/
    GO                                                       (_OBJ_FREE_FN_UID);
    if (object_ == NULL || object_->ob == NULL) {
        RETURN(NIL);
    }

    /* check that object has been previously initialized */
    if (CAST(unsigned long, object_->ob) == 0xCCCCCCCCU ||
        CAST(unsigned long, object_->ob) == 0xFEEEFEEEU) {
        WARN(_T("Uninitialized object!"), UID(E31F12));
        RETURN(NIL);
    } else {
        const size_t  bytes_size = sizeof(_OBJ_INNER_TYPE);
        uint8_t*      old_mem    = CAST(uint8_t*, object_->ob) - bytes_size;

        MEMSET(old_mem, 0x00, bytes_size);
        FREE(old_mem);
        object_->ob = NULL;
    }
    RETURN(NIL);
} /* _object_free */


static _OBJ_HANDLE_TYPE  _object_wrap(  _OBJ_INNER_TYPE*  object_ ) {      /*F*/
    GO                                                       (_OBJ_WRAP_FN_UID);
    _OBJ_HANDLE_TYPE  ret        = { NULL };
    const size_t      bytes_size = sizeof(_OBJ_INNER_TYPE);

    ret.ob = CAST(uint8_t*, object_) + bytes_size;

    RETURN(ret);
} /* _object_wrap */


static const _OBJ_INNER_TYPE*  _object_const(                              /*F*/
    const _OBJ_HANDLE_TYPE*  object_,                                      /*-*/
    const uint32_t           uid_ ) {                                      /*-*/
    GO                                                      (_OBJ_CONST_FN_UID);
    _OBJ_INNER_TYPE*  ret = NULL;

    if (object_ != NULL && object_->ob != NULL) {
        /* check that object has been previously initialized */
        if (CAST(unsigned long, object_->ob) == 0xCCCCCCCCU ||
            CAST(unsigned long, object_->ob) == 0xFEEEFEEEU) {
            WARN(_T("Uninitialized object!"), uid_);
        } else {
            const size_t  bytes_size = sizeof(_OBJ_INNER_TYPE);
            ret = CAST(_OBJ_INNER_TYPE*,
                       CAST(uint8_t*, object_->ob) - bytes_size);
        }
    }
    RETURN(ret);
} /* _object_const */


static _OBJ_INNER_TYPE*  _object(                                          /*F*/
    const _OBJ_HANDLE_TYPE*  object_,                                      /*-*/
    const uint32_t           uid_ ) {                                      /*-*/
    GO                                                            (_OBJ_FN_UID);
    _OBJ_INNER_TYPE*  ret =
        CAST(_OBJ_INNER_TYPE*, _object_const(object_, uid_));
    RETURN(ret);
} /* _object */


#endif                                                                   /*eof*/
