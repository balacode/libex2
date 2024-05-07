/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                 [libex_http_server.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_HTTP_SERVER_H
#define      INCLUDED_LIBEX_HTTP_SERVER_H

#include "libex.h"
#include "libex_stringc.h"

#define lx_HttpServer_callback_fn( CALLBACK_FN_PTR_ )                       \
    lx_new_bytes_t (*CALLBACK_FN_PTR_)( lx_http_request_t*  request_ )  /*#*/

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

typedef struct  lx_HttpServer {
    uint8_t*  ob;                                            /* lx_HttpServer */
}
lx_HttpServer, lx_new_HttpServer;

typedef struct  lx_http_request_t {
    lx_new_bchars_t  recv_header;                        /* lx_http_request_t */
    lx_new_bchars_t  recv_command;                       /* lx_http_request_t */
    lx_new_bchars_t  recv_url;                           /* lx_http_request_t */
    lx_new_bchars_t  recv_body;                          /* lx_http_request_t */
    lx_new_bchars_t  recv_data;                          /* lx_http_request_t */
}
lx_http_request_t, lx_new_http_request_t;

/* -------------------------------------------------------------------------- */
/* Constructor:                                                               */

LX_PUBLIC lx_HttpServer  lx_HttpServer_init( void );                       /*C*/

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

LX_PUBLIC void  lx_HttpServer_free( lx_HttpServer*  object_ );             /*D*/

/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */

LX_PUBLIC void  lx_HttpServer_run(                                         /*M*/
    lx_HttpServer  object_,                                                /*-*/
    const int      listen_on_port_ );                                      /*-*/

LX_PUBLIC void  lx_HttpServer_setHttpGetHandler(                           /*M*/
    lx_HttpServer  object_,                                                /*-*/
    lx_HttpServer_callback_fn(callback_fn_) );                             /*-*/

LX_PUBLIC void  lx_HttpServer_stop( lx_HttpServer  object_ );              /*M*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
