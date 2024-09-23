#pragma once

#define cex constexpr

template<bool chk,typename T> using When=typename enable_if<chk,T>::type;

struct Lambda{};
struct App{};
struct None{};
constexpr const None none;
template<typename Out> Out& operator<<(Out& out, const None) {return out<<"⊥";}

//// lambda expression
template<typename...> struct Expr;

template<> struct Expr<> {
  template<typename O> cex const Expr<O> cons(const O o) const {return o;}
  template<typename O> cex const Expr<O> operator()(const O o) const {return {o};}
  template<typename O> cex const O concat(const O o) const {return o;}
};
using Empty=Expr<>;
constexpr const Empty empty;
template<typename Out> Out& operator<<(Out& out, const Empty) {return out<<"ø";}

template<typename H,typename... TT>
struct Expr<H,TT...>:App {
  using Head=H;
  using Tail=Expr<TT...>;
  const Head head;
  const Tail tail;
  cex Expr():head(Head{}),tail(Tail{}){}
  cex Expr(const Head h,const Tail t):head(h),tail(t) {}
  cex Expr(const Head h,const TT... tt):head(h),tail(Expr<TT...>{tt...}) {}
  template<typename O> cex const Expr<O,H,TT...> cons(const O o) const {return {o,*this};}
  template<typename O> cex const Expr<H,TT...,O> operator()(const O o) const {return {head,tail(o)};}
  template<typename O> cex const Expr<H,TT...,O> concat(const Expr<O> o) const {return operator()(o.head);}
  template<typename O,typename... OO> cex const Expr<H,TT...,O,OO...> concat(const Expr<O,OO...> o) const {return tail.concat(o).cons(head);}
};

template<typename O> constexpr bool isNone() {return is_same<O,None>::value;}
template<typename O> constexpr bool isEmpty() {return is_same<O,Empty>::value;}
template<typename O> constexpr bool isApp() {return is_convertible<O,App>::value;}

cex const Empty expr() {return empty;}
template<typename O> cex const When<isApp<O>(),O> expr(const O o) {return o;}
template<typename O,typename... OO> cex const When<!isApp<O>(),Expr<O,OO...>> expr(const O o,const OO... oo) {return Expr<O,OO...>(o,oo...);}
template<typename O,typename... OO> cex auto expr(const O o,const OO... oo)->const When< isApp<O>(),decltype(o.concat(expr(oo...)))> {return o.concat(expr(oo...));}
template<typename... OO> cex const Expr<OO...> expr(const OO... oo) {return Expr<OO...>(oo...);}

template<typename Out,typename O,typename... OO> When<!isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...> o) {return out<<o.head<<" "<<o.tail;}
template<typename Out,typename O,typename... OO> When< isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...> o) {return out<<"("<<o.head<<") "<<o.tail;}

template<typename O> cex const O concat(const O o,const Empty) {return o;}
template<typename A, typename B> cex const When<!isApp<A>()&&!isApp<B>(),Expr<A,B>> concat(const A a,const B b) {return {a,b};}
template<typename A, typename B> cex auto concat(const A a,const B b)->const When< isApp<A>(),decltype(a.concat(b))> {return a.concat(b);}
template<typename A, typename B> cex auto concat(const A a,const B b)->const When<!isApp<A>()&&isApp<B>(),decltype(b.cons(a))> {return b.cons(a);}

//// beta reduction

//beta steps--
template<typename C,typename O,typename... OO>
cex auto step(const Expr<C,O,OO...> o)
  -> const decltype(concat(C::beta(o.tail.head),o.tail.tail))
  {return           concat(C::beta(o.tail.head),o.tail.tail);}

template<typename C,typename O,typename P,typename... OO>
cex auto step(const Expr<C,O,P,OO...> o)
  -> const decltype(concat(C::beta(o.tail.head,o.tail.tail.head),o.tail.tail.tail))
  {return           concat(C::beta(o.tail.head,o.tail.tail.head),o.tail.tail.tail);}

template<typename C,typename O,typename P,typename Q,typename... OO>
cex auto step(const Expr<C,O,P,Q,OO...> o)
  -> const decltype(concat(C::beta(o.tail.head, o.tail.tail.head, o.tail.tail.tail.head),o.tail.tail.tail.tail))
  {return           concat(C::beta(o.tail.head, o.tail.tail.head, o.tail.tail.tail.head),o.tail.tail.tail.tail);}

template<typename C,typename O,typename P,typename Q,typename R,typename... OO>
cex auto step(const Expr<C,O,P,Q,R,OO...> o)
  -> const decltype(concat(C::beta(o.tail.head, o.tail.tail.head, o.tail.tail.tail.head, o.tail.tail.tail.tail.head), o.tail.tail.tail.tail.tail))
  {return           concat(C::beta(o.tail.head, o.tail.tail.head, o.tail.tail.tail.head, o.tail.tail.tail.tail.head), o.tail.tail.tail.tail.tail);}

template<typename O> cex const None step(const O) {return none;}

//recursion/result--
template<typename O> cex const O res(const O o,const O) {return o;}
template<typename O> cex const O res(const None,const O o) {return o;}
template<typename R,typename O,When<!isNone<O>()&&!is_same<R,O>::value,bool> = false> cex auto res(const R r,const O)->const decltype(beta(r)) {return beta(r);}

//beta start---
cex const Empty beta(const Empty) {return empty;}
template<typename O> cex auto beta(const O o)->const When<!isEmpty<O>(),decltype(res(step(o),o))> {return res(step(o),o);}
template<typename O> cex auto beta(const Expr<O> o)->const decltype(beta(o.head)) {return beta(o.head);}

