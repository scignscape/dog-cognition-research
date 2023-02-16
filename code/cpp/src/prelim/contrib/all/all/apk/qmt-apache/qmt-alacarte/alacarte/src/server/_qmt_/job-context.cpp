
#include "job-context.h"

#include <QtMath>

Job_Context::Job_Context()
  : image_count_(0)
{
}


double tilex2long(int x, int z)
{
 return x / (double)(1 << z) * 360.0 - 180;
}

double tiley2lat(int y, int z)
{
 double n = M_PI - 2.0 * M_PI * y / (double)(1 << z);
 return 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
}

