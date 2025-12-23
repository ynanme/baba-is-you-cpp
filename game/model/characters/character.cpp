#include "character.hpp"


Character :: Character (Position position, Label label, Category category):
position {position},
label {label}, 
category {category} {}


Position Character :: get_position () const {
    return position;
}

Label Character :: get_label () const {
    return label;
}

Category Character :: get_category () const {
    return category;
}


void Character :: move (Direction direction) {
    position.shift(direction);
}



ostream& operator << (ostream& out, const Character& character) {
    out << character.label << " at " << character.position;
    return out;
}
