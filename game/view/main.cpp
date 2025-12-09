#include "../model/core/board.hpp"
#include "../model/core/game.hpp"
#include "../model/core/ruler.hpp"
#include "../model/characters/character.hpp"
#include "../utils/geometry.hpp"
#include "board_view.hpp"
#include "../model/core/loader.hpp"

#include <iostream>

int main() {
    /*Board board(12, 7);   

    Game game(board);

    Character* baba = new Character(Position(1, 1), CollisionResult::COEXISTED, Label::BABA);
    Character* word_baba = new Character(Position(5, 5), CollisionResult::SHIFTED, Label::WORD_BABA);

    Character* rock = new Character(Position(6, 5), CollisionResult::BLOCKED, Label::ROCK);
    Character* flag = new Character(Position(10, 5), CollisionResult::AWARDED, Label::FLAG);
    Character* skull = new Character(Position(0, 5), CollisionResult::DEFEATED, Label::SKULL);

    game.add_player(baba);

    game.add_character(word_baba);
    game.add_character(rock);
    game.add_character(flag);
    game.add_character(skull);*/

    Loader loader;
    Game * game=loader.load("../../res/levels/1.txt");

    cout << *game << endl;

    BoardView view(game->get_board(), *game);

    while (view.isOpen()) {
        view.processEvents();
        view.render();
    }

    return 0;
}
