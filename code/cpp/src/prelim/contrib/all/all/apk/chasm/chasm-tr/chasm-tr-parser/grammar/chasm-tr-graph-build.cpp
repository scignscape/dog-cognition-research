
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chasm-tr-graph-build.h"

#include "kernel/frame/chasm-tr-frame.h"

#include "kernel/graph/chasm-tr-graph.h"

#include "chasm-tr-source-type.h"

#include "chasm-tr-source-file.h"

#include <QMap>

#include "global-types.h"

USING_AQNS(ChasmTR)


Chasm_TR_Graph_Build::Chasm_TR_Graph_Build(Chasm_TR_Document* d, Chasm_TR_Parser& p, Chasm_TR_Graph& g)
 : Flags(0)
   ,document_(d)
   ,graph_(g)
   ,parser_(p)
   ,fr_(Chasm_TR_Frame::instance())
   ,held_line_number_(0)
   ,current_context_code_(0)
   ,current_source_type_(nullptr)
{
 current_source_file_ = new Chasm_TR_Source_File;
}

void Chasm_TR_Graph_Build::init()
{

}


void Chasm_TR_Graph_Build::hold_line_number(u2 line_number)
{
 held_line_number_ = line_number;
}


void Chasm_TR_Graph_Build::enter_qj_context(u2 line_number, QString context_name)
{
 static QMap<QString, u1> static_map {
   {"enum:def", qj_enum_def},
   {"enum:ops", qj_enum_ops},
   {"enum:str", qj_enum_str},
   {"accessors", qj_accessors}
  };

 u1 code = static_map.value(context_name);

 switch(code)
 {
 case 0: break;

 case qj_enum_def: parse_context_.flags.enum_def = true; break;
 case qj_enum_ops: parse_context_.flags.enum_ops = true; break;
 case qj_enum_str: parse_context_.flags.enum_str = true; break;
 case qj_accessors: parse_context_.flags.accessors = true; break;

 }

 if(code)
   current_context_code_ = code;
}


void Chasm_TR_Graph_Build::note_enum_def(QString label, QString value)
{
 //Chasm_TR_Source_Type* sty = new Chasm_TR_Source_Type;
 if(!current_source_type_)
   current_source_type_ = new Chasm_TR_Source_Type;

 current_source_type_->note_enum_field(label, value);

}


void Chasm_TR_Graph_Build::leave_qj_context(u2 line_number, QString s)
{
 switch(current_context_code_)
 {
 case 0: break;

 case qj_enum_def:
  parse_context_.flags.enum_def = false;
  current_source_file_->add_source_type(current_source_type_);
  current_source_type_ = nullptr;
  break;

 case qj_enum_ops: parse_context_.flags.enum_ops = false; break;
 case qj_enum_str: parse_context_.flags.enum_str = false; break;
 case qj_accessors: parse_context_.flags.accessors = false; break;

 }

}
