#include "ruler.hpp"


void Ruler :: update (CharacterSet event) {

    if (word_index(event.board->at(event.position)) != -1) {

        vector<LabelT> potential_rules = filter_on_rules(
            filter_on_phrases(
                get_cells_to_scan(
                    *event.board, get_positions_to_scan(event.position)
                )
            )
        );

        if (!potential_rules.empty()) {
            notify({potential_rules});
        }
        
    }

}


vector<PositonT> Ruler :: get_positions_to_scan (Position word_position) {
    return {
        {
            Position::neighbor(word_position, Direction::LEFT, 2),
            Position::neighbor(word_position, Direction::LEFT, 1),
            word_position
        },
        {
            Position::neighbor(word_position, Direction::LEFT, 1),
            word_position,
            Position::neighbor(word_position, Direction::RIGHT, 1)
        },
        {
            word_position,
            Position::neighbor(word_position, Direction::RIGHT, 1),
            Position::neighbor(word_position, Direction::RIGHT, 2)
        },
        {
            Position::neighbor(word_position, Direction::UP, 2),
            Position::neighbor(word_position, Direction::UP, 1),
            word_position
        },
        {
            Position::neighbor(word_position, Direction::UP, 1),
            word_position,
            Position::neighbor(word_position, Direction::DOWN, 1)
        },
        {
            word_position, 
            Position::neighbor(word_position, Direction::DOWN, 1),
            Position::neighbor(word_position, Direction::DOWN, 2)
        }
    };
}


vector<CellT> Ruler :: get_cells_to_scan (Board & board, vector<PositonT> scanned_positions) {

    vector<CellT> cells_to_scan;

    for (PositonT triplet : scanned_positions) {
        cells_to_scan.push_back({
            board.at(get<0>(triplet)),
            board.at(get<1>(triplet)),
            board.at(get<2>(triplet))
        });
    }

    return cells_to_scan;

}


vector<LabelT> Ruler :: filter_on_phrases (vector<CellT> scanned_cells) {

    vector<LabelT> phrases;

    for (CellT triplet : scanned_cells) {

        int first_index = word_index(get<0>(triplet));
        int second_index = word_index(get<1>(triplet));
        int third_index = word_index(get<2>(triplet));

        if (first_index != -1 && second_index != -1 && third_index != -1) {
            phrases.push_back({
                get<0>(triplet).at(first_index)->get_label(),
                get<1>(triplet).at(second_index)->get_label(),
                get<2>(triplet).at(third_index)->get_label()
            });
        }

    }

    return phrases;

}


vector<LabelT> Ruler :: filter_on_rules (vector<LabelT> filtered_phrases) {

    vector<LabelT> rules;

    for (LabelT phrase: filtered_phrases) {
        if (
            words_tokens[get<0>(phrase)] == Token::SUBJECT &&
            words_tokens[get<1>(phrase)] == Token::VERB &&
            words_tokens[get<2>(phrase)] == Token::PROPERTY
        ) {
            rules.push_back(phrase);
        }
    }
    
    return rules;
    
}


int Ruler :: word_index (vector<Character *> cell) {
    int index = -1;
    for (int i = 0; i < cell.size(); i ++) {
        if (words.find((cell.at(i)->get_label())) != words.end()) {
            index = i;
        }
    }
    return index;
}
