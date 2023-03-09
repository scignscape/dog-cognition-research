
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GTAGML_OUTPUT_BASE__H
#define GTAGML_OUTPUT_BASE__H

#include "relae-graph/relae-node-ptr.h"

#include "kernel/gtagml-dominion.h"

#include "kernel/query/gtagml-query.h"

#include <QString>
#include <QTextStream>

#include "accessors.h"


#include "kans.h"
KANS_CLASS_DECLARE(HTXN ,HTXN_Document_8b)
USING_KANS(HTXN)


#include "kans.h"

KANS_(GTagML)

class GTagML_Graph;
class GTagML_Document;


class GTagML_Output_Base
{
protected:

 GTagML_Document& document_;
 GTagML_Graph& graph_;

 const GTagML_Query& qry_;
 
 HTXN_Document_8b* htxn_document_;

public:


 GTagML_Output_Base(GTagML_Document& document);

 ~GTagML_Output_Base();

 virtual void generate(QTextStream& qts) = 0;

 ACCESSORS(HTXN_Document_8b* ,htxn_document)


};

_KANS(GTagML)


#endif
