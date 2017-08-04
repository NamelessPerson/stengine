## Makefile Conventions
#----------------------

NAME 		= snake

SRC_CPP 	= main.cpp test/test.cpp
SRC_DIR 	= src/
OUTPUT_DIR 	= bin/

SRC 		= $(addprefix $(SRC_DIR), $(SRC_CPP))
OBJ 		= $(addprefix $(OUTPUT_DIR), $(SRC_CPP:.cpp=.o))

CXX 		= g++
CXXFLAGS 	+= -std=c++0x -Wall -Werror -I.
LDFLAGS 	+= -Wall -Werror
RM 			= rm -f -d

all: $(OBJ)
	g++ $(OBJ) -o $(NAME) $(LDFLAGS)

$(OUTPUT_DIR)%.o: $(SRC_DIR)%.cpp
	mkdir -p $(@D)
	$(CXX) $< -c $(CXXFLAGS) -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) -r $(OUTPUT_DIR)