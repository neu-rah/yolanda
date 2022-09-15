#pragma once

#include "peano.h"

#ifndef YO_DEBUG
  namespace yo {
#endif

  using Cons=V;
  using Nil=Expr<K,K>;

  //sugar...
  // template<typename... OO> struct List;
  // template<typename O,typename... OO> struct List<O,OO...>:Expr<Cons,O,List<OO...>> {};
  // template<typename O> struct List<O>:Expr<Cons,O,Nil> {};
  // template<> struct List<>:Nil {};

  using Head=Fst;
  using Tail=Snd;
  // using Null=Expr<T,Expr<True,Expr<True,False>>>;
  struct Null:Combinator<Null,1> {
    template<typename O> using Beta=Expr<O,Expr<True,Expr<True,False>>>;
    template<typename O> static auto beta(const O&&o)
      ->decltype(o(_true(_true(std::forward<const False>(_false)))))
      {return o(_true(_true(std::forward<const False>(_false))));}
  };

  constexpr const Cons cons;
  constexpr const Nil nil;
  constexpr const Null null;
  constexpr const Head head;
  constexpr const Tail tail;

  struct _Length:Combinator<_Length,3> {
    template<typename O> using Bind=Binder<_Length,O,2>;
    template<typename F,typename Cnt,typename X>
    using Beta=Expr<Null,X,Cnt,Expr<F,Expr<Succ,Cnt>,Expr<Tail,X>>>;
    template<typename F,typename Cnt,typename X>
    static auto beta(const F&&f,const Cnt&&cnt,const X&&x)
      ->decltype(null(std::forward<const X>(x))(std::forward<const Cnt>(cnt))(f(succ(std::forward<const Cnt>(cnt)))(tail(std::forward<const X>(x)))))
      {return null(std::forward<const X>(x))(std::forward<const Cnt>(cnt))(f(succ(std::forward<const Cnt>(cnt)))(tail(std::forward<const X>(x))));}
  };
  constexpr const _Length _length;
  using Length=Y::Bind<_Length>::Bind<N0>;
  constexpr const Length length;

  struct Drop:Combinator<Drop,2> {
    template<typename N,typename O>
    using Beta=Expr<N,Tail,O>;
    template<typename N,typename O>
    static auto beta(const N&&n,const O&&o)
      ->decltype(n(std::forward<const Tail>(tail))(std::forward<const O>(o)))
      {return n(std::forward<const Tail>(tail))(std::forward<const O>(o));}
  };
  constexpr const Drop drop;

  struct Index:Combinator<Index,2> {
    template<typename X,typename N>
    using Beta=Expr<Head,Expr<N,Tail,X>>;
    template<typename X,typename N>
    static auto beta(const X&&x,const N&&n)
      ->decltype(head(n(tail)(std::forward<const X>(x))))
      {return head(n(tail)(std::forward<const X>(x)));}
  };
  constexpr const Index _index;

  struct _Last:Combinator<_Last,2> {
    template<typename F,typename O>
    using Beta=Expr<Null,O,Nil,Expr<Null,Expr<Tail,O>,Expr<Head,O>,Expr<F,Expr<Tail,O>>>>;
    template<typename F,typename O>
    static auto beta(const F&&f, const O&&o) 
      ->decltype(null(std::forward<const O>(o))
        (std::forward<const Nil>(nil))
        (null(tail(std::forward<const O>(o)))
          (head(std::forward<const O>(o)))
          (f(tail(std::forward<const O>(o))))))
      {return null(std::forward<const O>(o))
        (std::forward<const Nil>(nil))
        (null(tail(std::forward<const O>(o)))
          (head(std::forward<const O>(o)))
          (f(tail(std::forward<const O>(o)))));}
  };
  using Last=Expr<Y,_Last>;
  constexpr const Last last;

  struct _Concat:Combinator<_Concat,3> {
    template<typename F,typename A,typename B>
    using Beta=Expr<Expr<Null,A>,B,Expr<Cons,Expr<Head,A>,Expr<F,Expr<Tail,A>,B>>>;
    template<typename F,typename A,typename B>
    static auto beta(const F&&f,const A&&a,const B&&b)
      ->decltype(null(a)(b)(cons(head(a))(f(tail(a))(b))))
      {return null(std::forward<const A>(a))
        (std::forward<const B>(b))
        (cons
          (head(std::forward<const A>(a)))
          (f(tail(std::forward<const A>(a)))(std::forward<const B>(b))));}
  };
  using Concat=Expr<Y,_Concat>;
  constexpr const Concat concat;
  
  struct _Init:Combinator<_Init,2> {
    template<typename F,typename O>
    using Beta=Expr<
      Null,O,
      Nil,
      Expr<
        Null,Expr<Tail,O>,
        Nil,
        Expr<
          Pair,Expr<Head,O>,Expr<F,Expr<Tail,O>>
        >
      >
    >;
    template<typename F,typename O>
    static auto beta(const F&&f, const O&&o) 
      ->decltype(null(std::forward<const O>(o))
        (std::forward<const Nil>(nil))
        (null(tail(std::forward<const O>(o)))
          (std::forward<const Nil>(nil))
          (cons(head(std::forward<const O>(o)))(f(tail(std::forward<const O>(o)))))
        ))
      {return null(std::forward<const O>(o))
        (std::forward<const Nil>(nil))
        (null(tail(std::forward<const O>(o)))
          (std::forward<const Nil>(nil))
          (cons(head(std::forward<const O>(o)))(f(tail(std::forward<const O>(o)))))
        );}
  };
  using Init=Expr<Y,_Init>;
  constexpr const Init _init;

  struct _Reverse:Combinator<_Reverse,3> {
    template<typename F,typename A,typename L>
    using Beta=Expr<
      Null,L,
      A,
      Expr<
        F,Expr<
          Pair,
          Expr<Head,L>,
          A
        >,
        Expr<Tail,L>
      >
    >;
    template<typename F,typename A,typename L>
    static auto beta(const F&&f,const A&&a,const L&&l)
      ->decltype(null(std::forward<const L>(l))
        (std::forward<const A>(a))
        (f(cons(head(std::forward<const L>(l)))(std::forward<const A>(a)))(tail(std::forward<const L>(l)))))
      {return null(std::forward<const L>(l))
        (std::forward<const A>(a))
        (f(cons(head(std::forward<const L>(l)))(std::forward<const A>(a)))(tail(std::forward<const L>(l))));}
  };
  using Reverse=Expr<Y,_Reverse,Nil>;
  constexpr const Reverse _reverse;

  //infinit list of numerals starting at N
  struct _Nats:Combinator<_Nats,2> {
    template<typename F,typename N>
    using Beta=Expr<Cons,N,Expr<F,Expr<Succ,N>>>;
    template<typename F,typename N>
    static auto  beta(const F&&f,const N&&n)
      ->decltype(cons(std::forward<const N>(n))(f(succ(std::forward<const N>(n)))))
      {return cons(std::forward<const N>(n))(f(succ(std::forward<const N>(n))));}
  };
  using NatsN=Expr<Y,_Nats>;

  struct Nats:Expr<NatsN,N1> {};
  constexpr const Nats nats;

  struct _Map:Combinator<_Map,3> {
    template<typename G,typename F, typename O>
    using Beta=Expr<
      Expr<Null,O>,
      Nil,
      Expr<
        Cons,
        Expr<F,Expr<Head,O>>,
        Expr<G,F,Expr<Tail,O>>
      >
    >;
    template<typename G,typename F, typename O>
    static auto beta(const G&&g,const F&&f,const O&&o)
      ->decltype(null(std::forward<const O>(o))
        (std::forward<const Nil>(nil))
        (cons
          (f(head(std::forward<const O>(o))))
          (g(std::forward<const F>(f))(tail(std::forward<const O>(o))))))
      {return null(std::forward<const O>(o))
        (std::forward<const Nil>(nil))
        (cons
          (f(head(std::forward<const O>(o))))
          (g(std::forward<const F>(f))(tail(std::forward<const O>(o)))));}  
  };

  using Map=Expr<Y,_Map>;
  constexpr const Map _map;

  // λgfx. NULL x NIL (f (CAR x) (PAIR (CAR x)) I (g f (CDR x)))
  struct _Filter:Combinator<_Filter,3> {
    template<typename G,typename F, typename O>
    using Beta=
      Expr<
        Expr<Null,O>,
        Nil,
        Expr<
          F,
          Expr<Head,O>,
          Expr<
            Cons,
            Expr<Head,O>
          >,
          I,
          Expr<G,F,Expr<Tail,O>>
        >
      >;
    template<typename G,typename F, typename O>
    static auto beta(const G&&g, const F&&f, const O&&o)
      ->decltype(null(std::forward<const O>(o))
          (std::forward<const Nil>(nil))
          (f
            (head(std::forward<const O>(o)))
            (cons(head(std::forward<const O>(o))))
            (std::forward<const Id>(id))
            (g(std::forward<const F>(f))(tail(std::forward<const O>(o))))
          ))
      {return 
        null(std::forward<const O>(o))
          (std::forward<const Nil>(nil))
          (f
            (head(std::forward<const O>(o)))
            (cons(head(std::forward<const O>(o))))
            (std::forward<const Id>(id))
            (g(std::forward<const F>(f))(tail(std::forward<const O>(o))))
          );}
  };
  using Filter=Expr<Y,_Filter>;
  constexpr const Filter filter;

  // λgfex. NULL x e (g f (f e (CAR x)) (CDR x))  
  struct _FoldL:Combinator<_FoldL,4> {
    template<typename G,typename F,typename E,typename X>
    using Beta=Expr<
      Expr<Null,X>,
      E,
      Expr<
        G,
        F,
        Expr<F,E,Expr<Head,X>>,
        Expr<Tail,X>
      >
    >;
    template<typename G,typename F,typename E,typename X>
    static auto beta(const G&&g,const F&&f,const E&&e, const X&&x)
      ->decltype(null(std::forward<const X>(x))
        (std::forward<const E>(e))
        (g
          (std::forward<const F>(f))
          (f
            (std::forward<const E>(e))
            (head(std::forward<const X>(x)))
          )
          (tail(std::forward<const X>(x)))))
      {return null(std::forward<const X>(x))
        (std::forward<const E>(e))
        (g
          (std::forward<const F>(f))
          (f
            (std::forward<const E>(e))
            (head(std::forward<const X>(x)))
          )
          (tail(std::forward<const X>(x))));}
  };
  using FoldL=Expr<Y,_FoldL>;
  constexpr const FoldL foldl;

  // FOLD-RIGHT := λfex. Y (λgy. NULL y e (f (CAR y) (g (CDR y)))) x
  struct _FoldR:Combinator<_FoldR,4> {
    template<typename F,typename E,typename G,typename H>
    using Beta=Expr<
      Expr<Null,H>,
      E,
      Expr<
        F,
        Expr<Head,H>,
        Expr<G,Expr<Tail,H>>
      >
    >;
    template<typename F,typename E,typename G,typename H>
    static auto beta(const F&&f,const E&&e,const G&&g,const H&&h)
      ->decltype(null(std::forward<const H>(h))
        (std::forward<const E>(e))
        (f(head(std::forward<const H>(h)))(g(tail(std::forward<const H>(h))))))
      {return null(std::forward<const H>(h))
        (std::forward<const E>(e))
        (f(head(std::forward<const H>(h)))(g(tail(std::forward<const H>(h)))));}
  };

  struct FoldR:Combinator<FoldR,3> {
    template<typename F,typename E,typename X>
    using Beta=Expr<Y,Expr<_FoldR,F,E>,X>;
    template<typename F,typename E,typename X>
    static auto beta(const F&&f,const E&&e,const X&&x)
      ->decltype(Y()(_FoldR()(std::forward<const F>(f))(std::forward<const E>(e)))(std::forward<const X>(x)))
      {return Y()(_FoldR()(std::forward<const F>(f))(std::forward<const E>(e)))(std::forward<const X>(x));}
  };
  constexpr const FoldR foldr;

  struct _Zip:Combinator<_Zip,3> {
    template<typename F,typename A,typename B>
    using Beta=
      typename If<Expr<Or,Expr<Null,A>,Expr<Null,B>>>
      ::template Then<Nil>
      ::template Else<
        Expr<
          Cons,
          Expr<Cons,Expr<Head,A>,Expr<Head,B>>,
          Expr<F,Expr<Tail,A>,Expr<Tail,B>>
        >
      >;
    template<typename F,typename A,typename B>
    static auto beta(const F&&f,const A&&a, const B&&b)
      ->decltype(_or(null(std::forward<const A>(a)))(null(std::forward<const B>(b)))
        (std::forward<const Nil>(nil))
        (cons
          (cons
            (head(std::forward<const A>(a)))
            (head(std::forward<const B>(b)))
          )
          (f(tail(std::forward<const A>(a)))(tail(std::forward<const B>(b))))
        ))
      {return 
        _or(null(std::forward<const A>(a)))(null(std::forward<const B>(b)))
        (std::forward<const Nil>(nil))
        (cons
          (cons
            (head(std::forward<const A>(a)))
            (head(std::forward<const B>(b)))
          )
          (f(tail(std::forward<const A>(a)))(tail(std::forward<const B>(b))))
        );
      }
  };
  using Zip=Expr<Y,_Zip>;
  constexpr const Zip zip;

  // list sugar -----------
  template<typename...OO> struct List;
  template<typename O,typename...OO> struct List<O,OO...>:Expr<yo::Cons,O,List<OO...>> {
    using Base=Expr<yo::Cons,O,List<OO...>>;
  };
  template<> struct List<>:Nil {
    using Base=Nil;
  };



#ifndef YO_DEBUG
  };
#endif
