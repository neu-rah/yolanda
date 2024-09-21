#pragma once

// #define cex
#define cex constexpr

template<bool chk,typename T> using When=typename enable_if<chk,T>::type;

struct None {};
constexpr const None none;
template<typename O> constexpr bool isNone() {return is_same<O,None>::value;}

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
struct Expr<H,TT...> {
  using Head=H;
  using Tail=Expr<TT...>;
  const Head head;\
  const Tail tail;
  template<typename O> cex const Expr<O,H,TT...> cons(const O o) const {return {o,*this};}
  template<typename O> cex const Expr<H,TT...,O> operator()(const O o) const {return {head,tail(o)};}
  template<typename O> cex const Expr<H,TT...,O> concat(const Expr<O> o) const {return operator()(o.head);}
  template<typename O,typename... OO> cex const Expr<H,TT...,O,OO...> concat(const Expr<O,OO...> o) const {return tail.concat(o).cons(head);}
};

template<typename Out> Out& operator<<(Out& out,const Empty) {return out<<"ø";}
template<typename Out,typename... OO> Out& operator<<(Out& out,const Expr<OO...> o) {return out<<"("<<o.head<<":"<<o.tail<<")";}

template<typename F>
struct Combinator {
  template<typename O> cex Expr<F,O> operator()(const O o) const {return {*(F*)this,o};}
};

struct I:Combinator<I> {
  template<typename O> static cex const O beta(const O o) {return o;}
};
cex const I id;

template<typename Out> Out& operator<<(Out& out,const I) {return out<<"id";}

struct K:Combinator<K> {
  template<typename O,typename P> static cex const O beta(const O o,const P) {return o;}
};
cex const K _true;

template<typename Out> Out& operator<<(Out& out,const K) {return out<<"true";}

struct S:Combinator<S> {
  template<typename F,typename G,typename O> static cex auto beta(const F f,const G g,const O o)->const decltype(f(o)(g(o))) {return f(o)(g(o));}
};
cex const S _S;

template<typename Out> Out& operator<<(Out& out,const S) {return out<<"S";}

// cex const Empty beta(const Empty o) {return o;}

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
  {return           {C::beta(o.tail.head,o.tail.tail.head,o.tail.tail.tail.head),o.tail.tail.tail.tail};}

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

