#include "events.hpp"


RuleChange :: RuleChange (vector<tuple<Label, Label, Label>> new_rules, vector<tuple<Label, Label, Label>> old_rules):
new_rules {new_rules}, old_rules {old_rules} {}


CharacterSet :: CharacterSet (Board * board, Character * set_character):
board {board}, set_character {set_character} {}
