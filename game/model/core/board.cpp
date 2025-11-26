#include "board.hpp"
#include <iostream>

Board::Board(int width, int height)
    : width{width}, height{height} {}


int Board::get_width() const { return width; }

int Board::get_height() const { return height; }

const vector<Character*>& Board::at(const Position& pos) const {
    static const vector<Character*> empty;
    auto it = grid.find(pos);
    return (it != grid.end() ? it->second : empty);
}

vector<Character*>& Board::get_cell(const Position& pos) {
    return grid[pos]; 
}

bool Board::in_bounds(const Position& pos) const {
    return pos.get_x() >= 0 &&
           pos.get_y() >= 0 &&
           pos.get_x() < height &&
           pos.get_y() < width;
}


void Board::add_character(Character* character) {
    Position pos = character->get_position();
    get_cell(pos).push_back(character);
    notify(); 
}

void Board::remove_character(Character* character) {
    Position pos = character->get_position();
    auto& cell = get_cell(pos);

    cell.erase(std::remove(cell.begin(), cell.end(), character), cell.end());
    notify();
}

Action Board::move_character(Character& character, Direction direction) {
    Position current = character.get_position();
    Position next = current;
    next.shift(direction);

    Action action(character, direction, CollisionResult::COEXISTED);

    if (!in_bounds(next)) {
        action = Action(character, direction, CollisionResult::BLOCKED);
        return action;
    }

    auto& destination_cell = get_cell(next);

    for (Character* other : destination_cell) {
        CollisionResult result = other->collide();

        action = Action(character, direction, result);
        action.add_involved_character(*other);

        switch (result) {

            case CollisionResult::BLOCKED:
                return action;

            case CollisionResult::SHIFTED: {
                Action push = move_character(*other, direction);
                if (push.get_result() == CollisionResult::BLOCKED)
                    return action; 
                break;
            }

            case CollisionResult::DEFEATED:
                remove_character(&character);
                notify();
                return action;

            case CollisionResult::AWARDED:
                notify();
                return action;

            case CollisionResult::COEXISTED:
                break;
        }
    }

    auto& old_cell = get_cell(current);
    old_cell.erase(std::remove(old_cell.begin(), old_cell.end(), &character),
                   old_cell.end());

    character.move(direction);
    get_cell(next).push_back(&character);

    notify();
    return action;
}
