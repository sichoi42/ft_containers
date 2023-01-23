NAME			= simple_test

CPP				= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
INC = -I ../containers -I ../implements -I ../utils -I ./vector/utils -I ./map/utils

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
CHECK = \033[0;32m\xE2\x9C\x94\033[0m

FUNC = ./map/erase2

SRC = $(addsuffix .cpp, $(FUNC))
OBJ = $(addsuffix .o, $(FUNC))

%.o: %.cpp
	@echo "$(NAME): $(GREEN) compiling... $< $(CHECK) $(RESET)"
	@$(CPP) $(CXXFLAGS) $(INC) -o $@ -c $<

$(NAME): $(OBJ)
	@$(CPP) $(CXXFLAGS) $(INC) -o $(NAME) $(OBJ)
	@echo "$(NAME): $(GREEN) $(NAME) was created! $(CHECK) $(RESET)"

all: $(NAME)

clean :
	@rm -rf $(OBJ)
	@echo "$(NAME): $(RED) object files were deleted $(RESET)"

fclean:	clean
	@rm -rf $(NAME)
	@echo "$(NAME): $(RED) $(NAME) was deleted $(RESET)"

re :
	@$(MAKE) fclean
	@$(MAKE) all

stdflags:
	@$(eval CXXFLAGS += -D USING_STD)

std: stdflags all

debugflags:
	@$(eval CXXFLAGS += -g -fsanitize=address)

debug: debugflags all

ftout:
	@$(MAKE) fclean
	@$(MAKE)
	@echo "$(NAME): $(GREEN) ftout created! $(CHECK) $(RESET)"
	@./$(NAME) > ft.out

stdout:
	@$(MAKE) fclean
	@$(MAKE) std
	@echo "$(NAME): $(GREEN) stdout created! $(CHECK) $(RESET)"
	@./$(NAME) > std.out

out:
	@$(MAKE) stdout
	@$(MAKE) ftout

diff:
	@diff ft.out std.out
