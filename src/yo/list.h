#pragma once

#include "peano.h"

namespace yo {
  // list --------------------------------------------------
  struct Cons:V{};
  cex const Cons cons;

  // struct Nil:Expr<K,K> {};
  using Nil=Expr<K,K>;
  const Nil nil{};

  using Head=Alt<Fst>;
  const Head head{};

  using Tail=Alt<Snd>;
  const Tail tail{};

  struct Null:Combinator<Null> {
    template<typename O> static cex auto beta(const O o)
      ->const decltype(o(_true(_true(_false))))
      {return o(_true(_true(_false)));}
  };
  cex const Null null;

  struct _Length:Combinator<_Length> {
    template<typename F,typename Cnt,typename X>
    static cex auto beta(const F f,const Cnt cnt,const X x)
      ->const decltype(null(forward<const X>(x))(forward<const Cnt>(cnt))(f(succ(forward<const Cnt>(cnt)))(tail(forward<const X>(x)))))
      {return null(forward<const X>(x))(forward<const Cnt>(cnt))(f(succ(forward<const Cnt>(cnt)))(tail(forward<const X>(x))));}
  };
  cex const _Length _length;
  using Length=Expr<Y,_Length,N0>;
  cex const Length length{};

  struct Drop:Combinator<Drop> {
    template<typename N,typename O>
    static cex auto beta(const N n,const O o)
      ->const decltype(n(move(tail))(forward<const O>(o)))
      {return n(move(tail))(forward<const O>(o));}
  };
  cex const Drop drop;

  struct Index:Combinator<Index> {
    template<typename X,typename N>
    static cex auto beta(const X x,const N n)
      ->const decltype(head(n(move(tail))(forward<const X>(x))))
      {return head(n(move(tail))(forward<const X>(x)));}
  };
  cex const Index index;

  struct _Last:Combinator<_Last> {
    template<typename F,typename O>
    static cex auto beta(const F f, const O o) 
      ->const decltype(null(forward<const O>(o))
        (nil)
        (null(tail(forward<const O>(o)))
          (head(forward<const O>(o)))
          (f(tail(forward<const O>(o))))))
      {return null(forward<const O>(o))
        (nil)
        (null(tail(forward<const O>(o)))
          (head(forward<const O>(o)))
          (f(tail(forward<const O>(o)))));}
  };
  using Last=Expr<Y,_Last>;
  cex const Last last{};

  struct _Concat:Combinator<_Concat> {
    template<typename F,typename A,typename B>
    static cex auto beta(const F f,const A a,const B b)
      ->const decltype(null(forward<const A>(a))
        (forward<const B>(b))
        (cons
          (head(forward<const A>(a)))
          (f(tail(forward<const A>(a)))(forward<const B>(b)))))
      {return null(forward<const A>(a))
        (forward<const B>(b))
        (cons
          (head(forward<const A>(a)))
          (f(tail(forward<const A>(a)))(forward<const B>(b))));}
  };
  using Concat=Expr<Y,_Concat>;
  cex const Concat concat{};

  struct _Init:Combinator<_Init> {
    template<typename F,typename O>
    static cex auto beta(const F f, const O o) 
      ->const decltype(null(forward<const O>(o))
        (nil)
        (null(tail(forward<const O>(o)))
          (nil)
          (cons(head(forward<const O>(o)))(f(tail(forward<const O>(o)))))
        ))
      {return null(forward<const O>(o))
        (nil)
        (null(tail(forward<const O>(o)))
          (nil)
          (cons(head(forward<const O>(o)))(f(tail(forward<const O>(o)))))
        );}
  };
  using Init=Expr<Y,_Init>;
  cex const Init _init{};

  struct _Reverse:Combinator<_Reverse> {
    template<typename F,typename A,typename L>
    static cex auto beta(const F f,const A a,const L l)
      ->const decltype(null(forward<const L>(l))
        (forward<const A>(a))
        (f(cons(head(forward<const L>(l)))(forward<const A>(a)))(tail(forward<const L>(l)))))
      {return null(forward<const L>(l))
        (forward<const A>(a))
        (f(cons(head(forward<const L>(l)))(forward<const A>(a)))(tail(forward<const L>(l))));}
  };
  using Reverse=Expr<Y,_Reverse,Nil>;
  cex const Reverse reverse{};

