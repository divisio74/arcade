NAME        = arcade

CXX         = g++
CXXFLAGS    = -std=c++20 -Wall -Wextra -fno-gnu-unique
CXXFLAGSLIB = -shared -fPIC -fno-gnu-unique -std=c++20 -Wall -Wextra

SRC         = main.cpp \
              src/Vm/Vm.cpp \
              src/Vm/Libdl.cpp \
              src/Vm/CustomError.cpp

OBJ         = $(SRC:.cpp=.o)

LIB_DIR     = lib

GRAPHICALS  = $(LIB_DIR)/arcade_ncurses.so \
              $(LIB_DIR)/arcade_csfml.so \
			  $(LIB_DIR)/arcade_sdl2.so

GAMES       = $(LIB_DIR)/arcade_menue.so \
              $(LIB_DIR)/arcade_snake.so \
			  $(LIB_DIR)/arcade_pacman.so \

all: core games graphicals


core: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) -ldl


games: $(GAMES)

$(LIB_DIR)/arcade_menue.so: src/games/Menue.cpp
	mkdir -p $(LIB_DIR)
	$(CXX) $(CXXFLAGSLIB) -o $@ $<

$(LIB_DIR)/arcade_pacman.so: src/games/Pacman.cpp
	mkdir -p $(LIB_DIR)
	$(CXX) $(CXXFLAGSLIB) -o $@ $<

$(LIB_DIR)/arcade_snake.so: src/games/Snake.cpp
	mkdir -p $(LIB_DIR)
	$(CXX) $(CXXFLAGSLIB) -o $@ $<

graphicals: $(GRAPHICALS)

$(LIB_DIR)/arcade_sdl2.so: src/libs/SDL2.cpp
	mkdir -p $(LIB_DIR)
	$(CXX) $(CXXFLAGSLIB) -o $@ $< -lSDL2 -lSDL2_ttf

$(LIB_DIR)/arcade_ncurses.so: src/libs/NCurse.cpp
	mkdir -p $(LIB_DIR)
	$(CXX) $(CXXFLAGSLIB) -o $@ $< -lncurses

$(LIB_DIR)/arcade_csfml.so: src/libs/CSFML.cpp
	mkdir -p $(LIB_DIR)
	$(CXX) $(CXXFLAGSLIB) -o $@ $< -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf $(LIB_DIR)

re: fclean all

