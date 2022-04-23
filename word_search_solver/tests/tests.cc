// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>
#include <string>
#include <vector>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("example 1", "example1") {
    std::vector<std::vector<char>> puzzle{ 
        {'d', 'e', 'a', 'o', 'u'},
        {'h', 'e', 'l', 'l', 'o'},
        {'c', 'a', 'l', 'o', 'm'},
        {'a', 'e', 't', 'a', 'u'},
        {'t', 'e', 't', 'o', 'u'}
    };
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("hello");
    REQUIRE(result.word == "hello");
    vector<CharPositions> vec;
    CharPositions cp0 = {'h', 1, 0};
    CharPositions cp1 = {'e', 1, 1};
    CharPositions cp2 = {'l', 1, 2};
    CharPositions cp3 = {'l', 1, 3};
    CharPositions cp4 = {'o', 1, 4};
    vec.push_back(cp0);
    vec.push_back(cp1);
    vec.push_back(cp2);
    vec.push_back(cp3);
    vec.push_back(cp4);
    for (unsigned i = 0; i < result.char_positions.size(); i++) {
        REQUIRE(result.char_positions[i].character == vec[i].character);
        REQUIRE(result.char_positions[i].row == vec[i].row);
        REQUIRE(result.char_positions[i].col == vec[i].col);
    }
}

TEST_CASE("example 2", "example2") {
    std::vector<std::vector<char>> puzzle{ 
        {'d', 'e', 'a', 'o', 'u'},
        {'h', 'e', 'l', 'l', 'o'},
        {'c', 'a', 'l', 'o', 'm'},
        {'a', 'e', 't', 'a', 'u'},
        {'t', 'e', 't', 'o', 'u'}
    };
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("hat");
    REQUIRE(result.word == "hat");
    vector<CharPositions> vec;
    CharPositions cp0 = {'h', 1, 0};
    CharPositions cp1 = {'a', 2, 1};
    CharPositions cp2 = {'t', 3, 2};
    vec.push_back(cp0);
    vec.push_back(cp1);
    vec.push_back(cp2);
    for (unsigned i = 0; i < result.char_positions.size(); i++) {
        REQUIRE(result.char_positions[i].character == vec[i].character);
        REQUIRE(result.char_positions[i].row == vec[i].row);
        REQUIRE(result.char_positions[i].col == vec[i].col);
    }
}

TEST_CASE("example 3", "example3") {
    std::vector<std::vector<char>> puzzle{ 
        {'d', 'e', 'a', 'o', 'u'},
        {'h', 'e', 'l', 'l', 'o'},
        {'c', 'a', 'l', 'o', 'm'},
        {'a', 'e', 't', 'a', 'u'},
        {'t', 'e', 't', 'o', 'u'}
    };
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("mat");
    REQUIRE(result.word == "mat");
    vector<CharPositions> vec;
    CharPositions cp0 = {'m', 2, 4};
    CharPositions cp1 = {'a', 3, 3};
    CharPositions cp2 = {'t', 4, 2};
    vec.push_back(cp0);
    vec.push_back(cp1);
    vec.push_back(cp2);
    for (unsigned i = 0; i < result.char_positions.size(); i++) {
        REQUIRE(result.char_positions[i].character == vec[i].character);
        REQUIRE(result.char_positions[i].row == vec[i].row);
        REQUIRE(result.char_positions[i].col == vec[i].col);
    }
}

TEST_CASE("example 4", "example4") {
    std::vector<std::vector<char>> puzzle{ 
        {'d', 'e', 'a', 'o', 'u'},
        {'h', 'e', 'l', 'l', 'o'},
        {'c', 'a', 'l', 'o', 'm'},
        {'a', 'e', 't', 'a', 'u'},
        {'t', 'e', 't', 'o', 'u'}
    };
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("cat");
    REQUIRE(result.word == "cat");
    vector<CharPositions> vec;
    CharPositions cp0 = {'c', 2, 0};
    CharPositions cp1 = {'a', 3, 0};
    CharPositions cp2 = {'t', 4, 0};
    vec.push_back(cp0);
    vec.push_back(cp1);
    vec.push_back(cp2);
    for (unsigned i = 0; i < result.char_positions.size(); i++) {
        REQUIRE(result.char_positions[i].character == vec[i].character);
        REQUIRE(result.char_positions[i].row == vec[i].row);
        REQUIRE(result.char_positions[i].col == vec[i].col);
    }
}

