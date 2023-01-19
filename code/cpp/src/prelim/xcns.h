

//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)



#ifndef XCNS__H
#define XCNS__H

#ifdef USE_XCNS

#define XCNS_(X) \
 namespace Xc { namespace X {

#define _XCNS(X) \
 } }


#define XCNS_CLASS_DECLARE(X ,C) \
 namespace Xc{ namespace X { class C; } }



#define USING_XCNS(x) \
 using namespace Xc::x;


#else

#define XCNS_(X) \

#define _XCNS(X) \

#define USING_XCNS(x) \

#define XCNS_CLASS_DECLARE(X ,C) \
  class C;

#endif


#endif // XCNS__H
