
#ifndef GTAGML_ANNOTATION_TILE__H
#define GTAGML_ANNOTATION_TILE__H

#include "accessors.h"
#include "flags.h"


#include <QString>

#include <functional>

#include "kans.h"
KANS_(GTagML)


class GTagML_Annotation_Tile
{
 QString connector_;
 QString tile_;
 QString subject_;

 int starting_line_number_;
 int ending_line_number_;

public:

 ACCESSORS(QString ,connector)
 ACCESSORS(QString ,tile)
 ACCESSORS(QString ,subject)

 ACCESSORS(int ,starting_line_number)
 ACCESSORS(int ,ending_line_number)

 GTagML_Annotation_Tile();

 void parse(QString str);

 QString thumbnail(int length = 4, int ellipsis = 3) const;

};

_KANS(GTagML)

#endif
