
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DH_TYPE_FIELD_INFO_STATE__H
#define DH_TYPE_FIELD_INFO_STATE__H

#include <functional>

#include <QMap>

#include "global-types.h"

//#include "dw-stage-value.h"
//#include "stage/dw-stage-queue.h"

// #include "_whitedb/_whitedb.h"

#include "accessors.h"

#include "kans.h"

#include "dh-subvalue-field.h"


#include <QtXml>


 //?KANS_(DgDb)

//class DgDb_Node;

//class DH_Node;
//class DH_Stage_Value;
//struct DH_Stage_Queue;


class DgDb_Hypernode;

class DH_Subvalue_Field;

class DH_Type;

class DH_Type_Field_Info_State
{
 QString field_name_;
 DH_Type& _this;
 u4 held_start_;
 DH_Subvalue_Field* field_;

 QMap<DH_Subvalue_Field*, QVector<QPair<DH_Subvalue_Field*, u2>>> query_partners_;


public:
 enum class Wide_Input_State : u1 {
   N_A, Field_Vecotor, Field_Map, Field_Name, Query, Record, Encode
 };

 enum class Narrow_Input_State : u1 {
   N_A, Declared_Path, Declared_Field_Index,
   Declared_Block_Indexes, Declared_Byte_Length,
   Query_Column, Query_Partner
 };

private:
 Wide_Input_State wide_;
 Narrow_Input_State narrow_;

 void note_field_block_offset(u4 start, u4 end, u1 qtc = 255);
 void note_write_mode(DH_Subvalue_Field::Write_Mode wm);

public:

 DH_Type_Field_Info_State(DH_Type& th, QString field_name = {})
   :   field_name_(field_name), _this(th),
      held_start_(-1), field_(nullptr),
      wide_(Wide_Input_State::N_A),
      narrow_(Narrow_Input_State::N_A)
 {

 }

 DH_Type_Field_Info_State(DH_Type& th, Wide_Input_State wst, QString field_name = {})
    : field_name_(field_name), _this(th),
      held_start_(-1),
      field_(nullptr),
      wide_(wst),
      narrow_(Narrow_Input_State::N_A)
 {

 }

 DH_Type* operator->()
 {
  return &_this;
 }

 DH_Type_Field_Info_State& operator()(QString another_field_name);

 DH_Type_Field_Info_State& operator()(u4 start, u4 end);

 DH_Type_Field_Info_State& operator()(u1 byte_len);

 DH_Type_Field_Info_State& operator()(QPair<
   QPair<DH_Subvalue_Field::Write_Mode, DH_Stage_Code::Query_Typecode>, u2> pr);
 DH_Type_Field_Info_State& operator()(DH_Subvalue_Field::Write_Mode wm);
 DH_Type_Field_Info_State& operator()(QPair<DH_Subvalue_Field::Write_Mode, u2> pr);
 DH_Type_Field_Info_State& operator()(QPair<DH_Subvalue_Field::Write_Mode, DH_Stage_Code::Query_Typecode> pr);

 DH_Type_Field_Info_State& operator[](u2 index);
 DH_Type_Field_Info_State& operator[](QString partner);

 DH_Type_Field_Info_State& _signed_(u4 start, u4 end);
 DH_Type_Field_Info_State& _date_(u4 start, u4 end);
 DH_Type_Field_Info_State& _time_(u4 start, u4 end);
 DH_Type_Field_Info_State& _datetime_(u4 start, u4 end);

 template<typename T>
 DH_Type_Field_Info_State& query(QString path);

 template<typename T>
 DH_Type_Field_Info_State& record(u2 column_index = 0);

 template<typename T>
 DH_Type_Field_Info_State& encode();

// ACCESSORS(QString ,field_name)
// ACCESSORS(u4 ,held_start)

};


 //?_KANS(DgDb)

#endif // DH_TYPE__H


