# shell script to launch the cutelyst console ...
#
cd ../Chasm-app;
LD_LIBRARY_PATH=/home/nlevisrael/Qt/5.15.2/gcc_64/lib:\
/home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/via-qtc/lib:\
$LD_LIBRARY_PATH \
/home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/via-qtc/bin/cutelyst-console --server --app-file /home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/apps/Chasm-app/tsi/-build_/lib/libChasm-app.so ;
cd --
