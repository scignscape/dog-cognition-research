# shell script to launch cutelyst generators ...
# note: the arguments after the cutelyst invocation will pass the -h
# argument unless this script is called with one or more alternative parameters
#

#!/bin/bash
current_dir=${PWD##*/}
cd ..
appname=${PWD##*/} 
echo "Creating application, with name $appname"
cd $current_dir
./_run.sh --create-app $appname

