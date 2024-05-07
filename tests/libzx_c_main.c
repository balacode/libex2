/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                      [libex_c_main.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_c_tests.h"

#include <stdio.h>
#include <string.h>   /* for memset() */

#if PLATFORM_LINUX
#include <termios.h>
#include <unistd.h>
#endif

#include <./tests/libex_c_tests_.h>
#include "libex_all_.h"


/* -------------------------------------------------------------------------- */
/* getch() implementation (for Linux)                                         */


#if PLATFORM_LINUX
PUBLIC char  _getch( void );                                               /*F*/
PUBLIC char  _getch( void ) {                                              /*F*/
    /* #include <termios.h> */
    /* #include <unistd.h>  */
    char            ret = 0;
    struct termios  old;

    CLEAR(old);
    fflush(stdout);

    if (tcgetattr(0, &old) < 0) {
        perror("tcgetattr()");
    }

    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN]  = 1;
    old.c_cc[VTIME] = 0;

    if (tcsetattr(0, TCSANOW, &old) < 0) {
        perror("tcsetattr() ICANON");
    }

    if (read(0, &ret, 1) < 0) {
        perror("read()");
    }

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;

    if (tcsetattr(0, TCSADRAIN, &old) < 0) {
        perror("tcsetattr() ~ICANON");
    }

    printf("%c\n", ret);
    return ret;
} /* _getch */
#endif                                                      /* PLATFORM_LINUX */


static bool  process_file(                                                 /*F*/
    const char*   filename_,                                               /*-*/
    const size_t  file_size_ ) {                                           /*-*/
    printf("\r\n file: %s %d", filename_, CAST(int, file_size_));;;
    return true;
}

/* -------------------------------------------------------------------------- */
/* main() function                                                            */

#if PLATFORM_WIN32
int  _tmain( void )                                                        /*F*/
#endif                                                      /* PLATFORM_WIN32 */

#if PLATFORM_LINUX
PUBLIC int  main( void )                                                   /*F*/
#endif                                                      /* PLATFORM_LINUX */
/* -------------------------------------------------------------------------- */
{
    /* run unit tests */
    mem_report();

    process_files_in_folder(
        _T("/mnt/x/user/projects/code/clg/cprojects/"), true, &process_file);

#if 000

    PRINTF_T(_T("\r\n \r\n test_dtime_class"));
    test_dtime_class();

    PRINTF_T(_T("\r\n test_string_class"));
    test_string_class();
    /* also tests functions in libex_stringc.h            */
    /* TODO: test_string_class() causes SEGFAULT on Linux */

#if PLATFORM_WIN32
    PRINTF_T(_T("\r\ntest_File"));
    test_file_class();
    /* TODO: test_file_class() causes SEGFAULT on Linux */
#endif

    /* c_::mem_static(MB(128)); */
    test_pdf_class();

#if defined CALL_TRACE && CALL_TRACE == 2
    c_::fn_call_report();
#endif

#endif /* 000 */

    mem_report();
    PRINTF_T(_T("\r\nPress any key to exit."));
    _getch();

    return 0;
} /* main */


/*eof*/
