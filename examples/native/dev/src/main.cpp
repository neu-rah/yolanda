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

struct None {};
constexpr const None none;
template<typename Out> Out& operator<<(Out& out,const None&) {return out<<"⊥";}
struct Lambda {};
struct App {};
struct Alias {};

template<typename...> struct Expr;

template<> struct Expr<> {
  cex Expr() {}
  cex Expr(const Expr& o) {}
};
using Empty=Expr<>;
cex const Empty empty;
#ifdef YO_VERB
  template<typename Out> Out& operator<<(Out& out,const Empty& o) {return out<<"ø@ "<<&o;}
#else
  template<typename Out> Out& operator<<(Out& out,const Empty&) {return out;}
#endif

template<typename O> constexpr bool isNone() {return is_same<O,None>::value;}
template<typename O> constexpr bool isEmpty() {return is_same<O,Empty>::value;}
template<typename O> constexpr bool isAlias() {return is_convertible<O,Alias>::value;}
template<typename O> constexpr const bool isLambda() {return is_convertible<O,Lambda>::value;}
template<typename O> constexpr const bool isApp() {return is_convertible<O,App>::value;}

template<typename H>
struct Expr<H>:App {
  using Head=H;
  using Tail=Empty;
  const Head& head;
  const Tail& tail;
  cex Expr() {}
  cex Expr(const H& h):head(h),tail(empty) {}
  template<typename O> cex const Expr<O,H> cons(const O& o) const {return {o,head};}
  cex const Expr<H,const char*> operator()(const char* o) const {return {head,o};}
  template<typename O> cex const Expr<H,O> operator()(const O& o) const {return {head,o};}
  template<typename O> cex const Expr<H,O> _concat(const O& o) const {return operator()(o);}
  template<typename O> cex const Expr<H,O> _concat(const Expr<O>& o) const {return operator()(o.head);}
  template<typename O,typename... OO> cex auto _concat(const Expr<O,OO...>& o) const->const decltype(o.cons(head)) {return o.cons(head);}
};

template<typename H,typename T>
struct Expr<H,T>:App {
  using Head=H;
  using Tail=Expr<T>;
  const Head& head;
  const Tail& tail;
  cex Expr() {}
  cex Expr(const H& h,const T& t):head(h),tail(t) {}
  template<typename O> cex const Expr<O,H,T> cons(const O& o) const {return {o,*this};}
  cex const Expr<H,T,const char*> operator()(const char* o) const {return {head,tail,o};}
  template<typename O> cex const Expr<H,T,O> operator()(const O& o) const {return tail(o).cons(head);}
  template<typename O> cex const Expr<H,T,O> _concat(const O& o) const {return operator()(o);}
  template<typename O> cex const Expr<H,T,O> _concat(const Expr<O>& o) const {return operator()(o.head);}
  template<typename O,typename... OO> cex auto _concat(const Expr<O,OO...>& o) const->const decltype(o.cons(tail).cons(head)) {return o.cons(tail).cons(head);}
};

template<typename H,typename T,typename... TT>
struct Expr<H,T,TT...>:App {
  using Head=H;
  using Tail=Expr<T,TT...>;
  const Head& head;
  const Tail tail;
  cex Expr() {}
  cex Expr(const H& h,const Tail& t):head(h),tail(t) {}
  cex Expr(const H& h,const T& t,const TT&... tt):head(h),tail(t,tt...) {}
  template<typename O> cex const Expr<O,H,T,TT...> cons(const O& o) const {return {o,*this};}
  cex const Expr<H,T,TT...,const char*> operator()(const char* o) const {return tail(o).cons(head);}
  template<typename O> cex auto operator()(const O& o) const->const decltype(tail(o).cons(head)) {return tail(o).cons(head);}
  template<typename O> cex auto _concat(const O& o) const->const decltype(operator()(o)) {return operator()(o);}
  template<typename O> cex const Expr<H,T,TT...,O> _concat(const Expr<O>& o) const {return operator()(o.head);}
  template<typename O,typename... OO> cex auto _concat(const Expr<O,OO...>& o) const->const decltype(tail._concat(o).cons(head)) {return tail._concat(o).cons(head);}
};

template<typename... OO> cex const Expr<OO...> expr(const OO&... oo) {return {oo...};}

#ifdef YO_VERB
  template<typename Out,typename O,typename... OO> When<true||!isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...>& o) {return out<<"("<<o.head<<"@ "<<&o.head<<"| "<<o.tail<<")";}
  // template<typename Out,typename O,typename... OO> When< isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...>& o) {return out<<"("<<o.head<<" "<<o.tail<<")";}
#else
  template<typename Out,typename O,typename... OO> When<!isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...>& o) {return out<<o.head<<" "<<o.tail;}
  template<typename Out,typename O,typename... OO> When< isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...>& o) {return out<<"("<<o.head<<") "<<o.tail;}
#endif

template<typename O> cex const O _concat(const O& o,const Empty) {return o;}
template<typename A, typename B> cex const When<!isApp<A>()&&!isApp<B>(),Expr<A,B>> _concat(const A& a,const B& b) {return {a,b};}
template<typename A, typename B> cex auto _concat(const A& a,const B& b)->const When< isApp<A>(),decltype(a._concat(b))> {return a._concat(b);}
template<typename A, typename B> cex auto _concat(const A& a,const B& b)->const When<!isApp<A>()&&isApp<B>(),decltype(b.cons(a))> {return b.cons(a);}

