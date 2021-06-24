#ifndef LOAD_LEVELS_H
#define LOAD_LEVELS_H

bool isCommentLine(std::string& line);
bool isEndOfLevels(std::string& line);
bool isContainsLevelName(std::string& line);
std::string getLevelNameFromLine(std::string& line);
unsigned countCharacter(std::string& line, char input_char);
void trimRightWhileChar(std::string& line, char c);
Board<ushort> loadLevelFromLine(unsigned width, unsigned height, const std::string& s);
std::vector<Board<ushort>> loadLevels(std::ifstream *levels_file);
void addLevel(std::vector<Board<ushort>> *listOfLevels, int levelId, unsigned maxWidth, unsigned levelHeight, std::string currentLevelString, std::string levelName);

#endif
