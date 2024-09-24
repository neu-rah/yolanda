#pragma once

#include "peano.h"

namespace yo {
  // list --------------------------------------------------
  struct Cons:V{};
  cex const Cons cons;

  // struct Nil:Expr<K,K> {};
  using Nil=decltype(_K(_K));
  const Nil nil;

  using Head=Alt<Fst>;
  const Head head;

  using Tail=Alt<Snd>;
  const Tail tail;

  struct Null:Combinator<Null> {
    template<typename O> static cex auto beta(const O o)
      ->const decltype(o(_true(_true(_false))))
      {return o(_true(_true(_false)));}
  };
  cex const Null null;

  struct _Length:Combinator<_Length> {
    template<typename F,typename Cnt,typename X>
    static cex auto beta(const F f,const Cnt cnt,const X x)
      ->const decltype(null(x)(cnt)(f(succ(cnt))(tail(x))))
      {return null(x)(cnt)(f(succ(cnt))(tail(x)));}
  };
  cex const _Length _length;
  using Length=decltype(_Y(_length)(n0));//Expr<Y,_Length,N0>;
  cex const Length length;

  struct Drop:Combinator<Drop> {
    template<typename N,typename O>
    static cex auto beta(const N n,const O o)
      ->const decltype(n(tail)(o))
      {return n(tail)(o);}
  };
  cex const Drop drop;

  struct Index:Combinator<Index> {
    template<typename X,typename N>
    static cex auto beta(const X x,const N n)
      ->const decltype(head(n(tail)(x)))
      {return head(n(tail)(x));}
  };
  cex const Index index;

  struct _Last:Combinator<_Last> {
    template<typename F,typename O>
    static cex auto beta(const F f, const O o) 
      ->const decltype(null(o)
        (nil  )
        (null(tail(o))
          (head(o))
          (f(tail(o)))))
      {return null(o)
        (nil)
        (null(tail(o))
          (head(o))
          (f(tail(o))));}
  };
  using Last=decltype(_Y(_Last{}));//Expr<Y,_Last>;
  cex const Last last;

  struct _Concat:Combinator<_Concat> {
    template<typename F,typename A,typename B>
    static cex auto beta(const F f,const A a,const B b)
      ->const decltype(null(a)(b)(cons(head(a))(f(tail(a))(b))))
      {return null(a)
        (b)
        (cons
          (head(a))
          (f(tail(a))(b)));}
  };
  using Concat=decltype(_Y(_Concat{}));//Expr<Y,_Concat>;
  cex const Concat concat;

  struct _Init:Combinator<_Init> {
    template<typename F,typename O>
    static cex auto beta(const F f, const O o) 
      ->const decltype(null(o)
        (nil)
        (null(tail(o))
          (nil)
          (cons(head(o))(f(tail(o))))
        ))
      {return null(o)
        (nil)
        (null(tail(o))
          (nil)
          (cons(head(o))(f(tail(o))))
        );}
  };
  using Init=decltype(_Y(_Init{}));//Expr<Y,_Init>;
  cex const Init _init;

  struct _Reverse:Combinator<_Reverse> {
    template<typename F,typename A,typename L>
    static cex auto beta(const F f,const A a,const L l)
      ->const decltype(null(l)
        (a)
        (f(cons(head(l))(a))(tail(l))))
      {return null(l)
        (a)
        (f(cons(head(l))(a))(tail(l)));}
  };
  using Reverse=decltype(_Y(_Reverse{})(nil));//Expr<Y,_Reverse,Nil>;
  cex const Reverse reverse;

  struct _TakeR:Combinator<_TakeR> {
    template<typename F,typename To,typename N,typename From>
    static cex auto beta(const F f,const To to,const N n, const From from)
      ->const decltype(is0(n)(to)(f(_pair(head(from))(to))(pred(n))(tail(from))))
      {return is0(n)(to)(f(_pair(head(from))(to))(pred(n))(tail(from)));}
  };
  using TakeR=decltype(_Y(_TakeR{})(nil));//Expr<Y,_TakeR,Nil>;
  cex const TakeR taker;

  //take n elements from a list--
  struct Take:Combinator<Take> {
    template<typename N,typename O>//still the most compact one---
    static cex auto beta(const N n, const O o)
      ->decltype(reverse(taker(n)(o)))
      {return reverse(taker(n)(o));}
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
      ->const decltype(cons(n)(f(succ(n))))
      {return cons(n)(f(succ(n)));}
  };
  using NatsN=decltype(_Y(_Nats{}));//Expr<Y,_Nats>;
  cex NatsN natsn;

