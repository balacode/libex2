# ^^clang.sh: Shows all warnings and errors generated by CLANG, without compiling object files

rm *.o 2> /dev/null                                  > __clang.txt

clang -c -Wall -Wextra libex_archive.c             2>> __clang.txt
clang -c -Wall -Wextra libex_array.c               2>> __clang.txt
clang -c -Wall -Wextra libex_byte_array.c          2>> __clang.txt
clang -c -Wall -Wextra libex_bytes.c               2>> __clang.txt
clang -c -Wall -Wextra libex_c_precompiled.c       2>> __clang.txt
clang -c -Wall -Wextra libex_canvas.c              2>> __clang.txt
clang -c -Wall -Wextra libex_clipboard.c           2>> __clang.txt
clang -c -Wall -Wextra libex_color.c               2>> __clang.txt
clang -c -Wall -Wextra libex_console.c             2>> __clang.txt
clang -c -Wall -Wextra libex_crypto.c              2>> __clang.txt
clang -c -Wall -Wextra libex_csv.c                 2>> __clang.txt
clang -c -Wall -Wextra libex_dtime.c               2>> __clang.txt
clang -c -Wall -Wextra libex_file.c                2>> __clang.txt
clang -c -Wall -Wextra libex_font.c                2>> __clang.txt
clang -c -Wall -Wextra libex_functions.c           2>> __clang.txt
clang -c -Wall -Wextra libex_hash.c                2>> __clang.txt
clang -c -Wall -Wextra libex_html_functions.c      2>> __clang.txt
clang -c -Wall -Wextra libex_html_generator.c      2>> __clang.txt
clang -c -Wall -Wextra libex_html_list.c           2>> __clang.txt
clang -c -Wall -Wextra libex_http_server.c         2>> __clang.txt
clang -c -Wall -Wextra libex_key.c                 2>> __clang.txt
clang -c -Wall -Wextra libex_language.c            2>> __clang.txt
clang -c -Wall -Wextra libex_libc.c                2>> __clang.txt
clang -c -Wall -Wextra libex_logging.c             2>> __clang.txt
clang -c -Wall -Wextra libex_mutex.c               2>> __clang.txt
clang -c -Wall -Wextra libex_network.c             2>> __clang.txt
clang -c -Wall -Wextra libex_number.c              2>> __clang.txt
clang -c -Wall -Wextra libex_object_wrapper.inc.c  2>> __clang.txt
clang -c -Wall -Wextra libex_pdf.c                 2>> __clang.txt
clang -c -Wall -Wextra libex_pdf_report.c          2>> __clang.txt
clang -c -Wall -Wextra libex_point.c               2>> __clang.txt
clang -c -Wall -Wextra libex_string_class.c        2>> __clang.txt
clang -c -Wall -Wextra libex_stringc.c             2>> __clang.txt
clang -c -Wall -Wextra libex_system.c              2>> __clang.txt
clang -c -Wall -Wextra libex_variant_functions.c   2>> __clang.txt
clang -c -Wall -Wextra libex_win_registry.c        2>> __clang.txt
clang -c -Wall -Wextra libex_xml_reader.c          2>> __clang.txt

rm *.o 2> /dev/null
cat __clang.txt
