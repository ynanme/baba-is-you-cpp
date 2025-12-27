#ifndef _CHARACTER
#define _CHARACTER

#include "labels.hpp"
#include "../../utils/geometry.hpp"


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


    friend std::ostream& operator << (ostream& out, const Character& character);

};



ostream& operator << (ostream& out, const Character& character);


#endif