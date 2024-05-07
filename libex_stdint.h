/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                      [libex_stdint.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_STDINT_H
#define      INCLUDED_LIBEX_STDINT_H

#if defined _MSC_VER && _MSC_VER < 1300
typedef signed char       int8_t;
typedef signed short      int16_t;
typedef signed int        int32_t;
typedef unsigned char     uint8_t;
typedef unsigned short    uint16_t;
typedef unsigned int      uint32_t;

#elif defined _MSC_VER
typedef signed __int8     int8_t;
typedef signed __int16    int16_t;
typedef signed __int32    int32_t;
typedef signed __int64    int64_t;
typedef unsigned __int8   uint8_t;
typedef unsigned __int16  uint16_t;
typedef unsigned __int32  uint32_t;
typedef unsigned __int64  uint64_t;

#else
#include <stdint.h>
#endif

/* typedef signed long long    int64_t;  */
/* typedef unsigned long long  uint64_t; */

#endif                                                                   /*eof*/
