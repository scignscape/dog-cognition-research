
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


include(../build-group.pri)


QT += gui widgets

TEMPLATE = app

CONFIG += no_keywords


QMAKE_CC = gcc-7
QMAKE_CXX = g++-7

CONFIG += c++17


INCLUDEPATH += \
  /usr/include/cairo \


INCLUDEPATH += \
  $$SRC_GROUP_DIR/alacarte/src/server/_qmt_


DEFINES += QT_HOOK

DEFINES += MAX_ZOOM_DIFF=5
DEFINES += MAX_X_DIFF=100
DEFINES += MAX_Y_DIFF=100



INCLUDEPATH += \
  $$SRC_GROUP_DIR/alacarte/src/_qlog_ \


INCLUDEPATH += \
  $$SRC_GROUP_DIR/alacarte/include


HEADERS += \
  $$SRC_GROUP_DIR/alacarte/src/_run-console_/qmt-shape-object.h \
  $$SRC_GROUP_DIR/alacarte/src/_run-console_/qmt-painter.h \
  $$SRC_GROUP_DIR/alacarte/src/_run-console_/qmt-paint-context.h \
  $$SRC_GROUP_DIR/alacarte/src/_run-console_/qmt-render-broker.h \


SOURCES += \
 $$SRC_GROUP_DIR/alacarte/src/_run-console_/main.cpp \
 $$SRC_GROUP_DIR/alacarte/src/_run-console_/qmt-shape-object.cpp \
 $$SRC_GROUP_DIR/alacarte/src/_run-console_/qmt-painter.cpp \
 $$SRC_GROUP_DIR/alacarte/src/_run-console_/qmt-paint-context.cpp \
 $$SRC_GROUP_DIR/alacarte/src/_run-console_/qmt-render-broker.cpp \


#ALACARTE_QLOG_DIR = $$SRC_GROUP_DIR/alacarte/../alacarte-master/-qlog_
#DEFINES += ALACARTE_QLOG_FOLDER=\\\"$${ALACARTE_QLOG_DIR}\\\"
#DEFINES += ALACARTE_QLOG_FILE=\\\"$${ALACARTE_QLOG_DIR}/qlog.txt\\\"
#DEFINES += ALACARTE_QLOG_IMAGES_FOLDER=\\\"$${ALACARTE_QLOG_DIR}/images\\\"


LIBS += -L$$TARGETSDIR -lqmt-alacarte-lib  -lqmt-alacarte-server-lib



LIBS += -lboost_program_options \
   -lboost_system  -lboost_filesystem \
   -lboost_serialization  -lboost_log  -lboost_thread \
   -lboost_log_setup -lboost_regex -lboost_iostreams \
   -lboost_chrono -lboost_date_time -lboost_atomic \
   -lboost_unit_test_framework \


LIBS += -lcairo


