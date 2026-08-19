/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:09:09 by hcissoko          #+#    #+#             */
/*   Updated: 2026/08/19 15:09:09 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loads_images(t_data *data, t_game *game)
{
	int	h;
	int	w;

	game->img_no = mlx_xpm_file_to_image(game->mlx, data->no_path, &w, &h);
	if (!game->img_no)
		return (print_error("Image north init fail"), 1);
	game->img_so = mlx_xpm_file_to_image(game->mlx, data->so_path, &w, &h);
	if (!game->img_so)
		return (print_error("Image south init fail"), 1);
	game->img_ea = mlx_xpm_file_to_image(game->mlx, data->ea_path, &w, &h);
	if (!game->img_ea)
		return (print_error("Image east init fail"), 1);
	game->img_we = mlx_xpm_file_to_image(game->mlx, data->we_path, &w, &h);
	if (!game->img_we)
		return (print_error("Image weast init fail"), 1);
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
	data->game->addr = mlx_get_data_addr(data->game->img,
			&data->game->bits_per_pixel,
			&data->game->size_line, &data->game->endian);
	if (!data->game->addr)
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
	game->addr = NULL;
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
