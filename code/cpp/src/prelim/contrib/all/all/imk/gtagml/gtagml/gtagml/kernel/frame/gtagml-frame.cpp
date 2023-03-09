
#include "gtagml-frame.h"

#include "kernel/graph/gtagml-node.h"

#include "kans.h"

#include <QDebug>


USING_KANS(GTagML)

GTagML_Frame::GTagML_Frame()
 : node_frame<GTagML_Dominion>()
{


}

GTagML_Frame& GTagML_Frame::instance()
{
 static GTagML_Frame* the_instance = nullptr;
 if(!the_instance)
  the_instance = new GTagML_Frame;
 return *the_instance;
}
