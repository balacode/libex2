/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_array.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_array_.h"
#if defined INCLUDED_LIBEX_ARRAY_H

#include <string.h>  /* for memset() */

#include "libex_.h"
#include "libex_call_.h"
#include "libex_debug_.h"
#include "libex_error_.h"
#include "libex_macro_.h"
#include "libex_stringc_.h"
#include "libex_type_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#if defined _MSC_VER
#pragma warning (disable:4710)  /* W:L4 function not inlined */
#endif


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


/* -------------------------------------------------------------------------- */
/* Array Structures:                                                          */


typedef struct  _array_t {
    size_t  item_size;                                            /* _array_t */
    /* Number of bytes used by each */
    /* item in the array.           */

    size_t  cap;                                                  /* _array_t */
    /* Allocated number of items,   */
    /* some of which may be unused. */
    /* (always _cap >= me->count)   */

    size_t  count;                                                /* _array_t */
    /* Actual number of items  */
    /* contained by the array. */

    size_t  grow_by;                                              /* _array_t */
    /* Number of items by which the array is  */
    /* to be grown when re-allocating memory. */

    uint8_t*  items;                                              /* _array_t */
    /* Pointer to allocated memory    */
    /* containing a sequence of items. */
}
_array_t;


/* -------------------------------------------------------------------------- */
/* Functions: Private                                                         */


#define _BASE_OBJ_WRAP_INC
#define _OBJ_HANDLE_TYPE   array_t
#define _OBJ_INNER_TYPE    _array_t
#define _OBJ_ALLOC_FN_UID  UID(FFF665)
#define _OBJ_FREE_FN_UID   UID(F0E495)
#define _OBJ_CONST_FN_UID  UID(F888CB)
#define _OBJ_FN_UID        UID(F0BA56)
#define _OBJ_WRAP_FN_UID   UID(F695DF)
#include "libex_object_wrapper.inc.c"


/* -------------------------------------------------------------------------- */
/* Constructor:                                                               */


PUBLIC  new_array_t  Array_init(                                           /*C*/
    const size_t  item_size_in_bytes_,                                     /*-*/
    const size_t  capacity_,                                               /*-*/
    const size_t  grow_by_ ) {                                             /*-*/
    GO                                                            (UID(F5DDCD));
    new_array_t  ret = { NULL };

    /* validate arguments */
    if (item_size_in_bytes_ < 1) {
        ERR(_T("item_size_in_bytes_ < 1"), UID(ED4791));

    } else if (capacity_ < 1) {
        ERR(_T("capacity_ < 1"), UID(E53754));
    } else {
        _array_t*  new_ob = _object_alloc();
        new_ob->item_size  = item_size_in_bytes_;
        new_ob->cap        = capacity_;
        new_ob->count      = 0;
        new_ob->grow_by    = grow_by_;
        new_ob->items      = NULL;

        {
            /* allocate initial space for key and items data */
            const size_t  item_size  = sizeof(char_t*) + item_size_in_bytes_;
            const size_t  data_bytes = capacity_ * item_size;
            if (data_bytes > 0) {
                new_ob->items = MALLOC(data_bytes);
                MEMSET(new_ob->items, 0x00, data_bytes);
            }
        }
        ret = _object_wrap(new_ob);
    }
    RETURN(ret);
} /* Array_init */


/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */


PUBLIC void  Array_free( array_t*  object_ ) {                             /*M*/
    GO                                                            (UID(F7FB85));
    if (object_ != NULL && object_->ob != NULL) {
        Array_removeItems(object_);
    }

    _object_free(object_);

    RETURN(NIL);
} /* Array_free */


/* -------------------------------------------------------------------------- */
/* Methods: Informative                                                       */


PUBLIC size_t  Array_count( const array_t  object_ ) {                     /*M*/
    GO                                                            (UID(F63C14));
    const _array_t* const  me = _object_const(&object_, UID(E3885D));
    const size_t  ret = me->count;
    RETURN(ret);
} /* Array_count */


