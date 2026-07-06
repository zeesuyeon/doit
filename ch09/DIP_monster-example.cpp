#include <iostream>
#include <list>
#include <random>

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> dis(0, 99);
uniform_int_distribution<int> select(0, 2);

const int forest_terrain_type = 0;
const int cyber_terrain_type = 1;
const int urban_terrain_type = 2;

const int monster_a_type = 0;
const int monster_b_type = 1;
const int monster_c_type = 2;

class IRoute {
 public:
  virtual void FindRoute(int x, int y) = 0;
  virtual void SetLocation(int x, int y) = 0;
  virtual int GetLocation(bool x) = 0;
};

class IAttack {
 public:
  virtual bool AttachTarget(void* target_player) = 0;
  virtual void CheckTarget(void* target_player) = 0;
  virtual void AttackSpecial(void* target_player) = 0;
};

class IWeapon {
 public:
  virtual void ReloadBullet() = 0;
  virtual bool IsBulletEmpty() = 0;
  virtual void ShootWeapon(void* target_player) = 0;
};

class IRidingObject {
 public:
  virtual int CheckEnergy() = 0;
  virtual void SetDestination(int x, int y) = 0;
  virtual void RunToDestination() = 0;
};

class Character {
 public:
  Character() : hp(100), power(100) {};
  int GetHp() { return hp; };
  int GetPower() { return power; };

 protected:
  int hp;
  int power;
};

class Monster : public IRoute, public IAttack {
 public:
  int GetMonsterType() { return monster_type; };
  virtual void SetLocation(int x, int y) override {
    location_x = x;
    location_y = y;
  };
  virtual int GetLocation(bool x) override {
    return x ? location_x : location_y;
  };

 protected:
  int CalculateDistance(int x, int y);
  void DepenceStrikeBack(void* target_player);
  Character* target_player = nullptr;
  int monster_type;
  Character MonsterBody;

 private:
  int location_x;
  int location_y;
};

class MonsterA : public Monster {
 public:
  MonsterA() { monster_type = monster_a_type; };

  virtual void FindRoute(int x, int y) override;
  virtual bool AttachTarget(void* target_player) override;
  virtual void CheckTarget(void* target_player) override;
  virtual void AttackSpecial(void* target_player) override;
};

class MonsterB : public Monster {
 public:
  MonsterB() { monster_type = monster_b_type; };

  virtual void FindRoute(int x, int y) override;
  virtual bool AttachTarget(void* target_player) override;
  virtual void CheckTarget(void* target_player) override;
  virtual void AttackSpecial(void* target_player) override;
};

class MonsterC : public Monster {
 public:
  MonsterC() { monster_type = monster_b_type; };

  virtual void FindRoute(int x, int y) override;
  virtual bool AttachTarget(void* target_player) override;
  virtual void CheckTarget(void* target_player) override;
  virtual void AttackSpecial(void* target_player) override;
};

class NpcObject : public IRoute {
 public:
  virtual void FindRoute(int x, int y) override;
  virtual void SetLocation(int x, int y) override;
  virtual int GetLocation(bool x) override;

 private:
  int location_x;
  int location_y;
};

class CharacterFactory {
 public:
  static void CreateMonster(const int Terrain_type, int count);
  static void DestroyMonster();
  static void CreateTerrain();
  static void DestroyTerrain();
  static void CreateNpc();
  static void DestroyNpc();
  static Monster* GetMonster(int index);
  static int GetMonsterCount();
  static void InitializeMonster();

 private:
  static Monster* CreateMonster(const int Terrain_type, void* terrai_inst);
  static list<Monster*> mon_list;
  static list<NpcObject*> npc_list;
  static int mon_count;
  static void* terrain_inst[3];
};

class Player : public Character, public IRoute {
 public:
  virtual void FindRoute(int x, int y) override;
  virtual void SetLocation(int x, int y) override;
  virtual int GetLocation(bool x) override;
  void SetWeapon(IWeapon* new_weapon) { weapon = new_weapon; };
  void SetRidingObject(IRidingObject* new_riding_object) {
    riding_object = new_riding_object;
  };
  void ReleaseWeapon() { weapon = nullptr; };
  void ReleaseRidingObject() { riding_object = nullptr; };
  void* GetWeapon() { return weapon; };
  void* GetRidingObject() { return riding_object; };

 private:
  int location_x;
  int location_y;
  IWeapon* weapon = nullptr;
  IRidingObject* riding_object = nullptr;
};

