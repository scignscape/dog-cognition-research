
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


include(../build-group.pri)

QT -= gui

include($$ROOT_DIR/../preferred/sysr.pri)


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$WCM_SRC_GROUP_DIR
INCLUDEPATH += $$NTXH_SRC_GROUP_DIR
INCLUDEPATH += $$NTXH_SRC_GROUP_DIR/ntxh
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR

INCLUDEPATH += $$HTXN_SRC_GROUP_DIR


DEFINES += DEFAULT_WCM_FOLDER=\\\"$$DEV_ROOT_DIR/wcm\\\"

DEFINES += DEFAULT_NTXH_FOLDER=\\\"$$DEV_ROOT_DIR/ntxh\\\"

DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES

CONFIG += no_keywords


DEFINES += USE_KANS


HEADERS += \
  $$SRC_DIR/kernel/gtagml-dominion.h \
  $$SRC_DIR/kernel/gtagml-root.h \
  $$SRC_DIR/kernel/document/gtagml-document.h \
  $$SRC_DIR/kernel/document/gtagml-document-info.h \
  $$SRC_DIR/kernel/document/gtagml-folder.h \
  $$SRC_DIR/kernel/document/gtagml-project-info.h \
  $$SRC_DIR/kernel/dominion/connectors.h \
  $$SRC_DIR/kernel/dominion/types.h \
  $$SRC_DIR/kernel/frame/gtagml-frame.h \
  $$SRC_DIR/kernel/grammar/gtagml-grammar.h \
  $$SRC_DIR/kernel/grammar/gtagml-graph-build.h \
  $$SRC_DIR/kernel/grammar/gtagml-parser.h \
  $$SRC_DIR/kernel/grammar/gtagml-parsing-mode.h \
  $$SRC_DIR/kernel/grammar/gtagml-parse-context.h \
  $$SRC_DIR/kernel/graph/gtagml-graph.h \
  $$SRC_DIR/kernel/graph/gtagml-node.h \
  $$SRC_DIR/kernel/graph/gtagml-markup-position.h \
  $$SRC_DIR/kernel/query/gtagml-query.h \
  $$SRC_DIR/kernel/output/gtagml-connection-descriptor.h \
  $$SRC_DIR/kernel/output/gtagml-output-bundle.h \
  $$SRC_DIR/tile/gtagml-token.h \
  $$SRC_DIR/tile/gtagml-tile.h \
  $$SRC_DIR/tile/gtagml-raw-tile.h \
  $$SRC_DIR/tile/gtagml-attribute-tile.h \
  $$SRC_DIR/tile/gtagml-paralex-tile.h \
  $$SRC_DIR/annotation/gtagml-annotation-tile.h \
  $$SRC_DIR/annotation/gtagml-annotation-filter.h \
  $$SRC_DIR/tag-command/gtagml-tag-command.h \
  $$SRC_DIR/tag-command/gtagml-tag-command-callback.h \
  $$SRC_DIR/gh/gh-block-base.h  \
  $$SRC_DIR/gh/gh-block-parse-mode.h \
  $$SRC_DIR/gh/gh-block-writer.h  \
  $$SRC_DIR/gh/gh-block-standard-8bit.h \
  $$SRC_DIR/gh/gh-prenode.h \
  $$SRC_DIR/gh/gh-prenode-sequence.h \
  $$SRC_DIR/gh/gh-prenode-sequence-list.h \
  $$SRC_DIR/gh/gh-tag-command-node.h \
  $$SRC_DIR/gh/glyphdeck/gh-glyphdeck-standard-8bit.h \
  $$SRC_DIR/whitespace/gtagml-whitespace.h \
  $$SRC_DIR/whitespace/gtagml-whitespace-holder.h \
  $$SRC_DIR/output/gtagml-output-base.h \
  $$SRC_DIR/output/gtagml-output-callbacks-common.h \
  $$SRC_DIR/output/gtagml-output-event-generator.h \
  $$SRC_DIR/output/gtagml-output-event-handler.h \
  $$SRC_DIR/output/gtagml-output-latex.callbacks.h \
  $$SRC_DIR/output/gtagml-output-latex.h \
  $$SRC_DIR/output/gtagml-output-blocks.h \
  $$SRC_DIR/output/gtagml-output-blocks.callbacks.h \
  $$SRC_DIR/output/gtagml-output-sdi-infoset.h \
  $$SRC_DIR/output/gtagml-output-sdi-infoset.callbacks.h \
  $$SRC_DIR/sdi/gh-sdi-document.h \


