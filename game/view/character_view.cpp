#include "character_view.hpp"

CharacterView::CharacterView(
    const Character& character,
    const TextureManager& textures,
    unsigned int cellSize
)
    : character(character), cellSize(cellSize) 
{
    const SpriteInfo& info = textures.getSprite(character.get_label());

    sprite.setTexture(*info.texture);
    sprite.setTextureRect(info.rect);

    sprite.setPosition(
        static_cast<float>(character.get_position().get_x() * cellSize),
        static_cast<float>(character.get_position().get_y() * cellSize)
    );
}

void CharacterView::updatePosition() {
    Position pos = character.get_position();

    sprite.setPosition(
        static_cast<float>(pos.get_x() * cellSize),
        static_cast<float>(pos.get_y() * cellSize)
    );
}

void CharacterView::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
