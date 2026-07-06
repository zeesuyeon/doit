#include <iostream>
#include <string>
using namespace std;

template <typename Type1, typename Type2>
class data_package {
 public:
  template <typename Type3>
  class nested_class_data_package {
   public:
    nested_class_data_package(Type3 data) : nested_class_data(data) {};
    Type3 get_element() { return nested_class_data; };
    Type3 nested_class_data;
  };

  template <typename Type4>
  class nested_class {
   public:
    nested_class(Type4 data) : nested_class_data(data) {};
    void print_out_element() {
      cout << "중첩 클래스 데이터: " << nested_class_data << endl;
    }

   private:
    Type4 nested_class_data;
  };

  data_package(Type1 first, Type2 second) : first(first), second(second) {};
  void print_out_element() {
    cout << "First: " << first << ", Second: " << second << endl;
    cout << "Nested class data: " << internal_data.get_element() << endl;
  }

 private:
  Type1 first;
  Type2 second;
  nested_class_data_package<Type2> internal_data;
};

int main() {
  data_package<int, double> template_inst1(5, 10.5);
  data_package<string, int>::nested_class<int> template_inst2(500);

  template_inst1.print_out_element();
  template_inst2.print_out_element();
}