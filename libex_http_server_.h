/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                [libex_http_server_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_HTTP_SERVER__H
#define      INCLUDED_LIBEX_HTTP_SERVER__H
#include "libex_http_server.h"

#define HttpServer_callback_fn          lx_HttpServer_callback_fn

/* -------------------------------------------------------------------------- */

#define HttpServer                      lx_HttpServer
#define new_HttpServer                  lx_new_HttpServer

#define http_request_t                  lx_http_request_t
#define new_http_request_t              lx_new_http_request_t

/* -------------------------------------------------------------------------- */
/* Constructor:                                                               */

#define HttpServer_init                 lx_HttpServer_init

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

#define HttpServer_free                 lx_HttpServer_free

/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */

#define HttpServer_run                  lx_HttpServer_run
#define HttpServer_setHttpGetHandler    lx_HttpServer_setHttpGetHandler
#define HttpServer_stop                 lx_HttpServer_stop

#endif                                                                   /*eof*/
