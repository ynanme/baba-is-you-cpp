#include "action.hpp"


Action :: Action (Direction direction):
direction {direction} {}


Direction Action :: get_direction () const {
    return direction;
}

vector<Character *> Action :: get_moved_characters () const {
    return moved_characters;
}

vector<Character *> Action :: get_destroyed_characters () const {
    return destroyed_characters;
}


void Action :: add_moved_character (Character * moved_character) {
    moved_characters.push_back(moved_character);
}

void Action :: add_destroyed_character (Character * destroyed_character) {
    destroyed_characters.push_back(destroyed_character);
}