/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenrach <abenrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 19:35:51 by abenrach          #+#    #+#             */
/*   Updated: 2026/07/22 21:44:17 by abenrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_win(t_data *data)
{
	free_all(data);
	exit(0);
}

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

void	put_pixel(t_game *game, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		*(unsigned int *)(game->addr + (y * game->size_line + x
					* (game->bits_per_pixel / 8))) = color;
		return ;
	}
	printf("Error\n");
	exit(0);
}

void	clear_image(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			put_pixel(game, i, j, BLACK);
			j++;
		}
		i++;
	}
}

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

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		return (close_win(data));
	if (keycode == 119)
		data->keys.w = 1;
	if (keycode == 115)
		data->keys.s = 1;
	if (keycode == 100)
		data->keys.d = 1;
	if (keycode == 97)
		data->keys.a = 1;
	if (keycode == 65361)
		data->keys.right = 1;
	if (keycode == 65363)
		data->keys.left = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 119)
		data->keys.w = 0;
	if (keycode == 115)
		data->keys.s = 0;
	if (keycode == 100)
		data->keys.d = 0;
	if (keycode == 97)
		data->keys.a = 0;
	if (keycode == 65361)
		data->keys.right = 0;
	if (keycode == 65363)
		data->keys.left = 0;
	return (0);
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

int	main(int ac, char **av)
{
	t_data	*data;
	t_game	*game;

	if (ac != 2 || is_cub(av[1]))
		return (print_error("Wrong argument"), 1);
	data = init_data(av[1]);
	if (!data)
		return (1);
	game = init_game(data);
	if (!game)
		return (free_all(data), 1);
	mlx_loop_hook(game->mlx, (int (*)())(void *)raycast, data);
	mlx_hook(game->win, 17, 0, (int (*)())(void *)close_win, data);
	mlx_hook(game->win, 2, 1, (int (*)())(void *)key_press, data);
	mlx_hook(game->win, 3, 2, (int (*)())(void *)key_release, data);
	mlx_loop(game->mlx);
	return (0);
}
