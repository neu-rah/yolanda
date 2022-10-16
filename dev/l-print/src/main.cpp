#include <iostream>
#include <cstring>
using namespace std;

#include <yolanda.h>
using namespace yo;

/////////////////////////////////////////////////////////////////////////////
//device provides IO
template<typename In,typename Out>
struct Device {
  template<typename O>
  struct Part:O {};
};

template<typename Title,typename Body>
using Menu=Expr<Cons,Title,Body>;

constexpr const char* mainMenu_text="Main menu";
constexpr const char* op1_text="Op 1";
constexpr const char* op2_text="Op 2";
constexpr const char* opn_text="Op...";

using Op1=StaticText<&op1_text>;

using MainMenu=Menu<
  StaticText<&mainMenu_text>,
  List<
    Op1,
    StaticText<&op2_text>,
    StaticText<&opn_text>
  >
>;

using Title=Fst;
using Body=Snd;
constexpr const Title title;
constexpr const Body body;

MainMenu mainMenu;

using Test=List<StaticChar<'a'>,StaticChar<'b'>>;

template<const char* const* text,size_t i,bool end> struct _CharList;

template<const char* const* text,size_t i=0>
using CharList=_CharList<text,i,(strlen(text[0])<=i)>;

template<const char* const* text,size_t i,bool end> struct _CharList;

template<const char* const* text,size_t i>
struct _CharList<text,i,false>:Expr<
  Cons,StaticChar<text[0][i]>,CharList<text,i+1>
> {};

template<const char* const* text,size_t i>
struct _CharList<text,i,true>:Nil {};

template<const char* const* text,size_t i,bool end>
Str toStr(const _CharList<text,i,end>&) {return &text[0][i];}


using L1=CharList<&opn_text>;

int main() {
  // cout<<"testing"<<endl;
  _print(title(mainMenu));
  _print(yo::index(body(mainMenu))(n0));
  _print(yo::index(body(mainMenu))(n1));
  _print(yo::index(body(mainMenu))(n2));
  _print((_map(show)(body(mainMenu))));
  _print(Expr<Head,L1>::Run());
  _print(Expr<Head,Expr<Tail,L1>::Run>());
  _print(_map(print)(L1()).beta());
  return 0;
}