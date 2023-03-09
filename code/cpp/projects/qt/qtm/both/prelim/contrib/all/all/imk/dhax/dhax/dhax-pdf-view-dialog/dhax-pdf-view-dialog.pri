

#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)

QT += xml widgets network webenginewidgets


INCLUDEPATH += $$SRC_DIR



include($$ROOT_DIR/../preferred/poppler.pri)

INCLUDEPATH += $$POPPLER_INCLUDE_DIR


include($$ROOT_DIR/../preferred/compiler.pri)


CONFIG += c++17


FEATURE_IFC = "USE_IFC"

defined(FEATURE_IFC ,var) {
 DEFINES += $$FEATURE_IFC
 include($$ROOT_DIR/../preferred/occt.pri)
}

DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"

#include($$ROOT_DIR/../preferred/aim.pri)
#DEFINES += AIM_DATA_FOLDER=\\\"$$AIM_DATA_DIR\\\"

include($$ROOT_DIR/../preferred/dhax.pri)

DEFINES += DHAX_DATA_FOLDER=\\\"$$DHAX_DATA_DIR\\\"
DEFINES += DHAX_IMAGE_FOLDER=\\\"$$DHAX_IMAGE_DIR\\\"

DEFINES += DEFAULT_DHAX_TEMP_FOLDER=\\\"$$DHAX_TEMP_DIR\\\"
DEFINES += DEFAULT_DGI_TEMP_FOLDER=\\\"$$DGI_TEMP_DIR\\\"



DEFINES += DEFAULT_DEV_TKRZW_FOLDER=\\\"$$ROOT_DIR/../dev/consoles/dgdb/tkrzw\\\"

DEFINES += DEFAULT_DEV_DGDB_FOLDER=\\\"$$ROOT_DIR/../dev/consoles/dgdb/instances\\\"

DEFINES += SCREENSHOTS_FOLDER=\\\"$$ROOT_DIR/../dev/screenshots\\\"

DEFINES += USE_KANS

INCLUDEPATH += $$DGDB_SRC_GROUP_DIR

INCLUDEPATH += $$DGDB_SRC_GROUP_DIR/tkrzw

INCLUDEPATH += $$DGDB_WHITE_SRC_GROUP_DIR

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

INCLUDEPATH += $$SRC_GROUP_DIR/tkrzw

INCLUDEPATH += $$WHITEDB_SRC_GROUP_DIR

INCLUDEPATH += $$CHASM_SRC_GROUP_DIR

#FORGE

DEFINES += LIBCRYPTO_FILE_NAME=\\\"$$ROOT_DIR/../ssl/install/ldir/libcrypto.so.1.1\\\"
DEFINES += LIBSSL_FILE_NAME=\\\"$$ROOT_DIR/../ssl/install/ldir/libssl.so.1.1\\\"

DEFINES += DEFAULT_FORGE_UPLOAD_FOLDER=\\\"$$ROOT_DIR/../forge\\\"

DEFINES += DEFAULT_FORGE_TEMP_FOLDER=\\\"$$ROOT_DIR/../forge/temp\\\"


DEFINES += FORGE_IMAGE_FOLDER=\\\"$$ROOT_DIR/../forge/images\\\"

DEFINES += FORGE_CREDENTIALS_FOLDER=\\\"$$ROOT_DIR/../forge/credentials\\\"

## This is needed for adding to the QInputDialog layout in Special_Dialog ...
QT_HEADER_LOCATION = $$[QT_INSTALL_HEADERS]

INCLUDEPATH += $${QT_HEADER_LOCATION}/QtCore/$$[QT_VERSION]
INCLUDEPATH += $${QT_HEADER_LOCATION}/QtGui/$$[QT_VERSION]
INCLUDEPATH += $${QT_HEADER_LOCATION}/QtWidgets/$$[QT_VERSION]

INCLUDEPATH += $${QT_HEADER_LOCATION}/QtGui/$$[QT_VERSION]/QtGui
INCLUDEPATH += $${QT_HEADER_LOCATION}/QtCore/$$[QT_VERSION]/QtCore
INCLUDEPATH += $${QT_HEADER_LOCATION}/QtWidgets/$$[QT_VERSION]/QtWidgets


include($$ROOT_DIR/../preferred/opencv.pri)

INCLUDEPATH += $$OPENCV_SRC_DIR/modules/core/include
INCLUDEPATH += $$OPENCV_SRC_DIR/modules/imgproc/include
INCLUDEPATH += $$OPENCV_SRC_DIR/modules/imgcodecs/include
INCLUDEPATH += $$OPENCV_BUILD_DIR


HEADERS += \
  $$SRC_DIR/paraviews/dhax-pdf-view-dialog.h \
  $$SRC_DIR/pleneviews/view-pdf-frame.h \
  $$SRC_DIR/subwindows/pdf-document-widget.h \
  $$SRC_DIR/subwindows/reverse-spinbox.h \
  $$SRC_DIR/subwindows/multiline-rubber-band.h \
  $$SRC_DIR/subwindows/rotateable-arrow-annotation.h \
  $$SRC_DIR/subwindows/multistep-annotation-base.h \



SOURCES += \
  $$SRC_DIR/paraviews/dhax-pdf-view-dialog.cpp \
  $$SRC_DIR/pleneviews/view-pdf-frame.cpp \
  $$SRC_DIR/subwindows/pdf-document-widget.cpp \
  $$SRC_DIR/subwindows/reverse-spinbox.cpp \
  $$SRC_DIR/subwindows/multiline-rubber-band.cpp \
  $$SRC_DIR/subwindows/rotateable-arrow-annotation.cpp \
  $$SRC_DIR/subwindows/multistep-annotation-base.cpp \


POPPLER_DIR = ~/gits/okular/poppler-install/lib

LIBS += -L$$POPPLER_DIR -lpoppler-qt5

#LIBS += -L$$TARGETSDIR  -laimlib -ldcmsr -lofstd -loflog -ldcmdata \
#   -ldcmimage -ldcmimgle


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
