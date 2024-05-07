/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_win32.h] */
/* -------------------------------------------------------------------------- */

#include "libex_config.h"
#if !defined INCLUDED_LIBEX_WIN32_H && LX_PLATFORM_WIN32
#define      INCLUDED_LIBEX_WIN32_H

#if !defined(_INC_WINDOWS)
#error "<windows.h> should be included before <libex_win32.h>"
#endif

/* undefine macros defined in windef.h, that may cause naming conflicts */
#undef max
#undef min

/* -------------------------------------------------------------------------- */
/* Common Definitions:                                                        */

#if defined __cplusplus
#define LX_PUBLIC    extern "C"
#else                                                          /* __cplusplus */
#define LX_PUBLIC
#endif                                                        /* !__cplusplus */

typedef unsigned int   UINT_win;
typedef unsigned long  DWORD_win;
typedef const char*    LPCSTR_win;
typedef wchar_t*       LPWSTR_win;

/* -------------------------------------------------------------------------- */
/* Special Cases:                                                             */

#define MultiByteToWideChar_win          lx_multi_byte_to_wide_char /*winnls.h*/
/* this function calls a wrapper function that tests for the                  */
/* presence of a multibyte conversion bug in MultiByteToWideChar()            */
/* The wrapper function is defined in libex_libc.c                            */

LX_PUBLIC int  lx_multi_byte_to_wide_char(                                 /*F*/
    const UINT_win   code_page_,                                           /*-*/
    const DWORD_win  flags_,                                               /*-*/
    LPCSTR_win       multibyte_str_,                                       /*-*/
    const int        multibyte_len_,                                       /*-*/
    LPWSTR_win       wide_char_str_,                                       /*-*/
    const int        wide_char_len_ );                                     /*-*/

/* -------------------------------------------------------------------------- */
/* Definitions: Windows API Function Aliases                                  */

#define AllocConsole_win                 AllocConsole               /*wincon.h*/
#define AngleArc_win                     AngleArc                   /*wingdi.h*/
#define AppendMenu_win                   AppendMenu                /*winuser.h*/
#define BeginPaint_win                   BeginPaint                /*winuser.h*/
#define BeginPath_win                    BeginPath                  /*wingdi.h*/
#define BitBlt_win                       BitBlt                     /*wingdi.h*/
#define CallWindowProc_win               CallWindowProc            /*winuser.h*/
#define CancelIo_win                     CancelIo                  /*winbase.h*/
#define ChangeServiceConfig2_win         ChangeServiceConfig2       /*winsvc.h*/
#define CheckMenuItem_win                CheckMenuItem             /*winuser.h*/
#define ClientToScreen_win               ClientToScreen            /*winuser.h*/
#define CloseClipboard_win               CloseClipboard            /*winuser.h*/
#define CloseHandle_win                  CloseHandle               /*winbase.h*/
#define CloseServiceHandle_win           CloseServiceHandle         /*winsvc.h*/
#define CoCreateGuid_win                 CoCreateGuid              /*objbase.h*/
#define CoInitialize_win                 CoInitialize              /*objbase.h*/
#define CoInitializeEx_win               CoInitializeEx            /*objbase.h*/
#define CommDlgExtendedError_win         CommDlgExtendedError      /*commdlg.h*/
#define CopyFile_win                     CopyFile                  /*winbase.h*/
#define CopySid_win                      CopySid                   /*winbase.h*/
#define CoUninitialize_win               CoUninitialize            /*objbase.h*/
#define CreateCaret_win                  CreateCaret               /*winuser.h*/
#define CreateCompatibleBitmap_win       CreateCompatibleBitmap     /*wingdi.h*/
#define CreateCompatibleDC_win           CreateCompatibleDC         /*wingdi.h*/
#define CreateDC_win                     CreateDC                   /*wingdi.h*/
#define CreateDirectory_win              CreateDirectory           /*winbase.h*/
#define CreateDirectoryW_win             CreateDirectoryW          /*winbase.h*/
#define CreateEvent_win                  CreateEvent               /*winbase.h*/
#define CreateFile_win                   CreateFile                /*winbase.h*/
#define CreateFileA_win                  CreateFileA               /*winbase.h*/
#define CreateFileW_win                  CreateFileW               /*winbase.h*/
#define CreateFont_win                   CreateFont                 /*wingdi.h*/
#define CreateFontIndirect_win           CreateFontIndirect         /*wingdi.h*/
#define CreateMenu_win                   CreateMenu                /*winuser.h*/
#define CreateMutex_win                  CreateMutex               /*winbase.h*/
#define CreatePen_win                    CreatePen                  /*wingdi.h*/
#define CreateProcess_win                CreateProcess             /*winbase.h*/
#define CreateRectRgn_win                CreateRectRgn              /*wingdi.h*/
#define CreateRoundRectRgn_win           CreateRoundRectRgn         /*wingdi.h*/
#define CreateService_win                CreateService              /*winsvc.h*/
#define CreateSolidBrush_win             CreateSolidBrush           /*wingdi.h*/
#define CreateStreamOnHGlobal_win        CreateStreamOnHGlobal        /*ole2.h*/
#define CreateThread_win                 CreateThread              /*winbase.h*/
#define CreateToolhelp32Snapshot_win     CreateToolhelp32Snapshot /*tlhelp32.h*/
#define CreateWindow_win                 CreateWindow              /*winuser.h*/
#define CreateWindowEx_win               CreateWindowEx            /*winuser.h*/
#define DebugBreak_win                   DebugBreak                /*winbase.h*/
#define DefWindowProc_win                DefWindowProc             /*winuser.h*/
#define DeleteCriticalSection_win        DeleteCriticalSection     /*winbase.h*/
#define DeleteDC_win                     DeleteDC                   /*wingdi.h*/
#define DeleteFile_win                   DeleteFile                /*winbase.h*/
#define DeleteObject_win                 DeleteObject               /*wingdi.h*/
#define DeleteService_win                DeleteService              /*winsvc.h*/
#define DeregisterEventSource_win        DeregisterEventSource     /*winbase.h*/
#define DestroyCaret_win                 DestroyCaret              /*winuser.h*/
#define DestroyMenu_win                  DestroyMenu               /*winuser.h*/
#define DestroyWindow_win                DestroyWindow             /*winuser.h*/
#define DialogBox_win                    DialogBox                 /*winuser.h*/
#define DialogBoxIndirect_win            DialogBoxIndirect         /*winuser.h*/
#define DispatchMessage_win              DispatchMessage           /*winuser.h*/
#define DPtoLP_win                       DPtoLP                     /*wingdi.h*/
#define DragAcceptFiles_win              DragAcceptFiles          /*shellapi.h*/
#define DragFinish_win                   DragFinish               /*shellapi.h*/
#define DragQueryFile_win                DragQueryFile            /*shellapi.h*/
#define DrawEdge_win                     DrawEdge                  /*winuser.h*/
#define DrawFocusRect_win                DrawFocusRect             /*winuser.h*/
#define DrawFrameControl_win             DrawFrameControl          /*winuser.h*/
#define DrawText_win                     DrawText                  /*winuser.h*/
#define Ellipse_win                      Ellipse                    /*wingdi.h*/
#define EmptyClipboard_win               EmptyClipboard            /*winuser.h*/
#define EnableWindow_win                 EnableWindow              /*winuser.h*/
#define EndDialog_win                    EndDialog                 /*winuser.h*/
#define EndDoc_win                       EndDoc                     /*wingdi.h*/
#define EndPage_win                      EndPage                    /*wingdi.h*/
#define EndPaint_win                     EndPaint                  /*winuser.h*/
#define EndPath_win                      EndPath                    /*wingdi.h*/
#define EnterCriticalSection_win         EnterCriticalSection      /*winbase.h*/
#define EnumProcesses_win                EnumProcesses               /*psapi.h*/
#define EnumProcessModules_win           EnumProcessModules          /*psapi.h*/
#define EnumThreadWindows_win            EnumThreadWindows         /*winuser.h*/
#define EnumWindows_win                  EnumWindows               /*winuser.h*/
#define EqualRect_win                    EqualRect                 /*winuser.h*/
#define ExtSelectClipRgn_win             ExtSelectClipRgn           /*wingdi.h*/
#define ExtTextOut_win                   ExtTextOut                 /*wingdi.h*/
#define FileTimeToSystemTime_win         FileTimeToSystemTime      /*winbase.h*/
#define FillMemory_win                   FillMemory                /*winbase.h*/
#define FillRect_win                     FillRect                  /*winuser.h*/
#define FindClose_win                    FindClose                 /*winbase.h*/
#define FindFirstFile_win                FindFirstFile             /*winbase.h*/
#define FindFirstFileEx_win              FindFirstFileEx           /*winbase.h*/
#define FindFirstFileW_win               FindFirstFileW            /*winbase.h*/
#define FindNextFile_win                 FindNextFile              /*winbase.h*/
#define FindNextFileW_win                FindNextFileW             /*winbase.h*/
#define FindResource_win                 FindResource              /*winbase.h*/
#define FlushFileBuffers_win             FlushFileBuffers          /*winbase.h*/
#define FormatMessage_win                FormatMessage             /*winbase.h*/
#define FreeLibrary_win                  FreeLibrary               /*winbase.h*/
#define FreeResource_win                 FreeResource              /*winbase.h*/
#define GetActiveWindow_win              GetActiveWindow           /*winuser.h*/
#define GetCharWidth32_win               GetCharWidth32             /*wingdi.h*/
#define GetClassInfoEx_win               GetClassInfoEx            /*winuser.h*/
#define GetClassNameA_win                GetClassNameA             /*winuser.h*/
#define GetClientRect_win                GetClientRect             /*winuser.h*/
#define GetClipboardData_win             GetClipboardData          /*winuser.h*/
#define GetClipRgn_win                   GetClipRgn                 /*wingdi.h*/
#define GetComboBoxInfo_win              GetComboBoxInfo           /*winuser.h*/
#define GetCommandLine_win               GetCommandLine            /*winbase.h*/
#define GetCurrentDirectory_win          GetCurrentDirectory       /*winbase.h*/
#define GetCurrentProcess_win            GetCurrentProcess         /*winbase.h*/
#define GetCurrentProcessId_win          GetCurrentProcessId       /*winbase.h*/
#define GetCurrentThread_win             GetCurrentThread          /*winbase.h*/
#define GetCurrentThreadId_win           GetCurrentThreadId        /*winbase.h*/
#define GetCursorPos_win                 GetCursorPos              /*winuser.h*/
#define GetDC_win                        GetDC                     /*winuser.h*/
#define GetDefaultPrinter_win            GetDefaultPrinter        /*winspool.h*/
#define GetDeviceCaps_win                GetDeviceCaps              /*wingdi.h*/
#define GetDiskFreeSpace_win             GetDiskFreeSpace          /*winbase.h*/
#define GetDiskFreeSpaceEx_win           GetDiskFreeSpaceEx        /*winbase.h*/
#define GetDlgItem_win                   GetDlgItem                /*winuser.h*/
#define GetDlgItemText_win               GetDlgItemText            /*winuser.h*/
#define GetFileAttributesW_win           GetFileAttributesW        /*winbase.h*/
#define GetFileSize_win                  GetFileSize               /*winbase.h*/
#define GetFocus_win                     GetFocus                  /*winuser.h*/
#define GetForegroundWindow_win          GetForegroundWindow       /*winuser.h*/
#define GetFullPathName_win              GetFullPathName           /*winbase.h*/
#define GetKeyState_win                  GetKeyState               /*winuser.h*/
#define GetLastError_win                 GetLastError              /*winbase.h*/
#define GetLengthSid_win                 GetLengthSid              /*winbase.h*/
#define GetLocaleInfo_win                GetLocaleInfo              /*winnls.h*/
#define GetLocalTime_win                 GetLocalTime              /*winbase.h*/
#define GetMapMode_win                   GetMapMode                 /*wingdi.h*/
#define GetMenu_win                      GetMenu                   /*winuser.h*/
#define GetMessage_win                   GetMessage                /*winuser.h*/
#define GetModuleFileName_win            GetModuleFileName         /*winbase.h*/
#define GetModuleFileNameEx_win          GetModuleFileNameEx       /*winbase.h*/
#define GetModuleHandle_win              GetModuleHandle           /*winbase.h*/
#define GetOpenFileName_win              GetOpenFileName           /*commdlg.h*/
#define GetOverlappedResult_win          GetOverlappedResult       /*winbase.h*/
#define GetParent_win                    GetParent                 /*winuser.h*/
#define GetProcAddress_win               GetProcAddress            /*winbase.h*/
#define GetProcessHeap_win               GetProcessHeap            /*winbase.h*/
#define GetScrollInfo_win                GetScrollInfo             /*winuser.h*/
#define GetStdHandle_win                 GetStdHandle              /*winbase.h*/
#define GetStockObject_win               GetStockObject             /*wingdi.h*/
#define GetSysColor_win                  GetSysColor               /*winuser.h*/
#define GetSysColorBrush_win             GetSysColorBrush          /*winuser.h*/
#define GetSystemMetrics_win             GetSystemMetrics          /*winuser.h*/
#define GetSystemTime_win                GetSystemTime             /*winbase.h*/
#define GetTempFileName_win              GetTempFileName           /*winbase.h*/
#define GetTempPath_win                  GetTempPath               /*winbase.h*/
#define GetTextExtentPoint32_win         GetTextExtentPoint32       /*wingdi.h*/
#define GetTextMetrics_win               GetTextMetrics             /*wingdi.h*/
#define GetTickCount_win                 GetTickCount              /*winbase.h*/
#define GetTokenInformation_win          GetTokenInformation       /*winbase.h*/
#define GetVersionEx_win                 GetVersionEx              /*winbase.h*/
#define GetVolumeInformation_win         GetVolumeInformation      /*winbase.h*/
#define GetWindowDC_win                  GetWindowDC               /*winuser.h*/
#define GetWindowLong_win                GetWindowLong             /*winuser.h*/
#define GetWindowLongPtr_win             GetWindowLongPtr          /*winuser.h*/
#define GetWindowRect_win                GetWindowRect             /*winuser.h*/
#define GetWindowsDirectory_win          GetWindowsDirectory       /*winbase.h*/
#define GetWindowText_win                GetWindowText             /*winuser.h*/
#define GetWindowTextA_win               GetWindowTextA            /*winuser.h*/
#define GetWindowTextLength_win          GetWindowTextLength       /*winuser.h*/
#define GlobalAlloc_win                  GlobalAlloc               /*winbase.h*/
#define GlobalFree_win                   GlobalFree                /*winbase.h*/
#define GlobalLock_win                   GlobalLock                /*winbase.h*/
#define GlobalMemoryStatus_win           GlobalMemoryStatus        /*winbase.h*/
#define GlobalSize_win                   GlobalSize                /*winbase.h*/
#define GlobalUnlock_win                 GlobalUnlock              /*winbase.h*/
#define HeapAlloc_win                    HeapAlloc                 /*winbase.h*/
#define HeapFree_win                     HeapFree                  /*winbase.h*/
#define HeapReAlloc_win                  HeapReAlloc               /*winbase.h*/
#define HeapValidate_win                 HeapValidate              /*winbase.h*/
#define HideCaret_win                    HideCaret                 /*winuser.h*/
#define InitCommonControls_win           InitCommonControls       /*commctrl.h*/
#define InitCommonControlsEx_win         InitCommonControlsEx     /*commctrl.h*/
#define InvalidateRect_win               InvalidateRect            /*winuser.h*/
#define IsChild_win                      IsChild                   /*winuser.h*/
#define IsDebuggerPresent_win            IsDebuggerPresent         /*winbase.h*/
#define IsDialogMessage_win              IsDialogMessage           /*winuser.h*/
#define IsIconic_win                     IsIconic                  /*winuser.h*/
#define IsMenu_win                       IsMenu                    /*winuser.h*/
#define IsTextUnicode_win                IsTextUnicode             /*winbase.h*/
#define IsWindow_win                     IsWindow                  /*winuser.h*/
#define IsWindowEnabled_win              IsWindowEnabled           /*winuser.h*/
#define IsWindowVisible_win              IsWindowVisible           /*winuser.h*/
#define IsZoomed_win                     IsZoomed                  /*winuser.h*/
#define KillTimer_win                    KillTimer                 /*winuser.h*/
#define LeaveCriticalSection_win         LeaveCriticalSection      /*winbase.h*/
#define LineTo_win                       LineTo                     /*wingdi.h*/
#define LoadAccelerators_win             LoadAccelerators          /*winuser.h*/
#define LoadCursor_win                   LoadCursor                /*winuser.h*/
#define LoadIcon_win                     LoadIcon                  /*winuser.h*/
#define LoadImage_win                    LoadImage                 /*winuser.h*/
#define LoadLibrary_win                  LoadLibrary               /*winbase.h*/
#define LoadResource_win                 LoadResource              /*winbase.h*/
#define LoadString_win                   LoadString                /*winuser.h*/
#define LocalAlloc_win                   LocalAlloc                /*winbase.h*/
#define LocalFree_win                    LocalFree                 /*winbase.h*/
#define LockFile_win                     LockFile                  /*winbase.h*/
#define LockResource_win                 LockResource              /*winbase.h*/
#define MapVirtualKey_win                MapVirtualKey             /*winuser.h*/
#define MapWindowPoints_win              MapWindowPoints           /*winuser.h*/
#define MessageBeep_win                  MessageBeep               /*winuser.h*/
#define MessageBox_win                   MessageBox                /*winuser.h*/
#define MessageBoxA_win                  MessageBoxA               /*winuser.h*/
#define midiOutClose_win                 midiOutClose             /*mmsystem.h*/
#define midiOutOpen_win                  midiOutOpen              /*mmsystem.h*/
#define midiOutReset_win                 midiOutReset             /*mmsystem.h*/
#define midiOutShortMsg_win              midiOutShortMsg          /*mmsystem.h*/
#define mmioAscend_win                   mmioAscend               /*mmsystem.h*/
#define mmioClose_win                    mmioClose                /*mmsystem.h*/
#define mmioCreateChunk_win              mmioCreateChunk          /*mmsystem.h*/
#define mmioFOURCC_win                   mmioFOURCC               /*mmsystem.h*/
#define mmioOpen_win                     mmioOpen                 /*mmsystem.h*/
#define mmioWrite_win                    mmioWrite                /*mmsystem.h*/
#define MoveFile_win                     MoveFile                  /*winbase.h*/
#define MoveMemory_win                   MoveMemory                /*winbase.h*/
#define MoveToEx_win                     MoveToEx                   /*wingdi.h*/
#define MoveWindow_win                   MoveWindow                /*winuser.h*/
#define MulDiv_win                       MulDiv                    /*winbase.h*/
#define OffsetRect_win                   OffsetRect                /*winuser.h*/
#define OleLoadPicture_win               OleLoadPicture             /*olectl.h*/
#define OpenClipboard_win                OpenClipboard             /*winuser.h*/
#define OpenEvent_win                    OpenEvent                 /*winbase.h*/
#define OpenMutex_win                    OpenMutex                 /*winbase.h*/
#define OpenProcess_win                  OpenProcess               /*winbase.h*/
#define OpenProcessToken_win             OpenProcessToken          /*winbase.h*/
#define OpenSCManager_win                OpenSCManager              /*winsvc.h*/
#define OpenService_win                  OpenService                /*winsvc.h*/
#define OpenThreadToken_win              OpenThreadToken           /*winbase.h*/
#define OutputDebugString_win            OutputDebugString         /*winbase.h*/
#define PageSetupDlg_win                 PageSetupDlg              /*commdlg.h*/
#define PathAppend_win                   PathAppend                /*shlwapi.h*/
#define PathFileExists_win               PathFileExists            /*shlwapi.h*/
#define PathFindOnPath_win               PathFindOnPath            /*shlwapi.h*/
#define PathRemoveFileSpec_win           PathRemoveFileSpec        /*shlwapi.h*/
#define PathStripPath_win                PathStripPath             /*shlwapi.h*/
#define PeekMessage_win                  PeekMessage               /*winuser.h*/
#define Polygon_win                      Polygon                    /*wingdi.h*/
#define Polyline_win                     Polyline                   /*wingdi.h*/
#define PostMessage_win                  PostMessage               /*winuser.h*/
#define PostQuitMessage_win              PostQuitMessage           /*winuser.h*/
#define PostThreadMessage_win            PostThreadMessage         /*winuser.h*/
#define PrintDlg_win                     PrintDlg                  /*commdlg.h*/
#define Process32First_win               Process32First          /* tlhelp32.h*/
#define Process32Next_win                Process32Next           /* tlhelp32.h*/
#define PtInRect_win                     PtInRect                  /*winuser.h*/
#define ReadFile_win                     ReadFile                  /*winbase.h*/
#define Rectangle_win                    Rectangle                  /*wingdi.h*/
#define RedrawWindow_win                 RedrawWindow              /*winuser.h*/
#define RegCloseKey_win                  RegCloseKey                /*winreg.h*/
#define RegCreateKeyEx_win               RegCreateKeyEx             /*winreg.h*/
#define RegDeleteValue_win               RegDeleteValue             /*winreg.h*/
#define RegisterClassEx_win              RegisterClassEx           /*winuser.h*/
#define RegisterEventSource_win          RegisterEventSource       /*winbase.h*/
#define RegOpenKeyEx_win                 RegOpenKeyEx               /*winreg.h*/
#define RegQueryValueEx_win              RegQueryValueEx            /*winreg.h*/
#define RegSetValueEx_win                RegSetValueEx              /*winreg.h*/
#define ReleaseCapture_win               ReleaseCapture            /*winuser.h*/
#define ReleaseDC_win                    ReleaseDC                 /*winuser.h*/
#define ReleaseMutex_win                 ReleaseMutex              /*winbase.h*/
#define RemoveDirectory_win              RemoveDirectory           /*winbase.h*/
#define ReportEvent_win                  ReportEvent               /*winbase.h*/
#define ResetEvent_win                   ResetEvent                /*winbase.h*/
#define RoundRect_win                    RoundRect                  /*wingdi.h*/
#define SafeArrayGetElement_win          SafeArrayGetElement       /*oleauto.h*/
#define SafeArrayGetUBound_win           SafeArrayGetUBound        /*oleauto.h*/
#define SelectClipRgn_win                SelectClipRgn              /*wingdi.h*/
#define SelectObject_win                 SelectObject               /*wingdi.h*/
#define SendMessage_win                  SendMessage               /*winuser.h*/
#define SetActiveWindow_win              SetActiveWindow           /*winuser.h*/
#define SetBkColor_win                   SetBkColor                 /*wingdi.h*/
#define SetBkMode_win                    SetBkMode                  /*wingdi.h*/
#define SetCapture_win                   SetCapture                /*winuser.h*/
#define SetCaretPos_win                  SetCaretPos               /*winuser.h*/
#define SetClipboardData_win             SetClipboardData          /*winuser.h*/
#define SetCursor_win                    SetCursor                 /*winuser.h*/
#define SetDCBrushColor_win              SetDCBrushColor            /*wingdi.h*/
#define SetDCPenColor_win                SetDCPenColor              /*wingdi.h*/
#define SetDlgItemText_win               SetDlgItemText            /*winuser.h*/
#define SetEvent_win                     SetEvent                  /*winbase.h*/
#define SetFilePointer_win               SetFilePointer            /*winbase.h*/
#define SetFocus_win                     SetFocus                  /*winuser.h*/
#define SetMapMode_win                   SetMapMode                 /*wingdi.h*/
#define SetMenu_win                      SetMenu                   /*winuser.h*/
#define SetMenuItemInfo_win              SetMenuItemInfo           /*winuser.h*/
#define SetParent_win                    SetParent                 /*winuser.h*/
#define SetRect_win                      SetRect                   /*winuser.h*/
#define SetScrollInfo_win                SetScrollInfo             /*winuser.h*/
#define SetServiceStatus_win             SetServiceStatus           /*winsvc.h*/
#define SetTextColor_win                 SetTextColor               /*wingdi.h*/
#define SetTimer_win                     SetTimer                  /*winuser.h*/
#define SetWindowLong_win                SetWindowLong             /*winuser.h*/
#define SetWindowLongPtr_win             SetWindowLongPtr          /*winuser.h*/
#define SetWindowOrgEx_win               SetWindowOrgEx             /*wingdi.h*/
#define SetWindowPos_win                 SetWindowPos              /*winuser.h*/
#define SetWindowRgn_win                 SetWindowRgn              /*winuser.h*/
#define SetWindowText_win                SetWindowText             /*winuser.h*/
#define ShellExecute_win                 ShellExecute             /*shellapi.h*/
#define SHFileOperation_win              SHFileOperation          /*shellapi.h*/
#define ShowCaret_win                    ShowCaret                 /*winuser.h*/
#define ShowWindow_win                   ShowWindow                /*winuser.h*/
#define SizeofResource_win               SizeofResource            /*winbase.h*/
#define Sleep_win                        Sleep                     /*winbase.h*/
#define SleepEx_win                      SleepEx                   /*winbase.h*/
#define StartDoc_win                     StartDoc                   /*wingdi.h*/
#define StartPage_win                    StartPage                  /*wingdi.h*/
#define StretchDIBits_win                StretchDIBits              /*wingdi.h*/
#define StrokeAndFillPath_win            StrokeAndFillPath          /*wingdi.h*/
#define SysAllocString_win               SysAllocString            /*oleauto.h*/
#define SysAllocStringByteLen_win        SysAllocStringByteLen     /*oleauto.h*/
#define SysAllocStringLen_win            SysAllocStringLen         /*oleauto.h*/
#define SysFreeString_win                SysFreeString             /*oleauto.h*/
#define SysStringByteLen_win             SysStringByteLen          /*oleauto.h*/
#define SystemTimeToFileTime_win         SystemTimeToFileTime      /*winbase.h*/
#define TerminateProcess_win             TerminateProcess        /* winbase.h */
#define TextOut_win                      TextOut                    /*wingdi.h*/
#define TokenUser_win                    TokenUser                   /*winnt.h*/
#define TranslateAccelerator_win         TranslateAccelerator      /*winuser.h*/
#define TranslateMessage_win             TranslateMessage          /*winuser.h*/
#define UnlockFile_win                   UnlockFile                /*winbase.h*/
#define UnregisterHotKey_win             UnregisterHotKey          /*winuser.h*/
#define UpdateWindow_win                 UpdateWindow              /*winuser.h*/
#define UuidCreate_win                   UuidCreate                 /*rpcdce.h*/
#define VarBstrFromCy_win                VarBstrFromCy             /*oleauto.h*/
#define VarCyAdd_win                     VarCyAdd                  /*oleauto.h*/
#define VarCyCmpR8_win                   VarCyCmpR8                /*oleauto.h*/
#define VarCyFromStr_win                 VarCyFromStr              /*oleauto.h*/
#define VarCyMul_win                     VarCyMul                  /*oleauto.h*/
#define VarCyMulI4_win                   VarCyMulI4                /*oleauto.h*/
#define VarCyNeg_win                     VarCyNeg                  /*oleauto.h*/
#define VarCySub_win                     VarCySub                  /*oleauto.h*/
#define VarDateFromStr_win               VarDateFromStr            /*oleauto.h*/
#define VariantChangeType_win            VariantChangeType         /*oleauto.h*/
#define VariantClear_win                 VariantClear              /*oleauto.h*/
#define WaitForSingleObject_win          WaitForSingleObject       /*winbase.h*/
#define WaitMessage_win                  WaitMessage               /*winuser.h*/
#define waveInAddBuffer_win              waveInAddBuffer          /*mmsystem.h*/
#define waveInClose_win                  waveInClose              /*mmsystem.h*/
#define waveInGetDevCaps_win             waveInGetDevCaps         /*mmsystem.h*/
#define waveInGetErrorText_win           waveInGetErrorText       /*mmsystem.h*/
#define waveInGetNumDevs_win             waveInGetNumDevs         /*mmsystem.h*/
#define waveInOpen_win                   waveInOpen               /*mmsystem.h*/
#define waveInPrepareHeader_win          waveInPrepareHeader      /*mmsystem.h*/
#define waveInStart_win                  waveInStart              /*mmsystem.h*/
#define waveInStop_win                   waveInStop               /*mmsystem.h*/
#define WideCharToMultiByte_win          WideCharToMultiByte        /*winnls.h*/
#define WindowFromDC_win                 WindowFromDC              /*winuser.h*/
#define WriteConsoleInputA_win           WriteConsoleInputA         /*wincon.h*/
#define WriteFile_win                    WriteFile                 /*winbase.h*/

