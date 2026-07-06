#include <iostream>
#include <string>

using namespace std;

template <typename T = int>
class DataPackage {
 public:
  DataPackage(T first) : first(first) {};
  template <typename C>
  friend void PrintOutFriendElement(C& data_object);

 private:
  T first;
};

template <typename C>
void PrintOutFriendElement(C& data_object) {
  cout << "(friend 클래스 템플릿 호출) 템플릿 매개변수 값: "
       << data_object.first << endl;
}

int main() {
  DataPackage<> template_inst1(5);
  DataPackage<string> template_inst2("클래스 템플릿 기본값이 아닌 string형");

  PrintOutFriendElement(template_inst1);
  PrintOutFriendElement(template_inst2);
  return 0;
}