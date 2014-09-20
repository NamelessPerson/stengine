NAME = main
TARBALL = jphilli2-$(NAME).tar.gz
SRC = main.cpp Debug.cpp
TSRC = unit_test.cpp Debug.cpp
OBJ = $(SRC:.cpp=.o)
TOBJ = $(TSRC:.cpp=.o)
RM = rm -f

all: $(OBJ)
	g++ $(OBJ) -o $(NAME) -mwin32

test: $(TOBJ)
	g++ $(TOBJ) -o test

clean:
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.o
	-$(RM) *.core
	-$(RM) *.stackdump

fclean:	clean
	-$(RM) $(NAME)
	-$(RM) test

re: fclean all

submit: fclean
	tar cvzf $(TARBALL) *
