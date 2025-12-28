#ifndef _LABELS
#define _LABELS

#include <iostream>


enum class Label {

    BABA,
    FLAG,
    GRASS,
    LAVA,
    ROCK,
    SKULL,
    WALL,
    WATER,
    KEY,
    DOOR,

    WORD_BABA,
    WORD_FLAG,
    WORD_GRASS,
    WORD_LAVA,
    WORD_ROCK,
    WORD_SKULL,
    WORD_WALL,
    WORD_WATER,
    WORD_PULL,
    WORD_KEY,
    WORD_DOOR,
    WORD_SHUT,

    WORD_IS,

    WORD_DEFEAT,
    WORD_HOT,
    WORD_MELT,
    WORD_PUSH,
    WORD_SINK,
    WORD_STOP,
    WORD_WIN,
    WORD_YOU,
    WORD_OPEN,

    NONE
    
};


enum class Category {
    OBJECT,
    WORD
};


std::ostream& operator << (std::ostream& out, Label label);


#endif