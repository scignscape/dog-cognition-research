

##
cmake_step.commands = cd ../run-cmake/working; \
  ../run-cmake.sh; make; make install
QMAKE_EXTRA_TARGETS += cmake_step
PRE_TARGETDEPS += cmake_step


include(../preferred/cmake.pri)

exists(../preferred/compiler.pri): include(../preferred/compiler.pri)


DEFINES += CMAKE_EXE=\\\"$${CMAKE_EXECUTABLE}\\\"

DEFINES += COMPILER_CMD_CXX=\\\"$${QMAKE_CXX}\\\"
DEFINES += COMPILER_CMD_CC=\\\"$${QMAKE_CC}\\\"



#QMAKE_CC=/home/nlevisrael/gits/gcc-10/install/bin/gcc
#QMAKE_CXX=/home/nlevisrael/gits/gcc-10/install/bin/g++
#message(QMAKE_CXX_PATH: $${QMAKE_CXX_PATH})


#cmake_step.commands = cd /home/nlevisrael/gits/cutelyst/-build_/run-cmake; echo 'p'; echo `pwd`; \
#  ./run-cmake.sh; make; make install
#QMAKE_EXTRA_TARGETS += cmake_step
#PRE_TARGETDEPS += cmake_step



#done.commands = echo 'Qt make step skipped'
#QMAKE_EXTRA_TARGETS += done


QT += network


DEFINES += QT_5_or_6=QT_MAJOR_VERSION


ROOT_DIR = $$_PRO_FILE_PWD_
ROOT_DIR ~= s!/-build_/qt.*!!


FRAMEWORK_ROOT_DIR = $${ROOT_DIR}/framework
APPS_ROOT_DIR = $${ROOT_DIR}/apps
INSTALL_ROOT_DIR = $${ROOT_DIR}/-build_/install
BUILD_WORKING_DIR = $${ROOT_DIR}/-build_/run-cmake/working

#CMAKE_CURRENT_SOURCE_DIR=N/A

DEFINES += QT_LIBS_FOLDER=\\\"$$[QT_INSTALL_LIBS]\\\"
DEFINES += QT_CMAKE_FOLDER=\\\"$$[QT_INSTALL_LIBS]/cmake\\\"


DEFINES += FRAMEWORK_ROOT_FOLDER=\\\"$${FRAMEWORK_ROOT_DIR}\\\"
DEFINES += ROOT_FOLDER=\\\"$${ROOT_DIR}\\\"
DEFINES += APPS_ROOT_FOLDER=\\\"$${APPS_ROOT_DIR}\\\"
DEFINES += INSTALL_ROOT_FOLDER=\\\"$${INSTALL_ROOT_DIR}\\\"

DEFINES += CMAKE_CURRENT_SOURCE_FOLDER

DEFINES += TSI_QMAKE_GENERATED=1
DEFINES += TSI_CMAKE_GENERATED=0


#DEFINES += FRAMEWORK_ROOT_FOLDER_qt=\\\"$${FRAMEWORK_ROOT_DIR}\\\"_qt
#DEFINES += ROOT_FOLDER_qt=\\\"$${ROOT_DIR}\\\"_qt
#DEFINES += APPS_ROOT_FOLDER_qt=\\\"$${APPS_ROOT_DIR}\\\"_qt
#DEFINES += INSTALL_ROOT_FOLDER_qt=\\\"$${INSTALL_ROOT_DIR}\\\"_qt
#? DEFINES += CMAKE_CURRENT_SOURCE_FOLDER_qt=\\\"$${CMAKE_CURRENT_SOURCE_DIR}\\\"_qt





INCLUDEPATH += \
  $${INSTALL_ROOT_DIR}/include/cutelyst3-qt5 \
  $${INSTALL_ROOT_DIR}/include/cutelyst3-qt5/Cutelyst \
  $${BUILD_WORKING_DIR} \

INCLUDEPATH += \
  $${FRAMEWORK_ROOT_DIR} \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst \


# /home/nlevisrael/gits/cutelyst/cutelyst/Cutelyst/

#  ../../ \

#INCLUDEPATH += \
#  /home/nlevisrael/gits/cutelyst \





#/home/nlevisrael/gits/cutelyst/-build_/install/include/cutelyst3-qt5/ \

# $${FRAMEWORK_ROOT_DIR} \
#/home/nlevisrael/gits/cutelyst/-build_/install/include/cutelyst3-qt5/



