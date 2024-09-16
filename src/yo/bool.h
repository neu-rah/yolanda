#pragma once

#include "combinators.h"

using True=Alt<Const>;
using False=Alt<KI>;
using Not=Alt<Flip>;

constexpr const Not _not;
constexpr const True _true;
const False _false;

struct Or:M {};
constexpr const Or _or;

struct And:Combinator<And> {
  using Combinator::beta;
  template<typename P,typename Q>  
  static auto beta(const P&p,const Q&q)
    ->const decltype(p(q)(p))
    {return p(q)(p);}
};
constexpr const And _and;

struct BEq:Combinator<BEq> {
  using Combinator::beta;
  template<typename P,typename Q>  
  static auto beta(const P&p,const Q&q)
    ->const decltype(p(q)(_not(p)))
    {return p(q)(_not(p));}
};
constexpr const BEq beq;

template<typename O>
static bool toBool(const O o) {return beta(o(true)(false));}

struct FromBool:Combinator<FromBool> {
  using Combinator::beta;
  template<typename B,typename O,typename P>
  static auto beta(const B b,const O o,const P p)->const decltype(b?o:p) {return b?o:p;}
};

constexpr const FromBool fromBool;

template<typename Out> Out& operator<<(Out& out,const True) {return out<<"true";}
template<typename Out> Out& operator<<(Out& out,const False) {return out<<"false";}
template<typename Out> Out& operator<<(Out& out,const Not) {return out<<"not";}
template<typename Out> Out& operator<<(Out& out,const Or) {return out<<"or";}
template<typename Out> Out& operator<<(Out& out,const And) {return out<<"and";}
