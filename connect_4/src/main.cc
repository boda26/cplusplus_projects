#include <iostream>

#include "board.hpp"

int main() {
  // Board b;
  Board b;
  InitBoard(b);
  BoardToStr(b);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  std::cout << BoardToStr(b) << std::endl;
  bool h = SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag);
  std::cout << h << std::endl;
}