

//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)



#ifndef AQNS__H
#define AQNS__H

#ifdef USE_AQNS

#define AQNS_(X) \
 namespace Aq { namespace X {

#define _AQNS(X) \
 } }


#define AQNS_CLASS_DECLARE(X ,C) \
 namespace Aq{ namespace X { class C; } }



#define USING_AQNS(x) \
 using namespace Aq::x;


#else

#define AQNS_(X) \

#define _AQNS(X) \

#define USING_AQNS(x) \

#define AQNS_CLASS_DECLARE(X ,C) \
  class C;

#endif


#endif // AQNS__H
