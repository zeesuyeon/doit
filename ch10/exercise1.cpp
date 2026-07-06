#include <iostream>
#include <string>
using namespace std;

template <typename T>
void print_data(T data) {
  cout << "입력 받은 값은 " << data << endl;
}

int main() {
  print_data("문자열");
  print_data(100);
  print_data('A');
  return 0;
}