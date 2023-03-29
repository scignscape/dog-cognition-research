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

/**
 * @file Internal interface for lexer and parser APIs.
 */

#pragma once

#include <functional>

#include "cppast.h"

#include "qh/qj-callback.h"

class Qh_Context;

using ErrorHandler =
  std::function<void(const char* errLineText, size_t lineNum, size_t errorStartPos, int lexerContext)>;

//using Qj_Callback = std::function<void(int)>;

void set_qj_callback(Qj_Callback qjc);
Qh_Context& qh_context();

void setErrorHandler(ErrorHandler errorHandler);
void resetErrorHandler();

CppCompoundPtr parseStream(char* stm, size_t stmSize);
