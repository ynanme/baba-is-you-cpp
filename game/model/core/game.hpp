#ifndef _GAME
#define _GAME

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <set>
#include "board.hpp"
#include "../characters/character.hpp"
#include "./action.hpp"
#include "../../utils/observer_pattern.hpp"
#include "events.hpp"
#include "ruler.hpp"
#include "properties.hpp"

using namespace std;

using Rule = tuple<Label, Label, Label>;


class Game : public Observer<RuleChange> {
private:

    static unordered_map<Label, Property> WORDS_PROPERTIES;
    static unordered_map<Label, Label> WORDS_SUBJECTS;
    static unordered_map<CoexistionResult, int> COEXISTION_RESULTS_PRIORITIES;

    Board * board;
    Ruler * ruler;

    stack<Action *> done_actions;      
    stack<Action *> undone_actions;   
    
    vector<Character *> characters;
    vector<Character *> players;

    set<Rule> rules_history;
    unordered_map<Label, set<Property>> properties;

    bool is_terminated = false;     
    bool has_won = false;
    string end_message;

public:

    Game(int board_width, int board_height);
    ~ Game ();

    Board& get_board() const;

    void update(const RuleChange & event) override;

    void add_character(Character* character);

    void apply_rule (Rule rule);
    void unapply_rule (Rule rule);
    void make_player (Label label);
    void unmake_player (Label label);
    void add_property (Label label, Property property);
    void remove_property (Label label, Property property);
    void transfer_properties (Label from, Label to);
    void retrieve_properties (Label of, Label to);
    void check_for_tautologies (Label label);


    void play (Direction direction);
    void undo ();
    void redo ();
    void replay_action_movings (Action * action, bool undoing);
    void register_destruction (Character * character, Action * ongoing_action);
    void register_move (Character * character, Direction direction, Action * ongoing_action, bool is_move_winning);

    void move (Character * player, Direction direction, Action * ongoing_action);
    bool has_property (Label label, Property property);
    bool has_property (Character * character, Property property);
    bool is_open (Position position);
    bool is_subject_to_push (Position position);
    void move_characters (Position position, Direction direction, Action * ongoing_action);
    CoexistionResult get_coexistion_result (Character * visitor, Character * host);
    CoexistionResult get_prioritary_coexistion_result (Character * visitor, Position hosts_position);
    int pushes_chain_range (Position start, Direction direction);
    void launch_pushes (Position start, Direction direction, int range, Action * ongoing_action);

    void terminate(bool win, const std::string& message = "");

    bool isTerminated() const noexcept { return is_terminated; }
    bool isVictory() const noexcept { return is_terminated && has_won; }
    bool isDefeat() const noexcept { return is_terminated && !has_won; }


    void move_character (Character * character, Direction direction, Action * ongoing_action);

private:
    //void reverseAction(const Action& action); 
    
    
    friend ostream& operator << (ostream& out, const Game& game);

};


ostream& operator << (ostream& out, const Game& game);


#endif
