#pragma once

#include "combinator.h"

#ifndef YO_DEBUG
  namespace yo {
#endif
  ////////////////////////////////////////
  // compile time count items in a list of types
  template<typename... OO> struct Count;

  template<typename O,typename... OO>
  struct Count<O,OO...> {
    constexpr int operator()(){return 1+Count<OO...>()();}
    constexpr operator int(){return 1+Count<OO...>()();}
  };

  template<typename O>
  struct Count<O> {
    constexpr int operator()(){return 1;}
    constexpr operator int(){return 1;}
  };

  template<>
  struct Count<> {
    constexpr int operator()(){return 0;}
    constexpr operator int(){return 0;}
  };

  ///////////////////////////////////////////////////////////////////////////////
  //Wire C++ functions
  // by allowing them to participate on the app chain
  template<typename F,F f> struct Curry;

  template<typename R,typename O,typename... OO,Func<R,O,OO...>f>
  struct Curry<Func<R,O,OO...>,f>:Combinator<Curry<Func<R,O,OO...>,f>,(int)Count<O,OO...>()> {
    using This=Curry<Func<R,O,OO...>,f>;
    template<typename Q,typename...QQ> using Beta=R;
    using Base=Combinator<This,(int)Count<O,OO...>()>;
    // using Base::beta;
    // template<typename Q>
    // static R beta(const Q&q) {
    //   return R(f(run<R,Q>(std::forward<const Q>(q))));
    // }
    // template<typename Q,typename...QQ>
    // static R beta(const Q&q, const QQ&...qq) {
    //   return R(f(run<R,Q,QQ...>(std::forward<const Q>(q),std::forward<const QQ...>(qq...))));
    // }
    template<typename Q>
    static R beta(const Q&&q) {
      return R(f(run<R,Q>(std::forward<const Q>(q))));
    }
    template<typename Q,typename...QQ>
    static R beta(const Q&&q, const QQ&&...qq) {
      return R(f(run<R,Q,QQ...>(std::forward<const Q>(q),std::forward<const QQ...>(qq...))));
    }
  };
#ifndef YO_DEBUG
  };
#endif
