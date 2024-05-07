/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                              [libex_ado_connection.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_ADO_CONNECTION_H && LX_PLATFORM_WIN32
#define      INCLUDED_LIBEX_ADO_CONNECTION_H

#undef  _WIN32_WINNT
#define _WIN32_WINNT  0x0501  /* Windows XP or later */

#include "libex.h"

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx)

typedef struct  {
    void*  ado;
} lx_Ado;                             /* lx_Ado */

/* -------------------------------------------------------------------------- */
/* Constructor / Destructor:                                                  */

LX_PUBLIC lx_Ado  lx_Ado_openSqlServerDb(                                  /*C*/
    lx_chars_t  sql_server_name_,                                          /*-*/
    lx_chars_t  db_name_,                                                  /*-*/
    lx_chars_t  user_name_,                                                /*-*/
    lx_chars_t  user_password_ );                                          /*-*/

LX_PUBLIC lx_Ado  lx_Ado_openJetDb(                                        /*C*/
    lx_chars_t  db_name_,                                                  /*-*/
    lx_chars_t  jet_db_password_,                                          /*-*/
    lx_chars_t  user_name_,                                                /*-*/
    lx_chars_t  user_password_,                                            /*-*/
    lx_chars_t  jet_sys_db_name_ );                                        /*-*/

LX_PUBLIC LX_CL lx_bool  lx_Ado_free( lx_Ado*  object_ );                  /*D*/

/* -------------------------------------------------------------------------- */
/* Properties:                                                                */

LX_PUBLIC lx_chars_t  lx_Ado_connectionString( lx_Ado  object_ );          /*P*/

/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */

LX_PUBLIC int  lx_Ado_execute(                                             /*M*/
    lx_Ado         object_,                                                /*-*/
    lx_chars_t     sql_statements_,                                        /*-*/
    LX_CL lx_bool  immediate_,                                             /*-*/
    LX_CL lx_bool  ignore_lock_errors_ );                                  /*-*/

LX_PUBLIC int  lx_Ado_execute2(                                            /*M*/
    lx_Ado      object_,                                                   /*-*/
    lx_chars_t  sql_statements_ );                                         /*-*/

LX_PUBLIC lx_new_chars_t  lx_Ado_readCsv(                                  /*M*/
    lx_Ado         object_,                                                /*-*/
    lx_chars_t     sql_statement_,                                         /*-*/
    LX_CL lx_bool  include_column_names_ );                                /*-*/

LX_END_NAMESPACE  /*lx*/
#endif                                                                   /*eof*/
