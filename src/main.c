/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:09:09 by hcissoko          #+#    #+#             */
/*   Updated: 2026/08/19 15:09:09 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_win(t_data *data)
{
	free_all(data);
	exit(0);
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
