/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_array.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_ARRAY_H
#define      INCLUDED_LIBEX_ARRAY_H

#include "libex.h"

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

typedef struct  lx_array_t {
    uint8_t*  ob;
}
lx_array_t, lx_new_array_t;

static lx_array_t  lx_null_array = { NULL };

/* -------------------------------------------------------------------------- */
/* Constructor:                                                               */

/* Constructor: Creates an array with the given pre-allocated capacity.       */
/* (See lx_Array_reserve() for an explanation of capacity_ and grow_by_.)     */
LX_PUBLIC  lx_new_array_t  lx_Array_init(                                  /*C*/
    const size_t  item_size_in_bytes_,                                     /*-*/
    const size_t  capacity_,                                               /*-*/
    const size_t  grow_by_ );                                              /*-*/

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

LX_PUBLIC void  lx_Array_free( lx_array_t*  object_ );                     /*M*/

/* -------------------------------------------------------------------------- */
/* Methods: Informative                                                       */

/* returns the number of items added to the array.                            */
/* (Not to be confused with the array's capacity.)                            */
LX_PUBLIC size_t  lx_Array_count( const lx_array_t  object_ );             /*M*/

LX_PUBLIC size_t  lx_Array_getKeyIndex(                                    /*M*/
    const lx_array_t  object_,                                             /*-*/
    lx_chars_t        key_ );                                              /*-*/

LX_PUBLIC lx_bool  lx_Array_keyExists(                                     /*M*/
    const lx_array_t  object_,                                             /*-*/
    lx_chars_t        key_ );                                              /*-*/

/* -------------------------------------------------------------------------- */
/* Methods: Manipulative                                                      */

LX_PUBLIC void  lx_Array_addItem(                                          /*M*/
    lx_array_t*   object_,                                                 /*-*/
    const void*   item_data_,                                              /*-*/
    const size_t  item_size_in_bytes_,                                     /*-*/
    lx_chars_t    key_ );                                                  /*-*/

LX_PUBLIC uint8_t*  lx_Array_getItemAt(                                    /*M*/
    lx_array_t*   object_,                                                 /*-*/
    const size_t  index_ );                                                /*-*/

LX_PUBLIC uint8_t*  lx_Array_getItemByKey(                                 /*M*/
    lx_array_t*  object_,                                                  /*-*/
    lx_chars_t   key_ );                                                   /*-*/

LX_PUBLIC uint8_t*  lx_Array_getLastItem( lx_array_t*  object_ );          /*M*/

/* Removes all items from the array.                                          */
/* You have to call the destructor of each item before calling this.          */
LX_PUBLIC void  lx_Array_removeItems( lx_array_t*  object_ );              /*M*/

LX_PUBLIC void  lx_Array_removeAt(                                         /*M*/
    lx_array_t*   object_,                                                 /*-*/
    const size_t  index_ );                                                /*-*/

LX_PUBLIC void  lx_Array_removeItemByKey(                                  /*M*/
    lx_array_t*  object_,                                                  /*-*/
    lx_chars_t   key_ );                                                   /*-*/

LX_PUBLIC void  lx_Array_removeLast( lx_array_t*  object_ );               /*M*/

LX_PUBLIC void  lx_Array_resize(                                           /*M*/
    lx_array_t*   object_,                                                 /*-*/
    const size_t  new_count_ );                                            /*-*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
