#include "geometry.hpp"


Position :: Position (int x, int y): x {x}, y {y} {}


int Position :: get_x () const {
    return x;
}

int Position :: get_y () const {
    return y;
}


void Position :: shift (Direction direction) {
    switch (direction) {
        case Direction::UP:
            -- x;
            break;
        case Direction::RIGHT:
            ++ y;
            break;
        case Direction::DOWN:
            ++ x;
            break;
        case Direction::LEFT:
            -- y;
            break;
    }
}

Position Position :: neighbor (Position position, Direction direction, int range) {
    Position neighbor {position.get_x(), position.get_y()};
    for (int i = 1; i <= range; i ++) {
        neighbor.shift(direction);
    }
    return neighbor;
}


bool operator == (const Position& first, const Position& second) {
    return first.get_x() == second.get_x() && first.get_y() == second.get_y();
}

ostream& operator << (ostream& out, const Position& position) {
    out << "(" << position.get_x() << ", " << position.get_y() << ")";
    return out;
}

bool operator<(const Position& first, const Position& second) {
    if (first.get_x() != second.get_x()) return first.get_x() < second.get_x();
    return first.get_y() < second.get_y();
}



Direction operator ! (Direction direction) {
    switch (direction) {
        case Direction::UP:
            return Direction::DOWN;
        case Direction::RIGHT:
            return Direction::LEFT;
        case Direction::DOWN:
            return Direction::UP;
        default:
            return Direction::RIGHT;
    }
}

ostream& operator << (ostream& out, Direction direction) {
    switch (direction) {
        case Direction::UP:
            return out << "UP";
        case Direction::RIGHT:
            return out << "RIGHT";
        case Direction::DOWN:
            return out << "DOWN";
        case Direction::LEFT:
            return out << "LEFT";
    }
    return out;
}
