#pragma once

// Church encoder Maybe
// nothing =    λn.λj.n
//    just = λx.λn.λj.j x

#ifndef YO_DEBUG
  namespace yo {
#endif
  struct Nothing:Combinator<Nothing,2> {
    template<typename N,typename J> using Beta=N;
    template<typename N,typename J>
    static N beta(const N&&n,const J&&) {return n;}
  };
  constexpr const Nothing nothing;

  struct Just:Combinator<Just,3> {
    template<typename O,typename N,typename J> using Beta=Expr<J,O>;
    template<typename O,typename N,typename J>
    static auto beta(const O&&o,const N&&,const J&&j)
      ->decltype(j(o))
      {return j(o);}
  };
  constexpr const Just just;
#ifndef YO_DEBUG
  };
#endif
