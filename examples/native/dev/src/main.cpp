#ifdef ARDUINO
  #include <Arduino.h>
// #endif
// #ifdef __AVR__
  #include <streamFlow.h>
  using namespace StreamFlow;
  #define cout Serial
  #define endl "\n"
  #ifdef __AVR__
    #include <avr_std.h>
    using namespace avr_std;
  #endif
#else
  #include <iostream>
  using namespace std;
#endif

#include <yolanda.h>
using namespace yo;

//// test ///////////////////////////////////////////////////////////////
template<typename E> void show(const E e) {cout<<e<<endl;}
template<typename E> void show(const E e,const E) {cout<<e<<" -> irreducible."<<endl;}
template<typename E,typename R> void show(const E e,const R r) {cout<<e<<" = "<<r<<endl;}

template<typename E,typename R> void test(const E e,const R r) {show(e,r);}
template<typename E> void test(const E e) {show(e,beta(e));}

void steps(const None) {cout<<none<<endl;}
template<typename O> void steps(const O o) {
  cout<<o<<endl<<" = ";
  steps(step(o));
}

/////////////////////////////////////////////////////////
int main() {
  // cout<<_concat(expr(1,2),3)<<endl;
  // test(_I("ok")("zZz"));
  // steps(_S(_I)(_I)(_I)("ok")("x"));
  steps(_C(_true)("fail")("ok"));
  cout<<"end"<<endl;
  return 0;
}