/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenrach <abenrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 23:09:10 by abenrach          #+#    #+#             */
/*   Updated: 2026/07/03 19:48:39 by abenrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t          i;
    unsigned char   *p1;
    unsigned char   *p2;

    i = 0;
    p1 = (unsigned char *)s1;
    p2 = (unsigned char *)s2;
    while (i < n && (p1[i] != '\0' || p2[i] != '\0'))
    {
        if (p1[i] != p2[i])
            return (p1[i] - p2[i]);
        i++;
    }
    return (0);
}

int	is_cub(char *str)
{
	size_t	i;

	i = ft_strlen(str) - 1;
	while ((i > 0) && str[i] == ' ')
		i--;
	if (str[i] == 'b' && str[i - 1] == 'u' && str[i - 2] == 'c'
            && str[i - 3] == '.')
		return (1);
	return (0);
}

void    free_all_data(t_data *data)
{
    if (data->ceiling_color)
        free(data->ceiling_color);
    if (data->floor_color)
        free(data->floor_color);
    if (data->ea_path)
        free(data->ea_path);
    if (data->we_path)
        free(data->we_path);
    if (data->so_path)
        free(data->so_path);
    if (data->no_path)
        free(data->no_path);
    free(data);
}
