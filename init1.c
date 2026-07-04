/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenrach <abenrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 16:54:30 by abenrach          #+#    #+#             */
/*   Updated: 2026/07/04 09:09:41 by abenrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*fill_line_path(t_data *data, char *line)
{
	char	*new_path;
	size_t	i;
	size_t	len;
	size_t	start;

	if (data->nb_ea > 1 || data->nb_we > 1 || data->nb_no > 1 || data->nb_so > 1
		|| data->nb_color > 1 || data->nb_floor > 1)
		return (NULL);
	start = len_path_dir(line);
	len = ft_strlen(line) - start;
	if (len > 0 && line[start + len - 1] == '\n')
		len--;
	new_path = malloc(sizeof(char) * (len + 1));
	if (!new_path)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_path[i] = line[i + start];
		i++;
	}
	new_path[i] = '\0';
	return (new_path);
}

void	add_nb_dir(t_data *data, char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!ft_strncmp(line + i, "NO", 2))
	{
		data->nb_no++;
		data->no_path = fill_line_path(data, line);
	}
	else if (!ft_strncmp(line + i, "SO", 2))
	{
		data->nb_so++;
		data->so_path = fill_line_path(data, line);
	}
	else if (!ft_strncmp(line + i, "EA", 2))
	{
		data->nb_ea++;
		data->ea_path = fill_line_path(data, line);
	}
	else if (!ft_strncmp(line + i, "WE", 2))
	{
		data->nb_we++;
		data->we_path = fill_line_path(data, line);
	}
}

void	add_nb_floor_or_color(t_data *data, char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == 'F')
	{
		data->nb_floor++;
		data->floor_color = fill_line_path(data, line);
	}
	else if (line[i] == 'C')
	{
		data->nb_color++;
		data->ceiling_color = fill_line_path(data, line);
	}
	return ;
}

void	malloc_path_dir(t_data *data, char *line, int dir)
{
	if (dir == 1)
		add_nb_dir(data, line);
	else if (dir == 2)
		add_nb_floor_or_color(data, line);
}

int	path_in_data(t_data *data, int fd)
{
	size_t	i;
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (!ft_strncmp(line + i, "F", 1) || !ft_strncmp(line + i, "C", 1))
			malloc_path_dir(data, line, 2);
		else if (!ft_strncmp(line + i, "NO", 2) || !ft_strncmp(line + i, "WE",
				2) || !ft_strncmp(line + i, "EA", 2) || !ft_strncmp(line + i,
				"SO", 2))
			malloc_path_dir(data, line, 1);
		else if (line[i] != '\0' && line[i] != '\n' && line[i] != '1'
			&& line[i] != '_')
			return (free(line), close(fd), 1);
		free(line);
		line = get_next_line(fd);
	}
	if (!data->ea_path || !data->so_path || !data->no_path || !data->we_path
		|| !data->floor_color || !data->ceiling_color)
		return (close(fd), 1);
	return (close(fd), 0);
}
