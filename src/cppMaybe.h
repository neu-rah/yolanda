#pragma once
#include <assert.h>

//c++ runtime `Maybe`
namespace cppMaybe {
  template<typename O>
  struct Maybe {
    bool o_isJust;
    O value;
    // operator bool() const {return o_isJust;}
    // operator O() const {return value;}
    O isNothing() const {return !o_isJust;}
    O isJust() const {return o_isJust;}
    O fromJust() const {assert(o_isJust);return value;}
    template<typename F>//fmap
    auto operator()(F f) const->Maybe<decltype(f(O{}))> {
      using T=decltype(f(O{}));
      return o_isJust?
        (Maybe<T>){true,f(value)}:
        (Maybe<T>){false,{}};
    }
  };
  //constructors
  template<typename T> Maybe<T> just(T o) {return (Maybe<T>){true,o};}
  template<typename T> Maybe<T> nothing(T=T{}) {return (Maybe<T>){false,T{}};}

  template<typename O> O isNothing(const Maybe<O> o) {return !o.isJust();}
  template<typename O> O isJust(const Maybe<O> o) {return o.isJust();}
  template<typename O> O fromJust(const Maybe<O> o) {return o.fromJust();}

  template<typename O,typename F> 
  auto operator >>= (Maybe<O> o,F f)->decltype(isJust(o)?f(fromJust(o)):o) {return isJust(o)?f(fromJust(o)):o;}

  template<typename O>
  Maybe<O> operator||(Maybe<O> o,Maybe<O> p) {return isJust(o)?o:p;}
};