#pragma once

#include "lambda.h"

//// combinators
template<typename Fn>
struct Combinator:Lambda {
  template<typename O> cex Expr<Fn,O> operator()(const O o) const {return {*(Fn*)this,o};}
};

// λo.o
struct I:Combinator<I> {
  template<typename O> static cex const O beta(const O o) {return o;}
};
cex const I id;
template<typename Out> Out& operator<<(Out& out, const I) {return out<<"id";}

// λab.a
struct K:Combinator<K> {
  template<typename O,typename P> static cex const O beta(const O o,const P) {return o;}
};
cex const K _true;
template<typename Out> Out& operator<<(Out& out, const K) {return out<<"true";}

// λfgo.fo(go)
struct S:Combinator<S> {
  template<typename F,typename G,typename O> static cex auto beta(const F f,const G g, const O o)->const decltype(f(o)(g(o))) {return f(o)(g(o));}
};
cex const S _S;
template<typename Out> Out& operator<<(Out& out, const S) {return out<<"S";}

// λfgo.f(go)
struct B:Combinator<B> {
  template<typename F,typename G,typename O> static cex auto beta(const F f,const G g, const O o)->const decltype(f(g(o))) {return f(g(o));}
};
cex const B _B;
template<typename Out> Out& operator<<(Out& out, const B) {return out<<"B";}

// λfab.fba
struct C:Combinator<C> {
  template<typename F,typename A,typename B> static cex auto beta(const F f,const A a, const B b)->const decltype(f(b)(a)) {return f(b)(a);}
};
cex const C _C;
template<typename Out> Out& operator<<(Out& out, const C) {return out<<"C";}

// λop.opp
struct W:Combinator<W> {
  template<typename O,typename P> static cex auto beta(const O o,const P p)->decltype(o(p)(p)) {return o(p)(p);}
};
cex const W _W;
template<typename Out> Out& operator<<(Out& out, const W) {return out<<"W";}

// λof.fo
struct T:Combinator<T> {
  template<typename O,typename F>
  static cex auto beta(const O o,const F f)->decltype(f(o)) {return f(o);}
};
cex const T _T;
template<typename Out> Out& operator<<(Out& out, const T) {return out<<"T";}

// λabf.fab
struct V:Combinator<V> {
  template<typename O,typename P,typename F>
  static cex auto beta(const O o,const P p,const F f)->decltype(f(o)(p)) {return f(o)(p);}
};
cex const V _V;
template<typename Out> Out& operator<<(Out& out, const V) {return out<<"V";}

// λo.oo
struct M:Combinator<M> {
  template<typename F>
  static cex auto beta(const F f)->decltype(f(f)) {return f(f);}
};
cex const M _M;
template<typename Out> Out& operator<<(Out& out, const M) {return out<<"M";}

using L=decltype(_C(_B)(_M));//Expr<C,B,M>;
cex const L _L;
template<typename Out> Out& operator<<(Out& out, const L) {return out<<"L";}

using Y=decltype(_S(_L)(_L));//Expr<S,L,L>;
cex const Y _Y;
template<typename Out> Out& operator<<(Out& out, const Y) {return out<<"Y";}

using Bb=decltype(_B(_B)(_B));//Expr<B,B,B>;
cex const Bb _Bb;
template<typename Out> Out& operator<<(Out& out, const Bb) {return out<<"Bb";}

