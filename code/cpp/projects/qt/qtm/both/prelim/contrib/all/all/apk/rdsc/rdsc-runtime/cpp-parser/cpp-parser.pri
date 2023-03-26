
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = cpp-parser

include(../build-group.pri)


#QT += gui widgets webenginewidgets location

exists($$ROOT_DIR/../preferred/sysr.pri): include($$ROOT_DIR/../preferred/sysr.pri)
exists($$ROOT_DIR/../preferred/sysr-c.pri): include($$ROOT_DIR/../preferred/sysr-c.pri)
exists($$ROOT_DIR/../preferred/compiler.pri): include($$ROOT_DIR/../preferred/compiler.pri)

exists($$ROOT_DIR/../preferred/openssl.pri): include($$ROOT_DIR/../preferred/openssl.pri)

CONFIG += c++17


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR



CONFIG += no_keywords

DEFINES += USE_KANS

DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"



QMAKE_LFLAGS +=  --coverage

TEMPLATE = lib
CONFIG += staticlib

QMAKE_LINK = g++-7

#DESTDIR = ../dest
#LIBS += -lboost_program_options -lboost_system -lboost_filesystem

INCLUDEPATH += $$SRC_DIR/common/third_party/boost_tp/

INCLUDEPATH += $$SRC_DIR/pub

FLEX = /usr/bin/flex

message("$${FLEX} -o$$SRC_DIR/src/parser.lex.cpp $$SRC_DIR/src/parser.l")
system("$${FLEX} -o$$SRC_DIR/src/parser.lex.cpp $$SRC_DIR/src/parser.l")

BTYACC = $${ROOT_DIR}/../preferred/tools/btyacc
message("$${BTYACC} -v -b parser -d $${SRC_DIR}/src/parser.y")
system("$${BTYACC} -v -b parser -d $${SRC_DIR}/src/parser.y")

message("mv parser.tab.c $${SRC_DIR}/src/parser.tab.cpp")
system(mv parser.tab.c $${SRC_DIR}/src/parser.tab.cpp)


HEADERS += \
 $$SRC_DIR/hack/unistd.h \
 $$SRC_DIR/pub/cppast.h \
 $$SRC_DIR/pub/cppcompound-info-accessor.h \
 $$SRC_DIR/pub/cppconst.h \
 $$SRC_DIR/pub/cppeasyptr.h \
 $$SRC_DIR/pub/cppfunc-info-accessor.h \
 $$SRC_DIR/pub/cppindent.h \
 $$SRC_DIR/pub/cppobj-info-accessor.h \
 $$SRC_DIR/pub/cppobjfactory.h \
 $$SRC_DIR/pub/cppparser.h \
 $$SRC_DIR/pub/cppprog.h \
 $$SRC_DIR/pub/cpptypetree.h \
 $$SRC_DIR/pub/cpputil.h \
 $$SRC_DIR/pub/cppvar-info-accessor.h \
 $$SRC_DIR/pub/cppwriter.h \
 $$SRC_DIR/pub/string-utils.h \
 $$SRC_DIR/pub/typemodifier.h \
 $$SRC_DIR/src/cpptoken.h \
 $$SRC_DIR/src/cppvarinit.h \
 $$SRC_DIR/src/lexer-helper.h \
 $$SRC_DIR/src/obj-factory-helper.h \
 $$SRC_DIR/src/parser.h \
 $$SRC_DIR/src/parser.l \
 $$SRC_DIR/src/parser.l.h \
 $$SRC_DIR/src/parser.tab.h \
 $$SRC_DIR/src/utils.h \
 $$SRC_DIR/src/qh/qh-context.h \


SOURCES += \
 $$SRC_DIR/src/cppast.cpp \
 $$SRC_DIR/src/cppobjfactory.cpp \
 $$SRC_DIR/src/cppparser.cpp \
 $$SRC_DIR/src/cppprog.cpp \
 $$SRC_DIR/src/cppwriter.cpp \
 $$SRC_DIR/src/lexer-helper.cpp \
 $$SRC_DIR/src/parser.lex.cpp \
 $$SRC_DIR/src/parser.tab.c \
 $$SRC_DIR/src/parser.tab.cpp \
 $$SRC_DIR/src/utils.cpp \
 $$SRC_DIR/src/qh/qh-context.cpp \




message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

