NAME = philo

CFLAGS = -O3 -Wall -Wextra -Werror

MLX = mlx

HEADER = philo.h

CC = gcc

SRC =	philo.c	tools.c	init.c	cheker.c	libftools.c	lst.c

OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -g  -pthread

run:
	./a.out 4 410 200 200

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

me:
	@echo $(NAME)
	@echo "#    #  ####   ####  #####   #    #  ####   ####  #####  "
	@echo "##   # #    # #    # #    #  ##   # #    # #    # #    # "
	@echo "# #  # #    # #    # #####   # #  # #    # #    # #####  "
	@echo "#  # # #    # #    # #    #  #  # # #    # #    # #    # "
	@echo "#   ## #    # #    # #    #  #   ## #    # #    # #    # "
	@echo "#    #  ####   ####  #####   #    #  ####   ####  #####  "

norm:
	norminette $(SRC) $(HEADER)

leaks:
	leaks $(NAME) > leak