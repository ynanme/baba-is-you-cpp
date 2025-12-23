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

    Board* board = build_board(file);
    Game* game = new Game(*board);
    Ruler* ruler = new Ruler();

    Label who_is_you = get_you(file);

    build_rules_and_characters(file, game);


    setup_game(game, board, ruler, who_is_you);
    
    return game;
}

Board * Loader :: build_board (istream& file) {
    int width, height;
    file >> width >> height;
    return new Board(width, height);
}

Label Loader :: get_you (istream& file) {
    string you;
    file >> you;
    return LABELS[you];
}


void Loader :: build_rules (istream& file, Game * game) {
    cout << "rules" << endl;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string subject, verb, property;
        if (!(iss >> subject >> verb >> property)) {
            string subject, verb, property;
            cout << subject << " " << verb << " " << property << endl;
            game->apply_rule({LABELS[subject], LABELS[verb], LABELS[property]});
        }
    }
}

void Loader :: build_characters (istream& file, Game * game) {
    int x, y;
    string label, collision;
    cout << "characters" << endl;
    while (file >> x >> y >> label >> collision) {
        cout << x << " " << y << " " << label << " " << collision << endl;
    }
}

void Loader::build_rules_and_characters(std::istream& file, Game* game) {
    string first;
    while (file >> first) {
        if (isdigit(first[0])) {
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

void Loader :: setup_game (Game * game, Board * board, Ruler * ruler, Label who_is_you) {
    board->attach(ruler);
    ruler->attach(game);
    game->make_player(who_is_you);
}
