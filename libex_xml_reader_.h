/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                 [libex_xml_reader_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_XML_READER__H
#define      INCLUDED_LIBEX_XML_READER__H
#include "libex_xml_reader.h"

/* -------------------------------------------------------------------------- */

#define new_Xmlr                        lx_new_Xmlr
#define Xmlr                            lx_Xmlr

#define Xmlr_TokenTypeEnum              lx_Xmlr_TokenTypeEnum
#define XML_ATTR_NAME                   LX_XML_ATTR_NAME
#define XML_ATTR_VAL                    LX_XML_ATTR_VAL
#define XML_COMMENT_END_TAG             LX_XML_COMMENT_END_TAG
#define XML_COMMENT_START_TAG           LX_XML_COMMENT_START_TAG
#define XML_COMMENT_TEXT                LX_XML_COMMENT_TEXT
#define XML_EMPTY_TAG                   LX_XML_EMPTY_TAG
#define XML_END_TAG                     LX_XML_END_TAG
#define XML_START_TAG                   LX_XML_START_TAG
#define XML_TEXT                        LX_XML_TEXT
#define XML_UNKNOWN_TOKEN               LX_XML_UNKNOWN_TOKEN

#define Xmlr_ParseErrorEnum             lx_Xmlr_ParseErrorEnum
#define ERR_ALPHA                       LX_ERR_ALPHA
#define ERR_ASSIGN                      LX_ERR_ASSIGN
#define ERR_COLON                       LX_ERR_COLON
#define ERR_DOUBLE_QUOTE                LX_ERR_DOUBLE_QUOTE
#define ERR_ENDTAG_1                    LX_ERR_ENDTAG_1
#define ERR_ENDTAG_2                    LX_ERR_ENDTAG_2
#define ERR_NO_ROOT                     LX_ERR_NO_ROOT
#define ERR_NO_XML                      LX_ERR_NO_XML
#define ERR_NONE                        LX_ERR_NONE
#define ERR_NUMBER1                     LX_ERR_NUMBER1
#define ERR_NUMBER2                     LX_ERR_NUMBER2
#define ERR_QUOTE                       LX_ERR_QUOTE
#define ERR_SLASH                       LX_ERR_SLASH
#define ERR_START_TAG                   LX_ERR_START_TAG
#define ERR_SYMBOL                      LX_ERR_SYMBOL
#define ERR_TAG_MISMATCH                LX_ERR_TAG_MISMATCH
#define ERR_UNKNOWN_CHAR                LX_ERR_UNKNOWN_CHAR
#define ERR_WHITESPACE1                 LX_ERR_WHITESPACE1
#define ERR_WHITESPACE2                 LX_ERR_WHITESPACE2

#define XmlrToken                       lx_XmlrToken

/* -------------------------------------------------------------------------- */
/* Constructors / Destructor:                                                 */

#define Xmlr_init                       lx_Xmlr_init
#define Xmlr_of_chars                   lx_Xmlr_of_chars
#define Xmlr_of_file                    lx_Xmlr_of_file

#if 000   /* Uncomment when the copy constructor is implemented: */
#define Xmlr_copy                       lx_Xmlr_copy
#endif                                                                 /* 000 */

/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */

#define freeXmlr                        lx_freeXmlr

/* -------------------------------------------------------------------------- */
/* Properties: Metadata                                                       */

#define Xmlr_doctypeTag                 lx_Xmlr_doctypeTag

/* -------------------------------------------------------------------------- */
/* Properties: Token Querying                                                 */

#define Xmlr_tokenValue                 lx_Xmlr_tokenValue
#define Xmlr_tokenType                  lx_Xmlr_tokenType
#define Xmlr_tokenDepth                 lx_Xmlr_tokenDepth
#define Xmlr_isText                     lx_Xmlr_isText
#define Xmlr_isStartTag                 lx_Xmlr_isStartTag
#define Xmlr_isEndTag                   lx_Xmlr_isEndTag
#define Xmlr_isEmptyTag                 lx_Xmlr_isEmptyTag
#define Xmlr_isCommentText              lx_Xmlr_isCommentText
#define Xmlr_isCommentStartTag          lx_Xmlr_isCommentStartTag
#define Xmlr_isCommentEndTag            lx_Xmlr_isCommentEndTag
#define Xmlr_isAttributeValue           lx_Xmlr_isAttributeValue
#define Xmlr_isAttributeName            lx_Xmlr_isAttributeName

/* -------------------------------------------------------------------------- */
/* Properties: Token Class Querying                                           */

#define Xmlr_isComment                  lx_Xmlr_isComment

/* -------------------------------------------------------------------------- */
/* Properties:                                                                */

#define Xmlr_attr                       lx_Xmlr_attr
#define Xmlr_attrByIndex                lx_Xmlr_attrByIndex
#define Xmlr_attrCount                  lx_Xmlr_attrCount
#define Xmlr_attrExists                 lx_Xmlr_attrExists
#define Xmlr_attrName                   lx_Xmlr_attrName
#define Xmlr_attrsToCsv                 lx_Xmlr_attrsToCsv
#define Xmlr_childContent               lx_Xmlr_childContent
#define Xmlr_childCount                 lx_Xmlr_childCount
#define Xmlr_content                    lx_Xmlr_content
#define Xmlr_debugInfo                  lx_Xmlr_debugInfo
#define Xmlr_eof                        lx_Xmlr_eof
#define Xmlr_errorCode                  lx_Xmlr_errorCode
#define Xmlr_errorColumn                lx_Xmlr_errorColumn
#define Xmlr_errorLine                  lx_Xmlr_errorLine
#define Xmlr_errorName                  lx_Xmlr_errorName
#define Xmlr_errorReport                lx_Xmlr_errorReport
#define Xmlr_exists                     lx_Xmlr_exists
#define Xmlr_existsInner                lx_Xmlr_existsInner
#define Xmlr_innerCount                 lx_Xmlr_innerCount
#define Xmlr_isParentTag                lx_Xmlr_isParentTag
#define Xmlr_isTagName                  lx_Xmlr_isTagName
#define Xmlr_isWellFormed               lx_Xmlr_isWellFormed
#define Xmlr_position                   lx_Xmlr_position
#define Xmlr_tagDepth                   lx_Xmlr_tagDepth
#define Xmlr_tagName                    lx_Xmlr_tagName
#define Xmlr_tagText                    lx_Xmlr_tagText
#define Xmlr_text                       lx_Xmlr_text
#define Xmlr_tokenCount                 lx_Xmlr_tokenCount

/* -------------------------------------------------------------------------- */
/* Methods: Parsing                                                           */

#define Xmlr_parse                      lx_Xmlr_parse

/* -------------------------------------------------------------------------- */
/* Methods: General                                                           */

#define Xmlr_keyValuesToCsv             lx_Xmlr_keyValuesToCsv
#define Xmlr_removeComments             lx_Xmlr_removeComments

/* -------------------------------------------------------------------------- */
/* Methods: Navigation                                                        */

#define Xmlr_goAnyNext                  lx_Xmlr_goAnyNext
#define Xmlr_goChild                    lx_Xmlr_goChild
#define Xmlr_goChildOrNext              lx_Xmlr_goChildOrNext
#define Xmlr_goFirst                    lx_Xmlr_goFirst
#define Xmlr_goInner                    lx_Xmlr_goInner
#define Xmlr_goLast                     lx_Xmlr_goLast
#define Xmlr_goNext                     lx_Xmlr_goNext
#define Xmlr_goParent                   lx_Xmlr_goParent
#define Xmlr_goPosition                 lx_Xmlr_goPosition
#define Xmlr_goPrev                     lx_Xmlr_goPrev
#define Xmlr_goRoot                     lx_Xmlr_goRoot
#define Xmlr_skipElement                lx_Xmlr_skipElement
#define Xmlr_skipTag                    lx_Xmlr_skipTag

/* -------------------------------------------------------------------------- */
/* Static Functions:                                                          */

#define from_xml                        lx_from_xml

#endif                                                                   /*eof*/
