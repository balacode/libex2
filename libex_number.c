/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                      [libex_number.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_number_.h"
#if defined INCLUDED_LIBEX_NUMBER_H

#include <limits.h>
#include <stdio.h>   /* for printf()  sprintf*() */
#include <string.h>  /* for memset()             */

#include  "libex_config_.h"
#include "libex_.h"
#include "libex_call_.h"
#include "libex_const_.h"
#include "libex_debug_.h"
#include "libex_error_.h"
#include "libex_macro_.h"
#include "libex_string_class_.h"
#include "libex_stringc_.h"
#include "libex_type_.h"

#if PLATFORM_WIN32
#include "libex_win32_.h"
#endif

#if NUMBER_TESTS > 0
#include "libex_test.h"
#endif

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#if defined(_MSC_VER)
#pragma warning (disable:4710)  /* W:L4 function not inlined                  */
#endif

#if defined __GNUC__ && !defined __MINGW32__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#endif

#define DECIMAL_MARK  '.'

/* -------------------------------------------------------------------------- */
NAMESPACE(c_)

static int  _test_no = 0;


/* -------------------------------------------------------------------------- */
/* Functions: Private                                                         */


static bool  _eval_subexpressions_in_brackets( str_t*  expression_ ) {     /*F*/
    GO                                                            (UID(F17F1E));
    int      nesting = 0;
    size_t   pos     = 0;
    size_t   bracket = 0;
    chars_t  rd      = expression_->cs;

    while (*rd) {
        if (*rd == '(') {
            if (nesting++ == 0) {
                bracket = pos;
            }

        } else if (*rd == ')' && --nesting == 0) {
            new_str_t  sub_expr =
                S_substr(*expression_, bracket + 1, pos - bracket - 1);

            new_str_t  result = num_eval(sub_expr.cs);

            removeInS(expression_, bracket, pos - bracket + 1);
            insert3InS(expression_, result.cs, bracket);
            freeS(&sub_expr);
            freeS(&result);
        }

        pos++;
        rd++;
    }

    {
        const bool  ret = (nesting == 0);
        RETURN(ret);
    }
} /* _eval_subexpressions_in_brackets */


static new_str_t  _eval_get_system_decimal_separator( void ) {             /*F*/
    GO                                                            (UID(FD1E72));
    new_str_t  ret = { NULL };

#if PLATFORM_LINUX
    IMPLEMENT_LINUX();  /* TODO: Lx. _eval_get_system_decimal_separator() */
#endif

#if PLATFORM_WIN32
    GetLocaleInfo_win(
        LOCALE_USER_DEFAULT_win,
        LOCALE_SDECIMAL_win,
        getEmptyBufferS(&ret, 8), 8);

    closeBufferS(&ret);
#endif                                                      /* PLATFORM_WIN32 */

    RETURN(ret);
} /* _eval_get_system_decimal_separator */


static new_str_t  _eval_get_system_number_group_separator( void ) {        /*F*/
    GO                                                            (UID(F78F41));
    /* determine character(s) used to separate groups */
    /* of digits to the left of the decimal           */

    new_str_t  ret = { NULL };

#if PLATFORM_LINUX
    IMPLEMENT_LINUX();  /* TODO: Linux ..._system_number_group_separator() */
#endif

#if PLATFORM_WIN32
    GetLocaleInfo_win(
        LOCALE_USER_DEFAULT_win,
        LOCALE_STHOUSAND_win,
        getEmptyBufferS(&ret, 8), 8);

    closeBufferS(&ret);
#endif                                                      /* PLATFORM_WIN32 */
    RETURN(ret);
} /* _eval_get_system_number_group_separator */


typedef struct  _operand_t {
    chars_t     text;                                           /* _operand_t */
    /*          string from which operand was read */

    bool        is_negative;                                    /* _operand_t */
    /*          true if the number is negative */

    bool        is_fract;                                       /* _operand_t */
    /*          true if the number has a decimal mark */

    chars_t     first;                                          /* _operand_t */
    /*          rightmost digit from which reading begins */

    chars_t     ptr;                                            /* _operand_t */
    /*          temporary reading pointer */

    int         digits;                                         /* _operand_t */
    /*          total number of digits in the operand */

    int         intgr;                                          /* _operand_t */
    /*          number of integral digits in the operand */

    int         fract;                                          /* _operand_t */
    /*          number of decimal places in the operand */

    int         digit;                                          /* _operand_t */
    /*          current digit (temporary variable) */

    int         left;                                           /* _operand_t */
    /*          number of digits left to parse ```RENAME TO 'remain' */
}
_operand_t;


static _operand_t  _num_parse_operand( chars_t  operand_ ) {               /*F*/
    GO                                                            (UID(FD662D));
    chars_t  rd       = operand_;
    bool     is_blank = true;

    _operand_t  ret;
    ret.text        = operand_;  /* string from which operand was read        */
    ret.is_negative = false;     /* true if the number is negative            */
    ret.is_fract    = false;     /* true if the number has a decimal mark     */
    ret.first       = operand_;  /* rightmost digit at which reading begins   */
    ret.ptr         = NULL;      /* temporary reading pointer                 */
    ret.digits      = 0;         /* total number of digits in the operand     */
    ret.intgr       = 0;         /* number of integral digits in the operand  */
    ret.fract       = 0;         /* number of decimal places in the operand   */
    ret.digit       = 0;         /* current digit (temporary variable)        */
    ret.left        = 0;         /* number of digits left to parse            */

    if (operand_ == NULL) {
        RETURN(ret);
    }

    while (*rd) {
        if (*rd == '-') {
            is_blank = false;
            ret.is_negative = true;

        } else if (*rd == DECIMAL_MARK) {
            is_blank = false;
            ret.is_fract = true;

        } else if (IS_DIGIT(*rd)) {
            if (ret.is_fract) {
                ret.fract++;
            } else {
                ret.intgr++;
            }
            is_blank = false;
            ret.digits++;

        } else if (!IS_SPACE(*rd)) {
            is_blank = false;
        }
        rd++;
    }

    if (is_blank) {
        ret.digits = 0;
        rd = NULL;

    } else {
        rd--;
    }

    while (ret.digits > 0 && !IS_DIGIT(*rd)) {
        rd--;
    }

    ret.first = rd;

    /* reduce number of decimal places, for trailing zeros */
    if (ret.fract > 0) {
        ret.ptr = ret.first;

        while (ret.fract > 0 && *ret.ptr-- == '0') {
            ret.first = ret.ptr;
            ret.digits--;
            ret.fract--;
        }

        if (*ret.first == DECIMAL_MARK) {
            ret.first--;
        }
    }

    ret.ptr  = ret.first;
    ret.left = ret.digits;

    RETURN(ret);
} /* _num_parse_operand */


static void  _eval_read_left_operand(                                      /*F*/
    chars_t       expression_,                                             /*-*/
    const size_t  operator_position_,                                      /*-*/
    const str_t   decimal_mark_,                                           /*-*/
    const str_t   group_separator_,                                        /*-*/
    bool*         operand_found_out_,                                      /*-*/
    size_t*       left_position_out_ ) {                                   /*-*/
    GO                                                            (UID(F8DA93));
    const size_t  dec_mark_len  = lengthS(decimal_mark_);
    const size_t  group_sep_len = lengthS(group_separator_);
    bool          is_found      = false;
    bool          is_minus      = false;
    bool          is_decimal    = false;

    size_t    pos = operator_position_ == 0 ? 0 : operator_position_ - 1;
    chars_t   rd  = expression_ + pos;

    if (operator_position_ == NONE || operator_position_ == 0) {
        goto _set_args;
    }

    /* read trailing minus */
    if (rd >= expression_ && *rd == '-') {
        is_minus = true;
        rd--;
        pos--;
    }

    while (rd >= expression_) {
        if (IS_DIGIT(*rd)) {  /* read numeric characters */
            is_found = true;
            rd--;
            if (pos > 0) {
                pos--;
            }

            /* read decimal mark (can be more than 1 character long) */
        } else if (STRNCMP_T(rd - dec_mark_len + 1,
                             decimal_mark_.cs, dec_mark_len) == 0) {
            if (is_decimal) {
                break;
            }

            if (pos < dec_mark_len) {
                pos = 0;
                break;
            }

            is_decimal = true;
            is_found   = true;
            rd  -= dec_mark_len;
            pos -= dec_mark_len;

            /* skip digit group separators (can be more than 1 char long) */
        } else if (STRNCMP_T(rd - group_sep_len + 1,
                             group_separator_.cs, group_sep_len) == 0) {

            if (pos < group_sep_len) {
                pos = 0;
                break;
            }

            rd  -= group_sep_len;
            pos -= group_sep_len;

            /* read minus */
        } else if (*rd == '-') {
            if (is_minus) {
                break;
            }

            is_minus = true;
            rd--;

            if (pos > 0) {
                pos--;
            }
        } else {
            break;
        }
    };

_set_args:
    if (operand_found_out_) {
        *operand_found_out_ = is_found;
    }

    if (left_position_out_) {
        *left_position_out_ = pos;
    }
    RETURN(NIL);
} /* _eval_read_left_operand */


static void  _eval_read_right_operand(                                     /*F*/
    chars_t       expression_,                                             /*-*/
    const size_t  operator_position_,                                      /*-*/
    const str_t   decimal_mark_,                                           /*-*/
    const str_t   group_separator_,                                        /*-*/
    bool*         operand_found_out_,                                      /*-*/
    size_t*       right_position_out_ ) {                                  /*-*/
    GO                                                            (UID(F10453));
    const size_t  dec_mark_len  = lengthS(decimal_mark_);
    const size_t  group_sep_len = lengthS(group_separator_);
    const size_t  len           = lenT(expression_);
    bool          is_found      = false;
    bool          is_decimal    = false;
    size_t        pos           = operator_position_ + 1;
    chars_t       rd            = expression_ + pos;

    if (operator_position_ == NONE || operator_position_ >= (len - 1)) {
        goto _set_args;
    }

    while (rd < (expression_ + len)) {
        if (IS_DIGIT(*rd)) {  /* read numeric characters */
            is_found = true;
            rd++;
            if (pos < len) {
                pos++;
            }

            /* read decimal mark (can be more than 1 character long) */
        } else if (STRNCMP_T(rd - dec_mark_len + 1,
                             decimal_mark_.cs, dec_mark_len) == 0) {
            if (is_decimal) {
                break;
            }

            is_decimal = true;
            is_found   = true;
            rd  += dec_mark_len;
            pos += dec_mark_len;

            /* skip digit group separators (can be more than 1 char long) */
        } else if (STRNCMP_T(rd - group_sep_len + 1,
                             group_separator_.cs, group_sep_len) == 0)

        {
            rd += group_sep_len;
            pos += group_sep_len;
        } else {
            break;
        }
    };

_set_args:
    if (operand_found_out_) {
        *operand_found_out_ = is_found;
    }

    if (right_position_out_) {
        *right_position_out_ = pos;
    }
    RETURN(NIL);
} /* _eval_read_right_operand */


static void  _eval_remove_whitespaces_and_constants( str_t*  expr_ ) {     /*F*/
    GO                                                            (UID(F56176));
    /* remove all whitespaces from the expression string */
    replace3InS(expr_, _T(" "),  BLANK);
    replace3InS(expr_, _T("\n"), BLANK);
    replace3InS(expr_, _T("\r"), BLANK);
    replace3InS(expr_, _T("\t"), BLANK);

    /* if the string ends with '=', remove it */
    if (endsS(*expr_, _T("="), IGNORE_CASE)) {
        removeEndInS(expr_, 1);
    }

    /* replace PI with literal value */
    toupperInS(expr_);
    replace3InS(expr_, _T("PI"), _T("(22/7)"));

    RETURN(NIL);
} /* _eval_remove_whitespaces_and_constants */


static void  _eval_simplify_negative_and_positive_signs( str_t*  str_ ) {  /*F*/
    GO                                                            (UID(FA9331));
    while (find2S(*str_, _T("--")) != NONE ||
           find2S(*str_, _T("-+")) != NONE ||
           find2S(*str_, _T("+-")) != NONE ||
           find2S(*str_, _T("++")) != NONE) {

        replace3InS(str_, _T("--"), _T("+"));
        replace3InS(str_, _T("-+"), _T("-"));
        replace3InS(str_, _T("+-"), _T("-"));
        replace3InS(str_, _T("++"), _T("+"));
    }
    RETURN(NIL);
} /* _eval_simplify_negative_and_positive_signs */


static void  _num_trim_leading_zeros( char_t*  string_to_trim_ ) {         /*F*/
    GO                                                            (UID(F66B7D));
    chars_t  rd   = string_to_trim_;
    char_t*  wr   = string_to_trim_;
    bool     trim = true;

    while (rd && *rd) {
        if (trim) {
            if (IS_SPACE(*rd)) {
                rd++;
                continue;
            }

            if (*rd == '0' &&
                *(rd + 1) != DECIMAL_MARK &&
                *(rd + 1) != '\0') {
                rd++;
                continue;
            }

            if (*rd == '-') {
                *wr++ = *rd++;
                continue;
            }

            trim = false;
        }
        *wr++ = *rd++;
    }
    *wr = '\0';
    RETURN(NIL);
} /* _num_trim_leading_zeros */


#if NUMBER_TESTS > 0

static void  test_m_num_trim_leading_zeros( void ) {                       /*F*/
    GO                                                            (UID(F44FBF));
    struct _test_t {
        uint32_t  test_id;                                         /* _test_t */
        chars_t   text;                                            /* _test_t */
        chars_t   correct_result;                                  /* _test_t */
    }
    test[] = {

        { UID(EB74B2), _T("-001"),       _T("-1") },
        { UID(E1E51A), _T("-01"),        _T("-1") },
        { UID(E5D811), _T("-10"),        _T("-10") },
        { UID(EA52FB), _T("-010"),       _T("-10") },
        { UID(E1753E), _T("-0010"),      _T("-10") },
        { UID(E200C9), _T("-0010.00"),   _T("-10.00") },

        { UID(EC2182), _T(" -001"),      _T("-1") },
        { UID(E12715), _T(" -01"),       _T("-1") },
        { UID(E6A6AC), _T(" -10"),       _T("-10") },
        { UID(E34834), _T(" -010"),      _T("-10") },
        { UID(E359C0), _T(" -0010"),     _T("-10") },
        { UID(EB9323), _T(" -0010.00"),  _T("-10.00") },

        { UID(E6E31F), _T(" -001 "),     _T("-1 ") },
        { UID(EB2C7C), _T(" -01 "),      _T("-1 ") },
        { UID(EFEF51), _T(" -10 "),      _T("-10 ") },
        { UID(E409ED), _T(" -010 "),     _T("-10 ") },
        { UID(E4527B), _T(" -0010 "),    _T("-10 ") },
        { UID(E706F5), _T(" -0010.00 "), _T("-10.00 ") },

        { UID(E79C7E), _T("001"),        _T("1") },
        { UID(EABC27), _T("01"),         _T("1") },
        { UID(ED3276), _T("10"),         _T("10") },
        { UID(EA856D), _T("010"),        _T("10") },
        { UID(E429C1), _T("0010"),       _T("10") },
        { UID(E7E9B3), _T("0010.00"),    _T("10.00") },

        { UID(EA9AA0), _T(" 001"),       _T("1") },
        { UID(E2AEEE), _T(" 01"),        _T("1") },
        { UID(E63655), _T(" 10"),        _T("10") },
        { UID(E5F061), _T(" 010"),       _T("10") },
        { UID(EC1BE0), _T(" 0010"),      _T("10") },
        { UID(E99C3F), _T(" 0010.00"),   _T("10.00") },

        { UID(E231FD), _T(" 001 "),      _T("1 ") },
        { UID(EBEBB0), _T(" 01 "),       _T("1 ") },
        { UID(E564B5), _T(" 10 "),       _T("10 ") },
        { UID(E119FD), _T(" 010 "),      _T("10 ") },
        { UID(E1BCFA), _T(" 0010 "),     _T("10 ") },
        { UID(E3F560), _T(" 0010.00 "),  _T("10.00 ") },

        /* NULL, NULL terminates loop */
        { 0, NULL, NULL }
    };

    int  i = 0;
    while (0 != test[i].test_id) {
        const uint32_t  test_id        = test[i].test_id;
        chars_t         text           = test[i].text;
        chars_t         correct_result = test[i].correct_result;
        new_chars_t     result         = T_chars(text);

        /* should be '== -1', unless you need to debug a failed test */
        if (_test_no == -1) {
            DEBUG_BREAK;
        }

        _num_trim_leading_zeros(result);

        if (0 != STRCMP_T(result, correct_result)) {
            PRINTF_T(_T("\r\n")
                     _T("Failed Test %08X: _num_trim_leading_zeros('%s')")
                     _T(" is '%s' instead of '%s'!!"),
                     test_id, text, result, correct_result);
            DEBUG_BREAK;
        }

        freeT(&result);
        _test_no++;
        i++;
    }
    RETURN(NIL);
} /* test_m_num_trim_leading_zeros */
#endif                                                    /* NUMBER_TESTS > 0 */


static void  _num_trim_trailing_zeros( char_t*  string_to_trim_ ) {        /*F*/
    GO                                                            (UID(F4C47E));
    /* trim trailing zeros after decimal mark */

    chars_t  rd               = string_to_trim_;
    bool     has_decimal_mark = false;

    while (*rd) {
        if (*rd++ == DECIMAL_MARK) {
            has_decimal_mark = true;
        }
    }

    if (has_decimal_mark) {
        char_t*  wr = CAST(char_t*, rd - 1);

        while (*wr == '0'  || *wr == ' '  || *wr == '\a' ||
               *wr == '\b' || *wr == '\f' || *wr == '\n' ||
               *wr == '\r' || *wr == '\t' || *wr == '\v') {
            *wr = '\0';
            wr--;
        }

        if (*wr == DECIMAL_MARK) {
            *wr = '\0';
        }
    }
    RETURN(NIL);
} /* _num_trim_trailing_zeros */


#if NUMBER_TESTS > 0

static void  test_m_num_trim_trailing_zeros( void ) {                      /*F*/
    GO                                                            (UID(FF24AB));
    /* TODO*/
    RETURN(NIL);
} /* test_m_num_trim_trailing_zeros */
#endif                                                    /* NUMBER_TESTS > 0 */


/* -------------------------------------------------------------------------- */
/* Functions: Private (2)                                                     */


static new_str_t  _num_add_or_subtract(                                    /*F*/
    _operand_t*  number_1_,                                                /*-*/
    _operand_t*  number_2_,                                                /*-*/
    const bool   addition_ ) {                                             /*-*/
    GO                                                            (UID(F626D9));
    int          i          = 0;
    int          result_len = 0;
    int          writ       = 0;
    _operand_t*  a          = number_1_;
    _operand_t*  b          = number_2_;
    _operand_t*  x          = NULL;
    char_t*      wr         = NULL;
    new_chars_t  result     = NULL;
    bool         has_carry        = false;
    bool         has_non_zero     = false;
    bool         has_decimal_mark = false;

    const int  cmp = num_cmp(number_1_->text, number_2_->text, true);

    const bool  is_negative_result = cmp >= 0 ? a->is_negative : addition_
                                     ? b->is_negative : !b->is_negative;

    const bool  is_addition = addition_ == (a->is_negative == b->is_negative);

    if (a->digits == 0 && b->digits == 0) {
        new_str_t  ret = S_chars(_T("0"));
        RETURN(ret);
    }

    if (!is_addition && cmp < 0) {
        a = number_2_;
        b = number_1_;
    }

    result_len = 2                               /* space for minus and carry */
                 + GREATER(a->intgr, b->intgr)            /* integer part     */
                 + ((a->fract + b->fract > 0) ? 1 : 0)    /* for decimal mark */
                 + GREATER(a->fract, b->fract);           /* fractional part  */

    result = mallocT(result_len + 1);  /* + 1 in case of a carry */
    wr = result + result_len - 1;

    while (a->left > 0 || b->left > 0) {
        bool  write_decimal_mark = false;
        bool  reduce_fract[2]    = { false, false };

        a->digit = 0;
        b->digit = 0;

        for (i = 0; i < 2; i++) {
            x = i == 0 ? a : b;

            while (x->ptr != NULL && x->left > 0) {
                char_t  ch = *x->ptr;

                if (IS_SPACE(ch) || ch == DECIMAL_MARK) {
                    x->ptr--;
                    continue;

                } else if ((i == 0 && a->fract < b->fract) ||
                           (i == 1 && a->fract > b->fract)) {
                    x->digit = 0;

                } else if (IS_DIGIT(ch)) {
                    x->digit = ch - '0';
                    if (x->fract > 0) {
                        if (x->fract == 1) {
                            write_decimal_mark = true;
                        }
                        reduce_fract[i] = true;
                    }
                    x->ptr--;
                    x->left--;

                } else {
                    x->ptr = NULL;
                }
                break;
            }
        }

        for (i = 0; i < 2; i++) {
            x = i == 0 ? a : b;
            if (reduce_fract[i]) {
                x->fract--;
            }
        }

        if (is_addition) {
            a->digit += b->digit + (has_carry ? 1 : 0);
            has_carry = (a->digit > 9 ? true : false);

            if (has_carry) {
                a->digit -= 10;
            }

        } else {
            a->digit -= b->digit + (has_carry ? 1 : 0);

            if (has_carry) {
                has_carry = false;
            }

            if (a->digit < 0) {
                a->digit = 10 + a->digit;
                has_carry = true;
            }
        }

        if (!has_non_zero && a->digit > 0) {
            has_non_zero = true;
        }

        *wr = CAST(char_t, '0' + a->digit);
        wr--;
        writ++;

        if (write_decimal_mark) {
            *wr = DECIMAL_MARK;
            wr--;
            writ++;
            has_decimal_mark = true;
        }
    }

    if (is_addition && has_carry) {
        *wr = '1';
        wr--;
        writ++;
        has_non_zero = true;
    }

    if (*(wr + 1) == DECIMAL_MARK) {
        *wr = '0';
        wr--;
        writ++;
    }

    /* write minus sign if both operands are negative (negative addition) */
    /* prevent writing minus sign if there are no non-zero digits         */
    if (is_negative_result && has_non_zero) {
        bool     found = false;
        chars_t  rd    = wr + 1;

        while (*rd) {
            if (IS_DIGIT(*rd)) {
                found = true;
                break;
            }
            rd++;
        }

        if (found) {
            *wr = '-';
            wr--;
            writ++;
        }
    }

    if (result_len > writ) {
        const int  left = result_len - writ;
        chars_t    rd   = result + left;

        wr = result;
        while (*rd) {
            *wr = *rd;
            wr++;
            rd++;
        }
        *wr = '\0';
    }

    _num_trim_leading_zeros(result);

    if (has_decimal_mark || a->is_fract) {
        _num_trim_trailing_zeros(result);
    }

    {
        const new_str_t  ret = S_newT(result);
        RETURN(ret);
    }
} /* _num_add_or_subtract */


#if defined __GNUC__
#pragma GCC diagnostic pop
#endif


/* -------------------------------------------------------------------------- */
/* Function: Complete Unit Tests                                              */


#if NUMBER_TESTS > 0
PUBLIC void  test_number( void ) {                                         /*F*/
    GO                                                            (UID(FC2D8D));
    _test_no = 0;

    /* Functions: Private */
    test_m_num_trim_leading_zeros();
    test_m_num_trim_trailing_zeros();

    /* Functions: Arithmetic Operations */
    test_num_add();
    test_num_div();
    test_num_mul();
    test_num_sub();

    /* Function: Logic */
    test_num_cmp();

    /* Functions: General Calculation Evaluation */
    test_num_eval();

    PRINTF_T(_T("\r\n") _T("Number of tests: %d"), _test_no);
    _test_no = 0;

    RETURN(NIL);
} /* test_number */
#endif                                                    /* NUMBER_TESTS > 0 */


/* -------------------------------------------------------------------------- */
/* Functions: Arithmetic Operations                                           */


PUBLIC new_str_t  num_add(                                                 /*F*/
    chars_t  augend_,                                                      /*-*/
    chars_t  addend_ ) {                                                   /*-*/
    GO                                                            (UID(FCB294));
    _operand_t  augend = _num_parse_operand(augend_);
    _operand_t  addend = _num_parse_operand(addend_);
    new_str_t   ret    = _num_add_or_subtract(&augend, &addend, true);
    RETURN(ret);
} /* num_add */


#if NUMBER_TESTS > 0
PUBLIC void  test_num_add( void ) {                                        /*F*/
    GO                                                            (UID(FB0CED));
    /* specify values for initial test here */
    static chars_t  AUGEND[] = { _T("1"), NULL };
    static chars_t  ADDEND[] = { _T("1"), NULL };
#define RESULT                   _T("2")

    struct _test_t {
        uint32_t  test_id;                                         /* _test_t */
        chars_t*  augends;                                         /* _test_t */
        chars_t*  addends;                                         /* _test_t */
        chars_t   correct_result;                                  /* _test_t */
    }
    test[] = {

        /* test 1 */
        { UID(EEFBEF), AUGEND, ADDEND, RESULT },
#undef RESULT

        /* add negative and positive values */
        { UID(E0FDE0), TEST_10,   TEST_5,    _T("15") },
        { UID(ED9D1F), TEST_10,   TEST_M_5,  _T("5") },
        { UID(EF346F), TEST_M_10, TEST_5,    _T("-5") },
        { UID(E28D79), TEST_M_10, TEST_M_5,  _T("-15") },
        { UID(E577B9), TEST_5,    TEST_10,   _T("15") },
        { UID(EE5421), TEST_5,    TEST_M_10, _T("-5") },
        { UID(EAD8C6), TEST_M_5,  TEST_10,   _T("5") },
        { UID(E297A0), TEST_M_5,  TEST_M_10, _T("-15") },

        /* subtracting smaller or equal numbers from larger numbers */
        { UID(E55781), TEST_1,     TEST_M_1,     _T("0") },
        { UID(E9E178), TEST_10,    TEST_M_1,     _T("9") },
        { UID(E58C91), TEST_10,    TEST_M_6,     _T("4") },
        { UID(E4CEDE), TEST_100,   TEST_M_1,     _T("99") },
        { UID(EC8122), TEST_100,   TEST_M_99,    _T("1") },
        { UID(E2D1EF), TEST_1000,  TEST_M_543,   _T("457") },
        { UID(EC15FC), TEST_10001, TEST_M_10000, _T("1") },
        { UID(E6C373), TEST_10001, TEST_M_10001, _T("0") },
        { UID(E71C1D), TEST_12,    TEST_M_11,    _T("1") },

        /* blanks and zeros */
        { UID(ED3A1B), TEST_BLANKS, TEST_BLANKS, _T("0") },
        { UID(EBB7B9), TEST_BLANKS, TEST_0,      _T("0") },
        { UID(E4010A), TEST_0,      TEST_BLANKS, _T("0") },
        { UID(E31193), TEST_0,      TEST_0,      _T("0") },

        /* blank + value */
        { UID(ED0040), TEST_BLANKS, TEST_1,   _T("1") },
        { UID(EDB936), TEST_BLANKS, TEST_M_1, _T("-1") },
        { UID(E7D6DE), TEST_BLANKS, TEST_123, _T("123") },

        /* value + blank */
        { UID(EB6650), TEST_1,   TEST_BLANKS, _T("1") },
        { UID(EB0A31), TEST_M_1, TEST_BLANKS, _T("-1") },
        { UID(EB0426), TEST_123, TEST_BLANKS, _T("123") },

        /* test_id == 0 terminates loop */
        { 0, NULL, NULL, NULL }
    };

    int  i = 0;
    while (0 != test[i].test_id) {
        const uint32_t  test_id        = test[i].test_id;
        chars_t*        augends        = test[i].augends;
        chars_t*        addends        = test[i].addends;
        chars_t         correct_result = test[i].correct_result;
        new_str_t       result         = { NULL };
        int             aug_no         = 0;

        while (augends[aug_no]) {
            chars_t  augend = augends[aug_no];
            int      add_no = 0;

            while (addends[add_no]) {
                chars_t  addend = addends[add_no];

                /* should be '== -1', unless you need to debug a failure */
                if (_test_no == -1) {
                    DEBUG_BREAK;
                }

                result = num_add(augend, addend);

                if (0 != STRCMP_T(result.cs, correct_result)) {
                    PRINTF_T(_T("\r\n")
                             _T("Failed Test %08X: num_add('%s', '%s')")
                             _T(" returned '%s' instead of '%s'!!"),
                             test_id, augend, addend,
                             result.cs, correct_result);
                    DEBUG_BREAK;
                }

                freeS(&result);
                _test_no++;
                add_no++;;
            }
            aug_no++;
        }
        i++;
    }
    PRINTF_T(_T("\r\n"));
    RETURN(NIL);
} /* test_num_add */
#endif                                                    /* NUMBER_TESTS > 0 */


PUBLIC new_str_t  num_div(                                                 /*F*/
    chars_t    dividend_,                                                  /*-*/
    chars_t    divisor_,                                                   /*-*/
    const int  decimal_places_ ) {                                         /*-*/
    GO                                                            (UID(F3A24E));
    new_str_t          ret      = { NULL };
    const long double  dividend = doubleT(dividend_);
    const long double  divisor  = doubleT(divisor_);

    if (CAST(int, divisor * 1000000) == 0) {
        ret = S_chars(_T("error"));

    } else {
        const long double  result = dividend / divisor;
        ret = S_newT(T_double(result, decimal_places_));
    }
    RETURN(ret);
} /* num_div */


#if NUMBER_TESTS > 0
PUBLIC void  test_num_div( void ) {                                        /*F*/
    GO                                                            (UID(F2108E));
    /* TODO*/
    RETURN(NIL);
} /* test_num_div */
#endif                                                    /* NUMBER_TESTS > 0 */


PUBLIC new_str_t  num_mul(                                                 /*F*/
    chars_t  multiplicand_,                                                /*-*/
    chars_t  multiplier_ ) {                                               /*-*/
    GO                                                            (UID(F01A0E));
    new_str_t    ret        = { NULL };
    _operand_t   num        = _num_parse_operand(multiplicand_);
    _operand_t   mul        = _num_parse_operand(multiplier_);
    char_t*      wr         = NULL;
    bool         is_writ    = false;
    new_chars_t  result_str = NULL;
    _operand_t   result;

    if (num.digits == 0 || mul.digits == 0) {
        ret = S_chars(_T("0"));
        RETURN(ret);
    }

    CLEAR(result);

    result.digits = num.digits + mul.digits;
    {
        if (num.fract > 0 || mul.fract > 0) {
            result.digits += 2;    /* add space for '.' or '0.' */
        }

        if (num.is_negative || mul.is_negative) {
            result.is_negative = XOR(num.is_negative, mul.is_negative);
            result.digits += 1;
        }
    }

    result_str  = mallocT(result.digits + 1);
    result.ptr  = result_str + result.digits;
    result.left = result.digits;

    /* multiplier loop */
    mul.digit = 0;
    mul.left  = mul.digits;
    mul.ptr   = mul.first;

    while (mul.left > 0) {
        chars_t  pos1 = NULL;

        /* skip non-digit characters */
        mul.digit = *mul.ptr;

        if (IS_DIGIT(mul.digit)) {
            mul.digit -= '0';
            mul.left--;
        } else {
            mul.ptr--;
            continue;
        }

        /* multiplicand loop */
        num.digit = 0;
        num.left  = num.digits;
        num.ptr   = num.first;
        pos1      = --result.ptr;

        while (0 != mul.digit && num.left > 0) {

            /* skip non-digit characters */
            num.digit = *num.ptr;

            if (IS_DIGIT(num.digit)) {
                num.digit -= '0';
                num.left--;
            } else {
                num.ptr--;
                continue;
            }

            {
                chars_t  pos2      = result.ptr;
                int      digit     = num.digit * mul.digit;
                int      carry_val = digit / 10;

                if (carry_val) {
                    digit -= carry_val * 10;
                }

                /* additive loop */
                while (carry_val || digit || *result.ptr == '\0') {
                    if (*result.ptr == '\0') {
                        result.left--;
                    } else {
                        digit += (*result.ptr - '0');
                    }

                    if (digit > 9) {
                        digit -= 10;
                        carry_val += 1;
                    }

                    wr      = CAST(char_t*, result.ptr);
                    *wr     = '0' + CAST(char_t, digit);
                    is_writ = true;

                    digit = carry_val;
                    carry_val = 0;
                    result.ptr--;
                }
                result.ptr = pos2;
                result.ptr--;
            }
            num.ptr--;
        }
        result.ptr = pos1;
        mul.ptr--;
    }

    if (!is_writ) {
        wr  = CAST(char_t*, result_str);
        *wr = '0';
        *(wr + 1) = '\0';
        ret = S_newT(wr);
        RETURN(ret);
    }

    if (result.is_negative) {
        wr = CAST(char_t*, result_str);
        *wr = '-';
    }

    if (result.left > 0) {
        result.ptr = result_str + result.left;
        wr = CAST(char_t*, result_str);

        while (*result.ptr) {
            *wr++ = *result.ptr++;
        }
        *wr = '\0';
    }

    if ((num.fract + mul.fract) > 0) {
        int  dec_places = num.fract + mul.fract;

        wr = CAST(char_t*, result_str);

        while (*wr != '\0') {
            wr++;
        }
        wr++;

        /* + 1 for \0 */
        while ((dec_places + 1) > 0) {
            *wr = *(wr - 1);
            wr--;
            dec_places--;
        }
        *wr = DECIMAL_MARK;
    }

    wr = CAST(char_t*, result_str);
    _num_trim_leading_zeros(wr);

    if ((num.fract + mul.fract) > 0) {
        _num_trim_trailing_zeros(wr);
    }

    ret = S_newT(wr);
    RETURN(ret);
} /* num_mul */


#if NUMBER_TESTS > 0
PUBLIC void  test_num_mul( void ) {                                        /*F*/
    GO                                                            (UID(F30CE9));
    struct _test_t {
        uint32_t  test_id;                                         /* _test_t */
        chars_t   multiplicand;                                    /* _test_t */
        chars_t   multiplier;                                      /* _test_t */
        chars_t   correct_result;                                  /* _test_t */
    }
    test[] = {

        /* number 1, number2, result */
        { UID(EAB02B), _T("9.0"), _T("1.0"),   _T("9")      },
        { UID(ED2CB5), _T("1-"),  _T("1.234"), _T("-1.234") },
        { UID(E12C1D), _T("2-"),  _T("2.001"), _T("-4.002") },

        /* negative / positive values */
        { UID(E6BFD8), _T(" 5"), _T(" 5"), _T("25")  },
        { UID(E04E0D), _T(" 5"), _T("-5"), _T("-25") },
        { UID(E125C2), _T("-5"), _T(" 5"), _T("-25") },
        { UID(E64B65), _T("-5"), _T("-5"), _T("25")  },

        /* fractions */
        { UID(E748CC), _T(".001"), _T(".001"), _T("0.000001") },
        { UID(E515CB), _T(".9"),   _T("0.9"),  _T("0.81")     },
        { UID(E5A649), _T("0.0"),  _T("0.0"),  _T("0")        },
        { UID(E03EB4), _T("1"),    _T(".2"),   _T("0.2")      },
        { UID(E0EB67), _T("9"),    _T(".1"),   _T("0.9")      },
        { UID(E8276B), _T("9.0"),  _T("1.0"),  _T("9")        },

        /* miscellaneous */
        { UID(E24986), _T("-.001"),  _T("-.001"), _T("0.000001") },
        { UID(E0FD41), _T("2-"),     _T("2.001"), _T("-4.002")   },
        { UID(EBFBC6), _T("2 -"),    _T("2.001"), _T("-4.002")   },
        { UID(EF053A), _T("-2"),     _T("2.001"), _T("-4.002")   },
        { UID(E63326), _T("-2.0"),   _T("2.001"), _T("-4.002")   },
        { UID(EA7462), _T("-2.000"), _T("2.001"), _T("-4.002")   },
        { UID(EF9CE7), _T("-2."),    _T("2.001"), _T("-4.002")   },

        { UID(E51C92), _T("98"), _T("76"), _T("7448") },
        { UID(EA87BB), _T("99"), _T("9"),  _T("891")  },
        { UID(E561B9), _T("12"), _T("2"),  _T("24")   },
        { UID(E1AC58), _T("2"),  _T("2"),  _T("4")    },

        /* nines */
        { UID(E5AE95), _T("9"), _T("9"), _T("81") },
        { UID(EA06D9), _T("99"), _T("99"), _T("9801") },
        { UID(EE8A05), _T("999"), _T("999"), _T("998001") },
        { UID(EC603C), _T("9999"), _T("9999"), _T("99980001") },
        { UID(EB0A56), _T("99999"), _T("99999"), _T("9999800001") },
        { UID(E2023F), _T("999999"), _T("999999"), _T("999998000001") },
        { UID(E36399), _T("9999999"), _T("9999999"), _T("99999980000001") },
        { UID(E533CD), _T("99999999"), _T("99999999"), _T("9999999800000001") },
        { UID(E41D9F), _T("999999999"), _T("999999999"), _T("999999998000000001") },
        { UID(EF4FBB), _T("9999999999"), _T("9999999999"), _T("99999999980000000001") },
        { UID(ECE784), _T("99999999999"), _T("99999999999"), _T("9999999999800000000001") },
        { UID(E51E1F), _T("999999999999"), _T("999999999999"), _T("999999999998000000000001") },
        { UID(EF7DF4), _T("9999999999999"), _T("9999999999999"), _T("99999999999980000000000001") },
        { UID(ED3966), _T("99999999999999"), _T("99999999999999"), _T("9999999999999800000000000001") },
        { UID(E80AA9), _T("999999999999999"), _T("999999999999999"), _T("999999999999998000000000000001") },

        /* zero-gaps */
        { UID(ED1CA5), _T("101"),         _T("1"),           _T("101")                   },
        { UID(E40CEB), _T("10000001"),    _T("1"),           _T("10000001")              },
        { UID(ED02C7), _T("10000000001"), _T("1"),           _T("10000000001")           },
        { UID(E696DB), _T("10000000001"), _T("10000000001"), _T("100000000020000000001") },
        { UID(E0109B), _T("10000000001"), _T("101"),         _T("1010000000101")         },
        { UID(E4CDBD), _T("10001"),       _T("10001"),       _T("100020001")             },
        { UID(EF3062), _T("10001"),       _T("999"),         _T("9990999")               },
        { UID(E790E3), _T("1001"),        _T("1001"),        _T("1002001")               },
        { UID(EB5BA0), _T("1001"),        _T("999"),         _T("999999")                },
        { UID(E3F9AC), _T("101"),         _T("101"),         _T("10201")                 },
        { UID(E5E0CC), _T("101"),         _T("999"),         _T("100899")                },

        /* null string */
        { UID(E65304), NULL, NULL, _T("0") },

        /* blank strings */
        { UID(EC625D), _T("   "),    _T("   "),    _T("0") },
        { UID(E0C5DD), _T("  "),     _T("  "),     _T("0") },
        { UID(EF7F44), _T(" "),      _T(" "),      _T("0") },
        { UID(E479F2), _T(""),       _T(""),       _T("0") },
        { UID(ED1593), _T("\n"),     _T("\n"),     _T("0") },
        { UID(E31ED9), _T("\r"),     _T("\r"),     _T("0") },
        { UID(E93DF3), _T("\r\n"),   _T("\r\n"),   _T("0") },
        { UID(E74C34), _T("\t"),     _T("\t"),     _T("0") },

        /* blank + value */
        { UID(EDEA01), _T("   "),    _T("123"),    _T("0") },
        { UID(EE9E30), _T("  "),     _T("123"),    _T("0") },
        { UID(E99961), _T(" "),      _T("123"),    _T("0") },
        { UID(E6FFAB), _T(""),       _T("123"),    _T("0") },
        { UID(E74E31), _T("\n"),     _T("123"),    _T("0") },
        { UID(EE4530), _T("\r"),     _T("123"),    _T("0") },
        { UID(E6F606), _T("\r\n"),   _T("123"),    _T("0") },
        { UID(EDEDED), _T("\t"),     _T("123"),    _T("0") },
        { UID(E5C737), NULL,         _T("123"),    _T("0") },

        /* value + blank */
        { UID(EF1A4B), _T("123"),    _T("   "),    _T("0") },
        { UID(EE244D), _T("123"),    _T("  "),     _T("0") },
        { UID(E79F46), _T("123"),    _T(" "),      _T("0") },
        { UID(EB7B61), _T("123"),    _T(""),       _T("0") },
        { UID(EC0A27), _T("123"),    _T("\n"),     _T("0") },
        { UID(E1A289), _T("123"),    _T("\r"),     _T("0") },
        { UID(E97C3B), _T("123"),    _T("\r\n"),   _T("0") },
        { UID(EC0BC3), _T("123"),    _T("\t"),     _T("0") },
        { UID(E7AC0B), _T("123"),    NULL,         _T("0") },

        /* miscellaneous */
        { UID(ED3D28), _T("0111"),   _T("0222"),   _T("24642") },
        { UID(ED0B3D), _T("1"),      _T("99"),     _T("99")    },
        { UID(EA3DB5), _T("12"),     _T("34"),     _T("408")   },
        { UID(E65E81), _T("88"),     _T("77"),     _T("6776")  },
        { UID(E69510), _T("9"),      _T("9"),      _T("81")    },
        { UID(E18EC4), _T("9999"),   _T("0"),      _T("0")     },
        { UID(E0DB92), _T("9999"),   NULL,         _T("0")     },

        /* miscellaneous: whitespace-padded */
        { UID(EC6163), _T(" 0111 "), _T(" 0222 "), _T("24642") },
        { UID(E87634), _T(" 1 "),    _T(" 99 "),   _T("99")    },
        { UID(E71341), _T(" 12 "),   _T(" 34 "),   _T("408")   },
        { UID(EE5018), _T(" 88 "),   _T(" 77 "),   _T("6776")  },
        { UID(E8E1D8), _T(" 9 "),    _T(" 9 "),    _T("81")    },
        { UID(ED3ECC), _T(" 9999 "), _T(" 0 "),    _T("0")     },
        { UID(E63CCC), _T(" 9999 "), NULL,         _T("0")     },

        /* zeros */
        { UID(E56C15), _T("0"),      _T("0"),      _T("0") },
        { UID(E1C293), _T("0"),      _T("00"),     _T("0") },
        { UID(E687B5), _T("0"),      _T("000"),    _T("0") },
        { UID(E9CD6B), _T("00"),     _T("0"),      _T("0") },
        { UID(EC2A0D), _T("000"),    _T("0"),      _T("0") },

        /* test_id == 0 terminates loop */
        { 0, NULL, NULL, NULL }
    };

    int  i = 0;
    while (0 != test[i].test_id) {
        const uint32_t  test_id        = test[i].test_id;
        chars_t         multiplicand   = test[i].multiplicand;
        chars_t         multiplier     = test[i].multiplier;
        chars_t         correct_result = test[i].correct_result;
        new_str_t       result         = { NULL };

        /* should be '== -1', unless you need to debug a failed test */
        if (_test_no == -1) {
            DEBUG_BREAK;
        }

        result = num_mul(multiplicand, multiplier);

        if (0 != STRCMP_T(result.cs, correct_result)) {
            PRINTF_T(_T("\r\n")
                     _T("Failed Test %08X: num_mul('%s', '%s')")
                     _T(" returned '%s' instead of '%s'!!"),
                     test_id, multiplicand, multiplier,
                     result.cs, correct_result);
            DEBUG_BREAK;
        }

        freeS(&result);
        _test_no++;
        i++;
    }
    RETURN(NIL);
} /* test_num_mul */
#endif                                                    /* NUMBER_TESTS > 0 */


PUBLIC new_str_t  num_sub(                                                 /*F*/
    chars_t  minuend_,                                                     /*-*/
    chars_t  subtrahend_ ) {                                               /*-*/
    GO                                                            (UID(F9DA8F));
    _operand_t       minuend    = _num_parse_operand(minuend_);
    _operand_t       subtrahend = _num_parse_operand(subtrahend_);
    const new_str_t  ret = _num_add_or_subtract(&minuend, &subtrahend, false);
    RETURN(ret);
} /* num_sub */


#if NUMBER_TESTS > 0
PUBLIC void  test_num_sub( void ) {                                        /*F*/
    GO                                                            (UID(FA9AEA));
    /* specify values for initial test here */
    static chars_t  MINUEND[]    = { _T("1"), NULL };
    static chars_t  SUBTRAHEND[] = { _T("1"), NULL };
#define RESULT                    _T("0")

    struct _test_t {
        uint32_t  test_id;                                         /* _test_t */
        chars_t*  minuends;                                        /* _test_t */
        chars_t*  subtrahends;                                     /* _test_t */
        chars_t   correct_result;                                  /* _test_t */
    }
    test[] = {

        /* test 1 */
        { UID(E8594D), MINUEND, SUBTRAHEND, RESULT },
#undef RESULT

        { UID(E90E5D), TEST_BLANKS, TEST_123,    _T("-123") },
        { UID(E4B1D7), TEST_BLANKS, TEST_1,      _T("-1") },
        { UID(E20A82), TEST_123,    TEST_BLANKS, _T("123") },
        { UID(ECD42E), TEST_1,      TEST_BLANKS, _T("1") },

        /* miscellaneous */
        { UID(E12DE4), TEST_111,  TEST_222,    _T("-111") },
        { UID(E399AE), TEST_1,    TEST_99,     _T("-98") },
        { UID(EC0D26), TEST_12,   TEST_34,     _T("-22") },
        { UID(E20C71), TEST_88,   TEST_77,     _T("11") },
        { UID(EE1BAD), TEST_77,   TEST_88,     _T("-11") },
        { UID(E2EBF8), TEST_77,   TEST_66,     _T("11") },
        { UID(E7DD06), TEST_9,    TEST_9,      _T("0") },
        { UID(E7EFD4), TEST_8,    TEST_9,      _T("-1") },
        { UID(EC43E0), TEST_9999, TEST_0,      _T("9999") },
        { UID(E53B8F), TEST_9999, TEST_BLANKS, _T("9999") },

        /* zeros */
        { UID(E415D6), TEST_0, TEST_0, _T("0") },

        /* miscellaneous: negative */
        { UID(EDCB86), TEST_111,  TEST_222,    _T("111") },
        { UID(EF0390), TEST_1,    TEST_99,     _T("98") },
        { UID(EFADD9), TEST_12,   TEST_34,     _T("22") },
        { UID(EBC0D3), TEST_77,   TEST_88,     _T("11") },
        { UID(E07F67), TEST_88,   TEST_77,     _T("-11") },
        { UID(ECEB6D), TEST_8,    TEST_9,      _T("1") },
        { UID(EF09F8), TEST_9999, TEST_0,      _T("-9999") },
        { UID(E4883A), TEST_9999, TEST_BLANKS, _T("-9999") },

        /* fractions */
        { UID(E524B7), TEST_0,         TEST_P001,      _T("-0.001") },
        { UID(EEB06B), TEST_0,         TEST_P01,       _T("-0.01") },
        { UID(E2C3DD), TEST_0P0000001, TEST_1000000,   _T("-999999.9999999") },
        { UID(EA0282), TEST_0P99,      TEST_99,        _T("-98.01") },
        { UID(EFCC02), TEST_0P99,      TEST_99P0,      _T("-98.01") },
        { UID(E7DC7E), TEST_0P99,      TEST_99P00,     _T("-98.01") },
        { UID(ED5DFA), TEST_1000000,   TEST_0P0000001, _T("999999.9999999") },
        { UID(EB44E8), TEST_1000000,   TEST_P0000001,  _T("999999.9999999") },
        { UID(E5C639), TEST_99,        TEST_0P99,      _T("98.01") },
        { UID(E7FDC0), TEST_99,        TEST_P99,       _T("98.01") },
        { UID(E44EB1), TEST_99P0,      TEST_0P99,      _T("98.01") },
        { UID(E598AD), TEST_99P0,      TEST_P99,       _T("98.01") },
        { UID(E48918), TEST_99P00,     TEST_0P99,      _T("98.01") },
        { UID(E6FFA0), TEST_99P00,     TEST_P99,       _T("98.01") },
        { UID(E45A2F), TEST_9P8,       TEST_9,         _T("0.8") },
        { UID(E46FAE), TEST_9P87,      TEST_9P8,       _T("0.07") },
        { UID(E398AA), TEST_9P876,     TEST_9P87,      _T("0.006") },
        { UID(E32B57), TEST_P0000001,  TEST_1000000,   _T("-999999.9999999") },
        { UID(EF7E4D), TEST_P001,      TEST_P001,      _T("0") },
        { UID(EA651A), TEST_P99,       TEST_99,        _T("-98.01") },
        { UID(E21AF7), TEST_P99,       TEST_99P0,      _T("-98.01") },
        { UID(ED69BD), TEST_P99,       TEST_99P00,     _T("-98.01") },

        /* long fractions */
        { UID(E07CD1), TEST_1E60, TEST_1E60, _T("0") },

        {
            UID(EFF7F1),
            TEST_9P876DP58,
            TEST_9P876DP38,
            _T("0.0000000000000000000000000000000000000009876543210987654321"),
        },

        {
            UID(E588B4),
            TEST_9P876DP38,
            TEST_9P876DP58,
            _T("-0.0000000000000000000000000000000000000009876543210987654321"),
        },

        /* null string */
        /* { UID(E4FFA0), NULL, NULL, _T("0") }, */

        /* test_id == 0 terminates loop */
        { 0, NULL, NULL, NULL }
    };

    int  i = 0;
    while (0 != test[i].test_id) {
        const uint32_t  test_id        = test[i].test_id;
        chars_t*        minuends       = test[i].minuends;
        chars_t*        subtrahends    = test[i].subtrahends;
        chars_t         correct_result = test[i].correct_result;
        new_str_t       result         = { NULL };
        int             min_no         = 0;

        while (minuends[min_no]) {
            chars_t  minuend = minuends[min_no];
            int      sub_no  = 0;

            while (subtrahends[sub_no]) {
                chars_t  subtrahend = subtrahends[sub_no];

                /* should be '== -1', unless you need to debug a failure */
                if (_test_no == -1) {
                    DEBUG_BREAK;
                }

                result = num_sub(minuend, subtrahend);

                if (0 != STRCMP_T(result.cs, correct_result)) {
                    PRINTF_T(_T("\r\n")
                             _T("Failed Test %08X: num_sub('%s', '%s')")
                             _T(" returned '%s' instead of '%s'!!"),
                             test_id,
                             minuend,
                             subtrahend,
                             result.cs,
                             correct_result);
                    DEBUG_BREAK;
                }
                freeS(&result);
                _test_no++;
                sub_no++;;
            }
            min_no++;
        }
        i++;
    }
    PRINTF_T(_T("\r\n"));
    RETURN(NIL);
} /* test_num_sub */
#endif                                                    /* NUMBER_TESTS > 0 */


/* -------------------------------------------------------------------------- */
/* Functions: Logic                                                           */


/* return value:                                                              */
/* -1 number_1_ is less than number_2_                                        */
/*  0 number_1_ is equal to number_2_                                         */
/*  1 number_1_ is greater than number_2_                                     */

PUBLIC int  num_cmp(                                                       /*F*/
    chars_t     number_1_,                                                 /*-*/
    chars_t     number_2_,                                                 /*-*/
    const bool  absolute_value_ ) {                                        /*-*/
    GO                                                            (UID(FA61A5));
    const char_t  ZERO_DIGIT = '0';

    int      i          = 0;
    chars_t  num[2]     = { NULL, NULL };
    chars_t  intgr[2]   = { 0, 0 };
    chars_t  fract[2]   = { NULL, NULL };
    bool     has_int[2] = { false, false };
    int      len[2]     = { 0, 0 };

    UNUSED(absolute_value_);

    if (number_1_ == NULL && number_2_ == NULL) {
        RETURN(0);

    } else if (number_1_ == NULL) {
        RETURN(-1);

    } else if (number_2_ == NULL) {
        RETURN(1);
    }

    num[0] = number_1_;
    num[1] = number_2_;

    /* skip all non-numeric characters and leading zeros */
    for (i = 0; i < 2; i++) {
        while (!(*num[i] == '\0')) {
            if ((IS_DIGIT(*num[i]) && *num[i] != ZERO_DIGIT) ||
                *num[i] == DECIMAL_MARK) {
                break;
            }
            num[i]++;
        }

        has_int[i] = (IS_DIGIT(*num[i]) && *num[i] != ZERO_DIGIT);
    }

    /* return 1 if operand 1 has an integer component while */
    /* operand 2 doesn't, and return -1 if vice versa       */
    if (has_int[0] && !has_int[1]) {
        RETURN(1);
    }

    if (!has_int[0] && has_int[1]) {
        RETURN(-1);
    }

    /* count number of digits in integer part */
    for (i = 0; i < 2; i++) {
        intgr[i] = NULL;

        if (has_int[i] > 0) {
            intgr[i] = num[i];
            len[i]   = 0;

            while (!(*num[i] == '\0') && *num[i] != DECIMAL_MARK) {
                if (IS_DIGIT(*num[i])) {
                    len[i]++;
                }
                num[i]++;
            }
        }
        fract[i] = num[i];
    }

    /* return -1 if operand 1 has more digits */
    /* than operand 2 or -1 if less           */
    if (len[0] > len[1]) {
        RETURN(1);
    }

    if (len[0] < len[1]) {
        RETURN(-1);
    }

    /* compare both operands if they have the same number of digits */
    if (len[0] > 0 && len[0] == len[1]) {
        num[0] = intgr[0];
        num[1] = intgr[1];

        while (!(*num[0] == '\0') || !(*num[1] == '\0')) {

            /* skip non-digit characters */
            for (i = 0; i < 2; i++) {
                while (!(*num[i] == '\0') && *num[i] != DECIMAL_MARK &&
                       !IS_DIGIT(*num[i])) {
                    num[i]++;
                }
            }

            if (IS_DIGIT(*num[0]) || IS_DIGIT(*num[1])) {
                if (*num[0] > *num[1]) {
                    RETURN(1);
                }

                if (*num[0] < *num[1]) {
                    RETURN(-1);
                }

                len[0]--;
                len[1]--;
            }

            /* move to next digit */
            for (i = 0; i < 2; i++) {
                if (!(*num[i] == '\0')) {
                    num[i]++;
                }
            }

            if (len[0] > 0 && len[1] == 0) {
                RETURN(1);
            }

            if (len[0] == 0 && len[1] > 0) {
                RETURN(-1);
            }

            if (len[0] == 0 && len[1] == 0) {
                break;
            }
        }
    }

    /* skip non-digit characters from decimal mark */
    for (i = 0; i < 2; i++) {
        num[i] = fract[i];

        while (!(*num[i] == '\0') && !IS_DIGIT(*num[i])) {
            num[i]++;
        }
    }

    /* check fractional digits */
    while (!(*num[0] == '\0') || !(*num[1] == '\0')) {

        /* skip non-digit characters */
        for (i = 0; i < 2; i++) {
            while (!(*num[i] == '\0') && !IS_DIGIT(*num[i])) {
                num[i]++;
            }
        }

        if (IS_DIGIT(*num[0]) && IS_DIGIT(*num[1])) {

            if (*num[0] > *num[1]) {
                RETURN(1);
            }

            if (*num[0] < *num[1]) {
                RETURN(-1);
            }
        } else if (IS_DIGIT(*num[0]) || IS_DIGIT(*num[1])) {

            if (*num[0] != ZERO_DIGIT && (*num[1] == '\0')) {
                RETURN(1);
            }

            if (*num[1] != ZERO_DIGIT && (*num[0] == '\0')) {
                RETURN(-1);
            }
        }

        /* move to next digit */
        for (i = 0; i < 2; i++) {
            if (!(*num[i] == '\0')) {
                num[i]++;
            }
        }
    }
    RETURN(0);
} /* num_cmp */


#if NUMBER_TESTS > 0
PUBLIC void  test_num_cmp( void ) {                                        /*F*/
    GO                                                            (UID(F46716));
    /* specify values for initial test here */
    static chars_t  NUMBER_A[] = { _T(""), NULL };
    static chars_t  NUMBER_B[] = { _T(""), NULL };

    struct _test_t {
        uint32_t  test_id;                                         /* _test_t */
        chars_t*  numbers1;                                        /* _test_t */
        chars_t*  numbers2;                                        /* _test_t */
        bool      correct_result;                                  /* _test_t */
    }
    test[] = {

#define RESULT  0
        { UID(E91558), NUMBER_A, NUMBER_B, RESULT },
#undef RESULT

        { UID(E1C060), TEST_BLANKS, TEST_BLANKS,  0 },
        { UID(E29912), TEST_BLANKS, TEST_9,      -1 },
        { UID(E30440), TEST_BLANKS, TEST_1,      -1 },
        { UID(EF6B48), TEST_BLANKS, TEST_10,     -1 },
        { UID(E3CE38), TEST_BLANKS, TEST_2,      -1 },
        { UID(E8AC81), TEST_BLANKS, TEST_0,       0 },
        { UID(E134A5), TEST_BLANKS, TEST_1P0123, -1 },
        { UID(E8F7C3), TEST_BLANKS, TEST_1P123,  -1 },
        { UID(EE096A), TEST_BLANKS, TEST_P00001, -1 },

        { UID(E0CA2C), TEST_9, TEST_BLANKS,  1 },
        { UID(E090F6), TEST_9, TEST_9,       0 },
        { UID(EC23A5), TEST_9, TEST_1,       1 },
        { UID(EBD880), TEST_9, TEST_10,     -1 },
        { UID(EF4735), TEST_9, TEST_2,       1 },
        { UID(E57F10), TEST_9, TEST_0,       1 },
        { UID(E859F8), TEST_9, TEST_1P0123,  1 },
        { UID(E8FC52), TEST_9, TEST_1P123,   1 },
        { UID(EC3EAC), TEST_9, TEST_P00001,  1 },

        { UID(E4BC6D), TEST_1, TEST_BLANKS,  1 },
        { UID(E4AD40), TEST_1, TEST_9,      -1 },
        { UID(E98E80), TEST_1, TEST_1,       0 },
        { UID(E61F5B), TEST_1, TEST_10,     -1 },
        { UID(EAF05E), TEST_1, TEST_2,      -1 },
        { UID(E85B44), TEST_1, TEST_0,       1 },
        { UID(EFFBD2), TEST_1, TEST_1P0123, -1 },
        { UID(ED29B0), TEST_1, TEST_1P123,  -1 },
        { UID(E3CAF4), TEST_1, TEST_P00001,  1 },

        { UID(E04075), TEST_10, TEST_BLANKS,  1 },
        { UID(EDEFF3), TEST_10, TEST_9,       1 },
        { UID(EABFD1), TEST_10, TEST_1,       1 },
        { UID(EEC312), TEST_10, TEST_10,      0 },
        { UID(E51194), TEST_10, TEST_2,       1 },
        { UID(EFE466), TEST_10, TEST_0,       1 },
        { UID(EE0353), TEST_10, TEST_1P0123,  1 },
        { UID(E3D307), TEST_10, TEST_1P123,   1 },
        { UID(E0C5D4), TEST_10, TEST_P00001,  1 },

        { UID(E56F91), TEST_2, TEST_BLANKS,  1 },
        { UID(EF8F06), TEST_2, TEST_9,      -1 },
        { UID(E44A18), TEST_2, TEST_1,       1 },
        { UID(E64B3F), TEST_2, TEST_10,     -1 },
        { UID(E225BC), TEST_2, TEST_2,       0 },
        { UID(E2E570), TEST_2, TEST_0,       1 },
        { UID(EB2359), TEST_2, TEST_1P0123,  1 },
        { UID(E0F7C9), TEST_2, TEST_1P123,   1 },
        { UID(ED2695), TEST_2, TEST_P00001,  1 },

        { UID(E58730), TEST_0, TEST_BLANKS,  0 },
        { UID(E56AE1), TEST_0, TEST_9,      -1 },
        { UID(E7C0B8), TEST_0, TEST_1,      -1 },
        { UID(EE2465), TEST_0, TEST_10,     -1 },
        { UID(EDB3EA), TEST_0, TEST_2,      -1 },
        { UID(E60BD2), TEST_0, TEST_0,       0 },
        { UID(E5AC7B), TEST_0, TEST_1P0123, -1 },
        { UID(ED288A), TEST_0, TEST_1P123,  -1 },
        { UID(E192BA), TEST_0, TEST_P00001, -1 },

        { UID(EA4ACE), TEST_1P0123, TEST_BLANKS,  1 },
        { UID(E91189), TEST_1P0123, TEST_9,      -1 },
        { UID(E8E060), TEST_1P0123, TEST_1,       1 },
        { UID(EA2908), TEST_1P0123, TEST_10,     -1 },
        { UID(EEDEDE), TEST_1P0123, TEST_2,      -1 },
        { UID(E9DFF8), TEST_1P0123, TEST_0,       1 },
        { UID(ECD01F), TEST_1P0123, TEST_1P0123,  0 },
        { UID(E31DA0), TEST_1P0123, TEST_1P123,  -1 },
        { UID(E2D3CC), TEST_1P0123, TEST_P00001,  1 },

        { UID(E71664), TEST_1P123, TEST_BLANKS,  1 },
        { UID(E58CBF), TEST_1P123, TEST_9,      -1 },
        { UID(E196B7), TEST_1P123, TEST_1,       1 },
        { UID(ECA216), TEST_1P123, TEST_10,     -1 },
        { UID(E04D4B), TEST_1P123, TEST_2,      -1 },
        { UID(EE7696), TEST_1P123, TEST_0,       1 },
        { UID(EC0FFD), TEST_1P123, TEST_1P0123,  1 },
        { UID(EA2704), TEST_1P123, TEST_1P123,   0 },
        { UID(ECF8BF), TEST_1P123, TEST_P00001,  1 },

        { UID(E57349), TEST_P00001, TEST_BLANKS,  1 },
        { UID(EA4375), TEST_P00001, TEST_9,      -1 },
        { UID(E310B7), TEST_P00001, TEST_1,      -1 },
        { UID(EA0798), TEST_P00001, TEST_10,     -1 },
        { UID(E0AF9C), TEST_P00001, TEST_2,      -1 },
        { UID(EC0597), TEST_P00001, TEST_0,       1 },
        { UID(E00B2D), TEST_P00001, TEST_1P0123, -1 },
        { UID(EC3E88), TEST_P00001, TEST_1P123,  -1 },
        { UID(ECEB5C), TEST_P00001, TEST_P00001,  0 },

        /* test_id == 0 terminates loop */
        { 0, NULL, NULL, false }
    };

    int  i = 0;
    while (0 != test[i].test_id) {
        const uint32_t  test_id        = test[i].test_id;
        chars_t*        numbers1       = test[i].numbers1;
        chars_t*        numbers2       = test[i].numbers2;
        const int       correct_result = test[i].correct_result;
        int             result         = INT_MIN;
        int             num1           = 0;

        while (numbers1[num1]) {
            chars_t  number1 = numbers1[num1++];
            int      num2    = 0;

            while (numbers2[num2]) {
                chars_t  number2 = numbers2[num2++];

                /* should be '== -1', unless you need to debug a failure */
                if (_test_no == -1) {
                    DEBUG_BREAK;
                }

                result = num_cmp(number1, number2, false);

                if (result != correct_result) {
                    PRINTF_T(_T("\r\n")
                             _T("Failed Test %08X: num_cmp('%s', '%s')")
                             _T(" returned %d instead of %d!!"),
                             test_id,
                             number1,
                             number2,
                             result,
                             correct_result);
                    DEBUG_BREAK;
                }
                _test_no++;
            }
        }
        i++;
    }
    RETURN(NIL);
} /* test_num_cmp */
#endif                                                    /* NUMBER_TESTS > 0 */


/* -------------------------------------------------------------------------- */
/* Functions: General Calculation Evaluation                                  */


PUBLIC new_str_t  num_eval( chars_t  expression_ ) {                       /*F*/
    GO                                                            (UID(FDD76D));
    new_str_t   ret          = S_chars(expression_);
    new_str_t   decimal      = _eval_get_system_decimal_separator();
    new_str_t   separator    = _eval_get_system_number_group_separator();
    size_t      find_pos     = 0;
    int         oper         = 0;
    const char  operators[5] = { '^', '/', '*', '+', '-' };

    _eval_remove_whitespaces_and_constants(&ret);
    _eval_simplify_negative_and_positive_signs(&ret);

    if (lengthS(ret) == 0) {
        setInS(&ret, _T("0"));
        RETURN(ret);
    }

    /* process sub-expressions in brackets  */
    /* by calling this function recursively */
    if (!_eval_subexpressions_in_brackets(&ret)) { /* mismatched brackets */
        setInS(&ret, _T("error"));
        RETURN(ret);
    }

    /* process arithmetic operators in the expression */
    oper     = 0;
    find_pos = 0;

    while (oper < 5) {
        new_str_t  op1           = { NULL };
        new_str_t  op2           = { NULL };
        new_str_t  result        = { NULL };
        size_t     left_pos      = 0;
        size_t     right_pos     = 0;
        bool       left_operand  = false;
        bool       right_operand = false;

        find_pos = findChar3S(ret, operators[oper], find_pos);

        if (find_pos == NONE) {
            find_pos = 0;
            oper++;
            continue;
        }

        /* determine the first operand and the     */
        /* leftmost position of the sub-expression */
        _eval_read_left_operand(ret.cs, find_pos, decimal, separator,
                                &left_operand, &left_pos);

        /* determine the second operand and the rightmost */
        /* character of the sub-expression                */
        _eval_read_right_operand(ret.cs, find_pos, decimal, separator,
                                 &right_operand, &right_pos);

        op1 = S_substr(ret, left_pos, find_pos - left_pos);
        op2 = S_substr(ret, find_pos + 1, right_pos - find_pos);
        find_pos++;

        /* perform the required arithmetic operation on the operands, */
        /* depending on the current operator (one of /, *, +, -)      */
        switch (operators[oper]) {

                CASE('+', result = num_add(op1.cs, op2.cs); );
                CASE('-', result = num_sub(op1.cs, op2.cs); );

            case '^':
                if (!left_operand) { /* missing operand */
                    setInS(&ret, _T("error"));
                    RETURN(ret);
                }
                /* TODO: Number_raise(op1.cs, op2.cs, 10); */
                break;

            case '/':
                if (!left_operand) { /* missing operand */
                    setInS(&ret, _T("error"));
                    RETURN(ret);
                }
                result = num_div(op1.cs, op2.cs, 10);
                break;

            case '*':
                if (!left_operand) { /* missing operand */
                    setInS(&ret, _T("error"));
                    RETURN(ret);
                }
                result = num_mul(op1.cs, op2.cs);
                break;

            default:
                WARN(_T("unknown operator"), UID(E0C2E4));
        }

        /* replace the sub-expression with the result of its evaluation */
        if (right_pos - left_pos + 1 >= 1) {
            removeInS(&ret, left_pos, right_pos - left_pos);
            insert3InS(&ret, result.cs, left_pos);
        }

        /* exit loop if only 1 unary minus is left: that's the result */
        if (*ret.cs == '-' && STRCHR_T(ret.cs + 1, '-') == NULL) {
            break;
        }
    }
    RETURN(ret);
} /* num_eval */


#if NUMBER_TESTS > 0
PUBLIC void  test_num_eval( void ) {                                       /*F*/
    GO                                                            (UID(F7402A));
    struct _test_t {
        uint32_t  test_id;                                         /* _test_t */
        chars_t   calc_expr;                                       /* _test_t */
        chars_t   correct_result;                                  /* _test_t */
    }
    test[] = {

        /* null string */
        { UID(E82BEF), NULL,          _T("0") },

        /* blank strings */
        { UID(E6CD7E), _T("   "),     _T("0") },
        { UID(E214B5), _T("  "),      _T("0") },
        { UID(E0FFAE), _T(" "),       _T("0") },
        { UID(EB3797), _T(""),        _T("0") },
        { UID(E80FD7), _T("\n"),      _T("0") },
        { UID(EAF35D), _T("\r"),      _T("0") },
        { UID(E3C800), _T("\r\n"),    _T("0") },
        { UID(E3989B), _T("\t"),      _T("0") },

        /* operators without operands */
        { UID(E9C6F6), _T("="),       _T("0") },
        { UID(EF4390), _T("= "),      _T("0") },
        { UID(EEAB37), _T(" ="),      _T("0") },
        { UID(EFD1B9), _T(" = "),     _T("0") },

        { UID(EDD5FD), _T("/"),       _T("error") },
        { UID(ED27BC), _T("/ "),      _T("error") },
        { UID(E37C85), _T(" /"),      _T("error") },
        { UID(E64F24), _T(" / "),     _T("error") },

        { UID(E159F4), _T("*"),       _T("error") },
        { UID(E101A3), _T("* "),      _T("error") },
        { UID(E6700B), _T(" *"),      _T("error") },
        { UID(EE9E04), _T(" * "),     _T("error") },

        { UID(E99081), _T("+"),       _T("0") },
        { UID(E381E8), _T("+ "),      _T("0") },
        { UID(E70F87), _T(" +"),      _T("0") },
        { UID(E00BBE), _T(" + "),     _T("0") },

        { UID(E82E43), _T("-"),       _T("0") },
        { UID(E867E7), _T("- "),      _T("0") },
        { UID(E38AFB), _T(" -"),      _T("0") },
        { UID(E4F187), _T(" - "),     _T("0") },

        /* zero strings */
        { UID(EA2F3D), _T("0"),       _T("0") },
        { UID(E62D2B), _T(" 0"),      _T("0") },
        { UID(E636FE), _T("0 "),      _T("0") },
        { UID(E78A0D), _T("-0"),      _T("0") },
        { UID(ECAD8D), _T("-0"),      _T("0") },
        { UID(EA461C), _T("0-"),      _T("0") },
        { UID(E09CE4), _T(" 0-"),     _T("0") },
        { UID(EB9A8E), _T("0 -"),     _T("0") },
        { UID(E32D4F), _T("- 0"),     _T("0") },
        { UID(ECB504), _T(" 0 "),     _T("0") },
        { UID(EEAF8B), _T("+0"),      _T("0") },
        { UID(E6C3CA), _T("0+"),      _T("0") },
        { UID(E1A741), _T("0 +"),     _T("0") },
        { UID(E55F6E), _T("+ 0"),     _T("0") },

        /* simple integer operations */
        { UID(E6FF27), _T("-1 - 1="), _T("-2")  },
        { UID(EE7D9D), _T("1+2"),     _T("3")   },
        { UID(E4CB8E), _T("11+22"),   _T("33")  },
        { UID(E61A82), _T("111+222"), _T("333") },
        { UID(EEF28E), _T("-1 + 2"),  _T("1")   },

        /* simple fractions */
        { UID(E0D8CA), _T("0.5            + 0.5"),           _T("1") },
        { UID(E497AB), _T("0.05           + 0.05"),          _T("0.1") },
        { UID(E5154A), _T("0.005          + 0.005"),         _T("0.01") },
        { UID(E60AD4), _T("0.0005         + 0.0005"),        _T("0.001") },
        { UID(E2BDE3), _T("0.00005        + 0.00005"),       _T("0.0001") },
        { UID(EB520B), _T("0.000005       + 0.000005"),      _T("0.00001") },
        { UID(E7BD37), _T("0.0000005      + 0.0000005"),     _T("0.000001") },
        { UID(E7A379), _T("0.00000005     + 0.00000005"),    _T("0.0000001") },
        { UID(EA5A4D), _T("0.000000005    + 0.000000005"),   _T("0.00000001") },
        { UID(E33400), _T("0.0000000005   + 0.0000000005"),  _T("0.000000001") },
        { UID(EF1E53), _T("0.00000000005  + 0.00000000005"), _T("0.0000000001") },

        { UID(EA72B4), _T("3.03 * 7"), _T("21.21") },

        /* brackets */
        { UID(E16E60), _T("(1.01+2.02) * 7"), _T("21.21") },

        /* test_id == 0 terminates loop */
        { 0, NULL, NULL }
    };

    int  i = 0;
    while (0 != test[i].test_id) {
        const uint32_t  test_id        = test[i].test_id;
        chars_t         calc_expr      = test[i].calc_expr;
        chars_t         correct_result = test[i].correct_result;
        new_str_t       result         = { NULL };

        /* should be '== -1', unless you need to debug a failed test */
        if (_test_no == -1) {
            DEBUG_BREAK;
        }

        result = num_eval(calc_expr);

        if (0 != STRCMP_T(result.cs, correct_result)) {
            PRINTF_T(_T("\r\n")
                     _T("Failed Test %08X: num_eval('%s')")
                     _T(" returned '%s' instead of '%s'!!"),
                     test_id, calc_expr,
                     result.cs, correct_result);
            DEBUG_BREAK;
        }

        freeS(&result);
        _test_no++;
        i++;
    }
    RETURN(NIL);
} /* test_num_eval */
#endif                                                    /* NUMBER_TESTS > 0 */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
