/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 18:31:47 by enemxa            #+#    #+#             */
/*   Updated: 2026/07/19 16:57:25 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	len_tab_in_file(int fd, int index_tab)
{
	int		i;
	int		count;
	char	*line;

	i = 0;
	count = 0;
	while (i < index_tab)
	{
		line = get_next_line(fd);
		free(line);
		i++;
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), count);
}

int	fill_tab_data(t_data *data, int index_tab, int len_tab, int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (i++ < index_tab)
	{
		free(line);
		line = get_next_line(fd);
	}
	data->tab = malloc(sizeof(char *) * (len_tab + 1));
	if (!data->tab)
		return (close(fd), 1);
	i = 0;
	while (line != NULL)
	{
		data->tab[i] = ft_strdup(line);
		if (!data->tab[i])
			return (free_tab(data->tab, i), close(fd), 1);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	data->tab[i] = NULL;
	return (close(fd), 0);
}

void	remove_line(t_data *data)
{
	int	i;
	int	j;

	i = tab_len(data->tab) - 1;
	while (i >= 0)
	{
		j = ft_strlen(data->tab[i]) - 1;
		while (j >= 0)
		{
			if (data->tab[i][j] == '1' || data->tab[i][j] == '0'
				|| data->tab[i][j] == 'W' || data->tab[i][j] == 'N'
				|| data->tab[i][j] == 'E' || data->tab[i][j] == 'S')
				return ;
			j--;
		}
		free(data->tab[i]);
		data->tab[i] = NULL;
		i--;
	}
}

int	tab_in_data(t_data *data)
{
	int	fd;
	int	index_tab;
	int	len_tab;

	fd = open(data->path_map, O_RDONLY);
	if (fd < 0)
		return (1);
	index_tab = init_pos_tab_in_file(fd);
	if (index_tab == -1)
		return (1);
	fd = open(data->path_map, O_RDONLY);
	if (fd < 0)
		return (1);
	len_tab = len_tab_in_file(fd, index_tab);
	fd = open(data->path_map, O_RDONLY);
	if (fd < 0)
		return (1);
	if (fill_tab_data(data, index_tab, len_tab, fd))
		return (1);
	remove_line(data);
	return (0);
}
