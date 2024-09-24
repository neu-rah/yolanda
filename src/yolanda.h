#pragma once

#ifdef __AVR__
  #include "avr_std.h"
  using namespace avr_std;
#else
  #include <type_traits>
  using namespace std;
#endif

#ifdef ARDUINO
  #include <streamFlow.h>
  using namespace StreamFlow;
  #define cout Serial
  #define endl "\n"
#else
  #include <iostream>
  using namespace std;
#endif

#include "yo/lambda.h"
#include "yo/combinators.h"
#include "yo/curry.h"
#include "yo/bool.h"
#include "yo/peano.h"
#include "yo/list.h"

#ifdef ARDUINO
namespace yo {
  template<typename O>
  typename enable_if<!yo::isApp<O>()&&!yo::isLambda<O>()&&!yo::isEmpty<O>()&&!isNone<O>(),Serial_>::type&
  operator<<(Serial_& out,const O o)
    {out.print(o);return out;}
};
#endif
