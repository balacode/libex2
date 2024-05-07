/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                    [libex_http_app.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_HTTP_APP_H
#define      INCLUDED_LIBEX_HTTP_APP_H

#include "libex_archive.h"
#include "libex_http_server.h"

#define LX_HTTP_APP_DATA_READER_FN( CALLBACK_FN_PTR_ )          \
    lx_new_chars_t (*CALLBACK_FN_PTR_)( lx_chars_t  sql_ )  /*#*/

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

/* -------------------------------------------------------------------------- */
/* Initializer:                                                               */

LX_PUBLIC void  lx_HttpApp_init(                                           /*C*/
    lx_archive_t  archive_,                                                /*-*/
    lx_chars_t    site_path_ );                                            /*-*/

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

LX_PUBLIC void  lx_HttpApp_free( void );                                   /*D*/

/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */

LX_PUBLIC void  lx_HttpApp_setDataReader(                                  /*M*/
    LX_HTTP_APP_DATA_READER_FN(callback_fn_) );                            /*-*/

LX_PUBLIC void  lx_HttpApp_run( const int  listen_on_port_ );              /*M*/

/* -------------------------------------------------------------------------- */
/* Methods: HTTP                                                              */

LX_PUBLIC lx_new_bytes_t  lx_HttpApp_get( lx_http_request_t*  request_ );  /*M*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
