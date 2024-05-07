/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                   [libex_html_list.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_HTML_LIST_H
#define      INCLUDED_LIBEX_HTML_LIST_H

#include "libex.h"

#if defined _MSC_VER
#pragma once
#endif

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

typedef struct  lx_HtmlList {
    uint8_t*  ob;                                        /* lx_HtmlList */
}
lx_HtmlList, lx_new_HtmlList;

/* -------------------------------------------------------------------------- */
/* Constructor:                                                               */

LX_PUBLIC lx_new_HtmlList  lx_HtmlList_init( void );                       /*C*/

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

LX_PUBLIC void  lx_HtmlList_free( lx_HtmlList*  object_ );                 /*D*/

/* -------------------------------------------------------------------------- */
/* Properties:                                                                */

LX_PUBLIC lx_chars_t  lx_HtmlList_getKeyField( lx_HtmlList  object_ );     /*P*/

LX_PUBLIC void  lx_HtmlList_setKeyField(                                   /*P*/
    lx_HtmlList  object_,                                                  /*-*/
    lx_chars_t   value_ );                                                 /*-*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