  struct _TakeR:Combinator<_TakeR> {
    template<typename F,typename To,typename N,typename From>
    static cex auto beta(const F f,const To to,const N n, const From from)
      ->const decltype(is0(forward<const N>(n))(forward<const To>(to))(f(_pair(head(forward<const From>(from)))(forward<const To>(to)))(pred(forward<const N>(n)))(tail(forward<const From>(from)))))
      {return is0(forward<const N>(n))(forward<const To>(to))(f(_pair(head(forward<const From>(from)))(forward<const To>(to)))(pred(forward<const N>(n)))(tail(forward<const From>(from))));}
  };
  using TakeR=Expr<Y,_TakeR,Nil>;
  cex const TakeR taker{};

  //take n elements from a list--
  struct Take:Combinator<Take> {
    template<typename N,typename O>//still the most compact one---
    static cex auto beta(const N n, const O o)
      ->decltype(reverse(taker(forward<const N>(n))(forward<const O>(o))))
      {return reverse(taker(forward<const N>(n))(forward<const O>(o)));}
  };
  // struct _Take:Combinator<_Take> {
  //   template<typename F,typename N,typename O>
  //   static cex auto beta(const F f,const N n,const O o) 
  //     ->const decltype(_or(is0(n))(null(o))(nil)(cons(head(o))(f(pred(n))(tail(o)))))
  //     {return _or(is0(n))(null(o))(nil)(cons(head(o))(f(pred(n))(tail(o))));}
  // };
  // using Take=decltype(_Y(_Take{}));
  cex const Take take;

  //infinit list of numerals starting at N--
  struct _Nats:Combinator<_Nats> {
    template<typename F,typename N>
    static cex auto  beta(const F f,const N n)
      ->const decltype(cons(forward<const N>(n))(f(succ(forward<const N>(n)))))
      {return cons(forward<const N>(n))(f(succ(forward<const N>(n))));}
  };
  using NatsN=Expr<Y,_Nats>;
  cex NatsN natsn{};

  //natural numbers (numerals), 1 to +∞ --
  // struct Nats:Expr<NatsN,N1> {};
  using Nats=Expr<NatsN,N1>;
  cex const Nats nats{};

  //build a numerals range list--
  struct Range:Combinator<Range> {
    template<typename S,typename E>//still the most compact one---
    static cex auto beta(const S s, const E e)
      ->decltype(take(sub(forward<const E>(e))(forward<const S>(s)))(natsn(forward<const S>(s))))
      {return take(sub(forward<const E>(e))(forward<const S>(s)))(natsn(forward<const S>(s)));}
  };
  // struct Range:Combinator<Range> {
  //   template<typename S,typename E>
  //   static cex auto beta(const S s, const E e)
  //     ->const decltype(take(sub(e)(s))(nats(s)))
  //     {return take(sub(e)(s))(nats(s));}
  // };
  cex const Range range;

  struct _Map:Combinator<_Map> {
    template<typename G,typename F, typename O>
    static cex auto beta(const G g,const F f,const O o)
      ->const decltype(null(forward<const O>(o))
        (nil)
        (cons
          (f(head(forward<const O>(o))))
          (g(forward<const F>(f))(tail(forward<const O>(o))))))
      {return null(forward<const O>(o))
        (nil)
        (cons
          (f(head(forward<const O>(o))))
          (g(forward<const F>(f))(tail(forward<const O>(o)))));}
  };
  using Map=Expr<Y,_Map>;
  cex const Map _map{};

