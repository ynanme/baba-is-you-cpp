#ifndef _COLLISION_HANDLERS
#define _COLLISION_HANDLERS

#include "../../utils/geometry.hpp"


enum class CollisionResult {
    BLOCKED,
    SHIFTED,
    COEXISTED,
    DEFEATED,
    AWARDED
};


class CollisionHandler {

    public:
        virtual CollisionResult handle_collision ();

};


class Blocker : public CollisionHandler {

    public:
        CollisionResult handle_collision ();

};

class Shifter : public CollisionHandler {

    public:
        CollisionResult handle_collision ();

};

class Coexister : public CollisionHandler {

    public:
        CollisionResult handle_collision ();

};

class Defeater : public CollisionHandler {

    public:
        CollisionResult handle_collision ();

};

class Awarder : public CollisionHandler {

    public:
        CollisionResult handle_collision ();

};


#endif