DISTFILES += \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/CutelystQt5Core.pc.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/CutelystQt5Authentication.pc.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/CSRFProtection/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/CSRFProtection/CutelystQt5CSRFProtection.5.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/CSRFProtection/CutelystQt5CSRFProtection.pc.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/CSRFProtection/i18n/plugin_csrfprotection.de.ts \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/CSRFProtection/i18n/plugin_csrfprotection.en.ts \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Memcached/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Memcached/CutelystQt5Memcached.5.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Memcached/CutelystQt5Memcached.pc.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Memcached/i18n/plugin_memcached.de.ts \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Memcached/i18n/plugin_memcached.en.ts \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/MemcachedSessionStore/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/MemcachedSessionStore/CutelystQt5MemcachedSessionStore.5.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/MemcachedSessionStore/CutelystQt5MemcachedSessionStore.pc.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Session/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Session/CutelystQt5Session.5.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Session/CutelystQt5Session.pc.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/StaticCompressed/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/StaticCompressed/CutelystQt5StaticCompressed.pc.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/StaticSimple/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/StaticSimple/CutelystQt5StaticSimple.pc.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/StatusMessage/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/StatusMessage/CutelystQt5StatusMessage.pc.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/UserAgent/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/UserAgent/CutelystQt5UserAgent.pc.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/LangSelect/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/LangSelect/CutelystQt5UtilsLangSelect.pc.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Pagination/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Pagination/CutelystQt5UtilsPagination.pc.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Sql/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Sql/CutelystQt5UtilsSql.pc.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/CutelystQt5UtilsValidator.pc.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/i18n/plugin_utils_validator.de.ts \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/i18n/plugin_utils_validator.en.ts \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/ClearSilver/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/ClearSilver/CutelystQt5ViewClearSilver.pc.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/ClearSilver/metadata.json \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Cutelee/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Cutelee/CutelystQt5Cutelee.pc.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Cutelee/i18n/plugin_view_cutelee.de.ts \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Cutelee/i18n/plugin_view_cutelee.en.ts \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Email/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Email/CutelystQt5ViewEmail.pc.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Grantlee/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Grantlee/CutelystQt5Grantlee.pc.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Grantlee/i18n/plugin_view_grantlee.de.ts \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Grantlee/i18n/plugin_view_grantlee.en.ts \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/JSON/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/JSON/CutelystQt5ViewJSON.pc.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/cutelyst.doxygen \
  $${FRAMEWORK_ROOT_DIR}/server/CMakeLists.txt \
  $${FRAMEWORK_ROOT_DIR}/server/CutelystQt5Server.pc.in \
  $${FRAMEWORK_ROOT_DIR}/server/i18n/cutelystserver.de.ts \
  $${FRAMEWORK_ROOT_DIR}/server/i18n/cutelystserver.en.ts

