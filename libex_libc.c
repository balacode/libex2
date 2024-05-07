/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                        [libex_libc.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_libc_.h"
#if defined INCLUDED_LIBEX_LIBC_H

#include "libex_config_.h"

#include <ctype.h>   /* for tolower()                  */
#include <limits.h>  /* for INT_MIN, INT_MAX           */
#include <stdio.h>   /* for printf()                   */
#include <stdlib.h>  /* for free(), malloc(), strtol() */
#include <string.h>  /* for memset()                   */

#if PLATFORM_LINUX
#include <fcntl.h>           /* For O_* constants */
#include <semaphore.h>
#include <sys/stat.h>        /* For mode constants */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
#include "libex_win32_.h"
#endif

#include "libex_call_.h"
#include "libex_const_.h"
#include "libex_debug_.h"
#include "libex_error_.h"
#include "libex_macro_.h"
#include "libex_.h"
#include "libex_type_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#if defined __GNUC__ && !defined __MINGW32__
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wundef"
#endif
#if defined __clang__
#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#endif
#if defined _MSC_VER
#pragma warning (disable:4555)  /* W:L1 expression has no effect              */
#pragma warning (disable:4710)  /* W:L4 function not inlined                  */
#pragma warning (disable:4711)  /* W:L1 functn. selected for inline expansion */
#endif

#define _PVAL( POINTER_ )  ((unsigned long)(POINTER_))


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


/* -------------------------------------------------------------------------- */
/* Linux Development Stuff:                                                   */


PUBLIC void  implement_linux(                                              /*F*/
    const char*  source_func_,                                             /*-*/
    const char*  source_file_,                                             /*-*/
    const int    source_line_ ) {                                          /*-*/
    GO                                                            (UID(F3F229));
    /*BREAKPOINT*/
    printf("IMPLEMENT_LINUX: %s()  line: %d  file: %s\n",
           source_func_, source_line_, source_file_);
    RETURN(NIL);
} /* implement_linux */


/* -------------------------------------------------------------------------- */


/* FSOPEN_T(): open a file (with sharing). <stdio.h>                       */
#if !(defined _MSC_VER && _MSC_VER >= 1400)  /* VS2005 */
PUBLIC FILE*  FSOPEN_T(                                                    /*F*/
    chars_t    filename_,                                                  /*-*/
    chars_t    mode_,                                                      /*-*/
    const int  share_flag_ ) {                                             /*-*/
    GO                                                            (UID(F3EA72));
    IMPLEMENT_LINUX();  /* TODO: implement FSOPEN_T() on Linux */
    UNUSED(filename_);
    UNUSED(mode_);
    UNUSED(share_flag_);

    RETURN(NULL);
} /* FSOPEN_T */
#endif                                                   /* !_MSC_VER >= 1400 */


PUBLIC errno_t  itoa_fn(                                                   /*F*/
    const int     value_,                                                  /*-*/
    char*         buffer_,                                                 /*-*/
    const size_t  buffer_chars_len_,                                       /*-*/
    const int     base_ ) {                                                /*-*/
    GO                                                            (UID(F81044));
    static const char*  cdigits = "0123456789abcdefghijklmnopqrstuv";

    uint64_t  len   = 0;
    uint64_t  digit = 0;
    uint64_t  div   = 0;
    char*     wr    = buffer_;
    errno_t   ret   = 0;  /* returns 0 if all is OK, or error code */

    /* use 64-bit unsigned integers so INT_MIN/INT_MAX can be handled */
    /* if the number is negative, first make it positive              */
    const bool  negative = C_BOOL(value_ < 0);

    uint64_t  val = CAST(uint64_t, negative ? -CAST(int64_t, value_) : value_);

    if (base_ < 2 || base_ > 32) {
        *wr = 0;
        WARN(_T("invalid base_"), UID(EA67F0));
        RETURN(1);
    }

    /* calculate length of number (len) and value of divisor (div) */
    div = 1;

    do {
        div *= base_;
        len++;
    } while (div <= val);

    div /= base_;

    if ((negative ? 1 : 0) + len > (buffer_chars_len_ - 1)) {
        *wr = 0;
        WARN(_T("buffer overrun."), UID(EE50A1));
        RETURN(2);
    }

    /* iterate and write each digit starting from the most significant */
    if (negative) {
        *wr++ = '-';
    }

    while (len--) {
        digit = div == 0 ? 0 : val / div;
        *wr++ = cdigits[CAST(int, digit & 0xFFFF)];
        val -= (digit * div);
        div /= base_;
    }
    *wr = 0;

    RETURN(ret);
} /* itoa_fn */


PUBLIC bool  test_itoa_fn( void ) {                                        /*F*/
    GO                                                            (UID(F4BA6A));
    int   index     = 0;
    int   base      = 0;
    int   val       = 0;
    int   val_check = 0;
    char  buf[50];

    static const int  test_values[49] = {
        0, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        -1, -2, -3, -4, -5, -6, -7, -8, -9, -10,
        -11, -12, -13, -14, -15, -16, -17, -18, -19, -20,
        INT_MIN, (INT_MIN + 1), 0, (INT_MAX - 1), INT_MAX,
        1000000001, -1000000001, 999999999, -999999999
    };

    bool  ret = true;

    for (index = 0; index < 49; index++) {
        for (base = 32; base <= 32; base++) {
            val = test_values[index];
            MEMSET(buf, 0x00, 50 * sizeof(char));
            itoa_fn(val, buf, 50, base);
            val_check = STRTOL(buf, 0, base);

            if (val_check != val) {
                ret = false;
                PRINTF_T(_T("\r\n") _T("Failed: itoa_fn() ")
                         _T("value_ = %d, base_ = %d"), val, base);
                break;
            }
        }
    }
    RETURN(ret);
} /* test_itoa_fn */


PUBLIC errno_t  itow_fn(                                                   /*F*/
    const int     value_,                                                  /*-*/
    wchar_t*      buffer_,                                                 /*-*/
    const size_t  buffer_chars_len_,                                       /*-*/
    const int     base_ ) {                                                /*-*/
    GO                                                            (UID(F8A7B7));
    char*         narrow = CAST(char*, buffer_);
    wchar_t*      wide   = buffer_;
    errno_t       result = itoa_fn(value_, narrow, buffer_chars_len_, base_);
    const size_t  len    = STRLEN(narrow);
    size_t        i      = len;

    do {
        wide[i] = CAST(wchar_t, narrow[i]);
    } while (i-- > 0);

    RETURN(result);
} /* itow_fn */


PUBLIC errno_t  itot_fn(                                                   /*F*/
    const int     value_,                                                  /*-*/
    char_t*       buffer_,                                                 /*-*/
    const size_t  buffer_chars_len_,                                       /*-*/
    const int     base_ ) {                                                /*-*/
    GO                                                            (UID(F16DC5));
#if defined UNICODE || defined _UNICODE
    const errno_t  ret = itow_fn(value_, buffer_, buffer_chars_len_, base_);
#else
    const errno_t  ret = itoa_fn(value_, buffer_, buffer_chars_len_, base_);
#endif
    RETURN(ret);
} /* itot_fn */


// TODO: change function name ``
PUBLIC int  STRICMP_T(                                                     /*F*/
    chars_t  string1_,                                                     /*-*/
    chars_t  string2_ ) {                                                  /*-*/
    GO                                                            (UID(F47888));
    int  ret = 0;

    if (string1_ && string2_) {
        while (*string1_ != '\0' && *string2_ != '\0' &&
               TOLOWER(*string1_) == TOLOWER(*string2_)) {
            string1_++;
            string2_++;
        }
    }

    if ((string1_ == NULL && string2_ == NULL) ||
        (*string1_ == '\0' && *string2_ == '\0')) {
        ret = 0;

    } else if (*string1_ < *string2_) {
        ret = -1;

    } else if (*string1_ > *string2_) {
        ret = 1;
    }
    RETURN(ret);
} /* STRICMP_T */


/* -------------------------------------------------------------------------- */

#if PLATFORM_LINUX
PUBLIC errno_t  FOPEN_S_T(                                                 /*F*/
    FILE**   file_ptr_ptr_,                                                /*-*/
    chars_t  filename_,                                                    /*-*/
    chars_t  mode_ ) {                                                     /*-*/
    GO                                                            (UID(FC4EC3));
    errno_t  ret = 0;

#if defined UNICODE || defined _UNICODE
    *file_ptr_ptr_ = _wfopen(filename_, mode_);
#else                                                  /* UNICODE || _UNICODE */
    *file_ptr_ptr_ = fopen(filename_, mode_);
#endif                                               /* !UNICODE && !_UNICODE */

    RETURN(ret);
} /* FOPEN_S_T */
#endif                                                      /* PLATFORM_LINUX */


/* -------------------------------------------------------------------------- */


/* Removed PUBLIC to avoid                                                    */
/* Error C2732 linkage specification contradicts earlier specification        */
bool  assert_fn(                                                           /*F*/
    const bool      assert_,                                               /*-*/
    chars_t         assert_text_,                                          /*-*/
    const uint32_t  src_uid_,                                              /*-*/
    const char*     source_func_,                                          /*-*/
    const char*     source_file_,                                          /*-*/
    const int       source_line_ ) {                                       /*-*/
    GO                                                            (UID(F183D7));
    UNUSED(assert_text_);
    UNUSED(source_func_);
    UNUSED(source_file_);
    UNUSED(source_line_);

    if (!assert_) {
        WARN(assert_text_, src_uid_);
    }

#if 000
    if (!assert_) {
        char  buf[512];
        CLEAR_N(buf, 512);

        PRINTF(buf, 512,
               "\r\n" "Assertion Failed:"
               "\r\n" "%s"
               "\r\n"
               "\r\n" " Srce. ID:\t    UID(%08XU)"
               "\r\n" " Function:\t    %s()"
               "\r\n" " Filename:\t    %s"
               "\r\n" " line no.:\t    %d",
               assert_text_, src_uid_, func_name_, filename_, source_line_);

        puts(buf);
        MessageBoxA_win(NULL, buf, _T("!ASSERT (debug: SHIFT+ENTER)"), 0);

        if (0 > GetKeyState_win(VK_SHIFT_win)) {
            __debugbreak();
        }
    }
#endif                                                                 /* 000 */

    RETURN(assert_);
} /* assert_fn */


PUBLIC bool  bool_reflect( const bool  condition_ ) {                      /*F*/
    GO                                                            (UID(FC8817));
    RETURN(condition_);
} /* bool_reflect */


/* -------------------------------------------------------------------------- */
/* Functions: Memory Management                                               */


typedef struct  _header_t {
    /* prev_block and next_block actually point to _header_t structures: */
    uint8_t*  prev_block;                                        /* _header_t */
    uint8_t*  next_block;                                        /* _header_t */
    size_t    block_size;                                        /* _header_t */

#if defined MEM_DEBUG && MEM_DEBUG > 0
    int       alloc_no_debug;                                    /* _header_t */
    chars_t   src_file_debug;                                    /* _header_t */
    int       src_line_debug;                                    /* _header_t */
#endif                                                       /* MEM_DEBUG > 0 */
}
_header_t;


#define _header( VARIABLE_ )   CAST(_header_t*, VARIABLE_)


static size_t       _mem_static_size = 0;
static size_t       _mem_static_used = 0;
static uint8_t*     _mem_static_mem  = NULL;

static size_t       _mem_alloc_count = 0;
static size_t       _mem_alloc_size  = 0;
static size_t       _mem_freed_count = 0;
static size_t       _mem_freed_size  = 0;
static size_t       _mem_error_count = 0;
static _header_t*  _mem_first       = NULL;
static _header_t*  _mem_last        = NULL;


#if defined MEM_DEBUG && MEM_DEBUG > 0
#define _IF_MEM_DEBUG( CODE_STATEMENTS_ )   CODE_STATEMENTS_
#else
#define _IF_MEM_DEBUG( CODE_STATEMENTS_ )
#endif


#if defined MEM_DEBUG && MEM_DEBUG > 0
static uint32_t  _check_link_fn_call_count = 0;
static uint32_t  _mem_alloc_call_count     = 0;
static uint32_t  _mem_free_call_count      = 0;
static uint32_t  _mem_liink_end_call_count = 0;
static uint32_t  _mem_offset_call_count    = 0;
static uint32_t  _mem_unlink_call_count    = 0;
static uint32_t  call_count_alloc_id       = 0;
static uint32_t  call_count_free_all       = 0;
static uint32_t  call_count_free_id        = 0;
static uint32_t  call_count_mem_check      = 0;
static uint32_t  call_count_mem_pending    = 0;
static uint32_t  call_count_mem_report     = 0;
static uint32_t  call_count_realloc_id     = 0;
#endif                                                       /* MEM_DEBUG > 0 */


#if defined MEM_DEBUG && MEM_DEBUG > 0
static int  _mem_serial = 0;

#define _SIGNATURE_SIZE  54

static const uint8_t  _mem_guard_signature[_SIGNATURE_SIZE] = {
    0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9,
    0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9,
    0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9,
    0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9,
    0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9,
    0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9,
};
#endif                                                       /* MEM_DEBUG > 0 */


#if defined MEM_DEBUG && MEM_DEBUG > 0

#define _check_link( PREV_, NEXT_ )                     \
    _check_link_fn(_header(PREV_), _header(NEXT_))  /*#*/

static void  _check_link_fn(                                               /*F*/
    _header_t*  prev_,                                                     /*-*/
    _header_t*  next_ ) {                                                  /*-*/
    GO                                                            (UID(FA6322));
    _IF_MEM_DEBUG(_check_link_fn_call_count++);

    if (_mem_static_size > 0 && prev_ && next_ && prev_ >= next_) {
        WARN(_T("prev_ >= next_"), UID(E36613));
    }
    RETURN(NIL);
} /* _check_link */

#else                                                     /* MEM_DEBUG > 0 */
#define _check_link( PREV_, NEXT_ )                                        /*F*/
#endif                                                          /* !MEM_DEBUG */


#if defined MEM_DEBUG && MEM_DEBUG >= 2
static unsigned long  _mem_offset( void*  address_ ) {                     /*F*/
    GO                                                            (UID(F1F4F3));
    unsigned long  ret = 0;

    _IF_MEM_DEBUG(_mem_offset_call_count++);

    if (address_ == NULL) {
        ret = 0;

    } else if (_mem_static_size != 0) {
        ret = CAST(unsigned long, CAST(uint8_t*, address_)
                   - CAST(uint8_t*, _mem_static_mem));
    } else {
        ret = CAST(unsigned long, address_);
    }
    RETURN(ret);
} /* _mem_offset */
#endif                                                      /* MEM_DEBUG >= 2 */


static void*  _mem_alloc( const size_t  size_ ) {                          /*F*/
    GO                                                            (UID(FAE193));
    uint8_t*  ret = NULL;

    _IF_MEM_DEBUG(_mem_alloc_call_count++);

    if (_mem_static_size == 0) {

#if PLATFORM_WIN32 && defined MEM_USE_OS_FUNCTIONS
        const HANDLE_win  heap   = GetProcessHeap_win();
        const BOOL_win    result = HeapValidate_win(heap, 0, NULL);

        if (result == FALSE_win) {
            WARN(_T("HeapValidate() failed."), UID(EFC2BF));
        }

        ret = CAST(uint8_t*, HeapAlloc_win(CAST(HANDLE_win, heap),
                                           HEAP_ZERO_MEMORY_win,
                                           CAST(DWORD_win, size_)));
        if (ret == NULL) {
            WARN(_T("HeapAlloc() returned NULL"), UID(E775D6));
        }
#else                           /* ^ PLATFORM_WIN32 && MEM_USE_OS_FUNCTIONS ^ */

        ret = malloc(size_);
#endif
    } else {
        const size_t  free_bytes = _mem_static_size - _mem_static_used;

        if (size_ > free_bytes) {
            WARN(_T("No more static bytes to allocate!"), UID(EC7835));
            ret = NULL;
        } else {
            ret = CAST(uint8_t*, _mem_static_mem) + _mem_static_used;
            MEMCPY(ret, &size_, sizeof(size_t));
            ret += sizeof(size_t);
            _mem_static_used += (sizeof(size_t) + size_);
        }
    }
    RETURN(ret);
} /* _mem_alloc */


static void  _free( void*  mem_block_ ) {                                  /*F*/
    GO                                                            (UID(F26CC4));
    _IF_MEM_DEBUG(_mem_free_call_count++);

    if (_mem_static_size == 0) {

#if PLATFORM_WIN32 && defined MEM_USE_OS_FUNCTIONS
        const HANDLE_win  heap   = GetProcessHeap_win();
        const BOOL_win    result = HeapFree_win(heap, 0, mem_block_);

        if (result == FALSE_win) {
            WARN(system_error_name(0), UID(EBB6E0));
        }
#else                           /* ^ PLATFORM_WIN32 && MEM_USE_OS_FUNCTIONS ^ */

        free(mem_block_);
#endif
    } else { /* read the block size */
        size_t  bytes_size = 0;
        MEMCPY(&bytes_size, CAST(uint8_t*, mem_block_) - sizeof(size_t),
               sizeof(size_t));
        MEMSET(mem_block_, 0xFF, bytes_size);
    }
    RETURN(NIL);
} /* _free */


static void  _mem_liink_end( _header_t*  header_ ) {                       /*F*/
    GO                                                            (UID(FBE6C2));
    _IF_MEM_DEBUG(_mem_liink_end_call_count++);
    ASSERT(header_->next_block == NULL, UID(E3FC54));

    if ((_mem_alloc_count - _mem_freed_count) == 1) {
        _mem_first = header_;
    } else {
        _header_t*  last = _mem_last;

        if (last != NULL) {
            ASSERT(last->next_block == NULL, UID(E0B0FD));
            last->next_block = CAST(uint8_t*, header_);
            header_->prev_block = CAST(uint8_t*, last);
            _check_link(last, last->next_block);
            _check_link(header_->prev_block, header_);
        }
    }
    _mem_last = header_;

    RETURN(NIL);
} /* _mem_liink_end */


static void  _mem_unlink( _header_t*  header_ ) {                          /*F*/
    GO                                                            (UID(F14AC0));
    _IF_MEM_DEBUG(_mem_unlink_call_count++);

    /* link previous and next blocks, unlinking header_ from the chain */
    if (header_->prev_block != NULL) {
        ASSERT(_header(header_->prev_block)->next_block
               == CAST(uint8_t*, header_), UID(E86746));

        _header(header_->prev_block)->next_block = header_->next_block;

        _check_link(header_->prev_block,
                    _header(header_->prev_block)->next_block);
    }

    if (header_->next_block != NULL) {
        ASSERT(_header(header_->next_block)->prev_block
               == CAST(uint8_t*, header_), UID(E98577));

        _header(header_->next_block)->prev_block =
            CAST(uint8_t*, header_->prev_block);

        _check_link(_header(header_->next_block)->prev_block,
                    header_->next_block);
    }

    /* update global list pointers (pointers to head and tail of list) */
    if (_mem_first == header_) {
        ASSERT(header_->prev_block == NULL, UID(EC7A76));
        _mem_first = _header(header_->next_block);
    }

    if (_mem_last == header_) {
        ASSERT(header_->next_block == NULL, UID(ED7190));
        _mem_last = _header(header_->prev_block);
    }
    RETURN(NIL);
} /* _mem_unlink */


static void  _mem_critical_sectn( const bool  begin_critical_sectn_ ) {    /*F*/
    /* never put GO here */
#if PLATFORM_LINUX
    /* the semaphore is created in /dev/shm */
    sem_t*  sem = sem_open("/base_libc.lx",
                           O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO, 1);

    if (sem == SEM_FAILED) {
        WARN(system_error_name(errno), UID(E6DDD4));

    } else if (begin_critical_sectn_) {
        if (sem_wait(sem) == -1) {
            WARN(system_error_name(errno), UID(E520E9));
        }
    } else {
        if (sem_post(sem) == -1) {
            WARN(system_error_name(errno), UID(E44D29));
        }
    }
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    {
        static bool                  initialized = false;
        static CRITICAL_SECTION_win  critical_sectn;

        if (initialized == false) {
            InitializeCriticalSection_win(&critical_sectn);
            initialized = true;
        }

        if (begin_critical_sectn_) {
            EnterCriticalSection_win(&critical_sectn);
        } else {
            LeaveCriticalSection_win(&critical_sectn);
        }
    }
#endif                                                      /* PLATFORM_WIN32 */

    /* never put RETURN here */
} /* _mem_critical_sectn */


/* -------------------------------------------------------------------------- */


PUBLIC void  free_id(                                                      /*F*/
    void*      mem_alloc_,                                                 /*-*/
    chars_t    filename_,                                                  /*-*/
    const int  source_line_ ) {                                            /*-*/
    GO                                                            (UID(FBB72B));
    _mem_critical_sectn(true);

    _IF_MEM_DEBUG(call_count_free_id++);
    _IF_MEM_DEBUG(_mem_serial++);
    _IF_MEM_DEBUG(mem_check());

    UNUSED(filename_);
    UNUSED(source_line_);

    /* FREE() called without prior call to malloc_id() */
    ASSERT(_mem_alloc_count > 0, UID(E94DD2));

    if (mem_alloc_ == NULL) {
        WARN(_T("mem_alloc_ == NULL"), UID(EEA829));
    }

    if (_mem_alloc_count > 0 &&
        mem_alloc_ != NULL    &&
        mem_alloc_ != CAST(uint8_t*, BLANK)) {

        uint8_t*  freed_bytes = CAST(uint8_t*, mem_alloc_) - sizeof(_header_t);
        _header_t*  freed_header = CAST(_header_t*, freed_bytes);
        const size_t  size = sizeof(_header_t) + freed_header->block_size;

        _mem_unlink(freed_header);
        _mem_freed_count++;
        _mem_freed_size += freed_header->block_size;
        MEMSET(freed_bytes, 0x00, size);

#if defined MEM_DEBUG && MEM_DEBUG >= 2
        {
            DUMP_OPEN;
            DUMP(_T("\r")
                 _T("%3d 0x%08lX %8lu^ [%5lu bytes] FREE() -> about to free"),
                 _mem_serial,
                 _PVAL(freed_bytes),
                 _mem_offset(freed_bytes),
                 freed_bytes);
            DUMP_CLOSE;
        }
#endif                                                      /* MEM_DEBUG >= 2 */

        _free(freed_bytes);

#if defined MEM_DEBUG && MEM_DEBUG >= 2
        {
            DUMP_OPEN;
            DUMP(
                _T("\r")
                _T("%3d 0x%08lX %8lu^ [%5lu bytes] FREE() -> freed"),
                _mem_serial,
                _PVAL(freed_bytes),
                _mem_offset(freed_bytes),
                freed_bytes);
            DUMP_CLOSE;
        }
#endif                                                       /* MEM_DEBUG >= 2*/
    }

    _mem_critical_sectn(false);
    RETURN(NIL);
} /* free_id */


PUBLIC void  free_all( void ) {                                            /*F*/
    GO                                                            (UID(FE8EC0));
    size_t  serial_no = 0;
    size_t  allocated = _mem_alloc_count - _mem_freed_count;

    _IF_MEM_DEBUG(call_count_free_all++);

    while (allocated > 0) {
        _header_t*  last = _mem_last;

        if (_mem_last == NULL) {
            WARN(_T("_mem_last == NULL"), UID(E34B12));
            break;
        } else {
            void*  alloc_last = CAST(uint8_t*, last) + sizeof(_header_t);
            FREE(alloc_last);
            allocated = _mem_alloc_count - _mem_freed_count;
            serial_no++;
        }
    }

    /* this while() loop should not normally be entered */
    allocated = _mem_alloc_count - _mem_freed_count;

    while (allocated > 0) {
        _header_t*  first = _mem_first;

        WARN(_T("Not all items freed by using _mem_last."), UID(E9D3A7));

        if (_mem_first == NULL) {
            WARN(_T("_mem_first == NULL"), UID(E5CC4E));
            break;
        } else {
            void*  alloc_first = CAST(uint8_t*, first) + sizeof(_header_t);
            FREE(alloc_first);
            allocated = _mem_alloc_count - _mem_freed_count;
            serial_no++;
        }
    }
    RETURN(NIL);
} /* free_all */


PUBLIC void*  malloc_id(                                                   /*F*/
    const size_t  size_in_bytes_,                                          /*-*/
    chars_t       filename_,                                               /*-*/
    const int     source_line_ ) {                                         /*-*/
    GO                                                            (UID(F8E6D3));
    void*  ret = NULL;

    _mem_critical_sectn(true);

    _IF_MEM_DEBUG(call_count_alloc_id++);  /* malloc_id() # */
    _IF_MEM_DEBUG(_mem_serial++);
    _IF_MEM_DEBUG(mem_check());

    ASSERT(size_in_bytes_ > 0, UID(EB0B36));

    if (size_in_bytes_ > 0) {
        size_t      bytes_size = sizeof(_header_t) + size_in_bytes_;
        _header_t*  new_header = NULL;

        _IF_MEM_DEBUG(bytes_size += _SIGNATURE_SIZE);

        new_header = CAST(_header_t*, _mem_alloc(bytes_size));

        if (new_header == NULL) {
            WARN(_T("_mem_alloc() returned NULL"), UID(EECF51));
        }

#if defined MEM_DEBUG && MEM_DEBUG >= 2
        {
            DUMP_OPEN;
            DUMP(
                _T("\r")
                _T("%3d 0x%08lX %8lu^ [%5lu bytes]")
                _T(" malloc_id() #%u allocated"),
                _mem_serial,
                _PVAL(new_header),
                _mem_offset(new_header),
                bytes_size,
                call_count_alloc_id);
            DUMP_CLOSE;
        }
#endif                                                      /* MEM_DEBUG >= 2 */

        if (new_header == NULL) {
            _mem_error_count++;
            ret = NULL;
        } else {
            MEMSET(new_header, 0x00, bytes_size);

#if defined MEM_DEBUG && MEM_DEBUG > 0
            {
                uint8_t*  signature = CAST(uint8_t*, new_header)
                                      + bytes_size - _SIGNATURE_SIZE;

                MEMCPY(signature, _mem_guard_signature, _SIGNATURE_SIZE);
            }
#endif                                                       /* MEM_DEBUG > 0 */

            _mem_alloc_count++;
            _mem_alloc_size += size_in_bytes_;

            new_header->block_size = size_in_bytes_;

#if defined MEM_DEBUG && MEM_DEBUG > 0
            new_header->src_file_debug = filename_;
            new_header->src_line_debug = source_line_;
            new_header->alloc_no_debug = _mem_alloc_count;

#if defined MEM_DEBUG && MEM_DEBUG > 0
#define _MEM_SN_UNFREED  000  /* <=== UNFREED */
#endif

            if (new_header->alloc_no_debug == _MEM_SN_UNFREED) {
                DEBUG_BREAK;
            }
#else                                                     /* MEM_DEBUG > 0 */
            UNUSED(filename_);
            UNUSED(source_line_);
#endif                                                          /* !MEM_DEBUG */

            new_header->prev_block = CAST(uint8_t*, _mem_last);
            new_header->next_block = NULL;

            _check_link(new_header->prev_block, new_header);
            _check_link(new_header, new_header->next_block);

            if (_mem_first == NULL) {
                _mem_first = new_header;
            }

            if (_mem_last != NULL) {
                _mem_last->next_block = CAST(uint8_t*, new_header);
                _check_link(_mem_last,
                            _header(_mem_last->next_block));
            }

            _mem_last = new_header;

            ret = CAST(uint8_t*, new_header) + sizeof(_header_t);
        }
    }

    _mem_critical_sectn(false);

    RETURN(ret);
} /* malloc_id */


#if defined MEM_DEBUG && MEM_DEBUG > 0
static int  _write_to_debug_log(                                           /*F*/
    const char*  filename_,                                                /*-*/
    const char*  text_ ) {                                                 /*-*/
    GO                                                            (UID(F68A7E));
    int           err_no = 0;
    const size_t  len    = STRLEN(text_);

    if (len > 0) {
#if PLATFORM_LINUX
        UNUSED(filename_);
        UNUSED(text_);
        IMPLEMENT_LINUX();  /* TODO: Implement _write_to_debug_log() Lnx. */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
        DWORD_win  fsize      = 0;
        DWORD_win  bytes_writ = 0;

        /* open the file */
        const HANDLE_win  file =
            CreateFileA_win(
                filename_,                  /* file name            */
                GENERIC_WRITE_win,          /* desired access       */
                FILE_SHARE_READ_win,        /* share mode           */
                NULL,                       /* security attributes) */
                OPEN_ALWAYS_win,            /* creation disposition */
                FILE_ATTRIBUTE_NORMAL_win,  /* flags and attributes */
                NULL);                      /* template file        */

        if (file == INVALID_HANDLE_VALUE_win) {
            err_no = 1;
        }

        /* get the file size */
        if (err_no == 0) {
            fsize = GetFileSize_win(file, NULL);
            if (fsize == INVALID_FILE_SIZE_win) {
                err_no = 2;
            }
        }

        /* lock the file to prevent other processes from writing to it */
        if (err_no == 0) {
            const DWORD_win  begun  = GetTickCount_win();
            BOOL_win         locked = FALSE_win;

            /* attempt to acquire lock in 2 seconds */
            while (!locked && GetTickCount_win() < begun + 2000) {
                locked =
                    LockFile_win(
                        file,                                        /* file  */
                        CAST(DWORD_win, fsize),             /*dwFileOffsetLow */
                        0,                                /* dwFileOffsetHigh */
                        fsize,                     /* nNumberOfBytesToLockLow */
                        0);                       /* nNumberOfBytesToLockHigh */

                if (!locked) {
                    Sleep_win(250);
                }
            }

            if (!locked) {
                err_no = 3;
            }
        }

        /* move file pointer to the write position */
        if (err_no == 0 && SetFilePointer_win(
                file,                   /* file                 */
                CAST(LONG, fsize),      /* lDistanceToMove      */
                0,                      /* lpDistanceToMoveHigh */
                FILE_BEGIN_win)         /* dwMoveMethod         */
            == INVALID_SET_FILE_POINTER_win) {
            err_no = 4;
        }

        /* write to the file */
        if (err_no == 0 && !WriteFile_win(
                file,                  /* file                   */
                text_,                 /* lpBuffer               */
                CAST(DWORD_win, len),  /* nNumberOfBytesToWrite  */
                &bytes_writ,           /* lpNumberOfBytesWritten */
                NULL)) {               /* lpOverlapped           */
            err_no = 5;
        }

        /* close the opened file */
        if (err_no != 1 && !CloseHandle_win(file)) {
            err_no = 6;
        }
#endif                                                      /* PLATFORM_WIN32 */
    }
    RETURN(err_no);
} /* _write_to_debug_log */
#endif                                          /* MEM_DEBUG && MEM_DEBUG > 0 */


PUBLIC void  mem_report( void ) {                                          /*F*/
    GO                                                            (UID(F82EFF));
    bool  mem_debug = false;

    _IF_MEM_DEBUG(mem_debug = true);
    _IF_MEM_DEBUG(call_count_mem_report++);

    {
        const uint32_t  pending = _mem_alloc_count - _mem_freed_count;
        const uint32_t  alloc   = _mem_alloc_count;
        const uint32_t  freed   = _mem_freed_count;
        const uint32_t  failed  = _mem_error_count;

        PRINTF_T(
            _T("\r\n\r\n") _T("%s") _T("mem_report():   ")
            _T("Pending: %u   Alloc: %u   Freed: %u   Failed: %u"),
            (mem_debug ? _T("MEM_DEBUG mode") _T("\r\n") : BLANK),
            pending, alloc, freed, failed);
    }

#if defined MEM_DEBUG && MEM_DEBUG > 0
    {
        int                sn     = 0;
        const _header_t*  header = _mem_first;

        while (header) {
            const int       alloc_no   = header->alloc_no_debug;
            chars_t         src_file   = header->src_file_debug;
            const int       src_line   = header->src_line_debug;
            const size_t    block_size = header->block_size;
            const uint32_t  addr       = _PVAL(CAST(uint8_t*, header)
                                               + sizeof(_header_t));
            sn++;

#if defined _MSC_VER
            {
                char*  buf = malloc(512);  /* don't use MALLOC() here */
                MEMSET(buf, 0x00, 512);

                SNPRINTF(buf, 512,
                         "\r" "_MEM_SN_UNFREED:%4d in %s:%4d"
                         " Addr:0x%08lX Size: %5lu (0x%00lX)",
                         alloc_no, src_file, src_line,
                         addr, block_size, block_size);

                _write_to_debug_log(DEBUG_LOG_FILE, buf);

                free(buf);  /* don't use FREE() here */
            }
#endif                                                                 /* 000 */

#if 000
            _MEM_SN_UNFREED;
#endif

            PRINTF_T(_T("\r\n") _T("_MEM_SN_UNFREED:%04d in %s:%4d")
                     _T(" Addr:0x%08lX Size: %5lu (0x%00lX)"),
                     alloc_no, src_file, src_line,
                     addr, block_size, block_size);

            header = _header(header->next_block);
        }
    }
#endif                                                       /* MEM_DEBUG > 0 */

    RETURN(NIL);
} /* mem_report */


PUBLIC void*  realloc_id(                                                  /*F*/
    void*         mem_alloc_,                                              /*-*/
    const size_t  size_in_bytes_,                                          /*-*/
    chars_t       source_file_,                                            /*-*/
    const int     source_line_ ) {                                         /*-*/
    GO                                                            (UID(F6F2F4));
    _mem_critical_sectn(true);

    UNUSED(source_file_);
    UNUSED(source_line_);

    _IF_MEM_DEBUG(call_count_realloc_id++);  /* realloc_id() # */
    _IF_MEM_DEBUG(mem_check());

    /* if size_in_bytes_ is zero, just return mem_alloc_ */
    if (size_in_bytes_ < 1) {
        _mem_critical_sectn(false);
        RETURN(mem_alloc_);
    } else {
        size_t    old_size  = 0;
        uint8_t*  old_alloc = NULL;
        uint8_t*  new_alloc = NULL;

        /* get pointers & size of existing memory block, before reallocation  */
        if (mem_alloc_ != NULL) {
            old_alloc = CAST(uint8_t*, mem_alloc_) - sizeof(_header_t);
            {
                _header_t*  old_header = CAST(_header_t*, old_alloc);
                old_size = old_header->block_size;

                if (size_in_bytes_ > old_size) {
                    _mem_unlink(old_header);
                }
            }
        }

        /* re-allocate the memory block */
        new_alloc = old_alloc;

        if (size_in_bytes_ > old_size) {
            /* 'gross' new size includes the size of the header, the data     */
            /* size (size_in_bytes_) and the guarding signature in debug mode */
            size_t  gross_new_size = sizeof(_header_t) + size_in_bytes_;
            _IF_MEM_DEBUG(gross_new_size += _SIGNATURE_SIZE);

            if (_mem_static_size == 0) {
#if PLATFORM_WIN32 && defined MEM_USE_OS_FUNCTIONS

                const HANDLE_win  heap = GetProcessHeap_win();

                if (old_alloc == NULL) {
                    new_alloc =
                        CAST(uint8_t*,
                             HeapAlloc_win(
                                 heap, HEAP_ZERO_MEMORY_win,
                                 CAST(DWORD_win, gross_new_size)));
                } else {
                    new_alloc =
                        CAST(uint8_t*,
                             HeapReAlloc_win(
                                 heap,
                                 HEAP_ZERO_MEMORY_win,
                                 old_alloc,
                                 CAST(DWORD_win, gross_new_size)));
                }
#else                           /* ^ PLATFORM_WIN32 && MEM_USE_OS_FUNCTIONS ^ */

                new_alloc =
                    CAST(uint8_t*, realloc(old_alloc, gross_new_size));
#endif
            } else {
                /* read the old block size */
                old_size = 0;
                if (old_alloc != NULL) {
                    MEMCPY(&old_size,
                           CAST(uint8_t*, old_alloc) - sizeof(size_t),
                           sizeof(size_t));
                }

                /* allocate the new block */
                new_alloc = CAST(uint8_t*, _mem_alloc(gross_new_size));

                if (new_alloc != NULL) {
                    if (old_alloc != NULL) {
                        /* copy data from the old block to the new block */
                        const size_t  nbytes = old_size < size_in_bytes_
                                               ? old_size : size_in_bytes_;
                        if (nbytes > 0) {
                            MEMCPY(new_alloc, old_alloc, nbytes);
                        }
                        MEMSET(old_alloc, 0xFF, old_size);
                    }
                    /* clear the unused part of the new block */
                    if (size_in_bytes_ > old_size) {
                        const size_t  nbytes = size_in_bytes_ - old_size;
                        MEMSET(new_alloc + old_size, 0x00, nbytes);
                    }
                }
            }
        }

#if defined MEM_DEBUG && MEM_DEBUG >= 2
        {
            DUMP_OPEN;
            DUMP(
                _T("\r") _T("%3d 0x%08lX %8lu^ [%5lu bytes]")
                _T(" realloc_id() #%u")
                _T(" re-allocated from 0x%08lX %8lu^ [%5lu bytes]"),
                _mem_serial,
                _PVAL(new_alloc),
                _mem_offset(new_alloc),
                size_in_bytes_,
                call_count_realloc_id,
                _PVAL(old_alloc),
                _mem_offset(old_alloc),
                old_size);
            DUMP_CLOSE;
        };
#endif                                                      /* MEM_DEBUG >= 2 */

        if (new_alloc == NULL) {
            _mem_error_count++;
            RETURN(NULL);
        }

        {
            _header_t*  new_header  = CAST(_header_t*, new_alloc);
            new_header->block_size = size_in_bytes_;

#if defined MEM_DEBUG && MEM_DEBUG > 0
            {
                uint8_t*  signature = CAST(uint8_t*, new_header)
                                      + sizeof(_header_t) + size_in_bytes_;

                MEMCPY(signature, _mem_guard_signature, _SIGNATURE_SIZE);
            }
            new_header->src_file_debug = source_file_;
            new_header->src_line_debug = source_line_;
            new_header->alloc_no_debug = _mem_alloc_count + 1;

            if (new_header->alloc_no_debug == _MEM_SN_UNFREED) {
                DEBUG_BREAK;
            }
#endif                                                       /* MEM_DEBUG > 0 */

            /* update global memory statistics */
            _mem_alloc_count++;
            _mem_alloc_size += size_in_bytes_;

            if (old_size > 0) {
                _mem_freed_count++;
                _mem_freed_size += old_size;
            }

            /* link new item to the end of the list                           */
            /* (also links the first item (when _mem_alloc_count == 1)        */
            /* so make sure _mem_liink_end() is called after incrementing it) */
            if (size_in_bytes_ > old_size) {
                new_header->next_block = NULL;
                _mem_liink_end(new_header);
            }

            {
                void*  ret = new_alloc + sizeof(_header_t);
                _mem_critical_sectn(false);
                RETURN(ret);
            }
        }
    }
} /* realloc_id */


PUBLIC bool  mem_check( void ) {                                           /*F*/
    GO                                                            (UID(F801D7));
    _header_t*  item             = _mem_first;
    bool        ret              = true;
    int         count_from_first = 0;
    int         count_from_last  = 0;

    const int  count_used_blocks =
        CAST(int, _mem_alloc_count - _mem_freed_count);

    _IF_MEM_DEBUG(call_count_mem_check++);

    while (item) {
#if defined MEM_DEBUG && MEM_DEBUG > 0
        /* check if memory beyond allocated block hasn't been overwritten */
        uint8_t*  signature = CAST(uint8_t*, item)
                              + sizeof(_header_t) + item->block_size;

        const int  result =
            MEMCMP(signature, _mem_guard_signature, _SIGNATURE_SIZE);

        if (result != 0) {
            WARN(_T("Memory written past end of block!"), UID(E57C82));
            ret = false;
        }

#endif                                                       /* MEM_DEBUG > 0 */

        /* check integrity of links to next and previous item */
        if (item->prev_block &&
            item->prev_block == item->next_block) {
            WARN(_T("item->prev_block == item->next_block"), UID(E8D09A));
            ret = false;
        }

        if (item && item == _header(item->next_block)) {
            WARN(_T("item == item->next_block"), UID(E1F523));
            ret = false;
        }

        if (item && item == _header(item->prev_block)) {
            WARN(_T("item == item->prev_block"), UID(E459A8));
            ret = false;
        }

        if (item && item->prev_block) {
            _header_t*  prev = _header(item->prev_block);

            if (_header(prev->next_block) != item) {
                WARN(_T("prev->next_block != item"), UID(E735C1));
                ret = false;
            }
        }

        if (item && item->next_block) {
            _header_t*  next = _header(item->next_block);

            if (_header(next->prev_block) != item) {
                WARN(_T("next->prev_block != item"), UID(E1A28C));
                ret = false;
            }
        }

        item = _header(item->prev_block);
    }

    /* count number of items in linked list, starting from the first item */
    if (_mem_first) {
        item = _mem_first;

        while (item) {
            count_from_first++;

            if (count_from_first > count_used_blocks) {
                item = _mem_first;
                count_from_first = 0;

                while (item &&
                       count_from_first < (count_used_blocks + 100)) {
#if defined MEM_DEBUG && MEM_DEBUG >= 2
                    DUMP_OPEN;
                    DUMP(
                        _T("\r") _T("CHECK: %3d")
                        _T(" <-0x%08lX %8lu^")
                        _T(" <-[0x%08lX %8lu^]->")
                        _T(" 0x%08lX %8lu^")
                        _T(" #%d"),
                        count_from_first,
                        _PVAL(item->prev_block),
                        _mem_offset(item->prev_block),
                        _PVAL(item),
                        _mem_offset(item),
                        _PVAL(item->next_block),
                        _mem_offset(item->next_block),
                        item->alloc_no_debug);
                    DUMP_CLOSE;
#endif                                                      /* MEM_DEBUG >= 2 */
                    count_from_first++;
                    item = _header(item->next_block);
                }

                WARN(_T("count_from_first > count_used_blocks"), UID(E124C9));
                ret = false;
                break;
            }

            item = _header(item->next_block);
        }

        if (count_from_first != count_used_blocks) {
            WARN(_T("count_from_first != count_used_blocks"), UID(E7F267));
            ret = false;
        }
    }

    /* count number of items in linked list, starting from the last item */
    if (_mem_last) {
        item = _mem_last;

        while (item) {
            count_from_last++;

            if (count_from_last > count_used_blocks) {
                WARN(_T("count_from_last > count_used_blocks"), UID(E4618A));
                ret = false;
                break;
            }

            item = _header(item->prev_block);
        }

        if (count_from_last != count_used_blocks) {
            WARN(_T("count_from_last != count_used_blocks"), UID(E60A24));
            ret = false;
        }
    }
    RETURN(ret);
} /* mem_check */


PUBLIC int  mem_pending( void ) {                                          /*F*/
    GO                                                            (UID(F68327));
    const int  ret = CAST(int, _mem_alloc_count - _mem_freed_count);
    _IF_MEM_DEBUG(call_count_mem_pending++);
    RETURN(ret);
} /* mem_pending */


PUBLIC void  mem_static( const size_t  size_in_bytes_ ) {                  /*F*/
    GO                                                            (UID(F3B3DE));
    if (size_in_bytes_ < 1) {
        WARN(_T("size_in_bytes_ < 1"), UID(E9F21C));
        RETURN(NIL);
    }

    if (_mem_static_size != 0    ||
        _mem_static_used != 0    ||
        _mem_alloc_count != 0    ||
        _mem_alloc_size  != 0    ||
        _mem_freed_count != 0    ||
        _mem_freed_size  != 0    ||
        _mem_error_count != 0    ||
        _mem_static_mem  != NULL ||
        _mem_first       != NULL ||
        _mem_last        != NULL) {

        WARN(_T("mem_static() called on memory in use"), UID(E4B6D9));
        RETURN(NIL);
    }

    /* allocate required memory */
    _mem_static_size = size_in_bytes_;
    _mem_static_mem  = CAST(uint8_t*, malloc(_mem_static_size));

    if (_mem_static_mem == NULL) {
        WARN(_T("One-time memory allocation failed."), UID(E9D876));
        RETURN(NIL);
    }

    MEMSET(_mem_static_mem, 0x00, _mem_static_size);

#if defined MEM_DEBUG && MEM_DEBUG >= 2
    {
        DUMP_OPEN;
        DUMP(
            _T("\r")
            _T("mem_static(%lu): _mem_static_mem address = 0x%08lX")
            _T("\r"),
            size_in_bytes_,
            _PVAL(_mem_static_mem));
        DUMP_CLOSE;
    }
#endif                                                      /* MEM_DEBUG >= 2 */

    RETURN(NIL);
} /* mem_static */


#if 000
PUBLIC void  stack_src(                                                    /*F*/
    chars_t    filename_,                                                  /*-*/
    const int  source_line_ ) {                                            /*-*/
    GO                                                            (UID(F4E651));
    _header_t*  header = NULL;

    _IF_MEM_DEBUG(call_count_stack_src++);
    _IF_MEM_DEBUG(_mem_serial++);
    _IF_MEM_DEBUG(mem_check());

    header = CAST(_header_t*, _mem_alloc(sizeof(_header_t)));

#if defined MEM_DEBUG && MEM_DEBUG >= 2
    {
        DUMP_OPEN;
        DUMP(
            _T("\r")
            _T("%3d 0x%08lX %8d^ [%5d] stack_src()")
            _T(" -> allocated sizeof(_header_t)"),
            _mem_serial,
            header,
            _mem_offset(header),
            sizeof(_header_t));
        DUMP_CLOSE;
    }
#endif                                                      /* MEM_DEBUG >= 2 */

    if (header == NULL) {
        _mem_error_count++;
        RETURN(NIL);
    }

    _mem_alloc_count++;

    memset(header, 0x00, sizeof(_header_t));
    header->block_size = 0;

#if defined MEM_DEBUG && MEM_DEBUG > 0
    header->src_file_debug = source_file_;
    header->src_line_debug = source_line_;
    header->alloc_no_debug = _mem_alloc_count;
#else                                                     /* MEM_DEBUG > 0 */
    UNUSED(filename_);
    UNUSED(source_line_);
#endif                                                          /* !MEM_DEBUG */

    header->prev_block = _mem_last;
    header->next_block = NULL;

    _check_link(header->prev_block, header);
    _check_link(header, header->next_block);

    if (_mem_first == NULL || _mem_alloc_count == 1) {
        _mem_first = header;
    }

    if (_mem_last != NULL) {
        _mem_last->next_block = header;
        _check_link(_mem_last, _mem_last->next_block);
    }

    _mem_last = header;
    RETURN(NIL);
} /* stack_src */
#endif                                                                 /* 000 */


#if 000
PUBLIC void  unstack_src(                                                  /*F*/
    chars_t    filename_,                                                  /*-*/
    const int  source_line_ ) {                                            /*-*/
    GO                                                            (UID(F183D5));
    _IF_MEM_DEBUG(call_count_unstack_src++);
    unstack_and_retain_src(NULL, filename_, source_line_);
    RETURN(NIL);
} /* unstack_src */
#endif                                                                 /* 000 */


#if 000
PUBLIC void*  unstack_and_retain_src(                                      /*F*/
    void*      mem_alloc_,                                                 /*-*/
    chars_t    filename_,                                                  /*-*/
    const int  source_line_ ) {                                            /*-*/
    GO                                                            (UID(F97BF9));
    bool         found_retain  = false;
    _header_t*  header        = _mem_last;
    _header_t*  header_retain = (mem_alloc_ == NULL)
                                ? NULL
                                : CAST(_header_t*,
                                       CAST(uint8_t*, mem_alloc_)
                                       - sizeof(_header_t));

    _IF_MEM_DEBUG(call_count++);

    UNUSED(filename_);
    UNUSED(source_line_);

    while (header) {
        void*   bytes      = NULL;
        size_t  bytes_size = 0;

        if (header == header_retain) {
            found_retain = true;
        } else {
            bytes = CAST(uint8_t*, header) + sizeof(_header_t);
            bytes_size = header->block_size;
        }

        header = _header(header->prev_block);

        if (bytes_size > 0) {
            FREE(bytes, filename_, source_line_);
        } else {
            if (found_retain) {
                if (header) {
                    header->next_block = header_retain;
                }
                header_retain->prev_block = header;
            }
            break;
        }
    }

    if (found_retain) {
        _mem_last = header_retain;

    } else if (mem_alloc_ != NULL) {
        WARN(_T("Retained memory block not in stack."), UID(EE4041));
    }
    RETURN(mem_alloc_);
} /* unstack_and_retain_src */
#endif                                                                 /* 000 */


/* -------------------------------------------------------------------------- */
/* Call Tracing and Statistics:                                               */

#define CALLS_MAX  10000000  /* 10 million */

typedef uint64_t  _time_t;


/* -------------------------------------------------------------------------- */
#if PLATFORM_LINUX           /* Linux Timing-Related Definitions: */

#define _CLOCK_TYPE  CLOCK_MONOTONIC
/* select one of the following clocks provided by the OS:                     */
/*                                                                            */
/* CLOCK_MONOTONIC:          arbitrary clock, for relative timing only        */
/* CLOCK_REALTIME:           system-wide realtime clock                       */
/* CLOCK_PROCESS_CPUTIME_ID: hi-res tmr. provided by CPU for each process     */
/* CLOCK_THREAD_CPUTIME_ID:  hi-res timer provided by CPU for each thread     */
/*                                                                            */
/* for clock_gettime() in GCC: add -lrt                                       */

#define _SET_HIGH_RESOLUTION_TIME( TIME_VAR_ )                    \
    {                                                             \
        struct timespec  time;                                    \
        CLOCK_GETTIME(_CLOCK_TYPE, &time);                        \
        TIME_VAR_ = (time.tv_sec * 1000000000 + time.tv_nsec);    \
    }                                                         /*#*/

#define _SET_HIGH_RESOLUTION_FREQUENCY( TIME_VAR_ )                    \
    TIME_VAR_ = 1000000000;  /* 1 billion nanoseconds / second */  /*#*/

#endif                                                      /* PLATFORM_LINUX */


/* -------------------------------------------------------------------------- */
#if PLATFORM_WIN32            /* Windows Timing-Related Definitions: */

#define _SET_HIGH_RESOLUTION_TIME( TIME_VAR_ )            \
    {                                                     \
        LARGE_INTEGER_win  perf_count = { 0, 0 };         \
        if (!QueryPerformanceCounter_win(&perf_count)) {  \
            DEBUG_BREAK;                                  \
        }                                                 \
        TIME_VAR_ = perf_count.QuadPart;                  \
    }                                                 /*#*/

#define _SET_HIGH_RESOLUTION_FREQUENCY( TIME_VAR_ )        \
    {                                                      \
        LARGE_INTEGER_win  frequency = { 0, 0 };           \
        if (!QueryPerformanceFrequency_win(&frequency)) {  \
            DEBUG_BREAK;                                   \
        }                                                  \
        TIME_VAR_ = frequency.QuadPart;                    \
    }                                                  /*#*/
#endif                                                      /* PLATFORM_WIN32 */


/* -------------------------------------------------------------------------- */
/* Call Tracing and Timing Data Types and Structures:                         */

#if defined CALL_TRACE && CALL_TRACE == 2

typedef struct  _call_t {
    uint32_t     fn_id;                                            /* _call_t */
    const char*  fn_name;                                          /* _call_t */
    _time_t      time;                                             /* _call_t */
    int16_t      depth;                                            /* _call_t */
    bool         entry;                                            /* _call_t */
}
_call_t;

typedef struct  _call_sum_t {
    uint32_t     serial_no;                                    /* _call_sum_t */
    uint32_t     fn_id;                                        /* _call_sum_t */
    uint32_t     call_count;                                   /* _call_sum_t */
    double       gross_seconds;                                /* _call_sum_t */
    double       net_seconds;                                  /* _call_sum_t */
    double       avg_net_sec_per_call;                         /* _call_sum_t */
    const char*  fn_name;                                      /* _call_sum_t */
}
_call_sum_t;

static bool      _immediate_call_trace = false;
static _time_t   _call_start_time      = 0;
static uint32_t  _call_capacity        = CALLS_MAX;
static uint32_t  _call_data_index      = 0;
static int16_t   _call_depth           = 0;
static _call_t*  _call_data            = NULL;

#endif                                                     /* CALL_TRACE == 2 */


/* -------------------------------------------------------------------------- */
/* Call Stack Functions:                                                      */


typedef struct  _source_ref_t {
    uint32_t     src_uid;                                    /* _source_ref_t */
    const char*  src_fn;                                     /* _source_ref_t */
    const char*  src_file;                                   /* _source_ref_t */
    int          src_line;                                   /* _source_ref_t */
}
_source_ref_t;


_source_ref_t  _call_stack[1000];
size_t          _call_stack_depth = 0;


#if defined CALL_TRACE && CALL_TRACE == 2
static void  _call_stack_push(                                             /*F*/
    const uint32_t  src_uid_,                                              /*-*/
    const char*     source_func_,                                          /*-*/
    const char*     source_file_,                                          /*-*/
    const int       source_line_ ) {                                       /*-*/
    if (_call_stack_depth == 0) {
        CLEAR(_call_stack);
    }

    {
        _source_ref_t*  call = &_call_stack[_call_stack_depth];

        call->src_uid  = src_uid_;
        call->src_fn   = source_func_;
        call->src_file = source_file_;
        call->src_line = source_line_;

#if 000
        if (_call_stack_depth > 0) {
            const char*  called_by_fn =
                _call_stack[_call_stack_depth - 1].src_fn;

            printf ("(DIGRAPH) \"%s()\" -> \"%s()\";\n",
                    called_by_fn, call->src_fn);
        }
#endif

    }

    _call_stack_depth++;
} /* _call_stack_push */
#endif                                                     /* CALL_TRACE == 2 */


#if defined CALL_TRACE && CALL_TRACE == 2
static void  _call_stack_pop( void ) {                                     /*F*/
    if (_call_stack_depth > 0) {
        _call_stack_depth--;
    }
} /* _call_stack_pop */
#endif                                                     /* CALL_TRACE == 2 */


/* -------------------------------------------------------------------------- */
/* Call Tracing and Timing Functions:                                         */


#if defined CALL_TRACE && CALL_TRACE == 2
PUBLIC uint32_t  fn_call_entry(                                            /*F*/
    const uint32_t  src_uid_,                                              /*-*/
    const char*     source_func_,                                          /*-*/
    const char*     source_file_,                                          /*-*/
    const int       source_line_ ) {                                       /*-*/
    /* never put GO here */
    _time_t  time = 0;

    _SET_HIGH_RESOLUTION_TIME(time);

    _call_stack_push(src_uid_, source_func_, source_file_, source_line_);

    if (_immediate_call_trace) {
        uint32_t  thread_id = 0;
        int16_t   depth     = 0;

#if PLATFORM_LINUX
        IMPLEMENT_LINUX();  /* TODO: implement fn_call_entry() on Linux */
        /* TODO: How to get current thread's ID in Linux? */
        thread_id = 0;
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
        thread_id = CAST(uint32_t, GetCurrentThreadId_win());
#endif

        DUMP_OPEN;
        DUMP(_T("\r\n"));

        for (depth = 0; depth < _call_depth; depth++) {
            DUMP(_T("  "));
        }

        DUMP(_T("THREAD:%d  0x%08X  %s"), thread_id,
             CAST(uint32_t, src_uid_), source_func_);
        DUMP_CLOSE;
    }

    if (_call_start_time == 0) {
        const size_t  struct_size = sizeof(_call_t);

        _call_start_time = time;
        _call_capacity   = CALLS_MAX;
        _call_data_index = 0;
        _call_depth      = 0;

        _call_data = malloc(_call_capacity * struct_size);
        if (_call_data == NULL) {
            printf("_call_data == NULL");
            DEBUG_BREAK;
        } else {
            memset(_call_data, 0x00, _call_capacity * struct_size);
        }

        /* re-check the starting time (allocating can take a second or 2) */
        _SET_HIGH_RESOLUTION_TIME(time);
    }

    time -= _call_start_time;

    {
        _call_t*  item = &_call_data[_call_data_index++];

        item->fn_id   = src_uid_;
        item->fn_name = source_func_;
        item->time    = time;
        item->depth   = _call_depth++;
        item->entry   = true;
    }

    /* never put RETURN here */
    return src_uid_;
} /* fn_call_entry */
#endif                                                     /* CALL_TRACE == 2 */


#if defined CALL_TRACE && CALL_TRACE == 2
PUBLIC void  fn_call_exit(                                                 /*F*/
    const uint32_t  src_uid_,                                              /*-*/
    const char*     source_func_,                                          /*-*/
    const char*     source_file_,                                          /*-*/
    const int       source_line_ ) {                                       /*-*/
    /* never put GO here */
    _time_t  time = 0;

    UNUSED(source_file_);
    UNUSED(source_line_);

    _call_stack_pop();

    _SET_HIGH_RESOLUTION_TIME(time);

    time -= _call_start_time;
    {
        _call_t*  item = &_call_data[_call_data_index++];

        item->fn_id   = src_uid_;
        item->fn_name = source_func_;
        item->time    = time;
        item->depth   = --_call_depth;
        item->entry   = false;
    }
    /* never put RETURN here */

} /* fn_call_exit */
#endif                                                     /* CALL_TRACE == 2 */


#if defined CALL_TRACE && CALL_TRACE == 2
static uint32_t  _call_count( void ) {                                     /*F*/
    /* calculate number of call entries, exits and maximum call depth */

    _call_t*  item       = NULL;
    uint32_t   i          = 0;
    uint32_t   exit_count = 0;
    uint32_t   ret        = 0;

    for (i = 0; i < _call_data_index; i++) {
        item = &_call_data[i];

        if (item->entry) {
            ret++;
        } else {
            exit_count++;
        }
    }

    if (exit_count != ret) {
        DEBUG_BREAK;
        return 0;
    }

    return ret;  /* don't use RETURN here */
} /* _call_count */
#endif                                                     /* CALL_TRACE == 2 */


#if defined CALL_TRACE && CALL_TRACE == 2
static int16_t  _max_call_depth( void ) {                                  /*F*/
    _call_t*  item = NULL;
    int16_t    ret  = 0;
    uint32_t   i    = 0;

    for (i = 0; i < _call_data_index; i++) {
        item = _call_data + i;
        if (ret < item->depth) {
            ret = item->depth;
        }
    }

    return ret;  /* don't use RETURN here */
} /* _max_call_depth */
#endif                                                     /* CALL_TRACE == 2 */


#if defined CALL_TRACE && CALL_TRACE == 2
static uint32_t  _called_fn_count(                                         /*F*/
    _call_t*      func_call_array_,                                        /*-*/
    const size_t  array_length_ ) {                                        /*-*/
    _call_t*  item         = NULL;
    uint32_t*  function_ids = NULL;
    uint32_t   i            = 0;
    uint32_t   b            = 0;
    uint32_t   ret_count    = 0;

    {
        /* allocate enough memory for the unique list of function IDs */
        const size_t  bytes_size = (array_length_ / 2) * sizeof(uint32_t);
        function_ids = malloc(bytes_size);
        if (function_ids == NULL) {
            DEBUG_BREAK;
        }
        memset(function_ids, 0x00, bytes_size);
    }

    /* iterate through the calls array and add unique function IDs to a    */
    /* temporary array of unique function IDs, also increasing the counter */
    for (i = 0; i < array_length_; i++) {

        bool  is_found = false;
        item = &func_call_array_[i];

        for (b = 0; b < ret_count; b++) {
            if (function_ids[b] == item->fn_id) {
                is_found = true;
                break;
            }
        }

        if (!is_found) {
            function_ids[ret_count] = item->fn_id;
            ret_count++;
        }
    }

    /* release memory and return */
    if (function_ids) {
        free(function_ids);
    }

    return ret_count;  /* don't use RETURN here */
} /* _called_fn_count */
#endif                                                     /* CALL_TRACE == 2 */


#if defined CALL_TRACE && CALL_TRACE == 2
static _call_sum_t*  _create_call_summary(                                 /*F*/
    _call_t*      func_call_array_,                                        /*-*/
    const size_t  array_length_,                                           /*-*/
    size_t        func_count_ ) {                                          /*-*/
    _call_sum_t*  ret = NULL;

    if (func_count_ == 0) {
        func_count_ = _called_fn_count(func_call_array_, array_length_);
    }

    {
        /* allocate memory for function call summary: */
        const size_t  bytes_size = func_count_ * sizeof(_call_sum_t);
        ret = malloc(bytes_size);
        if (ret == NULL) {
            DEBUG_BREAK;
        }
        memset(ret, 0x00, bytes_size);
    }

    {
        const _call_t*      record = NULL;
        const _call_sum_t*  sum    = NULL;
        size_t               i      = 0;
        size_t               b      = 0;
        size_t               count  = 0;
        _time_t             freq   = 0;

        _SET_HIGH_RESOLUTION_FREQUENCY(freq);

        for (i = 0; i < array_length_; i++) {

            bool  is_found = false;
            record = &func_call_array_[i];

            for (b = 0; b < count; b++) {
                sum = &ret[b];

                if (sum->fn_id == record->fn_id) {
                    if (sum->fn_name != record->fn_name) {
                        DEBUG_BREAK;
                    }

                    if (record->entry) {
                        sum->call_count++;
                    } else {
                        size_t     prev             = i - 1;
                        _call_t*  prev             = NULL;
                        _time_t   sub_exit_at_time = 0;
                        _time_t   subcall_time     = 0;

                        /* match call exit with corresponding */
                        /* call entry and get the difference */
                        do {
                            prev = &func_call_array_[prev--];

                            if (prev->depth == record->depth + 1) {
                                if (prev->entry) {
                                    subcall_time
                                    += (sub_exit_at_time - prev->time);
                                } else {
                                    sub_exit_at_time = prev->time;
                                }
                            }
                        } while (prev->fn_id != record->fn_id &&
                                 prev->depth != record->depth);

                        {
                            _time_t  call_time = record->time - prev->time;

                            double gross_seconds = freq == 0 ? 0
                                                   : CAST(double, call_time)
                                                   / CAST(double, freq);

                            double net_seconds =
                                freq == 0 ? 0
                                : CAST(double, call_time - subcall_time)
                                / CAST(double, freq);

                            sum->gross_seconds += gross_seconds;
                            sum->net_seconds   += net_seconds;
                            sum->avg_net_sec_per_call =
                                sum->net_seconds
                                / CAST(double, sum->call_count);
                        }
                    }
                    is_found = true;
                    break;
                }
            } /* for */

            if (!is_found) {
                sum = &ret[count];
                sum->serial_no            = ++count;
                sum->fn_id                = record->fn_id;
                sum->call_count           = 1;
                sum->gross_seconds        = 0;
                sum->net_seconds          = 0;
                sum->avg_net_sec_per_call = 0;
                sum->fn_name              = record->fn_name;

                if (record->entry != true) {
                    DEBUG_BREAK;
                }

            }
        }
    }
    return ret;
} /* _create_call_summary */
#endif                                                     /* CALL_TRACE == 2 */


#if defined CALL_TRACE && CALL_TRACE == 2
PUBLIC void  fn_call_report( void ) {                                      /*F*/
    double          net_seconds_total = 0;
    uint32_t        i                 = 0;
    const uint32_t  max_depth         = _max_call_depth();
    const uint32_t  call_count        = _call_count();
    const uint32_t  fn_count
        = _called_fn_count(_call_data, _call_data_index);

    _call_sum_t*  sum = _create_call_summary(
                            _call_data, _call_data_index, fn_count);

#if defined _MSC_VER
#define _printf( FORMAT_, ... )  DUMP(FORMAT_, __VA_ARGS__);
#else
#define _printf( FORMAT_, ... )  DUMP(FORMAT_, ## __VA_ARGS__);
#endif

#define _LINE               /* 140 dashes */       \
    _T("-----------------------------------")      \
    _T("-----------------------------------")      \
    _T("-----------------------------------")      \
    _T("-----------------------------------")  /*#*/

    DUMP_OPEN;

    _printf(_T("\r\n")
            _LINE _T("\r\n")
            _T(" S/N | Function ID| # Calls  |  Gross Seconds ")
            _T("|    Net Seconds | Avg Net/Call | Function name") _T("\r\n")
            _LINE);

    for (i = 0; i < fn_count; i++) {
        _printf(
            _T("\r\n")
            _T("%4u | 0x%08X | %8u | %14.9f | %14.9f | %12.9f | %s()"),
            sum[i].serial_no,
            sum[i].fn_id,
            sum[i].call_count,
            sum[i].gross_seconds,
            sum[i].net_seconds,
            sum[i].avg_net_sec_per_call,
            sum[i].fn_name);

        net_seconds_total += sum[i].net_seconds;
    }

    {
        /* output statistics: */
        double  avg_time_per_call = call_count == 0 ? 0 : net_seconds_total
                                    / CAST(double, call_count);

        _printf(_T("\r\n")  _LINE);

        _printf(_T("\r\n") _T("Total number of fn. calls:  %15u"),
                call_count);

        _printf(_T("\r\n") _T("Average time per call (ms): %15.9f"),
                avg_time_per_call);

        _printf(_T("\r\n") _T("Total time spent (seconds): %15.9f"),
                net_seconds_total);

        _printf(_T("\r\n") _T("Total number of functions:  %15u"),
                fn_count);

        _printf(_T("\r\n") _T("Maximum call depth:         %15d"),
                max_depth);

        _printf(_T("\r\n")  _LINE  _T("\r\n")  _T("\r\n"));
    }
    DUMP_CLOSE;
} /* fn_call_report */
#endif                                                     /* CALL_TRACE == 2 */


/* -------------------------------------------------------------------------- */
/* Windows API Wrapper Functions                                              */


#if PLATFORM_WIN32
static bool  _detect_multibyte_conversion_bug( void ) {                    /*F*/
    GO                                                            (UID(F07695));
    static bool  tested_already = false;
    static bool  ret            = false;

    if (!tested_already) {
        int      result = 0;
        uint8_t  buf[64];

        CLEAR(buf);

        /* Don't use MultiByteToWideChar_win() here. We need the original. */
        result = MultiByteToWideChar(
                     CP_UTF8,                /* CodePage       */
                     MB_ERR_INVALID_CHARS,   /* dwFlags        */
                     ".\xc2.",               /* lpMultiByteStr */
                     -1,                     /* cbMultiByte    */
                     CAST(WCHAR_win*, buf),  /* lpWideCharStr  */
                     64);                    /* cchWideChar    */

        ret = C_BOOL(result && MEMCMP(buf, ".\0.\0\0\0", 6) == 0);

        if (ret) {
            WARN(_T("Warning: MultiByteToWideChar() has a bug"), UID(E14BF9));
        }

        tested_already = true;
    }
    RETURN(ret);
} /* _detect_multibyte_conversion_bug */
#endif                                                      /* PLATFORM_WIN32 */


#if PLATFORM_WIN32
/* Wraps MultiByteToWideChar() and checks for multibyte conversion bug,       */
/* in which case it returns ERROR_NO_UNICODE_TRANSLATION.                     */
/* Systems that have the bug can't convert ANSI chars to UCS-2                */
PUBLIC int  multi_byte_to_wide_char(                                       /*F*/
    const UINT_win   code_page_,                                           /*-*/
    const DWORD_win  flags_,                                               /*-*/
    LPCSTR_win       multibyte_str_,                                       /*-*/
    const int        multibyte_len_,                                       /*-*/
    LPWSTR_win       wide_char_str_,                                       /*-*/
    const int        wide_char_len_ ) {                                    /*-*/
    GO                                                            (UID(FC3A68));
    /* validate input string (multibyte_str_) */
    if (multibyte_str_ == NULL) {
        WARN(_T("multibyte_str_ == NULL"), UID(E65F33));
        RETURN(ERROR_INVALID_PARAMETER);
    } else if (_detect_multibyte_conversion_bug()) {

        bool         all_ascii_chars = true;
        const char*  ch              = multibyte_str_;
        int          i               = 0;

        for (i = 0; i < multibyte_len_ && *ch != '\0'; i++, ch++) {
            if (*ch > 127) {
                all_ascii_chars = false;
                break;
            }
        }

        if (!all_ascii_chars) {
            WARN(_T("Conversion failed: MultiByteToWideChar() has a bug."),
                 UID(EC8D84));
            RETURN(ERROR_NO_UNICODE_TRANSLATION);
        }
    }
    {
        /* Don't use MultiByteToWideChar_win() here to avoid */
        /* recursion, just use MultiByteToWideChar()         */
        const int  ret = MultiByteToWideChar(
                             code_page_, flags_,
                             multibyte_str_, multibyte_len_,
                             wide_char_str_, wide_char_len_);
        RETURN(ret);
    }
} /* multi_byte_to_wide_char */
#endif                                                      /* PLATFORM_WIN32 */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