#define ChangeWindowMessageFilter_win \
    ChangeWindowMessageFilter                                      /*winuser.h*/

#define FileTimeToLocalFileTime_win \
    FileTimeToLocalFileTime                                        /*winbase.h*/

#define GetConsoleScreenBufferInfo_win \
    GetConsoleScreenBufferInfo                                      /*wincon.h*/

#define GetWindowThreadProcessId_win \
    GetWindowThreadProcessId                                       /*winuser.h*/

#define InitializeCriticalSection_win \
    InitializeCriticalSection                                      /*winbase.h*/

#define InitializeCriticalSectionAndSpinCount_win \
    InitializeCriticalSectionAndSpinCount                          /*winbase.h*/

#define IsClipboardFormatAvailable_win \
    IsClipboardFormatAvailable                                     /*winuser.h*/

#define QueryPerformanceCounter_win \
    QueryPerformanceCounter                                        /*winbase.h*/

#define QueryPerformanceFrequency_win \
    QueryPerformanceFrequency                                      /*winbase.h*/

#define RegisterServiceCtrlHandler_win \
    RegisterServiceCtrlHandler                                      /*winsvc.h*/

#define SetConsoleScreenBufferSize_win \
    SetConsoleScreenBufferSize                                      /*wincon.h*/

#define StartServiceCtrlDispatcher_win \
    StartServiceCtrlDispatcher                                      /*winsvc.h*/

#define SystemTimeToVariantTime_win \
    SystemTimeToVariantTime                                        /*oleauto.h*/

#define VariantTimeToSystemTime_win \
    VariantTimeToSystemTime                                        /*oleauto.h*/

#define WaitForMultipleObjects_win \
    WaitForMultipleObjects                                         /*winbase.h*/

#define waveInUnprepareHeader_win \
    waveInUnprepareHeader                                         /*mmsystem.h*/

/* -------------------------------------------------------------------------- */
/* Definitions: Windows API Constants, Types, Macros, Et Cetera               */

