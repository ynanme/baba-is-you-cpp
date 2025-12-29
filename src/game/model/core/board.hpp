#ifndef _BOARD
#define _BOARD

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "game/utils/geometry.hpp"
#include "game/utils/observer_pattern.hpp"
#include "game/model/characters/character.hpp"
#include "game/model/core/events.hpp"

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
    void set(Character * character, bool notify_ruler = true);

    bool in_bounds(const Position& pos) const;
    vector<Character*>& get_cell(const Position& pos);

friend ostream& operator << (ostream& out, const Board& board);

};


ostream& operator << (ostream& out, const Board& board);


#endif