/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                     [libex_network.h] */
/* -------------------------------------------------------------------------- */

#if (defined __GNUC__ || defined __clang__) && !defined __MINGW32__
#pragma GCC diagnostic ignored "-Wunused-macros"
#endif

#if !defined INCLUDED_LIBEX_NETWORK_H
#define      INCLUDED_LIBEX_NETWORK_H

#include "libex.h"
#include "libex_config.h"

#if LX_PLATFORM_LINUX
#include <netinet/in.h>
#include <sys/select.h>
#endif

#if defined _MSC_VER && LX_PLATFORM_WIN32 && !defined _WINSOCK2API_
#pragma message("NOTE: winsock2.h hasn't been included before libex_network.h")
#endif

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

/* -------------------------------------------------------------------------- */
/* Standard network constants and types:                                      */

#if LX_PLATFORM_LINUX
#define LX_INVALID_SOCKET  LX_CAST(lx_socket_t, -1)
#define LX_SOCKET_ERROR    LX_CAST(lx_socket_t, -1)
#endif                                                   /* LX_PLATFORM_LINUX */

#if LX_PLATFORM_WIN32
#define LX_INVALID_SOCKET  LX_CAST(lx_socket_t, ~0)
#define LX_SOCKET_ERROR    SOCKET_ERROR                       /*win:winsock2.h*/
#endif                                                   /* LX_PLATFORM_WIN32 */

#if LX_PLATFORM_LINUX
typedef in_addr_t      lx_in_addr_t;
typedef int            lx_socket_t;
#endif

#if LX_PLATFORM_WIN32
typedef unsigned long  lx_in_addr_t;
typedef unsigned int   lx_socket_t;
#endif

/* -------------------------------------------------------------------------- */
/* HTTP Enumerations:                                                         */

typedef enum  _lx_http_method_enum {
    LX_HTTP_METHOD_UNKNOWN = 0,                        /* lx_http_method_enum */
    LX_HTTP_METHOD_GET,                                /* lx_http_method_enum */
    LX_HTTP_METHOD_HEAD,                               /* lx_http_method_enum */
    LX_HTTP_METHOD_POST                                /* lx_http_method_enum */
}
lx_http_method_enum;                                                    /*enum*/

