#ifndef _GEOMETRY
#define _GEOMETRY

#include <iostream>

using namespace std;


enum class Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

Direction operator ! (Direction direction);

ostream& operator << (ostream& out, Direction direction);


class Position {

    private:

        int x, y;
    
    public:

        Position (int x, int y);

        int get_x () const;
        int get_y () const;

        void shift (Direction direction);

        static Position neighbor (Position position, Direction direction, int range);

};

bool operator == (const Position& first, const Position& second);

bool operator<(const Position& first, const Position& second);

ostream& operator << (ostream& out, const Position& position);


#endif
