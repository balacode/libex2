# ---------------------------------------------------------------------------- #
# ^^galaxy.sh

GRAPH_FILE="../dot/galaxy.graph";
PNG_FILE="../galaxy.jpeg";

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
SQL="SELECT Node FROM NodeV;";
echo $SQL | sqlite3 graph.db | sed 's/~1/    /g;' >> $GRAPH_FILE;

# connections between nodes
SQL="SELECT Link FROM LinkV;";
echo $SQL | sqlite3 graph.db | sed 's/~1/    /g;' >> $GRAPH_FILE;

# generate PNG file with Graphviz (neato)
echo '}' >> $GRAPH_FILE;
neato $GRAPH_FILE -Tjpeg > $PNG_FILE;

echo 'output ' $PNG_FILE;

#eof#
