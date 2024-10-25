#include <yolanda.h>
using namespace yo;

#ifdef __AVR__
  // #include <streamFlow.h>
  // using namespace StreamFlow;
  #define cout Serial
  #define endl "\n\r"
#else
  #include <iostream>
  using namespace std;
#endif

namespace test {
  //// test ///////////////////////////////////////////////////////////////--
  template<typename E> void show(const E e) {cout<<e<<endl;}
  template<typename E> void show(const E e,const E) {cout<<e<<" -> irreducible."<<endl;}
  template<typename E,typename R> void show(const E e,const R r) {cout<<e<<" = "<<r<<endl;}

  template<typename E,typename R> void test(const E e,const R r) {show(e,r);}
  template<typename E> void test(const E e) {show(e,beta(e));}

  void steps(const None) {cout<<none<<endl;}
  template<typename O> void steps(O&&o) {
    cout<<o<<endl<<" = ";
    steps(step(forward<O>(o)));
  }
}; using namespace test;

cex const int y=1967;
cex const Expr<int,const int&> e{11,y};
cex const auto yesno{_V("yes")("no")};

void run() {
  // cout<<y<<"->"<<&y<<endl;
  // cout<<e<<endl;
  // cout<<yesno<<endl;
  steps(yesno(_true));
  // cout<<e.head<<endl;
  // cout<<e.tail.head<<endl;
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
