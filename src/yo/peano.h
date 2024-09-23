#pragma once

#include "combinators.h"
#include "curry.h"
#include "bool.h"

namespace yo {
  // peano ----------------------------------------------
  using Succ=decltype(_S(_B));//Expr<S,B>;
  const Succ succ;

  struct Add:Combinator<Add> {
    static cex int beta(int n,int o) {return n+o;}
    static cex int beta(double n,double o) {return n+o;}
    template<typename N,typename O>
    static cex auto beta(const N n,const O o)
      ->const decltype(n(succ)(o))
      {return n(succ)(o);}
  };
  constexpr const Add _add;

  using Mul=Alt<B>;
  cex const Mul mul;

  using Pow=Alt<T>;
  cex const Pow _pow;

  using N0=Alt<False>;
  cex const N0 n0;
  using N1=Alt<Id>;
  cex const N1 n1;
  using N2=decltype(succ(n1));//Expr<Succ,N1>;
  cex const N2 n2;
  using N3=decltype(succ(n2));//Expr<Succ,N2>;
  cex const N3 n3;
  using N4=decltype(succ(n3));//Expr<Succ,N3>;
  cex const N4 n4;
  using N5=decltype(succ(n4));//Expr<Succ,N4>;
  cex const N5 n5;
  using N6=decltype(succ(n5));//Expr<Succ,N5>;
  cex const N6 n6;
  using N7=decltype(succ(n6));//Expr<Succ,N6>;
  cex const N7 n7;
  using N8=decltype(succ(n7));//Expr<Succ,N7>;
  cex const N8 n8;
  using N9=decltype(succ(n8));//Expr<Succ,N8>;
  cex const N9 n9;


  struct Is0:Combinator<Is0> {
    static cex bool delta(int n) {return n==0;}
    static cex bool delta(double n) {return n==0.0;}
    template<typename O>
    cex static auto beta(const O o)
      ->decltype(o(_true(_false))(_true))
      {return    o(_true(_false))(_true);}
  };
  cex const Is0 is0;

  struct Phi:Combinator<Phi> {
    template<typename O>
    cex static auto beta(const O o)
      ->decltype(_pair(snd(o))(succ(snd(o))))
      {return _pair(snd(o))(succ(snd(o)));}
  };

  struct Pred:Combinator<Pred> {
    using N0N0=decltype(_pair(n0)(n0));//Expr<Pair,N0,N0>;
    static int    delta(int n){return n-1;}
    static double delta(double n){return n-1;}
    template<typename N>
    cex static auto beta(const N n)
      ->decltype(fst(n(Phi())(N0N0{})))
      {return fst(n(Phi())(N0N0{}));}
  };
  cex const Pred pred;

  struct Sub:Combinator<Sub> {
    static cex int delta(int n,int o) {return n-o;}
    static cex int delta(double n,double o) {return n-o;}
    template<typename N,typename O>
    cex static auto beta(const N n, const O o)
      ->decltype(o(pred)(n))
      {return o(pred)(n);}
  };
  cex const Sub sub;

  struct LEq:Combinator<LEq> {
    static cex  bool delta(int n,int o) {return n<=o;}
    static cex  bool delta(double n,double o) {return n<=o;}
    template<typename N,typename O>
    cex static auto beta(const N n,const O o)
      ->decltype(is0(sub(n)(o)))
      {return is0(sub(n)(o));}
  };
  cex const LEq leq;

  struct GEq:Combinator<GEq> {
    static cex  bool delta(int n,int o) {return n>=o;}
    static cex  bool delta(double n,double o) {return n>=o;}
    template<typename N,typename O>
    cex static auto beta(const N n,const O o)
      ->decltype(is0(sub(o)(n)))
      {return is0(sub(o)(n));}
  };
  cex const GEq geq;

  using GT=decltype(_Bb(_not)(leq));//Expr<Bb,Not,LEq>;
  const GT gt;

  struct Eq:Combinator<Eq> {
    static cex  bool delta(int n,int o) {return n==o;}
    static cex  bool delta(double n,double o) {return n==o;}
    template<typename N,typename O>
    cex static auto beta(const N n,const O o)
      ->decltype(_and(leq(n)(o))(leq(o)(n)))
      {return _and(leq(n)(o))(leq(o)(n));}
  };
  cex const Eq eq;

  using LT=decltype(_C(gt));//Expr<Flip,GT>;
  const LT lt;

  struct NEq:Combinator<NEq> {
    static cex  bool delta(int n,int o) {return n!=o;}
    static cex  bool delta(double n,double o) {return n!=o;}
    template<typename N,typename O>
    cex static auto beta(const N n,const O o)
      ->decltype(_or(gt(n)(o))(gt(o)(n)))
      {return _or(gt(n)(o))(gt(o)(n));}
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
    {return (n(plus1)(0));}
  CurryTemplateFunction(_toInt) toInt;

  #ifdef YO_PRINT
    template<typename Out> Out& operator<<(Out& out,const yo::N0)   {return out<<"#0";}
    template<typename Out> Out& operator<<(Out& out,const yo::N1)   {return out<<"#1";}
    template<typename Out> Out& operator<<(Out& out,const yo::N2)   {return out<<"#2";}
    template<typename Out> Out& operator<<(Out& out,const yo::N3)   {return out<<"#3";}
    template<typename Out> Out& operator<<(Out& out,const yo::N4)   {return out<<"#4";}
    template<typename Out> Out& operator<<(Out& out,const yo::N5)   {return out<<"#5";}
    template<typename Out> Out& operator<<(Out& out,const yo::N6)   {return out<<"#6";}
    template<typename Out> Out& operator<<(Out& out,const yo::N7)   {return out<<"#7";}
    template<typename Out> Out& operator<<(Out& out,const yo::N8)   {return out<<"#8";}
    template<typename Out> Out& operator<<(Out& out,const yo::N9)   {return out<<"#9";}

    template<typename Out> Out& operator<<(Out& out,const yo::Add)   {return out<<"(+)";}
    template<typename Out> Out& operator<<(Out& out,const yo::Mul)   {return out<<"(*)";}
    template<typename Out> Out& operator<<(Out& out,const yo::Pow)   {return out<<"(^)";}
    template<typename Out> Out& operator<<(Out& out,const yo::Is0)   {return out<<"(0==)";}
    template<typename Out> Out& operator<<(Out& out,const yo::Succ)  {return out<<"(++)";}
    template<typename Out> Out& operator<<(Out& out,const yo::Phi)  {return out<<"φ";}
    template<typename Out> Out& operator<<(Out& out,const yo::Pred)  {return out<<"(--)";}
    template<typename Out> Out& operator<<(Out& out,const yo::Sub)   {return out<<"(-)";}
    template<typename Out> Out& operator<<(Out& out,const yo::LEq)   {return out<<"(≤)";}
    template<typename Out> Out& operator<<(Out& out,const yo::GEq)   {return out<<"(≥)";}
    template<typename Out> Out& operator<<(Out& out,const yo::GT)    {return out<<"(>)";}
    template<typename Out> Out& operator<<(Out& out,const yo::LT)    {return out<<"(<)";}
    template<typename Out> Out& operator<<(Out& out,const yo::Eq)    {return out<<"(=)";}
    template<typename Out> Out& operator<<(Out& out,const yo::NEq)   {return out<<"(≠)";}
    template<typename Out,int n> Out& operator<<(Out& out,const yo::FromInt<n>)   {return out<<"fromInt<"<<n<<">";}
  #endif
};