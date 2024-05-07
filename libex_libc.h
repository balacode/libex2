/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                        [libex_libc.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_LIBC_H
#define      INCLUDED_LIBEX_LIBC_H

#include "libex_config.h"
#include "libex.h"

#if LX_PLATFORM_LINUX
#include <stdio.h>
#endif

#if LX_PLATFORM_WIN32
#include <conio.h>  /* for _getch()   */
#include <share.h>  /* for _SH_DENYNO */
#include <tchar.h>  /* Windows: _getts_s()  _istalpha()  _istlower()  etc.    */
#endif

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

/* -------------------------------------------------------------------------- */
/* Linux Development Stuff:                                                   */

#if LX_PLATFORM_LINUX
#define LX_IMPLEMENT_LINUX( )   lx_implement_linux(__func__, __FILE__, __LINE__)
#define LX_DL                printf("ran line %d in %s()\n", __LINE__, __func__)
#else
#define LX_DL  /* prints the line and function being executed */
#endif

LX_PUBLIC void  lx_implement_linux(                                        /*F*/
    const char*  source_func_,                                             /*-*/
    const char*  source_file_,                                             /*-*/
    const int    source_line_ );                                           /*-*/

/* -------------------------------------------------------------------------- */
/* ctype.h / wchar.h                                                          */

/* ISALPHA_T(): Check if a character is an alphabetic character. */
/* ISDIGIT_T(): Check if a character is a numeric character.     */
/* TOLOWER_T(): Convert a character to lower case.               */
/* TOUPPER_T(): Convert a character to upper case.               */

#if defined UNICODE || defined _UNICODE
#define ISALPHA_T( INT_CHARACTER_ )     iswalpha(INT_CHARACTER_)           /*F*/
#define ISDIGIT_T( INT_CHARACTER_ )     iswdigit(INT_CHARACTER_)           /*F*/
#define TOLOWER_T( INT_CHARACTER_ )     towlower(INT_CHARACTER_)           /*F*/
#define TOUPPER_T( INT_CHARACTER_ )     towupper(INT_CHARACTER_)           /*F*/
#else
#define ISALPHA_T( INT_CHARACTER_ )     isalpha(INT_CHARACTER_)            /*F*/
#define ISDIGIT_T( INT_CHARACTER_ )     isdigit(INT_CHARACTER_)            /*F*/
#define TOLOWER_T( INT_CHARACTER_ )     tolower(INT_CHARACTER_)            /*F*/
#define TOUPPER_T( INT_CHARACTER_ )     toupper(INT_CHARACTER_)            /*F*/
#endif

#define TOLOWER                         tolower           /*no-args-def*/  /*F*/
#define TOUPPER                         toupper           /*no-args-def*/  /*F*/
#define TOWLOWER                        towlower          /*no-args-def*/  /*F*/
#define TOWUPPER                        towupper          /*no-args-def*/  /*F*/

/* -------------------------------------------------------------------------- */
/* float.h (Win32) / math.h (Linux)                                           */

#if LX_PLATFORM_LINUX

#if defined _ISOC99_SOURCE
#define ISNAN  isnan                                      /*no-args-def*/  /*F*/
#else
#define ISNAN( value__ )  ((value__) != (value__))
#endif

#endif                                                   /* LX_PLATFORM_LINUX */

#if LX_PLATFORM_WIN32
#define ISNAN  _isnan                                     /*no-args-def*/  /*F*/
#endif

//lxcv

/* -------------------------------------------------------------------------- */
/* malloc.h (with extensions)                                                 */

/* Extended Memory Management Functions: */

#if 000

#define lx_stack( )  lx_stack_src(LX_STR(__FILE__), __LINE__)              /*F*/

LX_PUBLIC void  lx_stack_src(                                              /*F*/
    lx_chars_t  filename_,                                                 /*-*/
    const int   source_line_ );                                            /*-*/

#define lx_unstack( )  lx_unstack_src(LX_STR(__FILE__), __LINE__)          /*F*/

LX_PUBLIC void  lx_unstack_src(                                            /*F*/
    lx_chars_t  filename_,                                                 /*-*/
    const int   source_line_ );                                            /*-*/

#define lx_unstack_and_retain( MEMORY_BLOCK_PTR_ )                        /*F*/\
    lx_unstack_and_retain_src(MEMORY_BLOCK_PTR_,                               \
                              LX_STR(__FILE__), __LINE__)                  /*#*/

LX_PUBLIC void*  lx_unstack_and_retain_src(                                /*F*/
    void*       mem_alloc_,                                                /*-*/
    lx_chars_t  filename_,                                                 /*-*/
    const int   source_line_ );                                            /*-*/

#endif                                                                 /* 000 */

/* FREE... */
#define FREE( MEMORY_BLOCK_PTR_ )                                         /*F*/\
    LX_CL lx_free_id(MEMORY_BLOCK_PTR_, LX_STR(__FILE__), __LINE__)        /*#*/
#if !defined FREE
#define FREE( MEMORY_BLOCK_PTR_ )                                         /*F*/\
    free(MEMORY_BLOCK_PTR_)                                                /*#*/
#endif                                                               /* !FREE */

LX_PUBLIC void  lx_free_id(                                                /*F*/
    void*       mem_alloc_,                                                /*-*/
    lx_chars_t  filename_,                                                 /*-*/
    const int   source_line_ );                                            /*-*/

LX_PUBLIC void  lx_free_all( void );                                       /*F*/

/* MALLOC...() */
#define MALLOC( SIZE_IN_BYTES_ )                                          /*F*/\
    LX_CL lx_malloc_id(SIZE_IN_BYTES_, LX_STR(__FILE__), __LINE__)         /*#*/
#if !defined MALLOC
#define MALLOC( SIZE_IN_BYTES_ )  malloc(SIZE_IN_BYTES_)                   /*F*/
#endif                                                             /* !MALLOC */

LX_PUBLIC void*  lx_malloc_id(                                             /*F*/
    const size_t  size_in_bytes_,                                          /*-*/
    lx_chars_t    filename_,                                               /*-*/
    const int     source_line_ );                                          /*-*/

LX_PUBLIC void  lx_mem_report( void );                                     /*F*/

/* REALLOC... */
#define REALLOC(   MEMORY_BLOCK_PTR_, SIZE_IN_BYTES_ )                    /*F*/\
    lx_realloc_id( MEMORY_BLOCK_PTR_, SIZE_IN_BYTES_,                          \
                   LX_STR(__FILE__), __LINE__)                             /*#*/

#if !defined REALLOC
#define REALLOC( MEMORY_BLOCK_PTR_, SIZE_IN_BYTES_ )                      /*F*/\
    realloc(     MEMORY_BLOCK_PTR_, SIZE_IN_BYTES_)                        /*#*/
#endif                                                            /* !REALLOC */

LX_PUBLIC void*  lx_realloc_id(                                            /*F*/
    void*         mem_alloc_,                                              /*-*/
    const size_t  size_in_bytes_,                                          /*-*/
    lx_chars_t    filename_,                                               /*-*/
    const int     source_line_ );                                          /*-*/

/* Debugging / Informative Functions: */

LX_PUBLIC lx_bool  lx_mem_check( void );                                   /*F*/

LX_PUBLIC int  lx_mem_pending( void );                                     /*F*/

LX_PUBLIC void  lx_mem_static( const size_t  size_in_bytes_ );             /*F*/

/* -------------------------------------------------------------------------- */
/* math.h / stdlib.h or wchar.h                                               */

/* ATOF_T(): Convert a string to double. */
/* ATOI_T(): Convert a string to int.    */

#if defined UNICODE || defined _UNICODE
#define ATOF_T( STRING_ )  _wtof(STRING_)                                  /*F*/
#define ATOI_T( STRING_ )  _wtoi(STRING_)                                  /*F*/
#else                                                  /* UNICODE || _UNICODE */
#define ATOF_T( STRING_ )  atof(STRING_)                                   /*F*/
#define ATOI_T( STRING_ )  atoi(STRING_)                                   /*F*/
#endif                                               /* !UNICODE && !_UNICODE */

#define POW  pow                                          /*no-args-def*/  /*F*/

/* -------------------------------------------------------------------------- */
/* memory.h / string.h                                                        */

#define MEMCMP  memcmp                                    /*no-args-def*/  /*F*/

/* MEMCPY(): Copies bytes between buffers. */
#if defined _MSC_VER && _MSC_VER >= 1400  /* VS2005 */
#define MEMCPY( DEST_, SRC_, BYTES_LEN_ )                                 /*F*/\
    memcpy_s(   DEST_, BYTES_LEN_, SRC_, BYTES_LEN_)                       /*#*/
#else
#define MEMCPY( DEST_, SRC_, BYTES_LEN_ )                                 /*F*/\
    memcpy(     DEST_, SRC_, BYTES_LEN_)                                   /*#*/
#endif

/* MEMMOVE(): Moves one buffer to another. */
#if defined _MSC_VER && _MSC_VER >= 1400  /* VS2005 */
#define MEMMOVE( DEST_, SRC_, BYTES_LEN_ )                                /*F*/\
    memmove_s(   DEST_, BYTES_LEN_, SRC_, BYTES_LEN_)                      /*#*/
#else
#define MEMMOVE( DEST_, SRC_, BYTES_LEN_ )                                /*F*/\
    memmove(     DEST_, SRC_, BYTES_LEN_)                                  /*#*/
#endif

#define MEMSET   memset                                   /*no-args-def*/  /*F*/
#define STRCMP   strcmp                                   /*no-args-def*/  /*F*/
#define STRNCMP  strncmp                                  /*no-args-def*/  /*F*/
#define STRRCHR  strrchr                                  /*no-args-def*/  /*F*/
#define WCSCPY   wcscpy                                   /*no-args-def*/  /*F*/

/* -------------------------------------------------------------------------- */
/* stdio.h                                                                    */

/* FPRINTF_T(): Print formatted data to a stream. <stdio.h>                */
#if defined _MSC_VER && _MSC_VER >= 1400  /* VS2005 */
#define FPRINTF_T( STREAM_, FORMAT_, ... )                                /*F*/\
    _ftprintf_s(   STREAM_, FORMAT_, __VA_ARGS__)                          /*#*/
#elif defined UNICODE || defined _UNICODE
#define FPRINTF_T( STREAM_, FORMAT_, ... )                                /*F*/\
    fwprintf(      STREAM_, FORMAT_, __VA_ARGS__)                          /*#*/
#else
#define FPRINTF_T( STREAM_, FORMAT_, ... )                                /*F*/\
    fprintf(       STREAM_, FORMAT_, ## __VA_ARGS__)                       /*#*/
#endif

/* PRINTF_T(): Print formatted output to the standard output stream.       */
#if defined UNICODE || defined _UNICODE
#define PRINTF_T   wprintf                                /*no-args-def*/  /*F*/
#else
#define PRINTF_T   printf                                 /*no-args-def*/  /*F*/
#endif

/* SNPRINTF_T(): Write formatted data to a string. <stdio.h> */
#if defined _MSC_VER && _MSC_VER >= 1400  /* VS2005 */
#define SNPRINTF_T( BUF_, BUF_SIZE_, FORMAT_, ... )                       /*F*/\
    _stprintf_s(    BUF_, BUF_SIZE_, FORMAT_, __VA_ARGS__)                 /*#*/
#elif defined UNICODE || defined _UNICODE
#define SNPRINTF_T( BUF_, BUF_SIZE_, FORMAT_, ... )                       /*F*/\
    swprintf(       BUF_, BUF_SIZE_, FORMAT_, __VA_ARGS__)                 /*#*/
#elif defined _ISOC99_SOURCE
#define SNPRINTF_T( BUF_, BUF_SIZE_, FORMAT_, ... )                       /*F*/\
    snprintf(       BUF_, BUF_SIZE_, FORMAT_, __VA_ARGS__)                 /*#*/
#else
#define SNPRINTF_T( BUF_, BUF_SIZE_, FORMAT_, ... )                       /*F*/\
    sprintf(        BUF_,            FORMAT_, __VA_ARGS__)                 /*#*/
#endif

/* SNPRINTF(): Write formatted data to a string. <stdio.h> */
#if defined _MSC_VER && _MSC_VER >= 1400  /* VS2005 */
#define SNPRINTF( BUF_, BUF_SIZE_, FORMAT_, ... )                         /*F*/\
    sprintf_s(    BUF_, BUF_SIZE_, FORMAT_, __VA_ARGS__)                   /*#*/
#else
#define SNPRINTF( BUF_, BUF_SIZE_, FORMAT_, ... )                         /*F*/\
    snprintf(     BUF_, BUF_SIZE_, FORMAT_, __VA_ARGS__)                   /*#*/
#endif

/* SWPRINTF_S(): Write formatted data to a string. <stdio.h> */
#if defined _MSC_VER && _MSC_VER >= 1400  /* VS2005 */
#define SWPRINTF_S( BUF_, BUF_SIZE_, FORMAT_, ... )                       /*F*/\
    swprintf_s(     BUF_, BUF_SIZE_, FORMAT_, __VA_ARGS__)                 /*#*/
#else
#define SWPRINTF_S( BUF_, BUF_SIZE_, FORMAT_, ... )                       /*F*/\
    swprintf(       BUF_, BUF_SIZE_, FORMAT_, __VA_ARGS__)                 /*#*/
#endif

/* SSCANF_T(): Read formatted data from a string.. <stdio.h> */
#if defined _MSC_VER && _MSC_VER >= 1400  /* VS2005 */
#define SSCANF_T( BUFFER_, FORMAT_, ... )                                 /*F*/\
    _stscanf_s(   BUFFER_, FORMAT_, __VA_ARGS__)                           /*#*/
#elif defined UNICODE || defined _UNICODE
#define SSCANF_T( BUFFER_, FORMAT_, ... )                                 /*F*/\
    swscanf(      BUFFER_, FORMAT_, __VA_ARGS__)                           /*#*/
#else
#define SSCANF_T( BUFFER_, FORMAT_, ... )                                 /*F*/\
    sscanf(       BUFFER_, FORMAT_, __VA_ARGS__)                           /*#*/
#endif

#define FCLOSE         fclose                             /*no-args-def*/  /*F*/
#define FFLUSH         fflush                             /*no-args-def*/  /*F*/
#define FGETPOS        fgetpos                            /*no-args-def*/  /*F*/
#define FOPEN          fopen                              /*no-args-def*/  /*F*/
#define FPRINTF        fprintf                            /*no-args-def*/  /*F*/
#define FREAD          fread                              /*no-args-def*/  /*F*/
#define FSEEK          fseek                              /*no-args-def*/  /*F*/
#define FWPRINTF       fwprintf                           /*no-args-def*/  /*F*/
#define FWRITE         fwrite                             /*no-args-def*/  /*F*/
#define SNTPRINTF      _sntprintf                         /*no-args-def*/  /*F*/
#define SPRINTF        sprintf                            /*no-args-def*/  /*F*/
#define VSNPRINTF_S    _vsnprintf_s                       /*no-args-def*/  /*F*/
#define VSNWPRINTF_S   _vsnwprintf_s                      /*no-args-def*/  /*F*/
#define WFOPEN         _wfopen                            /*no-args-def*/  /*F*/

/* -------------------------------------------------------------------------- */
/* stdlib.h                                                                   */

#if !defined _MSC_VER
typedef int  errno_t;
#endif

LX_PUBLIC errno_t  lx_itot_fn(                                             /*F*/
    const int     value_,                                                  /*-*/
    lx_char_t*    buffer_,                                                 /*-*/
    const size_t  buffer_chars_len_,                                       /*-*/
    const int     base_ );                                                 /*-*/

/* STRTOL_T(): Convert a string to an unsigned long-integer value.         */
#if defined UNICODE || defined _UNICODE
#define STRTOL_T( STRING_, END_PTR_, RADIX_ )                             /*F*/\
    wcstol(       STRING_, END_PTR_, RADIX_)                               /*#*/
#else
#define STRTOL_T( STRING_, END_PTR_, RADIX_ )                             /*F*/\
    strtol(       STRING_, END_PTR_, RADIX_)                               /*#*/
#endif

/* STRTOUL_T(): Convert a string to an unsigned long-integer value.        */
#if defined UNICODE || defined _UNICODE
#define STRTOUL_T( STRING_, END_PTR_, RADIX_ )                            /*F*/\
    wcstoul(       STRING_, END_PTR_, RADIX_)                              /*#*/
#else
#define STRTOUL_T( STRING_, END_PTR_, RADIX_ )                            /*F*/\
    strtoul(       STRING_, END_PTR_, RADIX_)                              /*#*/
#endif

/* ULTOA_T(): Convert an unsigned long integer to a string.                */
#if defined _MSC_VER && _MSC_VER >= 1400  /* VS2005 */
#define ULTOA_T( VALUE_, DEST_, DEST_SIZE_, RADIX_ )                      /*F*/\
    _ultot_s(    VALUE_, DEST_, DEST_SIZE_, RADIX_)                        /*#*/
#elif defined UNICODE || defined _UNICODE
#define ULTOA_T( VALUE_, DEST_, DEST_SIZE_, RADIX_ )                      /*F*/\
    _ultow(      VALUE_, DEST_,             RADIX_)                        /*#*/
#else
#define ULTOA_T( VALUE_, DEST_, DEST_SIZE_, RADIX_ )                      /*F*/\
    _ultoa(      VALUE_, DEST_,             RADIX_)                        /*#*/
#endif

/* ITOA() */
#define ITOA lx_itoa_fn
LX_PUBLIC errno_t  lx_itoa_fn(                                             /*F*/
    const int     value_,                                                  /*-*/
    char*         buffer_,                                                 /*-*/
    const size_t  buffer_chars_len_,                                       /*-*/
    const int     base_ );                                                 /*-*/
LX_PUBLIC lx_bool  lx_test_itoa_fn( void );                                /*F*/

/* ITOW() */
#define ITOW lx_itow_fn
LX_PUBLIC errno_t  lx_itow_fn(                                             /*F*/
    const int     value_,                                                  /*-*/
    wchar_t*      buffer_,                                                 /*-*/
    const size_t  buffer_chars_len_,                                       /*-*/
    const int     base_ );                                                 /*-*/

#define MBSTOWCS( DEST_, SOURCE_, MAX_COUNT_ )                            /*F*/\
    mbstowcs(     DEST_, SOURCE_, MAX_COUNT_)                              /*#*/

#define PRINTF    printf                                  /*no-args-def*/  /*F*/
#define QSORT     qsort                                   /*no-args-def*/  /*F*/
#define RAND      rand                                    /*no-args-def*/  /*F*/
#define SRAND     srand                                   /*no-args-def*/  /*F*/
#define STRTOL    strtol                                  /*no-args-def*/  /*F*/
#define WCSTOMBS  wcstombs                                /*no-args-def*/  /*F*/

/* -------------------------------------------------------------------------- */
/* string.h / wchar.h                                                         */

/* STRCAT_S_T(): Append a string. */
#if defined _MSC_VER && _MSC_VER >= 1400  /* VS2005 */
#define STRCAT_S_T( DEST_, DEST_SIZE_, SRC_ )                             /*F*/\
    _tcscat_s(      DEST_, DEST_SIZE_, SRC_)                               /*#*/
#elif defined UNICODE || defined _UNICODE
#define STRCAT_S_T( DEST_, DEST_SIZE_, SRC_ )                             /*F*/\
    wcscat(         DEST_,             SRC_)                               /*#*/
#else
#define STRCAT_S_T( DEST_, DEST_SIZE_, SRC_ )                             /*F*/\
    strcat(         DEST_,             SRC_)                               /*#*/
#endif

/* STRCHR_T(): Pointer to a character found in a string.. */
#if defined UNICODE || defined _UNICODE
#define STRCHR_T( STRING_, CHAR_ )   wcschr(STRING_, CHAR_)                /*F*/
#else
#define STRCHR_T( STRING_, CHAR_ )  strchr(STRING_, CHAR_)                 /*F*/
#endif

/* STRCMP_T(): compare strings (0 if equal, < 0 if STR_1_ < STR_2_) */
#if defined UNICODE || defined _UNICODE
#define STRCMP_T( STR_1_, STR_2_ )  wcscmp(STR_1_, STR_2_)                 /*F*/
#else
#define STRCMP_T( STR_1_, STR_2_ )  strcmp(STR_1_, STR_2_)                 /*F*/
#endif

/* STRCPY_S_T(): copy one string to another */
#if defined _MSC_VER && _MSC_VER >= 1400  /* VS2005 */
#define STRCPY_S_T( DEST_, DEST_SIZE_, SRC_ )                             /*F*/\
    _tcscpy_s(      DEST_, DEST_SIZE_, SRC_)                               /*#*/
#elif defined UNICODE || defined _UNICODE
#define STRCPY_S_T( DEST_, DEST_SIZE_, SRC_ )                             /*F*/\
    wcscpy(         DEST_,             SRC_)                       /* wchar.h */
#else
#define STRCPY_S_T( DEST_, DEST_SIZE_, SRC_ )                             /*F*/\
    strcpy(         DEST_,             SRC_)                      /* string.h */
#endif

/* STRICMP_T(): Perform a lowercase comparison of strings */
LX_PUBLIC int  STRICMP_T(                                                  /*F*/
    lx_chars_t  string1_,                                                  /*-*/
    lx_chars_t  string2_ );                                                /*-*/

/* STRLEN_T(): get the length of a string: strlen(), wcslen() */
#if defined UNICODE || defined _UNICODE   /* ctype.h */
#define STRLEN_T( STRING_ )                                               /*F*/\
    (LX_CAST(lx_chars_t , STRING_) == 0 || *(STRING_) == 0 ?                   \
     0 : wcslen(STRING_))                                          /* wchar.h */
#else
#define STRLEN_T( STRING_ )                                               /*F*/\
    (LX_CAST(lx_chars_t , STRING_) == 0 || *(STRING_) == 0 ?                   \
     0 : strlen(STRING_))                                         /* string.h */
#endif

/* STRNCAT_S_T(): Append a string. */
#if defined _MSC_VER && _MSC_VER >= 1400  /* VS2005 */
#define STRNCAT_S_T( DEST_, DEST_SIZE_, SRC_, COUNT_ )                    /*F*/\
    _tcsncat_s(      DEST_, DEST_SIZE_, SRC_, COUNT_)                      /*#*/
#elif defined UNICODE || defined _UNICODE
#define STRNCAT_S_T( DEST_, DEST_SIZE_, SRC_, COUNT_ )                    /*F*/\
    wcsncat(         DEST_,             SRC_, COUNT_)                      /*#*/
#else
#define STRNCAT_S_T( DEST_, DEST_SIZE_, SRC_, COUNT_ )                    /*F*/\
    strncat(         DEST_,             SRC_, COUNT_)                      /*#*/
#endif

/* STRNCMP_T(): compare N characters of two strings. */
#if defined UNICODE || defined _UNICODE
#define STRNCMP_T( STR_1_, STR_2_, COUNT_ )                               /*F*/\
    wcsncmp(       STR_1_, STR_2_, COUNT_)                                 /*#*/
#else
#define STRNCMP_T( STR_1_, STR_2_, COUNT_ )                               /*F*/\
    strncmp(       STR_1_, STR_2_, COUNT_)                                 /*#*/
#endif

/* STRNCPY_S_T(): copy N characters of one string to another */
#if defined _MSC_VER && _MSC_VER >= 1400  /* VS2005 */
#define STRNCPY_S_T( DEST_, DEST_SIZE_, SRC_, COUNT_ )                    /*F*/\
    _tcsncpy_s(      DEST_, DEST_SIZE_, SRC_, COUNT_)                      /*#*/
#elif defined UNICODE || defined _UNICODE
#define STRNCPY_S_T( DEST_, DEST_SIZE_, SRC_, COUNT_ )                    /*F*/\
    wcsncpy(         DEST_,             SRC_, COUNT_)              /* wchar.h */
#else
#define STRNCPY_S_T( DEST_, DEST_SIZE_, SRC_, COUNT_ )                    /*F*/\
    strncpy(         DEST_,             SRC_, COUNT_)                      /*#*/
#endif

/* STRSPN_T(): return index of first character in string that */
/* doesn't belong to a set of characters. (string.h)                          */
#if defined UNICODE || defined _UNICODE
#define STRSPN_T( STRING_, CHARSET_ )                                     /*F*/\
    wcsspn(       STRING_, CHARSET_)                                       /*#*/
#else
#define STRSPN_T( STRING_, CHARSET_ )                                     /*F*/\
    strspn(       STRING_, CHARSET_)                                       /*#*/
#endif

/* STRSTR_T(): Pointer to first occurrence of a substring */
#if defined UNICODE || defined _UNICODE
#define STRSTR_T( STRING_, SUBSTR_ )                                      /*F*/\
    wcsstr(       STRING_, SUBSTR_)                                /* wchar.h */
#else
#define STRSTR_T( STRING_, SUBSTR_ )                                      /*F*/\
    strstr(       STRING_, SUBSTR_)                               /* string.h */
#endif

/* STRUPR_T(): Convert a string to uppercase. */
#if defined _MSC_VER && _MSC_VER >= 1400  /* VS2005 */
#define STRUPR_T( STRING_, SIZE_ )                                        /*F*/\
    _tcsupr_s(    STRING_, SIZE_)                                          /*#*/
#elif defined UNICODE || defined _UNICODE
#define STRUPR_T( STRING_ )                                               /*F*/\
    _strupr(      STRING_)                                                 /*#*/
#else
#define STRUPR_T( STRING_ )                                               /*F*/\
    _wcsupr(      STRING_)                                                 /*#*/
#endif

/* STRCAT_S(): Append a string.                                            */
#if defined _MSC_VER && _MSC_VER >= 1400  /* VS2005 */
#define STRCAT_S( DEST_, DEST_SIZE_, SRC_ )                               /*F*/\
    strcat_s(     DEST_, DEST_SIZE_, SRC_)                                 /*#*/
#else
#define STRCAT_S( DEST_, DEST_SIZE_, SRC_ )                               /*F*/\
    strcat(       DEST_,             SRC_)                                 /*#*/
#endif

/* WCSCAT_S(): Append a wide string.                                       */
#if defined _MSC_VER && _MSC_VER >= 1400  /* VS2005 */
#define WCSCAT_S( DEST_, DEST_SIZE_, SRC_ )                               /*F*/\
    wcscat_s(     DEST_, DEST_SIZE_, SRC_)                                 /*#*/
#else
#define WCSCAT_S( DEST_, DEST_SIZE_, SRC_ )                               /*F*/\
    wcscat(       DEST_,             SRC_)                                 /*#*/
#endif

#define STRCHR     strchr                                 /*no-args-def*/  /*F*/
#define STRCMP     strcmp                                 /*no-args-def*/  /*F*/
#define STRCPY     strcpy                                 /*no-args-def*/  /*F*/
#define STRLEN     strlen                                 /*no-args-def*/  /*F*/
#define STRSTR     strstr                                 /*no-args-def*/  /*F*/
#define WCSLEN     wcslen                                 /*no-args-def*/  /*F*/
#define WCSRTOMBS  wcsrtombs                              /*no-args-def*/  /*F*/
#define WCSSTR     wcsstr                                 /*no-args-def*/  /*F*/

/* -------------------------------------------------------------------------- */
/* tchar.h                                                                    */

#define _GETTS_S     _getts_s                           /*no-args-def*/    /*F*/
#define _ISTALPHA    _istalpha                          /*no-args-def*/    /*F*/
#define _ISTLOWER    _istlower                          /*no-args-def*/    /*F*/
#define _ISTUPPER    _istupper                          /*no-args-def*/    /*F*/
#define _PUTTS       _putts                             /*no-args-def*/    /*F*/
#define _STPRINTF_S  _stprintf_s                        /*no-args-def*/    /*F*/
#define _ULTOT_S     _ultot_s                           /*no-args-def*/    /*F*/

/* FOPEN_S_T(): open a file (without sharing). <stdio.h> */
#if defined _MSC_VER && _MSC_VER >= 1400  /* VS2005 */
#define FOPEN_S_T  _tfopen_s                              /*no-args-def*/  /*F*/
#else
LX_PUBLIC errno_t  FOPEN_S_T(                                              /*F*/
    FILE**      file_ptr_ptr_,                                             /*-*/
    lx_chars_t  filename_,                                                 /*-*/
    lx_chars_t  mode_ );                                                   /*-*/
#endif

/* FSOPEN_T(): open a file (with sharing). <stdio.h> */
#if defined _MSC_VER && _MSC_VER >= 1400  /* VS2005 */
#define FSOPEN_T                        _tfsopen          /*no-args-def*/  /*F*/
#define lx_fsopen                       _fsopen           /*no-args-def*/  /*F*/
#else
LX_PUBLIC FILE*  FSOPEN_T(                                                 /*F*/
    lx_chars_t  filename_,                                                 /*-*/
    lx_chars_t  mode_,                                                     /*-*/
    const int   share_flag_ );                                             /*-*/
#endif

/* -------------------------------------------------------------------------- */
/* time.h                                                                     */

#define STRFTIME                        strftime          /*no-args-def*/  /*F*/

/* -------------------------------------------------------------------------- */
/* time.inl                                                                   */

#define GMTIME                          gmtime            /*no-args-def*/  /*F*/
#define LOCALTIME                       localtime         /*no-args-def*/  /*F*/
#define TIME                            time              /*no-args-def*/  /*F*/

#if LX_PLATFORM_LINUX
#define CLOCK_GETTIME  clock_gettime  /* In GCC/Clang: add -lrt */
#endif

/* -------------------------------------------------------------------------- */
/* Miscellaneous OS:                                                          */

#define SETSOCKOPT                      setsockopt   /* WinSock.h, WinSock2.h */

#if LX_PLATFORM_LINUX
#define CLOSE                           close             /*no-args-def*/  /*F*/
#define CLOSEDIR                        closedir          /*no-args-def*/  /*F*/
#define FSTAT                           fstat             /*no-args-def*/  /*F*/
#define OPEN                            open              /*no-args-def*/  /*F*/
#define OPENDIR                         opendir           /*no-args-def*/  /*F*/
#define READ                            read              /*no-args-def*/  /*F*/
#define READDIR                         readdir           /*no-args-def*/  /*F*/
#define SIGNAL                          signal            /*no-args-def*/  /*F*/
#define STAT                            stat              /*no-args-def*/  /*F*/
#define STRNCASECMP                     strncasecmp       /*no-args-def*/  /*F*/
#define SYSTEM                          system            /*no-args-def*/  /*F*/
#endif                                                   /* LX_PLATFORM_LINUX */

/* -------------------------------------------------------------------------- */
LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