  // λgfx. NULL x NIL (f (CAR x) (PAIR (CAR x)) I (g f (CDR x)))
  struct _Filter:Combinator<_Filter> {
    template<typename G,typename F, typename O>
    static cex auto beta(const G g, const F f, const O o)
      ->const decltype(null(forward<const O>(o))
          (nil)
          (f
            (head(forward<const O>(o)))
            (cons(head(forward<const O>(o))))
            (id)
            (g(forward<const F>(f))(tail(forward<const O>(o))))
          ))
      {return 
        null(forward<const O>(o))
          (nil)
          (f
            (head(forward<const O>(o)))
            (cons(head(forward<const O>(o))))
            (id)
            (g(forward<const F>(f))(tail(forward<const O>(o))))
          );}
  };
  using Filter=Expr<Y,_Filter>;
  cex const Filter filter{};

  // λgfex. NULL x e (g f (f e (CAR x)) (CDR x))  
  struct _FoldL:Combinator<_FoldL> {
    template<typename G,typename F,typename E,typename X>
    static cex auto beta(const G g,const F f,const E e, const X x)
      ->const decltype(null(forward<const X>(x))(forward<const E>(e))(g(forward<const F>(f))(f(forward<const E>(e))(head(forward<const X>(x))))(tail(forward<const X>(x)))))
      {return null(forward<const X>(x))(forward<const E>(e))(g(forward<const F>(f))(f(forward<const E>(e))(head(forward<const X>(x))))(tail(forward<const X>(x))));}
  };
  using FoldL=Expr<Y,_FoldL>;
  cex const FoldL foldl{};

  // FOLD-RIGHT := λfex. Y (λgy. NULL y e (f (CAR y) (g (CDR y)))) x
  struct _FoldR:Combinator<_FoldR> {
    template<typename F,typename E,typename G,typename H>
    static cex auto beta(const F f,const E e,const G g,const H h)
      ->const decltype(null(forward<const H>(h))(forward<const E>(e))(f(head(forward<const H>(h)))(g(tail(forward<const H>(h))))))
      {return null(forward<const H>(h))(forward<const E>(e))(f(head(forward<const H>(h)))(g(tail(forward<const H>(h)))));}
  };

  struct FoldR:Combinator<FoldR> {
    template<typename F,typename E,typename X>
    static cex auto beta(const F f,const E e,const X x)
      ->const decltype(Y{}(_FoldR{}(forward<const F>(f))(forward<const E>(e)))(forward<const X>(x)))
      {return Y{}(_FoldR{}(forward<const F>(f))(forward<const E>(e)))(forward<const X>(x));}
  };
  cex const FoldR foldr;

  struct _Zip:Combinator<_Zip> {
    template<typename F,typename A,typename B>
    static cex auto beta(const F f,const A a, const B b)
      ->const decltype(_or(null(forward<const A>(a)))(null(forward<const B>(b)))
        (nil)
        (cons
          (cons(head(forward<const A>(a)))(head(forward<const B>(b))))
          (f(tail(forward<const A>(a)))(tail(forward<const B>(b))))
        ))
      {return 
        _or(null(forward<const A>(a)))(null(forward<const B>(b)))
        (nil)
        (cons
          (cons(head(forward<const A>(a)))(head(forward<const B>(b))))
          (f(tail(forward<const A>(a)))(tail(forward<const B>(b))))
        );
      }
  };
  using Zip=Expr<Y,_Zip>;
  cex const Zip zip{};

  template<typename...OO> struct List;
  template<typename O,typename...OO>
  struct List<O,OO...>:Expr<Cons,O,List<OO...>> {
    cex List(const O o,const OO... oo):Expr<Cons,O,List<OO...>>(cons,forward<const O>(o),List<OO...>(forward<const OO>(oo)...)) {}
  };
  template<> struct List<>:Nil {using Nil::Nil;};

  template<typename...OO> cex List<OO...> list(const OO... oo) {return List<OO...>(forward<const OO>(oo)...);}

