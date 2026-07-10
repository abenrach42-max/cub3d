NAME = cub3d

SRCS =  main.c \
		utils1.c \
		utils2.c \
		parsing1.c \
		init1_data.c \
		init2_data.c \
		init3_data.c \
		init1_game.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

CC = cc
FLAGS = -Wall -Werror -Wextra

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(FLAGS) $(OBJS) $(MLX_LIB) -no-pie $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(MLX_LIB):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
