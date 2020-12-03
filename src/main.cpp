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
vector<Board<TCell>> stack;

template <typename TCell>
void undo(Board<TCell>& f) {
  if (stack<TCell>.size() >= 1) {
    f = stack<TCell>.back();
    stack<TCell>.pop_back();
    cout << "Undo." << endl;
  } else {
    cout << "Can't undo! stack.size() == 0" << endl;
  }
  cout << "stack.size = " << stack<TCell>.size() << endl;
}

template <typename TCell>
void addBoard(Board<TCell>& f) {
  if ((stack<TCell>.size() == 0) or (not f.isEqual(stack<TCell>.back())) ) {
    stack<TCell>.push_back(f);
  }
}

template <typename TCell>
void gameLoop(Board<TCell>& f, std::string startState, bool wide=false) {
  f.loadFromString(startState);
  cout << f.toString(wide) << endl;
  while(true) {
    char key = _getch();
    // cout << key << endl;
    switch (key) {
      case 'w': addBoard(f); f.movePlayerByDiff(-1, 0); break;
      case 's': addBoard(f); f.movePlayerByDiff(+1, 0); break;
      case 'a': addBoard(f); f.movePlayerByDiff(0, -1); break;
      case 'd': addBoard(f); f.movePlayerByDiff(0, +1); break;
      case 'r': f.loadFromString(startState); stack<TCell>.clear(); break;
      case 'u': undo(f); break;
      case 'p': return;
      default: break;
    }
    cout << f.toString(wide) << endl;
  }
}

int main() {
  Board<ushort> f(9, 9);
  cout << "width = " << f.width << ", height = " << f.height << endl;
  std::string startString = 
  "#####    "
  "#   #    "
  "# $@# ###"
  "# $$# #.#"
  "### ###.#"
  " ##    .#"
  " #   #  #"
  " #   ####"
  " #####   ";

  gameLoop(f, startString, WIDE);
  
  // test();
  return 0;
}
