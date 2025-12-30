#include "game/view/menu.hpp"
#include <iostream>

Menu::Menu() {
    window.create(VideoMode(900, 700), "Baba Is You - Menu");

    if (!font.loadFromFile("res/assets/DejaVuSans.ttf")) {
        std::cerr << "Erreur : impossible de charger la police DejaVuSans.ttf\n";
    }

    background.setFillColor(Color(25, 35, 60));

    title.setFont(font);
    title.setString("BABA IS YOU");
    title.setCharacterSize(72);
    title.setFillColor(Color(255, 220, 100));
    title.setStyle(Text::Bold);

    titleShadow = title;
    titleShadow.setFillColor(Color(0, 0, 0, 140));
}

void Menu::createModeSelection() {
    buttons.clear();

    Vector2f size = static_cast<Vector2f>(window.getSize());

    background.setSize(size);

    float btnW = size.x * 0.60f;
    float btnH = 100.f;
    float spacing = 60.f;

    float startY = size.y / 2.f - (btnH * 2.f + spacing) / 2.f;

    // Bouton Mode Normal
    Button normal;
    normal.rect.setSize({btnW, btnH});
    normal.rect.setFillColor(Color(40, 80, 160));
    normal.rect.setOutlineColor(Color(100, 180, 255));
    normal.rect.setOutlineThickness(5.f);
    normal.rect.setPosition((size.x - btnW)/2.f, startY);

    normal.text.setFont(font);
    normal.text.setString("Mode Normal");
    normal.text.setCharacterSize(52);
    normal.text.setFillColor(Color::White);
    normal.text.setStyle(Text::Bold);

    // Centrage texte
    FloatRect bounds = normal.text.getLocalBounds();
    normal.text.setOrigin(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f);
    normal.text.setPosition(normal.rect.getPosition() + Vector2f(btnW/2.f, btnH/2.f - 5.f));

    normal.index = 0;

    // Bouton Mode Explorer
    Button explorer = normal;
    explorer.rect.setPosition((size.x - btnW)/2.f, startY + btnH + spacing);
    explorer.text.setString("Mode Explorer");
    explorer.text.setCharacterSize(44);
    FloatRect expBounds = explorer.text.getLocalBounds();
    explorer.text.setOrigin(expBounds.left + expBounds.width/2.f, expBounds.top + expBounds.height/2.f);
    explorer.text.setPosition(explorer.rect.getPosition() + Vector2f(btnW/2.f, (btnH/2.f) - 5.f));
    explorer.index = 1;

    buttons.push_back(normal);
    buttons.push_back(explorer);

    // Position titre
    FloatRect tBounds = title.getLocalBounds();
    title.setOrigin(tBounds.left + tBounds.width/2.f, tBounds.top + tBounds.height/2.f);
    title.setPosition(size.x/2.f, size.y * 0.18f);

    titleShadow.setOrigin(title.getOrigin());
    titleShadow.setPosition(title.getPosition() + Vector2f(5.f, 5.f));
}

int Menu::handleModeSelection() {
    Vector2i pixelPos = Mouse::getPosition(window);
    Vector2f mousePos = window.mapPixelToCoords(pixelPos);

    // Mise à jour visuelle du hover
    for (Button& btn : buttons) {
        bool hovered = btn.rect.getGlobalBounds().contains(mousePos);

        if (hovered) {
            btn.rect.setFillColor(Color(70, 120, 220));
            btn.rect.setOutlineColor(Color(180, 230, 255));
        } else {
            btn.rect.setFillColor(Color(40, 80, 160));
            btn.rect.setOutlineColor(Color(100, 180, 255));
        }
    }

    // Gestion des événements
    Event event;   
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return -1;
        }

        if (event.type == Event::MouseButtonPressed && 
            event.mouseButton.button == Mouse::Left) {
            
            for (const Button& btn : buttons) {
                if (btn.rect.getGlobalBounds().contains(mousePos)) {
                    return static_cast<int>(btn.index); // 0 = normal, 1 = explorer
                }
            }
        }
    }

    return -2; 
}

