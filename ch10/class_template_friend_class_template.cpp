#include <iostream>
#include <string>

using namespace std;

template <typename U>
class Caller {
 public:
  Caller() : object(nullptr) {};
  void SetObject(U* obj_pointer) { object = obj_pointer; };
  void PrintOutFriendObject() {
    cout << "(friend 클래스 템플릿 호출) 템플릿 매개변수 값: " << object->first
         << endl;
  };

 private:
  U* object;
};

template <typename T = int>
class DataPackage {
 public:
  DataPackage(T first) : first(first) {};
  friend Caller<DataPackage>;

 private:
  T first;
};

int main() {
  Caller<DataPackage<>> caller_int_obj;
  Caller<DataPackage<string>> caller_string_obj;

  DataPackage<> template_inst1(5);
  DataPackage<string> template_inst2("클래스 템플릿 기본값이 아닌 string형");

  caller_int_obj.SetObject(&template_inst1);
  caller_string_obj.SetObject(&template_inst2);
  caller_int_obj.PrintOutFriendObject();
  caller_string_obj.PrintOutFriendObject();
  return 0;
}