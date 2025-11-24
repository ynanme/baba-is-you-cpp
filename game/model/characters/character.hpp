#ifndef _CHARACTER
#define _CHARACTER

#include "labels.hpp"
#include "../collision_handlers/collision_handlers.hpp"
#include "../../utils/geometry.hpp"



class Character {

    private:
    
        Position position;
        CollisionHandler collision_handler;
        Label label;

    public:

        Character (Position position, CollisionHandler collision_handler, Label label);

        Position get_position () const;
        Label get_label () const;

        void move (Direction direction);

        CollisionResult collide ();
        void change_collision_handling (CollisionHandler new_collision_handler);

};


#endif