#define _MAX_PATH_win                        _MAX_PATH              /*stdlib.h*/
#define ANSI_CHARSET_win                     ANSI_CHARSET           /*wingdi.h*/
#define APIENTRY_win                         APIENTRY               /*windef.h*/
#define ATOM_win                             ATOM                   /*windef.h*/
#define BF_MONO_win                          BF_MONO               /*winuser.h*/
#define BF_RECT_win                          BF_RECT               /*winuser.h*/
#define BITMAP_win                           BITMAP                 /*wingdi.h*/
#define BN_CLICKED_win                       BN_CLICKED            /*winuser.h*/
#define BOOL_win                             BOOL                   /*windef.h*/
#define BS_3STATE_win                        BS_3STATE             /*winuser.h*/
#define BS_AUTO3STATE_win                    BS_AUTO3STATE         /*winuser.h*/
#define BS_AUTOCHECKBOX_win                  BS_AUTOCHECKBOX       /*winuser.h*/
#define BS_AUTORADIOBUTTON_win               BS_AUTORADIOBUTTON    /*winuser.h*/
#define BS_BITMAP_win                        BS_BITMAP             /*winuser.h*/
#define BS_BOTTOM_win                        BS_BOTTOM             /*winuser.h*/
#define BS_CENTER_win                        BS_CENTER             /*winuser.h*/
#define BS_CHECKBOX_win                      BS_CHECKBOX           /*winuser.h*/
#define BS_COMMANDLINK_win                   BS_COMMANDLINK       /*commctrl.h*/
#define BS_DEFCOMMANDLINK_win                BS_DEFCOMMANDLINK    /*commctrl.h*/
#define BS_DEFPUSHBUTTON_win                 BS_DEFPUSHBUTTON      /*winuser.h*/
#define BS_DEFSPLITBUTTON_win                BS_DEFSPLITBUTTON    /*commctrl.h*/
#define BS_FLAT_win                          BS_FLAT               /*winuser.h*/
#define BS_GROUPBOX_win                      BS_GROUPBOX           /*winuser.h*/
#define BS_ICON_win                          BS_ICON               /*winuser.h*/
#define BS_LEFT_win                          BS_LEFT               /*winuser.h*/
#define BS_LEFTTEXT_win                      BS_LEFTTEXT           /*winuser.h*/
#define BS_MULTILINE_win                     BS_MULTILINE          /*winuser.h*/
#define BS_NOTIFY_win                        BS_NOTIFY             /*winuser.h*/
#define BS_OWNERDRAW_win                     BS_OWNERDRAW          /*winuser.h*/
#define BS_PUSHBUTTON_win                    BS_PUSHBUTTON         /*winuser.h*/
#define BS_PUSHLIKE_win                      BS_PUSHLIKE           /*winuser.h*/
#define BS_RADIOBUTTON_win                   BS_RADIOBUTTON        /*winuser.h*/
#define BS_RIGHT_win                         BS_RIGHT              /*winuser.h*/
#define BS_RIGHTBUTTON_win                   BS_RIGHTBUTTON        /*winuser.h*/
#define BS_SPLITBUTTON_win                   BS_SPLITBUTTON       /*commctrl.h*/
#define BS_TEXT_win                          BS_TEXT               /*winuser.h*/
#define BS_TOP_win                           BS_TOP                /*winuser.h*/
#define BS_TYPEMASK_win                      BS_TYPEMASK           /*winuser.h*/
#define BS_USERBUTTON_win                    BS_USERBUTTON         /*winuser.h*/
#define BS_VCENTER_win                       BS_VCENTER            /*winuser.h*/
#define BST_CHECKED_win                      BST_CHECKED           /*winuser.h*/
#define BST_UNCHECKED_win                    BST_UNCHECKED         /*winuser.h*/
#define BSTR_win                             BSTR                   /*wtypes.h*/
#define BYTE_win                             BYTE                   /*windef.h*/
#define CALLBACK_FUNCTION_win                CALLBACK_FUNCTION    /*mmsystem.h*/
#define CALLBACK_win                         CALLBACK               /*windef.h*/
#define CB_ADDSTRING_win                     CB_ADDSTRING          /*winuser.h*/
#define CBS_DROPDOWN_win                     CBS_DROPDOWN          /*winuser.h*/
#define CBS_DROPDOWNLIST_win                 CBS_DROPDOWNLIST      /*winuser.h*/
#define CBS_SIMPLE_win                       CBS_SIMPLE            /*winuser.h*/
#define CDERR_DIALOGFAILURE_win              CDERR_DIALOGFAILURE     /*cderr.h*/
#define CDERR_FINDRESFAILURE_win             CDERR_FINDRESFAILURE    /*cderr.h*/
#define CDERR_INITIALIZATION_win             CDERR_INITIALIZATION    /*cderr.h*/
#define CDERR_LOADRESFAILURE_win             CDERR_LOADRESFAILURE    /*cderr.h*/
#define CDERR_LOADSTRFAILURE_win             CDERR_LOADSTRFAILURE    /*cderr.h*/
#define CDERR_LOCKRESFAILURE_win             CDERR_LOCKRESFAILURE    /*cderr.h*/
#define CDERR_MEMALLOCFAILURE_win            CDERR_MEMALLOCFAILURE   /*cderr.h*/
#define CDERR_MEMLOCKFAILURE_win             CDERR_MEMLOCKFAILURE    /*cderr.h*/
#define CDERR_NOHINSTANCE_win                CDERR_NOHINSTANCE       /*cderr.h*/
#define CDERR_NOHOOK_win                     CDERR_NOHOOK            /*cderr.h*/
#define CDERR_NOTEMPLATE_win                 CDERR_NOTEMPLATE        /*cderr.h*/
#define CDERR_REGISTERMSGFAIL_win            CDERR_REGISTERMSGFAIL   /*cderr.h*/
#define CDERR_STRUCTSIZE_win                 CDERR_STRUCTSIZE        /*cderr.h*/
#define CF_TEXT_win                          CF_TEXT               /*winuser.h*/
#define CF_UNICODETEXT_win                   CF_UNICODETEXT        /*winuser.h*/
#define CFERR_MAXLESSTHANMIN_win             CFERR_MAXLESSTHANMIN    /*cderr.h*/
#define CFERR_NOFONTS_win                    CFERR_NOFONTS           /*cderr.h*/
#define CLIP_DEFAULT_PRECIS_win              CLIP_DEFAULT_PRECIS    /*wingdi.h*/
#define CLR_INVALID_win                      CLR_INVALID            /*wingdi.h*/
#define COLOR_3DFACE_win                     COLOR_3DFACE          /*winuser.h*/
#define COLOR_3DHIGHLIGHT_win                COLOR_3DHIGHLIGHT     /*winuser.h*/
#define COLOR_3DSHADOW_win                   COLOR_3DSHADOW        /*winuser.h*/
#define COLOR_BTNFACE_win                    COLOR_BTNFACE         /*winuser.h*/
#define COLOR_BTNSHADOW_win                  COLOR_BTNSHADOW       /*winuser.h*/
#define COLOR_BTNTEXT_win                    COLOR_BTNTEXT         /*winuser.h*/
#define COLOR_WINDOW_win                     COLOR_WINDOW          /*winuser.h*/
#define COLOR_WINDOWTEXT_win                 COLOR_WINDOWTEXT      /*winuser.h*/
#define COLORREF_win                         COLORREF               /*windef.h*/
#define CONST_win                            CONST                  /*windef.h*/
#define CP_ACP_win                           CP_ACP                 /*winnls.h*/
#define CP_UTF8_win                          CP_UTF8                /*winnls.h*/
#define CREATE_NEW_win                       CREATE_NEW            /*winbase.h*/
#define CREATESTRUCT_win                     CREATESTRUCT          /*winuser.h*/
#define CRITICAL_SECTION_win                 CRITICAL_SECTION      /*winbase.h*/
#define CRYPT_E_NOT_FOUND_win                CRYPT_E_NOT_FOUND    /*winerror.h*/
#define CS_DBLCLKS_win                       CS_DBLCLKS            /*winuser.h*/
#define CS_HREDRAW_win                       CS_HREDRAW            /*winuser.h*/
#define CS_VREDRAW_win                       CS_VREDRAW            /*winuser.h*/
#define CURRENCY_win                         CURRENCY                /*oaidl.h*/
#define CW_USEDEFAULT_win                    CW_USEDEFAULT         /*winuser.h*/
#define CY_win                               CY                     /*wtypes.h*/
#define DATE_win                             DATE                   /*wtypes.h*/
#define DECIMAL_win                          DECIMAL                /*wtypes.h*/
#define DEFAULT_CHARSET_win                  DEFAULT_CHARSET        /*wingdi.h*/
#define DEFAULT_PITCH_win                    DEFAULT_PITCH          /*wingdi.h*/
#define DEFAULT_QUALITY_win                  DEFAULT_QUALITY        /*wingdi.h*/
#define DFC_BUTTON_win                       DFC_BUTTON            /*winuser.h*/
#define DFCS_BUTTONPUSH_win                  DFCS_BUTTONPUSH       /*winuser.h*/
#define DFCS_PUSHED_win                      DFCS_PUSHED           /*winuser.h*/
#define DIB_RGB_COLORS_win                   DIB_RGB_COLORS         /*wingdi.h*/
#define DISP_E_BADVARTYPE_win                DISP_E_BADVARTYPE    /*winerror.h*/
#define DISP_E_OVERFLOW_win                  DISP_E_OVERFLOW      /*winerror.h*/
#define DISP_E_TYPEMISMATCH_win              DISP_E_TYPEMISMATCH  /*winerror.h*/
#define DLGPROC_win                          DLGPROC               /*winuser.h*/
#define DT_CENTER_win                        DT_CENTER             /*winuser.h*/
#define DT_LEFT_win                          DT_LEFT               /*winuser.h*/
#define DT_NOCLIP_win                        DT_NOCLIP             /*winuser.h*/
#define DT_SINGLELINE_win                    DT_SINGLELINE         /*winuser.h*/
#define DT_VCENTER_win                       DT_VCENTER            /*winuser.h*/
#define DWORD_PTR_win                        DWORD_PTR             /*basetsd.h*/
#define E_INVALIDARG_win                     E_INVALIDARG         /*winerror.h*/
#define E_OUTOFMEMORY_win                    E_OUTOFMEMORY        /*winerror.h*/
#define E_UNEXPECTED_win                     E_UNEXPECTED         /*winerror.h*/
#define EC_RIGHTMARGIN_win                   EC_RIGHTMARGIN        /*winuser.h*/
#define EM_CANUNDO_win                       EM_CANUNDO            /*winuser.h*/
#define EM_CHARFROMPOS_win                   EM_CHARFROMPOS        /*winuser.h*/
#define EM_EMPTYUNDOBUFFER_win               EM_EMPTYUNDOBUFFER    /*winuser.h*/
#define EM_FMTLINES_win                      EM_FMTLINES           /*winuser.h*/
#define EM_GETFIRSTVISIBLELINE_win           EM_GETFIRSTVISIBLELINE/*winuser.h*/
#define EM_GETHANDLE_win                     EM_GETHANDLE          /*winuser.h*/
#define EM_GETIMESTATUS_win                  EM_GETIMESTATUS       /*winuser.h*/
#define EM_GETLIMITTEXT_win                  EM_GETLIMITTEXT       /*winuser.h*/
#define EM_GETLINE_win                       EM_GETLINE            /*winuser.h*/
#define EM_GETLINECOUNT_win                  EM_GETLINECOUNT       /*winuser.h*/
#define EM_GETMARGINS_win                    EM_GETMARGINS         /*winuser.h*/
#define EM_GETMODIFY_win                     EM_GETMODIFY          /*winuser.h*/
#define EM_GETPASSWORDCHAR_win               EM_GETPASSWORDCHAR    /*winuser.h*/
#define EM_GETRECT_win                       EM_GETRECT            /*winuser.h*/
#define EM_GETSEL_win                        EM_GETSEL             /*winuser.h*/
#define EM_GETTHUMB_win                      EM_GETTHUMB           /*winuser.h*/
#define EM_GETWORDBREAKPROC_win              EM_GETWORDBREAKPROC   /*winuser.h*/
#define EM_LIMITTEXT_win                     EM_LIMITTEXT          /*winuser.h*/
#define EM_LINEFROMCHAR_win                  EM_LINEFROMCHAR       /*winuser.h*/
#define EM_LINEINDEX_win                     EM_LINEINDEX          /*winuser.h*/
#define EM_LINELENGTH_win                    EM_LINELENGTH         /*winuser.h*/
#define EM_LINESCROLL_win                    EM_LINESCROLL         /*winuser.h*/
#define EM_POSFROMCHAR_win                   EM_POSFROMCHAR        /*winuser.h*/
#define EM_REPLACESEL_win                    EM_REPLACESEL         /*winuser.h*/
#define EM_SCROLL_win                        EM_SCROLL             /*winuser.h*/
#define EM_SCROLLCARET_win                   EM_SCROLLCARET        /*winuser.h*/
#define EM_SETHANDLE_win                     EM_SETHANDLE          /*winuser.h*/
#define EM_SETIMESTATUS_win                  EM_SETIMESTATUS       /*winuser.h*/
#define EM_SETLIMITTEXT_win                  EM_SETLIMITTEXT       /*winuser.h*/
#define EM_SETMARGINS_win                    EM_SETMARGINS         /*winuser.h*/
#define EM_SETMODIFY_win                     EM_SETMODIFY          /*winuser.h*/
#define EM_SETPASSWORDCHAR_win               EM_SETPASSWORDCHAR    /*winuser.h*/
#define EM_SETREADONLY_win                   EM_SETREADONLY        /*winuser.h*/
#define EM_SETRECT_win                       EM_SETRECT            /*winuser.h*/
#define EM_SETRECTNP_win                     EM_SETRECTNP          /*winuser.h*/
#define EM_SETSEL_win                        EM_SETSEL             /*winuser.h*/
#define EM_SETTABSTOPS_win                   EM_SETTABSTOPS        /*winuser.h*/
#define EM_SETWORDBREAKPROC_win              EM_SETWORDBREAKPROC   /*winuser.h*/
#define EM_UNDO_win                          EM_UNDO               /*winuser.h*/
#define ERROR_ALREADY_EXISTS_win             ERROR_ALREADY_EXISTS /*winerror.h*/
#define ERROR_FILE_NOT_FOUND_win             ERROR_FILE_NOT_FOUND /*winerror.h*/
#define ERROR_HANDLE_EOF_win                 ERROR_HANDLE_EOF     /*winerror.h*/
#define ERROR_IO_INCOMPLETE_win              ERROR_IO_INCOMPLETE  /*winerror.h*/
#define ERROR_MORE_DATA_win                  ERROR_MORE_DATA      /*winerror.h*/
#define ERROR_NO_MORE_FILES_win              ERROR_NO_MORE_FILES  /*winerror.h*/
#define ERROR_SUCCESS_win                    ERROR_SUCCESS        /*winerror.h*/
#define ERROR_win                            ERROR                  /*wingdi.h*/
#define ES_AUTOHSCROLL_win                   ES_AUTOHSCROLL        /*winuser.h*/
#define ES_AUTOVSCROLL_win                   ES_AUTOVSCROLL        /*winuser.h*/
#define ES_CENTER_win                        ES_CENTER             /*winuser.h*/
#define ES_LEFT_win                          ES_LEFT               /*winuser.h*/
#define ES_MULTILINE_win                     ES_MULTILINE          /*winuser.h*/
#define ES_PASSWORD_win                      ES_PASSWORD           /*winuser.h*/
#define ES_READONLY_win                      ES_READONLY           /*winuser.h*/
#define ES_RIGHT_win                         ES_RIGHT              /*winuser.h*/
#define ES_WANTRETURN_win                    ES_WANTRETURN         /*winuser.h*/
#define ETO_OPAQUE_win                       ETO_OPAQUE             /*wingdi.h*/
#define EVENT_MODIFY_STATE_win               EVENT_MODIFY_STATE      /*winnt.h*/
#define EVENTLOG_ERROR_TYPE_win              EVENTLOG_ERROR_TYPE     /*winnt.h*/
#define EVENTLOG_SUCCESS_win                 EVENTLOG_SUCCESS        /*winnt.h*/
#define EVENTLOG_WARNING_TYPE_win            EVENTLOG_WARNING_TYPE   /*winnt.h*/
#define FAILED_win                           FAILED               /*winerror.h*/
#define FALSE_win                            FALSE                  /*windef.h*/
#define FAR_win                              FAR                    /*windef.h*/
#define FARPROC_win                          FARPROC                /*windef.h*/
#define FF_DONTCARE_win                      FF_DONTCARE            /*wingdi.h*/
#define FF_SWISS_win                         FF_SWISS               /*wingdi.h*/
#define FILE_ATTRIBUTE_DIRECTORY_win         FILE_ATTRIBUTE_DIRECTORY/*winnt.h*/
#define FILE_ATTRIBUTE_NORMAL_win            FILE_ATTRIBUTE_NORMAL   /*winnt.h*/
#define FILE_BEGIN_win                       FILE_BEGIN            /*winbase.h*/
#define FILE_SHARE_READ_win                  FILE_SHARE_READ         /*winnt.h*/
#define FILE_SHARE_WRITE_win                 FILE_SHARE_WRITE        /*winnt.h*/
#define FILETIME_win                         FILETIME               /*windef.h*/
#define FNERR_BUFFERTOOSMALL_win             FNERR_BUFFERTOOSMALL    /*cderr.h*/
#define FNERR_INVALIDFILENAME_win            FNERR_INVALIDFILENAME   /*cderr.h*/
#define FNERR_SUBCLASSFAILURE_win            FNERR_SUBCLASSFAILURE   /*cderr.h*/
#define FO_DELETE_win                        FO_DELETE            /*shellapi.h*/
#define FOF_ALLOWUNDO_win                    FOF_ALLOWUNDO        /*shellapi.h*/
#define FOF_NOCONFIRMATION_win               FOF_NOCONFIRMATION   /*shellapi.h*/
#define FOF_NOERRORUI_win                    FOF_NOERRORUI        /*shellapi.h*/
#define FOF_SILENT_win                       FOF_SILENT           /*shellapi.h*/
#define FRERR_BUFFERLENGTHZERO_win           FRERR_BUFFERLENGTHZERO  /*cderr.h*/
#define FW_BOLD_win                          FW_BOLD                /*wingdi.h*/
#define FW_NORMAL_win                        FW_NORMAL              /*wingdi.h*/
#define GDI_ERROR_win                        GDI_ERROR              /*wingdi.h*/
#define GENERIC_READ_win                     GENERIC_READ            /*winnt.h*/
#define GENERIC_WRITE_win                    GENERIC_WRITE           /*winnt.h*/
#define GET_WHEEL_DELTA_WPARAM_win           GET_WHEEL_DELTA_WPARAM/*winuser.h*/
#define GMEM_MOVEABLE_win                    GMEM_MOVEABLE         /*winbase.h*/
#define GMEM_ZEROINIT_win                    GMEM_ZEROINIT         /*winbase.h*/
#define GW_OWNER_win                         GW_OWNER              /*winuser.h*/
#define GWL_HINSTANCE_win                    GWL_HINSTANCE         /*winuser.h*/
#define GWL_STYLE_win                        GWL_STYLE             /*winuser.h*/
#define GWL_WNDPROC_win                      GWL_WNDPROC           /*winuser.h*/
#define HACCEL_win                           HACCEL                 /*windef.h*/
#define HANDLE_win                           HANDLE                  /*winnt.h*/
#define HBITMAP_win                          HBITMAP                /*windef.h*/
#define HBRUSH_win                           HBRUSH                 /*windef.h*/
#define HCERTSTORE_win                       HCERTSTORE           /*wincrypt.h*/
#define HCURSOR_win                          HCURSOR                /*windef.h*/
#define HDC_win                              HDC                    /*windef.h*/
#define HDROP_win                            HDROP                /*shellapi.h*/
#define HEAP_ZERO_MEMORY_win                 HEAP_ZERO_MEMORY        /*winnt.h*/
#define HFONT_win                            HFONT                  /*windef.h*/
#define HGDI_ERROR_win                       HGDI_ERROR             /*wingdi.h*/
#define HGDIOBJ_win                          HGDIOBJ                /*windef.h*/
#define HGLOBAL_win                          HGLOBAL                /*windef.h*/
#define HIBYTE_win                           HIBYTE                 /*windef.h*/
#define HICON_win                            HICON                  /*wingdi.h*/
#define HINSTANCE_win                        HINSTANCE              /*windef.h*/
#define HIWORD_win                           HIWORD                 /*windef.h*/
#define HKEY_CLASSES_ROOT_win                HKEY_CLASSES_ROOT      /*winreg.h*/
#define HKEY_CURRENT_CONFIG_win              HKEY_CURRENT_CONFIG    /*winreg.h*/
#define HKEY_CURRENT_USER_win                HKEY_CURRENT_USER      /*winreg.h*/
#define HKEY_DYN_DATA_win                    HKEY_DYN_DATA          /*winreg.h*/
#define HKEY_LOCAL_MACHINE_win               HKEY_LOCAL_MACHINE     /*winreg.h*/
#define HKEY_PERFORMANCE_DATA_win            HKEY_PERFORMANCE_DATA  /*winreg.h*/
#define HKEY_PERFORMANCE_TEXT_win            HKEY_PERFORMANCE_TEXT  /*winreg.h*/
#define HKEY_USERS_win                       HKEY_USERS             /*winreg.h*/
#define HKEY_win                             HKEY                   /*windef.h*/
#define HMENU_win                            HMENU                  /*windef.h*/
#define HMIDIOUT_win                         HMIDIOUT                   /*none*/
#define HMMIO_win                            HMMIO                      /*none*/
#define HMODULE_win                          HMODULE                /*windef.h*/
#define HORZRES_win                          HORZRES                /*wingdi.h*/
#define HPEN_win                             HPEN                   /*windef.h*/
#define HRESULT_win                          HRESULT                 /*winnt.h*/
#define HRGN_win                             HRGN                   /*windef.h*/
#define HRSRC_win                            HRSRC                  /*windef.h*/
#define HWAVEIN_win                          HWAVEIN                    /*none*/
#define HWND_BOTTOM_win                      HWND_BOTTOM           /*winuser.h*/
#define HWND_DESKTOP_win                     HWND_DESKTOP          /*winuser.h*/
#define HWND_NOTOPMOST_win                   HWND_NOTOPMOST        /*winuser.h*/
#define HWND_TOP_win                         HWND_TOP              /*winuser.h*/
#define HWND_TOPMOST_win                     HWND_TOPMOST          /*winuser.h*/
#define HWND_win                             HWND                   /*windef.h*/
#define ICC_TAB_CLASSES_win                  ICC_TAB_CLASSES            /*none*/
#define ICC_WIN95_CLASSES_win                ICC_WIN95_CLASSES          /*none*/
#define ICON_BIG_win                         ICON_BIG              /*winuser.h*/
#define ICON_SMALL_win                       ICON_SMALL            /*winuser.h*/
#define IDC_ARROW_win                        IDC_ARROW             /*winuser.h*/
#define IDC_SIZENESW_win                     IDC_SIZENESW          /*winuser.h*/
#define IDC_SIZENS_win                       IDC_SIZENS            /*winuser.h*/
#define IDC_SIZENWSE_win                     IDC_SIZENWSE          /*winuser.h*/
#define IDC_SIZEWE_win                       IDC_SIZEWE            /*winuser.h*/
#define IDI_APPLICATION_win                  IDI_APPLICATION       /*winuser.h*/
#define IDYES_win                            IDYES                 /*winuser.h*/
#define IMAGE_ICON_win                       IMAGE_ICON            /*winuser.h*/
#define INADDR_NONE_win                      INADDR_NONE            /*ws2def.h*/
#define INIT_SECURITY_INTERFACE_A_win        INIT_SECURITY_INTERFACE_A  /*none*/
#define INITCOMMONCONTROLSEX_win             INITCOMMONCONTROLSEX       /*none*/
#define INPUT_RECORD_win                     INPUT_RECORD           /*wincon.h*/
#define INT_PTR_win                          INT_PTR               /*winbase.h*/
#define INT_win                              INT                    /*windef.h*/
#define INVALID_FILE_SIZE_win                INVALID_FILE_SIZE     /*winbase.h*/
#define INVALID_HANDLE_VALUE_win             INVALID_HANDLE_VALUE  /*winbase.h*/
#define IOC_OUT_win                          IOC_OUT              /*winsock2.h*/
#define IOCPARM_MASK_win                     IOCPARM_MASK         /*winsock2.h*/
#define ISC_REQ_ALLOCATE_MEMORY_win          ISC_REQ_ALLOCATE_MEMORY  /*sspi.h*/
#define ISC_REQ_CONFIDENTIALITY_win          ISC_REQ_CONFIDENTIALITY  /*sspi.h*/
#define ISC_REQ_REPLAY_DETECT_win            ISC_REQ_REPLAY_DETECT    /*sspi.h*/
#define ISC_REQ_SEQUENCE_DETECT_win          ISC_REQ_SEQUENCE_DETECT  /*sspi.h*/
#define ISC_REQ_STREAM_win                   ISC_REQ_STREAM           /*sspi.h*/
#define ISC_RET_EXTENDED_ERROR_win           ISC_RET_EXTENDED_ERROR   /*sspi.h*/
#define KEY_ALL_ACCESS_win                   KEY_ALL_ACCESS          /*winnt.h*/
#define KEY_ESVENT_win                       KEY_ESVENT                 /*none*/
#define KEY_EVENT_win                        KEY_EVENT              /*wincon.h*/
#define KEY_READ_win                         KEY_READ                /*winnt.h*/
#define KEY_SET_VALUE_win                    KEY_SET_VALUE           /*winnt.h*/
#define LANG_NEUTRAL_win                     LANG_NEUTRAL            /*winnt.h*/
#define LANG_USER_DEFAULT_win                LANG_USER_DEFAULT       /*winnt.h*/
#define LARGE_INTEGER_win                    LARGE_INTEGER           /*winnt.h*/
#define LCID_win                             LCID                    /*winnt.h*/
#define LF_FACESIZE_win                      LF_FACESIZE            /*wingdi.h*/
#define LMEM_FIXED_win                       LMEM_FIXED            /*winbase.h*/
#define LOBYTE_win                           LOBYTE                 /*windef.h*/
#define LOCALE_SDECIMAL_win                  LOCALE_SDECIMAL        /*winnls.h*/
#define LOCALE_SGROUPING_win                 LOCALE_SGROUPING       /*winnls.h*/
#define LOCALE_STHOUSAND_win                 LOCALE_STHOUSAND       /*winnls.h*/
#define LOCALE_USER_DEFAULT_win              LOCALE_USER_DEFAULT     /*winnt.h*/
#define LOGFONT_win                          LOGFONT                /*wingdi.h*/
#define LOGPIXELSX_win                       LOGPIXELSX             /*wingdi.h*/
#define LOGPIXELSY_win                       LOGPIXELSY             /*wingdi.h*/
#define LONG_PTR_win                         LONG_PTR              /*basetsd.h*/
#define LONG_win                             LONG                    /*winnt.h*/
#define LOWORD_win                           LOWORD                 /*windef.h*/
#define LPARAM_win                           LPARAM                 /*windef.h*/
#define LPBOOL_win                           LPBOOL                 /*windef.h*/
#define LPBYTE_win                           LPBYTE                 /*windef.h*/
#define LPCREATESTRUCT_win                   LPCREATESTRUCT        /*winuser.h*/
#define LPCTSTR_win                          LPCTSTR                 /*winnt.h*/
#define LPCVOID_win                          LPCVOID                /*windef.h*/
#define LPCWSTR_win                          LPCWSTR                 /*winnt.h*/
#define LPDLGITEMTEMPLATE_win                LPDLGITEMTEMPLATE     /*winuser.h*/
#define LPDLGTEMPLATE_win                    LPDLGTEMPLATE         /*winuser.h*/
#define LPDRAWITEMSTRUCT_win                 LPDRAWITEMSTRUCT      /*winuser.h*/
#define LPDWORD_win                          LPDWORD                /*windef.h*/
#define LPMENUITEMINFO_win                   LPMENUITEMINFO        /*winuser.h*/
#define LPMSG_win                            LPMSG                 /*winuser.h*/
#define LPNMHDR_win                          LPNMHDR               /*winuser.h*/
#define LPNMTREEVIEW_win                     LPNMTREEVIEW         /*commctrl.h*/
#define LPOLESTR_win                         LPOLESTR               /*wtypes.h*/
#define LPOVERLAPPED_win                     LPOVERLAPPED          /*winbase.h*/
#define LPPOINT_win                          LPPOINT                /*windef.h*/
#define LPPROCESS_INFORMATION_win            LPPROCESS_INFORMATION /*winbase.h*/
#define LPSECURITY_ATTRIBUTES_win            LPSECURITY_ATTRIBUTES /*winbase.h*/
#define LPSTARTUPINFO_win                    LPSTARTUPINFO         /*winbase.h*/
#define LPSTR_win                            LPSTR                   /*winnt.h*/
#define LPTSTR_win                           LPTSTR                  /*winnt.h*/
#define LPVOID_win                           LPVOID                 /*windef.h*/
#define LPWIN32_FIND_DATAW_win               LPWIN32_FIND_DATAW    /*winbase.h*/
#define LPWNDCLASSEX_win                     LPWNDCLASSEX          /*winuser.h*/
#define LPWORD_win                           LPWORD                 /*windef.h*/
#define LR_DEFAULTSIZE_win                   LR_DEFAULTSIZE        /*winuser.h*/
#define LRESULT_win                          LRESULT                /*windef.h*/
#define MAKEINTRESOURCE_win                  MAKEINTRESOURCE       /*winuser.h*/
#define MAKEINTRESOURCEA_win                 MAKEINTRESOURCEA      /*winuser.h*/
#define MAKEINTRESOURCEW_win                 MAKEINTRESOURCEW      /*winuser.h*/
#define MAKELANGID_win                       MAKELANGID              /*winnt.h*/
#define MAKEWORD_win                         MAKEWORD               /*windef.h*/
#define MAPVK_VK_TO_VSC_win                  MAPVK_VK_TO_VSC       /*winuser.h*/
#define MAX_PATH_win                         MAX_PATH               /*windef.h*/
#define MB_APPLMODAL_win                     MB_APPLMODAL          /*winuser.h*/
#define MB_DEFBUTTON1_win                    MB_DEFBUTTON1         /*winuser.h*/
#define MB_DEFBUTTON2_win                    MB_DEFBUTTON2         /*winuser.h*/
#define MB_ICONASTERISK_win                  MB_ICONASTERISK       /*winuser.h*/
#define MB_ICONERROR_win                     MB_ICONERROR          /*winuser.h*/
#define MB_ICONEXCLAMATION_win               MB_ICONEXCLAMATION    /*winuser.h*/
#define MB_ICONHAND_win                      MB_ICONHAND           /*winuser.h*/
#define MB_ICONINFORMATION_win               MB_ICONINFORMATION    /*winuser.h*/
#define MB_ICONQUESTION_win                  MB_ICONQUESTION       /*winuser.h*/
#define MB_ICONSTOP_win                      MB_ICONSTOP           /*winuser.h*/
#define MB_ICONWARNING_win                   MB_ICONWARNING        /*winuser.h*/
#define MB_OK_win                            MB_OK                 /*winuser.h*/
#define MB_TASKMODAL_win                     MB_TASKMODAL          /*winuser.h*/
#define MB_TOPMOST_win                       MB_TOPMOST            /*winuser.h*/
#define MB_YESNO_win                         MB_YESNO              /*winuser.h*/
#define MEMORYSTATUS_win                     MEMORYSTATUS          /*winbase.h*/
#define MENUITEMINFO_win                     MENUITEMINFO          /*winuser.h*/
#define MF_CHECKED_win                       MF_CHECKED            /*winuser.h*/
#define MF_POPUP_win                         MF_POPUP              /*winuser.h*/
#define MF_SEPARATOR_win                     MF_SEPARATOR          /*winuser.h*/
#define MF_STRING_win                        MF_STRING             /*winuser.h*/
#define MF_UNCHECKED_win                     MF_UNCHECKED          /*winuser.h*/
#define MFT_STRING_win                       MFT_STRING            /*winuser.h*/
#define MIIM_SUBMENU_win                     MIIM_SUBMENU          /*winuser.h*/
#define MM_ANISOTROPIC_win                   MM_ANISOTROPIC         /*wingdi.h*/
#define MM_HIENGLISH_win                     MM_HIENGLISH           /*wingdi.h*/
#define MM_HIMETRIC_win                      MM_HIMETRIC            /*wingdi.h*/
#define MM_ISOTROPIC_win                     MM_ISOTROPIC           /*wingdi.h*/
#define MM_LOENGLISH_win                     MM_LOENGLISH           /*wingdi.h*/
#define MM_LOMETRIC_win                      MM_LOMETRIC            /*wingdi.h*/
#define MM_TEXT_win                          MM_TEXT                /*wingdi.h*/
#define MM_TWIPS_win                         MM_TWIPS               /*wingdi.h*/
#define MMCKINFO_win                         MMCKINFO             /*mmsystem.h*/
#define MMIO_CREATE_win                      MMIO_CREATE          /*mmsystem.h*/
#define MMIO_CREATERIFF_win                  MMIO_CREATERIFF      /*mmsystem.h*/
#define MMIO_WRITE_win                       MMIO_WRITE           /*mmsystem.h*/
#define MMIOINFO_win                         MMIOINFO             /*mmsystem.h*/
#define MMRESULT_win                         MMRESULT             /*mmsystem.h*/
#define MMSYSERR_NOERROR_win                 MMSYSERR_NOERROR     /*mmsystem.h*/
#define MSG_win                              MSG                   /*winuser.h*/
#define NO_ERROR_win                         NO_ERROR             /*winerror.h*/
#define NULL_BRUSH_win                       NULL_BRUSH             /*wingdi.h*/
#define NULL_PEN_win                         NULL_PEN               /*wingdi.h*/
#define ODS_FOCUS_win                        ODS_FOCUS             /*winuser.h*/
#define ODS_SELECTED_win                     ODS_SELECTED          /*winuser.h*/
#define ODT_BUTTON_win                       ODT_BUTTON            /*winuser.h*/
#define OFN_DONTADDTORECENT_win              OFN_DONTADDTORECENT   /*commdlg.h*/
#define OFN_ENABLESIZING_win                 OFN_ENABLESIZING      /*commdlg.h*/
#define OFN_FILEMUSTEXIST_win                OFN_FILEMUSTEXIST     /*commdlg.h*/
#define OFN_HIDEREADONLY_win                 OFN_HIDEREADONLY      /*commdlg.h*/
#define OFN_NOVALIDATE_win                   OFN_NOVALIDATE        /*commdlg.h*/
#define OFN_OVERWRITEPROMPT_win              OFN_OVERWRITEPROMPT   /*commdlg.h*/
#define OFN_PATHMUSTEXIST_win                OFN_PATHMUSTEXIST     /*commdlg.h*/
#define OPEN_ALWAYS_win                      OPEN_ALWAYS           /*winbase.h*/
#define OPEN_EXISTING_win                    OPEN_EXISTING         /*winbase.h*/
#define OPENFILENAME_win                     OPENFILENAME          /*commdlg.h*/
#define OSVERSIONINFO_win                    OSVERSIONINFO           /*winnt.h*/
#define OSVERSIONINFOEX_win                  OSVERSIONINFOEX         /*winnt.h*/
#define OUT_DEFAULT_PRECIS_win               OUT_DEFAULT_PRECIS     /*wingdi.h*/
#define OUT_TT_ONLY_PRECIS_win               OUT_TT_ONLY_PRECIS     /*wingdi.h*/
#define PAINTSTRUCT_win                      PAINTSTRUCT           /*winuser.h*/
#define PBYTE_win                            PBYTE                  /*windef.h*/
#define PCCERT_CHAIN_CONTEXT_win             PCCERT_CHAIN_CONTEXT /*wincrypt.h*/
#define PCCERT_CONTEXT_win                   PCCERT_CONTEXT       /*wincrypt.h*/
#define PCHAR_win                            PCHAR                   /*winnt.h*/
#define PDERR_CREATEICFAILURE_win            PDERR_CREATEICFAILURE   /*cderr.h*/
#define PDERR_DEFAULTDIFFERENT_win           PDERR_DEFAULTDIFFERENT  /*cderr.h*/
#define PDERR_DNDMMISMATCH_win               PDERR_DNDMMISMATCH      /*cderr.h*/
#define PDERR_GETDEVMODEFAIL_win             PDERR_GETDEVMODEFAIL    /*cderr.h*/
#define PDERR_INITFAILURE_win                PDERR_INITFAILURE       /*cderr.h*/
#define PDERR_LOADDRVFAILURE_win             PDERR_LOADDRVFAILURE    /*cderr.h*/
#define PDERR_NODEFAULTPRN_win               PDERR_NODEFAULTPRN      /*cderr.h*/
#define PDERR_NODEVICES_win                  PDERR_NODEVICES         /*cderr.h*/
#define PDERR_PARSEFAILURE_win               PDERR_PARSEFAILURE      /*cderr.h*/
#define PDERR_PRINTERNOTFOUND_win            PDERR_PRINTERNOTFOUND   /*cderr.h*/
#define PDERR_RETDEFFAILURE_win              PDERR_RETDEFFAILURE     /*cderr.h*/
#define PDERR_SETUPFAILURE_win               PDERR_SETUPFAILURE      /*cderr.h*/
#define PLARGE_INTEGER_win                   PLARGE_INTEGER          /*winnt.h*/
#define PLONG_win                            PLONG                   /*winnt.h*/
#define POINT_win                            POINT                  /*windef.h*/
#define PRINTDLG_win                         PRINTDLG              /*commdlg.h*/
#define PROCESS_ALL_ACCESS_win               PROCESS_ALL_ACCESS      /*winnt.h*/
#define PROCESS_INFORMATION_win              PROCESS_INFORMATION   /*winbase.h*/
#define PROCESS_TERMINATE_win                PROCESS_TERMINATE     /* winnt.h */
#define PROCESS_VM_READ_win                  PROCESS_VM_READ         /*winnt.h*/
#define PROCESSENTRY32_win                   PROCESSENTRY32      /* tlhelp32.h*/
#define PROOF_QUALITY_win                    PROOF_QUALITY          /*wingdi.h*/
#define PS_SOLID_win                         PS_SOLID               /*wingdi.h*/
#define PSID_win                             PSID                    /*winnt.h*/
#define PTOKEN_USER_win                      PTOKEN_USER             /*winnt.h*/
#define PUCHAR_win                           PUCHAR                 /*windef.h*/
#define PVOID_win                            PVOID                   /*winnt.h*/
#define PWSTR_win                            PWSTR                   /*winnt.h*/
#define READ_CONTROL_win                     READ_CONTROL            /*winnt.h*/
#define RECT_win                             RECT                   /*windef.h*/
#define REG_DWORD_win                        REG_DWORD               /*winnt.h*/
#define REG_OPTION_NON_VOLATILE_win          REG_OPTION_NON_VOLATILE /*winnt.h*/
#define REG_SZ_win                           REG_SZ                  /*winnt.h*/
#define RGN_AND_win                          RGN_AND                /*wingdi.h*/
#define RGN_COPY_win                         RGN_COPY               /*wingdi.h*/
#define RPC_E_CHANGED_MODE_win               RPC_E_CHANGED_MODE   /*winerror.h*/
#define RPC_S_OK_win                         RPC_S_OK             /*rpcnterr.h*/
#define RT_HTML_win                          RT_HTML               /*winuser.h*/
#define RT_STRING_win                        RT_STRING             /*winuser.h*/
#define S_FALSE_win                          S_FALSE              /*winerror.h*/
#define S_OK_win                             S_OK                 /*winerror.h*/
#define SAFEARRAY_win                        SAFEARRAY               /*oaidl.h*/
#define SB_BOTTOM_win                        SB_BOTTOM             /*winuser.h*/
#define SB_ENDSCROLL_win                     SB_ENDSCROLL          /*winuser.h*/
#define SB_LINEDOWN_win                      SB_LINEDOWN           /*winuser.h*/
#define SB_LINEUP_win                        SB_LINEUP             /*winuser.h*/
#define SB_PAGEDOWN_win                      SB_PAGEDOWN           /*winuser.h*/
#define SB_PAGEUP_win                        SB_PAGEUP             /*winuser.h*/
#define SB_THUMBPOSITION_win                 SB_THUMBPOSITION      /*winuser.h*/
#define SB_THUMBTRACK_win                    SB_THUMBTRACK         /*winuser.h*/
#define SB_TOP_win                           SB_TOP                /*winuser.h*/
#define SB_VERT_win                          SB_VERT               /*winuser.h*/
#define SC_CLOSE_win                         SC_CLOSE              /*winuser.h*/
#define SC_HANDLE_win                        SC_HANDLE              /*winsvc.h*/
#define SC_MANAGER_ALL_ACCESS_win            SC_MANAGER_ALL_ACCESS  /*winsvc.h*/
#define SCODE_win                            SCODE                  /*wtypes.h*/
#define SCROLLINFO_win                       SCROLLINFO            /*winuser.h*/
#define SEC_CHAR_win                         SEC_CHAR                 /*sspi.h*/
#define SEC_E_INTERNAL_ERROR_win             SEC_E_INTERNAL_ERROR /*winerror.h*/
#define SEC_E_INVALID_HANDLE_win             SEC_E_INVALID_HANDLE /*winerror.h*/
#define SEC_E_INVALID_TOKEN_win              SEC_E_INVALID_TOKEN  /*winerror.h*/
#define SEC_E_NO_CREDENTIALS_win             SEC_E_NO_CREDENTIALS /*winerror.h*/
#define SEC_E_OK_win                         SEC_E_OK             /*winerror.h*/
#define SEC_FAR_win                          SEC_FAR                  /*sspi.h*/
#define SEC_I_RENEGOTIATE_win                SEC_I_RENEGOTIATE    /*winerror.h*/
#define SECBUFFER_DATA_win                   SECBUFFER_DATA           /*sspi.h*/
#define SECBUFFER_EMPTY_win                  SECBUFFER_EMPTY          /*sspi.h*/
#define SECBUFFER_EXTRA_win                  SECBUFFER_EXTRA          /*sspi.h*/
#define SECBUFFER_STREAM_HEADER_win          SECBUFFER_STREAM_HEADER  /*sspi.h*/
#define SECBUFFER_STREAM_TRAILER_win         SECBUFFER_STREAM_TRAILER /*sspi.h*/
#define SECBUFFER_TOKEN_win                  SECBUFFER_TOKEN          /*sspi.h*/
#define SECBUFFER_VERSION_win                SECBUFFER_VERSION        /*sspi.h*/
#define SECPKG_ATTR_STREAM_SIZES_win         SECPKG_ATTR_STREAM_SIZES /*sspi.h*/
#define SECPKG_CRED_OUTBOUND_win             SECPKG_CRED_OUTBOUND     /*sspi.h*/
#define SECURITY_NATIVE_DREP_win             SECURITY_NATIVE_DREP     /*sspi.h*/
#define SECURITY_STATUS_win                  SECURITY_STATUS        /*ncrypt.h*/
#define SERVICE_ACCEPT_STOP_win              SERVICE_ACCEPT_STOP    /*winsvc.h*/
#define SERVICE_ALL_ACCESS_win               SERVICE_ALL_ACCESS     /*winsvc.h*/
#define SERVICE_CONTROL_PAUSE_win            SERVICE_CONTROL_PAUSE  /*winsvc.h*/
#define SERVICE_CONTROL_STOP_win             SERVICE_CONTROL_STOP   /*winsvc.h*/
#define SERVICE_DEMAND_START_win             SERVICE_DEMAND_START    /*winnt.h*/
#define SERVICE_DESCRIPTION_win              SERVICE_DESCRIPTION    /*winsvc.h*/
#define SERVICE_ERROR_NORMAL_win             SERVICE_ERROR_NORMAL    /*winnt.h*/
#define SERVICE_PAUSED_win                   SERVICE_PAUSED         /*winsvc.h*/
#define SERVICE_RUNNING_win                  SERVICE_RUNNING        /*winsvc.h*/
#define SERVICE_START_PENDING_win            SERVICE_START_PENDING  /*winsvc.h*/
#define SERVICE_STATUS_HANDLE_win            SERVICE_STATUS_HANDLE  /*winsvc.h*/
#define SERVICE_STATUS_win                   SERVICE_STATUS         /*winsvc.h*/
#define SERVICE_STOPPED_win                  SERVICE_STOPPED        /*winsvc.h*/
#define SERVICE_TABLE_ENTRY_win              SERVICE_TABLE_ENTRY    /*winsvc.h*/
#define SERVICE_WIN32_win                    SERVICE_WIN32           /*winnt.h*/
#define SHFILEOPSTRUCT_win                   SHFILEOPSTRUCT       /*shellapi.h*/
#define SIF_PAGE_win                         SIF_PAGE              /*winuser.h*/
#define SIF_POS_win                          SIF_POS               /*winuser.h*/
#define SIF_RANGE_win                        SIF_RANGE             /*winuser.h*/
#define SIF_TRACKPOS_win                     SIF_TRACKPOS          /*winuser.h*/
#define SIZE_win                             SIZE                   /*windef.h*/
#define SM_CXICON_win                        SM_CXICON             /*winuser.h*/
#define SM_CXSCREEN_win                      SM_CXSCREEN           /*winuser.h*/
#define SM_CXVSCROLL_win                     SM_CXVSCROLL          /*winuser.h*/
#define SM_CYICON_win                        SM_CYICON             /*winuser.h*/
#define SM_CYSCREEN_win                      SM_CYSCREEN           /*winuser.h*/
#define SP_PROT_PCT1_CLIENT_win              SP_PROT_PCT1_CLIENT  /*schannel.h*/
#define SP_PROT_PCT1_win                     SP_PROT_PCT1         /*schannel.h*/
#define SP_PROT_SSL2_CLIENT_win              SP_PROT_SSL2_CLIENT  /*schannel.h*/
#define SP_PROT_SSL2_win                     SP_PROT_SSL2         /*schannel.h*/
#define SP_PROT_SSL3_CLIENT_win              SP_PROT_SSL3_CLIENT  /*schannel.h*/
#define SP_PROT_SSL3_win                     SP_PROT_SSL3         /*schannel.h*/
#define SP_PROT_TLS1_CLIENT_win              SP_PROT_TLS1_CLIENT  /*schannel.h*/
#define SP_PROT_TLS1_win                     SP_PROT_TLS1         /*schannel.h*/
#define SRCCOPY_win                          SRCCOPY                /*wingdi.h*/
#define STARTUPINFO_win                      STARTUPINFO           /*winbase.h*/
#define STD_INPUT_HANDLE_win                 STD_INPUT_HANDLE      /*winbase.h*/
#define SUBLANG_DEFAULT_win                  SUBLANG_DEFAULT         /*winnt.h*/
#define SW_HIDE_win                          SW_HIDE               /*winuser.h*/
#define SW_MAXIMIZE_win                      SW_MAXIMIZE           /*winuser.h*/
#define SW_MINIMIZE_win                      SW_MINIMIZE           /*winuser.h*/
#define SW_RESTORE_win                       SW_RESTORE            /*winuser.h*/
#define SW_SHOW_win                          SW_SHOW               /*winuser.h*/
#define SW_SHOWNA_win                        SW_SHOWNA             /*winuser.h*/
#define SWP_ASYNCWINDOWPOS_win               SWP_ASYNCWINDOWPOS    /*winuser.h*/
#define SWP_HIDEWINDOW_win                   SWP_HIDEWINDOW        /*winuser.h*/
#define SWP_NOACTIVATE_win                   SWP_NOACTIVATE        /*winuser.h*/
#define SWP_NOMOVE_win                       SWP_NOMOVE            /*winuser.h*/
#define SWP_NOOWNERZORDER_win                SWP_NOOWNERZORDER     /*winuser.h*/
#define SWP_NOSIZE_win                       SWP_NOSIZE            /*winuser.h*/
#define SWP_NOZORDER_win                     SWP_NOZORDER          /*winuser.h*/
#define SWP_SHOWWINDOW_win                   SWP_SHOWWINDOW        /*winuser.h*/
#define SYNCHRONIZE_win                      SYNCHRONIZE             /*winnt.h*/
#define SYSTEMTIME_win                       SYSTEMTIME            /*winbase.h*/
#define szOID_SGC_NETSCAPE_win               szOID_SGC_NETSCAPE   /*wincrypt.h*/
#define TCHAR_win                            TCHAR                   /*winnt.h*/
#define TCIF_TEXT_win                        TCIF_TEXT                  /*none*/
#define TCITEM_win                           TCITEM                     /*none*/
#define TCM_INSERTITEM_win                   TCM_INSERTITEM             /*none*/
#define TCN_SELCHANGE_win                    TCN_SELCHANGE        /*commctrl.h*/
#define TCS_TABS_win                         TCS_TABS             /*commctrl.h*/
#define TEXTMETRIC_win                       TEXTMETRIC             /*wingdi.h*/
#define TH32CS_SNAPALL_win                   TH32CS_SNAPALL      /* tlhelp32.h*/
#define TOKEN_QUERY_win                      TOKEN_QUERY             /*winnt.h*/
#define TRACE_win                            TRACE                      /*none*/
#define TRANSPARENT_win                      TRANSPARENT            /*wingdi.h*/
#define TRUE_win                             TRUE                   /*windef.h*/
#define TRUST_E_FAIL_win                     TRUST_E_FAIL         /*winerror.h*/
#define TVS_HASBUTTONS_win                   TVS_HASBUTTONS       /*commctrl.h*/
#define TVS_HASLINES_win                     TVS_HASLINES         /*commctrl.h*/
#define UINT_PTR_win                         UINT_PTR              /*basetsd.h*/
#define ULARGE_INTEGER_win                   ULARGE_INTEGER          /*winnt.h*/
#define ULONG_PTR_win                        ULONG_PTR             /*basetsd.h*/
#define ULONG_win                            ULONG                  /*windef.h*/
#define ULONGLONG_win                        ULONGLONG               /*winnt.h*/
#define UNISP_NAME_A_win                     UNISP_NAME_A         /*schannel.h*/
#define USAGE_MATCH_TYPE_OR_win              USAGE_MATCH_TYPE_OR  /*wincrypt.h*/
#define V_BSTR_win                           V_BSTR                /*oleauto.h*/
#define VAR_DATEVALUEONLY_win                VAR_DATEVALUEONLY     /*oleauto.h*/
#define VAR_TIMEVALUEONLY_win                VAR_TIMEVALUEONLY     /*oleauto.h*/
#define VARCMP_EQ_win                        VARCMP_EQ             /*oleauto.h*/
#define VARCMP_GT_win                        VARCMP_GT             /*oleauto.h*/
#define VARCMP_LT_win                        VARCMP_LT             /*oleauto.h*/
#define VARCMP_NULL_win                      VARCMP_NULL           /*oleauto.h*/
#define VARIANT_BOOL_win                     VARIANT_BOOL           /*wtypes.h*/
#define VARIANT_FALSE_win                    VARIANT_FALSE          /*wtypes.h*/
#define VARIANT_TRUE_win                     VARIANT_TRUE           /*wtypes.h*/
#define VARIANT_win                          VARIANT                 /*oaidl.h*/
#define VARTYPE_win                          VARTYPE                /*wtypes.h*/
#define VER_PLATFORM_WIN32_NT_win            VER_PLATFORM_WIN32_NT   /*winnt.h*/
#define VERTRES_win                          VERTRES                /*wingdi.h*/
#define VK_ADD_win                           VK_ADD                /*winuser.h*/
#define VK_APPS_win                          VK_APPS               /*winuser.h*/
#define VK_BACK_win                          VK_BACK               /*winuser.h*/
#define VK_BROWSER_BACK_win                  VK_BROWSER_BACK       /*winuser.h*/
#define VK_BROWSER_FAVORITES_win             VK_BROWSER_FAVORITES  /*winuser.h*/
#define VK_BROWSER_FORWARD_win               VK_BROWSER_FORWARD    /*winuser.h*/
#define VK_BROWSER_HOME_win                  VK_BROWSER_HOME       /*winuser.h*/
#define VK_BROWSER_REFRESH_win               VK_BROWSER_REFRESH    /*winuser.h*/
#define VK_BROWSER_SEARCH_win                VK_BROWSER_SEARCH     /*winuser.h*/
#define VK_BROWSER_STOP_win                  VK_BROWSER_STOP       /*winuser.h*/
#define VK_CONTROL_win                       VK_CONTROL            /*winuser.h*/
#define VK_DELETE_win                        VK_DELETE             /*winuser.h*/
#define VK_DIVIDE_win                        VK_DIVIDE             /*winuser.h*/
#define VK_DOWN_win                          VK_DOWN               /*winuser.h*/
#define VK_END_win                           VK_END                /*winuser.h*/
#define VK_ESCAPE_win                        VK_ESCAPE             /*winuser.h*/
#define VK_F1_win                            VK_F1                 /*winuser.h*/
#define VK_F10_win                           VK_F10                /*winuser.h*/
#define VK_F11_win                           VK_F11                /*winuser.h*/
#define VK_F12_win                           VK_F12                /*winuser.h*/
#define VK_F13_win                           VK_F13                /*winuser.h*/
#define VK_F14_win                           VK_F14                /*winuser.h*/
#define VK_F15_win                           VK_F15                /*winuser.h*/
#define VK_F16_win                           VK_F16                /*winuser.h*/
#define VK_F17_win                           VK_F17                /*winuser.h*/
#define VK_F18_win                           VK_F18                /*winuser.h*/
#define VK_F19_win                           VK_F19                /*winuser.h*/
#define VK_F2_win                            VK_F2                 /*winuser.h*/
#define VK_F20_win                           VK_F20                /*winuser.h*/
#define VK_F21_win                           VK_F21                /*winuser.h*/
#define VK_F22_win                           VK_F22                /*winuser.h*/
#define VK_F23_win                           VK_F23                /*winuser.h*/
#define VK_F24_win                           VK_F24                /*winuser.h*/
#define VK_F3_win                            VK_F3                 /*winuser.h*/
#define VK_F4_win                            VK_F4                 /*winuser.h*/
#define VK_F5_win                            VK_F5                 /*winuser.h*/
#define VK_F6_win                            VK_F6                 /*winuser.h*/
#define VK_F7_win                            VK_F7                 /*winuser.h*/
#define VK_F8_win                            VK_F8                 /*winuser.h*/
#define VK_F9_win                            VK_F9                 /*winuser.h*/
#define VK_HOME_win                          VK_HOME               /*winuser.h*/
#define VK_INSERT_win                        VK_INSERT             /*winuser.h*/
#define VK_LAUNCH_APP1_win                   VK_LAUNCH_APP1        /*winuser.h*/
#define VK_LAUNCH_APP2_win                   VK_LAUNCH_APP2        /*winuser.h*/
#define VK_LAUNCH_MAIL_win                   VK_LAUNCH_MAIL        /*winuser.h*/
#define VK_LBUTTON_win                       VK_LBUTTON            /*winuser.h*/
#define VK_LEFT_win                          VK_LEFT               /*winuser.h*/
#define VK_LSHIFT_win                        VK_LSHIFT             /*winuser.h*/
#define VK_MBUTTON_win                       VK_MBUTTON            /*winuser.h*/
#define VK_MEDIA_NEXT_TRACK_win              VK_MEDIA_NEXT_TRACK   /*winuser.h*/
#define VK_MEDIA_PLAY_PAUSE_win              VK_MEDIA_PLAY_PAUSE   /*winuser.h*/
#define VK_MEDIA_PREV_TRACK_win              VK_MEDIA_PREV_TRACK   /*winuser.h*/
#define VK_MEDIA_STOP_win                    VK_MEDIA_STOP         /*winuser.h*/
#define VK_MENU_win                          VK_MENU               /*winuser.h*/
#define VK_MULTIPLY_win                      VK_MULTIPLY           /*winuser.h*/
#define VK_NEXT_win                          VK_NEXT               /*winuser.h*/
#define VK_NUMLOCK_win                       VK_NUMLOCK            /*winuser.h*/
#define VK_OEM_4_win                         VK_OEM_4              /*winuser.h*/
#define VK_OEM_6_win                         VK_OEM_6              /*winuser.h*/
#define VK_PRIOR_win                         VK_PRIOR              /*winuser.h*/
#define VK_RBUTTON_win                       VK_RBUTTON            /*winuser.h*/
#define VK_RETURN_win                        VK_RETURN             /*winuser.h*/
#define VK_RIGHT_win                         VK_RIGHT              /*winuser.h*/
#define VK_RSHIFT_win                        VK_RSHIFT             /*winuser.h*/
#define VK_SCROLL_win                        VK_SCROLL             /*winuser.h*/
#define VK_SHIFT_win                         VK_SHIFT              /*winuser.h*/
#define VK_SPACE_win                         VK_SPACE              /*winuser.h*/
#define VK_SUBTRACT_win                      VK_SUBTRACT           /*winuser.h*/
#define VK_TAB_win                           VK_TAB                /*winuser.h*/
#define VK_UP_win                            VK_UP                 /*winuser.h*/
#define VK_VOLUME_DOWN_win                   VK_VOLUME_DOWN        /*winuser.h*/
#define VK_VOLUME_MUTE_win                   VK_VOLUME_MUTE        /*winuser.h*/
#define VK_VOLUME_UP_win                     VK_VOLUME_UP          /*winuser.h*/
#define VK_XBUTTON1_win                      VK_XBUTTON1           /*winuser.h*/
#define VK_XBUTTON2_win                      VK_XBUTTON2           /*winuser.h*/
#define VT_ARRAY_win                         VT_ARRAY               /*wtypes.h*/
#define VT_BLOB_OBJECT_win                   VT_BLOB_OBJECT         /*wtypes.h*/
#define VT_BLOB_win                          VT_BLOB                /*wtypes.h*/
#define VT_BOOL_win                          VT_BOOL                /*wtypes.h*/
#define VT_BSTR_BLOB_win                     VT_BSTR_BLOB           /*wtypes.h*/
#define VT_BSTR_win                          VT_BSTR                /*wtypes.h*/
#define VT_BYREF_win                         VT_BYREF               /*wtypes.h*/
#define VT_CARRAY_win                        VT_CARRAY              /*wtypes.h*/
#define VT_CF_win                            VT_CF                  /*wtypes.h*/
#define VT_CLSID_win                         VT_CLSID               /*wtypes.h*/
#define VT_CY_win                            VT_CY                  /*wtypes.h*/
#define VT_DATE_win                          VT_DATE                /*wtypes.h*/
#define VT_DECIMAL_win                       VT_DECIMAL             /*wtypes.h*/
#define VT_DISPATCH_win                      VT_DISPATCH            /*wtypes.h*/
#define VT_EMPTY_win                         VT_EMPTY               /*wtypes.h*/
#define VT_ERROR_win                         VT_ERROR               /*wtypes.h*/
#define VT_FILETIME_win                      VT_FILETIME            /*wtypes.h*/
#define VT_HRESULT_win                       VT_HRESULT             /*wtypes.h*/
#define VT_I1_win                            VT_I1                  /*wtypes.h*/
#define VT_I2_win                            VT_I2                  /*wtypes.h*/
#define VT_I4_win                            VT_I4                  /*wtypes.h*/
#define VT_I8_win                            VT_I8                  /*wtypes.h*/
#define VT_ILLEGAL_win                       VT_ILLEGAL             /*wtypes.h*/
#define VT_ILLEGALMASKED_win                 VT_ILLEGALMASKED       /*wtypes.h*/
#define VT_INT_PTR_win                       VT_INT_PTR             /*wtypes.h*/
#define VT_INT_win                           VT_INT                 /*wtypes.h*/
#define VT_LPSTR_win                         VT_LPSTR               /*wtypes.h*/
#define VT_LPWSTR_win                        VT_LPWSTR              /*wtypes.h*/
#define VT_NULL_win                          VT_NULL                /*wtypes.h*/
#define VT_PTR_win                           VT_PTR                 /*wtypes.h*/
#define VT_R4_win                            VT_R4                  /*wtypes.h*/
#define VT_R8_win                            VT_R8                  /*wtypes.h*/
#define VT_RECORD_win                        VT_RECORD              /*wtypes.h*/
#define VT_RESERVED_win                      VT_RESERVED            /*wtypes.h*/
#define VT_SAFEARRAY_win                     VT_SAFEARRAY           /*wtypes.h*/
#define VT_STORAGE_win                       VT_STORAGE             /*wtypes.h*/
#define VT_STORED_OBJECT_win                 VT_STORED_OBJECT       /*wtypes.h*/
#define VT_STREAM_win                        VT_STREAM              /*wtypes.h*/
#define VT_STREAMED_OBJECT_win               VT_STREAMED_OBJECT     /*wtypes.h*/
#define VT_TYPEMASK_win                      VT_TYPEMASK            /*wtypes.h*/
#define VT_UI1_win                           VT_UI1                 /*wtypes.h*/
#define VT_UI2_win                           VT_UI2                 /*wtypes.h*/
#define VT_UI4_win                           VT_UI4                 /*wtypes.h*/
#define VT_UI8_win                           VT_UI8                 /*wtypes.h*/
#define VT_UINT_PTR_win                      VT_UINT_PTR            /*wtypes.h*/
#define VT_UINT_win                          VT_UINT                /*wtypes.h*/
#define VT_UNKNOWN_win                       VT_UNKNOWN             /*wtypes.h*/
#define VT_USERDEFINED_win                   VT_USERDEFINED         /*wtypes.h*/
#define VT_VARIANT_win                       VT_VARIANT             /*wtypes.h*/
#define VT_VECTOR_win                        VT_VECTOR              /*wtypes.h*/
#define VT_VERSIONED_STREAM_win              VT_VERSIONED_STREAM    /*wtypes.h*/
#define VT_VOID_win                          VT_VOID                /*wtypes.h*/
#define W2CA_win                             W2CA                       /*none*/
#define WA_INACTIVE_win                      WA_INACTIVE           /*winuser.h*/
#define WAIT_ABANDONED_0_win                 WAIT_ABANDONED_0      /*winbase.h*/
#define WAIT_FAILED_win                      WAIT_FAILED           /*winbase.h*/
#define WAIT_OBJECT_0_win                    WAIT_OBJECT_0         /*winbase.h*/
#define WAIT_TIMEOUT_win                     WAIT_TIMEOUT         /*winerror.h*/
#define WAVE_FORMAT_1M08_win                 WAVE_FORMAT_1M08     /*mmsystem.h*/
#define WAVE_FORMAT_1M16_win                 WAVE_FORMAT_1M16     /*mmsystem.h*/
#define WAVE_FORMAT_1S08_win                 WAVE_FORMAT_1S08     /*mmsystem.h*/
#define WAVE_FORMAT_1S16_win                 WAVE_FORMAT_1S16     /*mmsystem.h*/
#define WAVE_FORMAT_2M08_win                 WAVE_FORMAT_2M08     /*mmsystem.h*/
#define WAVE_FORMAT_2M16_win                 WAVE_FORMAT_2M16     /*mmsystem.h*/
#define WAVE_FORMAT_2S08_win                 WAVE_FORMAT_2S08     /*mmsystem.h*/
#define WAVE_FORMAT_2S16_win                 WAVE_FORMAT_2S16     /*mmsystem.h*/
#define WAVE_FORMAT_4M08_win                 WAVE_FORMAT_4M08     /*mmsystem.h*/
#define WAVE_FORMAT_4M16_win                 WAVE_FORMAT_4M16     /*mmsystem.h*/
#define WAVE_FORMAT_4S08_win                 WAVE_FORMAT_4S08     /*mmsystem.h*/
#define WAVE_FORMAT_4S16_win                 WAVE_FORMAT_4S16     /*mmsystem.h*/
#define WAVE_FORMAT_96M08_win                WAVE_FORMAT_96M08    /*mmsystem.h*/
#define WAVE_FORMAT_96M16_win                WAVE_FORMAT_96M16    /*mmsystem.h*/
#define WAVE_FORMAT_96S08_win                WAVE_FORMAT_96S08    /*mmsystem.h*/
#define WAVE_FORMAT_96S16_win                WAVE_FORMAT_96S16    /*mmsystem.h*/
#define WAVE_FORMAT_PCM_win                  WAVE_FORMAT_PCM      /*mmsystem.h*/
#define WAVEFORMATEX_win                     WAVEFORMATEX         /*mmsystem.h*/
#define WAVEHDR_win                          WAVEHDR              /*mmsystem.h*/
#define WAVEINCAPS_win                       WAVEINCAPS           /*mmsystem.h*/
#define WCHAR_win                            WCHAR                   /*winnt.h*/
#define WHDR_DONE_win                        WHDR_DONE            /*mmsystem.h*/
#define WHEEL_DELTA_win                      WHEEL_DELTA           /*winuser.h*/
#define WHITE_BRUSH_win                      WHITE_BRUSH            /*wingdi.h*/
#define WIM_CLOSE_win                        WIM_CLOSE            /*mmsystem.h*/
#define WIM_DATA_win                         WIM_DATA             /*mmsystem.h*/
#define WIM_OPEN_win                         WIM_OPEN             /*mmsystem.h*/
#define WIN32_FIND_DATA_win                  WIN32_FIND_DATA       /*winbase.h*/
#define WINAPI_win                           WINAPI                 /*windef.h*/
#define WM_ACTIVATE_win                      WM_ACTIVATE           /*winuser.h*/
#define WM_ACTIVATEAPP_win                   WM_ACTIVATEAPP        /*winuser.h*/
#define WM_AFXFIRST_win                      WM_AFXFIRST           /*winuser.h*/
#define WM_AFXLAST_win                       WM_AFXLAST            /*winuser.h*/
#define WM_APP_win                           WM_APP                /*winuser.h*/
#define WM_APPCOMMAND_win                    WM_APPCOMMAND         /*winuser.h*/
#define WM_ASKCBFORMATNAME_win               WM_ASKCBFORMATNAME    /*winuser.h*/
#define WM_CANCELJOURNAL_win                 WM_CANCELJOURNAL      /*winuser.h*/
#define WM_CANCELMODE_win                    WM_CANCELMODE         /*winuser.h*/
#define WM_CAPTURECHANGED_win                WM_CAPTURECHANGED     /*winuser.h*/
#define WM_CHANGECBCHAIN_win                 WM_CHANGECBCHAIN      /*winuser.h*/
#define WM_CHANGEUISTATE_win                 WM_CHANGEUISTATE      /*winuser.h*/
#define WM_CHAR_win                          WM_CHAR               /*winuser.h*/
#define WM_CHARTOITEM_win                    WM_CHARTOITEM         /*winuser.h*/
#define WM_CHILDACTIVATE_win                 WM_CHILDACTIVATE      /*winuser.h*/
#define WM_CLEAR_win                         WM_CLEAR              /*winuser.h*/
#define WM_CLOSE_win                         WM_CLOSE              /*winuser.h*/
#define WM_COMMAND_win                       WM_COMMAND            /*winuser.h*/
#define WM_COMMNOTIFY_win                    WM_COMMNOTIFY         /*winuser.h*/
#define WM_COMPACTING_win                    WM_COMPACTING         /*winuser.h*/
#define WM_COMPAREITEM_win                   WM_COMPAREITEM        /*winuser.h*/
#define WM_CONTEXTMENU_win                   WM_CONTEXTMENU        /*winuser.h*/
#define WM_COPY_win                          WM_COPY               /*winuser.h*/
#define WM_COPYDATA_win                      WM_COPYDATA           /*winuser.h*/
#define WM_CREATE_win                        WM_CREATE             /*winuser.h*/
#define WM_CTLCOLORBTN_win                   WM_CTLCOLORBTN        /*winuser.h*/
#define WM_CTLCOLORDLG_win                   WM_CTLCOLORDLG        /*winuser.h*/
#define WM_CTLCOLOREDIT_win                  WM_CTLCOLOREDIT       /*winuser.h*/
#define WM_CTLCOLORLISTBOX_win               WM_CTLCOLORLISTBOX    /*winuser.h*/
#define WM_CTLCOLORMSGBOX_win                WM_CTLCOLORMSGBOX     /*winuser.h*/
#define WM_CTLCOLORSCROLLBAR_win             WM_CTLCOLORSCROLLBAR  /*winuser.h*/
#define WM_CTLCOLORSTATIC_win                WM_CTLCOLORSTATIC     /*winuser.h*/
#define WM_CUT_win                           WM_CUT                /*winuser.h*/
#define WM_DEADCHAR_win                      WM_DEADCHAR           /*winuser.h*/
#define WM_DELETEITEM_win                    WM_DELETEITEM         /*winuser.h*/
#define WM_DESTROY_win                       WM_DESTROY            /*winuser.h*/
#define WM_DESTROYCLIPBOARD_win              WM_DESTROYCLIPBOARD   /*winuser.h*/
#define WM_DEVICECHANGE_win                  WM_DEVICECHANGE       /*winuser.h*/
#define WM_DEVMODECHANGE_win                 WM_DEVMODECHANGE      /*winuser.h*/
#define WM_DISPLAYCHANGE_win                 WM_DISPLAYCHANGE      /*winuser.h*/
#define WM_DRAWCLIPBOARD_win                 WM_DRAWCLIPBOARD      /*winuser.h*/
#define WM_DRAWITEM_win                      WM_DRAWITEM           /*winuser.h*/
#define WM_DROPFILES_win                     WM_DROPFILES          /*winuser.h*/
#define WM_ENABLE_win                        WM_ENABLE             /*winuser.h*/
#define WM_ENDSESSION_win                    WM_ENDSESSION         /*winuser.h*/
#define WM_ENTERIDLE_win                     WM_ENTERIDLE          /*winuser.h*/
#define WM_ENTERMENULOOP_win                 WM_ENTERMENULOOP      /*winuser.h*/
#define WM_ENTERSIZEMOVE_win                 WM_ENTERSIZEMOVE      /*winuser.h*/
#define WM_ERASEBKGND_win                    WM_ERASEBKGND         /*winuser.h*/
#define WM_EXITMENULOOP_win                  WM_EXITMENULOOP       /*winuser.h*/
#define WM_EXITSIZEMOVE_win                  WM_EXITSIZEMOVE       /*winuser.h*/
#define WM_FONTCHANGE_win                    WM_FONTCHANGE         /*winuser.h*/
#define WM_GETDLGCODE_win                    WM_GETDLGCODE         /*winuser.h*/
#define WM_GETFONT_win                       WM_GETFONT            /*winuser.h*/
#define WM_GETHOTKEY_win                     WM_GETHOTKEY          /*winuser.h*/
#define WM_GETICON_win                       WM_GETICON            /*winuser.h*/
#define WM_GETMINMAXINFO_win                 WM_GETMINMAXINFO      /*winuser.h*/
#define WM_GETOBJECT_win                     WM_GETOBJECT          /*winuser.h*/
#define WM_GETTEXT_win                       WM_GETTEXT            /*winuser.h*/
#define WM_GETTEXTLENGTH_win                 WM_GETTEXTLENGTH      /*winuser.h*/
#define WM_HANDHELDFIRST_win                 WM_HANDHELDFIRST      /*winuser.h*/
#define WM_HANDHELDLAST_win                  WM_HANDHELDLAST       /*winuser.h*/
#define WM_HELP_win                          WM_HELP               /*winuser.h*/
#define WM_HOTKEY_win                        WM_HOTKEY             /*winuser.h*/
#define WM_HSCROLL_win                       WM_HSCROLL            /*winuser.h*/
#define WM_HSCROLLCLIPBOARD_win              WM_HSCROLLCLIPBOARD   /*winuser.h*/
#define WM_ICONERASEBKGND_win                WM_ICONERASEBKGND     /*winuser.h*/
#define WM_IME_CHAR_win                      WM_IME_CHAR           /*winuser.h*/
#define WM_IME_COMPOSITION_win               WM_IME_COMPOSITION    /*winuser.h*/
#define WM_IME_CONTROL_win                   WM_IME_CONTROL        /*winuser.h*/
#define WM_IME_ENDCOMPOSITION_win            WM_IME_ENDCOMPOSITION /*winuser.h*/
#define WM_IME_KEYDOWN_win                   WM_IME_KEYDOWN        /*winuser.h*/
#define WM_IME_KEYUP_win                     WM_IME_KEYUP          /*winuser.h*/
#define WM_IME_NOTIFY_win                    WM_IME_NOTIFY         /*winuser.h*/
#define WM_IME_REQUEST_win                   WM_IME_REQUEST        /*winuser.h*/
#define WM_IME_SELECT_win                    WM_IME_SELECT         /*winuser.h*/
#define WM_IME_SETCONTEXT_win                WM_IME_SETCONTEXT     /*winuser.h*/
#define WM_INITDIALOG_win                    WM_INITDIALOG         /*winuser.h*/
#define WM_INITMENU_win                      WM_INITMENU           /*winuser.h*/
#define WM_INITMENUPOPUP_win                 WM_INITMENUPOPUP      /*winuser.h*/
#define WM_INPUT_win                         WM_INPUT              /*winuser.h*/
#define WM_INPUTLANGCHANGE_win               WM_INPUTLANGCHANGE    /*winuser.h*/
#define WM_KEYDOWN_win                       WM_KEYDOWN            /*winuser.h*/
#define WM_KEYUP_win                         WM_KEYUP              /*winuser.h*/
#define WM_KILLFOCUS_win                     WM_KILLFOCUS          /*winuser.h*/
#define WM_LBUTTONDBLCLK_win                 WM_LBUTTONDBLCLK      /*winuser.h*/
#define WM_LBUTTONDOWN_win                   WM_LBUTTONDOWN        /*winuser.h*/
#define WM_LBUTTONUP_win                     WM_LBUTTONUP          /*winuser.h*/
#define WM_MBUTTONDBLCLK_win                 WM_MBUTTONDBLCLK      /*winuser.h*/
#define WM_MBUTTONDOWN_win                   WM_MBUTTONDOWN        /*winuser.h*/
#define WM_MBUTTONUP_win                     WM_MBUTTONUP          /*winuser.h*/
#define WM_MDIACTIVATE_win                   WM_MDIACTIVATE        /*winuser.h*/
#define WM_MDICASCADE_win                    WM_MDICASCADE         /*winuser.h*/
#define WM_MDICREATE_win                     WM_MDICREATE          /*winuser.h*/
#define WM_MDIDESTROY_win                    WM_MDIDESTROY         /*winuser.h*/
#define WM_MDIGETACTIVE_win                  WM_MDIGETACTIVE       /*winuser.h*/
#define WM_MDIICONARRANGE_win                WM_MDIICONARRANGE     /*winuser.h*/
#define WM_MDIMAXIMIZE_win                   WM_MDIMAXIMIZE        /*winuser.h*/
#define WM_MDINEXT_win                       WM_MDINEXT            /*winuser.h*/
#define WM_MDIREFRESHMENU_win                WM_MDIREFRESHMENU     /*winuser.h*/
#define WM_MDIRESTORE_win                    WM_MDIRESTORE         /*winuser.h*/
#define WM_MDISETMENU_win                    WM_MDISETMENU         /*winuser.h*/
#define WM_MDITILE_win                       WM_MDITILE            /*winuser.h*/
#define WM_MEASUREITEM_win                   WM_MEASUREITEM        /*winuser.h*/
#define WM_MENUCHAR_win                      WM_MENUCHAR           /*winuser.h*/
#define WM_MENUCOMMAND_win                   WM_MENUCOMMAND        /*winuser.h*/
#define WM_MENUDRAG_win                      WM_MENUDRAG           /*winuser.h*/
#define WM_MENUGETOBJECT_win                 WM_MENUGETOBJECT      /*winuser.h*/
#define WM_MENURBUTTONUP_win                 WM_MENURBUTTONUP      /*winuser.h*/
#define WM_MENUSELECT_win                    WM_MENUSELECT         /*winuser.h*/
#define WM_MOUSEACTIVATE_win                 WM_MOUSEACTIVATE      /*winuser.h*/
#define WM_MOUSEHOVER_win                    WM_MOUSEHOVER         /*winuser.h*/
#define WM_MOUSELEAVE_win                    WM_MOUSELEAVE         /*winuser.h*/
#define WM_MOUSEMOVE_win                     WM_MOUSEMOVE          /*winuser.h*/
#define WM_MOUSEWHEEL_win                    WM_MOUSEWHEEL         /*winuser.h*/
#define WM_MOVE_win                          WM_MOVE               /*winuser.h*/
#define WM_MOVING_win                        WM_MOVING             /*winuser.h*/
#define WM_NCACTIVATE_win                    WM_NCACTIVATE         /*winuser.h*/
#define WM_NCCALCSIZE_win                    WM_NCCALCSIZE         /*winuser.h*/
#define WM_NCCREATE_win                      WM_NCCREATE           /*winuser.h*/
#define WM_NCDESTROY_win                     WM_NCDESTROY          /*winuser.h*/
#define WM_NCHITTEST_win                     WM_NCHITTEST          /*winuser.h*/
#define WM_NCLBUTTONDBLCLK_win               WM_NCLBUTTONDBLCLK    /*winuser.h*/
#define WM_NCLBUTTONDOWN_win                 WM_NCLBUTTONDOWN      /*winuser.h*/
#define WM_NCLBUTTONUP_win                   WM_NCLBUTTONUP        /*winuser.h*/
#define WM_NCMBUTTONDBLCLK_win               WM_NCMBUTTONDBLCLK    /*winuser.h*/
#define WM_NCMBUTTONDOWN_win                 WM_NCMBUTTONDOWN      /*winuser.h*/
#define WM_NCMBUTTONUP_win                   WM_NCMBUTTONUP        /*winuser.h*/
#define WM_NCMOUSEHOVER_win                  WM_NCMOUSEHOVER       /*winuser.h*/
#define WM_NCMOUSELEAVE_win                  WM_NCMOUSELEAVE       /*winuser.h*/
#define WM_NCMOUSEMOVE_win                   WM_NCMOUSEMOVE        /*winuser.h*/
#define WM_NCPAINT_win                       WM_NCPAINT            /*winuser.h*/
#define WM_NCRBUTTONDBLCLK_win               WM_NCRBUTTONDBLCLK    /*winuser.h*/
#define WM_NCRBUTTONDOWN_win                 WM_NCRBUTTONDOWN      /*winuser.h*/
#define WM_NCRBUTTONUP_win                   WM_NCRBUTTONUP        /*winuser.h*/
#define WM_NCXBUTTONDBLCLK_win               WM_NCXBUTTONDBLCLK    /*winuser.h*/
#define WM_NCXBUTTONDOWN_win                 WM_NCXBUTTONDOWN      /*winuser.h*/
#define WM_NCXBUTTONUP_win                   WM_NCXBUTTONUP        /*winuser.h*/
#define WM_NEXTDLGCTL_win                    WM_NEXTDLGCTL         /*winuser.h*/
#define WM_NEXTMENU_win                      WM_NEXTMENU           /*winuser.h*/
#define WM_NOTIFY_win                        WM_NOTIFY             /*winuser.h*/
#define WM_NOTIFYFORMAT_win                  WM_NOTIFYFORMAT       /*winuser.h*/
#define WM_NULL_win                          WM_NULL               /*winuser.h*/
#define WM_PAINT_win                         WM_PAINT              /*winuser.h*/
#define WM_PAINTCLIPBOARD_win                WM_PAINTCLIPBOARD     /*winuser.h*/
#define WM_PAINTICON_win                     WM_PAINTICON          /*winuser.h*/
#define WM_PALETTECHANGED_win                WM_PALETTECHANGED     /*winuser.h*/
#define WM_PALETTEISCHANGING_win             WM_PALETTEISCHANGING  /*winuser.h*/
#define WM_PARENTNOTIFY_win                  WM_PARENTNOTIFY       /*winuser.h*/
#define WM_PASTE_win                         WM_PASTE              /*winuser.h*/
#define WM_PENWINFIRST_win                   WM_PENWINFIRST        /*winuser.h*/
#define WM_PENWINLAST_win                    WM_PENWINLAST         /*winuser.h*/
#define WM_POWER_win                         WM_POWER              /*winuser.h*/
#define WM_POWERBROADCAST_win                WM_POWERBROADCAST     /*winuser.h*/
#define WM_PRINT_win                         WM_PRINT              /*winuser.h*/
#define WM_PRINTCLIENT_win                   WM_PRINTCLIENT        /*winuser.h*/
#define WM_QUERYDRAGICON_win                 WM_QUERYDRAGICON      /*winuser.h*/
#define WM_QUERYENDSESSION_win               WM_QUERYENDSESSION    /*winuser.h*/
#define WM_QUERYNEWPALETTE_win               WM_QUERYNEWPALETTE    /*winuser.h*/
#define WM_QUERYOPEN_win                     WM_QUERYOPEN          /*winuser.h*/
#define WM_QUERYUISTATE_win                  WM_QUERYUISTATE       /*winuser.h*/
#define WM_QUEUESYNC_win                     WM_QUEUESYNC          /*winuser.h*/
#define WM_QUIT_win                          WM_QUIT               /*winuser.h*/
#define WM_RBUTTONDBLCLK_win                 WM_RBUTTONDBLCLK      /*winuser.h*/
#define WM_RBUTTONDOWN_win                   WM_RBUTTONDOWN        /*winuser.h*/
#define WM_RBUTTONUP_win                     WM_RBUTTONUP          /*winuser.h*/
#define WM_RENDERALLFORMATS_win              WM_RENDERALLFORMATS   /*winuser.h*/
#define WM_RENDERFORMAT_win                  WM_RENDERFORMAT       /*winuser.h*/
#define WM_SETCURSOR_win                     WM_SETCURSOR          /*winuser.h*/
#define WM_SETFOCUS_win                      WM_SETFOCUS           /*winuser.h*/
#define WM_SETFONT_win                       WM_SETFONT            /*winuser.h*/
#define WM_SETHOTKEY_win                     WM_SETHOTKEY          /*winuser.h*/
#define WM_SETICON_win                       WM_SETICON            /*winuser.h*/
#define WM_SETREDRAW_win                     WM_SETREDRAW          /*winuser.h*/
#define WM_SETTEXT_win                       WM_SETTEXT            /*winuser.h*/
#define WM_SETTINGCHANGE_win                 WM_SETTINGCHANGE      /*winuser.h*/
#define WM_SHOWWINDOW_win                    WM_SHOWWINDOW         /*winuser.h*/
#define WM_SIZE_win                          WM_SIZE               /*winuser.h*/
#define WM_SIZECLIPBOARD_win                 WM_SIZECLIPBOARD      /*winuser.h*/
#define WM_SIZING_win                        WM_SIZING             /*winuser.h*/
#define WM_SOCKET_DEAD_win                   WM_SOCKET_DEAD        /*winuser.h*/
#define WM_SOCKET_NOTIFY_win                 WM_SOCKET_NOTIFY      /*winuser.h*/
#define WM_SPOOLERSTATUS_win                 WM_SPOOLERSTATUS      /*winuser.h*/
#define WM_STYLECHANGED_win                  WM_STYLECHANGED       /*winuser.h*/
#define WM_STYLECHANGING_win                 WM_STYLECHANGING      /*winuser.h*/
#define WM_SYNCPAINT_win                     WM_SYNCPAINT          /*winuser.h*/
#define WM_SYSCHAR_win                       WM_SYSCHAR            /*winuser.h*/
#define WM_SYSCOLORCHANGE_win                WM_SYSCOLORCHANGE     /*winuser.h*/
#define WM_SYSCOMMAND_win                    WM_SYSCOMMAND         /*winuser.h*/
#define WM_SYSDEADCHAR_win                   WM_SYSDEADCHAR        /*winuser.h*/
#define WM_SYSKEYDOWN_win                    WM_SYSKEYDOWN         /*winuser.h*/
#define WM_SYSKEYUP_win                      WM_SYSKEYUP           /*winuser.h*/
#define WM_TABLET_FIRST_win                  WM_TABLET_FIRST       /*winuser.h*/
#define WM_TABLET_LAST_win                   WM_TABLET_LAST        /*winuser.h*/
#define WM_TCARD_win                         WM_TCARD              /*winuser.h*/
#define WM_THEMECHANGED_win                  WM_THEMECHANGED       /*winuser.h*/
#define WM_TIMECHANGE_win                    WM_TIMECHANGE         /*winuser.h*/
#define WM_TIMER_win                         WM_TIMER              /*winuser.h*/
#define WM_UNDO_win                          WM_UNDO               /*winuser.h*/
#define WM_UNICHAR_win                       WM_UNICHAR            /*winuser.h*/
#define WM_UNINITMENUPOPUP_win               WM_UNINITMENUPOPUP    /*winuser.h*/
#define WM_UPDATEUISTATE_win                 WM_UPDATEUISTATE      /*winuser.h*/
#define WM_USER_win                          WM_USER               /*winuser.h*/
#define WM_USERCHANGED_win                   WM_USERCHANGED        /*winuser.h*/
#define WM_VKEYTOITEM_win                    WM_VKEYTOITEM         /*winuser.h*/
#define WM_VSCROLL_win                       WM_VSCROLL            /*winuser.h*/
#define WM_VSCROLLCLIPBOARD_win              WM_VSCROLLCLIPBOARD   /*winuser.h*/
#define WM_WINDOWPOSCHANGED_win              WM_WINDOWPOSCHANGED   /*winuser.h*/
#define WM_WINDOWPOSCHANGING_win             WM_WINDOWPOSCHANGING  /*winuser.h*/
#define WM_WININICHANGE_win                  WM_WININICHANGE       /*winuser.h*/
#define WM_WTSSESSION_CHANGE_win             WM_WTSSESSION_CHANGE  /*winuser.h*/
#define WM_XBUTTONDBLCLK_win                 WM_XBUTTONDBLCLK      /*winuser.h*/
#define WM_XBUTTONDOWN_win                   WM_XBUTTONDOWN        /*winuser.h*/
#define WM_XBUTTONUP_win                     WM_XBUTTONUP          /*winuser.h*/
#define WNDCLASSEX_win                       WNDCLASSEX            /*winuser.h*/
#define WNDENUMPROC_win                      WNDENUMPROC           /*winuser.h*/
#define WNDPROC_win                          WNDPROC               /*winuser.h*/
#define WORD_win                             WORD                   /*windef.h*/
#define WPARAM_win                           WPARAM                 /*windef.h*/
#define WS_BORDER_win                        WS_BORDER             /*winuser.h*/
#define WS_CAPTION_win                       WS_CAPTION            /*winuser.h*/
#define WS_CHILD_win                         WS_CHILD              /*winuser.h*/
#define WS_CLIPCHILDREN_win                  WS_CLIPCHILDREN       /*winuser.h*/
#define WS_CLIPSIBLINGS_win                  WS_CLIPSIBLINGS       /*winuser.h*/
#define WS_DISABLED_win                      WS_DISABLED           /*winuser.h*/
#define WS_DLGFRAME_win                      WS_DLGFRAME           /*winuser.h*/
#define WS_EX_ACCEPTFILES_win                WS_EX_ACCEPTFILES     /*winuser.h*/
#define WS_EX_APPWINDOW_win                  WS_EX_APPWINDOW       /*winuser.h*/
#define WS_EX_CLIENTEDGE_win                 WS_EX_CLIENTEDGE      /*winuser.h*/
#define WS_EX_CONTEXTHELP_win                WS_EX_CONTEXTHELP     /*winuser.h*/
#define WS_EX_CONTROLPARENT_win              WS_EX_CONTROLPARENT   /*winuser.h*/
#define WS_EX_DLGMODALFRAME_win              WS_EX_DLGMODALFRAME   /*winuser.h*/
#define WS_EX_LEFT_win                       WS_EX_LEFT            /*winuser.h*/
#define WS_EX_LEFTSCROLLBAR_win              WS_EX_LEFTSCROLLBAR   /*winuser.h*/
#define WS_EX_LTRREADING_win                 WS_EX_LTRREADING      /*winuser.h*/
#define WS_EX_MDICHILD_win                   WS_EX_MDICHILD        /*winuser.h*/
#define WS_EX_NOPARENTNOTIFY_win             WS_EX_NOPARENTNOTIFY  /*winuser.h*/
#define WS_EX_PALETTEWINDOW_win              WS_EX_PALETTEWINDOW   /*winuser.h*/
#define WS_EX_RIGHT_win                      WS_EX_RIGHT           /*winuser.h*/
#define WS_EX_RIGHTSCROLLBAR_win             WS_EX_RIGHTSCROLLBAR  /*winuser.h*/
#define WS_EX_RTLREADING_win                 WS_EX_RTLREADING      /*winuser.h*/
#define WS_EX_STATICEDGE_win                 WS_EX_STATICEDGE      /*winuser.h*/
#define WS_EX_TOOLWINDOW_win                 WS_EX_TOOLWINDOW      /*winuser.h*/
#define WS_EX_TOPMOST_win                    WS_EX_TOPMOST         /*winuser.h*/
#define WS_EX_TRANSPARENT_win                WS_EX_TRANSPARENT     /*winuser.h*/
#define WS_EX_WINDOWEDGE_win                 WS_EX_WINDOWEDGE      /*winuser.h*/
#define WS_GROUP_win                         WS_GROUP              /*winuser.h*/
#define WS_HSCROLL_win                       WS_HSCROLL            /*winuser.h*/
#define WS_MAXIMIZE_win                      WS_MAXIMIZE           /*winuser.h*/
#define WS_MAXIMIZEBOX_win                   WS_MAXIMIZEBOX        /*winuser.h*/
#define WS_MINIMIZE_win                      WS_MINIMIZE           /*winuser.h*/
#define WS_MINIMIZEBOX_win                   WS_MINIMIZEBOX        /*winuser.h*/
#define WS_OVERLAPPED_win                    WS_OVERLAPPED         /*winuser.h*/
#define WS_OVERLAPPEDWINDOW_win              WS_OVERLAPPEDWINDOW   /*winuser.h*/
#define WS_POPUP_win                         WS_POPUP              /*winuser.h*/
#define WS_POPUPWINDOW_win                   WS_POPUPWINDOW        /*winuser.h*/
#define WS_SYSMENU_win                       WS_SYSMENU            /*winuser.h*/
#define WS_TABSTOP_win                       WS_TABSTOP            /*winuser.h*/
#define WS_THICKFRAME_win                    WS_THICKFRAME         /*winuser.h*/
#define WS_VISIBLE_win                       WS_VISIBLE            /*winuser.h*/
#define WS_VSCROLL_win                       WS_VSCROLL            /*winuser.h*/
#define X509_ASN_ENCODING_win                X509_ASN_ENCODING    /*wincrypt.h*/

