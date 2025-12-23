#ifndef _ACTION
#define _ACTION

#include <vector>

#include "../characters/character.hpp"
#include "../../utils/geometry.hpp"


class Action {

    private:
        vector<Character *> involved_characters;
        Direction direction;

    public:

        Action (Character * initiator, Direction direction);

        Direction get_direction () const;

        Character * get_initiator () const;
        vector<Character *> get_involved_characters () const;
        void add_involved_character (Character & involved_character);

};


#endif