#pragma once

// #define cex
#define cex constexpr

// #define cex
#define cex constexpr

namespace yo {
    template<bool chk, typename T> using When=typename enable_if<chk,T>::type;

  template<typename H,typename... TT>
  struct Expr<H,TT...>:App {
    using Head=H;
    using Tail=Expr<TT...>;
    Head head;
    cex Expr():head{},tail{}{}
    Tail tail;
    cex Expr(H h,TT... tt):head(h),tail(forward<TT>(tt)...){}
    template<typename O> cex auto concat(O&&o) const->When<!isApp<O>(),decltype(_app(forward<O>(o),move(*this)))> {return _app(forward<O>(o),move(*this));}
    template<typename O> cex auto concat(O&&o) const
      ->When< isApp<O>(),decltype(_cons(move(head),_concat(move(tail),forward<O>(o))))>
      {return _cons(move(head),_concat(move(tail),forward<O>(o)));}
    template<typename O> cex auto operator()(O&&o)->decltype(_app(forward<O>(o),move(*this))) {return _app(forward<O>(o),move(*this));}
  };

  template<typename H,typename T>
  struct Expr<H,Chain,T>:App {
    using Head=H;
    using Tail=T;
    Head head;
    Tail tail;
    cex Expr():head{},tail{}{}
    cex Expr(H h,T t):head(h),tail(t){}
    template<typename O> cex auto concat(O&&o) const->When<!isApp<O>(),decltype(_app(forward<O>(o),move(*this)))> {return _app(forward<O>(o),move(*this));}
    template<typename O> cex auto concat(O&&o) const
      ->When< isApp<O>(),decltype(_cons(move(head),_concat(move(tail),forward<O>(o))))>
      {return _cons(move(head),_concat(move(tail),forward<O>(o)));}
    template<typename O> cex auto operator()(O&&o)->decltype(_app(forward<O>(o),move(*this))) {return _app(forward<O>(o),move(*this));}
  };

  //expr--
  template<typename... OO> cex Expr<OO...> expr(OO&&... oo) {return {forward<OO>(oo)...};}

  //chain--
  template<typename O,typename... OO> cex Expr<O,Chain,const Expr<OO...> > chain(O&& o,const Expr<OO...>&& oo) {return {forward<O>(o),forward<const Expr<OO...>>(oo)};}
  template<typename O,typename... OO> cex Expr<O,Chain,const Expr<OO...>&> chain(O&& o,const Expr<OO...>& oo) {return {forward<O>(o),oo};}

  //_cons--
  template<typename O,typename E> cex When<!isApp<E>(),Expr<O,E>> _cons(O&& o,E&& e){return {forward<O>(o),forward<E>(e)};}
  template<typename O,typename... EE> cex auto _cons(O&& o,const Expr<EE...>&& e)
    ->decltype(chain(forward<O>(o),forward<const Expr<EE...>>(e)))
    {return chain(forward<O>(o),forward<const Expr<EE...>>(e));}

  template<typename O,typename... EE> cex auto _cons(O&& o,const Expr<EE...>& e)
    ->decltype(chain(forward<O>(o),e))
    {return chain(forward<O>(o),e);}

  //_app--
  template<typename O> cex O _app(O&&o,const Empty){return o;}
  template<typename O,typename E> cex Expr<E,O> _app(O&&o,const Expr<E>&&e) {return {forward<const E>(e.head),forward<O>(o)};}

  template<typename E,typename... OO> cex const When<!isApp<E>(),Expr<E,const Expr<OO...>>> _app(const Expr<OO...>&& o,E&&e) {return {e,o};}

  template<typename O,typename... EE> 
  cex auto _app(O&&o,const Expr<EE...>& e)
    ->decltype(_cons(forward<const typename Expr<EE...>::Head>(e.head),_app(forward<O>(o),forward<const typename Expr<EE...>::Tail>(e.tail))))
    {return    _cons(forward<const typename Expr<EE...>::Head>(e.head),_app(forward<O>(o),forward<const typename Expr<EE...>::Tail>(e.tail)));}

