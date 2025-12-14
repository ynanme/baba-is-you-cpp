#ifndef _RULER
#define _RULER

#include <vector>
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include "board.hpp"
#include "events.hpp"
#include "../characters/character.hpp"
#include "../characters/labels.hpp"
#include "../../utils/geometry.hpp"


enum class Token {
    SUBJECT, VERB, PROPERTY
};


using PositonT = tuple<Position, Position, Position>;
using CellT = tuple<vector<Character *>, vector<Character *>, vector<Character *>>;
using LabelT = tuple<Label, Label, Label>;

class Ruler: public Observer<CharacterSet>, public Subject<RuleChange> {

    struct RuleHash {
        std::size_t operator()(LabelT const& rule) const noexcept {
            std::size_t h1 = std::hash<int>{}(static_cast<int>(std::get<0>(rule)));
            std::size_t h2 = std::hash<int>{}(static_cast<int>(std::get<1>(rule)));
            std::size_t h3 = std::hash<int>{}(static_cast<int>(std::get<2>(rule)));

            // Combinaison classique de hash (boost-style)
            std::size_t seed = h1;
            seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= h3 + 0x9e3779b9 + (seed << 6) + (seed >> 2);

            return seed;
        }
    };


    private:

        static unordered_set<Label> WORDS;
        static unordered_map<Label, Token> WORDS_TOKENS;

        unordered_set<LabelT, RuleHash> active_rules;


        vector<PositonT> get_positions_to_scan_for_rule_creation (Position word_position);
        vector<PositonT> get_positions_to_scan_for_rule_destruction (Position word_position);
        vector<CellT> get_cells_to_scan (Board & board, vector<PositonT> scanned_positions);
        vector<PositonT> get_all_rule_positions(Board& board);

        vector<LabelT> filter_on_phrases (vector<CellT> scanned_cells);
        vector<LabelT> filter_on_rules (vector<LabelT> filtered_phrases);
        
        int word_index (vector<Character *> cell);

    public:

        void update (CharacterSet event);

};


void print_rules (vector<LabelT> rules);


#endif