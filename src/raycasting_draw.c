/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenrach <abenrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:09:09 by hcissoko          #+#    #+#             */
/*   Updated: 2026/08/31 11:35:51 by abenrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_wall_dir_and_x(t_player *player)
{
	if (player->side == 0)
	{
		player->wall_x = player->pos_y + player->perp_wall_dist
			* player->ray_dir_y;
		if (player->step_x > 0)
			player->wall_dir = 3;
		else
			player->wall_dir = 2;
	}
	else
	{
		player->wall_x = player->pos_x + player->perp_wall_dist
			* player->ray_dir_x;
		if (player->step_y > 0)
			player->wall_dir = 0;
		else
			player->wall_dir = 1;
	}
	player->wall_x -= floor(player->wall_x);
}

void	raycasting_per_column(t_data *data, int x)
{
	double	camera;

	camera = 2.0 * x / (double)WIDTH - 1.0;
	data->player->ray_dir_x = data->player->dir_x + data->player->plane_x
		* camera;
	data->player->ray_dir_y = data->player->dir_y + data->player->plane_y
		* camera;
	data->player->map_x = (int)data->player->pos_x;
	data->player->map_y = (int)data->player->pos_y;
	init_delta_dist(data->player);
	calculate_step(data->player);
	perform_dda(data, data->player);
	calculate_wall_height(data->player);
	calculate_wall_dir_and_x(data->player);
	draw_wall(data, x, data->player);
}

int	raycast(t_data *data)
{
	int	x;

	x = 0;
	handle_movement(data);
	clear_image(data->game);
	while (x < WIDTH)
		raycasting_per_column(data, x++);
	mlx_put_image_to_window(data->game->mlx, data->game->win, data->game->img,
		0, 0);
	return (0);
}
