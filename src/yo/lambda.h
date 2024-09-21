#pragma once

// #define cex
#define cex constexpr

namespace yo {
  template<bool chk,typename T> using When=typename enable_if<chk,T>::type;

  struct None {};
  constexpr const None none;
  template<typename Out> Out& operator<<(Out& out,const None) {return out<<"⊥";}

  struct Lambda {};
  struct LambdaApp {};
  struct Alias {};

  template<typename O> constexpr bool isNone() {return is_same<O,None>::value;}
  template<typename O> constexpr bool isAlias() {return is_convertible<O,Alias>::value;}
  template<typename O> constexpr bool isApp() {return is_convertible<O,LambdaApp>::value;}
  template<typename O> constexpr When<!isApp<O>(),bool> isLambda() {return is_convertible<O,Lambda>::value;}
  template<typename O> constexpr When< isApp<O>(),bool> isLambda() {return isApp<typename O::Head>();}

  template<typename...> struct Expr;
  template<> struct Expr<> {
    template<typename O> cex const Expr<O> cons(const O o) const {return o;}
    template<typename O> cex const Expr<O> operator()(const O o) const {return {o};}
    template<typename O> cex const O concat(const O o) const {return o;}
  };
  using Empty=Expr<>;
  Empty empty;
  template<typename O> constexpr bool isEmpty() {return is_same<O,Empty>::value;}
  template<typename H,typename... TT>
  struct Expr<H,TT...>:LambdaApp {
    using Head=H;
    using Tail=Expr<TT...>;
    const Head head;
    const Tail tail;
    cex Expr():head(Head{}),tail(Tail{}){}
    cex Expr(const Head h,const Tail t):head(h),tail(t){}
    cex Expr(const Head h,const TT... tt):head(h),tail(tt...){}
    template<typename O> cex const Expr<O,H,TT...> cons(const O o) const {return {o,*this};}
    template<typename O> cex const Expr<H,TT...,O> operator()(const O o) const {return {head,tail(o)};}
    template<typename O> cex const Expr<H,TT...,O> concat(const Expr<O> o) const {return operator()(o.head);}
    template<typename O,typename... OO> cex const Expr<H,TT...,O,OO...> concat(const Expr<O,OO...> o) const {return tail.concat(o).cons(head);}
  };

  template<typename... OO> cex const Expr<OO...> expr(const OO... oo) {return Expr<OO...>(oo...);}

  #ifdef YO_VERB
    template<typename Out> Out& operator<<(Out& out,const Empty) {return out<<"ø";}
    template<typename Out,typename... OO> Out& operator<<(Out& out,const Expr<OO...> o) {return out<<"(@"<<&o.head<<"|"<<o.head<<": @"<<&o.tail<<"|"<<o.tail<<")";}
  #else
    template<typename Out> Out& operator<<(Out& out,const Empty) {return out;}
    template<typename Out,typename O, typename... OO> When<isAlias<O>()||!isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...> o) {return out<<o.head<<" "<<o.tail;}
    template<typename Out,typename O, typename... OO> When< isApp<O>()&&!isAlias<O>(),Out>& operator<<(Out& out,const Expr<O,OO...> o) {return out<<o.head<<") "<<o.tail;}
  #endif

  //alias (for printing)--
  template<typename Fn> struct Alt:Fn {
    cex operator const Alias() const {return Alias{};}
    template<typename O> cex const Expr<Alt<Fn>,O> operator()(const O o) const {return {*this,o};}
  };

  template<typename Fn>
  struct Combinator:Lambda {
    template<typename O> cex Expr<Fn,O> operator()(const O o) const {return {*(Fn*)this,o};}
    // template<typename... OO> cex auto beta(const OO... oo)->const decltype(Fn::delta(oo...)) {return Fn::delta(oo...);}
  };

  template<typename C,typename O,typename... OO>
  cex auto step(const Expr<C,O,OO...> o)
    -> const Expr<decltype(C::beta(o.tail.head)),OO...>
    {return           {C::beta(o.tail.head),o.tail.tail};}

  template<typename C,typename O,typename P,typename... OO>
  cex auto step(const Expr<C,O,P,OO...> o)
    -> const Expr<decltype(C::beta(o.tail.head,o.tail.tail.head)),OO...>
    {return           {C::beta(o.tail.head,o.tail.tail.head),o.tail.tail.tail};}

  template<typename C,typename O,typename P,typename Q,typename... OO>
  cex auto step(const Expr<C,O,P,Q,OO...> o)
    -> const Expr<decltype(C::beta(o.tail.head,o.tail.tail.head,o.tail.tail.tail.head)),OO...>
    {return           {C::beta(o.tail.head, o.tail.tail.head, o.tail.tail.tail.head), o.tail.tail.tail.tail};}

  template<typename C,typename O,typename P,typename Q,typename R,typename... OO>
  cex auto step(const Expr<C,O,P,Q,R,OO...> o)
    -> const Expr<decltype(C::beta(o.tail.head, o.tail.tail.head, o.tail.tail.tail.head, o.tail.tail.tail.tail.head)),OO...>
    {return           {C::beta(o.tail.head, o.tail.tail.head, o.tail.tail.tail.head, o.tail.tail.tail.tail.head), o.tail.tail.tail.tail.tail};}

  template<typename O> cex const None step(const O) {return none;}

  template<typename O> cex const O res(const O o,const O) {return o;}
  template<typename O> cex const O res(const None,const O o) {return o;}
  template<typename R,typename O,When<!isNone<O>()&&!is_same<R,O>::value,bool> = false> cex auto res(const R r,const O)->const decltype(beta(r)) {return beta(r);}

  cex const Empty beta(const Empty o) {return o;}
  cex const None beta(const None o) {return o;}
  template<typename O> cex auto beta(const O o)->const When<isNone<decltype(step(o))>(),O> {return o;}
  template<typename O> cex auto beta(const O o)->const When<!isEmpty<O>()&&!isNone<O>(),decltype(res(step(o),o))> {return res(step(o),o);}
  template<typename O> cex auto beta(const Expr<O> o)->const decltype(beta(o.head)) {return beta(o.head);}
  template<typename O,typename... OO> cex auto beta(const Expr<O,OO...> o)->const decltype(beta(o.head.concat(o.tail))) {return beta(o.head.concat(o.tail));}
};
