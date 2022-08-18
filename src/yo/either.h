#pragma once

//  left = λx.λl.λr.l x
// right = λx.λl.λr.r x

#ifndef YO_DEBUG
  namespace yo {
#endif
  struct Left:Combinator<Left,3> {
    template<typename O,typename L,typename R> using Beta=Expr<L,O>;
    template<typename O,typename L,typename R>
    static auto beta(const O&&o,const L&&l,const R&&r)
      ->decltype(l(o))
      {return l(o);}
  };
  constexpr const Left left;

  struct Right:Combinator<Right,3> {
    template<typename O,typename L,typename R> using Beta=Expr<R,O>;
    template<typename O,typename L,typename R>
    static auto beta(const O&&o,const L&&,const R&&r)
      ->decltype(r(o))
      {return r(o);}
  };
  constexpr const Right right;
#ifndef YO_DEBUG
  };
#endif
