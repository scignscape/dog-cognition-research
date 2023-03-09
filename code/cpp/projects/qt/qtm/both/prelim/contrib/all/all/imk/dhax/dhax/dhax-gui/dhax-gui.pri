

#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)

QT += xml widgets network webenginewidgets


QT += multimedia
QT += multimediawidgets


INCLUDEPATH += $$SRC_DIR

INCLUDEPATH += $$SRC_PROSET_DIR/aimlib/aimlib/AIMLib/
INCLUDEPATH += $$SRC_KERNEL_DIR/iat/iat/


include($$ROOT_DIR/../preferred/compiler.pri)
include($$ROOT_DIR/../preferred/pdflatex.pri)
#? include($$ROOT_DIR/../preferred/openssl.pri)


DEFINES += PDFLATEX_EXE=\\\"$$PDFLATEX_EXE_FILE\\\"


INCLUDEPATH += $${POPPLER_INCLUDE_DIR}


CONFIG += c++17



##? FEATURE_IFC = USE_IFC
defined(FEATURE_IFC ,var) {
 DEFINES += $$FEATURE_IFC
 include($$ROOT_DIR/../preferred/occt.pri)
}


##? FEATURE_XCSD = USE_XCSD
defined(FEATURE_XCSD ,var) {
 DEFINES += $$FEATURE_XCSD
 LIBS += -L$$TARGETSDIR -lxcsd-1d -lxcsd-2d #-lxcsdx
}

##? FEATURE_CHASM = USE_CHASM
defined(FEATURE_CHASM ,var) {
 DEFINES += $$FEATURE_CHASM
 LIBS += -L$$TARGETSDIR -lchasm-lib -lchasm-lib-X1 -lchasm-lib-X2 \
   -lchasm-lib-33 -lchasm-lib-43
}


##? FEATURE_NGML = USE_NGML
defined(FEATURE_NGML ,var) {
 DEFINES += $$FEATURE_NGML
 LIBS += -L$$TARGETSDIR  -lngml-sdi
}


DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"

#include($$ROOT_DIR/../preferred/aim.pri)
#DEFINES += AIM_DATA_FOLDER=\\\"$$AIM_DATA_DIR\\\"

include($$ROOT_DIR/../preferred/dhax.pri)

include($$ROOT_DIR/../preferred/poppler.pri)

include($$ROOT_DIR/../preferred/you-tube.pri)


DEFINES += YOU_TUBE_DOWNLOAD_CMD_FOLDER=\\\"$${YOU_TUBE_DOWNLOAD_CMD_DIR}\\\"
DEFINES += YOU_TUBE_DOWNLOAD_EXE=\\\"$${YOU_TUBE_DOWNLOAD_EXE}\\\"
DEFINES += YOU_TUBE_DOWNLOAD_FOLDER=\\\"$${YOU_TUBE_DOWNLOAD_DIR}\\\"



DEFINES += DHAX_DATA_FOLDER=\\\"$$DHAX_DATA_DIR\\\"
DEFINES += DHAX_IMAGE_FOLDER=\\\"$$DHAX_IMAGE_DIR\\\"

DEFINES += DEFAULT_DHAX_TEMP_FOLDER=\\\"$$DHAX_TEMP_DIR\\\"
DEFINES += DEFAULT_DGI_TEMP_FOLDER=\\\"$$DGI_TEMP_DIR\\\"



DEFINES += DEFAULT_DEV_TKRZW_FOLDER=\\\"$$ROOT_DIR/../dev/consoles/dgdb/tkrzw\\\"

DEFINES += DEFAULT_DEV_DGDB_FOLDER=\\\"$$ROOT_DIR/../dev/consoles/dgdb/instances\\\"

DEFINES += SCREENSHOTS_FOLDER=\\\"$$ROOT_DIR/../dev/screenshots\\\"

DEFINES += DHAX_STAT_FOLDER=\\\"$${ROOT_DIR}/../dev/dhax-stats\\\"


DEFINES += USE_KANS


# #  for ntxh ...
INCLUDEPATH += $$NTXH_SRC_GROUP_DIR
INCLUDEPATH += $$NTXH_SRC_GROUP_DIR/ntxh
INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR


INCLUDEPATH += $$IAT_SRC_GROUP_DIR

