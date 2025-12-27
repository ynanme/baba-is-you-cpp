#include <iostream>
#include <fstream>

#include "loader.hpp"
#include "../characters/character.hpp"
#include "../../utils/geometry.hpp"

using namespace std;


unordered_map<string, Label> Loader :: LABELS = {

    {"BABA", Label::BABA},
    {"FLAG", Label::FLAG},
    {"GRASS", Label::GRASS},
    {"LAVA", Label::LAVA},
    {"ROCK", Label::ROCK},
    {"SKULL", Label::SKULL},
    {"WALL", Label::WALL},
    {"WATER", Label::WATER},

    {"WORD_BABA", Label::WORD_BABA},
    {"WORD_FLAG", Label::WORD_FLAG},
    {"WORD_GRASS", Label::WORD_GRASS},
    {"WORD_LAVA", Label::WORD_LAVA},
    {"WORD_ROCK", Label::WORD_ROCK},
    {"WORD_SKULL", Label::WORD_SKULL},
    {"WORD_WALL", Label::WORD_WALL},
    {"WORD_WATER", Label::WORD_WATER},

    {"WORD_IS", Label::WORD_IS},

    {"WORD_DEFEAT", Label::WORD_DEFEAT},
    {"WORD_HOT", Label::WORD_HOT},
    {"WORD_MELT", Label::WORD_MELT},
    {"WORD_PUSH", Label::WORD_PUSH},
    {"WORD_SINK", Label::WORD_SINK},
    {"WORD_STOP", Label::WORD_STOP},
    {"WORD_WIN", Label::WORD_WIN},
    {"WORD_YOU", Label::WORD_YOU}

};


unordered_map<string, Category> Loader :: CATEGORIES = {
    {"O", Category::OBJECT},
    {"W", Category::WORD}
};



Game* Loader::load(string file_path) {

    ifstream file(file_path);
    if (!file.is_open()) {
        throw runtime_error("Unfound path: " + file_path);
    }

    int width, height;
    file >> width >> height;

    Game* game = new Game(width, height);

    load_rules_and_characters(file, game);
    
    return game;

}


void Loader :: load_rules_and_characters(std::istream& file, Game* game) {
    string first;
    while (file >> first) {
        if (isdigit(first[0])) {
            int x = std::stoi(first);
            int y;
            string label, category;
            file >> y >> label >> category;
            cout << x << " " << y << " " << label << " " << category << endl;
            game->add_character(new Character({x, y}, LABELS[label], CATEGORIES[category]));
        }
        else {
            string verb, property;
            file >> verb >> property;
            cout << first << " " << verb << " " << property << endl;
            game->apply_rule({LABELS[first], LABELS[verb], LABELS[property]});
        }
    }
}
