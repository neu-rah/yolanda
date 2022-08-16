#pragma once

#include "curry.h"
#include "core.h"
#include "bool.h"
#include "data.h"

#ifndef YO_DEBUG
  namespace yo {
#endif
  using Succ=Expr<S,B>;
  constexpr const Succ succ;

  struct Add:Combinator<Add,2> {
    template<typename N,typename O>
    using Beta=typename N::template Bind<Succ>::template Bind<O>;
    template<typename N,typename O>
    static auto beta(const N&n,const O&o)
      ->decltype(n(std::forward<const Succ>(succ))(std::forward<const O>(o)))
      {return n(std::forward<const Succ>(succ))(std::forward<const O>(o));}
  };
  constexpr const Add add;

  struct Mul:B{};
  constexpr const Mul mul;

  struct Pow:T{};
  constexpr const Pow _pow;

  using N0=False;
  using N1=Id;//Succ::Bind<N0>;
  using N2=Succ::Bind<N1>;
  using N3=Succ::Bind<N2>;
  using N4=Succ::Bind<N3>;
  using N5=Succ::Bind<N4>;
  using N6=Succ::Bind<N5>;
  using N7=Succ::Bind<N6>;
  using N8=Succ::Bind<N7>;
  using N9=Succ::Bind<N8>;

  constexpr const N0 n0;
  constexpr const N1 n1;
  constexpr const N2 n2;
  constexpr const N3 n3;
  constexpr const N4 n4;
  constexpr const N5 n5;
  constexpr const N6 n6;
  constexpr const N7 n7;
  constexpr const N8 n8;
  constexpr const N9 n9;

  struct Is0:Combinator<Is0,1> {
    template<typename O> using Beta=Expr<O,Expr<True,False>,True>;
    template<typename O>
      static auto beta(const O&&o)
      ->decltype(o(_true(std::forward<const False>(_false)))(std::forward<const True>(_true)))
      {return o(_true(std::forward<const False>(_false)))(std::forward<const True>(_true));}
  };
  constexpr const Is0 is0;

  // template<typename P>
  // using _Phi=Expr<Pair,Expr<Snd,P>,Expr<Succ,Expr<Snd,P>>>;
  // using Phi=Curry<_Phi,1>;
  struct Phi:Combinator<Phi,1> {
    template<typename O>
    using Beta=Expr<Pair,Expr<Snd,O>,Expr<Succ,Expr<Snd,O>>>;
    template<typename O>
    static auto beta(const O&&o)
      ->decltype(_pair(snd(o))(succ(snd(o))))
      {return _pair(snd(std::forward<const O>(o)))(succ(snd(std::forward<const O>(o))));}
  };

  // template<typename N>
  // using _Pred=Expr<Fst,Expr<N,Phi,Expr<Pair,N0,N0>>>;
  // using Pred=Curry<_Pred,1>;
  struct Pred:Combinator<Pred,1> {
    template<typename N>
    using Beta=Expr<Fst,Expr<N,Phi,Expr<Pair,N0,N0>>>;
    template<typename N>
    static auto beta(const N&&n)
      ->decltype(fst(n(Phi())(Expr<Pair,N0,N0>())))
      {return fst(n(Phi())(Expr<Pair,N0,N0>()));}
  };
  constexpr const Pred pred;

  struct Sub:Combinator<Sub,2> {
    template<typename N,typename O>
    using Beta=Expr<O,Pred,N>;
    template<typename N,typename O>
    static auto beta(const N&&n, const O&&o)
      ->decltype(o(pred)(n))
      {return o(pred)(std::forward<const N>(n));}
  };
  constexpr const Sub sub;

  // template<typename N,typename K>
  // using _LEq=Expr<Is0,Expr<Sub,N,K>>;
  // using LEq=Curry<_LEq,2>;
  struct LEq:Combinator<LEq,2> {
    template<typename N,typename O>
    using Beta=Expr<Is0,Expr<Sub,N,O>>;
    template<typename N,typename O>
    static auto beta(const N&&n,const O&&o)
      ->decltype(is0(sub(n)(o)))
      {return is0(sub(std::forward<const N>(n))(std::forward<const O>(o)));}
  };
  constexpr const LEq leq;

  // using GEq=Flip::Bind<LEq>;//this is the functional negation, not the boolean one, it reverses the < signal but not the =
  struct GEq:Combinator<GEq,2> {
    template<typename N,typename O>
    using Beta=Expr<Is0,Expr<Sub,O,N>>;
    template<typename N,typename O>
    static auto beta(const N&&n,const O&&o)
      ->decltype(is0(sub(o)(n)))
      {return is0(sub(std::forward<const O>(o))(std::forward<const N>(n)));}
  };
  constexpr const GEq geq;

  using GT=Bb::Bind<Not>::Bind<LEq>;
  constexpr const GT gt;

  // template<typename N,typename K>
  // using _Eq=Expr<And,Expr<LEq,N,K>,Expr<LEq,K,N>>;
  // using Eq=Curry<_Eq,2>;
  struct Eq:Combinator<Eq,2> {
    template<typename N,typename O>
    using Beta=Expr<And,Expr<LEq,N,O>,Expr<LEq,O,N>>;
    template<typename N,typename O>
    static auto beta(const N&&n,const O&&o)
      ->decltype(_and(leq(n)(o))(leq(o)(n)))
      {return _and(leq(std::forward<const N>(n))(std::forward<const O>(o)))(leq(std::forward<const O>(o))(std::forward<const N>(n)));}
  };
  constexpr const Eq eq;

  using LT=Flip::Bind<GT>;
  constexpr const LT lt;

  // template<typename N,typename K>
  // using _NEq=Expr<Or,Expr<GT,N,K>,Expr<GT,K,N>>;
  // using NEq=Curry<_NEq,2>
  struct NEq {
    template<typename N,typename O>
    using Beta=Expr<Or,Expr<GT,N,O>,Expr<GT,O,N>>;
    template<typename N,typename O>
    static auto beta(const N&&n,const O&&o)
      ->decltype(_or(gt(n)(o))(gt(o)(n)))
      {return _or(gt(std::forward<const N>(n))(std::forward<const O>(o)))(gt(std::forward<const O>(o))(std::forward<const N>(n)));}
  };
  constexpr const NEq neq;
  
  ///////////////////////////////////////////////////////////////////////////////
  // convert to int
  static int _plus1(int n){return n+1;}
  Curry<decltype(&_plus1),&_plus1> plus1;

  // template<typename N>
  // int _toInt(const N&n) {return n(std::forward<const decltype(plus1)>(plus1))(0).template runTo<int>();}
  template<typename N>
  int _toInt(const N&&n) {return n(std::forward<const decltype(plus1)>(plus1))(0).template runTo<int>();}
  template<typename N> Int toInt(const N&n) {return Int(_toInt<N> (std::forward<const N>(n)));}
  template<typename N> Int toInt(const N&&n) {return Int(_toInt<N>(std::forward<const N>(n)));}
#ifndef YO_DEBUG
  };
#endif
