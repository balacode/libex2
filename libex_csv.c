/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                         [libex_csv.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_csv_.h"
#if defined INCLUDED_LIBEX_CSV_H

#include <float.h>   /* for _isnan()   */
#include <limits.h>  /* for SIZE_MAX   */
#include <stdio.h>   /* for snprintf() */
#include <string.h>  /* for memset()   */

#if 000
#include <ole2.h>
#include <oleauto.h>
#if defined _MSC_VER
#pragma comment (lib, "oleaut32.lib")
/*      SafeArrayGetElement()     */
/*      SafeArrayGetUBound()      */
/*      VariantChangeType()       */
/*      VariantTimeToSystemTime() */
#endif
#endif                                                                 /* 000 */

#include "libex_config_.h"

#include "libex_.h"
#include "libex_call_.h"
#include "libex_const_.h"
#include "libex_debug_.h"
#include "libex_error_.h"
#include "libex_macro_.h"
#include "libex_stringc_.h"
#include "libex_type_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#if defined _MSC_VER
#pragma warning (disable:4710)  /* W:L4 function not inlined                  */
#endif


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


typedef enum  _m_mode_enum {
    CSV_READER,                                                 /* _mode_enum */
    CSV_WRITER                                                  /* _mode_enum */
}
_mode_enum;                                                             /*enum*/


typedef struct  _csv_t {
    _mode_enum          mode;                                       /* _csv_t */
    chars_t             csv;                                        /* _csv_t */
    chars_t             read;                                       /* _csv_t */

    new_chars_t         mem;                                        /* _csv_t */
    size_t              writ;                                       /* _csv_t */
    size_t              alloc_cap;                                  /* _csv_t */
    csv_data_type_enum  val_type;                                   /* _csv_t */

    size_t              rows;                                       /* _csv_t */
    size_t              col_count;                                  /* _csv_t */
}
_csv_t;


/* -------------------------------------------------------------------------- */
/* Methods: Private                                                           */


#define _BASE_OBJ_WRAP_INC
#define _OBJ_HANDLE_TYPE   csv_t
#define _OBJ_INNER_TYPE    _csv_t
#define _OBJ_ALLOC_FN_UID  UID(FF2BB9)
#define _OBJ_FREE_FN_UID   UID(F11354)
#define _OBJ_CONST_FN_UID  UID(F5DD89)
#define _OBJ_FN_UID        UID(FE61CB)
#define _OBJ_WRAP_FN_UID   UID(FF9E7F)
#include "libex_object_wrapper.inc.c"


static void  _grow_salloc(                                                 /*F*/
    _csv_t*      me_,
    const size_t  addedLength_ ) {
    GO                                                            (UID(F454B5));
    /* re-allocate string if needed */
    if (me_->alloc_cap < (me_->writ + addedLength_ + 1)) {
        const size_t  new_cap =
            CAST(size_t, (CAST(double, me_->writ + addedLength_ + 1) * 1.5));

        new_chars_t  move_mem = reallocT(me_->mem, new_cap);
        ASSERT(move_mem != NULL, UID(E134AE));

        me_->alloc_cap = new_cap;
        me_->mem       = move_mem;
    }
    RETURN(NIL);
} /* _grow_salloc */


/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */


PUBLIC new_csv_t  CsvReader( chars_t  csv_string_ ) {                      /*C*/
    GO                                                            (UID(CA404E));
    /* create a new csv object */
    _csv_t*    ob  = _object_alloc();
    new_csv_t  ret = _object_wrap(ob);

    ob->mode      = CSV_READER;
    ob->col_count = SIZE_MAX;
    ob->rows      = SIZE_MAX;
    ob->csv       = csv_string_;
    ob->read      = csv_string_;
    ob->alloc_cap = KB(2);
    ob->writ      = 0;
    ob->mem       = MALLOC(ob->alloc_cap * sizeof(char_t));

    RETURN(ret);
} /* CsvReader */


PUBLIC new_csv_t  CsvWriter(                                               /*C*/
    const uint32_t  column_count_,                                         /*-*/
    const uint32_t  initial_capacity_opt_ ) {                              /*-*/
    GO                                                            (UID(CD848A));
    /* create a new csv object */
    _csv_t*    ob  = _object_alloc();
    new_csv_t  ret = _object_wrap(ob);

    const uint32_t  initial_cap =
        (initial_capacity_opt_ == 0) ? 1024 : initial_capacity_opt_;

    ob->mode      = CSV_WRITER;
    ob->col_count = column_count_;
    ob->rows      = SIZE_MAX;
    ob->csv       = NULL;
    ob->read      = NULL;
    ob->alloc_cap = initial_cap;
    ob->writ      = 0;
    ob->mem       = MALLOC(ob->alloc_cap * sizeof(char_t));

    /* TODO: ^ use column_count_ or get rid of it     */
    /* TODO: ^ update number of rows as they're added */

    RETURN(ret);
} /* CsvWriter */


/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */


PUBLIC void  freeCsv( csv_t*  object_ ) {                                  /*D*/
    GO                                                            (UID(FF039E));
    _csv_t* const  me = _object(object_, UID(E5DF8B));
    freeT(&me->mem);
    _object_free(object_);
    RETURN(NIL);
} /* freeCsv */


/* -------------------------------------------------------------------------- */
/* Properties:                                                                */


PUBLIC chars_t  charsCsv( csv_t  object_ ) {                               /*P*/
    GO                                                            (UID(F4E7A5));
    _csv_t* const  me = _object(&object_, UID(ED69A1));

    chars_t  ret = NULL;

    if (me->mode == CSV_READER) {
        ret = me->csv;

    } else if (me->mode == CSV_WRITER) {
        ret = me->mem;
    }
    RETURN(ret);
} /* charsCsv */


PUBLIC bool  isEofCsv( csv_t  object_ ) {                                  /*P*/
    GO                                                            (UID(F23602));
    _csv_t* const  me = _object(&object_, UID(E610AB));

    bool  ret = false;

    if (me->mode == CSV_READER) {
        ret = me->mem == NULL;

    } else if (me->mode == CSV_WRITER) {
        ret = true;    /* writer always returns true */
    }

    RETURN(ret);
} /* isEofCsv */


PUBLIC bool  isNewRowCsv( csv_t  object_ ) {                               /*P*/
    GO                                                            (UID(F2EB89));
    _csv_t* const  me = _object(&object_, UID(EFBDBE));

    bool  ret = false;

    if (me->mode == CSV_READER) {
        ret = me->mem != NULL && me->mem[0] == '\n';

    } else if (me->mode == CSV_WRITER) {
        ret = true;    /* writer always returns true */
    }

    RETURN(ret);
} /* isNewRowCsv */


/* -------------------------------------------------------------------------- */
/* Methods:                                                                   */


PUBLIC chars_t  readNextCsv( csv_t  object_ ) {                            /*M*/
    GO                                                            (UID(F46EA1));
    _csv_t* const  me = _object(&object_, UID(E4B351));

    chars_t  rd = me->read;
    char_t*  wr = me->mem;

    if (me->mode != CSV_READER) {
        ERR(_T("Tried to read from a writer!"), UID(ECF485));
        RETURN(NULL);
    }

    *wr = '\0';

    /* skip initial spaces and tabs */
    while (*rd == ' ' || *rd == '\t') {
        rd++;
    }

    if (*rd == CSV_CR || *rd == CSV_LF) {
        while (*rd == CSV_CR || *rd == CSV_LF) {
            rd++;
        }

        me->read = rd;

        if (*rd == '\0') {
            freeT(&me->mem);
            RETURN(NULL);
        } else {
            *wr++ = '\n';
            *wr   = '\0';
            RETURN(CSV_NEXT_ROW);
        }
    } else if (*rd == '\0') {
        freeT(&me->mem);
    }

    /* determine the data type */
    if (*rd == '\'') {
        me->val_type = CSV_TEXT;

    } else if (*rd == 'f' || *rd == 'F' || *rd == 't' || *rd == 'T') {
        me->val_type = CSV_BOOL;

    } else if ((*rd >= '0' && *rd <= '9') && rd[4] == '-' && rd[7] == '-') {
        me->val_type = CSV_DATE_TIME;

    } else if ((*rd >= '0' && *rd <= '9') || *rd == '-' || *rd == '.') {
        me->val_type = CSV_NUMBER;

    } else if (*rd == CSV_COMMA || *rd == 'n' || *rd == 'N') {
        me->val_type = CSV_NULL;
    } else {
        me->val_type = CSV_INVALID;
    }

    /* read the data and write to temporary value */
    if (me->val_type == CSV_TEXT) {
        ASSERT(*rd == CSV_QUOTE, UID(E96DD6));
        rd++;

        while (*rd != CSV_COMMA && *rd != '\0' &&
               *rd != CSV_CR && *rd != CSV_LF) {

            if (*rd == CSV_ESCAPE) {
                if (STRNCMP_T(rd, CSV_QUOTE_SUBST,
                              STRLEN_T(CSV_QUOTE_SUBST)) == 0) {

                    *wr++ = CSV_QUOTE;
                    rd += STRLEN_T(CSV_QUOTE_SUBST);
                } else if (STRNCMP_T(
                               rd, CSV_COMMA_SUBST,
                               STRLEN_T(CSV_COMMA_SUBST)) == 0) {
                    *wr++ = CSV_COMMA;
                    rd += STRLEN_T(CSV_COMMA_SUBST);

                } else if (STRNCMP_T(rd, CSV_CR_SUBST,
                                     STRLEN_T(CSV_CR_SUBST)) == 0) {
                    *wr++ = CSV_CR;
                    rd += STRLEN_T(CSV_CR_SUBST);

                } else if (STRNCMP_T(rd, CSV_LF_SUBST,
                                     STRLEN_T(CSV_LF_SUBST)) == 0) {

                    *wr++ = CSV_LF;
                    rd += STRLEN_T(CSV_LF_SUBST);
                }
            } else if (*rd == CSV_QUOTE) {
                rd++;
                break;
            } else {
                *wr++ = *rd++;
            }
        }

    } else if (me->val_type == CSV_BOOL) {
        if ((rd[0] == 't' || rd[0] == 'T') &&
            (rd[1] == 'r' || rd[1] == 'R') &&
            (rd[2] == 'u' || rd[2] == 'u') &&
            (rd[3] == 'e' || rd[3] == 'E')) {

            *wr++ = 't';
            *wr++ = 'r';
            *wr++ = 'u';
            *wr++ = 'e';
            rd += 4;
        } else if ((rd[0] == 'f' || rd[0] == 'F') &&
                   (rd[1] == 'a' || rd[1] == 'A') &&
                   (rd[2] == 'l' || rd[2] == 'L') &&
                   (rd[3] == 's' || rd[3] == 'S') &&
                   (rd[4] == 'e' || rd[4] == 'E')) {

            *wr++ = 'f';
            *wr++ = 'a';
            *wr++ = 'l';
            *wr++ = 's';
            *wr++ = 'e';
            rd += 5;
        } else {
            me->val_type = CSV_INVALID;
        }

    } else if (me->val_type == CSV_DATE_TIME) {
        if ((rd[0] >= '0' && rd[0] <= '9') &&
            (rd[1] >= '0' && rd[1] <= '9') &&
            (rd[2] >= '0' && rd[2] <= '9') &&
            (rd[3] >= '0' && rd[3] <= '9') &&
            (rd[4] == '-')                 &&
            (rd[5] >= '0' && rd[5] <= '9') &&
            (rd[6] >= '0' && rd[6] <= '9') &&
            (rd[7] == '-')                 &&
            (rd[8] >= '0' && rd[8] <= '9') &&
            (rd[9] >= '0' && rd[9] <= '9')) {

            *wr++ = rd[0];
            *wr++ = rd[1];
            *wr++ = rd[2];
            *wr++ = rd[3];
            *wr++ = rd[4];
            *wr++ = rd[5];
            *wr++ = rd[6];
            *wr++ = rd[7];
            *wr++ = rd[8];
            *wr++ = rd[9];
            rd += 10;

            if ((rd[0] == 'T' || rd[0] == ' ') &&
                (rd[1] >= '0' && rd[1] <= '9') &&
                (rd[2] >= '0' && rd[2] <= '9') &&
                (rd[3] == ':')                 &&
                (rd[4] >= '0' && rd[4] <= '9') &&
                (rd[5] >= '0' && rd[5] <= '9')) {

                *wr++ = rd[0];
                *wr++ = rd[1];
                *wr++ = rd[2];
                *wr++ = rd[3];
                *wr++ = rd[4];
                *wr++ = rd[5];
                rd += 6;

                if (rd[0] >= ':' &&
                    (rd[1] >= '0' && rd[1] <= '9') &&
                    (rd[2] >= '0' && rd[2] <= '9')) {

                    *wr++ = rd[0];
                    *wr++ = rd[1];
                    *wr++ = rd[2];
                    rd += 3;
                }
            } else {
                me->val_type = CSV_INVALID;
            }
        } else {
            me->val_type = CSV_INVALID;
        }

    } else if (me->val_type == CSV_NUMBER) {
        bool  minus   = false;
        bool  decimal = false;

        while (*rd != CSV_COMMA && *rd != '\0' &&
               *rd != CSV_CR && *rd != CSV_LF) {

            if (*rd >= '0' && *rd <= '9') {
                *wr++ = *rd++;

            } else if (*rd == '-') {
                if (minus) {
                    me->val_type = CSV_INVALID;
                    break;
                } else {
                    minus = true;
                    *wr++ = *rd++;
                }

            } else if (*rd == '.') {
                if (decimal) {
                    me->val_type = CSV_INVALID;
                    break;
                } else {
                    decimal = true;
                    *wr++ = *rd++;
                }

            } else if (*rd == CSV_COMMA) {
                break;
            }
        }

    } else if (me->val_type == CSV_NULL) {
        if ((rd[0] == 'n' || rd[0] == 'N') &&
            (rd[1] == 'u' || rd[1] == 'u') &&
            (rd[2] == 'l' || rd[2] == 'L') &&
            (rd[3] == 'l' || rd[3] == 'L')) {
            *wr++ = 'n';
            *wr++ = 'u';
            *wr++ = 'l';
            *wr++ = 'l';
        }
    }

    /* do nothing if (me->val_type == CSV_INVALID) */

    /* skip to the next delimiter */
    while (*rd != CSV_CR && *rd != CSV_LF &&
           *rd != CSV_COMMA && *rd != '\0') {
        rd++;
    }

    if (*rd == CSV_COMMA) {
        rd++;
    }

    *wr++ = '\0';
    me->read = rd;
    {
        chars_t  ret = me->mem;
        RETURN(ret);
    }
} /* readNextCsv */


#define _WRITE_STR( STR_ )           \
    {                                \
        chars_t  read_tmp = STR_;    \
        while (*read_tmp != '\0') {  \
            if (pass == 0) {         \
                calc_len++;          \
            } else {                 \
                *wr++ = *read_tmp;   \
            }                        \
            read_tmp++;              \
        }                            \
    }                            /*#*/


PUBLIC void  writeNewRowCsv( csv_t  object_ ) {                            /*M*/
    GO                                                            (UID(F5F4B2));
    _csv_t* const  me = _object(&object_, UID(F44484));

    if (me->mode != CSV_WRITER) {
        ERR(_T("Tried to write to a reader!"), UID(E3A497));
    } else {
        const size_t  len = STRLEN_T(CSV_NEXT_ROW);
        chars_t       rd  = CSV_NEXT_ROW;
        char_t*       wr  = NULL;

        /* re-allocate string if needed */
        if (me->alloc_cap < (me->writ + len + 1)) {
            _grow_salloc(me, len);
        }

        wr = me->mem + me->writ;

        while (*rd != '\0') {
            *wr++ = *rd++;
            me->writ++;
        }
    }
    RETURN(NIL);
} /* writeNewRowCsv */


PUBLIC void  writeTextCsv(                                                 /*M*/
    csv_t    object_,                                                      /*-*/
    chars_t  string_ ) {                                                   /*-*/
    GO                                                            (UID(F974AE));
    _csv_t* const  me = _object(&object_, UID(F7448D));

    uint32_t  pass     = 0;
    size_t    calc_len = 0;
    char_t*   wr       = NULL;

    if (me->mode != CSV_WRITER) {
        ERR(_T("Tried to write to a reader!"), UID(E944AB));
        RETURN(NIL);
    }

    calc_len = 3;  /* comma + quote + quote */

    for (pass = 0; pass < 2; pass++) {
        chars_t  rd = string_;

        if (pass == 1) {
            /* re-allocate string if needed */
            if (me->alloc_cap < (me->writ + calc_len + 1)) {
                _grow_salloc(me, calc_len);
            }

            wr = me->mem + me->writ;

            {
                /* write comma (if required): */
                const size_t  len = STRLEN_T(CSV_NEXT_ROW);

                if (me->writ > 0 &&
                    STRCMP_T(wr - len, CSV_NEXT_ROW) != 0) {
                    *wr++ = CSV_COMMA;
                    me->writ++;
                }
            }

            /* write opening quote */
            *wr++ = CSV_QUOTE;
            me->writ++;
        }

        while (*rd != '\0') {
            if (*rd == CSV_COMMA ||
                *rd == CSV_CR    ||
                *rd == CSV_LF    ||
                *rd == CSV_QUOTE) {

                if (pass == 0) {
                    calc_len += 6;

                } else if (*rd == CSV_COMMA) {
                    _WRITE_STR(CSV_COMMA_SUBST);

                } else if (*rd == CSV_CR) {
                    _WRITE_STR(CSV_CR_SUBST);

                } else if (*rd == CSV_LF) {
                    _WRITE_STR(CSV_LF_SUBST);

                } else if (*rd == CSV_QUOTE) {
                    _WRITE_STR(CSV_QUOTE_SUBST);
                }

                if (pass == 1) {
                    me->writ += 6;
                }
            } else {
                if (pass == 0) {
                    calc_len++;
                } else {
                    *wr++ = *rd;
                    me->writ++;
                }
            }
            rd++;
        }
    }

    /* write closing quote and '\0' */
    *wr++ = CSV_QUOTE;
    *wr = '\0';
    me->writ++;

    RETURN(NIL);
} /* writeTextCsv */


#undef _WRITE_STR


/* -------------------------------------------------------------------------- */
/* Functions: Lookup                                                          */


PUBLIC new_chars_t  csv_item(                                              /*F*/
    chars_t         csv_,                                                  /*-*/
    const uint32_t  row_no_,                                               /*-*/
    const uint32_t  column_no_ ) {                                         /*-*/
    GO                                                            (UID(FAE261));
    chars_t      rd       = csv_;
    chars_t      start    = NULL;
    size_t       row      = 0;
    size_t       col      = 0;
    bool         in_quote = false;
    new_chars_t  ret      = NULL;

    if (IS_BLANK(csv_)) {
        RETURN(NULL);
    }

    /* move pointer 'rd' to the required item */
    while (*rd != '\0' && !(row >= row_no_ && col >= column_no_)) {
        if (*rd == CSV_QUOTE) {
            in_quote = !in_quote;
        } else if (!in_quote && *rd == CSV_COMMA) {
            col++;
        } else if (!in_quote &&
                   (*rd == CSV_CR || *rd == CSV_LF)) {
            col = 0;
            row++;
        }
        rd++;
    }

    /* skip any initial spaces and tabs after a comma/newline */
    while (*rd == ' ' || *rd == '\t') {
        rd++;
    }

    start = rd;

    if (*rd == CSV_QUOTE) {
        start++;
        rd++;

        while (*rd != '\0' && *rd != CSV_CR && *rd != CSV_LF &&
               *rd != CSV_QUOTE) {
            rd++;
        }

        if (*rd != CSV_QUOTE) {
            rd = NULL;
        }
    } else {
        while (*rd != '\0' && *rd != CSV_CR && *rd != CSV_LF) {
            rd++;
        }
    }

    if ((rd - start) > 0) {
        ret = T_chars_n(start, rd - start);
    }
    RETURN(ret);
} /* csv_item */


PUBLIC new_chars_t  csv_key_value(                                         /*F*/
    chars_t  csv_,                                                         /*-*/
    chars_t  key_id_ ) {                                                   /*-*/
    GO                                                            (UID(F6A717));
    const char_t  qt_ch   = CSV_QUOTE;
    const size_t  key_len = STRLEN_T(key_id_);
    size_t        i       = 0;
    size_t        len[2]  = { 0, 0 };
    chars_t       str[2]  = { NULL, NULL };
    chars_t       rd      = csv_;
    new_chars_t   ret     = NULL;

    while (i != NONE && *rd != '\0') {
        for (i = 0; i < 2; i++) {
            if (i == 0 ||
                (i == 1 && len[0] == key_len &&
                 STRNCMP_T(str[0], key_id_, len[0]) == 0)) {

                while (*rd != qt_ch && *rd != '\n' && *rd != '\0') {
                    rd++;
                }

                str[i] = *rd != qt_ch ? NULL : ++rd;

                while (*rd != qt_ch && *rd != '\n' && *rd != '\0') {
                    rd++;
                }

                len[i] = *rd != qt_ch ? 0 : rd++ - str[i];

                if (i == 1) {
                    i = NONE;     /* exit both loops */
                    break;
                }

            } else if (i == 1) { /* scan for newline */
                while (*rd != '\n' && *rd != '\0') {
                    rd++;
                }

                if (*rd++ == '\n') {
                    str[0] = NULL;
                    continue;
                }
            }
        }
    }

    if (str[0] != NULL && str[1] != NULL && len[1] > 0) {
        ret = T_chars_n(str[1], len[1]);
    }
    RETURN(ret);
} /* csv_key_value */


/* -------------------------------------------------------------------------- */
/* Functions: Windows-specific                                                */


#if PLATFORM_WIN32 && defined __tagVARIANT

PUBLIC new_chars_t  csv_from_array(                                        /*F*/
    VARIANT_win*  variant_,                                                /*-*/
    chars_t       prepend_text_ ) {                                        /*-*/
    GO                                                            (UID(FC81EB));
    int             chars_cap    = 0;
    int             chars_in_val = 0;
    int             rows         = 0;
    int             col_count    = 0;
    int             row          = 0;
    int             col          = 0;
    long            ref[2]       = { 0 };
    chars_t         rd           = NULL;
    chars_t         read_tmp     = NULL;
    char_t*         wr           = NULL;
    new_chars_t     ret          = NULL;
    HRESULT_win     result       = 0;
    SYSTEMTIME_win  time         = { 0 };
    VARIANT_win     var;
    CLEAR(var);

    /* ESC char \0x1B is Chr$(27) in VB */

    {
        /* get number of rows: */
        long  upper_bound = 0;
        result = SafeArrayGetUBound_win(variant_->parray, 2, &upper_bound);
        if (result == 0) {
            rows = upper_bound + 1;
        }
    }

    {
        /* get number of columns: */
        long  upper_bound = 0;
        result = SafeArrayGetUBound_win(variant_->parray, 1, &upper_bound);
        if (result == 0) {
            col_count = upper_bound + 1;
        }
    }

    {
        /* allocate space for result: */
        size_t  prepend_len = 0;
        chars_cap = 128 * rows * col_count;
        if (!IS_BLANK(prepend_text_)) {
            prepend_len = lenT(prepend_text_);
            chars_cap += 2;  /* length of \r\n */
            chars_cap += prepend_len;
        }
        {
            const size_t  bytes_size = chars_cap * sizeof(char_t);
            wr = ret = MALLOC(bytes_size);
        }
        if (!IS_BLANK(prepend_text_)) {
            MEMCPY(wr, prepend_text_, prepend_len * sizeof(char_t));
            wr += prepend_len;
            MEMCPY(wr, _T("\r\n"), 2 * sizeof(char_t));
            wr += 2;  /* length of \r\n */
        }
    }

#define _WRITE( SOURCE_STRING_ )   \
    read_tmp = SOURCE_STRING_;     \
    while (*read_tmp) {            \
        *wr++ = *read_tmp++;       \
    }                          /*#*/

    for (row = 0; row < rows; row++) {
        for (col = 0; col < col_count; col++) {
            char_t*  text = NULL;

            /* write comma between column values */
            if (col > 0) {
                *wr++ = CSV_COMMA;
            }

            ref[0] = col;
            ref[1] = row;
            result = SafeArrayGetElement_win(variant_->parray, ref, &var);

            switch (var.vt) {
                case VT_EMPTY_win:
                case VT_NULL_win:
                    _WRITE(_T("null"));
                    break;

                case VT_BOOL_win:
                    if (var.boolVal == 0) {
                        _WRITE(_T("false"));
                    } else {
                        _WRITE(_T("true"));
                    }
                    break;

#if defined _MSC_VER
#pragma warning (disable:4996)  /* W:L3 'function': may be unsafe/deprecated  */
#endif
                    /* signed integers: */

                    CASE(VT_I1_win,
                         chars_in_val = SNTPRINTF(wr, 64, _T("%d"), var.cVal);
                         wr += chars_in_val;
                        );

                    CASE(VT_I2_win,
                         chars_in_val = SNTPRINTF(wr, 64, _T("%d"), var.iVal);
                         wr += chars_in_val;
                        );

                    CASE(VT_I4_win,
                         chars_in_val = SNTPRINTF(wr, 64, _T("%ld"), var.lVal);
                         wr += chars_in_val;
                        );

                    CASE(VT_INT_win,
                         chars_in_val = SNTPRINTF(wr, 64, _T("%d"), var.intVal);
                         wr += chars_in_val;
                        );

                    CASE(VT_I8_win,
                         chars_in_val =
                             SNTPRINTF(wr, 64, _T("%lld"), var.llVal);
                         wr += chars_in_val;
                        );

                    /* unsigned integers: */

                    CASE(VT_UI1_win,
                         chars_in_val = SNTPRINTF(wr, 64, _T("%u"), var.bVal);
                         wr += chars_in_val;
                        );

                    CASE(VT_UI2_win,
                         chars_in_val = SNTPRINTF(wr, 64, _T("%u"), var.uiVal);
                         wr += chars_in_val;
                        );

                    CASE(VT_UI4_win,
                         chars_in_val = SNTPRINTF(wr, 64, _T("%lu"), var.ulVal);
                         wr += chars_in_val;
                        );

                    CASE(VT_UINT_win,
                         chars_in_val =
                             SNTPRINTF(wr, 64, _T("%u"), var.uintVal);
                         wr += chars_in_val;
                        );

                    CASE(VT_UI8_win,
                         DEBUG_BREAK;
                         chars_in_val =
                             SNTPRINTF(wr, 64, _T("%llu"), var.ullVal);
                         wr += chars_in_val;
                        );

                    /* floating-point numbers: */

                    CASE(VT_R4_win,
                         chars_in_val = SNTPRINTF(wr, 64, _T("%f"), var.fltVal);
                         wr += chars_in_val;
                        );

                    CASE(VT_R8_win,
                         chars_in_val = SNTPRINTF(wr, 64, _T("%f"), var.dblVal);
                         wr += chars_in_val;
                        );

                /* currency and decimal types: */

                case VT_CY_win:
                case VT_DECIMAL_win:
                    VariantChangeType_win(&var, &var, 0, VT_BSTR);
                    text = T_bstr(var.bstrVal);
                    _WRITE(text);
                    freeT(&text);
                    break;

                case VT_DATE_win:
                    if (ISNAN(var.date)) {
                        _WRITE(_T("0000-00-00"));
                    } else {
                        if (VariantTimeToSystemTime_win(var.date, &time)
                            == FALSE_win) {

                            OS_WARN(_T("VariantTimeToSystemTime_win()"),
                                    UID(EDD597));
                            CLEAR(time);
                        }

                        /* date-only format */
                        if ((time.wHour + time.wMinute + time.wSecond) == 0) {
                            SNTPRINTF(wr, 64, _T("%04u-%02u-%02u"),
                                      time.wYear, time.wMonth, time.wDay);
                            wr += 10;
                        } else { /* date and time format */
                            SNTPRINTF(
                                wr, 64, _T("%04u-%02u-%02uT%02u:%02u:%02u"),
                                time.wYear, time.wMonth,  time.wDay,
                                time.wHour, time.wMinute, time.wSecond);
                            wr += 19;
                        }
                    }
                    break;

                case VT_BSTR_win:
                    text = T_bstr(var.bstrVal);
                    rd     = text;
                    *wr++  = CSV_QUOTE;

                    while (*rd) {
                        if (*rd == CSV_COMMA) {
                            rd++;
                            _WRITE(CSV_COMMA_SUBST);

                        } else if (*rd == CSV_CR) {
                            rd++;
                            _WRITE(CSV_CR_SUBST);

                        } else if (*rd == CSV_LF) {
                            rd++;
                            _WRITE(CSV_LF_SUBST);

                        } else if (*rd == CSV_QUOTE) {
                            rd++;
                            _WRITE(CSV_QUOTE_SUBST);
                        } else {
                            *wr++ = *rd++;
                        }
                    }
                    *wr++ = CSV_QUOTE;
                    freeT(&text);
                    break;

                    /* unhandled: VT_ARRAY_win            */
                    /* unhandled: VT_BLOB_win             */
                    /* unhandled: VT_BLOB_OBJECT_win      */
                    /* unhandled: VT_BSTR_BLOB_win        */
                    /* unhandled: VT_BYREF_win            */
                    /* unhandled: VT_CARRAY_win           */
                    /* unhandled: VT_CF_win               */
                    /* unhandled: VT_CLSID_win            */
                    /* unhandled: VT_DISPATCH_win         */
                    /* unhandled: VT_ERROR_win            */
                    /* unhandled: VT_FILETIME_win         */
                    /* unhandled: VT_HRESULT_win          */
                    /* unhandled: VT_ILLEGAL_win          */
                    /* unhandled: VT_INT_PTR_win          */
                    /* unhandled: VT_LPSTR_win            */
                    /* unhandled: VT_LPWSTR_win           */
                    /* unhandled: VT_PTR_win              */
                    /* unhandled: VT_RECORD_win           */
                    /* unhandled: VT_RESERVED_win         */
                    /* unhandled: VT_SAFEARRAY_win        */
                    /* unhandled: VT_STORAGE_win          */
                    /* unhandled: VT_STORED_OBJECT_win    */
                    /* unhandled: VT_STREAM_win           */
                    /* unhandled: VT_STREAMED_OBJECT_win  */
                    /* unhandled: VT_UINT_PTR_win         */
                    /* unhandled: VT_UNKNOWN_win          */
                    /* unhandled: VT_USERDEFINED_win      */
                    /* unhandled: VT_VARIANT_win          */
                    /* unhandled: VT_VECTOR_win           */
                    /* unhandled: VT_VERSIONED_STREAM_win */
                    /* unhandled: VT_VOID_win             */
            } /* switch (var.vt) */
        } /* for (col.. */

        _WRITE(_T("\r\n"));
    } /* for (row.. */

    *wr++ = '\0';

#undef _WRITE
    {
        const int    chars_writ = wr - ret;
        new_chars_t  shrunk     = MALLOC(chars_writ * sizeof(char_t));

        MEMCPY(shrunk, ret, chars_writ * sizeof(char_t));
        freeT(&ret);
        ret = shrunk;
    }
    RETURN(ret);
} /* csv_from_array */


#endif                                                      /* PLATFORM_WIN32 */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