#define COINIT_DISABLE_OLE1DDE_win \
    COINIT_DISABLE_OLE1DDE                                         /*objbase.h*/

#define COINIT_MULTITHREADED_win \
    COINIT_MULTITHREADED                                           /*objbase.h*/

#define COINIT_SPEED_OVER_MEMORY_win \
    COINIT_SPEED_OVER_MEMORY                                       /*objbase.h*/

#define ERROR_INSUFFICIENT_BUFFER_win \
    ERROR_INSUFFICIENT_BUFFER                                     /*winerror.h*/

#define EVENTLOG_INFORMATION_TYPE_win \
    EVENTLOG_INFORMATION_TYPE                                        /*winnt.h*/

#define FORMAT_MESSAGE_FROM_SYSTEM_win \
    FORMAT_MESSAGE_FROM_SYSTEM                                     /*winbase.h*/

#define FORMAT_MESSAGE_IGNORE_INSERTS_win \
    FORMAT_MESSAGE_IGNORE_INSERTS                                  /*winbase.h*/

#define HKEY_PERFORMANCE_NLSTEXT_win \
    HKEY_PERFORMANCE_NLSTEXT                                        /*winreg.h*/

#define INVALID_SET_FILE_POINTER_win \
    INVALID_SET_FILE_POINTER                                       /*winbase.h*/

