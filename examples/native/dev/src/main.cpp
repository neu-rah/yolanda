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

template<typename F,typename P>
struct App {
  const F lambda;
  const P param;
  cex App(const F f,const P p):lambda(f),param(p) {}
   template<typename O> cex const App<O,App<F,P>> cons(const O o) const {return {o,*this};}
};

template<typename O> cex const O expr(const O o) {return o;}
template<typename F, typename P> cex auto expr(const F f,const P p)->const App<F,P> {return {f,p};}
template<typename O, typename... OO> cex auto expr(const O o,const OO... oo)->const App<O,decltype(expr(oo...))> {return {o,expr(oo...)};}

template<typename Out,typename F,typename P> Out& operator<<(Out& out,const App<F,P>& o) {return out<<"("<<o.lambda<<","<<o.param<<")";}

int main() {
  cout<<"start!"<<endl;
  // cout<<x<<endl;
  cout<<expr(1967)<<endl;
  cout<<expr(1,2,3)<<endl;
  cout<<expr(1,expr(expr(2,3)))<<endl;
  cout<<expr(1,2,3).param<<endl;
  cout<<expr(1,expr(expr(2,3))).param<<endl;
  cout<<"end."<<endl;
  return  0;
} 
