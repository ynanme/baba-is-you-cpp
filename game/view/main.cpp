#include "../model/core/board.hpp"
#include "../model/core/game.hpp"
#include "../model/core/ruler.hpp"
#include "../model/characters/character.hpp"
#include "../utils/geometry.hpp"
#include "board_view.hpp"
#include "../model/core/loader.hpp"

#include <iostream>

int main() {

    Loader loader;
    Game * game=loader.load("../../res/levels/ruler_demo_1.txt");

    cout << *game << endl;

    BoardView view(game->get_board(), *game);

    while (view.isOpen()) {
        view.processEvents();
        view.render();
    }

    return 0;
}
