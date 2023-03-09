
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


include(../build-group.pri)

QT += gui widgets

include($$ROOT_DIR/../preferred/sysr.pri)

#include($$ROOT_DIR/../preferred/sysr-c.pri)

DEFINES += DEFAULT_GTAGML_GEN_FOLDER=\\\"$$ROOT_DIR/../gtagml\\\"

DEFINES += DEFAULT_DEV_DGDB_NGML_FOLDER=\\\"$$ROOT_DIR/../gtagml/dgdb\\\"

DEFINES += DEFAULT_SDI_FOLDER=\\\"$$ROOT_DIR/dev/consoles/gtagml/sdi\\\"

DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"

DEFINES += USE_KANS


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$WHITEDB_SRC_GROUP_DIR

INCLUDEPATH += $$SRC_GROUP_DIR/dgdb-white

INCLUDEPATH += $$SRC_GROUP_DIR/

INCLUDEPATH += $$SRC_ROOT_DIR/apk/gtagml/gtagml
INCLUDEPATH += $$SRC_ROOT_DIR/apk/hgdm/ntxh
INCLUDEPATH += $$SRC_ROOT_DIR/apk/hgdm/ntxh/ntxh


INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR

INCLUDEPATH += $$GTAGML_SRC_GROUP_DIR/gtagml
INCLUDEPATH += $$GTAGML_SRC_GROUP_DIR

message(GTAGML_SRC_GROUP_DIR: $$GTAGML_SRC_GROUP_DIR/gtagml)

HEADERS += \
  $$SRC_DIR/gt-module-ir.h \
  $$SRC_DIR/gtagml-dgh-module.h \


SOURCES += \
  $$SRC_DIR/gt-module-ir.cpp \
  $$SRC_DIR/gtagml-dgh-module.cpp \




LIBS += -L$$TARGETSDIR  \
  -lntxh  -lntxh-parser

#-lngml-sdi
#LIBS += -L$$TARGETSDIR -ldgh-sdi-repl-mw

LIBS += -L$$TARGETSDIR -lgtagml