PUBLIC size_t  Array_getKeyIndex(                                          /*M*/
    const array_t  object_,                                                /*-*/
    chars_t        key_ ) {                                                /*-*/
    GO                                                            (UID(F24108));
    const _array_t* const  me = _object_const(&object_, UID(EA2944));

    const size_t  count     = Array_count(object_);
    const size_t  item_size = sizeof(char_t*) /*key*/ + me->item_size;
    chars_t       key       = CAST(chars_t, me->items);
    size_t        i         = 0;

    for (i = 0; i < count; i++) {
        if (STRCMP_T(key_, key) == 0) {
            RETURN(i);
        }
        key = CAST(chars_t, CAST(uint8_t*, key) + item_size);
    }
    RETURN(SIZE_MAX);
} /* Array_getKeyIndex */


PUBLIC bool  Array_keyExists(                                              /*M*/
    const array_t  object_,                                                /*-*/
    chars_t        key_ ) {                                                /*-*/
    GO                                                            (UID(F43C2C));
    const size_t  index = Array_getKeyIndex(object_, key_);
    const bool    ret   = (index != SIZE_MAX);
    RETURN(ret);
} /* Array_keyExists */


/* -------------------------------------------------------------------------- */
/* Methods: Manipulative                                                      */


PUBLIC void  Array_addItem(                                                /*M*/
    array_t*      object_,                                                 /*-*/
    const void*   item_data_,                                              /*-*/
    const size_t  item_size_in_bytes_,                                     /*-*/
    chars_t       key_ ) {                                                 /*-*/
    GO                                                            (UID(F4E2D4));
    _array_t* const  me = _object(object_, UID(EB8805));

    const size_t  item_size = sizeof(char_t*) /*key*/ + me->item_size;

    UNUSED(key_);

    if (item_size_in_bytes_ != me->item_size) {
        ERR(_T("item_size_in_bytes_ != me->item_size"), UID(E8D2A9));
        RETURN(NIL);
    }

    /* ensure enough capacity for adding an item (re-allocate data if needed) */
    if ((me->count + 1) > me->cap || !me->items) {

        const size_t  old_cap = me->cap;  /* calculate new capacity */
        if (me->grow_by < 1) {
            me->grow_by = GREATER(10, me->cap / 5);
        }
        me->cap += me->grow_by;

        me->items = REALLOC(me->items, me->cap * item_size);

        MEMSET(me->items + (old_cap * item_size), 0x00,  /* wipe old mem */
               (me->cap - old_cap)  * item_size);
    }

    /* add item's data to array. */
    me->count++;
    {
        uint8_t*  item = me->items + (me->count - 1) * item_size;

        {
            /* store item's key: */
            const size_t  key_len = STRLEN_T(key_);
            new_chars_t*  key     = CAST(new_chars_t*, item);

            if (key_len == 0) {
                *key = NULL;
            } else {
                *key = MALLOC((key_len + 1) * sizeof(char_t));
                if (*key == NULL) {
                    WARN(_T("MALLOC() failed."), UID(E4CDC6));
                }
                STRCPY_S_T(*key, key_len + 1, key_);
            }
            item += sizeof(chars_t);
        }

        /* store item's data */
        if (item_data_ == NULL) {
            MEMSET(item, 0x00, me->item_size);
        } else {
            MEMCPY(item, item_data_, me->item_size);
        }
    }
    RETURN(NIL);
} /* Array_addItem */


PUBLIC uint8_t*  Array_getItemAt(                                          /*M*/
    array_t*      object_,                                                 /*-*/
    const size_t  index_ ) {                                               /*-*/
    GO                                                            (UID(FA47DF));
    _array_t* const  me = _object(object_, UID(E832F3));

    uint8_t*  ret = NULL;

    if (me->count == 0 || index_ > (me->count - 1)) {
        WARN(_T("index_ out of range."), UID(ECB76B));
    } else {
        const size_t  item_size = sizeof(char_t*) + me->item_size;
        ret = sizeof(char_t*) + (me->items + index_ * item_size);
    }
    RETURN(ret);
} /* Array_getItemAt */


