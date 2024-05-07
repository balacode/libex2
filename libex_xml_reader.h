/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                  [libex_xml_reader.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_XML_READER_H
#define      INCLUDED_LIBEX_XML_READER_H

#include "libex_string_class.h"
#include "libex_stringc.h"

/* -------------------------------------------------------------------------- */
LX_NAMESPACE(lx_c)

typedef struct  lx_Xmlr {
    uint8_t*  ob;
}
lx_Xmlr, lx_new_Xmlr;

typedef enum  lx_Xmlr_TokenTypeEnum {
    LX_XML_UNKNOWN_TOKEN = 0,                        /* lx_Xmlr_TokenTypeEnum */
    LX_XML_ATTR_NAME,                                /* lx_Xmlr_TokenTypeEnum */
    LX_XML_ATTR_VAL,                                 /* lx_Xmlr_TokenTypeEnum */
    LX_XML_COMMENT_END_TAG,                          /* lx_Xmlr_TokenTypeEnum */
    LX_XML_COMMENT_START_TAG,                        /* lx_Xmlr_TokenTypeEnum */
    LX_XML_COMMENT_TEXT,                             /* lx_Xmlr_TokenTypeEnum */
    LX_XML_EMPTY_TAG,                                /* lx_Xmlr_TokenTypeEnum */
    LX_XML_END_TAG,                                  /* lx_Xmlr_TokenTypeEnum */
    LX_XML_START_TAG,                                /* lx_Xmlr_TokenTypeEnum */
    LX_XML_TEXT                                      /* lx_Xmlr_TokenTypeEnum */
}
lx_Xmlr_TokenTypeEnum;                                                  /*enum*/

typedef enum  _lx_Xmlr_ParseErrorEnum {
    LX_ERR_NONE = 0,                                /* lx_Xmlr_ParseErrorEnum */
    LX_ERR_ALPHA,                                   /* lx_Xmlr_ParseErrorEnum */
    LX_ERR_ASSIGN,                                  /* lx_Xmlr_ParseErrorEnum */
    LX_ERR_COLON,                                   /* lx_Xmlr_ParseErrorEnum */
    LX_ERR_DOUBLE_QUOTE,                            /* lx_Xmlr_ParseErrorEnum */
    LX_ERR_ENDTAG_1,                                /* lx_Xmlr_ParseErrorEnum */
    LX_ERR_ENDTAG_2,                                /* lx_Xmlr_ParseErrorEnum */
    LX_ERR_NO_ROOT,                                 /* lx_Xmlr_ParseErrorEnum */
    LX_ERR_NO_XML,                                  /* lx_Xmlr_ParseErrorEnum */
    LX_ERR_NUMBER1,                                 /* lx_Xmlr_ParseErrorEnum */
    LX_ERR_NUMBER2,                                 /* lx_Xmlr_ParseErrorEnum */
    LX_ERR_QUOTE,                                   /* lx_Xmlr_ParseErrorEnum */
    LX_ERR_SLASH,                                   /* lx_Xmlr_ParseErrorEnum */
    LX_ERR_START_TAG,                               /* lx_Xmlr_ParseErrorEnum */
    LX_ERR_SYMBOL,                                  /* lx_Xmlr_ParseErrorEnum */
    LX_ERR_TAG_MISMATCH,                            /* lx_Xmlr_ParseErrorEnum */
    LX_ERR_UNKNOWN_CHAR,                            /* lx_Xmlr_ParseErrorEnum */
    LX_ERR_WHITESPACE1,                             /* lx_Xmlr_ParseErrorEnum */
    LX_ERR_WHITESPACE2                              /* lx_Xmlr_ParseErrorEnum */
}
lx_Xmlr_ParseErrorEnum;                                                 /*enum*/

typedef struct  lx_XmlrToken {
    lx_Xmlr_TokenTypeEnum  type;                              /* lx_XmlrToken */
    uint32_t               depth;                             /* lx_XmlrToken */
    lx_new_chars_t         value;                             /* lx_XmlrToken */
}
lx_XmlrToken;                                                         /*struct*/

/* -------------------------------------------------------------------------- */
/* Constructors / Destructor:                                                 */

/* Default constructor: Constructs a new object without doing anything.       */
LX_PUBLIC lx_new_Xmlr  lx_Xmlr_init( void );                               /*C*/

/* Constructs a new object and parses the given XML text.                     */
LX_PUBLIC lx_new_Xmlr  lx_Xmlr_of_chars(                                   /*C*/
    lx_chars_t  xml_ );                                                    /*-*/

/* Constructs a new object and parses the given XML file.                     */
LX_PUBLIC lx_new_Xmlr  lx_Xmlr_of_file(                                    /*C*/
    lx_chars_t  filename_ );                                               /*-*/

#if 000   /* Uncomment when the copy constructor is implemented: */
/* Copy Constructor */
LX_PUBLIC lx_new_Xmlr  lx_Xmlr_copy( const lx_Xmlr  copy_from_ );          /*C*/
#endif                                                                 /* 000 */

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

LX_PUBLIC void  lx_freeXmlr( lx_Xmlr*  object_ );                          /*D*/

/* -------------------------------------------------------------------------- */
/* Properties: Metadata                                                       */

LX_PUBLIC lx_chars_t  lx_Xmlr_doctypeTag( const lx_Xmlr  object_ );        /*P*/

/* -------------------------------------------------------------------------- */
/* Properties: Token Querying                                                 */

LX_PUBLIC lx_bool  lx_Xmlr_isAttributeName(                                /*P*/
    const lx_Xmlr  object_,                                                /*-*/
    lx_chars_t     attr_name_ );                                           /*-*/

LX_PUBLIC lx_bool  lx_Xmlr_isAttributeValue( const lx_Xmlr  object_ );     /*P*/

LX_PUBLIC lx_bool  lx_Xmlr_isCommentEndTag( const lx_Xmlr  object_ );      /*P*/

LX_PUBLIC lx_bool  lx_Xmlr_isCommentStartTag( const lx_Xmlr  object_ );    /*P*/

LX_PUBLIC lx_bool  lx_Xmlr_isCommentText( const lx_Xmlr  object_ );        /*P*/

LX_PUBLIC lx_bool  lx_Xmlr_isEmptyTag(                                     /*P*/
    const lx_Xmlr  object_,                                                /*-*/
    lx_chars_t     tag_name_opt_ );                                        /*-*/

LX_PUBLIC lx_bool  lx_Xmlr_isEndTag(                                       /*P*/
    const lx_Xmlr  object_,                                                /*-*/
    lx_chars_t     tag_name_opt_ );                                        /*-*/

LX_PUBLIC lx_bool  lx_Xmlr_isStartTag(                                     /*P*/
    const lx_Xmlr  object_,                                                /*-*/
    lx_chars_t     tag_name_opt_ );                                        /*-*/

LX_PUBLIC lx_bool  lx_Xmlr_isText( const lx_Xmlr  object_ );               /*P*/

LX_PUBLIC uint32_t  lx_Xmlr_tokenDepth( const lx_Xmlr  object_ );          /*P*/

LX_PUBLIC lx_Xmlr_TokenTypeEnum  lx_Xmlr_tokenType(                        /*P*/
    const lx_Xmlr  object_ );                                              /*-*/

LX_PUBLIC lx_chars_t  lx_Xmlr_tokenValue( const lx_Xmlr  object_ );        /*P*/

/* -------------------------------------------------------------------------- */
/* Properties: Token Class Querying                                           */

LX_PUBLIC lx_bool  lx_Xmlr_isComment( const lx_Xmlr  object_ );            /*P*/

/* -------------------------------------------------------------------------- */
/* Properties:                                                                */

/* returns the value of the current tag's attribute given by name_.           */
LX_PUBLIC lx_chars_t  lx_Xmlr_attr(                                        /*P*/
    const lx_Xmlr  object_,                                                /*-*/
    lx_chars_t     attr_name_ );                                           /*-*/

/* returns the value of the current tag's attribute at the given index.       */
LX_PUBLIC lx_chars_t  lx_Xmlr_attrByIndex(                                 /*P*/
    const lx_Xmlr  object_,                                                /*-*/
    const size_t   attr_index_ );                                          /*-*/

/* returns the number of attributes of the current tag.                       */
LX_PUBLIC size_t  lx_Xmlr_attrCount( const lx_Xmlr  object_ );             /*P*/

/* returns true if the current tag has an attribute given by name_.           */
LX_PUBLIC lx_bool  lx_Xmlr_attrExists(                                     /*P*/
    const lx_Xmlr  object_,                                                /*-*/
    lx_chars_t     attr_name_ );                                           /*-*/

/* returns the name of the current tag's attribute at the given index.        */
LX_PUBLIC lx_chars_t  lx_Xmlr_attrName(                                    /*P*/
    const lx_Xmlr  object_,                                                /*-*/
    const size_t   index_ );                                               /*-*/

/* returns a csv list created from all the current tag's attributes.          */
LX_PUBLIC lx_new_chars_t  lx_Xmlr_attrsToCsv( const lx_Xmlr  object_ );    /*M*/

/* returns true if the reading position is on the last token.                 */
LX_PUBLIC lx_bool  lx_Xmlr_eof( const lx_Xmlr  object_ );                  /*P*/

/* Composes and returns a string from the                                     */
/* contents of the current tag's child.                                       */
LX_PUBLIC lx_chars_t  lx_Xmlr_childContent(                                /*P*/
    const lx_Xmlr  object_,                                                /*-*/
    const lx_bool  indented_,                                              /*-*/
    lx_chars_t     search_expr_ );                                         /*-*/

#if 000  /* TODO: implement lx_Xmlr_childContentIndented() */
LX_PUBLIC lx_new_chars_t  lx_Xmlr_childContentIndented(                    /*P*/
    const lx_Xmlr  object_,                                                /*-*/
    lx_chars_t     search_expr_ );                                         /*-*/
#endif                                                                 /* 000 */

/* returns the number of direct descendant tags of the current tag.           */
/* (Only start-tags and empty tags are counted, excluding closing tags)       */
LX_PUBLIC size_t  lx_Xmlr_childCount(                                      /*P*/
    const lx_Xmlr  object_,                                                /*-*/
    lx_chars_t     search_expr_ );                                         /*-*/

/* Composes and returns a string from the contents of the current tag.        */
LX_PUBLIC lx_chars_t  lx_Xmlr_content(                                     /*P*/
    const lx_Xmlr  object_,                                                /*-*/
    const lx_bool  indented_ );                                            /*-*/

/* returns a string describing all member variables                           */
/* and arrays of this object.                                                 */
LX_PUBLIC lx_chars_t  lx_Xmlr_debugInfo( const lx_Xmlr  object_ );         /*P*/

/* returns a parsing error code, or LX_ERR_NONE                               */
/* if the last parse() was successful.                                        */
LX_PUBLIC lx_Xmlr_ParseErrorEnum  lx_Xmlr_errorCode(                       /*P*/
    const lx_Xmlr  object_ );                                              /*-*/

/* returns the column on the current line, where a parsing error occurred.    */
LX_PUBLIC size_t  lx_Xmlr_errorColumn( const lx_Xmlr  object_ );           /*P*/

/* returns the line number where a parsing error occurred.                    */
LX_PUBLIC size_t  lx_Xmlr_errorLine( const lx_Xmlr  object_ );             /*P*/

LX_PUBLIC lx_chars_t  lx_Xmlr_errorName( const lx_Xmlr  object_ );         /*P*/

/* returns a full error report, including error code,                         */
/* name and error line and column.                                            */
LX_PUBLIC lx_chars_t  lx_Xmlr_errorReport( const lx_Xmlr  object_ );       /*P*/

/* returns true if the current tag has a direct                               */
/* descendant matching the given criteria.                                    */
/* (Only start-tags and empty tags are considered)                            */
LX_PUBLIC lx_bool  lx_Xmlr_exists(                                         /*P*/
    const lx_Xmlr  object_,                                                /*-*/
    lx_chars_t     search_expr_ );                                         /*-*/

/* returns true if the current tag has any descendant                         */
/* matching the given criteria.                                               */
/* (Only start-tags and empty tags are considered)                            */
LX_PUBLIC lx_bool  lx_Xmlr_existsInner(                                    /*P*/
    const lx_Xmlr  object_,                                                /*-*/
    lx_chars_t     search_expr_ );                                         /*-*/

/* returns the current position of the cursor.                                */
LX_PUBLIC uint32_t  lx_Xmlr_position( const lx_Xmlr  object_ );            /*P*/

/* returns the number of direct or indirect                                   */
/* descendant tags of the current tag.                                        */
/* (Only start-tags and empty tags are counted, excluding closing tags)       */
LX_PUBLIC size_t  lx_Xmlr_innerCount(                                      /*P*/
    const lx_Xmlr  object_,                                                /*-*/
    lx_chars_t     search_expr_ );                                         /*-*/

/* returns true if the current tag's parent tag matches tag_name_             */
LX_PUBLIC lx_bool  lx_Xmlr_isParentTag(                                    /*P*/
    const lx_Xmlr  object_,                                                /*-*/
    lx_chars_t     tag_name_ );                                            /*-*/

/* returns true if the current token is a tag                                 */
/* (and if specified, matches tag_name_opt_)                                  */
LX_PUBLIC lx_bool  lx_Xmlr_isTagName(                                      /*P*/
    const lx_Xmlr  object_,                                                /*-*/
    lx_chars_t     tag_name_opt_ );                                        /*-*/

/* returns true if the object contains well-formed XML.                       */
LX_PUBLIC lx_bool  lx_Xmlr_isWellFormed(                                   /*P*/
    const lx_Xmlr  object_ );                                              /*-*/

/* returns the depth of the current tag.                                      */
LX_PUBLIC size_t  lx_Xmlr_tagDepth( const lx_Xmlr  object_ );              /*P*/

/* returns the name of the currently-selected tag.                            */
LX_PUBLIC lx_chars_t  lx_Xmlr_tagName( const lx_Xmlr  object_ );           /*P*/

/* returns the full text (including attributes)                               */
/* of the currently-selected tag.                                             */
LX_PUBLIC lx_chars_t  lx_Xmlr_tagText( const lx_Xmlr  object_ );           /*P*/

LX_PUBLIC size_t  lx_Xmlr_tokenCount( const lx_Xmlr  object_ );            /*P*/

/* Composes and returns an XML string from                                    */
/* the current tag and its contents.                                          */
LX_PUBLIC lx_chars_t  lx_Xmlr_text(                                        /*P*/
    const lx_Xmlr  object_,                                                /*-*/
    const lx_bool  indented_ );                                            /*-*/

/* -------------------------------------------------------------------------- */
/* Methods: Parsing                                                           */

/* Parses the given XML text and returns true if successful, or false         */
/* if the XML string is not well-formed. Use errorCode(), errorLine()         */
/* and errorColumn() to investigate the parsing error.                        */
LX_PUBLIC lx_bool  lx_Xmlr_parse(                                          /*M*/
    lx_Xmlr     object_,                                                   /*-*/
    lx_chars_t  xml_ );                                                    /*-*/

/* -------------------------------------------------------------------------- */
/* Methods: General                                                           */

LX_PUBLIC lx_new_chars_t  lx_Xmlr_keyValuesToCsv(                          /*M*/
    lx_Xmlr     object_,                                                   /*-*/
    lx_chars_t  container_element_,                                        /*-*/
    lx_chars_t  item_element_,                                             /*-*/
    lx_chars_t  key_attr_,                                                 /*-*/
    lx_chars_t  value_attr_ );                                             /*-*/

/* Removes all XML comments held in this object                               */
LX_PUBLIC lx_bool  lx_Xmlr_removeComments( lx_Xmlr  object_ );             /*M*/

/* -------------------------------------------------------------------------- */
/* Methods: Navigation                                                        */

LX_PUBLIC lx_bool  lx_Xmlr_goAnyNext(                                      /*M*/
    lx_Xmlr     object_,                                                   /*-*/
    lx_chars_t  search_expr_ );                                            /*-*/

/* Moves the cursor to an immediate child of the current tag,                 */
/* returning true if successful.                                              */
LX_PUBLIC lx_bool  lx_Xmlr_goChild(                                        /*M*/
    lx_Xmlr     object_,                                                   /*-*/
    lx_chars_t  search_expr_ );                                            /*-*/

/* Moves the cursor to a child or adjacent tag,                               */
/* returning true if successful.                                              */
LX_PUBLIC lx_bool  lx_Xmlr_goChildOrNext(                                  /*M*/
    lx_Xmlr     object_,                                                   /*-*/
    lx_chars_t  search_expr_ );                                            /*-*/

/* Moves the first tag on the depth of the current tag,                       */
/* returning true if successful.                                              */
LX_PUBLIC lx_bool  lx_Xmlr_goFirst(                                        /*M*/
    lx_Xmlr     object_,                                                   /*-*/
    lx_chars_t  search_expr_ );                                            /*-*/

/* Moves the cursor to the specified position.                                */
LX_PUBLIC lx_bool  lx_Xmlr_goPosition(                                     /*M*/
    lx_Xmlr         object_,                                               /*-*/
    const uint32_t  index_ );                                              /*-*/

/* Moves the cursor to a descendant of the current tag,                       */
/* returning true if successful.                                              */
LX_PUBLIC lx_bool  lx_Xmlr_goInner(                                        /*M*/
    lx_Xmlr     object_,                                                   /*-*/
    lx_chars_t  search_expr_ );                                            /*-*/

/* Moves the last tag on the depth of the current tag,                        */
/* returning true if successful.                                              */
LX_PUBLIC lx_bool  lx_Xmlr_goLast(                                         /*M*/
    lx_Xmlr     object_,                                                   /*-*/
    lx_chars_t  search_expr_ );                                            /*-*/

/* Moves the cursor to the tag following the current tag,                     */
/* returning true if successful.                                              */
LX_PUBLIC lx_bool  lx_Xmlr_goNext(                                         /*M*/
    lx_Xmlr     object_,                                                   /*-*/
    lx_chars_t  search_expr_ );                                            /*-*/

/* Moves the cursor to the parent of the current tag,                         */
/* returning true if successful.                                              */
LX_PUBLIC lx_bool  lx_Xmlr_goParent( lx_Xmlr  object_ );                   /*M*/

/* Moves the cursor to the tag preceding the current tag,                     */
/* returning true if successful.                                              */
LX_PUBLIC lx_bool  lx_Xmlr_goPrev(                                         /*M*/
    lx_Xmlr     object_,                                                   /*-*/
    lx_chars_t  search_expr_ );                                            /*-*/

/* Moves the cursor to the topmost tag.                                       */
LX_PUBLIC void  lx_Xmlr_goRoot( lx_Xmlr  object_ );                        /*M*/

LX_PUBLIC uint32_t  lx_Xmlr_skipElement( lx_Xmlr  object_ );               /*M*/

LX_PUBLIC uint32_t  lx_Xmlr_skipTag( lx_Xmlr  object_ );                   /*M*/

/* -------------------------------------------------------------------------- */
/* Static Functions:                                                          */

LX_PUBLIC lx_new_chars_t  lx_from_xml( lx_chars_t  xml_text_ );            /*F*/

/* TODO: lx_bool  hasNext( lx_chars_t  search_expr_ ) const; */

LX_END_NAMESPACE  /*lx_c*/
#endif                                                                   /*eof*/
