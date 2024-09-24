#pragma once

#include "lambda.h"

namespace yo {
  //////////////////////////////////////////////
  template<typename... OO> struct Count {static const int value=0;};
  template<typename O,typename... OO> struct Count<O,OO...> {static const int value=Count<OO...>::value+1;};

  template<typename R,typename... OO> using Func=R(*)(OO...);

  template<typename F,F f> struct Curry;

  template<typename R,typename O,typename... OO,Func<R,O,OO...> f>
  struct Curry<Func<R,O,OO...>,f>:Combinator<Curry<Func<R,O,OO...>,f>> {
    using This=Curry<Func<R,O,OO...>,f>;
    template<typename P,typename... PP>
    static cex auto beta(const P o,const PP... oo)
      ->const When< Count<P,PP...>::value==Count<O,OO...>::value,decltype(f(yo::beta(o),yo::beta(oo)...))>
      {return f(yo::beta(o),yo::beta(oo)...);}
  };

  // curry template function
  // providing its name
  #ifdef YO_PRINT
    #define CurryTemplateFunction(f)\
      struct f##TemplateCaller:Combinator<f##TemplateCaller> {\
        template<typename... OO>\
        static cex auto beta(const OO... oo)\
          ->const decltype(f(oo...))\
          {return f(oo...);}\
      };\
      template<typename Out>\
      Out& operator<<(Out& out,const f##TemplateCaller) {return out<<"{"<<#f<<"}";}\
      cex f##TemplateCaller 
  #else
    #define CurryTemplateFunction(f)\
      struct f##TemplateCaller:Combinator<f##TemplateCaller> {\
        template<typename... OO>\
        static cex auto beta(const OO... oo)\
          ->const decltype(f(yo::beta(oo)...))\
          {return f(yo::beta(oo)...);}\
      };\
      cex f##TemplateCaller 
  #endif

};