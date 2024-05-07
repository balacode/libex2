/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_error.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_ERROR_H
#define      INCLUDED_LIBEX_ERROR_H

#include "libex.h"

/* -------------------------------------------------------------------------- */
/* Error-Checking Macros:                                                     */

#define LX_LINE  err_line = __LINE__

#if (defined DEBUG || defined _DEBUG)
#define LX_ASSERT( CONDITION_, SRC_UID_ )                             \
    lx_assert_fn(LX_C_BOOL(CONDITION_), _T(#CONDITION_), SRC_UID_,    \
                 __FUNCTION__, __FILE__, __LINE__)                /*#*/
#else
#define LX_ASSERT( CONDITION_, SRC_UID_ )       \
    lx_bool_reflect(LX_C_BOOL(CONDITION_))  /*#*/
#endif                                                   /* !DEBUG && !_DEBUG */

#if !defined LX_ERR
#define LX_ERR( MESSAGE_, SRC_UID_ )  LX_DEBUG_BREAK
#endif

#if !defined LX_ERR_2
#define LX_ERR_2( MESSAGE_, MSG_2_, SRC_UID_ )  LX_DEBUG_BREAK
#endif

#if !defined LX_OS_ERR
#define LX_OS_ERR( MESSAGE_, SRC_UID_ )  LX_DEBUG_BREAK
#endif

#if !defined LX_VERIFY
#define LX_VERIFY( CONDITION_, SRC_UID_ )           \
    { if (!(CONDITION_)) { LX_DEBUG_BREAK; } }  /*#*/
#endif

#if !defined LX_OS_VERIFY
#define LX_OS_VERIFY( CONDITION_, SRC_UID_ )        \
    { if (!(CONDITION_)) { LX_DEBUG_BREAK; } }  /*#*/
#endif

#if !defined LX_WARN
#define LX_WARN( MESSAGE_, SRC_UID_ )                                          \
    { uint32_t  lx_uid = SRC_UID_; lx_uid++; lx_uid--; LX_DEBUG_BREAK; }   /*#*/
#endif

#if !defined LX_OS_WARN
#define LX_OS_WARN( MESSAGE_, SRC_UID_ )                                       \
    { uint32_t  lx_uid = SRC_UID_; lx_uid++; lx_uid--; LX_DEBUG_BREAK; }   /*#*/
#endif

#if !defined LX_WARN_2
#define LX_WARN_2( MESSAGE_, MSG_2_, SRC_UID_ )                                \
    { uint32_t  lx_uid = SRC_UID_; lx_uid++; lx_uid--; LX_DEBUG_BREAK; }   /*#*/
#endif

#if !defined LX_WARN_3
#define LX_WARN_3( MESSAGE_, MSG_2_, MSG_3_, SRC_UID_ )                        \
    { uint32_t  lx_uid = SRC_UID_; lx_uid++; lx_uid--; LX_DEBUG_BREAK; }   /*#*/
#endif

#if !defined LX_WARN_4
#define LX_WARN_4( MESSAGE_, MSG_2_, MSG_3_, MSG_4_, SRC_UID_ )  \
    { uint32_t  lx_uid = SRC_UID_; lx_uid++; lx_uid--;           \
        LX_DEBUG_BREAK; }                                    /*#*/
#endif

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

extern unsigned int  lx_counter;

/* Just a function that returns the same boolean it's been passed.            */
/* it's created to prevent GCC/CLANG warnings on LX_ASSERT                    */
LX_PUBLIC lx_bool  lx_bool_reflect( const lx_bool  condition_ );           /*F*/

#if defined DEBUG || defined _DEBUG
LX_PUBLIC lx_bool  lx_assert_fn(                                           /*F*/
    const lx_bool   assert_,                                               /*-*/
    lx_chars_t      assert_text_,                                          /*-*/
    const uint32_t  src_uid_,                                              /*-*/
    const char*     source_func_,                                          /*-*/
    const char*     source_file_,                                          /*-*/
    const int       source_line_ );                                        /*-*/
#endif                                     /* defined DEBUG || defined _DEBUG */

LX_END_NAMESPACE  /*lx_c*/

#endif                                                                   /*eof*/
