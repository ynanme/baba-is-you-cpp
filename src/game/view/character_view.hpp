#ifndef CHARACTER_VIEW_HPP
#define CHARACTER_VIEW_HPP

#include <SFML/Graphics.hpp>
#include "game/model/characters/character.hpp"
#include "game/view/texture_manager.hpp"

class CharacterView {
private:
    const Character& character;
    sf::Sprite sprite;
    unsigned int cellSize;

public:
    CharacterView(
        const Character& character,
        const TextureManager& textures,
        unsigned int cellSize
    );

    void updatePosition();
    void draw(sf::RenderWindow& window);
};

#endif
