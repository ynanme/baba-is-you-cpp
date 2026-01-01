#include "game/model/core/game.hpp"



void Game :: update (const RuleChange & event) {
    for (const Rule & new_rule: event.new_rules) {
        if (rules_history.find(new_rule) == rules_history.end())
            apply_rule(new_rule);
    }
    for (const Rule & old_rule: event.old_rules) {
        if (rules_history.find(old_rule) != rules_history.end())
            unapply_rule(old_rule);
    }
}


void Game :: apply_rule (Rule rule) {
    if (WORDS_PROPERTIES.find(get<2>(rule)) != WORDS_PROPERTIES.end())
        add_property(WORDS_SUBJECTS[get<0>(rule)], WORDS_PROPERTIES[get<2>(rule)]);
    else
        transfer_properties(WORDS_SUBJECTS[get<2>(rule)], WORDS_SUBJECTS[get<0>(rule)]);
    rules_history.insert(rule);
}


void Game :: unapply_rule (Rule rule) {
    if (WORDS_PROPERTIES.find(get<2>(rule)) != WORDS_PROPERTIES.end())
        remove_property(WORDS_SUBJECTS[get<0>(rule)], WORDS_PROPERTIES[get<2>(rule)]);
    else
        retrieve_properties(WORDS_SUBJECTS[get<2>(rule)], WORDS_SUBJECTS[get<0>(rule)]);
    rules_history.erase(rule);
}


void Game :: add_property (Label label, Property property) {
    properties[label].insert(property);
    if (property == Property::YOU) make_player(label);
    check_for_tautologies(label);
}


void Game :: remove_property (Label label, Property property) {
    properties[label].erase(property);
    if (property == Property::YOU) unmake_player(label);
}


void Game :: make_player (Label label) {
    for (Character * character : characters) {
        if (
            character->get_label() == label &&
            std::find(players.begin(), players.end(), character) == players.end()
        ) {
            players.push_back(character);
        }
    }
}


void Game :: unmake_player (Label label) {
    for (Character * character : characters) {
        if (character->get_label() == label) {
            players.erase(remove(players.begin(), players.end(), character), players.end());
        }
    }
}


void Game :: transfer_properties (Label of, Label to) {
    for (Property property: properties[of])
        add_property(to, property);
}


void Game :: retrieve_properties (Label of, Label to) {
    for (Property property: properties[of])
        remove_property(to, property);
}


void Game :: check_for_tautologies (Label label) {
    if (has_property(label, Property::YOU) && has_property(label, Property::DEFEAT))
        terminate(false);
    if (has_property(label, Property::YOU) && has_property(label, Property::WIN))
        terminate(true);
}
