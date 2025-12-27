#ifndef MENU_HPP
#define MENU_HPP

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Menu {
public:
    Menu();
    void update(const std::vector<bool>& unlocked);
    int run();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::RectangleShape background;
    sf::Text title;
    sf::Text titleShadow;

    struct Button {
        sf::RectangleShape rect;
        sf::Text text;
        sf::Text textShadow;
        std::size_t index;
        bool isLocked;
    };

    std::vector<Button> buttons;
};


#endif
