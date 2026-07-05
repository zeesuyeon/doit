#include <iostream>

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
};

void Monster::attack_special(Player target_player) {
  cout << "기본 공격 : 데미지 - 10 hp" << endl;
}

class MonsterA : public Monster, Character {
 public:
  virtual void attack_special(Player target_player) override;
};

void MonsterA::attack_special(Player target_player) {
  cout << "인텡글 공격 : 데미지 - 15 hp" << endl;
}

class MonsterB : public Monster, Character {
 public:
  virtual void attack_special(Player target_player) override;
};

void MonsterB::attack_special(Player target_player) {
  cout << "가상 공격 : 데미지 - 0 hp" << endl;
}

class MonsterC : public Monster, Character {
 public:
  MonsterC() : level(1), hp(100) {};
  virtual void attack_special(Player target_player) override;
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

MonsterC MonsterC::operator+(MonsterC &operand) {
  MonsterC result_monster;
  result_monster.set_level(level + operand.get_level());
  return result_monster;
}

int main() {
  MonsterC mon_c_1, mon_c_2;

  mon_c_2.set_level(2);
  MonsterC new_mon_c = mon_c_1 + mon_c_2;

  cout << "합체 전 몬스터 C #1 Level[" << mon_c_1.get_level()
       << "], 몬스터 C #2 Level[" << mon_c_2.get_level() << "]" << endl;

  cout << "합체 후 몬스터 C Level[" << new_mon_c.get_level() << "]" << endl;

  return 0;
}