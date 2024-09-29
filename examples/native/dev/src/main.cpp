#ifdef ARDUINO
  #include <Arduino.h>
// #endif
// #ifdef __AVR__
  #include <streamFlow.h>
  using namespace StreamFlow;
  #define cout Serial
  #define endl "\n"
  #ifdef __AVR__
    #include <avr_std.h>
    using namespace avr_std;
  #endif
#else
  #include <iostream>
  using namespace std;
#endif

// #define cex
#define cex constexpr

template<bool chk,typename T> using When=typename enable_if<chk,T>::type;

template<typename T>
struct Data {
  using Type=T;
  const Type data;
  cex Data(const T& o):data(o) {}
};

template<typename O> cex const Data<const O&> data(const O&  o) {return {o};}
template<typename O> cex const Data<O>  data(const O&& o) {return Data<O>{o};}

cex const int y=1967;
cex const auto a{data(y)};
cex const auto b{data(11)};

int main() {
  cout<<"start!"<<endl;
  cout<<&y<<endl;
  cout<<&a.data<<endl;
  cout<<&b.data<<endl;
  cout<<&data(y).data<<endl;
  cout<<&data(11).data<<endl;
  cout<<&data(23).data<<endl;
  cout<<"end."<<endl;
  return  0;
} 
