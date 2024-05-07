/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_macro.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_MACRO_H
#define      INCLUDED_LIBEX_MACRO_H

#define LX_NULL_STATEMENT   ;

/* -------------------------------------------------------------------------- */
/* Boolean Macros */

#define LX_C_BOOL( EXPRESSION_ )                                   \
    ((LX_CL lx_bool)((EXPRESSION_) ? LX_C_TRUE : LX_C_FALSE))  /*#*/

#define LX_CPP_BOOL( EXPRESSION_ )  ((EXPRESSION_) != LX_C_FALSE ? true : false)

#define LX_XOR( BOOL_1_, BOOL_2_ )                     \
    (                                                  \
            (((BOOL_1_) != 0) && ((BOOL_2_) == 0)) ||  \
            (((BOOL_1_) == 0)&&  ((BOOL_2_) != 0))     \
    )                                              /*#*/

/* -------------------------------------------------------------------------- */
/* Numeric Macros                                                             */

#define LX_KB( VALUE_ )  ((VALUE_) * 1024)
#define LX_MB( VALUE_ )  ((VALUE_) * 1048576)        /* 1024^2 */
#define LX_GB( VALUE_ )  ((VALUE_) * 1073741824)     /* 1024^3 */
#define LX_TB( VALUE_ )  ((VALUE_) * 1099511627776)  /* 1024^4 */

#define LX_ABS( VALUE_ )            ((VALUE_) < 0 ? -(VALUE_) : (VALUE_))
#define LX_EQUALS( VAL1_, VAL2_ ) (!((VAL1_) < (VAL2_)) && !((VAL1_) > (VAL2_)))
#define LX_GREATER( VAL1_, VAL2_ )  ((VAL1_) > (VAL2_) ? (VAL1_) : (VAL2_))
#define LX_LESSER( VAL1_, VAL2_ )   ((VAL1_) < (VAL2_) ? (VAL1_) : (VAL2_))
#define LX_POSITIVE( VALUE_ )       ((VALUE_) <= 0 ? 0 : (VALUE_))
#define LX_UNEQUAL( VAL1_, VAL2_ )  (((VAL1_) < (VAL2_)) || ((VAL1_) > (VAL2_)))

#define LX_ROLL_BITS_LEFT( DWORD_VAL_, COUNT_ )                       \
    ((DWORD_VAL_) >> (32 - (COUNT_)) | (DWORD_VAL_) << (COUNT_))  /*#*/

#define LX_ROLL_BITS_RIGHT( DWORD_VAL_, COUNT_ )                      \
    ((DWORD_VAL_) << (32 - (COUNT_)) | (DWORD_VAL_) >> (COUNT_))  /*#*/

#define LX_IS_SET_BIT( DWORD_VAL_, BIT_ )  (((DWORD_VAL_) >> (BIT_)) & 1)

/* -------------------------------------------------------------------------- */
/* String/Character Macros                                                    */

#define LX_HEX_DIGIT_VAL( CHAR_ )                                 \
    (((CHAR_) >= '0' && (CHAR_) <= '9') ? ((CHAR_) - '0') :       \
     ((CHAR_) >= 'a' && (CHAR_) <= 'f') ? ((CHAR_) - 'a' + 10) :  \
     ((CHAR_) >= 'A' && (CHAR_) <= 'F') ? ((CHAR_) - 'A' + 10) :  \
     (-1))                                                    /*#*/

#define LX_HEX_DIGIT( INT_0_TO_15_ )                 \
    ((INT_0_TO_15_) < 10                             \
     ? ('0' + (INT_0_TO_15_))                        \
     : (INT_0_TO_15_) >= 10 && (INT_0_TO_15_) <= 15  \
     ? ('A' + (INT_0_TO_15_)-10)                     \
     : '\0')                                     /*#*/

#define LX_IS_ALPHA( CHAR_ )                  \
    (((CHAR_) >= 'a' && (CHAR_) <= 'z') ||    \
     ((CHAR_) >= 'A' && (CHAR_) <= 'Z'))  /*#*/

#undef  LX_IS_BLANK
#define LX_IS_BLANK( STRING_ )  ((STRING_) == NULL || (STRING_)[0] == 0)

#define LX_IS_DIGIT( CHAR_ )  ((CHAR_) >= '0' && (CHAR_) <= '9')

#define LX_IS_HEX_DIGIT( CHAR_ )              \
    (((CHAR_) >= '0' && (CHAR_) <= '9') ||    \
     ((CHAR_) >= 'a' && (CHAR_) <= 'f') ||    \
     ((CHAR_) >= 'A' && (CHAR_) <= 'F'))  /*#*/

#define LX_IS_LOWER_CASE( CHAR_ )  ((CHAR_) >= 'a' && (CHAR_) <= 'z')

