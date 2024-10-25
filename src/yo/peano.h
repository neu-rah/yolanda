#pragma once

#include "combinators.h"
#include "curry.h"
#include "bool.h"

namespace yo {
  // peano ----------------------------------------------
  struct Succ:Combinator<Succ> {
    static cex int /*delta*/beta(int n) {return n+1;}
    static cex double /*delta*/beta(double n) {return n+1;}
    template<typename O>
    static cex auto beta(const O o)
      ->const decltype(_S(_B)(forward<const O>(o)))
      {return _S(_B)(forward<const O>(o));}
  };
  cex const Succ succ;

  struct Add:Combinator<Add> {
    static cex int /*delta*/beta(int n,int o) {return n+o;}
    static cex double /*delta*/beta(double n,double o) {return n+o;}
    template<typename N,typename O>
    static cex auto beta(const N n,const O o)
      ->const decltype(n(succ)(forward<const O>(o)))
      {return n(succ)(forward<const O>(o));}
  };
  cex const Add _add;

  using Mul=Alt<B>;
  cex const Mul mul;

  using Pow=Alt<T>;
  cex const Pow _pow;

  using N0=Alt<False>;
  using N1=Alt<Id>;
  using N2=Expr<Succ,N1>;
  using N3=Expr<Succ,N2>;
  using N4=Expr<Succ,N3>;
  using N5=Expr<Succ,N4>;
  using N6=Expr<Succ,N5>;
  using N7=Expr<Succ,N6>;
  using N8=Expr<Succ,N7>;
  using N9=Expr<Succ,N8>;
  cex const N0 n0{};
  cex const N1 n1{};
  cex const N2 n2{};
  cex const N3 n3{};
  cex const N4 n4{};
  cex const N5 n5{};
  cex const N6 n6{};
  cex const N7 n7{};
  cex const N8 n8{};
  cex const N9 n9{};


  struct Is0:Combinator<Is0> {
    static cex bool /*delta*/beta(int n) {return n==0;}
    static cex bool /*delta*/beta(double n) {return n==0.0;}
    template<typename O>
    cex static auto beta(const O o)
      ->decltype(o(_true(_false))(_true))
      {return    o(_true(_false))(_true);}
  };
  cex const Is0 is0;

  struct Phi:Combinator<Phi> {
    template<typename O>
    cex static auto beta(const O o)
      ->decltype(_pair(snd(forward<const O>(o)))(succ(snd(forward<const O>(o)))))
      {return    _pair(snd(forward<const O>(o)))(succ(snd(forward<const O>(o))));}
  };

  struct Pred:Combinator<Pred> {
    using N0N0=Expr<Pair,N0,N0>;
    static int    /*delta*/beta(int n){return n-1;}
    static double /*delta*/beta(double n){return n-1;}
    template<typename N>
    cex static auto beta(const N n)
      ->decltype(fst(n(Phi())(N0N0{})))
      {return fst(n(Phi())(N0N0{}));}
  };
  cex const Pred pred;

  struct Sub:Combinator<Sub> {
    static cex int /*delta*/beta(int n,int o) {return n-o;}
    static cex double /*delta*/beta(double n,double o) {return n-o;}
    template<typename N,typename O>
    cex static auto beta(const N n, const O o)
      ->decltype(o(pred)(forward<const N>(n)))
      {return o(pred)(forward<const N>(n));}
  };
  cex const Sub sub;

  struct LEq:Combinator<LEq> {
    static cex  bool /*delta*/beta(int n,int o) {return n<=o;}
    static cex  bool /*delta*/beta(double n,double o) {return n<=o;}
    template<typename N,typename O>
    cex static auto beta(const N n,const O o)
      ->decltype(is0(sub(forward<const N>(n))(forward<const O>(o))))
      {return is0(sub(forward<const N>(n))(forward<const O>(o)));}
  };
  cex const LEq leq;

  struct GEq:Combinator<GEq> {
    static cex  bool /*delta*/beta(int n,int o) {return n>=o;}
    static cex  bool /*delta*/beta(double n,double o) {return n>=o;}
    template<typename N,typename O>
    cex static auto beta(const N n,const O o)
      ->decltype(is0(sub(forward<const O>(o))(forward<const N>(n))))
      {return is0(sub(forward<const O>(o))(forward<const N>(n)));}
  };
  cex const GEq geq;

  using GT=Expr<Bb,Not,LEq>;
  const GT gt{};

