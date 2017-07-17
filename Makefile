NAME = main
TEST = test

ENGINE = level.cpp game.cpp scenemanager.cpp tile.cpp gridactor.cpp \
fixedgrid.cpp dwarfcontroller.cpp dispatcher.cpp

UTIL = debug.cpp jsonparser.cpp
SRC = main.cpp $(addprefix util/src/,$(UTIL)) $(addprefix engine/src/,$(ENGINE))
TSRC = unit_test.cpp $(addprefix util/src/,$(UTIL))
OBJ = $(SRC:.cpp=.o)
TOBJ = $(TSRC:.cpp=.o)

CC = g++
CXX = g++
CXXFLAGS += -std=c++0x -Wall -Werror -I.
LDFLAGS += -Wall -Werror
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	g++ $(OBJ) -o $(NAME) -lncurses

unit: $(TEST)

$(TEST): $(TOBJ)
	g++ $(TOBJ) -o $(TEST)

clean:
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.o
	-$(RM) *.obj
	-$(RM) *.core
	-$(RM) *.stackdump
	-$(RM) util/src/*.o
	-$(RM) engine/src/*.o

fclean:	clean
	-$(RM) *.exe
	-$(RM) $(NAME)
	-$(RM) $(TEST)

re: fclean all

tre: fclean test