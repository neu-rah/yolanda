#include <iostream>
#include <type_traits>
using namespace std;

// #define cex
#define cex constexpr

template<bool chk, typename T> using When=typename enable_if<chk,T>::type;

struct None {};
struct App {};

template<typename...> struct Expr;

template<> struct Expr<> {
  cex Expr() {}
  template<typename O> cex const Expr<O> operator()(const O& o) {return {o};}
};
using Empty=Expr<>;
cex const Empty empty;

template<typename O> constexpr bool isEmpty() {return is_same<O,Empty>::value;}
template<typename O> constexpr bool isApp() {return is_convertible<O,App>::value;}

template<typename H>
struct Expr<H>:App {
  using Head=H;
  using Tail=Empty;
  const Head& head;
  const Empty& tail;
  cex Expr(const H& h):head(h),tail(empty) {}
  template<typename O> cex const Expr<H,O> operator()(const O& o) {return {head,o};}
};

template<typename H,typename T, typename... TT>
struct Expr<H,T,TT...>:App {
  using Head=H;
  using Tail=Expr<T,TT...>;
  const Head& head;
  const Tail tail;
  cex Expr(const H& h,const T& t,const TT&... tt):head(h),tail(t,tt...) {}
  cex Expr(const H& h,const Expr<T,TT...>& t):head(h),tail(t) {}
  template<typename O> cex const Expr<O,H,T,TT...> cons(const O o) const {return {o,*this};}
  template<typename O> cex const Expr<H,T,TT...,O> operator()(const O& o) {return tail(o).cons(head);}
};

template<typename... OO> cex const Expr<OO...> expr(const OO&... oo) {return {oo...};}

template<typename Out> Out& operator<<(Out& out,const Empty&) {return out<<"ø";}
template<typename Out,typename O> Out& operator<<(Out& out,const Expr<O>& o) {return out<<o.head;}
template<typename Out,typename O,typename... OO> Out& operator<<(Out& out,const Expr<O,OO...>& o) {return out<<o.head<<" "<<o.tail;}
// template<typename Out,typename O,typename... OO> When<!isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...>& o) {return out<<o.head<<" "<<o.tail;}
// template<typename Out,typename O,typename... OO> When< isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...>& o) {return out<<"("<<o.head<<") "<<o.tail;}

template<typename Fn>
struct Combinator {
  template<typename O> cex const Expr<Fn,O> operator()(const O& o) {return {*(Fn*)this,o};}
};

struct I:Combinator<I> {
  template<typename O> cex const O& beta(const O& o) {return o;}
};
cex const I _I;
template<typename Out> Out& operator<<(Out& out,const I&) {return out<<"I";}

struct K:Combinator<K> {
  template<typename O,typename P> cex const O& beta(const O& o,const P&) {return o;}
};
cex const K _K;
template<typename Out> Out& operator<<(Out& out,const K&) {return out<<"K";}

struct S:Combinator<S> {
  template<typename F,typename G,typename O> cex auto beta(const F& f,const G& g,const O& o)->const decltype(f(o)(g(o))) {return f(o)(g(o));}
};
cex const S _S;
template<typename Out> Out& operator<<(Out& out,const S&) {return out<<"S";}

/////////////////////////////////////////////////////////
int main() {
  static cex const int a=1;
  static cex const int b=2;
  static cex const int c=3;
  static cex const int d=4;
  static cex const auto e1=expr(a,b);
  static cex const auto e2=expr(c,d);

  // const auto r=_S.beta(_I,_I,_I);
  // cout<<_S<<"->"<<r.head<<"+"<<r.tail.head<<"+"<<r.tail.tail<<endl;
  cout<<expr(1,2)<<endl;
  cout<<e1<<endl;
  cout<<e1<<"+"<<e2<<"="<<e1(e2)<<endl;
  cout<<"end"<<endl;
  return 0;
}