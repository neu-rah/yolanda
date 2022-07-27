#pragma once

#include "combinators.h"

#ifndef YO_DEBUG
  namespace yo {
#endif
  using Not=C;
  using True=K;
  using False=Expr<True,Id>;

  constexpr const Not _not;
  constexpr const True _true;
  constexpr const False _false;

  struct Or:M {};
  constexpr const Or _or;

  struct And:Combinator<And,2> {
    template<typename P,typename Q>  
    using Beta=typename P::template Bind<Q>::template Bind<P>;
    template<typename P,typename Q>  
    static auto beta(const P&p,const Q&q)
      ->decltype(p(q)(p))
      {return p(std::forward<const Q>(q))(std::forward<const P>(p));}
  };
  constexpr const And _and;

  struct BEq:Combinator<BEq,2> {
    template<typename P,typename Q>
    using Beta=typename P::template Bind<Q>::template Bind<Not::Bind<Q>>;
    template<typename P,typename Q>  
    static auto beta(const P&p,const Q&q)
      ->decltype(p(q)(_not(p)))
      {return p(std::forward<const Q>(q))(_not(std::forward<const P>(p)));}
  };
  constexpr const BEq beq;

#ifndef YO_DEBUG
  };
#endif
