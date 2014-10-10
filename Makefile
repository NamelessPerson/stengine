NAME = main
TEST = test

SRC = main.cpp
TSRC = unit_test.cpp
OBJ = $(SRC:.cpp=.o)
TOBJ = $(TSRC:.cpp=.o)

CC = g++
CXX = g++
CXXFLAGS += -std=c++11 -Wall -Werror
LDFLAGS += -Wall -Werror
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)

unit: $(TEST)

$(TEST): $(TOBJ)
	g++ $(TOBJ) -o $(TEST)

clean:
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.o
	-$(RM) *.core
	-$(RM) *.stackdump

fclean:	clean
	-$(RM) $(NAME)
	-$(RM) $(TEST)

re: fclean all

tre: fclean test