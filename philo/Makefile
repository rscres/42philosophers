NAME = philo

CC = cc
FLAGS = -Wall -Werror -Wextra -g3 
# -MMD -MP

SRC =	main.c				\
		eat.c				\
		init.c				\
		print.c				\
		checks.c			\
		routine.c			\
		get_time.c			\
		supervisor.c		\
		utils_libft.c		\
		input_validation.c

OBJ_DIR = obj
OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

INC = ./includes/

# DEP_DIR = dep
# DEP = $(patsubst $(OBJ_DIR)/%.o,$(DEP_DIR)/%.d,$(OBJ))

all: directory $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -pthread $(OBJ) -o $(NAME)

directory: $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# $(DEP_DIR):
# 	mkdir -p $(DEP_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(FLAGS) -pthread -c $< -o $@

# -includes: $(DEP)

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all