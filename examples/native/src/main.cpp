#include <yolanda.h>
#ifndef YO_DEBUG
  using namespace yo;
#endif

using L1=Expr<Cons,N1,Nil>;
using L2=Expr<Cons,N2,L1>;
using L3=Expr<Cons,N3,L2>;
constexpr auto l1=L1();
constexpr auto l2=L2();
// constexpr auto l3=L3();

// auto l1=cons(std::forward<const N1>(n1))(std::forward<const Nil>(nil));
// auto l2=cons(std::forward<const N2>(n2))(std::forward<const decltype(l1)>(l1));
auto l3=cons(std::forward<const N3>(n3))(std::forward<const decltype(l2)>(l2));

const char*yes_text="yes";
const char*no_text="no";

using Yes=StaticText<&yes_text>;
using No=StaticText<&no_text>;

Text yes(yes_text);
Text no(no_text);

template<typename F>
auto test__(const F&&f) 
  ->decltype(Expr<Mul,N2>()(std::forward<const F>(f))) {
  static constexpr const Expr<Mul,N2> dbl;
  return dbl(std::forward<const F>(f));
}

template<typename F>
auto test(const F f)
  ->decltype(test__(std::forward<const F>(f))) 
  {return test__(std::forward<const F>(f));}
  
void setup() {
  #ifdef ARDUINO
    Serial.begin(115200);
    while(!Serial);
  #endif
  clog<<"--[yolanda 0.00]--"<<endl;
  print(_true(Id()));//using rvalue
  print(_true(id));//using lvalue
  print(zip(l2)(l2));
  print(toInt(test(n8)));
  using Test=False;
  clog<<(Test::Bind<Type<int>>::Bind<Type<float>>::Run::Def)1.23<<endl;
  clog<<toInt(Expr<Length,Expr<Cons,StaticInt<1>,Nil>>::Run())<<endl;
  print(foldl(add)(n0)(l3));
  clog<<toInt(FoldR::Bind<Add>::Bind<N0>::Bind<L3>())<<endl;
  clog<<toInt(foldr(add)(n0)(l3))<<endl;
  print(toInt(length(filter(std::forward<const Is0>(is0))(cons(std::forward<const N0>(n0))(cons(std::forward<const N0>(n0))(std::forward<const Nil>(nil)))))));
  clog<<toStr(just(yes)(nothing)(id))<<endl;
  print(toInt(length(l3)));
  print(toInt(length(tail(l3))));
  print(last(l3));
  print(flip(_true)(yes)(no));
  print(drop(n0)(l3));
  print(drop(n1)(l3));
  print(drop(n2)(l3));
  print(drop(n3)(l3));
  print(null(drop(n3)(l3))(yes)(no));
  print(toInt(Expr<Length,Expr<Concat,L3,L2>>()));
  // clog<<showType<StaticData<int,1111>>()<<endl;
  // clog<<showType<Expr<Init,Expr<Cons,StaticInt<1111>,Expr<Cons,StaticInt<1967>,Nil>>>::Run>()<<endl;
  print(toInt(head(drop(n9)(nats))));
  print(_init(l2));
  print(_map(is0)(Expr<Cons,N1,Expr<Cons,N0,Nil>>()));
  print(toInt(foldl(add)(n0)(_map(snd)(zip(l1)(l1)))));
  clog<<toInt(Expr<FoldL,Add,N0,Expr<Map,Snd,Expr<Zip,L3,L2>>>::Run())<<endl;
  print(toInt(length(zip(l3)(l2))));
  print(toInt(last(l3)));
  print(l3);
  print(toInt(head(_map(mul(n9))(l3))));
  print(toInt(head(_map(fst)(zip(l3)(l2)))));
  print(_or(null(nil))(null(l1))(yes)(no));
  print(toInt(head(l3)));
  print(toInt(head(_reverse(l3))));
  
  //why can't this work on AVR's? ------------------------------------------
  clog<<toInt(foldl(add)(n0)(_map(snd)(zip(L3())(L2()))))<<endl;
  print(toInt(foldl(add)(n0)(_map(snd)(zip(l2)(l3)))));

  //----------------------------------------------------------
  // print(length(nats));//can not ask length of infinit list
  clog<<"end."<<endl;
}

#ifndef ARDUINO
  int main() {
    setup();
    // while(true) loop();
    return 0;
  }
#else
  void loop() {}
#endif
 