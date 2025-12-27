#ifndef _LABEL_TO_STRING
#define _LABEL_TO_STRING

#include "../model/characters/labels.hpp"
#include <iostream>

class LabelToString {
public:
    static std::string to_string(Label label);
};

#endif