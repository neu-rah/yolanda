#pragma once

#include "combinator.h"
#include "list.h"
#include "data.h"
#include "maybe.h"

#ifndef YO_DEBUG
  namespace yo {
#endif
  #ifdef ARDUINO
    Str show(const int n) {return Str(n);}
  #else
    Str show(const int n) {return std::to_string(n);}
  #endif
  Str show(const unsigned char t) {
    #ifdef ARDUINO
      return Str(t);
    #else
      return Str(1,t);
    #endif
  }
  Str show(const char* const t) {return t;}
  Str show(const I&) {return "id";}
  Str show(const K&o) {return "true";}
  Str show(const S&o) {return "S";}
  Str show(const B&o) {return "B";}
  Str show(const V&o) {return "V";}
  Str show(const M&o) {return "M";}
  Str show(const T&o) {return "T";}
  Str show(const Succ&o) {return "succ";}
  Str show(const Phi&o) {return "ϕ";}
  Str show(const Pred&o) {return "pred";}
  Str show(const False&o) {return "false";}
  Str show(const Flip&o) {return "flip";}
  Str show(const Fst&o) {return "fst";}
  Str show(const Snd&o) {return "snd";}
  Str show(const Null&o) {return "null";}
  Str show(const _Length&o) {return "length";}
  Str show(const Index&o) {return "index";}
  Str show(const _Last&o) {return "last";}
  Str show(const _Concat&o) {return "concat";}
  Str show(const _Init&o) {return "init";}
  Str show(const _Reverse&o) {return "reverse";}
  Str show(const _Filter&o) {return "filter";}
  Str show(const _Map&o) {return "map";}
  Str show(const _FoldL&o) {return "foldl";}
  Str show(const _FoldR&o) {return "foldr";}
  Str show(const _Zip&o) {return "zip";}
  Str show(const _Nats&o) {return "ℕ";}
  Str show(const Is0&o) {return "is0";}
  Str show(const Add&o) {return "add";}
  Str show(const Nothing&o) {return "nothing";}
  Str show(const Just&o) {return "just";}
  Str show(const Text&o) {return o.data;}
  Str show(const Bool&o) {return o.data?"true":"false";}
  template<bool v>
  Str show(const StaticBool<v>&o) {return v?"true":"false";}
  // template<typename... OO>
  // Str show(const List<OO...>&o) {
  //   return (toBool(null(o)))?(Str("[]")):(Str("(")+show(head(o))+","+show(tail(o))+")");
  // }


  template<typename Data,Data data>
  Str show(const StaticData<Data,data>&o) {return show((Data)o);}
  template<int n>
  Str show(const StaticInt<n>&) {
    #ifdef ARDUINO
      return Str(n);
    #else
      return std::to_string(n);
    #endif
  }
  // template<typename T> Str show(const Type<T>&o) {return showType<Type<T>>();}

  Str show(const Str&o) {return o;}

  template<typename T>
  Str show(const Data<T>&o) {return show(o.data);}

  template<typename Prev,typename Arg,int n>
  Str show(const Binder<Prev,Arg, n>&o) {return show(Prev())+" "+show(Arg());}

  template<typename Prev,typename A,typename B,int m,int n>
  Str show(const Binder<Prev,Binder<A,B,m>,n>&o) {return show(Prev())+"("+show(Binder<A,B,m>())+")";}

  template<typename Prev,typename Arg,int n>
  Str show(const Lambda<Prev,Arg, n>&o) {return show(o.prev)+" "+show(o.param);}

  template<typename Prev,typename A,typename B,int m,int n>
  Str show(const Lambda<Prev,Lambda<A,B,m>,n>&o) {return show(o.prev)+"("+show(o.param)+")";}

  template<typename R,typename O,typename... OO,Func<R,O,OO...>f>
  Str show(const Curry<Func<R,O,OO...>,f>&) {return "{c++}";}

  template<> Str show(const Expr<>&){return "";};
  template<typename O,typename...OO>
  Str show(const Expr<O,OO...>&){return show(O())+" "+show(Expr<OO...>());};


  // type show -----------------
  template<typename O> struct Show {};
  template<typename Data, Data data>
  struct Show< StaticData<Data,data> > {static Str type(){return showType<const Data>();}};
  // template<int n> struct Show<StaticData<int,n>> {static Str type(){return show(n);}};
  template<> struct Show<const int> {static Str type(){return "int";}};
  template<const char* const*text> struct Show<StaticText<text>> {static Str type(){return text[0];}};
  template<> struct Show<Type<int>> {static Str type(){return "Int";}};
  template<> struct Show<Type<unsigned int>> {static Str type(){return "Int";}};
  template<> struct Show<Type<bool>> {static Str type() {return "Bool";}};
  template<> struct Show<Type<const char*>> {static Str type(){return "Str";}};
  template<> struct Show<Type<const char* const*>> {static Str type(){return "StaticText";}};
  template<> struct Show<Type<const double>> {static Str type(){return "Double";}};
  template<> struct Show<I> {static Str type(){return "I";}};
  template<> struct Show<K> {static Str type(){return "K";}};
  template<> struct Show<S> {static Str type(){return "S";}};
  template<> struct Show<B> {static Str type(){return "B";}};
  template<> struct Show<V> {static Str type(){return "V";}};
  template<> struct Show<T> {static Str type(){return "T";}};
  template<> struct Show<M> {static Str type(){return "M";}};
  template<> struct Show<C> {static Str type(){return "C";}};
  template<> struct Show<Succ> {static Str type() {return "Succ";}};
  template<> struct Show<False> {static Str type() {return "False";}};
  // template<> struct Show<Flip> {static Str type() {return "Flip";}};
  template<> struct Show<Fst> {static Str type(){return "Fst";}};
  template<> struct Show<Snd> {static Str type(){return "Snd";}};
  template<> struct Show<Null> {static Str type() {return "Null";}};
  template<> struct Show<Index> {static Str type() {return "Index";}};
  template<> struct Show<_Last> {static Str type() {return "last";}};
  template<> struct Show<_Concat> {static Str type() {return "Concat";}};
  template<> struct Show<Is0> {static Str type() {return "Is0";}};
  template<> struct Show<_Init> {static Str type(){return "Init";}};
  template<> struct Show<_Length> {static Str type(){return "Length";}};
  template<> struct Show<_Map> {static Str type(){return "Map";}};
  template<> struct Show<_FoldL> {static Str type(){return "FoldL";}};
  template<> struct Show<_FoldR> {static Str type(){return "FoldR";}};
  template<> struct Show<_Zip> {static Str type(){return "Zip";}};
  template<> struct Show<Nothing> {static Str type(){return "Nothing";}};
  template<> struct Show<Just> {static Str type(){return "Just";}};
  // template<> struct Show<Length> {static Str type(){return "length";}};

  template<typename Prev,typename Arg,int n>
  struct Show<Binder<Prev, Arg, n>> {static Str type(){return Show<Prev>::type()+" "+Show<Arg>::type();}};
  template<typename Prev,typename A,typename B,int m,int n>
  struct Show<Binder<Prev, Binder<A,B,m>, n>> {static Str type(){return Show<Prev>::type()+"("+Show<Binder<A,B,m>>::type()+")";}};

  template<typename Prev,typename A,typename B,int m,int n>
  struct Show<Binder<Prev, Lambda<A,B,m>, n>> {static Str type(){return *Show<Prev>::type()+"("+Show<Lambda<A,B,m>>::type()+")";}};

  template<typename Prev,typename Arg,int n>
  struct Show<Lambda<Prev, Arg, n>> {static Str type(){return Show<Prev>::type()+" "+Show<Arg>::type();}};
  template<typename Prev,typename A,typename B,int m,int n>
  struct Show<const Lambda<Prev, Lambda<A,B,m>, n>> {static Str type(){return showType<Prev>()+"("+showType<Lambda<A,B,m>>()+")";}};

  template<> struct Show<Expr<>> {static Str type(){return "";}};
  template<typename O,typename...OO>
  struct Show<Expr<O,OO...>> {static Str type(){return Show<O>::type()+" "+Show<Expr<OO...>>::type();}};

  template<typename O> Str showType() {return Show<O>::type();}

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
