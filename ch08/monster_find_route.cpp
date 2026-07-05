#include <iostream>
#include <list>

using namespace std;

class Character {
 public:
  Character() : hp(100), power(100) {};

 protected:
  int hp;
  int power;
};

class Player : public Character {
 public:
  Player() {};
};

class Monster {
 public:
  Monster();
  virtual ~Monster();
  virtual void find_route() = 0;
  virtual void attack_special(Player target_player) = 0;
};

Monster::Monster() {
  cout << "Monster() 생성자 호출" << endl;
}

Monster::~Monster() {
  cout << "~Monster() 소멸자 호출" << endl;
}

class MonsterA : public Monster, Character {
 public:
  virtual void find_route() override;
  virtual void attack_special(Player target_player) override;
};

void MonsterA::find_route(){
  cout << "깊이 우선 탐색(DFS)" << endl;
}

void MonsterA::attack_special(Player target_player) {
  cout << "인텡글 공격 : 데미지 - 15 hp" << endl;
}

class MonsterB : public Monster, Character {
 public:
  virtual void find_route() override;
  virtual void attack_special(Player target_player) override;
};

void MonsterB::find_route(){
  cout << "너비 우선 탐색(BFS)" << endl;
}

void MonsterB::attack_special(Player target_player) {
  cout << "가상 공격 : 데미지 - 0 hp" << endl;
}

class MonsterC : public Monster, Character {
 public:
  virtual void find_route() override;
  virtual void attack_special(Player target_player) override;

};

void MonsterC::find_route(){
  cout << "다익스트라 최단 경로 알고리즘" << endl;
}

void MonsterC::attack_special(Player target_player) {
  cout << "강력 뇌전 공격 : - 100 hp" << endl;
}

void monster_routine(Monster *mon, Player target_player) {
  mon->find_route();
  mon->attack_special(target_player);
}

int main() {
  list<Monster*> mon_list;

  MonsterA first_monster;
  MonsterB second_monster;
  MonsterC third_monster;
  Player target_player;

  mon_list.push_back(&first_monster);
  mon_list.push_back(&second_monster);
  mon_list.push_back(&third_monster);


  for (auto item : mon_list) {
    monster_routine(item, target_player);
  }

  return 0;
}