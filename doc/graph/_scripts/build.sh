# ---------------------------------------------------------------------------- #
# ^^build.sh

rm --force graph.db;
cat graph_db_create.sql | sqlite3 graph.db;

# ---------------------------------------------------------------------------- #

FORMATS_TEMP_SQL='temp/formats.temp.sql';

echo -e "BEGIN TRANSACTION;\n" > $FORMATS_TEMP_SQL;
cat formats.txt |
sed '/^ *\#/d;/^[ \r]*$/d' |
{
    while read LINE;
    do
    {
        FMT_NAME=`echo $LINE | sed 's/:.*$//'`;
        FMT_TEXT=`echo $LINE | sed 's/^.*://'`;

        echo -e " \
        \n    INSERT INTO FormatT(FormatName, FormatText) \
        \n                VALUES ('$FMT_NAME', '$FMT_TEXT'); \
        " >> $FORMATS_TEMP_SQL;
    }
    done
};
echo -e "\nCOMMIT TRANSACTION;\n" >> $FORMATS_TEMP_SQL;
cat $FORMATS_TEMP_SQL | sqlite3 graph.db;

# ---------------------------------------------------------------------------- #

NAMES_TEMP_SQL='temp/names.temp.sql';

echo -e "BEGIN TRANSACTION;\n" > $NAMES_TEMP_SQL;
cat names.txt |
sed '/^ *\#/d;/^[ \r]*$/d' |
{
    while read LINE;
    do
    {
        FUNC_NAME=`echo $LINE | sed 's/:.*$//'`;
        FMT_NAME=`echo $LINE | sed 's/^.*://'`;

        echo -e " \
        \n    INSERT INTO FuncNameT(FuncName, FormatName) \
        \n                  VALUES ('$FUNC_NAME', '$FMT_NAME'); \
        " >> $NAMES_TEMP_SQL;
    }
    done
};
echo -e "\nCOMMIT TRANSACTION;\n" >> $NAMES_TEMP_SQL;
cat $NAMES_TEMP_SQL | sqlite3 graph.db;

# ---------------------------------------------------------------------------- #

SQL="BEGIN TRANSACTION;\n\
DELETE FROM CallT;\n\
UPDATE FormatT     SET FormatName  = TRIM(FormatName),\n\
                       FormatText  = TRIM(FormatText),\n\
                       Notes       = TRIM(Notes);\n\
UPDATE FuncNameT   SET FuncName    = TRIM(FuncName),\n\
                       FormatName  = TRIM(FormatName);\n\
UPDATE CallT       SET CallingFunc = TRIM(CallingFunc),\n\
                       CalledFunc  = TRIM(CalledFunc);\n\
COMMIT TRANSACTION;\n";
echo -e $SQL | sqlite3 graph.db;


ls -1 ../../../*.c |
{
    while read C_FILE;
    do
    {
        echo 'reading' $C_FILE;

        TEMP_SQL=`echo $C_FILE \
        | sed 's/..\/..\/..\//temp\//g; s/\.c/.temp.sql/g'`;

        echo "BEGIN TRANSACTION;" > $TEMP_SQL;
        cflow $C_FILE --main=undefined_main --depth=2  2> /dev/null \
        | ./cflowout sql $C_FILE >> $TEMP_SQL;
        echo "COMMIT TRANSACTION;" >> $TEMP_SQL;
    	cat $TEMP_SQL | sqlite3 graph.db;


        GRAPH_FILE=`echo $C_FILE \
        | sed 's/..\/..\/..\//..\/dot\//g;   s/\.c/.graph/g'`;

        SVG_FILE=`echo $C_FILE \
        | sed 's/..\/..\///g;   s/\.c/.svg/g'`;

        PNG_FILE=`echo $C_FILE \
        | sed 's/..\/..\///g;   s/\.c/.png/g'`;

        echo -e 'digraph' \
        '\n{' \
        '\n    rankdir = LR' \
        '\n    node [' \
        '\n        shape=none' \
        '\n        style="filled"' \
        '\n        fillcolor="LightSteelBlue"' \
        '\n    ];' \
        '\n    edge [' \
        '\n        len=10' \
        '\n        color="NavyBlue"' \
        '\n    ];' > $GRAPH_FILE;

	# node attributes
	SQL="SELECT Node FROM NodeV WHERE SourceFile = '$C_FILE';";
	echo $SQL | sqlite3 graph.db | sed 's/~1/    /g;' >> $GRAPH_FILE;

        # connections between nodes
        SQL="SELECT Link FROM LinkV WHERE SourceFile = '$C_FILE';";
	echo $SQL | sqlite3 graph.db | sed 's/~1/    /g;' >> $GRAPH_FILE;

	# generate SVG file with Graphviz (dot)
        echo '}' >> $GRAPH_FILE;
        dot $GRAPH_FILE -Tsvg > $SVG_FILE;
        dot $GRAPH_FILE -Tpng > $PNG_FILE;

        echo 'output ' $SVG_FILE;
    }
    done
}

#eof#
