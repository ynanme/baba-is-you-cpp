#include "collision_handlers.hpp"


CollisionResult Blocker :: handle_collision () {
    return CollisionResult::BLOCKED;
}


CollisionResult Shifter :: handle_collision () {
    return CollisionResult::SHIFTED;
}


CollisionResult Coexister :: handle_collision () {
    return CollisionResult::COEXISTED;
}


CollisionResult Defeater :: handle_collision () {
    return CollisionResult::DEFEATED;
}


CollisionResult Awarder :: handle_collision () {
    return CollisionResult::AWARDED;
}