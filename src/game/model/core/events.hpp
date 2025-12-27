#ifndef _EVENTS
#define _EVENTS

#include <vector>
#include <tuple>
#include "../characters/labels.hpp"
#include "../characters/character.hpp"


class Board;


class RuleChange {

    public:
        vector<tuple<Label, Label, Label>> new_rules;
        vector<tuple<Label, Label, Label>> old_rules;
        RuleChange (
            const vector<tuple<Label, Label, Label>> & new_rules,
            const vector<tuple<Label, Label, Label>> & old_rules
        );

};


class CharacterSet {

    public:
        Board & board;
        Character & set_character;
        CharacterSet (Board & board, Character & set_character);

};


#endif