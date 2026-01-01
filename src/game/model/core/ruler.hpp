#ifndef _RULER
#define _RULER

#include <vector>
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include "game/model/core/board.hpp"
#include "game/model/core/events.hpp"
#include "game/model/characters/character.hpp"
#include "game/model/characters/labels.hpp"
#include "game/utils/geometry.hpp"


enum class Token {
    SUBJECT, VERB, PROPERTY
};


using PositonT = tuple<Position, Position, Position>;
using CellT = tuple<vector<Character *>, vector<Character *>, vector<Character *>>;
using LabelT = tuple<Label, Label, Label>;

class Ruler: public Observer<CharacterSet>, public Subject<RuleChange> {

    private:

        static unordered_map<Label, Token> WORDS_TOKENS;

        vector<PositonT> get_positions_to_scan_for_rule_creation (Position word_position) const;
        vector<PositonT> get_positions_to_scan_for_rule_destruction (Position word_position) const;
        vector<CellT> get_cells_to_scan (const Board & board, const vector<PositonT> & scanned_positions) const;

        vector<LabelT> filter_on_phrases (const vector<CellT> & scanned_cells) const;
        vector<LabelT> filter_on_rules (const vector<LabelT> & filtered_phrases) const;
        
        int word_index (const vector<Character *> & cell) const;

    public:

        void update (const CharacterSet & event) override;

};


void print_rules (vector<LabelT> rules);


#endif