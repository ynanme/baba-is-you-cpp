#ifndef _GAME
#define _GAME

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include "board.hpp"
#include "../characters/character.hpp"
#include "./action.hpp"
#include "../../utils/observer_pattern.hpp"
#include "events.hpp"

using namespace std;

class Game : public Observer<RuleChange> {
private:

    static unordered_map<Label, CollisionResult> COLLISION_HANDLINGS;
    static unordered_map<Label, Label> WORDS_SUBJECTS;

    Board& board;

    vector<Action> actions;         
    stack<Action> done_actions;      
    stack<Action> redone_actions;   
    
    vector<Character *> characters;
    vector<Character *> players;

    bool is_terminated = false;     
    bool has_won = false;
    string end_message;

public:
    Game(Board& board);

    Board& get_board() const;

    void update(RuleChange __event) override;

    void add_character(Character* character);
    void add_player(Character* player);

    void make_player (Label label);
    void unmake_player (Label label);
    void change_collision_handlings (Label label, CollisionResult collision_handling);

    //Action computeNextAction(Character& character, Direction direction);

    void play (Direction direction);
    void _do(Action action);

    bool undo();
    bool redo();

    void terminate(bool win, const std::string& message = "");

    bool isTerminated() const noexcept { return is_terminated; }
    bool isVictory() const noexcept { return is_terminated && has_won; }
    bool isDefeat() const noexcept { return is_terminated && !has_won; }

    void push_chain(Character& obj, Direction dir, Action& action);
    bool can_push(Character& obj, Direction dir);
    void move_character (Character & character, Direction direction);

private:
    void reverseAction(const Action& action); 
    
    
    friend ostream& operator << (ostream& out, const Game& game);

};


ostream& operator << (ostream& out, const Game& game);


#endif
