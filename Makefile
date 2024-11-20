NAME		=	cub3d
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g
MLX			=	mlx/Makefile.gen
LFT			=	libft/libft.a
INC			=	-I ./src -I ./libft -I ./mlx
LIB			=	-L ./libft -lft -L ./mlx -lmlx -lX11 -lXext -lXrandr -lXrender -lm -lXfixes -lbsd
OBJ			=	$(SRC:.c=.o)
OBJBONUS	=	$(SRCBONUS:.c=.o)
GREEN		=	\033[0;32m
RED 		=	\033[0;31m
YELLOW		=	\033[0;33m
RESET		=	\033[0m
SRC			=	src/cub3d.c src/utilities.c src/events.c src/update.c \
				src/move.c src/dispaly_debug.c src/draw.c src/raycasting.c src/root_init.c \
				src/parse_config.c src/debug.c

all:		$(MLX) $(LFT) $(NAME)

$(NAME):	$(OBJ)
			@echo "$(RED)[ .. ] Compiling Mandatory..$(RESET)"
			@$(CC) $(CFLAGS) -o $@ $^ $(LIB)
			@echo "$(GREEN)[ OK ]$(RESET) $(YELLOW)Mandatory Ready!$(RESET)"

$(MLX):
			@echo "$(RED)[ .. ] | Compiling minilibx..$(RESET)"
			@make -s -C mlx
			@echo "$(GREEN)[ OK ]$(RESET)|$(YELLOW)Minilibx ready!$(RESET)"

$(LFT):
			@echo "$(RED)[ .. ] Compiling Libft..$(RESET)"
			@make -s -C libft
			@echo "$(GREEN)[ OK ]$(RESET) $(YELLOW)Libft ready!$(RESET)"

src/%.o:	src/%.c
			@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
			@make -s $@ -C libft
			@rm -rf $(OBJ) src/*.o
			@rm -rf $(OBJBONUS) bonus/*.o
			@echo "Object files removed."

fclean:		clean
			@make -s $@ -C libft
			@rm -rf $(NAME)
			@rm -rf $(NAMEB)
			@echo "Binary file removed."

re:			fclean all
re_b:			fclean bonus

.PHONY:		all clean fclean re
