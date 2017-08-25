SNAKE = snake/
ENGINE = stengine/
UTIL = stutil/
MAKEFLAGS += --no-print-directory --ignore-errors
MAKECMDGOALS := $(filter-out $(firstword $(MAKECMDGOALS)), $(MAKECMDGOALS))

all: util engine snake

.PHONY: snake
snake:
	@$(MAKE) -C $(SNAKE) $(MAKECMDGOALS)

.PHONY: engine
engine:
	@$(MAKE) -C $(ENGINE) $(MAKECMDGOALS) 

.PHONY: util
util:
	@$(MAKE) -C $(UTIL) $(MAKECMDGOALS) 

%: ;