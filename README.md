# Yolanda - micro lambda

### a C++ compiled untyped lambda-calculus that actually typechecks...

This library provides both type level and runtime versions of a lazy functional language.

## Yolanda is:

- static, all constants
- lazy, things only run if needed
- functional, all things are functions
- curryed, we can use partial application
- ~~SKI based, all other combinators are derived~~ not anymore, implemented many others as buitin code to obtain a more compact executable file
- can fit into MCU's (specially the typelevel layer), hence the C++11 base.

## Example
```c++
using Test=False;
clog<<(Test::Bind<Type<int>>::Bind<Type<float>>::Run::Def)1.23<<endl;
//compile time (typelevel)
cout<<toInt(Expr<Length,Expr<Cons,StaticInt<1>,Nil>>::Run())<<endl;
//runtime
cout<<toInt(length(cons(n1)(nil)))<<endl;
```
## About

This pseudo-language uses C++11 compiler and works both at typelevel and runtime.

Functions have a duo, all function starting with a capital letter are compile time evaluated (type-level), others will work at runtime (compiled).

**Head** type level, result is a type or dependent type.

**head** runtime level, result is a value

## Objective

Exploring functional paradigm

Extend C++ compiler

Use typelevel for small MCU's

## Language

implemented so far:

### Core

**Flip** - `λfab.fba` used function `f` with arguments in reverse order  
**Pair** - `λabf.fab` construct pair or values to deliver to function `f`  
**Fst** - `λo.o(λab.a)` get first element of a pair  
**Snd** - `λo.o(λab.b)` get second element of a pair  

### Logic
**True** - select first option `λab.a`  
**False** - select second option `λab.b`  
**And** - functional boolean `and`  
**Or** - functional boolean `or`  
**Not** - functional negation  

### Peano numerals

using Church encoded numerals

**Succ** - successor of a nominal  
**Pred** - predecessor or a nominal  
**N0 .. N9** - predefined numerals  
**Is0** - check if numeral is N0  
**Add** - sum 2 numerals  
**Sub** - subtract 2 numeral  
**Mul** - multiply 2 numerals  
**Pow** - numerals power  
**Eq** - check numeral equality  
**NEq** - check numeral inequality  
**LEq** - check numeral `<=` relation  
**GEq** - check numeral `>=` relation  
**Lt** - check numeral `<` relation  
**Gt** - check numeral `>` relation  

### List functions
**Head** - get first element of a list  
**Tail** - get ramaining of a list (but the head)  
**Cons** - construct a list node  
**Nil** - empty list  
**Null** - check if list is empty  
**Length** - get list length (numeral)  
**Index** - get element at index  
**Drop** - drop elements from list head  
**Init** - get list of all but last element  
**Last** - get last element of a list  
**Reverse** - reverse list order  
**Concat** - join 2 lists  
**Map** - map a function over list elements  
**Filter** - filter list elements  
**FoldL** - left fold a list with a function and start value  
**FoldR** - right fold a list with a function and start value  
**Zip** - join 2 lists in a list of pairs with minimal length  

### Extras
**Nothing** - `λn.λj.n`  
**Just** - `λxnj.j x`  

### Runtime

All above types have a runtime function with the same name but with a first low-case letter.

## SKI

**S:=** - λfgo.f(g o)  
**K:=** - λab.a  
**I:=** - λo.o  

### Other combinators

B,C,M,L,Y,T,V,R,Bb,Id

id

### aux functions

**toBool** convert expression to c++ bool

**toInt** convert expression to c++ int (numeral to c++ int)

**toStr** convert expression to string or String, depending on the platform

**print** reduces and prints the expression reduction result.

## sources

https://www.angelfire.com/tx4/cus/combinator/birds.html

https://users.monash.edu/~lloyd/tildeFP/Lambda/Examples/const-list/

https://sincereflattery.blog/2021/04/26/lists-in-the-lambda-calculus/

https://blog.ploeh.dk/2018/06/04/church-encoded-maybe/

https://www.cl.cam.ac.uk/~rmk35/lambda_calculus/lambda_calculus.html

https://github.com/neu-rah/lpp
