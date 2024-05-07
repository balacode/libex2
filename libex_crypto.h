/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                      [libex_crypto.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_CRYPTO_H
#define      INCLUDED_LIBEX_CRYPTO_H

#include "libex.h"

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

LX_PUBLIC lx_new_bytes_t  lx_simple_encrypt(                               /*F*/
    const lx_bytes_t  data_,                                               /*-*/
    const lx_bytes_t  key_ );                                              /*-*/

LX_PUBLIC lx_new_bytes_t  lx_simple_decrypt(                               /*F*/
    const lx_bytes_t  data_,                                               /*-*/
    const lx_bytes_t  key_ );                                              /*-*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