HEADERS += \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Action \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/ActionChain \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Application \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Component \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/ComponentFactory \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Context \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Controller \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Cookie \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/DispatchType \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Dispatcher \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Engine \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Headers \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/ParamsMultiMap \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugin \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/authentication.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/authentication_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/authenticationrealm.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/authenticationstore.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/authenticationuser.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/credentialhttp.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/credentialhttp_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/credentialpassword.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/credentialpassword_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/htpasswd.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/minimal.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/CSRFProtection/CSRFProtection \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/CSRFProtection/csrfprotection.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/CSRFProtection/csrfprotection_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Memcached/Memcached \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Memcached/memcached.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Memcached/memcached_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/MemcachedSessionStore/MemcachedSessionStore \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/MemcachedSessionStore/memcachedsessionstore.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/MemcachedSessionStore/memcachedsessionstore_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Session/Session \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Session/session.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Session/session_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Session/sessionstorefile.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/StaticCompressed/StaticCompressed \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/StaticCompressed/staticcompressed.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/StaticCompressed/staticcompressed_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/StaticSimple/StaticSimple \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/StaticSimple/staticsimple.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/StaticSimple/staticsimple_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/StatusMessage/StatusMessage \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/StatusMessage/statusmessage.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/UserAgent/UserAgent \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/UserAgent/useragent.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/LangSelect/LangSelect \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/LangSelect/langselect.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/LangSelect/langselect_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Pagination/Pagination \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Pagination/pagination.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Sql/Sql \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Sql/sql.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/Validator \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/ValidatorResult \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/ValidatorRule \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/Validators \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validator.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validator_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatoraccepted.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatoraccepted_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorafter.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorafter_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatoralpha.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatoralpha_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatoralphadash.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatoralphadash_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatoralphanum.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatoralphanum_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorbefore.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorbefore_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorbetween.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorbetween_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorboolean.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorboolean_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorcharnotallowed.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorcharnotallowed_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorconfirmed.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorconfirmed_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatordate.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatordate_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatordatetime.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatordatetime_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatordifferent.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatordifferent_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatordigits.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatordigits_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatordigitsbetween.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatordigitsbetween_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatordomain.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatordomain_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatoremail.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatoremail_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorfilesize.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorfilesize_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorfilled.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorfilled_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorin.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorin_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorinteger.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorinteger_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorip.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorip_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorjson.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorjson_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatormax.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatormax_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatormin.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatormin_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatornotin.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatornotin_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatornumeric.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatornumeric_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorpresent.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorpresent_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorpwquality.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorpwquality_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorregularexpression.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorregularexpression_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequired.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequired_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredif.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredif_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredifstash.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredifstash_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredunless.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredunless_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredunlessstash.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredunlessstash_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredwith.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredwith_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredwithall.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredwithall_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredwithout.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredwithout_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredwithoutall.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredwithoutall_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorresult.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorresult_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrule.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrule_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorsame.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorsame_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorsize.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorsize_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatortime.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatortime_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorurl.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorurl_p.h \
\#  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/ClearSilver/clearsilver.h \
\#  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/ClearSilver/clearsilver_p.h \
\#  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Cutelee/csrf.h \
\#  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Cutelee/cuteleeview.h \
\#  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Cutelee/cuteleeview_p.h \
\#  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Cutelee/cutelystcutelee.h \
\#  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Cutelee/urifor.h \
\#  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Email/viewemail.h \
\#  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Email/viewemail_p.h \
\#  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Email/viewemailtemplate.h \
\#  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Email/viewemailtemplate_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Grantlee/csrf.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Grantlee/cutelystgrantlee.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Grantlee/grantleeview.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Grantlee/grantleeview_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Grantlee/urifor.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/JSON/viewjson.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/JSON/viewjson_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Request \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Response \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Upload \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/View \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/action.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/action_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/actionchain.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/actionchain_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/application.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/application_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/async.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/common.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/component.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/component_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/componentfactory.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/context.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/context_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/controller.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/controller_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/cookie.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/cookie_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/cutelyst_global.h.in \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/dispatcher.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/dispatcher_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/dispatchtype.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/dispatchtypechained.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/dispatchtypechained_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/dispatchtypepath.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/dispatchtypepath_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/engine.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/engine_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/enginerequest.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/headers.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/multipartformdataparser.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/multipartformdataparser_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/paramsmultimap.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/plugin.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/request.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/request_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/response.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/response_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/stats.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/stats_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/upload.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/upload_p.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/utils.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/view.h \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/view_p.h \
  $${FRAMEWORK_ROOT_DIR}/EventLoopEPoll/eventdispatcher_epoll.h \
  $${FRAMEWORK_ROOT_DIR}/EventLoopEPoll/eventdispatcher_epoll_p.h \
   $${FRAMEWORK_ROOT_DIR}/server/abstractfork.h \
  $${FRAMEWORK_ROOT_DIR}/server/cwsgiengine.h \
  $${FRAMEWORK_ROOT_DIR}/server/hpack.h \
  $${FRAMEWORK_ROOT_DIR}/server/hpack_p.h \
  $${FRAMEWORK_ROOT_DIR}/server/localserver.h \
  $${FRAMEWORK_ROOT_DIR}/server/postunbuffered.h \
  $${FRAMEWORK_ROOT_DIR}/server/protocol.h \
  $${FRAMEWORK_ROOT_DIR}/server/protocolfastcgi.h \
  $${FRAMEWORK_ROOT_DIR}/server/protocolhttp.h \
  $${FRAMEWORK_ROOT_DIR}/server/protocolhttp2.h \
  $${FRAMEWORK_ROOT_DIR}/server/protocolwebsocket.h \
  $${FRAMEWORK_ROOT_DIR}/server/server.h \
  $${FRAMEWORK_ROOT_DIR}/server/server_p.h \
  $${FRAMEWORK_ROOT_DIR}/server/socket.h \
  $${FRAMEWORK_ROOT_DIR}/server/staticmap.h \
  $${FRAMEWORK_ROOT_DIR}/server/systemdnotify.h \
  $${FRAMEWORK_ROOT_DIR}/server/tcpserver.h \
  $${FRAMEWORK_ROOT_DIR}/server/tcpserverbalancer.h \
  $${FRAMEWORK_ROOT_DIR}/server/tcpsslserver.h \
  $${FRAMEWORK_ROOT_DIR}/server/unixfork.h \
  $${FRAMEWORK_ROOT_DIR}/cmd/helper.h \


#  $${FRAMEWORK_ROOT_DIR}/server/windowsfork.h

