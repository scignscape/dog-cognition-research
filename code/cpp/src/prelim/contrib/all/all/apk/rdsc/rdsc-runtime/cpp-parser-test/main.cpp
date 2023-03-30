


#include "cpp-parser/pub/cppparser.h"

#include "cpp-parser/src/qh/qh-context.h"

#include <QDebug>

#include <QLibrary>

int main()
{
 QString path = "/home/nlevisrael/gits/dcr-wip/ar/code/cpp/targets/contrib/all/all/qt/qt-multiple/nomark/targets-5-15-2-Desktop_Qt_5_15_2_GCC_64bit/librdsc-qh-demo.so.1.0.0";
 QLibrary myLib(path, QLibrary::ResolveAllSymbolsHint);

 typedef void (*MyPrototype)();

 MyPrototype myFunction = (MyPrototype) myLib.resolve("test_game");
 if (myFunction)
     myFunction();

 return 0;
}


int main1()
{
  CppParser  parser;

  Qh_Context& qh_context = parser.qh_context();
  qh_context.set_output_file(ROOT_FOLDER "/../qh/test.qh");

  parser.set_qj_callback([](QString content, QString rest_of_line, int i)
  {
   qDebug() << content << " + " << rest_of_line << " i = " << i;
  });


  //const std::string testFilePath = "/quasihome/nlevisrael/cpp/test/main.cpp";

  const std::string testFilePath = "/home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/all/all/apk/rdsc/rdsc-web-engine/rdsc-qh-demo/game/game-token.h";
  const auto ast          = parser.parseFile(testFilePath);

  const auto& members = ast->members();
  qh_context.save_output();

//  CppIncludeEPtr hashInclude = members[0];

//  CppFunctionEPtr func = members[1];
//  const auto& mainBodyMembers = func->defn()->members();

//  CppExprEPtr coutHelloWorld = mainBodyMembers[0];

  return 0;
}

