/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                     [libex_network.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_network_.h"
#if defined INCLUDED_LIBEX_NETWORK_H

#include "libex_config_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#include <stdio.h>   /* for printf() */
#include <string.h>  /* for memset() */

#if PLATFORM_LINUX
#include <arpa/inet.h>
/* connect()  htons() inet_pton()  SOCK_STREAM  sockaddr_in socket()  AF_INET */
#include <fcntl.h>
#include <netdb.h>      /* gethostbyname(), hostent       */
#include <sys/errno.h>  /* for various error constants    */
#include <sys/ioctl.h>  /* for ioctl()                    */
#include <unistd.h>     /* for dup() gethostname() read() */
#include <sys/types.h>
#include <sys/socket.h>
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32 && !defined INCLUDED_LIBEX_C_PRECOMPILED_H
#include <winerror.h>  /* for WSA*        */
#include <winsock2.h>
#include <ws2tcpip.h>  /* for inet_pton() */
#include "libex_win32_.h"
#endif

#include "libex_.h"
#include "libex_byte_array_.h"
#include "libex_bytes_.h"
#include "libex_call_.h"
#include "libex_const_.h"
#include "libex_crypto_.h"
#include "libex_libc_.h"
#include "libex_logging_.h"
#include "libex_macro_.h"
#include "libex_stringc_.h"
#include "libex_system_.h"   /* for uptime_ms() */
#include "libex_type_.h"

#if PLATFORM_WIN32 && defined _MSC_VER
#pragma comment (lib, "wsock32.lib")
#pragma comment (lib, "ws2_32.lib")
/* gethostbyaddr() */
/* gethostbyname() */
/* gethostname()   */
/* inet_addr()     */
/* inet_ntoa()     */
#endif

#if defined __GNUC__ && !defined __MINGW32__
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#endif
#if defined __clang__
#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#endif

#if defined _MSC_VER
#pragma warning (disable:4710)  /* W:L4 function not inlined                  */
#endif


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


/* -------------------------------------------------------------------------- */
/* Standard Network Functions:                                                */


/*winsock2.h*/  /*socket.h*/
PUBLIC int  accept_fn(                                                     /*F*/
    const int         socket_,                                             /*-*/
    struct sockaddr*  address_out_,                                        /*-*/
    int*              address_length_out_ ) {                              /*-*/
    GO                                                            (UID(F4A323));
#if PLATFORM_LINUX
    socklen_t  address_length = 0;
    const int  ret = accept(socket_, address_out_, &address_length);
    *address_length_out_ = CAST(int, address_length);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    const int  ret = accept(socket_, address_out_, address_length_out_);
#endif

    RETURN(ret);
} /* accept_fn */


/*winsock2.h*/  /*socket.h*/
PUBLIC int  bind_fn(                                                       /*F*/
    const int               socket_,                                       /*-*/
    const struct sockaddr*  address_,                                      /*-*/
    const int               name_length_ ) {                               /*-*/
    GO                                                            (UID(FABA55));
    const int  ret = bind(socket_, address_, name_length_);
    RETURN(ret);
} /* bind_fn */


/*winsock2.h*/  /*socket.h*/
PUBLIC int  connect_fn(                                                    /*F*/
    const int               socket_,                                       /*-*/
    const struct sockaddr*  name_,                                         /*-*/
    const int               name_length_ ) {                               /*-*/
    GO                                                            (UID(F25705));
    const int  ret = connect(socket_, name_, name_length_);
    RETURN(ret);
} /* connect_fn */


/*winsock2.h/netdb.h*/
PUBLIC struct hostent*  gethostbyaddr_fn(                                  /*F*/
    const char*  address_,                                                 /*-*/
    const int    length_,                                                  /*-*/
    const int    type_ ) {                                                 /*-*/
    GO                                                            (UID(F3902C));
    struct hostent*  ret = gethostbyaddr(address_, length_, type_);
    RETURN(ret);
} /* gethostbyaddr_fn */


/*winsock2.h/netdb.h*/
PUBLIC struct hostent*  gethostbyname_fn( const char*  name_ ) {           /*F*/
    GO                                                            (UID(F219F2));
    struct hostent*  ret = gethostbyname(name_);
    RETURN(ret);
} /* gethostbyname_fn */


/*winsock2.h*/  /*unistd.h*/
PUBLIC int  gethostname_fn(                                                /*F*/
    char*      name_out_,                                                  /*-*/
    const int  name_length_ ) {                                            /*-*/
    GO                                                            (UID(F361F7));
    const int  ret = gethostname( /* build with gcc/clang -D_XOPEN_SOURCE=500 */
                         name_out_, name_length_);
    RETURN(ret);
} /* gethostname_fn */


/*winsock2.h*/  /*in.h*/
PUBLIC unsigned long  htonl_fn( const unsigned long  host_short_ ) {       /*F*/
    GO                                                            (UID(F61534));
    const unsigned long  ret = htonl(host_short_);
    RETURN(ret);
} /* htonl_fn */


/*winsock2.h*/  /*in.h*/
PUBLIC unsigned short  htons_fn( const unsigned short  host_short_ ) {     /*F*/
    GO                                                            (UID(F0BA8F));
    const unsigned short  ret = htons(host_short_);
    RETURN(ret);
} /* htons_fn */


/*winsock2.h*/  /*inet.h*/
PUBLIC unsigned long  inet_addr_fn( const char*  cp_ ) {                   /*F*/
    GO                                                            (UID(FDE9C5));
    const unsigned long  ret = inet_addr(cp_);
    RETURN(ret);
} /* inet_addr_fn */


/*winsock2.h*/  /*inet.h*/
PUBLIC char*  inet_ntoa_fn( struct in_addr  in_ ) {                        /*F*/
    GO                                                            (UID(FC328F));
    char*  ret = inet_ntoa(in_);
    RETURN(ret);
} /* inet_ntoa_fn */


/*winsock2.h*/  /*socket.h*/
PUBLIC int  listen_fn(                                                     /*F*/
    const int  socket_,                                                    /*-*/
    const int  backlog_ ) {                                                /*-*/
    GO                                                            (UID(F19BAD));
    const int  ret = listen(socket_, backlog_);
    RETURN(ret);
} /* listen_fn */


/*winsock2.h*/  /*in.h*/
PUBLIC unsigned short  ntohs_fn( const unsigned short  net_short_ ) {      /*F*/
    GO                                                            (UID(FF2332));
    const unsigned short  ret = ntohs(net_short_);
    RETURN(ret);
} /* ntohs_fn */


/*winsock2.h*/  /*socket.h*/
PUBLIC int  recv_fn(                                                       /*F*/
    const int  socket_,                                                    /*-*/
    uint8_t*   buffer_out_,                                                /*-*/
    const int  length_,                                                    /*-*/
    const int  flags_ ) {                                                  /*-*/
    GO                                                            (UID(F143EC));
    /* if ret returns 0, the peer has performed an orderly shutdown. */
    const int  ret = recv(socket_, CAST(char*, buffer_out_), length_, flags_);
    if (ret == -1) {
        PRINTF_T(_T("recv(): error "));
        PRINTF_T(_T("%s\n"), system_error_name(errno));
    }
    RETURN(ret);  /* return number of bytes read */
} /* recv_fn */


/*winsock2.h*/  /*select.h*/
PUBLIC int  select_fn(                                                     /*F*/
    const int        number_of_fds_,                                       /*-*/
    fd_set*          read_fds_out_,                                        /*-*/
    fd_set*          write_fds_out_,                                       /*-*/
    fd_set*          except_fds_out_,                                      /*-*/
    struct timeval*  timeout_ ) {                                          /*-*/
    GO                                                            (UID(FD6593));
    const int  ret = select(number_of_fds_, read_fds_out_, write_fds_out_,
                            except_fds_out_, timeout_);
    RETURN(ret);
} /* select_fn */


/*winsock2.h*/  /*socket.h*/
PUBLIC int  send_fn(                                                       /*F*/
    const int    socket_,                                                  /*-*/
    const char*  buffer_,                                                  /*-*/
    const int    length_,                                                  /*-*/
    const int    flags_ ) {                                                /*-*/
    GO                                                            (UID(F14AD8));
    bool  is_error = false;
    int   ret      = 0;

    printf(">>> send_fn()\n");;;

#if PLATFORM_LINUX
    /* check if file descriptor is valid (especially not EBADF) */
    if (fcntl(socket_, F_GETFL) == -1) {
        printf("fcntl(): error ");
        printf("%s\n", system_error_name(errno));
        is_error = true;
    }

    {
        /* another way to check if file descriptor is valid: */
        const int  fd = dup(socket_);
        if (fd == -1) {
            printf("dup(): error ");
            printf("%s\n", system_error_name(errno));
            is_error = true;
        }
    }
#endif                                                      /* PLATFORM_LINUX */

    if (!is_error) {
        ret = send(socket_, buffer_, length_, flags_);
    }

    printf("<<< send_fn()\n");;;
    RETURN(ret);
} /* send_fn */

/*winsock2.h*/  /*socket.h*/
PUBLIC int  socket_fn(                                                     /*F*/
    const int  address_family_,                                            /*-*/
    const int  type_,                                                      /*-*/
    const int  protocol_ ) {                                               /*-*/
    GO                                                            (UID(FF1E91));
    const int  ret = socket(address_family_, type_, protocol_);
    RETURN(ret);
} /* socket_fn */


/* -------------------------------------------------------------------------- */


static const uint8_t  NETWORK_ENCRYPTION_KEY[] = {
    0x2E, 0xB6, 0x72, 0x86, 0xEB, 0x95, 0x46, 0xA5,
    0xB2, 0x7A, 0x50, 0xA2, 0x12, 0xF6, 0x52, 0xD0,
    0x2A, 0x2F, 0x14, 0x2C, 0x0B, 0xB0, 0x44, 0xD8,
    0x90, 0x5D, 0x66, 0x13, 0x14, 0x6D, 0xC0, 0x3B,
    0xCC, 0xE7, 0x82, 0xC7, 0x49, 0x90, 0x49, 0xBE,
    0x93, 0x1B, 0x45, 0xA3, 0x9B, 0xF6, 0x1A, 0x2C,
    0x6D, 0x77, 0xDC, 0x4F, 0x5C, 0x43, 0x42, 0x01,
    0xA6, 0x98, 0x06, 0xBE, 0xD9, 0xA9, 0x04, 0x03,
    0xAA, 0x31, 0x64, 0x50, 0x4E, 0xEC, 0x44, 0x59,
    0x80, 0x17, 0xF5, 0xC2, 0xDC, 0x26, 0x03, 0x1F,
    0xEC, 0xEB, 0x22, 0xC3, 0x61, 0x29, 0x4D, 0xAB,
    0x87, 0x89, 0x39, 0xEA, 0x4C, 0xF4, 0x0C, 0x03,
    0xCB, 0xFA, 0x4D, 0xD0, 0x1E, 0x7D, 0x4C, 0x0A,
    0x90, 0x2D, 0x6A, 0x7C, 0x8C, 0x30, 0x23, 0x9F,
    0x54, 0xF5, 0x45, 0x72, 0xCD, 0x52, 0x45, 0xB4,
    0x93, 0xF2, 0x41, 0x72, 0xCF, 0xAA, 0x73, 0xD3
};


static void  _warn(                                                        /*F*/
    chars_t         func_name_,                                            /*-*/
    const int       error_no_,                                             /*-*/
    const uint32_t  src_uid_ ) {                                           /*-*/
    GO                                                            (UID(FB4F7C));
#if PLATFORM_LINUX
    const int  err_no = (0 != error_no_) ? error_no_ : errno;
#endif

#if PLATFORM_WIN32
    const int  err_no = (0 != error_no_) ? error_no_ : WSAGetLastError_win();
#endif

    new_chars_t  msg = formatT(_T("%s() error: %d %s"),
                               func_name_, err_no, net_error_name(err_no));
    WARN(msg, src_uid_);
    freeT(&msg);

    RETURN(NIL);
} /* _warn */


static new_bytes_t  _receive_on_socket(                                    /*F*/
    const int     socket_,                                                 /*-*/
    const size_t  max_message_size_ ) {                                    /*-*/
    GO                                                            (UID(FBB608));
    /* receives data from an open socket */

    const size_t  CHUNK_SIZE = 1024;
    size_t        pos        = 0;
    int           bytes_recv = 0;

    const size_t  max_message_size = (max_message_size_ == 0)
                                     ? SIZE_MAX : max_message_size_;

    /* prepare buffer which holds the complete received message */
    new_bytes_t  reply = { 0, NULL };
    reply.size = CHUNK_SIZE;
    reply.data = MALLOC(reply.size);
    CLEAR_N(reply.data, reply.size);

    /* keep receiving and concatenating data */
    /* to the buffer, until there is no more */
    do {
        {
            /* increase the reply buffer's size if it's */
            /* too small to accept the next chunk       */

            const size_t  grow_by = GREATER(CHUNK_SIZE, CAST(size_t,
                                            CAST(double, pos) * 0.2));

            if (reply.size < (pos + CHUNK_SIZE)) {
                reply.size = pos + grow_by;
                REALLOC(reply.data, reply.size);
            }
        }

        /* receive and append server's reply to the buffer */
#if PLATFORM_LINUX
        bytes_recv = read(socket_, reply.data + pos, CHUNK_SIZE);
        if (bytes_recv > 0)
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
            bytes_recv = recv_fn(socket_, reply.data + pos, CHUNK_SIZE, 0);
        if (bytes_recv != 0 && bytes_recv != SOCKET_ERROR)
#endif                                                      /* PLATFORM_WIN32 */
        {
            pos += bytes_recv;
            if (pos > CAST(size_t, max_message_size)) {
                WARN(_T("Reply too long."), UID(EE0033));
                goto _ret_err;
            }
        }

        /* wait for 100ms and retry if no data has been received yet */
#if PLATFORM_LINUX
        if (pos == 0 && bytes_recv == 0)
#endif
#if PLATFORM_WIN32
            if (pos == 0 && bytes_recv == 0 && bytes_recv != SOCKET_ERROR)
#endif
            {
                sleep_ms(100);
                continue;
            }

        sleep_ms(100);

        {
            /* exit if there is no more data to receive: */
            unsigned long int  bytes_to_read = 0;

#if PLATFORM_LINUX
            const int  result = ioctl(socket_, FIONREAD, &bytes_to_read);
#endif

#if PLATFORM_WIN32
            const int  result =
                ioctlsocket_win(socket_, FIONREAD, &bytes_to_read);
#endif                                                      /* PLATFORM_WIN32 */

            if (bytes_to_read == 0 || result != 0) {
                break;
            }
        }
    } /* do */

#if PLATFORM_LINUX
    while (bytes_recv > 0);
#endif

#if PLATFORM_WIN32
    while (bytes_recv != 0 && bytes_recv != SOCKET_ERROR);
#endif

#if PLATFORM_LINUX
    if (bytes_recv < 0) {
        goto _ret_err;
    }
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    if (bytes_recv == SOCKET_ERROR) {
        goto _ret_err;
    }
#endif                                                      /* PLATFORM_WIN32 */

    if (pos == 0) {
        Bytes_free(&reply);
    } else {
        REALLOC(reply.data, pos);
    }

    reply.size = pos;
    RETURN(reply);

_ret_err:
    Bytes_free(&reply);
    reply.size = 0;
    reply.data = NULL;
    RETURN(reply);
} /* _receive_on_socket */


PUBLIC bool  net_start( const uint32_t  uid_ ) {                           /*F*/
    GO                                                            (UID(F47B30));
    /* Initializes the network subsystem. */
    /* Windows: calls WSAStartup_win()    */
    /* Linux: does nothing                */

#if PLATFORM_LINUX
    UNUSED(uid_);
#endif

#if PLATFORM_WIN32
    WORD_win  version_needed = MAKEWORD_win(2, 2);  /* ...or (1, 1) */

    /* initialize WinSock */
    WSADATA_win  wsa_data;
    CLEAR(wsa_data);
    {
        const int  err_no = WSAStartup_win(version_needed, &wsa_data);
        if (err_no != 0) {
            /*
                Error Meanings:

                WSASYSNOTREADY_win:
                The underlying network subsystem is
                not ready for network communication.

                WSAVERNOTSUPPORTED_win:
                The version of Windows Sockets support requested
                is not provided by this particular
                Windows Sockets implementation.

                WSAEINPROGRESS_win:
                A blocking Windows Sockets 1.1 operation is in progress.

                WSAEPROCLIM_win:
                A limit on the number of tasks supported by the
                Windows Sockets implementation has been reached.

                WSAEFAULT_win:
                The lpWSAData parameter is not a valid pointer.
            */

            new_chars_t  msg = formatT(_T("WSAStartup_win() error: %d - %s"),
                                       err_no, net_error_name(err_no));
            WARN(msg, uid_);
            freeT(&msg);

            RETURN(false);
        }
    }

    /* check the supported version */
    if (2 != LOBYTE_win(wsa_data.wVersion) ||
        2 != HIBYTE_win(wsa_data.wVersion)) {
        WSACleanup_win();
        RETURN(false);
    }

#endif                                                      /* PLATFORM_WIN32 */

    RETURN(true);
} /* net_start */


PUBLIC bool  net_end( const uint32_t  uid_ ) {                             /*F*/
    GO                                                            (UID(FD383B));
    /* Shuts down the network subsystem. */
    /* Windows: calls WSACleanup_win()   */
    /* Linux: does nothing               */

#if PLATFORM_LINUX
    UNUSED(uid_);
#endif

#if PLATFORM_WIN32
    {
        /* terminate use of the Winsock 2 DLL  */
        int  err_no = WSACleanup_win();
        if (err_no != 0 || err_no == SOCKET_ERROR) {
            err_no = WSAGetLastError_win();
            /*
                Error Meanings:

                WSANOTINITIALISED_win
                WSAStartup_win() must be called before using this function.

                WSAENETDOWN_win
                The network subsystem has failed.

                WSAEINPROGRESS_win
                A blocking Windows Sockets 1.1 call is in progress, or the service
                provider is still processing a callback function.
            */
            {
                new_chars_t  msg =
                    formatT(_T("WSACleanup_win() error: %d - %s"),
                            err_no, net_error_name(err_no));
                WARN(msg, uid_);
                freeT(&msg);
            }
            RETURN(false);
        } /* if */
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(true);
} /* net_end */


/* -------------------------------------------------------------------------- */


PUBLIC chars_t  http_status_name( const int  http_code_ ) {                /*F*/
    GO                                                            (UID(FB8B7F));
    /* Based on RFC-2616, HTTP/1.1, June 1999 */

    chars_t  ret = BLANK;

    switch (http_code_) {

            /* Informational 1xx */
            CASE(100, ret = _T("Continue"));
            CASE(101, ret = _T("Switching Protocols"));

            /* Successful 2xx */
            CASE(200, ret = _T("OK"));
            CASE(201, ret = _T("Created"));
            CASE(202, ret = _T("Accepted"));
            CASE(203, ret = _T("Non-Authoritative Information"));
            CASE(204, ret = _T("No Content"));
            CASE(205, ret = _T("Reset Content"));
            CASE(206, ret = _T("Partial Content"));

            /* Redirection 3xx */
            CASE(300, ret = _T("Multiple Choices"));
            CASE(301, ret = _T("Moved Permanently"));
            CASE(302, ret = _T("Found"));
            CASE(303, ret = _T("See Other"));
            CASE(304, ret = _T("Not Modified"));
            CASE(305, ret = _T("Use Proxy"));
            CASE(306, ret = _T("(Unused)"));
            CASE(307, ret = _T("Temporary Redirect"));

            /* Client Error 4xx */
            CASE(400, ret = _T("Bad Request"));
            CASE(401, ret = _T("Unauthorized"));
            CASE(402, ret = _T("Payment Required"));
            CASE(403, ret = _T("Forbidden"));
            CASE(404, ret = _T("Not Found"));
            CASE(405, ret = _T("Method Not Allowed"));
            CASE(406, ret = _T("Not Acceptable"));
            CASE(407, ret = _T("Proxy Authentication Required"));
            CASE(408, ret = _T("Request Timeout"));
            CASE(409, ret = _T("Conflict"));
            CASE(410, ret = _T("Gone"));
            CASE(411, ret = _T("Length Required"));
            CASE(412, ret = _T("Precondition Failed"));
            CASE(413, ret = _T("Request Entity Too Large"));
            CASE(414, ret = _T("Request-URI Too Long"));
            CASE(415, ret = _T("Unsupported Media Type"));
            CASE(416, ret = _T("Requested Range Not Satisfiable"));
            CASE(417, ret = _T("Expectation Failed"));

            /* Server Error 5xx */
            CASE(500, ret = _T("Internal Server Error"));
            CASE(501, ret = _T("Not Implemented"));
            CASE(502, ret = _T("Bad Gateway"));
            CASE(503, ret = _T("Service Unavailable"));
            CASE(504, ret = _T("Gateway Timeout"));
            CASE(505, ret = _T("HTTP Version Not Supported"));

        default:
            ret = _T("(Unknown Http Error)");
    }
    RETURN(ret);
} /* http_status_name */


PUBLIC chars_t  mime_type( chars_t  file_extension_ ) {                    /*F*/
    GO                                                            (UID(F37227));
#define _MIME( FILE_EXTENSION_, MIME_TYPE_ )      \
    if (ends4T(file_extension_, FILE_EXTENSION_,  \
               IGNORE_CASE, SIZE_MAX))            \
    {                   RETURN(MIME_TYPE_); }  /*#*/

    /* TODO: What is the correct or preferred MIME type for JS?         */
    /* _MIME(_T("js"),     _T("application/javascript"));   (RFC 4329) */
    /* _MIME(_T("js"),     _T("text/javascript"));                     */

    /* commonest MIME types: */
    _MIME(_T("htm"),       _T("text/html"));               /* 01 */
    _MIME(_T("html"),      _T("text/html"));               /* 02 */
    _MIME(_T("css"),       _T("text/css"));                /* 03 */
    _MIME(_T("js"),        _T("application/javascript"));  /* 04 */
    _MIME(_T("jpg"),       _T("image/jpeg"));              /* 05 */
    _MIME(_T("jpeg"),      _T("image/jpeg"));              /* 06 */
    _MIME(_T("png"),       _T("image/png"));               /* 07 */
    _MIME(_T("txt"),       _T("text/plain"));              /* 08 */
    _MIME(_T("xml"),       _T("application/xml"));         /* 09 */

    /* other MIME types: */
    _MIME(_T("es"),        _T("application/ecmascript"));
    _MIME(_T("pdf"),       _T("application/pdf"));
    _MIME(_T("xhtml"),     _T("application/xhtml+xml"));
    _MIME(_T("xls"),       _T("application/vnd.ms-excel"));
    _MIME(_T("xlt"),       _T("application/vnd.ms-excel"));
    _MIME(_T("zip"),       _T("application/zip"));

    _MIME(_T("bmp"),       _T("image/x-ms-bmp"));
    _MIME(_T("gif"),       _T("image/gif"));
    _MIME(_T("ico"),       _T("image/x-icon"));
    _MIME(_T("jpe"),       _T("image/jpeg"));
    _MIME(_T("svg"),       _T("image/svg+xml"));
    _MIME(_T("svgz"),      _T("image/svg+xml"));

    _MIME(_T("3gp"),       _T("video/3gpp"));
    _MIME(_T("asf"),       _T("video/x-ms-asf"));
    _MIME(_T("asx"),       _T("video/x-ms-asf"));
    _MIME(_T("avi"),       _T("video/x-msvideo"));
    _MIME(_T("flv"),       _T("video/x-flv"));
    _MIME(_T("mov"),       _T("video/quicktime"));
    _MIME(_T("mp4"),       _T("video/mp4"));
    _MIME(_T("mpe"),       _T("video/mpeg"));
    _MIME(_T("mpeg"),      _T("video/mpeg"));
    _MIME(_T("mpg"),       _T("video/mpeg"));
    _MIME(_T("wm"),        _T("video/x-ms-wm"));
    _MIME(_T("wmv"),       _T("video/x-ms-wmv"));
    _MIME(_T("wmx"),       _T("video/x-ms-wmx"));
    _MIME(_T("wvx"),       _T("video/x-ms-wvx"));

    _MIME(_T("mid"),       _T("audio/midi"));
    _MIME(_T("midi"),      _T("audio/midi"));
    _MIME(_T("ogg"),       _T("audio/ogg"));
    _MIME(_T("wav"),       _T("audio/x-wav"));
    _MIME(_T("wma"),       _T("audio/x-ms-wma"));

    /* text */
    _MIME(_T("323"),       _T("text/h323"));
    _MIME(_T("asc"),       _T("text/plain"));
    _MIME(_T("bib"),       _T("text/x-bibtex"));
    _MIME(_T("boo"),       _T("text/x-boo"));
    _MIME(_T("brf"),       _T("text/plain"));
    _MIME(_T("c"),         _T("text/x-csrc"));
    _MIME(_T("c++"),       _T("text/x-c++src"));
    _MIME(_T("cc"),        _T("text/x-c++src"));
    _MIME(_T("cls"),       _T("text/x-tex"));
    _MIME(_T("cpp"),       _T("text/x-c++src"));
    _MIME(_T("csh"),       _T("text/x-csh"));
    _MIME(_T("csv"),       _T("text/csv"));
    _MIME(_T("cxx"),       _T("text/x-c++src"));
    _MIME(_T("d"),         _T("text/x-dsrc"));
    _MIME(_T("diff"),      _T("text/x-diff"));
    _MIME(_T("etx"),       _T("text/x-setext"));
    _MIME(_T("gcd"),       _T("text/x-pcs-gcd"));
    _MIME(_T("h"),         _T("text/x-chdr"));
    _MIME(_T("h++"),       _T("text/x-c++hdr"));
    _MIME(_T("hh"),        _T("text/x-c++hdr"));
    _MIME(_T("hpp"),       _T("text/x-c++hdr"));
    _MIME(_T("hs"),        _T("text/x-haskell"));
    _MIME(_T("htc"),       _T("text/x-component"));
    _MIME(_T("hxx"),       _T("text/x-c++hdr"));
    _MIME(_T("ics"),       _T("text/calendar"));
    _MIME(_T("icz"),       _T("text/calendar"));
    _MIME(_T("jad"),       _T("text/vnd.sun.j2me.app-descriptor"));
    _MIME(_T("java"),      _T("text/x-java"));
    _MIME(_T("lhs"),       _T("text/x-literate-haskell"));
    _MIME(_T("ltx"),       _T("text/x-tex"));
    _MIME(_T("manifest"),  _T("text/cache-manifest"));
    _MIME(_T("mml"),       _T("text/mathml"));
    _MIME(_T("moc"),       _T("text/x-moc"));
    _MIME(_T("p"),         _T("text/x-pascal"));
    _MIME(_T("pas"),       _T("text/x-pascal"));
    _MIME(_T("patch"),     _T("text/x-diff"));
    _MIME(_T("pl"),        _T("text/x-perl"));
    _MIME(_T("pm"),        _T("text/x-perl"));
    _MIME(_T("pot"),       _T("text/plain"));
    _MIME(_T("py"),        _T("text/x-python"));
    _MIME(_T("rtx"),       _T("text/richtext"));
    _MIME(_T("scala"),     _T("text/x-scala"));
    _MIME(_T("sct"),       _T("text/scriptlet"));
    _MIME(_T("sh"),        _T("text/x-sh"));
    _MIME(_T("shtml"),     _T("text/html"));
    _MIME(_T("sty"),       _T("text/x-tex"));
    _MIME(_T("tcl"),       _T("text/x-tcl"));
    _MIME(_T("tex"),       _T("text/x-tex"));
    _MIME(_T("text"),      _T("text/plain"));
    _MIME(_T("tk"),        _T("text/x-tcl"));
    _MIME(_T("tm"),        _T("text/texmacs"));
    _MIME(_T("ts"),        _T("text/texmacs"));
    _MIME(_T("tsv"),       _T("text/tab-separated-values"));
    _MIME(_T("uls"),       _T("text/iuls"));
    _MIME(_T("vcf"),       _T("text/x-vcard"));
    _MIME(_T("vcs"),       _T("text/x-vcalendar"));
    _MIME(_T("wml"),       _T("text/vnd.wap.wml"));
    _MIME(_T("wmls"),      _T("text/vnd.wap.wmlscript"));
    _MIME(_T("wsc"),       _T("text/scriptlet"));

    /* image */
    _MIME(_T("art"),       _T("image/x-jg"));
    _MIME(_T("cdr"),       _T("image/x-coreldraw"));
    _MIME(_T("cdt"),       _T("image/x-coreldrawtemplate"));
    _MIME(_T("cpt"),       _T("image/x-corelphotopaint"));
    _MIME(_T("cr2"),       _T("image/x-canon-cr2"));
    _MIME(_T("crw"),       _T("image/x-canon-crw"));
    _MIME(_T("djv"),       _T("image/vnd.djvu"));
    _MIME(_T("djvu"),      _T("image/vnd.djvu"));
    _MIME(_T("erf"),       _T("image/x-epson-erf"));
    _MIME(_T("ief"),       _T("image/ief"));
    _MIME(_T("jng"),       _T("image/x-jng"));
    _MIME(_T("nef"),       _T("image/x-nikon-nef"));
    _MIME(_T("orf"),       _T("image/x-olympus-orf"));
    _MIME(_T("pat"),       _T("image/x-coreldrawpattern"));
    _MIME(_T("pbm"),       _T("image/x-portable-bitmap"));
    _MIME(_T("pcx"),       _T("image/pcx"));
    _MIME(_T("pgm"),       _T("image/x-portable-graymap"));
    _MIME(_T("pnm"),       _T("image/x-portable-anymap"));
    _MIME(_T("ppm"),       _T("image/x-portable-pixmap"));
    _MIME(_T("psd"),       _T("image/x-photoshop"));
    _MIME(_T("ras"),       _T("image/x-cmu-raster"));
    _MIME(_T("rgb"),       _T("image/x-rgb"));
    _MIME(_T("tif"),       _T("image/tiff"));
    _MIME(_T("tiff"),      _T("image/tiff"));
    _MIME(_T("wbmp"),      _T("image/vnd.wap.wbmp"));
    _MIME(_T("xbm"),       _T("image/x-xbitmap"));
    _MIME(_T("xpm"),       _T("image/x-xpixmap"));
    _MIME(_T("xwd"),       _T("image/x-xwindowdump"));

    /* application */

    _MIME(_T("docx"),      _T("application/vnd.openxmlformats-officedocument")
          _T(".wordprocessingml.document"));

    _MIME(_T("dotx"),      _T("application/vnd.openxmlformats-officedocument")
          _T(".wordprocessingml.template"));

    _MIME(_T("potx"),      _T("application/vnd.openxmlformats-officedocument")
          _T(".presentationml.template"));

    _MIME(_T("ppsx"),      _T("application/vnd.openxmlformats-officedocument")
          _T(".presentationml.slideshow"));

    _MIME(_T("pptx"),      _T("application/vnd.openxmlformats-officedocument")
          _T(".presentationml.presentation"));

    _MIME(_T("xlsx"),      _T("application/vnd.openxmlformats-officedocument")
          _T(".spreadsheetml.sheet"));

    _MIME(_T("xltx"),      _T("application/vnd.openxmlformats-officedocument")
          _T(".spreadsheetml.template"));

    _MIME(_T("%"),         _T("application/x-trash"));
    _MIME(_T("~"),         _T("application/x-trash"));
    _MIME(_T("7z"),        _T("application/x-7z-compressed"));
    _MIME(_T("abw"),       _T("application/x-abiword"));
    _MIME(_T("ai"),        _T("application/postscript"));
    _MIME(_T("anx"),       _T("application/annodex"));
    _MIME(_T("apk"),       _T("application/vnd.android.package-archive"));
    _MIME(_T("atom"),      _T("application/atom+xml"));
    _MIME(_T("atomcat"),   _T("application/atomcat+xml"));
    _MIME(_T("atomsrv"),   _T("application/atomserv+xml"));
    _MIME(_T("bak"),       _T("application/x-trash"));
    _MIME(_T("bat"),       _T("application/x-msdos-program"));
    _MIME(_T("bcpio"),     _T("application/x-bcpio"));
    _MIME(_T("bin"),       _T("application/octet-stream"));
    _MIME(_T("book"),      _T("application/x-maker"));
    _MIME(_T("cab"),       _T("application/x-cab"));
    _MIME(_T("cap"),       _T("application/cap"));
    _MIME(_T("cat"),       _T("application/vnd.ms-pki.seccat"));
    _MIME(_T("cbr"),       _T("application/x-cbr"));
    _MIME(_T("cbz"),       _T("application/x-cbz"));
    _MIME(_T("cda"),       _T("application/x-cdf"));
    _MIME(_T("cdf"),       _T("application/x-cdf"));
    _MIME(_T("cdy"),       _T("application/vnd.cinderella"));
    _MIME(_T("chrt"),      _T("application/x-kchart"));
    _MIME(_T("class"),     _T("application/java-vm"));
    _MIME(_T("cod"),       _T("application/vnd.rim.cod"));
    _MIME(_T("com"),       _T("application/x-msdos-program"));
    _MIME(_T("cpio"),      _T("application/x-cpio"));
    _MIME(_T("cpt"),       _T("application/mac-compactpro"));
    _MIME(_T("crl"),       _T("application/x-pkcs7-crl"));
    _MIME(_T("crt"),       _T("application/x-x509-ca-cert"));
    _MIME(_T("csh"),       _T("application/x-csh"));
    _MIME(_T("cu"),        _T("application/cu-seeme"));
    _MIME(_T("dat"),       _T("application/x-ns-proxy-autoconfig"));
    _MIME(_T("davmount"),  _T("application/davmount+xml"));
    _MIME(_T("dcr"),       _T("application/x-director"));
    _MIME(_T("deb"),       _T("application/x-debian-package"));
    _MIME(_T("dir"),       _T("application/x-director"));
    _MIME(_T("dll"),       _T("application/x-msdos-program"));
    _MIME(_T("dmg"),       _T("application/x-apple-diskimage"));
    _MIME(_T("dms"),       _T("application/x-dms"));
    _MIME(_T("doc"),       _T("application/msword"));
    _MIME(_T("dot"),       _T("application/msword"));
    _MIME(_T("dvi"),       _T("application/x-dvi"));
    _MIME(_T("dxr"),       _T("application/x-director"));
    _MIME(_T("eps"),       _T("application/postscript"));
    _MIME(_T("eps2"),      _T("application/postscript"));
    _MIME(_T("eps3"),      _T("application/postscript"));
    _MIME(_T("epsf"),      _T("application/postscript"));
    _MIME(_T("epsi"),      _T("application/postscript"));
    _MIME(_T("exe"),       _T("application/x-msdos-program"));
    _MIME(_T("ez"),        _T("application/andrew-inset"));
    _MIME(_T("fb"),        _T("application/x-maker"));
    _MIME(_T("fbdoc"),     _T("application/x-maker"));
    _MIME(_T("fig"),       _T("application/x-xfig"));
    _MIME(_T("fm"),        _T("application/x-maker"));
    _MIME(_T("frame"),     _T("application/x-maker"));
    _MIME(_T("frm"),       _T("application/x-maker"));
    _MIME(_T("gcf"),       _T("application/x-graphing-calculator"));
    _MIME(_T("gf"),        _T("application/x-tex-gf"));
    _MIME(_T("gnumeric"),  _T("application/x-gnumeric"));
    _MIME(_T("gsf"),       _T("application/x-font"));
    _MIME(_T("gtar"),      _T("application/x-gtar"));
    _MIME(_T("hdf"),       _T("application/x-hdf"));
    _MIME(_T("hqx"),       _T("application/mac-binhex40"));
    _MIME(_T("hta"),       _T("application/hta"));
    _MIME(_T("ica"),       _T("application/x-ica"));
    _MIME(_T("iii"),       _T("application/x-iphone"));
    _MIME(_T("info"),      _T("application/x-info"));
    _MIME(_T("ins"),       _T("application/x-internet-signup"));
    _MIME(_T("iso"),       _T("application/x-iso9660-image"));
    _MIME(_T("isp"),       _T("application/x-internet-signup"));
    _MIME(_T("jam"),       _T("application/x-jam"));
    _MIME(_T("jar"),       _T("application/java-archive"));
    _MIME(_T("jmz"),       _T("application/x-jmol"));
    _MIME(_T("jnlp"),      _T("application/x-java-jnlp-file"));
    _MIME(_T("key"),       _T("application/pgp-keys"));
    _MIME(_T("kil"),       _T("application/x-killustrator"));
    _MIME(_T("kml"),       _T("application/vnd.google-earth.kml+xml"));
    _MIME(_T("kmz"),       _T("application/vnd.google-earth.kmz"));
    _MIME(_T("kpr"),       _T("application/x-kpresenter"));
    _MIME(_T("kpt"),       _T("application/x-kpresenter"));
    _MIME(_T("ksp"),       _T("application/x-kspread"));
    _MIME(_T("kwd"),       _T("application/x-kword"));
    _MIME(_T("kwt"),       _T("application/x-kword"));
    _MIME(_T("latex"),     _T("application/x-latex"));
    _MIME(_T("lha"),       _T("application/x-lha"));
    _MIME(_T("lin"),       _T("application/bbolin"));
    _MIME(_T("lyx"),       _T("application/x-lyx"));
    _MIME(_T("lzh"),       _T("application/x-lzh"));
    _MIME(_T("lzx"),       _T("application/x-lzx"));
    _MIME(_T("m3g"),       _T("application/m3g"));
    _MIME(_T("maker"),     _T("application/x-maker"));
    _MIME(_T("man"),       _T("application/x-troff-man"));
    _MIME(_T("mdb"),       _T("application/msaccess"));
    _MIME(_T("me"),        _T("application/x-troff-me"));
    _MIME(_T("mif"),       _T("application/x-mif"));
    _MIME(_T("mm"),        _T("application/x-freemind"));
    _MIME(_T("mmf"),       _T("application/vnd.smaf"));
    _MIME(_T("ms"),        _T("application/x-troff-ms"));
    _MIME(_T("msi"),       _T("application/x-msi"));
    _MIME(_T("mxf"),       _T("application/mxf"));
    _MIME(_T("nb"),        _T("application/mathematica"));
    _MIME(_T("nbp"),       _T("application/mathematica"));
    _MIME(_T("nc"),        _T("application/x-netcdf"));
    _MIME(_T("nwc"),       _T("application/x-nwc"));
    _MIME(_T("o"),         _T("application/x-object"));
    _MIME(_T("oda"),       _T("application/oda"));
    _MIME(_T("ogx"),       _T("application/ogg"));
    _MIME(_T("old"),       _T("application/x-trash"));
    _MIME(_T("oza"),       _T("application/x-oz-application"));
    _MIME(_T("p7r"),       _T("application/x-pkcs7-certreqresp"));
    _MIME(_T("pac"),       _T("application/x-ns-proxy-autoconfig"));
    _MIME(_T("pcap"),      _T("application/cap"));
    _MIME(_T("pcf"),       _T("application/x-font"));
    _MIME(_T("pcf.Z"),     _T("application/x-font"));
    _MIME(_T("pfa"),       _T("application/x-font"));
    _MIME(_T("pfb"),       _T("application/x-font"));
    _MIME(_T("pgn"),       _T("application/x-mfc_chess-pgn"));
    _MIME(_T("pgp"),       _T("application/pgp-signature"));
    _MIME(_T("php"),       _T("application/x-httpd-php"));
    _MIME(_T("php3"),      _T("application/x-httpd-php3"));
    _MIME(_T("php3p"),     _T("application/x-httpd-php3-preprocessed"));
    _MIME(_T("php4"),      _T("application/x-httpd-php4"));
    _MIME(_T("php5"),      _T("application/x-httpd-php5"));
    _MIME(_T("phps"),      _T("application/x-httpd-php-source"));
    _MIME(_T("pht"),       _T("application/x-httpd-php"));
    _MIME(_T("phtml"),     _T("application/x-httpd-php"));
    _MIME(_T("pk"),        _T("application/x-tex-pk"));
    _MIME(_T("pps"),       _T("application/vnd.ms-powerpoint"));
    _MIME(_T("ppt"),       _T("application/vnd.ms-powerpoint"));
    _MIME(_T("prf"),       _T("application/pics-rules"));
    _MIME(_T("ps"),        _T("application/postscript"));
    _MIME(_T("pyc"),       _T("application/x-python-code"));
    _MIME(_T("pyo"),       _T("application/x-python-code"));
    _MIME(_T("qgs"),       _T("application/x-qgis"));
    _MIME(_T("qtl"),       _T("application/x-quicktimeplayer"));
    _MIME(_T("rar"),       _T("application/rar"));
    _MIME(_T("rb"),        _T("application/x-ruby"));
    _MIME(_T("rdf"),       _T("application/rdf+xml"));
    _MIME(_T("rhtml"),     _T("application/x-httpd-eruby"));
    _MIME(_T("roff"),      _T("application/x-troff"));
    _MIME(_T("rpm"),       _T("application/x-redhat-package-manager"));
    _MIME(_T("rss"),       _T("application/rss+xml"));
    _MIME(_T("rtf"),       _T("application/rtf"));
    _MIME(_T("scr"),       _T("application/x-silverlight"));
    _MIME(_T("sda"),       _T("application/vnd.stardivision.draw"));
    _MIME(_T("sdc"),       _T("application/vnd.stardivision.calc"));
    _MIME(_T("sdd"),       _T("application/vnd.stardivision.impress"));
    _MIME(_T("sdf"),       _T("application/vnd.stardivision.math"));
    _MIME(_T("sds"),       _T("application/vnd.stardivision.chart"));
    _MIME(_T("sdw"),       _T("application/vnd.stardivision.writer"));
    _MIME(_T("ser"),       _T("application/java-serialized-object"));
    _MIME(_T("sgf"),       _T("application/x-go-sgf"));
    _MIME(_T("sgl"),       _T("application/vnd.stardivision.writer-global"));
    _MIME(_T("sh"),        _T("application/x-sh"));
    _MIME(_T("shar"),      _T("application/x-shar"));
    _MIME(_T("shp"),       _T("application/x-qgis"));
    _MIME(_T("shx"),       _T("application/x-qgis"));
    _MIME(_T("sik"),       _T("application/x-trash"));
    _MIME(_T("sis"),       _T("application/vnd.symbian.install"));
    _MIME(_T("sit"),       _T("application/x-stuffit"));
    _MIME(_T("sitx"),      _T("application/x-stuffit"));
    _MIME(_T("skd"),       _T("application/x-koan"));
    _MIME(_T("skm"),       _T("application/x-koan"));
    _MIME(_T("skp"),       _T("application/x-koan"));
    _MIME(_T("skt"),       _T("application/x-koan"));
    _MIME(_T("smi"),       _T("application/smil"));
    _MIME(_T("smil"),      _T("application/smil"));
    _MIME(_T("spl"),       _T("application/futuresplash"));
    _MIME(_T("spl"),       _T("application/x-futuresplash"));
    _MIME(_T("src"),       _T("application/x-wais-source"));
    _MIME(_T("stc"),       _T("application/vnd.sun.xml.calc.template"));
    _MIME(_T("std"),       _T("application/vnd.sun.xml.draw.template"));
    _MIME(_T("sti"),       _T("application/vnd.sun.xml.impress.template"));
    _MIME(_T("stl"),       _T("application/vnd.ms-pki.stl"));
    _MIME(_T("stw"),       _T("application/vnd.sun.xml.writer.template"));
    _MIME(_T("sv4cpio"),   _T("application/x-sv4cpio"));
    _MIME(_T("sv4crc"),    _T("application/x-sv4crc"));
    _MIME(_T("swf"),       _T("application/x-shockwave-flash"));
    _MIME(_T("swfl"),      _T("application/x-shockwave-flash"));
    _MIME(_T("sxc"),       _T("application/vnd.sun.xml.calc"));
    _MIME(_T("sxd"),       _T("application/vnd.sun.xml.draw"));
    _MIME(_T("sxg"),       _T("application/vnd.sun.xml.writer.global"));
    _MIME(_T("sxi"),       _T("application/vnd.sun.xml.impress"));
    _MIME(_T("sxm"),       _T("application/vnd.sun.xml.math"));
    _MIME(_T("sxw"),       _T("application/vnd.sun.xml.writer"));
    _MIME(_T("t"),         _T("application/x-troff"));
    _MIME(_T("tar"),       _T("application/x-tar"));
    _MIME(_T("taz"),       _T("application/x-gtar"));
    _MIME(_T("tcl"),       _T("application/x-tcl"));
    _MIME(_T("texi"),      _T("application/x-texinfo"));
    _MIME(_T("texinfo"),   _T("application/x-texinfo"));
    _MIME(_T("tgz"),       _T("application/x-gtar"));
    _MIME(_T("torrent"),   _T("application/x-bittorrent"));
    _MIME(_T("tr"),        _T("application/x-troff"));
    _MIME(_T("tsp"),       _T("application/dsptype"));
    _MIME(_T("udeb"),      _T("application/x-debian-package"));
    _MIME(_T("ustar"),     _T("application/x-ustar"));
    _MIME(_T("vcd"),       _T("application/x-cdlink"));
    _MIME(_T("vsd"),       _T("application/vnd.visio"));
    _MIME(_T("wad"),       _T("application/x-doom"));
    _MIME(_T("wbxml"),     _T("application/vnd.wap.wbxml"));
    _MIME(_T("wk"),        _T("application/x-123"));
    _MIME(_T("wmd"),       _T("application/x-ms-wmd"));
    _MIME(_T("wmlc"),      _T("application/vnd.wap.wmlc"));
    _MIME(_T("wmlsc"),     _T("application/vnd.wap.wmlscriptc"));
    _MIME(_T("wmz"),       _T("application/x-ms-wmz"));
    _MIME(_T("wp5"),       _T("application/vnd.wordperfect5.1"));
    _MIME(_T("wpd"),       _T("application/vnd.wordperfect"));
    _MIME(_T("wz"),        _T("application/x-wingz"));
    _MIME(_T("xcf"),       _T("application/x-xcf"));
    _MIME(_T("xht"),       _T("application/xhtml+xml"));
    _MIME(_T("xlb"),       _T("application/vnd.ms-excel"));
    _MIME(_T("xpi"),       _T("application/x-xpinstall"));
    _MIME(_T("xsd"),       _T("application/xml"));
    _MIME(_T("xsl"),       _T("application/xml"));
    _MIME(_T("xspf"),      _T("application/xspf+xml"));
    _MIME(_T("xul"),       _T("application/vnd.mozilla.xul+xml"));

    _MIME(_T("db"),       _T("application/vnd.oasis.opendocument")
          _T(".database"));

    _MIME(_T("dc"),       _T("application/vnd.oasis.opendocument")
          _T(".chart"));

    _MIME(_T("odf"),       _T("application/vnd.oasis.opendocument")
          _T(".formula"));

    _MIME(_T("odg"),       _T("application/vnd.oasis.opendocument")
          _T(".graphics"));

    _MIME(_T("odi"),       _T("application/vnd.oasis.opendocument")
          _T(".image"));

    _MIME(_T("odm"),       _T("application/vnd.oasis.opendocument")
          _T(".text-master"));

    _MIME(_T("odp"),       _T("application/vnd.oasis.opendocument")
          _T(".presentation"));

    _MIME(_T("ods"),       _T("application/vnd.oasis.opendocument")
          _T(".spreadsheet"));

    _MIME(_T("odt"),       _T("application/vnd.oasis.opendocument")
          _T(".text"));

    _MIME(_T("otg"),       _T("application/vnd.oasis.opendocument")
          _T(".graphics-template"));

    _MIME(_T("oth"),       _T("application/vnd.oasis.opendocument")
          _T(".text-web"));

    _MIME(_T("otp"),       _T("application/vnd.oasis.opendocument")
          _T(".presentation-template"));

    _MIME(_T("ots"),       _T("application/vnd.oasis.opendocument")
          _T(".spreadsheet-template"));

    _MIME(_T("ott"),       _T("application/vnd.oasis.opendocument")
          _T(".text-template"));

    /* audio */
    _MIME(_T("aif"),       _T("audio/x-aiff"));
    _MIME(_T("aifc"),      _T("audio/x-aiff"));
    _MIME(_T("aiff"),      _T("audio/x-aiff"));
    _MIME(_T("amr"),       _T("audio/amr"));
    _MIME(_T("au"),        _T("audio/basic"));
    _MIME(_T("awb"),       _T("audio/amr-wb"));
    _MIME(_T("axa"),       _T("audio/annodex"));
    _MIME(_T("flac"),      _T("audio/flac"));
    _MIME(_T("gsm"),       _T("audio/x-gsm"));
    _MIME(_T("kar"),       _T("audio/midi"));
    _MIME(_T("m3u"),       _T("audio/mpegurl"));
    _MIME(_T("m3u"),       _T("audio/x-mpegurl"));
    _MIME(_T("m4a"),       _T("audio/mpeg"));
    _MIME(_T("mp2"),       _T("audio/mpeg"));
    _MIME(_T("mp3"),       _T("audio/mpeg"));
    _MIME(_T("mpega"),     _T("audio/mpeg"));
    _MIME(_T("mpga"),      _T("audio/mpeg"));
    _MIME(_T("oga"),       _T("audio/ogg"));
    _MIME(_T("pls"),       _T("audio/x-scpls"));
    _MIME(_T("ra"),        _T("audio/x-pn-realaudio"));
    _MIME(_T("ra"),        _T("audio/x-realaudio"));
    _MIME(_T("ram"),       _T("audio/x-pn-realaudio"));
    _MIME(_T("rm"),        _T("audio/x-pn-realaudio"));
    _MIME(_T("sd2"),       _T("audio/x-sd2"));
    _MIME(_T("sid"),       _T("audio/prs.sid"));
    _MIME(_T("snd"),       _T("audio/basic"));
    _MIME(_T("spx"),       _T("audio/ogg"));
    _MIME(_T("wax"),       _T("audio/x-ms-wax"));

    /* video */
    _MIME(_T("axv"),       _T("video/annodex"));
    _MIME(_T("dif"),       _T("video/dv"));
    _MIME(_T("dl"),        _T("video/dl"));
    _MIME(_T("dv"),        _T("video/dv"));
    _MIME(_T("fli"),       _T("video/fli"));
    _MIME(_T("gl"),        _T("video/gl"));
    _MIME(_T("lsf"),       _T("video/x-la-asf"));
    _MIME(_T("lsx"),       _T("video/x-la-asf"));
    _MIME(_T("mkv"),       _T("video/x-matroska"));
    _MIME(_T("mng"),       _T("video/x-mng"));
    _MIME(_T("movie"),     _T("video/x-sgi-movie"));
    _MIME(_T("mpv"),       _T("video/x-matroska"));
    _MIME(_T("mxu"),       _T("video/vnd.mpegurl"));
    _MIME(_T("ogv"),       _T("video/ogg"));
    _MIME(_T("qt"),        _T("video/quicktime"));

    /* model */
    _MIME(_T("iges"),      _T("model/iges"));
    _MIME(_T("igs"),       _T("model/iges"));
    _MIME(_T("mesh"),      _T("model/mesh"));
    _MIME(_T("msh"),       _T("model/mesh"));
    _MIME(_T("silo"),      _T("model/mesh"));
    _MIME(_T("wrl"),       _T("model/vrml"));
    _MIME(_T("vrml"),      _T("model/vrml"));
    _MIME(_T("x3db"),      _T("model/x3d+binary"));
    _MIME(_T("x3dv"),      _T("model/x3d+vrml"));
    _MIME(_T("x3d"),       _T("model/x3d+xml"));

    /* world */
    _MIME(_T("vrm"),       _T("x-world/x-vrml"));
    _MIME(_T("vrml"),      _T("x-world/x-vrml"));
    _MIME(_T("wrl"),       _T("x-world/x-vrml"));

    /* etc */
    _MIME(_T("eml"),       _T("message/rfc822"));
    _MIME(_T("ice"),       _T("x-conference/x-cooltalk"));
    _MIME(_T("sisx"),      _T("x-epoc/x-sisx-app"));

    /* chemical */
    _MIME(_T("smi"),       _T("#chemical/x-daylight-smiles"));
    _MIME(_T("mif"),       _T("#chemical/x-mif"));
    _MIME(_T("alc"),       _T("chemical/x-alchemy"));
    _MIME(_T("cache"),     _T("chemical/x-cache"));
    _MIME(_T("cac"),       _T("chemical/x-cache"));
    _MIME(_T("csf"),       _T("chemical/x-cache-csf"));
    _MIME(_T("cbin"),      _T("chemical/x-cactvs-binary"));
    _MIME(_T("ctab"),      _T("chemical/x-cactvs-binary"));
    _MIME(_T("cascii"),    _T("chemical/x-cactvs-binary"));
    _MIME(_T("cdx"),       _T("chemical/x-cdx"));
    _MIME(_T("cer"),       _T("chemical/x-cerius"));
    _MIME(_T("c3d"),       _T("chemical/x-chem3d"));
    _MIME(_T("chm"),       _T("chemical/x-chemdraw"));
    _MIME(_T("cif"),       _T("chemical/x-cif"));
    _MIME(_T("cmdf"),      _T("chemical/x-cmdf"));
    _MIME(_T("cml"),       _T("chemical/x-cml"));
    _MIME(_T("cpa"),       _T("chemical/x-compass"));
    _MIME(_T("bsd"),       _T("chemical/x-crossfire"));
    _MIME(_T("csm"),       _T("chemical/x-csml"));
    _MIME(_T("csml"),      _T("chemical/x-csml"));
    _MIME(_T("ctx"),       _T("chemical/x-ctx"));
    _MIME(_T("cef"),       _T("chemical/x-cxf"));
    _MIME(_T("cxf"),       _T("chemical/x-cxf"));
    _MIME(_T("embl"),      _T("chemical/x-embl-dl-nucleotide"));
    _MIME(_T("emb"),       _T("chemical/x-embl-dl-nucleotide"));
    _MIME(_T("pc"),       _T("chemical/x-galactic-pc"));
    _MIME(_T("inp"),       _T("chemical/x-gamess-input"));
    _MIME(_T("gam"),       _T("chemical/x-gamess-input"));
    _MIME(_T("gamin"),     _T("chemical/x-gamess-input"));
    _MIME(_T("fch"),       _T("chemical/x-gaussian-checkpoint"));
    _MIME(_T("fchk"),      _T("chemical/x-gaussian-checkpoint"));
    _MIME(_T("cub"),       _T("chemical/x-gaussian-cube"));
    _MIME(_T("gau"),       _T("chemical/x-gaussian-input"));
    _MIME(_T("gjc"),       _T("chemical/x-gaussian-input"));
    _MIME(_T("gjf"),       _T("chemical/x-gaussian-input"));
    _MIME(_T("gal"),       _T("chemical/x-gaussian-log"));
    _MIME(_T("gcg"),       _T("chemical/x-gcg8-sequence"));
    _MIME(_T("gen"),       _T("chemical/x-genbank"));
    _MIME(_T("hin"),       _T("chemical/x-hin"));
    _MIME(_T("ist"),       _T("chemical/x-isostar"));
    _MIME(_T("istr"),      _T("chemical/x-isostar"));
    _MIME(_T("dx"),        _T("chemical/x-jcamp-dx"));
    _MIME(_T("jdx"),       _T("chemical/x-jcamp-dx"));
    _MIME(_T("kin"),       _T("chemical/x-kinemage"));
    _MIME(_T("mcm"),       _T("chemical/x-macmolecule"));
    _MIME(_T("mmod"),      _T("chemical/x-macromodel-input"));
    _MIME(_T("mmd"),       _T("chemical/x-macromodel-input"));
    _MIME(_T("mol"),       _T("chemical/x-mdl-molfile"));
    _MIME(_T("rd"),        _T("chemical/x-mdl-rdfile"));
    _MIME(_T("rxn"),       _T("chemical/x-mdl-rxnfile"));
    _MIME(_T("sdf"),       _T("chemical/x-mdl-sdfile"));
    _MIME(_T("sd"),        _T("chemical/x-mdl-sdfile"));
    _MIME(_T("tgf"),       _T("chemical/x-mdl-tgf"));
    _MIME(_T("mcif"),      _T("chemical/x-mmcif"));
    _MIME(_T("mol2"),      _T("chemical/x-mol2"));
    _MIME(_T("b"),         _T("chemical/x-molconn-Z"));
    _MIME(_T("gpt"),       _T("chemical/x-mopac-graph"));
    _MIME(_T("mopcrt"),    _T("chemical/x-mopac-input"));
    _MIME(_T("mpc"),       _T("chemical/x-mopac-input"));
    _MIME(_T("mop"),       _T("chemical/x-mopac-input"));
    _MIME(_T("zmt"),       _T("chemical/x-mopac-input"));
    _MIME(_T("moo"),       _T("chemical/x-mopac-out"));
    _MIME(_T("mvb"),       _T("chemical/x-mopac-vib"));
    _MIME(_T("asn"),       _T("chemical/x-ncbi-asn1"));
    _MIME(_T("ent"),       _T("chemical/x-ncbi-asn1-ascii"));
    _MIME(_T("prt"),       _T("chemical/x-ncbi-asn1-ascii"));
    _MIME(_T("aso"),       _T("chemical/x-ncbi-asn1-binary"));
    _MIME(_T("val"),       _T("chemical/x-ncbi-asn1-binary"));
    _MIME(_T("asn"),       _T("chemical/x-ncbi-asn1-spec"));
    _MIME(_T("pdb"),       _T("chemical/x-pdb"));
    _MIME(_T("ent"),       _T("chemical/x-pdb"));
    _MIME(_T("ros"),       _T("chemical/x-rosdal"));
    _MIME(_T("sw"),        _T("chemical/x-swissprot"));
    _MIME(_T("vms"),       _T("chemical/x-vamas-iso14976"));
    _MIME(_T("vmd"),       _T("chemical/x-vmd"));
    _MIME(_T("xtel"),      _T("chemical/x-xtel"));
    _MIME(_T("xyz"),       _T("chemical/x-xyz"));
#undef _MIME

    RETURN(_T(""));
} /* mime_type */


PUBLIC chars_t  net_error_name( const int  error_no_ ) {                   /*F*/
    GO                                                            (UID(FD7B0B));
    chars_t  ret = BLANK;

#if PLATFORM_LINUX
    const int  err_no = (0 != error_no_) ? error_no_ : errno;
    ret = system_error_name(err_no);

#elif PLATFORM_WIN32
    const int  err_no = (0 != error_no_) ? error_no_ : WSAGetLastError_win();
    switch (err_no) {
            CASE_TO_TEXT(ERROR_SUCCESS_win,              ret);
            CASE_TO_TEXT(WSA_E_CANCELLED_win,            ret);
            CASE_TO_TEXT(WSA_E_NO_MORE_win,              ret);
            CASE_TO_TEXT(WSA_QOS_ADMISSION_FAILURE_win,  ret);
            CASE_TO_TEXT(WSA_QOS_BAD_OBJECT_win,         ret);
            CASE_TO_TEXT(WSA_QOS_BAD_STYLE_win,          ret);
            CASE_TO_TEXT(WSA_QOS_EFILTERCOUNT_win,       ret);
            CASE_TO_TEXT(WSA_QOS_EFILTERSTYLE_win,       ret);
            CASE_TO_TEXT(WSA_QOS_EFILTERTYPE_win,        ret);
            CASE_TO_TEXT(WSA_QOS_EFLOWCOUNT_win,         ret);
            CASE_TO_TEXT(WSA_QOS_EFLOWDESC_win,          ret);
            CASE_TO_TEXT(WSA_QOS_EFLOWSPEC_win,          ret);
            CASE_TO_TEXT(WSA_QOS_EOBJLENGTH_win,         ret);
            CASE_TO_TEXT(WSA_QOS_EPOLICYOBJ_win,         ret);
            CASE_TO_TEXT(WSA_QOS_EPROVSPECBUF_win,       ret);
            CASE_TO_TEXT(WSA_QOS_EPSFILTERSPEC_win,      ret);
            CASE_TO_TEXT(WSA_QOS_EPSFLOWSPEC_win,        ret);
            CASE_TO_TEXT(WSA_QOS_ESDMODEOBJ_win,         ret);
            CASE_TO_TEXT(WSA_QOS_ESERVICETYPE_win,       ret);
            CASE_TO_TEXT(WSA_QOS_ESHAPERATEOBJ_win,      ret);
            CASE_TO_TEXT(WSA_QOS_GENERIC_ERROR_win,      ret);
            CASE_TO_TEXT(WSA_QOS_NO_RECEIVERS_win,       ret);
            CASE_TO_TEXT(WSA_QOS_NO_SENDERS_win,         ret);
            CASE_TO_TEXT(WSA_QOS_POLICY_FAILURE_win,     ret);
            CASE_TO_TEXT(WSA_QOS_RECEIVERS_win,          ret);
            CASE_TO_TEXT(WSA_QOS_REQUEST_CONFIRMED_win,  ret);
            CASE_TO_TEXT(WSA_QOS_RESERVED_PETYPE_win,    ret);
            CASE_TO_TEXT(WSA_QOS_SENDERS_win,            ret);
            CASE_TO_TEXT(WSA_QOS_TRAFFIC_CTRL_ERROR_win, ret);
            CASE_TO_TEXT(WSAEACCES_win,                  ret);
            CASE_TO_TEXT(WSAEADDRINUSE_win,              ret);
            CASE_TO_TEXT(WSAEADDRNOTAVAIL_win,           ret);
            CASE_TO_TEXT(WSAEAFNOSUPPORT_win,            ret);
            CASE_TO_TEXT(WSAEALREADY_win,                ret);
            CASE_TO_TEXT(WSAEBADF_win,                   ret);
            CASE_TO_TEXT(WSAECANCELLED_win,              ret);
            CASE_TO_TEXT(WSAECONNABORTED_win,            ret);
            CASE_TO_TEXT(WSAECONNREFUSED_win,            ret);
            CASE_TO_TEXT(WSAECONNRESET_win,              ret);
            CASE_TO_TEXT(WSAEDESTADDRREQ_win,            ret);
            CASE_TO_TEXT(WSAEDISCON_win,                 ret);
            CASE_TO_TEXT(WSAEDQUOT_win,                  ret);
            CASE_TO_TEXT(WSAEFAULT_win,                  ret);
            CASE_TO_TEXT(WSAEHOSTDOWN_win,               ret);
            CASE_TO_TEXT(WSAEHOSTUNREACH_win,            ret);
            CASE_TO_TEXT(WSAEINPROGRESS_win,             ret);
            CASE_TO_TEXT(WSAEINTR_win,                   ret);
            CASE_TO_TEXT(WSAEINVAL_win,                  ret);
            CASE_TO_TEXT(WSAEINVALIDPROCTABLE_win,       ret);
            CASE_TO_TEXT(WSAEINVALIDPROVIDER_win,        ret);
            CASE_TO_TEXT(WSAEISCONN_win,                 ret);
            CASE_TO_TEXT(WSAELOOP_win,                   ret);
            CASE_TO_TEXT(WSAEMFILE_win,                  ret);
            CASE_TO_TEXT(WSAEMSGSIZE_win,                ret);
            CASE_TO_TEXT(WSAENAMETOOLONG_win,            ret);
            CASE_TO_TEXT(WSAENETDOWN_win,                ret);
            CASE_TO_TEXT(WSAENETRESET_win,               ret);
            CASE_TO_TEXT(WSAENETUNREACH_win,             ret);
            CASE_TO_TEXT(WSAENOBUFS_win,                 ret);
            CASE_TO_TEXT(WSAENOMORE_win,                 ret);
            CASE_TO_TEXT(WSAENOPROTOOPT_win,             ret);
            CASE_TO_TEXT(WSAENOTCONN_win,                ret);
            CASE_TO_TEXT(WSAENOTEMPTY_win,               ret);
            CASE_TO_TEXT(WSAENOTSOCK_win,                ret);
            CASE_TO_TEXT(WSAEOPNOTSUPP_win,              ret);
            CASE_TO_TEXT(WSAEPFNOSUPPORT_win,            ret);
            CASE_TO_TEXT(WSAEPROCLIM_win,                ret);
            CASE_TO_TEXT(WSAEPROTONOSUPPORT_win,         ret);
            CASE_TO_TEXT(WSAEPROTOTYPE_win,              ret);
            CASE_TO_TEXT(WSAEPROVIDERFAILEDINIT_win,     ret);
            CASE_TO_TEXT(WSAEREFUSED_win,                ret);
            CASE_TO_TEXT(WSAEREMOTE_win,                 ret);
            CASE_TO_TEXT(WSAESHUTDOWN_win,               ret);
            CASE_TO_TEXT(WSAESOCKTNOSUPPORT_win,         ret);
            CASE_TO_TEXT(WSAESTALE_win,                  ret);
            CASE_TO_TEXT(WSAETIMEDOUT_win,               ret);
            CASE_TO_TEXT(WSAETOOMANYREFS_win,            ret);
            CASE_TO_TEXT(WSAEUSERS_win,                  ret);
            CASE_TO_TEXT(WSAEWOULDBLOCK_win,             ret);
            CASE_TO_TEXT(WSAHOST_NOT_FOUND_win,          ret);
            CASE_TO_TEXT(WSANO_DATA_win,                 ret);
            CASE_TO_TEXT(WSANO_RECOVERY_win,             ret);
            CASE_TO_TEXT(WSANOTINITIALISED_win,          ret);
            CASE_TO_TEXT(WSASERVICE_NOT_FOUND_win,       ret);
            CASE_TO_TEXT(WSASYSCALLFAILURE_win,          ret);
            CASE_TO_TEXT(WSASYSNOTREADY_win,             ret);
            CASE_TO_TEXT(WSATRY_AGAIN_win,               ret);
            CASE_TO_TEXT(WSATYPE_NOT_FOUND_win,          ret);
            CASE_TO_TEXT(WSAVERNOTSUPPORTED_win,         ret);
#if defined WSA_QOS_EUNKOWNPSOBJ_win
            CASE_TO_TEXT(WSA_QOS_EUNKOWNPSOBJ_win,       ret);
#endif
        default:
            ret = _T("(Unknown Network Error)");
    } /* switch */

#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* net_error_name()*/


PUBLIC struct in_addr  ip_address( chars_t  ip_address_or_host_name_ ) {   /*F*/
    GO                                                            (UID(F381D1));
    /* returns an IP address given an IP string or host name.   */
    /* If the address can not be found, sets all fields in      */
    /* returned struct to 0.                                    */
    /* The network sockets code is common to Windows and Linux. */
    static struct in_addr  ret;
    new_bchars_t           char_addr = NULL;
    struct hostent*        host_info = NULL;

    {
        /* trim and convert address to an upper-case (char) string */
        new_chars_t  address = T_chars(ip_address_or_host_name_);
        upper_in_T(address);
        trim_in_T(address);
        char_addr = to_utf8T(address);
        freeT(&address);
    }

    /* try 000.000.000.000 address format */
    CLEAR(ret);
    ret.s_addr = inet_addr_fn(char_addr);

    if (ret.s_addr != CAST(unsigned, INADDR_NONE)) {
        goto _ret;
    }

    /* try HOSTNAME address format */
    CLEAR(ret);
    host_info = gethostbyname_fn(char_addr);
    if (host_info != NULL) {
        ret = *((struct in_addr*) *host_info->h_addr_list);
        goto _ret;
    }

    /* if both don't succeed, issue a warning and return zeroed address */
    CLEAR(ret);
    if (host_info == NULL) {
        new_chars_t  msg =
            formatT(_T("ip_address() error: ")
                    _T("%s (ip_address_or_host_name_='%s'"),
                    net_error_name(0), ip_address_or_host_name_);
        WARN(msg, UID(EE63DF));
        freeT(&msg);
    }

_ret:
    freeA(&char_addr);
    RETURN(ret);
} /* ip_address */


PUBLIC new_chars_t  net_text_request(                                      /*F*/
    chars_t         request_,                                              /*-*/
    chars_t         server_name_or_ip_,                                    /*-*/
    const uint32_t  port_,                                                 /*-*/
    const size_t    max_message_len_ ) {                                   /*-*/
    GO                                                            (UID(F55232));
    new_bytes_t  request;
    request.size = lenT(request_) + 1;  /* +1 for \0 */

    if (request.size > max_message_len_) {
        WARN(_T("Request too long."), UID(EA6587));
        RETURN(NULL);
    }

#if defined UNICODE || defined _UNICODE
    request.data = CAST(uint8_t*, to_utf8T(request_));
    *(request.data + request.size - 1) = '\0';
#else                                                  /* UNICODE || _UNICODE */
    request.data = CAST(void*, to_utf8T(request_));
#endif                                               /* !UNICODE && !_UNICODE */

    {
        /* send request to server */
        new_bytes_t  reply = net_encrypted_request(request, server_name_or_ip_,
                             port_, max_message_len_);

        /* convert reply to string */
        const bool   is_wide = is_wide_n(reply.data, reply.size);
        new_chars_t  ret     = NULL;

        if (is_wide) {
            ret = T_wchars_n(CAST(const wchar_t*, reply.data),
                             reply.size / sizeof(char_t));
        } else {
            ret = T_bchars_n(CAST(const char*, reply.data), reply.size);
        }

        if (reply.data) {
            Bytes_free(&reply);
        }

        RETURN(ret);  /* return the reply */
    }
} /* net_text_request */


PUBLIC new_bytes_t  net_encrypted_request(                                 /*F*/
    const bytes_t   request_,                                              /*-*/
    chars_t         server_name_or_ip_,                                    /*-*/
    const uint32_t  port_,                                                 /*-*/
    const size_t    max_message_size_ ) {                                  /*-*/
    GO                                                            (UID(FAFFBA));
    const unsigned long  begin_time      = uptime_ms();
    int                  sock            = 0;
    new_bytes_t          encrypted_reply = { 0, NULL };
    new_bytes_t          key             = { 0, NULL };

    key = Bytes_init(NETWORK_ENCRYPTION_KEY, sizeof(NETWORK_ENCRYPTION_KEY));

_connect:
    /* create client socket */
#if PLATFORM_LINUX
    sock = socket_fn(AF_INET, SOCK_STREAM, 0);
#endif

#if PLATFORM_WIN32
    sock = socket_fn(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#endif

    sock = (sock == INVALID_SOCKET) ? 0 : sock;

    if (!sock) {
        new_chars_t  msg = formatT(_T("socket_fn() error: %s"),
                                   net_error_name(0));
        WARN(msg, UID(EC3A1E));
        freeT(&msg);
        goto _ret_err;
    }

    {
        /* connect to server: */
        struct sockaddr_in  addr_server;
        CLEAR(addr_server);
        addr_server.sin_family = AF_INET;  /* always same */
        addr_server.sin_addr   = ip_address(server_name_or_ip_);
        addr_server.sin_port   = htons_fn(CAST(unsigned short, port_));
        {
            const int  result = connect_fn(sock,
                                           CAST(struct sockaddr*, &addr_server),
                                           sizeof(addr_server));

#if PLATFORM_LINUX

            if (result < 0)
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
                if (result == SOCKET_ERROR)
#endif
                {
#if PLATFORM_LINUX
                    close(sock);
#endif

#if PLATFORM_WIN32
                    closesocket_win(sock);
#endif

                    sleep_ms(500);  /* wait for 500 milliseconds */

                    if ((uptime_ms() - begin_time) <= 5000) { /* 5 sec. */
                        goto _connect;
                    } else {
                        goto _close;
                    }
                }
        }
    }
    {
        /* send the request to the server: */
        bytes_t  encrypted_req = simple_encrypt(request_, key);
#if PLATFORM_LINUX
        {
            const size_t  writ = write(sock,
                                       encrypted_req.data,
                                       encrypted_req.size);
            UNUSED(writ);
        }
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
        if (send_fn(sock, CAST(char*, encrypted_req.data),
                    encrypted_req.size, 0) == SOCKET_ERROR) {

            const int    err_no = WSAGetLastError_win();
            new_chars_t  msg    = formatT(_T("send_fn() error: %d - %s"),
                                          err_no, net_error_name(err_no));
            WARN(msg, UID(EFBEBC));
            freeT(&msg);
            goto _ret_err;
        }
#endif                                                      /* PLATFORM_WIN32 */
    }
    encrypted_reply = _receive_on_socket(sock, max_message_size_);

#if PLATFORM_LINUX
    /* TODO: On Linux, how to determine if there was an error? */
#endif

#if PLATFORM_WIN32

    if (encrypted_reply.size == 0 && encrypted_reply.data == NULL) {
        const int  err_no = WSAGetLastError_win();

        if (err_no == WSAECONNRESET_win || err_no == WSAECONNABORTED_win) {
            closesocket_win(sock);
            sleep_ms(500);  /* wait for 500 milliseconds */
            goto _connect;
        } else {
            new_chars_t  msg = formatT(_T("recv_fn() error: %d - %s"),
                                       err_no, net_error_name(err_no));

            WARN(msg, UID(E99956));
            freeT(&msg);
            goto _ret_err;
        }
    }

#endif                                                      /* PLATFORM_WIN32 */

_close:
    /* close client socket (remember to call net_end() */
    /* when the application exits)                        */
#if PLATFORM_LINUX
    close(sock);
#endif

#if PLATFORM_WIN32
    if (closesocket_win(sock) == SOCKET_ERROR) {
        const int  err_no = WSAGetLastError_win();

        if (err_no != WSAENOTSOCK_win) {
            new_chars_t  msg = formatT(_T("closesocket_win() error: %d - %s"),
                                       err_no, net_error_name(err_no));
            WARN(msg, UID(E42ED7));
            freeT(&msg);
            goto _ret_err;
        }
    }
#endif                                                      /* PLATFORM_WIN32 */
    {
        new_bytes_t  decrypted_reply = simple_decrypt(encrypted_reply, key);
        RETURN(decrypted_reply);
    }

_ret_err: {
        bytes_t  null_val = { 0, NULL };
        RETURN(null_val);
    }
} /* net_encrypted_request */


PUBLIC void  net_encrypted_server(                                         /*F*/
    const int  port_no_,                                                   /*-*/
    new_bytes_t (*callback_fn_)( const bytes_t  request_ ) ) {             /*-*/
    GO                                                            (UID(FD3607));
    /* initialise the server before receiving commands from clients   */
    /* (this may take a second or two, to load some data into memory) */

    bool  run_server  = true;
    int   server_sock = 0;

    net_start(UID(E98F55));

    {
        /* create a server socket to listen for incoming collections: */
        struct sockaddr_in  local_addr;        /* server's address */
        CLEAR(local_addr);
        local_addr.sin_family      = AF_INET;     /* address family   */
        local_addr.sin_addr.s_addr = INADDR_ANY;  /* IP address type  */
        local_addr.sin_port        = htons_fn(CAST(unsigned short, port_no_));

        /* create server socket */
        server_sock = socket_fn(AF_INET, SOCK_STREAM, 0);
        if (server_sock == INVALID_SOCKET) {
            server_sock = 0;
        }

        if (!server_sock) {
#if PLATFORM_LINUX
            const int  err_no = errno;
#endif

#if PLATFORM_WIN32
            const int  err_no = WSAGetLastError_win();
#endif

            new_chars_t  msg = formatT(_T("socket_fn() error: %d - %s"),
                                       err_no, net_error_name(err_no));
            WARN(msg, UID(E74944));
            freeT(&msg);
            goto _end_thread;
        }

        /* connect socket with local address and port */
        if (bind_fn(server_sock, (struct sockaddr*)
                    &local_addr, sizeof(local_addr)) != 0) {
            WARN(_T("bind_fn() failed"), UID(E0EB72));
            goto _end_thread;
        }

        /* put the socket into 'listen' mode to get */
        /* incoming connections from clients        */
        if (listen_fn(server_sock, 25) != 0) {
            WARN(_T("listen_fn() failed"), UID(EA8618));
            goto _end_thread;
        }
    }

    /* loop indefinitely until shutdown event is triggered */
    while (run_server) {
        int  client_sock = 0;

        /* wait for a client connection request or */
        /* the shutdown event to occur             */
        while (run_server) {
            /*** exit loop if shutdown event occurred */

            /* check if any data has arrived on the socket */
            fd_set          set;
            struct timeval  timeout = { 1, 0 };
            int             ret     = 0;

#if PLATFORM_LINUX
            FD_ZERO(&set);
            FD_SET(server_sock, &set);
            ret = select_fn(FD_SETSIZE, &set, NULL, NULL, &timeout);
            /* 0 = timeout,   1 = input available,   -1 = error */
#endif

#if PLATFORM_WIN32
            set.fd_count    = 1;
            set.fd_array[0] = server_sock;
            ret = select_fn(0, &set, NULL, NULL, &timeout);
            VERIFY(ret != SOCKET_ERROR, UID(ECC860));
#endif

            if (ret > 0) {
                break;
            }
        }

        {
            /* accept an incoming client connection: */
            struct sockaddr_in  client_addr;
            int  size   = CAST(int, sizeof(struct sockaddr_in));
            client_sock = accept_fn(server_sock,
                                    CAST(struct sockaddr*, &client_addr),
                                    &size);
        }

        {
            new_bytes_t  key = Bytes_init(NETWORK_ENCRYPTION_KEY,
                                          sizeof(NETWORK_ENCRYPTION_KEY));

            /* get client's request */
            new_bytes_t  encrypted_req = _receive_on_socket(client_sock, 0);
            new_bytes_t  decrypted_req = simple_decrypt(encrypted_req, key);

            /* process client's request */
            if (decrypted_req.size > 0 && decrypted_req.data) {

                /* invoke callback function to process the request */
                const new_bytes_t  reply = (*callback_fn_)(decrypted_req);
                new_bytes_t        encrypted_reply = { 0, NULL };

                if (reply.size > 0) {
                    encrypted_reply = simple_encrypt(reply, key);
                }

                /* send reply back to client */
                if (encrypted_reply.size == 0) {
                    send_fn(client_sock, "\0", 1, 0);
                } else {
                    send_fn(client_sock,
                            CAST(char*, encrypted_reply.data),
                            CAST(int,   encrypted_reply.size), 0);
                }
            }
        }
#if PLATFORM_LINUX
        tux_close(client_sock);
#endif

#if PLATFORM_WIN32
        closesocket_win(client_sock);
#endif
    }

#if PLATFORM_LINUX
    close(server_sock);
#endif

#if PLATFORM_WIN32
    closesocket_win(server_sock);
#endif

_end_thread:
    net_end(UID(E8B7C5));

    RETURN(NIL);
} /* net_encrypted_server */


/* returns an IP address string based on the specified host name              */
/* (if host name is not specified, uses local computer's name)                */
PUBLIC new_chars_t  net_ip_address( chars_t  host_name_ ) {                /*F*/
    GO                                                            (UID(F04465));
    new_chars_t  ret = NULL;
    char         hostname[256];

    net_start(UID(E9BA08));

    {
        /* determine host name: */
        const bool  no_host_name = IS_BLANK(host_name_);
        MEMSET(hostname, 0x00, sizeof(hostname));

        if (no_host_name) {
            const int  result = gethostname_fn(hostname, 256);

#if PLATFORM_LINUX
            if (result == -1) {
                _warn(_T("gethostname_fn"), errno, UID(EB4BB6));
            }
#endif

#if PLATFORM_WIN32
            if (result != ERROR_SUCCESS_win) {
                _warn(_T("gethostname_fn"), errno, UID(E0C3F2));
            }
#endif
        } else {
            int  len = STRLEN_T(host_name_);
            while (len--) {
                hostname[len] = CAST(char, *(host_name_ + len));
            }
        }
    }

    {
        /* get host's information and list of host's addresses: */
        struct hostent*  host = gethostbyname_fn(hostname);
        if (host != NULL) {
            int  i;
            for (i = 0; host->h_addr_list[i] != NULL; i++) {
                struct sockaddr_in  addr;
                MEMCPY(&(addr.sin_addr), host->h_addr_list[i], host->h_length);

                if (!IS_BLANK(ret)) {
                    appendT(&ret, _T(", "));
                }

                {
                    new_chars_t  str = Tutf8(inet_ntoa_fn(addr.sin_addr));
                    appendT(&ret, str);
                    freeT(&str);
                }
            }
        }
        net_end(UID(EDE7B1));
    }
    RETURN(ret);  /* return list of addresses */
} /* net_ip_address */


PUBLIC new_chars_t  net_plaintext_request(                                 /*F*/
    chars_t         request_,                                              /*-*/
    chars_t         server_name_or_ip_,                                    /*-*/
    const uint32_t  port_,                                                 /*-*/
    const size_t    max_message_size_ ) {                                  /*-*/
    GO                                                            (UID(F3FC55));
    unsigned long       begin_time  = uptime_ms();
    new_chars_t         reply       = NULL;
    uint8_t*            buf         = NULL;
    int                 client_sock = 0;
    struct hostent*     host_info   = NULL;
    struct sockaddr_in  addr_server;

    /* initialize WinSock */
    net_start(UID(EAF50F));

    /* determine host's IP address: */

    /* Create function ip_from_str() */
    {
        /* TODO create a means to create an text<char> */
        new_bchars_t  server  = to_utf8T(server_name_or_ip_);
        in_addr_t     addr    = inet_addr_fn(server);
        chars_t       fn_name = NULL;

        if (!IS_BLANK(server)) {
            _strupr_s(server, STRLEN(server) + 1);
        }

        if (addr == INADDR_NONE) {
            host_info = gethostbyname_fn(server);
            fn_name = _T("gethostbyname_fn");
        } else {
            host_info = gethostbyaddr_fn(CAST(char*, &addr), sizeof(addr),
                                         AF_INET);
            fn_name = _T("gethostbyaddr_fn");
        }

        if (host_info == NULL) {
            _warn(fn_name, 0, UID(E2541F));
            goto _ret_err;
        }
    }
    begin_time = uptime_ms();

_connect:
    /* create client socket */
    client_sock = socket_fn(AF_INET, SOCK_STREAM, IPPROTO_TCP);

#if PLATFORM_LINUX
    if (client_sock == INVALID_SOCKET) {
        _warn(_T("socket_fn"), errno, UID(E755A9));
        goto _ret_err;
    }
#endif

#if PLATFORM_WIN32
    if (client_sock == INVALID_SOCKET) {
        _warn(_T("socket_fn"), 0, UID(E22A08));
        goto _ret_err;
    }
#endif

    /* connect to server */
    addr_server.sin_addr.s_addr = *(CAST(unsigned long*,
                                         host_info->h_addr_list));

    addr_server.sin_family = AF_INET;  /* always same */
    addr_server.sin_port   = htons_fn(CAST(unsigned short, port_));

    if (0 != connect_fn(client_sock,
                        CAST(struct sockaddr*, &addr_server),
                        sizeof(addr_server))) {

#if PLATFORM_LINUX
        tux_close(client_sock);
#endif

#if PLATFORM_WIN32
        closesocket_win(client_sock);
#endif

        sleep_ms(500);  /* wait for 500 milliseconds */

        if ((uptime_ms() - begin_time) <= 5000) { /* 5 seconds */
            goto _connect;
        } else {
            goto _close;
        }
    }

    {
        /* send request to server: */
        bool  is_alloc = false;

#if defined UNICODE || defined _UNICODE
        char*      data = to_utf8T(request_);
        const int  len  = WCSLEN(request_) + 1;  /* +1 for \0 */
        is_alloc = true;

#else                                                  /* UNICODE || _UNICODE */
        char*      data = CAST(char*, request_);
        const int  len  = STRLEN(data) + 1;  /* +1 for \0 */
#endif                                               /* !UNICODE && !_UNICODE */

        if (CAST(size_t, len) > max_message_size_) {
            new_chars_t  msg = formatT(_T("Request too long: %d bytes")
                                       _T(" (max_message_size_ = %d)"),
                                       CAST(int, len),
                                       CAST(int, max_message_size_));
            WARN(msg, UID(ECEEA1));
            freeT(&msg);

            if (is_alloc) {
                FREE(data);
            }

            goto _ret_err;
        }

        {
            int        err_no = 0;
            const int  result = send_fn(client_sock, data, len, 0);

#if PLATFORM_LINUX
            if (result == -1) {
                err_no = errno;
            }
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
            if (result == SOCKET_ERROR) {
                err_no = WSAGetLastError_win();
            }
#endif                                                      /* PLATFORM_WIN32 */

            if (err_no != 0) {
                new_chars_t  msg = formatT(_T("send_fn() error: %d - %s"),
                                           err_no, net_error_name(err_no));
                WARN(msg, UID(EF19AC));
                freeT(&msg);

                if (is_alloc) {
                    FREE(data);
                }

                goto _ret_err;
            }
        }

        FREE(data);
    }

    {
        /* receive data: */
        const size_t  CHUNK_SIZE = 1024;

        int     pos        = 0;
        int     bytes_recv = 0;
        size_t  buf_size   = CHUNK_SIZE;

        /* prepare buffer which holds the complete received message */
        buf = MALLOC(buf_size);
        CLEAR_N(buf, buf_size);

        /* keep receiving and concatenating data to the buffer, */
        /* until there is no more                               */
        do {
            /* re-allocate buffer if it's too small to accept the next chunk */
            if ((pos + CHUNK_SIZE) > buf_size) {
                uint8_t*      new_buf  = NULL;
                const size_t  new_size = buf_size * 2 <= max_message_size_ ?
                                         buf_size * 2 : max_message_size_;
                new_buf = MALLOC(new_size);
                MEMSET(new_buf, 0x00, new_size);
                MEMCPY(new_buf, buf,  buf_size);
                FREE(buf);
                buf      = new_buf;
                buf_size = new_size;
            }

            /* receive and append server's reply to the buffer */
            bytes_recv = recv_fn(client_sock, buf + pos, CHUNK_SIZE, 0);

#if PLATFORM_LINUX
            if (bytes_recv == -1) {
                _warn(_T("recv_fn"), errno, UID(E6B545));
                goto _ret_err;
            }
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
            if (bytes_recv == SOCKET_ERROR) {
                _warn(_T("recv_fn"), 0, UID(E2BC3A));
                goto _ret_err;
            }
#endif                                                      /* PLATFORM_WIN32 */

            if (bytes_recv > 0) {
                pos += bytes_recv;

                if (pos > CAST(int, max_message_size_)) {
                    new_chars_t  msg = formatT(_T("Reply too long: %d bytes")
                                               _T(" (max_message_size_ = %d)"),
                                               CAST(int, bytes_recv),
                                               CAST(int, max_message_size_));
                    WARN(msg, UID(E8554F));
                    freeT(&msg);
                    goto _ret_err;
                }
            }

            /* wait for 100ms and retry if no data has been received yet */
            if (pos == 0 && bytes_recv == 0 && bytes_recv != SOCKET_ERROR) {
                sleep_ms(100);
                continue;
            }

            sleep_ms(100);

            {
                /* exit if there is no more data to receive: */
#if PLATFORM_WIN32
                unsigned long  bytes_to_read = 0;

                const int  result =
                    ioctlsocket_win(client_sock, FIONREAD, &bytes_to_read);

                if (bytes_to_read == 0 || result != 0) {
                    break;
                }
#endif                                                      /* PLATFORM_WIN32 */
            }
        } while (bytes_recv != 0 && bytes_recv != SOCKET_ERROR);

        reply = Tutf8(CAST(char*, buf));

        if (buf) {
            FREE(buf);
        }

#if PLATFORM_WIN32

        if (bytes_recv == SOCKET_ERROR) {
            const int  err_no = WSAGetLastError_win();

            if (err_no == WSAECONNRESET_win || err_no == WSAECONNABORTED_win) {
                closesocket_win(client_sock);
                sleep_ms(500);  /* wait for 500 milliseconds */
                goto _connect;
            } else {
                _warn(_T("recv_fn"), 0, UID(ECA826));
                goto _ret_err;
            }
        }

#endif                                                      /* PLATFORM_WIN32 */
    }

_close:
    /* close client socket (remember to call net_end() when quitting) */
#if PLATFORM_WIN32
    if (closesocket_win(client_sock) == SOCKET_ERROR) {
        _warn(_T("closesocket_win()"), 0, UID(E9DB82));
        goto _ret_err;
    }
#endif                                                      /* PLATFORM_WIN32 */
    RETURN(reply);

_ret_err:
    if (buf) {
        FREE(buf);
    }
    RETURN(NULL);
} /* net_plaintext_request */


PUBLIC new_chars_t  uri_encode( chars_t  text_ ) {                         /*F*/
    GO                                                            (UID(F2F36F));
    int      encoded_len = 0;
    chars_t  rd          = NULL;
    char_t   ch          = '\0';

#if 000   /* Not for used now. Using max uri escaping with _NO_ESCAPE. */
#define _ESCAPE( CHAR_ )                                         \
    ((CHAR_) < 33   ||  /* uri (space and all control chars) */  \
     (CHAR_) > 127  ||  /* uri (all non-ascii chars) */          \
     (CHAR_) == '#' ||  /* uri */                                \
     (CHAR_) == '%' ||  /* uri */                                \
     (CHAR_) == '?' ||  /* uri */                                \
     (CHAR_) == ';' ||  /* uri, args */                          \
     (CHAR_) == '&' ||  /* uri, args */                          \
     (CHAR_) == '+'     /* uri, args */                      /*#*/
#endif                                                                 /* 000 */

#define _NO_ESCAPE( CHAR_ )                 \
    (((CHAR_) >= '0' && (CHAR_) <= '9') ||  \
     ((CHAR_) >= 'A' && (CHAR_) <= 'Z') ||  \
     ((CHAR_) >= 'a' && (CHAR_) <= 'z') ||  \
     ((CHAR_) == '-')                   ||  \
     ((CHAR_) == '.')                   ||  \
     ((CHAR_) == '_')                   ||  \
     ((CHAR_) == '~'))                  /*#*/

    /* calculate length of encoded string                 */
    /* See RFC1630 "Reserved Characters" for more details */
    encoded_len = 0;

    for (rd = text_; *rd != '\0'; rd++) {
        ch = *rd;

        if (_NO_ESCAPE(ch)) {
            encoded_len++;
        } else {
            encoded_len += 3;  /* uses 3 chars: '%xx' */
        }
    }

    encoded_len++;  /* for \0 */
    {
        /* allocate string */
        char_t*  ret = MALLOC(encoded_len * sizeof(char_t));

        /* write and return encoded string */
        char_t*  wr = ret;
        for (rd = text_; *rd != '\0'; rd++) {
            ch = *rd;

            if (_NO_ESCAPE(ch)) {
                *wr++ = *rd;
            } else {
                *wr++ = '%';
                *wr++ = HEX_DIGIT(ch / 16);
                *wr++ = HEX_DIGIT(ch % 16);
            }
        }
        *wr = '\0';
        RETURN(ret);
    }
} /* uri_encode */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
