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

template<typename...> struct Expr;

template<> struct Expr<> {};
using Empty=Expr<>;
cex const Empty empty;

template<typename H>
struct Expr<H> {
  using Head=H;
  using Tail=Empty;
  const Head head;
  const Tail& tail;
  cex Expr(const Head& h):head(h),tail(empty) {}
};

template<typename H,typename... TT>
struct Expr<H,TT...> {
  using Head=H;
  using Tail=Expr<TT...>;
  const Head head;
  const Tail tail;
  cex Expr(const Head& h,const TT&... tt):head(h),tail(tt...) {}
};

template<typename Out> Out& operator<<(Out& out,const Empty& o) {return out<<"ø";}
template<typename Out,typename... OO> Out& operator<<(Out& out,const Expr<OO...>& o) {return out<<o.head<<" "<<o.tail;}

template<typename... OO> cex const Expr<const OO&...> expr(const OO&... oo) {return {oo...};}

cex const int y=1967;
cex const auto a{expr(y)};
cex const auto b{expr(y,"ok")};

int main() {
  cout<<"start!"<<endl;
  cout<<&y<<endl;
  cout<<&empty<<endl;
  cout<<&expr(y).head<<endl;
  cout<<&expr(1).head<<endl;
  cout<<a<<"->"<<&a.head<<endl;
  cout<<b<<"->"<<&b.head<<" "<<&b.tail<<" "<<&b.tail.tail<<endl;
  cout<<"end."<<endl;
  return  0;
} 
