

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "chvm-code-statement.h"


USING_AQNS(Chasm_TR)


ChVM_Code_Statement::ChVM_Code_Statement()
  :  channel_package_(nullptr)
{

}

QString ChVM_Code_Statement::lines_to_chvm()
{
 return code_lines_.toList().join("");
}

