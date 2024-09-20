#ifdef ARDUINO
  #include <Arduino.h>
  #include <streamFlow.h>
  using namespace StreamFlow;
  #define cout Serial
  #define endl "\n"
  #include <avr_std.h>
  using namespace avr_std;
#else
  #include <iostream>
  using namespace std;
#endif

// #defuine cex
#define cex constexpr

template<typename...> struct Expr;

template<bool chk,typename T=void> using When=typename enable_if<chk,T>::type;

template<> struct Expr<> {
  template<typename O> cex const Expr<O> operator()(const O o) const {return {o};}
  template<typename O> cex const Expr<O> cons(const O o) const {return {o};}
};
using Empty=Expr<>;
cex const Empty empty;

template<typename O> constexpr bool isEmpty() {return is_same<O,Empty>::value;}

template<typename H>
struct Expr<H> {
  using Head=H;
  using Tail=Empty;
  const Head head;
  const Tail tail;
  cex Expr(const H o):head(o),tail(empty){}
  template<typename O> cex const Expr<H,O> operator()(const O o) const {return {head,empty(o)};}
  template<typename O> cex auto cons(const O o) const->const Expr<O,H> {return {o,head};}
};

template<typename H,typename... TT>
struct Expr<H,TT...> {
  using Head=H;
  using Tail=Expr<TT...>;
  const Head head;
  const Tail tail;
  cex Expr(const H o,const TT... oo,When<!isEmpty<Expr<TT...>>(),int> = 0):head(o),tail(oo...){}
  cex Expr(const H o,const Expr<TT...> p,When<!isEmpty<Expr<TT...>>(),int> = 0):head(o),tail(&p){}
  template<typename O> cex const Expr<H,TT...,O> operator()(const O o) const {return {head,tail(o)};}
  template<typename O> cex auto cons(const O o) const->const Expr<O,H,TT...> {return {o,this};}
};

template<typename Out> Out& operator<<(Out& out,const Empty o) {return out<<"["<<(unsigned int)&o<<"]";}
template<typename Out,typename... OO> Out& operator<<(Out& out,const Expr<OO...> o) {return out<<"("<<(unsigned int)&o.head<<"|"<<o.head<<":"<<o.tail<<")";}

int main() {
  #ifdef ARDUINO
  Serial.begin(115200);
  #endif
  cout<<"============"<<endl;
  cout<<empty<<endl;
  auto e1=empty("sem outro assunto");
  cout<<e1<<endl;
  cout<<e1.cons("fail")<<endl;
  return  0;
} 