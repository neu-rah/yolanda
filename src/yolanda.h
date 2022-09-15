#pragma once

#ifndef IO_REBIND
  #define IO_REBIND
#endif

#ifndef REDUCE_ON_COMPLETION
  #define REDUCE_ON_COMPLETION
#endif

#ifdef _S
  #define YO_S_TMP _S
  #undef _S
#endif
#ifdef nl
  #define YO_nl_TMP nl
  #undef nl
#endif
#include "yo/base.h"
#include "yo/io.h"
#include "yo/data.h"
#include "yo/combinator.h"
#include "yo/lambda.h"
#include "yo/curry.h"
#include "yo/binder.h"
#include "yo/SKI.h"
#include "yo/core.h"
#include "yo/maybe.h"
#include "yo/either.h"
#include "yo/bool.h"
#include "yo/peano.h"
#include "yo/list.h"
#include "yo/toStr.h"
#include "yo/print.h"
#ifdef YO_S_TMP
  #define _S YO_S_TMP
#endif
#ifdef YO_nl_TMP
  #define nl YO_nl_TMP
#endif

//sugar
template<typename O,typename E>
const O runTo(const E&&e) {return e.template runTo<O>();}
