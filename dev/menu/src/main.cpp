#include <iostream>
using namespace std;

#include <yolanda.h>

using ConstText=const char*;

template<ConstText*text>
struct StaticText {template<typename O> struct Part:yo::StaticText<text>,O {};};

struct Empty {
    template<typename Out>
    static void printTo(Out&) {}
};

struct Text {
  template<typename O> 
  struct Part:yo::Text,O {
    using yo::Text::Text;
    template<typename Out>
    void printTo(Out& o) const {
      o<<(*this);
      O::printTo(o);
    }
  };
};

ConstText main_text="Main menu";
StaticText<&main_text>::Part<Empty> title;

Text::Part<Empty> text("!");

using yo::cons;
using yo::nil;
auto comment=cons(yo::Text("<!-- "),cons(yo::Text(" -->"),nil));

int main() {
  cout<<"test ----------------"<<endl;
  text.printTo(cout);
  cout<<"end. ----------------"<<endl;
  return 0;
}