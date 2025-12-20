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

void Game::add_player(Character* player) {
    players.push_back(player);
    add_character(player);
}

void Game :: add_rule_to_history (Rule rule) {
    rules_history.insert(rule);
}

/*void Game::update() {
    // on peut ajouter une fonction de rendu graphique, rafraîchir l'écran, etc...
    std::cout << "Board mis à jour." << std::endl;
}*/

void Game::update(RuleChange event) {

    cout << "game received rule change" << endl;

    for (const LabelT& rule : event.new_rules) {

        Label subject  = get<0>(rule);
        Label property = get<2>(rule);

        cout << " + rule added: ";
        print_rules({rule});

        change_collision_handlings(
            WORDS_SUBJECTS[subject],
            COLLISION_HANDLINGS[property]
        );

        /**/if (property == Label::WORD_YOU) {
            make_player(WORDS_SUBJECTS[subject]); 
            continue;
        }
        
        rules_history.insert(rule);
    
    }

    cout << "rules are ";
    for (Rule rule: rules_history) {
        cout << get<0>(rule) << "_" << get<1>(rule) << "_" << get<2>(rule) << " ";
    }
    cout << endl;

    for (const LabelT& rule : event.old_rules) {

        if (rules_history.find(rule) != rules_history.end()) {
            Label subject  = get<0>(rule);
            Label property = get<2>(rule);

            cout << " and do contain " << get<0>(rule) << "_" << get<1>(rule) << "_" << get<2>(rule) << endl;
    
            cout << " - rule removed: ";
            print_rules({rule});
    
            if (property == Label::WORD_YOU) {
                unmake_player(WORDS_SUBJECTS[subject]); 
            }
            else {
                change_collision_handlings(
                    WORDS_SUBJECTS[subject],
                    CollisionResult::COEXISTED
                );
            }
            rules_history.erase(rule);
        }

    }

    /*bool hasYou = !players.empty();

    if (!hasYou) {
        terminate(false, "NO MORE YOU!");
        return;
    }*/

    for (Character* player : players) {
        for (Character* obj : board.at(player->get_position())) {
            if (obj->collide() == CollisionResult::AWARDED) {
                terminate(true);
                return;
            }
        }
    }
}

void Game::force_rule_initialization() {

    for (Character* c : characters) {

        // Détecter si le character est un mot 
        if (WORDS_SUBJECTS.find(c->get_label()) == WORDS_SUBJECTS.end())
            continue;

        Position original = c->get_position();

        for (Direction dir : {
                 Direction::UP,
                 Direction::DOWN,
                 Direction::LEFT,
                 Direction::RIGHT }) {

            Position next = Position::neighbor(original, dir, 1);
            if (!board.in_bounds(next)) continue;

            move_character(*c, dir);
            move_character(*c, !dir);

            return; 
        }
    }
}



