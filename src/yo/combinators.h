#pragma once

#include "lambda.h"

//esp32 bad macros
#undef _L
#undef _S
#undef _C
#undef _B

namespace yo {
  // λo.o
  struct I:Combinator<I> {template<typename O> static cex const O beta(const O o) {return o;}};

  // λab.a
  struct K:Combinator<K> {template<typename O,typename P> static cex const O beta(const O o,const P p) {return o;}};

  // λfgo.fo(go)
  struct S:Combinator<S> {
    template<typename F,typename G,typename O>
    static cex auto beta(const F f,const G g,const O o)
      ->const decltype(f(o)(g(o)))
      {return          f(o)(g(o));}
  };

  // λfgo.f(go)
  struct B:Combinator<B> {
    template<typename F,typename G,typename O>
    static cex auto beta(const F f,const G g, const O o)
      ->decltype(f(g(o)))
      {return    f(g(o));}
  };

  // λfab.fba
  struct C:Combinator<C> {
    template<typename F,typename A,typename B>
    static cex auto beta(const F f,const A a, const B b)->decltype(f(b)(a)) {return f(b)(a);}
  };

  // λop.opp
  struct W:Combinator<W> {
    template<typename O,typename P>
    static cex auto beta(const O o,const P p)->decltype(o(p)(p)) {return o(p)(p);}
  };

  // λof.fo
  struct T:Combinator<T> {
    template<typename O,typename F>
    static cex auto beta(const O o,const F f)->decltype(f(o)) {return f(o);}
  };

  // λabf.fab
  struct V:Combinator<V> {
    template<typename O,typename P,typename F>
    static cex auto beta(const O o,const P p,const F f)->decltype(f(o)(p)) {return f(o)(p);}
  };

  // λf.ff
  struct M:Combinator<M> {
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
  using KI=decltype(_K(_I));//Expr<K,I>;
  cex const KI _KI;
  using Flip=Alt<C>;
  using Pair=Alt<V>;
  using L=decltype(_C(_B)(_M));//Expr<C,B,M>;
  cex const L _L;
  using Y=decltype(_S(_L)(_L));//Expr<S,L,L>;
  using Bb=decltype(_B(_B)(_B));//Expr<B,B,B>;
  using Fst=decltype(_T(_K));//Expr<T,K>;
  using Snd=decltype(_T(_KI));//Expr<T,KI>;

  cex const Id id;
  cex const Const _const;
  cex const Flip flip;
  cex const Pair _pair;
  cex const Y _Y;
  cex const Bb _Bb;
  cex const Fst fst;
  cex const Snd snd;

};