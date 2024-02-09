NAME = philo

CC = cc
FLAGS = -Wall -Werror -Wextra -g3

SRC_DIR = ./src/
SRC = main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -I. -I./includes/ -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean