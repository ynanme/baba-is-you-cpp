#include <SFML/Graphics.hpp>
#include "game/model/core/board.hpp"
#include "game/model/core/game.hpp"
#include "game/loader/loader.hpp"
#include "game/view/board_view.hpp"
#include "game/view/menu.hpp"
#include <iostream>
#include <vector>

// unlock tout les les niveaux si en mode explorer
std::vector<bool> buildLevelsToShow(const std::vector<bool>& realUnlocked, bool isExplorer) {
    std::vector<bool> toShow = realUnlocked;
    if (isExplorer) {
        std::fill(toShow.begin(), toShow.end(), true);
    }
    return toShow;
}

enum class GameState {
    ModeSelection,
    LevelSelection,
    Playing,
    Quit
};

int main() {
    Loader loader;
    Menu menu;

    std::vector<std::string> levels = {
        "res/levels/1.txt",
        "res/levels/2.txt",
        "res/levels/3.txt",
        "res/levels/4.txt",
        "res/levels/5.txt",
        "res/levels/6.txt",
        "res/levels/7.txt",
        "res/levels/8.txt",
        "res/levels/9.txt",
        "res/levels/10.txt",
        "res/levels/11.txt"
    };

    std::vector<bool> unlocked(levels.size(), false);
    unlocked[0] = true;  // niveau 1 toujours débloqué en mode normal

    GameState state = GameState::ModeSelection;
    int currentMode = -1;  // 0 = normal, 1 = explorer

    while (state != GameState::Quit) {
        switch (state) {
            case GameState::ModeSelection: {
                int modeChoice = menu.chooseGameMode();
                if (modeChoice < 0) {
                    state = GameState::Quit;
                } else {
                    currentMode = modeChoice;  
                    state = GameState::LevelSelection;
                }
                break;
            }

            case GameState::LevelSelection: {
                std::vector<bool> levelsToShow = buildLevelsToShow(unlocked, currentMode == 1);

                int choice = menu.runLevelSelection(levelsToShow);

                if (choice == -2) {
                    state = GameState::ModeSelection;
                }
                else if (choice < 0) {
                    state = GameState::Quit;
                }
                else {
                    Game* game = loader.load(levels[choice]);
                    BoardView view(game->get_board(), *game);

                    bool victory = false;
                    while (view.isOpen()) {
                        view.processEvents();
                        view.render();

                        if (game->is_victory()) {
                            victory = true;
                            break;
                        }
                    }

                    if (victory && currentMode == 0) {
                        unlocked[choice] = true;
                        if (choice + 1 < (int)unlocked.size()) {
                            unlocked[choice + 1] = true;
                        }
                    }

                    delete game;

                    state = GameState::LevelSelection;
                }
                break;
            }

            case GameState::Playing:
                state = GameState::LevelSelection;
                break;

            case GameState::Quit:
                break;
        }
    }

    return 0;
}
