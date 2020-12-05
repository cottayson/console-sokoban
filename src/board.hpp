#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <tuple>
#include <string>

typedef unsigned short ushort;

namespace CHARS {
  const char PLAYER         = '@';
  const char PLAYER_ON_GOAL = '+';
  const char BLOCK          = '$';
  const char BLOCK_ON_GOAL  = '*';
  const char FLOOR          = ' ';
  const char WALL           = '#';
  const char GOAL           = '.';
}

template<typename TCell>
class Board {
  public:
    static const char PLAYER_CHAR         = '@';
    static const char PLAYER_ON_GOAL_CHAR = '+';
    static const char BLOCK_CHAR          = '$';
    static const char BLOCK_ON_GOAL_CHAR  = '*';
    static const char FLOOR_CHAR          = ' ';
    static const char WALL_CHAR           = '#';
    static const char GOAL_CHAR           = '.';
    static const ushort LEFT_DIR  = 0;
    static const ushort RIGHT_DIR = 1;
    static const ushort UP_DIR    = 2;
    static const ushort DOWN_DIR  = 3;
    std::vector<TCell> cells;
    ushort player_i = -1, player_j = -1;
    ushort width, height;
    Board(ushort w, ushort h) : width(w), height(h) {
      cells.resize(w * h, FLOOR_CHAR);
    }

    static char cellToChar(TCell cell) {
      char c = (char)cell;
      switch (c) {
        case '$': return c;
        case '*': return c;
        case '.': return c;
        case '+': return c;
        case '@': return c;
        case '#': return c;
        case ' ': return c;
        default:  return '?';
      }
    }

    static unsigned toIndex(ushort width, ushort row, ushort column) {
      return width * (unsigned) row + (unsigned) column;
    }

    static std::tuple<ushort, ushort> fromIndex(ushort width, unsigned i) {
      return std::make_tuple(i / width, i % width);
    }

    TCell getCell(ushort row, ushort column) {
      return cells[toIndex(width, row, column)];
    }

    void setCell(ushort row, ushort column, TCell value) {
      cells[toIndex(width, row, column)] = value;
    }

    void loadFromString(std::string s) {
      // Load cells
      unsigned i = 0;
      for (char ch : s) {
        if (not (ch == '\n' or ch == '\t' or ch == '\r')) {
          if (ch == PLAYER_CHAR or ch == PLAYER_ON_GOAL_CHAR) {
            // Load player position
            std::tie (player_i, player_j) = fromIndex(width, i);
            // player_i = i / width; // i == index of row
            // player_j = i % width; // j == index of column
          }
          cells[i++] = (ushort)ch;
        }
      }
    }

    std::string toString(bool wide = false) {
      std::string s = "";
      for (unsigned i = 0; i < height; ++i) {
        for (unsigned j = 0; j < width; ++j) {
          s += cellToChar(getCell(i, j)); 
          if (wide) { s += ' '; }
        }
        s += '\n';
      }
      return s;
    }

    static bool isFreeCell(TCell cell) {
      char c = cellToChar(cell);
      return c == FLOOR_CHAR or c == GOAL_CHAR; // '$' '*' '.' '+' '@' '#' ' '
    }

    bool isMovableCell(TCell cell) {
      char c = cellToChar(cell);
      return c == BLOCK_CHAR or c == BLOCK_ON_GOAL_CHAR;
    }

    bool canMoveObjectByDiff(ushort i, ushort j, ushort di, ushort dj) {
      if (isMovableCell(getCell(i, j))) {
        return isFreeCell(getCell(i + di, j + dj));
      } else {
        return false;
      }
    }

    bool canMovePlayer(ushort dir) {
      switch (dir) {
        case LEFT_DIR:  return canMovePlayerByDiff(0, -1);
        case RIGHT_DIR: return canMovePlayerByDiff(0, +1);
        case UP_DIR:    return canMovePlayerByDiff(-1, 0);
        case DOWN_DIR:  return canMovePlayerByDiff(+1, 0);
        default:        return false;
      }
    }

