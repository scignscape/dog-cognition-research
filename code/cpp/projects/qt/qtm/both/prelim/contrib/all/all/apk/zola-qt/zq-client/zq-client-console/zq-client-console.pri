
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = zq-client-console

include(../build-group.pri)

TEMPLATE = app

QT += gui widgets webenginewidgets location

exists($$ROOT_DIR/../preferred/sysr.pri): include($$ROOT_DIR/../preferred/sysr.pri)
exists($$ROOT_DIR/../preferred/sysr-c.pri): include($$ROOT_DIR/../preferred/sysr-c.pri)
exists($$ROOT_DIR/../preferred/compiler.pri): include($$ROOT_DIR/../preferred/compiler.pri)

exists($$ROOT_DIR/../preferred/openssl.pri): include($$ROOT_DIR/../preferred/openssl.pri)

CONFIG += c++17


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$SRC_PROSET_DIR/../qmt-apache/qmt-native-client/MapGraphics

INCLUDEPATH += $$SRC_DIR/qmt-client


INCLUDEPATH += $$NTXH_SRC_GROUP_DIR
INCLUDEPATH += $$NTXH_SRC_GROUP_DIR/ntxh
INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR



CONFIG += no_keywords

DEFINES += USE_KANS

DEFINES += SCREENSHOTS_FOLDER=\\\"$$ROOT_DIR/../dev/zq\\\"
DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"

HEADERS += \

#INCLUDEPATH += \
#  $$SRC_GROUP_DIR/MapGraphics


HEADERS += \
  $$SRC_DIR/qmt-client/lanternfly/lanternfly-frame.h \
  $$SRC_DIR/qmt-client/main-window.h \
  $$SRC_DIR/qmt-client/lanternfly/lanternfly-sighting-dialog.h \
  $$SRC_DIR/qmt-client/lanternfly/lanternfly-configuration-dialog.h \
  $$SRC_DIR/qmt-client/lanternfly/lanternfly-sighting-filter-dialog.h \
  $$SRC_DIR/qmt-client/qmt-client-layer.h \
  $$SRC_DIR/qmt-client/qmt-client-context-menu-handler.h \
  $$SRC_DIR/qmt-client/qmt-client-location-focus.h \
  $$SRC_DIR/qmt-client/qmt-client-data-set.h \
  $$SRC_DIR/qmt-client/qmt-data-set-content-base.h \
  $$SRC_DIR/qmt-client/lanternfly-data-set.h \
  $$SRC_DIR/qmt-client/ses/ses-configuration-dialog.h \
  $$SRC_DIR/qmt-client/ses/ses-filter-dialog.h \
  $$SRC_DIR/qmt-client/ses/e-designation-dialog.h \


SOURCES += \
  $$SRC_DIR/qmt-client/lanternfly/lanternfly-frame.cpp \
  $$SRC_DIR/qmt-client/lanternfly/lanternfly-sighting-dialog.cpp \
  $$SRC_DIR/qmt-client/lanternfly/lanternfly-configuration-dialog.cpp \
  $$SRC_DIR/qmt-client/lanternfly/lanternfly-sighting-filter-dialog.cpp \
  $$SRC_DIR/qmt-client/main-window.cpp \
  $$SRC_DIR/main.cpp \
  $$SRC_DIR/qmt-client/qmt-client-layer.cpp \
  $$SRC_DIR/qmt-client/qmt-client-context-menu-handler.cpp \
  $$SRC_DIR/qmt-client/qmt-client-location-focus.cpp \
  $$SRC_DIR/qmt-client/qmt-client-data-set.cpp \
  $$SRC_DIR/qmt-client/qmt-data-set-content-base.cpp \
  $$SRC_DIR/qmt-client/lanternfly-data-set.cpp \
  $$SRC_DIR/qmt-client/ses/ses-configuration-dialog.cpp \
  $$SRC_DIR/qmt-client/ses/ses-filter-dialog.cpp \
  $$SRC_DIR/qmt-client/ses/e-designation-dialog.cpp \





#SOURCES += \
#  $$SRC_DIR/main.cpp \


LIBS += -L$$TARGETSDIR -lzq-client


LIBS += -L$$TARGETSDIR -lMapGraphics

#
LIBS += -L$$TARGETSDIR  \
  -lntxh  -lntxh-parser



message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

