
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chtr-graph-build.h"

#include "kernel/frame/chtr-frame.h"

#include "kernel/graph/chtr-graph.h"


#include "chtr-source-file.h"

#include <QMap>

#include "global-types.h"

USING_AQNS(Chasm_TR)


ChTR_Graph_Build::ChTR_Graph_Build(ChTR_Document* d, ChTR_Parser& p, ChTR_Graph& g)
 : Flags(0)
   ,document_(d)
   ,graph_(g)
   ,parser_(p)
   ,fr_(ChTR_Frame::instance())
   ,held_line_number_(0)
   ,current_context_code_(0)
   ,current_source_type_(nullptr)
{
 current_source_file_ = new ChTR_Source_File;
}

void ChTR_Graph_Build::init()
{

}


