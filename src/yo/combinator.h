#pragma once

#include "base.h"

#ifndef YO_DEBUG
  namespace yo {
#endif
  //we can extract values when we know the result type
  template<typename R,typename E> struct Run;
  template<typename R> R run(const Bool&e) {return e;}
  template<typename R> R run(const Int&e) {return e;}
  template<typename R> R run(const Char&e) {return e;}
  template<typename R> R run(const Float&e) {return e;}
  template<typename R> R run(const Text&e) {return e;}
  template<typename R,const char* const* text> R run(const StaticText<text>&e) {return e;}
  template<typename R,bool o> R run(const StaticBool<o>&e) {return e;}
  template<typename R,typename T> R run(const Type<T>&e) {return e;}
  template<typename R,typename T,T data> R run(const StaticData<T,data>&e) {return e;}
  template<typename R,typename E> R run(const E&e) {return Run<R,E>::run(e);}
  template<typename R,typename E> struct Run {static R run(const E&e) 
    #ifdef YO_DEBUG
      {return ::run<R>(e.beta());}
    #else
      {return yo::run<R>(e.beta());}
    #endif
  };
  template<typename R> struct Run<R,int> {static int run(const int n) {return n;}};

  template<typename This,int n>
  struct Combinator {
    using Def=This;
    static constexpr const int sz=n;
    inline operator const This() const {return *reinterpret_cast<const This*>(this);}
    template<typename O> using Bind=Binder<This,O,n<0?-1:n-1>;
    template<typename O>
    const Lambda<This,O,n<0?-1:n-1> operator()(const O&o) const
      {/*dbo<<"+";*/return Lambda<This,O,n<0?-1:n-1>(operator const This(),std::forward<const O>(o));}
    template<typename O>
    const Lambda<This,O,n<0?-1:n-1> operator()(const O&&o) const
      {/*dbo<<"-";*/return Lambda<This,O,n<0?-1:n-1>(std::forward<const This>(operator const This()),std::forward<const O>(o));}
    template<typename R> R runTo() const {return run<R,This>(operator const This());}
    // const This run() const {return *this;}
    using Run=This;
    using Beta=This;
  };

  struct ToBool:Combinator<ToBool,1> {
    template<typename Cond>
    using Beta=typename Cond::Run;
    template<typename Cond> 
    bool beta(const Cond& cond) const {
      return cond(Bool(true))(Bool(false)).template runTo<Bool>();
    }
    #ifdef REDUCE_ON_COMPLETION
      template<typename O>
      auto operator()(const O&o) const 
        ->decltype(beta(o)) 
        {return beta(o);}
    #endif
  };

  constexpr const ToBool toBool;
#ifndef YO_DEBUG
  };
#endif
