/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                  [libex_xml_reader.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_xml_reader_.h"
#if defined INCLUDED_LIBEX_XML_READER_H

#include <limits.h>
#include <stdio.h>  /* for for printf()  fclose()  fprintf_s()  _fsopen() */
#include <string.h>  /* for memset() */

#include "libex_.h"
#include "libex_array_.h"
#include "libex_bytes_.h"
#include "libex_call_.h"
#include "libex_const_.h"
#include "libex_csv_.h"
#include "libex_debug_.h"
#include "libex_error_.h"
#include "libex_file_.h"
#include "libex_macro_.h"
#include "libex_string_class_.h"
#include "libex_stringc_.h"
#include "libex_type_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif

#if defined _MSC_VER
#pragma warning (disable:4710)  /* W:L4 function not inlined                  */
#endif

/* -------------------------------------------------------------------------- */
/* Macros and Macro-like Functions                                            */

#define _CONST_CAST( CAST_, VALUE_ )  ((CAST_) VALUE_)

#define _CONST_CHARS_ASSIGN( THIS_, MEMBER_VAR_, ASSIGN_CHARS_NEW_ )  \
    {                                                                 \
        _xmlr_t*  _object = _CONST_CAST(_xmlr_t*, THIS_);             \
        freeT(&_object->MEMBER_VAR_);                                 \
        _object->MEMBER_VAR_ = ASSIGN_CHARS_NEW_;                     \
    }                                                             /*#*/

#define _CONST_CHARS_COPY( RET_STR_PTR_, COPY_CHARS_FROM_ )             \
    set_inT(_CONST_CAST(char_t**, RET_STR_PTR_), COPY_CHARS_FROM_)  /*#*/

#define _RETURN_IF_NO_CONTENT( VALUE_ )                              \
    if (me->err_code != ERR_NONE || Array_count(me->tokens) == 0)    \
    {       RETURN(VALUE_); }                                    /*#*/

#define _TOKEN( INDEX_ )                                 \
    CAST(const XmlrToken*, Array_getItemAt(              \
            &(CAST(_xmlr_t*, me)->tokens), INDEX_))  /*#*/

#define _TOKEN_LOOP                              \
    size_t        i     = me->pos;               \
    const size_t  depth = _TOKEN(i)->depth + 1;  \
    do                                           \
    {   i++; }                                   \
    while (i < Array_count(me->tokens)      &&   \
           _TOKEN(i)->type != XML_START_TAG &&   \
           _TOKEN(i)->type != XML_EMPTY_TAG);    \
    while (i < Array_count(me->tokens) &&        \
           _TOKEN(i)->depth >= depth)        /*#*/

#define _WRITE_STR( STR_ )          \
    {                               \
        chars_t  read_tmp = STR_;   \
        while (*read_tmp != '\0')   \
        {                           \
            if (pass == 0) {        \
                calc_len++;         \
            } else {                \
                *wr++ = *read_tmp;  \
            }                       \
            read_tmp++;             \
        }                           \
    }                           /*#*/


static bool  _is_attribute( const XmlrToken*  token_ ) {                   /*F*/
    return  token_->type == XML_ATTR_NAME || token_->type == XML_ATTR_VAL;
} /* _is_attribute */


static bool  _is_type(                                                     /*F*/
    const XmlrToken*    token_,                                            /*-*/
    Xmlr_TokenTypeEnum  type_,                                             /*-*/
    chars_t             name_ ) {                                          /*-*/
    return token_->type == type_ &&
           (name_ == NULL || equals2T(token_->value, name_));
} /* _is_type */


static bool  _is_attribute_name(                                           /*F*/
    const XmlrToken*  token_,                                              /*-*/
    chars_t           name_ ) {                                            /*-*/
    return _is_type(token_, XML_ATTR_NAME, name_);
} /* _is_attribute_name */


static bool  _is_attribute_value( const XmlrToken*  token_ ) {             /*F*/
    return _is_type(token_, XML_ATTR_VAL, NULL);
} /* _is_attribute_value */


static bool  _is_comment_end_tag( const XmlrToken*  token_ ) {             /*F*/
    return _is_type(token_, XML_COMMENT_END_TAG, NULL);
} /* _is_comment_end_tag */


static bool  _is_empty_tag(                                                /*F*/
    const XmlrToken*  token_,                                              /*-*/
    chars_t           name_opt_ ) {                                        /*-*/
    return _is_type(token_, XML_EMPTY_TAG, name_opt_);
} /* _is_empty_tag */


static bool  _is_end_tag(                                                  /*F*/
    const XmlrToken*  token_,                                              /*-*/
    chars_t           name_opt_ ) {                                        /*-*/
    return _is_type(token_, XML_END_TAG, name_opt_);
} /* _is_end_tag */


static bool  _is_start_tag(                                                /*F*/
    const XmlrToken*  token_,                                              /*-*/
    chars_t           name_opt_ ) {                                        /*-*/
    return _is_type(token_, XML_START_TAG, name_opt_);
} /* _is_start_tag */


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


typedef enum  _m_parse_mode_enum {
    PARSE_TAG_NAME,                                       /* _parse_mode_enum */
    PARSE_EMPTY_TAG,                                      /* _parse_mode_enum */
    PARSE_CLOSE_TAG,                                      /* _parse_mode_enum */
    PARSE_ATTR_NAME,                                      /* _parse_mode_enum */
    PARSE_ATTR_EQUAL,                                     /* _parse_mode_enum */
    PARSE_ATTR_QUOTE,                                     /* _parse_mode_enum */
    PARSE_ATTR_DOUBLE_QUOTE,                              /* _parse_mode_enum */
    PARSE_TEXT,                                           /* _parse_mode_enum */
    PARSE_COMMENT                                         /* _parse_mode_enum */
}
_parse_mode_enum;                                                       /*enum*/


typedef struct  _xmlr_t {
    size_t               pos;                                      /* _xmlr_t */
    array_t              tokens;                                   /* _xmlr_t */

    size_t               err_column;                               /* _xmlr_t */
    size_t               err_line;                                 /* _xmlr_t */
    Xmlr_ParseErrorEnum  err_code;                                 /* _xmlr_t */

    new_chars_t          attr_by_index_ret;                        /* _xmlr_t */
    new_chars_t          attr_by_name_ret;                         /* _xmlr_t */
    new_chars_t          attr_name_ret;                            /* _xmlr_t */
    new_chars_t          child_content_ret;                        /* _xmlr_t */
    new_chars_t          content_ret;                              /* _xmlr_t */
    new_chars_t          debug_info_ret;                           /* _xmlr_t */
    new_chars_t          doctype_tag_ret;                          /* _xmlr_t */
    new_chars_t          error_report_ret;                         /* _xmlr_t */
    new_chars_t          tag_text_ret;                             /* _xmlr_t */
    new_chars_t          xml_ret;                                  /* _xmlr_t */
}
_xmlr_t;  /*struct*/


typedef struct  _search_t {
    new_chars_t  parsed;                                         /* _search_t */
    chars_t      tag_name;                                       /* _search_t */
    chars_t      attr_name[2];                                   /* _search_t */
    chars_t      attr_value[2];                                  /* _search_t */
}
_search_t;  /*struct*/


/* -------------------------------------------------------------------------- */
/* Functions: Private                                                         */


#define _BASE_OBJ_WRAP_INC
#define _OBJ_HANDLE_TYPE   Xmlr
#define _OBJ_INNER_TYPE    _xmlr_t
#define _OBJ_ALLOC_FN_UID  UID(F090A0)
#define _OBJ_FREE_FN_UID   UID(F9032B)
#define _OBJ_CONST_FN_UID  UID(F6D9F1)
#define _OBJ_FN_UID        UID(F6BEC9)
#define _OBJ_WRAP_FN_UID   UID(F97410)
#include "libex_object_wrapper.inc.c"


static void  _add_token(                                                   /*F*/
    _xmlr_t*            me_,                                               /*-*/
    Xmlr_TokenTypeEnum  type_,                                             /*-*/
    str_t               token_ ) {                                         /*-*/
    GO                                                            (UID(F76E1D));
    XmlrToken  token;
    CLEAR(token);
    token.type  = type_;
    token.depth = 0;  /* <- calculated after tokens are added */
    token.value = T_chars(token_.cs);
    Array_addItem(&me_->tokens, &token, sizeof(token), NULL);
    RETURN(NIL);
} /* _add_token */


static  _search_t  _parse_search_expr( chars_t  search_expr_ ) {           /*F*/
    GO                                                            (UID(F0A4AF));
    _search_t  ret;
    CLEAR(ret);

    if (!IS_BLANK(search_expr_)) {
        char_t*  str = ret.parsed = T_chars(search_expr_);
        int      i   = 0;

        /* get the tag name (delimit it with \0) */
        ret.tag_name = str;

        while (!IS_SPACE(*str) && *str != '\0') {
            str++;
        }

        if (*str != '\0') {
            *str++ = '\0';
        }

        /* skip whitespaces */
        while (*str != '\0' && IS_SPACE(*str)) {
            str++;
        }

        for (i = 0; i < 2; i++) {
            /* get name of attribute */
            if (*str != '\0') {
                ret.attr_name[i] = str;
                while (*str != '\0' && !IS_SPACE(*str) && *str != '=') {
                    str++;
                }
                *str = '\0';
            }

            /* skip whitespaces */
            while (*str != '\0' && IS_SPACE(*str)) {
                str++;
            }

            if (*str != '\0' && *str == '=') {
                while (*str != '\0' && *str == '=') { /* skip '=' */
                    str++;
                }

                /* skip whitespaces */
                while (*str != '\0' && IS_SPACE(*str)) {
                    str++;
                }

                {
                    const int  quote = *str == '"'  ? '"'  :
                                       *str == '\'' ? '\'' :
                                       *str == '\0' ? '\0' :
                                       ' ';

                    if (quote != '\0') {
                        ret.attr_value[i] = ++str;

                        while (*str != '\0' && *str != quote) {
                            str++;
                        }

                        if (*str != '\0') {
                            *str++ = '\0';
                        }
                    }
                }
            }
        }
    }
    RETURN(ret);
} /* _parse_search_expr */


/* search_expr_: tagName attribute_name='value' attribute_name="value" ...    */
static bool  _matching(                                                    /*F*/
    const _xmlr_t*  me_,                                                   /*-*/
    const size_t    tag_index_,                                            /*-*/
    chars_t         search_expr_ ) {                                       /*-*/
    GO                                                            (UID(F14CDF));
    const _xmlr_t* const  me = me_;  /* used by _TOKEN */

    _search_t     exp         = _parse_search_expr(search_expr_);
    size_t        i           = tag_index_;
    const size_t  token_count = Array_count(me_->tokens);
    bool          match1      = false;
    bool          match2      = false;
    bool          ret         = false;

    const XmlrToken*  token = _TOKEN(i);  /* mutable */

    if ((token->type != XML_START_TAG &&
         token->type != XML_EMPTY_TAG) ||
        (!IS_BLANK(exp.tag_name) &&
         !equals2T(token->value, exp.tag_name))) {
        ret = false;

    } else if (IS_BLANK(exp.attr_name[0])  &&
               IS_BLANK(exp.attr_value[0]) &&
               IS_BLANK(exp.attr_name[1])  &&
               IS_BLANK(exp.attr_value[1])) {
        ret = true;

    } else {
        for (i = tag_index_ + 1;
             i < token_count && (!match1 || !match2);
             i++) {
            token = _TOKEN(i);

            if (token->type == XML_ATTR_NAME) {
                continue;

            } else if (token->type == XML_ATTR_VAL) {

                if ((IS_BLANK(exp.attr_name[0]) ||
                     equals2T(_TOKEN(i - 1)->value, exp.attr_name[0])) &&
                    (IS_BLANK(exp.attr_value[0]) ||
                     equals2T(token->value, exp.attr_value[0]))) {
                    match1 = true;
                }

                if ((IS_BLANK(exp.attr_name[1]) ||
                     equals2T(_TOKEN(i - 1)->value, exp.attr_name[1])) &&
                    (IS_BLANK(exp.attr_value[1]) ||
                     equals2T(token->value, exp.attr_value[1]))) {
                    match2 = true;
                }
            } else {
                break;
            }

            ret = (match1 && match2);
        }
    }
    RETURN(ret);
} /* _matching */


static void  _remove_all_tokens( _xmlr_t*  me_ ) {                         /*F*/
    GO                                                            (UID(F7AC5A));
    size_t        i           = 0;
    const size_t  token_count = Array_count(me_->tokens);

    for (i = 0; i < token_count; i++) {
        XmlrToken* const  token =
            CAST(XmlrToken*, Array_getItemAt(&me_->tokens, i));
        freeT(&token->value);
    }

    if (token_count > 0) {
        Array_removeItems(&me_->tokens);
    }
    RETURN(NIL);
} /* _remove_all_tokens */


static size_t  _adjacent_index(                                            /*F*/
    const _xmlr_t*  me_,                                                   /*-*/
    const size_t    tag_index_,                                            /*-*/
    const bool      next_tag_,                                             /*-*/
    chars_t         search_expr_ ) {                                       /*-*/
    GO                                                            (UID(FE927F));
    const _xmlr_t* const  me = me_;  /* used by _TOKEN */

    size_t        i     = tag_index_;
    const size_t  depth = _TOKEN(tag_index_)->depth;

    if (depth == 1     ||
        tag_index_ < 1 ||
        tag_index_ >= (Array_count(me_->tokens) - 1)) {
        RETURN(NONE);
    }

    while (_TOKEN(i)->depth >= depth) {
        if (next_tag_) {
            i++;
        } else {
            i--;
        }

        if (_TOKEN(i)->depth == depth &&
            _matching(me_, i, search_expr_)) {
            RETURN(i);
        }
    }
    RETURN(NONE);
} /* _adjacent_index */


static new_chars_t  _xml_text(                                             /*F*/
    const _xmlr_t*  me_,                                                   /*-*/
    const size_t    tag_index_,                                            /*-*/
    const bool      current_tag_only_,                                     /*-*/
    const bool      indented_ ) {                                          /*-*/
    GO                                                            (UID(F42249));
    const _xmlr_t* const  me = me_;  /* used by _TOKEN */

    int          pass           = 0;
    size_t       i              = 0;
    size_t       calc_len       = 0;  /* TODO: calc_len not set anywhere */
    size_t       curr_depth     = 0;
    size_t       nesting_spaces = 0;
    size_t       prev_depth     = 0;
    size_t       token_count    = Array_count(me->tokens);
    bool         empty_tag      = false;
    char_t*      wr             = NULL;
    new_chars_t  ret            = NULL;

    _RETURN_IF_NO_CONTENT(ret);

    curr_depth = _TOKEN(tag_index_)->depth;

    {
        const XmlrToken* const  token = _TOKEN(me->pos);

        if (token->type == XML_ATTR_VAL        ||
            token->type == XML_COMMENT_END_TAG ||
            token->type == XML_COMMENT_TEXT    ||
            token->type == XML_END_TAG         ||
            token->type == XML_TEXT) {
            token_count = tag_index_ + 1;

        } else if (token->type == XML_ATTR_NAME) {
            token_count = tag_index_ + 2;
        }

        /* XML_COMMENT_START_TAG */
        /* XML_EMPTY_TAG         */
        /* XML_START_TAG         */
    }

    for (pass = 0; pass < 2; pass++) {
        if (pass == 1) {
            wr = ret = mallocT(calc_len + 1);
            ASSERT(ret != NULL, UID(EDE802));
        }

        for (i = tag_index_; i < token_count; i++) {
            const XmlrToken* const  token = _TOKEN(i);

            if (token->depth < curr_depth) {
                break;
            }

            if (indented_ && token->depth != prev_depth) {
                size_t  b = 0;

                nesting_spaces = 0;

                for (b = 0; b < token->depth; b++) {
                    nesting_spaces++;
                }

                prev_depth = token->depth;
            }

            if (token->type == XML_START_TAG ||
                token->type == XML_EMPTY_TAG ||
                token->type == XML_ATTR_VAL) {

                if (token->type == XML_START_TAG) {
                    empty_tag = false;

                } else if (token->type == XML_EMPTY_TAG) {
                    empty_tag = true;
                }

                /* write tag or attribute name */
                if (token->type == XML_ATTR_VAL) {
                    _WRITE_STR(_T("\""));
                    _WRITE_STR(token->value);
                    _WRITE_STR(_T("\""));
                } else {
                    if (nesting_spaces > 0) {
                        _WRITE_STR(_T("\r\n"));
                    }

                    while (nesting_spaces > 0) {
                        nesting_spaces--;
                        _WRITE_STR(_T("  "));
                    }

                    _WRITE_STR(_T("<"));
                    _WRITE_STR(token->value);
                }

                if (i == (token_count - 1) ||
                    _TOKEN(i + 1)->type != XML_ATTR_NAME) {
                    if (empty_tag) {
                        _WRITE_STR(_T(" /"));
                    }

                    _WRITE_STR(_T(">"));

                    if (current_tag_only_) {
                        break;
                    }
                }

            } else if (token->type == XML_ATTR_NAME) {
                _WRITE_STR(_T(" "));
                _WRITE_STR(token->value);
                _WRITE_STR(_T("="));

            } else if (token->type == XML_TEXT) {
                if (contains2T(token->value, _T("&"))) {
                    new_chars_t  decoded = from_xml(token->value);
                    _WRITE_STR(decoded);
                    freeT(&decoded);
                } else {
                    _WRITE_STR(token->value);
                }

            } else if (token->type == XML_COMMENT_START_TAG) {
                _WRITE_STR(_T("<!--"));

            } else if (token->type == XML_COMMENT_TEXT) {
                _WRITE_STR(token->value);

            } else if (token->type == XML_COMMENT_END_TAG) {
                _WRITE_STR(_T("-->"));

            } else if (token->type == XML_END_TAG) {
                if (i > 0 && _TOKEN(i - 1)->type == XML_TEXT) {
                    _WRITE_STR(_T("</"));
                    _WRITE_STR(token->value);
                    _WRITE_STR(_T(">"));
                } else {
                    if (nesting_spaces > 0) {
                        _WRITE_STR(_T("\r\n"));
                    }

                    while (nesting_spaces > 0) {
                        nesting_spaces--;
                        _WRITE_STR(_T("  "));
                    }

                    _WRITE_STR(_T("</"));
                    _WRITE_STR(token->value);
                    _WRITE_STR(_T(">"));
                }

                if (current_tag_only_) {
                    break;
                }
            }
        }
        _WRITE_STR(_T("\0"));
    }
    RETURN(ret);
} /* _xml_text */


/* -------------------------------------------------------------------------- */
/* Constructors:                                                              */


PUBLIC new_Xmlr  Xmlr_init( void ) {                                       /*C*/
    GO                                                            (UID(C585B2));
    _xmlr_t*  ob  = _object_alloc();
    new_Xmlr  ret = _object_wrap(ob);

    ob->tokens = Array_init(sizeof(XmlrToken), 1024, 0);

    ob->pos               = 0;
    ob->err_code          = ERR_NONE;
    ob->err_column        = 0;
    ob->err_line          = 0;
    ob->attr_by_index_ret = NULL;
    ob->attr_by_name_ret  = NULL;
    ob->attr_name_ret     = NULL;
    ob->child_content_ret = NULL;
    ob->content_ret       = NULL;
    ob->debug_info_ret    = NULL;
    ob->doctype_tag_ret   = NULL;
    ob->error_report_ret  = NULL;
    ob->tag_text_ret      = NULL;
    ob->xml_ret           = NULL;

    RETURN(ret);
} /* Xmlr_init */


PUBLIC new_Xmlr  Xmlr_of_chars( chars_t  xml_ ) {                          /*C*/
    GO                                                            (UID(CCB5CE));
    new_Xmlr  ret = Xmlr_init();
    Xmlr_parse(ret, xml_);
    RETURN(ret);
} /* Xmlr_of_chars */


/* Constructs a new object and parses the given XML file.                     */
PUBLIC new_Xmlr  Xmlr_of_file( chars_t  filename_ ) {                      /*C*/
    GO                                                            (UID(CADEE0));
    new_Xmlr  ret  = Xmlr_init();
    new_chars_t    xml  = NULL;
    new_bytes_t    data = file_load_bytes(filename_);

    xml = Tutf8(CAST(const char*, data.data));
    Bytes_free(&data);
    Xmlr_parse(ret, xml);

    RETURN(ret);
} /* Xmlr_of_file */


#if 000   /* Uncomment when the copy constructor is implemented: */
PUBLIC new_Xmlr  Xmlr_copy( const Xmlr  copy_from_ )                       /*C*/
_CTOR_INIT {
    GO                                                            (UID(C8D118));
    me->tokens            (copy_from_->tokens);
    me->pos               (copy_from_->pos);

    me->err_code          (copy_from_->err_code);
    me->err_column        (copy_from_->err_column);
    me->err_line          (copy_from_->err_line);

    me->attr_by_index_ret (copy_from_->attr_by_index_ret);
    me->attr_by_name_ret  (copy_from_->attr_by_name_ret);
    me->attr_name_ret     (copy_from_->attr_name_ret);
    me->child_content_ret (copy_from_->child_content_ret);
    me->content_ret       (copy_from_->content_ret);
    me->debug_info_ret    (copy_from_->debug_info_ret);
    me->doctype_tag_ret   (copy_from_->doctype_tag_ret);
    me->error_report_ret  (copy_from_->error_report_ret);
    me->tag_text_ret      (copy_from_->tag_text_ret);
    me->xml_ret           (copy_from_->xml_ret);

    WARN(_T("XmlData: call to unimplemented copy constructor!"),
    UID(E8FDBC));

    RETURN(NIL);
} /* Xmlr_copy */
#endif                                                                 /* 000 */


/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */


PUBLIC void  freeXmlr( Xmlr*  object_ ) {                                  /*D*/
    GO                                                            (UID(D122D1));
    _xmlr_t* const  me = _object(object_, UID(E2B2D8));

    _remove_all_tokens(me);
    Array_free(&me->tokens);

    /* free all temporary strings */
    freeT(&me->attr_by_index_ret);
    freeT(&me->attr_by_name_ret);
    freeT(&me->attr_name_ret);
    freeT(&me->child_content_ret);
    freeT(&me->content_ret);
    freeT(&me->debug_info_ret);
    freeT(&me->doctype_tag_ret);
    freeT(&me->error_report_ret);
    freeT(&me->tag_text_ret);
    freeT(&me->xml_ret);

    _object_free(object_);

    RETURN(NIL);

} /* freeXmlr */


/* -------------------------------------------------------------------------- */
/* Properties: Metadata                                                       */


PUBLIC chars_t  Xmlr_doctypeTag( const Xmlr  object_ ) {                   /*P*/
    GO                                                            (UID(F81BAF));
    const _xmlr_t* const  me = _object_const(&object_, UID(E909B9));
    RETURN(me->doctype_tag_ret);
} /* Xmlr_doctypeTag */


/* -------------------------------------------------------------------------- */
/* Properties: Token Querying                                                 */


#define _XML_IS_TYPE( METHOD_, CONSTANT_, SOURCE_UID_, ERROR_ID_ )      \
    PUBLIC bool  METHOD_( const Xmlr  object_ )                         \
    {                                                                   \
        GO  (SOURCE_UID_);                                              \
        const _xmlr_t* const  me = _object_const(&object_, ERROR_ID_);  \
        bool  ret = false;                                              \
        _RETURN_IF_NO_CONTENT(false);                                   \
        ret = (_TOKEN(me->pos)->type == CONSTANT_);                     \
        RETURN(ret);                                                    \
    }                                                               /*#*/

_XML_IS_TYPE(Xmlr_isAttributeValue, XML_ATTR_VAL,
             UID(FCD715), UID(EB481C))

_XML_IS_TYPE(Xmlr_isCommentEndTag, XML_COMMENT_END_TAG,
             UID(FA0AAA), UID(EDE4B2))

_XML_IS_TYPE(Xmlr_isCommentStartTag, XML_COMMENT_START_TAG,
             UID(F6CA69), UID(EF8569))

_XML_IS_TYPE(Xmlr_isCommentText, XML_COMMENT_TEXT,
             UID(FDD2EC), UID(E3E439))

_XML_IS_TYPE(Xmlr_isText, XML_TEXT,
             UID(F0B2E1), UID(E581E5))

#define _XML_IS_TYPE_AND_NAME( METHOD_, CONSTANT_, SOURCE_UID_, ERROR_ID_ )  \
    PUBLIC bool  METHOD_(const Xmlr  object_,                                \
                         chars_t     name_opt_)                              \
    {                                                                        \
        GO  (SOURCE_UID_);                                                   \
        const _xmlr_t* const  me = _object_const(&object_, ERROR_ID_);       \
        _RETURN_IF_NO_CONTENT(false);                                        \
        {                                                                    \
            const XmlrToken* const  token = _TOKEN(me->pos);                 \
            const bool  ret = (token->type == CONSTANT_) &&                  \
                              (name_opt_ == NULL ||                          \
                               equals_icT(token->value, name_opt_));         \
            RETURN(ret);                                                     \
        }                                                                    \
    }                                                                    /*#*/

_XML_IS_TYPE_AND_NAME(Xmlr_isAttributeName, XML_ATTR_NAME,
                      UID(F29B2F), UID(E9A883))

_XML_IS_TYPE_AND_NAME(Xmlr_isEmptyTag, XML_EMPTY_TAG,
                      UID(F35C4C), UID(E23D27))

_XML_IS_TYPE_AND_NAME(Xmlr_isEndTag, XML_END_TAG,
                      UID(FD0CC5), UID(E9B372))

_XML_IS_TYPE_AND_NAME(Xmlr_isStartTag, XML_START_TAG,
                      UID(FFD962), UID(E64D68))


#undef _XML_IS_TYPE
#undef _XML_IS_TYPE_AND_NAME


PUBLIC uint32_t  Xmlr_tokenDepth( const Xmlr  object_ ) {                  /*P*/
    GO                                                            (UID(F63F87));
    const _xmlr_t* const  me = _object_const(&object_, UID(E1B576));
    _RETURN_IF_NO_CONTENT(0);
    {
        const XmlrToken* const  token = _TOKEN(me->pos);
        const uint32_t          ret   = token->depth;
        RETURN(ret);
    }
} /* Xmlr_tokenDepth */


PUBLIC Xmlr_TokenTypeEnum  Xmlr_tokenType(                                 /*P*/
    const Xmlr  object_ ) {                                                /*-*/
    GO                                                            (UID(F7B139));
    const _xmlr_t* const  me = _object_const(&object_, UID(E3F110));
    _RETURN_IF_NO_CONTENT(0);
    {
        const XmlrToken* const    token = _TOKEN(me->pos);
        const Xmlr_TokenTypeEnum  ret   = token->type;
        RETURN(ret);
    }
} /* Xmlr_tokenType */


PUBLIC chars_t  Xmlr_tokenValue( const Xmlr  object_ ) {                   /*P*/
    GO                                                            (UID(F1E563));
    const _xmlr_t* const  me = _object_const(&object_, UID(EBE3D3));
    _RETURN_IF_NO_CONTENT(BLANK);
    {
        const XmlrToken* const  token = _TOKEN(me->pos);
        chars_t                 ret   = token->value;
        RETURN(ret);
    }
} /* Xmlr_tokenValue */


/* -------------------------------------------------------------------------- */
/* Properties: Token Class Querying                                           */


PUBLIC bool  Xmlr_isComment( const Xmlr  object_ ) {                       /*P*/
    GO                                                            (UID(F7EC69));
    const _xmlr_t* const  me = _object_const(&object_, UID(E3F174));

    _RETURN_IF_NO_CONTENT(false);
    {
        Xmlr_TokenTypeEnum  type = _TOKEN(me->pos)->type;
        const bool  ret = (type == XML_COMMENT_START_TAG ||
                           type == XML_COMMENT_TEXT      ||
                           type == XML_COMMENT_END_TAG);
        RETURN(ret);
    }
} /* Xmlr_isComment */


/* -------------------------------------------------------------------------- */
/* Properties:                                                                */


PUBLIC chars_t  Xmlr_attr(                                                 /*P*/
    const Xmlr  object_,                                                   /*-*/
    chars_t     attr_name_ ) {                                             /*-*/
    GO                                                            (UID(F2F0EE));
    const _xmlr_t* const  me = _object_const(&object_, UID(EC9595));

    size_t        i           = 0;
    const size_t  token_count = Array_count(me->tokens);

    _CONST_CHARS_COPY(&me->attr_by_name_ret, BLANK);

    _RETURN_IF_NO_CONTENT(me->attr_by_name_ret);

    for (i = me->pos + 1; i < token_count; i++) {
        const XmlrToken*  token = _TOKEN(i);  /* mutable */

        if (_is_attribute_name(token, attr_name_)) {
            token = _TOKEN(++i);
            _CONST_CHARS_COPY(&me->attr_by_name_ret, token->value);
            break;

        } else if (token->type != XML_ATTR_NAME &&
                   token->type != XML_ATTR_VAL) {
            break;
        }
    }
    RETURN(me->attr_by_name_ret);
} /* Xmlr_attr */


PUBLIC chars_t  Xmlr_attrByIndex(                                          /*P*/
    const Xmlr    object_,                                                 /*-*/
    const size_t  attr_index_ ) {                                          /*-*/
    GO                                                            (UID(F59CE3));
    const _xmlr_t* const  me = _object_const(&object_, UID(E21316));

    int     index = -1;  /* leave as int, has to be -1 */
    size_t  i     = 0;

    _CONST_CHARS_COPY(&me->attr_by_index_ret, BLANK);

    _RETURN_IF_NO_CONTENT(me->attr_by_index_ret);

    for (i = me->pos + 1;
         i < Array_count(me->tokens) &&
         (_TOKEN(i)->type == XML_ATTR_NAME ||
          _TOKEN(i)->type == XML_ATTR_VAL);
         i++) {

        if (_is_attribute_name(_TOKEN(i), NULL)) {
            index++;

        } else if (_is_attribute_value(_TOKEN(i)) &&
                   CAST(size_t, index) == attr_index_) {

            _CONST_CHARS_COPY(&me->attr_by_index_ret, _TOKEN(i)->value);
            break;
        }
    }
    RETURN(me->attr_by_index_ret);
} /* Xmlr_attrByIndex */


PUBLIC size_t  Xmlr_attrCount( const Xmlr  object_ ) {                     /*P*/
    GO                                                            (UID(F25AAA));
    const _xmlr_t* const  me = _object_const(&object_, UID(E3C925));
    _RETURN_IF_NO_CONTENT(0);
    {
        size_t        i           = me->pos + 1;
        const size_t  token_count = Array_count(me->tokens);
        size_t        ret         = 0;

        while (i < token_count && _is_attribute(_TOKEN(i))) {
            if (_TOKEN(i)->type == XML_ATTR_NAME) {
                ret++;
            }
            i++;
        }
        RETURN(ret);
    }
} /* AttrCount */


PUBLIC bool  Xmlr_attrExists(                                              /*P*/
    const Xmlr  object_,                                                   /*-*/
    chars_t     name_ ) {                                                  /*-*/
    GO                                                            (UID(F6A8A3));
    const _xmlr_t* const  me = _object_const(&object_, UID(E5654F));
    _RETURN_IF_NO_CONTENT(false);
    {
        size_t        i           = me->pos + 1;
        const size_t  token_count = Array_count(me->tokens);
        bool          ret         = false;

        while (i < token_count && _is_attribute(_TOKEN(i))) {
            chars_t  token_value = _TOKEN(i)->value;

            if (_TOKEN(i)->type == XML_ATTR_NAME &&
                equals2T(token_value, name_)) {
                ret = true;
                break;
            }
            i++;
        }
        RETURN(ret);
    }
} /* Xmlr_attrExists */


PUBLIC chars_t  Xmlr_attrName(                                             /*P*/
    const Xmlr    object_,                                                 /*-*/
    const size_t  index_ ) {                                               /*-*/
    GO                                                            (UID(F89EAD));
    const _xmlr_t* const  me = _object_const(&object_, UID(E1A447));

    _CONST_CHARS_COPY(&me->attr_name_ret, BLANK);

    _RETURN_IF_NO_CONTENT(me->attr_name_ret);
    {
        size_t        i           = me->pos + 1;
        size_t        index       = 0;
        const size_t  token_count = Array_count(me->tokens);

        while (i < token_count && _is_attribute(_TOKEN(i))) {
            if (_TOKEN(i)->type == XML_ATTR_NAME) {
                if (index == index_) {
                    _CONST_CHARS_COPY(
                        &me->attr_name_ret, _TOKEN(i)->value);
                    break;
                }
                index++;
            }
            i++;
        }
    }
    RETURN(me->attr_name_ret);
} /* Xmlr_attrName */


PUBLIC new_chars_t  Xmlr_attrsToCsv( const Xmlr  object_ ) {               /*M*/
    GO                                                            (UID(F7B514));
    const _xmlr_t* const  me = _object_const(&object_, UID(EB56C2));

    const XmlrToken*  token    = NULL;
    size_t            i        = me->pos;
    bool              has_rows = false;
    new_csv_t         csv      = CsvWriter(2, 0);

    _RETURN_IF_NO_CONTENT(NULL);

    token = _CONST_CAST(XmlrToken*, _TOKEN(i));

    if (_is_empty_tag(token, NULL) || _is_start_tag(token, NULL)) {
        do {
            token = _CONST_CAST(XmlrToken*, _TOKEN(++i));

            if (_is_attribute_name(token, NULL)) {
                chars_t  name = token->value;
                i++;

                if (!IS_BLANK(name)) {
                    chars_t  val = _TOKEN(i)->value;

                    if (has_rows) {
                        writeNewRowCsv(csv);
                    }

                    has_rows = true;
                    writeTextCsv(csv, name);
                    writeTextCsv(csv, val);
                }
            }
        } while (_is_attribute(token));
    }
    {
        chars_t      str = charsCsv(csv);
        new_chars_t  ret = NULL;
        if (!IS_BLANK(str)) {
            ret = T_chars(str);
        }
        freeCsv(&csv);
        RETURN(ret);
    }
} /* Xmlr_attrsToCsv */


PUBLIC bool  Xmlr_eof( const Xmlr  object_ ) {                             /*P*/
    GO                                                            (UID(F97DA8));
    const _xmlr_t* const  me          = _object_const(&object_, UID(E7D836));
    const size_t          token_count = Array_count(me->tokens);
    const bool            ret         = (me->pos > (token_count - 1));
    RETURN(ret);
} /* Xmlr_eof */


PUBLIC chars_t  Xmlr_childContent(                                         /*P*/
    const Xmlr  object_,                                                   /*-*/
    const bool  indented_,                                                 /*-*/
    chars_t     search_expr_ ) {                                           /*-*/
    GO                                                            (UID(FDB849));
    const _xmlr_t* const  me = _object_const(&object_, UID(E2E499));

    size_t        i           = me->pos + 1;
    const size_t  token_count = Array_count(me->tokens);
    bool          is_found    = false;

    _CONST_CHARS_COPY(&me->child_content_ret, BLANK);

    _RETURN_IF_NO_CONTENT(me->child_content_ret);

    {
        /* locate child tag */
        const size_t      depth = _TOKEN(me->pos)->depth + 1;
        const XmlrToken*  token = _TOKEN(i);  /* mutable */

        while (i < token_count && token->depth >= depth) {
            if (token->depth == depth &&
                _matching(me, i, search_expr_)) {
                is_found = true;
                break;
            }
            token = _TOKEN(++i);
        }
    }

    if (is_found) {
        /* skip attribute names and values of the located child tag */
        do {
            i++;
        } while (i < token_count &&
                 (_TOKEN(i)->type == XML_ATTR_NAME ||
                  _TOKEN(i)->type == XML_ATTR_VAL));

        _CONST_CHARS_ASSIGN(me, child_content_ret,
                            _xml_text(me, i, false, indented_));
    }
    RETURN(me->child_content_ret);
} /* Xmlr_childContent */


/* Xmlr_childContentIndented */   /* TODO: IMPLEMENT */


PUBLIC size_t  Xmlr_childCount(                                            /*P*/
    const Xmlr  object_,                                                   /*-*/
    chars_t     search_expr_ ) {                                           /*-*/
    GO                                                            (UID(FE026D));
    const _xmlr_t* const  me = _object_const(&object_, UID(EE3422));

    size_t  ret_count = 0;
    _RETURN_IF_NO_CONTENT(0);
    {
        _TOKEN_LOOP {
            if (_TOKEN(i)->depth == depth &&
            _matching(me, i, search_expr_)) {
                ret_count++;
            }
            i++;
        }
    }
    RETURN(ret_count);
} /* Xmlr_childCount */


PUBLIC chars_t  Xmlr_content(                                              /*P*/
    const Xmlr  object_,                                                   /*-*/
    const bool  indented_ ) {                                              /*-*/
    GO                                                            (UID(F5FA65));
    const _xmlr_t* const  me = _object_const(&object_, UID(E9F501));

    size_t        i           = me->pos;
    const size_t  token_count = Array_count(me->tokens);

    _CONST_CHARS_COPY(&me->content_ret, BLANK);

    _RETURN_IF_NO_CONTENT(me->content_ret);

    /* there is no content to return if 'XML_START_TAG' */
    /* is immediately followed by 'XML_END_TAG'         */
    if (i < (token_count - 1) &&
        _TOKEN(i)->type     == XML_START_TAG &&
        _TOKEN(i + 1)->type == XML_END_TAG) {
        RETURN(BLANK);
    }

    /* skip attribute names and values of the current tag */
    do {
        i++;
    } while (i < token_count && _is_attribute(_TOKEN(i)));

    _CONST_CHARS_ASSIGN(me, content_ret,
                        _xml_text(me, i, false, indented_));

    RETURN(me->content_ret);
} /* Xmlr_content */


PUBLIC chars_t  Xmlr_debugInfo(const Xmlr  object_ ) {                     /*P*/
    GO                                                            (UID(F21ABA));
    const _xmlr_t* const  me = _object_const(&object_, UID(EDD934));

    size_t        i           = 0;
    const size_t  token_count = Array_count(me->tokens);
    chars_t       token_type  = BLANK;
    new_str_t     info        = S_blank();
    new_chars_t   summary     = formatT(_T("RESULTS:")          _T("\r\n")
                                        _T("Error Code   = %d") _T("\r\n")
                                        _T("Error Name   = %s") _T("\r\n")
                                        _T("Error Line   = %d") _T("\r\n")
                                        _T("Error Column = %d") _T("\r\n"),
                                        me->err_code,
                                        Xmlr_errorName(object_),
                                        me->err_line,
                                        me->err_column);

    addTS(&info, summary);
    freeT(&summary);

    for (i = 0; i < token_count; i++) {
        new_chars_t  token_info = NULL;

        switch (_TOKEN(i)->type) {
                CASE_TO_TEXT(XML_ATTR_NAME,         token_type);
                CASE_TO_TEXT(XML_ATTR_VAL,          token_type);
                CASE_TO_TEXT(XML_COMMENT_END_TAG,   token_type);
                CASE_TO_TEXT(XML_COMMENT_START_TAG, token_type);
                CASE_TO_TEXT(XML_COMMENT_TEXT,      token_type);
                CASE_TO_TEXT(XML_EMPTY_TAG,         token_type);
                CASE_TO_TEXT(XML_END_TAG,           token_type);
                CASE_TO_TEXT(XML_START_TAG,         token_type);
                CASE_TO_TEXT(XML_TEXT,              token_type);
                CASE_TO_TEXT(XML_UNKNOWN_TOKEN,     token_type);
            default:
                token_type = _T("XML_UNKNOWN_TOKEN");
        }

        token_info = formatT(
                         _T("\r\n") _T("[%04d] %2d %s '%s'"),
                         i, _TOKEN(i)->depth, token_type,
                         _TOKEN(i)->value);

        addTS(&info, token_info);
        freeT(&token_info);
    }

    _CONST_CHARS_COPY(&me->debug_info_ret, info.cs);

    freeS(&info);

    RETURN(me->debug_info_ret);
} /* Xmlr_debugInfo */


PUBLIC Xmlr_ParseErrorEnum  Xmlr_errorCode(                                /*P*/
    const Xmlr  object_ ) {                                                /*-*/
    GO                                                            (UID(F19E20));
    const _xmlr_t* const       me  = _object_const(&object_, UID(EFF571));
    const Xmlr_ParseErrorEnum  ret = me->err_code;
    RETURN(ret);
} /* Xmlr_errorCode */


PUBLIC size_t  Xmlr_errorColumn( const Xmlr  object_ ) {                   /*P*/
    GO                                                            (UID(F37036));
    const _xmlr_t* const  me  = _object_const(&object_, UID(EE64E3));
    const size_t          ret = me->err_column;
    RETURN(ret);
} /* Xmlr_errorColumn */


PUBLIC size_t  Xmlr_errorLine( const Xmlr  object_ ) {                     /*P*/
    GO                                                            (UID(F11B9F));
    const _xmlr_t* const  me  = _object_const(&object_, UID(E6FF9F));
    const size_t          ret = me->err_line;
    RETURN(ret);
} /* Xmlr_errorLine */


PUBLIC chars_t  Xmlr_errorName( const Xmlr  object_ ) {                    /*P*/
    GO                                                            (UID(F064EC));
    const _xmlr_t* const  me  = _object_const(&object_, UID(EC826E));
    chars_t               ret = BLANK;

    switch (me->err_code) {
            CASE_TO_TEXT(ERR_NONE,         ret);
            CASE_TO_TEXT(ERR_ALPHA,        ret);
            CASE_TO_TEXT(ERR_ASSIGN,       ret);
            CASE_TO_TEXT(ERR_COLON,        ret);
            CASE_TO_TEXT(ERR_DOUBLE_QUOTE, ret);
            CASE_TO_TEXT(ERR_ENDTAG_1,     ret);
            CASE_TO_TEXT(ERR_ENDTAG_2,     ret);
            CASE_TO_TEXT(ERR_NO_ROOT,      ret);
            CASE_TO_TEXT(ERR_NO_XML,       ret);
            CASE_TO_TEXT(ERR_NUMBER1,      ret);
            CASE_TO_TEXT(ERR_NUMBER2,      ret);
            CASE_TO_TEXT(ERR_QUOTE,        ret);
            CASE_TO_TEXT(ERR_SLASH,        ret);
            CASE_TO_TEXT(ERR_START_TAG,    ret);
            CASE_TO_TEXT(ERR_SYMBOL,       ret);
            CASE_TO_TEXT(ERR_TAG_MISMATCH, ret);
            CASE_TO_TEXT(ERR_UNKNOWN_CHAR, ret);
            CASE_TO_TEXT(ERR_WHITESPACE1,  ret);
            CASE_TO_TEXT(ERR_WHITESPACE2,  ret);
        default:
            ret = _T("UNKNOWN");
    }
    RETURN(ret);
} /* Xmlr_errorName */


PUBLIC chars_t  Xmlr_errorReport( const Xmlr  object_ ) {                  /*P*/
    GO                                                            (UID(FCD7F3));
    const _xmlr_t* const  me = _object_const(&object_, UID(EDFB90));

    _CONST_CHARS_ASSIGN(me, error_report_ret,
                        formatT(
                            _T("<error code='%s' line=%d column=%d />"),
                            Xmlr_errorName(object_),
                            Xmlr_errorLine(object_),
                            Xmlr_errorColumn(object_)));

    RETURN(me->error_report_ret);
} /* Xmlr_errorReport */


PUBLIC bool  Xmlr_exists(                                                  /*P*/
    const Xmlr  object_,                                                   /*-*/
    chars_t     search_expr_ ) {                                           /*-*/
    GO                                                            (UID(F48067));
    const _xmlr_t* const  me = _object_const(&object_, UID(E30BB4));

    _RETURN_IF_NO_CONTENT(false);
    {
        _TOKEN_LOOP {
            if (_TOKEN(i)->depth == depth &&
            _matching(me, i, search_expr_)) {
                RETURN(true);
            }
            i++;
        }
    }
    RETURN(false);
} /* Xmlr_exists */


PUBLIC bool  Xmlr_existsInner(                                             /*P*/
    const Xmlr  object_,                                                   /*-*/
    chars_t     search_expr_ ) {                                           /*-*/
    GO                                                            (UID(FEF957));
    const _xmlr_t* const  me = _object_const(&object_, UID(E8F384));

    _RETURN_IF_NO_CONTENT(false);
    {
        _TOKEN_LOOP {
            if (_matching(me, i, search_expr_)) {
                RETURN(true);
            }
            i++;
        }
    }
    RETURN(false);
} /* Xmlr_existsInner */


PUBLIC uint32_t  Xmlr_position( const Xmlr  object_ ) {                    /*P*/
    GO                                                            (UID(F014DF));
    const _xmlr_t* const  me  = _object_const(&object_, UID(E4B0FB));
    const uint32_t        ret = me->pos;
    RETURN(ret);
} /* Xmlr_position */


PUBLIC size_t  Xmlr_innerCount(                                            /*P*/
    const Xmlr  object_,                                                   /*-*/
    chars_t     search_expr_ ) {                                           /*-*/
    GO                                                            (UID(F5D0B5));
    const _xmlr_t* const  me = _object_const(&object_, UID(E85EAE));
    size_t                ret_count = 0;
    _RETURN_IF_NO_CONTENT(0);
    {
        _TOKEN_LOOP {
            if (_matching(me, i, search_expr_)) {
                ret_count++;
            }
            i++;
        }
    }
    RETURN(ret_count);
} /* Xmlr_innerCount */


PUBLIC bool  Xmlr_isParentTag(                                             /*P*/
    const Xmlr  object_,                                                   /*-*/
    chars_t     tag_name_ ) {                                              /*-*/
    GO                                                            (UID(FA6026));
    const _xmlr_t* const  me = _object_const(&object_, UID(E2286F));

    size_t  i  = me->pos;
    _RETURN_IF_NO_CONTENT(false);

    if (i == 0) {
        RETURN(false);
    } else {
        const XmlrToken*  token = _TOKEN(i);  /* mutable */
        const size_t      depth = token->depth - 1;

        do {
            token = _TOKEN(i);

            if (token->depth == depth &&
                _is_start_tag(token, tag_name_)) {
                RETURN(true);
            }
        } while (i-- > 0 && token->depth >= depth);
    }
    RETURN(false);
} /* Xmlr_isParentTag */


/* returns true if the current tag matches tag_name_                          */
PUBLIC bool  Xmlr_isTagName(                                               /*P*/
    const Xmlr  object_,                                                   /*-*/
    chars_t     tag_name_opt_ ) {                                          /*-*/
    GO                                                            (UID(F8095D));
    const _xmlr_t* const  me = _object_const(&object_, UID(EC52C4));

    bool  ret = false;
    _RETURN_IF_NO_CONTENT(false);
    {
        const XmlrToken* const  token = _TOKEN(me->pos);

        switch (token->type) {
            case XML_COMMENT_END_TAG:
            case XML_COMMENT_START_TAG:
            case XML_EMPTY_TAG:
            case XML_END_TAG:
            case XML_START_TAG:
                if (tag_name_opt_ == NULL ||
                    equals2T(token->value, tag_name_opt_)) {
                    ret = true;
                }
                break;

            case XML_ATTR_NAME:
            case XML_ATTR_VAL:
            case XML_COMMENT_TEXT:
            case XML_TEXT:
            case XML_UNKNOWN_TOKEN:
            default:
                ret = false;
        }
    }
    RETURN(ret);
} /* Xmlr_isTagName */


PUBLIC bool  Xmlr_isWellFormed( const Xmlr  object_ ) {                    /*P*/
    GO                                                            (UID(F33EC2));
    const _xmlr_t* const  me = _object_const(&object_, UID(EE7EF6));
    const bool  ret = (me->err_code == ERR_NONE && Array_count(me->tokens) > 0);
    RETURN(ret);
} /* Xmlr_isWellFormed */


PUBLIC size_t  Xmlr_tagDepth( const Xmlr  object_ ) {                      /*P*/
    GO                                                            (UID(FB9A15));
    const _xmlr_t* const  me  = _object_const(&object_, UID(E29122));
    const size_t          ret = _TOKEN(me->pos)->depth;
    RETURN(ret);
} /* Xmlr_tagDepth */


PUBLIC chars_t  Xmlr_tagName( const Xmlr  object_ ) {                      /*P*/
    GO                                                            (UID(FF533F));
    const _xmlr_t* const  me    = _object_const(&object_, UID(E30ACC));
    chars_t               ret   = BLANK;
    const XmlrToken*      token = NULL;

    _RETURN_IF_NO_CONTENT(BLANK);

    token = CAST(const XmlrToken*, Array_getItemAt(
                     _CONST_CAST(array_t*, &me->tokens), me->pos));
    ret = token->value;
    RETURN(ret);
} /* Xmlr_tagName */


PUBLIC chars_t  Xmlr_tagText( const Xmlr  object_ ) {                      /*P*/
    GO                                                            (UID(FEC8B5));
    const _xmlr_t* const  me = _object_const(&object_, UID(E3AB55));
    _RETURN_IF_NO_CONTENT(BLANK);
    _CONST_CHARS_ASSIGN(
        me, tag_text_ret, _xml_text(me, me->pos, true, false));
    RETURN(me->tag_text_ret);
} /* Xmlr_tagText */


PUBLIC size_t  Xmlr_tokenCount( const Xmlr  object_ ) {                    /*P*/
    GO                                                            (UID(F64C68));
    const _xmlr_t* const  me  = _object_const(&object_, UID(E97CC9));
    const size_t          ret = Array_count(me->tokens);
    RETURN(ret);
} /* Xmlr_tokenCount */


PUBLIC chars_t  Xmlr_text(                                                 /*P*/
    const Xmlr  object_,                                                   /*-*/
    const bool  indented_ ) {                                              /*-*/
    GO                                                            (UID(F6CB81));
    const _xmlr_t* const  me = _object_const(&object_, UID(EDA5C5));
    _CONST_CHARS_COPY(&me->xml_ret, BLANK);
    _RETURN_IF_NO_CONTENT(me->xml_ret);
    _CONST_CHARS_ASSIGN(
        me,  xml_ret,  _xml_text(me, me->pos, false, indented_));
    RETURN(me->xml_ret);
} /* Xmlr_text */


/* -------------------------------------------------------------------------- */
/* Methods: Parsing                                                           */


PUBLIC bool  Xmlr_parse(                                                   /*M*/
    Xmlr     object_,                                                      /*-*/
    chars_t  xml_ ) {                                                      /*-*/
    GO                                                            (UID(F783BA));
    _xmlr_t* const  me = _object(&object_, UID(ED0E77));

    _parse_mode_enum  mode        = PARSE_TEXT;
    size_t            col         = 0;
    size_t            line        = 1;
    size_t            token_count = 0;
    chars_t           xml         = xml_;
    new_str_t         token       = S_blank();

    me->err_code   = ERR_NONE;
    me->err_column = 0;
    me->err_line   = 0;

    _remove_all_tokens(me);

    /* xml text must not be blank */
    if (IS_BLANK(xml)) {
        me->err_code = ERR_NO_XML;
        goto _malformed;
    }

    /* skip whitespaces */
    while (*xml != '\0' && IS_SPACE(*xml)) {
        xml++;
    }

    {
        /* skip byte-order-mark (BOM) if such is found */
        const uint8_t*  bom = CAST(const uint8_t*, xml);

        if (bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF) {
            xml = CAST(chars_t, bom + 3);  /* UTF-8 */

        } else if (bom[0] == 0xFE && bom[1] == 0xFF) {
            xml = CAST(chars_t, bom + 2);  /* UTF-16 big-endian */

        } else if (*bom == 0xFF && *(bom + 1) == 0xFE) {
            xml = CAST(chars_t, bom + 2);  /* UTF-16 little-endian */
        }
    }

    /* skip the xml declaration */
    if (beginsT(xml, _T("<?xml"))) {
        chars_t  end = STRSTR_T(xml, _T("?>"));

        if (end == NULL) {
            goto _malformed;
        } else {
            xml = end + 2;  /* + 2 = length of '?>' */
        }
    }

    /* store and skip the DOCTYPE declaration */
    if (beginsT(xml, _T("<!DOCTYPE"))) {
        chars_t  end = STRSTR_T(xml, _T(">"));

        _CONST_CHARS_COPY(&me->doctype_tag_ret, BLANK);

        if (end == NULL) {
            goto _malformed;
        } else {
            _CONST_CHARS_ASSIGN(me, doctype_tag_ret,
                                T_chars_n(xml, end - xml + 1));

            xml = end + 1;  /* + 1 = length of '>' */
        }
    }

    /* skip any whitespaces again */
    while (*xml != '\0' && IS_SPACE(*xml)) {
        xml++;
    }

    /* xml text must begin with a root element */
    if (*xml != '<') {
        me->err_code = ERR_NO_ROOT;
        goto _malformed;
    }

    while (*xml != '\0') {
        const uint32_t  ch = *xml;
        xml++;

        if (ch == '\r') {
            line++;
            col = 1;
        } else {
            col++;
        }

        if (mode == PARSE_COMMENT) {
            if (ch == '-' && *xml == '-' && xml[1] == '>') {
                xml += 2;

                _add_token(me, XML_COMMENT_TEXT, token);

                setInS(&token, _T("--"));
                _add_token(me, XML_COMMENT_END_TAG, token);

                setInS(&token, BLANK);
                mode = PARSE_TEXT;
            } else {
                addCharS(&token, CAST(char_t, ch));
            }

        } else if ((mode == PARSE_TEXT              && ch != '<')  ||
                   (mode == PARSE_ATTR_QUOTE        && ch != '\'') ||
                   (mode == PARSE_ATTR_DOUBLE_QUOTE && ch != '"')) {
            addCharS(&token, CAST(char_t, ch));

        } else if ((ch >= 'a' && ch <= 'z') ||
                   (ch >= 'A' && ch <= 'Z') ||
                   ch == ':'                ||
                   ch == '_') {

            if (mode == PARSE_TAG_NAME  ||
                mode == PARSE_CLOSE_TAG ||
                mode == PARSE_ATTR_NAME) {
                addCharS(&token, CAST(char_t, ch));
            } else {
                me->err_code = ERR_ALPHA;
                goto _malformed;
            }

        } else if (ch == '-' || ch == '.' || (ch >= '0' && ch <= '9')) {

            if (mode == PARSE_TAG_NAME  ||
                mode == PARSE_CLOSE_TAG ||
                mode == PARSE_ATTR_NAME) {

                if (lengthS(token) > 0) {
                    addCharS(&token, CAST(char_t, ch));
                } else {
                    me->err_code = ERR_NUMBER1;
                    goto _malformed;
                }

            } else if (mode == PARSE_EMPTY_TAG ||
                       mode == PARSE_ATTR_EQUAL) {
                me->err_code = ERR_NUMBER2;
                goto _malformed;
            }

        } else if (ch == '<') {
            if (mode == PARSE_TEXT) {
                if (is_whitespaceT(token.cs)) {
                    if (contains2T(token.cs, _T("\r")) ||
                        contains2T(token.cs, _T("\n"))) {

                        setInS(&token, _T("\r\n"));
                        _add_token(me, XML_TEXT, token);
                    }
                } else if (!IS_BLANK(token.cs)) {
                    _add_token(me, XML_TEXT, token);
                }

                setInS(&token, BLANK);
                mode = PARSE_TAG_NAME;
            } else {
                me->err_code = ERR_START_TAG;
                goto _malformed;
            }

        } else if (ch == '>') {
            if (mode == PARSE_TAG_NAME || mode == PARSE_CLOSE_TAG) {
                Xmlr_TokenTypeEnum  token_type =
                    mode == PARSE_TAG_NAME  ? XML_START_TAG :
                    mode == PARSE_CLOSE_TAG ? XML_END_TAG   :
                    XML_COMMENT_TEXT;

                _add_token(me, token_type, token);

                setInS(&token, BLANK);
                mode = PARSE_TEXT;

            } else if (mode == PARSE_EMPTY_TAG) {
                if (lengthS(token) > 0) {
                    _add_token(me, XML_EMPTY_TAG, token);
                } else {
                    size_t  i = Array_count(me->tokens) - 1;

                    while (_TOKEN(i)->type != XML_START_TAG) {
                        i--;
                    }

                    CAST(XmlrToken*, _TOKEN(i))->type = XML_EMPTY_TAG;
                }

                setInS(&token, BLANK);
                mode = PARSE_TEXT;

            } else if (mode == PARSE_ATTR_NAME) {
                if (lengthS(token) == 0) {
                    mode = PARSE_TEXT;
                } else {
                    me->err_code = ERR_ENDTAG_1;
                    goto _malformed;
                }

            } else {
                me->err_code = ERR_ENDTAG_2;
                goto _malformed;
            }

        } else if (ch == '/') {
            if (mode == PARSE_TAG_NAME) {
                mode = lengthS(token) > 0 ?
                       PARSE_EMPTY_TAG : PARSE_CLOSE_TAG;
            } else if (mode == PARSE_ATTR_NAME) {
                mode = PARSE_EMPTY_TAG;
            } else {
                me->err_code = ERR_SLASH;
                goto _malformed;
            }

        } else if (ch == '=') {
            if (mode == PARSE_ATTR_NAME) {
                _add_token(me, XML_ATTR_NAME, token);
                setInS(&token, BLANK);
                mode = PARSE_ATTR_EQUAL;
            } else {
                me->err_code = ERR_ASSIGN;
                goto _malformed;
            }

        } else if (ch == '\'') {
            if (mode == PARSE_ATTR_EQUAL) {
                mode = PARSE_ATTR_QUOTE;
            } else if (mode == PARSE_ATTR_QUOTE) {
                _add_token(me, XML_ATTR_VAL, token);
                setInS(&token, BLANK);
                mode = PARSE_ATTR_NAME;
            } else {
                me->err_code = ERR_QUOTE;
                goto _malformed;
            }

        } else if (ch == '"') {
            if (mode == PARSE_ATTR_EQUAL) {
                mode = PARSE_ATTR_DOUBLE_QUOTE;
            } else if (mode == PARSE_ATTR_DOUBLE_QUOTE) {
                _add_token(me, XML_ATTR_VAL, token);
                setInS(&token, BLANK);
                mode = PARSE_ATTR_NAME;
            } else {
                me->err_code = ERR_DOUBLE_QUOTE;
                goto _malformed;
            }

        } else if (IS_SPACE(ch)) {
            if (mode == PARSE_TAG_NAME) {
                if (lengthS(token) > 0) {
                    _add_token(me, XML_START_TAG, token);
                    setInS(&token, BLANK);
                    mode = PARSE_ATTR_NAME;
                } else {
                    me->err_code = ERR_WHITESPACE1;
                    goto _malformed;
                }
            } else if (mode == PARSE_CLOSE_TAG) {
                me->err_code = ERR_WHITESPACE2;
                goto _malformed;
            }

        } else if (ch == ':') {
            if ((mode == PARSE_TAG_NAME  ||
                 mode == PARSE_CLOSE_TAG ||
                 mode == PARSE_ATTR_NAME) && lengthS(token) > 0 &&
                find2S(token, _T(":")) == NONE) {
                addTS(&token, _T(":"));
            } else {
                me->err_code = ERR_COLON;
                goto _malformed;
            }

        } else if (IS_SYMBOL(ch)) {
            if (mode == PARSE_TAG_NAME &&
                ch == '!' && xml[0] == '-' && xml[1] == '-') {
                setInS(&token, _T("--"));
                _add_token(me, XML_COMMENT_START_TAG, token);
                setInS(&token, BLANK);
                mode = PARSE_COMMENT;
                xml += 2;
            } else {
                me->err_code = ERR_SYMBOL;
                goto _malformed;
            }

        } else { /* the character type is unknown */
            me->err_code = ERR_UNKNOWN_CHAR;
            goto _malformed;
        }
    }

    me->err_code   = ERR_NONE;
    me->err_column = 0;
    me->err_line   = 0;

    /* set nesting depths and make sure each opening tag has a closing tag */
    token_count = Array_count(me->tokens);

    if (token_count > 0) {
        size_t   i         = 0;
        size_t   depth     = 1;
        array_t  hierarchy = Array_init(sizeof(size_t), 10, 0);

        while (i < token_count) {
            if (_TOKEN(i)->type == XML_START_TAG ||
                _TOKEN(i)->type == XML_EMPTY_TAG) {

                bool  advance;
                CAST(XmlrToken*, _TOKEN(i))->depth = depth;
                advance = (_TOKEN(i)->type == XML_START_TAG);

                if (advance) {
                    Array_addItem(&hierarchy, &i, sizeof(size_t), NULL);
                }

                i++;

                while (i < token_count) {
                    if (_TOKEN(i)->type == XML_ATTR_NAME) {
                        CAST(XmlrToken*, _TOKEN(i))->depth = depth + 1;
                    } else if (_TOKEN(i)->type == XML_ATTR_VAL) {
                        CAST(XmlrToken*, _TOKEN(i))->depth = depth + 2;
                    } else {
                        i--;
                        break;
                    }
                    i++;
                }

                if (advance) {
                    depth++;
                }
            } else if (_TOKEN(i)->type == XML_END_TAG) {
                chars_t   val1  = _TOKEN(i)->value;
                uint32_t  index = Array_count(hierarchy);

                if (index > 0) {
                    chars_t  val2 = NULL;

                    index--;

                    {
                        /* long process to get back a stored size_t */
                        size_t    tok  = 0;
                        uint8_t*  data = Array_getItemAt(&hierarchy, index);

                        MEMCPY(&tok, data, sizeof(size_t));
                        val2 = _TOKEN(tok)->value;
                    }

                    if (!equals2T(val1, val2)) {
                        me->err_code = ERR_TAG_MISMATCH;
                        goto _malformed;
                    }

                    Array_removeLast(&hierarchy);
                }

                depth--;
                CAST(XmlrToken*, _TOKEN(i))->depth = depth;
            } else {
                CAST(XmlrToken*, _TOKEN(i))->depth = depth;
            }

            i++;
        }
        Array_free(&hierarchy);
    }

    freeS(&token);
    RETURN(true);

_malformed:
    freeS(&token);
    me->err_line   = line;
    me->err_column = col;

    DUMP_OPEN;
    DUMP(_T("%s"), Xmlr_debugInfo(object_));
    DUMP_CLOSE;

    RETURN(false);
} /* Xmlr_parse */


/* -------------------------------------------------------------------------- */
/* Methods: General                                                           */


PUBLIC new_chars_t  Xmlr_keyValuesToCsv(                                   /*M*/
    Xmlr     object_,                                                      /*-*/
    chars_t  container_element_,                                           /*-*/
    chars_t  item_element_,                                                /*-*/
    chars_t  key_attr_,                                                    /*-*/
    chars_t  value_attr_ ) {                                               /*-*/
    GO                                                            (UID(F572A8));
    _xmlr_t* const  me          = _object(&object_, UID(E520FD));
    const size_t    token_count = Array_count(me->tokens);
    size_t          i           = 0;
    bool            container   = false;
    bool            has_rows    = false;
    new_chars_t     ret         = NULL;
    new_csv_t       csv         = CsvWriter(2, 0);

    const XmlrToken*  token = NULL;

    _RETURN_IF_NO_CONTENT(NULL);

    do {
        token = _CONST_CAST(XmlrToken*, _TOKEN(i));

        if (!container && _is_start_tag(token, container_element_)) {
            container = true;

        } else if (container) {
            if (_is_empty_tag(token, item_element_)) {
                chars_t  key = NULL;
                chars_t  val = NULL;

                do {
                    token = _CONST_CAST(XmlrToken*, _TOKEN(++i));

                    if (_is_attribute_name(token, NULL)) {

                        if (equals2T(token->value, key_attr_)) {
                            key = _TOKEN(i + 1)->value;
                            i++;

                        } else if (equals2T(token->value, value_attr_)) {
                            val = _TOKEN(i + 1)->value;
                            i++;
                        }
                    }
                } while (_is_attribute(token));

                if (!IS_BLANK(key)) {
                    if (has_rows) {
                        writeNewRowCsv(csv);
                    }
                    has_rows = true;
                    writeTextCsv(csv, key);
                    writeTextCsv(csv, val);
                }
            }
        }
    } while (++i < token_count &&
             !(container && _is_end_tag(token, container_element_)));

    {
        chars_t  str = charsCsv(csv);
        if (!IS_BLANK(str)) {
            ret = T_chars(str);
        }
    }
    freeCsv(&csv);

    RETURN(ret);
} /* Xmlr_keyValuesToCsv */


PUBLIC bool  Xmlr_removeComments( Xmlr  object_ ) {                        /*M*/
    GO                                                            (UID(F422A9));
    _xmlr_t* const  me          = _object(&object_, UID(E6F894));
    const size_t    token_count = Array_count(me->tokens);
    size_t          i           = 0;
    size_t          write       = 0;
    bool            ret_removed = false;

    me->pos = 0;

    for (i = 0; i < token_count; i++) {
        XmlrToken* const  token =
            _CONST_CAST(XmlrToken*, _TOKEN(i));

        if (token->type == XML_COMMENT_START_TAG ||
            token->type == XML_COMMENT_END_TAG   ||
            token->type == XML_COMMENT_TEXT) {

            freeT(&token->value);
            token->depth = 0;
            token->type  = XML_UNKNOWN_TOKEN;
            ret_removed  = true;
        } else if (ret_removed) {
            XmlrToken* const  write_token =
                _CONST_CAST(XmlrToken*, _TOKEN(write++));

            *write_token = *token;
        } else {
            write++;
        }
    }

    Array_resize(&me->tokens, write);

    RETURN(ret_removed);
} /* Xmlr_removeComments */


/* -------------------------------------------------------------------------- */
/* Methods: Navigation                                                        */


PUBLIC bool  Xmlr_goAnyNext(                                               /*M*/
    Xmlr     object_,                                                      /*-*/
    chars_t  search_expr_ ) {                                              /*-*/
    GO                                                            (UID(F1E02C));
    _xmlr_t* const  me = _object(&object_, UID(E116F2));

    _RETURN_IF_NO_CONTENT(false);
    {
        size_t        i           = me->pos + 1;
        const size_t  token_count = Array_count(me->tokens);

        while (i < token_count) {
            if (_matching(me, i, search_expr_)) {
                me->pos = i;
                RETURN(true);
            }
            i++;
        }
    }
    RETURN(false);
} /* Xmlr_goAnyNext */


PUBLIC bool  Xmlr_goChild(                                                 /*M*/
    Xmlr     object_,                                                      /*-*/
    chars_t  search_expr_ ) {                                              /*-*/
    GO                                                            (UID(F7602E));
    _xmlr_t* const  me = _object(&object_, UID(EFF222));

    _RETURN_IF_NO_CONTENT(false);
    {
        _TOKEN_LOOP {
            if (_TOKEN(i)->depth == depth &&
            _matching(me, i, search_expr_)) {
                me->pos = i;
                RETURN(true);
            }
            i++;
        }
    }
    RETURN(false);
} /* Xmlr_goChild */


PUBLIC bool  Xmlr_goChildOrNext(                                           /*M*/
    Xmlr     object_,                                                      /*-*/
    chars_t  search_expr_ ) {                                              /*-*/
    GO                                                            (UID(FF895A));
    _xmlr_t* const  me  = _object(&object_, UID(E2096A));
    bool            ret = false;

    _RETURN_IF_NO_CONTENT(false);
    {
        if (Xmlr_goChild(object_, search_expr_)) {
            ret = true;
        } else {
            ret = Xmlr_goNext(object_, search_expr_);
        }
    }
    RETURN(ret);
} /* Xmlr_goChildOrNext */


PUBLIC bool  Xmlr_goFirst(                                                 /*M*/
    Xmlr     object_,                                                      /*-*/
    chars_t  search_expr_ ) {                                              /*-*/
    GO                                                            (UID(F308F1));
    _xmlr_t* const  me  = _object(&object_, UID(EB0109));
    bool            ret = false;

    _RETURN_IF_NO_CONTENT(false);
    {
        size_t  i    = me->pos;
        size_t  prev = 0;

        do {
            prev = _adjacent_index(me, i, false, search_expr_);

            if (prev != NONE) {
                ret = true;
                i = prev;
            }
        } while (prev != NONE);

        if (ret) {
            me->pos = i;
        }
    }
    RETURN(ret);
} /* Xmlr_goFirst */


PUBLIC bool  Xmlr_goPosition(                                              /*M*/
    Xmlr            object_,                                               /*-*/
    const uint32_t  index_ ) {                                             /*-*/
    GO                                                            (UID(F092F1));
    _xmlr_t* const  me  = _object(&object_, UID(ECEEF1));
    bool            ret = false;

    _RETURN_IF_NO_CONTENT(false);
    {
        const size_t  token_count = Array_count(me->tokens);

        if (index_ < token_count) {
            me->pos = index_;
            ret = true;
        }
    }
    RETURN(ret);
} /* Xmlr_goPosition */


PUBLIC bool  Xmlr_goInner(                                                 /*M*/
    Xmlr     object_,                                                      /*-*/
    chars_t  search_expr_ ) {                                              /*-*/
    GO                                                            (UID(FA1C36));
    _xmlr_t* const  me = _object(&object_, UID(E995E9));

    _RETURN_IF_NO_CONTENT(false);
    {
        _TOKEN_LOOP {
            if (_matching(me, i, search_expr_)) {
                me->pos = i;
                RETURN(true);
            }
            i++;
        }
    }
    RETURN(false);
} /* Xmlr_goInner */


PUBLIC bool  Xmlr_goLast(                                                  /*M*/
    Xmlr     object_,                                                      /*-*/
    chars_t  search_expr_ ) {                                              /*-*/
    GO                                                            (UID(FD4300));
    _xmlr_t* const  me  = _object(&object_, UID(EA6E6E));
    bool            ret = false;

    _RETURN_IF_NO_CONTENT(false);
    {
        size_t  i    = me->pos;
        size_t  next = 0;

        do {
            next = _adjacent_index(me, i, false, search_expr_);

            if (next != NONE) {
                ret = true;
                i = next;
            }
        } while (next != NONE);

        if (ret) {
            me->pos = i;
        }
    }
    RETURN(ret);
} /* Xmlr_goLast */


PUBLIC bool  Xmlr_goNext(                                                  /*M*/
    Xmlr     object_,                                                      /*-*/
    chars_t  search_expr_ ) {                                              /*-*/
    GO                                                            (UID(F93A27));
    _xmlr_t* const  me  = _object(&object_, UID(EFF06C));
    bool            ret = false;

    _RETURN_IF_NO_CONTENT(false);
    {
        const size_t  index = _adjacent_index(me, me->pos, true, search_expr_);

        if (index != NONE) {
            me->pos = index;
        }

        ret = (index != NONE);
    }
    RETURN(ret);
} /* Xmlr_goNext */


PUBLIC bool  Xmlr_goParent( Xmlr  object_ ) {                              /*M*/
    GO                                                            (UID(FCD6A4));
    _xmlr_t* const  me = _object(&object_, UID(E27B4C));

    _RETURN_IF_NO_CONTENT(false);

    if (me->pos == 0) {
        RETURN(false);
    } else {
        size_t        i     = me->pos;
        const size_t  depth = _TOKEN(i)->depth;

        do {
            i--;
            if (_TOKEN(i)->depth < depth &&
                (_TOKEN(i)->type == XML_START_TAG ||
                 _TOKEN(i)->type == XML_EMPTY_TAG)) {
                me->pos = i;
                RETURN(true);
            }
        } while (i > 0);
    }
    RETURN(false);
} /* Xmlr_goParent */


PUBLIC bool  Xmlr_goPrev(                                                  /*M*/
    Xmlr     object_,                                                      /*-*/
    chars_t  search_expr_ ) {                                              /*-*/
    GO                                                            (UID(FA27AB));
    _xmlr_t* const  me  = _object(&object_, UID(E20347));
    bool            ret = false;

    _RETURN_IF_NO_CONTENT(false);
    {
        const size_t  index =
            _adjacent_index(me, me->pos, false, search_expr_);

        if (index != NONE) {
            me->pos = index;
        }

        ret = (index != NONE);
    }
    RETURN(ret);
} /* Xmlr_goPrev */


PUBLIC void  Xmlr_goRoot( Xmlr  object_ ) {                                /*M*/
    GO                                                            (UID(FDA722));
    _xmlr_t* const  me          = _object(&object_, UID(EBD410));
    size_t          i           = 0;
    const size_t    token_count = Array_count(me->tokens);

    while (i < token_count) {
        if (_TOKEN(i)->type == XML_START_TAG &&
            !equals2T(_TOKEN(i)->value, _T("--"))) {
            me->pos = i;
            break;
        }
        i++;
    }
    RETURN(NIL);
} /* Xmlr_goRoot */


PUBLIC uint32_t  Xmlr_skipElement( Xmlr  object_ ) {                       /*M*/
    GO                                                            (UID(FA86B3));
    _xmlr_t* const  me          = _object(&object_, UID(E4E2D9));
    uint32_t        i           = me->pos;
    const size_t    token_count = Array_count(me->tokens);
    uint32_t        ret         = me->pos;

    _RETURN_IF_NO_CONTENT(0);

    while (_TOKEN(i)->type == XML_ATTR_NAME ||
           _TOKEN(i)->type == XML_ATTR_VAL) {
        i--;
    }

    if (_TOKEN(i)->type == XML_EMPTY_TAG) {
        while (++i < token_count &&
               (_TOKEN(i)->type == XML_ATTR_NAME ||
                _TOKEN(i)->type == XML_ATTR_VAL)) {
            ;
        }
    } else if (_TOKEN(i)->type == XML_START_TAG) {
        const uint32_t  depth = _TOKEN(i)->depth;
        chars_t         tag   = _TOKEN(i)->value;

        while (++i < token_count && _TOKEN(i)->depth >= depth) {
            if (_TOKEN(i)->depth == depth && _is_end_tag(_TOKEN(i), tag)) {
                break;
            }
        }
    } else if (_TOKEN(i)->type == XML_COMMENT_START_TAG) {
        const uint32_t  depth = _TOKEN(i)->depth;

        while (++i < token_count && _TOKEN(i)->depth >= depth) {
            if (_TOKEN(i)->depth == depth && _is_comment_end_tag(_TOKEN(i))) {
                break;
            }
        }
    } else if (_TOKEN(i)->type == XML_TEXT) {
        while (++i < token_count && _TOKEN(i)->type == XML_TEXT) {
            ;
        }
    } else if (_TOKEN(i)->type == XML_COMMENT_TEXT) {
        while (++i < token_count && _TOKEN(i)->type == XML_COMMENT_TEXT) {
            ;
        }
    }

    /* skip ending tags */
    if (i < (token_count - 1) &&
        (_TOKEN(i)->type == XML_END_TAG ||
         _TOKEN(i)->type == XML_COMMENT_END_TAG)) {
        i++;
    }

    if (i > (token_count - 1)) {
        WARN(_T("position out of range"), UID(E64C62));
        i = token_count - 1;
    }

    ret = me->pos = i;
    RETURN(ret);
} /* Xmlr_skipElement */


PUBLIC uint32_t  Xmlr_skipTag( Xmlr  object_ ) {                           /*M*/
    GO                                                            (UID(F2CD96));
    _xmlr_t* const  me          = _object(&object_, UID(E31D86));
    uint32_t        i           = me->pos;
    const size_t    token_count = Array_count(me->tokens);
    uint32_t        ret         = me->pos;

    _RETURN_IF_NO_CONTENT(0);

    {
        const XmlrToken* const  token = _TOKEN(i);

        if (token->type == XML_EMPTY_TAG ||
            token->type == XML_START_TAG ||
            token->type == XML_COMMENT_START_TAG ||
            token->type == XML_ATTR_NAME ||
            token->type == XML_ATTR_VAL) {

            while (++i < token_count &&
                   (_TOKEN(i)->type == XML_ATTR_NAME ||
                    _TOKEN(i)->type == XML_ATTR_VAL)) {
                ;
            }

        } else if (token->type == XML_TEXT) {
            while (++i < token_count && _TOKEN(i)->type == XML_TEXT) {
                ;
            }

        } else if (token->type == XML_COMMENT_TEXT) {
            while (++i < token_count && _TOKEN(i)->type == XML_COMMENT_TEXT) {
                ;
            }

        } else if (token->type == XML_END_TAG ||
                   token->type == XML_COMMENT_END_TAG) {
            i++;
        }
    }

    if (i > token_count) {
        WARN(_T("position out of range"), UID(E278A6));
        i = token_count;
    }
    ret = me->pos = i;
    RETURN(ret);
} /* Xmlr_skipTag */


/* -------------------------------------------------------------------------- */
/* Functions: Static                                                          */


PUBLIC new_chars_t  from_xml( chars_t  xml_text_ ) {                       /*F*/
    GO                                                            (UID(FCB6C2));
    size_t        i   = 0;
    const size_t  len = lenT(xml_text_);
    char_t*       wr  = NULL;
    chars_t       rd  = xml_text_;
    uint32_t      ch  = 0;
    new_chars_t   ret = mallocT(len + 1);

    for (i = 0; i < len && *rd != '\0'; i++) {
        if (*rd == '&') {
            if (rd[1] == 'l' && rd[2] == 't' && rd[3] == ';') {
                ch = '<';
                rd += 4;

            } else if (rd[1] == 'g' && rd[2] == 't' && rd[3] == ';') {
                ch = '>';
                rd += 4;

            } else if (rd[1] == 'a' && rd[2] == 'm' && rd[3] == 'p' &&
                       rd[4] == ';') {
                ch = '&';
                rd += 5;

            } else if (
                rd[1] == 'q' &&
                rd[2] == 'u' &&
                rd[3] == 'o' &&
                rd[4] == 't' &&
                rd[5] == ';') {
                ch = '"';
                rd += 6;

            } else if (
                rd[1] == 'a' &&
                rd[2] == 'p' &&
                rd[3] == 'o' &&
                rd[4] == 's' &&
                rd[5] == ';') {
                ch = '\'';
                rd += 6;

            } else if (rd[1] == '#' && IS_DIGIT(rd[2])) {
                /* read the decimal character code */
                ch = 0;
                rd += 2;  /* skip &# */

                while (IS_DIGIT(*rd)) {
                    ch *= 10;
                    ch += (*rd - '0');
                    rd++;
                }

                if (*rd == ';') {
                    rd++;
                }

            } else if (rd[1] == '#' && (rd[2] == 'x' || rd[2] == 'X')) {
                /* read hexadecimal character code */
                ch = 0;
                rd += 3;  /* skip &#x */

                while (IS_HEX_DIGIT(*rd)) {
                    ch *= 16;
                    ch += HEX_DIGIT_VAL(*rd);
                    rd++;
                }

                if (*rd == ';') {
                    rd++;
                }
            }
        } else {
            ch = *rd;
            rd++;
        }

#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4127)  /* W:L4 conditional expression is constant    */
#endif

        if (sizeof(char_t) == 1 && ch > 255) {
            ch = '?';
        }

#if defined _MSC_VER
#pragma warning (pop)
#endif

        *wr++ = CAST(char_t, ch);
    }
    *wr = '\0';

    RETURN(ret);
} /* from_xml */


#if defined __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
#endif

#if 000  /* not used at the moment */
PUBLIC new_chars_t  Xmlr_fromChars( chars_t  plain_text_ ) {               /*F*/
    GO                                                            (UID(FEACF8));
    size_t       calc_len = 0;  /* calculated after fist pass */
    int          pass     = 0;
    new_chars_t  ret      = NULL;
    chars_t      rd       = plain_text_;
    char_t*      wr       = NULL;
    char_t*      val      = NULL;

    for (pass = 0; pass < 2; pass++) {
        if (pass == 1) {
            wr = ret = mallocT(calc_len + 1);
            ASSERT(ret != NULL, UID(E596D4));
        }

        while (rd && *rd != '\0') {
            if (*rd == '&') {
                _WRITE_STR(_T("&amp;"));

            } else if (*rd == '<') {
                _WRITE_STR(_T("&lt;"));

            } else if (*rd == '>') {
                _WRITE_STR(_T("&gt;"));

            } else if (*rd == '"') {
                _WRITE_STR(_T("&quot;"));

            } else if (*rd == '\'') {
                _WRITE_STR(_T("&apos;"));

            } else if (*rd < 32 || *rd > 127) {
                if (val == NULL) {
                    val = mallocT(32);
                }
                SNPRINTF_T(val, 32, _T("&#%d;"), CAST(int, *rd));
                _WRITE_STR(val);
            } else {
                if (pass == 0) {
                    calc_len++;
                } else {
                    *wr++ = *rd++;
                }
            }
        }
    }
    freeT(&val);

    RETURN(ret);
} /* Xmlr_fromChars */
#endif                                                                 /* 000 */

#if defined __GNUC__
#pragma GCC diagnostic pop
#endif

/* TODO: add mode property CaseSensitive( ) */

/* TODO: add code to catch duplicate attributes during well-formedness check */

/* TODO: create property hasNext( search_expr_ );                */
/*       hasPrev( search_expr_ );  HasChild( search_expr_ ) etc. */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/
