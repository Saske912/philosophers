NAME = philo_two
FILE = philo_two.c death_check.c helps.c isolate.c lists.c utils.c
HEADER = philo_two.h
FLAGS = -Wall -Wextra -Werror
OBJ = $(FILE:.c=.o)

$(NAME):
	gcc $(FLAGS) $(FILE) $(HEADER) -pthread -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all