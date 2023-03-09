
#ifndef GTAGML_ANNOTATION_FILTER__H
#define GTAGML_ANNOTATION_FILTER__H

#include "accessors.h"
#include "flags.h"


#include <QString>
#include <QStringList>

#include <functional>

#include "kans.h"
KANS_(GTagML)


class GTagML_Annotation_Filter
{
 QStringList positive_keys_;
 QStringList negative_keys_;

public:

 GTagML_Annotation_Filter(QString raw_text);

 void parse(QString raw_text);
 static void parse(QString raw_text, QStringList& target);

 bool check(QString& key);
};

_KANS(GTagML)

#endif
