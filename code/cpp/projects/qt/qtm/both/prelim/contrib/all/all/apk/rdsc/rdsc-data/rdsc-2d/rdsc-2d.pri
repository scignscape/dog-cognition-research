
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


PROJECT_NAME = rdsc-2d


#QT -= gui

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

INCLUDEPATH += $$SRC_PROSET_DIR/rdsc-1d


CONFIG += no_keywords

DEFINES += USE_KANS

DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"

DEFINES += USE_XSNS


HEADERS += \
  $$SRC_DIR/mat2d.h \
  $$SRC_DIR/mat2d.templates.h \
  $$SRC_DIR/mat2d.templates_fetch.h \
  $$SRC_DIR/mat2d.templates.special-modes.h \
  $$SRC_DIR/mat2d.templates.special-modes_fetch.h \
  $$SRC_DIR/coords2d.h \



SOURCES += \
  $$SRC_DIR/mat2d.cpp \
  $$SRC_DIR/coords2d.cpp \


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

