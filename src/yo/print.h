#pragma once
#include "io.h"
#include "show.h"

#ifndef YO_DEBUG
  namespace yo {
#endif
  //generic stream as base og obj's to compose with IO<...>
  template<typename IO,IO& io>
  struct PrintIO {
    static void nl() {io<<endl;}
    template<typename O> void operator()(const O&&o) {
      io<<show(std::forward<const O>(o))<<flush;
    }
  };

  #ifdef ARDUINO
    using SerialIO=PrintIO<decltype(Serial)&,Serial>;
    IO<SerialIO> serialIO;

    template<typename E>
    void print(const E&e) {serialIO.ret(std::forward<const E>(e));serialIO.nl();}

    template<typename E>
    void print(const E&&e) {serialIO.ret(std::forward<const E>(e));serialIO.nl();}

  #else
    using Std=PrintIO<decltype(clog)&,clog>;
    IO<Std> stdIO;

    template<typename E>
    void print(const E&e) {
      // #ifdef YO_DEBUG
      //   clog<<show(std::forward<const E>(e))<<" => ";
      // #endif
      stdIO.ret(std::forward<const E>(e));
      stdIO.nl();
    }
  #endif

#ifndef YO_DEBUG
  };
#endif