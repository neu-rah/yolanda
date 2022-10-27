#pragma once

#if defined(ARDUINO) && defined(__AVR__)
  using Str=String;
  using serial_t=decltype(Serial);
  template<typename O>
  serial_t& operator<<(serial_t& so,const O o) {so.print(o);return so;}
  namespace std {
    using ostream=serial_t;
    #define cout Serial
    #define endl "\n\r"
  };
#else
  #include <cstring>
  #include <iostream>
  #include <sstream>
  using Str=std::string;
#endif

namespace yo {
  using ConstText=const char*;

  ////////////////////////////////////////
  // compile time count items in a list of types
  template<typename... OO> struct Count;

  template<typename O,typename... OO>
  struct Count<O,OO...> {
    constexpr int operator()(){return 1+Count<OO...>()();}
    constexpr operator int(){return 1+Count<OO...>()();}
  };

  template<typename O>
  struct Count<O> {
    constexpr int operator()(){return 1;}
    constexpr operator int(){return 1;}
  };

  template<>
  struct Count<> {
    constexpr int operator()(){return 0;}
    constexpr operator int(){return 0;}
  };

  // struct Printer;
  // extern Printer out;

  /////////////////////////////////////////////////////
  // expression build sugar -------------------------------------------
  template<typename O,typename... OO> struct _Expr;
  template<typename O> struct _Expr<O> {using Base=O;};
  // template<typename O> struct Expr<Expr<O>>:O {};
  template<typename O,typename OO>
  struct _Expr<O,OO> {
    using Base=typename O::template Bind<OO>;
    // using Base::Base;
  };
  template<typename O,typename OO,typename... OOO>
  struct _Expr<O,OO,OOO...> {
    using Base=typename _Expr<typename O::template Bind<OO>,OOO...>::Base;
    // using Base::Base;
  };

  template<typename O,typename... OO> using Expr=typename _Expr<O,OO...>::Base;

  template<typename condition>
  struct If {
    template<typename then_action>
    struct Then {
      template<typename else_action>
      using Else=Expr<condition,then_action,else_action>;
    };
  };

  template<typename O> struct Alt:O{using O::O;using Base=O;};

  /////////////////////////////////////////////////////
  // static data --------------------------------------
  template<typename T, T t>
  struct StaticData {
    operator T() const {return t;}
  };

  template<ConstText* text>
  struct StaticText {
    operator ConstText() const {return text[0];}
  };

  template<unsigned int n> using StaticInt=StaticData<unsigned int,n>;

  ////////////////////////////////////////////////////////////
  template<typename Def,int n> struct Combinator;
};