#pragma once

#include "base.h"
#include "data.h"

#ifndef YO_DEBUG
  namespace yo {
#endif
  // template<typename IO,typename E>
  // void betaIO(IO&&io,const E&e) {io.ret(e.beta());}

  //faking constexpr `if` on c++11
  template<typename IO,typename E,int sz>
  struct BetaIO {
    // void operator()(IO&io,const E&e) const {io.ret(e);}
    void operator()(IO&&io,const E&&e) const {io.ret(std::forward<const E>(e));}
  };

  template<typename IO,typename E>
  struct BetaIO<IO,E,0> {
    void operator()(IO&&io,const E&&e) const {
      // clog<<"{λ0}";
      io.ret(e.beta());
    }
  };
  template<typename IO,const char* const*text,int n>
  struct BetaIO<IO,StaticText<text>,n> {
    void operator()(IO&&io,const StaticText<text>&&e) const {
      io.ret(e);
    }
  };
  //TODO: other data types here...

  template<typename IO,typename E>
  struct BetaIO<IO,E,-1> {
    void operator()(IO&&io,const E&&e) const {/*clog<<"{-1}";*/io.ret(e.beta());}
  };

  template<typename Fn>
  struct IO:Fn {
    using This=IO;
    using Fn::Fn;
    template<typename T> static void ret(const Type<T>&&o) {Fn()(o);}
    template<typename T> static void ret(const Data<T>&&o) {Fn()(std::forward<const Data<T>>(o));}
    template<typename T,T data> static void ret(const StaticData<T,data>&) {Fn()(std::forward<const T>(data));}
    template<int N> static void ret(const StaticInt<N> n) {Fn()(std::forward<const StaticInt<N>>(n));}
    static void ret(const int n) {Fn()(std::forward<const int>(n));}
    static void ret(const unsigned int n) {Fn()(std::forward<const unsigned int>(n));}
    static void ret(const char o) {Fn()(std::forward<const char>(o));}
    static void ret(const unsigned char o) {Fn()(o);}
    template<const char* const*text> static void ret(const StaticText<text>& n) {Fn()(text[0]);}
    static void ret(const char* t) {Fn()(std::forward<const char*>(t));}
    static void ret(char* t) {Fn()(std::forward<char*>(t));}
    template<typename O>
    static void ret(const O&&o) {
      // clog<<"["<<O::sz<<"]";
      if(O::sz<=0) {//c++11, no constexpr if! #@>:-((
        BetaIO<This,O,O::sz>()(IO<Fn>(),std::forward<const O>(o));//will apply a beta reduction step
      } else Fn()(std::forward<const O>(o));//can not reduce further
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
      void ret(const O&&o) {
        // clog<<"{"<<O::sz<<"}";
        if(O::sz<=0) //c++11, no constexpr if! #@>:-((
          BetaIO<This,O,O::sz>()(std::forward<This>(*this),std::forward<const O>(o));//will apply a beta reduction step
        else io.ret(o(std::forward<const Next>(next)));//can not reduce further
      }
    };

    template<typename IO,typename Prev,typename Arg>
    struct BetaIO<IO,Lambda<Prev,Arg,-1>,-1> {
      void operator()(IO&&io,const Lambda<Prev,Arg,-1>&&e) const {
          // clog<<"{λ-1}";
          RebindIO<IO,decltype(e.param)>(io,std::forward<const Arg>(e.param)).ret(e.prev.beta());
        }
    };
  #endif
#ifndef YO_DEBUG
  };
#endif
