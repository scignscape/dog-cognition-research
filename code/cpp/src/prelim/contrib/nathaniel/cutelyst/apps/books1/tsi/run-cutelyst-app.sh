# shell script to launch cutelyst generators ...
# note: the arguments after the cutelyst invocation will pass the -h
# argument unless this script is called with one or more alternative parameters
#
cd ../books1;
LD_LIBRARY_PATH=/home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/install/lib:\
/home/nlevisrael/Qt/5.15.2/gcc_64/lib:$LD_LIBRARY_PATH \
/home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/install/bin/cutelyst3-qt5 --server --app-file /home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/apps/books1/tsi/-build_/lib/libbooks1.so ;
cd --
