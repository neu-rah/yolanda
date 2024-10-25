#pragma once

#include "lambda.h"

namespace yo  {

  template<typename O> constexpr const O nth0(const O o) {return o;}
  template<typename O> constexpr const typename O::Tail nth1(const O o) {return o.tail;}
  template<typename O> constexpr const typename O::Tail::Tail nth2(const O o) {return nth1(o).tail;}
  template<typename O> constexpr const typename O::Tail::Tail::Tail nth3(const O o) {return nth2(o).tail;}
  template<typename O> constexpr const typename O::Tail::Tail::Tail::Tail nth4(const O o) {return nth3(o).tail;}

  template<typename... OO> cex const Expr<OO...> step(const Expr<Expr<OO...>> o) {return o.head;}
  template<typename O,typename... OO> cex auto step(const Expr<O,OO...> o)
    ->const When<isApp<O>(),decltype(_concat(move(o.head),move(o.tail)))>
    {return _concat(move(o.head),move(o.tail));}

  template<typename... OO>
  cex auto step(const Expr<OO...> o) 
    ->const decltype(_concat(o.head.beta(nth1(o).head),nth1(o).tail))
    {return          _concat(o.head.beta(nth1(o).head),nth1(o).tail);}

  template<typename... OO>
  cex auto step(const Expr<OO...> o) 
    ->const decltype(_concat(o.head.beta(nth1(o).head,nth2(o).head),nth2(o).tail))
    {return          _concat(o.head.beta(nth1(o).head,nth2(o).head),nth2(o).tail);}

  template<typename... OO>
  cex auto step(const Expr<OO...> o) 
    ->const decltype(_concat(o.head.beta(nth1(o).head,nth2(o).head,nth3(o).head),nth3(o).tail))
    {return          _concat(o.head.beta(nth1(o).head,nth2(o).head,nth3(o).head),nth3(o).tail);}

  template<typename... OO>
  cex auto step(const Expr<OO...> o) 
    ->const decltype(_concat(o.head.beta(nth1(o).head,nth2(o).head,nth3(o).head,nth4(o).head),nth4(o).tail))
    {return          _concat(o.head.beta(nth1(o).head,nth2(o).head,nth3(o).head,nth4(o).head),nth4(o).tail);}

  cex const None step(int){return none;}
  cex const None step(const char*){return none;}
  template<typename O> cex const None step(const O o){return none;}

  cex const Empty beta(const Empty);
  template<typename O> cex auto beta(const O o)->const When<!isEmpty<O>(),decltype(res(step(o),o))>;
  template<typename O> cex auto beta(const Expr<O> o)->const decltype(beta(o.head));

  //recursion/result--
  template<typename O> cex const O res(const O o,const O) {return o;}
  template<typename O> cex const O res(const None,const O o) {return o;}
  template<typename R,typename O,When<!isNone<O>()&&!is_same<R,O>::value,bool> = false> cex auto res(const R r,const O)->const decltype(beta(r)) {return beta(r);}

  //beta start--
  cex const Empty beta(const Empty) {return empty;}
  template<typename O> cex auto beta(const O o)->const When<!isEmpty<O>(),decltype(res(step(o),o))> {return res(step(o),o);}
  template<typename O> cex auto beta(const Expr<O> o)->const decltype(beta(o.head)) {return beta(o.head);}
  //natural precedence -- this fixes the type level construction! runtime precdedence should be handled on construction (less rewrite)
  template<typename O,typename... OO> cex auto beta(const Expr<O,OO...> o)->const When<!isApp<O>(),decltype(res(step(o),o))> {return res(step(o),o);}
  template<typename O,typename... OO> cex auto beta(const Expr<O,OO...> o)->const When< isApp<O>(),decltype(beta(o.head._concat(o.tail)))> {return beta(o.head._concat(o.tail));}

};