TEST_CASE("reverse", "reverse") {
    std::vector<std::vector<char>> puzzle{ 
        {'a', 'e', 'a', 'o', 'u'},
        {'o', 'l', 'l', 'e', 'h'},
        {'c', 'a', 'l', 'o', 'm'},
        {'a', 'e', 't', 'a', 'u'},
        {'t', 'e', 't', 'o', 'u'}
    };
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("hello", CheckDirection::kHorizontal);
    REQUIRE(result.word != "hello");

    std::vector<std::vector<char>> puzzle2{ 
        {'a', 'o', 'a', 'o', 'u'},
        {'p', 'l', 'l', 'j', 'h'},
        {'c', 'l', 'l', 'o', 'm'},
        {'a', 'e', 't', 'a', 'u'},
        {'t', 'h', 't', 'o', 'u'}
    };
    WordSearchSolver wss2(puzzle2);
    WordLocation result2 = wss2.FindWord("hello", CheckDirection::kVertical);
    REQUIRE(result2.word != "hello");

    std::vector<std::vector<char>> puzzle3{ 
        {'o', 'e', 'a', 'o', 'u'},
        {'o', 'l', 'm', 'e', 'h'},
        {'c', 'a', 'l', 'o', 'm'},
        {'a', 'e', 't', 'e', 'u'},
        {'t', 'e', 't', 'o', 'h'}
    };
    WordSearchSolver wss3(puzzle3);
    WordLocation result3 = wss3.FindWord("hello", CheckDirection::kRightDiag);
    REQUIRE(result3.word != "hello");

    std::vector<std::vector<char>> puzzle4{ 
        {'a', 'e', 'a', 'o', 'o'},
        {'o', 'l', 'l', 'l', 'h'},
        {'c', 'a', 'l', 'o', 'm'},
        {'a', 'e', 't', 'a', 'u'},
        {'h', 'e', 't', 'o', 'u'}
    };
    WordSearchSolver wss4(puzzle4);
    WordLocation result4 = wss4.FindWord("hello");
    REQUIRE(result4.word != "hello");

}

TEST_CASE("diff row", "diff row") {
    std::vector<std::vector<char>> puzzle{ 
        {'a', 'l', 'a', 'o', 'l'},
        {'o', 'l', 'h', 'e', 'l'},
        {'l', 'o', 'h', 'o', 'o'},
        {'a', 'c', 't', 'h', 'p'},
        {'h', 'e', 't', 'e', 'q'}
    };
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("hello");
    REQUIRE(result.word != "hello");

    std::vector<std::vector<char>> puzzle2{ 
        {'a', 'l', 'a', 'o', 'l'},
        {'o', 'l', 'l', 'e', 'l'},
        {'l', 'o', 'h', 'o', 'h'},
        {'a', 'c', 't', 'e', 'p'},
        {'h', 'e', 'l', 'e', 'e'}
    };
    WordSearchSolver wss2(puzzle);
    WordLocation result2 = wss2.FindWord("hello");
    REQUIRE(result2.word != "hello");
}

TEST_CASE("consecutive", "consecutive") {
    std::vector<std::vector<char>> puzzle{ 
        {'a', 'l', 'a', 'o', 'l'},
        {'o', 'l', 'h', 'e', 'l'},
        {'c', 'c', 'a', 't', 'o'},
        {'a', 'c', 't', 'h', 'p'},
        {'h', 'e', 't', 'e', 'q'}
    };
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("cat");
    REQUIRE(result.word == "cat");

    std::vector<std::vector<char>> puzzle2{ 
        {'a', 'l', 'a', 'o', 'l'},
        {'o', 'c', 'h', 'e', 'l'},
        {'l', 'c', 'h', 'o', 'o'},
        {'a', 'a', 't', 'h', 'p'},
        {'h', 't', 't', 'e', 'q'}
    };
    WordSearchSolver wss2(puzzle);
    WordLocation result2 = wss2.FindWord("cat");
    REQUIRE(result2.word == "cat");

    std::vector<std::vector<char>> puzzle3{ 
        {'a', 'l', 'a', 'o', 'l'},
        {'o', 'c', 'h', 'e', 'l'},
        {'l', 'o', 'c', 'o', 'o'},
        {'a', 'c', 't', 'a', 'p'},
        {'h', 'e', 't', 'e', 't'}
    };
    WordSearchSolver wss3(puzzle);
    WordLocation result3 = wss3.FindWord("cat");
    REQUIRE(result3.word == "cat");

    std::vector<std::vector<char>> puzzle4{ 
        {'a', 'l', 'a', 'o', 'c'},
        {'o', 'l', 'h', 'c', 'l'},
        {'l', 'o', 'a', 'o', 'o'},
        {'a', 't', 't', 'h', 'p'},
        {'h', 'e', 't', 'e', 'q'}
    };
    WordSearchSolver wss4(puzzle4);
    WordLocation result4 = wss4.FindWord("cat");
    REQUIRE(result4.word == "cat");
}

TEST_CASE("puzzle shape", "puzzle shape") {

    std::vector<std::vector<char>> puzzlev{ 
        {'b', 'l', 'a', 'o', 'h', 'j'},
        {'o', 'a', 'h', 'e', 'u', 'd'},
        {'l', 'o', 'n', 'n', 'o', 'd'},
        {'a', 'c', 'g', 'a', 'p', 'd'},
        {'a', 'l', 'd', 'l', 'n', 'd'},
        {'e', 'c', 'd', 'l', 'p', 'a'},
    };
    WordSearchSolver wssv(puzzlev);
    WordLocation resultv = wssv.FindWord("banana");
    REQUIRE(resultv.word == "banana");

    WordLocation resultv2 = wssv.FindWord("jungle");
    REQUIRE(resultv2.word == "jungle");
}

/////////////////////////////////////////////////////////////////////////////////////////////