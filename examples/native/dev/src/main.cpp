// #include <avr_std.h>
// using namespace avr_std;

#include <iostream>
#include <type_traits>
using namespace std;

#define cex constexpr

template<typename F,typename S>
struct Pair {
  using Fst=const F&;
  using Snd=const S&;
  Fst fst;
  Snd snd;
  cex Pair(Fst f,Snd s):fst(f),snd(s){}
};

template<typename F,typename S>
cex const Pair<F,S> _pair(F& f,S& s) {return {f,s};}

template<typename Out,typename F,typename S>
Out& operator<<(Out& out,const Pair<F,S> o) {return out<<o.fst<<" "<<o.snd;}

int main() {
  cout<<"yolanda/refs"<<endl;
  auto f="Rui Azevedo";
  auto s=1967;
  auto a=_pair(f,s);
  auto p=_pair(a,a);
  cout<<&p.fst<<" "<<&p.snd<<endl;
  cout<<&p.fst.fst<<" "<<&p.fst.snd<<endl<<&p.snd.fst<<" "<<&p.snd.snd<<endl;
  p.snd.snd=11;
  cout<<&p.fst.fst<<" "<<&p.fst.snd<<endl<<&p.snd.fst<<" "<<&p.snd.snd<<endl;
  cout<<s<<endl;
  return 0;
}