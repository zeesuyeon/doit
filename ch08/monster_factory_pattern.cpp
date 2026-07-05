#include <iostream>
#include <list>

using namespace std;

const int forest_terrain = 0;
const int cyber_terrain = 1;
const int urban_terrain = 2;

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

  static Monster* create_monster(const int terrian_type);
  static void destroy_monster();
  static Monster* get_monster(const int terrian_type, int index);
  static int get_monster_count(const int terrian_type);

  static list<Monster*> mon_a_list;
  static list<Monster*> mon_b_list;
  static list<Monster*> mon_c_list;

  static int mon_a_count;
  static int mon_b_count;
  static int mon_c_count;
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

void MonsterA::find_route() {
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

void MonsterB::find_route() {
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

void MonsterC::find_route() {
  cout << "다익스트라 최단 경로 알고리즘" << endl;
}

void MonsterC::attack_special(Player target_player) {
  cout << "강력 뇌전 공격 : - 100 hp" << endl;
}

list<Monster*> Monster::mon_a_list = {};
list<Monster*> Monster::mon_b_list = {};
list<Monster*> Monster::mon_c_list = {};

int Monster::mon_a_count = 0;
int Monster::mon_b_count = 0;
int Monster::mon_c_count = 0;

int Monster::get_monster_count(const int terrian_type) {
  switch (terrian_type) {
    case forest_terrain:
      return mon_a_count;
    case cyber_terrain:
      return mon_b_count;
    case urban_terrain:
      return mon_c_count;
  }
  return 0;
}

Monster* Monster::get_monster(const int terrian_type, int index) {
  Monster* new_mon = nullptr;
  switch (terrian_type) {
    case forest_terrain: {
      auto item = mon_a_list.begin();
      advance(item, index);
      new_mon = *item;

    } break;

    case cyber_terrain: {
      auto item = mon_b_list.begin();
      advance(item, index);
      new_mon = *item;
    } break;
    case urban_terrain: {
      auto item = mon_c_list.begin();
      advance(item, index);
      new_mon = *item;
    } break;
  }
  return new_mon;
}

Monster *Monster::create_monster(const int terrian_type) {
  Monster* new_mon = nullptr;
  switch(terrian_type) {
    case forest_terrain:
      new_mon = new MonsterA();
      mon_a_list.push_back(new_mon);
      mon_a_count++;
      break;
    case cyber_terrain:
      new_mon = new MonsterB();
      mon_b_list.push_back(new_mon);
      mon_b_count++;
      break;
    case urban_terrain:
      new_mon = new MonsterC();
      mon_c_list.push_back(new_mon);
      mon_c_count++;
      break;
  }
  return new_mon;
}

void Monster::destroy_monster() {
  for (auto mon : mon_a_list) {
    delete mon;
  }

  for (auto mon : mon_b_list) {
    delete mon;
  }

  for (auto mon : mon_c_list) {
    delete mon;
  }
}

void monster_routine(Monster* mon, Player target_player) {
  mon->find_route();
  mon->attack_special(target_player);
}

void create_monster(const int terrian_type, int count) {
  for (int i = 0; i < count; i++) {
    Monster::create_monster(terrian_type);
  }
}

void attach_all(const int terrian_type) {
  int mon_count, i;
  Player target_player_dummy;

  mon_count = Monster::get_monster_count(terrian_type);
  for (int i = 0; i < mon_count; ++i) {
    monster_routine(Monster::get_monster(terrian_type, i), target_player_dummy);
  }
}

int main() {
  create_monster(forest_terrain, 5);
  create_monster(cyber_terrain, 7);
  create_monster(urban_terrain, 5);

  attach_all(forest_terrain);
  attach_all(cyber_terrain);
  attach_all(urban_terrain);

  Monster::destroy_monster();
  return 0;
}