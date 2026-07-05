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
  virtual void attack_special(Player target_player) override;
};

void MonsterC::attack_special(Player target_player) {
  cout << "강력 뇌전 공격 : - 100 hp" << endl;
}

int main() {
  Player player_1;

  MonsterA forest_monster;
  MonsterB tutorial_monster;
  MonsterC boss_monster;

  cout << "몬스터 총 공격" << endl;
  forest_monster.attack_special(player_1);
  tutorial_monster.attack(player_1);
  boss_monster.attack_special(player_1);

  return 0;
}