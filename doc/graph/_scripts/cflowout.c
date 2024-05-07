/* -------------------------------------------------------------------------- */
/* cflowout.c                             Converts CFLOW output to SQL INSERT */
/*                                     statements or DOT nodes (for Graphviz) */
/* -------------------------------------------------------------------------- */
/*                                                                            */
/*  Usage:          cflow --main=unnamed --depth=2 filename.c                 */
/*                        | ./cflowout sql filename.c                         */
/*                                                                            */
/*                    or  | ./cflowout dot                                    */
/*                                                                            */
/*  To compile:     gcc cflowout.c -o cflowout                                */
/*                                                                            */
/*  Tested on:      Linux Mint 17 Qiana (on 2014-09-14)                       */
/*                  Debian 7                                                  */
/*                                                                            */
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/* Copyright:                   2014 Silvester Balarabe (rsvp.bala@gmail.com) */
/*                                                                            */
/* License:                     MIT                                           */
/*                                                                            */
/* Permission is hereby granted, free of charge, to any person obtaining a    */
/* copy of this software and associated documentation files (the "Software"), */
/* to deal in the Software without restriction, including without limitation  */
/* the rights to use, copy, modify, merge, publish, distribute, sublicense,   */
/* and/or sell copies of the Software, and to permit persons to whom the      */
/* Software is furnished to do so, subject to the following conditions:       */
/*                                                                            */
/* The above copyright notice and this permission notice shall be included    */
/* in all copies or substantial portions of the Software.                     */
/*                                                                            */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS    */
/* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF                 */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.     */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY       */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,       */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE          */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                     */
/* -------------------------------------------------------------------------- */


#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


/* -------------------------------------------------------------------------- */
/* standard lx-library definitions used here:                                 */


#define CLEAR( VARIABLE_ )  memset(&VARIABLE_, 0x00, sizeof(VARIABLE_))

#if defined __cplusplus
#define PUBLIC  extern "C"
#else                                                          /* __cplusplus */
#define PUBLIC
#endif                                                        /* !__cplusplus */

typedef enum  bool_t { false = 0, true = 1 } bool;


/* -------------------------------------------------------------------------- */


typedef enum  _m_output_mode_enum {
    MODE_UNKNOWN    = 0,                                 /* _output_mode_enum */
    MODE_GRAPH_NODE = 1,                                 /* _output_mode_enum */
    MODE_SQL        = 2                                  /* _output_mode_enum */
}
_output_mode_enum;


typedef struct  _args_t {
    _output_mode_enum  output_mode;                                /* _args_t */
    const char*        src_file;                                   /* _args_t */
    const char*        field_table_name;                           /* _args_t */
    const char*        field_source_file;                          /* _args_t */
    const char*        field_calling_fn;                           /* _args_t */
    const char*        field_called_fn;                            /* _args_t */
}
_args_t;


static void  _output_node(                                                 /*F*/
    const char*  call_from_,                                               /*-*/
    const char*  call_to_,                                                 /*-*/
    char*        temp_buffer_ ) {                                          /*-*/
    temp_buffer_[0] = '\0';

    /* DOT graph nodes */
    sprintf(temp_buffer_, "    \"%s()\" -> \"%s()\";\n",
            call_from_, call_to_);

    write(STDOUT_FILENO, temp_buffer_, strlen(temp_buffer_));
} /* _output_node */


static void  _output_sql(                                                  /*F*/
    _args_t*     args_,                                                    /*-*/
    const char*  call_from_,                                               /*-*/
    const char*  call_to_,                                                 /*-*/
    char*        temp_buffer_ ) {                                          /*-*/
    temp_buffer_[0] = '\0';

    sprintf(temp_buffer_, "INSERT INTO %s (%s, %s, %s)"
            " VALUES ('%s', '%s()', '%s()');\n",
            args_->field_table_name,
            args_->field_source_file,
            args_->field_calling_fn,
            args_->field_called_fn,
            args_->src_file,
            call_from_,
            call_to_);

    write(STDOUT_FILENO, temp_buffer_, strlen(temp_buffer_));
} /* _output_sql */


PUBLIC void  cflowout( _args_t*  args_ ) {                                 /*F*/
    char  temp_buf[1024];
    char  call_from[1024];
    char  call_to[1024];

    char*      name       = call_from;
    char       ch         = '\0';
    bool       is_newline = false;
    const int  rfile      = STDIN_FILENO;
    /* ^ for testing, use: rfile = open("/path/filename.txt", O_RDONLY); */

    CLEAR(temp_buf);
    CLEAR(call_from);
    CLEAR(call_to);

    while (read(rfile, &ch, 1) > 0) {
        if (is_newline) {
            is_newline = false;
            name  = (ch == ' ') ? call_to : call_from;
            *name = '\0';
        }

        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ||
            (ch >= '_') || (ch >= '0' && ch <= '9')) {
            *name++ = ch;

        } else if (ch == '(') {
            while (read(rfile, &ch, 1) > 0 &&
                   ch != '\n' &&  ch != '\0') {
                ;    /* null statement. skips all chars up to end of line. */
            }
        }

        if (ch == '\n' || ch == '\0') {
            if (strlen(call_from) > 0 && strlen(call_to) > 0) {
                *name = '\0';

                if (args_->output_mode == MODE_GRAPH_NODE) {
                    _output_node(call_from, call_to, temp_buf);

                } else if (args_->output_mode == MODE_SQL) {
                    _output_sql(args_, call_from, call_to, temp_buf);
                }
            }
            is_newline = true;
        }
    }
} /* cflowout */


PUBLIC int  main(                                                          /*F*/
    const int  argc_,                                                      /*-*/
    chars_t    argv_[] ) {                                                 /*-*/
    _args_t  args;
    CLEAR(args);

    if (argc_ == 3 && strcmp(argv_[1], "sql") == 0) {
        args.src_file = argv_[2];

#if 000 /* use this if you need to remove the path from the filename */
        args.src_file = rindex(argv_[2], '/');
        if (args.src_file == NULL) {
            args.src_file = argv_[2];
        } else {
            args.src_file++;
        }
#endif                                                                 /* 000 */

        if (args.src_file == NULL || strlen(args.src_file) < 1) {
            error(1, ENOENT, "Missing source file name.");
        }

        args.output_mode = MODE_SQL;
    } else if (argc_ == 2 && strcmp(argv_[1], "dot") == 0) {
        args.output_mode = MODE_GRAPH_NODE;
    } else {
        error(3, EINVAL, NULL);
    }

    if (args.output_mode == MODE_SQL) {
        args.field_table_name  = "CallT";
        args.field_source_file = "SourceFile";
        args.field_calling_fn  = "CallingFunc";
        args.field_called_fn   = "CalledFunc";
    }

    cflowout(&args);
    return 0;
} /* main */


/*eof*/
