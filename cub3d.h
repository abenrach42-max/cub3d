/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenrach <abenrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 19:27:47 by abenrach          #+#    #+#             */
/*   Updated: 2026/08/31 11:47:03 by abenrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define HEIGHT 720
# define WIDTH 1280
# define SPEED 0.01
# define ANGLE_SPEED 0.01
# define BLACK 0x00000000
# define GREEN 0x0000FF00
# define RED 0x00FF0000
# define YELLOW 0x00FFFF00
# define FRONT 1
# define BEHIND -1
# include "get_next_line/get_next_line.h"
# include "libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_player
{
	double			perp_wall_dist;
	int				line_height;
	double			draw_start;
	double			draw_end;
	int				hit;
	double			angle;
	double			ray_dir_x;
	double			ray_dir_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	double			pos_x;
	double			pos_y;
	char			dir_char;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	int				side;
	int				map_x;
	int				map_y;
	int				left_rotation;
	int				right_rotation;
	int				front;
	int				behind;
	int				wall_dir;
	double			wall_x;
	char			*tex_addr;
	int				tex_width;
	int				tex_height;
	int				tex_bpp;
	int				tex_size_line;
	int				tex_x;
	double			tex_step;
	double			tex_pos;
}					t_player;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*img_so;
	void			*img_no;
	void			*img_ea;
	void			*img_we;
	int				bpp_img;
	int				bpp_no;
	int				bpp_so;
	int				bpp_ea;
	int				bpp_we;
	int				size_line_img;
	int				size_line_no;
	int				size_line_so;
	int				size_line_we;
	int				size_line_ea;
	int				endian_img;
	int				endian_no;
	int				endian_so;
	int				endian_ea;
	int				endian_we;
	char			*addr_img;
	char			*addr_no;
	char			*addr_so;
	char			*addr_ea;
	char			*addr_we;
	int				text_no_w;
	int				text_so_w;
	int				text_ea_w;
	int				text_we_w;
	int				text_no_h;
	int				text_so_h;
	int				text_ea_h;
	int				text_we_h;
}					t_game;

typedef struct s_keys
{
	int				w;
	int				s;
	int				a;
	int				d;
	int				left;
	int				right;
}					t_keys;

typedef struct s_data
{
	char			**tab;
	int				pos_tab_in_file;
	char			*path_map;
	int				nb_color;
	int				nb_floor;
	int				nb_no;
	int				nb_so;
	int				nb_we;
	int				nb_ea;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	char			*floor_color;
	char			*ceiling_color;
	int				int_floor;
	int				int_ceiling;
	t_game			*game;
	t_player		*player;
	t_keys			keys;
}					t_data;

typedef struct s_clr
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_clr;

t_data				*init_data(char *av);
int					path_in_data(t_data *data, int fd);
size_t				len_path_dir(char *line);
int					init_pos_tab_in_file(int fd);
int					tab_in_data(t_data *data);
int					only_valid_char(char **tab);
char				**ft_grid_cpy(char **tab);
int					flood_fill(char **grid, int row, int col);
int					create_rgb(char *str);

t_game				*init_game(t_data *data);
int					init_player(t_data *data, t_player *player);
void				init_player_dir(t_player *player);

void				put_pixel(t_game *game, int x, int y, int color);
void				clear_image(t_game *game);
void				init_delta_dist(t_player *player);
void				calculate_step(t_player *player);
void				perform_dda(t_data *data, t_player *player);
void				calculate_wall_height(t_player *player);
void				select_texture(t_game *game, t_player *player);
void				draw_wall(t_data *data, int x, t_player *player);
void				handle_movement(t_data *data);
int					raycast(t_data *data);
int					close_win(t_data *data);
int					key_press(int keycode, t_data *data);
int					key_release(int keycode, t_data *data);
int					init_img_no(t_data *data, t_game *game);
int					init_img_so(t_data *data, t_game *game);
int					init_img_ea(t_data *data, t_game *game);
int					init_img_we(t_data *data, t_game *game);

int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					is_cub(char *str);
int					tab_len(char **tab);
int					find_max_tab(char **tab);
void				print_error(char *str);
void				free_tab(char **tab, int size);
void				free_all(t_data *data);
#endif