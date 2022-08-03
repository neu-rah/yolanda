#pragma once

#include "combinator.h"

#ifndef YO_DEBUG
  namespace yo {
#endif
  template<typename Prev,typename Arg>
  struct Bond {
    // template<typename... OO> 
    // static auto beta(const OO&...oo)
    //   ->decltype(Prev().beta(Arg(),oo...)); 
      // {return Prev().beta(std::forward<const Arg>(Arg()),std::forward<const OO>(oo)...);}
    template<typename... OO> 
    static auto beta(const OO&&...oo)
      ->decltype(Prev().beta(std::forward<const Arg>(Arg()),std::forward<const OO>(oo)...)) 
      {return Prev().beta(std::forward<const Arg>(Arg()),std::forward<const OO>(oo)...);}
  };

  template<typename Prev,typename Arg,int n>
  struct Binder:Combinator<Binder<Prev,Arg,n>,n>,Bond<Prev,Arg> {};

  template<typename Prev,typename Arg> 
  struct Binder<Prev,Arg,3>:Combinator<Binder<Prev,Arg,3>,3>,Bond<Prev,Arg> {
    template<typename O,typename P,typename Q> 
    using Beta=typename Prev::template Beta<Arg,O,P,Q>;
  };

  template<typename Prev,typename Arg> 
  struct Binder<Prev,Arg,2>:Combinator<Binder<Prev,Arg,2>,2>,Bond<Prev,Arg> {
    template<typename O,typename P> 
    using Beta=typename Prev::template Beta<Arg,O,P>;
  };

  template<typename Prev,typename Arg> 
  struct Binder<Prev,Arg,1>:Combinator<Binder<Prev,Arg,1>,1>,Bond<Prev,Arg> {
    template<typename O> using Beta=typename Prev::template Beta<Arg,O>;
    template<typename O> using Bind=Beta<O>;
  };

  template<typename Prev,typename Arg> 
  struct Binder<Prev,Arg,0>:Combinator<Binder<Prev,Arg,0>,0>,Bond<Prev,Arg> {
    using Beta=typename Prev::template Beta<Arg>;
    auto beta() const 
      ->decltype(Prev().beta(Arg())) 
      {/*dbo<<"·";*/return Prev().beta(std::forward<Arg>(Arg()));}
    using Run=typename Beta::Run;
  };

  template<typename Prev,typename Arg> 
  struct Binder<Prev,Arg,-1>:Combinator<Binder<Prev,Arg,-1>,-1>,Bond<Prev,Arg> {
    using Beta=typename Prev::Beta::template Bind<Arg>;
    auto beta() const
      ->decltype(Prev().beta()(Arg()))
      {/*dbo<<"~"*/;return Prev().beta()(std::forward<const Arg>(Arg()));}
    template<typename O> using Bind=typename Prev::Beta::template Bind<Arg>::template Bind<O>;
    using Run=typename Beta::Run;
  };

  template<typename...> struct Expr {};
  template<typename O,typename OO,typename... OOO>
  struct Expr<O,OO,OOO...>:Expr<typename O::template Bind<OO>,OOO...> {};
  template<typename O> struct Expr<O>:O {};

  template<typename condition>
  struct If {
    template<typename then_action>
    struct Then {
      template<typename else_action>
      using Else=Expr<condition,then_action,else_action>;
    };
  };

#ifndef YO_DEBUG
  };
#endif
