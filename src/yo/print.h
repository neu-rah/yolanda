#pragma once

#include "lambda.h"
#include "curry.h"
#include "combinators.h"
#include "bool.h"
#include "peano.h"
#include "list.h" 

namespace yo {

  #ifdef ARDUINO
    Serial_& operator<<(Serial_& out,void* o) {out.print((int)o);return out;}
    template<typename O>
    typename enable_if<!isApp<O>()&&!isLambda<O>()&&!yo::isEmpty<O>()&&!isNone<O>(),Serial_>::type&
    operator<<(Serial_& out,const O o)      {out.print(o);return out;}
  #endif

  #ifdef YO_PRINT
    template<typename Out> Out& operator<<(Out& out, const None) {return out<<"⊥";}

    #ifdef YO_VERB
      template<typename Out> Out& operator<<(Out& out, const Empty) {return out<<"ø";}
    #else
      template<typename Out> Out& operator<<(Out& out, const Empty) {return out;}
    #endif

    template<typename Out,typename O,typename... OO> When<!isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...> o) {return out<<o.head<<" "<<o.tail;}
    template<typename Out,typename O,typename... OO> When< isApp<O>(),Out>& operator<<(Out& out,const Expr<O,OO...> o) {return out<<"("<<o.head<<") "<<o.tail;}

    template<typename Out,typename F, F f>
    Out& operator<<(Out& out,const yo::Curry<F,f>) {return out<<"λ"<<"("<<"@"<<(void*)f<<")";}

    template<typename Out> Out& operator<<(Out& out,const yo::I) {return out<<"I";}
    template<typename Out> Out& operator<<(Out& out,const yo::K) {return out<<"K";}
    template<typename Out> Out& operator<<(Out& out,const yo::S) {return out<<"S";}
    template<typename Out> Out& operator<<(Out& out,const yo::B) {return out<<"B";}
    template<typename Out> Out& operator<<(Out& out,const yo::C) {return out<<"C";}
    template<typename Out> Out& operator<<(Out& out,const yo::W) {return out<<"W";}
    template<typename Out> Out& operator<<(Out& out,const yo::T) {return out<<"T";}
    template<typename Out> Out& operator<<(Out& out,const yo::V) {return out<<"V";}
    template<typename Out> Out& operator<<(Out& out,const yo::M) {return out<<"M";}

    template<typename Out> Out& operator<<(Out& out,const yo::Id) {return out<<"id";}
    template<typename Out> Out& operator<<(Out& out,const yo::Const) {return out<<"const";}
    template<typename Out> Out& operator<<(Out& out,const yo::KI) {return out<<"KI";}
    template<typename Out> Out& operator<<(Out& out,const yo::Flip) {return out<<"flip";}
    template<typename Out> Out& operator<<(Out& out,const yo::Pair) {return out<<"pair";}
    template<typename Out> Out& operator<<(Out& out,const yo::L) {return out<<"L";}
    template<typename Out> Out& operator<<(Out& out,const yo::Y) {return out<<"Y";}
    template<typename Out> Out& operator<<(Out& out,const yo::Bb) {return out<<"Bb";}
    template<typename Out> Out& operator<<(Out& out,const yo::Fst) {return out<<"fst";}
    template<typename Out> Out& operator<<(Out& out,const yo::Snd) {return out<<"snd";}

    template<typename Out> Out& operator<<(Out& out,const yo::True) {return out<<"true";}
    template<typename Out> Out& operator<<(Out& out,const yo::False) {return out<<"false";}
    template<typename Out> Out& operator<<(Out& out,const yo::Not) {return out<<"not";}
    template<typename Out> Out& operator<<(Out& out,const yo::Or) {return out<<"or";}
    template<typename Out> Out& operator<<(Out& out,const yo::And) {return out<<"and";}
    template<typename Out> Out& operator<<(Out& out,const yo::BEq) {return out<<"===";}

    template<typename Out> Out& operator<<(Out& out,const yo::N0)   {return out<<"#0";}
    template<typename Out> Out& operator<<(Out& out,const yo::N1)   {return out<<"#1";}
    template<typename Out> Out& operator<<(Out& out,const yo::N2)   {return out<<"#2";}
    template<typename Out> Out& operator<<(Out& out,const yo::N3)   {return out<<"#3";}
    template<typename Out> Out& operator<<(Out& out,const yo::N4)   {return out<<"#4";}
    template<typename Out> Out& operator<<(Out& out,const yo::N5)   {return out<<"#5";}
    template<typename Out> Out& operator<<(Out& out,const yo::N6)   {return out<<"#6";}
    template<typename Out> Out& operator<<(Out& out,const yo::N7)   {return out<<"#7";}
    template<typename Out> Out& operator<<(Out& out,const yo::N8)   {return out<<"#8";}
    template<typename Out> Out& operator<<(Out& out,const yo::N9)   {return out<<"#9";}

    template<typename Out> Out& operator<<(Out& out,const yo::Add)   {return out<<"(+)";}
    template<typename Out> Out& operator<<(Out& out,const yo::Mul)   {return out<<"(*)";}
    template<typename Out> Out& operator<<(Out& out,const yo::Pow)   {return out<<"(^)";}
    template<typename Out> Out& operator<<(Out& out,const yo::Is0)   {return out<<"(0==)";}
    template<typename Out> Out& operator<<(Out& out,const yo::Succ)  {return out<<"(++)";}
    template<typename Out> Out& operator<<(Out& out,const yo::Phi)  {return out<<"φ";}
    template<typename Out> Out& operator<<(Out& out,const yo::Pred)  {return out<<"(--)";}
    template<typename Out> Out& operator<<(Out& out,const yo::Sub)   {return out<<"(-)";}
    template<typename Out> Out& operator<<(Out& out,const yo::LEq)   {return out<<"(≤)";}
    template<typename Out> Out& operator<<(Out& out,const yo::GEq)   {return out<<"(≥)";}
    template<typename Out> Out& operator<<(Out& out,const yo::GT)    {return out<<"(>)";}
    template<typename Out> Out& operator<<(Out& out,const yo::LT)    {return out<<"(<)";}
    template<typename Out> Out& operator<<(Out& out,const yo::Eq)    {return out<<"(=)";}
    template<typename Out> Out& operator<<(Out& out,const yo::NEq)   {return out<<"(≠)";}
    template<typename Out,int n> Out& operator<<(Out& out,const yo::FromInt<n>) {return out<<"fromInt<"<<n<<">";}

    template<typename Out> Out& operator<<(Out& out,const yo::Cons)           {return out<<"cons";}
    template<typename Out> Out& operator<<(Out& out,const yo::Nil)            {return out<<"nil";}
    template<typename Out> Out& operator<<(Out& out,const yo::Head)           {return out<<"head";}
    template<typename Out> Out& operator<<(Out& out,const yo::Tail)           {return out<<"tail";}
    template<typename Out> Out& operator<<(Out& out,const yo::Null)           {return out<<"null";}
    template<typename Out> Out& operator<<(Out& out,const yo::_Length)        {return out<<"_length";}
    template<typename Out> Out& operator<<(Out& out,const yo::Length)         {return out<<"length";}
    template<typename Out> Out& operator<<(Out& out,const yo::Drop)           {return out<<"drop";}
    template<typename Out> Out& operator<<(Out& out,const yo::Index)          {return out<<"index";}
    template<typename Out> Out& operator<<(Out& out,const yo::_Last)          {return out<<"_last";}
    template<typename Out> Out& operator<<(Out& out,const yo::Last)           {return out<<"last";}
    template<typename Out> Out& operator<<(Out& out,const yo::_Concat)        {return out<<"concat";}
    template<typename Out> Out& operator<<(Out& out,const yo::Concat)         {return out<<"concat";}
    template<typename Out> Out& operator<<(Out& out,const yo::_Init)          {return out<<"_init";}
    template<typename Out> Out& operator<<(Out& out,const yo::Init)           {return out<<"init";}
    template<typename Out> Out& operator<<(Out& out,const yo::_Reverse)       {return out<<"_reverse";}
    template<typename Out> Out& operator<<(Out& out,const yo:: Reverse)       {return out<< "reverse";}
    template<typename Out> Out& operator<<(Out& out,const yo::_TakeR)         {return out<<"_taker";}
    template<typename Out> Out& operator<<(Out& out,const yo::TakeR)          {return out<< "taker";}
    // template<typename Out> Out& operator<<(Out& out,const yo::_Take)           {return out<< "_take";}
    template<typename Out> Out& operator<<(Out& out,const yo::Take)           {return out<< "take";}
    template<typename Out> Out& operator<<(Out& out,const yo::Nats)           {return out<<"ℕ";}
    template<typename Out> Out& operator<<(Out& out,const yo::_Nats)          {return out<<"Nat";}
    template<typename Out> Out& operator<<(Out& out,const yo::Range)          {return out<<"range";}
    template<typename Out,typename S> Out& operator<<(Out& out,const Expr<yo::Nats,S> n)  {return out<< "["<<S{}<<"..]";}
    template<typename Out> Out& operator<<(Out& out,const yo::_Map)           {return out<<"_map";}
    template<typename Out> Out& operator<<(Out& out,const yo:: Map)           {return out<< "map";}
    template<typename Out> Out& operator<<(Out& out,const yo::_Filter)        {return out<<"_filter";}
    template<typename Out> Out& operator<<(Out& out,const yo:: Filter)        {return out<< "filter";}
    template<typename Out> Out& operator<<(Out& out,const yo::_FoldL)         {return out<<"_foldl";}
    template<typename Out> Out& operator<<(Out& out,const yo:: FoldL)         {return out<< "foldl";}
    template<typename Out> Out& operator<<(Out& out,const yo::_FoldR)         {return out<<"_foldr";}
    template<typename Out> Out& operator<<(Out& out,const yo:: FoldR)         {return out<< "foldr";}
    template<typename Out> Out& operator<<(Out& out,const yo::_Zip)           {return out<<"_zip";}
    template<typename Out> Out& operator<<(Out& out,const yo:: Zip)           {return out<< "zip";}
    template<typename Out> Out& operator<<(Out& out,const yo::FromBool)       {return out<<"fromBool";}

    #ifdef YO_VERB
      template<typename Out,typename O,typename... OO>
      Out& operator<<(Out& out,const List<O,OO...> o){
        if(beta(null(o)(1)(0))) return out;
        else return out<<"(@"<<&beta(head(o))<<"|"<<beta(head(o))<<":"<<beta(tail(o));
      }
    #else
      template<typename Out>
      Out& operator<<(Out& out,const List<> o){return out<<"[]";}
      template<typename Out,typename O,typename... OO>
      Out& operator<<(Out& out,const List<O,OO...> o){return out<<o.tail.head<<":"<<o.tail.tail.head;}
    #endif
  #else

    template<typename Out,typename O> When<isLambda<O>(),Out>& operator<<(Out& out,const O) {return out<<"λ";}
    template<typename Out,typename O> When<isApp<O>(),Out>& operator<<(Out& out,const O o) {return out<<o.head<<" "<<o.tail;}
    template<typename Out,typename O> When<isEmpty<O>()||isNone<O>(),Out>& operator<<(Out& out,const O) {return out;}

  #endif
};