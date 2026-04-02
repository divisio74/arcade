NAME        = arcade

CXX         = g++
CXXFLAGS    = -std=c++20 -Wall -Wextra -fno-gnu-unique
CXXFLAGSLIB = -shared -fPIC -fno-gnu-unique -std=c++20 -Wall -Wextra

SRC         = main.cpp \
              src/Vm/Vm.cpp

OBJ         = $(SRC:.cpp=.o)

LIB_DIR     = Lib

LIBS        = $(LIB_DIR)/NCurse.so \
              $(LIB_DIR)/Menue.so \
              $(LIB_DIR)/Snake.so

all: $(LIBS) $(NAME)

$(LIB_DIR)/NCurse.so: src/libs/NCurse.cpp
	$(CXX) $(CXXFLAGSLIB) -o $@ $< -lncurses

$(LIB_DIR)/Menue.so: src/games/Menue.cpp
	$(CXX) $(CXXFLAGSLIB) -o $@ $<

$(LIB_DIR)/Snake.so: src/games/Snake.cpp
	$(CXX) $(CXXFLAGSLIB) -o $@ $<

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) -ldl

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(LIBS)

re: fclean all

