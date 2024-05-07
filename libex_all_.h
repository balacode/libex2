/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                        [libex_all_.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_ALL__H
#define      INCLUDED_LIBEX_ALL__H

/* NOTE: "libex_network_.h" is not included, */
/*       you need to include it separately     */

#include "libex_config_.h"
/* Automatically defines PLATFORM_LINUX and PLATFORM_WIN32                 */
/* Both constants get defined, but one will be 0 while the other will be 1 */

/* -------------------------------------------------------------------------- */
/* Core Headers: */

#include "libex_.h"                 /* Defines common types and constructs    */
#include "libex_call_.h"            /* CALL_TRACE, GO, RETURN, fn_call_...    */
#include "libex_const_.h"           /* Defines numeric and string constants   */
#include "libex_debug_.h"           /* Debugging functions and macros         */
#include "libex_error_.h"           /* Error handling functions and macros    */
#include "libex_libc_.h"            /* Standard library aliases and functions */
#include "libex_macro_.h"           /* Various macros                         */

/* -------------------------------------------------------------------------- */

#include "libex_archive_.h"
#include "libex_array_.h"
#include "libex_byte_array_.h"
#include "libex_bytes_.h"
#include "libex_canvas_.h"
#include "libex_clipboard_.h"
#include "libex_color_.h"
#include "libex_console_.h"
#include "libex_crypto_.h"
#include "libex_csv_.h"
#include "libex_dtime_.h"
#include "libex_file_.h"
#include "libex_font_.h"
#include "libex_functions_.h"
#include "libex_hash_.h"
#include "libex_html_functions_.h"
#include "libex_html_generator_.h"
#include "libex_html_list_.h"
#include "libex_http_app_.h"
#include "libex_http_server_.h"
#include "libex_key_.h"
#include "libex_language_.h"
#include "libex_logging_.h"
#include "libex_mutex_.h"
#include "libex_number_.h"
#include "libex_pdf_.h"
#include "libex_pdf_report_.h"
#include "libex_string_class_.h"
#include "libex_stringc_.h"
#include "libex_system_.h"
#include "libex_type_.h"
#include "libex_variant_functions_.h"
#include "libex_xml_reader_.h"

#if PLATFORM_WIN32
#include "libex_ado_connection_.h"
#include "libex_win_registry_.h"
#include "libex_win32_.h"
#endif

#endif                                                                   /*eof*/