void Game :: change_collision_handlings (Label label, CollisionResult collision_handling) {
    for (Character * character : characters) {
        if (character->get_label() == label && character->get_label() != Label::WORD_YOU) {
            cout << character->get_label() << " at " << character->get_position() << " now handle collisions like " << collision_handling << endl;
            character->change_collision_handling(collision_handling);
        }
    }
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

unordered_map<Label, CollisionResult> Game :: COLLISION_HANDLINGS = {
    {Label::WORD_DEFEAT, CollisionResult::DEFEATED},
    {Label::WORD_HOT, CollisionResult::DEFEATED},
    {Label::WORD_PUSH, CollisionResult::SHIFTED},
    {Label::WORD_SINK, CollisionResult::DEFEATED},
    {Label::WORD_STOP, CollisionResult::BLOCKED},
    {Label::WORD_WIN, CollisionResult::AWARDED}
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
    if (is_terminated) {
        return;
    }
    for (Character * player: players) {
        Action action {player, direction};
        _do(action);
    }
}

/*void Game :: _do (Action action) {

    Character & player = *action.get_initiator();
    vector<Character*> neighbors = board.get_neighbor(player, action.get_direction());
    if(neighbors.empty()) {
        move_character (player, action.get_direction());
        done_actions.push(action);
        return;
    }
    for (Character* neighbor_ptr : neighbors){

        Character& neighbor = *neighbor_ptr;

        CollisionResult result = neighbor.collide();
        action.set_result(result);
        
        switch (action.get_result()) {
    
            case CollisionResult::BLOCKED:
                cout << "Mouvement bloqué." << endl;
                break;
    
            case CollisionResult::SHIFTED:
                cout << "On pousse un objet." << endl;
                // Vérifier si on peut pousser la chaîne d'objets
                if (can_push(neighbor, action.get_direction())) {
                    // Pousser la chaîne d'objets du dernier voisin au premier
                    push_chain(neighbor, action.get_direction(), action);
                    move_character(player, action.get_direction());
                }
                break;
    
            case CollisionResult::COEXISTED:
                cout << "Superposition autorisée." << endl;
                move_character (player, action.get_direction());
                break;
    
            case CollisionResult::DEFEATED:
                cout << "Le joueur est mort." << endl;
                terminate(false);
                break;
    
            case CollisionResult::AWARDED:
                cout << "Victoire !" << endl;
                terminate(true);
    
                break;
        }
        done_actions.push(action);
         
    }
    
}*/

void Game::_do(Action action) {
    Character& player = *action.get_initiator();
    Direction dir = action.get_direction();

    Position target_pos = Position::neighbor(player.get_position(), dir, 1);
    if (!board.in_bounds(target_pos)) {
        cout << "Mouvement bloqué (hors limites)." << endl;
        return;
    }

    vector<Character*> target_objects = board.at(target_pos);

    if (target_objects.empty()) {
        move_character(player, dir);
        check_effects_after_move(player); 
        done_actions.push(action);
        return;
    }

    bool has_blocked = false;
    bool has_shifted = false;
    vector<Character*> pushable_objects;

    for (Character* obj : target_objects) {
        CollisionResult res = obj->collide();
        switch (res) {
            case CollisionResult::BLOCKED:
                has_blocked = true;
                break;
            case CollisionResult::SHIFTED:
                has_shifted = true;
                pushable_objects.push_back(obj);
                break;
            case CollisionResult::COEXISTED:
                break;
            case CollisionResult::DEFEATED:
            case CollisionResult::AWARDED:
                break;
        }
    }

    if (has_blocked) {
        cout << "Mouvement bloqué." << endl;
        return;
    }

    bool will_move = true;
    if (has_shifted) {
        bool can_push_all = true;
        for (Character* pushable : pushable_objects) {
            if (!can_push(*pushable, dir)) {
                can_push_all = false;
                break;
            }
        }

        if (can_push_all) {
            cout << "On pousse un objet." << endl;
            // Pousser toute la chaîne
            for (Character* pushable : pushable_objects) {
                push_chain(*pushable, dir, action);
            }
        } else {
            cout << "Mouvement bloqué (objet non poussable)." << endl;
            will_move = false;
        }
    }

    if (will_move) {
        // Cas COEXISTED ou vide ou après push : on bouge
        if (!has_shifted) {
            cout << "Superposition autorisée." << endl;
        }
        move_character(player, dir);
        check_effects_after_move(player);  // Check defeated/awarded sur la NOUVELLE position
        done_actions.push(action);
    }
}

void Game::check_effects_after_move(Character& player) {
    vector<Character*> current_objects = board.at(player.get_position());

    bool has_defeated = false;
    bool has_awarded = false;

    for (Character* obj : current_objects) {
        if (obj == &player) continue;  

        CollisionResult res = obj->collide();
        if (res == CollisionResult::DEFEATED) {
            has_defeated = true;
        } else if (res == CollisionResult::AWARDED) {
            has_awarded = true;
        }
    }

    if (has_defeated) {
        cout << "Le joueur est mort." << endl;
        terminate(false);
        return;
    }

    if (has_awarded) {
        cout << "Victoire !" << endl;
        terminate(true);
        return;
    }
}

void Game::push_chain(Character& obj, Direction dir, Action& action) {
    Position next_pos = Position::neighbor(obj.get_position(), dir, 1);
    if (!board.in_bounds(next_pos)) return;

    vector<Character*> next_cell = board.at(next_pos);

    // Pousser récursivement tout ce qui est poussable devant
    for (Character* candidate : next_cell) {
        if (candidate->collide() == CollisionResult::SHIFTED) {
            if (can_push(*candidate, dir)) {
                push_chain(*candidate, dir, action);  // pousse d'abord plus loin
            }
        }
    }

    // Maintenant on peut déplacer l'objet courant en toute sécurité
    move_character(obj, dir);
    action.add_involved_character(obj);
}

bool Game::can_push(Character& obj, Direction dir) {
    Position next_pos = Position::neighbor(obj.get_position(), dir, 1);
    if (!board.in_bounds(next_pos)) return false;

    vector<Character*> next_cell = board.at(next_pos);
    if (next_cell.empty()) return true;

    for (Character* c : next_cell) {
        if (c->collide() == CollisionResult::BLOCKED) {
            return false;
        }
    }

    for (Character* c : next_cell) {
        if (c->collide() == CollisionResult::SHIFTED) {
            if (!can_push(*c, dir)) {
                return false;
            }
        }
    }

    return true;
}

void Game :: move_character (Character & character, Direction direction) {
    board.remove_character(&character);
    character.move(direction);
    board.set(character);
}


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
            move_character(*character, direction); 
        }
    }

    done_actions.push(action); 
    
    cout << "Redo effectué : " << action.get_involved_characters().size() 
         << " caractères déplacés." << endl;

    return true;
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

    // notify(); 
}

void Game::reverseAction(const Action& action) {
    Character& c = *action.get_initiator();
    Direction dir = action.get_direction();

    Direction inverse = !dir; 
    Position old_pos = c.get_position();
    Position new_pos = old_pos;
    new_pos.shift(inverse);
    for (Character* character : action.get_involved_characters()) {
        if (character) {
            move_character(*character, inverse); 
        }
    }

    vector<Character*>& old_cell = board.get_cell(old_pos);
}



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
