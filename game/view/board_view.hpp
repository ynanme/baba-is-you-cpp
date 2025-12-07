#ifndef BOARD_VIEW_HPP
#define BOARD_VIEW_HPP

#include <SFML/Graphics.hpp>
#include "../model/core/board.hpp"
#include "../model/core/game.hpp"
#include "../utils/geometry.hpp"
#include "texture_manager.hpp"
#include "character_view.hpp"

class BoardView {
private:
    Board& board;
    Game& game;

    sf::RenderWindow window;
    TextureManager textures;

    unsigned int cellSize;

    std::vector<CharacterView> characterViews;

    void createWindow();
    void rebuildCharacters(); // clé

public:
    BoardView(Board& board, Game& game);

    bool isOpen() const;
    void processEvents();
    void render();
};


#endif