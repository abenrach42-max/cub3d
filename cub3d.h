/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenrach <abenrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 19:27:47 by abenrach          #+#    #+#             */
/*   Updated: 2026/07/04 09:44:02 by abenrach         ###   ########.fr       */
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
void		free_all_data(t_data *data);

#endif