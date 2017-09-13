#----------------------------------------------------------
# SMALL TERMINAL ENGINE
# 
# 
#----------------------------------------------------------

NAME 		= stengine
OUTPUT 		= $(addprefix lib/lib, $(addsuffix .a, $(NAME)))
TEST 		= testrun

SRC_CPP 	= engine.cpp fixedgrid.cpp
SRC_DIR 	= src/
OUTPUT_DIR 	= bin/
INCLUDE_DIR	= include/

SRC 		= $(addprefix $(SRC_DIR), $(SRC_CPP))
OBJ 		= $(addprefix $(OUTPUT_DIR), $(SRC_CPP:.cpp=.o))
TEST_SRC	= test.cpp

CXX 		= g++-7
CXXFLAGS 	+= -std=c++14 -Wall -Werror -I$(INCLUDE_DIR) -I../stutil/include -g
LDFLAGS 	+= -Wall -Werror -L../stutil/lib -lstutil
TEST_LDFLAGS= -Llib/ -lstengine
RM 			= rm -f -d

.PHONY: all
all: $(OUTPUT)

$(OUTPUT): $(OBJ)
	ar -rcs $(OUTPUT) $(OBJ)

$(OUTPUT_DIR)%.o: $(SRC_DIR)%.cpp $(INCLUDE_DIR)$(NAME)/%.h
	@mkdir -p $(@D)
	$(CXX) $< -c $(CXXFLAGS) -o $@

.PHONY: test
test: $(TEST)

$(TEST): $(OUTPUT) $(TEST_SRC)
	$(CXX) $(TEST_SRC) -o $(TEST) $(CXXFLAGS) $(LDFLAGS) $(TEST_LDFLAGS)
	./$(TEST)

clean:
	$(RM) $(OBJ)
	$(RM) *.log

fclean: clean
	$(RM) $(OUTPUT)
	$(RM) $(TEST)
	$(RM) -r $(OUTPUT_DIR)