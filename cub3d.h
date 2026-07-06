/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enemxa <enemxa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 19:27:47 by abenrach          #+#    #+#             */
/*   Updated: 2026/07/06 21:49:17 by enemxa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
char    	*ft_strdup(char *str);
int			tab_len(char **tab);

#endif