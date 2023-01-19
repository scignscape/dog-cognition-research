
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


include(../build-group.pri)


QT -= gui

QMAKE_CC = gcc-7
QMAKE_CXX = g++-7

CONFIG += c++17

include($$ROOT_DIR/../preferred/sysr.pri)

#include($$ROOT_DIR/../preferred/sysr-c.pri)

DEFINES += DEFAULT_DEV_DGDB_FOLDER=\\\"$$ROOT_DIR/dev/consoles/dgdb\\\"

DEFINES += _TKRZW_PKG_VERSION=\\\"1.1.0\\\"
DEFINES += _TKRZW_PKG_VERSION=\\\"1.1.0\\\"


DEFINES += USE_KANS


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$WHITEDB_SRC_GROUP_DIR

INCLUDEPATH += $$SRC_GROUP_DIR/dgdb-white


HEADERS += \
  $$SRC_DIR/doxy-overview.h \
  $$SRC_DIR/tkrzw_cmd_util.h \
  $$SRC_DIR/tkrzw_compress.h \
  $$SRC_DIR/tkrzw_containers.h \
  $$SRC_DIR/tkrzw_dbm.h \
  $$SRC_DIR/tkrzw_dbm_async.h \
  $$SRC_DIR/tkrzw_dbm_baby.h \
  $$SRC_DIR/tkrzw_dbm_cache.h \
  $$SRC_DIR/tkrzw_dbm_common_impl.h \
  $$SRC_DIR/tkrzw_dbm_hash.h \
  $$SRC_DIR/tkrzw_dbm_hash_impl.h \
  $$SRC_DIR/tkrzw_dbm_poly.h \
  $$SRC_DIR/tkrzw_dbm_shard.h \
  $$SRC_DIR/tkrzw_dbm_skip.h \
  $$SRC_DIR/tkrzw_dbm_skip_impl.h \
  $$SRC_DIR/tkrzw_dbm_std.h \
  $$SRC_DIR/tkrzw_dbm_test_common.h \
  $$SRC_DIR/tkrzw_dbm_tiny.h \
  $$SRC_DIR/tkrzw_dbm_tree.h \
  $$SRC_DIR/tkrzw_dbm_tree_impl.h \
  $$SRC_DIR/tkrzw_file.h \
  $$SRC_DIR/tkrzw_file_mmap.h \
  $$SRC_DIR/tkrzw_file_poly.h \
  $$SRC_DIR/tkrzw_file_pos.h \
  $$SRC_DIR/tkrzw_file_std.h \
  $$SRC_DIR/tkrzw_file_test_common.h \
  $$SRC_DIR/tkrzw_file_util.h \
  $$SRC_DIR/tkrzw_hash_util.h \
  $$SRC_DIR/tkrzw_index.h \
  $$SRC_DIR/tkrzw_key_comparators.h \
  $$SRC_DIR/tkrzw_langc.h \
  $$SRC_DIR/tkrzw_lib_common.h \
  $$SRC_DIR/tkrzw_logger.h \
  $$SRC_DIR/tkrzw_str_util.h \
  $$SRC_DIR/tkrzw_sys_config.h \
  $$SRC_DIR/tkrzw_sys_file_mmap_std.h \
  $$SRC_DIR/tkrzw_sys_file_mmap_windows.h \
  $$SRC_DIR/tkrzw_sys_file_pos_std.h \
  $$SRC_DIR/tkrzw_sys_file_pos_windows.h \
  $$SRC_DIR/tkrzw_sys_util_posix.h \
  $$SRC_DIR/tkrzw_sys_util_windows.h \
  $$SRC_DIR/tkrzw_thread_util.h \
  $$SRC_DIR/tkrzw_time_util.h \

