#!/bin/bash

cmake=`cat ../../preferred/which/cmake`
echo "Using cmake: $cmake"

prefix=`cat ../../preferred/which/cmake-prefix-path`

re='(.*)\\\s+(.*)'
while [[ $prefix =~ $re ]]; do
  prefix=${BASH_REMATCH[1]}${BASH_REMATCH[2]}
done

echo "Using prefix-path: $prefix"
$cmake \
 -D CMAKE_BUILD_TYPE=Debug \
 -D CMAKE_C_COMPILER=`cat ../../preferred/which/cc` \
 -D CMAKE_CXX_COMPILER=`cat ../../preferred/which/cxx` \
 -D CMAKE_PREFIX_PATH="$prefix" \
 -D CMAKE_INSTALL_PREFIX=../../install \
 -D PLUGIN_VIEW_GRANTLEE:BOOL=ON \
 ../../../framework

# -D CMAKE_PREFIX_PATH=/quasihome/nlevisrael/opencv/xnfinstall/lib/cmake/opencv4/ \
# PLUGIN_VIEW_GRANTLEE:BOOL=OFF
#  -D QT_LIBS_DIR="/home/nlevisrael/Qt/5.15.2/gcc_64/lib/" \

