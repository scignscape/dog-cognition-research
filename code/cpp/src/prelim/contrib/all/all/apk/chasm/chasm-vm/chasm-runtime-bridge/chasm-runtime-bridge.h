
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_RUNTIME_BRIDGE__H
#define CHASM_RUNTIME_BRIDGE__H

#include <QString>

#include <QStack>
#include <QVariant>
#include <QQueue>
#include <deque>

#include <QDebug>

//?#include "chasm/chasm-carrier.h"

//?#include "chasm-tr/chasm-tr/chtr-carrier.h"

#include "accessors.h"
#include "flags.h"

#include "global-types.h"
#include "kans.h"

#include "chasm-lib/chasm/chasm-runtime.h"
#include "chasm-lib/chasm/chasm-carrier.h"

//#define register_s0(proc ,code) register_procedure_s0(#proc, (void(*)()) &proc, #code)
//#define register_s1(proc ,code) register_procedure_s1(#proc, (void(_min_::*)()) &proc, #code)

#include "chasm-procedure-table/chasm-procedure-table.h"

class Chasm_Call_Package;
class Chasm_Type_Object;
class CSM_Ghost_Scope;

class CHVM_Lexical_Scope;


//typedef void(*_minimal_fn_s0_type)();
//typedef void(_min_::*_minimal_fn_s1_type)();
//union _minimal_fn_type { _minimal_fn_s0_type s0; _minimal_fn_s1_type s1; };

class Chasm_Runtime_Bridge
{
 Chasm_Runtime* csr_;
 Chasm_Call_Package* current_call_package_;
 Chasm_Type_Object* current_type_object_;


 Chasm_Type_Object* type_object_ref_;
 Chasm_Type_Object* type_object_u1_;
 Chasm_Type_Object* type_object_u2_;
 Chasm_Type_Object* type_object_QString_;
 Chasm_Type_Object* type_object_u4_;
 Chasm_Type_Object* type_object_QByteArray_;
 Chasm_Type_Object* type_object_r8_;
 Chasm_Type_Object* type_object_QVariant_;
 Chasm_Type_Object* type_object_n8_;
 Chasm_Type_Object* type_object_ptr_;

 QVector<QStringList> current_pins_;
 QString* current_value_literal_position_;

 QStack<std::deque<Chasm_Carrier>*> carrier_stacks_;

 std::deque<Chasm_Carrier>* current_carrier_deque_;

 n8 current_loaded_raw_value_;

 CSM_Ghost_Scope* current_ghost_scope_;
 QStack<CSM_Ghost_Scope*> active_ghost_scopes_;

 CHVM_Lexical_Scope* current_lexical_scope_;

 Chasm_Procedure_Table* proctable_;

 u4 current_source_file_index_;
 u4 current_statement_line_number_;

 QMap<QString, u4> interned_symbols_;
 u4 max_interned_symbol_;

 u4 interned(QString sym)
 {
  auto it = interned_symbols_.find(sym);
  if(it == interned_symbols_.end())
  {
   interned_symbols_.insert(sym, ++max_interned_symbol_);
   return max_interned_symbol_;
  }
  return *it;
 }


 void infer_unsigned_type()
 {
  // // find least type for the number
  if(current_loaded_raw_value_ <= 0xFF)
    load_type_u1();
  else if(current_loaded_raw_value_ <= 0xFFFF)
    load_type_u2();
  else if(current_loaded_raw_value_ <= 0xFFFFFFFF)
    load_type_u4();
  else
    load_type_n8();
 }

 void infer_signed_type()
 {
  // //  must load type explicitly for signed integers greater than 4 bytes
  s4 rv = current_loaded_raw_value_;
  if(rv < 0)
  {
   rv = -rv;
   if(rv <= 0x80)
     load_type_u1();
   else if(rv <= 0x8000)
     load_type_u2();
   else
     load_type_u4();
  }
  else if(rv <= 0x7F)
    load_type_u1();
  else if(rv <= 0x7FFF)
    load_type_u2();
  else
    load_type_u4();
 }


 void load_symbol_u_(QString literal, u1 radix);
 void load_symbol_s_(QString literal, u1 radix);

 QStack<QString> held_procnames_;

 QStringList channel_handoff_keys_;

 QMap<QString, QVector<Chasm_Carrier>> held_handoff_carriers_;

public:

 ACCESSORS(Chasm_Procedure_Table* ,proctable)

 Chasm_Runtime_Bridge(Chasm_Runtime* csr);

 static u4 truncate_u(u4 value, u1 byte_span);
 static s4 truncate_s(s4 value, u1 byte_span);

 Chasm_Carrier last_carrier();

 void resolve_pins();
 void load_value_literal(QString token);
 void resolve_value_literal(QStringList& qsl);

 void load_unsigned_literal_int(QString token);

 void new_call_package(); //Chasm_Call_Package*

 void add_new_channel(QString name);

 void init_source_file_lexical_scope();
 void declare_lexical_typed_symbol(QString symbol);

 void init_new_ghost_scope();
 void single_init_pin(QString symbol);

 void check_claims(const Chasm_Carrier& cc);
 void check_ghost(const Chasm_Carrier& cc);

 void clear_current_ghost_scope();
 void source_file_index(QString value);
 void statement_line_number(QString value);

 void gen_return_channels();
 void resolve_handoffs(QString channels);

 void resolve_handoffs(QMap<QString, QString> channels);

 void load_type_object(QString token);

 void load_type_ref();
 void load_type_u1();
 void load_type_u2();
 void load_type_QString();
 void load_type_u4();
 void load_type_QByteArray();
 void load_type_r8();
 void load_type_QVariant();
 void load_type_n8();
 void load_type_ptr();

 void pop_call_package();
 void pull_call_package();
 void pop_proc_name();

 void gen_retvalue_channel_u4();

 void push_carrier_deque();
 void gen_carrier();
 void gen_carrier(void* pv);
 void gen_carrier_tvr(QString rep);
 void gen_carrier_lsr();
 void gen_carrier(Chasm_Type_Object* cto);
 void gen_carrier(QString symbol, Chasm_Type_Object* cto);

 void gen_carrier_with_raw_value();


 void load_string_literal(QString literal);

 void load_proc_name(QString name);
 void load_carrier_symbol_lxs(QString symbol);

 void load_symbol_u10(QString literal);
 void load_symbol_s10(QString literal);
 void load_symbol_u8(QString literal);
 void load_symbol_s8(QString literal);
 void load_symbol_u2(QString literal);
 void load_symbol_s2(QString literal);
 void load_symbol_u16(QString literal);
 void load_symbol_s16(QString literal);
 void load_symbol_u32(QString literal);
 void load_symbol_s32(QString literal);

 void run_proc_eval();

 void reset_loaded_raw_value();
 void reset_type_object();

 void add_carriers();
 void reset_carrier_deque();

 void run_eval(QString proc_name);

};

// _KANS(GTagML)

#endif // CHASM_RUNTIME_BRIDGE__H
