#include "game/model/core/game.hpp"
#include "game/model/core/ruler.hpp"
#include <iostream>



Game :: Game (int board_width, int board_height):
board {new Board(board_width, board_height)},
ruler {new Ruler()}
{
    board->attach(ruler);
    ruler->attach(this);
}


Game :: ~ Game () {
    for (Character * character: characters) delete character;
    clear_actions(done_actions);
    clear_actions(undone_actions);
    delete ruler;
    delete board;
}


void Game :: clear_actions (stack<Action *> & actions) {
    while (!actions.empty()) {
        delete actions.top();
        actions.pop();
    }
}


Board& Game::get_board() const { return *board; }


void Game::add_character(Character* character) {
    characters.push_back(character);
    board->set(character, false);
}


bool Game :: has_property (Label label, Property property) {
    return
        properties.find(label) != properties.end() &&
        properties[label].find(property) != properties[label].end()
    ;
}


bool Game :: has_property (Character * character, Property property) {
    if (character->get_category() == Category::WORD)
        return property == Property::PUSH || property == Property::PULL;
    return has_property(character->get_label(), property);
}


bool Game :: has_property (Position position, Property property) {
    for (Character * character: board->at(position)) {
        if (has_property(character, property)) {
            return true;
        }
    }
    return false;
}


bool Game :: has_property_but (Character * character, Property property, Property but) {
    return has_property(character, property) && !has_property(character, but);
}


bool Game :: has_property_but (Position position, Property property, Property but) {
    for (Character * character: board->at(position)) {
        if (has_property_but(character, property, but)) {
            return true;
        }
    }
    return false;
}


void Game::terminate(bool win, const string& message) {
    if (is_terminated) {
        return; 
    }

    is_terminated = true;
    has_won = win;

    if (message.empty()) {
        end_message = win ? "YOU WIN !" : "Maybe next time...";
    } else {
        end_message = message;
    }

}


bool Game :: ended() const noexcept {
    return is_terminated; 
}

bool Game :: is_victory() const noexcept {
    return is_terminated && has_won;
}

bool Game :: is_defeat() const noexcept {
    return is_terminated && !has_won;
}




unordered_map<Label, Property> Game :: WORDS_PROPERTIES = {
    {Label::WORD_DEFEAT, Property::DEFEAT},
    {Label::WORD_HOT, Property::HOT},
    {Label::WORD_MELT, Property::MELT},
    {Label::WORD_OPEN, Property::OPEN},
    {Label::WORD_PULL, Property::PULL},
    {Label::WORD_PUSH, Property::PUSH},
    {Label::WORD_SHUT, Property::SHUT},
    {Label::WORD_SINK, Property::SINK},
    {Label::WORD_STOP, Property::STOP},
    {Label::WORD_WIN, Property::WIN},
    {Label::WORD_YOU, Property::YOU}
};


unordered_map<Label, Label> Game :: WORDS_SUBJECTS = {
    {Label::WORD_BABA, Label::BABA},
    {Label::WORD_DOOR, Label::DOOR},
    {Label::WORD_FLAG, Label::FLAG},
    {Label::WORD_KEY, Label::KEY},
    {Label::WORD_GRASS, Label::GRASS},
    {Label::WORD_LAVA, Label::LAVA},
    {Label::WORD_ROCK, Label::ROCK},
    {Label::WORD_SKULL, Label::SKULL},
    {Label::WORD_WALL, Label::WALL},
    {Label::WORD_WATER, Label::WATER}
};


unordered_map<CoexistionResult, int>  Game :: COEXISTION_RESULTS_PRIORITIES = {
    {CoexistionResult::COEXISTED, 4},
    {CoexistionResult::DEFEATED, 1},
    {CoexistionResult::MELTED, 1},
    {CoexistionResult::OPENED, 3},
    {CoexistionResult::SINKED, 0},
    {CoexistionResult::WON, 2}
};




ostream& operator << (ostream& out, const Game& game) {
    out << "Game has " << game.board << " and following characters:" << endl;
    for (Character * character: game.characters) {
        out << *character;
        if (find(game.players.begin(), game.players.end(), character) != game.players.end()) {
            out << " IS YOU";
        }
        out << endl;
    }
    for (Rule rule: game.rules_history) {
        cout << get<0>(rule) << "_" << get<1>(rule) << "_" << get<2>(rule) << " ";
    }
    cout << endl;
    return out;
}
