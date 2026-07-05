#include <iostream>

using namespace std;

class Character {
 public:
  Character() : hp(100), power(100) {};
  int get_hp() { return hp; };
  int get_power() { return power; };

 protected:
  int hp;
  int power;
};

class Player {
 public:
  Player() {};

 private:
  Character main_body;
};

class Monster {
 public:
  Monster() {};
  void get_damage(int _damage) {};
  virtual void attack(Player target_player) {
    cout << " 공격 : 데미지 - 10 hp" << endl;
  };
};

class Monster2ndGen : public Monster {
 public:
  virtual void attack(Player target_player) override {
    cout << " 새로운 공격 : 데미지 - 30 hp" << endl;
  };
};

class MonsterA {
 public:
  void attack(Player target_player) { main_role.attack(target_player); };

 private:
  Character main_body;
  Monster main_role;
};

class MonsterB {
 public:
  MonsterB(Character& ref_character, Monster& ref_monster)
      : main_body(ref_character), main_role(ref_monster) {};
  void attack(Player target_player) { main_role.attack(target_player); }

 private:
  Character& main_body;
  Monster& main_role;
};

int main() {
  Character character_obj;
  Monster monster_obj;
  Monster2ndGen monster_new_obj;

  Player player_1;

  MonsterA forest_monster;

  MonsterB tutorial_monster(character_obj, monster_obj);
  MonsterB urban_monster(character_obj, monster_new_obj);
  cout << "몬스터 A 공격" << endl;
  tutorial_monster.attack(player_1);

  cout << endl << "몬스터 B 공격" << endl;
  forest_monster.attack(player_1);
  urban_monster.attack(player_1);

  return 0;
}