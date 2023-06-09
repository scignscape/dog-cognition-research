
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chasm-runtime-bridge.h"

#include "chasm-lib/chasm/chasm-runtime.h"
#include "chasm-lib/chasm/chasm-call-package.h"

#include "chasm-procedure-table/chasm-procedure-table.h"

#include "csm-ghost-scope.h"

#include <QString>
#include <QVariant>
#include <QByteArray>

#include <QUrl>

#include <QPoint>


Chasm_Runtime_Bridge::Chasm_Runtime_Bridge(Chasm_Runtime* csr)
  :  csr_(csr), current_call_package_(nullptr),
     current_type_object_(nullptr), current_carrier_deque_(nullptr),
     current_loaded_raw_value_(0), current_ghost_scope_(nullptr),
     proctable_(nullptr)
{
 const QVector<Chasm_Type_Object*>& pto = *csr_->pretype_type_objects();

 type_object_ref_ = pto[0];
 type_object_u1_ = pto[1];
 type_object_u2_ = pto[2];
 type_object_QString_ = pto[3];
 type_object_u4_ = pto[4];
 type_object_QByteArray_ = pto[5];
 type_object_r8_ = pto[6];
 type_object_QVariant_ = pto[7];
 type_object_n8_ = pto[8];
 type_object_ptr_ = pto[9];
}

void Chasm_Runtime_Bridge::init_new_ghost_scope()
{
 if(current_ghost_scope_)
   active_ghost_scopes_.push(current_ghost_scope_);
 current_ghost_scope_ = new CSM_Ghost_Scope;
}

void Chasm_Runtime_Bridge::clear_current_ghost_scope()
{
 if(current_ghost_scope_)
   current_ghost_scope_->clear_all();
}

void Chasm_Runtime_Bridge::run_proc_eval()
{
 run_eval(held_procname_);
}

void Chasm_Runtime_Bridge::load_proc_name(QString name)
{
 held_procname_ = name;
}


void Chasm_Runtime_Bridge::run_eval(QString proc_name)
{
 {
  auto it = proctable_->procedure_name_resolutions().find(proc_name);
  if(it != proctable_->procedure_name_resolutions().end())
    proc_name = *it;
 }
 auto it = proctable_->registered_procedures().find(proc_name);
 if(it == proctable_->registered_procedures().end())
   return;
 const QPair<CFC_Pair, _minimal_fn_type>& pr = *it;
 if(pr.first.first.convention == 0)
 {
  csr_->evaluate(current_call_package_, pr.first, pr.second.s0);
 }
 else if(pr.first.first.convention == 1)
 {
  csr_->evaluate(current_call_package_, pr.first, pr.second.s1);
 }
}


void Chasm_Runtime_Bridge::reset_carrier_deque()
{
 current_carrier_deque_->clear();
}

void Chasm_Runtime_Bridge::add_carriers()
{
 current_call_package_->add_carriers(*current_carrier_deque_);
}

void Chasm_Runtime_Bridge::push_carrier_deque()
{
 if(current_carrier_deque_)
   carrier_stacks_.push(current_carrier_deque_);
 current_carrier_deque_ = new std::deque<Chasm_Carrier>;
}

void Chasm_Runtime_Bridge::check_claims(const Chasm_Carrier& cc)
{
 check_ghost(cc);
}

void Chasm_Runtime_Bridge::check_ghost(const Chasm_Carrier& cc)
{
 if(current_ghost_scope_)
   current_ghost_scope_->add_carrier(cc);
}


void Chasm_Runtime_Bridge::load_symbol_u_(QString literal, u1 radix)
{
 current_loaded_raw_value_ = literal.toULongLong(nullptr, radix);
 if(!current_type_object_)
   infer_signed_type();

}

void Chasm_Runtime_Bridge::load_symbol_s_(QString literal, u1 radix)
{
 current_loaded_raw_value_ = literal.toInt(nullptr, radix);
 if(!current_type_object_)
   infer_signed_type();
}


