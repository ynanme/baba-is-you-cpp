#include "game.hpp"
#include <iostream>

Game::Game(Board& board)
    : board(board)
{
    board.attach(this);
}

void Game::add_character(Character* character) {
    characters.push_back(character);
    board.add_character(character);
}

void Game::update() {
    // on peut ajouter une fonction de rendu graphique, rafraîchir l'écran, etc...
    std::cout << "Board mis à jour." << std::endl;
}


Action Game::computeNextAction(Character& player, Direction direction) {

    if (!is_you(player)) {
        std::cout << "Ce character ne peut pas bouger (pas YOU)." << std::endl;
        return Action(player, direction, CollisionResult::BLOCKED);
    }

    // board de tenter de se déplacer
    Action action = board.move_character(player, direction);

    switch (action.get_result()) {

        case CollisionResult::BLOCKED:
            std::cout << "Mouvement bloqué." << std::endl;
            break;

        case CollisionResult::SHIFTED:
            std::cout << "On pousse un objet." << std::endl;
            break;

        case CollisionResult::COEXISTED:
            std::cout << "Superposition autorisée." << std::endl;
            break;

        case CollisionResult::DEFEATED:
            std::cout << "Le joueur est mort." << std::endl;
            break;

        case CollisionResult::AWARDED:
            std::cout << "Victoire !" << std::endl;
            break;
    }

    actions.push_back(action);
    done_actions.push(action);

    return action;
}

// ??????????????????????????????????????????????????????
bool Game::is_you(const Character& character) const {
    return character.get_label() == Label::BABA; 
}

bool Game::undo() {
    if (done_actions.empty()) {
        std::cout << "Rien à undo." << std::endl;
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
        std::cout << "Rien à redo." << std::endl;
        return false;
    }

    Action action = redone_actions.top();
    redone_actions.pop();

    // Rejouer exactement la même action
    Character& c = action.get_initiator();
    board.move_character(c, action.get_direction());

    // La remettre dans done_actions
    done_actions.push(action);

    return true;
}


void Game::reverseAction(const Action& action) {
    Character& c = action.get_initiator();
    Direction dir = action.get_direction();

    Direction inverse = !dir; 

    Position old_pos = c.get_position();
    Position new_pos = old_pos;
    new_pos.shift(inverse);

    auto& old_cell = board.get_cell(old_pos);
    old_cell.erase(
        std::remove(old_cell.begin(), old_cell.end(), &c),
        old_cell.end()
    );

    auto& new_cell = board.get_cell(new_pos);
    new_cell.push_back(&c);

    c.move(inverse);

    board.notify();
}
