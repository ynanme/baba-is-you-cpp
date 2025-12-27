#ifndef _LOADER
#define _LOADER

#include <string>
#include <unordered_map>

#include "board.hpp"
#include "ruler.hpp"
#include "../characters/labels.hpp"
#include "game.hpp"
#include <sstream>


class Loader {

    private:

        static unordered_map<string, Label> LABELS;
        static unordered_map<string, Category> CATEGORIES;

        void load_rules_and_characters (std::istream& file, Game * game);

    public:
    
        Game * load (std::string file_path);

};


#endif