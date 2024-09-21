#include <iostream>
using namespace std;

template<typename... OO> struct Expr;

template<> struct Expr<> {};

template<typename H, typename... TT>
struct Expr<H,TT...> {
  using Head=H;
  using Tail=Expr<TT...>;
  const Head head;
  const Tail& tail;
};

template<typename Out,typename H,typename... TT>
Out& operator<<(Out& out,const Expr<H,TT...> o) {return out<<o.head<<" "<<o.tail;}

int main() {
  cout<<"yolanda/refs"<<endl;
  Expr<int,int> a{1,2};
  cout<<a<<endl;
  return 0;
}