SRCS	=	main.c utils.c init.c est.c

OBJS	= $(SRCS:.c=.o)

NAME	= philo

GCC	= gcc

FLAGS =  -Wall -Wextra -Werror

INCLUDE	= -lpthread

HEADER	= philo.h


all:	$(NAME)

$(NAME): $(OBJS)
	$(GCC) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c $(HEADER)
	$(GCC) $(FLAGS) -c $<  -o $(<:.c=.o)

.PHONY:	clean fclean re