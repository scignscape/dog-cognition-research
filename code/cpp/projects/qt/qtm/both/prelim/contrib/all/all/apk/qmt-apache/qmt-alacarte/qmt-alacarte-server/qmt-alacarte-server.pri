
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


include(../build-group.pri)


QT += gui  #?widgets


QMAKE_CC = gcc-7
QMAKE_CXX = g++-7

CONFIG += c++17

TEMPLATE = lib

# http://localhost:11213/14/8529/5974.png
# http://localhost:11213/12/1205/1540.png
# http://localhost:11213/12/1171/1566.png
# http://localhost:11213/14/4685/6267.png

# http://localhost:11213/14/9676/5786.png
# https//localhost:11213/13/4837/2893.png

# http://localhost:11213/14/8529/5974.png


#/home/nlevisrael/gits/osm/alacarte-master/-run-cmake_/install/etc/alacarte-maps.conf


INCLUDEPATH += \
   $$SRC_GROUP_DIR/alacarte/include


INCLUDEPATH += \
  /usr/include/cairo \



DEFINES += BOOST_LOG_DYN_LINK


DEFINES += DEFAULT_PORT=\\\"11213\\\"  # a-l-a-c


#DISTFILES += \
#  /home/nlevisrael/gits/osm/alacarte-master/-run-cmake_/install/share/alacarte-maps/styles/default.mapcss





HEADERS += \
  $$SRC_GROUP_DIR/alacarte/include/server/cache.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/eval/binary_operation_node.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/eval/eval.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/eval/eval_helpers.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/eval/function_operation_node.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/eval/stleaf.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/eval/stnode.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/eval/unary_operation_node.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/http/request_parser.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/http_request.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/http_server.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/job.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/meta_identifier.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/parser/color_grammar.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/parser/comment_skipper.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/parser/eval_grammar.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/parser/mapcss_def.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/parser/mapcss_grammar.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/parser/mapcss_parser.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/parser/parse_info.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/parser/parse_info_parser.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/parser/parser_logger.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/render_attributes.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/request_manager.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/rule.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/selectors/apply_selector.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/selectors/area_selector.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/selectors/childnodes_selector.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/selectors/childways_selector.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/selectors/hasnottag_selector.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/selectors/hastag_selector.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/selectors/line_selector.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/selectors/selector.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/selectors/selectors.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/selectors/tagequals_selector.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/selectors/taglarger_selector.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/selectors/taglargerequals_selector.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/selectors/tagmatches_selector.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/selectors/tagsmaller_selector.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/selectors/tagsmallerequals_selector.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/selectors/tagunequals_selector.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/style.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/style_template.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/stylesheet.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/stylesheet_manager.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/tile.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/tile_identifier.hpp \
  $$SRC_GROUP_DIR/alacarte/src/server/_qmt_/job-context.h \
  $$SRC_GROUP_DIR/alacarte/src/server/_qmt_/qmt-accessors.h \
  $$SRC_GROUP_DIR/alacarte/src/server/_qmt_/qmt-enum-macros.h \
  $$SRC_GROUP_DIR/alacarte/src/server/_qmt_/qmt-global-macros.h \
  $$SRC_GROUP_DIR/alacarte/src/server/_qmt_/qmt-global-types.h


HEADERS += \
  $$SRC_GROUP_DIR/alacarte/include/server/renderer/node_renderer.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/renderer/object_renderer.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/renderer/relation_renderer.hpp \
  $$SRC_GROUP_DIR/alacarte/include/server/renderer/way_renderer.hpp


#HEADERS += \
#  $$SRC_GROUP_DIR/alacarte/src/server/renderer/node_renderer.hpp \
#  $$SRC_GROUP_DIR/alacarte/src/server/renderer/object_renderer.hpp \
#  $$SRC_GROUP_DIR/alacarte/src/server/renderer/relation_renderer.hpp \
#  $$SRC_GROUP_DIR/alacarte/src/server/renderer/way_renderer.hpp


#HEADERS += \
#   $$SRC_GROUP_DIR/alacarte/src/server/qlog/qt-logger.h
#

SOURCES += \
   $$SRC_GROUP_DIR/alacarte/src/server/_qmt_/job-context.cpp \
   $$SRC_GROUP_DIR/alacarte/src/server/_qmt_/single-job-context.cpp \
   $$SRC_GROUP_DIR/alacarte/src/server/_qmt_/qmt-tile-object.cpp \


HEADERS += \
   $$SRC_GROUP_DIR/alacarte/src/server/_qmt_/job-context.h \
   $$SRC_GROUP_DIR/alacarte/src/server/_qmt_/single-job-context.h \
   $$SRC_GROUP_DIR/alacarte/src/server/_qmt_/qmt-tile-object.h \


DEFINES += QT_HOOK



INCLUDEPATH += \
  $$SRC_GROUP_DIR/alacarte/src/_qlog_


SOURCES += \
  $$SRC_GROUP_DIR/alacarte/src/alacarte_server.cpp \

SOURCES += \
  $$SRC_GROUP_DIR/alacarte/src/server/cache.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/eval/binary_operation_node.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/eval/eval.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/eval/eval_helpers.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/eval/function_operation_node.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/eval/stleaf.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/eval/unary_operation_node.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/http/request_parser.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/http_request.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/http_server.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/job.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/meta_identifier.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/parser/color_grammar.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/parser/comment_skipper.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/parser/eval_grammar.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/parser/mapcss_grammar.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/parser/mapcss_parser.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/parser/parser_logger.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/renderer/node_renderer.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/renderer/object_renderer.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/renderer/relation_renderer.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/renderer/render_canvas.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/renderer/renderer.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/renderer/way_renderer.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/request_manager.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/rule.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/selectors/apply_selector.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/selectors/area_selector.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/selectors/childnodes_selector.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/selectors/childways_selector.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/selectors/hasnottag_selector.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/selectors/hastag_selector.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/selectors/line_selector.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/selectors/selector.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/selectors/tagequals_selector.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/selectors/taglarger_selector.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/selectors/taglargerequals_selector.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/selectors/tagmatches_selector.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/selectors/tagsmaller_selector.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/selectors/tagsmallerequals_selector.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/selectors/tagunequals_selector.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/style.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/style_template.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/stylesheet.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/stylesheet_manager.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/tile.cpp \
  $$SRC_GROUP_DIR/alacarte/src/server/tile_identifier.cpp


#SOURCES += \
#   $$SRC_GROUP_DIR/alacarte/src/server/qlog/qt-logger.cpp


LIBS += -L$$TARGETSDIR -lqmt-alacarte-lib


LIBS += -lboost_program_options \
   -lboost_system  -lboost_filesystem \
   -lboost_serialization  -lboost_log  -lboost_thread \
   -lboost_log_setup -lboost_regex -lboost_iostreams \
   -lboost_chrono -lboost_date_time -lboost_atomic \
   -lboost_unit_test_framework \


LIBS += -lcairo


