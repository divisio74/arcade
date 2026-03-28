NAME	=	arcade

CXX	=	g++
CXXFLAGS	=	-std=c++20 -Wall -Wextra
CXXFLAGSLIB =   -shared -fPIC

SRC	=	main.cpp \

LIB_NAME = TermDisplay.so \
		   FileDisplay.so \
		   countergame.so

LIB_SRC = TermDisplay.cpp \
		  FileDisplay.cpp \
		  countergame.cpp


OBJ	=	$(SRC:.cpp=.o)

all:	$(LIB_NAME) $(NAME)

%.so: %.cpp
	$(CXX) $(CXXFLAGSLIB) -o $@ $<

$(NAME):	$(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) -ldl

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME) $(LIB_NAME)

re:	fclean all

