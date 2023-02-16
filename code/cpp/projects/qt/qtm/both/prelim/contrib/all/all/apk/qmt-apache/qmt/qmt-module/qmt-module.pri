
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
  $$SRC_GROUP_DIR/qmt-utils/qmt-utils.h \
  $$SRC_GROUP_DIR/qmt-utils/qmt-utils.hpp \


HEADERS += \
  $$SRC_GROUP_DIR/qmt-accessors.h \
  $$SRC_GROUP_DIR/qmt-global-types.h \


SOURCES += \
  $$SRC_GROUP_DIR/qmt-utils/qmt-utils.cpp \


#$$SRC_GROUP_DIR/qmt-server/qmt-server-response.cpp \
#  $$SRC_GROUP_DIR/qmt-server/qmt-server-response.h \


SOURCES += \
  $$SRC_DIR/qmt-module.c \


#/home/nlevisrael/gits/ctg-temp/ar/code/cpp/src/dbk/qmt-apache/qmt/qmt-server/qmt-raw-file-server-response.h


# LoadModule qmt_module /home/nlevisrael/gits/ctg-temp/ar/code/cpp/targets/qt/qt-multiple/nomark/targets-5-15-2-Desktop_Qt_5_15_2_GCC_64bit/libqmt-module.so.1.0.0

