# shell script to launch the cutelyst console ...
#
cd ../Chasm-app;
LD_LIBRARY_PATH=/home/nlevisrael/Qt/5.15.2/gcc_64/lib:\
/home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/install/lib:\
$LD_LIBRARY_PATH \
/home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/install/bin/cutelyst3-qt5 --server --app-file /home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/apps/Chasm-app/tsi/-build_/lib/libChasm_app.so ;
cd --
