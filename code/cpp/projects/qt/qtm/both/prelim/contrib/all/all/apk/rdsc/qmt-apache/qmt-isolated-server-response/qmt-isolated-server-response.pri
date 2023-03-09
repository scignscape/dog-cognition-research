
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


include(../build-group.pri)

include($$ROOT_DIR/../preferred/apache.pri)


TEMPLATE = app

QT += network


QMAKE_CC = gcc-7
QMAKE_CXX = g++-7

CONFIG += c++17


#PREFERRED_LOG_DIR=$${ROOT_DIR}/../qmt/run-logs   http://localhost:6600/qmt/rs~png/tiles/kherson/kherson_oblast-latest.osm-14-9674-5784.png
#DEFINES += PREFERRED_LOG_FOLDER=\\\"$${PREFERRED_LOG_DIR}\\\"
#DEFINES += PREFERRED_LOG_FILE=\\\"$${PREFERRED_LOG_DIR}/-qmt.txt\\\"
#DEFINES += LOCAL_SOCKET_PATH=\\\"$${PREFERRED_LOG_DIR}/qmt--named.sock\\\"

#message(local socket path: $$LOCAL_SOCKET_PATH)

#include($$ROOT_DIR/../preferred/apache.pri)


INCLUDEPATH += $$SRC_GROUP_DIR


INCLUDEPATH += \
  $${APACHE_INCLUDE_DIR}




#HEADERS += \
#  $$SRC_GROUP_DIR/qmt-utils/qmt-utils.h \
#  $$SRC_GROUP_DIR/qmt-utils/qmt-utils.hpp \


#HEADERS += \
#  $$SRC_GROUP_DIR/qmt-server/qmt-server-response.h \
#  $$SRC_GROUP_DIR/qmt-accessors.h \
#  $$SRC_GROUP_DIR/qmt-global-types.h \ http://localhost:6600/qmt-l/rs~png/~tiles/kherson/~osm-14-9674-5784


SOURCES += \
  $$SRC_GROUP_DIR/qmt-utils/qmt-utils.cpp \

SOURCES += \
  $$SRC_DIR/main.cpp \

#$$SRC_GROUP_DIR/qmt-server/qmt-server-response.cpp \

LIBS += -L$$TARGETSDIR -lqmt-main-server-response -lqmt-contextual-server-responses


