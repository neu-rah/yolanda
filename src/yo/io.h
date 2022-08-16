#pragma once

#include "base.h"
#include "data.h"

#ifndef YO_DEBUG
  namespace yo {
#endif
  template<typename IO,typename E,int sz=E::sz>
  struct BetaIO {
    void operator()(IO&&io,const E&&e) const {
      io.ret(std::forward<const E>(e));
    }
  };

  template<typename IO,typename E>
  struct BetaIO<IO,E,0> {
    void operator()(IO&&io,const E&&e) const {
      io.run(e.beta());}
  };

  template<typename IO,typename E>
  struct BetaIO<IO,E,-1> {
    void operator()(IO&&io,const E&&e) const {
      io.run(e.beta());}
  };

  template<typename Fn>
  struct IO:Fn {
    using This=IO;
    using Fn::Fn;
    template<typename O>
    static void run(const Combinator<O,O::sz>&&o) {
      BetaIO<This,O,O::sz>()(IO<Fn>(),std::forward<const O>(o));//will apply a beta reduction step
    }
    template<typename O,bool term=O::term>
    static void run(const O&&o) {
      Fn()(std::forward<const O>(o));//can not reduce further
    }
    template<typename O>
    static void ret(const O&&o) {
      Fn()(std::forward<const O>(o));//can not reduce further
    }
  };

  #ifdef IO_REBIND
    template<typename IO,typename Next>
    struct RebindIO {
      using This=RebindIO<IO,Next>;
      IO& io;
      const Next next;
      RebindIO(IO& io,const Next&&e):io(io),next(e) {}
      template<typename O>
      void run(const O&&o) {
        if(O::sz<=0)
          BetaIO<This,O,O::sz>()(std::forward<This>(*this),std::forward<const O>(o));//will apply a beta reduction step
        else io.run(o(std::forward<const Next>(next)));//can not reduce further
      }
      template<typename O>
      void ret(const O&&o) {
        io.run(o(std::forward<const Next>(next)));//can not reduce further
      }
    };

    template<typename IO,typename Prev,typename Arg>
    struct BetaIO<IO,Lambda<Prev,Arg,-1>,-1> {
      void operator()(IO&&io,const Lambda<Prev,Arg,-1>&&e) const {
          RebindIO<IO,decltype(e.param)>(io,std::forward<const Arg>(e.param)).run(e.prev.beta());
        }
    };
  #endif
#ifndef YO_DEBUG
  };
#endif