void Menu::createLevelSelection(const std::vector<bool>& unlocked) {
    buttons.clear();

    Vector2f windowSize = static_cast<Vector2f>(window.getSize());

    background.setSize(windowSize);

    float buttonWidth  = windowSize.x * 0.55f; 
    float buttonHeight = 80.f;
    float buttonSpacing = 50.f;

    float startY = 200.f; // juste sous le titre

    // Création des boutons de niveaux
    for (std::size_t i = 0; i < unlocked.size(); ++i) {
        Button btn;

        btn.rect.setSize(Vector2f(buttonWidth, buttonHeight));
        if (unlocked[i]) {
            btn.rect.setFillColor(Color(40, 80, 160));
            btn.rect.setOutlineColor(Color(100, 180, 255));
        } else {
            btn.rect.setFillColor(Color(50, 50, 50));
            btn.rect.setOutlineColor(Color(80, 80, 80));
        }
        btn.rect.setOutlineThickness(4.f);

        btn.text.setFont(font);
        if (unlocked[i]) {
            btn.text.setString("Niveau " + std::to_string(i + 1));
            btn.text.setFillColor(Color::White);
        } else {
            btn.text.setString("Niveau " + std::to_string(i + 1) + " (Verrouille)");
            btn.text.setFillColor(Color(120, 120, 120));
        }
        btn.text.setCharacterSize(42);
        btn.text.setStyle(Text::Bold);

        btn.textShadow = btn.text;
        btn.textShadow.setFillColor(Color(0, 0, 0, 150));

        float posX = (windowSize.x - buttonWidth) / 2.0f;
        float posY = startY + static_cast<float>(i) * (buttonHeight + buttonSpacing);

        btn.rect.setPosition(posX, posY);

        FloatRect textBounds = btn.text.getLocalBounds();
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

    // Bouton RETOUR 
    Button backBtn;
    backBtn.rect.setSize({160.f, 60.f});
    backBtn.rect.setPosition(30.f, 30.f);
    backBtn.rect.setFillColor(Color(120, 40, 40));
    backBtn.rect.setOutlineColor(Color(220, 80, 80));
    backBtn.rect.setOutlineThickness(4.f);

    backBtn.text.setFont(font);
    backBtn.text.setString("Retour");
    backBtn.text.setCharacterSize(34);
    backBtn.text.setFillColor(Color::White);
    backBtn.text.setStyle(Text::Bold);

    // Centrage du texte dans le bouton retour
    FloatRect backTextBounds = backBtn.text.getLocalBounds();
    backBtn.text.setOrigin(backTextBounds.left + backTextBounds.width / 2.0f,
                           backTextBounds.top + backTextBounds.height / 2.0f);
    backBtn.text.setPosition(
        30.f + 160.f / 2.f,
        30.f + 60.f / 2.f
    );

    // Ombre 
    backBtn.textShadow = backBtn.text;
    backBtn.textShadow.setFillColor(Color(0, 0, 0, 140));
    backBtn.textShadow.setPosition(backBtn.text.getPosition() + Vector2f(3.f, 3.f));

    backBtn.index = -999;       // valeur spéciale pour le reconnaître
    backBtn.isLocked = false;

    buttons.push_back(backBtn);

    scrollView = window.getDefaultView();

    float contentHeight = unlocked.size() * buttonHeight + (unlocked.size() - 1) * buttonSpacing;

    float viewHeight = scrollView.getSize().y;

    // si le contenu dépasse
    if (contentHeight > viewHeight) {
        maxScroll = contentHeight - viewHeight + 240.f; 
    } else {
        maxScroll = 0.f;
    }

    scrollOffset = 0.f;


    // Titre 
    FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2.0f,
                    titleBounds.top + titleBounds.height / 2.0f);
    title.setPosition(windowSize.x / 2.0f, windowSize.y * 0.15f); 

    titleShadow.setPosition(title.getPosition().x + 4.f, title.getPosition().y + 4.f);
}

