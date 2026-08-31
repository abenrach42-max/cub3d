/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenrach <abenrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 11:23:57 by abenrach          #+#    #+#             */
/*   Updated: 2026/08/31 11:38:30 by abenrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	compute_tex_x(t_player *player)
{
	player->tex_x = (int)(player->wall_x * (double)player->tex_width);
	if ((player->wall_dir == 3 && player->ray_dir_x > 0)
		|| (player->wall_dir == 2 && player->ray_dir_x < 0)
		|| (player->wall_dir == 0 && player->ray_dir_y < 0)
		|| (player->wall_dir == 1 && player->ray_dir_y > 0))
		player->tex_x = player->tex_width - player->tex_x - 1;
}

int	get_texture_pixel(t_player *player, int tex_y)
{
	return (*(unsigned int *)(player->tex_addr + (tex_y * player->tex_size_line
			+ player->tex_x * (player->tex_bpp / 8))));
}

void	init_draw(t_data *data, t_player *player)
{
	select_texture(data->game, player);
	compute_tex_x(player);
	player->tex_step = (double)player->tex_height / player->line_height;
	player->tex_pos = (player->draw_start - HEIGHT / 2.0 + player->line_height
			/ 2.0) * player->tex_step;
}

void	draw_wall(t_data *data, int x, t_player *player)
{
	int	y;
	int	tex_y;

	init_draw(data, player);
	y = 0;
	while (y < HEIGHT)
	{
		if (y < player->draw_start)
			put_pixel(data->game, x, y, data->int_ceiling);
		else if (y <= player->draw_end)
		{
			tex_y = (int)player->tex_pos % player->tex_height;
			player->tex_pos += player->tex_step;
			put_pixel(data->game, x, y, get_texture_pixel(player, tex_y));
		}
		else
			put_pixel(data->game, x, y, data->int_floor);
		y++;
	}
}
