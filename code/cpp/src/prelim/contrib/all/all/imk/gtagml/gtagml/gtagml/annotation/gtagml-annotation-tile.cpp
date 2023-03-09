
#include "gtagml-annotation-tile.h"

#include "kans.h"

#include <QRegExp>

USING_KANS(GTagML)

GTagML_Annotation_Tile::GTagML_Annotation_Tile()
{
}

QString GTagML_Annotation_Tile::thumbnail(int length, int ellipsis) const
{
 QString result = subject_.trimmed().left(length);
 if(ellipsis > 0 && subject_.size() > length)
  result += QString(ellipsis, '.');
 return result;
}

void GTagML_Annotation_Tile::parse(QString str)
{
 // //  Superceded by initial grammar rules?
}


