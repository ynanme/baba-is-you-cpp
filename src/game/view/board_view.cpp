#include "game/view/board_view.hpp"

BoardView::BoardView(Board& board, Game& game)
    :  board(board), game(game), cellSize(25)
{
    createWindow();
    rebuildCharacters();
}


void BoardView::createWindow() {
    window.create(
        sf::VideoMode(
            board.get_width() * cellSize,
            board.get_height() * cellSize
        ),
        "BABA IS YOU"
    );
}

void BoardView::rebuildCharacters() {
    characterViews.clear();

    for (int y = 0; y < board.get_height(); ++y) {
        for (int x = 0; x < board.get_width(); ++x) {

            Position pos(x, y);
            const std::vector<Character*>& cell =
                board.at(pos);            

            for (std::size_t i = 0; i < cell.size(); ++i) {
                characterViews.push_back(
                    CharacterView(*cell[i], textures, cellSize)
                );
            }
        }
    }

}


bool BoardView::isOpen() const {
    return window.isOpen();
}

void BoardView::processEvents() {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || game.ended()) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up)
                game.play(Direction::UP);
            if (event.key.code == sf::Keyboard::Down)
                game.play(Direction::DOWN);
            if (event.key.code == sf::Keyboard::Left)
                game.play(Direction::LEFT);
            if (event.key.code == sf::Keyboard::Right)
                game.play(Direction::RIGHT);
            if (event.key.code == sf::Keyboard::Z)
                game.undo();
            if (event.key.code == sf::Keyboard::Y)
                game.redo();

            rebuildCharacters();
        }
    }
}

void BoardView::render() {
    window.clear(sf::Color(82, 161, 73));

    for (std::size_t i = 0; i < characterViews.size(); ++i) {
        characterViews[i].updatePosition();
        characterViews[i].draw(window);
    }

    window.display();
}

