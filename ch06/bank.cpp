#include <iostream>

using namespace std;

class Bank {
 public:
  Bank();
  void use_counter(int _in, int _out);

 private:
  int safe;
};

Bank::Bank() {
  safe = 1000;
  cout << "최초 금고: " << safe << endl;
  cout << endl;
}

void Bank::use_counter(int _in, int _out) {
  safe += _in;
  safe -= _out;

  cout << "입금: " << _in << endl;
  cout << "출금: " << _out << endl;
  cout << "금고: " << safe << endl;
  cout << endl;
}

int main() {
  Bank my_bank;

  my_bank.use_counter(0, 20);
  my_bank.use_counter(50, 0);
  my_bank.use_counter(100, 50);

  return 0;
}