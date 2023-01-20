
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RELAE_PARSER__H
#define RELAE_PARSER__H

#include "flags.h"

#include "relae-regex.h"

#include "relae-node-ptr.h"


struct RZ_Match_Data_Base;

template<typename GALAXY>
class Relae_Parser
{
 typedef RZ_Core_Rule tRule;

 struct Match_Info
 {
  RZ_Match_Data_Base* data;
  RZ_Core_Rule* rule;
  Match_Info(RZ_Match_Data_Base* d = nullptr, RZ_Core_Rule* r = nullptr)
   : data(d),rule(r){}
 };

 typedef typename GALAXY::Graph_type tGraph;
 RZ_Match_Data_Base* match_;

 tString eval_string_;
 tString seek_string_;

 int current_position_;

 caon_ptr<tGraph> graph_;

 QVector<Match_Info> saved_matches_;

 tRule* rule_;
 Match_Info last_match_;
 void* cancel_info_;
 void* end_of_file_info_;

public:

 ACCESSORS(caon_ptr<tGraph> ,graph)
 ACCESSORS(void* ,end_of_file_info)

 Relae_Parser(caon_ptr<tGraph> g):graph_(g),match_(nullptr),
   cancel_info_(nullptr), end_of_file_info_(nullptr), current_position_(0)
 {

 }

 void set_eval_text(tString s)
 {
  eval_string_ = s;
 }

 bool check_seek(tString& s);
 void write_data_text(tString& s);
 void enter_comment_mode();
 void load_file(tString path);
 void set_match(RZ_Match_Data_Base* m, tRule* r, int pos);
 void delete_last_match();
 void delete_match(RZ_Match_Data_Base* m);
 void cancel_match(void* details);
 void cancel_match();
 void* reset_cancel();
 void end_of_file(void* pVoid);
 tString matched(int capture_number);
 tString matched(tString capture_name);
 tString match_text();
};

#endif //RELAE_PARSER__H
