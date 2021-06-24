#include <cassert>
#include "board.hpp"
#include "load_levels.hpp"
#include <iostream>

void testLoadFromString() {
  // width = 3, height = 2
  Board<ushort> f(3, 2);
  // *** 2 row = 0
  // *** 5 row = 1
  // *@* 8 row = 2, column = 1
  assert(f.toIndex(1, 0, 0) == 0);
  assert(f.toIndex(3, 2, 1) == 7);

  // hel
  // lo_
  // row = 1, column = 2 => 101 = e
  f.loadFromString("hello");
  assert((char)f.getCell(0, 1) == 'e');
}

void testLoadPlayer() {
  Board<ushort> f(7, 4);
  f.loadFromString(
    "#######"
    "#.$   #"
    "#@  * #"
    "#######"
  );
  assert(f.width == 7 && f.height == 4);
  assert(f.player_i == 2 && f.player_j == 1);
}

void testCanMove() {
    Board<ushort> f(7, 5);
    f.loadFromString(
    "#######"
    "#     #"
    "#.$@$$#"
    "#  *  #"
    "#######"
  );

  assert(not f.isMovableCell(f.getCell(2, 1)));
  assert(    f.isMovableCell(f.getCell(3, 3)));
  assert(    f.isMovableCell(f.getCell(2, 2)));
  assert(    f.isMovableCell(f.getCell(2, 4)));

  assert(    f.canMovePlayer(f.LEFT_DIR));
  assert(not f.canMovePlayer(f.RIGHT_DIR));
  assert(    f.canMovePlayer(f.UP_DIR));
  assert(not f.canMovePlayer(f.DOWN_DIR));

  f.loadFromString(
    "#######"
    "#   * #"
    "# .*+##"
    "#   $ #"
    "#######"
  );
  // assert(1 == 2); test working of current subsroutine `void testCanMove()`
  assert(    f.canMovePlayer(f.LEFT_DIR));
  assert(not f.canMovePlayer(f.RIGHT_DIR));
  assert(not f.canMovePlayer(f.UP_DIR));
  assert(not f.canMovePlayer(f.DOWN_DIR));
}

void testEquality() {
  Board<ushort> f(7, 5);
  Board<ushort> g(7, 5);
  f.loadFromString(
    "#######"
    "#     #"
    "#.$@$$#"
    "#  *  #"
    "#######"
  );

  g.loadFromString(
    "#######"
    "#     #"
    "#.$@$$#"
    "#  *  #"
    "#######"
  );

  assert(f.isEqual(g));
  g.loadFromString(
    "#######"
    "#  @  #"
    "#.$ $$#"
    "#  *  #"
    "#######"
  );

  assert(not f.isEqual(g));
}


void testMovePlayerByDiff() {
  Board<ushort> f(7, 5);
  Board<ushort> g(7, 5);
  f.loadFromString(
    "#######"
    "#  @  #"
    "#  $  #"
    "#     #"
    "#######"
  );
  
  assert(f.movePlayerByDiff(1, 0));
  g.loadFromString(
    "#######"
    "#     #"
    "#  @  #"
    "#  $  #"
    "#######"
  );

  assert(f.isEqual(g));

  f.loadFromString(
    "#######"
    "#     #"
    "#  $@ #"
    "#     #"
    "#######"
  );
  
  assert(    f.movePlayerByDiff(0, -1));
  assert(    f.movePlayerByDiff(0, -1));
  assert(not f.movePlayerByDiff(0, -1));

  g.loadFromString(
    "#######"
    "#     #"
    "#$@   #"
    "#     #"
    "#######"
  );

  assert(f.isEqual(g));
  // have error: #$* +$#, expected: #$* + #, difference is symbol '$' => we have error when we put block on board
  // fixed by: adding 4th branch to if (next_pos_char == FLOOR_CHAR) { ... }
  f.loadFromString(
    "#######"
    "#     #"
    "#$.$+ #"
    "#     #"
    "#######"
  );
  
  assert(f.movePlayerByDiff(0, -1));
  assert(f.movePlayerByDiff(0, +1));

  g.loadFromString(
    "#######"
    "#     #"
    "#$* + #"
    "#     #"
    "#######"
  );

  assert(f.isEqual(g));

  f.loadFromString(
    "#######"
    "#.... #"
    "#   . #"
    "#   + #"
    "#######"
  );
  
  assert(    f.movePlayerByDiff(-1, 0));
  assert(    f.movePlayerByDiff(-1, 0));
  assert(not f.movePlayerByDiff(-1, 0));
  assert(f.movePlayerByDiff(0, +1));

  g.loadFromString(
    "#######"
    "#....@#"
    "#   . #"
    "#   . #"
    "#######"
  );
  
  assert(f.isEqual(g));

  assert(    f.movePlayerByDiff(0, -1));
  assert(    f.movePlayerByDiff(0, -1));
  assert(    f.movePlayerByDiff(0, -1));
  assert(    f.movePlayerByDiff(0, -1));
  assert(not f.movePlayerByDiff(0, -1));

  g.loadFromString(
    "#######"
    "#+... #"
    "#   . #"
    "#   . #"
    "#######"
  );

  assert(f.isEqual(g));

  f.loadFromString(
    "#######"
    "#     #"
    "# *.* #"
    "# $ + #"
    "#######"
  );

  assert(f.movePlayerByDiff(-1, 0));

  g.loadFromString(
    "#######"
    "#   $ #"
    "# *.+ #"
    "# $ . #"
    "#######"
  );

  assert(f.movePlayerByDiff(0, -1));
  assert(f.movePlayerByDiff(0, -1));
  assert(not f.movePlayerByDiff(0, -1));
  assert(f.movePlayerByDiff(0, +1));
  assert(f.movePlayerByDiff(+1, 0));
  assert(not f.movePlayerByDiff(+1, 0));
  assert(f.movePlayerByDiff(0, -1));
  assert(not f.movePlayerByDiff(0, -1));

  g.loadFromString(
    "#######"
    "#   $ #"
    "#$... #"
    "#$@ . #"
    "#######"
  );

  assert(f.isEqual(g));
}

void testCountObjects() {
  Board<ushort> f(8, 8);
  f.loadFromString(
    "  ####  "
    "  #..#  "
    " ## .## "
    " #  $.# "
    "## $  ##"
    "#  #$$ #"
    "#  @   #"
    "########"
  );

  assert(f.countObjects(f.BLOCK_CHAR) == 4);
  assert(f.countObjects(f.GOAL_CHAR) == 4);
  assert(f.countObjects(f.WALL_CHAR) == 29);
  assert(not f.isWin());
}

void testLoadLevelFromLine() {
  Board<ushort> levelBoard = loadLevelFromLine(3, 3, "###|###|###");
  assert(levelBoard.toString() == "###\n###\n###\n");

  levelBoard = loadLevelFromLine(7, 3, " ### |#   #|#######");
  assert(levelBoard.toString() == " ###   \n#   #  \n#######\n");
}

void test() {
  testLoadFromString();
  testLoadPlayer();
  testCanMove();
  testEquality();
  testMovePlayerByDiff();
  testCountObjects();
  testLoadLevelFromLine();
}

int main() {
  test();
  return 0;
}
