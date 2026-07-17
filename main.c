/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenrach <abenrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 19:35:51 by abenrach          #+#    #+#             */
/*   Updated: 2026/07/17 19:55:05 by abenrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_win(t_data *data)
{
	puts(data->no_path);
	exit(0);
}

void	go_right(t_data *data)
{
	int		x;
	int		y;

	x = (int)(data->player->pos_x + SPEED);
	y = (int)data->player->pos_y;
	if (data->tab[y][x] == '1')
		return ;
	data->player->pos_x += SPEED;
}

void	go_left(t_data *data)
{
	int		x;
	int		y;

	x = (int)(data->player->pos_x - SPEED);
	y = (int)data->player->pos_y;
	if (data->tab[y][x] == '1')
		return ;
	data->player->pos_x -= SPEED;
}

void	go_front(t_data *data)
{
	int		x;
	int		y;

	x = (int)(data->player->pos_x);
	y = (int)(data->player->pos_y - SPEED);
	if (data->tab[y][x] == '1')
		return ;
	data->player->pos_y -= SPEED;
}

void	go_behind(t_data *data)
{
	int		x;
	int		y;

	x = (int)(data->player->pos_x);
	y = (int)(data->player->pos_y + SPEED);
	if (data->tab[y][x] == '1')
		return ;
	data->player->pos_y += SPEED;
}

int	get_key(int keycode, t_data *data)
{
	printf("%d\n", keycode);
	if (keycode == 65307)
		return (close_win(data));
	if (keycode == 119)
		go_front(data);
	if (keycode == 115)
		go_behind(data);
	if (keycode == 100)
		go_right(data);
	if (keycode == 97)
		go_left(data);
	return (0);
}

 
void	put_pixel(t_game *game, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		*(unsigned int *)(game->addr + (y * game->size_line + x * (game->bits_per_pixel / 8))) = color;
		return ;
	}
	printf("Error\n");
	exit(0);
}

void	clear_image(t_game *game)
{
	int		i;
	int		j;

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

void	draw_one_wall(t_data *data, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			put_pixel(data->game, x + i, y + j, RED);
			j++;
		}
		i++;
	}
}

void	init_delta_dist(t_player *player)
{
	if (player->ray_dir_x == 0)
		player->delta_dist_x = INFINITY;
	else
		player->delta_dist_x = fabs(1 / player->ray_dir_x);
	if (player->ray_dir_x == 0)
		player->delta_dist_y = INFINITY;
	else
		player->delta_dist_y = fabs(1 / player->ray_dir_y);
}

void    calculate_step(t_player *player)
{
    if (player->ray_dir_x < 0)
    {
        player->step_x = -1;
        player->side_dist_x = (player->pos_x - player->map_x) * player->delta_dist_x;
    }
    else
    {
        player->step_x = 1;
        player->side_dist_x = (player->map_x + 1.0 - player->pos_x) * player->delta_dist_x;
    }
    if (player->ray_dir_y < 0)
    {
        player->step_y = -1;
        player->side_dist_y = (player->pos_y - player->map_y) * player->delta_dist_y;
    }
    else
    {
        player->step_y = 1;
        player->side_dist_y = (player->map_y + 1.0 - player->pos_y) * player->delta_dist_y;
    }
}

void    perform_dda(t_data *data, t_player *player)
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

void    draw_wall(t_data *data, int x, t_player *player)
{
    int y;

    y = 0;
    while (y < HEIGHT)
    {
        if (y >= player->draw_start && y <= player->draw_end)
        {
            if (player->side == 0)
                put_pixel(data->game, x, y, 0xFF5733);
            else
                put_pixel(data->game, x, y, 0x99331A);
        }
        y++;
    }
}

void    calculate_wall_height(t_player *player)
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

void    raycasting_per_column(t_data *data, int x)
{
	double camera = 2.0 * x / (double)WIDTH - 1.0;
    data->player->ray_dir_x = data->player->dir_x + data->player->plane_x * camera;
    data->player->ray_dir_y = data->player->dir_y + data->player->plane_y * camera;
    data->player->map_x = (int)data->player->pos_x;
    data->player->map_y = (int)data->player->pos_y;
	init_delta_dist(data->player);
    calculate_step(data->player);
    perform_dda(data, data->player);
    calculate_wall_height(data->player);
    draw_wall(data, x, data->player); 
}

void	init_raycast(t_data *data)
{
	clear_image(data->game);	
	for (int x = 0; x < WIDTH; x++)
		raycasting_per_column(data, x);
	mlx_put_image_to_window(data->game->mlx, data->game->win, data->game->img, 0, 0);
}

int	do_game(t_data *data)
{
	init_raycast(data);
    return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_game	*game;

	if (ac != 2)
		return (1);
	data = init_data(av[1]);
	if (!data)
		return (1);
	game = init_game(data);
	if (!game)
		return (1);
	printf("ehhhhh : %d\n", find_max_tab(data->tab));
	mlx_loop_hook(game->mlx, (int (*)())(void *)do_game, data);
	mlx_hook(game->win, 17, 0, (int (*)())(void *)close_win, data);
	mlx_hook(game->win, 2, 1, (int (*)())(void *)get_key, data);
	mlx_loop(game->mlx);
	return (0);
}
