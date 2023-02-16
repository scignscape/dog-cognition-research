
#include "qmt-tile-object.h"

#include "qt-logger.h"

#include <QtMath>

#include "utils/transform.hpp"

namespace {
// // taken from OpenStreetMaps info

double tilex2long(int x, int z)
{
 return x / (double)(1 << z) * 360.0 - 180;
}

double tiley2lat(int y, int z)
{
 double n = M_PI - 2.0 * M_PI * y / (double)(1 << z);
 return 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
}
}



QMT_Tile_Object::QMT_Tile_Object(u1 zoom, u4 x, u4 y)
  : x_(x), y_(y), zoom_(zoom)
{
 calculate_latitude_and_longitude();


 init_meractor_measures();
}

void QMT_Tile_Object::init_meractor_measures()
{
 int mx, my, mx1, my1;

 tileToMercator(x_, y_, zoom_, mx, my);
 tileToMercator(x_ + 1, y_ + 1, zoom_, mx1, my1);

 set_meractor_measures((s4) mx, (s4) my, (u2) qAbs(mx1 - mx), (u2) qAbs(my1 - my));
}

void QMT_Tile_Object::set_meractor_measures(s4 mercator_x, s4 mercator_y, u2 mercator_width, u2 mercator_height)
{
 mercator_x_ = mercator_x;
 mercator_y_ = mercator_y;
 mercator_width_ = mercator_width;
 mercator_height_ = mercator_height;
}


void QMT_Tile_Object::calculate_latitude_and_longitude()
{
 top_left_latitude_ = tiley2lat(y_, zoom_);
 top_left_longitude_ = tilex2long(x_, zoom_);

 bottom_right_latitude_ = tiley2lat(y_ + 1, zoom_);
 bottom_right_longitude_ = tilex2long(x_ + 1, zoom_);

// bottom_right_latitude_ = tiley2lat(y_ + height_, zoom_);
// bottom_right_longitude_ = tilex2long(x_ + width_, zoom_);

 //r8 brl =

}

void QMT_Tile_Object::mercator_to_latitude_and_longitude(u4 mx, u4 my, u1 zoom, r8& lat, r8& lon)
{
 int x, y;
 mercatorToTile(mx, my, (u4) zoom, x, y);
 qlog("mercatorToTile: mx = %1, my = %2, x = %3, y = %4, zoom = %5\n"_qt.
   arg(mx).arg(my).arg(x).arg(y).arg(zoom));
 lat = tiley2lat(y, zoom);
 lon = tilex2long(x, zoom);
}



