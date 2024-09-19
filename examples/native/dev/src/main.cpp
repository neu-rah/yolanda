#include <iostream>
using namespace std;

#define cex constexpr

template<typename...> struct Expr;

template<> struct Expr<> {
  template<typename O> cex auto operator()(const O o) const->const O {return o;}
};
using Empty=Expr<>;
cex const Empty empty;

template<typename H,typename... TT>
struct Expr<H,TT...> {
  using Head=H;
  using Tail=Expr<TT...>;
  Head head;
  Tail tail;
  cex Expr(const H o,const TT... oo):head(o),tail(oo...){}
  cex Expr(const H o,const Expr<TT...> p):head(o),tail(p){}
  template<typename O> cex auto operator()(const O o) const->const Expr<H,decltype(tail(o))> {return {head,tail(o)};}
};

template<typename Out> Out& operator<<(Out& out,const Empty) {return out<<"[]";}
template<typename Out,typename... OO> Out& operator<<(Out& out,const Expr<OO...> o) {return out<<"("<<o.head<<":"<<o.tail<<")";}

int main() {
  cout<<Expr<int,int>{1,2}<<endl;
  cout<<Expr<int>{1}(2)(3)(4)<<endl;
  return  0;
}