#ifndef GAMELOOP_H
#define GAMELOOP_H
#include <conio.h> // for keypress
template <typename TCell>
std::vector<Board<TCell>> stack;

template <typename TCell>
void undo(Board<TCell>& f) {
  if (stack<TCell>.size() >= 1) {
    f = stack<TCell>.back();
    stack<TCell>.pop_back();
    std::cout << "Undo." << std::endl;
  } else {
    std::cout << "Can't undo! stack.size() == 0" << std::endl;
  }
  std::cout << "stack.size = " << stack<TCell>.size() << std::endl;
}

template <typename TCell>
void addBoard(Board<TCell>& f) {
  if ((stack<TCell>.size() == 0) or (not f.isEqual(stack<TCell>.back())) ) {
    stack<TCell>.push_back(f);
  }
}

void changeMode() {
  g_wide = not g_wide;
}

template <typename TCell>
void gameLoop(Board<TCell>& startBoard) {
  auto f = startBoard;
  std::cout << f.toString(g_wide) << std::endl;
  while(true) {
    char key = _getch();
    // cout << key << endl;
    switch (key) {
      case 'w': addBoard(f); f.movePlayerByDiff(-1, 0); break;
      case 's': addBoard(f); f.movePlayerByDiff(+1, 0); break;
      case 'a': addBoard(f); f.movePlayerByDiff(0, -1); break;
      case 'd': addBoard(f); f.movePlayerByDiff(0, +1); break;
      case 'r': f = startBoard; stack<TCell>.clear(); break;
      case 'u': undo(f); break;
      case 'm': changeMode(); break;
      case 'p': return;
      default: break;
    }
    if(f.isWin()) {
      std::cout << "You win!" << std::endl;
    }
    std::cout << f.toString(g_wide) << std::endl;
  }
}

template <typename TCell>
void gameLoop(Board<TCell>& f, std::string startState) {
  f.loadFromString(startState);
  std::cout << f.toString(g_wide) << std::endl;
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
      case 'm': changeMode(); break;
      case 'p': return;
      default: break;
    }
    if(f.isWin()) {
      std::cout << "You win!" << std::endl;
    }
    std::cout << f.toString(g_wide) << std::endl;
  }
}
#endif
