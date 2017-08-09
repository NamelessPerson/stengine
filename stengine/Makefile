#----------------------------------------------------------
# SMALL TERMINAL ENGINE
# 
# 
#----------------------------------------------------------

NAME 		= stengine
OUTPUT 		= $(addprefix lib/lib, $(addsuffix .a, $(NAME)))
TEST 		= test

SRC_CPP 	= print.cpp
SRC_DIR 	= src/
OUTPUT_DIR 	= bin/

SRC 		= $(addprefix $(SRC_DIR), $(SRC_CPP))
OBJ 		= $(addprefix $(OUTPUT_DIR), $(SRC_CPP:.cpp=.o))
TEST_SRC	= test.cpp

CXX 		= g++
CXXFLAGS 	+= -std=c++0x -Wall -Werror -I./include
LDFLAGS 	+= -Wall -Werror
TEST_LDFLAGS= -Llib/ -lstengine
RM 			= rm -f -d

all: $(OUTPUT)

$(OUTPUT): $(OBJ)
	ar -rcs $(OUTPUT) $(OBJ)

$(OUTPUT_DIR)%.o: $(SRC_DIR)%.cpp
	mkdir -p $(@D)
	$(CXX) $< -c $(CXXFLAGS) -o $@

test: all
	g++ $(TEST_SRC) -o $(TEST) $(CXXFLAGS) $(LDFLAGS) $(TEST_LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(OUTPUT)
	$(RM) $(TEST)
	$(RM) -r $(OUTPUT_DIR)