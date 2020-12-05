#ifndef VERIFIER_H
#define VERIFIER_H
#include "board.hpp"

template<typename T>
class Verifier {
public:
  Verifier() {}

  checkBlocksAndGoals(Board<T>& b) {
    unsigned freeBlocks = b.countObjects(b.BLOCK_CHAR);
    unsigned emptyGoals = b.countObjects(b.GOAL_CHAR) + 
      b.countObjects(b.PLAYER_ON_GOAL_CHAR);
    return freeBlocks == emptyGoals;
  }
  // vector<tuple<ushort, ushort, ushort>> getPossiblePushes() {
  //   // returns vector of tuples (posx, posy, direction)

  // }

  // if no pushes possible then check will return false
  bool check(Board<T>& b) {
    // type width = ushort, type height = ushort
    // type (width * height) = <ushort, ushort> ~= unsigned
    for (ushort i = 0; i < b.height; ++i) { // i = number of row
      for (ushort j = 0; j < b.width; ++j) { // j = number of column
        auto cell = b.getCell(i, j);
        char c = b.cellToChar(cell);
        if (c == b.BLOCK_CHAR) {
          // check cells around block
          return false;
        }
      }
    }
    return true;
  }
};

#endif