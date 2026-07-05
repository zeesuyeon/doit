#include <iostream>

using namespace std;

class Bank {
 public:
  Bank(string name) : bank_name(name) { safe = 0; };
  ~Bank() {};
  int get_safe() { return safe; };
  string get_bank_name() { return bank_name; };
  void reset_account();
  void use_counter(int _in, int _out);
  void transfer_account(int safe);
  Bank& deposit_interest(int interest);
  Bank& withdraw_utility(int utility);
  Bank& withdraw_tax(int tax);

 private:
  int safe;
  string bank_name;
};

void Bank::use_counter(int _in, int _out) {
  safe += _in;
  safe -= _out;

  cout << bank_name << " 처리 - 입금: " << _in << ", 출금: " << _out << endl;
}

void Bank::reset_account() {
  safe = 0;
  cout << bank_name << " 계좌가 초기화 되었습니다." << endl;
}

void Bank::transfer_account(int safe) {
  this->safe = safe;
  cout << bank_name << "로 계좌 이동: " << safe << endl;
}

Bank& Bank::deposit_interest(int interest) {
  safe += interest;
  cout << bank_name << " 이자 지급: " << interest << endl;
  return *this;
}

Bank& Bank::withdraw_utility(int uitlity) {
  safe -= uitlity;
  cout << bank_name << " 공과금 납부: " << uitlity << endl;
  return *this;
}

Bank& Bank::withdraw_tax(int tax) {
  safe -= tax;
  cout << bank_name << " 세금 납부: " << tax << endl;
  return *this;
}

int main() {
  Bank rich_bank("부유한 은행"), global_bank("세계적 은행");

  rich_bank.use_counter(50, 10);
  cout << endl;
  global_bank.transfer_account(rich_bank.get_safe());
  rich_bank.reset_account();
  cout << endl;
  global_bank.deposit_interest(10).withdraw_utility(1).withdraw_tax(2);
  cout << endl;
  cout << global_bank.get_bank_name() << "잔액: " << global_bank.get_safe()
       << endl;
  return 0;
}