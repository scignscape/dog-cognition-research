

#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)

QT += xml widgets

INCLUDEPATH += $$SRC_DIR

INCLUDEPATH += $$SRC_PROSET_DIR/aimlib/aimlib/AIMLib/

include($$ROOT_DIR/../preferred/compiler.pri)


CONFIG += c++17


DEFINES += USE_KANS

DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"

#include($$ROOT_DIR/../preferred/aim.pri)
#DEFINES += AIM_DATA_FOLDER=\\\"$$AIM_DATA_DIR\\\"

include($$ROOT_DIR/../preferred/dhax.pri)

DEFINES += DHAX_DATA_FOLDER=\\\"$$DHAX_DATA_DIR\\\"
DEFINES += DHAX_IMAGE_FOLDER=\\\"$$DHAX_IMAGE_DIR\\\"


DEFINES += DEFAULT_DEV_TKRZW_FOLDER=\\\"$$ROOT_DIR/../dev/consoles/dgdb/tkrzw\\\"

DEFINES += DEFAULT_DEV_DGDB_FOLDER=\\\"$$ROOT_DIR/../dev/consoles/dgdb/instances\\\"


DEFINES += USE_KANS

INCLUDEPATH += $$DGDB_SRC_GROUP_DIR

INCLUDEPATH += $$DGDB_SRC_GROUP_DIR/tkrzw


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

INCLUDEPATH += $$SRC_GROUP_DIR/tkrzw

INCLUDEPATH += $$WHITEDB_SRC_GROUP_DIR


HEADERS += \
  $$SRC_DIR/ann/dhax-annotation-target.h \
  $$SRC_DIR/ann/dhax-annotation-environment.h \
  $$SRC_DIR/ann/dhax-annotation-folder.h \
  $$SRC_DIR/ann/dhax-annotation-group.h \
  $$SRC_DIR/ann/dhax-annotation-instance.h \
  $$SRC_DIR/ann/location/dhax-location-2d.h \
  $$SRC_DIR/ann/location/dhax-signed-location-2d.h \
  $$SRC_DIR/ann/location/dhax-float-location-2d.h \
  $$SRC_DIR/ann/location/dhax-double-location-2d.h \



SOURCES += \
  $$SRC_DIR/ann/dhax-annotation-target.cpp \
  $$SRC_DIR/ann/dhax-annotation-environment.cpp \
  $$SRC_DIR/ann/dhax-annotation-folder.cpp \
  $$SRC_DIR/ann/dhax-annotation-group.cpp \
  $$SRC_DIR/ann/dhax-annotation-instance.cpp \
  $$SRC_DIR/ann/dhax-annotation-instance.ic-rect.cpp \
  $$SRC_DIR/ann/location/dhax-location-2d.cpp \
  $$SRC_DIR/ann/location/dhax-signed-location-2d.cpp \
  $$SRC_DIR/ann/location/dhax-float-location-2d.cpp \
  $$SRC_DIR/ann/location/dhax-double-location-2d.cpp \



# #  for dcmtk OFString = std::string ...
DEFINES += HAVE_STD_STRING
DEFINES += HAVE_STL_STRING



#LIBS += -L$$TARGETSDIR  -laimlib -ldcmsr -lofstd -loflog -ldcmdata \
#   -ldcmimage -ldcmimgle

#LIBS += -L$$TARGETSDIR  -laxfi

LIBS += -lrt


#LIBS += -L$$TARGETSDIR -ldgdb

#LIBS += -L$$TARGETSDIR -ltkrzw -llz4  -llzma -lz
LIBS += -L$$TARGETSDIR -llz4  -llzma -lz

#LIBS += -L$$TARGETSDIR -lwhitedb



#LIBS += -L$$TARGETSDIR -laimlib


# #  assumed xerces is installed ...
LIBS += -lxerces-c


DCMTK_DIR = $$DCMTK_SRC_GROUP_DIR


INCLUDEPATH += $$DCMTK_DIR/ofstd/include
INCLUDEPATH += $$DCMTK_DIR/dcm-config/include
INCLUDEPATH += $$DCMTK_DIR/dcmsr/include
INCLUDEPATH += $$DCMTK_DIR/dcmdata/include
INCLUDEPATH += $$DCMTK_DIR/oflog/include


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

