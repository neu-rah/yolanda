#pragma once

#include "peano.h"

namespace yo {
  // list --------------------------------------------------
  struct Cons:V{};
  cex const Cons cons;

  struct Nil:Expr<K,K> {};
  const Nil nil;

  using Head=Alt<Fst>;
  const Head head;

  using Tail=Alt<Snd>;
  const Tail tail;

  struct Null:Combinator<Null> {
    using Combinator::beta;
    template<typename O> static cex auto beta(const O o)
      ->decltype(o(_true(_true(_false))))
      {return o(_true(_true(_false)));}
  };
  cex const Null null;

  struct _Length:Combinator<_Length> {
    using Combinator::beta;
    template<typename F,typename Cnt,typename X>
    static cex auto beta(const F f,const Cnt cnt,const X x)
      ->decltype(null(x)(cnt)(f(succ(cnt))(tail(x))))
      {return null(x)(cnt)(f(succ(cnt))(tail(x)));}
  };
  cex const _Length _length;
  using Length=Expr<Y,_Length,N0>;
  cex const Length length;

  struct Drop:Combinator<Drop> {
    using Combinator::beta;
    template<typename N,typename O>
    static cex auto beta(const N n,const O o)
      ->decltype(n(tail)(o))
      {return n(tail)(o);}
  };
  cex const Drop drop;

  struct Index:Combinator<Index> {
    using Combinator::beta;
    template<typename X,typename N>
    static cex auto beta(const X x,const N n)
      ->decltype(head(n(tail)(x)))
      {return head(n(tail)(x));}
  };
  cex const Index index;

  struct _Last:Combinator<_Last> {
    using Combinator::beta;
    template<typename F,typename O>
    static cex auto beta(const F f, const O o) 
      ->decltype(null(o)
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
  using Last=Expr<Y,_Last>;
  cex const Last last;

  struct _Concat:Combinator<_Concat> {
    using Combinator::beta;
    template<typename F,typename A,typename B>
    static cex auto beta(const F f,const A a,const B b)
      ->decltype(null(a)(b)(cons(head(a))(f(tail(a))(b))))
      {return null(a)
        (b)
        (cons
          (head(a))
          (f(tail(a))(b)));}
  };
  using Concat=Expr<Y,_Concat>;
  cex const Concat concat;

  struct _Init:Combinator<_Init> {
    using Combinator::beta;
    template<typename F,typename O>
    static cex auto beta(const F f, const O o) 
      ->decltype(null(o)
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
  using Init=Expr<Y,_Init>;
  cex const Init _init;

  struct _Reverse:Combinator<_Reverse> {
    using Combinator::beta;
    template<typename F,typename A,typename L>
    static cex auto beta(const F f,const A a,const L l)
      ->decltype(null(l)
        (a)
        (f(cons(head(l))(a))(tail(l))))
      {return null(l)
        (a)
        (f(cons(head(l))(a))(tail(l)));}
  };
  using Reverse=Expr<Y,_Reverse,Nil>;
  cex const Reverse reverse;

  struct _TakeR:Combinator<_TakeR> {
    using Combinator::beta;
    template<typename F,typename To,typename N,typename From>
    static cex auto beta(const F f,const To to,const N n, const From from)
      ->decltype(is0(n)(to)(f(_pair(head(from))(to))(pred(n))(tail(from))))
      {return is0(n)(to)(f(_pair(head(from))(to))(pred(n))(tail(from)));}
  };
  using TakeR=Expr<Y,_TakeR,Nil>;
  cex const TakeR taker;

  //take n elements from a list
  struct Take:Combinator<Take> {
    using Combinator::beta;
    template<typename N,typename O>
    static cex auto beta(const N n, const O o)
      ->decltype(reverse(taker(n)(o)))
      {return reverse(taker(n)(o));}
  };
  cex const Take take;

    //infinit list of numerals starting at N
  struct _Nats:Combinator<_Nats> {
    using Combinator::beta;
    template<typename F,typename N>
    static cex auto  beta(const F f,const N n)
      ->decltype(cons(n)(f(succ(n))))
      {return cons(n)(f(succ(n)));}
  };
  using NatsN=Expr<Y,_Nats>;
  cex NatsN natsn;

  struct Nats:Expr<NatsN,N1> {};
  cex const Nats nats;

  struct Range:Combinator<Range> {
    using Combinator::beta;
    template<typename S,typename E>
    static cex auto beta(const S s, const E e)
      ->decltype(take(sub(e)(s))(natsn(s)))
      {return take(sub(e)(s))(natsn(s));}
  };
  cex const Range range;

  struct _Map:Combinator<_Map> {
    using Combinator::beta;
    template<typename G,typename F, typename O>
    static cex auto beta(const G g,const F f,const O o)
      ->decltype(null(o)
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
  using Map=Expr<Y,_Map>;
  cex const Map _map;

  // λgfx. NULL x NIL (f (CAR x) (PAIR (CAR x)) I (g f (CDR x)))
  struct _Filter:Combinator<_Filter> {
    using Combinator::beta;
    template<typename G,typename F, typename O>
    static cex auto beta(const G g, const F f, const O o)
      ->decltype(null(o)
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
  using Filter=Expr<Y,_Filter>;
  cex const Filter filter;

  // λgfex. NULL x e (g f (f e (CAR x)) (CDR x))  
  struct _FoldL:Combinator<_FoldL> {
    using Combinator::beta;
    template<typename G,typename F,typename E,typename X>
    static cex auto beta(const G g,const F f,const E e, const X x)
      ->decltype(null(x)(e)(g(f)(f(e)(head(x)))(tail(x))))
      {return null(x)(e)(g(f)(f(e)(head(x)))(tail(x)));}
  };
  using FoldL=Expr<Y,_FoldL>;
  cex const FoldL foldl;

  // FOLD-RIGHT := λfex. Y (λgy. NULL y e (f (CAR y) (g (CDR y)))) x
  struct _FoldR:Combinator<_FoldR> {
    template<typename F,typename E,typename G,typename H>
    static cex auto beta(const F f,const E e,const G g,const H h)
      ->decltype(null(h)(e)(f(head(h))(g(tail(h)))))
      {return null(h)(e)(f(head(h))(g(tail(h))));}
  };

  struct FoldR:Combinator<FoldR> {
    template<typename F,typename E,typename X>
    static cex auto beta(const F f,const E e,const X x)
      ->decltype(Y()(_FoldR()(f)(e))(x))
      {return Y()(_FoldR()(f)(e))(x);}
  };
  cex const FoldR foldr;

  struct _Zip:Combinator<_Zip> {
    using Combinator::beta;
    template<typename F,typename A,typename B>
    static cex auto beta(const F f,const A a, const B b)
      ->decltype(_or(null(a))(null(b))
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
  using Zip=Expr<Y,_Zip>;
  cex const Zip zip;

  // list sugar -----------
  template<typename...OO> struct List;
  template<> struct List<>:Nil {using Nil::Nil;};
  template<typename O,typename...OO>
  struct List<O,OO...>:Expr<Cons,O,List<OO...>> {
    using Tail=List<OO...>;
    cex List(const O o,const OO... oo):Expr<Cons,O,List<OO...>>(cons,o,List<OO...>(oo...)) {}
  };

  template<typename...OO> cex List<OO...> list(const OO... oo) {return List<OO...>(oo...);}

  // template<typename Out> Out& operator<<(Out& out,const Nil) {return out<<"nil";}

};