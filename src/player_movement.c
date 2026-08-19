/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:09:09 by hcissoko          #+#    #+#             */
/*   Updated: 2026/08/19 15:09:09 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_data *data, double dx, double dy)
{
	double	next_x;
	double	next_y;

	next_x = data->player->pos_x + dx * SPEED;
	next_y = data->player->pos_y + dy * SPEED;
	if (data->tab[(int)data->player->pos_y][(int)next_x] != '1')
		data->player->pos_x = next_x;
	if (data->tab[(int)next_y][(int)data->player->pos_x] != '1')
		data->player->pos_y = next_y;
}

void	rotate_player(t_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	data->player->dir_x = data->player->dir_x * cos(angle) - data->player->dir_y
		* sin(angle);
	data->player->dir_y = old_dir_x * sin(angle) + data->player->dir_y
		* cos(angle);
	data->player->plane_x = data->player->plane_x * cos(angle)
		- data->player->plane_y * sin(angle);
	data->player->plane_y = old_plane_x * sin(angle) + data->player->plane_y
		* cos(angle);
}

void	handle_movement(t_data *data)
{
	if (data->keys.w)
		move_player(data, data->player->dir_x, data->player->dir_y);
	if (data->keys.s)
		move_player(data, -data->player->dir_x, -data->player->dir_y);
	if (data->keys.d)
		move_player(data, -data->player->dir_y, data->player->dir_x);
	if (data->keys.a)
		move_player(data, data->player->dir_y, -data->player->dir_x);
	if (data->keys.left)
		rotate_player(data, ANGLE_SPEED);
	if (data->keys.right)
		rotate_player(data, -ANGLE_SPEED);
}
