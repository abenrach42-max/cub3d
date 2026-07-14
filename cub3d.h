/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enemxa <enemxa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 19:27:47 by abenrach          #+#    #+#             */
/*   Updated: 2026/07/14 00:56:00 by enemxa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1080
# define HEIGHT 1920
# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	char	dir_char;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}			t_player;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*img_so;
	void	*img_no;
	void	*img_ea;
	void	*img_we;
}			t_game;

typedef struct s_data
{
	char	**tab;
	int		pos_tab_in_file;
	char	*path_map;
	int		nb_color;
	int		nb_floor;
	int		nb_no;
	int		nb_so;
	int		nb_we;
	int		nb_ea;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*floor_color;
	char	*ceiling_color;
	t_game	*game;
	t_player	*player;
}			t_data;

int			path_in_data(t_data *data, int fd);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			is_cub(char *str);
int			only_valid_char(char **tab);
t_data		*init_data(char *av);
size_t		len_path_dir(char *line);
int			init_pos_tab_in_file(int fd);
void		free_all_data(t_data *data);
int			tab_in_data(t_data *data);
char		*ft_strdup(char *str);
int			tab_len(char **tab);
void		free_tab(char **tab, int size);
t_game		*init_game(t_data *data);

#endif