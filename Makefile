NAME = cub3d

SRCS =  main.c \
		utils1.c \
		utils2.c \
		parsing1.c \
		init1_data.c \
		init2_data.c \
		init3_data.c \
		init1_game.c \
		flood_fill.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

CC = cc
FLAGS = -Wall -Werror -Wextra

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -lXext -lX11 -lm

LIBFT_DIR = ./libft
LIBFT_LIB = ${LIBFT_DIR}/libft.a

INCS	= -I . -I ${LIBFT_DIR}

all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT_LIB)
	$(CC) $(FLAGS) $(OBJS) $(MLX_LIB) -no-pie $(MLX_FLAGS) -o $(NAME) ${LIBFT_LIB}
	@echo "✅ Build complete! Executable: $(NAME)"
	@errors=$$(norminette | grep "Error:" | wc -l); \
	if [ "$$errors" -gt 0 ]; then \
		echo "❌ $$errors norm error(s)"; \
	fi

%.o: %.c
	$(CC) $(FLAGS) $(INCS) -c $< -o $@

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

$(MLX_LIB):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
