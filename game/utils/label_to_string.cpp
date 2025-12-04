#include "label_to_string.hpp"
#include <iostream>


std::string LabelToString::to_string(Label label) {
    switch (label) {
        case Label::BABA:        return "BABA";
        case Label::FLAG:        return "FLAG";
        case Label::GRASS:       return "GRASS";
        case Label::LAVA:        return "LAVA";
        case Label::ROCK:        return "ROCK";
        case Label::SKULL:       return "SKULL";
        case Label::WALL:        return "WALL";
        case Label::WATER:       return "WATER";

        case Label::WORD_BABA:   return "TEXT_BABA";
        case Label::WORD_FLAG:   return "TEXT_FLAG";
        case Label::WORD_GRASS:  return "TEXT_GRASS";
        case Label::WORD_LAVA:   return "TEXT_LAVA";
        case Label::WORD_ROCK:   return "TEXT_ROCK";
        case Label::WORD_SKULL:  return "TEXT_SKULL";
        case Label::WORD_WALL:   return "TEXT_WALL";
        case Label::WORD_WATER:  return "TEXT_WATER";

        case Label::WORD_IS:     return "IS";

        case Label::WORD_DEFEAT: return "DEFEAT";
        case Label::WORD_HOT:    return "HOT";
        case Label::WORD_PUSH:   return "PUSH";
        case Label::WORD_SINK:   return "SINK";
        case Label::WORD_STOP:   return "STOP";
        case Label::WORD_WIN:    return "WIN";
        case Label::WORD_YOU:    return "YOU";

        default:                 return "UNKNOWN";
    }
}