#define LX_IS_SPACE( CHAR_ )   \
    ((CHAR_) == ' '    ||      \
     (CHAR_) == '\a'   ||      \
     (CHAR_) == '\b'   ||      \
     (CHAR_) == '\f'   ||      \
     (CHAR_) == '\n'   ||      \
     (CHAR_) == '\r'   ||      \
     (CHAR_) == '\t'   ||      \
     (CHAR_) == '\v'  )    /*#*/

#define LX_IS_SYMBOL( CHAR_ )  \
    ((CHAR_) == '!'    ||      \
     (CHAR_) == '"'    ||      \
     (CHAR_) == '#'    ||      \
     (CHAR_) == '$'    ||      \
     (CHAR_) == '%'    ||      \
     (CHAR_) == '&'    ||      \
     (CHAR_) == '('    ||      \
     (CHAR_) == ')'    ||      \
     (CHAR_) == '*'    ||      \
     (CHAR_) == '+'    ||      \
     (CHAR_) == ','    ||      \
     (CHAR_) == '-'    ||      \
     (CHAR_) == '.'    ||      \
     (CHAR_) == '/'    ||      \
     (CHAR_) == ':'    ||      \
     (CHAR_) == ';'    ||      \
     (CHAR_) == '<'    ||      \
     (CHAR_) == '='    ||      \
     (CHAR_) == '>'    ||      \
     (CHAR_) == '?'    ||      \
     (CHAR_) == '@'    ||      \
     (CHAR_) == '['    ||      \
     (CHAR_) == '\''   ||      \
     (CHAR_) == '\\'   ||      \
     (CHAR_) == ']'    ||      \
     (CHAR_) == '^'    ||      \
     (CHAR_) == '_'    ||      \
     (CHAR_) == '\x60' ||      \
     (CHAR_) == '{'    ||      \
     (CHAR_) == '|'    ||      \
     (CHAR_) == '}'    ||      \
     (CHAR_) == '~'            \
    )                      /*#*/

#define LX_IS_UPPER_CASE( CHAR_ )  ((CHAR_) >= 'A' && (CHAR_) <= 'Z')

#define LX_STR_EQUAL( STR_1_, STR_2_ )  (STRCMP_T(STR_1_, STR_2_) == 0)

/* Variable-Size Character Macros:                 */
/* (All require char_size_ argument in their scope */

#define LX_CHAR_GET( PTR_ ) (char_size_ == 1 ? *PTR_ : *LX_CAST(wchar_t*, PTR_))

#define LX_CHAR_GET_AT( PTR_, OFFSET_ )                         \
    (                                                           \
            char_size_ == 1 ? *(PTR_ + OFFSET_) :               \
            *LX_CAST(wchar_t*, (PTR_ + OFFSET_ * char_size_))   \
    )                                                       /*#*/

#define LX_CHAR_PUT( PTR_, VALUE_ )                           \
    if (char_size_ == 1) {                                    \
        *LX_CAST(char*, PTR_) = LX_CAST(char, VALUE_);        \
    } else {                                                  \
        *LX_CAST(wchar_t*, PTR_) = LX_CAST(wchar_t, VALUE_);  \
    }                                                     /*#*/

/* -------------------------------------------------------------------------- */
/* Miscellaneous Macros: */

#define LX_CASE( CASE_VAL_, STATEMENTS_ )        \
    case CASE_VAL_: { STATEMENTS_; } break;  /*#*/

#define LX_CASE_TO_TEXT( CASE_VAL_, SET_STR_VARIABLE_ )            \
    case CASE_VAL_: SET_STR_VARIABLE_ = _T(#CASE_VAL_); break  /*#*/

#define LX_CHAR_TO_STR( STRING_, CHAR_ )  \
    lx_char_t  STRING_[2];                \
    STRING_[0] = CHAR_;                   \
    STRING_[1] = '\0'                 /*#*/

#define LX_CLEAR_CHARS( CHARS_ )  MEMSET(CHARS_, 0x00, sizeof(CHARS_))

#define LX_CLEAR_N( VARIABLE_, LENGTH_ )  MEMSET(VARIABLE_, 0x00, LENGTH_)

#define LX_CLEAR_VARIANT( VARIABLE_ )                                          \
    LX_OS_VERIFY(VariantClear_win(&VARIABLE_) == S_OK_win, LX_UID(EE838A)) /*#*/

#define LX_CLEAR( VARIABLE_ )  MEMSET(&VARIABLE_, 0x00, sizeof(VARIABLE_))

#if defined _MSC_VER
#define LX_IMPLEMENT( VARIABLE_ )  VARIABLE_
#else
#define LX_IMPLEMENT( VARIABLE_ )
#endif

#define LX_TEST_CODE( CODE_ )  CODE_

#if !defined LX_TRANSLITERATE
#define LX_TRANSLITERATE( NUMBER_, CONSTANT_, ASSIGNEE_ )  \
    {                                                      \
        if (NUMBER_ == CONSTANT_)                          \
        {   ASSIGNEE_ = _T(#CONSTANT_); }                  \
    }                                                  /*#*/
#endif

#endif                                                                   /*eof*/
