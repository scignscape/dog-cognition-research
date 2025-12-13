
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#define DOMINION_NODE_TYPE ChTR_Node

#ifndef DOMINION_HIDE_NO_NAMESPACE
// // No namespace
#include "relae-graph/dominion-macros.h"
DOMINION_TYPE(dbl, double, Double)
DOMINION_TYPE(integer, int, Int)
DOMINION_TYPE(i8, char, I8)
DOMINION_TYPE(qstring, QString, QStr)
DOMINION_TYPE(phhn, phaong<pg_t>::Hypernode, Phaong_Hypernode)
#endif

//?#include "relae-graph/dominion-macros.h"

#define DOMINION_OUTER_NAMESPACE Aq



//#define DOMINION_INNER_NAMESPACE Qh
//#include "relae-graph/dominion-macros.h"
//DOMINION_TYPE(qh_root, Qh_Root, Qh_Root)
//DOMINION_TYPE(qh_token, Qh_Token, Qh_Token)
//DOMINION_TYPE(qh_node_base, Qh_Node_Base, Qh_Node_Base)

//?#undef DOMINION_INNER_NAMESPACE

#define DOMINION_INNER_NAMESPACE Chasm_TR
#include "relae-graph/dominion-macros.h"

DOMINION_TYPE(channel_object, ChTR_Channel_Object, Channel_Object)
DOMINION_TYPE(source_file, ChTR_Source_File, Source_File)
DOMINION_TYPE(code_statement, ChTR_Code_Statement, Code_Statement)



//#define DOMINION_INNER_NAMESPACE GBuild
//#include "relae-graph/dominion-macros.h"
////?
//DOMINION_TYPE(core_function, SE_Lisp_Graph_Core_Function, Graph_CoreFun)
//DOMINION_TYPE(cfn, SY_Lisp_Core_Function, Token_CoreFun)
//DOMINION_TYPE(null_value, SE_Null_Value, Null_Value)
////DOMINION_TYPE(cfn, RZ_Lisp_Core_Function, CoreFun)
//DOMINION_TYPE(empty_tuple, SE_Lisp_Empty_Tuple, EmptyTuple)
//#undef DOMINION_INNER_NAMESPACE

//#define DOMINION_INNER_NAMESPACE GVal
//#include "relae-graph/dominion-macros.h"
//DOMINION_TYPE(opc, SE_Opaque_Call, Opc)
//DOMINION_TYPE(ops, SE_Opaque_Symbol, Ops)
//DOMINION_TYPE(ots, SE_Opaque_Type_Symbol, Ots)
//DOMINION_TYPE(block_info, SE_Lisp_Graph_Block_Info, Block_Info)
//DOMINION_TYPE(rz_function_def_info, SE_Function_Def_Info, SE_Function_Def_Info)
//#undef DOMINION_INNER_NAMESPACE

#undef DOMINION_OUTER_NAMESPACE
#undef DOMINION_NODE_TYPE