/* Status Codes (RFC-2616, HTTP/1.1, June 1999 */
typedef enum  _lx_http_status_enum {
    LX_HTTP_0_NO_STATUS                    = 0,        /* lx_http_status_enum */

    /* Info 1xx */
    LX_HTTP_100_CONTINUE                   = 100,      /* lx_http_status_enum */
    LX_HTTP_101_SWITCHING_PROTOCOLS        = 101,      /* lx_http_status_enum */

    /* Successful 2xx */
    LX_HTTP_200_OK                         = 200,      /* lx_http_status_enum */
    LX_HTTP_201_CREATED                    = 201,      /* lx_http_status_enum */
    LX_HTTP_202_ACCEPTED                   = 202,      /* lx_http_status_enum */
    LX_HTTP_203_NON_AUTHORITATIVE_INFO     = 203,      /* lx_http_status_enum */
    LX_HTTP_204_NO_CONTENT                 = 204,      /* lx_http_status_enum */
    LX_HTTP_205_RESET_CONTENT              = 205,      /* lx_http_status_enum */
    LX_HTTP_206_PARTIAL_CONTENT            = 206,      /* lx_http_status_enum */

    /* Redirection 3xx */
    LX_HTTP_300_MULTIPLE_CHOICES           = 300,      /* lx_http_status_enum */
    LX_HTTP_301_MOVED_PERMANENTLY          = 301,      /* lx_http_status_enum */
    LX_HTTP_302_FOUND                      = 302,      /* lx_http_status_enum */
    LX_HTTP_303_SEE_OTHER                  = 303,      /* lx_http_status_enum */
    LX_HTTP_304_NOT_MODIFIED               = 304,      /* lx_http_status_enum */
    LX_HTTP_305_USE_PROXY                  = 305,      /* lx_http_status_enum */
    LX_HTTP_306_UNUSED                     = 306,      /* lx_http_status_enum */
    LX_HTTP_307_TEMPORARY_REDIRECT         = 307,      /* lx_http_status_enum */

    /* Client Error 4xx */
    LX_HTTP_400_BAD_REQUEST                = 400,      /* lx_http_status_enum */
    LX_HTTP_401_UNAUTHORIZED               = 401,      /* lx_http_status_enum */
    LX_HTTP_402_PAYMENT_REQUIRED           = 402,      /* lx_http_status_enum */
    LX_HTTP_403_FORBIDDEN                  = 403,      /* lx_http_status_enum */
    LX_HTTP_404_NOT_FOUND                  = 404,      /* lx_http_status_enum */
    LX_HTTP_405_METHOD_NOT_ALLOWED         = 405,      /* lx_http_status_enum */
    LX_HTTP_406_NOT_ACCEPTABLE             = 406,      /* lx_http_status_enum */
    LX_HTTP_407_PROXY_AUTH_REQUIRED        = 407,      /* lx_http_status_enum */
    LX_HTTP_408_REQUEST_TIMEOUT            = 408,      /* lx_http_status_enum */
    LX_HTTP_409_CONFLICT                   = 409,      /* lx_http_status_enum */
    LX_HTTP_410_GONE                       = 410,      /* lx_http_status_enum */
    LX_HTTP_411_LENGTH_REQUIRED            = 411,      /* lx_http_status_enum */
    LX_HTTP_412_PRECONDITION_FAILED        = 412,      /* lx_http_status_enum */
    LX_HTTP_413_REQUEST_ENTITY_TOO_LARGE   = 413,      /* lx_http_status_enum */
    LX_HTTP_414_REQUEST_URI_TOO_LONG       = 414,      /* lx_http_status_enum */
    LX_HTTP_415_UNSUPPORTED_MEDIA_TYPE     = 415,      /* lx_http_status_enum */
    LX_HTTP_416_REQ_RANGE_NOT_SATISFIABLE  = 416,      /* lx_http_status_enum */
    LX_HTTP_417_EXPECTATION_FAILED         = 417,      /* lx_http_status_enum */

    /* Server Error 5xx */
    LX_HTTP_500_INTERNAL_SERVER_ERROR      = 500,      /* lx_http_status_enum */
    LX_HTTP_501_NOT_IMPLEMENTED            = 501,      /* lx_http_status_enum */
    LX_HTTP_502_BAD_GATEWAY                = 502,      /* lx_http_status_enum */
    LX_HTTP_503_SERVICE_UNAVAILABLE        = 503,      /* lx_http_status_enum */
    LX_HTTP_504_GATEWAY_TIMEOUT            = 504,      /* lx_http_status_enum */
    LX_HTTP_505_HTTP_VERSION_NOT_SUPPORTED = 505       /* lx_http_status_enum */

}
lx_http_status_enum;                                                    /*enum*/

/* -------------------------------------------------------------------------- */
/* Standard Network Functions:                                                */

#define ACCEPT                          LX_CL lx_accept_fn
#define BIND                            LX_CL lx_bind_fn
#define CONNECT                         LX_CL lx_connect_fn
#define GETHOSTBYADDR                   LX_CL lx_gethostbyaddr_fn
#define GETHOSTBYNAME                   LX_CL lx_gethostbyname_fn
#define GETHOSTNAME                     LX_CL lx_gethostname_fn
#define HTONL                           LX_CL lx_htonl_fn
#define HTONS                           LX_CL lx_htons_fn
#define INET_ADDR                       LX_CL lx_inet_addr_fn
#define INET_NTOA                       LX_CL lx_inet_ntoa_fn
#define LISTEN                          LX_CL lx_listen_fn
#define NTOHS                           LX_CL lx_ntohs_fn
#define RECV                            LX_CL lx_recv_fn
#define SELECT                          LX_CL lx_select_fn
#define SEND                            LX_CL lx_send_fn
#define _SOCKET                         LX_CL lx_socket_fn

/* Sockets:                                  On Windows             On Linux  */
#define closesocket_win  closesocket         /*winsock2.h*/
#define ioctlsocket_win  ioctlsocket         /*winsock2.h*/
#define tux_close        close                                      /*unistd.h*/

LX_PUBLIC int  lx_accept_fn(                 /*winsock2.h*/  /*socket.h*/  /*F*/
    const int         socket_,                                             /*-*/
    struct sockaddr*  address_out_,                                        /*-*/
    int*              address_length_out_ );                               /*-*/

LX_PUBLIC int  lx_bind_fn(                   /*winsock2.h*/  /*socket.h*/  /*F*/
    const int               socket_,                                       /*-*/
    const struct sockaddr*  address_,                                      /*-*/
    const int               name_length_ );                                /*-*/

