
#include <iostream>
using std::cout;
using std::endl;

#include <vector> // vector
#include <functional> // lambda functions
//#include <algorithm> // find_if

int main() {

  int n[3] = {1, 2, 3};
  for (int i = 0; i < 3; i++) cout << n[i];
  cout << endl;

  std::vector<int> values = {1, 5, 4, 2, 3};
  std::function<void(int)> lambda = [=](int x) { cout << "Value = " << x << endl;  };
  for (int value: values) lambda(value);

  // Filter like this...
  //auto it = std::find_if(values.begin(), values.end(), [](int value) { return value > 3; });
  //cout << *it << endl;

  return 0;
}
