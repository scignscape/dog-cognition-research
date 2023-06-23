
#include "qmt-geospatial-marker.h"

QMT_Geospatial_Marker::QMT_Geospatial_Marker(QPolygonF outline, QColor passive_color, QColor highlight_color)
  :  //client_data_set_base_(nullptr),
  held_outline_code_(0), outline_(outline),
  outline_code_(0), scale_(1), passive_color_(passive_color),
  highlight_color_(highlight_color), current_color_(passive_color)
{}

