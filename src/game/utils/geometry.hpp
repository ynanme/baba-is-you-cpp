#ifndef _GEOMETRY
#define _GEOMETRY

#include <iostream>


enum class Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

Direction operator ! (Direction direction);

std::ostream& operator << (std::ostream& out, Direction direction);


class Position {

    private:

        int x, y;
    
    public:

        Position (int x, int y);

        int get_x () const;
        int get_y () const;

        void shift (Direction direction);

        static Position neighbor (Position position, Direction direction, int range = 1);

};

bool operator == (const Position& first, const Position& second);

bool operator != (const Position& first, const Position& second);

bool operator<(const Position& first, const Position& second);

std::ostream& operator << (std::ostream& out, const Position& position);


#endif
