

#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)

QT += xml widgets

TEMPLATE = app

INCLUDEPATH += $$SRC_DIR

INCLUDEPATH += $$SRC_PROSET_DIR/aimlib/aimlib/AIMLib/

include($$ROOT_DIR/../preferred/compiler.pri)


CONFIG += c++17


DEFINES += USE_XCNS


#? FEATURE_IFC = USE_IFC
defined(FEATURE_IFC ,var) {
 DEFINES += $$FEATURE_IFC
 include($$ROOT_DIR/../preferred/occt.pri)
}

#? FEATURE_NGML = USE_NGML
defined(FEATURE_NGML ,var) {
 DEFINES += $$FEATURE_NGML
 LIBS += -L$$TARGETSDIR -lngml-sdi
}

#? FEATURE_XCSD = USE_XCSD
defined(FEATURE_XCSD ,var) {
 DEFINES += $$FEATURE_XCSD
 LIBS += -L$$TARGETSDIR -lxcsd-1d -lxcsd-2d -lxcsd
}

#? FEATURE_CHASM = USE_CHASM
defined(FEATURE_CHASM ,var) {
 DEFINES += $$FEATURE_CHASM
 LIBS += -L$$TARGETSDIR -lchasm-lib -lchasm-lib-X1 -lchasm-lib-X2 \
   -lchasm-lib-33 -lchasm-lib-43
}

#? FEATURE_FORGE = USE_FORGE
defined(FEATURE_FORGE ,var) {
 DEFINES += $$FEATURE_FORGE
 LIBS += -L$$TARGETSDIR -liat-forge
}



#? FEATURE_IMAGE_EDITOR = USE_IMAGE_EDITOR
defined(FEATURE_IMAGE_EDITOR ,var) {
 DEFINES += $$FEATURE_FEATURE_IMAGE_EDITOR
 LIBS += -L$$TARGETSDIR  -limage-editor
}





DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"

#include($$ROOT_DIR/../preferred/aim.pri)

include($$ROOT_DIR/../preferred/dhax.pri)

include($$ROOT_DIR/../preferred/opencv.pri)

DEFINES += DHAX_DATA_FOLDER=\\\"$$DHAX_DATA_DIR\\\"
DEFINES += DHAX_IMAGE_FOLDER=\\\"$$DHAX_IMAGE_DIR\\\"


DEFINES += DEFAULT_DEV_TKRZW_FOLDER=\\\"$$ROOT_DIR/../dev/consoles/dgdb/tkrzw\\\"

DEFINES += DEFAULT_DEV_DGDB_FOLDER=\\\"$$ROOT_DIR/../dev/consoles/dgdb/instances\\\"

DEFINES += SCREENSHOTS_FOLDER=\\\"$$ROOT_DIR/../dev/screenshots\\\"

DEFINES += USE_KANS

INCLUDEPATH += $$DGDB_SRC_GROUP_DIR

INCLUDEPATH += $$DGDB_SRC_GROUP_DIR/tkrzw


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

INCLUDEPATH += $$SRC_GROUP_DIR/tkrzw

INCLUDEPATH += $$WHITEDB_SRC_GROUP_DIR



HEADERS += \


SOURCES += \
  $$SRC_DIR/main.cpp \


# #  for dcmtk OFString = std::string ...
DEFINES += HAVE_STD_STRING
DEFINES += HAVE_STL_STRING

LIBS += -L$$TARGETSDIR  \
  -lntxh  -lntxh-parser



LIBS += -L$$TARGETSDIR  -ldhax-gui -ldhax-data



LIBS += -L$$POPPLER_LIB_DIR -lpoppler-qt5


#LIBS += -L$$TARGETSDIR  -laimlib -ldcmsr -lofstd -loflog -ldcmdata \
#   -ldcmimage -ldcmimgle

#LIBS += -L$$TARGETSDIR  -laxfi

LIBS += -lrt


#LIBS += -L$$TARGETSDIR -ldgdb

#LIBS += -L$$TARGETSDIR -ltkrzw
LIBS += -L$$TARGETSDIR -llz4  -llzma -lz

#LIBS += -L$$TARGETSDIR -lwhitedb


#LIBS += -L$$TARGETSDIR -laimlib


# #  assumed xerces is installed ...
LIBS += -lxerces-c


##?FEATURE_OpenCV = USE_OpenCV

# ### For OpenCV 
defined(FEATURE_OpenCV ,var) {
 message(Using OpenCV)
 LIBS += -L$$TARGETSDIR  -ldgi-opencv
 LIBS += -L$$OPENCV_LIB_DIR -lopencv_core -lopencv_imgcodecs -lopencv_imgproc
 LIBS += -L$$OPENCV_LIB_DIR  -lopencv_xfeatures2d  \
   -lopencv_features2d
}



#DCMTK_DIR = $$DCMTK_SRC_GROUP_DIR

#INCLUDEPATH += $$DCMTK_DIR/ofstd/include
#INCLUDEPATH += $$DCMTK_DIR/dcm-config/include
#INCLUDEPATH += $$DCMTK_DIR/dcmsr/include
#INCLUDEPATH += $$DCMTK_DIR/dcmdata/include
#INCLUDEPATH += $$DCMTK_DIR/oflog/include


# ### For IFC (Industry Foundation Classes)
defined(FEATURE_IFC ,var) {

message(Using IFC Libraries)

 DEFINES += $$FEATURE_IFC

LIBS += $$TARGETSDIR/libifc-multi.a


LIBS += $$TARGETSDIR/libifc-2x3.a \
  $$TARGETSDIR/libifc-4.a \
  $$TARGETSDIR/libifc-4x1.a \
  $$TARGETSDIR/libifc-4x2.a \
  $$TARGETSDIR/libifc-4x3_rc1.a \
  $$TARGETSDIR/libifc-4x3_rc2.a \
  $$TARGETSDIR/libifc-4x3_rc3.a \
  $$TARGETSDIR/libifc-4x3_rc4.a \


LIBS += \
 -lboost_program_options \
 -lboost_system \
 -lboost_program_options \
 -lboost_regex \
 -lboost_thread \
 -lboost_date_time \
 -lboost_chrono \
 -lboost_atomic \
 -lpthread \
 -lxml2

LIBS += -L$$OCCT_LIB_DIR \
 -lTKernel \
 -lTKMath \
 -lTKBRep \
 -lTKGeomBase \
 -lTKGeomAlgo \
 -lTKG3d \
 -lTKG2d \
 -lTKShHealing \
 -lTKTopAlgo \
 -lTKMesh \
 -lTKPrim \
 -lTKBool \
 -lTKBO \
 -lTKFillet \
 -lTKSTEP \
 -lTKSTEPBase \
 -lTKSTEPAttr \
 -lTKXSBase \
 -lTKSTEP209 \
 -lTKIGES \
 -lTKOffset \
 -lTKHLR

}



message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