class Car : public IRidingObject {
 public:
  virtual int CheckEnergy() override;
  virtual void SetDestination(int x, int y) override;
  virtual void RunToDestination() override;
};

class Horse : public IRidingObject {
 public:
  virtual int CheckEnergy() override;
  virtual void SetDestination(int x, int y) override;
  virtual void RunToDestination() override;
};

class MotorCycle : public IRidingObject {
 public:
  virtual int CheckEnergy() override;
  virtual void SetDestination(int x, int y) override;
  virtual void RunToDestination() override;
};

class Terrain {
 public:
  virtual void AllocateMonster(Monster* mon) = 0;
  virtual void BoostMonster(Monster* mon) = 0;
  void SetStartLocation(int x, int y) {
    start_location_x = x;
    start_location_y = y;
  };
  void SetEndLocation(int x, int y) {
    end_location_x = x;
    end_location_y = y;
  };

 protected:
  int terrain_type;
  void UpdateMonsterList(Monster* mon);

 private:
  int start_location_x;
  int start_location_y;
  int end_location_x;
  int end_location_y;
  list<Monster*> mon_list;
};

class ForestTerrain : public Terrain {
 public:
  ForestTerrain() { terrain_type = forest_terrain_type; };
  virtual void AllocateMonster(Monster* mon) override;
  virtual void BoostMonster(Monster* mon) override;
};

class CyberTerrain : public Terrain {
 public:
  CyberTerrain() { terrain_type = cyber_terrain_type; };
  virtual void AllocateMonster(Monster* mon) override;
  virtual void BoostMonster(Monster* mon) override;
};

class UrbanTerrain : public Terrain {
 public:
  UrbanTerrain() { terrain_type = urban_terrain_type; };
  virtual void AllocateMonster(Monster* mon) override;
  virtual void BoostMonster(Monster* mon) override;
};

class Gun : public IWeapon {
 public:
  virtual void ReloadBullet() override;
  virtual bool IsBulletEmpty() override;
  virtual void ShootWeapon(void* target_player) override;
};

class MachineGun : public IWeapon {
 public:
  virtual void ReloadBullet() override;
  virtual bool IsBulletEmpty() override;
  virtual void ShootWeapon(void* target_player) override;
};

class Arrow : public IWeapon {
 public:
  virtual void ReloadBullet() override;
  virtual bool IsBulletEmpty() override;
  virtual void ShootWeapon(void* target_player) override;
};

list<Monster*> CharacterFactory::mon_list = {};
list<NpcObject*> CharacterFactory::npc_list = {};
int CharacterFactory::mon_count = 0;
void* CharacterFactory::terrain_inst[] = {
    nullptr,
};

int Monster::CalculateDistance(int x, int y ) {
 return (int)sqrt(pow(x - GetLocation(true), 2) + pow(y - GetLocation(false), 2));
}

void Monster::DepenceStrikeBack(void* target_player) {
  Player* target_player_inst = (Player*)target_player;
  IWeapon* weapon = (IWeapon*)target_player_inst->GetWeapon();
  IRidingObject* riding_object = (IRidingObject*)target_player_inst->GetRidingObject();
  if (nullptr == weapon) {
    return;
  }

  if (weapon->IsBulletEmpty()) {
    weapon->ReloadBullet();
  }
  weapon->ShootWeapon(this);

  if (riding_object->CheckEnergy() > 10) {
    riding_object->SetDestination(GetLocation(true) + 30, GetLocation(false) + 30);
    riding_object->RunToDestination();
  }
}

void MonsterA::AttackSpecial(void* target_player) {
  cout << "인텡글 공격 : 데미지 - 15 hp" << endl;
  DepenceStrikeBack(target_player);
}

void MonsterA::FindRoute(int x, int y) {
  cout << "타겟 찾아 가기 - 최단 거리 우선" << endl;
}

bool MonsterA::AttachTarget(void* target_player) {
  Player* target = (Player*)target_player;
  if (CalculateDistance(target->GetLocation(true), target->GetLocation(false)) < 30) {
    this->target_player = (Character*)target_player;
    cout << "뒤따라 가면서 플레이어 쫓아 가기" << endl;
    return true;
  }

  return false;
}

void MonsterA::CheckTarget(void* target_player) {
  Player* target = (Player*)target_player;
  if (target->GetHp() < 40) {
    AttackSpecial(target_player);
    return;
  }
}

