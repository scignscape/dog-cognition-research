
#ifndef JOB_CONTEXT__H
#define JOB_CONTEXT__H

#include <QString>

#include <string>

#include "accessors.h"

#include "global-types.h"

//struct static_Job_Context
//{
// int image_count;

// static static_Job_Context* the_instance()
// {
//  static static_Job_Context* result = nullptr;
//  if(!result)
//  {
//   static static_Job_Context _the_instance {0};
//   result = &_the_instance;
//  }
//  return result;
// }

//};

class Job_Context
{
 int image_count_;

public:

 Job_Context();

 ACCESSORS(u4 ,image_count)

// static Job_Context* the_instance()
// {
//  static Job_Context* result = nullptr;
//  if(!result)
//  {
//   static Job_Context _the_instance;
//   result = &_the_instance;
//  }
//  return result;
// }

// u4 get_held_width_times_height()
// {
//  return held_width_ * held_height_;
// }

 u4 get_inc_current_image_count()
 {
  return ++image_count_;
 }

};


#endif // JOB_CONTEXT__H
