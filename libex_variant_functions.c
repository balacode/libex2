/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                           [libex_variant_functions.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_variant_functions_.h"
#if defined INCLUDED_LIBEX_VARIANT_FUNCTIONS_H

#include "libex_config_.h"

#include "libex_.h"
#include "libex_call_.h"
#include "libex_logging_.h"
#include "libex_macro_.h"
#include "libex_string_class_.h"
#include "libex_stringc_.h"
#include "libex_system_.h"
#include "libex_type_.h"

#if PLATFORM_WIN32
#include "libex_win32_.h"
#endif

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#define _CONVERT_VARIANT( TYPE_, NULL_VAL_, SRC_UID_ )                         \
    VARIANT_win  vnt;                                                          \
    HRESULT_win  result;                                                       \
    if (value_.vt == VT_NULL_win || value_.vt == VT_EMPTY_win)                 \
    {       RETURN(NULL_VAL_); }                                               \
    CLEAR(vnt);                                                                \
    result = VariantChangeType_win(&vnt,                                       \
                                   CAST(VARIANT_win*, &value_), 0, TYPE_);     \
    if (S_OK_win != result) {                                                  \
        _report_conversion_error(result, value_.vt, SRC_UID_);                 \
        RETURN(NULL_VAL_);                                                     \
    }                                                                      /*#*/

#define _SET_VARIANT( TYPE_, MEMBER_, VALUE_ )   \
    VARIANT_win  vnt;                            \
    MEMSET(&vnt, 0x00, sizeof(vnt));             \
    vnt.vt = TYPE_;                              \
    vnt.MEMBER_ = VALUE_                     /*#*/


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


/* -------------------------------------------------------------------------- */
/* Functions: Helper                                                          */


static void  _report_conversion_error(                                     /*F*/
    const HRESULT_win  call_result_,                                       /*-*/
    const VARTYPE_win  var_type_,                                          /*-*/
    const uint32_t     src_uid_ ) {                                        /*-*/
    GO                                                            (UID(F06CDF));
    char_t*  msg  = MALLOC(64 * sizeof(char_t));
    char_t*  code = _T("UNKNOWN_CODE");
    char_t*  str  = NULL;

    switch (call_result_) {
            CASE_TO_TEXT(DISP_E_BADVARTYPE_win,   code);
            CASE_TO_TEXT(DISP_E_OVERFLOW_win,     code);
            CASE_TO_TEXT(DISP_E_TYPEMISMATCH_win, code);
            CASE_TO_TEXT(E_INVALIDARG_win,        code);
            CASE_TO_TEXT(E_OUTOFMEMORY_win,       code);
    }

    STRCAT_S_T(msg, 64, code);
    STRCAT_S_T(msg, 64, _T(" vt = "));
    str = msg + STRLEN_T(msg);
    ULTOA_T(var_type_, str, 16, 10);
    WARN(msg, src_uid_);
    freeT(&msg);

    RETURN(NIL);
} /* _report_conversion_error */


/* -------------------------------------------------------------------------- */
/* Functions: Conversion from Variant                                         */


PUBLIC new_chars_t  T_of_var( const VARIANT_win  value_ ) {                /*F*/
    GO                                                            (UID(FFAE70));
    new_chars_t  ret = NULL;

    if (value_.vt == VT_NULL_win || value_.vt == VT_EMPTY_win) {
        ret = NULL;

    } else if (value_.vt == VT_BSTR_win) {
        ret = T_bstr(value_.bstrVal);

    } else {
        VARIANT_win  vnt;
        HRESULT_win  result;

        CLEAR(vnt);
        result = VariantChangeType_win(
                     &vnt, CAST(VARIANT_win*, &value_), 0, VT_BSTR_win);

        OS_VERIFY(result == S_OK_win, UID(ECE721));

        if (result == S_OK_win) {
            ret = T_bstr(vnt.bstrVal);
            RETURN(ret);
        }

        OS_VERIFY(VariantClear_win(&vnt) == S_OK_win, UID(EA1B29));
    }
    RETURN(ret);
} /* T_of_var */


PUBLIC new_str_t  S_of_var( const VARIANT_win  value_ ) {                  /*F*/
    GO                                                            (UID(FA092B));
    new_chars_t  chars = T_of_var(value_);
    RETURN(S_newT(chars));
} /* S_of_var */


PUBLIC bool  bool_of_var( const VARIANT_win  value_ ) {                    /*F*/
    GO                                                            (UID(FE3942));
    _CONVERT_VARIANT(VT_BOOL_win, false, UID(E96420));
    RETURN(!(vnt.boolVal == 0));
} /* bool_of_var */


PUBLIC uint8_t  byte_of_var( const VARIANT_win  value_ ) {                 /*F*/
    GO                                                            (UID(F33666));
    _CONVERT_VARIANT(VT_UI1_win, 0, UID(E66409));
    RETURN(vnt.bVal);
} /* byte_of_var */


PUBLIC int16_t  short_of_var( const VARIANT_win  value_ ) {                /*F*/
    GO                                                            (UID(FDC555));
    _CONVERT_VARIANT(VT_I2_win, 0, UID(EED08A));
    RETURN(vnt.iVal);
} /* short_of_var */


PUBLIC long  long_of_var( const VARIANT_win  value_ ) {                    /*F*/
    GO                                                            (UID(F85F68));
    _CONVERT_VARIANT(VT_I4_win, 0, UID(EB7BFF));
    RETURN(vnt.lVal);
} /* long_of_var */


PUBLIC float  float_of_var( const VARIANT_win  value_ ) {                  /*F*/
    GO                                                            (UID(F6BC99));
    _CONVERT_VARIANT(VT_R4_win, 0, UID(E70C7C));
    RETURN(vnt.fltVal);
} /* float_of_var */


PUBLIC double  double_of_var( const VARIANT_win  value_ ) {                /*F*/
    GO                                                            (UID(F6257F));
    if (value_.vt == VT_NULL_win || value_.vt == VT_EMPTY_win) {
        RETURN(0);

    } else if (value_.vt == VT_BSTR_win) {
        new_chars_t   str = T_of_var(value_);
        const double  ret = ATOF_T(str);
        freeT(&str);
        RETURN(ret);
    } else {
        _CONVERT_VARIANT(VT_R8_win, 0, UID(E5C658));
        RETURN(vnt.dblVal);
    }
} /* double_of_var */


PUBLIC CURRENCY_win  currency_of_var( const VARIANT_win  value_ ) {        /*F*/
    GO                                                            (UID(FA1A2F));
    CURRENCY_win  zero;
    zero.Hi = 0;
    zero.Lo = 0;

    {
        _CONVERT_VARIANT(VT_CY_win, zero, UID(EDDC0F));
        RETURN(vnt.cyVal);
    }
} /* currency_of_var */


PUBLIC DATE_win  date_of_var( const VARIANT_win  value_ ) {                /*F*/
    GO                                                            (UID(FA30CD));
    _CONVERT_VARIANT(VT_DATE_win, 0, UID(E1404D));
    RETURN(vnt.date);
} /* date_of_var */


/* -------------------------------------------------------------------------- */
/* Functions: Conversion to Variant                                           */


PUBLIC VARIANT_win  var_of_bool( const bool  value_ ) {                    /*F*/
    GO                                                            (UID(F64271));
    _SET_VARIANT(VT_BOOL_win, boolVal, value_ ? 0xFFFF : 0);
    RETURN(vnt);
} /* var_of_bool */


PUBLIC VARIANT_win  var_of_byte( const uint8_t  value_ ) {                 /*F*/
    GO                                                            (UID(FA68AE));
    _SET_VARIANT(VT_UI1_win, bVal, value_);
    RETURN(vnt);
} /* var_of_byte */


PUBLIC VARIANT_win  var_of_short( const short  value_ ) {                  /*F*/
    GO                                                            (UID(FBCB16));
    _SET_VARIANT(VT_I2_win, iVal, value_);
    RETURN(vnt);
} /* var_of_short */


PUBLIC VARIANT_win  var_of_long( const long  value_ ) {                    /*F*/
    GO                                                            (UID(F6BA90));
    _SET_VARIANT(VT_I4_win, lVal, value_);
    RETURN(vnt);
} /* var_of_long */


PUBLIC VARIANT_win  var_of_float( const float  value_ ) {                  /*F*/
    GO                                                            (UID(F7330C));
    _SET_VARIANT(VT_R4_win, fltVal, value_);
    RETURN(vnt);
} /* var_of_float */


PUBLIC VARIANT_win  var_of_double( const double  value_ ) {                /*F*/
    GO                                                            (UID(F48901));
    _SET_VARIANT(VT_R8_win, dblVal, value_);
    RETURN(vnt);
} /* var_of_double */


PUBLIC VARIANT_win  var_of_currency( const CURRENCY_win  value_ ) {        /*F*/
    GO                                                            (UID(F1ABD4));
    _SET_VARIANT(VT_CY_win, cyVal, value_);
    RETURN(vnt);
} /* var_of_currency */


PUBLIC VARIANT_win  var_of_date( const DATE_win  value_ ) {                /*F*/
    GO                                                            (UID(F3B046));
    _SET_VARIANT(VT_DATE_win, date, value_);
    RETURN(vnt);
} /* var_of_date */


PUBLIC VARIANT_win  var_of_chars( chars_t  value_ ) {                      /*F*/
    GO                                                            (UID(F84327));
    VARIANT_win  ret;
    CLEAR(ret);
    ret.vt      = VT_BSTR_win;
    ret.bstrVal = bstr_of_T(value_);
    RETURN(ret);
} /* var_of_chars */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
