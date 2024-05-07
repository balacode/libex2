/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                   [libex_http_app_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_HTTP_APP__H
#define      INCLUDED_LIBEX_HTTP_APP__H
#include "libex_http_app.h"

#define HTTP_APP_DATA_READER_FN         LX_HTTP_APP_DATA_READER_FN

/* Initializer: */
#define HttpApp_init                    lx_HttpApp_init

/* Destructor: */
#define HttpApp_free                    lx_HttpApp_free

/* Methods: */
#define HttpApp_setDataReader           lx_HttpApp_setDataReader
#define HttpApp_run                     lx_HttpApp_run

/* Methods: HTTP */
#define HttpApp_get                     lx_HttpApp_get

#endif                                                                   /*eof*/