#INCLUDEPATH += /home/nlevisrael/gits/ctg-temp/ar/code/cpp/src/prelim/contrib/all/all/imk/xcsd/xcsd-gui/xcsd-histograms/dialogs/
INCLUDEPATH += $$XCSD_GUI_SRC_GROUP_DIR
INCLUDEPATH += $$XCSD_GUI_SRC_GROUP_DIR/xcsd-scene
INCLUDEPATH += $$XCSD_GUI_SRC_GROUP_DIR/xcsd-histograms

#/home/nlevisrael/gits/ctg-temp/ar/code/cpp/projects/qt/qtm/both/prelim/contrib/all/all/

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


DEFINES += USE_XCNS

INCLUDEPATH += $$XCSD_SRC_GROUP_DIR
INCLUDEPATH += $$XCSD_SRC_GROUP_DIR/../xcsd-1d
INCLUDEPATH += $$XCSD_DATA_SRC_GROUP_DIR


#?FEATURE_OpenCV = USE_OpenCV

defined(FEATURE_OpenCV ,var) {

 message(Using OpenCV)

 DEFINES += $$FEATURE_OpenCV

 include($$ROOT_DIR/../preferred/opencv.pri)

 INCLUDEPATH += $$OPENCV_INCLUDE_DIR

# INCLUDEPATH += $$OPENCV_SRC_DIR/modules/core/include
# INCLUDEPATH += $$OPENCV_SRC_DIR/modules/imgproc/include
# INCLUDEPATH += $$OPENCV_SRC_DIR/modules/imgcodecs/include
# INCLUDEPATH += $$OPENCV_BUILD_DIR

 DCMTK_DIR = $$DCMTK_SRC_GROUP_DIR

 INCLUDEPATH += $$DCMTK_DIR/ofstd/include
 INCLUDEPATH += $$DCMTK_DIR/dcm-config/include
 INCLUDEPATH += $$DCMTK_DIR/dcmsr/include
 INCLUDEPATH += $$DCMTK_DIR/dcmdata/include
 INCLUDEPATH += $$DCMTK_DIR/oflog/include


 HEADERS += \
  $$SRC_DIR/stats/dhax-stat-assessment.h \
  $$SRC_DIR/stats/stat-test-image.h \
  $$SRC_DIR/stats/feature-classifier-transform.h \
  $$SRC_DIR/stats/slic/slic.h \
  $$SRC_DIR/stats/slico/slico.h \


SOURCES += \
  $$SRC_DIR/stats/dhax-stat-assessment.cpp \
  $$SRC_DIR/stats/dhax-stat-assessment.demo-test.cpp \
  $$SRC_DIR/stats/stat-test-image.cpp \
  $$SRC_DIR/stats/feature-classifier-transform.cpp \
  $$SRC_DIR/stats/slic/slic.cpp \
  $$SRC_DIR/stats/slico/slico.cpp \

}



INCLUDEPATH += $$POPPLER_INCLUDE_DIR


#?FEATURE_Forge = USE_Forge

defined(FEATURE_Forge ,var) {

 message(Using Forge)

 DEFINES += $$FEATURE_Forge

 HEADERS += \
   $$SRC_DIR/application/dhax-forge-controller.h \
   $$SRC_DIR/integration/forge-api/dhax-forge-api-integration-data.h \

 SOURCES += \
  $$SRC_DIR/application/dhax-forge-controller.cpp \
  $$SRC_DIR/integration/forge-api/dhax-forge-api-integration-data.cpp \

 LIBS += -L$$TARGETSDIR -liat-forge
}


#?FEATURE_Image_Editor = USE_Image_Editor

defined(FEATURE_Image_Editor ,var) {

 message(Using Image_Editor)

 DEFINES += $$FEATURE_Image_Editor

 LIBS += -L$$TARGETSDIR  -limage-editor

 INCLUDEPATH += $$AIMLIB_SRC_GROUP_DIR/../image-editor


}


