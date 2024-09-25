#ifdef ARDUINO
  #include <Arduino.h>
// #endif
// #ifdef __AVR__
  #include <streamFlow.h>
  using namespace StreamFlow;
  #define cout Serial
  #define endl "\n"
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

void run() {
  static cex const auto l1{list(1)};
  static cex const auto l2{list(1,2)};
  static cex const auto l3{list(1,2,3)};
  static cex const auto e1=id("ok")("zZz");
  static cex const auto e2=_true("ok")("fail")("zZz");
  static cex const auto e3=_S(id)(id)(id)("ok")("zZz");
  static cex const auto e4=_B(id)(id)("ok")("zZz");
  static cex const auto e5=_C(_true)("fail")("ok")("zZz");
  static cex const auto e6=_W(_true)("ok")("zZz");
  static cex const auto e7=_T("ok")(id)("zZz");
  static cex const auto e8=_V("ok")("fail")(_true)("zZz");
  static cex const auto e9=toInt(head(range(n1)(n2)));
  static cex const auto e10=_add(3)(5);
  static cex const auto e11=is0(length(nil))("yes")("no");
  static cex const auto e12=Expr<Is0,Expr<Length,Nil>>{}("yes")("no");
  static cex const auto e13=beta(toInt(length(take(n2)(l3))));//esp12 reset
  static cex const auto e14=beta(toInt(length(concat(l1)(l2))));//esp12 reset
  static cex const auto e15=beta(toInt(head(drop(n5)(_map(mul(n2))(nats)))));
  static cex const auto e16=beta(head(yo::reverse(l2)));
  static cex const auto e17=beta(toInt(head(tail(nats))));//cant print this steps, there is an infinit list there
  static cex const auto e18=beta(head(filter(flip(gt)(n2))(nats)));
  // static cex const auto e19=beta(toInt(fst(head(zip(l2)(nats)))));//<--------- this really messes the esp12.. why?
  cout<<"start"<<endl;
  test(e1);
  test(e2);
  test(e3);
  test(e4);
  test(e5);
  test(e6);
  test(e7);
  test(e8);
  test(e1);
  test(e2);
  test(e3);
  test(e4);
  test(e5);
  test(e6);
  test(e7);
  test(e8);
  test(e9);
  test(e10);
  test(e11);
  test(e12);
  test(e13);
  test(e14);
  test(e15);
  test(e16);
  test(e17);
  test(e18);
  // test(e19);
  test(null(nil)("yes")("no"));
  test(null(l1)("yes")("no"));
  test(is0(n0)("yes")("no"));
  test(is0(n1)("yes")("no"));
  // test(length(nil));
  // test(length(drop(n1)(l1)));
  // test(head(l2));
  // test(last(l2));
  // test(head(nats));//head of infinit list

  //mixing with c++ expr --
  cout<<"C++ mix --------------"<<endl;
  cout<<beta(toInt(n2))*3<<endl;
  cout<<beta(toInt(mul(n2)(n3)))*3<<endl;

  cout<<"end"<<endl;
}

#ifdef ARDUINO
  void setup() {
    Serial.begin(115200);
    while(!Serial);
    delay(2000);
    Serial.println("Yolanda 0.3.x");
  }
  void loop() {
    run();
    delay(1000);
  }
#else
  int main() {
    run();
    return  0;
  } 
#endif