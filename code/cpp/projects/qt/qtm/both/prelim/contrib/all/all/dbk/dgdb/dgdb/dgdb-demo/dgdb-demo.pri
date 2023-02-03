
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


CONFIG += c++17


DEFINES += DEFAULT_DEV_TKRZW_FOLDER=\\\"$$ROOT_DIR/../dev/consoles/dgdb/tkrzw\\\"

DEFINES += DEFAULT_DEV_DGDB_FOLDER=\\\"$$ROOT_DIR/../dev/consoles/dgdb/instances\\\"



DEFINES += USE_KANS



INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR


INCLUDEPATH += $$TKRZW_SRC_GROUP_DIR/tkrzw
INCLUDEPATH += $$TKRZW_SRC_GROUP_DIR
INCLUDEPATH += $$WHITEDB_SRC_GROUP_DIR





HEADERS += \
  $$SRC_DIR/test-class.h \
  $$SRC_DIR/demo-class.h \
  $$SRC_DIR/queue-demo-class.h \


SOURCES += \
  $$SRC_DIR/test-class.cpp \
  $$SRC_DIR/demo-class.cpp \
  $$SRC_DIR/queue-demo-class.cpp \


LIBS += -L$$TARGETSDIR -ldgdb

LIBS += -L$$TARGETSDIR -ltkrzw -llz4  -llzma -lz

LIBS += -L$$TARGETSDIR -lwhitedb


#LIBS += /home/nlevisrael/tkrzw/install/lib/libtkrzw.a  -llz4  -llzma -lz



