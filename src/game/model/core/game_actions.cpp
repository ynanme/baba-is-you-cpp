#include "game/model/core/game.hpp"


void Game :: play (Direction direction, bool pull) {
    Action * new_action = new Action(direction);
    cout << "---------------------------------------------------------------" << endl;
    for (Character * player: players) {
        cout << "playing with " << *player << " towards " << direction << endl;
        move(player, direction, new_action, pull);
    }
    cout << "---------------------------------------------------------------" << endl;
    if (
        new_action->get_moved_characters().empty() &&
        new_action->get_destroyed_characters().empty()
    )
        delete new_action;
    else
        done_actions.push(new_action);
}


void Game :: move (Character * player, Direction direction, Action * ongoing_action, bool pull) {
    Position destination = Position::neighbor(player->get_position(), direction);
    int pushes_range = pushes_chain_range(destination, direction);
    cout << "chain range is " << pushes_range << endl;
    if (pushes_range >= 0) {
        launch_pushes(player->get_position(), direction, pushes_range, ongoing_action);
        move_character(player, direction, ongoing_action);
        if (pull) {
            Position before = Position::neighbor(destination, !direction, 2);
            int pulls_range = pulls_chain_range(before, direction);
            cout << "pull range is " << pulls_range << endl;
            if (!has_property(Position::neighbor(before, direction), Property::STOP))
                launch_pulls(before, direction, pulls_range, ongoing_action);
        }
    }
}

void Game :: launch_pushes (Position start, Direction direction, int range, Action * ongoing_action) {
    cout << "pushes launched from " << start << " towards " << direction << ", range " << range << endl;
    Position end = Position::neighbor(start, direction, range);
    while (end != start) {
        move_characters(end, direction, Property::PUSH, ongoing_action);
        end.shift(!direction);
    }
}

void Game :: launch_pulls (Position start, Direction direction, int range, Action * ongoing_action) {
    cout << "pulls launched from " << start << " towards " << direction << ", range " << range << endl;
    while (range > 0) {
        move_characters(start, direction, Property::PULL, ongoing_action);
        start.shift(!direction);
        range --;
    }
}


int Game :: pushes_chain_range (Position start, Direction direction) {
    int range = 0;
    while (board->in_bounds(start)) {
        if (has_property(start, Property::STOP)) return -1;
        if (has_property(start, Property::SHUT) && !has_property(Position::neighbor(start, !direction), Property::OPEN)) return -1;
        if (has_property(start, Property::PUSH)) {
            range ++;
            start.shift(direction);
        } else break;
    }
    if (!board->in_bounds(start)) return -1;
    return range;
}

int Game :: pulls_chain_range (Position start, Direction direction) {
    int range = 0;
    while (
        board->in_bounds(start) &&
        !has_property(start, Property::STOP) &&
        has_property(start, Property::PULL)
    ) {
        range ++;
        start.shift(!direction);
    }
    return range;
}

void Game :: move_characters (Position position, Direction direction, Property moving_property, Action * ongoing_action) {
    for (Character * character: board->at(position)) {
        if (has_property(character, moving_property)) {
            move_character(character, direction, ongoing_action);
        }
    }
}

CoexistionResult Game :: get_coexistion_result (Character * visitor, Character * host) {
    if (has_property(visitor, Property::SINK) || has_property(host, Property::SINK)) {
        return CoexistionResult::SINKED;
    }
    if (has_property(visitor, Property::YOU) && has_property(host, Property::DEFEAT)) {
        return CoexistionResult::DEFEATED;
    }
    if (has_property(visitor, Property::MELT) && has_property(host, Property::HOT)) {
        return CoexistionResult::MELTED;
    }
    if (has_property(visitor, Property::YOU) && has_property(host, Property::WIN)) {
        return CoexistionResult::WON;
    }
    if (has_property(visitor, Property::OPEN) && has_property(host, Property::SHUT)) {
        return CoexistionResult::OPENED;
    }
    return CoexistionResult::COEXISTED;
}

CoexistionResult Game :: get_prioritary_coexistion_result (Character * visitor, Position hosts_position) {
    CoexistionResult final_result = CoexistionResult::COEXISTED;
    for (Character * host: board->at(hosts_position)) {
        CoexistionResult host_result = get_coexistion_result(visitor, host);
        if (COEXISTION_RESULTS_PRIORITIES[host_result] < COEXISTION_RESULTS_PRIORITIES[final_result]) final_result = host_result;
    }
    return final_result;
}



void Game :: move_character (Character * character, Direction direction, Action * ongoing_action) {
    Position destination = Position::neighbor(character->get_position(), direction);
    board->remove_character(character);
    switch (get_prioritary_coexistion_result(character, destination)) {
        case CoexistionResult::WON:
            cout << "WON" << endl;
            register_move(character, direction, ongoing_action, true);
            break;
        case CoexistionResult::DEFEATED:
            cout << "DEFEATED" << endl;
            register_destruction(character, ongoing_action);
            break;
        case CoexistionResult::MELTED:
            cout << "MELTED" << endl;
            register_destruction(character, ongoing_action);
            break;
        case CoexistionResult::SINKED:
            cout << "SINKED" << endl;
            register_destruction(character, ongoing_action);
            for (Character * character: board->at(destination)) register_destruction(character, ongoing_action);
            break;
        case CoexistionResult::OPENED:
            cout << "OPENED" << endl;
            register_destruction(character, ongoing_action);
            for (Character * character: board->at(destination))
                if (has_property(character, Property::SHUT)) register_destruction(character, ongoing_action);
            break;
        case CoexistionResult::COEXISTED:
            cout << "COEXISTED" << endl;
            register_move(character, direction, ongoing_action, false);
            break;
    }
}

void Game :: register_destruction (Character * character, Action * ongoing_action) {
    cout << "destruction of " << *character << endl;
    board->remove_character(character);
    ongoing_action->add_destroyed_character(character);
    if (
        has_property(character, Property::YOU) &&
        std::find(players.begin(), players.end(), character) != players.end()
    ) {
        players.erase(
            std::remove(players.begin(), players.end(), character),
            players.end()
        );
        if (players.size() == 0) terminate(false);
    }
}

void Game :: register_move (Character * character, Direction direction, Action * ongoing_action, bool is_move_winning) {
    cout << "moving of " << *character << " towards " << direction << endl;
    character->move(direction);    
    board->set(*character);
    ongoing_action->add_moved_character(character);
    if (is_move_winning) terminate(true);
}


void Game :: undo () {
    if (!done_actions.empty()) {
        Action * last_done_action = done_actions.top();
        replay_action_movings(last_done_action, true);
        for (Character * character: last_done_action->get_destroyed_characters()) {
            board->set(*character);
            if (
                has_property(character, Property::YOU) &&
                std::find(players.begin(), players.end(), character) == players.end()
            ) players.push_back(character);
        }
        done_actions.pop();
        undone_actions.push(last_done_action);
    }
}

void Game :: redo () {
    if (!undone_actions.empty()) {
        Action * last_undone_action = undone_actions.top();
        replay_action_movings(last_undone_action, false);
        for (Character * character: last_undone_action->get_destroyed_characters()) {
            board->remove_character(character);
        }
        undone_actions.pop();
        done_actions.push(last_undone_action);
    }
}

void Game :: replay_action_movings (Action * action, bool undoing) {
    Direction moving_direction = action->get_direction();
    if (undoing) moving_direction = !moving_direction;
    for (Character * character: action->get_moved_characters()) {
        board->remove_character(character);
        character->move(moving_direction);
        board->set(*character);
    }
}
