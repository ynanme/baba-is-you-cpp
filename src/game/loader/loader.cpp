#include <iostream>
#include <fstream>

#include "game/loader/loader.hpp"
#include "game/model/characters/character.hpp"
#include "game/utils/geometry.hpp"

using namespace std;


unordered_map<string, Label> Loader :: LABELS = {

    {"BABA", Label::BABA},
    {"DOOR", Label::DOOR},
    {"FLAG", Label::FLAG},
    {"GRASS", Label::GRASS},
    {"KEY", Label::KEY},
    {"LAVA", Label::LAVA},
    {"ROCK", Label::ROCK},
    {"SKULL", Label::SKULL},
    {"WALL", Label::WALL},
    {"WATER", Label::WATER},

    {"WORD_BABA", Label::WORD_BABA},
    {"WORD_DOOR", Label::WORD_DOOR},
    {"WORD_FLAG", Label::WORD_FLAG},
    {"WORD_GRASS", Label::WORD_GRASS},
    {"WORD_KEY", Label::WORD_KEY},
    {"WORD_LAVA", Label::WORD_LAVA},
    {"WORD_ROCK", Label::WORD_ROCK},
    {"WORD_SKULL", Label::WORD_SKULL},
    {"WORD_WALL", Label::WORD_WALL},
    {"WORD_WATER", Label::WORD_WATER},

    {"WORD_IS", Label::WORD_IS},

    {"WORD_DEFEAT", Label::WORD_DEFEAT},
    {"WORD_HOT", Label::WORD_HOT},
    {"WORD_MELT", Label::WORD_MELT},
    {"WORD_OPEN", Label::WORD_OPEN},
    {"WORD_PULL", Label::WORD_PULL},
    {"WORD_PUSH", Label::WORD_PUSH},
    {"WORD_SHUT", Label::WORD_SHUT},
    {"WORD_SINK", Label::WORD_SINK},
    {"WORD_STOP", Label::WORD_STOP},
    {"WORD_WIN", Label::WORD_WIN},
    {"WORD_YOU", Label::WORD_YOU}

};


unordered_map<string, Category> Loader :: CATEGORIES = {
    {"O", Category::OBJECT},
    {"W", Category::WORD}
};



Game* Loader::load(string file_path) const {

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


void Loader :: load_rules_and_characters(std::istream& file, Game* game) const {
    string first;
    while (file >> first) {
        if (isdigit(static_cast<unsigned char>(first[0]))) {
            int x = std::stoi(first);
            int y;
            string label, category;
            file >> y >> label >> category;
            game->add_character(new Character({x, y}, LABELS[label], CATEGORIES[category]));
        }
        else {
            string verb, property;
            file >> verb >> property;
            game->apply_rule({LABELS[first], LABELS[verb], LABELS[property]});
        }
    }
}
