/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enemxa <enemxa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 16:57:09 by abenrach          #+#    #+#             */
/*   Updated: 2026/07/06 19:05:04 by enemxa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	len_path_dir(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i])
		i += 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

void	init_data_var(t_data *data)
{
	data->pos_tab_in_file = 0;
	data->nb_ea = 0;
	data->nb_we = 0;
	data->nb_no = 0;
	data->nb_so = 0;
	data->nb_color = 0;
	data->nb_floor = 0;
	data->no_path = NULL;
	data->so_path = NULL;
	data->ea_path = NULL;
	data->we_path = NULL;
	data->floor_color = NULL;
	data->ceiling_color = NULL;
}

int is_valid_identifier(char *str)
{
    if (!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2)
        || !ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "EA", 2))
    {
        if (str[2] == ' ' || str[2] == '\t' || str[2] == '_')
            return (1);
    }
    if (!ft_strncmp(str, "F", 1) || !ft_strncmp(str, "C", 1))
    {
        if (str[1] == ' ' || str[1] == '\t' || str[1] == '_')
            return (1);
    }
    return (0);
}

int	init_pos_tab_in_file(int fd) 
{
	size_t	i;
	size_t	j;
	int		count;
	char	*line;

	count = 0;
	j = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (is_valid_identifier(line + i))
			count++;
		else if (line[i] != '\0' && line[i] != '\n' && line[i] != '1')
			return (free(line), close(fd), 1);
		if (count == 6 && line[i] == '1')
			return (free(line), close(fd), j);
		j++;
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), -1);
}

t_data	*init_data(char *av)
{
	int		fd;
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->path_map = av;
	init_data_var(data);
	fd = open(data->path_map, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (path_in_data(data, fd))
		return (NULL);
	if (tab_in_data(data))
		return (NULL);
	return (data);
}
