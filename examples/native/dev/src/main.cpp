#include <yolanda.h>
using namespace yo;
using namespace std;

//// test ///////////////////////////////////////////////////////////////
template<typename E> void show(const E e) {cout<<e<<endl;}
template<typename E> void show(const E e,const E) {cout<<e<<" -> irreducible."<<endl;}
template<typename E,typename R> void show(const E e,const R r) {cout<<e<<" = "<<r<<endl;}

template<typename E,typename R> void test(const E e,const R r) {show(e,r);}
template<typename E> void test(const E e) {show(e,beta(e));}

// constexpr const auto soma=[](int a,int b){return a+b;}

void run() {
  // static cex const auto e1{toInt(head(_map(mul(n2))(list(n3,n2))))};
  cout<<"Start -->"<<endl;
  // test(e1);
  #ifdef ARDUINO
    while(!Serial.available());
    char u=Serial.read();
  #else
    char u;
    cin>>u;
  #endif
  // const auto r=head(list(u,4));
  test(head(list(u,u,1,2,3)));//ALERT!-- this makes a HUGE difference (for worst) from the previous version!

  // cout<<beta(toInt(length(list(1,2,3,"ok!"))))<<endl;
  // cout<<beta(toInt(foldl(mul)(n2)(list(n2,n3))))<<endl;
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
  int main() {
    run();
    return 0;
  }
#endif

