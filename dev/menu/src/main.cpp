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

Text::Part<Empty> text("!\r\n");

using yo::cons;
using yo::nil;
auto comment=cons(yo::Text("<!-- "))(cons(yo::Text(" -->"))(nil));

template<typename O>
Str toStr(const O o) {return cStr(forward<O>(o));}

template<typename Out,Out& out>
struct PrintTo {
  template<typename O>
  static void printTo(O&& o) {out<<o;}
};

template<typename O>
auto _printTo=PrintTo<decltype(cout),cout>::printTo<O>;

template<typename O>
yo::Curry<decltype(&_printTo<O>),&_printTo<O>> printTo;

int main() {
  cout<<"test ----------------"<<endl;
  // text.printTo(cout);
  printTo<decltype(move(text))>(move(text));
  cout<<"end. ----------------"<<endl;
  return 0;
}