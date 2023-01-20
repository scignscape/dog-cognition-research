
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


include(../build-group.pri)


QT -= gui

exists($$ROOT_DIR/../preferred/sysr.pri): include($$ROOT_DIR/../preferred/sysr.pri)
exists($$ROOT_DIR/../preferred/sysr-c.pri): include($$ROOT_DIR/../preferred/sysr-c.pri)
exists($$ROOT_DIR/../preferred/compiler.pri): include($$ROOT_DIR/../preferred/compiler.pri)


CONFIG += c++17

DEFINES += USE_KANS


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

#? INCLUDEPATH += $$SRC_KERNEL_DIR/whitedb/whitedb 

INCLUDEPATH += $$NTXH_SRC_GROUP_DIR  $$NTXH_SRC_GROUP_DIR/ntxh 
INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$WHITEDB_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR


HEADERS += \
  $$SRC_DIR/wdb-manager.h  \
  $$SRC_DIR/dw-manager.h  \
  $$SRC_DIR/wdb-instance.h  \
  $$SRC_DIR/dw-instance.h  \
  $$SRC_DIR/dw-record.h  \
  $$SRC_DIR/dw-stage-value.h  \
  $$SRC_DIR/dgenvironment.h  \
  $$SRC_DIR/dw-frame.h  \
  $$SRC_DIR/dw-dominion.h  \
  $$SRC_DIR/dw-query-layer.h  \
  $$SRC_DIR/stage/dw-stage-queue.h  \
  $$SRC_DIR/types/dw-type.h  \
  $$SRC_DIR/types/dw-type-system.h  \
  $$SRC_DIR/types/dw-type-builder.h  \


SOURCES += \
  $$SRC_DIR/wdb-manager.cpp  \
  $$SRC_DIR/dw-manager.cpp  \
  $$SRC_DIR/wdb-instance.cpp  \
  $$SRC_DIR/dw-instance.cpp  \
  $$SRC_DIR/dw-record.cpp  \
  $$SRC_DIR/dw-stage-value.cpp  \
  $$SRC_DIR/dgenvironment.cpp  \
  $$SRC_DIR/dw-frame.cpp  \
  $$SRC_DIR/dw-dominion.cpp  \
  $$SRC_DIR/dw-query-layer.cpp  \
  $$SRC_DIR/stage/dw-stage-queue.cpp  \
  $$SRC_DIR/types/dw-type.cpp  \
  $$SRC_DIR/types/dw-type-system.cpp  \
  $$SRC_DIR/types/dw-type-builder.cpp  \



LIBS += -L$$TARGETSDIR -lwhitedb  \
  -lntxh  -lntxh-parser


