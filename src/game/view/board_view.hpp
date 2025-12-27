#ifndef BOARD_VIEW_HPP
#define BOARD_VIEW_HPP

#include <SFML/Graphics.hpp>
#include "game/model/core/board.hpp"
#include "game/model/core/game.hpp"
#include "game/utils/geometry.hpp"
#include "game/view/texture_manager.hpp"
#include "game/view/character_view.hpp"

class BoardView {
private:
    Board& board;
    Game& game;

    sf::RenderWindow window;
    TextureManager textures;

    unsigned int cellSize;

    std::vector<CharacterView> characterViews;

    void createWindow();
    void rebuildCharacters(); 

public:
    BoardView(Board& board, Game& game);

    bool isOpen() const;
    void processEvents();
    void render();
};


#endif