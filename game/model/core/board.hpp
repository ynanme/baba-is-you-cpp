#ifndef _BOARD
#define _BOARD

#include <map>
#include <vector>
#include <algorithm>
#include "../utils/geometry.hpp"
#include "../characters/character.hpp"
#include "action.hpp"
#include "observer_pattern.hpp"

using std::map;
using std::vector;

class Game;

class Board : public Subject {
private:
    map<Position, vector<Character*>> grid;
    int width;
    int height;

public:
    Board(int width, int height);

    int get_width() const;
    int get_height() const;
    const vector<Character*>& at(const Position& pos) const;

    void add_character(Character* character);
    void remove_character(Character* character);

    Action move_character(Character& character, Direction direction);

private:
    bool in_bounds(const Position& pos) const;
    vector<Character*>& get_cell(const Position& pos);
};

#endif
