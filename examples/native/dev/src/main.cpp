#include <iostream>
using namespace std;

#define cex constexpr

template<bool chk,typename T> using When=typename enable_if<chk,T>::type;

struct App{};
struct Lambda{};
struct None{};
constexpr const None none;
template<typename Out> Out& operator<<(Out& out, const None) {return out<<"⊥";}

template<typename...> struct Expr;

template<> struct Expr<> {
  template<typename O> cex const Expr<O> cons(const O o) const {return o;}
  template<typename O> cex const Expr<O> operator()(const O o) const {return {o};}
  template<typename O> cex const O concat(const O o) const {return o;}
};
using Empty=Expr<>;
constexpr const Empty empty;
template<typename Out> Out& operator<<(Out& out, const Empty) {return out<<"ø";}

template<typename H,typename... TT>
struct Expr<H,TT...>:App {
  using Head=H;
  using Tail=Expr<TT...>;
  const Head head;
  const Tail tail;
  cex Expr():head(Head{}),tail(Tail{}){}
  cex Expr(const Head h,const Tail t):head(h),tail(t) {}
  cex Expr(const Head h,const TT... tt):head(h),tail(Expr<TT...>{tt...}) {}
  template<typename O> cex const Expr<O,H,TT...> cons(const O o) const {return {o,*this};}
  template<typename O> cex const Expr<H,TT...,O> operator()(const O o) const {return {head,tail(o)};}
  template<typename O> cex const Expr<H,TT...,O> concat(const Expr<O> o) const {return operator()(o.head);}
  template<typename O,typename... OO> cex const Expr<H,TT...,O,OO...> concat(const Expr<O,OO...> o) const {return tail.concat(o).cons(head);}
};

template<typename O> constexpr bool isEmpty() {return is_same<O,Empty>::value;}
template<typename O> constexpr bool isApp() {return is_convertible<O,App>::value;}

cex const Empty expr() {return empty;}
template<typename O> cex const When<isApp<O>(),O> expr(const O o) {return o;}
template<typename O,typename... OO> cex const When<!isApp<O>(),Expr<O,OO...>> expr(const O o,const OO... oo) {return Expr<O,OO...>(o,oo...);}
template<typename O,typename... OO> cex auto expr(const O o,const OO... oo)->const When< isApp<O>(),decltype(o.concat(expr(oo...)))> {return o.concat(expr(oo...));}
template<typename... OO> cex const Expr<OO...> expr(const OO... oo) {return Expr<OO...>(oo...);}

template<typename Out,typename O,typename... OO> When<!isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...> o) {return out<<o.head<<" "<<o.tail;}
template<typename Out,typename O,typename... OO> When< isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...> o) {return out<<"("<<o.head<<") "<<o.tail;}

template<typename A, typename B> cex const When<!isApp<A>()&&!isApp<B>(),Expr<A,B>> concat(const A a,const B b) {return {a,b};}
template<typename A, typename B> cex auto concat(const A a,const B b)->const When< isApp<A>(),decltype(a.concat(b))> {return a.concat(b);}
template<typename A, typename B> cex auto concat(const A a,const B b)->const When<!isApp<A>()&&isApp<B>(),decltype(b.cons(a))> {return b.cons(a);}

template<typename Fn>
struct Combinator:Lambda {
  template<typename O> cex Expr<Fn,O> operator()(const O o) const {return {*(Fn*)this,o};}
};

struct I:Combinator<I> {
  template<typename O> static cex const O beta(const O o) {return o;}
};
cex const I id;
template<typename Out> Out& operator<<(Out& out, const I) {return out<<"id";}

struct K:Combinator<K> {
  template<typename O,typename P> static cex const O beta(const O o,const P) {return o;}
};
cex const K _true;
template<typename Out> Out& operator<<(Out& out, const K) {return out<<"true";}

struct S:Combinator<S> {
  template<typename F,typename G,typename O> static cex auto beta(const F f,const G g, const O o)->const decltype(f(o)(g(o))) {return f(o)(g(o));}
};
cex const S _S;
template<typename Out> Out& operator<<(Out& out, const S) {return out<<"S";}

template<typename C,typename O,typename... OO>
cex auto step(const Expr<C,O,OO...> o)
  -> const decltype(concat(C::beta(o.tail.head),o.tail.tail))
  {return           concat(C::beta(o.tail.head),o.tail.tail);}

template<typename C,typename O,typename P,typename... OO>
cex auto step(const Expr<C,O,P,OO...> o)
  -> const decltype(concat(C::beta(o.tail.head,o.tail.tail.head),o.tail.tail.tail))
  {return           concat(C::beta(o.tail.head,o.tail.tail.head),o.tail.tail.tail);}

template<typename C,typename O,typename P,typename Q,typename... OO>
cex auto step(const Expr<C,O,P,Q,OO...> o)
  -> const decltype(concat(C::beta(o.tail.head, o.tail.tail.head, o.tail.tail.tail.head),o.tail.tail.tail.tail))
  {return           concat(C::beta(o.tail.head, o.tail.tail.head, o.tail.tail.tail.head),o.tail.tail.tail.tail);}

template<typename C,typename O,typename P,typename Q,typename R,typename... OO>
cex auto step(const Expr<C,O,P,Q,R,OO...> o)
  -> const decltype(concat(C::beta(o.tail.head, o.tail.tail.head, o.tail.tail.tail.head, o.tail.tail.tail.tail.head), o.tail.tail.tail.tail.tail))
  {return           concat(C::beta(o.tail.head, o.tail.tail.head, o.tail.tail.tail.head, o.tail.tail.tail.tail.head), o.tail.tail.tail.tail.tail);}

template<typename O> cex const None step(const O) {return none;}

//// test ///////////////////////////////////////////////////////////////
template<typename E> void show(const E e) {cout<<e<<endl;}
template<typename E> void show(const E e,const E) {cout<<e<<" -> irreducible."<<endl;}
template<typename E,typename R> void show(const E e,const R r) {cout<<e<<" = "<<r<<endl;}

template<typename E,typename R> void test(const E e,const R r) {show(e,r);}
template<typename E> void test(const E e) {show(e,beta(e));}

void steps(const None) {cout<<none<<endl;}
template<typename O> void steps(const O o) {
  cout<<o<<" = ";
  steps(step(o));
}

int main() {
  static cex const auto e1=id("ok")("zZz");
  static cex const auto e2=_true("ok")("fail")("zZz");
  static cex const auto e3=_S(id)(id)(id)("ok")("zZz");
  steps(e1);
  steps(e2);
  steps(e3);
  return 0;
}