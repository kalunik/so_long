CC	=	gcc
RM	=	rm -f
CFLAGS	=	-I./includes -Imlx #-Wall -Wextra -Werror
NAME	=	so_long
LIBFT	=	./libft
SRCS	=	so_long.c map.c \
			get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
#MLX_DIR		=	mlx
#MLX_LIB		=	libmlx.dylib

OBJS	=	$(patsubst %.c, %.o, $(SRCS))

all:
			@$(MAKE) -C $(LIBFT)
			@$(MAKE) $(NAME)

$(NAME):	$(OBJS) $(LIBFT)/libft.a libft/libft.h
#			$(MLX_LIB)
			@$(CC) -Lmlx -lmlx -framework AppKit -o $(NAME) $(OBJS) $(LIBFT)/libft.a
			@echo "so_long is ready to use ✅ "

%.o: %.c	includes/so_long.h get_next_line/get_next_line.h
			@$(CC) $(CFLAGS) -c $< -o $@

#$(MLX_LIB):
#			$(MAKE) -C $(MLX_DIR)
#			@cp $(MLX_DIR)/$(MLX_LIB) ./$(MLX_LIB)

clean:
			@$(MAKE) -C $(LIBFT)/ clean
			@$(RM)	$(OBJS)
			@echo ".o Deleted 🗿"

fclean: 	clean
			@$(MAKE) -C $(LIBFT)/ fclean
#			@$(MAKE) -C mlx/ clean
			@$(RM)	 $(NAME) $(MLX_LIB)
			@echo "Deleted 😬"

re:			fclean all

.PHONY: all clean fclean re