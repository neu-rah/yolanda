#pragma once

#include "yo/lambda.h"
#include "yo/combinators.h"
#include "yo/curry.h"
#include "yo/bool.h"
#include "yo/peano.h"
#include "yo/list.h"

#ifdef ARDUINO
namespace yo {
  template<typename O> typename enable_if<!isApp<O>()&&!isLambda<O>()&&!isEmpty<O>(),Serial_>::type& operator<<(Serial_& out,const O o) {out.print(o);return out;}
};
#endif
