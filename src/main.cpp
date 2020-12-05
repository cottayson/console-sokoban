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

using namespace std;

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

bool isCommentLine(std::string& line) {
  return line[0] == '-' and line[1] == '-';
}

bool isEndOfLevels(std::string& line) {
  return line[0] == '|' and line[1] == '|';
}

bool isContainsLevelName(std::string& line) {
  return line[3] == '|';
}

std::string getLevelNameFromLine(std::string& line) {
  return line.substr(5, string::npos);
}

unsigned countCharacter(std::string& line, char input_char) {
  unsigned counter = 0;
  for (char c : line) {
    if (c == input_char) {
      counter++;
    }
  }
  return counter;
}

void trimRightWhileChar(std::string& line, char c) {
  while(line.size() > 0 && line.back() != c) {
    line.pop_back();
  }
}

Board<ushort> loadLevelFromString(unsigned width, unsigned height, const std::string& s) {
  Board<ushort> b(width, height);
  // Load cells
  unsigned i = 0;
  for (char ch : s) {
    if (ch == '|') { // line ends with '|' character then jump index forward
      // amount = width - i % width
      // i = i + width - i % width; <=> 
      if (i % width == 0) {
        cout << "i = " << i << endl;
      } else {
        i = (i / width + 1) * width;
      }
      continue;
    }
    if (ch == CHARS::PLAYER or ch == CHARS::PLAYER_ON_GOAL) {
      // Load player position
      std::tie(b.player_i, b.player_j) = b.fromIndex(b.width, i);
    }
    b.cells[i++] = (ushort)ch;
  }
  return b;
}

vector<Board<ushort>> loadLevels(const std::string& filename) {
  vector<Board<ushort>> listOfLevels;
  // bool readingLevel = false;
  std::string currentLevelString = "";
  unsigned levelId = 0;
  unsigned levelHeight = 0;
  unsigned maxWidth = 0;
  ifstream levels_file(filename);
  // levels_file.open("levels.txt");
  string line = "";
  if (levels_file.is_open()) {
    while (getline(levels_file, line)) {
      if (isCommentLine(line)) {
        if (isContainsLevelName(line)) {
          cout << "name = " << getLevelNameFromLine(line) << endl;
          if (levelId > 0) {
            // check and add readed level to database
            // cout << "LEVEL BEGIN" << endl;
            // cout << currentLevelString << endl;
            // cout << "LEVEL END, loaded level:" << endl;
            Board<ushort> level = loadLevelFromString(maxWidth, levelHeight, currentLevelString);
            listOfLevels.push_back(level);
            cout << level.toString() << endl;
            // cout << "maxWidth = " << maxWidth << endl;
            // cout << "Height = " << levelHeight << endl;

            // reset level parameters
            currentLevelString = "";
            maxWidth = 0;
            levelHeight = 0;
          }
          levelId++;
          cout << "levelId = " << levelId << endl;
          // readingLevel = true;
        }
        continue;
      } else if (isEndOfLevels(line)) {
        cout << "detected end of levels" << endl;
        break;
      } else if (countCharacter(line, CHARS::WALL) > 0) {
        // reading part of level
        // "  ## ###    "
        //  012345678
        trimRightWhileChar(line, CHARS::WALL);
        if (maxWidth < line.size()) {
          maxWidth = line.size();
        }
        currentLevelString += line;
        levelHeight++;
        
        currentLevelString.push_back('|');
      }
      cout << line << endl;
    }
    levels_file.close();
  }
  return listOfLevels;
}

int main() {
  test();
  Board<ushort> f(22, 13);
  cout << "width = " << f.width << ", height = " << f.height << endl;
  
  // cout << s1 + s2 << endl;
  auto levels = loadLevels("levels.txt");

  gameLoop(levels[3]);

  
  // std::string startString = 
  // " #################### "
  // " #      ##     #    ##"
  // " # ##.   # $ . #. .  #"
  // " #  # #  # ##  #  $  #"
  // " # .###    #   ## #  #"
  // " # $  #$ #.#$. $  ####"
  // " #    #           #   "
  // " #.  ###$ ######  #   "
  // "####$  #  #    ####   "
  // "# $    ####           "
  // "# # #. #              "
  // "#+$ ####              "
  // "#####                 ";
  
  // Verifier<ushort> v;
  // f.loadFromString(startString);
  // assert(v.checkBlocksAndGoals(f));
  
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