#define LPTHREAD_START_ROUTINE_win \
    LPTHREAD_START_ROUTINE                                         /*winbase.h*/

#define PROCESS_QUERY_INFORMATION_win \
    PROCESS_QUERY_INFORMATION                                        /*winnt.h*/

#define SCH_CRED_MANUAL_CRED_VALIDATION_win \
    SCH_CRED_MANUAL_CRED_VALIDATION                                     /*none*/

#define SEC_E_BUFFER_TOO_SMALL_win \
    SEC_E_BUFFER_TOO_SMALL                                        /*winerror.h*/

#define SEC_E_CRYPTO_SYSTEM_INVALID_win \
    SEC_E_CRYPTO_SYSTEM_INVALID                                   /*winerror.h*/

#define SEC_E_DECRYPT_FAILURE_win \
    SEC_E_DECRYPT_FAILURE                                         /*winerror.h*/

#define SEC_E_ENCRYPT_FAILURE_win \
    SEC_E_ENCRYPT_FAILURE                                         /*winerror.h*/

#define SEC_E_INCOMPLETE_MESSAGE_win \
    SEC_E_INCOMPLETE_MESSAGE                                      /*winerror.h*/

#define SEC_E_INSUFFICIENT_MEMORY_win \
    SEC_E_INSUFFICIENT_MEMORY                                     /*winerror.h*/

