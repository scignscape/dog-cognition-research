
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RELAE_PARSER__TEMPLATES__H
#define RELAE_PARSER__TEMPLATES__H

#include "relae-parser.h"

#include <QFile>

template<typename GALAXY>
bool Relae_Parser<GALAXY>::check_seek(tString& s)
{
 if(seek_string_ == "")
  return false;
 else
 {
  s = seek_string_;
  seek_string_ = "";
  return true;
 }
}

template<typename GALAXY>
void Relae_Parser<GALAXY>::write_data_text(tString& s)
{
 int i;
 match_->reset_position(i);
 s = eval_string_.mid(i);
}

template<typename GALAXY>
void Relae_Parser<GALAXY>::load_file(tString path)
{
 QFile file(path);

 if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  return;

 graph_->source_file = path;

 QTextStream in(&file);
 while (!in.atEnd())
 {
  eval_string_ += in.readLine() + " \n";
 }

}

template<typename GALAXY>
void Relae_Parser<GALAXY>::set_match(RZ_Match_Data_Base* m, tRule* r, int pos)
{
#ifdef NO_CAON
#else //NO_CAON
 delete_last_match();
#endif //NO_CAON
 last_match_ = Match_Info(match_, rule_);
 match_ = m;
 #ifdef NO_CAON
 rule_ = r;
 #else
 rule_ = r;
 #endif
 current_position_ = pos;
}

template<typename GALAXY>
void Relae_Parser<GALAXY>::delete_last_match()
{
 delete_match(last_match_.data);
}


template<typename GALAXY>
void Relae_Parser<GALAXY>::delete_match(RZ_Match_Data_Base* m)
{
 if(m)
  m->clean_up();
 m = 0;
 delete m;
}

template<typename GALAXY>
void Relae_Parser<GALAXY>::cancel_match(void* details)
{
 cancel_info_ = details;
}

template<typename GALAXY>
void Relae_Parser<GALAXY>::cancel_match()
{
 cancel_info_ = this;
}

template<typename GALAXY>
void Relae_Parser<GALAXY>::end_of_file(void* pVoid)
{
 end_of_file_info_ = pVoid;
}

template<typename GALAXY>
void* Relae_Parser<GALAXY>::reset_cancel()
{
 void* result = cancel_info_;
 cancel_info_ = nullptr;
 return result;
}

template<typename GALAXY>
tString Relae_Parser<GALAXY>::matched(int capture_number)
{
 if(match_)
 {
  RZ_Match_Data_Qt* m = (RZ_Match_Data_Qt*) match_;
  return match_->text(capture_number);
 }
 return "";
}

template<typename GALAXY>
tString Relae_Parser<GALAXY>::matched(tString capture_name)
{
 if(match_)
 {
  return match_->text(capture_name);
 }
 return "";
}


template<typename GALAXY>
tString Relae_Parser<GALAXY>::match_text()
{
 if(match_)
 {
  return match_->text();
 }
 return "";
}

#endif //RELAE_PARSER__TEMPLATES__H
