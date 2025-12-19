#ifndef _LOADER
#define _LOADER

#include <string>
#include <unordered_map>

#include "board.hpp"
#include "ruler.hpp"
#include "../characters/labels.hpp"
#include "game.hpp"
#include <sstream>

using RuleT = tuple<Label, Label, Label>;

class Loader {

    private:

        static unordered_map<string, Label> LABELS;
        static unordered_map<string, CollisionResult> COLLISION_HANDLINGS;

        Board * build_board (std::istream& file);
        Label get_you (std::istream& file);
        void build_characters (std::istream& file, Game * game);
        void setup_game (Game * game, Board * board, Ruler * ruler, Label who_is_you);

    public:
        Game * load (std::string file_path);

};


#endif