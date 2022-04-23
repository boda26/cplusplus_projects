#include "illini_book.hpp"
#include <list>
#include <iostream>

using namespace std;

int main() {
  IlliniBook ib("example/persons.csv", "example/relations.csv");
  vector<int> steps =  ib.GetSteps(1,2);
  for (auto it = steps.begin(); it != steps.end(); ++it) {
    cout << *it << endl;
  }
}
