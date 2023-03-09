
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = ngml-sdi

include(../build-group.pri)

QT -= gui

include($$ROOT_DIR/../preferred/sysr.pri)

INCLUDEPATH +=   $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$NTXH_SRC_GROUP_DIR
INCLUDEPATH += $$NTXH_SRC_GROUP_DIR/ntxh
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR

INCLUDEPATH += $$DGH_SDI_SRC_GROUP_DIR


QUA_ZIP_PATH = $$QUA_ZIP_SRC_GROUP_DIR

defined(QUA_ZIP_PATH, var) { INCLUDEPATH += $$QUA_ZIP_SRC_GROUP_DIR
  DEFINES += USING_ZIP
}


DEFINES += DEFAULT_NTXH_FOLDER=\\\"$$DEV_ROOT_DIR/ntxh\\\"

DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES

CONFIG += no_keywords


DEFINES += USE_KANS


HEADERS += \
  $$SRC_DIR/nds-project.h \
  $$SRC_DIR/nds-paragraph.h \
  $$SRC_DIR/nds-sentence.h \


SOURCES += \
  $$SRC_DIR/nds-project.cpp \
  $$SRC_DIR/nds-paragraph.cpp \
  $$SRC_DIR/nds-sentence.cpp \


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

