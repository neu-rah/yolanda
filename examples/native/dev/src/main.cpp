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

template<typename T>
struct Data {
  using Type=T;
  const Type data;
  cex Data(const T& o):data(o) {}
  operator const Type&() const {return data;}
};

template<typename O> cex const Data<const O&> data(const O&  o) {return {o};}
template<typename O> cex const Data<const O>  data(const O&& o) {return {forward<const O>(o)};}

template<typename...> struct Expr;

template<> struct Expr<> {};
using Empty=Expr<>;
cex const Empty empty;

template<typename H>
struct Expr<H> {
  using Head=Data<H>;
  using Tail=Empty;
  const Head head;
  const Tail& tail;
  Expr(const H& h):head(h),tail(empty){}
};

// template<typename... OO> cex const Expr<OO...> expr(const OO&... oo) {return {oo...};}
// template<typename... OO> cex const Expr<OO...> expr(const OO&&... oo) {return {oo...};}
template<typename... OO> cex const Expr<OO...> expr(const OO... oo) {return {oo...};}

template<typename H,typename... TT>
struct Expr<H,TT...> {
  using Head=Data<H>;
  using Tail=Expr<TT...>;
  const Head head;
  const Tail tail;
  // Expr(const H&& h,const TT&&... tt):head(h),tail(expr(tt...)){}
  // Expr(const H& h,const TT&... tt):head(h),tail(expr(tt...)){}
  Expr(const H h,const TT... tt):head(h),tail(expr(tt...)){}
};

struct Test {};
template<typename Out> Out& operator<<(Out& out,const Test o) {return out<<"ŧ"<<&o;}

template<typename Out> Out& operator<<(Out& out,const Empty) {return out<<"ø";}
template<typename Out,typename... OO> Out& operator<<(Out& out,const Expr<OO...>& o) {return out<<o.head<<" "<<o.tail;}

cex const int y=1967;
cex const Test z{};

int main() {
  cout<<"start!"<<endl;
  cout<<&y<<endl;
  // cout<<&expr(y).head<<endl;
  cout<<expr(Test{})<<endl;
  cout<<&z<<"->";
  cout<<expr(z)<<endl;
  cout<<expr(1,2)<<endl;
  cout<<"end."<<endl;
  return  0;
} 
