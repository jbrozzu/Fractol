NAME = fractol

SRCS =      main.c mandelbrot.c

OBJS =		$(SRCS:.c=.o)

INCLUDES =	-I libft/ -I minilibx_macos/ -I ./

LIBS =		-L libft/ -lft -L minilibx_macos/ -lmlx -framework OpenGL -framework AppKit

FLAGS =	    -Wall -Wextra -Werror


$(NAME):	$(OBJS)
				@make -C libft/ fclean
				@make -C libft/
				@make -C minilibx_macos/ clean
				@make -C minilibx_macos/
				@echo "Create binary" 
				@gcc -o $(NAME) $(OBJS) $(LIBS)
				@echo "Complitation ok"

$(OBJS): %.o: %.c
				@gcc $(FLAGS) $(INCLUDES) -c $< -o $@

all:		$(NAME)

clean:
	rm -f	$(OBJS)

fclean: clean
	rm -f	$(NAME)

re: fclean all

.PHONY:	 all clean fclean re