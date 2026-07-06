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
  template<typename D>
  friend void PrintOutData(D& data);

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
template<typename D>
void PrintOutData(D& data) {
  cout << "Data: " << data.GetData() << endl;
}
int main() {
  DataPackage<bool> bool_a(true), bool_b(false);
  DataPackage<int> int_a(10), int_b(10);
  DataPackage<float> float_a(1.234567f), float_b(2.345678f);
  DataPackage<double> double_a(1.234567), double_b(1.234568);
  DataPackage<string> string_a("Hello World"), string_b("hello world");

  PrintOutData(bool_a);
  PrintOutData(int_a);
  PrintOutData(float_a);
  PrintOutData(double_a);
  PrintOutData(string_a);

  return 0;
}