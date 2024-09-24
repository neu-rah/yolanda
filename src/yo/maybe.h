#pragma once
#include "combinators.h"
// #include "curry.h"
#include "bool.h"


namespace yo {

  struct Nothing:Alt<K>{};
  constexpr Nothing nothing;

  //just:=λo.λn.λj.j o
  struct Just:Combinator<Just> {
    template<typename O,typename N,typename J> static auto beta(const O o,const N,const J j)
      ->decltype(j(o)) {return j(o);}
  };

  //isNothing (ChurchMaybe m) = m True (const False)
  struct IsNothing:Combinator<IsNothing> {
    template<typename M> static auto beta(const M m)->decltype(m(_true)(_const(_false))) {return m(_true)(_const(_false));}
  };

  constexpr IsNothing isNothing;

  struct IsJust:Combinator<IsJust> {
    template<typename M> static auto beta(const M m)->decltype(m(_false)(_const(_true))) {return m(_false)(_const(_true));}
  };

  constexpr IsJust isJust;

  constexpr Just just;
};
