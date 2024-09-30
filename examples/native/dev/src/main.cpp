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

template<typename O> constexpr bool isApp() {return is_convertible<O,App>::value;}

template<typename...> struct Expr;

template<> struct Expr<>{};
using Empty=Expr<>;
cex const Empty empty;

//termination--
template<typename H>
struct Expr<H>{
  using This=Expr<H>;
  using Head=H;
  using Tail=Empty;
  const Head& head;
  const Tail& tail;
  cex Expr(const Head& h):head(h),tail(::empty){}
  cex Expr(const Head& h,const Empty& o):head(h),tail(o){}
  template<typename O> cex const Expr<O,const This> cons(const O& o) const {return {o,*this};}
};

//continuity--
template<typename H,typename T>
struct Expr<H,Expr<T>>{
  using This=Expr<H,Expr<T>>;
  using Head=H;
  using Tail=T;
  const Head& head;
  const Tail& tail;
  cex Expr(const Head& h,const T& t):head(h),tail(t){}
  template<typename O> cex const Expr<O,const This> cons(const O& o) const {return {o,*this};}
};

//expression
template<typename H,typename... TT>
struct Expr<H,TT...>{
  using This=Expr<H,TT...>;
  using Head=H;
  using Tail=Expr<TT...>;
  const Head& head;
  const Tail tail;
  cex Expr(const Head& h,const TT&... t):head(h),tail(t...){}
  template<typename O> cex const Expr<O,const This> cons(const O& o) const {return {o,*this};}
};

cex const Empty& expr() {return ::empty;}
template<typename O> cex const Expr<const O> expr(const O& o) {return {o};}
template<typename O, typename... OO> cex auto expr(const O& o,const OO&... tt)->const Expr<O,decltype(expr(tt...))> {return {o,expr(tt...)};}

#ifdef YO_VERB
  template<typename Out> Out& operator<<(Out& out,const Empty& o) {return out<<"ø@"<<&o;}
  template<typename Out,typename O,typename... OO> When<!isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...> &o) {return out<<"("<<&o<<":"<<o.head<<"@"<<&o.head<<" "<<o.tail<<")";}
  template<typename Out,typename O,typename... OO> When< isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...> &o) {return out<<"["<<&o<<":("<<o.head<<"@"<<&o.head<<") "<<o.tail<<"]";}
#else
  template<typename Out> Out& operator<<(Out& out,const Empty&) {return out<<"ø";}
  template<typename Out,typename O,typename... OO> When<!isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...> &o) {return out<<o.head<<" "<<o.tail;}
  template<typename Out,typename O,typename... OO> When< isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...> &o) {return out<<"("<<o.head<<") "<<o.tail;}
#endif

cex const char*n="rui";
cex const int y=1967;
cex const auto a{expr(n)};
cex const auto b{a.cons(y)};
cex const auto c{b.cons("ok")};

int main() {
  cout<<"start!"<<endl;
  cout<<a<<endl;
  cout<<b<<endl;
  cout<<c<<endl;
  cout<<"end."<<endl;
  return  0;
} 
