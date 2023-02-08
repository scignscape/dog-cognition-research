
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


include(../build-group.pri)


QT -= gui

QT += xml


exists($$ROOT_DIR/../preferred/sysr.pri): include($$ROOT_DIR/../preferred/sysr.pri)
exists($$ROOT_DIR/../preferred/sysr-c.pri): include($$ROOT_DIR/../preferred/sysr-c.pri)
exists($$ROOT_DIR/../preferred/compiler.pri): include($$ROOT_DIR/../preferred/compiler.pri)
exists($$ROOT_DIR/../preferred/qt-version.pri): include($$ROOT_DIR/../preferred/qt-version.pri)



# greaterThan(4, QT_MAJOR_VERSION): QT +=

CONFIG += c++17


DEFINES += DEFAULT_DEV_TKRZW_FOLDER=\\\"$$ROOT_DIR/../dev/consoles/dgdb/tkrzw\\\"

DEFINES += DEFAULT_DEV_DGDB_FOLDER=\\\"$$ROOT_DIR/../dev/consoles/dgdb/instances\\\"



DEFINES += USE_KANS



INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR


INCLUDEPATH += $$TKRZW_SRC_GROUP_DIR/tkrzw
INCLUDEPATH += $$TKRZW_SRC_GROUP_DIR
INCLUDEPATH += $$WHITEDB_SRC_GROUP_DIR


INCLUDEPATH += $$SRC_PROSET_DIR/dgdb




HEADERS += \
  $$SRC_DIR/dgvm-runtime-environment.h \
  $$SRC_DIR/dgvm-runtime-environment.templates.h \
  $$SRC_DIR/dgvm-runtime.h \
  $$SRC_DIR/dgvm-runtime.templates.h \



SOURCES += \
  $$SRC_DIR/dgvm-runtime-environment.cpp \
  $$SRC_DIR/dgvm-runtime.cpp \



LIBS += -L$$TARGETSDIR -ldgdb

LIBS += -L$$TARGETSDIR -ltkrzw -llz4  -llzma -lz

LIBS += -L$$TARGETSDIR -lwhitedb


#LIBS += /home/nlevisrael/tkrzw/install/lib/libtkrzw.a  -llz4  -llzma -lz



