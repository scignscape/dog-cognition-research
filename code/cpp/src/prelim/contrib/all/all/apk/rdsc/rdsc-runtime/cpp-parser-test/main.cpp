


#include "cpp-parser/pub/cppparser.h"

#include <QDebug>

int main()
{
  CppParser  parser;

  parser.set_qj_callback([](QString content, QString rest_of_line, int i)
  {
   qDebug() << content << " + " << rest_of_line << " i = " << i;
  });


  //const std::string testFilePath = "/quasihome/nlevisrael/cpp/test/main.cpp";

  const std::string testFilePath = "/home/nlevisrael/gits/dcr-wip/ar/code/cpp/src/prelim/contrib/all/all/apk/rdsc/rdsc-web-engine/rdsc-qh-demo/game/game-token.h";
  const auto ast          = parser.parseFile(testFilePath);

  const auto& members = ast->members();

  CppIncludeEPtr hashInclude = members[0];

  CppFunctionEPtr func = members[1];
  const auto& mainBodyMembers = func->defn()->members();

  CppExprEPtr coutHelloWorld = mainBodyMembers[0];

  return 0;
}