//// beta reduction ////////////////////////////////////////////////

//beta steps--
template<typename C,typename O,typename... OO>
cex auto step(const Expr<C,O,OO...> o)
  -> const decltype(_concat(C::beta(o.tail.head),o.tail.tail))
  {return           _concat(C::beta(o.tail.head),o.tail.tail);}

template<typename C,typename O,typename P,typename... OO>
cex auto step(const Expr<C,O,P,OO...> o)
  -> const decltype(_concat(C::beta(o.tail.head,o.tail.tail.head),o.tail.tail.tail))
  {return           _concat(C::beta(o.tail.head,o.tail.tail.head),o.tail.tail.tail);}

template<typename C,typename O,typename P,typename Q,typename... OO>
cex auto step(const Expr<C,O,P,Q,OO...> o)
  -> const decltype(_concat(C::beta(o.tail.head, o.tail.tail.head, o.tail.tail.tail.head),o.tail.tail.tail.tail))
  {return           _concat(C::beta(o.tail.head, o.tail.tail.head, o.tail.tail.tail.head),o.tail.tail.tail.tail);}

template<typename C,typename O,typename P,typename Q,typename R,typename... OO>
cex auto step(const Expr<C,O,P,Q,R,OO...> o)
  -> const decltype(_concat(C::beta(o.tail.head, o.tail.tail.head, o.tail.tail.tail.head, o.tail.tail.tail.tail.head), o.tail.tail.tail.tail.tail))
  {return           _concat(C::beta(o.tail.head, o.tail.tail.head, o.tail.tail.tail.head, o.tail.tail.tail.tail.head), o.tail.tail.tail.tail.tail);}

template<typename O> cex const None step(const O) {return none;}

cex const Empty beta(const Empty);
template<typename O> cex auto beta(const O o)->const When<!isEmpty<O>(),decltype(res(step(o),o))>;
template<typename O> cex auto beta(const Expr<O> o)->const decltype(beta(o.head));

//recursion/result--
template<typename O> cex const O res(const O o,const O) {return o;}
template<typename O> cex const O res(const None,const O o) {return o;}
template<typename R,typename O,When<!isNone<O>()&&!is_same<R,O>::value,bool> = false> cex auto res(const R r,const O)->const decltype(beta(r)) {return beta(r);}

//beta start---
cex const Empty beta(const Empty) {return empty;}
template<typename O> cex auto beta(const O o)->const When<!isEmpty<O>(),decltype(res(step(o),o))> {return res(step(o),o);}
template<typename O> cex auto beta(const Expr<O> o)->const decltype(beta(o.head)) {return beta(o.head);}
//natural precedence -- this fixes the type level construction! runtime precdedence should be handled on construction (less rewrite)
template<typename O,typename... OO> cex auto beta(const Expr<O,OO...> o)->const When<!isApp<O>(),decltype(res(step(o),o))> {return res(step(o),o);}
template<typename O,typename... OO> cex auto beta(const Expr<O,OO...> o)->const When< isApp<O>(),decltype(beta(o.head._concat(o.tail)))> {return beta(o.head._concat(o.tail));}

////////////////////////////////////////////////////////////////
template<typename Fn>
struct Combinator:Lambda {
  template<typename O> cex const Expr<Fn,O> operator()(const O& o) const {return {*(Fn*)this,o};}
};

struct I:Combinator<I> {
  template<typename O> static cex const O beta(const O& o) {return o;}
};
cex const I _I;
template<typename Out> Out& operator<<(Out& out,const I) {return out<<"I";}

struct K:Combinator<K> {
  template<typename O,typename P> static cex const O beta(const O& o,const P&) {return o;}
};
cex const K _K;
template<typename Out> Out& operator<<(Out& out,const K) {return out<<"K";}

struct S:Combinator<S> {
  template<typename F,typename G,typename O> static cex auto beta(const F& f,const G& g,const O& o)->const decltype(f(o)(g(o))) {return f(o)(g(o));}
};
cex const S _S;
template<typename Out> Out& operator<<(Out& out,const S) {return out<<"S";}

//// test ///////////////////////////////////////////////////////////////
template<typename E> void show(const E e) {cout<<e<<endl;}
template<typename E> void show(const E e,const E) {cout<<e<<" -> irreducible."<<endl;}
template<typename E,typename R> void show(const E e,const R r) {cout<<e<<" = "<<r<<endl;}

template<typename E,typename R> void test(const E e,const R r) {show(e,r);}
template<typename E> void test(const E e) {show(e,beta(e));}

void steps(const None) {cout<<none<<endl;}
template<typename O> void steps(const O o) {
  cout<<o<<endl<<" = ";
  steps(step(o));
}

int main() {
  cout<<"start!"<<endl;
  // test(_I("ok")("zZz"));
  // test(_K("ok")("fail")("zZz"));
  // test(_S(_I)(_I)(_I)("ok")("zZz"));
  // cout<<_I(_I)<<" "<<&_I<<endl;
  // static cex const auto e1=_S(_I)(_I)(_I);//("ok")("zZz");
  // cout<<e1<<endl;
  // cout<<step(e1)<<endl;
  // steps(e1);
  const auto a=expr(_I,_I);
  const auto b=expr(_I,_I);
  const auto c=a(b);

  cout<<a<<endl;
  cout<<b<<endl;
  cout<<c<<endl;
  cout<<"end"<<endl;
  return  0;
} 
