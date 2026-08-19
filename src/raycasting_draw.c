/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:09:09 by hcissoko          #+#    #+#             */
/*   Updated: 2026/08/19 15:09:09 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(t_data *data, int x, t_player *player)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < player->draw_start)
			put_pixel(data->game, x, y, YELLOW);
		else if (y >= player->draw_start && y <= player->draw_end)
		{
			if (player->side == 0)
				put_pixel(data->game, x, y, 0xFF5733);
			else
				put_pixel(data->game, x, y, 0x99331A);
		}
		else
			put_pixel(data->game, x, y, GREEN);
		y++;
	}
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
