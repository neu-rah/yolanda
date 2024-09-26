#include <iostream>
#include <type_traits>
using namespace std;

// #define cex
#define cex constexpr

template<bool chk, typename T> using When=typename enable_if<chk,T>::type;

template<typename...> struct Expr;

template<> struct Expr<> {
  template<typename O> cex const Expr<O> operator()(const O& o) {return {o};}
};
using Empty=Expr<>;
cex const Empty empty;

template<typename O> constexpr bool isEmpty() {return is_same<O,Empty>::value;}

template<typename H>
struct Expr<H> {
  using Head=H;
  using Tail=Empty;
  const Head& head;
  const Empty& tail;
  cex Expr(const H& h):head(h),tail(empty) {}
  template<typename O> cex const Expr<H,O> operator()(const O& o) {return {head,o};}
};

template<typename H,typename T, typename... TT>
struct Expr<H,T,TT...> {
  using Head=H;
  using Tail=Expr<T,TT...>;
  const Head& head;
  const Tail tail;
  cex Expr(const H& h,const T& t,const TT&... tt):head(h),tail(t,tt...) {}
  cex Expr(const H& h,const Expr<T,TT...>& t):head(h),tail(t) {}
  template<typename O> cex Expr<O,H,T,TT...> cons(const O o) const {return {o,*this};}
  template<typename O> cex const Expr<H,T,TT...,O> operator()(const O& o) {return tail(o).cons(head);}
};

template<typename... OO> cex const Expr<OO...> expr(const OO&... oo) {return {oo...};}

template<typename Out> Out& operator<<(Out& out,const Empty&) {return out<<"ø";}
template<typename Out,typename O> Out& operator<<(Out& out,const Expr<O>& o) {return out<<o.head;}
template<typename Out,typename O,typename... OO> Out& operator<<(Out& out,const Expr<O,OO...>& o) {return out<<o.head<<" "<<o.tail;}

cex const int d=11;
cex const int y=1967;
cex const char* n="rui";
cex const Expr<char const*,const int> x(n,y);

int main() {
  cout<<"----------------"<<endl;
  cout<<"x:"<<x<<endl;
  cout<<x.cons(11)<<endl;
  cout<<x(11)<<endl;
  cout<<expr(1,2,3,"Ok")<<endl;
  cout<<"end"<<endl;
  return 0;
}