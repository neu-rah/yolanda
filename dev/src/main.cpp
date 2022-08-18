// #include <ArduinoSTL.h>
#include <yolanda.h>
using namespace yo;
// using std::forward;

// using namespace yo;

// template<typename IO>
// Char getChar(IO& io) {return io.get();}

// template<typename IO>
// Text getLine(IO& io) {Str r;std::getline(io,r);return Text(std::forward<Str>(r));}

// IO monad from haskell
//(>>=)::IO o->(o->IO p)->IO b
//return::o->IO o

//binding actions
// getChar  >>=(\a->
// getChar  >>=(\b->
// putChar b>>=(\()->
// return (a,b))))

// return (a,b)=<<putChar b=<<let b=getChar=<<let a=getChar

//do notation
// do
//   a<-getChar
//   b<-getChar
//   putChar b
//   return (a,b)

// mempty::m->o->mo
// mappend::ma->mb->mc

struct GetChar {}; constexpr const GetChar getChar;
struct GetLine {}; constexpr const GetLine getLine;

template<typename IO,typename E=Id,bool reuse=false>
struct IOSys {
  using This=IOSys<IO,E>;
  IO& io;
  const E e;
  IOSys(IO& io,const E&e=id):io(io),e(e){}
  template<typename O>
  IOSys<IO,O> operator()(const O&o) const {return IOSys<IO,O>(io,o);}
  auto operator<<(GetChar) const->decltype(operator()(e(io.get()))) {return operator()(e(io.get()));}
  This operator<<(const char c) const {io<<c;return *this;}
  This operator<<(Str o) const {io<<o;return *this;}
  This operator<<(double o) const {io<<o;return *this;}
  This operator<<(const char* const o) const {io<<o;return *this;}
};

template<typename E=Id>
struct StdIO:E {
  using This=StdIO<E>;
  // const E e;
  // StdIO(const E&e=id):e(e){}
  using E::E;
  template<typename O>
  StdIO<O> operator()(const O o) const {return StdIO<O>(o);}

  template<typename _CharT, typename _Traits>
  This operator<<(const decltype(endl<_CharT,_Traits>)&) const {
    cout<<endl;
    return *this;
  }

  template<typename _CharT, typename _Traits>
  This operator<<(const decltype(flush<_CharT,_Traits>)&) const {
    cout<<flush;
    return *this;
  }

  template<typename O>
  This operator<<(const O o) const
    {cout<<show(o)<<flush;return *this;}
  auto operator<<(const GetChar) const
    ->decltype(operator()(cin.get())) 
    {cout.flush();return operator()(cin.get());}
  auto operator<<(const GetLine) const
    ->decltype(operator()(Text(std::forward<Str>(Str())))) {
      Str r;
      cout.flush();
      std::getline(cin,r);
      return operator()(Text(std::forward<Str>(r)));
    }
};

StdIO<Id> io;

template<typename E,typename O>
auto operator<<(StdIO<E>& io,const O o) ->decltype(io.operator<<(o)) {return io.operator<<(o);}

template<typename O>
Str toStr(const StdIO<O>&o) {return toStr(o)+"()";}


//so simple with c++14
// auto id=[](const auto o){return o;};
// auto _true=[](const auto o){return [o](const auto){return o;};};
// auto _S=[](const auto f){
//   return [f](const auto g){
//     return [f,g](const auto o){return f(o)(g(o));};
//   };
// };
// auto _false=_true(id);

const char* op1_text="op1";
const char* op2_text="op2";
using MainMenu=Expr<
  Cons,
  StaticText<&op1_text>,
  Expr<
    Cons,
    StaticText<&op2_text>,
    Nil
  >
>;

MainMenu mainMenu;

// namespace yo {
//   // template<typename O> using NullStr=StaticBool<((char)O::At<0>)==0>;
//   // template<typename O> using HeadStr=StaticChar<((const char*)O)[0]>;
//   // template<typename O> using TailStr=StaticText<&((const char*)O)[1]>;
//   struct _ToString:Combinator<_ToString,2> {
//    template<typename F,typename O>
//     using Beta=_ToString::Bind<O>;
//     template<typename F,typename O>
//     static auto beta(const F&&f, const O&&text) 
//       ->decltype(nullStr(std::forward<const O>(text))
//         (std::forward<const Nil>(nil))
//         (cons(headStr(text))(f(tailStr(text)))))
//       {return nullStr(std::forward<const O>(text))
//         (std::forward<const Nil>(nil))
//         (cons(headStr(text))(f(tailStr(text))));}
//     protected:
//       static Bool nullStr(const char *text) {return Bool(text[0]==0);}
//       static Char headStr(const char *text) {return Char(text[0]);}
//       static Text tailStr(const char *text) {return Text(&text[1]);}
//   };
//   using ToString=Expr<Y,_ToString>;
//   constexpr const ToString toString;
// };

int main() {
  clog<<"testing..."<<endl;
  // print(head(mainMenu));
  // print(head(tail(mainMenu)));
  // clog<<runTo<Str>(head(mainMenu))<<endl;
  // io<<length<<io<<cons<<getLine<<nil;
  auto a=io<<getLine;
  // io<<toString(a);
  clog<<"end."<<endl;
  return 0;
}

