
#ifndef QMT_TILE_OBJECT__H
#define QMT_TILE_OBJECT__H

#include <QString>

#include <string>

#include "accessors.h"

#include "global-types.h"


struct QMT_Tile_Object_Coordinates
{
 u1 zoom;
 u4 x;
 u4 y;

 void* save_info;
};


class QMT_Tile_Object
{
 r8 top_left_latitude_;
 r8 top_left_longitude_;

 r8 bottom_right_latitude_;
 r8 bottom_right_longitude_;

 s4 mercator_x_;
 s4 mercator_y_;

 u4 x_;
 u4 y_;
 u1 zoom_;

 u2 mercator_width_;
 u2 mercator_height_;

 void calculate_latitude_and_longitude();

 void init_meractor_measures();

public:

 QMT_Tile_Object(u1 zoom, u4 x, u4 y);

 void set_meractor_measures(s4 mercator_x, s4 mercator_y, u2 mercator_width, u2 mercator_height);

 void* const* matches(const QMT_Tile_Object_Coordinates& coords)
 {
  if( (x_ == coords.x) && y_ == (coords.y) && (zoom_ == coords.zoom) )
    return &coords.save_info;
  return nullptr;
 }

 ACCESSORS(r8 ,top_left_latitude)
 ACCESSORS(r8 ,top_left_longitude)

 ACCESSORS(r8 ,bottom_right_latitude)
 ACCESSORS(r8 ,bottom_right_longitude)


 ACCESSORS(u4 ,x)
 ACCESSORS(u4 ,y)

 ACCESSORS(s4 ,mercator_x)
 ACCESSORS(s4 ,mercator_y)


 ACCESSORS(u1 ,zoom)

 ACCESSORS(u2 ,mercator_width)
 ACCESSORS(u2 ,mercator_height)

 r8 get_latitude_span()
 {
  return bottom_right_latitude_ - top_left_latitude_;
 }

 r8 get_longitude_span()
 {
  return bottom_right_longitude_ - top_left_longitude_;
 }

 static void mercator_to_latitude_and_longitude(u4 mx, u4 my, u1 zoom, r8& lat, r8& lon);

};


#endif // QMT_TILE_OBJECT__H
