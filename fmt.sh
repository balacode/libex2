# ^^fmt.sh

# NOTE: Run this script with Artistic Style Version 2.03 or greater
# An earlier version (2.01) reported 'Invalid command line options:'
# for: align-reference=type, break-after-logical, 1max-code-length=80

# other possible file types: *.cx, *.cxx, *.hx, *.hxx
# other styles: --style=horstmann --style=lisp

astyle $1 \
    --add-brackets \
    --align-pointer=type \
    --align-reference=type \
    --break-after-logical \
    --break-closing-brackets \
    --indent=spaces=4 \
    --indent-preprocessor \
    --indent-switches \
    --keep-one-line-blocks \
    --lineend=windows \
    --max-code-length=80 \
    --max-instatement-indent=40 \
    --min-conditional-indent=0 \
    --options=none \
    --pad-header \
    --pad-oper \
    --recursive \
    --style=stroustrup \
    --suffix=none \

#eof#
