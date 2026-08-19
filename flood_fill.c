/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 12:05:03 by hcissoko          #+#    #+#             */
/*   Updated: 2026/08/19 13:39:18 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (row >= 0 && col >= 0 && grid[row] && grid[row][col])
	{
		if (grid[row][col] != '1' && grid[row][col] != 'X'
			&& grid[row][col] != ' ')
		{
			grid[row][col] = 'X';
			if (flood_fill(grid, row - 1, col)
				|| flood_fill(grid, row + 1, col)
				|| flood_fill(grid, row, col + 1)
				|| flood_fill(grid, row, col - 1))
				return (1);
		}
		if (grid[row][col] == ' ')
			return (1);
	}
	else
		return (1);
	return (0);
}