#define SEC_E_MESSAGE_ALTERED_win \
    SEC_E_MESSAGE_ALTERED                                         /*winerror.h*/

#define SEC_E_OUT_OF_SEQUENCE_win \
    SEC_E_OUT_OF_SEQUENCE                                         /*winerror.h*/

#define SEC_E_QOP_NOT_SUPPORTED_win \
    SEC_E_QOP_NOT_SUPPORTED                                       /*winerror.h*/

#define SEC_E_WRONG_PRINCIPAL_win \
    SEC_E_WRONG_PRINCIPAL                                         /*winerror.h*/

#define SEC_I_CONTEXT_EXPIRED_win \
    SEC_I_CONTEXT_EXPIRED                                         /*winerror.h*/

#define SEC_I_CONTINUE_NEEDED_win \
    SEC_I_CONTINUE_NEEDED                                         /*winerror.h*/

#define SECPKG_ATTR_CONNECTION_INFO_win \
    SECPKG_ATTR_CONNECTION_INFO                                   /*schannel.h*/

#define SECPKG_ATTR_ISSUER_LIST_EX_win \
    SECPKG_ATTR_ISSUER_LIST_EX                                    /*schannel.h*/

#define SERVICE_ACCEPT_PAUSE_CONTINUE_win \
    SERVICE_ACCEPT_PAUSE_CONTINUE                                   /*winsvc.h*/

