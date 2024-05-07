/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                 [libex_http_server.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_http_server_.h"
#if defined INCLUDED_LIBEX_HTTP_SERVER_H

#include "libex_config_.h"

#include <limits.h>
#include <stdio.h>   /* for printf() */
#include <stdlib.h>  /* for exit()   */
#include <string.h>  /* for memset() */

#if PLATFORM_LINUX
#include <error.h>
#include <pthread.h>
#endif

#if PLATFORM_WIN32
#include <winsock2.h>  /* Windows API */
#include <process.h>   /* threads     */
#endif

#include "libex_.h"
#include "libex_bytes_.h"
#include "libex_call_.h"
#include "libex_const_.h"
#include "libex_debug_.h"
#include "libex_error_.h"
#include "libex_logging_.h"
#include "libex_macro_.h"
#include "libex_network_.h"
#include "libex_stringc_.h"
#include "libex_system_.h"
#include "libex_type_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#if defined _MSC_VER
#pragma warning (disable:4710)  /* W:L4 function not inlined                  */
#pragma warning (disable:4820)  /* W:L4 'N' bytes padding added after 'NAME'  */
/* TODO: remove this later, once utf8 encoding is used everywhere */
#pragma warning (disable:4133)  /* W:L3 incompatible types - from T1 to T2    */
#endif

#define _DOC_NOT_FOUND                                                \
    "<!DOCTYPE html PUBLIC '-//w3c//dtd xhtml 1.0 transitional//en'"  \
    " 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd'>"     \
    "<html xmlns='http://www.w3.org/1999/xhtml'>"                     \
    "<head><title>E404</title></head>"                                \
    "<body bgcolor='#ffffff'>"                                        \
    "<div style='position: absolute; left: 55px; width: 350px;"       \
    " top: 55px; height: 85px; background-color: #FF3300;"            \
    " font-family: Arial, Helvetica, sans-serif;"                     \
    " font-size: xx-large; font-weight: bolder;"                      \
    " color: #FFFFFF;' align='center'>"                               \
    "404: That page was not found! *</div>"                           \
    "<div style='position: absolute; left: 55px; width: 350px;"       \
    " top: 150px; font-family: Arial, Helvetica, sans-serif;"         \
    " font-weight: bolder; color: #FF3300;' align='center'>"          \
    "* However the server is responding.</div>"                       \
    "</body></html>"                                              /*#*/

/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


typedef struct  _http_server_t {
    bool                   running_server;                  /* _http_server_t */
    int                    listen_port;                     /* _http_server_t */
    socket_t               server_sock;                     /* _http_server_t */
    HttpServer_callback_fn(http_get_handler_fn);            /* _http_server_t */
    /* TODO: array of requests? */
}
_http_server_t;


/* -------------------------------------------------------------------------- */
/* Functions: Private                                                         */


#define _BASE_OBJ_WRAP_INC
#define _OBJ_HANDLE_TYPE   HttpServer
#define _OBJ_INNER_TYPE    _http_server_t
#define _OBJ_ALLOC_FN_UID  UID(F293F7)
#define _OBJ_FREE_FN_UID   UID(F6E0C0)
#define _OBJ_CONST_FN_UID  UID(FF76AF)
#define _OBJ_FN_UID        UID(FF35EC)
#define _OBJ_WRAP_FN_UID   UID(F0D3C4)
#include "libex_object_wrapper.inc.c"


typedef struct  _client_thread_args_t {
    _http_server_t*  server;                         /* _client_thread_args_t */
    socket_t         client_sock;                    /* _client_thread_args_t */
    bool             args_read;                      /* _client_thread_args_t */
}
_client_thread_args_t;


/* -------------------------------------------------------------------------- */
/* Functions: Private General-Purpose                                         */


#if PLATFORM_LINUX
#define _ERRNO  errno
#endif

#if PLATFORM_WIN32
#define _ERRNO  WSAGetLastError_win()
#endif

#define _net_warn( SYSTEM_FN_NAME_, SRC_UID_ )                      \
    _net_warn_fn(SRC_UID_, FN_NAME_A, SYSTEM_FN_NAME_, _ERRNO)  /*#*/

static void  _net_warn_fn(                                                 /*F*/
    const uint32_t  src_uid_,                                              /*-*/
    chars_t         source_func_,                                          /*-*/
    const char*     system_func_,                                          /*-*/
    const int       error_no_ ) {                                          /*-*/
    GO                                                            (UID(F9E641));
#if PLATFORM_LINUX
    error(0, error_no_, "-> %s() -> %s. UID(%6X).", source_func_,
          system_func_, src_uid_);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    if (error_no_ != WSAECONNRESET_win) {
        new_chars_t  err = formatT(_T("%s error: %d - %s"),
                                   system_func_, error_no_,
                                   net_error_name(error_no_));
        log_warn(err, source_func_, src_uid_, NULL);
        freeT(&err);
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* _net_warn_fn */


static socket_t  _socket_create_listener( const int  port_ ) {             /*F*/
    GO                                                            (UID(FAEDEA));
    socket_t  ret = 0;

    /* create the server socket */
    ret = _SOCKET(AF_INET, SOCK_STREAM, 0);

    if (ret == INVALID_SOCKET) {
        WARN(_T("server_sock == INVALID_SOCKET"), UID(E1A2D0));
        RETURN(ret);
    }

    {
        /* set socket option to allow local address reuse: */
        int        reuse_address = 1;
        const int  result = SETSOCKOPT(
                                ret,                          /* socket  */
                                SOL_SOCKET,                   /* level   */
                                SO_REUSEADDR,                 /* optname */
                                CAST(void*, &reuse_address),  /* optval  */
                                sizeof(reuse_address));       /* optlen  */
        ASSERT(result == 0, UID(E82573));
    }

    {
        /* connect the server socket to the local address and port: */
        struct sockaddr_in  listen_address;
        CLEAR(listen_address);

        listen_address.sin_family      = AF_INET;  /* always AF_INET */
        listen_address.sin_addr.s_addr = HTONL(INADDR_ANY);  /* type */
        listen_address.sin_port        = HTONS(CAST(uint16_t, port_));

        {
            /* on Linux, bind() returns -1 and sets 'errno' */
            const int  result =
                BIND(ret, CAST(struct sockaddr*, &listen_address),
                     sizeof(listen_address));

            if (result != 0) {
                _net_warn(_T("BIND()"), UID(E0FB43));
                ret = INVALID_SOCKET;
                RETURN(ret);
            }
        }
    }

    /* put the socket into 'listen' mode to get */
    /* incoming connections from clients        */
    if (LISTEN(ret, 25) != 0) {
        _net_warn(_T("LISTEN()"), UID(EFA065));
    }
    RETURN(ret);
} /* _socket_create_listener */


static bool  _socket_is_readable_or_bad( const socket_t  socket_ ) {       /*F*/
    GO                                                            (UID(FBE90A));
    int             count   = 0;
    struct timeval  timeout = { 0, 100 };  /* seconds and microseconds */
    fd_set          sockets;
    FD_ZERO(&sockets);

#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4127)  /* W:L4 conditional expression is constant    */
#endif

    FD_SET(socket_, &sockets);

#if defined _MSC_VER
#pragma warning (pop)
#endif

    count = SELECT(
                socket_ + 1,  /* Max FD in set + 1. (Ignored on Windows) */
                &sockets,     /* set of sockets to check for readability */
                NULL,         /* set of sockets to check for writability */
                NULL,         /* set of sockets to check for errors      */
                &timeout);    /* maximum time to wait                    */

    if (count == SOCKET_ERROR) {
#if PLATFORM_LINUX
        const int   err_no     = errno;
        const bool  report_err = (errno != EBADF);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
        const int   err_no     = WSAGetLastError_win();
        const bool  report_err = (err_no != WSAENOTSOCK_win &&
                                  err_no != WSAECONNRESET_win);
#endif                                                      /* PLATFORM_WIN32 */

        if (report_err) {
            new_chars_t  err = formatT(_T("SELECT() error: %d - %s"),
                                       err_no, net_error_name(err_no));
            WARN(err, UID(EBD5C6));
            freeT(&err);
        }
    }

    {
        const bool  ret = (count > 0 && count != SOCKET_ERROR);
        RETURN(ret);
    }
} /* _socket_is_readable_or_bad */


static new_bytes_t  _socket_receive( const socket_t  socket_ ) {           /*F*/
    GO                                                            (UID(F2281C));
    const size_t  MAX_MESSAGE_SIZE = MB(16);
    const size_t  CHUNK_SIZE       = KB(16);

    int  recv_total = 0;  /* total number of bytes received        */
    int  recv       = 0;  /* number of bytes received on last read */

    /* prepare buffer which holds the complete received message */
    new_bytes_t  ret = { 0, NULL };
    ret.size = CHUNK_SIZE;
    ret.data = MALLOC(ret.size);
    MEMSET(ret.data, 0x00, ret.size);

    /* keep receiving and adding data to the buffer, until there's no more */
    do {
        /* re-allocate the buffer if it's too small for extra data */
        if ((recv_total + CHUNK_SIZE) > ret.size) {
            size_t  new_size = ret.size * 2;

            if (new_size > MAX_MESSAGE_SIZE) {
                new_size = MAX_MESSAGE_SIZE;
            }

            {
                uint8_t*  new_buf = REALLOC(ret.data, new_size);
                if (new_buf != NULL) {
                    ret.data = new_buf;
                    ret.size = new_size;
                }
            }
        }

        /* receive and append server's request to the buffer */
        recv = RECV(socket_, ret.data + recv_total, CHUNK_SIZE, 0);
        if (recv == SOCKET_ERROR) {
#if PLATFORM_LINUX
            printf("recv == SOCKET_ERROR\n");;;
#endif

#if PLATFORM_WIN32
            const int  err_no = WSAGetLastError_win();

            /* the virtual circuit was reset by the remote side    */
            /* executing a hard or abortive close. The application */
            /* should close the socket as it is no longer usable.  */
            if (err_no == WSAECONNRESET_win) {
                recv = 0;
            }

            if (err_no == WSAECONNABORTED_win) {
                recv = 0;
            } else
#endif                                                      /* PLATFORM_WIN32 */
            {
                /* the socket will be closed by closesocket(); */
                _net_warn(_T("RECV()"), UID(E6FE98));
            }
        } else if (recv > 0) {
            recv_total += recv;
            if (recv_total > CAST(int, MAX_MESSAGE_SIZE)) {
                log_warn(_T("Request is too long"), FN_NAME, UID(E4E247), NULL);
                if (ret.data) {
                    Bytes_free(&ret);
                    ret.data = NULL;
                }
                ret.size = 0;
                RETURN(ret);
            }
        } else {
            continue;    /* go back to fetch data, if none received yet */
        }

        sleep_ms(50);  /* wait for 50ms, exit if no more incoming data */
        {
            unsigned long  bytes_to_read = 0;
            int            result        = 0;

#if PLATFORM_WIN32
            result = ioctlsocket_win(socket_, FIONREAD, &bytes_to_read);
#endif
            if (bytes_to_read == 0 || result != 0) {
                break;
            }
        }
    } while (recv != 0 && recv != SOCKET_ERROR);

    Bytes_resize(&ret, recv_total);
    RETURN(ret);
} /* _socket_receive */


static bool  _socket_send_bytes(                                           /*F*/
    const socket_t  socket_,                                               /*-*/
    const bytes_t   send_data_ ) {                                         /*-*/
    GO                                                            (UID(FD96FE));
    printf(">>> _socket_send_bytes() A\n");;;

#if 000   /* debugging stuff */
    DUMP_OPEN;
    {
        new_chars_t  bytes = Bytes_describeT(send_data_);
        DUMP(_T("\n----------------------------\n")
             _T(" _SOCKET %d SENDING = %s"), socket_, bytes);
        freeT(&bytes);
    }
    DUMP_CLOSE;
#endif                                                                 /* 000 */

    {
        const int  result = SEND(socket_,
                                 CAST(char*, send_data_.data),
                                 CAST(int,   send_data_.size), 0);

        if (result == SOCKET_ERROR) {
#if PLATFORM_WIN32
            const int  err_no = WSAGetLastError_win();

            if (err_no != WSAECONNABORTED_win) {
                _net_warn(_T("SEND()"), UID(E4CA10));
            }

#endif                                                      /* PLATFORM_WIN32 */
            printf("<<< _socket_send_bytes() B\n");;;
            RETURN(false);
        }
    }

    printf("<<< _socket_send_bytes() C\n");;;
    RETURN(true);
} /* _socket_send_bytes */


/* -------------------------------------------------------------------------- */


static new_http_request_t  _parse_received_bytes(                          /*F*/
    const bytes_t  received_data_ ) {                                      /*-*/
    GO                                                            (UID(F6E353));
    http_request_t  ret;
    CLEAR(ret);

    ret.recv_data = Tutf8(CAST(const char*, received_data_.data));

    {
        size_t  delim_pos = find2T(ret.recv_data, "\r\n\r\n");
        size_t  delim_len = 4;

        {
            const size_t  pos = find2T(ret.recv_data, _T("\r\r"));

            if (delim_pos != NONE &&
                pos != NONE &&
                pos < delim_pos) {
                delim_pos = pos;
                delim_len = 2;
            }
        }
        ret.recv_header  = T_first(ret.recv_data, delim_pos);
        ret.recv_command = T_get_token(ret.recv_header, 0, _T(" "));
        ret.recv_url     = T_get_token(ret.recv_header, 1, _T(" "));

        upper_in_T(ret.recv_command);

        while (beginsT(ret.recv_url, _T("/")) ||
               ends2T(ret.recv_url, _T("/"))) {
            trim4_in_T(ret.recv_url, _T("/"), true, true);
        }

        ret.recv_body = T_offset(ret.recv_data, delim_pos + delim_len);
        trim_in_T(ret.recv_body);
    }
    RETURN(ret);
} /* _parse_received_bytes */


static void  _closesocket( socket_t*  socket_ ) {                          /*F*/
    GO                                                            (UID(F9A9C7));
#if PLATFORM_LINUX
    if (0 != close(*socket_)) {
        _net_warn("close()", UID(E77C2F));
    }
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    if (0 != closesocket_win(*socket_)) {
        const int  err_no = WSAGetLastError_win();

        if (err_no != WSAECONNRESET_win &&
            err_no != WSAENOTSOCK_win) {
            new_chars_t  err = formatT(_T("_closesocket() error: %d - %s"),
                                       err_no, net_error_name(err_no));
            WARN(err, UID(E947A3));
            freeT(&err);
        }
    }
#endif                                                      /* PLATFORM_WIN32 */

    *socket_ = INVALID_SOCKET;

    RETURN(NIL);
} /* _closesocket */


static void  _free_request( http_request_t*  request_ ) {                  /*F*/
    GO                                                            (UID(F3F979));
    if (request_ != NULL) {
        if (request_->recv_header != NULL) {
            freeA(&request_->recv_header);
        }

        if (request_->recv_command != NULL) {
            freeA(&request_->recv_command);
        }

        if (request_->recv_url != NULL) {
            freeA(&request_->recv_url);
        }

        if (request_->recv_body != NULL) {
            freeA(&request_->recv_body);
        }

        if (request_->recv_data != NULL) {
            freeA(&request_->recv_data);
        }
    }
    RETURN(NIL);
} /* _free_request */


static THREAD_RETURN_TYPE  _client_thread( void*  client_thread_args_ ) {  /*F*/
    GO                                                            (UID(FFD30E));
    bool  keep_running = true;
    _client_thread_args_t  args;
    CLEAR(args);

    {
        /* 'unbox' arguments: */
        _client_thread_args_t*  args_ptr = client_thread_args_;
        args = *args_ptr;
        args_ptr->args_read = true;
    }

    net_start(UID(EAC944));

    do {
        new_bytes_t  received = _socket_receive(args.client_sock);
        if (received.size == 0) {
            break;
        } else {
            new_http_request_t  request = _parse_received_bytes(received);

            new_bytes_t  reply       = { 0, NULL };
            bool         const_reply = false;
            const char*  mime        = mime_type(request.recv_url);

            {
                const int  received_size = CAST(int, received.size);
                printf("\n\n>>> ------------------->\n header=(%d bytes) %s\n",
                       received_size, request.recv_header);;;
            }

#if 000   /* debugging stuff */
            DUMP_OPEN;
            {
                new_chars_t  bytes = Bytes_describeT(received);
                DUMP(_T("\n----------------------------\n")
                     _T(" _SOCKET %d RECEIVED = %s"), args.client_sock, bytes);
                freeT(&bytes);
            }
            DUMP_CLOSE;
#endif                                                                 /* 000 */

            /* invoke the HTTP GET handler callback function */
            if (args.server->http_get_handler_fn != NULL) {
                reply = args.server->http_get_handler_fn(&request);
            }

            /* if request isn't processed, send boilerplate '404 - Not Found' */
            if (reply.size == 0) {
                const_reply = true;
                mime        = _T("text/html");
                reply.data  = CAST(uint8_t*, _DOC_NOT_FOUND);
                reply.size  = STRLEN(_DOC_NOT_FOUND);
            }

            {
                /* prepare HTTP headers and send reply */
                new_bytes_t  header =
                    Bytes_fromNewChars(
                        formatA(
                            "HTTP/1.1 200 OK"        "\r\n"
                            "Connection: keep-alive" "\r\n"
                            "Content-Type: %s"       "\r\n"
                            "Content-Length: %d"     "\r\n" "\r\n",
                            mime_type, reply.size));

                new_bytes_t  send = Bytes_join(header, reply);

                _socket_send_bytes(args.client_sock, send);

                Bytes_free(&send);
                Bytes_free(&header);
            }

            Bytes_free(&received);  /* free up memory */
            if (!const_reply) {
                Bytes_free(&reply);
            }
            _free_request(&request);

            {
                /* wait for more data to arrive on the socket */
                /* (HTTP 1.1 persistent connection)           */
                unsigned long  time_ms = uptime_ms();
                while (5000 > (uptime_ms() - time_ms) &&
                       !_socket_is_readable_or_bad(
                           args.client_sock)) {
                    sleep_ms(50);
                }
            }
        }
    } while (keep_running);

    if (args.client_sock != INVALID_SOCKET) {
        _closesocket(&args.client_sock);
    }

    net_end(UID(E30B12));

#if PLATFORM_LINUX
    RETURN(NULL);
#endif

#if PLATFORM_WIN32
    RETURN(NIL);
#endif

} /* _client_thread */


/* -------------------------------------------------------------------------- */
/* Constructor:                                                               */


PUBLIC HttpServer  HttpServer_init( void ) {                               /*C*/
    GO                                                            (UID(CD1F62));
    _http_server_t*  ob  = _object_alloc();
    new_HttpServer   ret = _object_wrap(ob);
    ob->listen_port = 0;
    net_start(UID(E1A42F));
    RETURN(ret);
} /* HttpServer_init */


/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */


PUBLIC void  HttpServer_free( HttpServer*  object_ ) {                     /*D*/
    GO                                                            (UID(D5042A));
    if (object_ != NULL) {
        _http_server_t* const  me = _object(object_, UID(E863B3));
        _closesocket(&me->server_sock);
        me->running_server = false;
        net_end(UID(EA60F7));
        _object_free(object_);
    }
    RETURN(NIL);
} /* HttpServer_free */


/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */


PUBLIC void  HttpServer_run(                                               /*M*/
    HttpServer  object_,                                                   /*-*/
    const int   listen_on_port_ ) {                                        /*-*/
    GO                                                            (UID(FF9A13));
    _http_server_t* const  me = _object(&object_, UID(E7A740));

    me->server_sock = _socket_create_listener(listen_on_port_);

    if (me->server_sock == INVALID_SOCKET) {
        RETURN(NIL);
    }

    me->listen_port    = listen_on_port_;
    me->running_server = true;

    while (me->running_server) {
        /* wait for a client connection request */
        socket_t  client_sock = 0;

        while (me->running_server && client_sock == 0) {
            if (me->running_server &&
                _socket_is_readable_or_bad(me->server_sock)) {

                struct sockaddr_in  client_addr;
                int                 size = sizeof(struct sockaddr_in);

                client_sock = ACCEPT(me->server_sock,
                                     CAST(struct sockaddr*, &client_addr),
                                     &size);
            }
        }

        /* start client thread */
        if (me->running_server) {
            _client_thread_args_t  args;

            args.server      = me;
            args.client_sock = client_sock;
            args.args_read   = false;
            {
#if PLATFORM_LINUX
                static pthread_t  client_thread = 0;

                const int  result =
                    pthread_create(&client_thread,  /* thread id (out) */
                                   NULL,            /* thread attribs. */
                                   _client_thread,  /* start routine   */
                                   &args);          /* pass argument   */

                /* On success, pthread_create() returns 0;    */
                /* on error, it returns an error number,      */
                /* and the contents of *thread are undefined. */

                if (result != 0) {
                    perror("pthread_create() failed");  /* UID(E936A7) */
                    exit(EXIT_FAILURE);
                }

#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
                const uintptr_t  client_thread =
                    _beginthread(_client_thread, 0, &args);
                while (client_thread != CAST(uintptr_t, -1) &&
                       !args.args_read) {
                    sleep_ms(20);
                }
#endif                                                      /* PLATFORM_WIN32 */
            }
        }
    }
    printf("_closesocket() C\n");;;
    _closesocket(&me->server_sock);
    RETURN(NIL);
} /* HttpServer_run */


PUBLIC void  HttpServer_setHttpGetHandler(                                 /*M*/
    HttpServer  object_,                                                   /*-*/
    HttpServer_callback_fn(callback_fn_) ) {                               /*-*/
    GO                                                            (UID(FD19C6));
    _http_server_t* const  me = _object(&object_, UID(E0FAF8));
    me->http_get_handler_fn = callback_fn_;
    RETURN(NIL);
} /* HttpServer_setHttpGetHandler */


PUBLIC void  HttpServer_stop( HttpServer  object_ ) {                      /*M*/
    GO                                                            (UID(F74C9F));
    _http_server_t* const  me = _object(&object_, UID(E6C90D));
    me->running_server = false;
    RETURN(NIL);
} /* HttpServer_stop */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
