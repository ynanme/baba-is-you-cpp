#ifndef _BOARD
#define _BOARD

#include <map>
#include <vector>
#include <algorithm>
#include "../../utils/geometry.hpp"
#include "../characters/character.hpp"
#include "action.hpp"
#include "../../utils/observer_pattern.hpp"
#include "events.hpp"

using std::map;
using std::vector;

class Game;

class Board : public Subject<CharacterSet> {

static Character NONE_CHARACTER;
static const std::vector<Character*> NONE_VECTOR;

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
    const vector<Character*>& get_neighbor(Character& character, Direction direction);
    void set(Character& character);

    bool in_bounds(const Position& pos) const;
    vector<Character*>& get_cell(const Position& pos);
};

#endif