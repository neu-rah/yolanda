#include <iostream>
using namespace std;

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

int main() {
  static cex const auto e1=id("ok")("zZz");
  static cex const auto e2=_true("ok")("fail")("zZz");
  static cex const auto e3=_S(id)(id)(id)("ok")("zZz");
  static cex const auto e4=_B(id)(id)("ok")("zZz");
  static cex const auto e5=_C(_true)("fail")("ok")("zZz");
  static cex const auto e6=_W(_true)("ok")("zZz");
  static cex const auto e7=_T("ok")(id)("zZz");
  static cex const auto e8=_V("ok")("fail")(_true)("zZz");
  static cex const auto e9=toInt(length(range(n2)(n4)));
  // steps(e1);
  // steps(e2);
  // steps(e3);
  // steps(e4);
  // steps(e5);
  // steps(e6);
  // steps(e7);
  // steps(e8);
  // test(e1);
  // test(e2);
  // test(e3);
  // test(e4);
  // test(e5);
  // test(e6);
  // test(e7);
  // test(e8);
  steps(e9);//long compile! and in error
  // steps(toInt(sub(n4)(n2)));//ok
  // steps(take(n1)(list(1,2)));
  // steps(drop(n2)(_map(toInt)(take(n9)(nats))));
  // beta(e9);//  check why this is not working as steps!
  // cout<<beta(null(nil)("yes")("no"))<<endl;
  // cout<<list(1,2,3)<<endl;
  // steps(toInt(head(drop(n5)(nats))));///in error
  return 0;
}