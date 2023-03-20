
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = rdsc-qh-demo

include(../build-group.pri)

TEMPLATE = app

QT += gui widgets webenginewidgets location

exists($$ROOT_DIR/../preferred/sysr.pri): include($$ROOT_DIR/../preferred/sysr.pri)
exists($$ROOT_DIR/../preferred/sysr-c.pri): include($$ROOT_DIR/../preferred/sysr-c.pri)
exists($$ROOT_DIR/../preferred/compiler.pri): include($$ROOT_DIR/../preferred/compiler.pri)

exists($$ROOT_DIR/../preferred/openssl.pri): include($$ROOT_DIR/../preferred/openssl.pri)

CONFIG += c++17


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR


INCLUDEPATH += $$RDSC_DATA_SRC_GROUP_DIR



CONFIG += no_keywords

DEFINES += USE_KANS

DEFINES += SCREENSHOTS_FOLDER=\\\"$$ROOT_DIR/../dev/zq\\\"
DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"

HEADERS += \

#INCLUDEPATH += \
#  $$SRC_GROUP_DIR/MapGraphics

HEADERS += \
  $$SRC_DIR/game/game-driver.h \
  $$SRC_DIR/game/game-player.h \
  $$SRC_DIR/game/game-token.h \
  $$SRC_DIR/game/game-board.h \
  $$SRC_DIR/game/game-position.h \
  $$SRC_DIR/game/token-group.h \
  $$SRC_DIR/game/message-display-window.h \
  $$SRC_DIR/game/game-variant.h \
  $$SRC_DIR/game/variants/au/au-game-variant.h \


SOURCES += \
  $$SRC_DIR/main.cpp \
  $$SRC_DIR/game/game-driver.cpp \
  $$SRC_DIR/game/game-player.cpp \
  $$SRC_DIR/game/game-token.cpp \
  $$SRC_DIR/game/game-board.cpp \
  $$SRC_DIR/game/game-position.cpp \
  $$SRC_DIR/game/token-group.cpp \
  $$SRC_DIR/game/message-display-window.cpp \
  $$SRC_DIR/game/game-variant.cpp \
  $$SRC_DIR/game/variants/au/au-game-variant.cpp \
  $$SRC_DIR/game/variants/au/move-options/au.bishop.cpp \








#SOURCES += \
#  $$SRC_DIR/main.cpp \


#LIBS += -L$$TARGETSDIR -lzq-client

LIBS += -L$$TARGETSDIR -lrdsc-qh


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

