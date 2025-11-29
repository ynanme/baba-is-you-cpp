#include "action.hpp"


Action :: Action (Character * initiator, Direction direction):
direction {direction} {
    involved_characters.push_back(initiator);
}


Direction Action :: get_direction () const {
    return direction;
}


CollisionResult Action :: get_result () const {
    return result;
}

void Action :: set_result (CollisionResult new_result) {
    result = new_result;
}


Character & Action :: get_initiator () const {
    return involved_characters.at(0);
}

vector<Character *> Action :: get_involved_characters () const {
    return involved_characters;
}

void Action :: add_involved_character (Character & involved_character) {
    involved_characters.push_back(&involved_character);
}