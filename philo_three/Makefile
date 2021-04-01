NAME = philo_three
FILE = philo_three.c helps.c isolate.c lists.c utils.c death_check.c
CFLAGS = -Wall -Wextra -Werror
HEADER = philo_three.h
OBJ = $(FILE:.c=.o)

$(NAME):
	gcc $(CFLAGS) $(FILE) $(HEADER) -pthread -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
