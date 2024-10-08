CC = cc
CFLAGS += -Wall -Wextra -Werror -g
LDFLAGS += -L./libft
LIBS += -lft -lreadline

SRC_DIR = ./src
OBJ_DIR = ./minishell_objs

SRC := $(wildcard $(SRC_DIR)/*.c)

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

EXEC_NAME = minishell

all: libft $(EXEC_NAME)
	@echo "\033[0;32m<---Everything is up to date--->\033[0m"

.PHONY: all clean fclean re libft

$(EXEC_NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC_NAME) $(LDFLAGS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c minishell.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

libft:
	@$(MAKE) -C ./libft > /dev/null

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C ./libft clean > /dev/null

fclean: clean	
	$(RM) $(EXEC_NAME)
	$(MAKE) -C ./libft fclean > /dev/null

re: fclean all
