
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


PROJECT_NAME = chtr

include(../build-group.pri)

QT -= gui

exists($$ROOT_DIR/../preferred/sysr.pri): include($$ROOT_DIR/../preferred/sysr.pri)
exists($$ROOT_DIR/../preferred/sysr-c.pri): include($$ROOT_DIR/../preferred/sysr-c.pri)
exists($$ROOT_DIR/../preferred/compiler.pri): include($$ROOT_DIR/../preferred/compiler.pri)

CONFIG += c++17


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR



CONFIG += no_keywords

DEFINES += USE_KANS
DEFINES += USE_AQNS


HEADERS += \
  $$SRC_DIR/source-char-token.h \


SOURCES += \
  $$SRC_DIR/source-char-token.cpp \



HEADERS += \
  $$SRC_DIR/kernel/chtr-dominion.h \
  $$SRC_DIR/kernel/frame/chtr-frame.h \
  $$SRC_DIR/kernel/query/chtr-query.h \
  $$SRC_DIR/kernel/graph/chtr-node.h \
  $$SRC_DIR/kernel/graph/chtr-graph.h \


SOURCES += \
  $$SRC_DIR/kernel/chtr-dominion.cpp \
  $$SRC_DIR/kernel/frame/chtr-frame.cpp \
  $$SRC_DIR/kernel/query/chtr-query.cpp \
  $$SRC_DIR/kernel/graph/chtr-node.cpp \
  $$SRC_DIR/kernel/graph/chtr-graph.cpp \




message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

