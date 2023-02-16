
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


include(../build-group.pri)


QT += network

TEMPLATE = lib


include($$ROOT_DIR/../preferred/apache.pri)

QMAKE_CC = gcc-7
QMAKE_CXX = g++-7

CONFIG += c++17



INCLUDEPATH += $$SRC_GROUP_DIR



INCLUDEPATH += \
  $${APACHE_INCLUDE_DIR}



HEADERS += \
  $$ALT_SRC_DIR/raw-file/qmt-raw-file-server-response.h \


SOURCES += \
  $$ALT_SRC_DIR/raw-file/qmt-raw-file-server-response.cpp \


HEADERS += \
  $$SRC_PROSET_DIR/qmt/qmt-resource-info.h


SOURCES += \
  $$SRC_PROSET_DIR/qmt/qmt-resource-info.cpp

# LoadModule qmt_module /home/nlevisrael/gits/ctg-temp/ar/code/cpp/targets/qt/qt-multiple/nomark/targets-5-15-2-Desktop_Qt_5_15_2_GCC_64bit/libqmt-module.so.1.0.0

