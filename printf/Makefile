CC = cc
CFLAGS += -Wall -Wextra -Werror

SRC_DIR = ./src
OBJ_DIR = ./objs

SRC := $(wildcard $(SRC_DIR)/*.c)

NAME = libftprintf.a
LIB = ar rc
RM = rm -f

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(NAME): $(OBJ)
	$(LIB) $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I includes

all: $(NAME)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME) 

re: fclean all

.PHONY: all clean fclean re