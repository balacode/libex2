/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                      [libex_array_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_ARRAY__H
#define      INCLUDED_LIBEX_ARRAY__H
#include "libex_array.h"

/* -------------------------------------------------------------------------- */

#define array_t                         lx_array_t
#define new_array_t                     lx_new_array_t
#define null_array                      lx_null_array

/* -------------------------------------------------------------------------- */
/* Constructor:                                                               */

#define Array_init                      lx_Array_init

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

#define Array_free                      lx_Array_free

/* -------------------------------------------------------------------------- */
/* Methods: Informative                                                       */

#define Array_count                     lx_Array_count
#define Array_getKeyIndex               lx_Array_getKeyIndex
#define Array_keyExists                 lx_Array_keyExists

/* -------------------------------------------------------------------------- */
/* Methods: Manipulative                                                      */

#define Array_addItem                   lx_Array_addItem
#define Array_getItemAt                 lx_Array_getItemAt
#define Array_getItemByKey              lx_Array_getItemByKey
#define Array_getLastItem               lx_Array_getLastItem
#define Array_removeAt                  lx_Array_removeAt
#define Array_removeItemByKey           lx_Array_removeItemByKey
#define Array_removeItems               lx_Array_removeItems
#define Array_removeLast                lx_Array_removeLast
#define Array_resize                    lx_Array_resize

#endif                                                                   /*eof*/
