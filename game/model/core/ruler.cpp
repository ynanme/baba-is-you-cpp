#include "ruler.hpp"

#include <iostream>

using namespace std;



void Ruler :: update (CharacterSet event) {

    Position event_position = event.set_character->get_position();

    cout << "ruler received notification for event at position " << event_position << endl;

    if (event.set_character->get_category() == Category::WORD) {

        cout << "found a word at said position" << endl;

        vector<LabelT> potential_new_rules = filter_on_rules(
            filter_on_phrases(
                get_cells_to_scan(
                    *event.board, get_positions_to_scan_for_rule_creation(event_position)
                )
            )
        );

        vector<LabelT> potential_old_rules = filter_on_rules(
            filter_on_phrases(
                get_cells_to_scan(
                    *event.board, get_positions_to_scan_for_rule_destruction(event_position)
                )
            )
        );

        cout << "and deduced following new rules: ";
        print_rules(potential_new_rules);
        cout << "and following old rules: ";
        print_rules(potential_old_rules);

        if (!potential_new_rules.empty() || !potential_old_rules.empty()) {
            notify({potential_new_rules, potential_old_rules});
        }

    }

}


vector<LabelT> Ruler :: filter_on_rules (vector<LabelT> filtered_phrases) {

    vector<LabelT> rules;

    for (LabelT phrase: filtered_phrases) {
        if (
            WORDS_TOKENS[get<0>(phrase)] == Token::SUBJECT &&
            WORDS_TOKENS[get<1>(phrase)] == Token::VERB &&
            WORDS_TOKENS[get<2>(phrase)] != Token::VERB
        ) {
            rules.push_back(phrase);
        }
    }
    
    return rules;
    
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


vector<PositonT> Ruler :: get_positions_to_scan_for_rule_creation (Position word_position) {
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


vector<PositonT> Ruler :: get_positions_to_scan_for_rule_destruction (Position word_position) {

    Position up_neighbor = Position::neighbor(word_position, Direction::UP, 1);
    Position right_neighbor = Position::neighbor(word_position, Direction::RIGHT, 1);
    Position down_neighbor = Position::neighbor(word_position, Direction::DOWN, 1);
    Position left_neighbor = Position::neighbor(word_position, Direction::LEFT, 1);

    return {
        {
            word_position,
            Position::neighbor(up_neighbor, Direction::RIGHT, 1),
            Position::neighbor(up_neighbor, Direction::RIGHT, 2)
        },
        {
            word_position,
            Position::neighbor(down_neighbor, Direction::RIGHT, 1),
            Position::neighbor(down_neighbor, Direction::RIGHT, 2)
        },
        {
            Position::neighbor(up_neighbor, Direction::LEFT, 1),
            word_position,
            Position::neighbor(up_neighbor, Direction::RIGHT, 1)
        },
        {
            Position::neighbor(down_neighbor, Direction::LEFT, 1),
            word_position,
            Position::neighbor(down_neighbor, Direction::RIGHT, 1)
        },
        {
            Position::neighbor(up_neighbor, Direction::LEFT, 2),
            Position::neighbor(up_neighbor, Direction::LEFT, 1),
            word_position
        },
        {
            Position::neighbor(down_neighbor, Direction::LEFT, 2),
            Position::neighbor(down_neighbor, Direction::LEFT, 1),
            word_position
        },
        {
            word_position,
            Position::neighbor(left_neighbor, Direction::DOWN, 1),
            Position::neighbor(left_neighbor, Direction::DOWN, 2)
        },
        {
            word_position,
            Position::neighbor(right_neighbor, Direction::DOWN, 1),
            Position::neighbor(right_neighbor, Direction::DOWN, 2),
        },
        {
            Position::neighbor(left_neighbor, Direction::UP, 1),
            word_position,
            Position::neighbor(left_neighbor, Direction::DOWN, 1)
        },
        {
            Position::neighbor(right_neighbor, Direction::UP, 1),
            word_position,
            Position::neighbor(right_neighbor, Direction::DOWN, 1)
        },
        {
            Position::neighbor(left_neighbor, Direction::UP, 2),
            Position::neighbor(left_neighbor, Direction::UP, 1),
            word_position
        },
        {
            Position::neighbor(right_neighbor, Direction::UP, 2),
            Position::neighbor(right_neighbor, Direction::UP, 1),
            word_position
        }
    };

}


int Ruler :: word_index (vector<Character *> cell) {
    for (size_t i = 0; i < cell.size(); i ++) {
        if (cell.at(i)->get_category() == Category::WORD) {
            return i;
        }
    }
    return -1;
}


void print_rules (vector<LabelT> rules) {
    for (LabelT rule: rules) {
        cout << get<0>(rule) << "_" << get<1>(rule) << "_" << get<2>(rule) << " ";
    }
    cout << endl;
}



unordered_map<Label, Token> Ruler :: WORDS_TOKENS = {

    {Label::WORD_BABA, Token::SUBJECT},
    {Label::WORD_FLAG, Token::SUBJECT},
    {Label::WORD_GRASS, Token::SUBJECT},
    {Label::WORD_LAVA, Token::SUBJECT},
    {Label::WORD_ROCK, Token::SUBJECT},
    {Label::WORD_SKULL, Token::SUBJECT},
    {Label::WORD_WALL, Token::SUBJECT},
    {Label::WORD_WATER, Token::SUBJECT},

    {Label::WORD_IS, Token::VERB},

    {Label::WORD_DEFEAT, Token::PROPERTY},
    {Label::WORD_HOT, Token::PROPERTY},
    {Label::WORD_PUSH, Token::PROPERTY},
    {Label::WORD_SINK, Token::PROPERTY},
    {Label::WORD_STOP, Token::PROPERTY},
    {Label::WORD_WIN, Token::PROPERTY},
    {Label::WORD_YOU, Token::PROPERTY}
    
};
