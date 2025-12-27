#pragma once
#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace sf;

struct Button {
    RectangleShape rect;
    Text text;
    Text textShadow;
    std::size_t index = 0;
    bool isLocked = false;
};

class Menu {
private:
    RenderWindow window;
    Font font;

    RectangleShape background;
    Text title;
    Text titleShadow;

    std::vector<Button> buttons;

    enum class State { 
        CHOOSE_MODE,      // 0 = Normal / 1 = Explorer
        CHOOSE_LEVEL    
    };

    State currentState = State::CHOOSE_MODE;

    bool explorerMode = false;  

    void createModeSelection();
    void createLevelSelection(const std::vector<bool>& unlocked);

    int handleModeSelection();
    int handleLevelSelection(Event& event);

public:
    Menu();

    int chooseGameMode();
    int runLevelSelection(const std::vector<bool>& unlocked);
    bool isExplorerMode() const { return explorerMode; }
};

#endif 
