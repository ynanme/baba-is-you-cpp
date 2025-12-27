#include "menu.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>


Menu::Menu() {
    window.create(sf::VideoMode(900, 700), "Menu Principal");

    if (!font.loadFromFile("./assets/DejaVuSans.ttf")) {
        std::cerr << "Erreur : impossible de charger la police DejaVuSans.ttf" << std::endl;
    }

    background.setFillColor(sf::Color(25, 35, 60));

    title.setFont(font);
    title.setString("BABA IS YOU");
    title.setCharacterSize(64);
    title.setFillColor(sf::Color(255, 220, 100));
    title.setStyle(sf::Text::Bold);
}

void Menu::update(const std::vector<bool>& unlocked) {
    buttons.clear();

    sf::Vector2f windowSize = static_cast<sf::Vector2f>(window.getSize());

    background.setSize(windowSize);

    float buttonWidth  = windowSize.x * 0.55f; 
    float buttonHeight = 80.f;
    float buttonSpacing = 50.f;

    std::size_t visibleCount = 0;
    for (bool b : unlocked) if (b) ++visibleCount;

    float totalHeight = unlocked.size() * buttonHeight + (unlocked.size() - 1) * buttonSpacing;
    float startY = (windowSize.y - totalHeight) / 2.0f + 60.f;

    for (std::size_t i = 0; i < unlocked.size(); ++i) {
        Button btn;

        // Rectangle du bouton
        btn.rect.setSize(sf::Vector2f(buttonWidth, buttonHeight));
        if (unlocked[i]) {
            btn.rect.setFillColor(sf::Color(40, 80, 160));
            btn.rect.setOutlineColor(sf::Color(100, 180, 255));
        } else {
            btn.rect.setFillColor(sf::Color(50, 50, 50));
            btn.rect.setOutlineColor(sf::Color(80, 80, 80));
        }
        btn.rect.setOutlineThickness(4.f);

        btn.text.setFont(font);
        if (unlocked[i]) {
            btn.text.setString("Niveau " + std::to_string(i + 1));
            btn.text.setFillColor(sf::Color::White);
        } else {
            btn.text.setString("Niveau " + std::to_string(i + 1) + " (Verrouillé)");
            btn.text.setFillColor(sf::Color(120, 120, 120));
        }
        btn.text.setCharacterSize(42);
        btn.text.setStyle(sf::Text::Bold);

        // Ombre du texte
        btn.textShadow = btn.text;
        btn.textShadow.setFillColor(sf::Color(0, 0, 0, 150));

        // Centrage horizontal du bouton
        float posX = (windowSize.x - buttonWidth) / 2.0f;
        float posY = startY + static_cast<float>(i) * (buttonHeight + buttonSpacing);

        btn.rect.setPosition(posX, posY);

        // Centrage du texte dans le bouton
        sf::FloatRect textBounds = btn.text.getLocalBounds();
        btn.text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                           textBounds.top + textBounds.height / 2.0f);
        btn.textShadow.setOrigin(textBounds.left + textBounds.width / 2.0f,
                                 textBounds.top + textBounds.height / 2.0f);

        btn.text.setPosition(posX + buttonWidth / 2.0f, posY + buttonHeight / 2.0f - 8.f);
        btn.textShadow.setPosition(posX + buttonWidth / 2.0f + 4.f, posY + buttonHeight / 2.0f - 4.f);

        btn.index = i;
        btn.isLocked = !unlocked[i];

        buttons.push_back(btn);
    }

    // Centrage du titre 
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2.0f,
                    titleBounds.top + titleBounds.height / 2.0f);
    title.setPosition(windowSize.x / 2.0f, windowSize.y * 0.15f); 

    titleShadow.setPosition(title.getPosition().x + 4.f, title.getPosition().y + 4.f);
}

int Menu::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter && !buttons.empty()) {
                    for (std::size_t i = 0; i < buttons.size(); ++i) {
                        if (buttons[i].isLocked) {
                            return buttons[i-1].index;
                        }
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
                                      static_cast<float>(event.mouseButton.y));

                for (std::size_t i = 0; i < buttons.size(); ++i) {
                    if (!buttons[i].isLocked && buttons[i].rect.getGlobalBounds().contains(mousePos)) {
                        return buttons[i].index;
                    }
                }
            }
        }

        // Hover effect
        sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel);

        for (std::size_t i = 0; i < buttons.size(); ++i) {
            bool hovered = buttons[i].rect.getGlobalBounds().contains(mousePos) && !buttons[i].isLocked;

            if (hovered) {
                buttons[i].rect.setFillColor(sf::Color(70, 120, 220));
                buttons[i].rect.setOutlineColor(sf::Color(150, 220, 255));
            } else {
                if (buttons[i].isLocked) {
                    buttons[i].rect.setFillColor(sf::Color(50, 50, 50));
                    buttons[i].rect.setOutlineColor(sf::Color(80, 80, 80));
                } else {
                    buttons[i].rect.setFillColor(sf::Color(40, 80, 160));
                    buttons[i].rect.setOutlineColor(sf::Color(100, 180, 255));
                }
            }
        }

        // Dessin
        window.clear();
        window.draw(background);
        window.draw(titleShadow);
        window.draw(title);

        for (std::size_t i = 0; i < buttons.size(); ++i) {
            window.draw(buttons[i].rect);
            window.draw(buttons[i].textShadow);
            window.draw(buttons[i].text);
        }

        window.display();
    }

    return -1;
}

