NAME = philo

CC = cc
FLAGS = -Wall -Werror- Wextra -g3 -03

SRC_DIR = ./src/
SRC = main.c

OBJ = $(SRC:.c=.o)

LIBS = -Llibft -lft

LIBFT = ./libft/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(LIBFT):
	@echo Creating Libft.
	@make -C libft
	@echo Libft done.

%.o: %.c
	$(CC) $(FLAGS) -I. -I./includes/ -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean