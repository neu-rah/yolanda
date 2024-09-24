#pragma once

#include "combinators.h"

namespace yo {

  using True=Alt<Const>;
  using False=Alt<KI>;
  struct Not:Flip {
    static bool /*delta*/beta(bool o) {return !o;}
  };

  constexpr const Not _not;
  constexpr const True _true;
  const False _false;

  struct Or:M {
    static bool /*delta*/beta(bool a,bool b) {return a||b;}
  };
  constexpr const Or _or;

  struct And:Combinator<And> {
    static bool /*delta*/beta(bool a,bool b) {return a&&b;}
    template<typename P,typename Q>  
    static auto beta(const P&p,const Q&q)
      ->const decltype(p(q)(p))
      {return p(q)(p);}
  };
  constexpr const And _and;

  struct BEq:Combinator<BEq> {
    static bool /*delta*/beta(bool a,bool b) {return a==b;}
    template<typename P,typename Q>  
    static auto beta(const P&p,const Q&q)
      ->const decltype(p(q)(_not(p)))
      {return p(q)(_not(p));}
  };
  constexpr const BEq beq;

  template<typename O>
  static bool toBool(const O o) {return beta(o(true)(false));}

  struct FromBool:Combinator<FromBool> {
    template<typename B,typename O,typename P>
    static auto beta(const B b,const O o,const P p)->const decltype(b?o:p) {return b?o:p;}
  };

  constexpr const FromBool fromBool;

  #ifdef YO_PRINT
    // template<typename Out> Out& operator<<(Out& out,const yo::True) {return out<<"true";}
    // template<typename Out> Out& operator<<(Out& out,const yo::False) {return out<<"false";}
    template<typename Out> Out& operator<<(Out& out,const yo::Not) {return out<<"not";}
    template<typename Out> Out& operator<<(Out& out,const yo::Or) {return out<<"or";}
    template<typename Out> Out& operator<<(Out& out,const yo::And) {return out<<"and";}
    template<typename Out> Out& operator<<(Out& out,const yo::BEq) {return out<<"===";}
  #endif
};