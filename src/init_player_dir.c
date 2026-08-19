/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:09:09 by hcissoko          #+#    #+#             */
/*   Updated: 2026/08/19 15:09:09 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_dir_n(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = -1;
	player->plane_x = 0.70;
	player->plane_y = 0;
}

void	init_player_dir_s(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = 1;
	player->plane_x = -0.70;
	player->plane_y = 0;
}

void	init_player_dir_e(t_player *player)
{
	player->dir_x = 1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.70;
}

void	init_player_dir_w(t_player *player)
{
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = -0.70;
}

void	init_player_dir(t_player *player)
{
	if (player->dir_char == 'N')
		init_player_dir_n(player);
	else if (player->dir_char == 'S')
		init_player_dir_s(player);
	else if (player->dir_char == 'W')
		init_player_dir_w(player);
	else if (player->dir_char == 'E')
		init_player_dir_e(player);
}