int Menu::handleLevelSelection(Event& event) {
    if (event.type == Event::Closed) {
        window.close();
        return -1;
    }

    if (event.type == Event::MouseButtonPressed &&
        event.mouseButton.button == Mouse::Left) {

        window.setView(scrollView);
        Vector2f mousePosScroll =
            window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        window.setView(window.getDefaultView());

        for (const Button& btn : buttons) {
            if (btn.index != -999 && 
                btn.rect.getGlobalBounds().contains(mousePosScroll)) {

                if (!btn.isLocked)
                    return btn.index;
            }
        }

        Vector2f mousePosFixed =
            window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

        for (const Button& btn : buttons) {
            if (btn.index == -999 &&
                btn.rect.getGlobalBounds().contains(mousePosFixed)) {

                return -2;
            }
        }
    }

    return -1;
}

int Menu::chooseGameMode() {
    createModeSelection();

    while (window.isOpen()) {
        window.clear();
        window.draw(background);
        window.draw(titleShadow);
        window.draw(title);

        for (const Button& btn : buttons) {
            window.draw(btn.rect);
            window.draw(btn.textShadow);
            window.draw(btn.text);
        }
        window.display();

        int choice = handleModeSelection();

        if (choice == -1) return -1;       // quitter
        if (choice >= 0 && choice <= 1) {
            explorerMode = (choice == 1);
            return choice;             
        }
    }
    return -1;
}

int Menu::runLevelSelection(const std::vector<bool>& unlocked) {
    createLevelSelection(unlocked);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::MouseWheelScrolled) {
                scrollOffset -= event.mouseWheelScroll.delta * 40.f;

                if (scrollOffset < 0.f) scrollOffset = 0.f;
                if (scrollOffset > maxScroll) scrollOffset = maxScroll;

                scrollView.setCenter(
                    scrollView.getSize().x / 2.f,
                    scrollView.getSize().y / 2.f + scrollOffset
                );
            }

            int choice = handleLevelSelection(event);

            if (choice != -1 && choice != -2) { 
                return choice; 
            }
            if (choice == -2 && event.type == Event::MouseButtonPressed) {
                return -2;
            }
        }

        // Hover effect
        Vector2i mousePixel = Mouse::getPosition(window);
        window.setView(scrollView);
        Vector2f mousePos = window.mapPixelToCoords(mousePixel);
        window.setView(window.getDefaultView());


        for (std::size_t i = 0; i < buttons.size(); ++i) {
            bool hovered = buttons[i].rect.getGlobalBounds().contains(mousePos) && !buttons[i].isLocked;

            if (hovered) {
                buttons[i].rect.setFillColor(Color(70, 120, 220));
                buttons[i].rect.setOutlineColor(Color(150, 220, 255));
            } else {
                if (buttons[i].isLocked) {
                    buttons[i].rect.setFillColor(Color(50, 50, 50));
                    buttons[i].rect.setOutlineColor(Color(80, 80, 80));
                } else {
                    buttons[i].rect.setFillColor(Color(40, 80, 160));
                    buttons[i].rect.setOutlineColor(Color(100, 180, 255));
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(titleShadow);
        window.draw(title);

        window.setView(scrollView);
        for (const Button& btn : buttons) {
            if (btn.index != -999) {
                window.draw(btn.rect);
                window.draw(btn.textShadow);
                window.draw(btn.text);
            }
        }
        window.setView(window.getDefaultView());

        // bouton retour
        for (const Button& btn : buttons) {
            if (btn.index == -999) {
                window.draw(btn.rect);
                window.draw(btn.textShadow);
                window.draw(btn.text);
            }
        }

        window.display();
    }
    return -1;
}