  #ifdef YO_PRINT
    template<typename Out> Out& operator<<(Out& out,const Cons)           {return out<<"cons";}
    template<typename Out> Out& operator<<(Out& out,const Nil)            {return out<<"nil";}
    template<typename Out> Out& operator<<(Out& out,const Head)           {return out<<"head";}
    template<typename Out> Out& operator<<(Out& out,const Tail)           {return out<<"tail";}
    template<typename Out> Out& operator<<(Out& out,const Null)           {return out<<"null";}
    template<typename Out> Out& operator<<(Out& out,const _Length)        {return out<<"_length";}
    template<typename Out> Out& operator<<(Out& out,const Length)         {return out<<"length";}
    template<typename Out> Out& operator<<(Out& out,const Drop)           {return out<<"drop";}
    template<typename Out> Out& operator<<(Out& out,const Index)          {return out<<"index";}
    template<typename Out> Out& operator<<(Out& out,const _Last)          {return out<<"_last";}
    template<typename Out> Out& operator<<(Out& out,const Last)           {return out<<"last";}
    template<typename Out> Out& operator<<(Out& out,const _Concat)        {return out<<"concat";}
    template<typename Out> Out& operator<<(Out& out,const Concat)         {return out<<"concat";}
    template<typename Out> Out& operator<<(Out& out,const _Init)          {return out<<"_init";}
    template<typename Out> Out& operator<<(Out& out,const Init)           {return out<<"init";}
    template<typename Out> Out& operator<<(Out& out,const _Reverse)       {return out<<"_reverse";}
    template<typename Out> Out& operator<<(Out& out,const  Reverse)       {return out<< "reverse";}
    template<typename Out> Out& operator<<(Out& out,const _TakeR)         {return out<<"_taker";}
    template<typename Out> Out& operator<<(Out& out,const TakeR)          {return out<< "taker";}
    // template<typename Out> Out& operator<<(Out& out,const _Take)           {return out<< "_take";}
    template<typename Out> Out& operator<<(Out& out,const Take)           {return out<< "take";}
    template<typename Out> Out& operator<<(Out& out,const Nats)           {return out<<"ℕ";}
    template<typename Out> Out& operator<<(Out& out,const _Nats)          {return out<<"Nat";}
    template<typename Out> Out& operator<<(Out& out,const Range)          {return out<<"range";}
    template<typename Out,typename S> Out& operator<<(Out& out,const Expr<Nats,S> n)  {return out<< "["<<S{}<<"..]";}
    template<typename Out> Out& operator<<(Out& out,const _Map)           {return out<<"_map";}
    template<typename Out> Out& operator<<(Out& out,const  Map)           {return out<< "map";}
    template<typename Out> Out& operator<<(Out& out,const _Filter)        {return out<<"_filter";}
    template<typename Out> Out& operator<<(Out& out,const  Filter)        {return out<< "filter";}
    template<typename Out> Out& operator<<(Out& out,const _FoldL)         {return out<<"_foldl";}
    template<typename Out> Out& operator<<(Out& out,const  FoldL)         {return out<< "foldl";}
    template<typename Out> Out& operator<<(Out& out,const _FoldR)         {return out<<"_foldr";}
    template<typename Out> Out& operator<<(Out& out,const  FoldR)         {return out<< "foldr";}
    template<typename Out> Out& operator<<(Out& out,const _Zip)           {return out<<"_zip";}
    template<typename Out> Out& operator<<(Out& out,const  Zip)           {return out<< "zip";}

    #ifdef YO_VERB
      template<typename Out,typename O,typename... OO>
      Out& operator<<(Out& out,const List<O,OO...> o){
        if(beta(null(o)(1)(0))) return out;
        else return out/*<<"(@"<<&beta(head(o))<<"|"*/<<beta(head(o))<<":"<<beta(tail(o));
      }
    #else
      template<typename Out> Out& operator<<(Out& out,const List<> o){return out<<"[]";}
      
      // template<typename Out,typename O,typename... OO>
      // Out& operator<<(Out& out,const List<O,OO...> o) {return out<<beta(head(o))<<":"<<beta(tail(o));}
      template<typename Out,typename O,typename... OO>
      Out& operator<<(Out& out,const List<O,OO...> o){out<<o.tail.head;out<<':';return out<<o.tail.tail.head;}
    #endif

  #endif

};