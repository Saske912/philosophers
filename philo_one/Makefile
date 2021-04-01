NAME = philo_one
FILE = philo_one.c helps.c lists.c isolate.c utils.c death_check.c
HEADER = philo_one.h
CFLAGS = -Wall -Wextra -Werror
OBJ = $(FILE:.c=.o)

$(NAME):
	gcc $(CFLAGS) $(FILE) $(HEADER) -pthread -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all