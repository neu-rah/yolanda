# Yolanda - micro lambda

### a C++ compiled untyped lambda-calculus that actually typechecks...

This library provides both type level and runtime versions of a lazy functional language.

## Yolanda is:

- static, all constants
- lazy, things only run if needed
- functional, all things are functions
- curryed, we can use partial application
- type inference
- can fit into MCU's (specially the typelevel layer), => the C++11 base.

## Example
```c++
cout<<beta(toInt(length(list(1,2,3,"ok!"))))<<endl;
cout<<beta(toInt(foldl(mul)(n2)(list(n2,n3))))<<endl;
```
output:
```text
4  
12
```

## changes

* full rewrite
* reversed execution queue order for smaller stacks
* full relly on `decltype(...)`, along with `constexpr` to obtain the type-level/compile-time versions
* use `beta(...)` function for expression reduction

## About

This pseudo-language uses C++11 compiler and works both at typelevel and runtime.

## Objective

Exploring functional paradigm

Extend C++ compiler

Use typelevel for small MCU's

## Language

implemented so far:

### Core

**flip** - `λfab.fba` used function `f` with arguments in reverse order  
**pair** - `λabf.fab` construct pair or values to deliver to function `f`  
**fst** - `λo.o(λab.a)` get first element of a pair  
**snd** - `λo.o(λab.b)` get second element of a pair  

### Logic
**_true** - select first option `λab.a`  
**_false** - select second option `λab.b`  
**_and** - functional boolean `and`  
**_or** - functional boolean `or`  
**_not** - functional negation  
**beq** - boolean equality  

### Peano numerals

using Church encoded numerals

**succ** - successor of a nominal  
**pred** - predecessor or a nominal  
**n0 .. n9** - predefined numerals  
**is0** - check if numeral is N0  
**add** - sum 2 numerals  
**sub** - subtract 2 numeral  
**mul** - multiply 2 numerals  
**_pow** - numerals power  
**eq** - check numeral equality  
**neq** - check numeral inequality  
**leq** - check numeral `<=` relation  
**geq** - check numeral `>=` relation  
**lt** - check numeral `<` relation  
**gt** - check numeral `>` relation  

### List functions
**head** - get first element of a list  
**tail** - get ramaining of a list (but the head)  
**cons** - construct a list node  
**nil** - empty list  
**null** - check if list is empty  
**length** - get list length (numeral)  
**index** - get element at index  
**drop** - drop elements from list head  
**init** - get list of all but last element  
**last** - get last element of a list  
**reverse** - reverse list order  
**take** - take elements from list start  
**nats** - list of all natural numbers as numerals (infinit list)  
**range** - range of numerals (list)
**concat** - join 2 lists  
**_map** - map a function over list elements  
**filter** - filter list elements  
**foldl** - left fold a list with a function and start value  
**foldr** - right fold a list with a function and start value  
**zip** - join 2 lists in a list of pairs with minimal length  

### Compile-time

**use:**

`constexpr` turn any code into a compile time value

`decltype` get type of expression 

## SKI

**S:=** - λfgo.f(g o)  
**K:=** - λab.a  
**I:=** - λo.o  

### Other combinators

**B:=** - λfgo.f(go)  
**C:=** - λfab.fba  
**M:=** - λo.oo  
**L:=** - CBM  
**Y:=** - SLL  
**T:=** - λof.fo  
**V:=** - λabf.fab  
**Bb:=** - BBB  

### aux functions

**beta** perform full beta reduction, returns the same if irreducible

**step** perform beta reduction step, return None if irreducible

**expr** expression builder, returns a chain of function application

**toBool** convert expression to c++ bool

**toInt** convert expression to c++ int (numeral to c++ int)

~~**toStr** convert expression to string or String, depending on the platform~~

~~**print** reduces and prints the expression reduction result.~~

now using c++ `operator<<(...)` for printing

**list** build a polymorphic list

example
```c++
constexpr const auto l1=list(1,2,"Ok");//compile time list build
const auto l2=list(1,2,"Ok");//runtime list build
```

## sources

https://www.angelfire.com/tx4/cus/combinator/birds.html

https://users.monash.edu/~lloyd/tildeFP/Lambda/Examples/const-list/

https://sincereflattery.blog/2021/04/26/lists-in-the-lambda-calculus/

https://blog.ploeh.dk/2018/06/04/church-encoded-maybe/

https://www.cl.cam.ac.uk/~rmk35/lambda_calculus/lambda_calculus.html

https://github.com/neu-rah/lpp

https://www.youtube.com/watch?v=3kMvXXGXaws

https://sookocheff.com/post/fp/evaluating-lambda-expressions/

https://groups.seas.harvard.edu/courses/cs152/2021sp/lectures/sld07-lambdacalc.pdf

https://gist.github.com/typesafedev/3465fab6320b39aa09b701a51f394f2d

https://codegolf.stackexchange.com/questions/231911/we-all-know-how-to-ski-but-can-you-bckw

https://en.wikipedia.org/wiki/B,_C,_K,_W_system

https://en.wikipedia.org/wiki/SKI_combinator_calculus

https://en.wikipedia.org/wiki/Combinatory_logic