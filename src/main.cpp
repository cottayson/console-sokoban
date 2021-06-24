#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <deque>
#include <string>
#include <cassert>
#include "board.hpp"
#include "utils.hpp"
#include "gameloop.hpp"
#include "verifier.hpp"
#include "load_levels.hpp"

int main(int argc, char* argv[]) {
  std::string fileName;
  unsigned levelId = 0;
  unsigned arguments = argc - 1;
  if (arguments == 0) {
    std::cout << "no arguments provided."  << std::endl;
    return 0;
  } else if (arguments == 1) {
    fileName = argv[1];
  } else {
    fileName = argv[1];
    levelId = std::atoi(argv[2]);
  }

  std::cout << "fileName = " << fileName << std::endl;
  std::cout << "levelId = " << levelId << std::endl;

  auto levels = loadLevels(fileName);
  
  
  if(levelId < levels.size()) {
    gameLoop(levels[levelId]);
  } else {
    std::cout << "levelId too big, levels.size() = " << levels.size() << std::endl;
  }
  
  

  // levels[3].movePlayerByDiff(1, 0);
  // levels[3].movePlayerByDiff(0, 1);
  // std::cout << levels[3].toString() << std::endl;

  // gameLoop(levels[3]);
  
  /* blocks ordered from left to right, up to down like letters
  "  ####  "
  "  #++#  "
  " ##@+## "
  " #@@1.# "
  "##@2  ##"
  "#@@#34@#"
  "#@@@@@@#"
  "########"; @ - indicates player position class (if cost of move = 0)
  numberOfDistinctPushes = {
    block 1: [R, D]  -- 2
    block 2: [R]     -- 1
    block 3: [U]     -- 1
    block 4: [U]     -- 1
  } => all_possible_pushes.size() == 5
  */

  // TODO: calculate number of possible pushes in current player position class
  // number of pushes in this start position = 

  // gameLoop(f, startString);
  
  return 0;
}
