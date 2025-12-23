#include "game.hpp"
#include "ruler.hpp"
#include <iostream>

Game::Game(Board& board)
    : board(board)
{}

Board& Game::get_board() const { return board; }

void Game::add_character(Character* character) {
    characters.push_back(character);
    board.add_character(character);
}



void Game :: update (RuleChange event) {
    for (Rule new_rule: event.new_rules) {
        apply_rule(new_rule);
    }
    for (Rule old_rule: event.old_rules) {
        if (rules_history.find(old_rule) != rules_history.end())
            unapply_rule(old_rule);
    }
}

void Game :: apply_rule (Rule rule) {
    add_property(WORDS_SUBJECTS[get<0>(rule)], WORDS_PROPERTIES[get<2>(rule)]);
    rules_history.insert(rule);
}

void Game :: unapply_rule (Rule rule) {
    remove_property(WORDS_SUBJECTS[get<0>(rule)], WORDS_PROPERTIES[get<2>(rule)]);
    rules_history.erase(rule);
}

void Game :: add_property (Label label, Property property) {
    properties[label].insert(property);
    if (property == Property::YOU) make_player(label);
}

void Game :: remove_property (Label label, Property property) {
    properties[label].erase(property);
    if (property == Property::YOU) unmake_player(label);
}

void Game :: make_player (Label label) {
    for (Character * character : characters) {
        if (character->get_label() == label) {
            cout << character->get_label() << " at " << character->get_position() << " became player" << endl;
            players.push_back(character);
        }
    }
}

void Game :: unmake_player (Label label) {
    for (Character * character : characters) {
        if (character->get_label() == label) {
            cout << character->get_label() << " at " << character->get_position() << " is no longer player" << endl;
            players.erase(remove(players.begin(), players.end(), character), players.end());
        }
    }
}

unordered_map<Label, Property> Game :: WORDS_PROPERTIES = {
    {Label::WORD_DEFEAT, Property::DEFEAT},
    {Label::WORD_HOT, Property::HOT},
    {Label::WORD_MELT, Property::MELT},
    {Label::WORD_PUSH, Property::PUSH},
    {Label::WORD_SINK, Property::SINK},
    {Label::WORD_STOP, Property::STOP},
    {Label::WORD_WIN, Property::WIN},
    {Label::WORD_YOU, Property::YOU}
};

unordered_map<Label, Label> Game :: WORDS_SUBJECTS = {
    {Label::WORD_BABA, Label::BABA},
    {Label::WORD_FLAG, Label::FLAG},
    {Label::WORD_GRASS, Label::GRASS},
    {Label::WORD_LAVA, Label::LAVA},
    {Label::WORD_ROCK, Label::ROCK},
    {Label::WORD_SKULL, Label::SKULL},
    {Label::WORD_WALL, Label::WALL},
    {Label::WORD_WATER, Label::WATER}
};


void Game :: play (Direction direction) {
    cout << "---------------------------------------------------------------" << endl;
    for (Character * player: players) {
        cout << "playing with " << *player << " towards " << direction << endl;
        move(player, direction);
    }
    cout << "---------------------------------------------------------------" << endl;
}


void Game :: move (Character * player, Direction direction) {
    Position destination = Position::neighbor(player->get_position(), direction);
    int chain_range = pushes_chain_range(destination, direction);
    cout << "chain range is " << chain_range << endl;
    if (chain_range >= 0) {
        launch_pushes(player->get_position(), direction, chain_range);
        move_character(player, direction);
    }
}

void Game :: launch_pushes (Position start, Direction direction, int range) {
    cout << "pushes launched from " << start << " towards " << direction << ", range " << range << endl;
    Position end = Position::neighbor(start, direction, range);
    while (end != start) {
        move_characters(end, direction);
        end.shift(!direction);
    }
}

bool Game :: has_property (Character * character, Property property) {
    if (character->get_category() == Category::WORD) return property == Property::PUSH;
    Label label = character->get_label();
    return
        properties.find(label) != properties.end() &&
        properties[label].find(property) != properties[label].end()
    ;
}

bool Game :: has_no_property (Label label) {
    return
        properties.find(label) == properties.end() ||
        properties[label].empty()
    ;
}

