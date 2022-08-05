#pragma once

#include "base.h"

#ifndef YO_DEBUG
  namespace yo {
#endif
  //we can extract values when we know the result type
  template<typename R,typename E> struct Run;
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
#ifndef YO_DEBUG
  };
#endif
