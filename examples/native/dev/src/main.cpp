#ifdef ARDUINO
  #include <Arduino.h>
  #include <streamFlow.h>
  using namespace StreamFlow;
  #define cout Serial
  #define endl "\n"
  #include <avr_std.h>
  using namespace avr_std;
#else
  #include <iostream>
  using namespace std;
#endif

#include <yolanda.h>
using namespace yo;

cex const auto e1{id(1967)};
cex const auto e2{_true(id)(1967)(11)};
cex const auto e3{_S(id)(id)(id)};

void run() {
  cout<<"start"<<endl;
  cout<<beta(empty("ok")("zZz"))<<endl;
  cout<<beta(e1("ok")("zZz"))<<endl;
  cout<<beta(e2("ok")("zZz"))<<endl;
  cout<<beta(e3("ok")("zZz"))<<endl;
  // cout<<"end"<<endl;
}

#ifdef ARDUINO
  void setup() {
    Serial.begin(115200);
    while(!Serial);
    run();
  }
  void loop() {}
#else
  int main() {
    run();
    return  0;
  } 
#endif