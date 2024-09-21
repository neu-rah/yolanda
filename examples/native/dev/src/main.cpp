#ifdef ARDUINO
  #include <Arduino.h>
  #include <streamFlow.h>
  using namespace StreamFlow;
  #define cout Serial
  #define endl "\n"
  #include <avr_std.h>
  using namespace avr_std;
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

void run() {
  static cex const auto e1{id(1967)};
  static cex const auto e2{_true(id)(1967)(11)};
  static cex const auto e3{_S(id)(id)(id)};
  static cex const auto l3{list(1,2,3)};
  cout<<"start"<<endl;
  test(empty("ok")("zZz"));
  test(e1("ok")("zZz"));
  test(e2("ok")("zZz"));
  test(e3("ok")("zZz"));
  cout<<l3<<endl;
  test(toInt(length(l3)));
  cout<<"end"<<endl;
}

#ifdef ARDUINO
  void setup() {
    Serial.begin(115200);
    while(!Serial);
    run();
  }
  void loop() {}
#else
  int main() {
    run();
    return  0;
  } 
#endif