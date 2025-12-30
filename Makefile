CC = g++ -Wall -std=c++11 -I./src
CCO = $(CC) -c $< -o $@

SRC = src/
BUILD = build/
UTILS = $(SRC)game/utils/
UTILS_BUILD = $(BUILD)game/utils/
CHARACTERS = $(SRC)game/model/characters/
CHARACTERS_BUILD = $(BUILD)game/model/characters/
LOADER = $(SRC)game/loader/
LOADER_BUILD = $(BUILD)game/loader/
CORE = $(SRC)game/model/core/
CORE_BUILD = $(BUILD)game/model/core/
VIEW = $(SRC)game/view/
VIEW_BUILD = $(BUILD)game/view/

OBJECTS = \
	$(UTILS_BUILD)geometry.o \
	$(CHARACTERS_BUILD)labels.o \
	$(CHARACTERS_BUILD)character.o \
	$(LOADER_BUILD)loader.o \
	$(CORE_BUILD)events.o \
	$(CORE_BUILD)action.o \
	$(CORE_BUILD)ruler.o \
	$(CORE_BUILD)board.o \
	$(CORE_BUILD)game_env.o \
	$(CORE_BUILD)game_actions.o \
	$(CORE_BUILD)rules_managing.o \
	$(VIEW_BUILD)menu.o \
	$(VIEW_BUILD)texture_manager.o \
	$(VIEW_BUILD)character_view.o \
	$(VIEW_BUILD)board_view.o \
	$(BUILD)main.o


all : $(OBJECTS)
	@mkdir -p $(BUILD)
	$(CC) -o otosan $(OBJECTS) -lsfml-graphics -lsfml-window -lsfml-system
	./otosan

$(UTILS_BUILD)geometry.o : $(UTILS)geometry.cpp $(UTILS)geometry.hpp
	@mkdir -p $(UTILS_BUILD)
	$(CCO)

$(UTILS_BUILD)observer_pattern.o : $(UTILS)observer_pattern.tpp $(UTILS)observer_pattern.hpp
	@mkdir -p $(UTILS_BUILD)
	$(CCO)

$(CHARACTERS_BUILD)labels.o : $(CHARACTERS)labels.cpp $(CHARACTERS)labels.hpp
	@mkdir -p $(CHARACTERS_BUILD)
	$(CCO)

$(CHARACTERS_BUILD)character.o : $(CHARACTERS)character.cpp $(CHARACTERS)character.hpp $(CHARACTERS)labels.hpp $(UTILS)geometry.hpp
	@mkdir -p $(CHARACTERS_BUILD)
	$(CCO)

$(LOADER_BUILD)loader.o : $(LOADER)loader.cpp $(LOADER)loader.hpp $(CHARACTERS)labels.hpp $(CORE)game.hpp
	@mkdir -p $(LOADER_BUILD)
	$(CCO)

$(CORE_BUILD)properties.o : $(CORE)properties.hpp
	@mkdir -p $(CORE_BUILD)
	$(CCO)

$(CORE_BUILD)events.o : $(CORE)events.cpp $(CORE)events.hpp $(CHARACTERS)character.hpp $(CHARACTERS)labels.hpp
	@mkdir -p $(CORE_BUILD)
	$(CCO)

$(CORE_BUILD)action.o : $(CORE)action.cpp $(CORE)action.hpp $(CHARACTERS)character.hpp $(UTILS)geometry.hpp
	@mkdir -p $(CORE_BUILD)
	$(CCO)

$(CORE_BUILD)ruler.o : $(CORE)ruler.cpp $(CORE)ruler.hpp $(CHARACTERS)character.hpp $(CHARACTERS)labels.hpp $(CORE)events.hpp $(CORE)board.hpp
	@mkdir -p $(CORE_BUILD)
	$(CCO)

$(CORE_BUILD)board.o : $(CORE)board.cpp $(CORE)board.hpp $(CHARACTERS)character.hpp $(CORE)events.hpp $(UTILS)geometry.hpp $(UTILS)observer_pattern.hpp
	@mkdir -p $(CORE_BUILD)
	$(CCO)

$(CORE_BUILD)game_env.o : $(CORE)game_env.cpp $(CORE)game.hpp $(CHARACTERS)character.hpp $(CHARACTERS)labels.hpp $(CORE)properties.hpp $(CORE)ruler.hpp $(CORE)board.hpp
	@mkdir -p $(CORE_BUILD)
	$(CCO)

$(CORE_BUILD)game_actions.o : $(CORE)game_actions.cpp $(CORE)game.hpp $(CHARACTERS)character.hpp $(CORE)properties.hpp $(CORE)action.hpp $(UTILS)geometry.hpp
	@mkdir -p $(CORE_BUILD)
	$(CCO)

$(CORE_BUILD)rules_managing.o : $(CORE)rules_managing.cpp $(CORE)game.hpp $(CHARACTERS)character.hpp $(CORE)properties.hpp $(CHARACTERS)labels.hpp $(CORE)events.hpp
	@mkdir -p $(CORE_BUILD)
	$(CCO)

$(VIEW_BUILD)sprite_info.o : $(VIEW)sprite_info.hpp
	@mkdir -p $(VIEW_BUILD)
	$(CCO)

$(VIEW_BUILD)menu.o : $(VIEW)menu.cpp $(VIEW)menu.hpp
	@mkdir -p $(VIEW_BUILD)
	$(CCO)

$(VIEW_BUILD)texture_manager.o : $(VIEW)texture_manager.cpp $(VIEW)texture_manager.hpp $(VIEW)sprite_info.hpp $(CHARACTERS)labels.hpp
	@mkdir -p $(VIEW_BUILD)
	$(CCO)

$(VIEW_BUILD)character_view.o : $(VIEW)character_view.cpp $(VIEW)character_view.hpp $(VIEW)texture_manager.hpp $(CHARACTERS)character.hpp
	@mkdir -p $(VIEW_BUILD)
	$(CCO)

$(VIEW_BUILD)board_view.o : $(VIEW)board_view.cpp $(VIEW)board_view.hpp $(VIEW)texture_manager.hpp $(VIEW)character_view.hpp $(UTILS)geometry.hpp $(CORE)board.hpp $(CORE)game.hpp
	@mkdir -p $(VIEW_BUILD)
	$(CCO)

$(BUILD)main.o : $(SRC)main.cpp $(CORE)board.hpp $(CORE)game.hpp $(LOADER)loader.hpp $(VIEW)menu.hpp $(VIEW)board_view.hpp
	@mkdir -p $(BUILD)
	$(CCO)

clean :
	rm -rf $(BUILD) otosan