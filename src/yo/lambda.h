#pragma once

#include<avr_std.h>
using avr_std::enable_if;
using avr_std::is_same;
using avr_std::is_convertible;

// #define cex

#ifndef cex
  #define cex constexpr
#else
  #ifdef ARDUINO
    #include <streamFlow.h>
    using namespace StreamFlow;
    #define cout Serial
    #define endl "\n\r"
  #else
    #include <iostream>
    using std::cout;
    using std::endl;
  #endif
#endif

template<bool chk,typename T> using When=typename enable_if<chk,T>::type;

struct None {};
cex const None none;
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
  template<typename O> cex const Expr<O> operator()(const O o) const {return {o};}
  template<typename O> cex const O cons(const O o) const {return o;}
  static constexpr int len() {return 0;}
};

using Empty=Expr<>;
cex const Empty empty;
template<typename O> constexpr bool isEmpty() {return is_same<const O,const Empty>::value;}

template<typename... OO> cex const Expr<OO...> expr(const OO... oo) {return Expr<OO...>(oo...);}

////_concat
template<typename A> cex A _concat(const A a,const Empty) {return a;}
template<typename A,typename B> cex auto _concat(const A a,const B b)->const When<!isApp<A>()&&!isApp<B>(),decltype(expr(a,b))> {return expr(a,b);}
template<typename A,typename B> cex auto _concat(const A a,const B b)->const When< isApp<A>()&&!isApp<B>(),decltype(a(b))> {return a(b);}
template<typename A,typename B> cex auto _concat(const A a,const B b)->const When<!isApp<A>()&& isApp<B>()&&!isEmpty<B>(),decltype(b.cons(a))> {return b.cons(a);}
template<typename A,typename B>
cex auto _concat(const A a,const B b)
  ->const When< isApp<A>()&& isApp<B>()&&!isEmpty<B>(),decltype(_concat(a.tail,b).cons(a.head))>
  {return _concat(a.tail,b).cons(a.head);}

//// beta

/*result*/     template<typename Fn,typename R,typename Nx,typename... OO> cex auto br(const R r,const Nx n,const OO...)->const When<!isNone<R>(),decltype(_concat(r,n))>;
/*last param*/ template<typename Fn,typename Nx,typename... OO> cex auto br(const None,const Expr<Nx> n,const OO... oo)->const decltype(Fn::beta(oo...,n.head));
/*add param*/  template<typename Fn,typename Nx,typename... OO> cex auto br(const None,const Nx n,const OO... oo)->const When<isApp<Nx>()&&(Nx::len()>1),decltype(br<Fn>(Fn::beta(oo...,n.head),n.tail,oo...,n.head))>;
/*add item*/   template<typename Fn,typename Nx,typename... OO> cex auto br(const None,const Nx n,const OO... oo)->const When<!isApp<Nx>(),decltype(Fn::beta(oo...,n))>;

//stop--
template<typename O> cex const O res(const None,const O o) {return o;}
template<typename O> cex const O res(const O,const O o) {return o;}

//result--
template<typename Fn,typename R,typename Nx,typename... OO>
cex auto br(const R r,const Nx n,const OO...)
  ->const When<!isNone<R>(),decltype(_concat(r,n))>
  {return _concat(r,n);}

//last param--
template<typename Fn,typename Nx,typename... OO>
cex auto br(const None,const Expr<Nx> n,const OO... oo)
  ->const decltype(Fn::beta(oo...,n.head))
  {return Fn::beta(oo...,n.head);}

//add param--
template<typename Fn,typename Nx,typename... OO>
cex auto br(const None,const Nx n,const OO... oo)
  ->const When<isApp<Nx>()&&(Nx::len()>1),decltype(br<Fn>(Fn::beta(oo...,n.head),n.tail,oo...,n.head))>
  {return br<Fn>(Fn::beta(oo...,n.head),n.tail,oo...,n.head);}

//add item--
template<typename Fn,typename Nx,typename... OO>
cex auto br(const None,const Nx n,const OO... oo)
  ->const When<!isApp<Nx>(),decltype(Fn::beta(oo...,n))>
  {return Fn::beta(oo...,n);}

//beta start--
template<typename H,typename... TT>
cex auto beta(const Expr<H,TT...> o)
  ->const decltype(res(br<H>(none,o.tail),o))
  {return res(br<H>(none,o.tail),o);}

//irreducible--
template<typename O> cex const O beta(const O o) {return o;}

//single--
template<typename H>
cex auto beta(const Expr<H> o)
  ->const decltype(beta(o.head))
  {return beta(o.head);}

//recursive--
template<typename R,typename O>
cex auto res(const R r,const O)
  ->const When<!isNone<R>(),decltype(beta(r))>
  {return beta(r);}

//natural precedence--
template<typename H,typename... TT,When<isApp<H>(),None> = none>
cex auto beta(const Expr<H,TT...> o)
  ->const decltype(res(_concat(o.head,o.tail),o))  
  {return res(_concat(o.head,o.tail),o);}

//// lambda application

template<typename H,typename... TT>
struct Expr<H,TT...>:LambdaApp {
  using This=Expr<H,TT...>;
  using Head=H;
  using Tail=Expr<TT...>;
  const Head head;
  const Tail tail;
  static constexpr int len() {return 1+Tail::len();}
  cex Expr():head(H{}),tail() {}
  cex Expr(const H o,const TT... oo):head(o),tail(oo...) {}
  cex Expr(const H o,const Expr<TT...> oo):head(o),tail(oo) {}
  template<typename O> cex const Expr<H,TT...,O> operator()(const O o) const {return {head,tail(o)};}
  cex const This cons(const Empty) const {return *this;}
  template<typename O> cex const Expr<O,H,TT...> cons(const O o) const {return {o,*this};}
  template<typename O,typename... OO>
  static cex auto beta(const O o,const OO... oo)
    ->const decltype(::beta(expr(H{},TT{}...,o,oo...)))
    {return ::beta(expr(H{},TT{}...,o,oo...));}
};

#ifdef YO_VERB
  template<typename Out> Out& operator<<(Out& out,const Expr<> o) {return out<<"ø";}
  template<typename Out,typename O,typename... OO> When<!isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...> o) {return out<<"["<<o.head<<" "<<o.tail<<"]";}
  template<typename Out,typename O,typename... OO> When< isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...> o) {return out<<"[("<<o.head<<") "<<o.tail<<"]";}
#else
  template<typename Out> Out& operator<<(Out& out,const Expr<> o) {return out;}
  template<typename Out,typename O,typename... OO> When<!isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...> o) {return out<<o.head<<" "<<o.tail;}
  template<typename Out,typename O,typename... OO> When< isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...> o) {return out<<"("<<o.head<<") "<<o.tail;}
#endif

//alias (for printing)--
template<typename Fn> struct Alt:Fn {
  cex operator const Alias() const {return Alias{};}
  template<typename O> cex const Expr<Alt<Fn>,O> operator()(const O o) const {return {*this,o};}
};

#ifdef YO_VERB
  template<typename Out,typename Fn> cex Out& operator<<(Out& out,const Alt<Fn> o) {return out<<"Alt{"<<(Fn&)o<<"}";}
#else
  template<typename Out,typename Fn> cex Out& operator<<(Out& out,const Alt<Fn> o) {return out<<(Fn&)o;}
#endif

template<typename Fn>
struct Combinator:Lambda {
  template<typename O> cex const Expr<Fn,O> operator()(const O o) const {return {*(Fn*)this,o};}
  template<typename... OO> static cex const None beta(const OO...) {return none;}
};
