# delete all generated files

rm ../*.svg           2> /dev/null
rm cflowout           2> /dev/null
rm graph.db           2> /dev/null
rm temp/*.dot_graph   2> /dev/null
rm temp/*.sql         2> /dev/null

# recompile and run all scripts

gcc -Wall -Wextra cflowout.c -o cflowout
./build.sh