#define SERVICE_CONFIG_DESCRIPTION_win \
    SERVICE_CONFIG_DESCRIPTION                                      /*winsvc.h*/

#define SERVICE_CONTROL_CONTINUE_win \
    SERVICE_CONTROL_CONTINUE                                        /*winsvc.h*/

#define SERVICE_CONTROL_INTERROGATE_win \
    SERVICE_CONTROL_INTERROGATE                                     /*winsvc.h*/

#define SERVICE_INTERACTIVE_PROCESS_win \
    SERVICE_INTERACTIVE_PROCESS                                      /*winnt.h*/

#define SERVICE_WIN32_OWN_PROCESS_win \
    SERVICE_WIN32_OWN_PROCESS                                        /*winnt.h*/

#define szOID_PKIX_KP_CLIENT_AUTH_win \
    szOID_PKIX_KP_CLIENT_AUTH                                     /*wincrypt.h*/

#define szOID_PKIX_KP_SERVER_AUTH_win \
    szOID_PKIX_KP_SERVER_AUTH                                     /*wincrypt.h*/

#define szOID_SERVER_GATED_CRYPTO_win \
    szOID_SERVER_GATED_CRYPTO                                     /*wincrypt.h*/

#define VER_PLATFORM_WIN32_WINDOWS_win \
    VER_PLATFORM_WIN32_WINDOWS                                       /*winnt.h*/

