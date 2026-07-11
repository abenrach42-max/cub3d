/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enemxa <enemxa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 17:48:55 by abenrach          #+#    #+#             */
/*   Updated: 2026/07/11 22:00:01 by enemxa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int loads_images(t_data *data, t_game *game)
{
    int h;
    int w;

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

int     init_mlx_game(t_game *game, t_data *data)
{
    data->game = game;
    game->mlx = mlx_init();
    if (!game->mlx)
        return (1);
    game->win = mlx_new_window(game->mlx, 1920, 1080, "cub3d");
    if (!game->win)
        return (1);
    if (loads_images(data, game))
        return (1);
    return (0);
}

t_game  *init_game(t_data *data)
{
    t_game  *game;

    game = malloc(sizeof(t_game));
    if (!game)
        return (NULL);
    if (init_mlx_game(game, data))
        return (NULL);
    return (game);
}
