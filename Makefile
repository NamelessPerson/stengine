SNAKE = snake/
ENGINE = stengine/
MAKEFLAGS += --no-print-directory

all: snake

.PHONY: snake
snake: engine
	$(MAKE) -C $(SNAKE)

.PHONY: engine
engine:
	$(MAKE) -C $(ENGINE)

clean:
	$(MAKE) -C $(SNAKE) clean
	$(MAKE) -C $(ENGINE) clean

fclean:
	$(MAKE) -C $(SNAKE) fclean
	$(MAKE) -C $(ENGINE) fclean


run:
	./snake/snake