LX_PUBLIC int  lx_connect_fn(                /*winsock2.h*/  /*socket.h*/  /*F*/
    const int               socket_,                                       /*-*/
    const struct sockaddr*  name_,                                         /*-*/
    const int               name_length_ );                                /*-*/

LX_PUBLIC struct hostent*  lx_gethostbyaddr_fn( /*winsock2.h/netdb.h*/     /*F*/
    const char*  address_,                                                 /*-*/
    const int    length_,                                                  /*-*/
    const int    type_ );                                                  /*-*/

LX_PUBLIC struct hostent*  lx_gethostbyname_fn( /*winsock2.h/netdb.h*/     /*F*/
    const char*  name_ );                                                  /*-*/

LX_PUBLIC int  lx_gethostname_fn(            /*winsock2.h*/  /*unistd.h*/  /*F*/
    char*      name_out_,                                                  /*-*/
    const int  name_length_ );                                             /*-*/

LX_PUBLIC unsigned long  lx_htonl_fn(            /*winsock2.h*/  /*in.h*/  /*F*/
    const unsigned long  host_short_ );                                    /*-*/

LX_PUBLIC unsigned short  lx_htons_fn(           /*winsock2.h*/  /*in.h*/  /*F*/
    const unsigned short  host_short_ );                                   /*-*/

LX_PUBLIC unsigned long  lx_inet_addr_fn(      /*winsock2.h*/  /*inet.h*/  /*F*/
    const char*  cp_ );                                                    /*-*/

LX_PUBLIC char*  lx_inet_ntoa_fn(              /*winsock2.h*/  /*inet.h*/  /*F*/
    struct in_addr  in_ );                                                 /*-*/

LX_PUBLIC int  lx_listen_fn(                 /*winsock2.h*/  /*socket.h*/  /*F*/
    const int  socket_,                                                    /*-*/
    const int  backlog_ );                                                 /*-*/

LX_PUBLIC unsigned short  lx_ntohs_fn(           /*winsock2.h*/  /*in.h*/  /*F*/
    const unsigned short  net_short_ );                                    /*-*/

LX_PUBLIC int  lx_recv_fn(                   /*winsock2.h*/  /*socket.h*/  /*F*/
    const int  socket_,                                                    /*-*/
    uint8_t*   buffer_out_,                                                /*-*/
    const int  length_,                                                    /*-*/
    const int  flags_ );                                                   /*-*/

/* NOTE: If you see error C2061: syntax error : identifier 'fd_set' here,     */
/* (MSVC)   then you've not included  Winsock2.h and Windows.h elsewhere      */

LX_PUBLIC int  lx_select_fn(                 /*winsock2.h*/  /*select.h*/  /*F*/
    const int        number_of_fds_,                                       /*-*/
    fd_set*          read_fds_out_,                                        /*-*/
    fd_set*          write_fds_out_,                                       /*-*/
    fd_set*          except_fds_out_,                                      /*-*/
    struct timeval*  timeout_ );                                           /*-*/

LX_PUBLIC int  lx_send_fn(                   /*winsock2.h*/  /*socket.h*/  /*F*/
    const int    socket_,                                                  /*-*/
    const char*  buffer_,                                                  /*-*/
    const int    length_,                                                  /*-*/
    const int    flags_ );                                                 /*-*/

LX_PUBLIC int  lx_socket_fn(                 /*winsock2.h*/  /*socket.h*/  /*F*/
    const int  address_family_,                                            /*-*/
    const int  type_,                                                      /*-*/
    const int  protocol_ );                                                /*-*/

/* -------------------------------------------------------------------------- */
/* Windows-only definitions                                                   */

#if LX_PLATFORM_WIN32

#define WSACleanup_win                       WSACleanup           /*winsock2.h*/
#define WSAGetLastError_win                  WSAGetLastError      /*winsock2.h*/
#define WSAStartup_win                       WSAStartup           /*winsock2.h*/
#define WSAStringToAddressA_win              WSAStringToAddressA  /*winsock2.h*/
#define WSACleanup_win                       WSACleanup           /*winsock2.h*/
#define WSAGetLastError_win                  WSAGetLastError      /*winsock2.h*/
#define WSAStartup_win                       WSAStartup           /*winsock2.h*/
#define WSAStringToAddressA_win              WSAStringToAddressA  /*winsock2.h*/