  template<typename O,typename... EE> 
  cex auto _app(O&&o,const Expr<EE...>&& e)
    ->decltype(_cons(forward<const typename Expr<EE...>::Head>(e.head),_app(forward<O>(o),forward<const typename Expr<EE...>::Tail>(e.tail))))
    {return    _cons(forward<const typename Expr<EE...>::Head>(e.head),_app(forward<O>(o),forward<const typename Expr<EE...>::Tail>(e.tail)));}

  //_concat--
  template<typename O> cex O _concat(O&&o,const Empty){return o;}
  template<typename O> cex O _concat(const Empty,O&&o){return o;}
  template<typename A,typename B> cex When<!isApp<A>()&&!isApp<B>(),Expr<A,B>> _concat(A&&a,B&&b){return {forward<A>(a),forward<B>(b)};}
  template<typename A,typename B> cex auto _concat(A&&a,B&&b)->When<!isApp<A>()&& isApp<B>(),decltype(_cons(forward<A>(a),forward<B>(b)))> {return _cons(forward<A>(a),forward<B>(b));}
  template<typename A,typename B> cex auto _concat(A&&a,B&&b)->When< isApp<A>()&&!isApp<B>(),decltype(_app(forward<B>(b),forward<A>(a)))>{return _app(forward<B>(b),forward<A>(a));}
  template<typename A,typename B>
  cex auto _concat(A&&a,B&&b)
    ->When<isApp<A>()&&isApp<B>(),decltype(a.concat(forward<B>(b)))>
    {return a.concat(forward<B>(b));}

  template<typename Fn> struct Combinator:Lambda {
    template<typename O> cex const Expr<Fn,O> operator()(O&&o) const {return {*(Fn*)this,forward<O>(o)};}
  };

  //alias (for printing)--
  template<typename Fn> struct Alt:Fn {
    cex operator const Alias() const {return Alias{};}
    template<typename O> cex const Expr<Alt<Fn>,O> operator()(const O o) const {return {*this,o};}
  };

  #ifdef YO_PRINT
    #ifdef YO_VERB
      template<typename Out> Out& operator<<(Out& out,const Empty){return out<<"ø";}
      #ifdef YO_DEBUG
        template<typename Out,typename... OO> Out& operator<<(Out& out,const Expr<OO...>&& o)
          {return out<<"["<<&o<<"]("<<forward<const typename Expr<OO...>::Head>(o.head)<<"@"<<&o.head<<" "<<forward<const typename Expr<OO...>::Tail>(o.tail)<<")";}
        template<typename Out,typename... OO> Out& operator<<(Out& out,const Expr<OO...>&  o)
          {return out<<"->["<<&o<<"]("<<forward<const typename Expr<OO...>::Head>(o.head)<<"@"<<&o.head<<" "<<forward<const typename Expr<OO...>::Tail>(o.tail)<<")";}
      #else
        template<typename Out,typename... OO> Out& operator<<(Out& out, Expr<OO...> o){return out<<"("<<o.head<<" "<<o.tail<<")";}
      #endif
    #else
      template<typename Out> Out& operator<<(Out& out,const Empty){return out;}
      template<typename Out,typename O> When<!isApp<O>(),Out>& operator<<(Out& out, const Expr<O> o){return out<<o.head;}
      template<typename Out,typename O> When< isApp<O>(),Out>& operator<<(Out& out, const Expr<O> o){return out<<"("<<o.head<<")";}
      template<typename Out,typename O,typename... OO> When<!isApp<O>(),Out>& operator<<(Out& out, const Expr<O,OO...> o){return out<<o.head<<" "<<o.tail;}
      template<typename Out,typename O,typename... OO> When< isApp<O>(),Out>& operator<<(Out& out, const Expr<O,OO...> o){return out<<"("<<o.head<<") "<<o.tail;}
    #endif
  #endif

};
