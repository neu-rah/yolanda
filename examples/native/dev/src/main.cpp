#ifdef ARDUINO
  #include <Arduino.h>
// #endif
// #ifdef __AVR__
  #include <streamFlow.h>
  using namespace StreamFlow;
  #define cout Serial
  #define endl "\n"
  #ifdef __AVR__
    #include <avr_std.h>
    using namespace avr_std;
  #endif
#else
  #include <iostream>
  using namespace std;
#endif

// #define cex
#define cex constexpr

template<bool chk,typename T> using When=typename enable_if<chk,T>::type;

template<typename H,typename T>
struct App {
  using Head=H;
  using Tail=T;
  const Head& head;
  const Tail& tail;
  cex App(){}
  cex App(const H& h,const T& t):head(h),tail(t) {}
};

template<typename Out,typename H,typename T> Out& operator<<(Out& out,const App<H,T> o) {return out<<o.head<<" "<<o.tail;}

cex const int year=1967;
cex const char* name="rui";
cex const App<int,const char*> a0{year,name};

int main() {
  cout<<"start!"<<endl;
  cout<<a0<<endl;
  cout<<"end"<<endl;
  return  0;
} 
