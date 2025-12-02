#ifndef _EVENTS
#define _EVENTS

#include "board.hpp"
#include "../../utils/geometry.hpp"


class RuleChange {

    public:
        vector<tuple<Label, Label, Label>> new_rules;

};


class CharacterSet {

    public:
        Board * board;
        Position position;

};


#endif