// // unsigned, base 10
void Chasm_Runtime_Bridge::load_symbol_u10(QString literal)
{
 load_symbol_u_(literal, 10);
}

// // unsigned, base 2
void Chasm_Runtime_Bridge::load_symbol_u2(QString literal)
{
 load_symbol_u_(literal, 2);
}

// // unsigned, base 8
void Chasm_Runtime_Bridge::load_symbol_u8(QString literal)
{
 load_symbol_u_(literal, 8);
}

// // unsigned, base 16
void Chasm_Runtime_Bridge::load_symbol_u16(QString literal)
{
 load_symbol_u_(literal, 16);
}



// // signed, base 10
void Chasm_Runtime_Bridge::load_symbol_s10(QString literal)
{
 load_symbol_s_(literal, 10);
}

// // signed, base 2
void Chasm_Runtime_Bridge::load_symbol_s2(QString literal)
{
 load_symbol_s_(literal, 2);
}


// // signed, base 8
void Chasm_Runtime_Bridge::load_symbol_s8(QString literal)
{
 load_symbol_s_(literal, 8);
}

// // signed, base 16
void Chasm_Runtime_Bridge::load_symbol_s16(QString literal)
{
 load_symbol_s_(literal, 16);
}


void Chasm_Runtime_Bridge::gen_carrier_lsr()
{
 gen_carrier_tvr({}); //?
}

void Chasm_Runtime_Bridge::gen_carrier_tvr(QString rep)
{
 Chasm_Typed_Value_Representation tvr({current_type_object_, current_loaded_raw_value_, rep});
 Chasm_Carrier cc = csr_->gen_carrier(tvr);
 check_claims(cc);
 current_carrier_deque_->push_back(cc);
}

void Chasm_Runtime_Bridge::reset_loaded_raw_value()
{
 current_loaded_raw_value_ = 0;
}

void Chasm_Runtime_Bridge::reset_type_object()
{
 current_type_object_ = nullptr;
}

Chasm_Carrier Chasm_Runtime_Bridge::last_carrier()
{
 return current_carrier_deque_->back();
}

void Chasm_Runtime_Bridge::gen_carrier()
{
 Chasm_Carrier cc = csr_->gen_carrier_by_type_object(current_type_object_);
 check_claims(cc);
 current_carrier_deque_->push_back(cc);
}

void Chasm_Runtime_Bridge::gen_carrier(void* pv)
{
 Chasm_Carrier cc = csr_->gen_carrier_by_type_object(current_type_object_, pv);
 check_claims(cc);
 current_carrier_deque_->push_back(cc);
}


void Chasm_Runtime_Bridge::load_type_ref()
{
 current_type_object_ = type_object_ref_;
}

void Chasm_Runtime_Bridge::load_type_u1()
{
 current_type_object_ = type_object_u1_;
}

void Chasm_Runtime_Bridge::load_type_u2()
{
 current_type_object_ = type_object_u2_;
}

void Chasm_Runtime_Bridge::load_type_QString()
{
 current_type_object_ = type_object_QString_;
}

void Chasm_Runtime_Bridge::load_type_u4()
{
 current_type_object_ = type_object_u4_;
}

void Chasm_Runtime_Bridge::load_type_QByteArray()
{
 current_type_object_ = type_object_QByteArray_;
}

void Chasm_Runtime_Bridge::load_type_r8()
{
 current_type_object_ = type_object_r8_;
}

void Chasm_Runtime_Bridge::load_type_QVariant()
{
 current_type_object_ = type_object_QVariant_;
}

void Chasm_Runtime_Bridge::load_type_n8()
{
 current_type_object_ = type_object_n8_;
}

void Chasm_Runtime_Bridge::load_type_ptr()
{
 current_type_object_ = type_object_ptr_;
}


void Chasm_Runtime_Bridge::new_call_package() //Chasm_Call_Package*
{
 current_call_package_ = csr_->new_call_package();
}

void Chasm_Runtime_Bridge::add_new_channel(QString name)
{
 current_call_package_->add_new_channel(name);
}

