// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}


TEST_CASE("board location", "[board_location]") {
  Board Student;
  InitBoard(Student);

  // bad cases
  bool b1 = BoardLocationInBounds(0, -1);
  bool b2 = BoardLocationInBounds(-1, 0);
  bool b3 = BoardLocationInBounds(-1, -1);
  bool b4 = BoardLocationInBounds(0, Board::kBoardWidth);
  bool b5 = BoardLocationInBounds(Board::kBoardHeight, 0);
  bool b6 = BoardLocationInBounds(Board::kBoardHeight, Board::kBoardWidth);
  REQUIRE(b1 == false);
  REQUIRE(b2 == false);
  REQUIRE(b3 == false);
  REQUIRE(b4 == false);
  REQUIRE(b5 == false);
  REQUIRE(b6 == false);
  // good cases
  bool b7 = BoardLocationInBounds(0, 0);
  bool b8 = BoardLocationInBounds(Board::kBoardHeight - 1, Board::kBoardWidth - 1);
  REQUIRE(b7 == true);
  REQUIRE(b8 == true);
}

TEST_CASE("drop", "[drop]") {
  Board Student;
  InitBoard(Student);
  bool b1 = false;
  bool b2 = false;
  bool b3 = false;
  try {
    DropDiskToBoard(Student, DiskType::kPlayer1, -1);
  } catch(const std::runtime_error& e) {
    b1 = true;
  }
  try {
    DropDiskToBoard(Student, DiskType::kPlayer1, Board::kBoardWidth);
  } catch(const std::runtime_error& e) {
    b2 = true;
  }
  try {
    DropDiskToBoard(Student, DiskType::kPlayer1, 0);
    DropDiskToBoard(Student, DiskType::kPlayer1, 0);
    DropDiskToBoard(Student, DiskType::kPlayer1, 0);
    DropDiskToBoard(Student, DiskType::kPlayer1, 0);
    DropDiskToBoard(Student, DiskType::kPlayer1, 0);
    DropDiskToBoard(Student, DiskType::kPlayer1, 0);
    DropDiskToBoard(Student, DiskType::kPlayer1, 0);
  } catch(const std::runtime_error& e) {
    b3 = true;
  }
  REQUIRE(b1 == true);
  REQUIRE(b2 == true);
  REQUIRE(b3 == true);
}

