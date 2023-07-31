

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
# executable path:
#   /home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/install/bin/cutelyst3-qt5
# command line arguments:
#   --server --app-file /home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/apps/books-2/tsi/-build_/lib/libbooks-2.so -- --chdir /home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/apps/books-2/tsi/-build_/lib
# working directory:
#   /home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/apps/books-2/tsi
# add to the environment:
#   /home/nlevisrael/Qt/5.15.2/gcc_64/lib:/home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/install/lib:$LD_LIBRARY_PATH

cmake_step.commands = cd ../run-cmake/working; \
../run-cmake.sh; make; ../copy-lib.sh
QMAKE_EXTRA_TARGETS += cmake_step
PRE_TARGETDEPS += cmake_step

INCLUDEPATH += \
books-2 \
$$INSTALL_ROOT_DIR/include/cutelyst3-qt5 \

TEMPLATE = lib

SRC_DIR = $${APPS_ROOT_DIR}/books-2/books-2/src


HEADERS += \
 $$SRC_DIR/root.h \
 $$SRC_DIR/books-2.h \
 $$SRC_DIR/books.h \


SOURCES += \
 $$SRC_DIR/root.cpp \
 $$SRC_DIR/books-2.cpp \
 $$SRC_DIR/books.cpp \


DISTFILES += \
 $$SRC_DIR/../CMakeLists.txt \
 $$SRC_DIR/CMakeLists.txt \




LIBS += -L$$INSTALL_ROOT_DIR/lib \
-lCutelyst3Qt5 \

