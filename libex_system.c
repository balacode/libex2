/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                      [libex_system.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_system_.h"
#if defined INCLUDED_LIBEX_SYSTEM_H

#include <stdio.h>   /* for printf() sprintf*()                */
#include <string.h>  /* for memset()                           */

#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4820)  /* W:L4 'N' bytes padding added after 'NAME'  */
#endif

#include <time.h>    /* for clock_gettime() localtime() time() */

#if defined _MSC_VER
#pragma warning (pop)
#endif

#include "libex_config_.h"

#if PLATFORM_WIN32
#undef  _WIN32_WINNT
#define _WIN32_WINNT  0x0501  /* Windows XP or later */
#include <tlhelp32.h>  /* Windows API */
#include <winsock2.h>  /* Windows API */
#if defined _MSC_VER
#pragma comment (lib, "kernel32.lib")                         /* winbase.h */
/*      FindResource()        */
/*      FormatMessage()       */
/*      FreeResource()        */
/*      GetCurrentProcess()   */
/*      GetLastError()        */
/*      GetLocalTime()        */
/*      GetModuleHandle()     */
/*      GetTickCount()        */
/*      LoadResource()        */
/*      LockResource()        */
/*      SizeofResource()      */
/*      Sleep()               */
/*      WaitForSingleObject() */
#pragma comment (lib, "ole32.lib")                            /* objbase.h */
/*      CoCreateGuid() */
#pragma comment (lib, "psapi.lib")
/*      GetModuleFileNameEx() */
#pragma comment (lib, "rpcrt4.lib")                               /* rpc.h */
/*      UuidCreate() */
#pragma comment (lib, "user32.lib")                           /* winuser.h */
/*      GetWindowText()       */
/*      GetWindowTextLength() */
/*      LoadString()          */
#pragma comment (lib, "winspool.lib")                        /* winspool.h */
#pragma comment (lib, "ws2_32.lib")
/*      gethostbyname()       */
/*      gethostname()         */
/*      inet_ntoa()           */
#endif                                                            /* _MSC_VER */
#endif                                                      /* PLATFORM_WIN32 */

#include "libex_.h"
#include "libex_bytes_.h"
#include "libex_call_.h"
#include "libex_const_.h"
#include "libex_dtime_.h"
#include "libex_file_.h"
#include "libex_functions_.h"
#include "libex_libc.h"
#include "libex_logging_.h"
#include "libex_macro_.h"
#include "libex_network_.h"
#include "libex_string_class_.h"
#include "libex_stringc_.h"
#include "libex_system_.h"
#include "libex_type_.h"

#if PLATFORM_WIN32
#include "libex_win_registry_.h"
#include "libex_win32_.h"
#endif

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#if defined __GNUC__ && !defined __MINGW32__
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#endif
#if defined __clang__
#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#endif

#if defined _MSC_VER
#pragma warning (disable:4710)  /* W:L4 function not inlined                  */
#endif

#define _CPU_ID_CIPHER_0   0x91742A34
#define _CPU_ID_CIPHER_1   0x3EC94D14
#define _CPU_ID_CIPHER_2   0xFFF34050
#define _CPU_ID_CIPHER_3   0x3A9EB550
#define _CPU_ID_CIPHER_4   0xA5414B05


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


/* -------------------------------------------------------------------------- */
/* Functions: Private                                                         */


#if PLATFORM_WIN32
static OSVERSIONINFOEX_win  _win_version_info( void ) {                    /*F*/
    GO                                                            (UID(FD2041));
    bool                 success = false;
    OSVERSIONINFOEX_win  version;
    CLEAR(version);

    /* attempt to get Windows version with GetVersionEx_win() */
    version.dwOSVersionInfoSize = sizeof(version);
    success = (GetVersionEx_win(CAST(OSVERSIONINFO_win*, &version)) != 0);

    if (!success) {
        /* if OSVERSIONINFOEX_win fails, use OSVERSIONINFO_win */
        version.dwOSVersionInfoSize = sizeof(OSVERSIONINFO_win);
        OS_VERIFY(GetVersionEx_win(CAST(OSVERSIONINFO_win*, &version)),
                  UID(E7B80E));
    }
    RETURN(version);
} /* _win_version_info */
#endif                                                      /* PLATFORM_WIN32 */


#if PLATFORM_WIN32
static new_chars_t  _registry_hardware_info( chars_t value_name_ ) {       /*F*/
    GO                                                            (UID(FE2D0B));
    new_chars_t  chars =
        registry_get_text(
            _T("HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System"),
            value_name_);
    trim_in_T(chars);
    RETURN(chars);
} /* _registry_hardware_info */
#endif                                                      /* PLATFORM_WIN32 */


/* returns a CLSID from four words in the format:                             */
static new_chars_t  _guid(                                                 /*F*/
    const uint32_t  dword_0_,                                              /*-*/
    const uint32_t  dword_1_,                                              /*-*/
    const uint32_t  dword_2_,                                              /*-*/
    const uint32_t  dword_3_ ) {                                           /*-*/
    GO                                                            (UID(F0C1F5));
    /* CLSID format: {11112222-3333-4444-5555-666677778888} */
    new_chars_t  ret = formatT(_T("{%04x%04x-%04x-%04x-%04x-%04x%04x%04x}"),
                               (dword_0_ & 0xFFFF0000) >> 16, 4,
                               (dword_0_ & 0xFFFF),           4,
                               (dword_1_ & 0xFFFF0000) >> 16, 4,
                               (dword_1_ & 0xFFFF),           4,
                               (dword_2_ & 0xFFFF0000) >> 16, 4,
                               (dword_2_ & 0xFFFF),           4,
                               (dword_3_ & 0xFFFF0000) >> 16, 4,
                               (dword_3_ & 0xFFFF),           4);
    RETURN(ret);
} /* _guid */


/* -------------------------------------------------------------------------- */
/* Functions: Operating System version                                        */


PUBLIC os_class_enum  os_class( void ) {                                   /*F*/
    GO                                                            (UID(F9F7DE));
    os_class_enum  ret = OS_UNKNOWN;

#if PLATFORM_WIN32
    const OSVERSIONINFOEX_win  info = _win_version_info();

    switch (info.dwPlatformId) {
            CASE(1, ret = OS_WINDOWS_9X);
            CASE(2, ret = OS_WINDOWS_NT);
        default:
            ret = OS_UNKNOWN;
    }
    /* 0: Win32s could likely be platform 0         */
    /* 1: e.g. Windows ME: ver 4.90, build 73010104 */
    /* 2: e.g. Windows XP: ver 5.1, build 2500      */
#endif                                                      /* PLATFORM_WIN32 */
    RETURN(ret);
} /* os_class */


PUBLIC bool  os_is_linux( void ) {                                         /*F*/
    GO                                                            (UID(FACDC5));
    const bool  ret = (os_class() == OS_LINUX);
    RETURN(ret);
} /* os_is_linux */


PUBLIC bool  os_is_win_9x( void ) {                                        /*F*/
    GO                                                            (UID(FF8D09));
    const bool  ret = (os_class() == OS_WINDOWS_9X);
    RETURN(ret);
} /* os_is_win_9x */


PUBLIC bool  os_is_win_nt( void ) {                                        /*F*/
    GO                                                            (UID(F2ADF8));
    const bool  ret = (os_class() == OS_WINDOWS_NT);
    RETURN(ret);
} /* os_is_win_nt */


PUBLIC double  os_version( void ) {                                        /*F*/
    GO                                                            (UID(F5178B));
    double  ret = 0;

#if PLATFORM_WIN32
    new_chars_t                ver  = NULL;
    const OSVERSIONINFOEX_win  info = _win_version_info();
    ver = formatT(_T("%u.%u"),
                  CAST(unsigned int, info.dwMajorVersion),
                  CAST(unsigned int, info.dwMinorVersion));
    ret = doubleT(ver);
    freeT(&ver);
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* os_version */


PUBLIC chars_t  os_version_text( void ) {                                  /*F*/
    GO                                                            (UID(FE9BA0));
    static bool    generated = false;
    static char_t  ret[128];

    if (!generated) {
#if PLATFORM_WIN32
        const OSVERSIONINFOEX_win  ver = _win_version_info();
        new_chars_t                csd = T_chars(ver.szCSDVersion);

        /* create a string containing version, build and service pack no. */
        new_chars_t  ver_str = formatT(_T("version %u.%u, build %u,")
                                       _T(" SP_%u.%u, platform %u"),
                                       CAST(uint32_t, ver.dwMajorVersion),
                                       CAST(uint32_t, ver.dwMinorVersion),
                                       CAST(uint32_t, ver.dwBuildNumber),
                                       CAST(uint32_t, ver.wServicePackMajor),
                                       CAST(uint32_t, ver.wServicePackMinor),
                                       CAST(uint32_t, ver.dwPlatformId));
        CLEAR(ret);
        trim_in_T(csd);

        if (IS_BLANK(csd)) {
            STRCPY_S_T(ret, 128, ver_str);
        } else {
            new_chars_t  version_and_csd =
                formatT(_T("%s, csd = '%s'"), ver_str, csd);
            STRCPY_S_T(ret, 128, version_and_csd);
            freeT(&version_and_csd);
        }

        freeT(&ver_str);
        freeT(&csd);
        generated = true;
#endif                                                      /* PLATFORM_WIN32 */
    }
    RETURN(ret);
} /* os_version_text */


PUBLIC chars_t  os_folder( void ) {                                        /*F*/
    GO                                                            (UID(F8B58E));
    chars_t  ret = NULL;

#if 000
    str_t           ret;
    const UINT_win  len = GetWindowsDirectory_win(
                              /* lpBuffer - buffer for Windows directory */
                              ret.getEmptyBuffer(MAX_PATH_win + 1),
                              /* uSize - size of directory buffer */
                              MAX_PATH_win + 1);
    ret.closeBuffer();
    ret = ret.substr(0, len);  /* TODO: Use ret.setFirst(len) */
#endif                                                                 /* 000 */
    RETURN(ret);
} /* os_folder */


PUBLIC uint32_t  os_volume_id( void ) {                                    /*F*/
    GO                                                            (UID(F60E86));
    uint32_t  ret  = 0;

#if 000
    str_t     path = os_folder();
    uint32_t  ret  = volume_id(path);
#endif                                                                 /* 000 */
    RETURN(ret);
} /* os_volume_id */


/* -------------------------------------------------------------------------- */
/* Functions: Firmware (BIOS) Identification                                  */


#define _WIN9X_HARDWARE_INFO_KEY                              \
    _T("HKEY_LOCAL_MACHINE\\Enum\\Root\\*PNP0C01\\0000")  /*#*/

PUBLIC chars_t  firmware_date( void ) {                                    /*F*/
    GO                                                            (UID(FEAC2C));
    static bool    generated = false;
    static char_t  ret[32];

    if (!generated) {
        CLEAR(ret);

#if PLATFORM_LINUX
        if (os_is_linux()) {
            IMPLEMENT_LINUX();    /* TODO: firmware_date() in Linux */
        }
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
        {
            new_chars_t  date = NULL;
            if (os_is_win_nt()) {
                date = _registry_hardware_info(_T("SystemBiosDate"));
                STRCPY_S_T(ret, 32, date);

            } else if (os_is_win_9x()) {
                date = registry_get_text(
                           _WIN9X_HARDWARE_INFO_KEY, _T("BiosDate"));
                STRCPY_S_T(ret, 32, date);
            }
            freeT(&date);
        }
#endif                                                      /* PLATFORM_WIN32 */

        trim_in_T(ret);
        generated = true;
    }
    RETURN(ret);
} /* firmware_date */


/* TODO-D03A647F */
PUBLIC chars_t  firmware_version( void ) {                                 /*F*/
    GO                                                            (UID(F82658));
#if 000
    if (os_is_win_nt()) {
        const str_t  ret = _registry_hardware_info(_T("SystemBiosVersion"));
        RETURN(ret);

    } else if (os_is_win_9x()) {
        new_chars_t  bios_name =
            registry_get_text(_WIN9X_HARDWARE_INFO_KEY, _T("BiosName"));

        new_chars_t  bios_version =
            registry_get_text(_WIN9X_HARDWARE_INFO_KEY, _T("BiosVersion"));

        new_chars_t  chars = T_join(TT, bios_name, _T(" "), bios_version, TT);

        trim_in_T(chars);
        freeT(&bios_name);
        freeT(&bios_version);
        {
            const str_t  ret = S_newT(chars);
            RETURN(ret);
        }
    }
#endif                                                                 /* 000 */

    RETURN(BLANK);
} /* firmware_version */


PUBLIC chars_t  video_firmware_date( void ) {                              /*F*/
    GO                                                            (UID(F3CE06));
    chars_t  ret = NULL;

#if 000
    str_t  ret = _registry_hardware_info(_T("VideoBiosDate"));
#endif

    RETURN(ret);
} /* video_firmware_date */


PUBLIC chars_t  video_firmware_version( void ) {                           /*F*/
    GO                                                            (UID(F438F5));
    chars_t  ret = NULL;

#if 000
    str_t  ret = _registry_hardware_info(_T("VideoBiosVersion"));
#endif

    RETURN(ret);
} /* video_firmware_version */


/* -------------------------------------------------------------------------- */
/* Functions: CPU Identification                                              */


PUBLIC chars_t  cpu_id( void ) {                                           /*F*/
    GO                                                            (UID(F82EC8));
    chars_t  ret = NULL;

#if 000
    /* call the integer version of this function */
    DWORD_win  id[5];
    cpu_id_1(id);

    /* create the serial number string */
    const str_t  ret = format(_T("%0 %1 - %2 %3 - %4 %5 - %6 %7 - %8 %9"),
                              T_hex((id[0] & 0xFFFF0000) >> 16, 4),
                              T_hex( id[0] & 0xFFFF, 4),
                              T_hex((id[1] & 0xFFFF0000) >> 16, 4),
                              T_hex( id[1] & 0xFFFF, 4),
                              T_hex((id[2] & 0xFFFF0000) >> 16, 4),
                              T_hex( id[2] & 0xFFFF, 4),
                              T_hex((id[3] & 0xFFFF0000) >> 16, 4),
                              T_hex( id[3] & 0xFFFF, 4),
                              T_hex((id[4] & 0xFFFF0000) >> 16, 4),
                              T_hex( id[4] & 0xFFFF, 4));
#endif                                                                 /* 000 */

    RETURN(ret);
} /* cpu_id */


PUBLIC void  cpu_id_1( uint32_t  cpu_id_out_[5] ) {                        /*F*/
    GO                                                            (UID(F6FA24));
    /* if compiler is not aware of 'cpuid' define the following: */
    /* #define cpuid  _asm _emit 0x0F _asm _emit 0xA2            */

    /* 0:CPU Features  1:CPU Advanced 2..4: Serial Number */
    uint32_t  info[5] = { 0, 0, 0, 0, 0 };

#if defined _MSC_VER
    /* determine CPU features */
    _asm {
        push eax
        push ebx
        push ecx
        push edx

        mov eax, 1
        cpuid
        mov info[0 * TYPE int], edx
        mov info[1 * TYPE int], ebx

        pop edx
        pop ecx
        pop ebx
        pop eax
    }

    /* if the processor has a serial number ... */
    if ((info[0] & 0x00040000) != 0) {
        _asm {
            push eax
            push ebx
            push ecx
            push edx

            mov eax, 3
            cpuid
            mov info[2 * TYPE int], ebx
            mov info[3 * TYPE int], ecx
            mov info[4 * TYPE int], edx

            pop edx
            pop ecx
            pop ebx
            pop eax
        }
    }

#endif                                                            /* _MSC_VER */

    /* copy CPU info values into supplied argument */
    cpu_id_out_[0] = info[0];
    cpu_id_out_[1] = info[1];
    cpu_id_out_[2] = info[2];
    cpu_id_out_[3] = info[3];
    cpu_id_out_[4] = info[4];

    RETURN(NIL);
} /* cpu_id */


PUBLIC bool  this_cpu_id( const uint32_t  encrypted_cpu_id_[5] ) {         /*F*/
    GO                                                            (UID(FB6F0F));
    UNUSED(encrypted_cpu_id_);  /* TODO: implement this_cpu_id() */

#if 000
    const uint32_t  cipher[5] = {
        _CPU_ID_CIPHER_0,
        _CPU_ID_CIPHER_1,
        _CPU_ID_CIPHER_2,
        _CPU_ID_CIPHER_3,
        _CPU_ID_CIPHER_4
    };

    uint32_t  cpu_id[5] = { 0, 0, 0, 0, 0 };
    int       i         = 0;

    /* decipher the ecrypted argument */
    for (i = 0; i < 5; i++) {
        cpu_id[i] = encrypted_cpu_id_[i] ^ cipher[i];
    }

    DWORD_win  this_id[5];
    cpu_id(this_id);

    for (i = 0; i < 5; i++) {
        if (this_id[i] != cpu_id[i]) {
            RETURN(false);
        }
    }
#endif                                                                 /* 000 */

    RETURN(true);
} /* this_cpu_id */


/* Returns a CPU ID, as a string CLSID                                        */
/*                                                                            */
/* cpu_id_[5]:   (OPTIONAL OVERLOAD) Pointer to a variable declared as:       */
/*               DWORD_win <name>[5]; This holds the CPU ID information.      */
/*                                                                            */
/* return value: after manipulating cpu_id_[], returns a string               */
/*               representing that CPU ID, formatted as a CLSID:              */
/*               {99999999-9999-9999-9999-999999999999}                       */
/*                                                                            */
/* version:      created on 11-Mar-2004 13:19pm                               */

PUBLIC chars_t  cpu_id_as_class_id( void ) {                               /*F*/
    GO                                                            (UID(F67330));
#if 000
    /* get this computer's CPU ID */
    DWORD_win  id[5];
    cpu_id(id);
    {
        const str_t  ret = cpu_id_as_class_id(id);
        RETURN(ret);
    }
#endif                                                                 /* 000 */

    RETURN(ERR_TEXT);
} /* cpu_id_as_class_id */


PUBLIC new_chars_t  cpu_id_as_class_id_1( const uint32_t
        cpu_id_arg_[5] ) { /*F*/
    GO                                                            (UID(FB66FB));
    static const uint8_t  mix[16] =
    { 8, 0, 1, 6, 15, 3, 7, 14, 12, 5, 2, 9, 11, 4, 13, 10 };

    uint32_t  id[5];  /* encrypt the CPU ID */
    id[0] = cpu_id_arg_[0] ^ _CPU_ID_CIPHER_0;
    id[1] = cpu_id_arg_[1] ^ _CPU_ID_CIPHER_1;
    id[2] = cpu_id_arg_[2] ^ _CPU_ID_CIPHER_2;
    id[3] = cpu_id_arg_[3] ^ _CPU_ID_CIPHER_3;
    id[4] = cpu_id_arg_[4] ^ _CPU_ID_CIPHER_4;

    /* shift last 2 DWORDs (serial number) over redundant DWORD_win 2 */
    id[2] = id[3];
    id[3] = id[4];

    bytes_transpose(CAST(uint8_t*, &id), mix, 16);

    {
        new_chars_t  ret = _guid(id[0], id[1], id[2], id[3]);
        RETURN(ret);
    }
} /* cpu_id_as_class_id_1 */


/* -------------------------------------------------------------------------- */
/* Function: Physical Memory                                                  */


PUBLIC size_t  physical_memory_size( void ) {                              /*F*/
    GO                                                            (UID(F7F073));
    size_t  ret = 0;

#if PLATFORM_WIN32
    MEMORYSTATUS_win  status;
    GlobalMemoryStatus_win(&status);
    ret = CAST(ULONG_win, status.dwTotalPhys);
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* physical_memory_size */


PUBLIC size_t  physical_memory_size_in_mb( void ) {                        /*F*/
    GO                                                            (UID(FFDD07));
    const size_t  ret = physical_memory_size() / 1024 / 1024;
    RETURN(ret);
} /* physical_memory_size_in_mb */


/* -------------------------------------------------------------------------- */
/* Functions: Storage                                                         */


PUBLIC uint32_t  volume_id( chars_t  path_ ) {                             /*F*/
    GO                                                            (UID(FA403F));
    uint32_t  ret = 0;

    UNUSED(path_);

#if 000
    str_t  drive = str_t(path_).substr(0, 3);

    if (!GetVolumeInformation_win(drive, 0, 0, &ret, 0, 0, 0, 0)) {
        OS_ERR(_T("GetVolumeInformation()"), UID(E49EB7));
    }
#endif                                                                 /* 000 */

    RETURN(ret);
} /* volume_id */


/* -------------------------------------------------------------------------- */
/* Functions: Network-Related                                                 */


PUBLIC chars_t  computer_name( void ) {                                    /*F*/
    GO                                                            (UID(F2E314));
    chars_t  ret = NULL;
#if 000
    new_chars_t  chars =
        registry_get_text(_T("HKEY_LOCAL_MACHINE")
                          _T("\\System\\CurrentControlSet")
                          _T("\\Control\\ComputerName\\ComputerName"),
                          _T("ComputerName"));
    str_t  ret = S_newT(chars);
#endif                                                                 /* 000 */
    RETURN(ret);
} /* computer_name */


PUBLIC chars_t  ip_address_list( chars_t  delimiter_ ) {                   /*F*/
    GO                                                            (UID(FFF7ED));
    UNUSED(delimiter_);

#if 000
    /* determine host name and get host info */
    char  hostname[MAX_PATH_win];
    GETHOSTNAME(hostname, MAX_PATH_win);
    hostent*  host = GETHOSTBYNAME(hostname);

    /* read list of host's addresses */
    str_t  addr_list;

    if (host != NULL) {
        sockaddr_in  addr;

        int  i;
        for (i = 0; host->h_addr_list[i] != NULL; i++) {
            MEMCPY(&addr.sin_addr, host->h_addr_list[i],
                   CAST(size_t, host->h_length));

            if (!addr_list.empty()) {
                addr_list += delimiter_;
            }

            addr_list += str_t(INET_NTOA(addr.sin_addr));
        }
    }
    RETURN(addr_list);
#endif                                                                 /* 000 */
    RETURN(ERR_TEXT);
} /* ip_address_list */


/* -------------------------------------------------------------------------- */
/* Functions: Date and time-Related                                           */


PUBLIC void  sleep_ms( const unsigned long  milliseconds_ ) {              /*F*/
    GO                                                            (UID(F97AB5));
#if PLATFORM_LINUX
    UNUSED(milliseconds_);

#if 000
    struct timespec  time;
    struct timespec  remain;

    /* seconds and milliseconds */
    time.tv_sec = CAST(time_t, milliseconds_ / 1000);
    milliseconds_ -= CAST(unsigned long, time.tv_sec * 1000);

    /* nanoseconds: 0 - 999,999,999 */
    time.tv_nsec = CAST(long, milliseconds_ * 1000000);

    if (nanosleep(&time, &remain) < 0) {
        PRINTF("nanosleep() failed.");
    }

#endif                                                                 /* 000 */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    /* Sleep_win(milliseconds_); */
    if (WAIT_FAILED_win == WaitForSingleObject_win(GetCurrentProcess_win(),
            CAST(DWORD_win, milliseconds_))) {
        OS_WARN(_T("WaitForSingleObject() == WAIT_FAILED_win"), UID(EFFDA7));
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(NIL);
} /* sleep_ms */


PUBLIC chars_t  timestamp( void ) {                                        /*F*/
    GO                                                            (UID(F372FD));
    /* returns the current local date and time as a string using    */
    /* the ISO-8601 format: yyyy-MM-ddThh:mm:ss 2019-02-05T15:46:00 */
    static char_t  ret[20];
    new_chars_t    buf = mallocT(20);

#if PLATFORM_LINUX
    time_t     now_utc = TIME(NULL);
    struct tm  now     = *LOCALTIME(&now_utc);

    SNPRINTF_T(buf, 20,
               _T("%04d-%02d-%02dT%02d:%02d:%02d"),
               now.tm_year + 1900, now.tm_mon + 1, now.tm_mday,
               now.tm_hour, now.tm_min, now.tm_sec);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    SYSTEMTIME_win  now;
    CLEAR(now);
    GetLocalTime_win(&now);
    SNPRINTF_T(buf, 20, _T("%04u-%02u-%02uT%02u:%02u:%02u"),
               now.wYear, now.wMonth, now.wDay,
               now.wHour, now.wMinute, now.wSecond);
#endif                                                      /* PLATFORM_WIN32 */

    STRCPY_S_T(ret, 20, buf);

    RETURN(ret);
} /* timestamp */


PUBLIC unsigned long  uptime_ms( void ) {                                  /*F*/
    GO                                                            (UID(F8EEE2));
    /* returns the system uptime in milliseconds.     */
    /* Equivalent to Windows function GetTickCount(). */
    unsigned long  ret = 0;

#if PLATFORM_LINUX
    struct timespec  time;
    CLOCK_GETTIME(CLOCK_MONOTONIC, &time);       /* in GCC/Clang: add -lrt */
    ret = CAST(unsigned long, time.tv_sec * 1000)
          + CAST(unsigned long, time.tv_nsec / 1000000);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    ret = GetTickCount_win();
#endif

    RETURN(ret);
} /* uptime_ms */


/* -------------------------------------------------------------------------- */
/* Functions: Process-Related                                                 */


static char_t  process_name_buf[2048];

PUBLIC chars_t  full_process_name( void ) {                                /*F*/
    GO                                                            (UID(F7CE05));
    /* returns the full path and name of the current */
    /* process, which is the name of the program,    */
    /* for example C:\Program Files\MyProgram.exe    */

#if PLATFORM_LINUX
    IMPLEMENT_LINUX();  /* TODO: full_process_name() on Linux */
#endif

#if PLATFORM_WIN32
    HANDLE_win           handle;
    WIN32_FIND_DATA_win  fdata;

    /* get filename of current process */
    CLEAR(process_name_buf);
    GetModuleFileName_win(
        NULL,                 /* NULL = current process   */
        process_name_buf,  /* receiving buffer         */
        _MAX_PATH_win + 1);   /* size of buffer in TCHARs */

    /* get file name in proper case                                 */
    /* (GetModuleFileName_win() may return an all-uppercase string) */

    handle = FindFirstFile_win(process_name_buf, &fdata);

    if (handle != INVALID_HANDLE_VALUE_win) {
        const size_t  full_len = lenT(process_name_buf);
        const size_t  name_len = lenT(fdata.cFileName);

        STRCPY_S_T(process_name_buf + full_len - name_len,
                   MAX_PATH_win + 1 - full_len + name_len,
                   fdata.cFileName);

        FindClose_win(handle);
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(process_name_buf);
} /* full_process_name */


PUBLIC bool  kill_process( chars_t  process_name_ ) {                      /*F*/
    GO                                                            (UID(F7DF05));
    /* Terminates all instances of the given process name.                    */
    /* On Windows, the process name is the name of the executable file,       */
    /* e.g. calc.exe for the calculator.                                      */
    /*                                                                        */
    /* - If you specify the name of the running process, all other instances  */
    /*   are terminated, but the current instance remains running.            */
    /*                                                                        */
    /* - The name match is not case-sensitive                                 */
    /*                                                                        */
    /* - requires #include <tlhelp32.h>                                       */

#if PLATFORM_LINUX
    UNUSED(process_name_);
    IMPLEMENT_LINUX();  /* TODO: kill_process() on Linux */
    RETURN(false);
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32

    /* get the ID of the running program, so it never gets terminated */
    DWORD_win  this_process_id = GetCurrentProcessId_win();

    PROCESSENTRY32_win  entry;
    CLEAR(entry);
    entry.dwSize = sizeof(entry);

    {
        /* Takes a snapshot of the specified processes, as well as the */
        /* heaps, modules, and threads used by these processes.        */
        const HANDLE_win  snapshot =
            CreateToolhelp32Snapshot_win(TH32CS_SNAPALL_win, 0);

        /* get info about the first process encountered in a system snapshot  */
        BOOL_win  success = Process32First_win(snapshot, &entry);
        while (success) {
            if (equals_icT(entry.szExeFile, process_name_) &&
                entry.th32ProcessID != this_process_id) {
                const HANDLE_win  process =
                    OpenProcess_win(PROCESS_TERMINATE_win,
                                    0, CAST(DWORD_win, entry.th32ProcessID));

                if (process != NULL) {
                    TerminateProcess_win(process, 9);
                    CloseHandle_win(process);
                }
            }
            success = Process32Next_win(snapshot, &entry);
        }
        CloseHandle_win(snapshot);
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(false);
} /* kill_process */


PUBLIC new_chars_t  log_filename( chars_t  file_extension_ ) {             /*F*/
    GO                                                            (UID(F45C4D));
    new_chars_t  ret = NULL;

#if PLATFORM_LINUX
    UNUSED(file_extension_);
    IMPLEMENT_LINUX();  /* TODO: implement Linux log_filename()*/
#endif

#if PLATFORM_WIN32
    chars_t      program = full_process_name();
    new_chars_t  name    = NULL;

    UNUSED(file_extension_);  /* TODO: implement Win log_filename() */

    /* get the program name (excluding .exe extension on Windows) */
    if (ends3T(program, _T(".exe"), true)) {
        const size_t  len = lenT(program) - 4;
        name = T_chars_n(program, len);
    } else {
        name = T_chars(program);
    }

    /* build logfile name */
    if (lenT(file_extension_) == 0) {
        ret = T_join(TT, name, _T(".lx.log"), TT);

    } else if (beginsT(file_extension_, _T("."))) {
        ret = T_join(TT, name, file_extension_, TT);

    } else {
        ret = T_join(TT, name, _T("."), file_extension_, TT);
    }

    FREE(name);
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* log_filename */


PUBLIC chars_t  process_name( void ) {                                     /*F*/
    /* Returns the name of the current process (the running program) */
    /* excluding the full path, e.g. 'myprogram.exe'                 */

#if PLATFORM_LINUX
    const char_t  break_ch = '/';
#endif
#if PLATFORM_WIN32
    const char_t  break_ch = '\\';
#endif

    chars_t       ret = full_process_name();
    const size_t  len = lenT(ret);

    if (ret != NULL && 0 < len) {
        chars_t  s = ret + len;
        while (s-- > ret) {
            if (break_ch == *s) {
                ret = s + 1;
                break;
            }
        }
    }

    return ret;
} /* process_name */


PUBLIC chars_t  program_path( void ) {                                     /*F*/
    GO                                                            (UID(F5F03B));
    chars_t  ret = full_process_name();
    /* TODO: ret = File::getPath(ret); */
    RETURN(ret);
} /* program_path */


PUBLIC new_chars_t  list_processes( chars_t  delimiter_ ) {                /*F*/
    GO                                                            (UID(F30989));
    new_chars_t  ret = NULL;

    UNUSED(delimiter_);

#if 000
    HMODULE_win  dll = NULL;

    typedef BOOL_win(CALLBACK_win * EnumProcesses_win)(
        DWORD_win*, DWORD_win, DWORD_win*);

    typedef BOOL_win(CALLBACK_win * EnumProcessModules_win)(
        HANDLE_win, HMODULE_win*, DWORD_win, LPDWORD_win);

    typedef BOOL_win(CALLBACK_win * GetModuleFileNameEx_win)(
        HANDLE_win, HMODULE_win, LPTSTR_win, DWORD_win);

    EnumProcesses_win        EnumProcesses_fn       = NULL;
    EnumProcessModules_win   EnumProcessModules_fn  = NULL;
    GetModuleFileNameEx_win  GetModuleFileNameEx_fn = NULL;

#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4191)  /* W:L3 operator/operation: unsafe conversion */
#endif

    {
        /* get a pointer to the required functions in PSAPI.DLL */
        dll = LoadLibrary_win(_T("psapi.dll"));

        if (!dll) {
            OS_ERR(_T("LoadLibrary('psapi.dll')"), UID(E183A9));
            RETURN(BLANK);
        }

        /* get a pointer to EnumProcesses_win() */
        EnumProcesses_fn = EnumProcesses_win(
                               GetProcAddress_win(dll, "EnumProcesses"));
        /*                              ^ Don't use _T() */

        if (!EnumProcesses_fn) {
            OS_ERR(_T("GetProcAddress('psapi.dll', 'EnumProcesses')"),
                   UID(EFBB54));
            RETURN(BLANK);
        }

        /* get a pointer to EnumProcessModules_win() */
        EnumProcessModules_fn =
            EnumProcessModules_win(
                GetProcAddress_win(dll, "EnumProcessModules"));
        /*                                   ^ Don't use _T() */

        if (!EnumProcessModules_fn) {
            OS_ERR(_T("GetProcAddress('psapi.dll', 'EnumProcessModules')"),
                   UID(EEE326));
            RETURN(BLANK);
        }

#if defined UNICODE || defined _UNICODE
#define _PROC_NAME  "GetModuleFileNameExW"  /* don't use _T() here */
#else
#define _PROC_NAME  "GetModuleFileNameExA"
#endif

        /* get a pointer to GetModuleFileNameEx_win() */
        GetModuleFileNameEx_fn = GetModuleFileNameEx_win(
                                     GetProcAddress_win(dll, _PROC_NAME));

#undef _PROC_NAME

        if (!GetModuleFileNameEx_fn) {
            OS_ERR(_T("GetProcAddress('psapi.dll','GetModuleFileNameEx')"),
                   UID(EB4B35));
            RETURN(BLANK);
        }
    }

#if defined _MSC_VER
#pragma warning (pop)
#endif

    /* get an array of all process IDs and the no. of running processes */
    DWORD_win  process_list[4096];
    DWORD_win  process_count = 0;
    {
        CLEAR(process_list);
        DWORD_win  bytes_size = 0;

        if (!EnumProcesses_fn(process_list,
                              sizeof(process_list), &bytes_size)) {
            OS_ERR(_T("EnumProcesses()"), UID(ECA325));
            RETURN(BLANK);
        }
        process_count = bytes_size / sizeof(DWORD_win);
    }

    str_t  ret;

    /* iterate through all the running processes */
    for (size_t  i = 0; i < process_count; i++) {
        /* open a process handle (if allowed by security) */
        HMODULE_win  process = HMODULE_win(
                                   OpenProcess_win(
                                       PROCESS_QUERY_INFORMATION_win |
                                       PROCESS_VM_READ_win,
                                       false, process_list[i]));

        if (!process) {
            continue;
        }

        /* get the main module's ID (if allowed by security) */
        HMODULE_win  module = NULL;
        DWORD_win    needed = 0;

        if (!EnumProcessModules_fn(
                process, &module, sizeof(module), &needed)) {
            continue;
        }

        /* get the full file name of the process */
        str_t  filename;
        GetModuleFileNameEx_fn(
            process, module,
            filename.getEmptyBuffer(_MAX_PATH_win + 1), _MAX_PATH_win + 1);

        filename.closeBuffer();

        /* add the file name to the list */
        if (!ret.empty()) {
            ret += delimiter_;
        }

        ret += filename;
    }
    OS_VERIFY(FreeLibrary_win(dll), UID(E58CC0));
#endif                                                                 /* 000 */

    RETURN(ret);
} /* list_processes */


PUBLIC bool  run_process(                                                  /*F*/
    chars_t  filename_,                                                    /*-*/
    chars_t  command_line_ ) {                                             /*-*/
    GO                                                            (UID(F1B418));
    bool  ret = false;

#if 000
    /* prepare requisite structures */

    STARTUPINFO_win  startup_info;
    CLEAR(startup_info);
    startup_info.cb = sizeof(startup_info);

    PROCESS_INFORMATION_win  process_info;
    CLEAR(process_info);

    /* copy command_line_ (which is const) to a buffer,            */
    /* because CreateProcess_win() needs a non-const lpCommandLine */
    str_t         cmd_line (command_line_);
    LPTSTR_win  lpCommandLine = cmd_line.getBuffer();

    /* call CreateProcess_win() to start a new process */
    BOOL_win  is_done = CreateProcess_win(
                            filename_,       /* lpApplicationName    */
                            lpCommandLine,   /* lpCommandLine        */
                            NULL,            /* lpProcessAttributes  */
                            NULL,            /* lpThreadAttributes   */
                            false,           /* binheritHandles      */
                            0,               /* dwCreationFlags      */
                            NULL,            /* lpEnvironment        */
                            NULL,            /* lpCurrentDirectory   */
                            &startup_info,   /* lpStartupInfo        */
                            &process_info);  /* lpProcessInformation */

    if (!is_done) {
        OS_ERR(_T("CreateProcess()"), UID(E58E60));
    }

#endif                                                                 /* 000 */

    const bool  is_done = false;

    UNUSED(filename_);
    UNUSED(command_line_);

    ret = (is_done ? true : false);
    RETURN(ret);
} /* run_process */


/* -------------------------------------------------------------------------- */
/* Functions: Printing                                                        */


PUBLIC chars_t  defaultPrinterName( void ) {                               /*F*/
    GO                                                            (UID(FBE7A9));
    new_chars_t  ret = NULL;

#if 000
    str_t  ret;

    /* prepare a buffer */
    DWORD_win  buf_size = 4;
    char_t*    buf      = new char_t[buf_size];  /* TODO-D074E788 */
    MEMSET(buf, 0x00, buf_size);

    bool  has_name = true;

    while (GetDefaultPrinter_win(buf, &buf_size) == FALSE_win) {
        DWORD_win  last_err = GetLastError_win();

        if (last_err == ERROR_INSUFFICIENT_BUFFER_win) {
            delete[] buf;
            buf = new char_t[buf_size];
            MEMSET(buf, 0x00, buf_size);

            /* there is no default printer */
        } else if (last_err == ERROR_FILE_NOT_FOUND_win) {
            has_name = false;
            break;

        } else {
            WARN(system_error_name(last_err), UID(EF6EAD));
            has_name = false;
            break;
        }
    }

    if (has_name) {
        ret = buf;
    }

    delete[] buf;
#endif                                                                 /* 000 */

    RETURN(ret);
} /* defaultPrinterName */


/* -------------------------------------------------------------------------- */
/* Functions: Miscellaneous                                                   */


PUBLIC new_str_t  create_guid( const bool  add_delimiter_ ) {              /*F*/
    GO                                                            (UID(F65496));
    new_str_t  ret = { NULL };

#if PLATFORM_LINUX
    UNUSED(add_delimiter_);
    IMPLEMENT_LINUX();  /* TODO: How to create GUID on Linux? */
#endif                                                      /* PLATFORM_LINUX */

#if PLATFORM_WIN32
    GUID  guid;  /* 16 bytes */
    CLEAR(guid);

    if (CoCreateGuid_win(&guid) != S_OK_win) {  /* ole32.lib */
        WARN(_T("CoCreateGuid_win() failed"), UID(E63FE0));
        ret = S_chars(_T("GUID_ERROR"));
        RETURN(ret);
    }

#if 000   /* alternative to create GUID by hashing CPU ID and current time */
    {
#if PLATFORM_WIN32 && defined _use_rpccrt4_lib

        if (UuidCreate_win(&guid) != RPC_S_OK_win)
#endif                                                      /* PLATFORM_WIN32 */
        {
            /* build a custom GUID if CoCreateGuid_win() */
            /* and UuidCreate_win() failed               */

            Hash  hashes[3];

            /* get hash of cpu ID */
            DWORD_win  cpu_id[5];
            system::cpu_id(cpu_id);
            hashes[0] = Hash::hashOfBytes(cpu_id, sizeof(cpu_id));
            /* 64-byte hash */

            /* hash BIOS information */
            str_t  bios = system::firmware_version() + System::firmware_date();
            hashes[1] = Hash::hashOfText(bios);  /* 64-byte hash */

            /* hash the current CPU uptime */
            LARGE_INTEGER_win  uptime;  /* 8 bytes */
            QueryPerformanceCounter_win(&uptime);
            hashes[2] = Hash::hashOfBytes(&uptime, sizeof(uptime));
            /* 64-byte hash */

            /* generate a composite hash of the preceding three hashes */
            Hash  hash = Hash::hashOfBytes(hashes, sizeof(hashes));

            /* copy data from middle of hash (64-bytes) */
            /* into the GUID (16-bytes) */
            MEMCPY(&guid, &hash[0] + 32, sizeof(guid));
        }
    }
#endif                                                                 /* 000 */

    {
        /* convert GUID to a string */
        static char  GUID_FORMAT[] =
            "%.08x-%.04x-%.04x-%.02x%.02x-%.02x%.02x%.02x%.02x%.02x%.02x";

        char  buf[40];
        MEMSET(buf, 0x00, sizeof(buf));

#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4774)  /* W:L4 format string is not a string literal */
#endif

        SNPRINTF(buf, 40, GUID_FORMAT,
                 guid.Data1, guid.Data2, guid.Data3,
                 guid.Data4[0], guid.Data4[1],
                 guid.Data4[2], guid.Data4[3],
                 guid.Data4[4], guid.Data4[5],
                 guid.Data4[6], guid.Data4[7]);

#if defined _MSC_VER
#pragma warning (pop)
#endif

        setCopyAnsiS(&ret, buf);
    }

    /* format and return the string */
    toupperInS(&ret);

    if (!add_delimiter_) {
        replace3InS(&ret, _T("-"), BLANK);
    }

#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* create_guid */


/* -------------------------------------------------------------------------- */

#define INPUT_BOX_MAX_LEN  1024
#define _IDC_STATIC_PROMPT    150
#define _IDC_EDIT_INPUT       160
#define _IDC_BUTTON_OK        170
#define _IDC_BUTTON_CANCEL    180


static char_t  input_box_title[INPUT_BOX_MAX_LEN]  = _T("");
static char_t  input_box_prompt[INPUT_BOX_MAX_LEN] = _T("");
static char_t  input_box_input[INPUT_BOX_MAX_LEN]  = _T("");

#if PLATFORM_WIN32
static HFONT_win  input_box_font = NULL;
#endif

#if PLATFORM_WIN32
LRESULT_win CALLBACK_win  input_box_callback_fn(                           /*F*/
    HWND_win    dialog_window_,                                            /*-*/
    UINT_win    message_,                                                  /*-*/
    WPARAM_win  wparam_,                                                   /*-*/
    LPARAM_win  lparam_ ) {                                                /*-*/
    UNUSED(lparam_);

    switch (message_) {
        case WM_INITDIALOG_win:

                /* set the font for all controls */

                SendMessage_win(
                    GetDlgItem_win(dialog_window_, _IDC_STATIC_PROMPT),
                    WM_SETFONT_win,
                    CAST(WPARAM_win, input_box_font), true);

            SendMessage_win(
                GetDlgItem_win(dialog_window_, _IDC_EDIT_INPUT),
                WM_SETFONT_win,
                CAST(WPARAM_win, input_box_font), true);

            SendMessage_win(
                GetDlgItem_win(dialog_window_, _IDC_BUTTON_OK),
                WM_SETFONT_win,
                CAST(WPARAM_win, input_box_font), true);

            SendMessage_win(
                GetDlgItem_win(dialog_window_, _IDC_BUTTON_CANCEL),
                WM_SETFONT_win,
                CAST(WPARAM_win, input_box_font), true);

            /* set title, prompt and default */

            SetWindowText_win(dialog_window_, input_box_title);

            SetDlgItemText_win(
                dialog_window_, _IDC_STATIC_PROMPT, input_box_prompt);

            SetDlgItemText_win(
                dialog_window_, _IDC_EDIT_INPUT, input_box_input);

            return TRUE_win;

        case WM_COMMAND_win:
                if (LOWORD_win(wparam_) == _IDC_EDIT_INPUT) {
                    GetDlgItemText_win(
                        dialog_window_,
                        _IDC_EDIT_INPUT,
                        input_box_input,
                        INPUT_BOX_MAX_LEN);
                    return TRUE_win;
                } else if (LOWORD_win(wparam_) == _IDC_BUTTON_OK) {
                    CLEAR_N(input_box_input, INPUT_BOX_MAX_LEN);

                    GetDlgItemText_win(dialog_window_,
                                       _IDC_EDIT_INPUT,
                                       input_box_input,
                                       INPUT_BOX_MAX_LEN);

                    return EndDialog_win(dialog_window_, _IDC_BUTTON_OK);
                } else if (LOWORD_win(wparam_) == _IDC_BUTTON_CANCEL) {
                    CLEAR_N(input_box_input, INPUT_BOX_MAX_LEN);
                    return EndDialog_win(dialog_window_, _IDC_BUTTON_CANCEL);
                }
            break;
    }
    return FALSE_win;
} /* input_box_callback_fn */
#endif                                                      /* PLATFORM_WIN32 */


#if PLATFORM_WIN32
static LPWORD_win  input_box_ptr_align( LPWORD_win  word_ ) {              /*F*/
    ULONG_win  ret = CAST(ULONG_win, word_);
    ret += 3;
    ret >>= 2;
    ret <<= 2;
    return CAST(LPWORD_win, ret);
} /* input_box_ptr_align */
#endif                                                      /* PLATFORM_WIN32 */

PUBLIC chars_t  input_box(                                                 /*F*/
    chars_t  prompt_,                                                      /*-*/
    chars_t  title_,                                                       /*-*/
    chars_t  default_,                                                     /*-*/
    void*    owner_window_ ) {                                             /*-*/
#if PLATFORM_LINUX
    UNUSED(owner_window_);
#endif

#if PLATFORM_WIN32
    LPWORD_win  dlg_tpl = NULL;
#endif

    CLEAR_N(input_box_title,  INPUT_BOX_MAX_LEN);
    CLEAR_N(input_box_prompt, INPUT_BOX_MAX_LEN);
    CLEAR_N(input_box_input,  INPUT_BOX_MAX_LEN);

    if (!IS_BLANK(title_)) {
        STRCPY_S_T(input_box_title,  INPUT_BOX_MAX_LEN, title_);
    }
    if (!IS_BLANK(prompt_)) {
        STRCPY_S_T(input_box_prompt, INPUT_BOX_MAX_LEN, prompt_);
    }
    if (!IS_BLANK(default_)) {
        STRCPY_S_T(input_box_input,  INPUT_BOX_MAX_LEN, default_);
    }

#if PLATFORM_WIN32
    {
        /* create font */

#define _FONT_NAME  _T("Arial")
#define _FONT_SIZE  9
        const HDC_win  hdc = GetDC_win(NULL);  /* screen device context */

        LOGFONT_win  font;
        font.lfHeight = -MulDiv_win(_FONT_SIZE,
                                    GetDeviceCaps_win(hdc, LOGPIXELSY_win), 72);
        font.lfWidth          = 0;
        font.lfEscapement     = 0;
        font.lfOrientation    = font.lfEscapement;
        font.lfWeight         = FW_NORMAL_win;
        font.lfItalic         = FALSE_win;
        font.lfUnderline      = FALSE_win;
        font.lfStrikeOut      = FALSE_win;
        font.lfCharSet        = DEFAULT_CHARSET_win;
        font.lfOutPrecision   = OUT_TT_ONLY_PRECIS_win;
        font.lfClipPrecision  = CLIP_DEFAULT_PRECIS_win;
        font.lfQuality        = PROOF_QUALITY_win;
        font.lfPitchAndFamily = DEFAULT_PITCH_win + FF_DONTCARE_win;
        STRCPY_S_T(font.lfFaceName, LF_FACESIZE_win, _FONT_NAME);

        input_box_font = CreateFontIndirect_win(&font);

#undef _FONT_NAME
#undef _FONT_SIZE
    }

    {
        HGLOBAL_win  handle = GlobalAlloc_win(GMEM_ZEROINIT_win, 4096);
        if (handle == NULL) {
            return NULL;
        }

        {
            /* dialog box: */
            LPDLGTEMPLATE_win
            dlg = CAST(LPDLGTEMPLATE_win, GlobalLock_win(handle));

            dlg->style = DS_CENTER | DS_MODALFRAME |
                         WS_BORDER | WS_CAPTION | WS_POPUP;

            dlg->dwExtendedStyle = 0;

            dlg->cdit = 4;    /* number of controls */
            dlg->x    = 0;
            dlg->y    = 0;
            dlg->cx   = 180;  /* width in dialog units  */
            dlg->cy   = 60;   /* height in dialog units */

            dlg_tpl = CAST(LPWORD_win, dlg + 1);

            *dlg_tpl++ = 0x0000;  /* no menu */
            *dlg_tpl++ = 0x0000;  /* predefined dialog box class */
        }
        {
            LPWSTR_win  str   = CAST(LPWSTR_win, dlg_tpl);
            int         chars = 1 + MultiByteToWideChar_win(
                                    CP_ACP, 0, "DialogBox", -1, str, 50);
            dlg_tpl += chars;
        }
        dlg_tpl = input_box_ptr_align(dlg_tpl);

        {
            /* Prompt label: */
            LPDLGITEMTEMPLATE_win  label = CAST(LPDLGITEMTEMPLATE_win, dlg_tpl);
            label->id    = _IDC_STATIC_PROMPT;
            label->x     = 10;
            label->y     = 5;
            label->cx    = 40;
            label->cy    = 20;
            label->style = WS_CHILD | WS_VISIBLE | SS_LEFT;

            dlg_tpl = CAST(LPWORD_win, label + 1);
            *dlg_tpl++ = 0xFFFF;
            *dlg_tpl++ = 0x0082;  /* static class */
        }

        {
            LPWSTR_win  str = CAST(LPWSTR_win, dlg_tpl);
            int         len = 0;

#if defined UNICODE || defined _UNICODE

            len = 1 + WCSLEN(prompt_);

#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4996)  /* W:L3 'function': may be unsafe/deprecated  */
#endif
            WCSCPY(str, prompt_);

#if defined _MSC_VER
#pragma warning (pop)
#endif
#else
            len = 1 + MultiByteToWideChar_win(CP_ACP, 0, prompt_, -1, str, 50);
#endif
            dlg_tpl += len;
        }
        *dlg_tpl = 0x0000;  /* no creation data */
        dlg_tpl  = input_box_ptr_align(dlg_tpl);

        {
            /* Edit control: */
            LPDLGITEMTEMPLATE_win  edit =
                CAST(LPDLGITEMTEMPLATE_win, dlg_tpl);

            edit->style = ES_LEFT    |
                          WS_BORDER  |
                          WS_CHILD   |
                          WS_TABSTOP |
                          WS_VISIBLE;

            edit->dwExtendedStyle = 0;
            edit->x  = 10;
            edit->y  = 17;
            edit->cx = 160;
            edit->cy = 12;
            edit->id = _IDC_EDIT_INPUT;

            dlg_tpl = CAST(LPWORD_win, edit + 1);
            *dlg_tpl++ = 0xFFFF;
            *dlg_tpl++ = 0x0081;  /* edit class       */
            *dlg_tpl++ = 0x0000;  /* no creation data */
        }
        dlg_tpl = input_box_ptr_align(dlg_tpl);

        {
            char*  c4 = CAST(char*, dlg_tpl);
            c4 += 4;
            dlg_tpl = CAST(LPWORD, c4);
        }

        {
            /* OK button: */
            LPDLGITEMTEMPLATE_win
            btn = CAST(LPDLGITEMTEMPLATE_win, dlg_tpl);

            btn->style = BS_DEFPUSHBUTTON | WS_CHILD | WS_TABSTOP | WS_VISIBLE;
            btn->dwExtendedStyle = 0;
            btn->x  = 65;
            btn->y  = 40;
            btn->cx = 50;
            btn->cy = 12;
            btn->id = _IDC_BUTTON_OK;

            dlg_tpl = CAST(LPWORD_win, btn + 1);
            *dlg_tpl++ = 0xFFFF;
            *dlg_tpl++ = 0x0080;  /* button class */
        }
        {
            LPWSTR_win  str = CAST(LPWSTR_win, dlg_tpl);
            const int  chars =
                1 + MultiByteToWideChar_win(CP_ACP, 0, "OK", -1, str, 50);
            dlg_tpl += chars;
        }
        *dlg_tpl++ = 0x0000;  /* no creation data */
        dlg_tpl = input_box_ptr_align(dlg_tpl);

        {
            /* Cancel button: */
            LPDLGITEMTEMPLATE_win  button =
                CAST(LPDLGITEMTEMPLATE_win, dlg_tpl);

            button->style = BS_PUSHBUTTON | WS_CHILD | WS_TABSTOP | WS_VISIBLE;
            button->dwExtendedStyle = 0;
            button->x  = 120;
            button->y  = 40;
            button->cx = 50;
            button->cy = 12;
            button->id = _IDC_BUTTON_CANCEL;

            dlg_tpl = CAST(LPWORD_win, button + 1);
            *dlg_tpl++ = 0xFFFF;
            *dlg_tpl++ = 0x0080;  /* button class */
        }
        {
            LPWSTR_win  str = CAST(LPWSTR_win, dlg_tpl);
            const int  chars =
                1 + MultiByteToWideChar_win(CP_ACP, 0, "Cancel", -1, str, 50);
            dlg_tpl += chars;
        }
        *dlg_tpl++ = 0x0000;  /* no creation data */
        dlg_tpl = input_box_ptr_align(dlg_tpl);

        GlobalUnlock_win(handle);

        {
            LRESULT_win  ret =
                DialogBoxIndirect_win(
                    NULL,
                    CAST(LPDLGTEMPLATE_win, handle),
                    CAST(HWND_win,          owner_window_),
                    CAST(DLGPROC_win,       input_box_callback_fn));

            /*
                Return Value

                If the function succeeds, the return value is the nResult parameter
                specified in the call to the EndDialog function that was used to
                terminate the dialog box.

                If the function fails because the hWndParent parameter is invalid,
                the return value is zero.

                If the function fails for any other reason, the return value is -1.
                To get extended error information, call GetLastError.
            */

            if (ret == -1) {
                DWORD_win  err_no = GetLastError();
                chars_t    err    = system_error_name(err_no);
                PRINTF_T(_T("%s"), err);;;
            }
            UNUSED(ret);
        }
        GlobalFree_win(handle);
    }
#endif                                                      /* PLATFORM_WIN32 */

    return input_box_input;
} /* input_box */


/* -------------------------------------------------------------------------- */


PUBLIC void  message_box(                                                  /*F*/
    chars_t                text_,                                          /*-*/
    chars_t                title_,                                         /*-*/
    message_box_icon_enum  icon_ ) {                                       /*-*/
    GO                                                            (UID(F0F572));
#if PLATFORM_WIN32
    MessageBox_win(NULL, text_, title_, MB_OK_win | MB_TOPMOST_win | icon_);
#endif

#if PLATFORM_LINUX
    UNUSED(text_);
    UNUSED(title_);
    UNUSED(icon_);

    IMPLEMENT_LINUX();  /* TODO: How to show a popup message box in Linux? */
#endif                                                      /* PLATFORM_LINUX */

    RETURN(NIL);
} /* message_box */


PUBLIC chars_t  system_error_name( const int  error_no_ ) {                /*F*/
    GO                                                            (UID(F72F97));
    /*BREAKPOINT*/

    chars_t  ret = _T("(ERR-UNKNOWN)");

#if PLATFORM_LINUX

    switch (error_no_) {
#define _CASE( ERR_ )  case ERR_: ret = _T(#ERR_); break
            /* errno-base.h */
            _CASE(EPERM);    /*  1 Operation not permitted         */
            _CASE(ENOENT);   /*  2 No such file or directory       */
            _CASE(ESRCH);    /*  3 No such process                 */
            _CASE(EINTR);    /*  4 Interrupted system call         */
            _CASE(EIO);      /*  5 I/O error                       */
            _CASE(ENXIO);    /*  6 No such device or address       */
            _CASE(E2BIG);    /*  7 Argument list too long          */
            _CASE(ENOEXEC);  /*  8 Exec format error               */
            _CASE(EBADF);    /*  9 Bad file number                 */
            _CASE(ECHILD);   /* 10 No child processes              */
            _CASE(EAGAIN);   /* 11 Try again/Operation would block */
            _CASE(ENOMEM);   /* 12 Out of memory                   */
            _CASE(EACCES);   /* 13 Permission denied               */
            _CASE(EFAULT);   /* 14 Bad address                     */
            _CASE(ENOTBLK);  /* 15 Block device required           */
            _CASE(EBUSY);    /* 16 Device or resource busy         */
            _CASE(EEXIST);   /* 17 File exists                     */
            _CASE(EXDEV);    /* 18 Cross-device link               */
            _CASE(ENODEV);   /* 19 No such device                  */
            _CASE(ENOTDIR);  /* 20 Not a directory                 */
            _CASE(EISDIR);   /* 21 Is a directory                  */
            _CASE(EINVAL);   /* 22 Invalid argument                */
            _CASE(ENFILE);   /* 23 File table overflow             */
            _CASE(EMFILE);   /* 24 Too many open files             */
            _CASE(ENOTTY);   /* 25 Not a typewriter                */
            _CASE(ETXTBSY);  /* 26 text file busy                  */
            _CASE(EFBIG);    /* 27 File too large                  */
            _CASE(ENOSPC);   /* 28 No space left on device         */
            _CASE(ESPIPE);   /* 29 Illegal seek                    */
            _CASE(EROFS);    /* 30 Read-only file system           */
            _CASE(EMLINK);   /* 31 Too many links                  */
            _CASE(EPIPE);    /* 32 Broken pipe                     */
            _CASE(EDOM);     /* 33 Math arg out of domain of func  */
            _CASE(ERANGE);   /* 34 Math result not representable   */

            /* errno.h */
            _CASE(EDEADLK);          /*  35 Resource deadlock would occur     */
            _CASE(ENAMETOOLONG);     /*  36 File name too long                */
            _CASE(ENOLCK);           /*  37 No record locks available         */
            _CASE(ENOSYS);           /*  38 Function not implemented          */
            _CASE(ENOTEMPTY);        /*  39 Directory not empty               */
            _CASE(ELOOP);            /*  40 Too many symbolic links           */
            _CASE(ENOMSG);           /*  42 No message of desired type        */
            _CASE(EIDRM);            /*  43 Identifier removed                */
            _CASE(ECHRNG);           /*  44 Channel number out of range       */
            _CASE(EL2NSYNC);         /*  45 Level 2 not synchronized          */
            _CASE(EL3HLT);           /*  46 Level 3 halted                    */
            _CASE(EL3RST);           /*  47 Level 3 reset                     */
            _CASE(ELNRNG);           /*  48 Link number out of range          */
            _CASE(EUNATCH);          /*  49 Protocol driver not attached      */
            _CASE(ENOCSI);           /*  50 No CSI structure available        */
            _CASE(EL2HLT);           /*  51 Level 2 halted                    */
            _CASE(EBADE);            /*  52 Invalid exchange                  */
            _CASE(EBADR);            /*  53 Invalid request descriptor        */
            _CASE(EXFULL);           /*  54 Exchange full                     */
            _CASE(ENOANO);           /*  55 No anode                          */
            _CASE(EBADRQC);          /*  56 Invalid request code              */
            _CASE(EBADSLT);          /*  57 Invalid slot                      */
            _CASE(EBFONT);           /*  59 Bad font file format              */
            _CASE(ENOSTR);           /*  60 Device not a stream               */
            _CASE(ENODATA);          /*  61 No data available                 */
            _CASE(ETIME);            /*  62 Timer expired                     */
            _CASE(ENOSR);            /*  63 Out of streams resources          */
            _CASE(ENONET);           /*  64 Machine is not on the network     */
            _CASE(ENOPKG);           /*  65 Package not installed             */
            _CASE(EREMOTE);          /*  66 Object is remote                  */
            _CASE(ENOLINK);          /*  67 Link has been severed             */
            _CASE(EADV);             /*  68 Advertise error                   */
            _CASE(ESRMNT);           /*  69 Srmount error                     */
            _CASE(ECOMM);            /*  70 Communication error on send       */
            _CASE(EPROTO);           /*  71 Protocol error                    */
            _CASE(EMULTIHOP);        /*  72 Multihop attempted                */
            _CASE(EDOTDOT);          /*  73 RFS specific error                */
            _CASE(EBADMSG);          /*  74 Not a data message                */
            _CASE(EOVERFLOW);        /*  75 Value too large for def data type */
            _CASE(ENOTUNIQ);         /*  76 Name not unique on network        */
            _CASE(EBADFD);           /*  77 File descriptor in bad state      */
            _CASE(EREMCHG);          /*  78 Remote address changed            */
            _CASE(ELIBACC);          /*  79 Can't access a needed shared lib  */
            _CASE(ELIBBAD);          /*  80 Accessing a corrupted shared lib  */
            _CASE(ELIBSCN);          /*  81 .lib section in a.out corrupted   */
            _CASE(ELIBMAX);          /*  82 At. to link too many shared libs  */
            _CASE(ELIBEXEC);         /*  83 Cannot exec a shared lib directly */
            _CASE(EILSEQ);           /*  84 Illegal byte sequence             */
            _CASE(ERESTART);         /*  85 Interrp. call should be restarted */
            _CASE(ESTRPIPE);         /*  86 Streams pipe error                */
            _CASE(EUSERS);           /*  87 Too many users                    */
            _CASE(ENOTSOCK);         /*  88 Socket operation on non-socket    */
            _CASE(EDESTADDRREQ);     /*  89 Destination address required      */
            _CASE(EMSGSIZE);         /*  90 Message too long                  */
            _CASE(EPROTOTYPE);       /*  91 Protocol wrong type for socket    */
            _CASE(ENOPROTOOPT);      /*  92 Protocol not available            */
            _CASE(EPROTONOSUPPORT);  /*  93 Protocol not supported            */
            _CASE(ESOCKTNOSUPPORT);  /*  94 Socket type not supported         */
            _CASE(EOPNOTSUPP);       /*  95 Op. not supported on tr. endpoint */
            _CASE(EPFNOSUPPORT);     /*  96 Protocol family not supported     */
            _CASE(EAFNOSUPPORT);     /*  97 Addr. family not supported by ptl */
            _CASE(EADDRINUSE);       /*  98 Address already in use            */
            _CASE(EADDRNOTAVAIL);    /*  99 Cannot assign requested address   */
            _CASE(ENETDOWN);         /* 100 Network is down                   */
            _CASE(ENETUNREACH);      /* 101 Network is unreachable            */
            _CASE(ENETRESET);        /* 102 Net dropped con. because of reset */
            _CASE(ECONNABORTED);     /* 103 Software caused connection abort  */
            _CASE(ECONNRESET);       /* 104 connection reset by peer          */
            _CASE(ENOBUFS);          /* 105 No buffer space available         */
            _CASE(EISCONN);          /* 106 Transport endpoint already connd. */
            _CASE(ENOTCONN);         /* 107 Transport endpoint is not conctd. */
            _CASE(ESHUTDOWN);        /* 108 Cannot send after endpt. shutdown */
            _CASE(ETOOMANYREFS);     /* 109 Too many references cannot splice */
            _CASE(ETIMEDOUT);        /* 110 connection timed out              */
            _CASE(ECONNREFUSED);     /* 111 connection refused                */
            _CASE(EHOSTDOWN);        /* 112 Host is down                      */
            _CASE(EHOSTUNREACH);     /* 113 No route to host                  */
            _CASE(EALREADY);         /* 114 Operation already in progress     */
            _CASE(EINPROGRESS);      /* 115 Operation now in progress         */
            _CASE(ESTALE);           /* 116 Stale file handle                 */
            _CASE(EUCLEAN);          /* 117 Structure needs cleaning          */
            _CASE(ENOTNAM);          /* 118 Not a XENIX named type file       */
            _CASE(ENAVAIL);          /* 119 No XENIX semaphores available     */
            _CASE(EISNAM);           /* 120 Is a named type file              */
            _CASE(EREMOTEIO);        /* 121 Remote I/O error                  */
            _CASE(EDQUOT);           /* 122 Quota exceeded                    */
            _CASE(ENOMEDIUM);        /* 123 No medium found                   */
            _CASE(EMEDIUMTYPE);      /* 124 Wrong medium type                 */
            _CASE(ECANCELED);        /* 125 Operation Canceled                */
            _CASE(ENOKEY);           /* 126 Required key not available        */
            _CASE(EKEYEXPIRED);      /* 127 Key has expired                   */
            _CASE(EKEYREVOKED);      /* 128 Key has been revoked              */
            _CASE(EKEYREJECTED);     /* 129 Key was rejected by service       */
            _CASE(EOWNERDEAD);       /* 130 Owner died                        */
            _CASE(ENOTRECOVERABLE);  /* 131 State not recoverable             */
            _CASE(ERFKILL);          /* 132 Oper. not possible due to RF-kill */
            _CASE(EHWPOISON);        /* 133 Memory page has hardware error    */
        default:
                ret = _T("(ERR-UNKNOWN)");
#undef _CASE
    }

#elif PLATFORM_WIN32
    {
        size_t           i      = 0;
        const DWORD_win  err_no = CAST(DWORD_win, error_no_) == 0
                                  ? GetLastError_win()
                                  : CAST(DWORD_win, error_no_);

        /* static buffer for the error description */
#define BUF_SIZE  256
        static char_t  static_buf[BUF_SIZE];
        MEMSET(static_buf, 0x00, sizeof(static_buf));

        /* get the error description from the OS */
        FormatMessage_win(
            FORMAT_MESSAGE_FROM_SYSTEM_win |
            FORMAT_MESSAGE_IGNORE_INSERTS_win,    /* dwFlags      */
            NULL,                                 /* lpSource     */
            err_no,                               /* dwMessageId  */
            MAKELANGID_win(LANG_NEUTRAL_win,
                           SUBLANG_DEFAULT_win),  /* dwLanguageID */
            CAST(char_t*, static_buf),            /* lpBuffer     */
            BUF_SIZE,                             /* nSize        */
            NULL);                                /* arguments    */

        /* remove all whitespaces from the end of the buffer */
        i = STRLEN_T(static_buf);
        while (i--) {
            if (static_buf[i] == ' '  || static_buf[i] == '\a' ||
                static_buf[i] == '\b' || static_buf[i] == '\f' ||
                static_buf[i] == '\n' || static_buf[i] == '\r' ||
                static_buf[i] == '\t' || static_buf[i] == '\v') {
                static_buf[i] = '\0';
            } else {
                break;
            }
        }

        ret = static_buf;
    }
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* system_error_name */


/* -------------------------------------------------------------------------- */
/* Functions: Windows-Specific                                                */


#if PLATFORM_WIN32
PUBLIC uint8_t*  load_resource_win(                                        /*F*/
    chars_t            type_,                                              /*-*/
    const int          resource_id_,                                       /*-*/
    size_t*            data_size_out_,                                     /*-*/
    const HMODULE_win  module_ ) {                                         /*-*/
    GO                                                            (UID(F5DB49));
    uint8_t*  ret = NULL;

    /* get instance handle, if not specified */
    const HMODULE_win  module = (module_ == NULL)
                                ? GetModuleHandle_win(NULL) : module_;
    if (module == NULL) {
        OS_WARN(_T("GetModuleHandle_win()"), UID(E42C4B));

    } else {  /* find the resource */
        const HRSRC_win  resource_info =
            FindResource_win(module, MAKEINTRESOURCE_win(resource_id_), type_);

        if (resource_info == NULL) {
            OS_WARN(_T("FindResource_win()"), UID(EA1F76));

        } else {  /* determine size of the resource in bytes */
            const DWORD_win  size = SizeofResource_win(module, resource_info);
            if (size < 1) {
                OS_WARN(_T("SizeofResource_win()"), UID(E04D2C));

            } else {  /* load the resource into global memory */
                const HGLOBAL_win
                hres = LoadResource_win(module, resource_info);
                if (hres == NULL) {
                    OS_WARN(_T("LoadResource_win()"), UID(E9BB5D));
                    RETURN(NULL);
                } else { /* lock the resource and return a pointer to its data */
                    ret = CAST(uint8_t*, LockResource_win(hres));
                    if (ret == NULL) {
                        OS_WARN(_T("LockResource_win()"), UID(EFE445));

                    } else if (data_size_out_) {
                        *data_size_out_ = size;
                    }
                }
            }
        }
    }
    /* no need to call FreeResource_win() as resources are auto-freed */
    RETURN(ret);
} /* load_resource_win */
#endif                                                      /* PLATFORM_WIN32 */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
