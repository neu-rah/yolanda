#pragma once

#include "bool.h"
// #include "peano.h"

#ifndef YO_DEBUG
  namespace yo {
#endif
  //type info----------------------------
  template<typename  T>
  struct Type {
    // static constexpr const int sz=0;
    static constexpr const bool term=true;
    using This=Type<T>;
    using Def=T;
    using Run=This;
  };

  // static data ------------------------------------------------
  template<typename T,T data>
  struct StaticData:Type<T> {
    using This=StaticData<T,data>;
    constexpr operator const T() const {return data;}
    using Run=This;
    // auto run() const->decltype(*this) {return *this;}
  };

  template<> struct StaticBool<true>:StaticData<bool,true>,True {
    using Def=StaticBool<true>;
    constexpr operator const bool() const {return true;}
    using Run=This;
    // auto run() const->decltype(*this) {return *this;}
  };

  template<> struct StaticBool<false>:StaticData<bool,false>,False {
    using Def=StaticBool<false>;
    constexpr operator const bool() const {return false;}
    using Run=This;
    // auto run() const->decltype(*this) {return *this;}
  };

  using _T=StaticBool<true>;
  using _F=StaticBool<false>;

  // slow compile of any StaticInt
  // template<int n> struct StaticInt:StaticData<int,n>,Succ::Bind<StaticInt<n-1>> {};
  // template<> struct StaticInt<0>:StaticData<int,0>,N0 {};

  template<int n> using StaticInt=StaticData<int,n>;

  template<const char* const* text> 
  struct StaticText:StaticData<const char* const*,text> {
    using This=StaticText<text>;
    // static constexpr const int sz=0;
    operator const char*() const {return text[0];}
    operator Str() const {return text[0];}
    using Run=This;
    // auto run() const->decltype(*this) {return *this;}
  };

  template<typename T>
  struct Data:Type<T> {
    using This=Data<T>;
    const T data;
    Data(const T&o):data(o) {}
    Data(const T&&o):data(o) {}
    operator const T() const {return data;}
    using Run=This;
    const This beta() const {return *this;}
    // auto run() const->decltype(*this) {return *this;}
  };

  // struct Int:Data<unsigned int>,Combinator<Int,2> {
  //   using Combinator<Int,2>::sz;
  //   using This=Int;
  //   using Base=Data<unsigned int>;
  //   using Base::Base;
  //   using Run=This;
  //   // const This beta() const {return *this;}
  //   template<typename F,typename O>
  //   auto beta(const F&&f,const O&&o) const
  //     ->decltype(Int(data-1)(f)(f(o)))
  //     {return Int(data-1)(std::forward<const F>(f))(f(std::forward<const O>(o)));}
  // };

  struct Text:Data<Str> {
    using Base=Data<Str>;
    using Base::Base;
    const This beta() const {return *this;}
    operator const char*() {return data.c_str();}
    // auto run() const->decltype(*this) {return *this;}
  };
#ifndef YO_DEBUG
  };
#endif
