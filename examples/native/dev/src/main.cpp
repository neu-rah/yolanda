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

struct App {};

template<typename O> constexpr const bool isApp() {return is_convertible<O,App>::value;}

template<typename...> struct Expr;

template<> struct Expr<> {};
using Empty=Expr<>;
cex const Empty empty;

template<typename H>
struct Expr<H>:App {
  using Head=H;
  using Tail=Empty;
  const Head head;
  const Tail& tail;
  cex Expr(const Head& h):head(h),tail(empty) {}
};

template<typename H,typename... TT>
struct Expr<H,TT...>:App {
  using Head=H;
  using Tail=Expr<TT...>;
  const Head head;
  const Tail tail;
  cex Expr(const Head& h,const TT&... tt):head(h),tail(tt...) {}
  cex Expr(const Head& h,const Expr<TT...>& t):head(h),tail(t) {}
};

#ifdef YO_VERB
  template<typename Out> Out& operator<<(Out& out,const Empty& o) {return out<<"ø@"<<&o;}
  template<typename Out,typename... OO> Out& operator<<(Out& out,const Expr<OO...>& o) {return out<<"("<<o.head<<"@"<<&o.head<<" "<<o.tail<<")";}
#else
  template<typename Out> Out& operator<<(Out& out,const Empty& o) {return out;}
  template<typename Out,typename O,typename... OO> When<!isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...>& o) {return out<<o.head<<" "<<o.tail;}
  template<typename Out,typename O,typename... OO> When< isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...>& o) {return out<<"("<<o.head<<") "<<o.tail;}
#endif

template<typename... OO> cex const Expr<const OO&...> expr(const OO&... oo) {return {oo...};}

cex const int y=1967;
cex const auto a{expr(y)};
cex const auto b{expr(y,"ok")};
cex const auto c{expr(b,a,b)};

int main() {
  cout<<"start!"<<endl;
  cout<<&y<<endl;
  cout<<&empty<<endl;
  cout<<&expr(y).head<<endl;
  cout<<&expr(1).head<<endl;
  cout<<a<<endl;
  cout<<b<<endl;
  cout<<c<<endl;
  cout<<expr(1,c.tail)<<endl;
  cout<<"end."<<endl;
  return  0;
} 