TEST_CASE("search", "[search]") {
  Board Student;
  InitBoard(Student);
  // horizontal
  DropDiskToBoard(Student, DiskType::kPlayer1, 0);
  DropDiskToBoard(Student, DiskType::kPlayer1, 1);
  DropDiskToBoard(Student, DiskType::kPlayer1, 2);
  bool b1 = SearchForWinner(Student, DiskType::kPlayer1, WinningDirection::kHorizontal);
  REQUIRE(b1 == false);

  InitBoard(Student);
  DropDiskToBoard(Student, DiskType::kPlayer1, 0);
  DropDiskToBoard(Student, DiskType::kPlayer1, 1);
  DropDiskToBoard(Student, DiskType::kPlayer1, 2);
  DropDiskToBoard(Student, DiskType::kPlayer2, 3);
  DropDiskToBoard(Student, DiskType::kPlayer1, 4);
  DropDiskToBoard(Student, DiskType::kPlayer1, 5);
  bool b2 = SearchForWinner(Student, DiskType::kPlayer1, WinningDirection::kHorizontal);
  REQUIRE(b2 == false);

  // vertical
  InitBoard(Student);
  DropDiskToBoard(Student, DiskType::kPlayer1, 0);
  DropDiskToBoard(Student, DiskType::kPlayer1, 0);
  DropDiskToBoard(Student, DiskType::kPlayer1, 0);
  bool b3 = SearchForWinner(Student, DiskType::kPlayer1, WinningDirection::kVertical);
  REQUIRE(b3 == false);

  InitBoard(Student);
  DropDiskToBoard(Student, DiskType::kPlayer1, 0);
  DropDiskToBoard(Student, DiskType::kPlayer1, 0);
  DropDiskToBoard(Student, DiskType::kPlayer1, 0);
  DropDiskToBoard(Student, DiskType::kPlayer2, 0);
  DropDiskToBoard(Student, DiskType::kPlayer1, 0);
  DropDiskToBoard(Student, DiskType::kPlayer1, 0);
  bool b4 = SearchForWinner(Student, DiskType::kPlayer1, WinningDirection::kVertical);
  REQUIRE(b4 == false);

  // right diagonal
  InitBoard(Student);
  DropDiskToBoard(Student, DiskType::kPlayer1, 0);
  DropDiskToBoard(Student, DiskType::kPlayer1, 1);
  DropDiskToBoard(Student, DiskType::kPlayer1, 1);
  DropDiskToBoard(Student, DiskType::kPlayer1, 2);
  DropDiskToBoard(Student, DiskType::kPlayer1, 2);
  DropDiskToBoard(Student, DiskType::kPlayer1, 2);
  bool b5 = SearchForWinner(Student, DiskType::kPlayer1, WinningDirection::kRightDiag);
  REQUIRE(b5 == false);

  InitBoard(Student);
  DropDiskToBoard(Student, DiskType::kPlayer1, 0);
  DropDiskToBoard(Student, DiskType::kPlayer1, 1);
  DropDiskToBoard(Student, DiskType::kPlayer1, 1);
  DropDiskToBoard(Student, DiskType::kPlayer1, 2);
  DropDiskToBoard(Student, DiskType::kPlayer1, 2);
  DropDiskToBoard(Student, DiskType::kPlayer1, 2);
  DropDiskToBoard(Student, DiskType::kPlayer2, 3);
  DropDiskToBoard(Student, DiskType::kPlayer2, 3);
  DropDiskToBoard(Student, DiskType::kPlayer2, 3);
  DropDiskToBoard(Student, DiskType::kPlayer2, 3);
  DropDiskToBoard(Student, DiskType::kPlayer1, 4);
  DropDiskToBoard(Student, DiskType::kPlayer1, 4);
  DropDiskToBoard(Student, DiskType::kPlayer1, 4);
  DropDiskToBoard(Student, DiskType::kPlayer1, 4);
  DropDiskToBoard(Student, DiskType::kPlayer1, 4);
  bool b6 = SearchForWinner(Student, DiskType::kPlayer1, WinningDirection::kRightDiag);
  REQUIRE(b6 == false);

  // left diagonal
  InitBoard(Student);
  DropDiskToBoard(Student, DiskType::kPlayer1, Board::kBoardWidth - 1);
  DropDiskToBoard(Student, DiskType::kPlayer1, Board::kBoardWidth - 2);
  DropDiskToBoard(Student, DiskType::kPlayer1, Board::kBoardWidth - 2);
  DropDiskToBoard(Student, DiskType::kPlayer1, Board::kBoardWidth - 3);
  DropDiskToBoard(Student, DiskType::kPlayer1, Board::kBoardWidth - 3);
  DropDiskToBoard(Student, DiskType::kPlayer1, Board::kBoardWidth - 3);
  bool b7 = SearchForWinner(Student, DiskType::kPlayer1, WinningDirection::kRightDiag);
  REQUIRE(b7 == false);

  InitBoard(Student);
  DropDiskToBoard(Student, DiskType::kPlayer1, Board::kBoardWidth - 1);
  DropDiskToBoard(Student, DiskType::kPlayer1, Board::kBoardWidth - 2);
  DropDiskToBoard(Student, DiskType::kPlayer1, Board::kBoardWidth - 2);
  DropDiskToBoard(Student, DiskType::kPlayer1, Board::kBoardWidth - 3);
  DropDiskToBoard(Student, DiskType::kPlayer1, Board::kBoardWidth - 3);
  DropDiskToBoard(Student, DiskType::kPlayer1, Board::kBoardWidth - 3);
  DropDiskToBoard(Student, DiskType::kPlayer2, Board::kBoardWidth - 4);
  DropDiskToBoard(Student, DiskType::kPlayer2, Board::kBoardWidth - 4);
  DropDiskToBoard(Student, DiskType::kPlayer2, Board::kBoardWidth - 4);
  DropDiskToBoard(Student, DiskType::kPlayer2, Board::kBoardWidth - 4);
  DropDiskToBoard(Student, DiskType::kPlayer1, Board::kBoardWidth - 5);
  DropDiskToBoard(Student, DiskType::kPlayer1, Board::kBoardWidth - 5);
  DropDiskToBoard(Student, DiskType::kPlayer1, Board::kBoardWidth - 5);
  DropDiskToBoard(Student, DiskType::kPlayer1, Board::kBoardWidth - 5);
  DropDiskToBoard(Student, DiskType::kPlayer1, Board::kBoardWidth - 5);
  bool b8 = SearchForWinner(Student, DiskType::kPlayer1, WinningDirection::kRightDiag);
  REQUIRE(b8 == false);
}

TEST_CASE("check", "[check]") {
  Board Student;
  InitBoard(Student);
  DropDiskToBoard(Student, DiskType::kPlayer1, 0);
  DropDiskToBoard(Student, DiskType::kPlayer2, 1);
  DropDiskToBoard(Student, DiskType::kPlayer1, 1);
  DropDiskToBoard(Student, DiskType::kPlayer2, 2);
  DropDiskToBoard(Student, DiskType::kPlayer2, 2);
  DropDiskToBoard(Student, DiskType::kPlayer1, 2);
  DropDiskToBoard(Student, DiskType::kPlayer2, 3);
  DropDiskToBoard(Student, DiskType::kPlayer2, 3);
  DropDiskToBoard(Student, DiskType::kPlayer2, 3);
  DropDiskToBoard(Student, DiskType::kPlayer1, 3);
  bool b = CheckForWinner(Student, DiskType::kPlayer1);
  REQUIRE(b == true);
}


/////////////////////////////////////////////////////////////////////////////////////////////