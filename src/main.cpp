#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <conio.h> // for keypress
#include "board.hpp"
#include "testing.hpp"
#include "utils.hpp"
#define WIDE true

using namespace std;

template <typename TCell>
void gameLoop(Board<TCell>& f, std::string startState, bool wide=false) {
  f.loadFromString(startState);
  cout << f.toString(wide) << endl;
  while(true) {
    char key = _getch();
    // cout << key << endl;
    switch (key) {
      case 'w': f.movePlayerByDiff(-1, 0); break;
      case 's': f.movePlayerByDiff(+1, 0); break;
      case 'a': f.movePlayerByDiff(0, -1); break;
      case 'd': f.movePlayerByDiff(0, +1); break;
      case 'r': f.loadFromString(startState); break;
      case 'p': return;
      default: break;
    }
    cout << f.toString(wide) << endl;
  }
}

int main() {
  Board<ushort> f(17, 16);
  cout << "width = " << f.width << ", height = " << f.height << endl;
  std::string startString = 
  "            #### "
  "###### #### #  # "
  "#    ### @###  # "
  "# $$ $ # $$    # "
  "#   $#  $ $ #$###"
  "####.### #$ $ $ #"
  "   #.....#  #   #"
  "####..##.##$  ###"
  "#  #.....   ###  "   
  "#  ....#$####    "
  "#  ##### #       "   
  "##$###   #       "   
  "#  ## $  #       "   
  "#    $ $##       "   
  "#  ##   #        "   
  "#########        ";


  gameLoop(f, startString, WIDE);
  
  // test();
  return 0;
}
