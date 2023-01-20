
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


include(../build-group.pri)

TEMPLATE = app

QT -= gui

exists($$ROOT_DIR/../preferred/sysr.pri): include($$ROOT_DIR/../preferred/sysr.pri)
exists($$ROOT_DIR/../preferred/sysr-c.pri): include($$ROOT_DIR/../preferred/sysr-c.pri)
exists($$ROOT_DIR/../preferred/compiler.pri): include($$ROOT_DIR/../preferred/compiler.pri)


DEFINES += DEFAULT_DEV_TKRZW_FOLDER=\\\"$$ROOT_DIR/../dev/consoles/dgdb/tkrzw\\\"

DEFINES += USE_KANS


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

INCLUDEPATH += $$SRC_GROUP_DIR/tkrzw

#INCLUDEPATH += /home/nlevisrael/tkrzw/install/include

DEFINES += _TKRZW_PKG_VERSION=\\\"1.1.0\\\"
DEFINES += _TKRZW_PKG_VERSION=\\\"1.1.0\\\"


HEADERS += \


SOURCES += \
  $$SRC_DIR/main.cpp \


LIBS += -L$$TARGETSDIR -ltkrzw -llz4  -llzma -lz

#LIBS += /home/nlevisrael/tkrzw/install/lib/libtkrzw.a  -llz4  -llzma -lz