SOURCES += \
  $$SRC_DIR/kernel/gtagml-dominion.cpp \
  $$SRC_DIR/kernel/document/gtagml-document.cpp \
  $$SRC_DIR/kernel/document/gtagml-document-info.cpp \
  $$SRC_DIR/kernel/document/gtagml-folder.cpp \
  $$SRC_DIR/kernel/document/gtagml-project-info.cpp \
  $$SRC_DIR/kernel/frame/gtagml-frame.cpp \
  $$SRC_DIR/kernel/grammar/gtagml-grammar.cpp \
  $$SRC_DIR/kernel/grammar/gtagml-graph-build.cpp \
  $$SRC_DIR/kernel/grammar/gtagml-parser.cpp \
  $$SRC_DIR/kernel/grammar/gtagml-parse-context.cpp \
  $$SRC_DIR/kernel/graph/gtagml-graph.cpp \
  $$SRC_DIR/kernel/graph/gtagml-node.cpp \
  $$SRC_DIR/kernel/graph/gtagml-markup-position.cpp \
  $$SRC_DIR/kernel/query/gtagml-query.cpp \
  $$SRC_DIR/kernel/output/gtagml-connection-descriptor.cpp \
  $$SRC_DIR/kernel/output/gtagml-output-bundle.cpp \
  $$SRC_DIR/tile/gtagml-token.cpp \
  $$SRC_DIR/tile/gtagml-tile.cpp \
  $$SRC_DIR/tile/gtagml-attribute-tile.cpp \
  $$SRC_DIR/tile/gtagml-paralex-tile.cpp \
  $$SRC_DIR/tile/gtagml-raw-tile.cpp \
  $$SRC_DIR/annotation/gtagml-annotation-tile.cpp \
  $$SRC_DIR/annotation/gtagml-annotation-filter.cpp \
  $$SRC_DIR/tag-command/gtagml-tag-command.cpp \
  $$SRC_DIR/tag-command/gtagml-tag-command-callback.cpp \
  $$SRC_DIR/gh/gh-block-base.cpp \
  $$SRC_DIR/gh/gh-block-parse-mode.cpp \
  $$SRC_DIR/gh/gh-block-writer.cpp \
  $$SRC_DIR/gh/gh-block-standard-8bit.cpp \
  $$SRC_DIR/gh/gh-prenode.cpp \
  $$SRC_DIR/gh/gh-prenode-sequence.cpp \
  $$SRC_DIR/gh/gh-prenode-sequence-list.cpp \
  $$SRC_DIR/gh/gh-tag-command-node.cpp \
  $$SRC_DIR/gh/glyphdeck/gh-glyphdeck-standard-8bit.cpp \
  $$SRC_DIR/whitespace/gtagml-whitespace.cpp \
  $$SRC_DIR/whitespace/gtagml-whitespace-holder.cpp \
  $$SRC_DIR/output/gtagml-output-event-handler.cpp \
  $$SRC_DIR/output/gtagml-output-event-generator.cpp \
  $$SRC_DIR/output/gtagml-output-latex.cpp \
  $$SRC_DIR/output/gtagml-output-base.cpp \
  $$SRC_DIR/output/gtagml-output-blocks.cpp \
  $$SRC_DIR/output/gtagml-output-sdi-infoset.cpp \
  $$SRC_DIR/sdi/gh-sdi-document.cpp \


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

