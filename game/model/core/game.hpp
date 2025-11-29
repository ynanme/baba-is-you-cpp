#ifndef _GAME
#define _GAME

#include <vector>
#include <stack>
#include "board.hpp"
#include "../characters/character.hpp"
#include "./action.hpp"
#include "../utils/observer_pattern.hpp"

using namespace std;

class Game : public Observer {
private:
    Board& board;

    vector<Action> actions;         
    stack<Action> done_actions;      
    stack<Action> redone_actions;   
    
    vector<Character &> players;

    bool is_terminated = false;     
    bool has_won = false;
    string end_message;

public:
    Game(Board& board);

    void update() override;

    void add_character(Character* character);

    //Action computeNextAction(Character& character, Direction direction);

    void play (Direction direction);
    void do(Action action);

    bool undo();
    bool redo();

    void terminate(bool win, const std::string& message = "");

    bool isTerminated() const noexcept { return is_terminated; }
    bool isVictory() const noexcept { return is_terminated && has_won; }
    bool isDefeat() const noexcept { return is_terminated && !has_won; }

private:
    void reverseAction(const Action& action);  
};

#endif
