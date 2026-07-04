#include <iostream>
#include <string>

using namespace std;

struct Monster {
  std::string name;
  int age;
  int height;
  float weight;
  std::string color;
};

void print(Monster* _monster) {
  cout << "name: " << _monster->name << endl;
  cout << "age: " << _monster->age << endl;
  cout << "height: " << _monster->height << endl;
  cout << "weight: " << _monster->weight << endl;
  cout << "color: " << _monster->color << endl;
}

int main () {
  Monster monster = {"monster", 100, 100, 100, "red"};

  print(&monster);
  
  return 0;
}