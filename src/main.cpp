#include <iostream>
#include <vector>
#include <cassert>
#include "board.hpp"
#include "testing.hpp"
#include "utils.hpp"

using namespace std;

int main() {
  Board<ushort> f(7, 5);
  Board<ushort> g(7, 5);
  cout << "width = " << f.width << ", height = " << f.height << endl;
  f.loadFromString(
    "#######"
    "#  @  #"
    "#  $  #"
    "#     #"
    "#######"
  );
  
  cout << f.player_i << " " << f.player_j << endl;
  
  cout << f.toString() << endl;
  
  test();
  return 0;
}
