#pragma once

#include "combinators.h"

namespace yo {

  using True=Alt<Const>;
  using False=Alt<KI>;
  struct Not:Flip {
    using Flip::beta;
    static bool /*delta*/beta(bool o) {return !o;}
  };

  cex const Not _not{};
  cex const True _true{};
  cex const False _false{};

  struct Or:M {
    using M::beta;
    static bool /*delta*/beta(bool a,bool b) {return a||b;}
  };
  cex const Or _or{};

  struct And:Combinator<And> {
    static bool /*delta*/beta(bool a,bool b) {return a&&b;}
    template<typename P,typename Q>  
    static auto beta(const P&p,const Q&q)
      ->const decltype(p(forward<const Q>(q))(forward<const P>(p)))
      {return p(forward<const Q>(q))(forward<const P>(p));}
  };
  cex const And _and;

  struct BEq:Combinator<BEq> {
    static bool /*delta*/beta(bool a,bool b) {return a==b;}
    template<typename P,typename Q>  
    static auto beta(const P&p,const Q&q)
      ->const decltype(p(forward<const Q>(q))(_not(forward<const Q>(q))))
      {return p(forward<const Q>(q))(_not(forward<const Q>(q)));}
  };
  cex const BEq beq;

  template<typename O>
  static bool toBool(const O o) {return beta(o(true)(false));}

  struct FromBool:Combinator<FromBool> {
    template<typename B,typename O,typename P>
    static auto beta(const B b,const O o,const P p)
      ->const decltype(b?forward<const O>(o):forward<const P>(p))
      {return b?forward<const O>(o):forward<const P>(p);}
  };

  cex const FromBool fromBool;

  #ifdef YO_PRINT
    template<typename Out> Out& operator<<(Out& out,const True) {return out<<"true";}
    template<typename Out> Out& operator<<(Out& out,const False) {return out<<"false";}
    template<typename Out> Out& operator<<(Out& out,const Not) {return out<<"not";}
    template<typename Out> Out& operator<<(Out& out,const Or) {return out<<"or";}
    template<typename Out> Out& operator<<(Out& out,const And) {return out<<"and";}
    template<typename Out> Out& operator<<(Out& out,const BEq) {return out<<"===";}
    template<typename Out> Out& operator<<(Out& out,const FromBool) {return out<<"fromBool";}
  #endif

};