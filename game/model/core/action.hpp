#ifndef _ACTION
#define _ACTION

#include <vector>

#include "../characters/character.hpp"
#include "../collision_handlers/collision_handlers.hpp"
#include "../../utils/geometry.hpp"


class Action {

    private:
        vector<Character &> involved_characters;
        Direction direction;
        CollisionResult result;

    public:

        Action (Character & initiator, Direction direction);

        Direction get_direction () const;

        CollisionResult get_result () const;
        void set_result (CollisionResult new_result);
        
        Character & get_initiator () const;
        vector<Character &> get_involved_characters () const;
        void add_involved_character (Character & involved_character);

};


#endif