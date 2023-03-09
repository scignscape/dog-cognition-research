
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = ngml-sdi-console

include(../build-group.pri)

QT -= gui

include($$ROOT_DIR/../preferred/sysr.pri)

TEMPLATE = app

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$DGH_SDI_SRC_GROUP_DIR

INCLUDEPATH += $$NTXH_SRC_GROUP_DIR

INCLUDEPATH += $$NTXH_SRC_GROUP_DIR/ntxh
INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR

INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR

DEFINES += DEFAULT_GTAGML_FOLDER=\\\"$$ROOT_DIR/dev/consoles/gtagml/gt\\\"

#DEFINES += DEFAULT_SDI_FOLDER=\\\"$$ROOT_DIR/dev/consoles/gtagml/sdi\\\"

DEFINES += DEFAULT_SDI_FOLDER=\\\"$$ROOT_DIR/../dev/documents\\\"

DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"

CONFIG += no_keywords

DEFINES += CAON_DEBUG

DEFINES += USE_KANS

DEFINES += RELAE_LABEL_NODES

HEADERS += \

SOURCES += \
  $$SRC_DIR/main.cpp \


LIBS += -L$$TARGETSDIR -lngml-sdi -lntxh-parser -lntxh  \
  -ldgh-sdi  -lquazip

# no longer applicable?
#QUA_ZIP_LIB_DIR = $$TARGETSDIR
#defined(QUA_ZIP_LIB_DIR, var) { LIBS += -L$$QUA_ZIP_LIB_DIR  -lquazip }



message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

