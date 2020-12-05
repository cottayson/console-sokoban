#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "verifier.hpp"

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
  return line.substr(5, std::string::npos);
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

Board<ushort> loadLevelFromLine(unsigned width, unsigned height, const std::string& s) {
  Board<ushort> b(width, height);
  // Load cells
  unsigned i = 0;
  for (char ch : s) {
    if (ch == '|') { // line ends with '|' character then jump index forward
      // amount = width - i % width
      // i = i + width - i % width; <=> 
      if (i % width > 0) {
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

std::vector<Board<ushort>> loadLevels(const std::string& filename) {
  Verifier<ushort> verifier;
  std::vector<Board<ushort>> listOfLevels;
  // bool readingLevel = false;
  std::string currentLevelString = "";
  unsigned levelId = 0;
  unsigned levelHeight = 0;
  unsigned maxWidth = 0;
  // std::ifstream levels_file(filename);
  std::ifstream levels_file("levels.txt");
  // levels_file.open("levels.txt");
  std::string line = "";
  if (levels_file.is_open()) {
    while (getline(levels_file, line)) {
      if (isCommentLine(line)) {
        if (isContainsLevelName(line)) {
          std::string levelName = getLevelNameFromLine(line);
          if (levelId > 0) {
            // check and add readed level to database
            // std::cout << "LEVEL BEGIN" << std::endl;
            // std::cout << currentLevelString << std::endl;
            // std::cout << "LEVEL END, loaded level:" << std::endl;
            Board<ushort> level = loadLevelFromLine(maxWidth, levelHeight, currentLevelString);
            if (not verifier.checkBlocksAndGoals(level)) {
              std::cout << "Error in level #" << levelId << "| " << levelName << std::endl;
              return listOfLevels;
            }
            listOfLevels.push_back(level);
            // std::cout << level.toString() << std::endl;
            // std::cout << "maxWidth = " << maxWidth << std::endl;
            // std::cout << "Height = " << levelHeight << std::endl;

            // reset level parameters
            currentLevelString = "";
            maxWidth = 0;
            levelHeight = 0;
          }
          levelId++;
          // std::cout << "levelId = " << levelId << std::endl;
          // readingLevel = true;
        }
        continue;
      } else if (isEndOfLevels(line)) {
        std::cout << "detected end of levels" << std::endl;
        break;
      } else if (countCharacter(line, CHARS::WALL) >= 2) { 
        // --------- just use prop of levels #5 from ideas.md
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
      // std::cout << line << std::endl;
    }
    levels_file.close();
  }
  return listOfLevels;
}