void MonsterB::AttackSpecial(void* target_player) {
  cout << "가상 공격 : 데미지 - 0 hp" << endl;
  DepenceStrikeBack(target_player);
}

void MonsterB::FindRoute(int x, int y) {
  cout << "타겟 찾아 가기 - 최소 시간 우선" << endl;
}

bool MonsterB::AttachTarget(void* target_player) {
  Player* target = (Player*)target_player;
  if (CalculateDistance(target->GetLocation(true), target->GetLocation(false)) > 30) {
    this->target_player = (Character*)target_player;
    cout << "위치 추적을 통해서 찾아 가기" << endl;
    return true;
  }

  return false;
}

void MonsterB::CheckTarget(void* target_player) {
  Player* target = (Player*)target_player;
  if (target->GetHp() < 10) {
    AttackSpecial(target_player);
    return;
  }
}

void MonsterC::AttackSpecial(void* target_player) {
  cout << "강력 뇌전 공격 : 데미지 - 100 hp" << endl;
  DepenceStrikeBack(target_player);
}

void MonsterC::FindRoute(int x, int y) {
  cout << "타겟 찾아 가기 - 타겟 시선에 보이지 않도록" << endl;
}

bool MonsterC::AttachTarget(void* target_player) {
  this->target_player = (Character*)target_player;
  cout << "눈에 띄면 무조건 따라감" << endl;
  return true;
}

void MonsterC::CheckTarget(void* target_player) {
  AttackSpecial(target_player);
}

int CharacterFactory::GetMonsterCount() {
  return mon_count;
}

Monster* CharacterFactory::GetMonster(int index) {
  Monster* new_mon = nullptr;
  auto item = mon_list.begin();
  advance(item, index);
  new_mon = *item;

  return new_mon;
}

void CharacterFactory::InitializeMonster() {
  CreateMonster(forest_terrain_type, 2);
  CreateMonster(cyber_terrain_type, 3);
  CreateMonster(urban_terrain_type, 1);
}

void CharacterFactory::CreateTerrain() {
  terrain_inst[0] = new ForestTerrain();
  terrain_inst[1] = new CyberTerrain();
  terrain_inst[2] = new UrbanTerrain();

  for (auto object : terrain_inst) {
    Terrain* terrain_object = (Terrain*)object;
    terrain_object->SetStartLocation(dis(gen), dis(gen));
    terrain_object->SetEndLocation(dis(gen), dis(gen));
  }
}

void CharacterFactory::DestroyTerrain() {
  for (auto inst : terrain_inst) {
    delete inst;
  }
}

void CharacterFactory::CreateNpc() {
  for (int i = 0; i < 10; ++i) {
    NpcObject* npc = new NpcObject();
    npc_list.push_back(npc);
  }
}
void CharacterFactory::DestroyNpc() {
}

Monster* CharacterFactory::CreateMonster(const int terrain_type, void* terrain_inst) {
  Monster* new_mon = nullptr;
  Terrain* terrain_object = (Terrain*)terrain_inst;
  switch (terrain_type) {
  case forest_terrain_type:
    new_mon = new MonsterA();
    break;
  case cyber_terrain_type:
    new_mon = new MonsterB();
    break;
  case urban_terrain_type:
    new_mon = new MonsterC();
    break;
  }

  terrain_object->AllocateMonster(new_mon);
  terrain_object->BoostMonster(new_mon);
  mon_list.push_back(new_mon);
  mon_count++;
  return new_mon;
}

void CharacterFactory::DestroyMonster() {
  for (auto mon : mon_list) {
    delete mon;
  }
}

void CharacterFactory::CreateMonster(const int terrain_type, int count) {
  Monster* mon = nullptr;

  for (int i = 0; i < count; ++i) {
    mon = CharacterFactory::CreateMonster(terrain_type, terrain_inst[select(gen)]);
    mon->SetLocation(dis(gen), dis(gen));
  }
}

void Player::FindRoute(int x, int y) {
}

void Player::SetLocation(int x, int y) {
  location_x = x;
  location_y = y;
}

int Player::GetLocation(bool x) {
  if (x) {
    return location_x;
  }

  return location_y;
}

void NpcObject::FindRoute(int x, int y) {
  cout << "정해진 구역에서만 돌아 다니기." << endl;
}

void NpcObject::SetLocation(int x, int y) {
  location_x = x;
  location_y = y;
}

