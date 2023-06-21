
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


QT += widgets gui


QT += location   network



include(../build-group.pri)

CONFIG += c++17


TEMPLATE = app

#MAPGRAPHICS_MASTER = ../../../MapGraphics-master
# http://localhost:6600/qmt-l/rs~png/~tiles/kherson/~osm-14-9674-5784


include($$ROOT_DIR/../preferred/openssl.pri)

#LIBS += /usr/lib/x86_64-linux-gnu/libssl.a

DEFINES += EXAMPLE_DATA_FOLDER=\\\"$${ROOT_DIR}/example-data/nathaniel-christen/industry-4_0-section-5\\\"


INCLUDEPATH += $$NTXH_SRC_GROUP_DIR
INCLUDEPATH += $$NTXH_SRC_GROUP_DIR/ntxh
INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR



INCLUDEPATH += \
  $$SRC_GROUP_DIR/qmt-case-map


HEADERS += \
  $$SRC_DIR/lanternfly/lanternfly-frame.h \
  $$SRC_DIR/main-window.h \
  $$SRC_DIR/lanternfly/lanternfly-sighting-dialog.h \
  $$SRC_DIR/lanternfly/lanternfly-configuration-dialog.h \
  $$SRC_DIR/lanternfly/lanternfly-sighting-filter-dialog.h \
  $$SRC_DIR/qmt-client-layer.h \
  $$SRC_DIR/qmt-client-context-menu-handler.h \
  $$SRC_DIR/qmt-client-location-focus.h \
  $$SRC_DIR/qmt-client-data-set.h \
  $$SRC_DIR/qmt-data-set-content-base.h \
  $$SRC_DIR/lanternfly-data-set.h \
  $$SRC_DIR/case-map/case-map-entry-dialog.h \

HEADERS += \
  $$SRC_DIR/case-map/case-map-gis-service.h


HEADERS += \
  $$SRC_DIR/case-map/csv/contentiterator.h \
  $$SRC_DIR/case-map/csv/filechecker.h \
  $$SRC_DIR/case-map/csv/symbols.h \
  $$SRC_DIR/case-map/csv/qtcsv/abstractdata.h \
  $$SRC_DIR/case-map/csv/qtcsv/qtcsv_global.h \
  $$SRC_DIR/case-map/csv/qtcsv/reader.h \
  $$SRC_DIR/case-map/csv/qtcsv/stringdata.h \
  $$SRC_DIR/case-map/csv/qtcsv/variantdata.h \
  $$SRC_DIR/case-map/csv/qtcsv/writer.h \


SOURCES += \
  $$SRC_DIR/case-map/csv/contentiterator.cpp \
  $$SRC_DIR/case-map/csv/reader.cpp \
  $$SRC_DIR/case-map/csv/variantdata.cpp \
  $$SRC_DIR/case-map/csv/writer.cpp \
  $$SRC_DIR/case-map/csv/stringdata.cpp \

SOURCES += \
  $$SRC_DIR/case-map/case-map-gis-service.cpp



SOURCES += \
  $$SRC_DIR/lanternfly/lanternfly-frame.cpp \
  $$SRC_DIR/lanternfly/lanternfly-sighting-dialog.cpp \
  $$SRC_DIR/lanternfly/lanternfly-configuration-dialog.cpp \
  $$SRC_DIR/lanternfly/lanternfly-sighting-filter-dialog.cpp \
  $$SRC_DIR/main-window.cpp \
  $$SRC_DIR/main.cpp \
  $$SRC_DIR/qmt-client-layer.cpp \
  $$SRC_DIR/qmt-client-context-menu-handler.cpp \
  $$SRC_DIR/qmt-client-location-focus.cpp \
  $$SRC_DIR/qmt-client-data-set.cpp \
  $$SRC_DIR/qmt-data-set-content-base.cpp \
  $$SRC_DIR/lanternfly-data-set.cpp \
  $$SRC_DIR/case-map/case-map-entry-dialog.cpp \




LIBS += -L$$TARGETSDIR -lqmt-case-map

LIBS += -L$$TARGETSDIR  \
  -lntxh  -lntxh-parser

#-lngml-sdi


#HEADERS += \

