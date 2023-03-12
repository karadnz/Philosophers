SRCS	=	main_bonus.c utils_bonus.c \
			init_bonus.c est_bonus.c

OBJS	= $(SRCS:.c=.o)

NAME	= philo_bonus

GCC	= gcc

FLAGS =  -Wall -Wextra -Werror

INCLUDE	= -lpthread

HEADER	= philo_bonus.h


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