  struct Eq:Combinator<Eq> {
    static cex  bool /*delta*/beta(int n,int o) {return n==o;}
    static cex  bool /*delta*/beta(double n,double o) {return n==o;}
    template<typename N,typename O>
    cex static auto beta(const N n,const O o)
      ->decltype(_and(leq(forward<const N>(n))(forward<const O>(o)))(leq(forward<const O>(o))(forward<const N>(n))))
      {return _and(leq(forward<const N>(n))(forward<const O>(o)))(leq(forward<const O>(o))(forward<const N>(n)));}
  };
  cex const Eq eq;

  using LT=Expr<Flip,GT>;
  const LT lt{};

  struct NEq:Combinator<NEq> {
    static cex  bool /*delta*/beta(int n,int o) {return n!=o;}
    static cex  bool /*delta*/beta(double n,double o) {return n!=o;}
    template<typename N,typename O>
    cex static auto beta(const N n,const O o)
      ->decltype(_or(gt(forward<const N>(n))(forward<const O>(o)))(gt(forward<const O>(o))(forward<const N>(n))))
      {return _or(gt(forward<const N>(n))(forward<const O>(o)))(gt(forward<const O>(o))(forward<const N>(n)));}
  };
  cex const NEq neq;

  //caution this can be damn slow to compile...
  template<int n,typename N=N0>
  struct FromInt:FromInt<n-1,decltype(succ(N{}))> {};
  template<typename N> struct FromInt<0,N>:N {};

  ///////////////////////////////////////////////////////////////////////////////
  // convert to int
  static cex int _plus1(int n){return n+1;}
  cex const Curry<decltype(&_plus1),&_plus1> plus1;

  template<typename N>
  cex auto _toInt(const N n)
    ->const decltype(n(plus1)(0))
    {return n(plus1)(0);}
  CurryTemplateFunction(_toInt) toInt;

  #ifdef YO_PRINT
    template<typename Out> Out& operator<<(Out& out,const Succ)  {return out<<"▲";}
    template<typename Out> Out& operator<<(Out& out,const N0)   {return out<<"#0";}
    template<typename Out> Out& operator<<(Out& out,const N1)   {return out<<"#1";}
    template<typename Out> Out& operator<<(Out& out,const N2)   {return out<<"#2";}
    template<typename Out> Out& operator<<(Out& out,const N3)   {return out<<"#3";}
    template<typename Out> Out& operator<<(Out& out,const N4)   {return out<<"#4";}
    template<typename Out> Out& operator<<(Out& out,const N5)   {return out<<"#5";}
    template<typename Out> Out& operator<<(Out& out,const N6)   {return out<<"#6";}
    template<typename Out> Out& operator<<(Out& out,const N7)   {return out<<"#7";}
    template<typename Out> Out& operator<<(Out& out,const N8)   {return out<<"#8";}
    template<typename Out> Out& operator<<(Out& out,const N9)   {return out<<"#9";}

    template<typename Out> Out& operator<<(Out& out,const Add)   {return out<<"⨁";}
    template<typename Out> Out& operator<<(Out& out,const Mul)   {return out<<"⨂";}
    template<typename Out> Out& operator<<(Out& out,const Pow)   {return out<<"(^)";}
    template<typename Out> Out& operator<<(Out& out,const Is0)   {return out<<"(0==)";}
    template<typename Out> Out& operator<<(Out& out,const Phi)   {return out<<"φ";}
    template<typename Out> Out& operator<<(Out& out,const Pred)  {return out<<"▼";}
    template<typename Out> Out& operator<<(Out& out,const Sub)   {return out<<"(-)";}
    template<typename Out> Out& operator<<(Out& out,const LEq)   {return out<<"(≤)";}
    template<typename Out> Out& operator<<(Out& out,const GEq)   {return out<<"(≥)";}
    template<typename Out> Out& operator<<(Out& out,const GT)    {return out<<"(>)";}
    template<typename Out> Out& operator<<(Out& out,const LT)    {return out<<"(<)";}
    template<typename Out> Out& operator<<(Out& out,const Eq)    {return out<<"(=)";}
    template<typename Out> Out& operator<<(Out& out,const NEq)   {return out<<"(≠)";}
    template<typename Out,int n> Out& operator<<(Out& out,const yo::FromInt<n>) {return out<<"fromInt<"<<n<<">";}
  #endif

};