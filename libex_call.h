/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                        [libex_call.h] */
/* -------------------------------------------------------------------------- */
/* Call Tracing and Definitions and Declarations:                             */

#if !defined INCLUDED_LIBEX_CALL_H
#define      INCLUDED_LIBEX_CALL_H

/* -------------------------------------------------------------------------- */
#if defined LX_CALL_TRACE && LX_CALL_TRACE == 2

#define LX_GO( SRC_UID_ )                                            \
    int  src_uid = LX_CL lx_fn_call_entry(SRC_UID_, LX_FN_NAME_A,    \
                                          __FILE__, __LINE__);   /*#*/

#define LX_RETURN( RETURN_VAL_ )                                           \
    {                                                                      \
        LX_CL lx_fn_call_exit(src_uid, LX_FN_NAME_A, __FILE__, __LINE__);  \
        return RETURN_VAL_;                                                \
    }                                                                  /*#*/

/* -------------------------------------------------------------------------- */
#elif defined LX_CALL_TRACE && LX_CALL_TRACE == 1

#define LX_GO( SRC_UID_ )                 \
    int  src_uid = SRC_UID_;              \
    printf("--> %s\n", LX_FN_NAME_A)  /*#*/

#define LX_RETURN( RETURN_VAL_ )                                               \
    { src_uid--; printf("<-- %s\n", LX_FN_NAME_A); return RETURN_VAL_; }   /*#*/

/* -------------------------------------------------------------------------- */
#else                                                   /* LX_CALL_TRACE == 0 */

#if defined __GNUC__ || defined __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#define LX_GO( SRC_UID_ )         int  src_uid = SRC_UID_
#define LX_RETURN( RETURN_VAL_ )  { src_uid--; return RETURN_VAL_; }

#if defined __GNUC__ || defined __clang__
#pragma GCC diagnostic pop
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#endif                                                      /* !LX_CALL_TRACE */

/* -------------------------------------------------------------------------- */
/* Call-Tracing Function Declarations:                                        */

#if defined LX_CALL_TRACE && LX_CALL_TRACE == 2
LX_NAMESPACE(lx_c)

LX_PUBLIC uint32_t  lx_fn_call_entry(                                      /*F*/
    const uint32_t  src_uid_,                                              /*-*/
    const char*     source_func_,                                          /*-*/
    const char*     source_file_,                                          /*-*/
    const int       source_line_ );                                        /*-*/

LX_PUBLIC void  lx_fn_call_exit(                                           /*F*/
    const uint32_t  src_uid_,                                              /*-*/
    const char*     source_func_,                                          /*-*/
    const char*     source_file_,                                          /*-*/
    const int       source_line_ );                                        /*-*/

LX_PUBLIC void  lx_fn_call_report( void );                                 /*F*/

LX_END_NAMESPACE  /*lx_c*/
#endif                                 /* LX_CALL_TRACE && LX_CALL_TRACE == 2 */

#endif                                                                   /*eof*/