SOURCES += \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/authentication.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/authenticationrealm.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/authenticationstore.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/authenticationuser.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/credentialhttp.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/credentialpassword.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/htpasswd.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Authentication/minimal.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/CSRFProtection/csrfprotection.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Memcached/memcached.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/MemcachedSessionStore/memcachedsessionstore.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Session/session.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Session/sessionstorefile.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/StaticCompressed/staticcompressed.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/StaticSimple/staticsimple.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/StatusMessage/statusmessage.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/UserAgent/useragent.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/LangSelect/langselect.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Pagination/pagination.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Sql/sql.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validator.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatoraccepted.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorafter.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatoralpha.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatoralphadash.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatoralphanum.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorbefore.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorbetween.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorboolean.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorcharnotallowed.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorconfirmed.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatordate.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatordatetime.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatordifferent.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatordigits.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatordigitsbetween.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatordomain.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatoremail.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorfilesize.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorfilled.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorin.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorinteger.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorip.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorjson.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatormax.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatormin.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatornotin.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatornumeric.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorpresent.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorpwquality.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorregularexpression.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequired.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredif.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredifstash.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredunless.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredunlessstash.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredwith.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredwithall.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredwithout.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrequiredwithoutall.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorresult.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorrule.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorsame.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorsize.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatortime.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/Utils/Validator/validatorurl.cpp \
\#  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/ClearSilver/clearsilver.cpp \
\#  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Cutelee/csrf.cpp \
\#  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Cutelee/cuteleeview.cpp \
\#  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Cutelee/cutelystcutelee.cpp \
\#  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Cutelee/urifor.cpp \
\#  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Email/viewemail.cpp \
\#  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Email/viewemailtemplate.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Grantlee/csrf.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Grantlee/cutelystgrantlee.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Grantlee/grantleeview.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/Grantlee/urifor.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/Plugins/View/JSON/viewjson.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/action.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/actionchain.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/application.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/async.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/component.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/context.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/controller.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/cookie.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/dispatcher.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/dispatchtype.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/dispatchtypechained.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/dispatchtypepath.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/engine.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/enginerequest.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/headers.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/multipartformdataparser.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/plugin.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/request.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/response.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/stats.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/upload.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/utils.cpp \
  $${FRAMEWORK_ROOT_DIR}/Cutelyst/view.cpp \
  $${FRAMEWORK_ROOT_DIR}/EventLoopEPoll/eventdispatcher_epoll.cpp \
  $${FRAMEWORK_ROOT_DIR}/EventLoopEPoll/eventdispatcher_epoll_p.cpp \
  $${FRAMEWORK_ROOT_DIR}/EventLoopEPoll/socknot_p.cpp \
  $${FRAMEWORK_ROOT_DIR}/EventLoopEPoll/timers_p.cpp \
  $${FRAMEWORK_ROOT_DIR}/server/abstractfork.cpp \
  $${FRAMEWORK_ROOT_DIR}/server/cwsgiengine.cpp \
  $${FRAMEWORK_ROOT_DIR}/server/hpack.cpp \
  $${FRAMEWORK_ROOT_DIR}/server/hpack_p.cpp \
  $${FRAMEWORK_ROOT_DIR}/server/localserver.cpp \
 \#  $${FRAMEWORK_ROOT_DIR}/server/main.cpp \
  $${FRAMEWORK_ROOT_DIR}/server/postunbuffered.cpp \
  $${FRAMEWORK_ROOT_DIR}/server/protocol.cpp \
  $${FRAMEWORK_ROOT_DIR}/server/protocolfastcgi.cpp \
  $${FRAMEWORK_ROOT_DIR}/server/protocolhttp.cpp \
  $${FRAMEWORK_ROOT_DIR}/server/protocolhttp2.cpp \
  $${FRAMEWORK_ROOT_DIR}/server/protocolwebsocket.cpp \
  $${FRAMEWORK_ROOT_DIR}/server/server.cpp \
  $${FRAMEWORK_ROOT_DIR}/server/socket.cpp \
  $${FRAMEWORK_ROOT_DIR}/server/staticmap.cpp \
  $${FRAMEWORK_ROOT_DIR}/server/systemdnotify.cpp \
  $${FRAMEWORK_ROOT_DIR}/server/tcpserver.cpp \
  $${FRAMEWORK_ROOT_DIR}/server/tcpserverbalancer.cpp \
  $${FRAMEWORK_ROOT_DIR}/server/tcpsslserver.cpp \
  $${FRAMEWORK_ROOT_DIR}/server/unixfork.cpp \


SOURCES += \
   $${FRAMEWORK_ROOT_DIR}/cmd/helper.cpp \
   $${FRAMEWORK_ROOT_DIR}/cmd/main.cpp \


QT += sql

LIBS += -lmemcached -lpwquality -lGrantlee_Templates

#  $${FRAMEWORK_ROOT_DIR}/server/windowsfork.cpp
