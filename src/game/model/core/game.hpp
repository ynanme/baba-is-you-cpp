#ifndef _GAME
#define _GAME

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <set>
#include "game/model/core/board.hpp"
#include "game/model/characters/character.hpp"
#include "game/model/core/action.hpp"
#include "game/utils/observer_pattern.hpp"
#include "game/model/core/events.hpp"
#include "game/model/core/ruler.hpp"
#include "game/model/core/properties.hpp"


using Rule = tuple<Label, Label, Label>;


class Game : public Observer<RuleChange> {

    public:

        Game(int board_width, int board_height);
        
        ~ Game ();
        Game (const Game &) = delete;
        Game & operator = (const Game &) = delete;

        Board& get_board() const;
        
        void update(const RuleChange & event) override;
        
        void add_character(Character* character);
        void apply_rule (Rule rule);
        
        void play (Direction direction, bool pull = true);
        void undo ();
        void redo ();

        bool ended() const noexcept;
        bool is_victory() const noexcept;
        bool is_defeat() const noexcept;


    private:

        static std::unordered_map<Label, Property> WORDS_PROPERTIES;
        static std::unordered_map<Label, Label> WORDS_SUBJECTS;
        static std::unordered_map<CoexistionResult, int> COEXISTION_RESULTS_PRIORITIES;

        Board * board;
        Ruler * ruler;

        std::stack<Action *> done_actions;      
        std::stack<Action *> undone_actions;   
        
        std::vector<Character *> characters;
        std::vector<Character *> players;

        std::set<Rule> rules_history;
        std::unordered_map<Label, set<Property>> properties;

        bool is_terminated = false;     
        bool has_won = false;
        string end_message;

        
        void unapply_rule (Rule rule);
        void make_player (Label label);
        void unmake_player (Label label);
        void add_property (Label label, Property property);
        void remove_property (Label label, Property property);
        void transfer_properties (Label of, Label to);
        void retrieve_properties (Label of, Label to);
        void check_for_tautologies (Label label);
        
        void move (Character * player, Direction direction, Action * ongoing_action, bool pull = true);
        void move_characters (Position position, Direction direction, Property moving_property, Action * ongoing_action);
        void move_character (Character * character, Direction direction, Action * ongoing_action);
        int pushes_chain_range (Position start, Direction direction);
        int pulls_chain_range (Position start, Direction direction);
        void launch_pushes (Position start, Direction direction, int range, Action * ongoing_action);
        void launch_pulls (Position start, Direction direction, int range, Action * ongoing_action);
        CoexistionResult get_coexistion_result (Character * visitor, Character * host);
        CoexistionResult get_prioritary_coexistion_result (Character * visitor, Position hosts_position);
        void register_destruction (Character * character, Action * ongoing_action);
        void register_move (Character * character, Direction direction, Action * ongoing_action, bool is_move_winning);
        void replay_action_movings (Action * action, bool undoing);
        
        bool has_property (Label label, Property property);
        bool has_property (Character * character, Property property);
        bool has_property (Position position, Property property);
        bool has_property_but (Character * character, Property property, Property but);
        bool has_property_but (Position position, Property property, Property but);
        void clear_actions (stack<Action *> & actions);
        void terminate(bool win, const std::string& message = "");
        
    
    friend ostream& operator << (ostream& out, const Game& game);

};


ostream& operator << (ostream& out, const Game& game);


#endif
