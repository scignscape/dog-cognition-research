
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


include(../build-group.pri)


DEFINES += QT_HOOK


INCLUDEPATH += \
   $$SRC_GROUP_DIR/alacarte/include/


INCLUDEPATH += \
  $$SRC_GROUP_DIR/alacarte/src/_qlog_


HEADERS += \
  $$SRC_GROUP_DIR/alacarte/src/_qlog_/qt-logger.h \


SOURCES += \
  $$SRC_GROUP_DIR/alacarte/src/_qlog_/qt-logger.cpp \


SOURCES += \
 $$SRC_GROUP_DIR/alacarte/src/general/configuration.cpp \
 $$SRC_GROUP_DIR/alacarte/src/general/geo_object.cpp \
 $$SRC_GROUP_DIR/alacarte/src/general/geodata.cpp \
 $$SRC_GROUP_DIR/alacarte/src/general/node.cpp \
 $$SRC_GROUP_DIR/alacarte/src/general/relation.cpp \
 $$SRC_GROUP_DIR/alacarte/src/general/way.cpp \
 $$SRC_GROUP_DIR/alacarte/src/precompiled_header.cpp \
 $$SRC_GROUP_DIR/alacarte/src/utils/applications.cpp \
 $$SRC_GROUP_DIR/alacarte/src/utils/archive.cpp \
 $$SRC_GROUP_DIR/alacarte/src/utils/cached_string.cpp \
 $$SRC_GROUP_DIR/alacarte/src/utils/colorTable.cpp \
 $$SRC_GROUP_DIR/alacarte/src/utils/precached_strings.cpp \
 $$SRC_GROUP_DIR/alacarte/src/utils/random.cpp \
 $$SRC_GROUP_DIR/alacarte/src/utils/statistic.cpp \
 $$SRC_GROUP_DIR/alacarte/src/utils/transform.cpp

HEADERS += \
 $$SRC_GROUP_DIR/alacarte/include/general/configuration.hpp \
 $$SRC_GROUP_DIR/alacarte/include/general/geo_object.hpp \
 $$SRC_GROUP_DIR/alacarte/include/general/geodata.hpp \
 $$SRC_GROUP_DIR/alacarte/include/general/node.hpp \
 $$SRC_GROUP_DIR/alacarte/include/general/relation.hpp \
 $$SRC_GROUP_DIR/alacarte/include/general/rtree.hpp \
 $$SRC_GROUP_DIR/alacarte/include/general/way.hpp \
 $$SRC_GROUP_DIR/alacarte/include/settings.hpp \
 $$SRC_GROUP_DIR/alacarte/include/utils/application.hpp \
 $$SRC_GROUP_DIR/alacarte/include/utils/archive.hpp \
 $$SRC_GROUP_DIR/alacarte/include/utils/cached_string.hpp \
 $$SRC_GROUP_DIR/alacarte/include/utils/color.hpp \
 $$SRC_GROUP_DIR/alacarte/include/utils/colorTable.hpp \
 $$SRC_GROUP_DIR/alacarte/include/utils/exceptions.hpp \
 $$SRC_GROUP_DIR/alacarte/include/utils/obj_counter.hpp \
 $$SRC_GROUP_DIR/alacarte/include/utils/point.hpp \
 $$SRC_GROUP_DIR/alacarte/include/utils/precached_strings.hpp \
 $$SRC_GROUP_DIR/alacarte/include/utils/random.hpp \
 $$SRC_GROUP_DIR/alacarte/include/utils/rect.hpp \
 $$SRC_GROUP_DIR/alacarte/include/utils/statistic.hpp \
 $$SRC_GROUP_DIR/alacarte/include/utils/transform.hpp \
 $$SRC_GROUP_DIR/alacarte/include/utils/typedId.hpp
