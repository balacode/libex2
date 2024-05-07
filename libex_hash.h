/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                        [libex_hash.h] */
/* -------------------------------------------------------------------------- */

#if (defined __GNUC__ || defined __clang__) && !defined __MINGW32__
#pragma GCC diagnostic ignored "-Wunused-macros"
#endif

#if !defined INCLUDED_LIBEX_HASH_H
#define      INCLUDED_LIBEX_HASH_H

#include "libex.h"

/* whirlpool-specific definitions */
#define NESSIE_HASH_DIGEST_BYTES  64
#define NESSIE_HASH_DIGEST_BITS   512         /* 8 * NESSIE_HASH_DIGEST_BYTES */

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

typedef struct  lx_hash_t {
    uint8_t  hash_bytes[NESSIE_HASH_DIGEST_BYTES];               /* lx_hash_t */
}
lx_hash_t;

LX_PUBLIC lx_bool  lx_hash_equal(                                          /*F*/
    const lx_hash_t*  hash_1_,                                             /*-*/
    const lx_hash_t*  hash_2_ );                                           /*-*/

LX_PUBLIC lx_new_chars_t  lx_hash_hex_of_file( lx_chars_t  filename_ );    /*F*/

#if defined UNICODE || defined _UNICODE
#define lx_hash_hex_of_text  lx_hash_hex_of_text_A                         /*F*/
#else
#define lx_hash_hex_of_text  lx_hash_hex_of_text_W                         /*F*/
#endif

LX_PUBLIC lx_new_chars_t  lx_hash_hex_of_text_A( const char*  text_ );     /*F*/

LX_PUBLIC lx_new_chars_t  lx_hash_hex_of_text_W( const wchar_t*  text_ );  /*F*/

LX_PUBLIC lx_new_chars_t  lx_hash_hex_text( const lx_hash_t*  hash_ );     /*F*/

LX_PUBLIC void  lx_hash_init( lx_hash_t*  hash_ );                         /*F*/

LX_PUBLIC lx_hash_t  lx_hash_of_bytes(                                     /*F*/
    const void*   bytes_,                                                  /*-*/
    const size_t  length_in_bytes_ );                                      /*-*/

LX_PUBLIC lx_hash_t  lx_hash_of_file( lx_chars_t  filename_ );             /*F*/

LX_PUBLIC lx_hash_t  lx_hash_of_hash( lx_hash_t*  hash_ );                 /*F*/

#if defined UNICODE || defined _UNICODE
#define lx_hash_of_text  lx_hash_of_text_A                                 /*F*/
#else                                                  /* UNICODE || _UNICODE */
#define lx_hash_of_text  lx_hash_of_text_W                                 /*F*/
#endif                                               /* !UNICODE && !_UNICODE */

LX_PUBLIC lx_hash_t  lx_hash_of_text_A( const char*  text_ );              /*F*/

LX_PUBLIC lx_hash_t  lx_hash_of_text_W( const wchar_t*  text_ );           /*F*/

void  nessie_test_api( void );                                             /*F*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
