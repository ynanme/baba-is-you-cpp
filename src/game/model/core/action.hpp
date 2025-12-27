#ifndef _ACTION
#define _ACTION

#include <vector>

#include "../characters/character.hpp"
#include "../../utils/geometry.hpp"


class Action {

    private:
        vector<Character *> moved_characters;
        vector<Character *> destroyed_characters;
        Direction direction;

    public:

        Action (Direction direction);

        Direction get_direction () const;
        vector<Character *> get_moved_characters () const;
        vector<Character *> get_destroyed_characters () const;

        void add_moved_character (Character * moved_character);
        void add_destroyed_character (Character * destroyed_character);

};


#endif