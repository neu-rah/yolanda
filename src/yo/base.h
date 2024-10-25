#pragma once

#ifdef ARDUINO
  #include <Arduino.h>
#endif

#ifdef __AVR__
  #include "avr_std.h"
  using avr_std::forward;
  using avr_std::move;
  using avr_std::is_convertible;
  using avr_std::is_same;
  using avr_std::enable_if;
#else
  #include <cmath>
  #include <utility>
  // using namespace std;
  using std::forward;
  using std::move;
  using std::is_convertible;
  using std::is_same;
  using std::enable_if;
#endif

//esp32 bad macros
#undef _L
#undef _S
#undef _C
#undef _B

namespace yo {
  template<bool chk,typename T> using When=typename enable_if<chk,T>::type;

  struct Chain{};
  struct App{};
  template<typename O> constexpr bool isApp() {return is_convertible<O,App>::value;}

  struct Alias{};

  struct Lambda {};
  template<typename O> constexpr bool isLambda() {return is_convertible<O,Lambda>::value;}

  template<typename...> struct Expr:App{};
  using Empty=Expr<>;
  constexpr const Empty empty;
  template<typename O> constexpr bool isEmpty() {return is_same<O,Empty>::value;}

  struct None{};
  constexpr const None none;
  template<typename O> constexpr bool isNone() {return is_same<O,None>::value;}
  #ifdef YO_PRINT
    template<typename Out> Out& operator<<(Out& out,const None){return out<<"⊥";}
  #endif

  #ifdef ARDUINO
    using Serial_=decltype(Serial);
    Serial_& operator<<(Serial_& out,void* o) {out.print((int)o);return out;}
    template<typename O>
    typename enable_if<!isApp<O>()&&!isLambda<O>()&&!isEmpty<O>()&&!isNone<O>(),Serial_>::type&
    operator<<(Serial_& out,const O o)      {out.print(o);return out;}
  #endif

}

