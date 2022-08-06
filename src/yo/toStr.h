#pragma once

#include "combinator.h"
#include "list.h"
#include "data.h"
#include "maybe.h"

#ifndef YO_DEBUG
  namespace yo {
#endif
  #ifdef ARDUINO
    Str toStr(const int n) {return Str(n);}
  #else
    Str toStr(const int n) {return std::to_string(n);}
  #endif
  Str toStr(const unsigned char t) {
    #ifdef ARDUINO
      return Str(t);
    #else
      return Str(1,t);
    #endif
  }
  Str toStr(const char* const t) {return t;}
  Str toStr(const I&) {return "id";}
  Str toStr(const K&o) {return "true";}
  Str toStr(const S&o) {return "S";}
  Str toStr(const B&o) {return "B";}
  Str toStr(const V&o) {return "V";}
  Str toStr(const M&o) {return "M";}
  Str toStr(const T&o) {return "T";}
  Str toStr(const Succ&o) {return "succ";}
  Str toStr(const Phi&o) {return "ϕ";}
  Str toStr(const Pred&o) {return "pred";}
  Str toStr(const False&o) {return "false";}
  Str toStr(const Flip&o) {return "flip";}
  Str toStr(const Fst&o) {return "fst";}
  Str toStr(const Snd&o) {return "snd";}
  Str toStr(const Null&o) {return "null";}
  Str toStr(const _Length&o) {return "length";}
  Str toStr(const Index&o) {return "index";}
  Str toStr(const _Last&o) {return "last";}
  Str toStr(const _Concat&o) {return "concat";}
  Str toStr(const _Init&o) {return "init";}
  Str toStr(const _Reverse&o) {return "reverse";}
  Str toStr(const _Filter&o) {return "filter";}
  Str toStr(const _Map&o) {return "map";}
  Str toStr(const _FoldL&o) {return "foldl";}
  Str toStr(const _FoldR&o) {return "foldr";}
  Str toStr(const _Zip&o) {return "zip";}
  Str toStr(const _Nats&o) {return "ℕ";}
  Str toStr(const Is0&o) {return "is0";}
  Str toStr(const Add&o) {return "add";}
  Str toStr(const Nothing&o) {return "nothing";}
  Str toStr(const Just&o) {return "just";}
  Str toStr(const Text&o) {return o.data;}
  Str toStr(const Bool&o) {return o.data?"true":"false";}
  template<bool v>
  Str toStr(const StaticBool<v>&o) {return v?"true":"false";}
  // template<typename... OO>
  // Str toStr(const List<OO...>&o) {
  //   return (toBool(null(o)))?(Str("[]")):(Str("(")+toStr(head(o))+","+toStr(tail(o))+")");
  // }


  template<typename Data,Data data>
  Str toStr(const StaticData<Data,data>&o) {return toStr((Data)o);}
  template<int n>
  Str toStr(const StaticInt<n>&) {
    #ifdef ARDUINO
      return Str(n);
    #else
      return std::to_string(n);
    #endif
  }
  // template<typename T> Str toStr(const Type<T>&o) {return showType<Type<T>>();}

  Str toStr(const Str&o) {return o;}

  template<typename T>
  Str toStr(const Data<T>&o) {return toStr(o.data);}

  template<typename Prev,typename Arg,int n>
  Str toStr(const Binder<Prev,Arg, n>&o) {return toStr(Prev())+" "+toStr(Arg());}

  template<typename Prev,typename A,typename B,int m,int n>
  Str toStr(const Binder<Prev,Binder<A,B,m>,n>&o) {return toStr(Prev())+"("+toStr(Binder<A,B,m>())+")";}

  template<typename Prev,typename Arg,int n>
  Str toStr(const Lambda<Prev,Arg, n>&o) {return toStr(o.prev)+" "+toStr(o.param);}

  template<typename Prev,typename A,typename B,int m,int n>
  Str toStr(const Lambda<Prev,Lambda<A,B,m>,n>&o) {return toStr(o.prev)+"("+toStr(o.param)+")";}

  template<typename R,typename O,typename... OO,Func<R,O,OO...>f>
  Str toStr(const Curry<Func<R,O,OO...>,f>&) {return "{c++}";}

  template<> Str toStr(const Expr<>&){return "";};
  template<typename O,typename...OO>
  Str toStr(const Expr<O,OO...>&){return toStr(O())+" "+toStr(Expr<OO...>());};


  // type toStr -----------------
  template<typename O> struct ToStr {};
  template<typename Data, Data data>
  struct ToStr< StaticData<Data,data> > {static Str type(){return showType<const Data>();}};
  // template<int n> struct ToStr<StaticData<int,n>> {static Str type(){return toStr(n);}};
  template<> struct ToStr<const int> {static Str type(){return "int";}};
  template<const char* const*text> struct ToStr<StaticText<text>> {static Str type(){return text[0];}};
  template<> struct ToStr<Type<int>> {static Str type(){return "Int";}};
  template<> struct ToStr<Type<unsigned int>> {static Str type(){return "Int";}};
  template<> struct ToStr<Type<bool>> {static Str type() {return "Bool";}};
  template<> struct ToStr<Type<const char*>> {static Str type(){return "Str";}};
  template<> struct ToStr<Type<const char* const*>> {static Str type(){return "StaticText";}};
  template<> struct ToStr<Type<const double>> {static Str type(){return "Double";}};
  template<> struct ToStr<I> {static Str type(){return "I";}};
  template<> struct ToStr<K> {static Str type(){return "K";}};
  template<> struct ToStr<S> {static Str type(){return "S";}};
  template<> struct ToStr<B> {static Str type(){return "B";}};
  template<> struct ToStr<V> {static Str type(){return "V";}};
  template<> struct ToStr<T> {static Str type(){return "T";}};
  template<> struct ToStr<M> {static Str type(){return "M";}};
  template<> struct ToStr<C> {static Str type(){return "C";}};
  template<> struct ToStr<Succ> {static Str type() {return "Succ";}};
  template<> struct ToStr<False> {static Str type() {return "False";}};
  // template<> struct ToStr<Flip> {static Str type() {return "Flip";}};
  template<> struct ToStr<Fst> {static Str type(){return "Fst";}};
  template<> struct ToStr<Snd> {static Str type(){return "Snd";}};
  template<> struct ToStr<Null> {static Str type() {return "Null";}};
  template<> struct ToStr<Index> {static Str type() {return "Index";}};
  template<> struct ToStr<_Last> {static Str type() {return "last";}};
  template<> struct ToStr<_Concat> {static Str type() {return "Concat";}};
  template<> struct ToStr<Is0> {static Str type() {return "Is0";}};
  template<> struct ToStr<_Init> {static Str type(){return "Init";}};
  template<> struct ToStr<_Length> {static Str type(){return "Length";}};
  template<> struct ToStr<_Map> {static Str type(){return "Map";}};
  template<> struct ToStr<_FoldL> {static Str type(){return "FoldL";}};
  template<> struct ToStr<_FoldR> {static Str type(){return "FoldR";}};
  template<> struct ToStr<_Zip> {static Str type(){return "Zip";}};
  template<> struct ToStr<Nothing> {static Str type(){return "Nothing";}};
  template<> struct ToStr<Just> {static Str type(){return "Just";}};
  template<> struct ToStr<Show> {static Str type(){return "show";}};
  // template<> struct ToStr<Length> {static Str type(){return "length";}};

  template<typename Prev,typename Arg,int n>
  struct ToStr<Binder<Prev, Arg, n>> {static Str type(){return ToStr<Prev>::type()+" "+ToStr<Arg>::type();}};
  template<typename Prev,typename A,typename B,int m,int n>
  struct ToStr<Binder<Prev, Binder<A,B,m>, n>> {static Str type(){return ToStr<Prev>::type()+"("+ToStr<Binder<A,B,m>>::type()+")";}};

  template<typename Prev,typename A,typename B,int m,int n>
  struct ToStr<Binder<Prev, Lambda<A,B,m>, n>> {static Str type(){return *ToStr<Prev>::type()+"("+ToStr<Lambda<A,B,m>>::type()+")";}};

  template<typename Prev,typename Arg,int n>
  struct ToStr<Lambda<Prev, Arg, n>> {static Str type(){return ToStr<Prev>::type()+" "+ToStr<Arg>::type();}};
  template<typename Prev,typename A,typename B,int m,int n>
  struct ToStr<const Lambda<Prev, Lambda<A,B,m>, n>> {static Str type(){return showType<Prev>()+"("+showType<Lambda<A,B,m>>()+")";}};

  template<> struct ToStr<Expr<>> {static Str type(){return "";}};
  template<typename O,typename...OO>
  struct ToStr<Expr<O,OO...>> {static Str type(){return ToStr<O>::type()+" "+ToStr<Expr<OO...>>::type();}};

  template<typename O> Str showType() {return ToStr<O>::type();}

  // template<typename E> Str code(const E&e);

  // #ifdef ARDUINO
  //   Str _code(const int n) {return Str(n);}
  // #else
  //   Str _code(const int n) {return to_string(n);}
  // #endif
  // Str _code(const char*t) {return t;}
  // Str _code(const I&) {return "id";}
  // Str _code(const K&o) {return "_true";}
  // Str _code(const S&o) {return "_S";}
  // Str _code(const Succ&o) {return "succ";}
  // Str _code(const False&o) {return "_false";}
  // Str _code(const Flip&o) {return "flip";}
  // Str _code(const _Length&o) {return "_length";}
  // Str _code(const Index&o) {return "index";}
  // Str _code(const Is0&o) {return "is0";}
  // // template<typename T> Str code(const Type<T>&o) {return code<Type<T>>();}

  // template<typename Prev,typename Arg,int n>
  // Str _code(const Binder<Prev,Arg, n>&o) {return code(Prev())+" "+code(Arg());}

  // template<typename Prev,typename A,typename B,int m,int n>
  // Str _code(const Binder<Prev,Binder<A,B,m>,n>&o) {return code(Prev())+"("+::code(Binder<A,B,m>())+")";}

  // template<typename Prev,typename Arg,int n>
  // Str _code(const Lambda<Prev,Arg, n>&o) {return code(o.prev)+" "+::code(o.param);}

  // template<typename Prev,typename A,typename B,int m,int n>
  // Str _code(const Lambda<Prev,Lambda<A,B,m>,n>&o) {return code(o.prev)+"("+code(o.param)+")";}

  // template<typename R,typename O,typename... OO,Func<R,O,OO...>f>
  // Str _code(const Curry<Func<R,O,OO...>,f>&) {return "{c++}";}

  // template<typename E>
  // Str code(const E&e) {return "("+_code(e)+")";}

  // template<typename O> Str code();

  // template<typename O> struct Code {};
  // template<typename Data, Data data>
  // struct Code< StaticData<Data,data> >
  //   {static Str code() {return ::code<const Data>();}};
  // template<int n>
  // struct Code<StaticData<int,n>>
  //   {static Str code() {return "StaticInt<"+::code(n)+">()";}};
  // template<const char* const*text>
  // struct Code<StaticText<text>> {static Str code() {return "StaticText<"+Str(text[0])+">()";}};
  // template<> struct Code<Type<int>> {static Str code() {return "Int";}};
  // template<> struct Code<Type<unsigned int>> {static Str code() {return "Int";}};
  // template<> struct Code<Type<bool>> {static Str code() {return "Bool";}};
  // template<> struct Code<Type<const char*>> {static Str code() {return "Str";}};
  // template<> struct Code<Type<const double>> {static Str code() {return "Double";}};
  // template<> struct Code<I> {static Str code() {return "_I";}};
  // template<> struct Code<K> {static Str code() {return "_K";}};
  // template<> struct Code<S> {static Str code() {return "_S";}};
  // template<> struct Code<_Length> {static Str code() {return "length";}};
  // template<typename Prev,typename Arg,int n>
  // struct Code<Binder<Prev, Arg, n>> 
  // {static Str code() {return ::code<Prev>()+"("+::code<Arg>()+")";}};
  // template<typename Prev,typename A,typename B,int m,int n>
  // struct Code<Binder<Prev, Binder<A,B,m>, n>> 
  // {static Str code() {return ::code<Prev>()+"("+::code<Binder<A,B,m>>()+")";}};
  // template<> struct Code<Expr<>> {static Str code() {return "";}};
  // template<typename O,typename...OO>
  // struct Code<Expr<O,OO...>> 
  // {static Str code() {return "("+::code<O>()+::code<Expr<OO...>>()+")";}};

  // template<typename O> Str code() {return "("+Code<O>::code()+")";}
  // template<> Str code<Expr<>>() {return "";}
#ifndef YO_DEBUG
  };
#endif