int NpcObject::GetLocation(bool x) {
  if (x) {
    return location_x;
  }

  return location_y;
}

int Car::CheckEnergy() {
  cout << "연료 체크" << endl;
  return 30;
}

void Car::SetDestination(int x, int y) {
}

void Car::RunToDestination() {
  cout << "부르르르릉" << endl;
}

int Horse::CheckEnergy() {
  cout << "체력 체크" << endl;
  return 30;
}

void Horse::SetDestination(int x, int y) {
}

void Horse::RunToDestination() {
  cout << "다그닥 다그닥" << endl;
}

int MotorCycle::CheckEnergy() {
  cout << "연료 체크" << endl;
  return 30;
}

void MotorCycle::SetDestination(int x, int y) {
}

void MotorCycle::RunToDestination() {
  cout << "부다다다다" << endl;
}

void ForestTerrain::AllocateMonster(Monster* mon) {
  if (monster_a_type == mon->GetMonsterType()) {
    UpdateMonsterList(mon);
    cout << "Monster A를 숲에 배치 합니다." << endl;
  }
}

void ForestTerrain::BoostMonster(Monster* mon) {
  if (monster_a_type == mon->GetMonsterType()) {
    cout << "몬스터A가 숲에서는 힘이 더 강해 집니다." << endl;
  }
}

void CyberTerrain::AllocateMonster(Monster* mon) {
  UpdateMonsterList(mon);
  cout << "모든 종류의 Monster를 사이버 공간에 배치 합니다." << endl;
}

void CyberTerrain::BoostMonster(Monster* mon) {
  cout << "모든 몬스터가 사이버 공간에서는 속도가 빨라 집니다." << endl;
}

void UrbanTerrain::AllocateMonster(Monster* mon) {
  if (monster_a_type != mon->GetMonsterType()) {
    UpdateMonsterList(mon);
    cout << "Monster B, C를 도심에 배치 합니다." << endl;
  }
}

void UrbanTerrain::BoostMonster(Monster* mon) {
  if (monster_c_type == mon->GetMonsterType()) {
    UpdateMonsterList(mon);
    cout << "Monster C는 도심에 힘이 강해 집니다." << endl;
  }
}

void Terrain::UpdateMonsterList(Monster* mon) {
  mon_list.push_back(mon);
}

void Gun::ReloadBullet() {
  cout << "탄창 교체" << endl;
}

bool Gun::IsBulletEmpty() {
  cout << "탄창에 남은 총알이 있는가?" << endl;
  return true; // 예제에서는 임의로 비었다고 가정함
}

void Gun::ShootWeapon(void* target_plaery) {
  cout << "\"탕\"" << endl;
}

void MachineGun::ReloadBullet() {
  cout << "대형 탄창 교체" << endl;
}

bool MachineGun::IsBulletEmpty() {
  cout << "탄창에 남은 총알이 있는가?" << endl;
  return true; // 예제에서는 임의로 비었다고 가정함
}

void MachineGun::ShootWeapon(void* target_plaery) {
  cout << "\"두두두두두두\"" << endl;
}

void Arrow::ReloadBullet() {
  cout << "화살통 채우기" << endl;
}

bool Arrow::IsBulletEmpty() {
  cout << "화살통이 비였는가?" << endl;
  return true; // 예제에서는 임의로 비었다고 가정함
}

void Arrow::ShootWeapon(void* target_plaery) {
  cout << "피이이잉" << endl;
}

/************* 전역 함수 영역 *************/
void MonsterRoute(Monster* mon, Player target_player) {
  mon->AttachTarget(&target_player);
  mon->FindRoute(target_player.GetLocation(true), target_player.GetLocation(false));
  mon->CheckTarget(&target_player);
}

int main() {
  int mon_count, i;
  Player target_player;
  Car riding_car;
  MachineGun m_gun;

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> dis(0, 99);

  target_player.SetRidingObject(&riding_car);
  target_player.SetWeapon(&m_gun);
  target_player.SetLocation(dis(gen), dis(gen));

  CharacterFactory::CreateTerrain();
  CharacterFactory::InitializeMonster();

  mon_count = CharacterFactory::GetMonsterCount();
  for (i = 0; i < mon_count; ++i) {
    cout << endl;
    MonsterRoute(CharacterFactory::GetMonster(i), target_player);
  }

  CharacterFactory::DestroyMonster();
  CharacterFactory::DestroyTerrain();

  return 0;
}