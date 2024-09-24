#pragma once

#ifdef __AVR__
  #include "avr_std.h"
  using namespace avr_std;
#else
  #include <type_traits>
  using namespace std;
#endif

#include "yo/lambda.h"
#include "yo/combinators.h"
#include "yo/curry.h"
#include "yo/bool.h"
#include "yo/peano.h"
#include "yo/list.h"
#include "yo/print.h"