HEADERS += \
  $$SRC_DIR/main-window/dhax-main-window.h \
  $$SRC_DIR/main-window/dhax-main-window-frame.h \
  $$SRC_DIR/main-window/dhax-main-window-data.h \
  $$SRC_DIR/main-window/dhax-main-window-menus.h \
  $$SRC_DIR/main-window/dhax-menu-system.h \
  $$SRC_DIR/main-window/dhax-main-window-controller.h \
  $$SRC_DIR/main-window/dhax-main-window-receiver.h \
  $$SRC_DIR/pdf-viewer/pdf-document-controller.h \
  $$SRC_DIR/pdf-viewer/pdf-document-info.h \
  $$SRC_DIR/pdf-viewer/pdf-document-state.h \
  $$SRC_DIR/application/dhax-application-controller.h \
  $$SRC_DIR/application/dhax-external-application-controller.h \
  $$SRC_DIR/application/dhax-application-receiver.h \
  $$SRC_DIR/application/dhax-application-state.h \
  $$SRC_DIR/dhax-graphics-view.h \
  $$SRC_DIR/dhax-graphics-scene.h \
  $$SRC_DIR/dhax-gui-environment.h \
  $$SRC_DIR/dhax-graphics-frame.h \
  $$SRC_DIR/dhax-signal-generator.h \
  $$SRC_DIR/image-viewer/dhax-image-viewer.h \
  $$SRC_DIR/image-viewer/dhax-image-scene-item.h \
  $$SRC_DIR/image-viewer/dhax-display-image-data.h \
  $$SRC_DIR/image-viewer/dhax-mouse-interaction-data.h \
  $$SRC_DIR/image-viewer/dhax-drawn-shape.h \
  $$SRC_DIR/image-viewer/image-document-controller.h \
  $$SRC_DIR/image-viewer/context-menu-prep-state.h \
  $$SRC_DIR/subwindows/range-slider.h \
  $$SRC_DIR/subwindows/clickable-label.h \
  $$SRC_DIR/pleneviews/shape-select-frame.h \
  $$SRC_DIR/pleneviews/zoom-and-navigate-frame.h \
  $$SRC_DIR/pleneviews/page-and-search-frame.h \
  $$SRC_DIR/integration/dhax-integration-controller.h \
  $$SRC_DIR/integration/meshlab/dhax-meshlab-integration-data.h \
  $$SRC_DIR/integration/meshlab/dhax-meshlab-integration-controller.h \
  $$SRC_DIR/integration/freecad/dhax-freecad-integration-data.h \
  $$SRC_DIR/integration/freecad/dhax-freecad-integration-controller.h \
  $$SRC_DIR/integration/ssr/dhax-ssr-integration-data.h \
  $$SRC_DIR/integration/ssr/dhax-ssr-integration-controller.h \
  $$SRC_DIR/virtual-packages/graphics-scene-demo.h \
  $$SRC_DIR/network/dhax-udp-controller.h \
  $$SRC_DIR/rpdf/rpdf-web-engine-page.h \
  $$SRC_DIR/rpdf/rpdf-web-engine-view.h \
  $$SRC_DIR/rpdf/webgl-view-dialog.h \
  $$SRC_DIR/rpdf/context-menu-provider.h \
  $$SRC_DIR/rpdf/url-or-event-pattern.h \
  $$SRC_DIR/rpdf/pattern-matcher-runtime.h \
  $$SRC_DIR/rpdf/my-page.h \
  $$SRC_DIR/rpdf/signal-generator.h \
  $$SRC_DIR/rpdf/bim-select-dialog.h \
  $$SRC_DIR/libspline/aaCurve.h \
  $$SRC_DIR/libspline/spline.h \
  $$SRC_DIR/aforms/dhax-annotation-presentation-data.h \
  $$SRC_DIR/aforms/multiline-rubber-band.h \
  $$SRC_DIR/aforms/skew-rhombus-annotation.h \
  $$SRC_DIR/aforms/rotateable-arrow-annotation.h \
  $$SRC_DIR/aforms/measurement-annotation.h \
  $$SRC_DIR/aforms/multistep-annotation-base.h \
  $$SRC_DIR/aforms/simple-annotation-base.h \
  $$SRC_DIR/aforms/simple/simple-rectangle-annotation.h \
  $$SRC_DIR/aforms/simple/simple-ellipse-annotation.h \
  $$SRC_DIR/aforms/simple/simple-polyline-annotation.h \
  $$SRC_DIR/aforms/measurement-dialogs/simple/simple-rectangle-measurement-dialog.h \
  $$SRC_DIR/dialogs/xcsd-local-histogram-dialog.h \
  $$SRC_DIR/dialogs/trimap-demo-frame.h \
  $$SRC_DIR/dialogs/color-mean-demo-frame.h \
  $$SRC_DIR/edge-detection/edge-detection-dialog.h \
  $$SRC_DIR/edge-detection/edge-detection-algorithms.h \
  $$SRC_DIR/edge-detection/edge-detection-kernels.h \
  $$SRC_DIR/dhax-video/dhax-video-grabber.h \
  $$SRC_DIR/dhax-video/dhax-video-navigation-frame.h \
  $$SRC_DIR/dhax-video/dhax-video-player-frame.h \
  $$SRC_DIR/dhax-video/dhax-video-player-dialog.h \
  $$SRC_DIR/dhax-video/dhax-video-annotation.h \
  $$SRC_DIR/dhax-video/dhax-video-annotation-set.h \


