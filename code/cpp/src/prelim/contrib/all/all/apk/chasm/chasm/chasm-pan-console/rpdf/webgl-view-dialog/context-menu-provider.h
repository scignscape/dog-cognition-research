
#ifndef CONTEXT_MENU_PROVIDER__H
#define CONTEXT_MENU_PROVIDER__H


#include <QVector>
#include <QMap>
#include <QString>

#include "accessors.h"

#include "global-types.h"

//?#include "../dev/consoles/fns/s0/a3/run-s0_3_re8.cpp"

#include "chasm-lib/chasm/chasm-runtime.h"

#include "url-or-event-pattern.h"

#include "pattern-matcher-runtime.h"

class Chasm_Call_Package;
class Chasm_Type_Object;

class Chasm_Runtime;

class Signal_Generator;

class Context_Menu_Provider
{
 Pattern_Matcher_Runtime* pm_runtime_;
 Chasm_Runtime* chasm_runtime_;

 Signal_Generator* signal_generator_;

// QVector<URL_Or_Event_Pattern> url_patterns_;

// QMap<QString, QString> procedure_name_resolutions_;

// Chasm_Runtime* chasm_runtime_;

// QMap<QString, QPair<u4, minimal_fn_s0_re8_type>> registered_procedures_;

public:

 Context_Menu_Provider(Pattern_Matcher_Runtime* pm_runtime, Signal_Generator* signal_generator);

// ACCESSORS__RGET(QVector<URL_Or_Event_Pattern> ,url_patterns)
 ACCESSORS(Chasm_Runtime* ,chasm_runtime)
 ACCESSORS(Pattern_Matcher_Runtime* ,pm_runtime)

 ACCESSORS(Signal_Generator* ,signal_generator)

 void check_url(QString procedure, QString arguments,
   QVector<Pattern_Matcher_Runtime::Action_Info>& info);

// void check_url_patterns(URL_Or_Event_Pattern::Pattern_Contexts context,
//   QString url, QVector<Context_Menu_Provider::Action_Info>& info,
//   QString secondary = {});

 void run_callback(Pattern_Matcher_Runtime::Action_Info ai);

};


#endif
