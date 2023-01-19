
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phaon-ir/channel/phr-channel-group.h"

#include "phaon-ir/phr-code-model.h"

#include "phr-direct-eval/phr-direct-eval.h"

#include "phaon-ir/table/phr-symbol-scope.h"

#include "phaon-ir/runtime/phr-command-package.h"

#include "phaon-lib/phr-runner.h"


#include "relae-graph/relae-caon-ptr.h"

#include <QObject>

#include "kans.h"


#ifdef USING_KPH

#include "phaon-ir/phaon-ir.h"
#include "phaon-ir/channel/phr-channel-system.h"

USING_KANS(Phaon)


void default_phr_startup(PhaonIR& phr)
{
 phr.init_type_system();
 phr.init_type("fbase", DEFAULT_PTR_BYTE_CODE);
 phr.init_type("u4", 4);
 phr.init_type("u8", 8);
 phr.init_type("argvec", 9);
 phr.init_type("pcv", DEFAULT_PTR_BYTE_CODE);
 phr.init_type("str", DEFAULT_PTR_BYTE_CODE);

 // //  setup
 phr.init_code_model();

 PHR_Code_Model& pcm = *phr.code_model();
 pcm.set_type_system(phr.type_system());

 phr.create_channel_semantic_protocol("lambda");
 phr.create_channel_semantic_protocol("result");
 phr.create_channel_semantic_protocol("sigma");
 phr.create_channel_semantic_protocol("fground");
 phr.init_table();

}

#endif // USING_KPH
