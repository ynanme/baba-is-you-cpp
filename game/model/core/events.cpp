#include "events.hpp"


RuleChange :: RuleChange (vector<tuple<Label, Label, Label>> new_rules): new_rules {new_rules} {}


CharacterSet :: CharacterSet (Board * board, Position position): board {board}, position {position} {}
