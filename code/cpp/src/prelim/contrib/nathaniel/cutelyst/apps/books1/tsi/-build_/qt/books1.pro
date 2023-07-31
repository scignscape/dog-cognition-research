

## auto-generated defines:
# INSTALL_ROOT_FOLDER: /home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/install
# APPS_ROOT_FOLDER: /home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/apps
# FRAMEWORK_ROOT_FOLDER: /home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/framework

INSTALL_ROOT_DIR=/home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/install
APPS_ROOT_DIR=/home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/apps
FRAMEWORK_ROOT_DIR=/home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/framework

DEFINES += INSTALL_ROOT_FOLDER=\\\"$${INSTALL_ROOT_DIR}\\\"
DEFINES += APPS_ROOT_FOLDER=\\\"$${APPS_ROOT_DIR}\\\"
DEFINES += FRAMEWORK_ROOT_FOLDER=\\\"$${FRAMEWORK_ROOT_DIR}\\\"


##  Paste this into the custom executable to run the server from Qt Creator ...
#  /home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/install/bin/cutelyst3-qt5
#  --server --app-file /home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/apps/books1/tsi/-build_/lib/libbooks1.so -- --chdir /home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/apps/books1/tsi/-build_/lib
#  /home/nlevisrael/Qt/5.15.2/gcc_64/lib:/home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/install/lib:$LD_LIBRARY_PATH

cmake_step.commands = cd ../run-cmake/working; \
  ../run-cmake.sh; make; ../copy-lib.sh
QMAKE_EXTRA_TARGETS += cmake_step
PRE_TARGETDEPS += cmake_step

INCLUDEPATH += \
  books1 \
  $${INSTALL_ROOT_DIR}/include/cutelyst3-qt5 \

TEMPLATE = lib

SRC_DIR = /home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/apps/books1/books1/src

HEADERS += \
  $${SRC_DIR}/root.h \
  $${SRC_DIR}/books1.h \

SOURCES += \
  $${SRC_DIR}/root.cpp \
  $${SRC_DIR}/books1.cpp \

LIBS += -L$${INSTALL_ROOT_DIR}/lib \
  -lCutelyst3Qt5 \

          