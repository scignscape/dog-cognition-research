

#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


QT += gui  widgets

include(../build-group.pri)

DEFINES += USE_XCNS


# #  needed for destructuring bind ...
QMAKE_CXX = g++-7


CONFIG += c++17


INCLUDEPATH += $$XCSD_DATA_SRC_GROUP_DIR


HEADERS += \
  $$SRC_DIR/dialogs/xcsd-local-histogram-dialog.h \


SOURCES += \
  $$SRC_DIR/dialogs/xcsd-local-histogram-dialog.cpp \



#LIBS += -L$$TARGETSDIR -lxcsd-1d


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