SOURCES += \
  $$SRC_DIR/main-window/dhax-main-window.cpp \
  $$SRC_DIR/main-window/dhax-main-window-frame.cpp \
  $$SRC_DIR/main-window/dhax-main-window-data.cpp \
  $$SRC_DIR/main-window/dhax-main-window-menus.cpp \
  $$SRC_DIR/main-window/dhax-main-window-controller.cpp \
  $$SRC_DIR/main-window/dhax-main-window-receiver.cpp \
  $$SRC_DIR/main-window/dhax-menu-system.cpp \
  $$SRC_DIR/pdf-viewer/pdf-document-controller.cpp \
  $$SRC_DIR/pdf-viewer/pdf-document-info.cpp \
  $$SRC_DIR/pdf-viewer/pdf-document-state.cpp \
  $$SRC_DIR/application/dhax-application-controller.cpp \
  $$SRC_DIR/application/dhax-application-controller.color-distance.cpp \
  $$SRC_DIR/application/dhax-application-controller.show-keypoints.cpp \
  $$SRC_DIR/application/dhax-application-state.cpp \
  $$SRC_DIR/application/dhax-application-receiver.cpp \
  $$SRC_DIR/application/dhax-external-application-controller.cpp \
  $$SRC_DIR/dhax-graphics-view.cpp \
  $$SRC_DIR/dhax-graphics-scene.cpp \
  $$SRC_DIR/dhax-gui-environment.cpp \
  $$SRC_DIR/dhax-graphics-frame.cpp \
  $$SRC_DIR/dhax-signal-generator.cpp \
  $$SRC_DIR/image-viewer/dhax-image-viewer.cpp \
  $$SRC_DIR/image-viewer/dhax-image-scene-item.cpp \
  $$SRC_DIR/image-viewer/dhax-mouse-interaction-data.cpp \
  $$SRC_DIR/image-viewer/dhax-drawn-shape.cpp \
  $$SRC_DIR/image-viewer/dhax-image-scene-item.mouse-events.cpp \
  $$SRC_DIR/image-viewer/image-document-controller.cpp \
  $$SRC_DIR/image-viewer/dhax-display-image-data.cpp \
  $$SRC_DIR/image-viewer/context-menu-prep-state.cpp \
  $$SRC_DIR/subwindows/range-slider.cpp \
  $$SRC_DIR/subwindows/clickable-label.cpp \
  $$SRC_DIR/pleneviews/shape-select-frame.cpp \
  $$SRC_DIR/pleneviews/zoom-and-navigate-frame.cpp \
  $$SRC_DIR/pleneviews/page-and-search-frame.cpp \
  $$SRC_DIR/integration/dhax-integration-controller.cpp \
  $$SRC_DIR/integration/meshlab/dhax-meshlab-integration-data.cpp \
  $$SRC_DIR/integration/meshlab/dhax-meshlab-integration-controller.cpp \
  $$SRC_DIR/integration/freecad/dhax-freecad-integration-data.cpp \
  $$SRC_DIR/integration/freecad/dhax-freecad-integration-controller.cpp \
  $$SRC_DIR/integration/ssr/dhax-ssr-integration-data.cpp \
  $$SRC_DIR/integration/ssr/dhax-ssr-integration-controller.cpp \
  $$SRC_DIR/virtual-packages/graphics-scene-demo.cpp \
  $$SRC_DIR/network/dhax-udp-controller.cpp \
  $$SRC_DIR/rpdf/rpdf-web-engine-page.cpp \
  $$SRC_DIR/rpdf/rpdf-web-engine-view.cpp \
  $$SRC_DIR/rpdf/webgl-view-dialog.cpp \
  $$SRC_DIR/rpdf/context-menu-provider.cpp \
  $$SRC_DIR/rpdf/url-or-event-pattern.cpp \
  $$SRC_DIR/rpdf/pattern-matcher-runtime.cpp \
  $$SRC_DIR/rpdf/my-page.cpp \
  $$SRC_DIR/rpdf/signal-generator.cpp \
  $$SRC_DIR/rpdf/bim-select-dialog.cpp \
  $$SRC_DIR/libspline/aaCurve.cpp \
  $$SRC_DIR/libspline/spline.cpp \
  $$SRC_DIR/aforms/dhax-annotation-presentation-data.cpp \
  $$SRC_DIR/aforms/multiline-rubber-band.cpp \
  $$SRC_DIR/aforms/rotateable-arrow-annotation.cpp \
  $$SRC_DIR/aforms/measurement-annotation.cpp \
  $$SRC_DIR/aforms/skew-rhombus-annotation.cpp \
  $$SRC_DIR/aforms/multistep-annotation-base.cpp \
  $$SRC_DIR/aforms/simple-annotation-base.cpp \
  $$SRC_DIR/aforms/simple/simple-rectangle-annotation.cpp \
  $$SRC_DIR/aforms/simple/simple-ellipse-annotation.cpp \
  $$SRC_DIR/aforms/simple/simple-polyline-annotation.cpp \
  $$SRC_DIR/aforms/measurement-dialogs/simple/simple-rectangle-measurement-dialog.cpp \
  $$SRC_DIR/dialogs/trimap-demo-frame.cpp \
  $$SRC_DIR/dialogs/color-mean-demo-frame.cpp \
  $$SRC_DIR/edge-detection/edge-detection-algorithms.cpp \
  $$SRC_DIR/edge-detection/edge-detection-dialog.cpp \
  $$SRC_DIR/dhax-video/dhax-video-grabber.cpp \
  $$SRC_DIR/dhax-video/dhax-video-navigation-frame.cpp \
  $$SRC_DIR/dhax-video/dhax-video-player-frame.cpp \
  $$SRC_DIR/dhax-video/dhax-video-player-dialog.cpp \
  $$SRC_DIR/dhax-video/dhax-video-annotation.cpp \
  $$SRC_DIR/dhax-video/dhax-video-annotation-set.cpp \
  $$SRC_DIR/dhax-video/instagram-temp.cpp \


