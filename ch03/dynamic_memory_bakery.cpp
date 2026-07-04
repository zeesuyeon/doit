#include <iostream>
#include <string>

using namespace std;
int main() {
  int custom_num = 0;

  cout << "오늘 방문 손님: ";
  cin >> custom_num;

  string* bread = new string[custom_num];

  for (int i = 0; i < custom_num; i++){
    bread[i] = "빵_" + to_string(i);
  }

  cout << endl << "--생산된 빵" << endl;
  for (int i = 0; i < custom_num; i++){
    cout << *(bread + i) << endl;
  }

  delete[] bread;
  return 0;
}