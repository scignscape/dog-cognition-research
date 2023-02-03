
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DH_LOCATION_STRUCTURE__H
#define DH_LOCATION_STRUCTURE__H

#include <QByteArray>

#include <functional>

#include "global-types.h"

#include "accessors.h"


// //  pattern
//     0b 0000'0000'0000'0000 0000'0000'0000'1000 0000'0000'0000'0000 0000'0000'0000'1000

#include "kans.h"

KANS_(DGDB)

class DH_Location_Structure
{
 n8 raw_code_;

public:

 enum class Field_Id_Options {
  Structure_Field_Index,
  Raw_Array_Position,
  Offset_Array_Position,
  Negative_Raw_Array_Position,
  Negative_Offset_Array_Position,

  Interned_Property_Name,
  Interned_Field_Name,
  Edge_Data
  //?Mapped_Field_Name
 };

 enum class Data_Options {
  QVariant, Numeric, QString,
  Raw_Binary, Shm_Pointer,
  Shm_Pointer_With_Path_Code,
  In_Edge,
  Out_Edge,
  Signed_Numeric, Typed_Numeric, Typed_QString,
  Typed_Raw_Binary, Typed_Shm_Pointer,
  Typed_Shm_Pointer_With_Path_Code,
  Typed_In_Edge,  // //  does "typed" make sense here?
  Typed_Out_Edge  // //  does "typed" make sense here?
 };


 DH_Location_Structure();

 ACCESSORS(n8 ,raw_code)

 u2 get_raw_primary_field_id();
 u2 get_raw_secondary_field_id();

 u4 get_edge_id();

 QPair<Field_Id_Options, u2> get_primary_field_id();
 QPair<Field_Id_Options, u2> get_secondary_field_id();
 QPair<Data_Options, u4> get_node_id();

 static QPair<Field_Id_Options, u2> split_index_code(u2 index_code);


 u4 get_raw_node_id();

 void set_node_id(u4 id);
 void set_edge_id(u4 id);

 void set_data_options(Data_Options opts);

 u2 set_primary_field_id(u2 field_number, Field_Id_Options fio);
 u2 set_secondary_field_id(u2 field_number, Field_Id_Options fio);

 void set_raw_primary_field_id(u2 index_code);
 void set_raw_secondary_field_id(u2 index_code);


};

_KANS(DGDB)

USING_KANS(DGDB)

namespace _class_DH_Location_Structure
{
 inline QPair<DH_Location_Structure::Field_Id_Options, u2>
   _split_index_code(u2 index_code)
 {
  return DH_Location_Structure::split_index_code(index_code);
 }


#define TEMP_MACRO(_x, x) \
 inline u2 _x(u2 i) { return (i & 0b0001'1111'1111'1111) | \
   ((u2)(DH_Location_Structure::Field_Id_Options::x) << 13);} \

 TEMP_MACRO(_structure_field_index, Structure_Field_Index)
 TEMP_MACRO(_raw_array_position, Raw_Array_Position)
 TEMP_MACRO(_offset_array_position, Offset_Array_Position)
 TEMP_MACRO(_negative_raw_array_position, Negative_Raw_Array_Position)
 TEMP_MACRO(_negative_offset_array_position, Negative_Offset_Array_Position)
 TEMP_MACRO(_interned_property_name, Interned_Property_Name)
 TEMP_MACRO(_interned_field_name, Interned_Field_Name)
 TEMP_MACRO(_edge_data, Edge_Data)
// TEMP_MACRO(_mapped_field_name, Mapped_Field_Name)

// TEMP_MACRO(_raw_index, Raw_Index)
// TEMP_MACRO(_raw_index, Raw_Index)

// Raw_Array_Position,
// Offset_Array_Position,
// Negative_Raw_Array_Position,
// Negative_Offset_Array_Position,

// Interned_Property_Name,
// Interned_Field_Name,
// Mapped_Field_Name


}

#endif // DH_LOCATION_STRUCTURE__H