    bool canMovePlayerByDiff(short di, short dj) {
      ushort pos_i = player_i + di;
      ushort pos_j = player_j + dj;
      return isFreeCell(getCell(pos_i, pos_j)) or canMoveObjectByDiff(pos_i, pos_j, di, dj);
    }

    void moveObjectByDiff(ushort i, ushort j, ushort di, ushort dj) {
      ushort next_i = i + di;
      ushort next_j = j + dj;
      char current_pos_char = cellToChar(getCell(i, j));
      char next_pos_char = cellToChar(getCell(next_i, next_j));
      // set next position
      if (next_pos_char == FLOOR_CHAR) { // ' '
        setCell(next_i, next_j, (TCell)BLOCK_CHAR); // '$'
      } else { // next_pos_char == '.'
        setCell(next_i, next_j, (TCell)BLOCK_ON_GOAL_CHAR); // '*'
      }
      // set current position
      if (current_pos_char == BLOCK_CHAR) { // '$'
        setCell(i, j, (TCell)FLOOR_CHAR); // ' '
      } else { // current_pos_char == '*'
        setCell(i, j, (TCell)GOAL_CHAR); // '.'
      }
    }

    bool movePlayerByDiff(short di, short dj) {
      ushort next_player_i = player_i + di;
      ushort next_player_j = player_j + dj;
      char current_pos_char = cellToChar(getCell(player_i, player_j));
      char next_pos_char = cellToChar(getCell(next_player_i, next_player_j));
      if (canMovePlayerByDiff(di, dj)) {
        // set next position
        if (next_pos_char == FLOOR_CHAR) { // ' '
          setCell(next_player_i, next_player_j, (TCell)PLAYER_CHAR); // '@'
        } else if (next_pos_char == BLOCK_CHAR) { // '$'
          moveObjectByDiff(next_player_i, next_player_j, di, dj);
          setCell(next_player_i, next_player_j, (TCell)PLAYER_CHAR); // '@'
        } else if (next_pos_char == BLOCK_ON_GOAL_CHAR) { // '*'
          moveObjectByDiff(next_player_i, next_player_j, di, dj);
          setCell(next_player_i, next_player_j, (TCell)PLAYER_ON_GOAL_CHAR); // '+'
        } else { // next_pos_char == '.'
          setCell(next_player_i, next_player_j, (TCell)PLAYER_ON_GOAL_CHAR);
        }
        // set current position
        if (current_pos_char == PLAYER_ON_GOAL_CHAR) { // '+'
          setCell(player_i, player_j, (TCell)GOAL_CHAR); // '.'
        } else { // current_pos_char == '@'
          setCell(player_i, player_j, (TCell)FLOOR_CHAR); // ' '
        }
        // update player position
        player_i = next_player_i;
        player_j = next_player_j;
        return true;
      } else {
        return false;
      }
    }

    bool isEqual(Board& b) {
      if (not (player_i == b.player_i and player_j == b.player_j)) {
        return false;
      }
      for (unsigned i = 0; i < cells.size(); ++i) {
        if (cells[i] != b.cells[i]) {
          return false;
        }
      }
      return true;
    }

    bool isEqualToBlockMove(Board& b) {
      // player move class
      // ######    ######    ######
      // #  $ #    #@ $ #    #  $ #
      // # @$ # == #  $ # != #  $@#
      // #  $ #    #  $ #    #  $ #
      // ######    ######    ######
      return false;
    }

    unsigned countObjects(char objectType) {
      unsigned counter = 0;
      for (unsigned i = 0; i < cells.size(); ++i) {
        auto cell = cells[i];
        char c = cellToChar(cell);
        if (c == objectType) {
          counter++;
        }
      }
      return counter;
    }

    bool isWin() {
      return countObjects(BLOCK_CHAR) == 0;
    }
};

#endif
