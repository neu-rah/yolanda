#pragma once

#ifdef __AVR__
  #include "avr_std.h"
  namespace yo {using namespace std;};
#endif

#ifdef ARDUINO
  #include <Arduino.h>
  template<typename Out,typename Data>
  Out& operator<<(Out& o,const Data& data)
    {o.print(data);return o;}
  const char* endl="\r\n";
  const char* flush="";
  using Str=String;
  #ifdef __AVR__
    #define clog Serial
  #endif

  // template<typename O> constexpr O std::forward(const O o) noexcept {return o;}
#else
  #include <iostream>
  #include <string>
  namespace yo {using namespace std;};
  using Str=std::string;
  using std::clog;
  using std::endl;
  using std::flush;
#endif

#ifndef YO_DEBUG
  namespace yo {
#endif

  template<typename O> Str show(const O&);
  template<typename O> Str showType();
  // template<typename O> Str code();
  // template<typename O> Str show(const O&o);

  #ifdef YO_DEBUG
    #define dbo clog
    // struct DBO:decltype(clog) {} dbo;
    // template<typename O> DBO& operator<<(DBO& dbo,const O&o) {return dbo<<o;}
  #else
    #define dbo clog
    // struct DBO {} dbo;
    // template<typename O> DBO& operator<<(DBO& dbo,const O&o) {return dbo;}
  #endif

  template<typename Prev,typename Arg,int n> struct Binder;
  template<typename Prev,typename Arg,int n> struct Lambda;

  //type equality
  template<typename O> bool EqT(const O,const O) {return true;}
  template<typename A,typename B> bool EqT(const A,const B) {return false;}

  template<typename R,typename O,typename... OO> using Func=R(*)(O,OO...);
#ifndef YO_DEBUG
  };
#endif