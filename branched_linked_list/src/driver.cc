#include <iostream>

#include "branched-linked-list.hpp"

int main() {
  /* EXAMPLE INTERACTIONS WITH BLL */
  BLL* first = new BLL();
  first->PushBack('h');
  first->PushBack('i');
  //std::cout << 1 << std::endl;
  //std::cout << first->ToString() << std::endl; // hi
  //std::cout << first->Size() << std::endl; // 2

  // /////////////////////////////////////

  
  BLL* second = new BLL();
  second->PushBack('i');
  second->PushBack('!');
  second->PushBack('@');
  

  //std::cout << second->ToString() << std::endl; // i!@
  //std::cout << second->Size() << std::endl; // 3

  // /////////////////////////////////////
  
  //first->Head()->next_bll_ = second;
  //std::cout << first->ToString() << std::endl;
  //std::cout << first->Size() << std::endl;

  first->Join(0, second);

  //std::cout << first->ToString() << std::endl; // hii!@
  //std::cout << first->Size() << std::endl; // 5

  //std::cout << second->ToString() << std::endl; // i!@
  //std::cout << second->Size() << std::endl; // 3

  // /////////////////////////////////////

  //std::cout << 0 << std::endl;

  BLL* first_clone = new BLL(*first);
  //std::cout << 0 << std::endl;
  //*first_clone = *first;

  //std::cout << 0 << std::endl;

  std::cout << first_clone->ToString() << std::endl; // hii!@
  std::cout << first_clone->Size() << std::endl; // 5

  return 0;
}
