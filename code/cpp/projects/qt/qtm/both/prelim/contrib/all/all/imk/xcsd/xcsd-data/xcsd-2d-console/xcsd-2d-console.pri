
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


PROJECT_NAME = xcsd-2d-console

include(../build-group.pri)

INCLUDEPATH += $$SRC_PROSET_DIR/xcsd-1d


#QT -= gui

!contains(QT, gui){
message($$PROJECT_NAME: $$QT)
DEFINES += HAVE_NO_QT_GUI_MODULE
}

TEMPLATE = app

include($$ROOT_DIR/../preferred/sysr.pri)

DEFINES += USE_XCNS

include($$ROOT_DIR/../preferred/compiler.pri)

CONFIG += c++17

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR

DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"

CONFIG += no_keywords

DEFINES += USE_KANS

DEFINES += USE_XSNS

HEADERS += \


SOURCES += \
  $$SRC_DIR/main.cpp \


LIBS += -L$$TARGETSDIR -lxcsd-1d -lxcsd-2d


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