# # todo should these be subwindows?
SOURCES += \
  $$XCSD_GUI_SRC_GROUP_DIR/xcsd-scene/xcsd-tierbox-scene-item.cpp \
  $$XCSD_GUI_SRC_GROUP_DIR/xcsd-scene/xcsd-outer-ring-scene-item.cpp \
  $$XCSD_GUI_SRC_GROUP_DIR/xcsd-histograms/dialogs/xcsd-local-histogram-dialog.cpp \


HEADERS += \
  $$XCSD_GUI_SRC_GROUP_DIR/xcsd-scene/xcsd-tierbox-scene-item.h \
  $$XCSD_GUI_SRC_GROUP_DIR/xcsd-scene/xcsd-outer-ring-scene-item.h \
  $$XCSD_GUI_SRC_GROUP_DIR/xcsd-histograms/dialogs/xcsd-local-histogram-dialog.h \

#$$SRC_DIR/subwindows/xcsd-tierbox-scene-item.h \
#$$SRC_DIR/subwindows/xcsd-outer-ring-scene-item.h \



QFontIcon_SRC_DIR = $$SRC_CONTRIB_DIR/external/QFontIcon-master/QFontIcon
INCLUDEPATH += $$QFontIcon_SRC_DIR/../
HEADERS += $$QFontIcon_SRC_DIR/qfonticon.h
SOURCES += $$QFontIcon_SRC_DIR/qfonticon.cpp
RESOURCES += $$QFontIcon_SRC_DIR/../resource.qrc


QtColorWidgets_SRC_DIR = $$SRC_CONTRIB_DIR/external/Qt-Color-Widgets-master
INCLUDEPATH += $$QtColorWidgets_SRC_DIR/include
FORMS += $$QtColorWidgets_SRC_DIR/src/QtColorWidgets/color_dialog.ui

message($$SRC_ROOT_DIR/external)

#FORMS += $$SRC_DIR/edge-detection/edge-detection-dialog.ui \


