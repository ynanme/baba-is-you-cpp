#ifndef _CHARACTER
#define _CHARACTER

#include "labels.hpp"
#include "../../utils/geometry.hpp"

enum class CollisionResult {
    BLOCKED,
    SHIFTED,
    COEXISTED,
    DEFEATED,
    AWARDED
};


class Character {

    private:
    
        Position position;
        CollisionResult collision_result;
        Label label;

    public:

        Character (Position position, CollisionResult collision_result, Label label);

        Position get_position () const;
        Label get_label () const;

        void move (Direction direction);

        CollisionResult collide ();
        void change_collision_handling (CollisionResult new_collision_result);


    friend std::ostream& operator << (ostream& out, const Character& character);

};



ostream& operator << (ostream& out, const Character& character);
ostream& operator << (ostream& out, CollisionResult collision_handling);


#endif