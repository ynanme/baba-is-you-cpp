#include <SFML/Graphics.hpp>
#include "../model/core/board.hpp"
#include "../model/core/game.hpp"
#include "../model/core/loader.hpp"
#include "../model/core/game.hpp"
#include "board_view.hpp"
#include "menu.hpp"

int main() {

    Loader loader;
    Menu menu;

    std::vector<std::string> levels;
    levels.push_back("../../res/levels/4.txt");
    levels.push_back("../../res/levels/6.txt");
    levels.push_back("../../res/levels/7.txt");
    levels.push_back("../../res/levels/9.txt");

    std::vector<bool> unlocked(levels.size(), false);
    unlocked[0] = true; // niveau 1 toujours jouable

    while (true) {

        menu.update(unlocked);
        int levelIndex = menu.run();

        if (levelIndex == -1)
            break;

        Game* game = loader.load(levels[levelIndex]);
        BoardView view(game->get_board(), *game);

        while (view.isOpen()) {
            view.processEvents();
            view.render();

            if (game->isVictory()) {
                unlocked[levelIndex] = true;
                if (levelIndex + 1 < unlocked.size())
                    unlocked[levelIndex + 1] = true;
                break;
            }
        }

        delete game;
    }

    return 0;
}
