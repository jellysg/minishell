CC = cc
CFLAGS += -Wall -Wextra -Werror
LDFLAGS += -L./libft -L./printf
LIBS += -lft -lftprintf -lreadline

SRC_DIR = ./src
OBJ_DIR = ./minishell_objs

SRC := $(wildcard $(SRC_DIR)/*.c)

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

EXEC_NAME = minishell

all: libft printf $(EXEC_NAME)

.PHONY: all clean fclean re libft printf

$(EXEC_NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC_NAME) $(LDFLAGS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c test.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

libft:
	$(MAKE) -C ./libft

printf:
	$(MAKE) -C ./printf

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C ./libft clean
	$(MAKE) -C ./printf clean

fclean: clean
	$(RM) $(EXEC_NAME)
	$(MAKE) -C ./libft fclean
	$(MAKE) -C ./printf fclean

re: fclean all