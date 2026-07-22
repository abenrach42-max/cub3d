/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 19:27:47 by abenrach          #+#    #+#             */
/*   Updated: 2026/07/22 18:41:49 by hcissoko         ###   ########.fr       */
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
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_player
{
	double		perp_wall_dist;
	int			line_height;
	double		draw_start;
	double		draw_end;
	int			hit;
	double		angle;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	double		pos_x;
	double		pos_y;
	char		dir_char;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			side;
	int			map_x;
	int			map_y;
	int			left_rotation;
	int			right_rotation;
	int			front;
	int			behind;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*img_so;
	void		*img_no;
	void		*img_ea;
	void		*img_we;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	char		*addr;
}				t_game;

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_data
{
	char		**tab;
	int			pos_tab_in_file;
	char		*path_map;
	int			nb_color;
	int			nb_floor;
	int			nb_no;
	int			nb_so;
	int			nb_we;
	int			nb_ea;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*floor_color;
	char		*ceiling_color;
	t_game		*game;
	t_player	*player;
	t_keys		keys;
}				t_data;

int				path_in_data(t_data *data, int fd);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				is_cub(char *str);
int				only_valid_char(char **tab);
t_data			*init_data(char *av);
size_t			len_path_dir(char *line);
int				init_pos_tab_in_file(int fd);
int				tab_in_data(t_data *data);
char			*ft_strdup(char *str);
int				tab_len(char **tab);
void			free_tab(char **tab, int size);
t_game			*init_game(t_data *data);
int				find_max_tab(char **tab);
void			free_all(t_data *data);

#endif