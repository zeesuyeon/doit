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
  Monster() {};
  void get_damage(int _damage) {};
  void attack(Player target_player) {};
  virtual void attack_special(Player target_player);
  virtual void attack_at_dawn() = 0;
};

void Monster::attack_special(Player target_player) {
  cout << "기본 공격 : 데미지 - 10 hp" << endl;
}

class MonsterA : public Monster, Character {
 public:
  virtual void attack_special(Player target_player) override;
  virtual void attack_at_dawn() override;
};

void MonsterA::attack_special(Player target_player) {
  cout << "인텡글 공격 : 데미지 - 15 hp" << endl;
}

void MonsterA::attack_at_dawn() {
  cout << "동쪽에서 기습!" << endl;
}

class MonsterB : public Monster, Character {
 public:
  virtual void attack_special(Player target_player) override;
  virtual void attack_at_dawn() override;
};

void MonsterB::attack_special(Player target_player) {
  cout << "가상 공격 : 데미지 - 0 hp" << endl;
}

void MonsterB::attack_at_dawn() {
  cout << "적진에 조용히 침투하여 방화!" << endl;
}

class MonsterC : public Monster, Character {
 public:
  MonsterC() : level(1), hp(100) {};
  virtual void attack_special(Player target_player) override;
  virtual void attack_at_dawn() override;
  MonsterC operator+(MonsterC& operand);
  void set_level(int level_value) { level = level_value; };
  void set_hp(int hp_value) { hp = hp_value; };
  int get_level() { return level; };
  int get_hp() { return hp; };

 private:
  int level;
  int hp;
};

void MonsterC::attack_special(Player target_player) {
  cout << "강력 뇌전 공격 : - 100 hp" << endl;
}

void MonsterC::attack_at_dawn() {
  cout << "남쪽에서 적진을 향해 대포 발사!" << endl;
}

MonsterC MonsterC::operator+(MonsterC& operand) {
  MonsterC result_monster;
  result_monster.set_level(level + operand.get_level());
  return result_monster;
}

int main() {
  list<Monster*> mon_list;

  MonsterA first_monster;
  mon_list.push_back(&first_monster);

  MonsterB second_monster;
  mon_list.push_back(&second_monster);

  MonsterC third_monster;
  mon_list.push_back(&third_monster);

  for (auto item : mon_list) {
    item->attack_at_dawn();
  }

  return 0;
}