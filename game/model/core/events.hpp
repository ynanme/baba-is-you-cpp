#ifndef _EVENTS
#define _EVENTS

#include <vector>
#include <tuple>
#include "../characters/labels.hpp"
#include "../../utils/geometry.hpp"


class Board;


class RuleChange {

    public:
        vector<tuple<Label, Label, Label>> new_rules;
        RuleChange (vector<tuple<Label, Label, Label>> new_rules);

};


class CharacterSet {

    public:
        Board * board;
        Position position;
        CharacterSet (Board * board, Position position);

};


#endif