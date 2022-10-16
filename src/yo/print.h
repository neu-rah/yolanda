#pragma once
#include "io.h"
#include "cStr.h"

#ifndef YO_DEBUG
  namespace yo {
#endif
  //generic stream as base og obj's to compose with IO<...>
  template<typename IO,IO& io>
  struct PrintIO {
    static void nl() {io<<endl;}
    template<typename O> void operator()(const O&&o) {
      io<<cStr(std::forward<const O>(o))<<flush;
    }
  };

  #ifdef ARDUINO
    using SerialIO=PrintIO<decltype(Serial)&,Serial>;
    IO<SerialIO> serialIO;

    template<typename E>
    void _print(const E&e) {
      serialIO.run(std::forward<const E>(e));serialIO.nl();}

    template<typename E>
    void _print(const E&&e) {
      serialIO.run(std::forward<const E>(e));
      serialIO.nl();
    }

  #else
    using Std=PrintIO<decltype(cout)&,cout>;
    IO<Std> stdIO;

    template<typename E>
    void _print(const E&e) {
      #ifdef YO_DEBUG
        clog<<cStr(std::forward<const E>(e))<<" => ";
      #endif
      stdIO.run(std::forward<const E>(e));
      stdIO.nl();
    }
  #endif

  struct Print:Combinator<Print,1> {
    template<typename F> using Beta=Print::Bind<F>;
    template<typename F>
    static Print beta(const F&&f)
      {
        _print(std::forward<const F>(f));
        return Print();
      }
  };

  constexpr const Print print;
  Str cStr(const Print&o) {return "print";}
  
#ifndef YO_DEBUG
  };
#endif
