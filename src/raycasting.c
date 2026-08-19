/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:09:09 by hcissoko          #+#    #+#             */
/*   Updated: 2026/08/19 15:09:09 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_delta_dist(t_player *player)
{
	if (player->ray_dir_x == 0)
		player->delta_dist_x = 1e30;
	else
		player->delta_dist_x = fabs(1.0 / player->ray_dir_x);
	if (player->ray_dir_y == 0)
		player->delta_dist_y = 1e30;
	else
		player->delta_dist_y = fabs(1.0 / player->ray_dir_y);
}

void	calculate_step(t_player *player)
{
	if (player->ray_dir_x < 0)
	{
		player->step_x = -1;
		player->side_dist_x = (player->pos_x - player->map_x)
			* player->delta_dist_x;
	}
	else
	{
		player->step_x = 1;
		player->side_dist_x = (player->map_x + 1.0 - player->pos_x)
			* player->delta_dist_x;
	}
	if (player->ray_dir_y < 0)
	{
		player->step_y = -1;
		player->side_dist_y = (player->pos_y - player->map_y)
			* player->delta_dist_y;
	}
	else
	{
		player->step_y = 1;
		player->side_dist_y = (player->map_y + 1.0 - player->pos_y)
			* player->delta_dist_y;
	}
}

void	perform_dda(t_data *data, t_player *player)
{
	player->hit = 0;
	while (player->hit == 0)
	{
		if (player->side_dist_x < player->side_dist_y)
		{
			player->side_dist_x += player->delta_dist_x;
			player->map_x += player->step_x;
			player->side = 0;
		}
		else
		{
			player->side_dist_y += player->delta_dist_y;
			player->map_y += player->step_y;
			player->side = 1;
		}
		if (data->tab[player->map_y][player->map_x] == '1')
			player->hit = 1;
	}
}

void	calculate_wall_height(t_player *player)
{
	if (player->side == 0)
		player->perp_wall_dist = (player->side_dist_x - player->delta_dist_x);
	else
		player->perp_wall_dist = (player->side_dist_y - player->delta_dist_y);
	player->line_height = (int)(HEIGHT / player->perp_wall_dist);
	player->draw_start = -player->line_height / 2 + HEIGHT / 2;
	if (player->draw_start < 0)
		player->draw_start = 0;
	player->draw_end = player->line_height / 2 + HEIGHT / 2;
	if (player->draw_end >= HEIGHT)
		player->draw_end = HEIGHT - 1;
}
