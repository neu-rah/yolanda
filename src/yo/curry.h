#pragma once

#include "lambda.h"

namespace yo {
  //////////////////////////////////////////////
  template<typename R,typename O,typename... OO> using Func=R(*)(O,OO...);

  template<typename F,F f> struct Curry;

  template<typename R,typename O,typename... OO, Func<R,O,OO...>f>
  struct Curry<Func<R,O,OO...>,f>:Combinator<Curry<Func<R,O,OO...>,f>,(int)Count<O,OO...>()> {
    using This=Curry<Func<R,O,OO...>,f>;
    template<typename Q,typename...QQ> using Beta=R;
    using Base=Combinator<This,(int)Count<O,OO...>()>;
    template<typename...PP>
    static auto beta(const PP... oo)->decltype(f(yo::beta(oo)...)) {return f(yo::beta(oo)...);}
  };


  struct CurriedTemplateFuncionMarker {};
  // curry template function
  // providing its name and arguments count
  #define CurryTemplateFunction(f,n)\
    struct f##TemplateCaller:Combinator<f##TemplateCaller,n>,CurriedTemplateFuncionMarker {\
      template<typename... OO>\
      static auto beta(const OO... oo)->decltype(f(yo::beta(oo)...)) {return f(yo::beta(oo)...);}\
      f##TemplateCaller beta() const {return *this;}\
      template<typename... OO> using Beta=decltype(beta<OO...>(OO{}...));\
    };\
    std::ostream& operator<<(std::ostream& out,const f##TemplateCaller) {return out<<("<...>");}\
    f##TemplateCaller 
};