
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


QT += network sql location widgets

QT += webenginewidgets

TEMPLATE = lib

DEFINES += MAPGRAPHICS_LIBRARY

DEFINES += SCREENSHOTS_FOLDER=\\\"$${ROOT_DIR}/../screenshots\\\"

DEFINES += ROOT_FOLDER=\\\"$${ROOT_DIR}\\\"

DEFINES += EXAMPLE_DATA_FOLDER=\\\"$${ROOT_DIR}/../example-data/contrib/nathaniel-christen/industry-4_0-section-5\\\"


INCLUDEPATH += $$NTXH_SRC_GROUP_DIR
INCLUDEPATH += $$NTXH_SRC_GROUP_DIR/ntxh
INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR



DEFINES += USE_KANS


CONFIG += c++17

INCLUDEPATH += $$SRC_PROSET_DIR


SOURCES += \
  $$SRC_DIR/MapGraphicsScene.cpp \
  $$SRC_DIR/MapGraphicsObject.cpp \
  $$SRC_DIR/MapGraphicsView.cpp \
  $$SRC_DIR/guts/PrivateQGraphicsScene.cpp \
  $$SRC_DIR/guts/PrivateQGraphicsObject.cpp \
  $$SRC_DIR/guts/Conversions.cpp \
  $$SRC_DIR/MapTileSource.cpp \
  $$SRC_DIR/tileSources/GridTileSource.cpp \
  $$SRC_DIR/guts/MapTileGraphicsObject.cpp \
  $$SRC_DIR/guts/PrivateQGraphicsView.cpp \
  $$SRC_DIR/tileSources/OSMTileSource.cpp \
  $$SRC_DIR/guts/MapGraphicsNetwork.cpp \
  $$SRC_DIR/tileSources/CompositeTileSource.cpp \
  $$SRC_DIR/guts/MapTileLayerListModel.cpp \
  $$SRC_DIR/guts/MapTileSourceDelegate.cpp \
  $$SRC_DIR/guts/CompositeTileSourceConfigurationWidget.cpp \
  $$SRC_DIR/CircleObject.cpp \
  $$SRC_DIR/guts/PrivateQGraphicsInfoSource.cpp \
  $$SRC_DIR/PolygonObject.cpp \
  $$SRC_DIR/Position.cpp \
  $$SRC_DIR/LineObject.cpp \
  $$SRC_DIR/qmt/main-window-controller.cpp \
  $$SRC_DIR/qmt/qmt-gis-utils.cpp \
  $$SRC_DIR/qmt/qmt-client-layer-base.cpp \
  $$SRC_DIR/qmt/qmt-client-data-set-base.cpp \
  $$SRC_DIR/qmt/qmt-client-context-menu-handler-base.cpp \
  $$SRC_DIR/qmt/qmt-client-location-focus-base.cpp \
  $$SRC_DIR/dialogs/tile-server-select-dialog.cpp \
  $$SRC_DIR/web-engine/qmt-web-engine-page.cpp \
  $$SRC_DIR/web-engine/qmt-web-engine-view.cpp \
  $$SRC_DIR/web-engine/qmt-my-page.cpp \


HEADERS += \
  $$SRC_DIR/MapGraphicsScene.h\
  $$SRC_DIR/MapGraphics_global.h \
  $$SRC_DIR/MapGraphicsObject.h \
  $$SRC_DIR/MapGraphicsView.h \
  $$SRC_DIR/guts/PrivateQGraphicsScene.h \
  $$SRC_DIR/guts/PrivateQGraphicsObject.h \
  $$SRC_DIR/guts/Conversions.h \
  $$SRC_DIR/MapTileSource.h \
  $$SRC_DIR/tileSources/GridTileSource.h \
  $$SRC_DIR/guts/MapTileGraphicsObject.h \
  $$SRC_DIR/guts/PrivateQGraphicsView.h \
  $$SRC_DIR/tileSources/OSMTileSource.h \
  $$SRC_DIR/guts/MapGraphicsNetwork.h \
  $$SRC_DIR/tileSources/CompositeTileSource.h \
  $$SRC_DIR/guts/MapTileLayerListModel.h \
  $$SRC_DIR/guts/MapTileSourceDelegate.h \
  $$SRC_DIR/guts/CompositeTileSourceConfigurationWidget.h \
  $$SRC_DIR/CircleObject.h \
  $$SRC_DIR/guts/PrivateQGraphicsInfoSource.h \
  $$SRC_DIR/PolygonObject.h \
  $$SRC_DIR/Position.h \
  $$SRC_DIR/LineObject.h \
  $$SRC_DIR/qmt/main-window-controller.h \
  $$SRC_DIR/qmt/qmt-gis-utils.h \
  $$SRC_DIR/qmt/qmt-client-layer-base.h \
  $$SRC_DIR/qmt/qmt-client-data-set-base.h \
  $$SRC_DIR/qmt/qmt-client-location-focus-base.h \
  $$SRC_DIR/qmt/qmt-client-context-menu-handler-base.h \
  $$SRC_DIR/dialogs/tile-server-select-dialog.h \
  $$SRC_DIR/dialogs/nlohmann-fifo-map.h \
  $$SRC_DIR/web-engine/qmt-web-engine-page.h \
  $$SRC_DIR/web-engine/qmt-web-engine-view.h \
  $$SRC_DIR/web-engine/qmt-my-page.h \


HEADERS += \
  $$SRC_DIR/qmt-gis/qmt-geospatial-marker.h \


SOURCES += \
  $$SRC_DIR/qmt-gis/qmt-geospatial-marker.cpp \


HEADERS += \
  $$SRC_PROSET_DIR/qmt/qmt-resource-info.h


SOURCES += \
  $$SRC_PROSET_DIR/qmt/qmt-resource-info.cpp




HEADERS += \
  $$SRC_DIR/case-map/qmt-single-case.h \
  $$SRC_DIR/case-map/qmt-case-group.h \


SOURCES += \
  $$SRC_DIR/case-map/qmt-single-case.cpp \
  $$SRC_DIR/case-map/qmt-case-group.cpp \





# # taken directly from the MapGraphics project file
#
symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE4F7F973
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = MapGraphics.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}
#
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
#

FORMS += \
  $$SRC_DIR/guts/CompositeTileSourceConfigurationWidget.ui

RESOURCES += \
  $$SRC_DIR/resources.qrc