bool Game :: is_open (Position position) {
    for (Character * character: board.at(position)) {
        if (has_property(character, Property::STOP)) {
            return false;
        }
    }
    return true;
}

bool Game :: is_subject_to_push (Position position) {
    for (Character * character: board.at(position)) {
        if (has_property(character, Property::PUSH)) {
            return true;
        }
    }
    return false;
}

int Game :: pushes_chain_range (Position start, Direction direction) {
    int range = 0;
    while (board.in_bounds(start)) {
        if (!is_open(start)) return -1;
        if (is_subject_to_push(start)) {
            range ++;
            start.shift(direction);
        } else break;
    }
    if (!board.in_bounds(start)) return -1;
    return range;
}

void Game :: move_characters (Position position, Direction direction) {
    for (Character * character: board.at(position)) {
        if (has_property(character, Property::PUSH)) {
            move_character(character, direction);
        }
    }
}

CoexistionResult Game :: get_coexistion_result (Character * visitor, Character * host) {
    if (has_property(visitor, Property::YOU) && has_property(host, Property::WIN)) {
        return CoexistionResult::WON;
    }
    if (has_property(visitor, Property::YOU) && has_property(host, Property::DEFEAT)) {
        return CoexistionResult::DEFEATED;
    }
    if (has_property(visitor, Property::MELT) && has_property(host, Property::HOT)) {
        return CoexistionResult::MELTED;
    }
    if (has_property(visitor, Property::SINK) || has_property(host, Property::SINK)) {
        return CoexistionResult::SINKED;
    }
    return CoexistionResult::COEXISTED;
}

CoexistionResult Game :: get_prioritary_coexistion_result (Character * visitor, Position hosts_position) {
    CoexistionResult final_result = CoexistionResult::COEXISTED;
    for (Character * host: board.at(hosts_position)) {
        CoexistionResult host_result = get_coexistion_result(visitor, host);
        if (host_result > final_result) final_result = host_result;
    }
    return final_result;
}



void Game :: move_character (Character * character, Direction direction) {
    cout << "moving " << *character << " towards " << direction << endl;
    board.remove_character(character);
    character->move(direction);    
    switch (get_prioritary_coexistion_result(character, character->get_position())) {
        case CoexistionResult::WON:
            cout << "chosen collision is WON" << endl;
            board.set(*character);
            terminate(true);
            break;
        case CoexistionResult::DEFEATED: // || CoexistionResult::MELTED
            cout << "chosen collision is DEFEATED or MELTED" << endl;
            terminate(false);
            break;
        case CoexistionResult::SINKED:
            cout << "chosen collision is SINKED" << endl;
            board.unset(character->get_position());
            if (has_property(character, Property::YOU)) terminate(false);
            break;
        case CoexistionResult::COEXISTED:
            cout << "chosen collision is COEXISTED" << endl;
            board.set(*character);
            break;
    }
}

/*
bool Game::undo() {
    if (done_actions.empty()) {
        cout << "Rien à undo." << endl;
        return false;
    }

    Action action = done_actions.top();
    done_actions.pop();

    // Appliquer l’inverse
    reverseAction(action);

    // Ajouter à la pile des redo
    redone_actions.push(action);

    return true;
}


bool Game::redo() {
    if (redone_actions.empty()) {
        cout << "Rien à redo." << endl;
        return false;
    }

    Action action = redone_actions.top();
    redone_actions.pop();
    
    Direction direction = action.get_direction();

    for (Character* character : action.get_involved_characters()) {
        if (character) {
            move_character(character, direction); 
        }
    }

    done_actions.push(action); 
    
    cout << "Redo effectué : " << action.get_involved_characters().size() 
         << " caractères déplacés." << endl;

    return true;
}*/

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

    // notify(); 
}

/*void Game::reverseAction(const Action& action) {
    Character& c = *action.get_initiator();
    Direction dir = action.get_direction();

    Direction inverse = !dir; 
    Position old_pos = c.get_position();
    Position new_pos = old_pos;
    new_pos.shift(inverse);
    for (Character* character : action.get_involved_characters()) {
        if (character) {
            move_character(character, inverse); 
        }
    }

    vector<Character*>& old_cell = board.get_cell(old_pos);
}
*/


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
