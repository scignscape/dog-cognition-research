
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


PROJECT_NAME = xcsd-1d


QT -= gui

include(../build-group.pri)

!contains(QT, gui){
message($$PROJECT_NAME: $$QT)
DEFINES += HAVE_NO_QT_GUI_MODULE
}


include($$ROOT_DIR/../preferred/compiler.pri)

CONFIG += c++17


include($$ROOT_DIR/../preferred/sysr.pri)


DEFINES += USE_XCNS


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR



CONFIG += no_keywords

DEFINES += USE_KANS


HEADERS += \
  $$SRC_DIR/arr1d.h \
  $$SRC_DIR/deq1d.h \
  $$SRC_DIR/dsk1d.h \
  $$SRC_DIR/que1d.h \
  $$SRC_DIR/stk1d.h \
  $$SRC_DIR/vec1d.h \
  $$SRC_DIR/_vec1d.h \
  $$SRC_DIR/hive-structure.h \
  $$SRC_DIR/hive-structure.templates.h \
  $$SRC_DIR/_each-holders.h \



SOURCES += \
  $$SRC_DIR/hive-structure.cpp \


#LIBS += -L$$TARGETSDIR -lxcsd-1d



message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

