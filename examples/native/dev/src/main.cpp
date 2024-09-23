#include <iostream>
using namespace std;

#include <yolanda.h>

//// test ///////////////////////////////////////////////////////////////
template<typename E> void show(const E e) {cout<<e<<endl;}
template<typename E> void show(const E e,const E) {cout<<e<<" -> irreducible."<<endl;}
template<typename E,typename R> void show(const E e,const R r) {cout<<e<<" = "<<r<<endl;}

template<typename E,typename R> void test(const E e,const R r) {show(e,r);}
template<typename E> void test(const E e) {show(e,beta(e));}

void steps(const None) {cout<<none<<endl;}
template<typename O> void steps(const O o) {
  cout<<o<<" = ";
  steps(step(o));
}

int main() {
  static cex const auto e1=id("ok")("zZz");
  static cex const auto e2=_true("ok")("fail")("zZz");
  static cex const auto e3=_S(id)(id)(id)("ok")("zZz");
  static cex const auto e4=_B(id)(id)("ok")("zZz");
  static cex const auto e5=_C(_true)("fail")("ok")("zZz");
  static cex const auto e6=_W(_true)("ok")("zZz");
  static cex const auto e7=_T("ok")(id)("zZz");
  static cex const auto e8=_V("ok")("fail")(_true)("zZz");
  steps(e1);
  steps(e2);
  steps(e3);
  steps(e4);
  steps(e5);
  steps(e6);
  steps(e7);
  steps(e8);
  test(e1);
  test(e2);
  test(e3);
  test(e4);
  test(e5);
  test(e6);
  test(e7);
  test(e8);
  return 0;
}