/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                             [libex_ado_connection_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_ADO_CONNECTION__H && LX_PLATFORM_WIN32
#define      INCLUDED_LIBEX_ADO_CONNECTION__H
#include "libex_ado_connection.h"

#define Ado                             lx_Ado

/* -------------------------------------------------------------------------- */
/* Constructor / Destructor:                                                  */

#define Ado_openSqlServerDb             lx_Ado_openSqlServerDb
#define Ado_openJetDb                   lx_Ado_openJetDb
#define Ado_free                        lx_Ado_free

/* -------------------------------------------------------------------------- */
/* Properties:                                                                */

#define Ado_connectionString            lx_Ado_connectionString

/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */

#define Ado_execute                     lx_Ado_execute
#define Ado_execute2                    lx_Ado_execute2
#define Ado_readCsv                     lx_Ado_readCsv

#endif                                                                   /*eof*/
