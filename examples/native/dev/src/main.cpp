#include <yolanda.h>
using namespace yo;
using namespace std;
//---------------------------------------

ConstText title_text="just a title";

int _test(ConstText msg) {cout<<(const char*)"test called, msg:"<<(const char*)msg<<endl;return 1967;}
Curry<decltype(&_test),&_test> test;

template<typename O,typename P>
int _ttest(const O o,const P p) {cout<<"here we go: "<<o<<","<<p<<endl;return 1111;}
CurryTemplateFunction(_ttest,2) ttest;

auto l1=cons("zZz")(nil);
auto l2=cons("Label")(l1);

auto l3=cons(n3)(cons(n2)(cons(n1)(nil)));

template<typename O> auto _pred1(const O o)->decltype(gt(o)(n6)){return gt(o)(n6);}

CurryTemplateFunction(_pred1,1) pred1;

using L1=List<N4,N3,N2,N1,N0>;

int main() {
  cout<<"Start -->"<<endl;
  // cout<<toInt(mul(n2)(mul(n2)(n2)))<<endl;
  cout<<toInt(foldl(mul)(n1)(list(n2,FromInt<120>{})))<<endl;
  // cout<<toInt(FromInt<100>{})<<endl;
  // cout<<list(1,2,3,4,"ok!")<<endl;
  // cout<<toStr(id("ok ko"))<<endl;
  // cout<<toInt(last(_map(mul(n2))(list(n2,n4))))<<endl;
  // cout<<beta(tail(_map(toInt)(list(n2,n4))))<<endl;
  // auto at=yo::index(list(n2,n4));
  // cout<<beta(toInt(at(n0)))<<endl;
  // cout<<beta(toInt(at(n1)))<<endl;
  // cout<<toStr(tail(list(1,2,3)))<<endl;
  // cout<<beta(head(_map(toStr)(nats)))<<endl;
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
  return 0;
}
