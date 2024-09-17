#include <yolanda.h>
using namespace yo;
using namespace std;

//// test ///////////////////////////////////////////////////////////////
template<typename E> void show(const E e) {cout<<e<<endl;}
template<typename E> void show(const E e,const E) {cout<<e<<" -> irreducible."<<endl;}
template<typename E,typename R> void show(const E e,const R r) {cout<<e<<" = "<<r<<endl;}

template<typename E,typename R> void test(const E e,const R r) {show(e,r);}
template<typename E> void test(const E e) {show(e,beta(e));}

void run() {
  cout<<"Start -->"<<endl;
  test(toInt(n2));
  // List<int,const char*>{1,""};
  // cout<<beta(toInt(mul(n2)(mul(n2)(n2))))<<endl;
  // cout<<beta(toInt(foldl(mul)(n1)(list(n2,n3))))<<endl;
  // cout<<toInt(FromInt<100>{})<<endl;
  // cout<<list(1,2,3,4,"ok!")<<endl;
  // cout<<toInt(last(_map(mul(n2))(list(n2,n4))))<<endl;
  // cout<<beta(tail(_map(toInt)(list(n2,n4))))<<endl;
  // auto at=yo::index(list(n2,n4));
  // cout<<beta(toInt(at(n0)))<<endl;
  // cout<<beta(toInt(at(n1)))<<endl;
  // cout<<toStr(tail(list(1,2,3)))<<endl;
  // test.beta("ok");//regular curried function
  // ttest.beta("ok",11);//curried template function
  // ttest("ok")(1111).beta();
  // cout<<beta(id(test)("ok"))<<endl;
  // cout<<id(_test)<<endl;
  // cout<<id(test)<<endl;
  // beta(T()("1967")(test));
  // beta(V()("Yay!")(1111)(ttest));
  // cout<<ttest<<endl;
  // cout<<toInt(n2)*3<<endl;
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
  // cout<<toInt(head(drop(n5)(_map(mul(n2))(nats))))<<endl;
  // cout<<beta(head(tail(nats)))<<endl;
  // cout<<beta(head(filter(flip(gt)(n2))(nats)))<<endl;//this is horrible slow to compile and requires more template depth
  // cout<<beta(snd(head(zip(l2)(nats))))<<endl;
  // cout<<toInt(length(take(n2)(l3)))<<endl;
  // cout<<toInt(length(range(n2)(n4)))<<endl;
  // cout<<toInt(length(L1{}))<<endl;
  // cout<<toInt(length(list(1,2,3,4,"ok!")))<<endl;
  // cout<<beta(last(list(1,"ok!")))<<endl;
  // cout<<beta(fromInt(2))<<endl;
  cout<<"<-- end"<<endl;
}

#ifdef ARDUINO
  void setup() {
    Serial.begin(115200);
    while(!Serial);
    run();
  }

  void loop() {}
#else
  int mnain() {
    run();
    return 0;
  }
#endif

