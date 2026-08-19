/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:09:09 by hcissoko          #+#    #+#             */
/*   Updated: 2026/08/19 15:09:09 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_game(t_game *game)
{
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->img_ea)
		mlx_destroy_image(game->mlx, game->img_ea);
	if (game->img_we)
		mlx_destroy_image(game->mlx, game->img_we);
	if (game->img_so)
		mlx_destroy_image(game->mlx, game->img_so);
	if (game->img_no)
		mlx_destroy_image(game->mlx, game->img_no);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
}

void	free_all(t_data *data)
{
	if (data->player)
		free(data->player);
	if (data->game)
		free_game(data->game);
	if (data->tab)
		free_tab(data->tab, tab_len(data->tab));
	if (data->ceiling_color)
		free(data->ceiling_color);
	if (data->floor_color)
		free(data->floor_color);
	if (data->ea_path)
		free(data->ea_path);
	if (data->we_path)
		free(data->we_path);
	if (data->so_path)
		free(data->so_path);
	if (data->no_path)
		free(data->no_path);
	free(data);
}
