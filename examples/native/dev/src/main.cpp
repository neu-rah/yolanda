#include <iostream>
using namespace std;

#define cex constexpr

template<typename...> struct Expr;

template<> struct Expr<> {};
using Empty=Expr<>;
cex const Empty empty;

template<typename H,typename... TT>
struct Expr<H,TT...> {
  using Head=H;
  using Tail=Expr<TT...>;
  const Head head;
  const Tail tail;
  cex Expr(const H& h,const Tail& t):head(h),tail(t) {}
};

template<typename O>
struct A {
  const O a;
  // constexpr A(int a):a(a){}
  constexpr A(const O& a):a(a){}
  // constexpr A(const O&& a):a(a){}//because its const we do not need this
};

int main() {
  cout<<a.a<<endl;
  cout<<b.a<<endl;
  cout<<c.a<<endl;
  cout<<d.a<<endl;
  cout<<a.a<<endl;
  cout<<b.a<<endl;
  cout<<c.a<<endl;
  cout<<d.a<<endl;
  return 0;
}