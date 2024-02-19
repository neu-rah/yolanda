#pragma once

#include "list.h"
#include "curry.h"
#include "maybe.h"

namespace yo {
  //lambda
  using std::ostream;
  template<typename Prev,typename Param,int n>
  ostream& operator<<(ostream& out,const Lambda<Prev,Param,n> o) {
    if(n>0) {
      out<<o.prev<<"("<<o.param<<")";
      return out<<"{"<<n<<"}";
    } else return out<<beta(o);//beta reduce lazyness for output
  }

  //curry
  template<typename R,typename O,typename... OO>
  ostream& operator<<(ostream& out,const Func<R,O,OO...>) {return out<<("{c++}");}

  template<typename F,F f>
  ostream& operator<<(ostream& out,const Curry<F,f>) {return out<<("(...)");}

  //combinators
  ostream& operator<<(ostream& out,const I) {return out<<"id";}
  ostream& operator<<(ostream& out,const Id) {return out<<"id";}
  ostream& operator<<(ostream& out,const K) {return out<<"K";}
  ostream& operator<<(ostream& out,const S) {return out<<"S";}
  ostream& operator<<(ostream& out,const B) {return out<<"B";}
  ostream& operator<<(ostream& out,const C) {return out<<"C";}
  ostream& operator<<(ostream& out,const W) {return out<<"W";}
  ostream& operator<<(ostream& out,const T) {return out<<"T";}
  ostream& operator<<(ostream& out,const V) {return out<<"V";}
  ostream& operator<<(ostream& out,const M) {return out<<"M";}
  ostream& operator<<(ostream& out,const L) {return out<<"L";}
  ostream& operator<<(ostream& out,const Const) {return out<<"Const";}
  //booleans
  ostream& operator<<(ostream& out,const True)  {return out<<"true";}
  ostream& operator<<(ostream& out,const False) {return out<<"false";}
  ostream& operator<<(ostream& out,const Not)   {return out<<"not";}
  ostream& operator<<(ostream& out,const Or)    {return out<<"or";}
  ostream& operator<<(ostream& out,const And)   {return out<<"and";}
  ostream& operator<<(ostream& out,const BEq)   {return out<<"(==)";}
  //peano
  ostream& operator<<(ostream& out,const Add)            {return out<<"add";}
  ostream& operator<<(ostream& out,const Mul)            {return out<<"mul";}
  ostream& operator<<(ostream& out,const Pow)            {return out<<"pow";}
  ostream& operator<<(ostream& out,const Succ)           {return out<<"1+";}
  ostream& operator<<(ostream& out,const N0)             {return out<<"#0";}
  ostream& operator<<(ostream& out,const Succ::Bind<N0>) {return out<<"#1";}
  ostream& operator<<(ostream& out,const N1)             {return out<<"#1";}
  ostream& operator<<(ostream& out,const N2)             {return out<<"#2";}
  ostream& operator<<(ostream& out,const N3)             {return out<<"#3";}
  ostream& operator<<(ostream& out,const N4)             {return out<<"#4";}
  ostream& operator<<(ostream& out,const N5)             {return out<<"#5";}
  ostream& operator<<(ostream& out,const N6)             {return out<<"#6";}
  ostream& operator<<(ostream& out,const N7)             {return out<<"#7";}
  ostream& operator<<(ostream& out,const N8)             {return out<<"#8";}
  ostream& operator<<(ostream& out,const N9)             {return out<<"#9";}
  ostream& operator<<(ostream& out,const Is0)            {return out<<"is0";}
  ostream& operator<<(ostream& out,const Phi)            {return out<<"phi";}
  ostream& operator<<(ostream& out,const Pred)           {return out<<"pred";}
  ostream& operator<<(ostream& out,const Sub)            {return out<<"sub";}
  ostream& operator<<(ostream& out,const LEq)            {return out<<"(≤)";}
  ostream& operator<<(ostream& out,const GEq)            {return out<<"(≥)";}
  ostream& operator<<(ostream& out,const GT)             {return out<<"(>)";}
  ostream& operator<<(ostream& out,const LT)             {return out<<"(<)";}
  ostream& operator<<(ostream& out,const Eq)             {return out<<"(=)";}
  ostream& operator<<(ostream& out,const NEq)            {return out<<"(≠)";}
  // ostream& operator<<(ostream& out,const _FromInt)       {return out<<"_fromInt";}
  // ostream& operator<<(ostream& out,const  FromInt)       {return out<< "fromInt";}
  //list
  ostream& operator<<(ostream& out,const Cons)           {return out<<"cons";}
  ostream& operator<<(ostream& out,const Nil)            {return out<<"nil";}
  ostream& operator<<(ostream& out,const Head)           {return out<<"head";}
  ostream& operator<<(ostream& out,const Tail)           {return out<<"tail";}
  ostream& operator<<(ostream& out,const Null)           {return out<<"null";}
  ostream& operator<<(ostream& out,const _Length)        {return out<<"_length";}
  ostream& operator<<(ostream& out,const Length)         {return out<<"length";}
  ostream& operator<<(ostream& out,const Drop)           {return out<<"drop";}
  ostream& operator<<(ostream& out,const Index)          {return out<<"index";}
  ostream& operator<<(ostream& out,const _Last)          {return out<<"_last";}
  ostream& operator<<(ostream& out,const Last)           {return out<<"last";}
  ostream& operator<<(ostream& out,const _Concat)        {return out<<"_concat";}
  ostream& operator<<(ostream& out,const Concat)         {return out<<"concat";}
  ostream& operator<<(ostream& out,const _Init)          {return out<<"_init";}
  ostream& operator<<(ostream& out,const Init)           {return out<<"init";}
  ostream& operator<<(ostream& out,const _Reverse)       {return out<<"_reverse";}
  ostream& operator<<(ostream& out,const  Reverse)       {return out<< "reverse";}
  ostream& operator<<(ostream& out,const _TakeR)         {return out<<"_taker";}
  ostream& operator<<(ostream& out,const TakeR)          {return out<< "taker";}
  ostream& operator<<(ostream& out,const Take)           {return out<< "take";}
  ostream& operator<<(ostream& out,const Nats)           {return out<<"ℕ";}
  ostream& operator<<(ostream& out,const _Nats)          {return out<<"Nat";}
  ostream& operator<<(ostream& out,const Range)          {return out<<"range";}
  template<typename S>
  ostream& operator<<(ostream& out,const Expr<Nats,S> n) {return out<< "["<<S{}<<"..]";}
  ostream& operator<<(ostream& out,const _Map)           {return out<<"_map";}
  ostream& operator<<(ostream& out,const  Map)           {return out<< "map";}
  ostream& operator<<(ostream& out,const _Filter)        {return out<<"_filter";}
  ostream& operator<<(ostream& out,const  Filter)        {return out<< "filter";}
  ostream& operator<<(ostream& out,const _FoldL)         {return out<<"_foldl";}
  ostream& operator<<(ostream& out,const  FoldL)         {return out<< "foldl";}
  ostream& operator<<(ostream& out,const _FoldR)         {return out<<"_foldr";}
  ostream& operator<<(ostream& out,const  FoldR)         {return out<< "foldr";}
  ostream& operator<<(ostream& out,const _Zip)           {return out<<"_zip";}
  ostream& operator<<(ostream& out,const  Zip)           {return out<< "zip";}
  ostream& operator<<(ostream& out,const FromBool)       {return out<<"fromBool";}

  ostream& operator<<(ostream& out,const Nothing) {return out<<"Nothing";}
  ostream& operator<<(ostream& out,const Just) {return out<<"Just";}

  template<typename... OO>
  ostream& operator<<(ostream& out,const List<OO...> o) {
    if(beta(null(o)(true)(false))) return out<<"[]";
    else return out<<beta(head(o))<<":"<<beta(tail(o));}

  ///////////////////////////////////////////////////
  template<typename O>
  Str _toStr(const O o) {
    std::stringstream ss;
    ss<<o;
    return ss.str();
  }
  CurryTemplateFunction(_toStr,1) toStr;

};