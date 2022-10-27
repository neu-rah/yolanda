#pragma once

#include "base.h"

namespace yo {

  template<typename Prev,typename Param>
  struct App {
    const Prev prev;
    const Param param;
    constexpr App(const Prev o={},const Param p={}):prev(o),param(p) {}
  };

  template<typename Prev,typename Param,int n>
  struct Lambda:App<Prev,Param> {
    using This=Lambda<Prev,Param,n>;
    using Base=App<Prev,Param>;
    using Base::Base;
    using Base::prev;
    using Base::param;
    template<typename O> using Bind=Lambda<This,O,n-1>;
    template<typename O> Bind<O> operator()(const O o) const {return Bind<O>(*this,o);}
    template<typename... OO> 
    auto beta(const OO... oo) const
      ->decltype(prev.beta(param,oo...))
      {return prev.beta(param,oo...);}
    template<typename... OO> using Beta=decltype(This{}.beta<OO...>(OO{}...));
  };

  // template<typename Prev,typename Param>
  // struct Lambda<Prev,Param,1>:App<Prev,Param> {
  //   using This=Lambda<Prev,Param,1>;
  //   using Base=App<Prev,Param>;
  //   using Base::Base;
  //   using Base::prev;
  //   using Base::param;
  //   template<typename... OO>
  //   auto beta(const OO... oo) const
  //     ->decltype(prev.beta(param,oo...))
  //     {return prev.beta(param,oo...);}
  //   template<typename... OO> using Beta=decltype(This{}.beta<OO...>(OO{}...));
  //   template<typename O> using Bind=typename This::template Beta<O>;
  //   template<typename O> auto operator()(const O o) const->decltype(beta(o)) {return beta(o);}
  // };

  template<typename Prev,typename Param>
  struct Lambda<Prev,Param,0>:App<Prev,Param> {
    using This=Lambda<Prev,Param,0>;
    using Base=App<Prev,Param>;
    using Base::Base;
    using Base::prev;
    using Base::param;
    template<typename O> using Bind=Lambda<This,O,-1>;
    template<typename O> Bind<O> operator()(const O o) const {return Bind<O>(*this,o);}
    auto beta() const->decltype(prev.beta(param)) {return prev.beta(param);}
    using Beta=typename Prev::template Beta<Param>;
  };

  template<typename Prev,typename Param>
  struct Lambda<Prev,Param,-1>:App<Prev,Param> {
    using This=Lambda<Prev,Param,-1>;
    using Base=App<Prev,Param>;
    using Base::Base;
    using Base::prev;
    using Base::param;
    template<typename O> using Bind=Lambda<This,O,-1>;
    template<typename O> Bind<O> operator()(const O o) const {return Bind<O>(*this,o);}
    auto beta() const->decltype(prev.beta()(param)) {return prev.beta()(param);}
    using Beta=typename Prev::Beta::template Bind<Param>;
  };

  template<typename Def,int n> struct Combinator;

  template<typename Def,int n>
  struct Combinator {
    using It=Def;
    template<typename O> using Bind=Lambda<Def,O,n-1>;
    template<typename O> Bind<O> operator()(const O o) const {return Bind<O>(Def{},o);}
    // auto operator()() const->decltype(*(Def*)this) {return *(Def*)this;}
  };

  template<typename Def>
  struct Combinator<Def,1> {
    using It=Def;
    template<typename O> using Bind=typename Lambda<Def,O,0>::Beta;
    template<typename O> auto operator()(const O o) const
      ->decltype(Lambda<Def,O,0>(*(Def*)this,o).beta()) 
      {return Lambda<Def,O,0>(*(Def*)this,o).beta();}
  };

  //---------------------------------------
  // beta reduction
  template<typename O> struct Beta;
  
  template<typename O> auto beta(const O o)->decltype(Beta<O>::reduce(o)) {return Beta<O>::reduce(o);}
  
  template<typename O> struct Beta {static const O reduce(const O o){return o;}};
  
  template<typename Prev,typename Param,int n>
  struct Beta<Lambda<Prev,Param,n>> {
    static auto reduce(const Lambda<Prev,Param,n> o)->decltype(o) {return o;}
  };

  template<typename Prev,typename Param>
  struct Beta<Lambda<Prev,Param,0>> {
    static auto reduce(const Lambda<Prev,Param,0> o)->decltype(beta(o.beta())) {return beta(o.beta());}
  };

  template<typename Prev,typename Param>
  struct Beta<Lambda<Prev,Param,-1>> {
    static auto reduce(const Lambda<Prev,Param,-1> o)->decltype(beta(o.beta())) {return beta(o.beta());}
  };

};