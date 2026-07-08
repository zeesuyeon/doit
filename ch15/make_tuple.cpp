#include <iostream>
#include <tuple>

using namespace std;

const int monster_a_type = 0;
const int monster_b_type = 1;
const int monster_c_type = 2;

class Monster {
public:
 int GetMonsterType() { return monster_type; };

protected:
 int monster_type;

private:
 int location_x;
 int location_y;
};

class MonsterA : public Monster {
public:
 MonsterA() { monster_type = monster_a_type;
 }
};

class MonsterB : public Monster {
public:
 MonsterB() { monster_type = monster_b_type;
 }
};

class MonsterC : public Monster {
public:
 MonsterC() { monster_type = monster_c_type;
 }
};

tuple<int, string, int, int> GetMonsterStatus(Monster& monster_inst) {
  int monster_type = monster_inst.GetMonsterType();
  string monster_name;
  int hp(100), power(100);

  switch(monster_type) {
    case monster_a_type:
      monster_name = "A 몬스터";
      hp += 10;
      break;
    case monster_b_type:
      monster_name = "B 몬스터";
      power += 20;
      break;
    case monster_c_type:
      monster_name = "C 몬스터";
      hp -= 10;
      power += 100;
      break;
  }

  return make_tuple(monster_type, monster_name, hp, power);
}

void PrintOutTuple(tuple<int, string, int, int> monster_status) {
  cout << get<1>(monster_status) << "(" << get<0>(monster_status) << ") : hp("
       << get<2>(monster_status) << ") : power(" << get<3>(monster_status)
       << ")" << endl;
}

template<class tupleObj, std::size_t N>
struct PrintOutTupleSecond {
  static void Show(const tupleObj& t) {
    PrintOutTupleSecond<tupleObj, N - 1>::Show(t);
    std::cout << ", " << std::get<N - 1>(t);
  }
};

template<class tupleObj>
struct PrintOutTupleSecond<tupleObj, 1> {
  static void Show(const tupleObj& t) { std::cout << std::get<0>(t); }
};

int main() {
  MonsterA monster_a_inst;
  MonsterB monster_b_inst;

  tuple<int, string, int, int> monster_a_status =
      GetMonsterStatus(monster_a_inst);
  tuple<int, string, int, int> monster_a_status_copy(monster_a_status);
  tuple<int, string, int, int> monster_b_status_temp{monster_b_type,
                                                     "B 몬스터 암시", 100, 100};
  auto monster_b_status = GetMonsterStatus(monster_b_inst);

  PrintOutTuple(monster_a_status);
  PrintOutTuple(monster_a_status_copy);
  PrintOutTuple(monster_b_status_temp);

  swap(monster_b_status, monster_b_status_temp);
  cout << "튜플 내용 교환 후" << endl;
  PrintOutTuple(monster_b_status_temp);

  auto monster_status_all = tuple_cat(monster_a_status, monster_b_status);
  cout << "tuple_cat 호출 이후 : {";
  PrintOutTupleSecond<decltype(monster_status_all), tuple_size<decltype(monster_status_all)>::value>::Show(monster_status_all);
  cout << "}" << endl;
  return 0;
}