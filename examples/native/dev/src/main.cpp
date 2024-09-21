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
  static cex const auto l1{list(1)};
  static cex const auto l3{list(1,2,3)};
  static cex const auto e4{beta(toInt(length(l3)))};
  cout<<"start"<<endl;
  test(empty("ok")("zZz"));
  test(e1("ok")("zZz"));
  test(e2("ok")("zZz"));
  test(e3("ok")("zZz"));
  test(e4);
  test(toInt(foldl(mul)(n1)(list(n2,n3))));
  // test(e);
  // test(toInt(foldl(mul)(n1)(list(n2,n3))));
  // test(toInt(mul(n2)(mul(n2)(n2))));
  // test(toInt(FromInt<30>{}));
  // test(toInt(last(_map(mul(n2))(list(n2,n4)))));
  // test(tail(list(2,4,"ok")));
  // test(last(list(2,4,"ok")));
  // static const auto at=yo::index(list(2,4));
  // test(at(n0));
  // test(at(n1));
  // cout<<beta(toInt(n2))*3<<endl;
  // cout<<toInt(mul(n2)(n3))*3<<endl;
  // cout<<beta(head(l1))<<endl;
  // cout<<beta(null(nil)("yes")("no"))<<endl;
  // cout<<beta(null(l1)("yes")("no"))<<endl;
  // cout<<beta(is0(n0))<<endl;
  // cout<<beta(is0(n1))<<endl;
  // cout<<l1<<endl;
  // cout<<beta(Expr<Is0,Expr<Length,Nil>>{}("yes")("no"))<<endl;
  // cout<<length(l1)<<endl;
  // cout<<beta(length(l1))<<endl;
  // cout<<toInt(length(l1))<<endl;
  // cout<<beta(head(l1))<<endl;
  // cout<<beta(length(drop(n1)(l1)))<<endl;
  // cout<<beta(last(l2))<<endl;
  // cout<<toInt(length(concat(l1)(l2)))<<endl;
  // cout<<toInt(length(yo::init(l2)))<<endl;
  // cout<<beta(head(l2))<<endl;
  // cout<<beta(head(reverse(l2)))<<endl;
  // cout<<beta(head(nats))<<endl;
  // cout<<beta(toInt(head(drop(n5)(_map(mul(n2))(nats)))))<<endl;
  // cout<<beta(head(tail(nats)))<<endl;
  // cout<<beta(head(filter(flip(gt)(n2))(nats)))<<endl;//this is horrible slow to compile and requires more template depth
  // cout<<beta(snd(head(zip(l2)(nats))))<<endl;
  // cout<<toInt(length(take(n2)(l3)))<<endl;
  // cout<<toInt(length(range(n2)(n4)))<<endl;
  // cout<<toInt(length(L1{}))<<endl;
  // cout<<toInt(length(list(1,2,3,4,"ok!")))<<endl;
  // cout<<beta(last(list(1,"ok!")))<<endl;
  // cout<<beta(fromInt(2))<<endl;
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