CXX     = g++
CXXFLAGS = -Wall -std=c++11

BUILD_DIR = build

# Trouve automatiquement tous les .cpp
SRC := $(shell find game -name "*.cpp")

# Transforme le chemin des .cpp en .o dans build
OBJ := $(patsubst game/%.cpp,$(BUILD_DIR)/%.o,$(SRC))
DEP := $(OBJ:.o=.d)

# Nom de l'exécutable
TARGET = $(BUILD_DIR)/otosan

# Règle principale
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation des .cpp en .o dans build
$(BUILD_DIR)/%.o: game/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

# Inclusion des fichiers .d
-include $(DEP)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
