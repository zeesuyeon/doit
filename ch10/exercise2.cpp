#include <string>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>

using namespace std;

template <typename T>
bool is_equal(T data1, T data2) {
  return data1 == data2;
}

template <>
bool is_equal(double data1, double data2) {
  return abs(data1 - data2) <= 0.00001;
}

template <>
bool is_equal(float data1, float data2) {
  return abs(data1 - data2) <= 0.00001;
}

template <>
bool is_equal(string data1, string data2) {
  data1.erase(remove_if(data1.begin(), data1.end(), ::isspace), data1.end());
  data2.erase(remove_if(data2.begin(), data2.end(), ::isspace), data2.end());

  std::transform(data1.begin(), data1.end(), data1.begin(), ::tolower);
  std::transform(data2.begin(), data2.end(), data2.begin(), ::tolower);

  return data1 == data2;
}

int main() {
  bool bool_a = true, bool_b = false;
  int int_a = 10, int_b = 10;
  float float_a = 1.234567f, float_b = 2.345678f;
  double double_a = 1.234567, double_b = 1.234568;
  string string_a = "Hello World", string_b = "hello world";

  cout << "[bool] a: " << bool_a << ", b: " << bool_b << " -> "
       << is_equal(bool_a, bool_b) << endl;
  cout << "[int] a: " << int_a << ", b: " << int_b << " -> "
       << is_equal(int_a, int_b) << endl;
  cout << "[float] a: " << float_a << ", b: " << float_b << " -> "
       << is_equal(float_a, float_b) << endl;
  cout << "[double] a: " << double_a << ", b: " << double_b << " -> "
       << is_equal(double_a, double_b) << endl;
  cout << "[string] a: " << string_a << ", b: " << string_b << " -> "
       << is_equal(string_a, string_b) << endl;

  return 0;
}