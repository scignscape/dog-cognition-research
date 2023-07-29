cmake=`cat ../preferred/which/cmake`
echo "Using cmake: $cmake"
$cmake \
 -D CMAKE_BUILD_TYPE=Debug \
 -D CMAKE_C_COMPILER=`cat ../preferred/which/gcc` \
 -D CMAKE_CXX_COMPILER=`cat ../preferred/which/g++` \
 -D CMAKE_PREFIX_PATH=`cat ../preferred/which/cmake-prefix-path` \
 -D CMAKE_INSTALL_PREFIX=../../install \
 -D PLUGIN_VIEW_GRANTLEE:BOOL=ON \
 ../../../cutelyst

# -D CMAKE_PREFIX_PATH=/quasihome/nlevisrael/opencv/xnfinstall/lib/cmake/opencv4/ \
# PLUGIN_VIEW_GRANTLEE:BOOL=OFF
#  -D QT_LIBS_DIR="/home/nlevisrael/Qt/5.15.2/gcc_64/lib/" \

