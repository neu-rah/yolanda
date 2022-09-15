#include <iostream>
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

const char* mainMenu_text="Main menu";
const char* op1_text="Op 1";
const char* op2_text="Op 2";
const char* opn_text="Op...";

using MainMenu=Menu<
  StaticText<&mainMenu_text>,
  List<
    StaticText<&op1_text>,
    StaticText<&op2_text>,
    StaticText<&opn_text>
  >
>;

using Title=Fst;
using Body=Snd;
constexpr const Title title;
constexpr const Body body;

MainMenu mainMenu;

int main() {
  // cout<<"testing"<<endl;
  _print(title(mainMenu));
  _print(index(body(mainMenu))(n0));
  _print(index(body(mainMenu))(n1));
  _print(index(body(mainMenu))(n2));
  //need map!
  // print(index(body(mainMenu))(n0));
  _print((_map(show)(body(mainMenu))));
  _print(StaticText<&op1_text>());
  return 0;
}