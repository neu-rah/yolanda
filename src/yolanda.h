#pragma once

#ifdef _S
  #define YO_S_TMP _S
  #undef _S
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
#include "yo/show.h"
#include "yo/print.h"
#ifdef _S
  #define _S YO_S_TMP
#endif