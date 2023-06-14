
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


PROJECT_NAME = chasm-console

include(../build-group.pri)

TEMPLATE = app


exists($$ROOT_DIR/../preferred/sysr.pri): include($$ROOT_DIR/../preferred/sysr.pri)
exists($$ROOT_DIR/../preferred/sysr-c.pri): include($$ROOT_DIR/../preferred/sysr-c.pri)
exists($$ROOT_DIR/../preferred/compiler.pri): include($$ROOT_DIR/../preferred/compiler.pri)



CONFIG += c++17

##?
FEATURE_OpenCV = USE_OpenCV

# ### For OpenCV
defined(FEATURE_OpenCV ,var) {
 message(Using OpenCV)

 DEFINES += USE_OpenCV
 exists($$ROOT_DIR/../preferred/opencv.pri): include($$ROOT_DIR/../preferred/opencv.pri)
 INCLUDEPATH += $$OPENCV_INCLUDE_DIR

 QT += widgets

 LIBS += -L$$OPENCV_LIB_DIR -lopencv_core  -lopencv_imgproc  -lopencv_imgcodecs

 LIBS += -L$$OPENCV_LIB_DIR  -lopencv_xfeatures2d  \
   -lopencv_features2d


 HEADERS += \
  $$SRC_DIR/stats/feature-classifier-transform.h \
  $$SRC_DIR/stats/slic/slic.h \
  $$SRC_DIR/stats/slico/slico.h \
  $$SRC_DIR/stats/stat-test-image.h \
  $$SRC_DIR/stats/test-stat-assessment.h

 SOURCES += \
  $$SRC_DIR/stats/feature-classifier-transform.cpp \
  $$SRC_DIR/stats/slic/slic.cpp \
  \# $$SRC_DIR/stats/slico/slic-demo.cpp \
  $$SRC_DIR/stats/slico/slico.cpp \
  $$SRC_DIR/stats/stat-test-image.cpp \
  $$SRC_DIR/stats/test-stat-assessment.cpp \
  $$SRC_DIR/stats/test-stat-assessment.demo-test.cpp

###

}



###
#?defined(USE_OpenCV)

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR


INCLUDEPATH += $$SRC_GROUP_DIR/chasm-tr

INCLUDEPATH += $$SRC_PROSET_DIR/chasm-vm
INCLUDEPATH += $$SRC_PROSET_DIR/chasm-lib


CONFIG += no_keywords

DEFINES += USE_KANS
DEFINES += USE_AQNS

DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"
DEFINES += DEMO_CVM_FOLDER=\\\"$$ROOT_DIR/../chtr\\\"

SOURCES += \
  $$SRC_DIR/main.cpp \


LIBS += -L$$TARGETSDIR -lchasm-tr  -lchasm-tr-parser


LIBS += -L$$TARGETSDIR -lchasm-lib \
  -lchasm-vm -lchasm-runtime-bridge -lchasm-procedure-table \
  -lchasm-lib-X1 -lchasm-lib-X2 \
  -lchasm-lib-33 -lchasm-lib-43




message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

