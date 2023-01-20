
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


include(../build-group.pri)


QT -= gui

QT += xml


exists($$ROOT_DIR/../preferred/sysr.pri): include($$ROOT_DIR/../preferred/sysr.pri)
exists($$ROOT_DIR/../preferred/sysr-c.pri): include($$ROOT_DIR/../preferred/sysr-c.pri)
exists($$ROOT_DIR/../preferred/compiler.pri): include($$ROOT_DIR/../preferred/compiler.pri)


CONFIG += c++17


DEFINES += USE_KANS



INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

DEFINES += _FTOK_CHAR=\\\'~\\\'


INCLUDEPATH += $$TKRZW_SRC_GROUP_DIR
INCLUDEPATH += $$WHITEDB_SRC_GROUP_DIR

#? INCLUDEPATH += $$SRC_KERNEL_DIR/whitedb/whitedb 

#INCLUDEPATH += $$NTXH_SRC_GROUP_DIR  $$NTXH_SRC_GROUP_DIR/ntxh
#INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
#INCLUDEPATH += $$WHITEDB_SRC_GROUP_DIR
#INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR


HEADERS += \
  $$SRC_DIR/dh-location-structure.h  \
  $$SRC_DIR/dgdb-database-instance.h  \
  $$SRC_DIR/dh-record-processors.h  \
  $$SRC_DIR/conversions.h  \
  $$SRC_DIR/dgdb-hypernode.h  \
  $$SRC_DIR/dwb/dwb-instance.h  \
  $$SRC_DIR/dtb/dtb-package.h  \
  $$SRC_DIR/dtb/sv-wrapper.h  \
  $$SRC_DIR/dtb/_sv-wrapper.h  \
  $$SRC_DIR/types/dh-type.h  \
  $$SRC_DIR/types/dh-type-system.h  \
  $$SRC_DIR/types/dh-type-builder.h  \
  $$SRC_DIR/types/dh-subvalue-field.h  \
  $$SRC_DIR/types/dh-type-field-info-state.h  \
  $$SRC_DIR/dgdb-data-out-stream.h  \
  $$SRC_DIR/dh-stage-value.h  \
  $$SRC_DIR/types/stage/dh-stage-queue.h  \
  $$SRC_DIR/types/stage/dh-stage-code.h  \
  $$SRC_DIR/graph/dh-frame.h  \
  $$SRC_DIR/graph/dh-dominion.h  \
  $$SRC_DIR/graph/dh-record.h  \
  $$SRC_DIR/dh-instance.h  \




SOURCES += \
  $$SRC_DIR/dh-location-structure.cpp  \
  $$SRC_DIR/dgdb-database-instance.cpp  \
  $$SRC_DIR/dgdb-hypernode.cpp  \
  $$SRC_DIR/dgdb-database-instance.data-options.cpp  \
  $$SRC_DIR/dgdb-database-instance.store-subvalue.cpp  \
  $$SRC_DIR/dgdb-database-instance._acc_conv.cpp  \
  $$SRC_DIR/dwb/dwb-instance.cpp  \
  $$SRC_DIR/dtb/dtb-package.cpp  \
  $$SRC_DIR/dtb/sv-wrapper.cpp  \
  $$SRC_DIR/types/dh-type.cpp  \
  $$SRC_DIR/types/dh-type-field-info-state.cpp  \
  $$SRC_DIR/types/dh-type-system.cpp  \
  $$SRC_DIR/types/dh-type-builder.cpp  \
  $$SRC_DIR/types/dh-subvalue-field.cpp  \
  $$SRC_DIR/dgdb-data-out-stream.cpp  \
  $$SRC_DIR/dh-stage-value.cpp  \
  $$SRC_DIR/types/stage/dh-stage-queue.cpp  \
  $$SRC_DIR/types/stage/dh-stage-code.cpp  \
  $$SRC_DIR/types/stage/dh-stage-value.to-qba.cpp  \
  $$SRC_DIR/graph/dh-frame.cpp  \
  $$SRC_DIR/graph/dh-dominion.cpp  \
  $$SRC_DIR/graph/dh-record.cpp  \
  $$SRC_DIR/dh-instance.cpp  \




#LIBS += -L$$TARGETSDIR -lwhitedb  \
#  -lntxh  -lntxh-parser


