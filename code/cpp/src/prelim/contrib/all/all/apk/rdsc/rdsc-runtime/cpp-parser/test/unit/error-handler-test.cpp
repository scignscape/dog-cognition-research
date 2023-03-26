/*
   The MIT License (MIT)

   Copyright (c) 2018 Satya Das

   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
   the Software, and to permit persons to whom the Software is furnished to do so,
   subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
   FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
   COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <catch/catch.hpp>

#include "cppparser.h"

#include "embedded-snippet-test-base.h"

#include <string>

class ErrorHandlerTest : public EmbeddedSnippetTestBase
{
protected:
  ErrorHandlerTest()
    : EmbeddedSnippetTestBase(__FILE__)
  {
  }
};

TEST_CASE_METHOD(ErrorHandlerTest, "Error line and column")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
#  if EVADE_COMPILER
  callFunc(x, y, ); // Error should be reported for the position of ')'
#  endif
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  bool                    errHandlerCalled = false;
  CppParser::ErrorHandler errHandler =
    [&errHandlerCalled](const char* errLineText, size_t lineNum, size_t errorStartPos, int lexerContext) {
      errHandlerCalled = true;
      CHECK(errLineText != nullptr);
      CHECK(lineNum == 2);
      CHECK(errorStartPos == 17);
    };
  CppParser parser;
  parser.setErrorHandler(errHandler);
  const bool exceptionThrown = [&]() {
    try
    {
      parser.parseStream(testSnippet.data(), testSnippet.size());
      // FAIL();
    }
    catch (const std::exception& e)
    {
      return true;
    }

    return false;
  }();

  CHECK(errHandlerCalled);
  // CHECK(exceptionThrown);
  (void) exceptionThrown;
}
