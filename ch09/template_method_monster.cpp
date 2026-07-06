#include <iostream>
#include <list>
#include <random>
#include <cmath>

using namespace std;

const int forest_terrain = 0;
const int cyber_terrain = 1;
const int urban_terrain = 2;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> dis(0, 99);


class Character {
 public:
  Character() : hp(100), power(100), location_x(0), location_y(0) {};
  int GetHp() { return hp; };
  int GetPower() { return power; };
  int GetLocation(bool x) { return x ? location_x : location_y; };
  void SetLocation(int x, int y) { location_x = x; location_y = y; };

 protected:
  int hp;
  int power;
  int location_x;
  int location_y;
};

class Player : public Character {
 public:
  Player() {};
};

class Monster {
 public:
  Monster(){};
  virtual ~Monster(){};

  virtual void FindRoute(Player &target_player) = 0;
  virtual bool AttachTarget(Player* target_player) = 0;
  virtual void CheckTarget(Player& target_player) = 0;
  virtual void AttackSpecial(Player& target_player) = 0;
  virtual void SetLocation(int x, int y) { monster_body.SetLocation(x, y); };

  protected:
   int CaculateDistance(Player& target_player);
   Character* target_player;

  private:
   Character monster_body;
};

int Monster::CaculateDistance(Player& target_player) {
  return (int)sqrt(pow(target_player.GetLocation(true) - monster_body.GetLocation(true), 2) +
    pow(target_player.GetLocation(false) - monster_body.GetLocation(false), 2));
}

class MonsterFactory {
public:
  static void CreateMonster(const int terrian_type, int count);
  static void DestroyMonster();
  static Monster* GetMonster(int index);
  static int GetMonsterCount();
  static void InitializeMonster();

 private:
  static Monster* CreateMonster(const int terrian_type);
  static list<Monster*> mon_list;
  static int mon_count;
};

list<Monster*> MonsterFactory::mon_list = {};
int MonsterFactory::mon_count = 0;

class MonsterA : public Monster {
 public:
  virtual void FindRoute(Player& target_player) override;
  virtual bool AttachTarget(Player* target_player) override;
  virtual void CheckTarget(Player& target_player) override;
  virtual void AttackSpecial(Player& target_player) override;
};

void MonsterA::FindRoute(Player& target_player) {
  cout << "타깃 찾아 가기 - 최단 거리 우선" << endl;
}

void MonsterA::AttackSpecial(Player& target_player) {
  cout << "인텡글 공격 : 데미지 - 15 hp" << endl;
}

bool MonsterA::AttachTarget(Player* target_player) {
  if (CaculateDistance(*target_player) < 30) {
    this->target_player = target_player;
    cout << "뒤따라 가면서 플레이어 쫓아 가기" << endl;
    return true;
  }

  return false;
}


void MonsterA::CheckTarget(Player& target_player) {
  if (target_player.GetHp() < 40) {
    AttackSpecial(target_player);
    return;
  }
}

class MonsterB : public Monster {
 public:
  virtual void FindRoute(Player& target_player) override;
  virtual bool AttachTarget(Player* target_player) override;
  virtual void CheckTarget(Player& target_player) override;
  virtual void AttackSpecial(Player& target_player) override;
};

void MonsterB::FindRoute(Player& target_player) {
  cout << "타깃 찾아 가기 - 최소 시간 우선" << endl;
}

void MonsterB::AttackSpecial(Player& target_player) {
  cout << "가상 공격 : 데미지 - 0 hp" << endl;
}

bool MonsterB::AttachTarget(Player* target_player) {
  if (CaculateDistance(*target_player) > 30) {
    this->target_player = target_player;
    cout << "위치 추적을 통해서 찾아 가기" << endl;
    return true;
  }

  return false;
}

void MonsterB::CheckTarget(Player& target_player) {
  if (target_player.GetHp() < 10) {
    AttackSpecial(target_player);
    return;
  }
}

class MonsterC : public Monster {
 public:
  virtual void FindRoute(Player& target_player) override;
  virtual bool AttachTarget(Player* target_player) override;
  virtual void CheckTarget(Player& target_player) override;
  virtual void AttackSpecial(Player& target_player) override;
};

void MonsterC::FindRoute(Player& target_player) {
  cout << "타깃 찾아 가기 - 타깃 시선에 보이지 않도록" << endl;
}

void MonsterC::AttackSpecial(Player& target_player) {
  cout << "강력 뇌전 공격 : - 100 hp" << endl;
}

bool MonsterC::AttachTarget(Player* target_player) {
  this->target_player = target_player;
  cout << "눈에 띄면 무조건 따라감" << endl;
  return true;
}

void MonsterC::CheckTarget(Player& target_player) {
  AttackSpecial(target_player);
}


int MonsterFactory::GetMonsterCount() {
  return mon_count;
}

Monster* MonsterFactory::GetMonster( int index) {
  Monster* new_mon = nullptr;
  auto item = mon_list.begin();
  advance(item, index);
  new_mon = *item;

  return new_mon;
}

void MonsterFactory::InitializeMonster() {
  CreateMonster(forest_terrain, 2);
  CreateMonster(cyber_terrain, 3);
  CreateMonster(urban_terrain, 1);
}

Monster *MonsterFactory::CreateMonster(const int terrian_type) {
  Monster* new_mon = nullptr;
  switch(terrian_type) {
    case forest_terrain:
      new_mon = new MonsterA();
      break;
    case cyber_terrain:
      new_mon = new MonsterB();
      break;
    case urban_terrain:
      new_mon = new MonsterC();
      break;
  }
  mon_list.push_back(new_mon);
  mon_count++;
  return new_mon;
}

void MonsterFactory::DestroyMonster() {
  for (auto mon : mon_list) {
    delete mon;
  }
}

void MonsterFactory::CreateMonster(const int terrian_type, int count) {
  Monster* mon = nullptr;

  for (int i = 0; i < count; i++) {
    mon = MonsterFactory::CreateMonster(terrian_type);
    mon->SetLocation(dis(gen), dis(gen));
  }
}

void monster_routine(Monster* mon, Player target_player) {
  mon->AttachTarget(&target_player);
  mon->FindRoute(target_player);
  mon->AttackSpecial(target_player);
}

int main() {
  int mon_count, i;
  Player target_player_dummy;

  target_player_dummy.SetLocation(dis(gen), dis(gen));
  MonsterFactory::InitializeMonster();

  mon_count = MonsterFactory::GetMonsterCount();
  for (int i = 0; i < mon_count; ++i) {
    cout << endl;
    cout << endl;
    monster_routine(MonsterFactory::GetMonster(i), target_player_dummy);
  }

  MonsterFactory::DestroyMonster();
  return 0;
}