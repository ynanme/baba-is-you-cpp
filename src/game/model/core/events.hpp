#ifndef _EVENTS
#define _EVENTS

#include <vector>
#include <tuple>
#include "game/model/characters/labels.hpp"
#include "game/model/characters/character.hpp"


class Board;


class RuleChange {

    public:
        std::vector<std::tuple<Label, Label, Label>> new_rules;
        std::vector<std::tuple<Label, Label, Label>> old_rules;
        RuleChange (
            const std::vector<std::tuple<Label, Label, Label>> & new_rules,
            const std::vector<std::tuple<Label, Label, Label>> & old_rules
        );

};


class CharacterSet {

    public:
        Board & board;
        Character & set_character;
        CharacterSet (Board & board, Character & set_character);

};


#endif