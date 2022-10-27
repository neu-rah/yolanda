#include <Arduino.h>
#include <yolanda.h>
using namespace yo;

using ConstText=const char*;

ConstText main_text="Main menu";
ConstText op1_text="Op #1";
ConstText op2_text="Op #2";
ConstText opn_text="Op...";
ConstText yes_text="yes";
ConstText no_text="no";

using Yes=StaticText<&yes_text>;
using No=StaticText<&no_text>;
constexpr const Yes yes;
constexpr const No no;

using L1=List<
  StaticInt<1>,
  StaticText<&main_text>
>;
L1 l1;

// auto l1=list(1,main_text);

using L2=List<
  StaticInt<1>,
  StaticInt<2>,
  StaticInt<3>
>;
L2 l2;

void setup() {
  Serial.begin(115200);
  // while(!Serial);
  // cout<<"---{ yolanda AVR port }---"<<endl;
  //using this typelevel or runtume syntax 
  // results in same memory usage as long 
  // as the defs are typelevel (with static data)

  // cout<<(Expr<Head,L1>::Beta::Beta::Beta{})<<endl;
  // cout<<beta(Expr<Head,L1>::Beta::Beta::Beta{})<<endl;
  #ifdef Yo
    print(head(l1));
    print(id(Int(1967)));
    print(_true(Text(yes_text))(Text(no_text)));
    print(toInt(length(l1)));
    print(is0(length(l1))(yes)(no));
  #else
    cout<<beta(head(l1))<<endl;
    cout<<beta(id(1967))<<endl;
    cout<<beta(_true(yes_text)(no_text))<<endl;
    cout<<toInt(length(l1))<<endl;
    cout<<beta(is0(length(l1))(yes)(no))<<endl;
  #endif
  // cout<<beta(index(l1)(n1))<<endl;
  // cout<<beta(_true(Id{}))<<endl;//using rvalue
  // cout<<beta(_true(id))<<endl;//using lvalue
  // cout<<beta(fst(head( drop(n1)(zip(l1)(l2)) )))<<endl;
}


void loop() {
  Serial.write('.');
  delay(1000);
}