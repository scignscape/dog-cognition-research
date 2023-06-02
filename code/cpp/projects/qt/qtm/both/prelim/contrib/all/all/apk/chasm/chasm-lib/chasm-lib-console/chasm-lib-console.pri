
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


include(../build-group.pri)

TEMPLATE = app

QT -= gui


include($$ROOT_DIR/../preferred/sysr.pri)


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

#INCLUDEPATH += $$NTXH_SRC_GROUP_DIR
#INCLUDEPATH += $$NTXH_SRC_GROUP_DIR/ntxh
#INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR
#INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
#INCLUDEPATH += $$HTXN_SRC_GROUP_DIR
#INCLUDEPATH += $$SRC_GROUP_DIR/gtagml


 # Most projects don't use ROOT_DIR as a basis
 # for includes but this one loads some generated
 # source code to experiment with ...
INCLUDEPATH += $$ROOT_DIR


DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"

DEFINES += HAVE_NO_QT_GUI_MODULE


DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES

CONFIG += no_keywords


DEFINES += USE_KANS


HEADERS += \



SOURCES += \
  $$SRC_DIR/main.cpp \



LIBS += -L$$TARGETSDIR -lchasm-lib


LIBS += -L$$TARGETSDIR  \   #\ -lchasm-runtime-bridge -lchasm-vm -lchasm-procedure-table \
  -lchasm-lib -lchasm-lib-X1 -lchasm-lib-X2 \
  -lchasm-lib-33 -lchasm-lib-43

# -lchasm-tr-parser



#$$SRC_DIR/chasm/chasm-runtime.eval-4of3.cpp \
#$$SRC_DIR/chasm/chasm-runtime.eval-3of3.cpp \
#$$SRC_DIR/chasm/chasm-runtime.eval-Xof2.cpp \
#$$SRC_DIR/chasm/chasm-runtime.eval-Xof1.cpp \

message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)


