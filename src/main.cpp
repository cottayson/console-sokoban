#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <deque>
#include <string>
#include <cassert>
#include "board.hpp"
#include "testing.hpp"
#include "utils.hpp"
#include "gameloop.hpp"
#include "verifier.hpp"
#include "load_levels.hpp"

int main() {
  test();
  auto levels = loadLevels("levels.txt");

  gameLoop(levels[10]);
  
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
