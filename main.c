/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enemxa <enemxa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 19:35:51 by abenrach          #+#    #+#             */
/*   Updated: 2026/07/13 04:05:00 by enemxa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int close_win(t_data *data)
{
    puts(data->no_path);
    exit(0);
}

int get_key(int keycode, t_data *data)
{
    printf("%d\n", keycode);
    if (keycode == 65307)
        return (close_win(data));
    if (keycode == 119)
        data->player->pos_x -= 0.1;
    if (keycode == 115)
        data->player->pos_x += 0.1;
    return (0);
}

int	main(int ac, char **av)
{
    t_data  *data;
    t_game  *game;

	if (ac != 2)
	    return (1);
    data = init_data(av[1]);
    if (!data)
        return (1);
    game = init_game(data);
    if (!game)
        return (1);
    mlx_hook(game->win, 17, 0, close_win, data);
    mlx_hook(game->win, 2, 1, get_key, data);
    mlx_loop(game->mlx);
    return (0);
}
