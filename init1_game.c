/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenrach <abenrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 17:48:55 by abenrach          #+#    #+#             */
/*   Updated: 2026/07/19 20:28:42 by abenrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loads_images(t_data *data, t_game *game)
{
	int	h;
	int	w;

	game->img_no = mlx_xpm_file_to_image(game->mlx, data->no_path, &w, &h);
	if (!game->img_no)
		return (1);
	game->img_so = mlx_xpm_file_to_image(game->mlx, data->so_path, &w, &h);
	if (!game->img_so)
		return (1);
	game->img_ea = mlx_xpm_file_to_image(game->mlx, data->ea_path, &w, &h);
	if (!game->img_ea)
		return (1);
	game->img_we = mlx_xpm_file_to_image(game->mlx, data->we_path, &w, &h);
	if (!game->img_we)
		return (1);
	return (0);
}

int	init_mlx_game(t_game *game, t_data *data)
{
	data->game = game;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	if (!game->win)
		return (1);
	if (loads_images(data, game))
		return (1);
	game->img = mlx_new_image(data->game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return (1);
	game->addr = mlx_get_data_addr(data->game->img, &data->game->bits_per_pixel,
			&data->game->size_line, &data->game->endian);
	if (!game->addr)
		return (1);
	return (0);
}

void	init_player_var(t_player *player)
{
	player->pos_x = -1;
	player->pos_y = -1;
	player->dir_char = '\0';
}

int	player_found_pos(t_data *data, t_player *player)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (data->tab[i] != NULL)
	{
		j = 0;
		while (data->tab[i][j])
		{
			if (data->tab[i][j] == 'N' || data->tab[i][j] == 'S'
				|| data->tab[i][j] == 'E' || data->tab[i][j] == 'W')
			{
				player->pos_x = (double)j + 0.5;
				player->pos_y = (double)i + 0.5;
				player->dir_char = data->tab[i][j];
				count++;
			}
			j++;
		}
		i++;
	}
	return (count != 1);
}

void	init_player_dir_n(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = -1;
	player->plane_x = 0.70;
	player->plane_y = 0;
}

void	init_player_dir_s(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = 1;
	player->plane_x = -0.70;
	player->plane_y = 0;
}

void	init_player_dir_e(t_player *player)
{
	player->dir_x = 1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.70;
}

void	init_player_dir_w(t_player *player)
{
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = -0.70;
}

void	init_player_dir(t_player *player)
{
	if (player->dir_char == 'N')
		init_player_dir_n(player);
	else if (player->dir_char == 'S')
		init_player_dir_s(player);
	else if (player->dir_char == 'W')
		init_player_dir_w(player);
	else if (player->dir_char == 'E')
		init_player_dir_e(player);
}

int	init_player(t_data *data, t_player *player)
{
	init_player_var(player);
	if (player_found_pos(data, player))
		return (1);
	player->map_x = (int)player->pos_x;
	player->map_y = (int)player->pos_y;
	init_player_dir(player);
	return (0);
}

t_game	*init_game(t_data *data)
{
	t_game		*game;
	t_player	*player;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	if (init_mlx_game(game, data))
		return (NULL);
	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	data->player = player;
	if (init_player(data, player))
		return (NULL);
	return (game);
}
