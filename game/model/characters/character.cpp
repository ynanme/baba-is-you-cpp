#include "character.hpp"


Character :: Character (Position position, CollisionHandler collision_handler, Label label):
position {position}, collision_handler {collision_handler}, label {label} {}


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
    return collision_handler.handle_collision();
}

void Character :: change_collision_handling (CollisionHandler new_collision_handler) {
    collision_handler = new_collision_handler;
}