
#include "signal-generator.h"


Signal_Generator::Signal_Generator()
{

}

void Signal_Generator::emit_new_dialog_requested(const QPoint& pos, QUrl url)
{
 Q_EMIT new_dialog_requested(pos, url);
}