#define WSA_E_CANCELLED_win                  WSA_E_CANCELLED
#define WSA_E_NO_MORE_win                    WSA_E_NO_MORE
#define WSA_QOS_ADMISSION_FAILURE_win        WSA_QOS_ADMISSION_FAILURE
#define WSA_QOS_BAD_OBJECT_win               WSA_QOS_BAD_OBJECT
#define WSA_QOS_BAD_STYLE_win                WSA_QOS_BAD_STYLE
#define WSA_QOS_EFILTERCOUNT_win             WSA_QOS_EFILTERCOUNT
#define WSA_QOS_EFILTERSTYLE_win             WSA_QOS_EFILTERSTYLE
#define WSA_QOS_EFILTERTYPE_win              WSA_QOS_EFILTERTYPE
#define WSA_QOS_EFLOWCOUNT_win               WSA_QOS_EFLOWCOUNT
#define WSA_QOS_EFLOWDESC_win                WSA_QOS_EFLOWDESC
#define WSA_QOS_EFLOWSPEC_win                WSA_QOS_EFLOWSPEC
#define WSA_QOS_EOBJLENGTH_win               WSA_QOS_EOBJLENGTH
#define WSA_QOS_EPOLICYOBJ_win               WSA_QOS_EPOLICYOBJ
#define WSA_QOS_EPROVSPECBUF_win             WSA_QOS_EPROVSPECBUF
#define WSA_QOS_EPSFILTERSPEC_win            WSA_QOS_EPSFILTERSPEC
#define WSA_QOS_EPSFLOWSPEC_win              WSA_QOS_EPSFLOWSPEC
#define WSA_QOS_ESDMODEOBJ_win               WSA_QOS_ESDMODEOBJ
#define WSA_QOS_ESERVICETYPE_win             WSA_QOS_ESERVICETYPE
#define WSA_QOS_ESHAPERATEOBJ_win            WSA_QOS_ESHAPERATEOBJ
#define WSA_QOS_EUNKOWNPSOBJ_win             WSA_QOS_EUNKOWNPSOBJ
#define WSA_QOS_GENERIC_ERROR_win            WSA_QOS_GENERIC_ERROR
#define WSA_QOS_NO_RECEIVERS_win             WSA_QOS_NO_RECEIVERS
#define WSA_QOS_NO_SENDERS_win               WSA_QOS_NO_SENDERS
#define WSA_QOS_POLICY_FAILURE_win           WSA_QOS_POLICY_FAILURE
#define WSA_QOS_RECEIVERS_win                WSA_QOS_RECEIVERS
#define WSA_QOS_REQUEST_CONFIRMED_win        WSA_QOS_REQUEST_CONFIRMED
#define WSA_QOS_RESERVED_PETYPE_win          WSA_QOS_RESERVED_PETYPE
#define WSA_QOS_SENDERS_win                  WSA_QOS_SENDERS
#define WSA_QOS_TRAFFIC_CTRL_ERROR_win       WSA_QOS_TRAFFIC_CTRL_ERROR
#define WSADATA_win                          WSADATA
#define WSAEACCES_win                        WSAEACCES
#define WSAEADDRINUSE_win                    WSAEADDRINUSE
#define WSAEADDRNOTAVAIL_win                 WSAEADDRNOTAVAIL
#define WSAEAFNOSUPPORT_win                  WSAEAFNOSUPPORT
#define WSAEALREADY_win                      WSAEALREADY
#define WSAEBADF_win                         WSAEBADF
#define WSAECANCELLED_win                    WSAECANCELLED
#define WSAECONNABORTED_win                  WSAECONNABORTED
#define WSAECONNREFUSED_win                  WSAECONNREFUSED
#define WSAECONNRESET_win                    WSAECONNRESET
#define WSAEDESTADDRREQ_win                  WSAEDESTADDRREQ
#define WSAEDISCON_win                       WSAEDISCON
#define WSAEDQUOT_win                        WSAEDQUOT
#define WSAEFAULT_win                        WSAEFAULT
#define WSAEHOSTDOWN_win                     WSAEHOSTDOWN
#define WSAEHOSTUNREACH_win                  WSAEHOSTUNREACH
#define WSAEINPROGRESS_win                   WSAEINPROGRESS
#define WSAEINTR_win                         WSAEINTR
#define WSAEINVAL_win                        WSAEINVAL
#define WSAEINVALIDPROCTABLE_win             WSAEINVALIDPROCTABLE
#define WSAEINVALIDPROVIDER_win              WSAEINVALIDPROVIDER
#define WSAEISCONN_win                       WSAEISCONN
#define WSAELOOP_win                         WSAELOOP
#define WSAEMFILE_win                        WSAEMFILE
#define WSAEMSGSIZE_win                      WSAEMSGSIZE
#define WSAENAMETOOLONG_win                  WSAENAMETOOLONG
#define WSAENETDOWN_win                      WSAENETDOWN
#define WSAENETRESET_win                     WSAENETRESET
#define WSAENETUNREACH_win                   WSAENETUNREACH
#define WSAENOBUFS_win                       WSAENOBUFS
#define WSAENOMORE_win                       WSAENOMORE
#define WSAENOPROTOOPT_win                   WSAENOPROTOOPT
#define WSAENOTCONN_win                      WSAENOTCONN
#define WSAENOTEMPTY_win                     WSAENOTEMPTY
#define WSAENOTSOCK_win                      WSAENOTSOCK
#define WSAEOPNOTSUPP_win                    WSAEOPNOTSUPP
#define WSAEPFNOSUPPORT_win                  WSAEPFNOSUPPORT
#define WSAEPROCLIM_win                      WSAEPROCLIM
#define WSAEPROTONOSUPPORT_win               WSAEPROTONOSUPPORT
#define WSAEPROTOTYPE_win                    WSAEPROTOTYPE
#define WSAEPROVIDERFAILEDINIT_win           WSAEPROVIDERFAILEDINIT
#define WSAEREFUSED_win                      WSAEREFUSED
#define WSAEREMOTE_win                       WSAEREMOTE
#define WSAESHUTDOWN_win                     WSAESHUTDOWN
#define WSAESOCKTNOSUPPORT_win               WSAESOCKTNOSUPPORT
#define WSAESTALE_win                        WSAESTALE
#define WSAETIMEDOUT_win                     WSAETIMEDOUT
#define WSAETOOMANYREFS_win                  WSAETOOMANYREFS
#define WSAEUSERS_win                        WSAEUSERS
#define WSAEWOULDBLOCK_win                   WSAEWOULDBLOCK
#define WSAHOST_NOT_FOUND_win                WSAHOST_NOT_FOUND
#define WSANO_DATA_win                       WSANO_DATA
#define WSANO_RECOVERY_win                   WSANO_RECOVERY
#define WSANOTINITIALISED_win                WSANOTINITIALISED
#define WSASERVICE_NOT_FOUND_win             WSASERVICE_NOT_FOUND
#define WSASYSCALLFAILURE_win                WSASYSCALLFAILURE
#define WSASYSNOTREADY_win                   WSASYSNOTREADY
#define WSATRY_AGAIN_win                     WSATRY_AGAIN
#define WSATYPE_NOT_FOUND_win                WSATYPE_NOT_FOUND
#define WSAVERNOTSUPPORTED_win               WSAVERNOTSUPPORTED
#define WSA_E_CANCELLED_win                  WSA_E_CANCELLED
#define WSA_E_NO_MORE_win                    WSA_E_NO_MORE
#define WSA_QOS_ADMISSION_FAILURE_win        WSA_QOS_ADMISSION_FAILURE
#define WSA_QOS_BAD_OBJECT_win               WSA_QOS_BAD_OBJECT
#define WSA_QOS_BAD_STYLE_win                WSA_QOS_BAD_STYLE
#define WSA_QOS_EFILTERCOUNT_win             WSA_QOS_EFILTERCOUNT
#define WSA_QOS_EFILTERSTYLE_win             WSA_QOS_EFILTERSTYLE
#define WSA_QOS_EFILTERTYPE_win              WSA_QOS_EFILTERTYPE
#define WSA_QOS_EFLOWCOUNT_win               WSA_QOS_EFLOWCOUNT
#define WSA_QOS_EFLOWDESC_win                WSA_QOS_EFLOWDESC
#define WSA_QOS_EFLOWSPEC_win                WSA_QOS_EFLOWSPEC
#define WSA_QOS_EOBJLENGTH_win               WSA_QOS_EOBJLENGTH
#define WSA_QOS_EPOLICYOBJ_win               WSA_QOS_EPOLICYOBJ
#define WSA_QOS_EPROVSPECBUF_win             WSA_QOS_EPROVSPECBUF
#define WSA_QOS_EPSFILTERSPEC_win            WSA_QOS_EPSFILTERSPEC
#define WSA_QOS_EPSFLOWSPEC_win              WSA_QOS_EPSFLOWSPEC
#define WSA_QOS_ESDMODEOBJ_win               WSA_QOS_ESDMODEOBJ
#define WSA_QOS_ESERVICETYPE_win             WSA_QOS_ESERVICETYPE
#define WSA_QOS_ESHAPERATEOBJ_win            WSA_QOS_ESHAPERATEOBJ
#define WSA_QOS_EUNKOWNPSOBJ_win             WSA_QOS_EUNKOWNPSOBJ
#define WSA_QOS_GENERIC_ERROR_win            WSA_QOS_GENERIC_ERROR
#define WSA_QOS_NO_RECEIVERS_win             WSA_QOS_NO_RECEIVERS
#define WSA_QOS_NO_SENDERS_win               WSA_QOS_NO_SENDERS
#define WSA_QOS_POLICY_FAILURE_win           WSA_QOS_POLICY_FAILURE
#define WSA_QOS_RECEIVERS_win                WSA_QOS_RECEIVERS
#define WSA_QOS_REQUEST_CONFIRMED_win        WSA_QOS_REQUEST_CONFIRMED
#define WSA_QOS_RESERVED_PETYPE_win          WSA_QOS_RESERVED_PETYPE
#define WSA_QOS_SENDERS_win                  WSA_QOS_SENDERS
#define WSA_QOS_TRAFFIC_CTRL_ERROR_win       WSA_QOS_TRAFFIC_CTRL_ERROR
#define WSADATA_win                          WSADATA
#define WSAEACCES_win                        WSAEACCES
#define WSAEADDRINUSE_win                    WSAEADDRINUSE
#define WSAEADDRNOTAVAIL_win                 WSAEADDRNOTAVAIL
#define WSAEAFNOSUPPORT_win                  WSAEAFNOSUPPORT
#define WSAEALREADY_win                      WSAEALREADY
#define WSAEBADF_win                         WSAEBADF
#define WSAECANCELLED_win                    WSAECANCELLED
#define WSAECONNABORTED_win                  WSAECONNABORTED
#define WSAECONNREFUSED_win                  WSAECONNREFUSED
#define WSAECONNRESET_win                    WSAECONNRESET
#define WSAEDESTADDRREQ_win                  WSAEDESTADDRREQ
#define WSAEDISCON_win                       WSAEDISCON
#define WSAEDQUOT_win                        WSAEDQUOT
#define WSAEFAULT_win                        WSAEFAULT
#define WSAEHOSTDOWN_win                     WSAEHOSTDOWN
#define WSAEHOSTUNREACH_win                  WSAEHOSTUNREACH
#define WSAEINPROGRESS_win                   WSAEINPROGRESS
#define WSAEINTR_win                         WSAEINTR
#define WSAEINVAL_win                        WSAEINVAL
#define WSAEINVALIDPROCTABLE_win             WSAEINVALIDPROCTABLE
#define WSAEINVALIDPROVIDER_win              WSAEINVALIDPROVIDER
#define WSAEISCONN_win                       WSAEISCONN
#define WSAELOOP_win                         WSAELOOP
#define WSAEMFILE_win                        WSAEMFILE
#define WSAEMSGSIZE_win                      WSAEMSGSIZE
#define WSAENAMETOOLONG_win                  WSAENAMETOOLONG
#define WSAENETDOWN_win                      WSAENETDOWN
#define WSAENETRESET_win                     WSAENETRESET
#define WSAENETUNREACH_win                   WSAENETUNREACH
#define WSAENOBUFS_win                       WSAENOBUFS
#define WSAENOMORE_win                       WSAENOMORE
#define WSAENOPROTOOPT_win                   WSAENOPROTOOPT
#define WSAENOTCONN_win                      WSAENOTCONN
#define WSAENOTEMPTY_win                     WSAENOTEMPTY
#define WSAENOTSOCK_win                      WSAENOTSOCK
#define WSAEOPNOTSUPP_win                    WSAEOPNOTSUPP
#define WSAEPFNOSUPPORT_win                  WSAEPFNOSUPPORT
#define WSAEPROCLIM_win                      WSAEPROCLIM
#define WSAEPROTONOSUPPORT_win               WSAEPROTONOSUPPORT
#define WSAEPROTOTYPE_win                    WSAEPROTOTYPE
#define WSAEPROVIDERFAILEDINIT_win           WSAEPROVIDERFAILEDINIT
#define WSAEREFUSED_win                      WSAEREFUSED
#define WSAEREMOTE_win                       WSAEREMOTE
#define WSAESHUTDOWN_win                     WSAESHUTDOWN
#define WSAESOCKTNOSUPPORT_win               WSAESOCKTNOSUPPORT
#define WSAESTALE_win                        WSAESTALE
#define WSAETIMEDOUT_win                     WSAETIMEDOUT
#define WSAETOOMANYREFS_win                  WSAETOOMANYREFS
#define WSAEUSERS_win                        WSAEUSERS
#define WSAEWOULDBLOCK_win                   WSAEWOULDBLOCK
#define WSAHOST_NOT_FOUND_win                WSAHOST_NOT_FOUND
#define WSANO_DATA_win                       WSANO_DATA
#define WSANO_RECOVERY_win                   WSANO_RECOVERY
#define WSANOTINITIALISED_win                WSANOTINITIALISED
#define WSASERVICE_NOT_FOUND_win             WSASERVICE_NOT_FOUND
#define WSASYSCALLFAILURE_win                WSASYSCALLFAILURE
#define WSASYSNOTREADY_win                   WSASYSNOTREADY
#define WSATRY_AGAIN_win                     WSATRY_AGAIN
#define WSATYPE_NOT_FOUND_win                WSATYPE_NOT_FOUND
#define WSAVERNOTSUPPORTED_win               WSAVERNOTSUPPORTED

