
#include "gtagml-annotation-filter.h"

#include "kans.h"

#include <QRegExp>

USING_KANS(GTagML)

GTagML_Annotation_Filter::GTagML_Annotation_Filter(QString raw_text)
{
 parse(raw_text);
}

void GTagML_Annotation_Filter::parse(QString raw_text)
{
 int neg_position = raw_text.indexOf('!');
 if(neg_position != -1)
 {
  QString positive = raw_text.mid(0, neg_position);
  QString negative = raw_text.mid(neg_position + 1);
  parse(positive, positive_keys_);
  parse(negative, negative_keys_);
 }
 else
  parse(raw_text, positive_keys_);
}

bool GTagML_Annotation_Filter::check(QString& key)
{
 if(negative_keys_.contains(key))
  return false;
 if(positive_keys_.isEmpty())
  return true;
 if(positive_keys_.contains(key))
  return true;
 return false;
}

void GTagML_Annotation_Filter::parse(QString raw_text, QStringList& target)
{
 QRegExp rx("(\\s*/\\s*)|$");

 int pos = 0;
 int old_pos = 0;
 while((pos = rx.indexIn(raw_text, pos)) != -1)
 {
  int length = rx.cap().length();
  QString key = raw_text.mid(old_pos, pos - old_pos).trimmed();
  pos += length;
  old_pos = pos;
  if(!key.isEmpty())
   target.push_back(key);
  if(length == 0)
    //  meaning end of raw_text
   break;
 }

}


