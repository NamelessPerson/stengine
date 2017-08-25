#----------------------------------------------------------
# SMALL TERMINAL ENGINE
# 
# 
#----------------------------------------------------------

NAME 		= stengine
OUTPUT 		= $(addprefix lib/lib, $(addsuffix .a, $(NAME)))
TEST 		= testrun

SRC_CPP 	= print.cpp
SRC_DIR 	= src/
OUTPUT_DIR 	= bin/

SRC 		= $(addprefix $(SRC_DIR), $(SRC_CPP))
OBJ 		= $(addprefix $(OUTPUT_DIR), $(SRC_CPP:.cpp=.o))
TEST_SRC	= test.cpp

CXX 		= g++
CXXFLAGS 	+= -std=c++0x -Wall -Werror -I./include -I../stutil/include -g
LDFLAGS 	+= -Wall -Werror -L../stutil/lib -lstutil
TEST_LDFLAGS= -Llib/ -lstengine
RM 			= rm -f -d

.PHONY: all
all: $(OUTPUT)

$(OUTPUT): $(OBJ)
	ar -rcs $(OUTPUT) $(OBJ)

$(OUTPUT_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(@D)
	$(CXX) $< -c $(CXXFLAGS) -o $@

.PHONY: test
test: $(TEST)

$(TEST): $(OUTPUT) $(TEST_SRC)
	g++ $(TEST_SRC) -o $(TEST) $(CXXFLAGS) $(LDFLAGS) $(TEST_LDFLAGS)
	./$(TEST)

clean:
	$(RM) $(OBJ)
	$(RM) *.log

fclean: clean
	$(RM) $(OUTPUT)
	$(RM) $(TEST)
	$(RM) -r $(OUTPUT_DIR)