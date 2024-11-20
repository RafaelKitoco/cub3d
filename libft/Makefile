NAME		= libft.a
CC			= gcc
FLAGS		= -Wall -Wextra -Werror
OBJ			= $(SRC:.c=.o)
SRC			= 	ft_calloc.c \
				ft_itoa.c \
				ft_memset.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_strcmp.c \
				ft_strjoin.c \
				ft_strlen.c \
				ft_strncmp.c \
				ft_strdup.c \
				ft_substr.c \
				ft_isdigit.c \
				ft_strtrim.c \
				ft_atoi.c \
				ft_strchr.c

all:		$(NAME)

$(NAME):	$(OBJ)
			ar rcs $@ $^

%.o:		%.c
			$(CC) $(FLAGS) -o $@ -c $<

clean:
			rm -rf $(OBJ)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
