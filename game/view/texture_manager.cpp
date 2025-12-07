#include "texture_manager.hpp"
#include <stdexcept>

TextureManager::TextureManager()
{
    tilesTexture_1.loadFromFile("assets/spritesheet_characters_1.png");
    tilesTexture_2.loadFromFile("assets/spritesheet_characters_2.png");
    tilesTexture_3.loadFromFile("assets/spritesheet_characters_3.png");
    wordsTexture.loadFromFile("assets/spritesheet_words.png");

    // tiles.png
    sprites.insert(std::make_pair(
        Label::BABA,
        SpriteInfo(&tilesTexture_1, getSpriteRect(1, 0))
    ));

    sprites.insert(std::make_pair(
        Label::ROCK,
        SpriteInfo(&tilesTexture_2, getSpriteRect(31, 24))
    ));

    sprites.insert(std::make_pair(
        Label::FLAG,
        SpriteInfo(&tilesTexture_2, getSpriteRect(14, 10))
    ));

    /*sprites.insert(std::make_pair(
        Label::LAVA,
        SpriteInfo(&tilesTexture_2, getSpriteRect(6, 10))
    ));*/
    sprites.insert(std::make_pair(
        Label::SKULL,
        SpriteInfo(&tilesTexture_3, getSpriteRect(15, 63))  
    ));

    // words.png
    sprites.insert(std::make_pair(
        Label::WORD_BABA,
        SpriteInfo(&tilesTexture_1, getSpriteRect(0, 0))
    ));

    /*sprites.insert(std::make_pair(
        Label::WORD_IS,
        SpriteInfo(&wordsTexture, sf::IntRect(25, 0, 24, 24))
    ));

    sprites.insert(std::make_pair(
        Label::WORD_YOU,
        SpriteInfo(&wordsTexture, sf::IntRect(50, 0, 24, 24))
    ));*/
}

const SpriteInfo& TextureManager::getSprite(Label label) const
{
    std::map<Label, SpriteInfo>::const_iterator it = sprites.find(label);
    if (it == sprites.end()) {
        throw std::runtime_error("Sprite not found");
    }
    return it->second;
}


sf::IntRect TextureManager::getSpriteRect(int col, int row) {
    int left = INITIAL_OFFSET + (col * STEP_SIZE);
    
    int top = INITIAL_OFFSET + (row * STEP_SIZE);

    return sf::IntRect(left, top, TILE_SIZE, TILE_SIZE);
}
