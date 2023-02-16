
#ifndef SINGLE_JOB_CONTEXT__H
#define SINGLE_JOB_CONTEXT__H

#include <QString>

#include <string>

#include "accessors.h"

#include "global-types.h"

class Job_Context;

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


class Single_Job_Context
{
 u4 held_width_;
 u4 held_height_;

//?
 Job_Context* job_context_;

 //?static_Job_Context* static_job_context_;

public:

 Single_Job_Context(); //Job_Context* job_context); // = nullptr);

 ACCESSORS(u4 ,held_width)
 ACCESSORS(u4 ,held_height)
//?
 ACCESSORS(Job_Context* ,job_context)
 //ACCESSORS(static_Job_Context* ,static_job_context)

 u4 get_held_width_times_height()
 {
  return held_width_ * held_height_;
 }


};


#endif // SINGLE_JOB_CONTEXT__H
