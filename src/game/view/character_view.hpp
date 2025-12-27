#ifndef CHARACTER_VIEW_HPP
#define CHARACTER_VIEW_HPP

#include <SFML/Graphics.hpp>
#include "../model/characters/character.hpp"
#include "texture_manager.hpp"

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
