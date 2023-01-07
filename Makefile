NAME =		philo
CC =		gcc
FLAGS =		-Wall -Werror -Wextra -pthread
RM =		rm -rf

SRC =		philo.c \
			loop.c \
			philo_utils.c

OBJECTS =	$(SRC:.c=.o)

.c.o:
			$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJECTS) philo.h
			$(CC) $(FLAGS) $(OBJECTS) -fsanitize=thread -o $(NAME)

clean:
			$(RM) $(OBJECTS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

linux:	$(OBJECTS) philo.h
			$(CC) $(FLAGS) $(OBJECTS) -lpthread -o $(NAME)

.PHONY: all clean fclean re linux
