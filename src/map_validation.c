/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houms <houms@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:09:09 by hcissoko          #+#    #+#             */
/*   Updated: 2026/09/22 15:24:55 by houms            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	has_empty_line(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j] == ' ')
			j++;
		if (tab[i][j] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	only_valid_char(char **tab)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (tab[i] != NULL)
	{
		j = 0;
		while (tab[i][j])
		{
			if (!(tab[i][j] == '1' || tab[i][j] == '0' || tab[i][j] == 'N'
					|| tab[i][j] == 'W' || tab[i][j] == 'S' || tab[i][j] == 'E'
					|| tab[i][j] == ' '))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

char	**ft_grid_cpy(char **tab)
{
	char	**grid;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	grid = malloc(sizeof(char *) * (i + 1));
	if (!grid)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		grid[i] = ft_strdup(tab[i]);
		if (!grid[i])
		{
			ft_strsfree(grid, i);
			return (NULL);
		}
		i++;
	}
	grid[i] = NULL;
	return (grid);
}

int	flood_fill(char **grid, int row, int col)
{
	if (row < 0 || col < 0 || !grid[row]
		|| col >= (int)ft_strlen(grid[row]) || grid[row][col] == ' ')
		return (1);
	if (grid[row][col] == '1' || grid[row][col] == 'X')
		return (0);
	grid[row][col] = 'X';
	return (flood_fill(grid, row - 1, col) || flood_fill(grid, row + 1, col)
		|| flood_fill(grid, row, col + 1) || flood_fill(grid, row, col - 1));
}
