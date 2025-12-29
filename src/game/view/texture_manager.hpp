#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include "game/model/characters/labels.hpp"
#include "game/view/sprite_info.hpp"

const int TILE_SIZE = 24;
const int STEP_SIZE = TILE_SIZE + 1; 
const int INITIAL_OFFSET = 1;

class TextureManager {
private:
    sf::Texture tilesTexture_1;
    sf::Texture tilesTexture_2;
    sf::Texture tilesTexture_3;
    sf::Texture wordsTexture;
    sf::Texture grassTexture;
    sf::Texture textGrassTexture;
    sf::Texture waterTexture;
    sf::Texture textWaterTexture;
    sf::Texture lavaTexture;
    sf::Texture textLavaTexture;
    sf::Texture hotTextTexture;
    sf::Texture skullTextTexture;
    sf::Texture meltTextTexture;
    sf::Texture keyTextTexture;
    sf::Texture doorTextTexture;
    sf::Texture openTextTexture;
    sf::Texture keyTexture;
    sf::Texture doorTexture;
    sf::Texture shutTextTexture;

    std::map<Label, SpriteInfo> sprites;

public:
    TextureManager();

    const SpriteInfo& getSprite(Label label) const;
    sf::IntRect getSpriteRect(int col, int row);
};

#endif
