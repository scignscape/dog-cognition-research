
//           Copyright Nathaniel Christen 2021.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dh-location-structure.h"

DH_Location_Structure::DH_Location_Structure()
  :  raw_code_(0)
{

}

void DH_Location_Structure::set_edge_id(u4 id)
{
 // //  highest bit should be clear
 id &= 0x7FFF'FFFF;

 raw_code_ |= ( (n8)id << 32 );
}

u4 DH_Location_Structure::get_edge_id()
{
 u4 result = raw_code_ >> 32;
 return result & 0x7FFF'FFFF;
}

u2 DH_Location_Structure::get_raw_primary_field_id()
{
 // return (u2) (raw_code_ & 0x0000'FFFF'0000'0000);
 return (u2) (raw_code_ >> 32);
}

u2 DH_Location_Structure::get_raw_secondary_field_id()
{
 u2 result = raw_code_ >> 48;
 return result & 0b0111'1111'1111'1111;
}


QPair<DH_Location_Structure::Field_Id_Options, u2>
  DH_Location_Structure::split_index_code(u2 index_code)
{
 static u2 mask13 = 0b0001'1111'1111'1111;
 return { (Field_Id_Options) (index_code >> 13), index_code & mask13 };
}


QPair<DH_Location_Structure::Field_Id_Options, u2>
  DH_Location_Structure::get_primary_field_id()
{
 u2 result = get_raw_primary_field_id();

 return split_index_code(result);
// static u2 mask13 = 0b0001'1111'1111'1111;
// return { (Field_Id_Options) (result >> 13), result & mask13};
}


QPair<DH_Location_Structure::Field_Id_Options, u2>
  DH_Location_Structure::get_secondary_field_id()
{
 u2 result = get_raw_secondary_field_id();

 return split_index_code(result);

// static u2 mask13 = 0b0001'1111'1111'1111;
// return { (Field_Id_Options) ( (result >> 13) & 3), result & mask13};
}

u4 DH_Location_Structure::get_raw_node_id()
{
// n8 result = raw_code_ & 0x0000'FFFF'FFFF'0000;
// return (u4) (result >> 16);
 return raw_code_ & 0xFFFF'FFFF;
}


void DH_Location_Structure::set_data_options(Data_Options opts)
{
 u1 data_options = (u1) opts & 7;

 // //  clear the data_options and typed flag bits ///
 raw_code_ &= 0x7FFF'FFFF'1FFF'FFFF;

 raw_code_ |= (n8)data_options << 29;

 if( (u1)opts & 8 )
   raw_code_ |= ( (n8)1 << 63);
}


QPair<DH_Location_Structure::Data_Options, u4> DH_Location_Structure::get_node_id()
{
 u4 result = get_raw_node_id();
 u1 data_options = result >> 29;
 result &= 0b0001'1111'1111'1111'1111'1111'1111'1111;
 if(raw_code_ >> 63)
 {
  // //  typed_flag bit set
  return { (DH_Location_Structure::Data_Options) (data_options | 8), result };
 }
 // //  typed_flag bit not set
 return { (DH_Location_Structure::Data_Options) data_options, result };
}

void DH_Location_Structure::set_node_id(u4 id)
{
 // //  id should be < 0x1FFF'FFFF ...

 // //  smallest four bytes should be 0b0001'1111 ... all ones ...
 raw_code_ &= 0xFFFF'FFFF'E000'0000;
 raw_code_ |= id;
}


void DH_Location_Structure::set_raw_primary_field_id(u2 index_code)
{
 raw_code_ &= 0xFFFF'0000'FFFF'FFFF;
 raw_code_ |= ( (n8) index_code << 32);
}

void DH_Location_Structure::set_raw_secondary_field_id(u2 index_code)
{
 raw_code_ &= 0x8000'FFFF'FFFF'FFFF;
 raw_code_ |= ( (n8)index_code << 48);
}


u2 DH_Location_Structure::set_primary_field_id(u2 field_number, Field_Id_Options fio)
{
 static u2 mask13 = 0b0001'1111'1111'1111;
 u2 result = field_number & mask13;

 // // if(result != field_number)
  //     opportunity to check the field_number is in proper bounds ...

 result |= ((u2) fio) << 13;

 set_raw_primary_field_id(result);

// raw_code_ &= 0xFFFF'FFFF'FFFF'0000;
// raw_code_ |= result;//(result << 16);

 return result;
}

u2 DH_Location_Structure::set_secondary_field_id(u2 field_number, Field_Id_Options fio)
{
 static u2 mask13 = 0b0001'1111'1111'1111;
 u2 result = field_number & mask13;

 // // if(result != field_number)
  //     opportunity to check the field_number is in proper bounds ...

 // //  fio should be only one of the first four options ...
 result |= (((u2) fio) & 3) << 13;

 set_raw_secondary_field_id(result);

// raw_code_ &= 0x8000'FFFF'FFFF'FFFF;
// raw_code_ |= ( (n8)result << 48);

 return result;
}


