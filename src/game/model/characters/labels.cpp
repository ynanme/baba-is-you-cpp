#include <iostream>
#include "game/model/characters/labels.hpp"

using namespace std;


ostream& operator << (ostream& out, Label label) {

    switch (label) {

        case Label::BABA:        return out << "BABA";
        case Label::FLAG:        return out << "FLAG";
        case Label::GRASS:       return out << "GRASS";
        case Label::LAVA:        return out << "LAVA";
        case Label::ROCK:        return out << "ROCK";
        case Label::SKULL:       return out << "SKULL";
        case Label::WALL:        return out << "WALL";
        case Label::WATER:       return out << "WATER";

        case Label::WORD_BABA:   return out << "TEXT_BABA";
        case Label::WORD_FLAG:   return out << "TEXT_FLAG";
        case Label::WORD_GRASS:  return out << "TEXT_GRASS";
        case Label::WORD_LAVA:   return out << "TEXT_LAVA";
        case Label::WORD_ROCK:   return out << "TEXT_ROCK";
        case Label::WORD_SKULL:  return out << "TEXT_SKULL";
        case Label::WORD_WALL:   return out << "TEXT_WALL";
        case Label::WORD_WATER:  return out << "TEXT_WATER";
        case Label::WORD_KEY:    return out << "TEXT_KEY";
        case Label::WORD_DOOR:   return out << "TEXT_DOOR";

        case Label::WORD_IS:     return out << "IS";

        case Label::WORD_DEFEAT: return out << "DEFEAT";
        case Label::WORD_HOT:    return out << "HOT";
        case Label::WORD_PUSH:   return out << "PUSH";
        case Label::WORD_SINK:   return out << "SINK";
        case Label::WORD_STOP:   return out << "STOP";
        case Label::WORD_WIN:    return out << "WIN";
        case Label::WORD_YOU:    return out << "YOU";
        case Label::WORD_OPEN:        return out << "OPEN";

    }

    return out;

}