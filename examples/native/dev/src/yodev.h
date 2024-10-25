#pragma once

#include <yolanda.h>
using namespace yo;

#ifdef __AVR__
  // #include <streamFlow.h>
  // using namespace StreamFlow;
  #define cout Serial
  #define endl "\n\r"
#else
  #include <iostream>
  using namespace std;
#endif

