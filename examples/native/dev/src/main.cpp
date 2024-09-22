// #include <avr_std.h>
// using namespace avr_std;

#include <iostream>
#include <type_traits>
using namespace std;

#define cex constexpr

template<typename F,typename S>
struct Pair {
  using Fst=F;
  using Snd=S;
  const Fst fst;
  const Snd snd;
  cex Pair(const Fst f,const Snd s):fst(f),snd(s){}
};

template<typename F,typename S>
cex const Pair<F,S> _pair(const F f,const S s) {return {f,s};}

template<typename Out,typename F,typename S>
Out& operator<<(Out& out,const Pair<F,S> o) {return out<<"[@"<<&o<<"{"<<&o.fst<<"|"<<sizeof(o.fst)<<"}"<<o.fst<<" "<<o.snd<<"]"<<endl;}

int main() {
  cout<<"yolanda/refs"<<endl;
  const auto a=_pair("Rui Azevedo",1967);
  cout<<_pair(a,a)<<endl;
  return 0;
}