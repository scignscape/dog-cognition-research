# shell script to launch cutelyst generators ...
# note: the arguments after the cutelyst invocation will pass the -h
# argument unless this script is called with one or more alternative parameters
#

#!/bin/bash

which_dir=../../../-build_/preferred/which
qtlib=`cat "$which_dir/cmake-prefix-path"`


prefix=`cat $which_dir/cmake-prefix-path`

re='(.*)\\\s+(.*)'
while [[ $prefix =~ $re ]]; do
  prefix=${BASH_REMATCH[1]}${BASH_REMATCH[2]}
done


re1ln='(.*)\\\s*'
if [[ $prefix =~ $re1ln ]]; then
  prefix=${BASH_REMATCH[1]}
fi


re_strip='(.*)/cmake/Qt[5-6];?'
if [[ $prefix =~ $re_strip ]]; then
  prefix=${BASH_REMATCH[1]}
fi

cd ..

appname=${PWD##*/} 

mkdir -p $appname

install_dir=../../-build_/install

LD_LIBRARY_PATH=$prefix:$install_dir/lib:$LD_LIBRARY_PATH \
$install_dir/bin/cutelyst3-qt5 ${1:-h} ${@:2:$#} 



