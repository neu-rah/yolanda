#pragma once
#include "bool.h"

#ifndef YO_DEBUG
  namespace yo {
#endif
  using Flip=C;
  // using Fst=Expr<T,True>;
  struct Fst:Combinator<Fst,1> {
    template<typename O> using Beta=Expr<O,True>;
    // template<typename O> 
    // static auto beta(const O&o)
    //   ->decltype(o(std::forward<const True>(_true)))
    //   {return o(std::forward<const True>(_true));}
    template<typename O> 
    static auto beta(const O&&o)
      ->decltype(o(std::forward<const True>(_true)))
      {return o(std::forward<const True>(_true));}
  };
  // using Snd=Expr<T,False>;
  struct Snd:Combinator<Snd,1> {
    template<typename O> using Beta=Expr<O,False>;
    // template<typename O> 
    // static auto beta(const O&o)
    //   ->decltype(o(std::forward<const False>(_false)))
    //   {return o(std::forward<const False>(_false));}
    template<typename O> 
    static auto beta(const O&&o)
      ->decltype(o(std::forward<const False>(_false)))
      {return o(std::forward<const False>(_false));}
  };
  using Pair=V;

  constexpr const Flip flip;
  constexpr const Fst fst;
  constexpr const Snd snd;
  constexpr const Pair _pair;
#ifndef YO_DEBUG
  };
#endif
