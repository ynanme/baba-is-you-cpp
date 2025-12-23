#ifndef _PROPERTIES
#define _PROPERTIES



enum class Property {
    YOU,
    PUSH,
    STOP,
    WIN,
    DEFEAT,
    HOT,
    MELT,
    SINK
};


enum CoexistionResult {
    WON = 1,
    DEFEATED = 2,
    MELTED = 2,
    SINKED = 3,
    COEXISTED = 0
};



#endif