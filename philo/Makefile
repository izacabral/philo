SRCS	=	philo.c \
			validation.c \

OBJS	=	$(SRCS:.c=.o)

NAME	=	philo

CC		=	cc

RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror -g
#-fsanitize=thread

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
