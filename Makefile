
SRCS	= main.c utils.c init.c est.c

OBJS	= $(SRCS:.c=.o)

NAME	= philo

GCC	= gcc

FLAGS =  -Wall -Wextra -Werror  -g

INCLUDE	= -lpthread

HEADER	= philo.h




all:	$(NAME)

.PHONY:	clean fclean re bonus bench bclean

$(NAME): $(OBJS)
	$(GCC) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

%.o: %.c $(HEADER)
	$(GCC) $(FLAGS) -c $<  -o $(<:.c=.o)
