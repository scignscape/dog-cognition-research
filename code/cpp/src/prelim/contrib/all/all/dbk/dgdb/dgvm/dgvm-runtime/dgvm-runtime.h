
//           Copyright Nathaniel Christen 2021.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DGVM_RUNTIME__H
#define DGVM_RUNTIME__H


#include "kans.h"
#include "accessors.h"
#include "global-types.h"


#include "tagged-ptr/mz/tagged_ptr.hpp"

#include <QString>
#include <QVector>
#include <QVariant>

#include <deque>
#include <vector>

#include <QDebug>

KANS_CLASS_DECLARE(DGDB ,DgDb_Database_Instance)
KANS_CLASS_DECLARE(DGDB ,DgDb_Hypernode)

USING_KANS(DGDB)

// Q_DECLARE_METATYPE(DgDb_Hypernode*)





KANS_(DGVM)


class DGVM_Runtime
{
 DgDb_Database_Instance* database_;

 template<typename VALUE_Type, size_t Align_size>
 mz::tagged_ptr<VALUE_Type, Align_size> _tag_ptr_value(VALUE_Type* val, u1 tag_size, u1 tag_value);

 template<typename VALUE_Type>
 mz::tagged_ptr<VALUE_Type> _tag_ptr_value(VALUE_Type* pVal, u1 tag_size, u1 tag_value);

public:

 DGVM_Runtime();

 ACCESSORS(DgDb_Database_Instance* , database)

 void init_database(QString folder, const QVector<QString>& known_flags);

//? void init_flags(QString flags_list);

 DgDb_Hypernode* new_hypernode();


 template<typename VALUE_Type>
 mz::tagged_ptr<VALUE_Type> tag_ptr_value(VALUE_Type* pVal, u1 tag_value, u1 tag_size, size_t align_size);

 template<typename VALUE_Type = void**>
 u1 get_ptr_tag(n8 raw_value);

 template<typename VALUE_Type = void**>
 VALUE_Type* detag_ptr(n8 raw_value);

// u1 _get_ptr_tag(n8 raw_value);

};

_KANS(DGVM)

#include "dgvm-runtime.templates.h"


#endif // DGVM_RUNTIME__H
