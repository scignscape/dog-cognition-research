
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_PACK_CODE__H
#define QH_PACK_CODE__H

#include <QByteArray>

#include <functional>

#include "global-types.h"

#include "kans.h"

KANS_(RdSC)

class Qh_Pack_Code
{
 QVector<u1> field_codes_;


public:

 enum class Type_Hints {
   N_A, Signed, Real, Chars_QString,
   Chars_Encoded, Blob, Opaque, Enum, Unsigned
 };

 Qh_Pack_Code();

 Qh_Pack_Code& add_u1(u2 array = 0);
 Qh_Pack_Code& add_u2(u2 array = 0);
 Qh_Pack_Code& add_u4(u2 array = 0);
 Qh_Pack_Code& add_n8(u2 array = 0);

 Qh_Pack_Code& add_s1(u2 array = 0);
 Qh_Pack_Code& add_s2(u2 array = 0);
 Qh_Pack_Code& add_s4(u2 array = 0);
 Qh_Pack_Code& add_s8(u2 array = 0);

 Qh_Pack_Code& add_ratio(u2 array = 0);
 Qh_Pack_Code& add_posit(u2 array = 0);
 Qh_Pack_Code& add_r4(u2 array = 0);
 Qh_Pack_Code& add_r8(u2 array = 0);

 Qh_Pack_Code& add_str(u2 array = 0);
 Qh_Pack_Code& add_txn(u2 array = 0);

 Qh_Pack_Code& add_proxy(u2 array = 0);
 Qh_Pack_Code& add_opaque(u2 array = 0);


 u1 with_proxy_hint(u1 cue);
 u1 with_type_hint(u1 cue, Type_Hints th);

 static u1 get_type_hint_code(Type_Hints th);
 static QString get_type_hint_string(Type_Hints th);

 void each(std::function<u2(u1, u2)> fn);

 void each(std::function<u2(u1, Type_Hints, u2)> fn);

 Type_Hints get_type_hint(u2 index);

 static Type_Hints parse_type_hint(u1 cue);

 QByteArray as_qba();

 QPair<u1, Type_Hints> get_requirements(u2 index);

 u2 check_index_to_array(u2 ix)
 {
  return (ix < field_codes_.size())? ix : 0;
 }


};

_KANS(RdSC)

#endif // QH_PACK_CODE__H


