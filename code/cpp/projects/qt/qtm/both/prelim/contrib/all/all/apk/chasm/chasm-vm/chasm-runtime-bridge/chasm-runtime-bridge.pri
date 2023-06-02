
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

QT -= gui


include(../build-group.pri)


include($$ROOT_DIR/../preferred/sysr.pri)


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

# INCLUDEPATH += $$CHASM_LIB_SRC_GROUP_DIR
INCLUDEPATH += $$SRC_PROSET_DIR/chasm-lib


#INCLUDEPATH += $$NTXH_SRC_GROUP_DIR
#INCLUDEPATH += $$NTXH_SRC_GROUP_DIR/ntxh
#INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR
#INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
#INCLUDEPATH += $$HTXN_SRC_GROUP_DIR
#INCLUDEPATH += $$SRC_GROUP_DIR/gtagml


 # Most projects don't use ROOT_DIR as a basis
 # for includes but this one loads some generated
 # source code to experiment with ...
INCLUDEPATH += $$ROOT_DIR


DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"


DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES

CONFIG += no_keywords


DEFINES += USE_KANS


HEADERS += \
  $$SRC_DIR/chasm-runtime-bridge.h \
  $$SRC_DIR/csm-ghost-scope.h \
  $$SRC_DIR/chasm-runtime-eval.h \



SOURCES += \
  $$SRC_DIR/chasm-runtime-bridge.cpp \
  $$SRC_DIR/csm-ghost-scope.cpp \
  $$SRC_DIR/chasm-runtime-eval.cpp \



message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)


