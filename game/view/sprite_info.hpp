#ifndef SPRITE_INFO_HPP
#define SPRITE_INFO_HPP

#include <SFML/Graphics.hpp>

struct SpriteInfo {
    const sf::Texture* texture;
    sf::IntRect rect;

    SpriteInfo() : texture(0), rect() {}

    SpriteInfo(const sf::Texture* t, sf::IntRect r)
        : texture(t), rect(r) {}
};

#endif
