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

template<typename...> struct Expr;

template<> struct Expr<> {
  cex Expr() {}
  cex Expr(const Expr& o) {}
};
using Empty=Expr<>;
cex const Empty empty;
template<typename Out> Out& operator<<(Out& out,const Empty&) {return out<<"ø";}

template<typename H>
struct Expr<H> {
  using Head=H;
  using Tail=Empty;
  const Head head;
  const Tail& tail;
  cex Expr() {}
  cex Expr(const H& h):head(h),tail(empty) {}
};

template<typename H,typename... TT>
struct Expr<H,TT...> {
  using Head=H;
  using Tail=Expr<TT...>;
  const Head head;
  const Tail tail;
  cex Expr() {}
  cex Expr(const H& h,const TT&... tt):head(h),tail(tt...) {}
};

template<typename... OO> cex const Expr<OO...> expr(const OO... oo) {return {oo...};}

template<typename Out,typename... OO> Out& operator<<(Out& out,const Expr<OO...>& o) {return out<<"("<<o.head<<" "<<o.tail<<")";}

template<typename Fn> struct Combinator {};

struct I:Combinator<I> {
  template<typename O> static cex const O beta(const O o) {return o;}
};
cex const I _I;
template<typename Out> Out& operator<<(Out& out,const I) {return out<<"I";}

struct K:Combinator<K> {
  template<typename O,typename P> static cex const O beta(const O o,const P) {return o;}
};
cex const K _K;
template<typename Out> Out& operator<<(Out& out,const K) {return out<<"K";}

int main() {
  cout<<"start!"<<endl;
  cout<<_I.beta("ok")<<endl;
  cout<<_K.beta("ok","fail")<<endl;
  cout<<"end"<<endl;
  return  0;
} 
