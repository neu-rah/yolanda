#pragma once

#include "peano.h"

namespace yo {
  // list --------------------------------------------------
  struct Cons:V{};
  constexpr const Cons cons;

  struct Nil:Expr<K,K> {};
  const Nil nil;

  using Head=Expr<Fst>;
  const Head head;

  using Tail=Expr<Snd>;
  const Tail tail;

  struct Null:Combinator<Null,1> {
    template<typename O> static auto beta(const O o)
      ->decltype(o(_true(_true(_false))))
      {return o(_true(_true(_false)));}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  constexpr const Null null;

  struct _Length:Combinator<_Length,3> {
    template<typename F,typename Cnt,typename X>
    static auto beta(const F f,const Cnt cnt,const X x)
      ->decltype(null(x)(cnt)(f(succ(cnt))(tail(x))))
      {return null(x)(cnt)(f(succ(cnt))(tail(x)));}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  constexpr const _Length _length;
  using Length=Y::Bind<_Length>::Bind<N0>;
  constexpr const Length length;

  struct Drop:Combinator<Drop,2> {
    template<typename N,typename O>
    static auto beta(const N n,const O o)
      ->decltype(n(tail)(o))
      {return n(tail)(o);}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  constexpr const Drop drop;

  struct Index:Combinator<Index,2> {
    template<typename X,typename N>
    static auto beta(const X x,const N n)
      ->decltype(head(n(tail)(x)))
      {return head(n(tail)(x));}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  constexpr const Index index;

  struct _Last:Combinator<_Last,2> {
    template<typename F,typename O>
    static auto beta(const F f, const O o) 
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
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  using Last=Expr<Y,_Last>;
  constexpr const Last last;

  struct _Concat:Combinator<_Concat,3> {
    template<typename F,typename A,typename B>
    static auto beta(const F f,const A a,const B b)
      ->decltype(null(a)(b)(cons(head(a))(f(tail(a))(b))))
      {return null(a)
        (b)
        (cons
          (head(a))
          (f(tail(a))(b)));}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  using Concat=Expr<Y,_Concat>;
  constexpr const Concat concat;

  struct _Init:Combinator<_Init,2> {
    template<typename F,typename O>
    static auto beta(const F f, const O o) 
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
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  using Init=Expr<Y,_Init>;
  constexpr const Init init;

  struct _Reverse:Combinator<_Reverse,3> {
    template<typename F,typename A,typename L>
    static auto beta(const F f,const A a,const L l)
      ->decltype(null(l)
        (a)
        (f(cons(head(l))(a))(tail(l))))
      {return null(l)
        (a)
        (f(cons(head(l))(a))(tail(l)));}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  using Reverse=Expr<Y,_Reverse,Nil>;
  constexpr const Reverse reverse;

  struct _TakeR:Combinator<_TakeR,4> {
    template<typename F,typename To,typename N,typename From>
    static auto beta(const F f,const To to,const N n, const From from)
      ->decltype(is0(n)(to)(f(_pair(head(from))(to))(pred(n))(tail(from))))
      {return is0(n)(to)(f(_pair(head(from))(to))(pred(n))(tail(from)));}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  using TakeR=Expr<Y,_TakeR,Nil>;
  constexpr const TakeR taker;

  //take n elements from a list
  struct Take:Combinator<Take,2> {
    template<typename N,typename O>
    static auto beta(const N n, const O o)
      ->decltype(reverse(taker(n)(o)))
      {return reverse(taker(n)(o));}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  constexpr const Take take;

   //infinit list of numerals starting at N
  struct _Nats:Combinator<_Nats,2> {
    template<typename F,typename N>
    static auto  beta(const F f,const N n)
      ->decltype(cons(n)(f(succ(n))))
      {return cons(n)(f(succ(n)));}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  using NatsN=Expr<Y,_Nats>;
  constexpr NatsN natsn;

  struct Nats:Expr<NatsN,N1> {};
  constexpr const Nats nats;

  struct Range:Combinator<Range,2> {
    template<typename S,typename E>
    static auto beta(const S s, const E e)
      ->decltype(take(sub(e)(s))(natsn(s)))
      {return take(sub(e)(s))(natsn(s));}
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  constexpr const Range range;

  struct _Map:Combinator<_Map,3> {
    template<typename G,typename F, typename O>
    static auto beta(const G g,const F f,const O o)
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
    template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  using Map=Expr<Y,_Map>;
  constexpr const Map _map;

  // λgfx. NULL x NIL (f (CAR x) (PAIR (CAR x)) I (g f (CDR x)))
  struct _Filter:Combinator<_Filter,3> {
    template<typename G,typename F, typename O>
    static auto beta(const G g, const F f, const O o)
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
     template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  using Filter=Expr<Y,_Filter>;
  constexpr const Filter filter;

  // λgfex. NULL x e (g f (f e (CAR x)) (CDR x))  
  struct _FoldL:Combinator<_FoldL,4> {
    template<typename G,typename F,typename E,typename X>
    static auto beta(const G g,const F f,const E e, const X x)
      ->decltype(null(x)(e)(g(f)(f(e)(head(x)))(tail(x))))
      {return null(x)(e)(g(f)(f(e)(head(x)))(tail(x)));}
     template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  using FoldL=Expr<Y,_FoldL>;
  constexpr const FoldL foldl;

  // FOLD-RIGHT := λfex. Y (λgy. NULL y e (f (CAR y) (g (CDR y)))) x
  struct _FoldR:Combinator<_FoldR,4> {
    template<typename F,typename E,typename G,typename H>
    static auto beta(const F f,const E e,const G g,const H h)
      ->decltype(null(h)(e)(f(head(h))(g(tail(h)))))
      {return null(h)(e)(f(head(h))(g(tail(h))));}
     template<typename... OO> using Beta=decltype(beta(OO{}...));
  };

  struct FoldR:Combinator<FoldR,3> {
    template<typename F,typename E,typename X>
    static auto beta(const F f,const E e,const X x)
      ->decltype(Y()(_FoldR()(f)(e))(x))
      {return Y()(_FoldR()(f)(e))(x);}
     template<typename... OO> using Beta=decltype(beta(OO{}...));
  };
  constexpr const FoldR foldr;

  struct _Zip:Combinator<_Zip,3> {
    template<typename F,typename A,typename B>
    static auto beta(const F f,const A a, const B b)
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
  constexpr const Zip zip;

  // list sugar -----------
  template<typename...OO> struct List;
  template<typename O,typename...OO>
  struct List<O,OO...>:Expr<yo::Cons,O,List<OO...>> {
    List() {}
    List(const O o,const OO... oo):Expr<yo::Cons,O,List<OO...>>(cons(o)(List<OO...>(oo...))) {}
  };
  template<> struct List<>:Nil {
    using Nil::Nil;
  };

  template<typename...OO> List<OO...> list(const OO... oo) {return List<OO...>(oo...);}
  
};
