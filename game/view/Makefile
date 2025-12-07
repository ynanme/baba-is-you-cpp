# Nom de l'exécutable final
TARGET = baba

# Compilateur C++
CXX = g++

# Options du compilateur (standard C++11 et chemins d'inclusion)
CXXFLAGS = -std=c++11 -Iinclude

# Bibliothèques SFML
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Liste des fichiers sources à compiler
# Note : L'utilisation de jokers (*) simplifie l'inclusion de tous les .cpp dans les dossiers spécifiés
SOURCES = \
    ../model/characters/labels.hpp \
    ../model/*/*.cpp \
    ../utils/*.cpp \
    ../utils/observer_pattern.hpp \
    texture_manager.cpp \
    character_view.cpp \
    board_view.cpp \
    main.cpp

# La règle 'all' est la cible par défaut
all: $(TARGET)

# Règle pour construire l'exécutable
$(TARGET):
	$(CXX) $(SOURCES) $(CXXFLAGS) $(LDFLAGS) -o $@

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(TARGET)