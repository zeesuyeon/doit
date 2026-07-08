#include <iostream>
#include <map>
#include <array>

using namespace std;

map<char, array<int, 4>> auto_type_example;
map<int, array<double, 3>> auto_type_example_2;

void build_map() {
  array<int, 4> array_a = {1, 2, 3, 4};
  auto_type_example.insert({'a', array_a});

  array<double, 3> array_e = {3.0, 4.0, 5.0};
  auto_type_example_2.insert({1, array_e});
}

int main(){
  build_map();

  map<char, array<int, 4>>::iterator iter;
  for (iter = auto_type_example.begin(); iter != auto_type_example.end(); iter++) {
    //
  }

  map<int, array<double, 3>>::iterator iter2;
  for (iter2 = auto_type_example_2.begin(); iter2 != auto_type_example_2.end(); iter2++) {
    //
  }

  auto iter3 = auto_type_example.begin();
  for (; iter3 != auto_type_example.end(); iter3++) {
    //
  }

  return 0;
}