/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenrach <abenrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 19:35:51 by abenrach          #+#    #+#             */
/*   Updated: 2026/07/17 00:11:26 by abenrach         ###   ########.fr       */
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

void	draw_player(t_data *data)
{
	put_pixel(data->game,(data->player->pos_x * 64), (data->player->pos_y * 64), GREEN);
	put_pixel(data->game,(data->player->pos_x * 64), (data->player->pos_y * 64) + 1, GREEN);
	put_pixel(data->game,(data->player->pos_x * 64), (data->player->pos_y * 64) - 1, GREEN);
	put_pixel(data->game,(data->player->pos_x * 64) + 1, (data->player->pos_y * 64), GREEN);
	put_pixel(data->game,(data->player->pos_x * 64) + 1, (data->player->pos_y * 64) + 1, GREEN);
	put_pixel(data->game,(data->player->pos_x * 64) + 1, (data->player->pos_y * 64) - 1, GREEN);
	put_pixel(data->game,(data->player->pos_x * 64) - 1, (data->player->pos_y * 64), GREEN);
	put_pixel(data->game,(data->player->pos_x * 64) - 1, (data->player->pos_y * 64) + 1, GREEN);
	put_pixel(data->game,(data->player->pos_x * 64) - 1, (data->player->pos_y * 64) - 1, GREEN);
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

void	draw_wall(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (data->tab[i] != NULL)
	{
		j = 0;
		while (data->tab[i][j])
		{
			if (data->tab[i][j] == '1')
				draw_one_wall(data, j * 64, i * 64);
			j++;
		}
		i++;
	}
}

void	init_raycast(t_data *data)
{
	clear_image(data->game);
	draw_player(data);
	draw_wall(data);	
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
