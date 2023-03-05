
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = rdsc-runtime-console

include(../build-group.pri)


#QT += gui widgets webenginewidgets location

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
  $$SRC_DIR/qhr/qh-runtime.h \
  $$SRC_DIR/qhr/qh-type.h \
  $$SRC_DIR/qhr/qh-type-system.h \
  $$SRC_DIR/qh-pack-code.h \
  $$SRC_DIR/qh-pack-builder.h \
  $$SRC_DIR/qh-pack-reader.h \
  $$SRC_DIR/qh-class-object.h \
  $$SRC_DIR/qh-field-info.h \
  $$SRC_DIR/graphs/qh-hyperedge-dominion.h \
  $$SRC_DIR/graphs/qh-hypernode.h \
  $$SRC_DIR/graphs/qh-node-data.h \
  $$SRC_DIR/graphs/qh-node-frame.h \
  $$SRC_DIR/graphs/qh-hyperedge.h \
  $$SRC_DIR/json/qh-json-file-reader.h \
  $$SRC_DIR/json/pseudo-jpath.h \

#$$SRC_DIR/json/JsonWax/JsonWax.h \
#  $$SRC_DIR/json/JsonWax/JsonWaxEditor.h \
#  $$SRC_DIR/json/JsonWax/JsonWaxParser.h \
#  $$SRC_DIR/json/JsonWax/JsonWaxSerializer.h \


SOURCES += \
  $$SRC_DIR/qhr/qh-runtime.cpp \
  $$SRC_DIR/qhr/qh-type.cpp \
  $$SRC_DIR/qhr/qh-type-system.cpp \
  $$SRC_DIR/qh-pack-code.cpp \
  $$SRC_DIR/qh-pack-builder.cpp \
  $$SRC_DIR/qh-pack-reader.cpp \
  $$SRC_DIR/qh-class-object.cpp \
  $$SRC_DIR/qh-field-info.cpp \
  $$SRC_DIR/graphs/qh-hyperedge-dominion.cpp \
  $$SRC_DIR/graphs/qh-hypernode.cpp \
  $$SRC_DIR/graphs/qh-node-data.cpp \
  $$SRC_DIR/graphs/qh-node-frame.cpp \
  $$SRC_DIR/graphs/qh-hyperedge.cpp \
  $$SRC_DIR/json/qh-json-file-reader.cpp \
  $$SRC_DIR/json/pseudo-jpath.cpp \


#LIBS += -L$$TARGETSDIR -lrdsc-runtime



message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

