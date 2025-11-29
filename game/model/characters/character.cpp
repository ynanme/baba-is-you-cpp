#include "character.hpp"


Character :: Character (Position position, CollisionResult collision_result, Label label):
position {position}, collision_result {collision_result}, label {label} {}


Position Character :: get_position () const {
    return position;
}

Label Character :: get_label () const {
    return label;
}


void Character :: move (Direction direction) {
    position.shift(direction);
}


CollisionResult Character :: collide () {
    return collision_result;
}

void Character :: change_collision_handling (CollisionResult new_collision_result) {
    collision_result = new_collision_result;
}