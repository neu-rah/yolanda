#pragma once

#include "combinator.h"

#ifndef YO_DEBUG
  namespace yo {
#endif
  struct I:Combinator<I,1> {
    template<typename O> using Beta=O;
    template<typename O> static O beta(const O&o) {return o;}
    #ifdef REDUCE_ON_COMPLETION
      template<typename O> const O operator()(const O&o) const {return o;}
    #endif
  };

  struct K:Combinator<K,2> {
    template<typename O,typename P> using Beta=O;
    template<typename O,typename P> static O beta(const O&o,const P&) {return o;}
    operator bool() const {return true;}
};

  struct S:Combinator<S,3> {
    template<typename F,typename G,typename O> using Beta=typename F::template Bind<O>::template Bind<typename G::template Bind<O>>;
    // template<typename F,typename G,typename O> 
    // static auto beta(const F&f,const G&g,const O&o)
    //   ->decltype(f(o)(g(o)));
      // {clog<<"S+";return f(std::forward<const O>(o))(std::forward<const decltype(g(o))>(g(std::forward<const O>(o))));}
    template<typename F,typename G,typename O> 
    static auto beta(const F&&f,const G&&g,const O&&o)
      ->decltype(f(std::forward<const O>(o))(g(std::forward<const O>(o))))
      {/*clog<<"S^";*/return f(std::forward<const O>(o))(g(std::forward<const O>(o)));}
  };
    
  #ifdef _S
    #undef _S
  #endif
  constexpr const S _S;
  constexpr const K _K;
  constexpr const I _I;
#ifndef YO_DEBUG
  };
#endif
