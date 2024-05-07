/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                    [libex_network_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_NETWORK__H
#define      INCLUDED_LIBEX_NETWORK__H

#include "libex_network.h"

#if !defined LX_PLATFORM_WIN32
#define INVALID_SOCKET                        LX_INVALID_SOCKET
#define SOCKET_ERROR                          LX_SOCKET_ERROR
#endif

#define in_addr_t                             lx_in_addr_t
#define socket_t                              lx_socket_t

/* -------------------------------------------------------------------------- */
/* HTTP Enumerations:                                                         */

#define http_method_enum                      lx_http_method_enum
#define HTTP_METHOD_UNKNOWN                   LX_HTTP_METHOD_UNKNOWN
#define HTTP_METHOD_GET                       LX_HTTP_METHOD_GET
#define HTTP_METHOD_HEAD                      LX_HTTP_METHOD_HEAD
#define HTTP_METHOD_POST                      LX_HTTP_METHOD_POST

#define http_status_enum                      lx_http_status_enum
#define HTTP_0_NO_STATUS                      LX_HTTP_0_NO_STATUS
#define HTTP_100_CONTINUE                     LX_HTTP_100_CONTINUE
#define HTTP_101_SWITCHING_PROTOCOLS          LX_HTTP_101_SWITCHING_PROTOCOLS
#define HTTP_200_OK                           LX_HTTP_200_OK
#define HTTP_201_CREATED                      LX_HTTP_201_CREATED
#define HTTP_202_ACCEPTED                     LX_HTTP_202_ACCEPTED
#define HTTP_203_NON_AUTHORITATIVE_INFO       LX_HTTP_203_NON_AUTHORITATIVE_INFO
#define HTTP_204_NO_CONTENT                   LX_HTTP_204_NO_CONTENT
#define HTTP_205_RESET_CONTENT                LX_HTTP_205_RESET_CONTENT
#define HTTP_206_PARTIAL_CONTENT              LX_HTTP_206_PARTIAL_CONTENT
#define HTTP_300_MULTIPLE_CHOICES             LX_HTTP_300_MULTIPLE_CHOICES
#define HTTP_301_MOVED_PERMANENTLY            LX_HTTP_301_MOVED_PERMANENTLY
#define HTTP_302_FOUND                        LX_HTTP_302_FOUND
#define HTTP_303_SEE_OTHER                    LX_HTTP_303_SEE_OTHER
#define HTTP_304_NOT_MODIFIED                 LX_HTTP_304_NOT_MODIFIED
#define HTTP_305_USE_PROXY                    LX_HTTP_305_USE_PROXY
#define HTTP_306_UNUSED                       LX_HTTP_306_UNUSED
#define HTTP_307_TEMPORARY_REDIRECT           LX_HTTP_307_TEMPORARY_REDIRECT
#define HTTP_400_BAD_REQUEST                  LX_HTTP_400_BAD_REQUEST
#define HTTP_401_UNAUTHORIZED                 LX_HTTP_401_UNAUTHORIZED
#define HTTP_402_PAYMENT_REQUIRED             LX_HTTP_402_PAYMENT_REQUIRED
#define HTTP_403_FORBIDDEN                    LX_HTTP_403_FORBIDDEN
#define HTTP_404_NOT_FOUND                    LX_HTTP_404_NOT_FOUND
#define HTTP_405_METHOD_NOT_ALLOWED           LX_HTTP_405_METHOD_NOT_ALLOWED
#define HTTP_406_NOT_ACCEPTABLE               LX_HTTP_406_NOT_ACCEPTABLE
#define HTTP_407_PROXY_AUTH_REQUIRED          LX_HTTP_407_PROXY_AUTH_REQUIRED
#define HTTP_408_REQUEST_TIMEOUT              LX_HTTP_408_REQUEST_TIMEOUT
#define HTTP_409_CONFLICT                     LX_HTTP_409_CONFLICT
#define HTTP_410_GONE                         LX_HTTP_410_GONE
#define HTTP_411_LENGTH_REQUIRED              LX_HTTP_411_LENGTH_REQUIRED
#define HTTP_412_PRECONDITION_FAILED          LX_HTTP_412_PRECONDITION_FAILED
#define HTTP_414_REQUEST_URI_TOO_LONG         LX_HTTP_414_REQUEST_URI_TOO_LONG
#define HTTP_415_UNSUPPORTED_MEDIA_TYPE       LX_HTTP_415_UNSUPPORTED_MEDIA_TYPE
#define HTTP_417_EXPECTATION_FAILED           LX_HTTP_417_EXPECTATION_FAILED
#define HTTP_500_INTERNAL_SERVER_ERROR        LX_HTTP_500_INTERNAL_SERVER_ERROR
#define HTTP_501_NOT_IMPLEMENTED              LX_HTTP_501_NOT_IMPLEMENTED
#define HTTP_502_BAD_GATEWAY                  LX_HTTP_502_BAD_GATEWAY
#define HTTP_503_SERVICE_UNAVAILABLE          LX_HTTP_503_SERVICE_UNAVAILABLE
#define HTTP_504_GATEWAY_TIMEOUT              LX_HTTP_504_GATEWAY_TIMEOUT

#define HTTP_416_REQ_RANGE_NOT_SATISFIABLE \
    LX_HTTP_416_REQ_RANGE_NOT_SATISFIABLE

#define HTTP_413_REQUEST_ENTITY_TOO_LARGE \
    LX_HTTP_413_REQUEST_ENTITY_TOO_LARGE

#define HTTP_505_HTTP_VERSION_NOT_SUPPORTED \
    LX_HTTP_505_HTTP_VERSION_NOT_SUPPORTED

/* -------------------------------------------------------------------------- */
/* Standard Network Functions:                                                */

#define accept_fn                       lx_accept_fn
#define bind_fn                         lx_bind_fn
#define connect_fn                      lx_connect_fn
#define gethostbyaddr_fn                lx_gethostbyaddr_fn
#define gethostbyname_fn                lx_gethostbyname_fn
#define gethostname_fn                  lx_gethostname_fn
#define htonl_fn                        lx_htonl_fn
#define htons_fn                        lx_htons_fn
#define inet_addr_fn                    lx_inet_addr_fn
#define inet_ntoa_fn                    lx_inet_ntoa_fn
#define listen_fn                       lx_listen_fn
#define ntohs_fn                        lx_ntohs_fn
#define recv_fn                         lx_recv_fn
#define select_fn                       lx_select_fn
#define send_fn                         lx_send_fn
#define socket_fn                       lx_socket_fn

/* -------------------------------------------------------------------------- */

#define net_end                         lx_net_end
#define net_start                       lx_net_start

/* -------------------------------------------------------------------------- */

#define http_status_name                lx_http_status_name
#define mime_type                       lx_mime_type
#define net_encrypted_request           lx_net_encrypted_request
#define net_encrypted_server            lx_net_encrypted_server
#define net_error_name                  lx_net_error_name
#define net_ip_address                  lx_net_ip_address
#define net_plaintext_request           lx_net_plaintext_request
#define net_text_request                lx_net_text_request
#define uri_encode                      lx_uri_encode

#endif                                                                   /*eof*/
