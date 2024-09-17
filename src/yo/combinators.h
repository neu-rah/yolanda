#pragma once

#include "lambda.h"

namespace yo {
  // λo.o
  struct I:Combinator<I> {
    using Combinator::beta;
    template<typename O> static cex const O beta(const O o) {return o;}
  };

  // λab.a
  struct K:Combinator<K> {
    using Combinator::beta;
    template<typename O,typename P> static cex const O beta(const O o,const P p) {return o;}
  };

  // λfgo.fo(go)
  struct S:Combinator<S> {
    using Combinator::beta;
    template<typename F,typename G,typename O>
    static cex auto beta(const F f,const G g,const O o)
      ->const decltype(f(o)(g(o)))
      {return          f(o)(g(o));}
  };

  // λfgo.f(go)
  struct B:Combinator<B> {
    using Combinator::beta;
    template<typename F,typename G,typename O>
    static cex auto beta(const F f,const G g, const O o)
      ->decltype(f(g(o)))
      {return    f(g(o));}
  };

  // λfab.fba
  struct C:Combinator<C> {
    using Combinator::beta;
    template<typename F,typename A,typename B>
    static cex auto beta(const F f,const A a, const B b)->decltype(f(b)(a)) {return f(b)(a);}
  };

  // λop.opp
  struct W:Combinator<W> {
    using Combinator::beta;
    template<typename O,typename P>
    static cex auto beta(const O o,const P p)->decltype(o(p)(p)) {return o(p)(p);}
  };

  struct T:Combinator<T> {
    using Combinator::beta;
    template<typename O,typename F>
    static cex auto beta(const O o,const F f)->decltype(f(o)) {return f(o);}
  };

  struct V:Combinator<V> {
    using Combinator::beta;
    template<typename O,typename P,typename F>
    static cex auto beta(const O o,const P p,const F f)->decltype(f(o)(p)) {return f(o)(p);}
  };

  struct M:Combinator<M> {
    using Combinator::beta;
    template<typename F>
    static cex auto beta(const F f)->decltype(f(f)) {return f(f);}
  };

  cex const I _I;
  cex const K _K;
  cex const S _S;
  cex const B _B;
  cex const C _C;
  cex const W _W;
  cex const T _T;
  cex const V _V;
  cex const M _M;

  using Id=Alt<I>;
  using Const=Alt<K>;
  using KI=Expr<K,I>;
  using Flip=Alt<C>;
  using Pair=Alt<V>;
  using L=Expr<C,B,M>;
  using Y=Expr<S,L,L>;
  using Bb=Expr<B,B,B>;
  using Fst=Expr<T,K>;
  using Snd=Expr<T,KI>;

  cex const Id id;
  cex const Const _const;
  cex const KI _KI;
  cex const Flip flip;
  cex const Pair _pair;
  cex const L _L;
  cex const Y _Y;
  cex const Bb _Bb;
  cex const Fst fst;
  cex const Snd snd;

};