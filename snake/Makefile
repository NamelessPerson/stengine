#----------------------------------------------------------
# TERMINAL SNAKE
# 
# This makefile compiles the snake game which is dependant
# on the STEngine and STUtil Libraries. Suggested to use
# top level makefile
#----------------------------------------------------------

OUTPUT 		= snake

SRC_CPP 	= main.cpp
SRC_DIR 	= src/
OUTPUT_DIR 	= bin/

SRC 		= $(addprefix $(SRC_DIR), $(SRC_CPP))
OBJ 		= $(addprefix $(OUTPUT_DIR), $(SRC_CPP:.cpp=.o))

CXX 		= g++
CXXFLAGS 	+= -std=c++0x -Wall -Werror -I. -I../stengine/include/ -g
LDFLAGS 	+= -Wall -Werror -L../stengine/lib/ -lstengine
RM 			= rm -f -d

all: $(OUTPUT)

$(OUTPUT): $(OBJ)
	g++ $(OBJ) $(LDFLAGS) -o $(OUTPUT)

$(OUTPUT_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(@D)
	$(CXX) $< -c $(CXXFLAGS) -o $@

clean:
	$(RM) $(OBJ)

test: all

fclean: clean
	$(RM) $(OUTPUT)
	$(RM) -r $(OUTPUT_DIR)