#define VK_LAUNCH_MEDIA_SELECT_win \
    VK_LAUNCH_MEDIA_SELECT                                         /*winuser.h*/

#define WM_IME_COMPOSITIONFULL_win \
    WM_IME_COMPOSITIONFULL                                         /*winuser.h*/

#define WM_IME_STARTCOMPOSITION_win \
    WM_IME_STARTCOMPOSITION                                        /*winuser.h*/

#define WM_INPUTLANGCHANGEREQUEST_win \
    WM_INPUTLANGCHANGEREQUEST                                      /*winuser.h*/

#define WS_EX_OVERLAPPEDWINDOW_win \
    WS_EX_OVERLAPPEDWINDOW                                         /*winuser.h*/

#define SCH_CRED_NO_DEFAULT_CREDS_win      SCH_CRED_NO_DEFAULT_CREDS    /*none*/
#define SCHANNEL_CRED_VERSION_win          SCHANNEL_CRED_VERSION        /*none*/
#define SCHANNEL_CRED_win                  SCHANNEL_CRED                /*none*/
#define SCHANNEL_SHUTDOWN_win              SCHANNEL_SHUTDOWN            /*none*/

/* -------------------------------------------------------------------------- */
#if defined __GNUC__ || defined __MINGW32__

/* Definitions: Re-definitions to avoid GCC Warnings */

/* -------------------------------------------------------------------------- */
/* windef.h                                                                   */

#undef  LOWORD_win
#define LOWORD_win( DWORD_VAL_ )                                \
    LX_CAST(WORD, LX_CAST(DWORD_PTR, DWORD_VAL_) & 0xFFFF)  /*#*/

#undef  HIWORD_win
#define HIWORD_win( DWORD_VAL_ )                             \
    LX_CAST(WORD, LX_CAST(DWORD_PTR, DWORD_VAL_) >> 16)  /*#*/

/* -------------------------------------------------------------------------- */
/* wtypes.h                                                                   */

#undef  VARIANT_FALSE_win
#define VARIANT_FALSE_win               LX_CAST(VARIANT_BOOL, 0)
#undef  VARIANT_TRUE_win
#define VARIANT_TRUE_win                LX_CAST(VARIANT_BOOL, -1)

/* -------------------------------------------------------------------------- */
/* winbase.h                                                                  */

#undef  INVALID_FILE_SIZE_win
#define INVALID_FILE_SIZE_win           LX_CAST(DWORD, 0xFFFFFFFFL)

#undef  INVALID_HANDLE_VALUE_win
#define INVALID_HANDLE_VALUE_win        LX_CAST(HANDLE, LX_CAST(LONG_PTR, -1))

#undef  INVALID_SET_FILE_POINTER_win
#define INVALID_SET_FILE_POINTER_win    LX_CAST(DWORD, -1)

#undef  WAIT_ABANDONED_0_win
#define WAIT_ABANDONED_0_win            LX_CAST(DWORD, 0x00000080L)

#undef  WAIT_FAILED_win
#define WAIT_FAILED_win                 LX_CAST(DWORD, 0xFFFFFFFFL)

#undef  WAIT_OBJECT_0_win
#define WAIT_OBJECT_0_win               LX_CAST(DWORD, 0x00000000L)

/* -------------------------------------------------------------------------- */
/* WinGDI.h                                                                   */

#undef  HGDI_ERROR_win
#define HGDI_ERROR_win                  LX_CAST(HANDLE, 0xFFFFFFFF)

/* -------------------------------------------------------------------------- */
/* winuser.h                                                                  */

#undef  HWND_BOTTOM_win
#define HWND_BOTTOM_win                 LX_CAST(HWND, 1)

#undef  HWND_NOTOPMOST_win
#define HWND_NOTOPMOST_win              LX_CAST(HWND, -2)

#undef  HWND_TOP_win
#define HWND_TOP_win                    LX_CAST(HWND, 0)

#undef  HWND_TOPMOST_win
#define HWND_TOPMOST_win                LX_CAST(HWND, -1)

#undef  MAKEINTRESOURCEA_win
#define MAKEINTRESOURCEA_win( ID_ )                             \
    LX_CAST(LPSTR, LX_CAST(ULONG_PTR, LX_CAST(WORD, ID_)))  /*#*/

#undef  MAKEINTRESOURCEW_win
#define MAKEINTRESOURCEW_win( ID_ )                              \
    LX_CAST(LPWSTR, LX_CAST(ULONG_PTR, LX_CAST(WORD, ID_)))  /*#*/

#undef  MAKEINTRESOURCE_win
#if defined UNICODE
#define MAKEINTRESOURCE_win     MAKEINTRESOURCEW_win
#else
#define MAKEINTRESOURCE_win     MAKEINTRESOURCEA_win
#endif

/* predefined resource types */

#undef  RT_STRING_win
#define RT_STRING_win                   MAKEINTRESOURCE_win(6)

#undef  RT_HTML_win
#define RT_HTML_win                     MAKEINTRESOURCE_win(23)

/* standard cursor id */

#undef  IDC_ARROW_win
#define IDC_ARROW_win                   MAKEINTRESOURCE_win(32512)

#undef  IDC_SIZENESW_win
#define IDC_SIZENESW_win                MAKEINTRESOURCE_win(32643)

#undef  IDC_SIZENS_win
#define IDC_SIZENS_win                  MAKEINTRESOURCE_win(32645)

#undef  IDC_SIZENWSE_win
#define IDC_SIZENWSE_win                MAKEINTRESOURCE_win(32642)

#undef  IDC_SIZEWE_win
#define IDC_SIZEWE_win                  MAKEINTRESOURCE_win(32644)

/* standard icon IDs */

#undef  BS_TYPEMASK_win
#define BS_TYPEMASK_win                 0x0000000FL

#undef  IDI_APPLICATION_win
#define IDI_APPLICATION_win             MAKEINTRESOURCE_win(32512)

/* -------------------------------------------------------------------------- */
/* WinError.h                                                                 */

#undef  DISP_E_BADVARTYPE_win
#define DISP_E_BADVARTYPE_win           0x80020008UL

#undef  DISP_E_OVERFLOW_win
#define DISP_E_OVERFLOW_win             0x8002000AUL

#undef  DISP_E_TYPEMISMATCH_win
#define DISP_E_TYPEMISMATCH_win         0x80020005UL

#undef  E_INVALIDARG_win
#define E_INVALIDARG_win                0x80070057UL

#undef  E_OUTOFMEMORY_win
#define E_OUTOFMEMORY_win               0x8007000EUL

#undef  FAILED_win
#define FAILED_win(HRESULT_)            LX_CAST(HRESULT, (HRESULT_) < 0)

#undef  S_FALSE_win
#define S_FALSE_win                     LX_CAST(HRESULT, 1)

#undef  S_OK_win
#define S_OK_win                        LX_CAST(HRESULT, 0)

/* mouse */

#undef  GET_WHEEL_DELTA_WPARAM_win
#define GET_WHEEL_DELTA_WPARAM_win( WPARAM_ )  \
    LX_CAST(short, HIWORD_win(WPARAM_))    /*#*/

/* -------------------------------------------------------------------------- */
/* winnt.h                                                                    */

#undef  MAKELANGID_win
#define MAKELANGID_win( P_, S_ )                         \
    ((LX_CAST(WORD, S_) << 10) | LX_CAST(WORD, P_))  /***/

#undef  LANG_USER_DEFAULT_win
#define LANG_USER_DEFAULT_win                          \
    MAKELANGID_win(LANG_NEUTRAL, SUBLANG_DEFAULT)  /***/

/* -------------------------------------------------------------------------- */
/* winreg.h                                                                   */

#undef  HKEY_CLASSES_ROOT_win
#define HKEY_CLASSES_ROOT_win                          \
    LX_CAST(HKEY, LX_CAST(ULONG_PTR, 0x80000000))  /***/

#undef  HKEY_CURRENT_USER_win
#define HKEY_CURRENT_USER_win                          \
    LX_CAST(HKEY, LX_CAST(ULONG_PTR, 0x80000001))  /*#*/

#undef  HKEY_LOCAL_MACHINE_win
#define HKEY_LOCAL_MACHINE_win                         \
    LX_CAST(HKEY, LX_CAST(ULONG_PTR, 0x80000002))  /*#*/

#undef  HKEY_PERFORMANCE_DATA_win
#define HKEY_PERFORMANCE_DATA_win                      \
    LX_CAST(HKEY, LX_CAST(ULONG_PTR, 0x80000004))  /*#*/

#undef  HKEY_PERFORMANCE_NLSTEXT_win
#define HKEY_PERFORMANCE_NLSTEXT_win                   \
    LX_CAST(HKEY, LX_CAST(ULONG_PTR, 0x80000060))  /*#*/

#undef  HKEY_PERFORMANCE_TEXT_win
#define HKEY_PERFORMANCE_TEXT_win                      \
    LX_CAST(HKEY, LX_CAST(ULONG_PTR, 0x80000050))  /*#*/

#undef  HKEY_USERS_win
#define HKEY_USERS_win                                 \
    LX_CAST(HKEY, LX_CAST(ULONG_PTR, 0x80000003))  /*#*/

#if defined WINVER && WINVER >= 0x0400
#undef  HKEY_CURRENT_CONFIG_win
#define HKEY_CURRENT_CONFIG_win                        \
    LX_CAST(HKEY, LX_CAST(ULONG_PTR, 0x80000005))  /*#*/

#undef  HKEY_DYN_DATA_win
#define HKEY_DYN_DATA_win                              \
    LX_CAST(HKEY, LX_CAST(ULONG_PTR, 0x80000006))  /*#*/
#endif                                                    /* WINVER >= 0x0400 */

#endif                                             /* __GNUC__ || __MINGW32__ */

/* -------------------------------------------------------------------------- */

#if defined __cplusplus
namespace lx_c {
#endif

/* -------------------------------------------------------------------------- */
/* Functions: Windows-Specific                                                */

#if !defined lx_chars_t
#if defined UNICODE || defined _UNICODE
#define lx_chars_t      const wchar_t*
#define lx_new_chars_t  wchar_t*
#else                                                  /* UNICODE || _UNICODE */
#define lx_chars_t      const char*
#define lx_new_chars_t  char*
#endif                                               /* !UNICODE && !_UNICODE */
#endif                                                        /* !lx_chars_t  */

LX_PUBLIC lx_chars_t  lx_map_mode_name_win( const UINT_win  map_mode_ );   /*F*/

LX_PUBLIC int  lx_message_loop_win( void );                                /*F*/

LX_PUBLIC lx_chars_t  lx_message_name_win(                                 /*F*/
    const UINT_win  message_code_ );                                       /*-*/

LX_PUBLIC void  lx_post_quit_message_to_thread_win(                        /*F*/
    const DWORD_win  thread_id_ );                                         /*-*/

LX_PUBLIC lx_new_chars_t  lx_resource_html_win(                            /*F*/
    const UINT_win       resource_id_,                                     /*-*/
    const HINSTANCE_win  instance_ );                                      /*-*/

LX_PUBLIC lx_new_chars_t  lx_resource_text_win(                            /*F*/
    const UINT_win       resource_id_,                                     /*-*/
    const HINSTANCE_win  instance_ );                                      /*-*/

LX_PUBLIC lx_new_chars_t  lx_window_text_win( const HWND_win  window_ );   /*F*/

/* -------------------------------------------------------------------------- */

#if defined __cplusplus
} /* namespace lx_c */
#endif

#endif                                                                   /*eof*/
