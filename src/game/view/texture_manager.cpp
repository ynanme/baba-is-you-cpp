#include "game/view/texture_manager.hpp"
#include <stdexcept>

TextureManager::TextureManager()
{
    tilesTexture_1.loadFromFile("res/assets/spritesheet_characters_1.png");
    tilesTexture_2.loadFromFile("res/assets/spritesheet_characters_2.png");
    tilesTexture_3.loadFromFile("res/assets/spritesheet_characters_3.png");
    wordsTexture.loadFromFile("res/assets/spritesheet_words.png");
    grassTexture.loadFromFile("res/assets/GRASS.png");
    textGrassTexture.loadFromFile("res/assets/Text_GRASS_0.png");
    waterTexture.loadFromFile("res/assets/WATER_0.png");
    textWaterTexture.loadFromFile("res/assets/Text_WATER_0.png");
    textLavaTexture.loadFromFile("res/assets/Text_LAVA_0.png");
    lavaTexture.loadFromFile("res/assets/LAVA_0.png");
    hotTextTexture.loadFromFile("res/assets/Text_HOT_0.png");

    skullTextTexture.loadFromFile("res/assets/Text_SKULL_0.png");
    meltTextTexture.loadFromFile("res/assets/Text_MELT_0.png");
    keyTextTexture.loadFromFile("res/assets/Text_KEY_0.png");
    doorTextTexture.loadFromFile("res/assets/Text_DOOR_0.png");
    openTextTexture.loadFromFile("res/assets/Text_OPEN_0.png");
    keyTexture.loadFromFile("res/assets/KEY_0.png");
    doorTexture.loadFromFile("res/assets/DOOR_0.png");

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
        Label::WALL,
        SpriteInfo(&tilesTexture_2, getSpriteRect(1, 4))
    ));

    sprites.insert(std::make_pair(
        Label::FLAG,
        SpriteInfo(&tilesTexture_2, getSpriteRect(14, 10))
    ));

    sprites.insert(std::make_pair(
        Label::SKULL,
        SpriteInfo(&tilesTexture_3, getSpriteRect(15, 63))  
    ));

    sf::Vector2u grassSize = grassTexture.getSize();
    sf::IntRect whole_pic_grass(0, 0, grassSize.x, grassSize.y);
    sprites.insert(std::make_pair(
        Label::GRASS,
        SpriteInfo(&grassTexture, whole_pic_grass)
    ));

    sf::Vector2u textGrassSize = textGrassTexture.getSize();
    sf::IntRect whole_pic_text_grass(0, 0, textGrassSize.x, textGrassSize.y);
    sprites.insert(std::make_pair(
        Label::WORD_GRASS,
        SpriteInfo(&textGrassTexture, whole_pic_text_grass)
    ));

    sf::Vector2u textWaterSize = textWaterTexture.getSize();
    sf::IntRect whole_pic_text_water(0, 0, textWaterSize.x, textWaterSize.y);
    sprites.insert(std::make_pair(
        Label::WORD_WATER,
        SpriteInfo(&textWaterTexture, whole_pic_text_water)
    ));

    sf::Vector2u waterSize = waterTexture.getSize();
    sf::IntRect whole_pic_water(0, 0, waterSize.x, waterSize.y);
    sprites.insert(std::make_pair(
        Label::WATER,
        SpriteInfo(&waterTexture, whole_pic_water)
    ));

    sf::Vector2u lavaSize = lavaTexture.getSize();
    sf::IntRect whole_pic_lava(0, 0, lavaSize.x, lavaSize.y);
    sprites.insert(std::make_pair(
        Label::LAVA,
        SpriteInfo(&lavaTexture, whole_pic_lava)
    ));

    sf::Vector2u textLavaSize = textLavaTexture.getSize();
    sf::IntRect whole_pic_text_lava(0, 0, textLavaSize.x, textLavaSize.y);
    sprites.insert(std::make_pair(
        Label::WORD_LAVA,
        SpriteInfo(&textLavaTexture, whole_pic_text_lava)
    ));

    sf::Vector2u textHotSize = hotTextTexture.getSize();
    sf::IntRect whole_pic_text_hot(0, 0, textHotSize.x, textHotSize.y);
    sprites.insert(std::make_pair(
        Label::WORD_HOT,
        SpriteInfo(&hotTextTexture, whole_pic_text_hot)
    ));

    sf::Vector2u textSkullSize = skullTextTexture.getSize();
    sf::IntRect whole_pic_text_skull(0, 0, textSkullSize.x, textSkullSize.y);
    sprites.insert(std::make_pair(
        Label::WORD_SKULL,
        SpriteInfo(&skullTextTexture, whole_pic_text_skull)
    ));

    sf::Vector2u textMeltSize = meltTextTexture.getSize();
    sf::IntRect whole_pic_text_melt(0, 0, textMeltSize.x, textMeltSize.y);
    sprites.insert(std::make_pair(
        Label::WORD_MELT,
        SpriteInfo(&meltTextTexture, whole_pic_text_melt)
    ));

    sf::Vector2u textKeySize = keyTextTexture.getSize();
    sf::IntRect whole_pic_text_key(0, 0, textKeySize.x, textKeySize.y);
    sprites.insert(std::make_pair(
        Label::WORD_KEY,
        SpriteInfo(&keyTextTexture, whole_pic_text_key)
    ));

    sf::Vector2u textDoorSize = doorTextTexture.getSize();
    sf::IntRect whole_pic_text_door(0, 0, textDoorSize.x, textDoorSize.y);
    sprites.insert(std::make_pair(
        Label::WORD_DOOR,
        SpriteInfo(&doorTextTexture, whole_pic_text_door)
    ));

    sf::Vector2u textOpenSize = openTextTexture.getSize();
    sf::IntRect whole_pic_text_open(0, 0, textOpenSize.x, textOpenSize.y);
    sprites.insert(std::make_pair(
        Label::WORD_OPEN,
        SpriteInfo(&openTextTexture, whole_pic_text_open)
    ));

    sf::Vector2u keySize = keyTexture.getSize();
    sf::IntRect whole_pic_key(0, 0, keySize.x, keySize.y);
    sprites.insert(std::make_pair(
        Label::KEY,
        SpriteInfo(&keyTexture, whole_pic_key)
    ));

    sf::Vector2u doorSize = doorTexture.getSize();
    sf::IntRect whole_pic_door(0, 0, doorSize.x, doorSize.y);
    sprites.insert(std::make_pair(
        Label::DOOR,
        SpriteInfo(&doorTexture, whole_pic_door)
    ));

    // words.png
    sprites.insert(std::make_pair(
        Label::WORD_BABA,
        SpriteInfo(&tilesTexture_1, getSpriteRect(0, 0))
    ));

    sprites.insert(std::make_pair(
        Label::WORD_IS,
        SpriteInfo(&wordsTexture, getSpriteRect(9, 4))
    ));

    sprites.insert(std::make_pair(
        Label::WORD_YOU,
        SpriteInfo(&wordsTexture, getSpriteRect(12, 10))
    ));

    sprites.insert(std::make_pair(
        Label::WORD_DEFEAT,
        SpriteInfo(&wordsTexture, getSpriteRect(0, 109))
    ));

    sprites.insert(std::make_pair(
        Label::WORD_PULL,
        SpriteInfo(&wordsTexture, getSpriteRect(6, 13))
    ));

    // à réctifier plus tard
    sprites.insert(std::make_pair(
        Label::WORD_WIN,
        SpriteInfo(&wordsTexture, getSpriteRect(8, 136))
    ));

    sprites.insert(std::make_pair(
        Label::WORD_STOP,
        SpriteInfo(&wordsTexture, getSpriteRect(9, 13))
    ));

    sprites.insert(std::make_pair(
        Label::WORD_PUSH,
        SpriteInfo(&wordsTexture, getSpriteRect(3, 13))
    ));

    // à réctifier plus tard
    sprites.insert(std::make_pair(
        Label::WORD_SINK,
        SpriteInfo(&wordsTexture, getSpriteRect(9, 129))
    ));

    sprites.insert(std::make_pair(
        Label::WORD_WALL,
        SpriteInfo(&tilesTexture_2, getSpriteRect(0, 4))
    ));

    sprites.insert(std::make_pair(
        Label::WORD_FLAG,
        SpriteInfo(&tilesTexture_2, getSpriteRect(13, 10))
    ));

    sprites.insert(std::make_pair(
        Label::WORD_ROCK,
        SpriteInfo(&tilesTexture_2, getSpriteRect(30, 25))
    ));



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
