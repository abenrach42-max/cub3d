NAME = cub3d

SRCS =  src/main.c \
		src/player_movement.c \
		src/input.c \
		src/render_utils.c \
		src/raycasting.c \
		src/raycasting_draw.c \
		src/init_game.c \
		src/init_player.c \
		src/init_player_dir.c \
		src/parse_config.c \
		src/parse_data.c \
		src/parse_map.c \
		src/map_validation.c \
		src/utils.c \
		src/errors.c \
		src/free_utils.c \
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
	@errors=$$(norminette src/ | grep "Error:" | wc -l); \
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
