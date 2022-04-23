#include <iostream>

#include "circular-linked-list.hpp"
#include "node.hpp"
using namespace std;

int main() {
    CircularLinkedList<int> cll;

    cll.InsertInOrder(1);

    CircularLinkedList<int> cc = cll;

    cout << cc << endl;

}