PUBLIC uint8_t*  Array_getItemByKey(                                       /*M*/
    array_t*  object_,                                                     /*-*/
    chars_t   key_ ) {                                                     /*-*/
    GO                                                            (UID(FFD1C8));
    uint8_t*      ret   = NULL;
    const size_t  index = Array_getKeyIndex(*object_, key_);

    if (index == SIZE_MAX) {
        WARN(_T("key_ not found."), UID(E575CB));
    } else {
        ret = Array_getItemAt(object_, index);
    }
    RETURN(ret);
} /* Array_getItemByKey */


PUBLIC uint8_t*  Array_getLastItem( array_t*  object_ ) {                  /*M*/
    GO                                                            (UID(F82915));
    _array_t* const  me = _object(object_, UID(ECCF7C));
    uint8_t*  ret = NULL;

    if (me->count > 0) {
        const size_t  item_size = sizeof(char_t*) + me->item_size;
        ret = sizeof(char_t*) + (me->items + (me->count - 1) * item_size);
    }
    RETURN(ret);
} /* Array_getLastItem */


PUBLIC void  Array_removeAt(                                               /*M*/
    array_t*      object_,                                                 /*-*/
    const size_t  index_ ) {                                               /*-*/
    GO                                                            (UID(FFEF1F));
    _array_t* const  me = _object(object_, UID(E57813));

    if (me->count == 0 || index_ > (me->count - 1)) {
        WARN(_T("index_ out of range."), UID(E5393C));
    } else {
        const size_t    item_size  = sizeof(char_t*) /*key*/ + me->item_size;
        const size_t    bytes_size = (me->count - 1 - index_) * item_size;
        const uint8_t*  from       = me->items + index_ * item_size;
        uint8_t*        to         = me->items + (me->count - 1) * item_size;

        MEMMOVE(to, from, bytes_size);
        to = me->items + (me->count - 1) * item_size;
        MEMSET(to, 0x00, bytes_size);
        me->count--;
    }
    RETURN(NIL);
} /* Array_removeAt */


PUBLIC void  Array_removeItemByKey(                                        /*M*/
    array_t*  object_,                                                     /*-*/
    chars_t   key_ ) {                                                     /*-*/
    GO                                                            (UID(F7C025));
    const size_t  index = Array_getKeyIndex(*object_, key_);

    if (index == SIZE_MAX) {
        WARN(_T("key_ not found."), UID(ECF8F0));
    } else {
        Array_removeAt(object_, index);
    }
    RETURN(NIL);
} /* Array_removeItemByKey */


PUBLIC void  Array_removeItems( array_t*  object_ ) {                      /*M*/
    GO                                                            (UID(F37D92));
    _array_t* const  me = _object(object_, UID(EE3D6B));

    /* release all the key strings */
    if (me->count > 0) {
        const size_t  key_size = sizeof(char_t*) /*key*/ + me->item_size;
        size_t        i        = me->count;

        while (i--) {
            new_chars_t*  key = CAST(new_chars_t*, me->items);
            if (*key) {
                freeT(key);
            }
            key = CAST(new_chars_t*, CAST(uint8_t*, key) + key_size);
        }
    }

    /* release the array data and the array structure */
    if (me != NULL && me->items != NULL) {
        MEMSET(me->items, 0xFF, me->cap * me->item_size);
        FREE(me->items);
        me->items = NULL;
        me->cap   = 0;
        me->count = 0;
    }
    RETURN(NIL);
} /* Array_removeItems */


PUBLIC void  Array_removeLast( array_t*  object_ ) {                       /*M*/
    GO                                                            (UID(FDDD44));
    _array_t* const  me = _object(object_, UID(E257C8));

    if (me->count > 0) {
        Array_removeAt(object_, me->count - 1);
    }
    RETURN(NIL);
} /* Array_removeLast */


PUBLIC void  Array_resize(                                                 /*M*/
    array_t*      object_,                                                 /*-*/
    const size_t  new_count_ ) {                                           /*-*/
    GO                                                            (UID(F4C59E));
    _array_t* const  me = _object(object_, UID(E3BE36));

    if (new_count_ > me->count) {
        while (new_count_ > me->count) {
            Array_addItem(object_, NULL, me->item_size, NULL);
        }
    } else if (new_count_ < me->count) {
        while (new_count_ < me->count) {
            Array_removeLast(object_);
        }
    }
    RETURN(NIL);
} /* Array_resize */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
