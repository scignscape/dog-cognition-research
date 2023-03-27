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

#include "cppobjfactory.h"

CppCompound* CppObjFactory::CreateCompound(std::string name, CppAccessType accessType, CppCompoundType type) const
{
  return new CppCompound(std::move(name), accessType, type);
}

CppCompound* CppObjFactory::CreateCompound(CppAccessType accessType, CppCompoundType type) const
{
  return new CppCompound(accessType, type);
}

CppCompound* CppObjFactory::CreateCompound(std::string name, CppCompoundType type) const
{
  return new CppCompound(std::move(name), type);
}

CppCompound* CppObjFactory::CreateCompound(CppCompoundType type) const
{
  return new CppCompound(type);
}

CppConstructor* CppObjFactory::CreateConstructor(CppAccessType   accessType,
                                                 std::string     name,
                                                 CppParamVector* params,
                                                 CppMemInits     memInits,
                                                 unsigned int    attr) const
{
  return new CppConstructor(accessType, std::move(name), params, memInits, attr);
}

CppDestructor* CppObjFactory::CreateDestructor(CppAccessType accessType, std::string name, unsigned int attr) const
{
  return new CppDestructor(accessType, name, attr);
}

CppFunction* CppObjFactory::CreateFunction(CppAccessType   accessType,
                                           std::string     name,
                                           CppVarType*     retType,
                                           CppParamVector* params,
                                           unsigned int    attr) const
{
  return new CppFunction(accessType, std::move(name), retType, params, attr);
}

CppTypeConverter* CppObjFactory::CreateTypeConverter(CppVarType* type, std::string name) const
{
  return new CppTypeConverter(type, std::move(name));
}
