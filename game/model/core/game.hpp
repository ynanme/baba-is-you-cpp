#ifndef _GAME
#define _GAME

#include <vector>
#include <stack>
#include "board.hpp"
#include "../characters/character.hpp"
#include "./action.hpp"
#include "../utils/observer_pattern.hpp"

class Game : public Observer {
private:
    Board& board;

    std::vector<Action> actions;         
    std::stack<Action> done_actions;      
    std::stack<Action> redone_actions;    

public:
    Game(Board& board);

    void update() override;

    void add_character(Character* character);

    Action computeNextAction(Character& character, Direction direction);

    bool undo();
    bool redo();

private:
    void reverseAction(const Action& action);  
};

#endif
