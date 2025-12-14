
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef CHTR_NODE_FACTORY__H
#define CHTR_NODE_FACTORY__H

#include "relae-graph/relae-parser.h"


#include "global-types.h"


#include "aqns.h"
AQNS_(Chasm_TR)

class ChTR_Node;

class ChTR_Source_Token;
class ChTR_Type_Object;


class ChTR_Node_Factory
{
 //QString raw_text_;

 u2 call_entry_count_;
 u2 block_entry_count_;
 u2 tuple_entry_count_;


 ChTR_Node_Factory();

public:

#define ACCESSORS__MAKE_ID(ty ,x) \
 ty make_##x##_id() { return ++x##_count_; }


 ACCESSORS__MAKE_ID(u2 ,call_entry)
 ACCESSORS__MAKE_ID(u2 ,block_entry)
 ACCESSORS__MAKE_ID(u2 ,tuple_entry)


 //ACCESSORS(QString ,raw_text)

 static ChTR_Node_Factory& instance()
 {
  ChTR_Node_Factory* the_instance = new ChTR_Node_Factory;
  return *the_instance;
 }


 caon_ptr<ChTR_Node> make_new_node(caon_ptr<ChTR_Source_Token> token) const;
 caon_ptr<ChTR_Node> make_new_node(caon_ptr<ChTR_Type_Object> cto) const;

// caon_ptr<ChTR_Node> make_new_node(caon_ptr<RZ_Block_Level_Type_Declaration> blt) const;
// caon_ptr<ChTR_Node> make_new_node(caon_ptr<ChasmRZ_Casement_Call_Entry> rce) const;
// caon_ptr<ChTR_Node> make_new_node(caon_ptr<ChasmRZ_Call_Entry> rce) const;
// caon_ptr<ChTR_Node> make_new_node(caon_ptr<ChasmRZ_Casement_Block_Entry> rbe) const;
// caon_ptr<ChTR_Node> make_new_node(caon_ptr<ChasmRZ_Block_Entry> rbe) const;
// caon_ptr<ChTR_Node> make_new_node(caon_ptr<ChasmRZ_Function_Def_Entry> fdef) const;
// caon_ptr<ChTR_Node> make_new_node(caon_ptr<RZ_String_Plex_Builder> rzspb) const;
// caon_ptr<ChTR_Node> make_new_node(caon_ptr<ChasmRZ_Anchored_Casement_Entry> ace) const;
// caon_ptr<ChTR_Node> make_new_node(caon_ptr<RZ_Observer_Function> rcf) const;

// caon_ptr<ChTR_Node> make_new_node(caon_ptr<RZ_ASG_Token> rat, QString label) const;



};

_AQNS(Chasm_TR)

#endif //CHTR_NODE_FACTORY__H
