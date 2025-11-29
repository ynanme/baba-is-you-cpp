#include "../model/core/board.hpp"
#include "../model/characters/character.hpp"  
#include "../utils/geometry.hpp"
#include "../utils/label_to_string.cpp"
#include "../model/characters/labels.hpp"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;


class TestCharacter : public Character {
public:
    TestCharacter(const Label& l, int x, int y)
        : Character(Position(x, y),         
                    CollisionResult::COEXISTED,       
                    l)                   
    {}

    Label get_label() const { return Character::get_label(); }
    string get_name() const { return LabelToString::to_string(get_label()); }
    
};

// Fonction utilitaire pour afficher un vector
void print_cell(const vector<Character*>& cell) {
    cout << "[ ";
    for (Character* c : cell) {
        if (c) cout << static_cast<TestCharacter*>(c)->get_name() << " ";
    }
    cout << "]" << endl;
}

int main() {
    cout << "=== Tests de la classe Board ===\n\n";

    Board board(5, 5); 

    // Test 1 : dimensions
    cout << "Test 1 : dimensions du plateau\n";
    assert(board.get_width() == 5);
    assert(board.get_height() == 5);
    cout << "OK\n\n";

    // Test 2 : case vide → retourne bien une référence vide stable
    cout << "Test 2 : case vide\n";
    Position p00(0, 0);
    const vector<Character*>& empty_cell = board.at(p00);
    assert(empty_cell.empty());
    assert(&board.at(p00) == &board.at(p00));  // même référence vide statique
    cout << "OK : case vide correcte\n\n";

    // Test 3 : ajout d'un personnage
    cout << "Test 3 : ajout d'un personnage\n";
    TestCharacter baba(Label::BABA, 1, 1);
    board.add_character(&baba);

    const vector<Character*>& cell11 = board.at(Position(1, 1));
    assert(cell11.size() == 1);
    assert(cell11[0] == &baba);
    cout << "OK : BABA bien placé en (1,1)\n\n";

    // Test 4 : get_cell() retourne bien une référence modifiable
    cout << "Test 4 : get_cell() modifiable\n";
    vector<Character*>& modifiable_cell = board.get_cell(Position(1, 1));
    TestCharacter rock(Label::ROCK, 1, 1);
    modifiable_cell.push_back(&rock);  // on ajoute directement !

    assert(board.at(Position(1, 1)).size() == 2);
    cout << "OK : plusieurs objets dans la même case\n\n";

    // Test 5 : in_bounds()
    cout << "Test 5 : in_bounds()\n";
    assert(board.in_bounds(Position(0, 0)) == true);
    assert(board.in_bounds(Position(4, 4)) == true);
    assert(board.in_bounds(Position(5, 5)) == false);
    assert(board.in_bounds(Position(-1, 2)) == false);
    cout << "OK : limites correctes\n\n";

    // Test 6 : get_neighbor() — doit lancer exception si hors limite
    cout << "Test 6 : get_neighbor() hors limite\n";
    TestCharacter edge(Label::BABA, 4, 4);
    board.add_character(&edge);

    bool exception_thrown = false;
    try {
        board.get_neighbor(edge, Direction::RIGHT);
    } catch (const out_of_range&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    cout << "OK : exception bien lancée hors limites\n\n";

    // Test 7 : set() évite les doublons
    cout << "Test 7 : set() évite les doublons\n";
    board.set(baba);        // déjà présent
    board.set(baba);        // encore une fois
    assert(board.at(Position(1, 1)).size() == 2);  // pas devenu 3
    cout << "OK : pas de doublon avec set()\n\n";

    // Test 8 : remove_character()
    cout << "Test 8 : suppression d'un personnage\n";
    board.remove_character(&rock);
    const auto& final_cell = board.at(Position(1, 1));
    assert(final_cell.size() == 1);
    assert(final_cell[0] == &baba);
    cout << "OK : ROCK supprimé, BABA reste\n\n";

    // Test 9 : plusieurs personnages sur bords opposés
    cout << "Test 9 : personnages aux coins\n";
    TestCharacter keke(Label::WALL, 0, 0);
    TestCharacter me(Label::BABA, 4, 4);
    board.add_character(&keke);
    board.add_character(&me);

    assert(!board.at(Position(0, 0)).empty());
    assert(!board.at(Position(4, 4)).empty());
    cout << "OK : coins bien occupés\n\n";

    cout << "TOUS LES TESTS SONT PASSÉS !\n";

    return 0;
}

