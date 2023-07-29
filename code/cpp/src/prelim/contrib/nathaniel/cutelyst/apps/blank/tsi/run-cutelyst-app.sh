# shell script to launch cutelyst generators ...
# note: the arguments after the cutelyst invocation will pass the -h
# argument unless this script is called with one or more alternative parameters
#
cd ../`pwd`;
LD_LIBRARY_PATH=??:\
??:$LD_LIBRARY_PATH \
??/install/bin/cutelyst3-qt5 --server --app-file ??/tsi/-build_/lib/libbHello.so ;
cd --
