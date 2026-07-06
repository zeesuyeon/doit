#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class DataPackage {
 public:
  DataPackage(T data) { data_ = data; };
  bool operator==(DataPackage& operand) { return data_ == operand.GetData(); };
  T GetData() { return data_; };

 private:
  T data_;
};

template <>
class DataPackage<double> {
 public:
  DataPackage(double data) { data_ = data; };
  bool operator==(DataPackage<double>& operand) {
    return abs(data_ - operand.GetData()) <= 0.00001;
  };
  double GetData() { return data_; };

 private:
  double data_;
};

template <>
class DataPackage<float> {
 public:
  DataPackage(float data) { data_ = data; };
  bool operator==(DataPackage<float>& operand) {
    return abs(data_ - operand.GetData()) <= 0.00001;
  };
  float GetData() { return data_; };

 private:
  float data_;
};

template <>
class DataPackage<string> {
 public:
  DataPackage(string data) {
    data.erase(remove_if(data.begin(), data.end(), ::isspace), data.end());
    std::transform(data.begin(), data.end(), data.begin(), ::tolower);
    data_ = data;
  };
  bool operator==(DataPackage<string>& operand) {
    return data_ == operand.GetData();
  };
  string GetData() { return data_; };

 private:
  string data_;
};

int main() {
  DataPackage<bool> bool_a(true), bool_b(false);
  DataPackage<int> int_a(10), int_b(10);
  DataPackage<float> float_a(1.234567f), float_b(2.345678f);
  DataPackage<double> double_a(1.234567), double_b(1.234568);
  DataPackage<string> string_a("Hello World"), string_b("hello world");

  cout << "[bool] a: " << bool_a.GetData() << ", b: " << bool_b.GetData()
       << " -> " << (bool_a == bool_b) << endl;
  cout << "[int] a: " << int_a.GetData() << ", b: " << int_b.GetData() << " -> "
       << (int_a == int_b) << endl;
  cout << "[float] a: " << float_a.GetData() << ", b: " << float_b.GetData()
       << " -> " << (float_a == float_b) << endl;
  cout << "[double] a: " << double_a.GetData() << ", b: " << double_b.GetData()
       << " -> " << (double_a == double_b) << endl;
  cout << "[string] a: " << string_a.GetData() << ", b: " << string_b.GetData()
       << " -> " << (string_a == string_b) << endl;

  return 0;
}