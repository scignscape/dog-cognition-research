
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)


QT += widgets gui


TEMPLATE = app


DEFINES += PROCESS_FOLDER=\\\"$$DESTDIR\\\"

INCLUDEPATH += \
  $$SRC_GROUP_DIR/alacarte/include

INCLUDEPATH += \
  $$SRC_GROUP_DIR/alacarte/extras




HEADERS += \
  $$SRC_GROUP_DIR/alacarte/include/importer/importer.hpp


SOURCES += \
  $$SRC_GROUP_DIR/alacarte/src/alacarte_importer.cpp \
  $$SRC_GROUP_DIR/alacarte/src/importer/importer.cpp


LIBS += -L$$TARGETSDIR -lqmt-alacarte-lib


LIBS += -lboost_program_options \
   -lboost_system  -lboost_filesystem \
   -lboost_serialization  -lboost_log \
   -lboost_log_setup -lboost_regex -lboost_iostreams \
   -lboost_chrono -lboost_date_time -lboost_atomic \
   -lboost_unit_test_framework \