#endif                                                   /* LX_PLATFORM_WIN32 */

/* -------------------------------------------------------------------------- */

LX_PUBLIC lx_bool  lx_net_start( const uint32_t  src_uid_ );               /*F*/

LX_PUBLIC lx_bool  lx_net_end( const uint32_t  src_uid_ );                 /*F*/

/* -------------------------------------------------------------------------- */

LX_PUBLIC lx_chars_t  lx_http_status_name( const int  http_code_ );        /*F*/

LX_PUBLIC lx_chars_t  lx_mime_type( lx_chars_t  extension_ );              /*F*/

LX_PUBLIC lx_chars_t  lx_net_error_name( const int  error_no_ );           /*F*/

LX_PUBLIC lx_new_chars_t  lx_net_text_request(                             /*F*/
    lx_chars_t      request_,                                              /*-*/
    lx_chars_t      server_name_or_ip_,                                    /*-*/
    const uint32_t  port_,                                                 /*-*/
    const size_t    max_message_len_ );                                    /*-*/

/* Return an IP address string based on the specified host name               */
/* (if host name is not specified, uses local computer's name).               */
LX_PUBLIC lx_new_chars_t  lx_net_ip_address( lx_chars_t  host_name_ );     /*F*/

LX_PUBLIC lx_new_chars_t  lx_net_plaintext_request(                        /*F*/
    lx_chars_t      request_,                                              /*-*/
    lx_chars_t      server_name_or_ip_,                                    /*-*/
    const uint32_t  port_,                                                 /*-*/
    const size_t    max_message_size_ );                                   /*-*/

LX_PUBLIC lx_new_bytes_t  lx_net_encrypted_request(                        /*F*/
    const lx_bytes_t  request_,                                            /*-*/
    lx_chars_t        server_name_or_ip_,                                  /*-*/
    const uint32_t    port_,                                               /*-*/
    const size_t      max_message_size_ );                                 /*-*/

LX_PUBLIC void  lx_net_encrypted_server(                                   /*F*/
    const int  port_no_,                                                   /*-*/
    lx_new_bytes_t  (*callback_fn_)( const lx_bytes_t  request_ ) );       /*-*/

/*    Use the following declaration format for the callback function:         */
/*    lx_new_bytes_t  CallbackFunctionName( lx_bytes_t  request_ )            */
/*                                                                            */
/*    Use it as follows:                                                      */
/*    lx_net_encrypted_server(111, &CallbackFunctionName);                    */
/*                                                                            */
/*    Substitute 111 and CallbackFunctionName with what you require.          */

LX_PUBLIC lx_new_chars_t  lx_uri_encode( lx_chars_t  text_ );              /*F*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
