
SRCS	=	main.c utils.c init.c est.c

BSRCS	=	bonus/main_bonus.c bonus/utils_bonus.c \
			bonus/init_bonus.c bonus/est_bonus.c

OBJS	= $(SRCS:.c=.o)

BOBJS	= $(BSRCS:.c=.o)

NAME	= philo

BNAME	= philo_bonus

GCC	= gcc

FLAGS =  

INCLUDE	= -lpthread

HEADER	= philo.h




all:	$(NAME)

bonus:	$(BNAME)

.PHONY:	clean fclean re bonus bclean

$(NAME): $(OBJS)
	$(GCC) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)

$(BNAME): $(BOBJS)
	$(GCC) $(INCLUDE) $(FLAGS) -o $(BNAME) $(BOBJS)

clean:
	rm -f $(OBJS) $(BOBJS)

fclean: clean
	rm -f $(NAME) $(BNAME)

re: fclean all

%.o: %.c $(HEADER)
	$(GCC) $(FLAGS) -c $<  -o $(<:.c=.o)