#ifndef _ACTION
#define _ACTION

#include <vector>

#include "game/model/characters/character.hpp"
#include "game/utils/geometry.hpp"


class Action {

    private:
        std::vector<Character *> moved_characters;
        std::vector<Character *> destroyed_characters;
        Direction direction;

    public:

        Action (Direction direction);

        Direction get_direction () const;
        const std::vector<Character *> & get_moved_characters () const;
        const std::vector<Character *> & get_destroyed_characters () const;

        void add_moved_character (Character * moved_character);
        void add_destroyed_character (Character * destroyed_character);

};


#endif