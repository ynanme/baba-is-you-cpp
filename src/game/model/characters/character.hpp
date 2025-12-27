#ifndef _CHARACTER
#define _CHARACTER

#include "game/model/characters/labels.hpp"
#include "game/utils/geometry.hpp"


class Character {

    private:
    
        Position position;
        Label label;
        Category category;

    public:

        Character (Position position, Label label, Category category);

        Position get_position () const;
        Label get_label () const;
        Category get_category () const;

        void move (Direction direction);


    friend std::ostream& operator << (std::ostream& out, const Character& character);

};



std::ostream& operator << (std::ostream& out, const Character& character);


#endif