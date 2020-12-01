#include <iostream>
#include <vector>
#include <cassert>
#include "board.hpp"
#include "testing.hpp"
#include "utils.hpp"

using namespace std;

int main() {
  Board<ushort> f(7, 5);
  cout << "width = " << f.width << ", height = " << f.height << endl;
  f.loadFromString(
    "#######"
    "#  @  #"
    "#  $  #"
    "#     #"
    "#######"
  );
  
  f.movePlayerByDiff(1, 0);

  f.loadFromString(
    "#######"
    "#     #"
    "#  $@ #"
    "#     #"
    "#######"
  );
  
  f.movePlayerByDiff(0, -1);
  f.movePlayerByDiff(0, -1);

  // have error: #$* +$#, expected: #$* + #, difference is symbol '$' => we have error when we put block on board
  // fixed by: adding 4th branch to if (next_pos_char == FLOOR_CHAR) { ... }
  f.loadFromString(
    "#######"
    "#     #"
    "#$*@. #"
    "#     #"
    "#######"
  );
  
  // f.movePlayerByDiff(0, -1);
  f.movePlayerByDiff(0, 1);


  cout << f.player_i << " " << f.player_j << endl;
  
  cout << f.toString() << endl;
  
  test();
  return 0;
}
