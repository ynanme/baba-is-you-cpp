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

    private:

        unordered_set<Label> words;
        unordered_map<Label, Token> words_tokens;

        vector<PositonT> get_positions_to_scan (Position word_position);
        vector<CellT> get_cells_to_scan (Board & board, vector<PositonT> scanned_positions);

        vector<LabelT> filter_on_phrases (vector<CellT> scanned_cells);
        vector<LabelT> filter_on_rules (vector<LabelT> filtered_phrases);
        
        int word_index (vector<Character *> cell);

    public:

        void update (CharacterSet event);

        void notify (RuleChange event);

};


#endif