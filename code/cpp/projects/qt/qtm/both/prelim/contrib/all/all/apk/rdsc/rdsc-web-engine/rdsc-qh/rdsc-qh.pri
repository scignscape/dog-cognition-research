
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = eqh-client

include(../build-group.pri)

QT += gui widgets webenginewidgets

exists($$ROOT_DIR/../preferred/sysr.pri): include($$ROOT_DIR/../preferred/sysr.pri)
exists($$ROOT_DIR/../preferred/sysr-c.pri): include($$ROOT_DIR/../preferred/sysr-c.pri)
exists($$ROOT_DIR/../preferred/compiler.pri): include($$ROOT_DIR/../preferred/compiler.pri)

CONFIG += c++17


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR



CONFIG += no_keywords

DEFINES += USE_KANS

DEFINES += SCREENSHOTS_FOLDER=\\\"$$ROOT_DIR/../dev/eqh\\\"
DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"

DEFINES += EMBER_PORT=6401


HEADERS += \
  $$SRC_DIR/JsInterface.h \


HEADERS += \
  $$SRC_DIR/qh-web-engine-view.h \
  $$SRC_DIR/qh-web-view-dialog.h \
  $$SRC_DIR/qh-web-engine-page.h \
  $$SRC_DIR/qh-web-page.h \
  $$SRC_DIR/qh-cross-map-coords.h \



SOURCES += \
  $$SRC_DIR/qh-web-engine-view.cpp \
  $$SRC_DIR/qh-web-view-dialog.cpp \
  $$SRC_DIR/qh-web-engine-page.cpp \
  $$SRC_DIR/qh-web-page.cpp \





message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

