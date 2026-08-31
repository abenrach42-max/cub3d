/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenrach <abenrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:09:09 by hcissoko          #+#    #+#             */
/*   Updated: 2026/08/31 11:45:36 by abenrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loads_images(t_data *data, t_game *game)
{
	if (init_img_no(data, game))
		return (1);
	if (init_img_so(data, game))
		return (1);
	if (init_img_ea(data, game))
		return (1);
	if (init_img_we(data, game))
		return (1);
	return (0);
}

int	init_mlx_game(t_data *data)
{
	data->game->mlx = mlx_init();
	if (!data->game->mlx)
		return (print_error("Mlx init fail"), 1);
	data->game->win = mlx_new_window(data->game->mlx, WIDTH, HEIGHT, "cub3d");
	if (!data->game->win)
		return (print_error("Window of Mlx init fail"), 1);
	if (loads_images(data, data->game))
		return (1);
	data->game->img = mlx_new_image(data->game->mlx, WIDTH, HEIGHT);
	if (!data->game->img)
		return (print_error("Image init fail"), 1);
	data->game->addr_img = mlx_get_data_addr(data->game->img,
			&data->game->bpp_img,
			&data->game->size_line_img, &data->game->endian_img);
	if (!data->game->addr_img)
		return (print_error("Get addr fail"), 1);
	return (0);
}

void	init_game_var(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->img_so = NULL;
	game->img_no = NULL;
	game->img_ea = NULL;
	game->img_we = NULL;
	game->addr_img = NULL;
}

t_game	*init_game(t_data *data)
{
	t_game		*game;
	t_player	*player;
	char		**grid_cpy;

	player = malloc(sizeof(t_player));
	if (!player)
		return (print_error("Malloc player init failed"), NULL);
	data->player = player;
	if (init_player(data, player))
		return (NULL);
	grid_cpy = ft_grid_cpy(data->tab);
	if (!grid_cpy)
		return (print_error("Duplication of grid failed"), NULL);
	if (flood_fill(grid_cpy, data->player->map_y, data->player->map_x))
		return (print_error("Flood Fill cannot be completed"),
			ft_strsfree(grid_cpy, ft_strs_size(grid_cpy)), NULL);
	ft_strsfree(grid_cpy, ft_strs_size(grid_cpy));
	game = malloc(sizeof(t_game));
	if (!game)
		return (print_error("Malloc game failed"), NULL);
	data->game = game;
	init_game_var(game);
	if (init_mlx_game(data))
		return (NULL);
	return (game);
}
