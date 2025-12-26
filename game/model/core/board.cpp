#include "board.hpp"
#include <iostream>

Character Board::NONE_CHARACTER(Position(-1, -1), Label::NONE, Category::OBJECT);
const std::vector<Character*> Board::NONE_VECTOR = {
    &Board::NONE_CHARACTER
};

Board::Board(int width, int height)
    : width{width}, height{height} {}


int Board::get_width() const { return width; }

int Board::get_height() const { return height; }

const vector<Character*>& Board::at(const Position& pos) const {
    static const vector<Character*> empty;  
    map<Position, vector<Character*>>::const_iterator it = grid.find(pos);
    if (it != grid.end()) {
        return it->second;  
    }
    return empty;  
}

vector<Character*>& Board::get_cell(const Position& pos) {
    return grid[pos]; 
}

const vector<Character*>& Board::get_neighbor(Character& character, Direction direction) {
    Position pos = character.get_position();
    pos.shift(direction);

    if (!in_bounds(pos)) {
        return NONE_VECTOR;
    }

    const vector<Character*>& cell = at(pos);

    return cell; 
}

void Board::set(Character& character) {
    Position pos = character.get_position();
    vector<Character*>& cell = get_cell(pos);

    if (std::find(cell.begin(), cell.end(), &character) == cell.end()) {
        cell.push_back(&character);
        notify({*this, character}); 
    }
}


bool Board::in_bounds(const Position& pos) const {
    return pos.get_x() >= 0 &&
           pos.get_y() >= 0 &&
           pos.get_x() < width &&
           pos.get_y() < height;
}


void Board::add_character(Character* character) {
    Position pos = character->get_position();
    if(!in_bounds(pos)) {
        throw std::out_of_range("Position hors des limites du plateau. " + std::to_string(pos.get_x()) + ", " + std::to_string(pos.get_y()));
    }
    get_cell(pos).push_back(character);
    notify({*this, *character}); 
}

void Board::remove_character(Character* character) {
    Position pos = character->get_position();
    vector<Character*>& cell = get_cell(pos);

    cell.erase(std::remove(cell.begin(), cell.end(), character), cell.end());
    notify({*this, *character}); 
}



ostream& operator << (ostream& out, const Board& board) {
    out << "Board(" << board.width << ", " << board.height << ")";
    return out;
}
