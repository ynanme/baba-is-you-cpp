#include "character.hpp"


ostream& operator << (ostream& out, CollisionResult collision_handling) {
    switch (collision_handling) {
        case CollisionResult::AWARDED:
            return out << "AWARDED";
        case CollisionResult::BLOCKED:
            return out << "BLOCKED";
        case CollisionResult::COEXISTED:
            return out << "COEXISTED";
        case CollisionResult::DEFEATED:
            return out << "DEFEATED";
        case CollisionResult::SHIFTED:
            return out << "SHIFTED";
    }
    return out;
}