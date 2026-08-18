/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 23:20:59 by abenrach          #+#    #+#             */
/*   Updated: 2026/08/18 16:12:50 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
