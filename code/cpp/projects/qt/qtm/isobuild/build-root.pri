
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)




defined(QMAKE_CONSOLE_TARGET_DIR, var){
 CHOICE_CODE = qmake-console-choices
 WHICH_BUILD_DIR_CODE = qmake-console
 include(../_choices/$${WHICH_BUILD_DIR_CODE}_choices.pri)
 BUILD_DIR_CODE = qmake-console
} else {
 CHOICE_CODE = isobuild-choices
 WHICH_BUILD_DIR_CODE = isobuild
 include(../_choices/$${WHICH_BUILD_DIR_CODE}_choices.pri)
 BUILD_DIR_CODE = qmake-console
 BUILD_DIR_CODE = $$OUT_PWD
 BUILD_DIR_CODE ~= s!.*/(build|release)-($$PROJECT_NAME)-(.*)-(Debug|Release)!\3
}

include(../build-root-both.pri)


