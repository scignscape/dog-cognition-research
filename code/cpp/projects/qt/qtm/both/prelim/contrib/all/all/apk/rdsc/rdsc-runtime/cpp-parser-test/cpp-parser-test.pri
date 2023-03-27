
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = cpp-parser-test

include(../build-group.pri)

TEMPLATE = app

exists($$ROOT_DIR/../preferred/sysr.pri): include($$ROOT_DIR/../preferred/sysr.pri)
exists($$ROOT_DIR/../preferred/sysr-c.pri): include($$ROOT_DIR/../preferred/sysr-c.pri)
exists($$ROOT_DIR/../preferred/compiler.pri): include($$ROOT_DIR/../preferred/compiler.pri)

exists($$ROOT_DIR/../preferred/openssl.pri): include($$ROOT_DIR/../preferred/openssl.pri)

CONFIG += c++17


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

message($$SRC_GROUP_DIR)

CONFIG += no_keywords

DEFINES += USE_KANS

DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"



QMAKE_LFLAGS +=  --coverage


QMAKE_LINK = g++-7

#DESTDIR = ../dest


#INCLUDEPATH += $$SRC_DIR/common/third_party/boost_tp/
#INCLUDEPATH += $$SRC_DIR/pub

message($$TARGETSDIR)
LIBS += -L$$TARGETSDIR -lcpp-parser

LIBS += -L$${ROOT_DIR}/../preferred/tools  -lboost_program_options -lboost_system -lboost_filesystem

#LIBS += -L/quasihome/nlevisrael/cpp/b3/boost -lboost_program_options -lboost_system -lboost_filesystem


#LIBS += -L../build -lboost_program_options -lboost_system -lboost_filesystem


#QMAKE_LFLAGS += "-g -O0 -Wall -std=c++1z -fvisibility=hidden -fvisibility-inlines-hidden -fprofile-arcs -ftest-coverage --coverage"

#QMAKE_LFLAGS += -fvisibility=hidden -fvisibility-inlines-hidden -fprofile-arcs -ftest-coverage --coverage

INCLUDEPATH += $$SRC_GROUP_DIR/cpp-parser

QMAKE_LFLAGS +=  --coverage

#?LIBS += -L/quasihome/nlevisrael/cpp/build/boost/ -lboost_program_options -lboost_system -lboost_filesystem

SOURCES += \
 $$SRC_DIR/main.cpp

#SOURCES += \
# ../CppParser/test/app/cppparsertest.cpp





message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

