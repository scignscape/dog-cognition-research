
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


PROJECT_NAME = chasm-tr-parser

include(../build-group.pri)

QT -= gui

exists($$ROOT_DIR/../preferred/sysr.pri): include($$ROOT_DIR/../preferred/sysr.pri)
exists($$ROOT_DIR/../preferred/sysr-c.pri): include($$ROOT_DIR/../preferred/sysr-c.pri)
exists($$ROOT_DIR/../preferred/compiler.pri): include($$ROOT_DIR/../preferred/compiler.pri)

CONFIG += c++17


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR


INCLUDEPATH += $$SRC_GROUP_DIR/chasm-tr
message($$SRC_GROUP_DIR/chasm-tr)


CONFIG += no_keywords

DEFINES += USE_KANS
DEFINES += USE_AQNS



HEADERS += \
  $$SRC_DIR/grammar/chtr-graph-build.h \
  $$SRC_DIR/grammar/chtr-grammar.h \
  $$SRC_DIR/grammar/chtr-parse-context.h \
  $$SRC_DIR/grammar/chtr-parser.h \
  $$SRC_DIR/chtr-source-file.h \
  $$SRC_DIR/chtr-document.h \



SOURCES += \
  $$SRC_DIR/grammar/chtr-graph-build.cpp \
  $$SRC_DIR/grammar/chtr-grammar.cpp \
  $$SRC_DIR/grammar/chtr-parse-context.cpp \
  $$SRC_DIR/grammar/chtr-parser.cpp \
  $$SRC_DIR/chtr-source-file.cpp \
  $$SRC_DIR/chtr-document.cpp \



LIBS += -L$$TARGETSDIR -lchasm-tr


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

