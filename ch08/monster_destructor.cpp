#include <iostream>
using namespace std;

class Monster {
 public:
  Monster();
  virtual ~Monster();

 private:
  int* dummy;
};

Monster::Monster() {
  cout << "Monster() 생성자 호출" << endl;
  dummy = new int;
}

Monster::~Monster() {
  cout << "~Monster() 소멸자 호출" << endl;
  delete dummy;
}

class MonsterA : public Monster {
 public:
  MonsterA();
  ~MonsterA();

 private:
  int* dummy_a;
};

MonsterA::MonsterA() {
  cout << "MonsterA() 생성자 호출" << endl;
  dummy_a = new int;
}

MonsterA::~MonsterA() {
  cout << "~MonsterA() 소멸자 호출" << endl;
  delete dummy_a;
}

int main() {
  Monster* mon = new MonsterA();

  delete mon;
  return 0;
}