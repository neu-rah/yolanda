#ifdef ARDUINO
  #include <Arduino.h>
// #endif
// #ifdef __AVR__
  #include <streamFlow.h>
  using namespace StreamFlow;
  #define cout Serial
  #define endl "\n"
  #ifdef __AVR__
    #include <avr_std.h>
    using namespace avr_std;
  #endif
#else
  #include <iostream>
  using namespace std;
#endif

// #define cex
#define cex constexpr

template<bool chk,typename T> using When=typename enable_if<chk,T>::type;

struct App {};

template<typename O> constexpr const bool isApp() {return is_convertible<O,App>::value;}

template<typename...> struct Expr;

template<> struct Expr<> {};
using Empty=Expr<>;
cex const Empty empty;

template<typename H>
struct Expr<H>:App {
  using This=Expr<H>;
  using Head=H;
  using Tail=Empty;
  const Head head;
  const Tail& tail;
  cex Expr(const Head& h):head(h),tail(empty) {}
  template<typename O> cex const Expr<O,H> cons(const O& o) const {return {o,this};}//using This& solves the refeerence problem... but creates a sub element, not a list continuation
  cex const Expr<H,const char*> operator()(const char* o) const {return {head,o};}
  template<typename O> cex const Expr<H,O> operator()(const O& o) const {return {head,o};}
  template<typename O> cex const Expr<H,O> _concat(const O& o) const {return operator()(o);}
  template<typename O> cex const Expr<H,O> _concat(const Expr<O>& o) const {return operator()(o.head);}
  template<typename O,typename... OO> cex auto _concat(const Expr<O,OO...>& o) const->const decltype(o.cons(head)) {return o.cons(head);}
};

template<typename H,typename T,typename... TT>
struct Expr<H,T,TT...>:App {
  using This=Expr<H,T,TT...>;
  using Head=H;
  using Tail=Expr<T,TT...>;
  const Head head;
  const Tail tail;
  cex Expr(const Head& h,const T& t,const TT&... tt):head(h),tail(t,tt...) {}
  cex Expr(const Head& h,const Expr<T,TT...>* t):head(h),tail(*t) {}
  template<typename O> cex const Expr<O,const This&> cons(const O& o) const {return {o,*this};}
  cex const Expr<H,T,TT...,const char*> operator()(const char* o) const {return tail(o).cons(head);}
  template<typename O> cex auto operator()(const O& o) const->const decltype(tail(o).cons(head)) {return tail(o).cons(head);}
  template<typename O> cex auto _concat(const O& o) const->const decltype(operator()(o)) {return operator()(o);}
  template<typename O> cex const Expr<H,T,TT...,O> _concat(const Expr<O>& o) const {return operator()(o.head);}
  template<typename O,typename... OO> cex auto _concat(const Expr<O,OO...>& o) const->const decltype(tail._concat(o).cons(head)) {return tail._concat(o).cons(head);}
};

#ifdef YO_VERB
  template<typename Out> Out& operator<<(Out& out,const Empty& o) {return out<<"ø@"<<&o;}
  template<typename Out,typename O,typename... OO> When<!isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...>& o) {return out<<"{"<<&o<<"}("<<o.head<<"@"<<&o.head<<" "<<o.tail<<")";}
  template<typename Out,typename O,typename... OO> When< isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...>& o) {return out<<"{"<<&o<<"}(["<<o.head<<"@"<<&o.head<<"] "<<o.tail<<")";}
#else
  template<typename Out> Out& operator<<(Out& out,const Empty& o) {return out;}
  template<typename Out,typename O,typename... OO> When<!isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...>& o) {return out<<o.head<<" "<<o.tail;}
  template<typename Out,typename O,typename... OO> When< isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...>& o) {return out<<"("<<o.head<<") "<<o.tail;}
#endif

template<typename... OO> cex const Expr<const OO&...> expr(const OO&... oo) {return {oo...};}

template<typename O> cex const O& _concat(const O& o,const Empty) {return o;}
template<typename A, typename B> cex const When<!isApp<A>()&&!isApp<B>(),Expr<A,B>> _concat(const A& a,const B& b) {return {a,b};}
template<typename A, typename B> cex auto _concat(const A& a,const B& b)->const When< isApp<A>(),decltype(a._concat(b))> {return a._concat(b);}
template<typename A, typename B> cex auto _concat(const A& a,const B& b)->const When<!isApp<A>()&&isApp<B>(),decltype(b.cons(a))> {return b.cons(a);}

cex const int y=1967;
cex const auto a{expr(y)};
cex const auto b{expr("ok","fail")};
cex const auto c{expr(b,a,b)};

int main() {
  cout<<"start!"<<endl;
  // cout<<&y<<endl;
  // cout<<&empty<<endl;
  // cout<<a<<endl;
  cout<<b<<endl;
  // cout<<c<<endl;
  cout<<b.tail.cons(1)<<endl;
  cout<<"end."<<endl;
  return  0;
} 
