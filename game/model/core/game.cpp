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
    
    }

    for (const LabelT& rule : event.old_rules) {

        Label subject  = get<0>(rule);
        Label property = get<2>(rule);

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
    }

    bool hasYou = !players.empty();

    if (!hasYou) {
        terminate(false, "NO MORE YOU!");
        return;
    }

    for (Character* player : players) {
        for (Character* obj : board.at(player->get_position())) {
            if (obj->collide() == CollisionResult::AWARDED) {
                terminate(true);
                return;
            }
        }
    }
}


void Game :: change_collision_handlings (Label label, CollisionResult collision_handling) {
    for (Character * character : characters) {
        if (character->get_label() == label) {
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

void Game :: _do (Action action) {

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
    
            // Je pense qu'on doit supprimer ce cas car le if au-dessus le gère déjà
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
    
}

/*void Game :: chain_move (vector<Character*> neighbors, Action action) {
    for(Character * neighbor : neighbors){
        Character& neighbor_ref = *neighbor;
        apply_chain(neighbor_ref, action);
    }
    
}

void apply_chain(Character& neighbor, Action action){
    //if (neighbor != nullptr && neighbor.collide() != CollisionResult::BLOCKED) {
    move_character(neighbor, action.get_direction());
    action.add_impacted_character(neighbor);
    vector<Character*>& neighbors = board.get_neighbor(neighbor, action.get_direction());
    chain_move(neighbors, action);
    //}
}*/

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
    if (!board.in_bounds(next_pos)) {
        return false;                            
    }

    vector<Character*> next_cell = board.at(next_pos);

    // Si la case devant est vide, alors on peut pousser
    if (next_cell.empty()) {
        return true;
    }

    // Sinon, on regarde tous les objets dans la case devant
    for (Character* candidate : next_cell) {
        if (candidate->collide() == CollisionResult::SHIFTED) {
            // S'il y en a au moins un qui est poussable ET qu'on peut le pousser lui-meme
            if (can_push(*candidate, dir)) {
                return true;
            }
        }
    }

    // Aucun objet poussable dans la case devant, alors bloqué
    return false;
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

    // Rejouer exactement la même action
    Character& c = *action.get_initiator();

    if (action.get_result() == CollisionResult::SHIFTED) {
        for (Character* neighbor : board.get_neighbor(c, action.get_direction())) {
            if (neighbor->collide() == CollisionResult::SHIFTED) {
                _do(Action(neighbor, action.get_direction()));        
            }
        }
    } 

    move_character(c, action.get_direction());

    // La remettre dans done_actions
    done_actions.push(action);

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

    if(action.get_result() == CollisionResult::SHIFTED) {
        for (Character* neighbor : board.get_neighbor(c, dir)) {
            if (neighbor->collide() == CollisionResult::SHIFTED) {
                Action action_neighbor = Action(neighbor, dir);
                reverseAction(action_neighbor);        
            }
        }
    }

    Direction inverse = !dir; 
    Position old_pos = c.get_position();
    Position new_pos = old_pos;
    new_pos.shift(inverse);

    vector<Character*>& old_cell = board.get_cell(old_pos);
    old_cell.erase(
        std::remove(old_cell.begin(), old_cell.end(), &c),
        old_cell.end()
    );

    vector<Character*>& new_cell = board.get_cell(new_pos);
    new_cell.push_back(&c);

    move_character(c, inverse);

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
    return out;
}
