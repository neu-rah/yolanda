#pragma once

#include "combinators.h"
#include "curry.h"
#include "bool.h"

namespace yo {
  // peano ----------------------------------------------
  using Succ=S::Bind<B>;//Expr<S,B>;
  const Succ succ;

  struct Add:Combinator<Add,2> {
    template<typename N,typename O>
    static auto beta(const N n,const O o)
      ->decltype(n(succ)(o))
      {return n(succ)(o);}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  constexpr const Add add;

  struct Mul:B{};
  constexpr const Mul mul;

  struct Pow:T{};
  constexpr const Pow _pow;

  using N0=Alt<False>;
  using N1=Alt<Id>;//Succ::Bind<N0>;
  using N2=Succ::Bind<N1>;
  using N3=Succ::Bind<N2>;
  using N4=Succ::Bind<N3>;
  using N5=Succ::Bind<N4>;
  using N6=Succ::Bind<N5>;
  using N7=Succ::Bind<N6>;
  using N8=Succ::Bind<N7>;
  using N9=Succ::Bind<N8>;

  extern const N0 n0;
  extern const N1 n1;
  extern const N2 n2;
  extern const N3 n3;
  extern const N4 n4;
  extern const N5 n5;
  extern const N6 n6;
  extern const N7 n7;
  extern const N8 n8;
  extern const N9 n9;

  struct Is0:Combinator<Is0,1> {
    template<typename O>
    static auto beta(const O o)
      ->decltype(o(_true(_false))(_true))
      {return o(_true(_false))(_true);}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  constexpr const Is0 is0;

  struct Phi:Combinator<Phi,1> {
    template<typename O>
    static auto beta(const O o)
      ->decltype(_pair(snd(o))(succ(snd(o))))
      {return _pair(snd(o))(succ(snd(o)));}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };

  struct Pred:Combinator<Pred,1> {
    using N0N0=Pair::Bind<N0>::Bind<N0>;
    template<typename N>
    static auto beta(const N n)
      ->decltype(fst(n(Phi())(N0N0{})))
      {return fst(n(Phi())(N0N0{}));}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  constexpr const Pred pred;

  struct Sub:Combinator<Sub,2> {
    template<typename N,typename O>
    static auto beta(const N n, const O o)
      ->decltype(o(pred)(n))
      {return o(pred)(n);}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  constexpr const Sub sub;

  struct LEq:Combinator<LEq,2> {
    template<typename N,typename O>
    static auto beta(const N n,const O o)
      ->decltype(is0(sub(n)(o)))
      {return is0(sub(n)(o));}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  constexpr const LEq leq;

  struct GEq:Combinator<GEq,2> {
    template<typename N,typename O>
    static auto beta(const N n,const O o)
      ->decltype(is0(sub(o)(n)))
      {return is0(sub(o)(n));}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  constexpr const GEq geq;

  using GT=Bb::Bind<Not>::Bind<LEq>;
  const GT gt;

  struct Eq:Combinator<Eq,2> {
    template<typename N,typename O>
    using Beta=Expr<And,Expr<LEq,N,O>,Expr<LEq,O,N>>;
    template<typename N,typename O>
    static auto beta(const N n,const O o)
      ->decltype(_and(leq(n)(o))(leq(o)(n)))
      {return _and(leq(n)(o))(leq(o)(n));}
  };
  constexpr const Eq eq;

  using LT=Flip::Bind<GT>;
  const LT lt;

  struct NEq {
    template<typename N,typename O>
    using Beta=Expr<Or,Expr<GT,N,O>,Expr<GT,O,N>>;
    template<typename N,typename O>
    static auto beta(const N n,const O o)
      ->decltype(_or(gt(n)(o))(gt(o)(n)))
      {return _or(gt(n)(o))(gt(o)(n));}
  };
  constexpr const NEq neq;

  //caution this can be damn slow to compile...
  template<int n,typename N=N0>
  struct FromInt:FromInt<n-1,Succ::template Bind<N>> {};
  template<typename N> struct FromInt<0,N>:N {};

  ///////////////////////////////////////////////////////////////////////////////
  // convert to int
  static int _plus1(int n){return n+1;}
  Curry<decltype(&_plus1),&_plus1> plus1;

  template<typename N>
  int _toInt(const N n) {return beta(n(plus1)(0));}
  CurryTemplateFunction(_toInt,1) toInt;
};