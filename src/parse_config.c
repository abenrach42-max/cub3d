/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:09:09 by hcissoko          #+#    #+#             */
/*   Updated: 2026/09/22 16:39:49 by hcissoko         ###   ########.fr       */
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

static void	set_path(t_data *data, char **dst, char *line)
{
	free(*dst);
	*dst = fill_line_path(data, line);
}

void	add_nb_dir(t_data *data, char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!ft_strncmp(line + i, "NO", 2) && ++data->nb_no)
		set_path(data, &data->no_path, line);
	else if (!ft_strncmp(line + i, "SO", 2) && ++data->nb_so)
		set_path(data, &data->so_path, line);
	else if (!ft_strncmp(line + i, "EA", 2) && ++data->nb_ea)
		set_path(data, &data->ea_path, line);
	else if (!ft_strncmp(line + i, "WE", 2) && ++data->nb_we)
		set_path(data, &data->we_path, line);
}

void	add_nb_floor_or_color(t_data *data, char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == 'F' && ++data->nb_floor)
		set_path(data, &data->floor_color, line);
	else if (line[i] == 'C' && ++data->nb_color)
		set_path(data, &data->ceiling_color, line);
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
			add_nb_floor_or_color(data, line);
		else if (!ft_strncmp(line + i, "NO", 2) || !ft_strncmp(line + i, "WE",
				2) || !ft_strncmp(line + i, "EA", 2) || !ft_strncmp(line + i,
				"SO", 2))
			add_nb_dir(data, line);
		else if (line[i] != '\0' && line[i] != '\n' && line[i] != '1')
			return (print_error("Strings in file"), free(line), drain_gnl(fd)
				, 1);
		free(line);
		line = get_next_line(fd);
	}
	if (!data->ea_path || !data->so_path || !data->no_path || !data->we_path
		|| !data->floor_color || !data->ceiling_color)
		return (print_error("Path in data NULL"), close(fd), 1);
	return (close(fd), 0);
}
