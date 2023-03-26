


#include "cpp-parser/pub/cppparser.h"

#include <QDebug>

int main()
{
  CppParser  parser;

  parser.set_qj_callback([](int i)
  {
   qDebug() << "i = " << i;
  });

  const std::string testFilePath = "/quasihome/nlevisrael/cpp/test/main.cpp";
  const auto ast          = parser.parseFile(testFilePath);

  const auto& members = ast->members();

  CppIncludeEPtr hashInclude = members[0];

  CppFunctionEPtr func = members[1];
  const auto& mainBodyMembers = func->defn()->members();

  CppExprEPtr coutHelloWorld = mainBodyMembers[0];

  return 0;
}

