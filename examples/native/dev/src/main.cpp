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

#include <yolanda.h>

// λo.o
// struct I:Combinator<I> {
//   template<typename O> static cex const O& beta(const O& o) {return o;}
// };
// cex const I _I;
// template<typename Out> Out& operator<<(Out& out,const I&) {return out<<"I";}

// // λab.a
// struct K:Combinator<K> {
//   template<typename O,typename P> static cex const O& beta(const O& o,const P&) {return o;}
// };
// cex const K _K;
// template<typename Out> Out& operator<<(Out& out,const K&) {return out<<"K";}

// // λfgo.fo(go)
// struct S:Combinator<S> {
//   template<typename F,typename G,typename O> static cex auto beta(const F& f,const G& g,const O& o)->const decltype(f(o)(g(o))) {return f(o)(g(o));}
// };
// cex const S _S;
// template<typename Out> Out& operator<<(Out& out,const S&) {return out<<"S";}

// // λfab.fba
// // using C=decltype( (_S( (_S (_K( (_S(_K(_S))) (_K)) ))(_S) )) (_K(_K)) );
// struct C:Combinator<C> {
//   template<typename F,typename A,typename B> static cex auto beta(const F& f,const A& a,const B& b)->const decltype(f(b)(a)) {return f(b)(a);}
// };
// cex const C _C;
// template<typename Out> Out& operator<<(Out& out,const C&) {return out<<"C";}

// // λabc.a(bc)
// //using B=decltype((_S(_K(_S)))(_K));
// struct B:Combinator<B> {
//   template<typename F,typename A,typename B> static cex auto beta(const F& f,const A& a,const B& b)->const decltype(f(b(a))) {return f(b(a));}
// };
// cex const B _B;
// template<typename Out> Out& operator<<(Out& out,const B&) {return out<<"B";}

// // λf.ff
// // ((S((SK)K))((SK)K))
// struct M:Combinator<M> {
//   template<typename F> static cex auto beta(const F& f)->const decltype(f(f)) {return f(f);}
// };
// cex const M _M;
// template<typename Out> Out& operator<<(Out& out,const M&) {return out<<"M";}

//// test ///////////////////////////////////////////////////////////////
template<typename E> void show(const E e) {cout<<e<<endl;}
template<typename E> void show(const E e,const E) {cout<<e<<" -> irreducible."<<endl;}
template<typename E,typename R> void show(const E e,const R r) {cout<<e<<" = "<<r<<endl;}

template<typename E,typename R> void test(const E e,const R r) {show(e,r);}
template<typename E> void test(const E e) {show(e,beta(e));}

void steps(const None) {cout<<none<<endl;}
template<typename O> void steps(const O o) {
  cout<<o<<endl<<" = ";
  steps(step(o));
}

/////////////////////////////////////////////////////////
int main() {
  // cout<<_concat(expr(1,2),3)<<endl;
  // test(_I("ok")("zZz"));
  // steps(_S(_I)(_I)(_I)("ok")("x"));
  steps(_C(_K)("fail")("ok"));
  cout<<"end"<<endl;
  return 0;
}