SOURCES += \
  $$SRC_DIR/tkrzw_langc_check.c \
  \# $$SRC_DIR/tkrzw_build_util.cc \
  $$SRC_DIR/tkrzw_cmd_util.cc \
  \# $$SRC_DIR/tkrzw_cmd_util_test.cc \
  $$SRC_DIR/tkrzw_compress.cc \
  \# $$SRC_DIR/tkrzw_compress_test.cc \
  \# $$SRC_DIR/tkrzw_containers_test.cc \
  $$SRC_DIR/tkrzw_dbm.cc \
  $$SRC_DIR/tkrzw_dbm_async.cc \
  \# $$SRC_DIR/tkrzw_dbm_async_test.cc \
  $$SRC_DIR/tkrzw_dbm_baby.cc \
  \# $$SRC_DIR/tkrzw_dbm_baby_test.cc \
  $$SRC_DIR/tkrzw_dbm_cache.cc \
  \# $$SRC_DIR/tkrzw_dbm_cache_test.cc \
  $$SRC_DIR/tkrzw_dbm_common_impl.cc \
  \# $$SRC_DIR/tkrzw_dbm_common_impl_test.cc \
  $$SRC_DIR/tkrzw_dbm_hash.cc \
  $$SRC_DIR/tkrzw_dbm_hash_impl.cc \
  \# $$SRC_DIR/tkrzw_dbm_hash_impl_test.cc \
  \# $$SRC_DIR/tkrzw_dbm_hash_test.cc \
  \# $$SRC_DIR/tkrzw_dbm_perf.cc \
  $$SRC_DIR/tkrzw_dbm_poly.cc \
  \# $$SRC_DIR/tkrzw_dbm_poly_test.cc \
  $$SRC_DIR/tkrzw_dbm_shard.cc \
  \# $$SRC_DIR/tkrzw_dbm_shard_test.cc \
  $$SRC_DIR/tkrzw_dbm_skip.cc \
  $$SRC_DIR/tkrzw_dbm_skip_impl.cc \
  \# $$SRC_DIR/tkrzw_dbm_skip_impl_test.cc \
  \# $$SRC_DIR/tkrzw_dbm_skip_test.cc \
  $$SRC_DIR/tkrzw_dbm_std.cc \
  \# $$SRC_DIR/tkrzw_dbm_std_test.cc \
  $$SRC_DIR/tkrzw_dbm_tiny.cc \
  \# $$SRC_DIR/tkrzw_dbm_tiny_test.cc \
  \# $$SRC_DIR/tkrzw_dbm_tran.cc \
  $$SRC_DIR/tkrzw_dbm_tree.cc \
  $$SRC_DIR/tkrzw_dbm_tree_impl.cc \
  \# $$SRC_DIR/tkrzw_dbm_tree_impl_test.cc \
  \# $$SRC_DIR/tkrzw_dbm_tree_test.cc \
  \# $$SRC_DIR/tkrzw_dbm_util.cc \
  $$SRC_DIR/tkrzw_dbm_ulog.cc \
  $$SRC_DIR/tkrzw_file_mmap.cc \
  \# $$SRC_DIR/tkrzw_file_mmap_test.cc \
  \# $$SRC_DIR/tkrzw_file_perf.cc \
  $$SRC_DIR/tkrzw_file_poly.cc \
  \# $$SRC_DIR/tkrzw_file_poly_test.cc \
  $$SRC_DIR/tkrzw_file_pos.cc \
  \# $$SRC_DIR/tkrzw_file_pos_test.cc \
  $$SRC_DIR/tkrzw_file_std.cc \
  \# $$SRC_DIR/tkrzw_file_std_test.cc \
  $$SRC_DIR/tkrzw_file_util.cc \
  \# $$SRC_DIR/tkrzw_file_util_test.cc \
  $$SRC_DIR/tkrzw_hash_util.cc \
  \# $$SRC_DIR/tkrzw_hash_util_test.cc \
  \# $$SRC_DIR/tkrzw_index_test.cc \
  \# $$SRC_DIR/tkrzw_key_comparators_test.cc \
  $$SRC_DIR/tkrzw_langc.cc \
  \# $$SRC_DIR/tkrzw_langc_test.cc \
  $$SRC_DIR/tkrzw_lib_common.cc \
  \# $$SRC_DIR/tkrzw_lib_common_test.cc \
  \# $$SRC_DIR/tkrzw_logger_test.cc \
  $$SRC_DIR/tkrzw_message_queue.cc \
  \# $$SRC_DIR/tkrzw_str_perf.cc \
  $$SRC_DIR/tkrzw_str_util.cc \
  \# $$SRC_DIR/tkrzw_str_util_test.cc \
  \# $$SRC_DIR/tkrzw_sys_config_test.cc \
  \# $$SRC_DIR/tkrzw_thread_util_test.cc \
  $$SRC_DIR/tkrzw_time_util.cc \
  \# $$SRC_DIR/tkrzw_time_util_test.cc \


