#include <yolanda.h>
using namespace yo;
using yo::operator<<;

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

  static cex const auto e11{id(1967)};
  static cex const auto e12{_true(id)(1967)(11)};
  static cex const auto e13{_S(id)(id)(id)};
  cout<<"start"<<endl;
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
  test(e9);
  test(e11);
  test(e12);
  test(e13);
  cout<<beta(toInt(n2))*3<<endl;
  cout<<beta(toInt(mul(n2)(n3)))*3<<endl;
  cout<<beta(head(l1))<<endl;
  cout<<beta(null(nil)("yes")("no"))<<endl;
  cout<<beta(null(l1)("yes")("no"))<<endl;
  cout<<beta(is0(n0))<<endl;
  cout<<beta(is0(n1))<<endl;
  cout<<l1<<endl;
  cout<<beta(Expr<Is0,Expr<Length,Nil>>{}("yes")("no"))<<endl;
  cout<<length(l1)<<endl;
  cout<<beta(length(l1))<<endl;
  cout<<beta(toInt(length(l1)))<<endl;
  cout<<beta(head(l1))<<endl;
  cout<<beta(length(drop(n1)(l1)))<<endl;
  cout<<beta(last(l2))<<endl;
  cout<<beta(toInt(length(concat(l1)(l2))))<<endl;
  cout<<beta(toInt(length(_init(l2))))<<endl;
  cout<<beta(head(l2))<<endl;
  cout<<beta(head(reverse(l2)))<<endl;
  cout<<beta(head(nats))<<endl;
  cout<<beta(toInt(head(drop(n5)(_map(mul(n2))(nats)))))<<endl;
  cout<<beta(toInt(head(tail(nats))))<<endl;
  cout<<beta(head(filter(flip(gt)(n2))(nats)))<<endl;//this is horrible slow to compile and requires more template depth (not on chain branch! :)
  cout<<beta((head(zip(l2)(nats))))<<endl;
  cout<<beta(toInt(length(take(n2)(l3))))<<endl;
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