HEADERS += \
  $$QtColorWidgets_SRC_DIR/include/QtColorWidgets/color_dialog.hpp \
  $$QtColorWidgets_SRC_DIR/include/QtColorWidgets/color_wheel.hpp \
  $$QtColorWidgets_SRC_DIR/include/QtColorWidgets/hue_slider.hpp \
  $$QtColorWidgets_SRC_DIR/include/QtColorWidgets/gradient_slider.hpp \
  $$QtColorWidgets_SRC_DIR/include/QtColorWidgets/color_preview.hpp \
  $$QtColorWidgets_SRC_DIR/include/QtColorWidgets/color_line_edit.hpp \
  $$QtColorWidgets_SRC_DIR/include/QtColorWidgets/color_utils.hpp \
  $$QtColorWidgets_SRC_DIR/src/QtColorWidgets/color_names.hpp \


SOURCES += \
  $$QtColorWidgets_SRC_DIR/src/QtColorWidgets/color_dialog.cpp \
  $$QtColorWidgets_SRC_DIR/src/QtColorWidgets/color_wheel.cpp \
  $$QtColorWidgets_SRC_DIR/src/QtColorWidgets/hue_slider.cpp \
  $$QtColorWidgets_SRC_DIR/src/QtColorWidgets/gradient_slider.cpp \
  $$QtColorWidgets_SRC_DIR/src/QtColorWidgets/color_preview.cpp \
  $$QtColorWidgets_SRC_DIR/src/QtColorWidgets/color_line_edit.cpp \
  $$QtColorWidgets_SRC_DIR/src/QtColorWidgets/color_utils.cpp \
  $$QtColorWidgets_SRC_DIR/src/QtColorWidgets/color_names.cpp \


RESOURCES += \
  $$QtColorWidgets_SRC_DIR/resources/QtColorWidgets/color_widgets.qrc

# $$QtColorWidgets_SRC_DIR/src/QtColorWidgets/utils.cpp \


#  $$QtColorWidgets_SRC_DIR/src/QtColorWidgets/color_dialog.cpp \
#  $$QtColorWidgets_SRC_DIR/src/QtColorWidgets/color_dialog.cpp \



#  $$SRC_DIR/dhax-gui.cpp \


# #  for dcmtk OFString = std::string ...
DEFINES += HAVE_STD_STRING
DEFINES += HAVE_STL_STRING




LIBS += -L$$TARGETSDIR  \
  -lntxh  -lntxh-parser



#LIBS += -L$$TARGETSDIR  -laimlib -ldcmsr -lofstd -loflog -ldcmdata \
#   -ldcmimage -ldcmimgle

#? LIBS += -L$$TARGETSDIR  -laxfi

LIBS += -L$$POPPLER_LIB_DIR -lpoppler-qt5

#LIBS += -L$$TARGETSDIR  -laimlib

LIBS += -lrt


DEFINES += USE_KANS


defined(FEATURE_OpenCV ,var) {

 message(Linking OpenCV)

 LIBS += -L$$TARGETSDIR  -ldgi-opencv

 LIBS += -L$$OPENCV_LIB_DIR -lopencv_core -lopencv_imgcodecs -lopencv_imgproc

 LIBS += -L$$OPENCV_LIB_DIR  -lopencv_xfeatures2d  \
    -lopencv_features2d
}

#LIBS += -L$$TARGETSDIR -lchasm-lib -lchasm-lib-X1 -lchasm-lib-X2 \
#  -lchasm-lib-33 -lchasm-lib-43




include($$ROOT_DIR/../preferred/freecad.pri)
DEFINES += FREECAD_BIN_FOLDER=\\\"$$FREECAD_BIN_DIR\\\"

include($$ROOT_DIR/../preferred/ssr.pri)
DEFINES += SSR_BIN_FOLDER=\\\"$$SSR_BIN_DIR\\\"

#?LIBS += -L$$TARGETSDIR -ldgdb

#LIBS += -L$$TARGETSDIR -ltkrzw -llz4  -llzma -lz
LIBS += -L$$TARGETSDIR -llz4  -llzma -lz


#?LIBS += -L$$TARGETSDIR -lwhitedb




# LIBS += -L$$TARGETSDIR -laimlib


# #  assumed xerces is installed ...
LIBS += -lxerces-c



# ### For IFC (Industry Foundation Classes)
defined(FEATURE_IFC ,var) {
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
