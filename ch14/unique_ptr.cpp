#include <iostream>
#include <memory>

using namespace std;

class class_object {
public:
 class_object() { cout << "메모리가 할당되었습니다." << endl; };
 ~class_object() { cout << "메모리가 해제되었습니다." << endl; };
 void print_out() { cout << "객체의 함수를 호출합니다." << endl; };
};

int main(){
  // unique_ptr<class_object> unique_pointer(new class_object());
  unique_ptr<class_object> unique_pointer = make_unique<class_object>();
  unique_pointer->print_out();

  return 0;
}