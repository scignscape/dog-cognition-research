
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NGML_SDI_PAGE_ELEMENT__H
#define NGML_SDI_PAGE_ELEMENT__H

#include "global-types.h"


#include <QDebug>

#include <QTextStream>

//#include "ntxh-parser/ntxh-document.h"

#include "kans.h"

#include "accessors.h"

//KANS_CLASS_DECLARE(HGDMCore ,NTXH_Graph)
//USING_KANS(HGDMCore)

//class hypernode_type;

class NGML_SDI_Mark_Base;

class NGML_SDI_Page_Element 
{
 NGML_SDI_Mark_Base* mark_;

 u4 count_in_page_;

public:
 
 NGML_SDI_Page_Element(NGML_SDI_Mark_Base* mark);

 ACCESSORS(NGML_SDI_Mark_Base* ,mark)
 ACCESSORS(u4 ,count_in_page)

 static QPair<u4, u4> get_minimal_vertical_compare_offset(QPair<u4, u4> new_values = {0, 0});

 void read_from_strings(QStringList& qsl);

};

bool operator <(const NGML_SDI_Page_Element& lhs, 
  const NGML_SDI_Page_Element& rhs);

#endif // NGML_SDI_PAGE_ELEMENT__H
