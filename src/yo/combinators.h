#pragma once

#include "SKI.h"
#include "binder.h"

#ifndef YO_DEBUG
  namespace yo {
#endif
  // using B=Expr<S,Expr<K,S>,K>;
  struct B:Combinator<B,3> {
    template<typename F,typename G,typename O> 
    using Beta=typename F::template Bind<typename G::template Bind<O>>;
    // template<typename F,typename G,typename O>
    // static auto beta(const F&f,const G&g,const O&o)
    //   ->decltype(f(g(o)))
    //   {return f(g(std::forward<const O>(o)));}
    template<typename F,typename G,typename O>
    static auto beta(const F&&f,const G&&g,const O&&o)
      ->decltype(f(g(std::forward<const O>(o))))
      {return f(g(std::forward<const O>(o)));}
  };
  // using C=Expr<S,Expr<B,B,S>,Expr<K,K>>;
  struct C:Combinator<C,3> {
    template<typename F,typename A,typename B> 
    using Beta=typename F::template Bind<B>::template Bind<A>;
    template<typename F,typename A,typename B>
    static auto beta(const F&&f,const A&&a,const B&&b)
      ->decltype(f(std::forward<const B>(b))(std::forward<const A>(a)))
      {return f(std::forward<const B>(b))(std::forward<const A>(a));}
  };
  // using M=Expr<S,I,I>;
  struct M:Combinator<M,1> {
    template<typename F> using Beta=typename F::template Bind<F>;
    // template<typename F>
    // static auto beta(const F&f)
    //   ->decltype(f(f))
    //   {return f(std::forward<const F>(f));}
    template<typename F>
    static auto beta(const F&&f)
      ->decltype(f(std::forward<const F>(f)))
      {return f(std::forward<const F>(f));}
  };
  using L=Expr<C,B,M>;
  // struct L:Combinator<L,2> {
  //   template<typename F,typename G> 
  //   using Beta=typename F::template Bind<typename G::template Bind<G>>;
  //   template<typename F,typename G>
  //   static auto beta(const F&f,const G&g)
  //     ->decltype(f(g(g)))
  //     {return f(g(g));}
  // };
  using Y=Expr<S,L,L>;
  // struct Y:Combinator<Y,1> {
  //   template<typename... OO> auto beta(const OO&... oo) const->const decltype(operator()(oo...)) {return operator()(oo...);}
  //   template<typename O> static auto beta(const O& o)->decltype(L()(o)(L()(o))) {return L()(o)(L()(o));}
  //   template<typename O,typename... OO> auto beta(const O& o,const OO&... oo) const->decltype(beta(o).beta(oo...)) {return beta(o).beta(oo...);}
  // };
  // using T=Expr<C,I>;
  struct T:Combinator<T,2> {
    template<typename O,typename F> 
    using Beta=typename F::template Bind<O>;
    template<typename O,typename F>
    static auto beta(const O&&o,const F&&f)
      ->decltype(f(o))
      {return f(std::forward<const O>(o));}
  };
  // using V=Expr<B,C,T>;
  struct V:Combinator<V,3> {
    template<typename A,typename B,typename F> 
    using Beta=typename F::template Bind<A>::template Bind<B>;
    template<typename A,typename B,typename F>
    static auto beta(const A&&a,const B&&b,const F&&f)
      ->decltype(f(std::forward<const A>(a))(std::forward<const B>(b)))
      {return f(std::forward<const A>(a))(std::forward<const B>(b));}
  };
  // using R=Expr<B,B,T>;
  // struct R:Combinator<R,3> {
  //   template<typename A,typename B,typename C> 
  //   using Beta=typename B::template Bind<C>::template Bind<A>;
  //   template<typename A,typename B,typename C>
  //   static auto beta(const A&a,const B&b,const C&c)
  //     ->decltype(b(c)(a))
  //     {return b(c)(a);}
  // };
  using Bb=Expr<B,B,B>;

  using Id=I;//just an alias
  constexpr const Id id;
#ifndef YO_DEBUG
  };
#endif
