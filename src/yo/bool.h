#pragma once

#include "combinators.h"

namespace yo {
  using True=Alt<K>;
  using False=Alt<KI>;
  using Not=Alt<Flip>;
  
  constexpr const Not _not;
  constexpr const True _true;
  const False _false;

  struct Or:M {};
  constexpr const Or _or;

  struct And:Combinator<And,2> {
    template<typename P,typename Q>  
    using Beta=typename P::template Bind<Q>::template Bind<P>;
    template<typename P,typename Q>  
    static auto beta(const P&p,const Q&q)
      ->decltype(p(q)(p))
      {return p(q)(p);}
  };
  constexpr const And _and;

  struct BEq:Combinator<BEq,2> {
    template<typename P,typename Q>
    using Beta=typename P::template Bind<Q>::template Bind<Not::Bind<Q>>;
    template<typename P,typename Q>  
    static auto beta(const P&p,const Q&q)
      ->decltype(p(q)(_not(p)))
      {return p(q)(_not(p));}
  };
  constexpr const BEq beq;

  template<typename O>
  bool toBool(const O o) {return o(true)(false);}
};