  //natural numbers (numerals), 1 to +∞ --
  // struct Nats:Expr<NatsN,N1> {};
  using Nats=decltype(natsn(n1));
  cex const Nats nats;

  //build a numerals range list--
  struct Range:Combinator<Range> {
    template<typename S,typename E>//still the most compact one---
    static cex auto beta(const S s, const E e)
      ->decltype(take(sub(e)(s))(natsn(s)))
      {return take(sub(e)(s))(natsn(s));}
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
      ->const decltype(null(o)
        (nil)
        (cons
          (f(head(o)))
          (g(f)(tail(o)))))
      {return null(o)
        (nil)
        (cons
          (f(head(o)))
          (g(f)(tail(o))));}  
  };
  using Map=decltype(_Y(_Map{}));//Expr<Y,_Map>;
  cex const Map _map;

  // λgfx. NULL x NIL (f (CAR x) (PAIR (CAR x)) I (g f (CDR x)))
  struct _Filter:Combinator<_Filter> {
    template<typename G,typename F, typename O>
    static cex auto beta(const G g, const F f, const O o)
      ->const decltype(null(o)
          (nil)
          (f
            (head(o))
            (cons(head(o)))
            (id)
            (g(f)(tail(o)))
          ))
      {return 
        null(o)
          (nil)
          (f
            (head(o))
            (cons(head(o)))
            (id)
            (g(f)(tail(o)))
          );}
  };
  using Filter=decltype(_Y(_Filter{}));//Expr<Y,_Filter>;
  cex const Filter filter;

  // λgfex. NULL x e (g f (f e (CAR x)) (CDR x))  
  struct _FoldL:Combinator<_FoldL> {
    template<typename G,typename F,typename E,typename X>
    static cex auto beta(const G g,const F f,const E e, const X x)
      ->const decltype(null(x)(e)(g(f)(f(e)(head(x)))(tail(x))))
      {return null(x)(e)(g(f)(f(e)(head(x)))(tail(x)));}
  };
  using FoldL=decltype(_Y(_FoldL{}));//Expr<Y,_FoldL>;
  cex const FoldL foldl;

  // FOLD-RIGHT := λfex. Y (λgy. NULL y e (f (CAR y) (g (CDR y)))) x
  struct _FoldR:Combinator<_FoldR> {
    template<typename F,typename E,typename G,typename H>
    static cex auto beta(const F f,const E e,const G g,const H h)
      ->const decltype(null(h)(e)(f(head(h))(g(tail(h)))))
      {return null(h)(e)(f(head(h))(g(tail(h))));}
  };

  struct FoldR:Combinator<FoldR> {
    template<typename F,typename E,typename X>
    static cex auto beta(const F f,const E e,const X x)
      ->const decltype(Y()(_FoldR()(f)(e))(x))
      {return Y()(_FoldR()(f)(e))(x);}
  };
  cex const FoldR foldr;

  struct _Zip:Combinator<_Zip> {
    template<typename F,typename A,typename B>
    static cex auto beta(const F f,const A a, const B b)
      ->const decltype(_or(null(a))(null(b))
        (nil)
        (cons
          (cons(head(a))(head(b)))
          (f(tail(a))(tail(b)))
        ))
      {return 
        _or(null(a))(null(b))
        (nil)
        (cons
          (cons(head(a))(head(b)))
          (f(tail(a))(tail(b)))
        );
      }
  };
  using Zip=decltype(_Y(_Zip{}));//Expr<Y,_Zip>;
  cex const Zip zip;

  // list sugar -----------
  template<typename...OO> struct List;
  template<typename...OO> cex List<OO...> list(const OO... oo);

  template<> struct List<>:Nil {using Nil::Nil;};

  template<typename O,typename...OO>
  struct List<O,OO...>:decltype(cons(O{})(List<OO...>{}))/*Expr<Cons,O,List<OO...>>*/ {
    using Tail=List<OO...>;
    using Base=decltype(cons(O{})(List<OO...>{}));//Expr<Cons,O,List<OO...>>;
    using Base::Base;
    cex List(const O o,const OO... oo):Base(cons(o)(list(oo...))) {}
  };

  template<typename...OO> cex List<OO...> list(const OO... oo) {return List<OO...>(oo...);}

  
};