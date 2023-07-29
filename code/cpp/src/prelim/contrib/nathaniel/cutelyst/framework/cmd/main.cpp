/*
 * SPDX-FileCopyrightText: (C) 2013-2022 Daniel Nicoletti <dantti12@gmail.com>
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <QCoreApplication>
#include <QCommandLineParser>

#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>
#include <QTextStream>

#include <QRegularExpression>
#include <QStringBuilder>
#include <QDir>

#include <server/server.h>

#include <iostream>

#ifdef Q_OS_UNIX
#include <utime.h>
#endif

#include "config.h"
#include "helper.h"

#define OUT_EXISTS  "  exists "
#define OUT_CREATED " created "

bool buildControllerHeader(const QString &filename, const QString &controllerName, bool helpers);
bool buildControllerImplementation(const QString &filename, const QString &controllerName, bool helpers);

bool createController(const QString &controllerName)
{
    if (controllerName.contains(QRegularExpression(QStringLiteral("\\W"))) || controllerName.contains(QRegularExpression(QStringLiteral("^\\d")))) {
        std::cerr << qUtf8Printable(QCoreApplication::translate("cutelystcmd", "Error: Invalid Controller name.")) << std::endl;
        return false;
    }

    QDir projectDir;
    if (!Helper::findProjectDir(QDir::current(), &projectDir)) {
        std::cerr << qUtf8Printable(QCoreApplication::translate("cutelystcmd", "Error: failed to find project")) << std::endl;
        return false;
    }

    if (!buildControllerHeader(projectDir.absoluteFilePath(QStringLiteral("src/")) % controllerName.toLower() % QLatin1String(".h"),
                               controllerName,
                               false)) {
        return false;
    }

    if (!buildControllerImplementation(projectDir.absoluteFilePath(QStringLiteral("src/")) % controllerName.toLower() % QLatin1String(".cpp"),
                                       controllerName,
                                       false)) {
        return false;
    }

#ifdef Q_OS_UNIX
    // Change the modification time of CMakeLists.txt to force FILE_GLOB to be updated
    utime(projectDir.absoluteFilePath(QStringLiteral("CMakeLists.txt")).toLatin1().data(), NULL);
#endif

    std::cout << qUtf8Printable(QCoreApplication::translate("cutelystcmd", "Now, on your application class include and instantiate the controller.")) << std::endl;

    return true;
}

#include <QDebug>

#include "../tsi/global-types.h"

bool build_tsi(const QString &filename, const QString &appName)
{
// QFileInfo qfi(filename);

// QString ap = qfi.absolutePath();
// qDebug() << "p = " << ap;

 QDir qd = QDir::current();
 qDebug() << "qd = " << qd.absolutePath();

 qd.mkpath("tsi"_qt);

 bool ok = qd.cd("tsi"_qt);

#define _STRINGIFY_(arg) #arg
#define _STRINGIFY(arg) _STRINGIFY_(arg)

#define CMAKE_QT_PREFIX QT_CMAKE_FOLDER "/Qt" _STRINGIFY(QT_VERSION_MAJOR)

#define cmake_CUTELYST_PREFIX INSTALL_ROOT_FOLDER "/cmake/Cutelyst3Qt5"


 QString _ROOT_FOLDER = ROOT_FOLDER ""_qt;
 QString _APPS_ROOT_FOLDER = APPS_ROOT_FOLDER ""_qt;
 QString _FRAMEWORK_ROOT_FOLDER = FRAMEWORK_ROOT_FOLDER ""_qt;
 QString _INSTALL_ROOT_FOLDER = INSTALL_ROOT_FOLDER ""_qt;


 while(ok)
 {
  {
// "-- --chdir /home/nlevisrael/gits/cutelyst/apps/%1/tsi/-build_/lib"
   QString run_app_params = "--server --app-file "
     APPS_ROOT_FOLDER "/%1/tsi/-build_/lib/lib%1.so"_qt.arg(filename);
   QString generic_run_params = "${1:-h} ${@:2:$#}"_qt;

   QString text = R"(# shell script to launch cutelyst generators ...
# note: the arguments after the cutelyst invocation will pass the -h
# argument unless this script is called with one or more alternative parameters
#
cd ../%1;
LD_LIBRARY_PATH=%2/lib:\
%3:$LD_LIBRARY_PATH \
%2/bin/cutelyst3-qt5 #=1 ;
cd --
)"_qt.arg(filename).arg(_INSTALL_ROOT_FOLDER).arg(QT_LIBS_FOLDER ""_qt).replace("#="_qt, "%"_qt);

   {
    QFile data(qd.absoluteFilePath("run-cutelyst.sh"_qt));

    if((ok = data.open(QFile::WriteOnly)))
    {
     QTextStream out(&data);
     out << text.arg(generic_run_params);

     data.close();
     data.setPermissions(QFile::ExeOwner | QFile::ReadOwner  | QFile::WriteOwner);
    }
    if(!ok) break;
   }


   {
    QFile data(qd.absoluteFilePath("run-cutelyst-app.sh"_qt));

    if((ok = data.open(QFile::WriteOnly)))
    {
     QTextStream out(&data);
     out << text.arg(run_app_params);

     data.close();
     data.setPermissions(QFile::ExeOwner | QFile::ReadOwner  | QFile::WriteOwner);
    }
    if(!ok) break;
   }
  }

  qd.mkpath("-build_"_qt);
  ok = qd.cd("-build_"_qt);
  if(!ok) break;

  qd.mkpath("lib"_qt);
  ok = qd.exists("lib"_qt);
  if(!ok) break;

  qd.mkpath("qt"_qt);
  ok = qd.cd("qt"_qt);
  if(!ok) break;

  QString fnlc = filename.toLower();

  {
   QFile data(qd.absoluteFilePath(filename + ".pro"_qt));

   if(data.open(QFile::WriteOnly))
   {
    QTextStream out(&data);
    out << R"(

## auto-generated defines:
# INSTALL_ROOT_FOLDER: %1
# APPS_ROOT_FOLDER: %2
# FRAMEWORK_ROOT_FOLDER: %3

INSTALL_ROOT_DIR=%1
APPS_ROOT_DIR=%2
FRAMEWORK_ROOT_DIR=%3

DEFINES += INSTALL_ROOT_FOLDER=\\\"$${INSTALL_ROOT_DIR}\\\"
DEFINES += APPS_ROOT_FOLDER=\\\"$${APPS_ROOT_DIR}\\\"
DEFINES += FRAMEWORK_ROOT_FOLDER=\\\"$${FRAMEWORK_ROOT_DIR}\\\"


##  Paste this into the custom executable to run the server from Qt Creator ...
#  %1/bin/cutelyst3-qt5
#  --server --app-file %2/%3/tsi/-build_/lib/lib%1.so -- --chdir %2/%4/tsi/-build_/lib
#  %6:%1/lib:$LD_LIBRARY_PATH

cmake_step.commands = cd ../run-cmake/working; \
  ../run-cmake.sh; make; ../copy-lib.sh
QMAKE_EXTRA_TARGETS += cmake_step
PRE_TARGETDEPS += cmake_step

INCLUDEPATH += \
  %4 \
  %1/include/cutelyst3-qt5 \

TEMPLATE = lib

SRC_DIR = %2/src

HEADERS += \
  $$SRC_DIR/root.h \
  $$SRC_DIR/src/%5.h \

SOURCES += \
  $$SRC_DIR/src/root.cpp \
  $$SRC_DIR/src/%5.cpp \

LIBS += -L%1/lib \
  -lCutelyst3Qt5 \

          )"_qt.arg(_INSTALL_ROOT_FOLDER).arg(_APPS_ROOT_FOLDER)
  .arg(_FRAMEWORK_ROOT_FOLDER).arg(filename).arg(fnlc).arg(QT_LIBS_FOLDER ""_qt);

    data.close();
   }
  }

  ok = qd.cdUp();
  if(!ok) break;

  qd.mkpath("run-cmake"_qt);
  ok = qd.cd("run-cmake"_qt);
  if(!ok) break;

  qd.mkpath("working"_qt);
  ok = qd.exists("working"_qt);

  {
   QFile data(qd.absoluteFilePath("run-cmake.sh"_qt));

   if((ok = data.open(QFile::WriteOnly)))
   {
    QTextStream out(&data);


    out << R"(
%1 \
 -D CMAKE_BUILD_TYPE=Debug \
 -D CMAKE_C_COMPILER=%2 \
 -D CMAKE_CXX_COMPILER=%3 \
 -D CMAKE_PREFIX_PATH="%4;\
%5" \
  ../../../../%6
           )"_qt.arg(CMAKE_EXE ""_qt).arg(COMPILER_CMD_CC ""_qt).arg(COMPILER_CMD_CXX ""_qt)
  .arg(CMAKE_QT_PREFIX ""_qt).arg(cmake_CUTELYST_PREFIX ""_qt).arg(filename);

    data.close();

    data.setPermissions(QFile::ExeOwner | QFile::ReadOwner  | QFile::WriteOwner);
   }
   if(!ok) break;
  }

  {
   QFile data(qd.absoluteFilePath("copy-lib.sh"_qt));

   if(data.open(QFile::WriteOnly))
   {
    QTextStream out(&data);

    out << R"(
cp ./src/lib%1.so ../../lib  \
           )"_qt.arg(filename);

    data.close();

    data.setPermissions(QFile::ExeOwner | QFile::ReadOwner  | QFile::WriteOwner);
   }
   if(!ok) break;
  }
  return true;
 }

 return false;
}

bool buildApplicationImplementation(const QString &filename, const QString &appName)
{
    QFile data(filename);
    if (data.exists()) {
        std::cerr << OUT_EXISTS << qPrintable(filename) << std::endl;
        return true;
    }

    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        QFileInfo fileInfo(filename);
        out << "#include \"" << fileInfo.baseName() << ".h\"" << "\n";
        out << "\n";
        out << "#include \"root.h\"" << "\n";
        out << "\n";
        out << "using namespace Cutelyst;" << "\n";
        out << "\n";
        out << appName << "::" << appName << "(QObject *parent) : Application(parent)" << "\n";
        out << "{" << "\n";
        out << "}" << "\n";
        out << "\n";
        out << appName << "::~" << appName << "()" << "\n";
        out << "{" << "\n";
        out << "}" << "\n";
        out << "\n";
        out << "bool " << appName << "::init" << "()" << "\n";
        out << "{" << "\n";
        out << "    new Root(this);" << "\n";
        out << "\n";
        out << "    return true;" << "\n";
        out << "}" << "\n";
        out << "\n";

        std::cout << OUT_CREATED << qPrintable(filename) << std::endl;

        return true;
    }
    std::cerr << qUtf8Printable(QCoreApplication::translate("cutelystcmd", "Error: failed to create file")) << qPrintable(filename) << std::endl;

    return false;
}

// // tsi ...
#ifndef HEADER_EXT_STRING
#define HEADER_EXT_STRING "__H"
#endif

bool buildApplicationHeader(const QString &filename, const QString &appName)
{
    QFile data(filename);
    if (data.exists()) {
        std::cout << OUT_EXISTS << qPrintable(filename) << std::endl;
        return true;
    }

    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        out << "#ifndef " << appName.toUpper() << HEADER_EXT_STRING << "\n";
        out << "#define " << appName.toUpper() << HEADER_EXT_STRING << "\n";
        out << "\n";
        out << "#include <Cutelyst/Application>" << "\n";
        out << "\n";
        out << "using namespace Cutelyst;" << "\n";
        out << "\n";
        out << "class " << appName << " : public Application" << "\n";
        out << "{" << "\n";
        out << "    Q_OBJECT" << "\n";
        out << "    CUTELYST_APPLICATION(IID \""<< appName << "\")" << "\n";
        out << "public:" << "\n";
        out << "    Q_INVOKABLE explicit " << appName << "(QObject *parent = nullptr);" << "\n";
        out << "    ~" << appName << "();" << "\n";
        out << "\n";
        out << "    bool init();" << "\n";
        out << "};" << "\n";
        out << "\n";
        out << "#endif //" << appName.toUpper() << HEADER_EXT_STRING << "\n";
        out << "\n";

        std::cout << OUT_CREATED << qPrintable(filename) << std::endl;

        return true;
    }
    std::cerr << qUtf8Printable(QCoreApplication::translate("cutelystcmd", "Error: failed to create file")) << qPrintable(filename) << std::endl;

    return false;
}

bool buildControllerImplementation(const QString &filename, const QString &controllerName, bool helpers)
{
    QFile data(filename);
    if (data.exists()) {
        std::cout << OUT_EXISTS << qPrintable(filename) << std::endl;
        return true;
    }

    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        QFileInfo fileInfo(filename);
        out << "#include \"" << fileInfo.baseName() << ".h\"" << "\n";
        out << "\n";
        out << "using namespace Cutelyst;" << "\n";
        out << "\n";
        out << controllerName << "::" << controllerName << "(QObject *parent) : Controller(parent)" << "\n";
        out << "{" << "\n";
        out << "}" << "\n";
        out << "\n";
        out << controllerName << "::~" << controllerName << "()" << "\n";
        out << "{" << "\n";
        out << "}" << "\n";
        out << "\n";
        out << "void " << controllerName << "::index" << "(Context *c)" << "\n";
        out << "{" << "\n";
        if (helpers) {
            out << "    c->response()->body() = \"Welcome to Cutelyst!\";" << "\n";
        } else {
            out << "    c->response()->body() = \"Matched Controller::" << controllerName << " in " << controllerName << ".\";" << "\n";
        }
        out << "}" << "\n";
        out << "\n";
        if (helpers) {
            out << "void " << controllerName << "::defaultPage" << "(Context *c)" << "\n";
            out << "{" << "\n";
            out << "    c->response()->body() = \"Page not found!\";" << "\n";
            out << "    c->response()->setStatus(404);" << "\n";
            out << "}" << "\n";
            out << "\n";
        }

        std::cout << OUT_CREATED << qPrintable(filename) << std::endl;

        return true;
    }
    std::cerr << qUtf8Printable(QCoreApplication::translate("cutelystcmd", "Error: failed to create file")) << qPrintable(filename) << std::endl;

    return false;
}

bool buildControllerHeader(const QString &filename, const QString &controllerName, bool helpers)
{
    QFile data(filename);
    if (data.exists()) {
        std::cout << OUT_EXISTS << qPrintable(filename) << std::endl;
        return true;
    }

    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        out << "#ifndef " << controllerName.toUpper() << HEADER_EXT_STRING << "\n";
        out << "#define " << controllerName.toUpper() << HEADER_EXT_STRING << "\n";
        out << "\n";
        out << "#include <Cutelyst/Controller>" << "\n";
        out << "\n";
        out << "using namespace Cutelyst;" << "\n";
        out << "\n";
        out << "class " << controllerName << " : public Controller" << "\n";
        out << "{" << "\n";
        out << "    Q_OBJECT" << "\n";
        if (helpers) {
            out << "    C_NAMESPACE(\"\")" << "\n";
        }
        out << "public:" << "\n";
        out << "    explicit " << controllerName << "(QObject *parent = nullptr);" << "\n";
        out << "    ~" << controllerName << "();" << "\n";
        out << "\n";
        out << "    C_ATTR(index, :Path :AutoArgs)" << "\n";
        out << "    void index(Context *c);" << "\n";
        if (helpers) {
            out << "\n";
            out << "    C_ATTR(defaultPage, :Path)" << "\n";
            out << "    void defaultPage(Context *c);" << "\n";
            out << "\n";
            out << "private:\n";
            out << "    C_ATTR(End, :ActionClass(\"RenderView\"))" << "\n";
            out << "    void End(Context *c) { Q_UNUSED(c); }" << "\n";
        }
        out << "};" << "\n";
        out << "\n";
        out << "#endif //" << controllerName.toUpper() << HEADER_EXT_STRING << "\n";
        out << "\n";

        std::cout << OUT_CREATED << qPrintable(filename) << std::endl;

        return true;
    }
    std::cerr << qUtf8Printable(QCoreApplication::translate("cutelystcmd", "Error: failed to create file")) << qPrintable(filename) << std::endl;

    return false;
}

bool buildSrcCMakeLists(const QString &name, const QString &appName)
{
    QFile data(name);
    if (data.exists()) {
        std::cout << OUT_EXISTS << qPrintable(name) << std::endl;
        return true;
    }

    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        out << "file(GLOB_RECURSE " << appName << "_SRCS *.cpp *.h)" << "\n";
        out << "\n";
        out << "set(" << appName << "_SRCS" << "\n";
        out << "    ${" << appName << "_SRCS}" << "\n";
        out << "    ${TEMPLATES_SRC}" << "\n";
        out << ")" << "\n";
        out << "\n";
        out << "# Create the application" << "\n";
        out << "add_library(" << appName << " SHARED ${" << appName << "_SRCS})" << "\n";
        out << "\n";
        out << "# Link to Cutelyst" << "\n";
        out << "target_link_libraries(" << appName << "\n";
        out << "    Cutelyst::Core" << "\n";
        out << "    Qt5::Core" << "\n";
        out << "    Qt5::Network" << "\n";
        out << ")" << "\n";

//        target_include_directories(dtHello PRIVATE "../../../../cutelyst")
        out << "\n";

        std::cout << OUT_CREATED << qPrintable(name) << std::endl;

        return true;
    }
    std::cerr << qUtf8Printable(QCoreApplication::translate("cutelystcmd", "Error: failed to create file")) << qPrintable(name) << std::endl;

    return false;
}

bool buildProjectCMakeLists(const QString &name, const QString &appName)
{
    QFile data(name);
    if (data.exists()) {
        std::cout << OUT_EXISTS << qPrintable(name) << std::endl;
        return true;
    }

    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        out << "project(" <<  appName << ")" << "\n";
        out << "\n";
        out << "cmake_minimum_required(VERSION 3.16 FATAL_ERROR)" << "\n";
        out << "\n";
        out << "if(WIN32)\n";
        out << "  if(MSVC)\n";
        out << "    add_definitions(-D_SCL_SECURE_NO_WARNINGS)\n";
        out << "    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)\n";
        out << "  endif()\n";
        out << "endif()\n\n";
        out << "find_package(Qt" << QT_VERSION_MAJOR << " COMPONENTS Core Network REQUIRED)" << "\n";
        out << "find_package(Cutelyst" << CUTELYST_VERSION_MAJOR << "Qt" << QT_VERSION_MAJOR << " REQUIRED)" << "\n";
        out << "\n";
        out << "# Auto generate moc files" << "\n";
        out << "set(CMAKE_AUTOMOC ON)" << "\n";
        out << "\n";
        out << "# As moc files are generated in the binary dir, tell CMake" << "\n";
        out << "# to always look for includes there:" << "\n";
        out << "set(CMAKE_INCLUDE_CURRENT_DIR ON)" << "\n";
        out << "\n";
        out << "file(GLOB_RECURSE TEMPLATES_SRC root/*)" << "\n";
        out << "\n";
        out << "add_subdirectory(src)" << "\n";

        std::cout << OUT_CREATED << qPrintable(name) << std::endl;

        return true;
    }
    std::cerr << qUtf8Printable(QCoreApplication::translate("cutelystcmd", "Error: failed to create file")) << qPrintable(name) << std::endl;

    return false;
}

bool createDir(const QDir &parentDir, const QString &name)
{
    const QString newDir = parentDir.relativeFilePath(name);
    if (parentDir.exists(name)) {
        std::cout << OUT_EXISTS << qPrintable(newDir) << std::endl;
        return true;
    } else if (parentDir.mkdir(name)) {
        std::cout << OUT_CREATED << qPrintable(newDir) << std::endl;
        return true;
    }

    std::cerr << qUtf8Printable(QCoreApplication::translate("cutelystcmd", "Error: failed to create directory:")) << qPrintable(newDir) << std::endl;
    return false;
}

bool createApplication(const QString &name)
{
    QString nameWithUnderscore = name;
    nameWithUnderscore.replace(u'-', u'_');
    if (nameWithUnderscore.contains(QRegularExpression(QStringLiteral("\\W"))) || nameWithUnderscore.contains(QRegularExpression(QStringLiteral("^\\d")))) {
        std::cerr << qUtf8Printable(QCoreApplication::translate("cutelystcmd", "Error: Invalid Application name.")) << std::endl;
        return false;
    }

    const QDir currentDir = QDir::current();

    if (!createDir(currentDir, name)) {
        return false;
    }

    if (!buildProjectCMakeLists(name % QStringLiteral("/CMakeLists.txt"), nameWithUnderscore)) {
        return false;
    }

    if (!createDir(currentDir, name % QStringLiteral("/build"))) {
        return false;
    }

    if (!createDir(currentDir, name % QStringLiteral("/root"))) {
        return false;
    }

    if (!createDir(currentDir, name % QLatin1String("/src"))) {
        return false;
    }

    if (!buildSrcCMakeLists(name % QLatin1String("/src/CMakeLists.txt"), nameWithUnderscore)) {
        return false;
    }

    if (!buildControllerHeader(name % QLatin1String("/src/root.h"),
                               QStringLiteral("Root"),
                               true)) {
        return false;
    }

    if (!buildControllerImplementation(name % QLatin1String("/src/root.cpp"),
                                       QStringLiteral("Root"),
                                       true)) {
        return false;
    }

    if (!buildApplicationHeader(name % QLatin1String("/src/") % name.toLower() % QLatin1String(".h"),
                                nameWithUnderscore)) {
        return false;
    }

    if (!buildApplicationImplementation(name % QLatin1String("/src/") % name.toLower() % QLatin1String(".cpp"),
                                        nameWithUnderscore)) {
        return false;
    }

    // // tsi ...
    if(!build_tsi(name, nameWithUnderscore))
      return false;


    std::cout << qUtf8Printable(QCoreApplication::translate("cutelystcmd", "Change to application directory, then build directory and Run \"cmake ..\" to make sure your install is complete")) << std::endl;

    return true;
}

#include "../tsi/global-types.h"


int main(int argc, char *argv[])
{
    QByteArray logging = qgetenv("QT_LOGGING_RULES");
    if (!logging.isEmpty()) {
        logging.append(';');
    }
    logging.append("cutelyst.*=true");
    qputenv("QT_LOGGING_RULES", logging);

    QCoreApplication app(argc, argv);
    QCoreApplication::setOrganizationName(QStringLiteral("Cutelyst"));
    QCoreApplication::setOrganizationDomain(QStringLiteral("cutelyst.org"));
    QCoreApplication::setApplicationName(QStringLiteral("cutelyst"));
    QCoreApplication::setApplicationVersion(QStringLiteral(VERSION));

    QTranslator qtTranslator;
    bool loadedTr = qtTranslator.load(QLatin1String("qt_") % QLocale::system().name(),
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
                                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
#else
                                      QLibraryInfo::path(QLibraryInfo::TranslationsPath));
#endif
    if (!loadedTr) {
        std::cerr << qUtf8Printable(QCoreApplication::translate("cutelystcmd", "Error: could not load translations")) << std::endl;
    }

    QCoreApplication::installTranslator(&qtTranslator);

    QTranslator appTranslator;
    if (appTranslator.load(QLocale(), QStringLiteral("cutelystcmd"), QStringLiteral("."), QStringLiteral(I18NDIR))) {
        QCoreApplication::installTranslator(&appTranslator);
    }

    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::translate("cutelystcmd", "Cutelyst DEVELOPER helper, it can create a skeleton for a new application, controllers and start your application"));
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption appName(QStringLiteral("create-app"),
                               QCoreApplication::translate("cutelystcmd", "Creates a new Cutelyst application"),
                               QStringLiteral("app_name"));
    parser.addOption(appName);

    QCommandLineOption controller(QStringLiteral("controller"),
                                  QCoreApplication::translate("cutelystcmd", "Name of the Controller application to create"),
                                  QStringLiteral("controller_name"));

    parser.addOption(controller);

    QCommandLineOption server(QStringLiteral("server"),
                              QCoreApplication::translate("cutelystcmd", "Starts a HTTP server"));
    parser.addOption(server);

    QCommandLineOption appFile(QStringLiteral("app-file"),
                               QCoreApplication::translate("cutelystcmd", "Application file of to use with the server (usually in build/src/lib*.so), if not set it will try to auto-detect"),
                               QStringLiteral("file_name"));
    parser.addOption(appFile);

    QCommandLineOption serverPort({ QStringLiteral("server-port"), QStringLiteral("p") },
                                  QCoreApplication::translate("cutelystcmd", "Development server port"),
                                  QStringLiteral("port"));
    parser.addOption(serverPort);

    QCommandLineOption restartOpt({ QStringLiteral("restart"), QStringLiteral("r") },
                                  QCoreApplication::translate("cutelystcmd", "Restarts the development server when the application file changes"));
    parser.addOption(restartOpt);

    //const
    QStringList arguments = app.arguments();

    // //  tsi ...
    if(arguments.size() == 1)
      arguments.append({"--create-app"_qt, QDir::current().dirName()});


    QStringList argsBeforeDashDash;
    QStringList argsAfterDashDash = arguments.mid(0, 1);

    int pos = arguments.indexOf(QStringLiteral("--"));
    if (pos != -1) {
        argsBeforeDashDash = arguments.mid(0, pos);
        argsAfterDashDash.append(arguments.mid(pos + 1));
    } else {
        argsBeforeDashDash = arguments;
    }

    // Process the actual command line arguments given by the user
    parser.process(argsBeforeDashDash);

    if (parser.isSet(appName)) {
        QString name = parser.value(appName);
        if (!createApplication(name)) {
            parser.showHelp(2);
        }
    } else if (parser.isSet(controller)) {
        QString name = parser.value(controller);
        if (!createController(name)) {
            parser.showHelp(3);
        }
    } else if (parser.isSet(server)) {
     int port = 20199; //  TSI
//?        int port = 3000;
        if (parser.isSet(serverPort)) {
            port = parser.value(serverPort).toInt();
        }

        Cutelyst::Server server;

        server.parseCommandLine(argsAfterDashDash);

        server.setHttpSocket({ QLatin1Char(':') + QString::number(port) });

        bool restart = parser.isSet(restartOpt);
        server.setMaster(restart);
        server.setAutoReload(restart);
        server.setLazy(restart);

        QDir projectDir;
        bool hasProjectDir = Helper::findProjectDir(QDir::current(), &projectDir);
        if (!hasProjectDir) {
            std::cerr << qUtf8Printable(QCoreApplication::translate("cutelystcmd", "Error: failed to find project")) << std::endl;
        } else {
            server.setChdir2(projectDir.absolutePath());
        }

        QString localFilename = parser.value(appFile);
        if (localFilename.isEmpty()) {
            if (!hasProjectDir) {
                return 1;
            }
            localFilename = Helper::findApplication(projectDir);
            if (!QFile::exists(localFilename)) {
                std::cerr << qUtf8Printable(QCoreApplication::translate("cutelystcmd", "Error: Application file not found")) << std::endl;
                return 1;
            }
        }
        server.setApplication(localFilename);

        return server.exec();
    } else {
        parser.showHelp(1);
    }

    return 0;
}
