#define cex

#include <yolanda.h>
using namespace yo;

#ifdef ARDUINO
  // #include <Arduino.h>
  #include <streamFlow.h>
  using namespace StreamFlow;
  #define cout Serial
  #define endl "\n\r"
#else
  #include <iostream>
  using std::cout;
  using std::endl;
#endif

//// test ///////////////////////////////////////////////////////////////
template<typename E> void show(const E e) {cout<<e<<endl;}
template<typename E> void show(const E e,const E) {cout<<e<<" -> irreducible."<<endl;}
template<typename E,typename R> void show(const E e,const R r) {cout<<e<<" = "<<r<<endl;}

template<typename E,typename R> void test(const E e,const R r) {show(e,r);}
template<typename E> void test(const E e) {show(e,beta(e));}

void run() {
  static cex const auto e1=(id("ok")("zZz"));
  static cex const auto e2=(_true("ok")("fail")("zZz"));
  static cex const auto e3=(_S(id)(id)(id)("ok")("zZz"));
  static cex const auto e4=(_B(id)(id)("ok")("zZz"));
  static cex const auto e5=(toInt(n3));//("zZz");
  static cex const auto l3=(list(n1,n2,n3));
  static cex const auto e6=(head(drop(n2)(l3)));//mcu stall
  static cex const auto e7=(head(nats));
  // static cex const auto e8=(head(_map(toInt)(l3)));
  test(e1);
  test(e2);
  test(e3);
  test(e4);
  test(e5);
  test(e6);
  test(e7);
  // test(e8);
}

#ifdef ARDUINO
  void setup() {
    Serial.begin(115200);
    while(!Serial);
    cout<<"Yolanda3 test"<<endl;
    run();
  }
  void loop() {
    delay(1);
  }
#else
  int main() { 
    run();
    return 0;
  };
#endif