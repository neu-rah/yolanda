#pragma once

#include "lambda.h"

namespace yo {
  struct I:Combinator<I,1> {
    template<typename O> static O beta(const O o) {return o;}
    template<typename... OO> using Beta=decltype(beta<OO...>(OO{}...));
    // template<typename O> auto operator()(const O o) const->decltype(beta(o)) {return beta(o);}
  };

  struct K:Combinator<K,2> {
    template<typename O,typename P> static O beta(const O o,const P) {return o;}
    template<typename... OO> using Beta=decltype(beta<OO...>(OO{}...));
  };

  struct S:Combinator<S,3> {
    template<typename F,typename G,typename O> 
    static auto beta(const F f,const G g,const O o)->decltype(f(o)(g(o))) {return f(o)(g(o));}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };

  struct B:Combinator<B,3> {
    template<typename F,typename G,typename O>
    static auto beta(const F f,const G g, const O o)->decltype(f(g(o))) {return f(g(o));}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };

  struct C:Combinator<C,3> {
    template<typename F,typename A,typename B>
    static auto beta(const F f,const A a, const B b)->decltype(f(b)(a)) {return f(b)(a);}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };

  struct W:Combinator<W,2> {
    template<typename O,typename P>
    static auto beta(const O o,const P p)->decltype(o(p)(p)) {return o(p)(p);}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };

  struct T:Combinator<T,2> {
    template<typename O,typename F>
    static auto beta(const O o,const F f)->decltype(f(o)) {return f(o);}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };

  struct V:Combinator<V,3> {
    template<typename O,typename P,typename F>
    static auto beta(const O o,const P p,const F f)->decltype(f(o)(p)) {return f(o)(p);}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };

  struct M:Combinator<M,1> {
    template<typename F>
    static auto beta(const F f)->decltype(f(f)) {return f(f);}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };

  using Id=Alt<I>;
  using KI=K::Bind<I>;
  using Flip=Alt<C>;
  using Pair=Alt<V>;
  using L=Expr<C,B,M>;
  using Y=Expr<S,L,L>;
  using Bb=Expr<B,B,B>;
  using Fst=Expr<T,K>;
  using Snd=Expr<T,KI>;

  constexpr const I id;
  constexpr const S _S;
  constexpr const B _B;
  constexpr const Flip flip;
  constexpr const W _W;
  constexpr const T _T;
  constexpr const V _V;
  constexpr const Pair _pair;
  const Fst fst;
  const Snd snd;
};