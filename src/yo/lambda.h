#pragma once

#include "combinator.h"

#ifndef YO_DEBUG
  namespace yo {
#endif
  template<typename Prev,typename Arg>
  struct Param {
    const Prev prev;
    const Arg param;
    Param(const Prev&p,const Arg&o):prev(p),param(o)  {dbo<<"(#1)";}
    Param(const Prev&p,const Arg&&o):prev(p),param(o) {dbo<<"(#2)";}
    Param(const Prev&&p,const Arg&o):prev(p),param(o) {dbo<<"(#3)";}
    Param(const Prev&&p,const Arg&&o):prev(p),param(o){/*dbo<<"(#4)";*/}
    // template<typename... OO> 
    // auto beta(const OO&...oo) const 
    //   ->decltype(prev.beta(param,oo...)) 
    //   {return prev.beta(param,oo...);}
    template<typename... OO> 
    auto beta(const OO&&...oo) const 
      ->decltype(prev.beta(std::forward<const Arg>(param),std::forward<const OO>(oo)...)) 
      {/*dbo<<"!";*/return prev.beta(std::forward<const Arg>(param),std::forward<const OO>(oo)...);}
  };

  template<typename Prev,typename Arg,int n>
  struct Lambda:Combinator<Lambda<Prev,Arg,n>,n>,Param<Prev,Arg> {
    using Base=Param<Prev,Arg>;
    using Base::Base;
  };

  template<typename Prev,typename Arg>
  struct Lambda<Prev,Arg,1>:Combinator<Lambda<Prev,Arg,1>,1>,Param<Prev,Arg> {
    using Base=Param<Prev,Arg>;
    using Comb=Combinator<Lambda<Prev,Arg,1>,1>;
    using Base::Base;
    // using Base::prev;
    // using Base::param;
    using Base::beta;
    #ifdef REDUCE_ON_COMPLETION
      template<typename O>
      const auto operator()(const O&o) const
        ->decltype(beta(std::forward<const O>(o)))
        {/*dbo<<"*";*/return beta(std::forward<const O>(o));}
      template<typename O>
      const auto operator()(const O&&o) const
        ->decltype(beta(std::forward<const O>(o)))
        {/*dbo<<"§";*/return beta(std::forward<const O>(o));}
    #else
      using Comb::operator();
    #endif
  };

  template<typename Prev,typename Arg>
  struct Lambda<Prev,Arg,0>:Combinator<Lambda<Prev,Arg,0>,0>,Param<Prev,Arg> {
    using Base=Param<Prev,Arg>;
    using Base::Base;
    using Base::prev;
    using Base::param;
    auto beta() const 
      ->decltype(prev.beta(std::forward<const Arg>(param))) 
      {/*dbo<<"|";*/return prev.beta(std::forward<const Arg>(param));}
    // auto run() const->decltype(beta().run()) {return beta().run();}
  };

  template<typename Prev,typename Arg>
  struct Lambda<Prev,Arg,-1>:Combinator<Lambda<Prev,Arg,-1>,-1>,Param<Prev,Arg> {
    using This=Lambda<Prev,Arg,-1>;
    using Base=Param<Prev,Arg>;
    using Base::Base;
    using Base::prev;
    using Base::param;
    auto beta() const
      ->decltype(prev.beta()(std::forward<const Arg>(param)))
      {/*dbo<<".";*/return prev.beta()(std::forward<const Arg>(param));}
    // auto run() const->decltype(prev.run()(param).run()) {return prev.run()(param).run();}

    // works very nice but only on compile time expressions
    // template<typename O>
    // const auto operator()(const O&o) const
    //   ->decltype(beta()(std::forward<const O>(o)))
    //   {dbo<<"%";return beta()(std::forward<const O>(o));}
    // template<typename O>
    // const auto operator()(const O&&o) const
    //   ->decltype(beta()(std::forward<const O>(o)))
    //   {dbo<<"$";return beta()(std::forward<const O>(o));}
  };

#ifndef YO_DEBUG
  };
#endif
