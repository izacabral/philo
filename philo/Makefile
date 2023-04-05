SRCS	=	philo.c \
			validation.c \
			init.c \
			routine.c \
			monitor.c \
			times_msgs.c \
			destroy_free.c \

OBJS	=	$(SRCS:.c=.o)

NAME	=	philo

CC		=	cc

RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror
#-lpthread
#-g -fsanitize=thread

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
