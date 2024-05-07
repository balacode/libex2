/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                [libex_win_registry.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_win_registry_.h"
#include "libex_config_.h"
#if defined INCLUDED_LIBEX_WIN_REGISTRY_H && PLATFORM_WIN32

#include "libex_.h"
#include "libex_call_.h"
#include "libex_const_.h"
#include "libex_logging_.h"
#include "libex_macro_.h"
#include "libex_stringc_.h"
#include "libex_system_.h"
#include "libex_type_.h"

#if PLATFORM_WIN32
#include "libex_win32_.h"
#endif

#if defined __cplusplus_cli
#pragma unmanaged
#endif


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


static chars_t  _ROOT_KEY_STRINGS[7] = {
    _T("HKEY_CLASSES_ROOT"),
    _T("HKEY_CURRENT_CONFIG"),
    _T("HKEY_CURRENT_USER"),
    _T("HKEY_DYN_DATA"),
    _T("HKEY_LOCAL_MACHINE"),
    _T("HKEY_PERFORMANCE_DATA"),
    _T("HKEY_USERS")
};

static const HKEY_win  _ROOT_KEY_HANDLES[7] = {

    HKEY_CLASSES_ROOT_win,
    HKEY_CURRENT_CONFIG_win,
    HKEY_CURRENT_USER_win,
    HKEY_DYN_DATA_win,
    HKEY_LOCAL_MACHINE_win,
    HKEY_PERFORMANCE_DATA_win,
    HKEY_USERS_win
};


/* -------------------------------------------------------------------------- */


PUBLIC HKEY_win  registry_extract_key( chars_t  key_ ) {                   /*F*/
    GO                                                            (UID(F12CA9));
    size_t    i   = 0;
    HKEY_win  ret = NULL;

    VERIFY(STRLEN_T(key_) > 0, UID(E28393));

    for (i = 0; i < 7; i++) {
        if (begins3T(key_, _ROOT_KEY_STRINGS[i], IGNORE_CASE)) {
            ret = _ROOT_KEY_HANDLES[i];
            break;
        }
    }

    if (ret == NULL) {
        new_chars_t  err = formatT(_T("invalid key: %s"), key_);
        ERR(err, UID(E4A14C));
        freeT(&err);
    }
    RETURN(ret);
} /* registry_extract_key */


/* returns the subkey value from the specified registry key string            */
PUBLIC new_chars_t  registry_extract_subkey( chars_t  key_ ) {             /*F*/
    GO                                                            (UID(F6E9BF));
    size_t  i   = 0;
    size_t  pos = NONE;

    for (i = 0; i < 7; i++) {
        if (begins3T(key_, _ROOT_KEY_STRINGS[i], IGNORE_CASE)) {
            pos = STRLEN_T(_ROOT_KEY_STRINGS[i]);
            break;
        }
    }

    if (pos == NONE) {
        new_chars_t  ret = CAST(char_t*, BLANK);
        new_chars_t  err = formatT(_T("invalid key: '%s'"), key_);
        ERR(err, UID(EE099B));
        freeT(&err);
        RETURN(ret);
    }

    {
        new_chars_t  ret = T_chars(key_ + pos + 1);
        RETURN(ret);
    }
} /* registry_extract_subkey */


/* returns True if the specified key and value name exists in the registry    */
PUBLIC bool  registry_value_exists(                                        /*F*/
    chars_t  key_,                                                         /*-*/
    chars_t  value_name_ ) {                                               /*-*/
    GO                                                            (UID(F317DF));
#define BUF_SIZE  64

    CHAR         buf[BUF_SIZE];
    HKEY_win     top_key = NULL;
    HKEY_win     key     = NULL;
    new_chars_t  subkey  = NULL;
    int          result  = 0;
    bool         ret     = false;

    if (STRLEN_T(key_) == 0) {
        WARN(_T("key_ is blank."), UID(E20F48));
        RETURN(false);
    }

    top_key = registry_extract_key(key_);
    subkey  = registry_extract_subkey(key_);

    /* attempt to open the specified registry key */
    result = RegOpenKeyEx_win(top_key, subkey, 0, KEY_READ_win, &key);
    if (ERROR_FILE_NOT_FOUND_win == result) {
        ret = true;
    }

    /* attempt to read the specified registry value */
    if (result == ERROR_SUCCESS_win) {
        DWORD_win  buf_size = BUF_SIZE;
        result = RegQueryValueEx_win(key,
                                     value_name_,
                                     0,
                                     0,
                                     CAST(LPBYTE_win, buf),
                                     &buf_size);

#undef BUF_SIZE

        switch (result) {
                CASE(ERROR_SUCCESS_win,        ret = true);
                CASE(ERROR_MORE_DATA_win,      ret = true);
                CASE(ERROR_FILE_NOT_FOUND_win, ret = false);
            default:
                result = CAST(int, NONE);
        }
    }

    if (result == CAST(int, NONE)) {
        new_chars_t  source = formatT(_T("registry_value_exists(")
                                      _T("key_='%s', value_name_='%s')"),
                                      key_, value_name_);

        new_chars_t  notes = formatT(_T("result == %d"), result);
        log_error(system_error_name(result), source, __LINE__, notes);

        freeT(&source);
        freeT(&notes);
        ret = false;
    }

    freeT(&subkey);
    RETURN(ret);
} /* registry_value_exists */


/* -------------------------------------------------------------------------- */
/* purpose: reads a string value from the named registry key and value name   */
/*                                                                            */
/* details: use registry_value_exists()                                       */
/*          to test for existence of the key and value name,                  */
/*          because this function logs an error if the key is not found       */
/*                                                                            */
/* params.: key_ - string specifying the registry key to be opened, it should */
/*                 begin with one of the following:                           */
/*                 HKEY_CLASSES_ROOT,                                         */
/*                 HKEY_CURRENT_CONFIG,                                       */
/*                 HKEY_CURRENT_USER,                                         */
/*                 HKEY_DYN_DATA,                                             */
/*                 HKEY_LOCAL_MACHINE,                                        */
/*                 HKEY_PERFORMANCE_DATA,                                     */
/*                 HKEY_USERS                                                 */
/*                                                                            */
/*          value_name_ - name of registry value to enquire                   */
/*                                                                            */
/* returns: the stored string value, or zero-length string if value not found */
/*                                                                            */
/* example: registry_get_text(                                                */
/*   _T("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion"),  */
/*   _T("Version"))                                                           */
/* -------------------------------------------------------------------------- */
PUBLIC new_chars_t  registry_get_text(                                     /*F*/
    chars_t  key_,                                                         /*-*/
    chars_t  value_name_ ) {                                               /*-*/
    GO                                                            (UID(F76B2B));
    if (STRLEN_T(key_) == 0) {
        new_chars_t  ret = CAST(new_chars_t, BLANK);
        WARN(_T("key_ is blank."), UID(EC709B));
        RETURN(ret);
    } else {
        HKEY_win     top_key  = NULL;
        HKEY_win     key      = NULL;
        new_chars_t  subkey   = NULL;
        DWORD_win    buf_size = 0;
        int          err_line = 0;
        int          result   = 0;

#define BUF_SIZE  1024

        /* prepare a buffer for reading the result */
        char_t  buf[BUF_SIZE];  /* don't use CHAR! */
        CLEAR_N(buf, BUF_SIZE);

        /* split registry key and subkey */
        LINE;
        top_key = registry_extract_key(key_);
        subkey  = registry_extract_subkey(key_);

        /* open the specified registry location */
        LINE;
        result = RegOpenKeyEx_win(top_key, subkey, 0, KEY_READ_win, &key);
        if (result == ERROR_SUCCESS_win) {
            /* read the specified registry value */
            buf_size = BUF_SIZE;

#undef BUF_SIZE

            result = RegQueryValueEx_win(key, value_name_, 0, 0,
                                         CAST(LPBYTE_win, buf),
                                         &buf_size);

            LINE;
            if (result == ERROR_SUCCESS_win ||
                result == ERROR_FILE_NOT_FOUND_win) {
                /* replace character 0 with space */
                size_t  pos = buf_size - 1;
                while (--pos) {
                    if (buf[pos] == '\0' && buf[pos - 1] != '\0') {
                        buf[pos] = ' ';
                    }
                }
            }
        }

        freeT(&subkey);

        if (ERROR_SUCCESS_win != result && ERROR_FILE_NOT_FOUND_win != result) {
            new_chars_t  str  = T_int(result);
            new_chars_t  note = formatT(_T("\r\n") _T(" key_ = '%s'")
                                        _T("\r\n") _T(" value_name_ = '%s'")
                                        _T("\r\n") _T(" returned '%s'"),
                                        key_, value_name_, str);

            log_warn(system_error_name(result), FN_NAME, err_line, note);

            freeT(&str);
            freeT(&note);
        }

        {
            /* return the registry value as a text object */
            new_chars_t  ret = T_chars_n(buf, buf_size);
            trim_in_T(ret);
            RETURN(ret);
        }
    }
} /* registry_get_text */


PUBLIC bool  registry_set_text(                                            /*F*/
    chars_t  key_,                                                         /*-*/
    chars_t  value_name_,                                                  /*-*/
    chars_t  value_ ) {                                                    /*-*/
    GO                                                            (UID(F51715));
    if (STRLEN_T(key_) == 0) {
        WARN(_T("key_ is blank."), UID(EDC20D));
        RETURN(0);
    } else {
        const HKEY_win  key        = registry_extract_key(key_);
        new_chars_t     subkey     = registry_extract_subkey(key_);
        const size_t    bytes_size = STRLEN_T(value_) * sizeof(char_t);
        HKEY_win        result_key = NULL;
        DWORD_win       disp       = 0;
        LONG_win        result     = 0;
        chars_t         err_name   = NULL;
        bool            ret        = false;

        result = RegCreateKeyEx_win(key, subkey, 0, 0,
                                    REG_OPTION_NON_VOLATILE_win,
                                    KEY_SET_VALUE_win, NULL,
                                    &result_key, &disp);

        if (result == ERROR_SUCCESS_win) {
            result = RegSetValueEx_win(
                         result_key, value_name_, 0, REG_SZ_win,
                         CAST(const BYTE_win*, value_),
                         CAST(DWORD_win, bytes_size));

            if (result == ERROR_SUCCESS_win) {
                ret = true;
            } else {
                err_name = system_error_name(result);
            }
        } else {
            err_name = system_error_name(result);
        }

        freeT(&subkey);
        RETURN(ret);
    }
} /* registry_set_text */


/* purpose: reads a DWORD value from the named registry key and value name    */
/* details: use registry_value_exists() to check if key/value exists          */
/*          name, because this function logs an error if key is not found     */
/* default: default_ = UINT_MAX                                               */
/* returns: the stored DWORD_win  value                                       */
/* example: registry_get_dword(                                               */
/*     "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion",        */
/*     "SetupFlags")                                                          */
PUBLIC DWORD_win  registry_get_dword(                                      /*F*/
    chars_t          key_,                                                 /*-*/
    chars_t          value_name_,                                          /*-*/
    const DWORD_win  default_ ) {                                          /*-*/
    GO                                                            (UID(F3723E));
    if (STRLEN_T(key_) == 0) {
        WARN(_T("key_ is blank."), UID(E31804));
        RETURN(0);
    } else {
        /* split registry key and subkey */
        HKEY_win     top_key = registry_extract_key(key_);
        new_chars_t  subkey  = registry_extract_subkey(key_);
        HKEY_win     key     = NULL;
        DWORD_win    type    = 0;
        DWORD_win    ret     = 0;

        /* open the specified registry location */
        if (ERROR_SUCCESS_win != RegOpenKeyEx_win(
                top_key, subkey, 0, KEY_READ_win, &key)) {

            if (default_ == UINT_MAX) {
                WARN(_T("RegOpenKeyEx() failed"), UID(E0D3E2));
                RETURN(0);
            } else {
                RETURN(default_);
            }
        }

        {
            /* read the specified registry value */
            DWORD_win  size   = sizeof(DWORD_win);
            LONG_win   result = RegQueryValueEx_win(
                                    key, value_name_, 0, &type,
                                    CAST(uint8_t*, &ret), &size);

            if (ERROR_SUCCESS_win != result &&
                ERROR_FILE_NOT_FOUND_win != result) {

                if (default_ == UINT_MAX) {
                    WARN(_T("RegQueryValueEx() failed"), UID(E7E95F));
                    ret = 0;
                    goto _ret;
                } else {
                    ret = default_;
                    goto _ret;
                }
            }
        }

        /* raise an error if the registry value is not a DWORD_win */
        if (type != REG_DWORD_win) {
            if (default_ == UINT_MAX) {
                WARN(_T("RegQueryValueEx() returned wrong datatype"),
                     UID(EA8EDF));
                ret = 0;
                goto _ret;
            } else {
                ret = default_;
                goto _ret;
            }
        }
_ret:
        freeT(&subkey);
        RETURN(ret);
    }
} /* registry_get_dword */


/* purpose: sets a DWORD value in the named registry key and value name       */
PUBLIC bool  registry_set_dword(                                           /*F*/
    chars_t          key_,                                                 /*-*/
    chars_t          value_name_,                                          /*-*/
    const DWORD_win  value_ ) {                                            /*-*/
    GO                                                            (UID(F17535));
    const size_t  key_len = STRLEN_T(key_);

    if (key_len == 0) {
        WARN(_T("key_ is blank."), UID(E348BF));
        RETURN(false);

    } else {
        HKEY_win     key        = registry_extract_key(key_);
        new_chars_t  subkey     = registry_extract_subkey(key_);
        HKEY_win     result_key = NULL;
        DWORD_win    disp       = 0;
        bool         ret        = false;

        if (ERROR_SUCCESS_win == RegCreateKeyEx_win(
                key, subkey, 0, 0,
                REG_OPTION_NON_VOLATILE_win, KEY_SET_VALUE_win,
                NULL, &result_key, &disp)) {

            if (ERROR_SUCCESS_win == RegSetValueEx_win(
                    result_key, value_name_, 0, REG_DWORD_win,
                    CAST(uint8_t*, &value_), sizeof(DWORD_win))) {
                ret = true;
            }
        }

        freeT(&subkey);
        RETURN(ret);
    }
} /* registry_set_dword */


PUBLIC bool  registry_delete_value(                                        /*F*/
    chars_t  key_,                                                         /*-*/
    chars_t  value_name_ ) {                                               /*-*/
    GO                                                            (UID(F47836));
    const HKEY_win  key        = registry_extract_key(key_);
    new_chars_t     subkey     = registry_extract_subkey(key_);
    HKEY_win        result_key = NULL;
    DWORD_win       disp       = 0;

    VERIFY(STRLEN_T(key_) > 0, UID(EFFE98));

    if (RegCreateKeyEx_win(key, subkey, 0, 0,
                           REG_OPTION_NON_VOLATILE_win, KEY_SET_VALUE_win,
                           NULL, &result_key, &disp)   == ERROR_SUCCESS_win
        && RegDeleteValue_win(result_key, value_name_) == ERROR_SUCCESS_win) {
        RETURN(true);
    }
    RETURN(false);
} /* registry_delete_value */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
