/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:09:09 by hcissoko          #+#    #+#             */
/*   Updated: 2026/08/19 15:09:09 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_var(t_player *player)
{
	player->pos_x = -1;
	player->pos_y = -1;
	player->dir_char = '\0';
}

int	player_found_pos(t_data *data, t_player *player)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (data->tab[i] != NULL)
	{
		j = 0;
		while (data->tab[i][j])
		{
			if (data->tab[i][j] == 'N' || data->tab[i][j] == 'S'
				|| data->tab[i][j] == 'E' || data->tab[i][j] == 'W')
			{
				player->pos_x = (double)j + 0.5;
				player->pos_y = (double)i + 0.5;
				player->dir_char = data->tab[i][j];
				count++;
			}
			j++;
		}
		i++;
	}
	return (count != 1);
}

int	init_player(t_data *data, t_player *player)
{
	init_player_var(player);
	if (player_found_pos(data, player))
		return (print_error("Position player not found"), 1);
	player->map_x = (int)player->pos_x;
	player->map_y = (int)player->pos_y;
	init_player_dir(player);
	return (0);
}
