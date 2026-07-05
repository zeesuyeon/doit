#include <array>
#include <iostream>

using namespace std;

class ManageDataStructure {
 public:
  ManageDataStructure();
  int get_current_index() { return current_index; };
  void set_current_index(int new_index);
  int get_array_value() { return data_queue[current_index]; };

private:
  int current_index;
  array<int, 10> data_queue;
};

ManageDataStructure::ManageDataStructure()
    : current_index(0), data_queue{0, 1, 2, 3, 4, 5, 6, 7, 8, 9} {}

void ManageDataStructure::set_current_index(int new_index) {
  if (new_index < 0 || new_index >= 10) {
    return;
  }
  current_index = new_index;
}

int main() {
  int data, index;
  ManageDataStructure data_structure;

  data_structure.set_current_index(-1);
  index = data_structure.get_current_index();
  data = data_structure.get_array_value();
  cout << "Data [" << index << "] : " << data << endl;
  return 0;
}